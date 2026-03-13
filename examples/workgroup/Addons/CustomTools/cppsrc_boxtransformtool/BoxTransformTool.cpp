///////////////////////////////////////////////////////////////////////////
//
// File: BoxTransformTool.cpp
//
// Description: This plugin implements the box transform tool.
//
// The tool can be invoked by typing BoxTransformTool at the command
// line or by assigning a hotkey to the BoxTransformTool custom script
// command in the keyboard mapping dialog.
//
// Copyright 2010 Autodesk, Inc. All rights reserved.
// Use of this software is subject to the terms of the Autodesk license
// agreement provided at the time of installation or download, or which
// otherwise accompanies this software in either electronic or hard copy
// form.
//
///////////////////////////////////////////////////////////////////////////
#include <vector>
#include <xsi_pluginregistrar.h>
#include <xsi_selection.h>
#include <xsi_kinematics.h>
#include <xsi_group.h>
#include <xsi_model.h>
#include <xsi_utils.h>
#include <xsi_menu.h>
#include <xsi_command.h>
#include <xsi_preferences.h>
#include "BoxTransformToolDelegate.h"
#include "ToolButton.h"
#include "ScaleToolHandle.h"
#include "ButtonToolHandle.h"
#include "TranslateToolHandle.h"
#include "DimensionToolHandle.h"
#include "RotateWheelToolHandle.h"
#include "RotateStickToolHandle.h"

////////////////////////////////////////////////////////////////////////////////
//
// LoadPlugin
//
////////////////////////////////////////////////////////////////////////////////

SICALLBACK XSILoadPlugin( PluginRegistrar& in_reg )
{
	in_reg.PutAuthor( L"Autodesk" );
	in_reg.PutName( L"BoxTransformTool Plugin" );
	in_reg.PutVersion( 1, 0 );

	// Tool
	in_reg.RegisterTool( L"BoxTransformTool" );

	// Command for recording box orientation for undo/redo
	in_reg.RegisterCommand( L"BoxTransformTool_UpdateOrientation" );

	// Register events that need to reset box orientation
	in_reg.RegisterEvent( L"BoxTransformTool_TimeChanged", siOnTimeChange );
	in_reg.RegisterEvent( L"BoxTransformTool_SelectionChanged", siOnSelectionChange );

	// Make tool accessible from the Transform menu
	in_reg.RegisterMenu( siMenuMCPTransformBottomID, L"BoxTransformTool_Menu", false, false );

	//RegistrationInsertionPoint - do not remove this line
	return CStatus::OK;
}

////////////////////////////////////////////////////////////////////////////////
//
// BoxTransformTool implementation
//
////////////////////////////////////////////////////////////////////////////////

class BoxTransformTool : public BoxTransformToolDelegate {
private: // Data
	typedef std::vector<ToolHandle *> HandleList;
	static BoxTransformTool * g_currentTool;
	static ULONG		g_selectionID;

	BBox				m_bbox;
	CRotation			m_bboxOri;
	CRotation			m_bboxSavedOri;
	ToolButton 			m_translateButton;
	ToolButton			m_rotateScaleButton;
	HandleList			m_handles;
	CRefArray			m_targets;
	CRefArray			m_expandedTargets;
	LONG				m_selectedIndex;
	ULONG				m_selectionID;
	bool				m_compatibleOri;
	bool				m_bboxOriDirty;

public: // Tool Methods
	enum ToolMode { kInvalidMode, kTranslateMode, kRotateScaleMode };

	BoxTransformTool()
	:	m_selectedIndex( kInvalidIndex )
	,	m_compatibleOri( false )
	,	m_bboxOriDirty( false )
	,	m_selectionID( 0 )
	{}

	~BoxTransformTool()
	{}

	CStatus Setup( ToolContext& in_ctxt )
	{
		// Called when tool is created
		CString slash = CUtils::Slash();

		CString texturePath;
#ifndef linux
		texturePath =  L".." + slash + L".." + slash; // On windows plugin is located two levels below...
#endif
		texturePath += L"textures" + slash;
		CString translatePath = texturePath + L"translate";
		CString rotateScalePath = texturePath + L"rotateScale";
		m_translateButton.Setup( translatePath.GetWideString(), 0/*index*/, 2/*total buttons*/);
		m_rotateScaleButton.Setup( rotateScalePath.GetWideString(), 1/*index*/, 2/*total buttons*/);
		in_ctxt.RegisterShortcutKey( kSwitchModeKey, L"Toggle Interaction Mode" );
		SetToolMode( kTranslateMode );
		g_currentTool = this;
		IncrementGlobalSelectionID();
		return CStatus::OK;
	}

	CStatus Cleanup( ToolContext& in_ctxt )
	{
		// Called when tool is destroyed
		m_translateButton.Cleanup();
		m_rotateScaleButton.Cleanup();
		ClearHandles();
		g_currentTool = NULL;
		return CStatus::OK;
	}

	CStatus Activate( ToolContext& in_ctxt )
	{
		// Called when tool becomes active
		in_ctxt.SetToolDescription( L"Box Transform Tool" );
		return CStatus::OK;
	}

	CStatus Deactivate( ToolContext& in_ctxt )
	{
		// Called when tool becomes inactive (i.e. another tool is activated in supra mode or tool exits)
		return CStatus::OK;
	}

	CStatus MouseDown( ToolContext& in_ctxt )
	{
		// Called when mouse button is pressed
		LONG x, y;
		in_ctxt.GetMousePosition( x, y );

		if ( in_ctxt.IsLeftButtonDown() )
		{
			UpdateSelectedHandle( in_ctxt );
			if ( m_selectedIndex != kInvalidIndex )
			{
				m_bboxOriDirty = false;
				m_bboxSavedOri = m_bboxOri;
				m_targets = GetTargetsFromSelection();
				m_expandedTargets = ExpandBranches( m_targets );
				m_handles[m_selectedIndex]->MouseDown( in_ctxt );
				return CStatus::OK;
			}
		}
		else if ( in_ctxt.IsRightButtonDown() )
		{
			in_ctxt.ShowContextMenu( x, y );
		}
		return CStatus::False; // Ignore other mouse buttons etc.
	}

	CStatus MouseDrag( ToolContext& in_ctxt )
	{
		// Called when mouse is moved with a mouse button pressed
		if ( m_selectedIndex != kInvalidIndex )
		{
			m_handles[m_selectedIndex]->MouseDrag( in_ctxt );
		}
		return CStatus::OK;
	}

	CStatus MouseUp( ToolContext& in_ctxt )
	{
		// Called when mouse button is released
		if ( m_selectedIndex != kInvalidIndex )
		{
			m_handles[m_selectedIndex]->MouseUp( in_ctxt );
			UpdateSelectedHandle( in_ctxt ); // Update highlight

			if ( m_bboxOriDirty )
			{
				// Generate command to track bbox orientation changes for undo/redo
				CValue result;
				double values[6];
				CValueArray args(6);
				m_bboxOri.GetXYZAngles( values[0], values[1], values[2] );
				m_bboxSavedOri.GetXYZAngles( values[3], values[4], values[5] );
				for ( int i = 0; i < 6; ++i ) args[i] = values[i];
				Application().ExecuteCommand( L"BoxTransformTool_UpdateOrientation", args, result );
				m_bboxOriDirty = false;
			}
		}
		return CStatus::OK;
	}

	CStatus MouseMove( ToolContext& in_ctxt )
	{
		// Called when mouse moves and we are not interacting
		if ( UpdateSelectedHandle( in_ctxt ) )
			in_ctxt.Redraw();
		return CStatus::OK;
	}

	CStatus Draw( ToolContext& in_ctxt )
	{
		// Update data
		if ( !in_ctxt.IsInteracting() )
		{
			// Note: For multiple object selections we do not detect when the transforms
			// change externally (e.g. through reset transform or some other command)
			// so in these circumstances the orientation will not be updated.
			if ( m_selectionID != g_selectionID )
			{
				// Selection has changed so recompute orientation
				m_targets = GetTargetsFromSelection();
				m_expandedTargets = ExpandBranches( m_targets );
				m_bboxOri = ComputeBBoxOrientation( m_targets, m_compatibleOri );
				m_selectionID = IncrementGlobalSelectionID();
			}
			else if ( m_compatibleOri )
			{
				// when dealing with compatible orientations always update
				m_bboxOri = ComputeBBoxOrientation( m_targets, m_compatibleOri );
			}	 
		}
		m_bbox = ComputeBBox( m_expandedTargets, m_bboxOri );
		
		// Draw 3D elements
		if ( !m_bbox.IsEmpty() )
		{
			// Draw bbox
			InitHeadlight( in_ctxt );
			glEnable( GL_DEPTH_TEST );
			SetGLColor( kBBoxColor );
			m_bbox.Draw( in_ctxt );

			// Draw normal handles
			glDepthMask( GL_TRUE );
			for ( LONG i = 0, count = (LONG)m_handles.size(); i < count; ++i )
			{
				if ( i == m_selectedIndex ) continue;
				ToolHandleID l_ID = m_handles[i]->HandleID();
				if ( l_ID >= kButtonHandleMinID && l_ID <= kButtonHandleMaxID ) continue;
				DrawHandle( in_ctxt, i );
			}
 
			// Draw selected handle
			if ( m_selectedIndex != kInvalidIndex )
			{
				DrawHandle( in_ctxt, m_selectedIndex );
			}

			// Draw button handles last
			for ( int i = kButtonHandleMinID; i <= kButtonHandleMaxID; ++i )
			{
				LONG index = GetHandleIndex( (ToolHandleID)i );
				if( index < 0 || index == m_selectedIndex ) continue;
				DrawHandle( in_ctxt, index );
			}

			// Cleanup
			glDepthMask( GL_FALSE );
			TermHeadlight( in_ctxt );
			glDisable( GL_DEPTH_TEST );
			LogOpenGLErrors();
		}
		return CStatus::OK;
	}

	CStatus ModifierChanged( ToolContext& in_ctxt )
	{
		// Called when modifer key is pressed or released
		return CStatus::OK;
	}

	CStatus SnapValid( ToolContext& in_ctxt )
	{
		// Called to validate targets during snapping
		CRef snapObject = in_ctxt.GetSnapObject();
		if ( snapObject.IsValid() )
		{
			// Don't snap to objects that we are manipulating
			for ( LONG i = 0, count = m_expandedTargets.GetCount(); i < count; ++i )
			{
				if ( snapObject == m_expandedTargets[i] )
					return CStatus::False;
			}
		}
		return CStatus::OK;
	}

	CStatus KeyDown( ToolContext& in_ctxt )
	{
		// Called when shortcut key pressed
		ULONG key = in_ctxt.GetShortcutKey();
		switch ( key ) {
		case kSwitchModeKey:
			SetToolMode( GetToolMode() == kTranslateMode ? kRotateScaleMode : kTranslateMode );
			in_ctxt.Redraw();
			break;
		default:
			break;
		}
		return CStatus::OK;
	}

	CStatus KeyUp( ToolContext& in_ctxt )
	{
		// Called when shortcut key released
		return CStatus::OK;
	}

	CStatus MenuInit( ToolContext& in_ctxt )
	{
		MenuItem menuItem;
		Menu menu = in_ctxt.GetSource();
		menu.AddCallbackItem( L"Next Manipulator\tTab", L"BoxTransformTool_ToggleMode", menuItem );
		menu.AddSeparatorItem();
		menu.AddCallbackItem( L"Translate", L"BoxTransformTool_TranslateMode", menuItem );
		menuItem.PutChecked( GetToolMode() == kTranslateMode );
		menu.AddCallbackItem( L"Scale", L"BoxTransformTool_RotateScaleMode", menuItem );
		menuItem.PutChecked( GetToolMode() == kRotateScaleMode );
		return CStatus::OK;
	}

	CStatus TranslateMode( ToolContext& in_ctxt )
	{
		if ( GetToolMode() != kTranslateMode )
		{
			SetToolMode( kTranslateMode );
			in_ctxt.Redraw();
		}
		return CStatus::OK;
	}

	CStatus RotateScaleMode( ToolContext& in_ctxt )
	{
		if ( GetToolMode() != kRotateScaleMode )
		{
			SetToolMode( kRotateScaleMode );
			in_ctxt.Redraw();
		}
		return CStatus::OK;
	}

	CStatus ToggleMode( ToolContext& in_ctxt )
	{
		SetToolMode( GetToolMode() != kTranslateMode ? kTranslateMode : kRotateScaleMode );
		in_ctxt.Redraw();
		return CStatus::OK;
	}

public: // Delegate methods (used by handles)
	const BBox & GetBBox()
	{
		return m_bbox;
	}

	CVector3 GetCenter()
	{
		return m_bbox.GetCenter( true/*world*/ ); // TODO - use object's center
	}

	CRefArray GetTargets()
	{
		return m_targets;
	}

	void SelectToolButton( ToolHandleID in_HandleID )
	{
		SetToolMode( in_HandleID == kTranslateButtonID ? kTranslateMode : kRotateScaleMode );
	}

	void UpdateBBoxOrientation( const CRotation &in_rot )
	{
		m_bboxOri = in_rot;
		m_bboxOriDirty = true;
	}

public: // Other public methods
	const CRotation & GetBBoxOrientation()
	{
		return m_bboxOri;
	}

	LONG GetSelectionID()
	{
		return m_selectionID;
	}

	static BoxTransformTool * CurrentTool()
	{
		return g_currentTool;
	}

	static ULONG IncrementGlobalSelectionID()
	{
		if ( ++g_selectionID == 0 )
			++g_selectionID; // Reserve 0 as an invalid ID
		return g_selectionID;
	}

private: // Helper methods
	CRotation ComputeBBoxOrientation( const CRefArray &in_list, bool &out_compatible )
	{
		CRotation result;
		if ( in_list.GetCount() > 0 )
		{
			X3DObject object = in_list[0];
			CRotation rotation = object.GetKinematics().GetGlobal().GetTransform().GetRotation();
			for ( LONG i = 1, count = in_list.GetCount(); i < count; ++i )
			{
				object = in_list[i];
				CRotation otherRotation = object.GetKinematics().GetGlobal().GetTransform().GetRotation();
				if ( !rotation.EpsilonEquals( otherRotation, 1.0e-3 ) )
				{
					out_compatible = false;
					return result; // No match -> identity
				}
			}
			result = rotation;
		}
		out_compatible = true;
		return result;
	}

	BBox ComputeBBox( const CRefArray &in_list, const CRotation &in_bboxOri )
	{
		BBox result;
		CTransformation bboxTransfo;
		bboxTransfo.SetRotation( in_bboxOri );
		result.SetTransform( bboxTransfo );
		CMatrix4 worldToBBox = result.GetInverseTransform().GetMatrix4();

		for ( LONG i = 0, count = in_list.GetCount(); i < count; ++i )
		{
			Model model = in_list[i];
			X3DObject object = in_list[i];

			// Note: Use Matrix4 when multiplying because we don't want Softimage scaling when transforming between different object spaces
			CTransformation objToBBox;
			objToBBox.SetMatrix4( object.GetKinematics().GetGlobal().GetTransform().GetMatrix4().MulInPlace( worldToBBox ) );
			if ( !model.IsValid() || model.GetModelKind() != siModelKind_Instance )
			{
				// Regular object
				double minx, miny, minz, maxx, maxy, maxz;
				if ( object.GetBoundingBox( minx, miny, minz, maxx, maxy, maxz, objToBBox ) == CStatus::OK )
				{
					result.IncludePoint( CVector3(minx, miny, minz) );
					result.IncludePoint( CVector3(maxx, maxy, maxz) );
				}
			}
			else
			{
				// Instance
				CTransformation identity;
				double minx, miny, minz, maxx, maxy, maxz;
				Model instance = model.GetInstanceMaster();
				if ( instance.IsValid() && instance.GetBoundingBox( minx, miny, minz, maxx, maxy, maxz, objToBBox, true/*include children*/ ) == CStatus::OK )
				{
					result.IncludePoint( CVector3(minx, miny, minz) );
					result.IncludePoint( CVector3(maxx, maxy, maxz) );
				}
			}
		}
		return result;
	}

	CRefArray GetTargetsFromSelection()
	{
		// Get a list of selected 3D objects (and expand groups)
		const CString empty;
		CStringArray families;
		CRefArray selection, flattened;
		families.Add( si3DObjectFamily );
		families.Add( siGroupFamily );
		Application().GetSelection().GetArray().Filter( empty, families, empty, selection );

		for ( LONG i = 0, count = selection.GetCount(); i < count; ++i )
		{
			Group group = selection[i];
			if ( group.IsValid() ) { // Group
				flattened += group.GetExpandedMembers();
			} else { // Object
				flattened.Add( selection[i] );
			}
		}
		return flattened;
	}

	CRefArray ExpandBranches( const CRefArray &in_list )
	{
		// Expand branches in input list
		const CString empty;
		CStringArray families;
		CRefArray flattened;
		families.Add( si3DObjectFamily );
		for ( LONG i = 0, count = in_list.GetCount(); i < count; ++i )
		{
			X3DObject object = in_list[i];
			if ( object.GetBranchFlag() != siBranch ) {
				flattened.Add( in_list[i] );
			} else { // Expand branch (includes this object through primitive)
				flattened.Add( in_list[i] );
				flattened += object.FindChildren2( empty, empty, families ); 
			}
		}
		return flattened;
	}

	ToolMode GetToolMode()
	{
		return m_translateButton.IsSelected() ? kTranslateMode : m_rotateScaleButton.IsSelected() ? kRotateScaleMode : kInvalidMode;
	}

	void SetToolMode( ToolMode in_Mode )
	{
		if ( in_Mode != GetToolMode() )
		{
			ClearHandles();
			switch( in_Mode ) {
			case kTranslateMode:
				m_rotateScaleButton.SetSelected( false );
				m_translateButton.SetSelected( true );
				CreateTranslateHandles();
				break;
			case kRotateScaleMode:
				m_translateButton.SetSelected( false );
				m_rotateScaleButton.SetSelected( true );
				CreateScaleHandles();
				break;
			}
			CreateRotateHandles();
			CreateScaleDimensionHandles();
			CreateButtonHandles();
		}
	}

	bool UpdateSelectedHandle( ToolContext &in_ctxt )
	{
		LONG index = GetHandleIndex( PickHandleUnderMouse( in_ctxt ) );
		if ( index != m_selectedIndex )
		{
			CString toolMsg = L"Box Transform Tool\n";

			if ( m_selectedIndex != kInvalidIndex )
				m_handles[m_selectedIndex]->SetSelected(false);

			m_selectedIndex = index;

			if ( m_selectedIndex != kInvalidIndex )
			{
				m_handles[m_selectedIndex]->SetSelected(true);
				toolMsg += m_handles[m_selectedIndex]->GetHandleDescription();
			}

			in_ctxt.SetToolDescription( toolMsg + L"\n\nContext Menu" );
			return true; // selected handle changed
		}
		return false; // selected handle unchanged
	}

	void ClearHandles()
	{
		m_selectedIndex = kInvalidIndex;
		for ( LONG i = 0, count = (LONG)m_handles.size(); i < count; ++i )
		{
			m_handles[i]->Cleanup();
			delete m_handles[i];
		}
		m_handles.clear();
	}

	LONG GetHandleIndex( ToolHandleID in_HandleID )
	{
		if ( in_HandleID != kInvalidHandleID )
		{
			for ( LONG i = 0, count = (LONG)m_handles.size(); i < count; ++i )
			{
				if ( m_handles[i]->HandleID() == in_HandleID )
					return i;
			}
		}
		return -1;
	}

	void CreateButtonHandles()
	{
		m_handles.push_back( new ButtonToolHandle(this, kTranslateButtonID, &m_translateButton) );
		m_handles.push_back( new ButtonToolHandle(this, kRotateScaleButtonID, &m_rotateScaleButton) );
	}

	void CreateTranslateHandles()
	{
		for ( int i = kTranslateHandleMinID; i <= kTranslateHandleMaxID; ++i )
			m_handles.push_back( new TranslateToolHandle(this, (ToolHandleID)i) );
	}

	void CreateRotateHandles()
	{
		m_handles.push_back( new RotateWheelToolHandle(this, kRotateWheelID) );
		m_handles.push_back( new RotateStickToolHandle(this, kRotateStickID) );
	}

	void CreateScaleHandles()
	{
		for ( int i = kScaleHandleMinID; i <= kScaleHandleMaxID; ++i )
			m_handles.push_back( new ScaleToolHandle(this, (ToolHandleID)i) );
	}

	void CreateScaleDimensionHandles()
	{
		for (int i = kDimensionScaleXID; i <= kDimensionScaleZID; ++i)
			m_handles.push_back( new DimensionToolHandle(this, (ToolHandleID)i) );
	}

	void DrawHandle( ToolContext &in_ctxt, LONG index )
	{
		if ( m_handles[index]->RequiresViewDraw() )
			in_ctxt.BeginViewDraw();
		else
			in_ctxt.EndViewDraw();
		m_handles[index]->Draw( in_ctxt );
	}

	ToolHandleID PickHandleUnderMouse( ToolContext &in_ctxt )
	{
		LONG x, y;
		ToolHandleID l_HandleID = kInvalidHandleID;
		if ( !m_bbox.IsEmpty() && in_ctxt.GetMousePosition( x, y ) == CStatus::OK )
		{
			if ( in_ctxt.BeginPickDraw( x, y, kPickSize, kPickSize ) == CStatus:: OK )
			{
				// Setup pick buffer
				#define MAXSELECT 512
				GLuint l_SelectBuffer[MAXSELECT];
				glSelectBuffer( MAXSELECT, l_SelectBuffer );
				glRenderMode( GL_SELECT );
				glInitNames();
				glPushName(0);

				// Draw handles for picking (use reverse drawing order so buttons have highest priority)
				for ( LONG i = ((LONG)m_handles.size())-1; i >= 0; --i )
				{
					glLoadName( m_handles[i]->HandleID() );
					DrawHandle( in_ctxt, i );
				}

				// Process hits
				glPopName();
				GLuint *ptr = l_SelectBuffer;
				GLuint l_MinDepth = UINT_MAX; // Initialize to farthest
				GLuint l_NumHits = glRenderMode( GL_RENDER );
				for (GLuint i = 0; i < l_NumHits; ++i )
				{
					GLuint l_NumIDs = *ptr++;
					GLuint l_MinZ   = *ptr++;
					GLuint l_MaxZ   = *ptr++;
					if (l_NumIDs > 0)
					{
						ToolHandleID l_ID = (ToolHandleID)*ptr++;
						ptr += l_NumIDs-1;
						
						// 2D handles are in front of everything else
						if ( m_handles[GetHandleIndex(l_ID)]->RequiresViewDraw() )
						{
							// Exception: treat dimension (text) handles as lower priority
							l_MinZ = l_MaxZ = ( l_ID >= kDimensionScaleXID && l_ID <= kDimensionScaleZID ? UINT_MAX-1 : 0 );
						}

						if ( l_MinZ < l_MinDepth )
						{
							// This is the closest handle so far
							l_HandleID = l_ID;
							l_MinDepth = l_MinZ;
						}
					}
				}
				LogOpenGLErrors();
				in_ctxt.EndPickDraw();
			}
		}
		return l_HandleID;
	}

	void InitHeadlight( ToolContext &in_ctxt )
	{
		TermHeadlight( in_ctxt ); // Disable existing lights
		CVector3 l_Pos( -1, 0, -2 );
		in_ctxt.CameraToWorld( l_Pos, l_Pos );
		GLfloat lightColor[]   = { 1.0, 1.0, 1.0, 1.0 };
		GLfloat ambientColor[] = { 0.2, 0.2, 0.2, 1.0 };
		GLfloat noColor[]      = { 0.0, 0.0, 0.0, 0.0 };
		GLfloat position[]     = { (GLfloat)l_Pos.GetX(), (GLfloat)l_Pos.GetY(), (GLfloat)l_Pos.GetZ(), 0.0 };
		glLightfv( GL_LIGHT0, GL_POSITION, position );
		glLightfv( GL_LIGHT0, GL_DIFFUSE,  lightColor );
		glLightfv( GL_LIGHT0, GL_SPECULAR, noColor );
		glLightf(  GL_LIGHT0, GL_SPOT_EXPONENT, 0.0 );
		glLightModelfv( GL_LIGHT_MODEL_AMBIENT, ambientColor );
		glEnable( GL_LIGHT0 );
	}

	void TermHeadlight( ToolContext &in_ctxt )
	{
		GLint l_MaxLights = 8;
		GLfloat noColor[] = { 0.0, 0.0, 0.0, 0.0 };
		GLfloat ambientColor[] = { 0.0, 0.0, 0.0, 1.0 };
		glLightModelfv( GL_LIGHT_MODEL_AMBIENT, ambientColor );
		glGetIntegerv( GL_MAX_LIGHTS, &l_MaxLights );
		for (GLint i = 0; i < l_MaxLights; ++i )
		{
			glDisable( GL_LIGHT0 + i );
			glLightfv( GL_LIGHT0 + i, GL_DIFFUSE,  noColor );
			glLightfv( GL_LIGHT0 + i, GL_SPECULAR, noColor );
			glLightfv( GL_LIGHT0 + i, GL_AMBIENT,  noColor );
		}
	}

	bool LogOpenGLErrors( const CString &extraInfo = CString() )
	{
		bool l_bError = false;
		for ( GLenum error; (error = glGetError()) != GL_NO_ERROR; )
		{
			const char *msg = (const char *)gluErrorString( error );
			CString errorMsg = L"BoxTransformTool: OpenGL error - ";
			errorMsg += ( msg ? msg : "unknown error" );
			if ( !extraInfo.IsEmpty() )
			{
				errorMsg += " (";
				errorMsg += extraInfo;
				errorMsg += ")";
			}
			Application().LogMessage( errorMsg, siWarningMsg );
			l_bError = true;
		}
		return l_bError;
	}
};

// Static data
/*static*/ BoxTransformTool *	BoxTransformTool::g_currentTool = NULL;
/*static*/ ULONG				BoxTransformTool::g_selectionID = 0;


////////////////////////////////////////////////////////////////////////////////
//
// Command to update bbox orientation (handles undo/redo)
//
////////////////////////////////////////////////////////////////////////////////

class BoxTransformTool_UpdateOrientation  {
private: // Data
	ULONG				m_selectId;
	CRotation			m_oldOri;
	CRotation			m_newOri;

public: // Tool Methods

	BoxTransformTool_UpdateOrientation()
	:	m_selectId( 0 )
	{}

	~BoxTransformTool_UpdateOrientation()
	{}

	CStatus Execute( Context& in_ctxt )
	{
		CValueArray args = in_ctxt.GetAttribute(L"Arguments");
		BoxTransformTool *l_pTool = BoxTransformTool::CurrentTool();
		if ( l_pTool )
		{
			m_selectId = l_pTool->GetSelectionID();
			m_newOri = CRotation( args[0], args[1], args[2] );
			m_oldOri = CRotation( args[3], args[4], args[5] );
		}
		return CStatus::OK;
	}

	CStatus Undo( Context& in_ctxt )
	{
		BoxTransformTool *l_pTool = BoxTransformTool::CurrentTool();
		if ( l_pTool && l_pTool->GetSelectionID() == m_selectId )
		{
			l_pTool->UpdateBBoxOrientation( m_oldOri );
		}
		return CStatus::OK;
	}

	CStatus Redo( Context& in_ctxt )
	{
		BoxTransformTool *l_pTool = BoxTransformTool::CurrentTool();
		if ( l_pTool && l_pTool->GetSelectionID() == m_selectId )
		{
			l_pTool->UpdateBBoxOrientation( m_newOri );
		}
		return CStatus::OK;
	}
};


////////////////////////////////////////////////////////////////////////////////
//
// Plugin callbacks
//
////////////////////////////////////////////////////////////////////////////////

SICALLBACK BoxTransformTool_Menu_Init( CRef& in_ctxt )
{
	Context ctxt( in_ctxt );
 	MenuItem menuItem;
 	Menu menu = ctxt.GetSource();
 	menu.AddCommandItem( L"Box Transform Tool", L"BoxTransformTool", menuItem );
 	return true;
}

////////////////////////////////////////////////////////////////////////////////
// Tool callbacks
////////////////////////////////////////////////////////////////////////////////

SICALLBACK BoxTransformTool_Init( CRef& in_ctxt )
{
	ToolContext l_ctxt( in_ctxt );

	// Create an instance of our tool
	BoxTransformTool *l_pTool = new BoxTransformTool;
	if ( !l_pTool ) return CStatus::Fail;
	l_ctxt.PutUserData( CValue((CValue::siPtrType)l_pTool) );
	return CStatus::OK;
}

SICALLBACK BoxTransformTool_Term( CRef& in_ctxt )
{
	ToolContext l_ctxt( in_ctxt );
	BoxTransformTool *l_pTool = (BoxTransformTool *)(CValue::siPtrType)l_ctxt.GetUserData();
	if ( !l_pTool ) return CStatus::Fail;
	delete l_pTool;
	l_ctxt.PutUserData( CValue((CValue::siPtrType)NULL) ); // Clear user data
	return CStatus::OK;
}

#define DECLARE_TOOL_CALLBACK(TOOL,CALLBACK) \
SICALLBACK TOOL##_##CALLBACK( ToolContext& in_ctxt ) { \
	TOOL *l_pTool = (TOOL *)(CValue::siPtrType)in_ctxt.GetUserData(); \
	return ( l_pTool ? l_pTool->CALLBACK( in_ctxt ) : CStatus::Fail ); \
}

DECLARE_TOOL_CALLBACK( BoxTransformTool, Setup );
DECLARE_TOOL_CALLBACK( BoxTransformTool, Cleanup );
DECLARE_TOOL_CALLBACK( BoxTransformTool, Activate );
DECLARE_TOOL_CALLBACK( BoxTransformTool, Deactivate );
DECLARE_TOOL_CALLBACK( BoxTransformTool, MouseDown );
DECLARE_TOOL_CALLBACK( BoxTransformTool, MouseDrag );
DECLARE_TOOL_CALLBACK( BoxTransformTool, MouseUp );
DECLARE_TOOL_CALLBACK( BoxTransformTool, MouseMove );
DECLARE_TOOL_CALLBACK( BoxTransformTool, Draw );
DECLARE_TOOL_CALLBACK( BoxTransformTool, ModifierChanged );
DECLARE_TOOL_CALLBACK( BoxTransformTool, SnapValid );
DECLARE_TOOL_CALLBACK( BoxTransformTool, KeyDown );
DECLARE_TOOL_CALLBACK( BoxTransformTool, KeyUp );
DECLARE_TOOL_CALLBACK( BoxTransformTool, MenuInit );
DECLARE_TOOL_CALLBACK( BoxTransformTool, TranslateMode );
DECLARE_TOOL_CALLBACK( BoxTransformTool, RotateScaleMode );
DECLARE_TOOL_CALLBACK( BoxTransformTool, ToggleMode );


////////////////////////////////////////////////////////////////////////////////
// Command callbacks
////////////////////////////////////////////////////////////////////////////////

SICALLBACK BoxTransformTool_UpdateOrientation_Init( CRef& in_ctxt )
{
   Context ctxt( in_ctxt );
   Command cmd = ctxt.GetSource();
   ArgumentArray args = cmd.GetArguments();
   args.Add(L"NewRotX", CValue(0.0f) );
   args.Add(L"NewRotY", CValue(0.0f) );
   args.Add(L"NewRotZ", CValue(0.0f) );
   args.Add(L"OldRotX", CValue(0.0f) );
   args.Add(L"OldRotY", CValue(0.0f) );
   args.Add(L"OldRotZ", CValue(0.0f) );
   return CStatus::OK;
}

SICALLBACK BoxTransformTool_UpdateOrientation_Execute( CRef& in_ctxt )
{
	Context l_ctxt( in_ctxt );
	BoxTransformTool_UpdateOrientation *l_pCmd = new BoxTransformTool_UpdateOrientation;
	if ( !l_pCmd ) return CStatus::OK;
	bool bUndoRequired = l_ctxt.GetAttribute( L"UndoRequired" );
	l_pCmd->Execute( l_ctxt );
	if ( bUndoRequired )
		l_ctxt.PutAttribute( L"UndoRedoData", (CValue::siPtrType)l_pCmd );
	else
		delete l_pCmd; // No undo required
	return CStatus::OK;
}

SICALLBACK BoxTransformTool_UpdateOrientation_TermUndoRedo( CRef& in_ctxt )
{
	Context l_ctxt( in_ctxt );
	BoxTransformTool_UpdateOrientation *l_pCmd = (BoxTransformTool_UpdateOrientation *)(CValue::siPtrType)l_ctxt.GetAttribute(L"UndoRedoData");
	if ( !l_pCmd ) return CStatus::OK;
	delete l_pCmd;
	l_ctxt.PutAttribute( L"UndoRedoData", (CValue::siPtrType)NULL ); // Probably not needed...
	return CStatus::OK;
}

SICALLBACK BoxTransformTool_UpdateOrientation_Undo( CRef& in_ctxt )
{
	Context l_ctxt( in_ctxt );
	BoxTransformTool_UpdateOrientation *l_pCmd = (BoxTransformTool_UpdateOrientation *)(CValue::siPtrType)l_ctxt.GetAttribute(L"UndoRedoData");
	if ( !l_pCmd ) return CStatus::OK;
	l_pCmd->Undo( l_ctxt );
	return CStatus::OK;
}

SICALLBACK BoxTransformTool_UpdateOrientation_Redo( CRef& in_ctxt )
{
	Context l_ctxt( in_ctxt );
	BoxTransformTool_UpdateOrientation *l_pCmd = (BoxTransformTool_UpdateOrientation *)(CValue::siPtrType)l_ctxt.GetAttribute(L"UndoRedoData");
	if ( !l_pCmd ) return CStatus::OK;
	l_pCmd->Redo( l_ctxt );
	return CStatus::OK;
}

SICALLBACK BoxTransformTool_TimeChanged_OnEvent( CRef& in_ctxt )
{
	// Make sure tool resets orientation
	BoxTransformTool::IncrementGlobalSelectionID();
	return CStatus::OK;
}

SICALLBACK BoxTransformTool_SelectionChanged_OnEvent( CRef& in_ctxt )
{
	// Make sure tool resets orientation
	BoxTransformTool::IncrementGlobalSelectionID();
	return CStatus::OK;
}
