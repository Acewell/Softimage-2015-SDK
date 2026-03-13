///////////////////////////////////////////////////////////////////////////
//
// File: BoneCreateTool.cpp
//
// Description: Box transform bounding box helper class
//
// Copyright 2011 Autodesk, Inc. All rights reserved.
// Use of this software is subject to the terms of the Autodesk license
// agreement provided at the time of installation or download, or which
// otherwise accompanies this software in either electronic or hard copy
// form.
//
///////////////////////////////////////////////////////////////////////////
#include <xsi_application.h>
#include <xsi_context.h>
#include <xsi_pluginregistrar.h>
#include <xsi_status.h>
#ifndef linux
#define WIN32_LEAN_AND_MEAN
#include <windows.h> // Needed for OpenGL on windows
#endif
#include <GL/gl.h>
#include <xsi_math.h>
#include <xsi_argument.h>
#include <xsi_toolcontext.h>
#include <xsi_menu.h>
#include <xsi_menuitem.h>
#include <xsi_model.h>
#include <xsi_kinematics.h>
#include <xsi_primitive.h>
#include <xsi_utils.h>
#include <xsi_preferences.h>
#include <xsi_command.h>

using namespace XSI::MATH; 
using namespace XSI; 

////////////////////////////////////////////////////////////////////////////////
//
// BoneCreateTool
//
////////////////////////////////////////////////////////////////////////////////
#define BONE_PARAM_LENGTH		L"length"
#define EPSILON							0.0001
#define MIN_BONE_LENGTH 0.01

namespace 
{
	CString Translate( const CString &in_string )
	{
		CString translated = CUtils::Translate( in_string, L"XSIVIEWINTERACTION" );
		return !translated.IsEmpty() ? translated : in_string;
	}
}



class BoneCreateTool {
private: // Data
	static BoneCreateTool * g_currentTool;

	CPlane						m_manipPlane;		// Manipulation plane
	CVector3					m_BonePos;			// Temp store for the Bone position during a single click
	X3DObject					m_objBone;			// The current Bone primitive being created
	CTransformation				m_transform;		// The base transform to apply when orientating the bone
	CVector3					m_vProjectedBoneDir;		// direction of the bone after it is projected onto manipulation plane
	CVector3					m_RootPos;			//Position of the bone chain root

	X3DObject					m_objParentBone;		// The parent Bone primitive
	X3DObject					m_objRootBone;			// The first bone in the current chain
	// Add tool data members here...

	// Converts the mouse position to the 3D world position
	CStatus ScreenTo3DWorldPosition( ToolContext& in_ctxt, LONG x, LONG y, CVector3 &out_Pos )
	{
		CVector3 l_Pos;
		if ( in_ctxt.GetWorldPosition( x, y, l_Pos ) == CStatus::OK )
		{
			// Reject points behind the camera
			CVector3 l_cameraPos;
			if ( in_ctxt.WorldToCamera( l_Pos, l_cameraPos ) == CStatus::OK && l_cameraPos.GetZ() < 0.0 )
			{
				out_Pos = l_Pos;
				return CStatus::OK;
			}
		}
		return CStatus::False;
	}

	// Utility function to compute the rotation transform for a bone to a new orientation
	// Uses the bonetool's current manipulation plane to resolve any problems with the rotation
	// objBone : the bone to get the current orientation from
	// vDir : The direction to point towards
	void ComputeRotationTransform( const X3DObject &objBone, CVector3 in_vDir, CTransformation &out_transform )
	{
		// determine the axis of rotation
		CVector3 l_vAxis;
		l_vAxis.Cross( m_vProjectedBoneDir, in_vDir );
		if ( l_vAxis.EpsilonEquals( CVector3( 0, 0, 0), EPSILON ) )
		{
			l_vAxis = m_manipPlane.GetNormal();
			in_vDir.NormalizeInPlace();
			if ( !m_vProjectedBoneDir.EpsilonEquals( in_vDir, EPSILON ) )
				l_vAxis.NegateInPlace();
		}

		// determine the angle to rotate to orientate the bone
		double l_dAngle = in_vDir.GetAngle( m_vProjectedBoneDir );
		out_transform.SetRotationFromAxisAngle( l_vAxis, l_dAngle );
	}

	void DrawChainRoot(ToolContext &in_ctxt)
	{
		if (m_objRootBone.IsValid())
		{
			//update position from rootbone
			KinematicState interestKine = m_objRootBone.GetKinematics().GetGlobal();
			m_RootPos.Set(interestKine.GetParameterValue( L"posx" ), 
						interestKine.GetParameterValue( L"posy" ), 
						interestKine.GetParameterValue( L"posz" ));
		}

		glColor4f( 1.0f, 1.0f, 1.0f, 1.0f);
		glBegin( GL_LINES );
			glVertex3d( m_RootPos.GetX()-1, m_RootPos.GetY(), m_RootPos.GetZ() );
			glVertex3d( m_RootPos.GetX()+1, m_RootPos.GetY(), m_RootPos.GetZ() );
			glVertex3d( m_RootPos.GetX(), m_RootPos.GetY()-1, m_RootPos.GetZ() );
			glVertex3d( m_RootPos.GetX(), m_RootPos.GetY()+1, m_RootPos.GetZ() );
			glVertex3d( m_RootPos.GetX(), m_RootPos.GetY(), m_RootPos.GetZ()-1 );
			glVertex3d( m_RootPos.GetX(), m_RootPos.GetY(), m_RootPos.GetZ()+1 );
		glEnd();
	}
public: // Methods
	BoneCreateTool()
	{}

	~BoneCreateTool()
	{}

	CStatus Setup( ToolContext& in_ctxt )
	{
		// Called when tool is created
		g_currentTool = this;
		return CStatus::OK;
	}

	CStatus Cleanup( ToolContext& in_ctxt )
	{
		// Called when tool is destroyed
		g_currentTool = NULL;
		return CStatus::OK;
	}

	CStatus Activate( ToolContext& in_ctxt )
	{
		// Called when tool becomes the active tool
		in_ctxt.SetCursor( siPenCursor );

		// Uncomment this to enable standard tool snapping behaviour
		in_ctxt.EnableSnapping( true );

		//Uncomment this to setup a custom tool shortcut key
		//in_ctxt.RegisterShortcutKey( 0x09/*Tab*/, L"Tab" );

		// Set custom status message
		in_ctxt.SetToolDescription( Translate(L"Draw Bones\nAdd Bone\nEnd Chain\nEnd Chain and Exit Tool") );

		return CStatus::OK;
	}

	CStatus Deactivate( ToolContext& in_ctxt )
	{
		// Called when tool becomes inactive (e.g. when user orbits using nav or chooses another tool)
		return CStatus::OK;
	}

	CStatus MouseDown( ToolContext& in_ctxt )
	{
		// Called when mouse button is pressed
		LONG x, y;
		in_ctxt.GetMousePosition( x, y );

		if ( in_ctxt.IsLeftButtonDown() )
		{
			// Use visible grid as default projection (not view plane)
			in_ctxt.GetViewPlane( m_manipPlane );

			// determine the direction of the bone projected on the project pt to the manip plane
			m_vProjectedBoneDir.Cross( CVector3( 0,1,0 ), m_manipPlane.GetNormal() );
			if ( m_vProjectedBoneDir.EpsilonEquals( CVector3( 0, 0, 0 ), EPSILON ) )
			{
				// give it a default direction if parallel
				m_vProjectedBoneDir = CVector3( 1,0,0 );
			}

			// Get projected 3D point
			CVector3 l_Pos;
			if (ScreenTo3DWorldPosition( in_ctxt, x, y, l_Pos) == CStatus::OK)
			{
				if ( !m_objParentBone.IsValid() )
				{
					// do the initial setup for bone chain creation
					m_objBone = Application().GetActiveSceneRoot();

					// Store the root position to mark with a null
					m_RootPos = l_Pos;
					m_objRootBone.ResetObject();

					return CStatus::OK;
				}

				// determine the signed angle to rotate around the y-axis to align the bone to the manip plane
				double l_dAngle = atan2( -m_vProjectedBoneDir.GetZ(), m_vProjectedBoneDir.GetX() );
				m_transform.SetRotY( RadiansToDegrees( l_dAngle ) );

				// Create a bone (and parent it if required)
				CValue l_AutoInspect, l_CmdLog;
				Application().GetPreferences().GetPreferenceValue( L"Interaction.autoinspect", l_AutoInspect );
				Application().GetPreferences().GetPreferenceValue( L"scripting.cmdlog", l_CmdLog );

				Application().GetPreferences().SetPreferenceValue( L"Interaction.autoinspect", in_ctxt.IsControlKeyDown() );
				Application().GetPreferences().SetPreferenceValue( L"scripting.cmdlog", true );
				CValue retval;
				CValueArray args(3);
				args[0] = L"Bone";
				args[1] = L"";
				if ( m_objParentBone.IsValid() )
					args[2] = m_objParentBone.GetName();
				else
					// parent bone might have been deleted already. Just let it go into scene root.
					args[2] = L"";
				Application().ExecuteCommand( L"GetPrim", args, retval );
				m_objBone = X3DObject( retval );
				Application().GetPreferences().SetPreferenceValue( L"scripting.cmdlog", l_CmdLog );
				Application().GetPreferences().SetPreferenceValue( L"Interaction.autoinspect", l_AutoInspect );

				if ( m_objBone.IsValid() )
				{
					CRefArray l_arrBone;
					l_arrBone.Add( m_objBone.GetRef() );
					in_ctxt.BeginTransformUpdate( l_arrBone );

					// Set initial position
					KinematicState kineLocal = m_objBone.GetKinematics().GetLocal();

					// find the initial position from the tip of the parent bone
					if ( m_objParentBone.IsKindOf( L"bone") )
					{
						kineLocal.GetParameter(L"posx").PutValue(m_objParentBone.GetActivePrimitive().GetParameterValue( BONE_PARAM_LENGTH ));
						kineLocal.GetParameter(L"posy").PutValue(CValue(0));
						kineLocal.GetParameter(L"posz").PutValue(CValue(0));
					}
					else
					{
						// parent bone is not a bone, ie. the scene root. So this is the first bone in a new chain
						kineLocal.GetParameter(L"posx").PutValue(m_RootPos.GetX());
						kineLocal.GetParameter(L"posy").PutValue(m_RootPos.GetY());
						kineLocal.GetParameter(L"posz").PutValue(m_RootPos.GetZ());
					}

					KinematicState kineGlobal = m_objBone.GetKinematics().GetGlobal();
					m_BonePos = CVector3(kineGlobal.GetParameterValue(L"posx"), kineGlobal.GetParameterValue(L"posy"), kineGlobal.GetParameterValue(L"posz"));

					Primitive l_primBone = m_objBone.GetActivePrimitive();
					if ( l_primBone.IsValid() )
					{
						Parameter bonelength = l_primBone.GetParameter( BONE_PARAM_LENGTH );
						in_ctxt.BeginParameterUpdate( bonelength );

						// Update bone length
						l_Pos.SubInPlace( m_BonePos );
						double l_dNewLength = l_Pos.GetLength();
						if (l_dNewLength < MIN_BONE_LENGTH)
						{
							l_dNewLength = MIN_BONE_LENGTH;
						}
						in_ctxt.UpdateParameter( bonelength, l_dNewLength );

						CTransformation l_transform;
						ComputeRotationTransform( m_objBone, l_Pos, l_transform );
						l_transform.Mul( m_transform, l_transform );

						in_ctxt.UpdateTransform( l_arrBone, l_transform, siRot );
					}
				}
			}
		}
		return CStatus::OK;
	}

	CStatus MouseDrag( ToolContext& in_ctxt )
	{
		// Called when mouse is moved with a mouse button pressed
		LONG x, y;
		in_ctxt.GetMousePosition( x, y );

		if ( in_ctxt.IsLeftButtonDown() )
		{
			// Move in plane
			CVector3 l_Pos;
			if (m_objBone.IsValid() && ScreenTo3DWorldPosition( in_ctxt, x, y, l_Pos) == CStatus::OK)
			{
				if ( m_objBone.IsKindOf( L"bone" ) )
				{
					// Update bone length
					l_Pos.SubInPlace( m_BonePos );
					double l_dNewLength = l_Pos.GetLength();
					if (l_dNewLength < MIN_BONE_LENGTH) l_dNewLength = MIN_BONE_LENGTH;

					Primitive l_primBone = m_objBone.GetActivePrimitive();
					in_ctxt.UpdateParameter( l_primBone.GetParameter( BONE_PARAM_LENGTH ), l_dNewLength );

					// Update bone orientation
					CTransformation l_transform;
					ComputeRotationTransform( m_objBone, l_Pos, l_transform );
					l_transform.Mul( m_transform, l_transform );

					CRefArray l_arrBone;
					l_arrBone.Add( m_objBone.GetRef() );
					in_ctxt.UpdateTransform( l_arrBone, l_transform, siRot );
				}
				else
				{
					m_RootPos = l_Pos;
				}
			}
		}
		return CStatus::OK;
	}

	CStatus MouseUp( ToolContext& in_ctxt )
	{
		// Called when mouse button is released
		LONG x, y;
		in_ctxt.GetMousePosition( x, y );

		if ( in_ctxt.IsLeftButtonDown() )
		{
			if ( m_objBone.IsValid() )
			{
				if ( m_objBone.IsKindOf( L"bone" ) )
				{
					CRefArray l_arrBone;
					l_arrBone.Add( m_objBone.GetRef() );
					in_ctxt.EndTransformUpdate( l_arrBone );

					KinematicState interestKine = m_objBone.GetKinematics().GetLocal();

					CValue l_CmdLog;
					Application().GetPreferences().GetPreferenceValue( L"scripting.cmdlog", l_CmdLog );
					Application().GetPreferences().SetPreferenceValue( L"scripting.cmdlog", true );


					CValue retval; 
					CValueArray args(6); 
					args[0] = L""; 
					args[1] = interestKine.GetParameterValue( L"posx" ); 
					args[2] = interestKine.GetParameterValue( L"posy" ); 
					args[3] = interestKine.GetParameterValue( L"posz" ); 
					args[4] = L"siAbsolute"; 
					args[5] = L"siLocal"; 
					Application().ExecuteCommand( L"Translate", args, retval ); 
					
					args[0] = L""; 
					args[1] = interestKine.GetParameterValue( L"rotx" ); 
					args[2] = interestKine.GetParameterValue( L"roty" ); 
					args[3] = interestKine.GetParameterValue( L"rotz" ); 
					args[4] = L"siAbsolute"; 
					args[5] = L"siLocal"; 
					Application().ExecuteCommand( L"Rotate", args, retval ); 

					args = CValueArray(2);
					args[0] = L".length";
					args[1] = m_objBone.GetActivePrimitive().GetParameterValue( BONE_PARAM_LENGTH );
					Application().ExecuteCommand( L"SetValue", args, retval );

					Application().GetPreferences().SetPreferenceValue( L"scripting.cmdlog", l_CmdLog );
				}

				CValue result;
				CValueArray args(5);
				args[0] = m_objParentBone.GetFullName();
				args[1] = m_objBone.GetFullName();
				args[2] = m_objRootBone.GetFullName();
				if (m_objParentBone.IsValid() && 
						!m_objRootBone.IsValid())
				{
					m_objRootBone = m_objBone;
				}
				args[3] = m_objRootBone.GetFullName();
				args[4] = m_RootPos;
				Application().ExecuteCommand( L"BoneCreateTool_UpdateBone", args, result );

				// Store the mouse up position as the new start position of the next bone
				m_objParentBone = m_objBone;

				m_objBone.ResetObject();
			}
		} 
		else if ( in_ctxt.IsMiddleButtonDown() )
		{
			CValue result;
			CValueArray args;
			Application().ExecuteCommand(L"DeselectAll", args, result);
			args = CValueArray(5);
			args[0] = m_objParentBone.GetFullName();
			args[1] = L"";
			args[2] = m_objRootBone.GetFullName();
			args[3] = L"";
			args[4] = m_RootPos;
			Application().ExecuteCommand( L"BoneCreateTool_UpdateBone", args, result );

			m_objParentBone.ResetObject();
			m_objRootBone.ResetObject();
		}
		else if ( in_ctxt.IsRightButtonDown() )
		{
			in_ctxt.ExitTool();
		}
			
		return CStatus::OK;
	}

	CStatus Draw( ToolContext& in_ctxt )
	{
		// Called to draw tool feedback
		if ( m_objParentBone.IsValid() || m_objBone.IsValid() )
		{
			DrawChainRoot( in_ctxt );
		}
		return CStatus::OK;
	}

	CStatus SetParentBone(const CString& in_NewParent)
	{
		m_objParentBone.ResetObject();
		CRef l_new;
		if (l_new.Set(in_NewParent) == CStatus::OK)
		{
			m_objParentBone.SetObject(l_new);
		}
		return CStatus::OK;
	}

	CStatus SetRootBone(const CString& in_NewRoot)
	{
		m_objRootBone.ResetObject();
		CRef l_new;
		if (l_new.Set(in_NewRoot) == CStatus::OK)
		{
			m_objRootBone.SetObject(l_new);
		}
		return CStatus::OK;
	}

	CStatus SetRootPos(const CVector3& in_RootPos)
	{
		m_RootPos = in_RootPos;
		return CStatus::OK;
	}

	static BoneCreateTool* CurrentTool()
	{
		return g_currentTool;
	}

}; // end class

BoneCreateTool*	BoneCreateTool::g_currentTool = NULL;

////////////////////////////////////////////////////////////////////////////////
//
// Command to update BoneCreateTool bone starting position (handles undo/redo)
//
////////////////////////////////////////////////////////////////////////////////

class BoneCreateTool_UpdateBone  {
private: // Data
	CValue			m_BoneOld;
	CValue			m_BoneNew;
	CValue			m_BoneRootOld;
	CValue			m_BoneRootNew;
	CValue			m_RootPos;

public: // Tool Methods

	BoneCreateTool_UpdateBone()
	{}

	~BoneCreateTool_UpdateBone()
	{}

	CStatus Execute( Context& in_ctxt )
	{
		CValueArray args = in_ctxt.GetAttribute(L"Arguments");
		BoneCreateTool *l_pTool = BoneCreateTool::CurrentTool();
		if ( l_pTool )
		{
			m_BoneOld = args[0];
			m_BoneNew = args[1];
			m_BoneRootOld = args[2];
			m_BoneRootNew = args[3];
			m_RootPos = args[4];
		}
		return CStatus::OK;
	}

	CStatus Undo( Context& in_ctxt )
	{
		BoneCreateTool *l_pTool = BoneCreateTool::CurrentTool();
		if ( l_pTool )
		{
			l_pTool->SetParentBone( m_BoneOld );
			l_pTool->SetRootBone( m_BoneRootOld );
			l_pTool->SetRootPos((CVector3)m_RootPos);
		}
		return CStatus::OK;
	}

	CStatus Redo( Context& in_ctxt )
	{
		BoneCreateTool *l_pTool = BoneCreateTool::CurrentTool();
		if ( l_pTool )
		{
			l_pTool->SetParentBone( m_BoneNew );
			l_pTool->SetRootBone( m_BoneRootNew );
			l_pTool->SetRootPos((CVector3)m_RootPos);
		}
		return CStatus::OK;
	}
};

////////////////////////////////////////////////////////////////////////////////
//
// Plugin Callbacks
//
////////////////////////////////////////////////////////////////////////////////

SICALLBACK XSILoadPlugin( PluginRegistrar& in_reg )
{
	in_reg.PutAuthor(L"Autodesk");
	in_reg.PutName(L"BoneCreateTool Plugin");
	in_reg.PutVersion(1,0);
	in_reg.RegisterTool(L"BoneCreateTool");
	in_reg.RegisterMenu(siMenuTbCreateSkeletonDrawID, L"BoneCreateMenu", false, false);

	// Command for recording box orientation for undo/redo
	in_reg.RegisterCommand( L"BoneCreateTool_UpdateBone" );

	//RegistrationInsertionPoint - do not remove this line
	return CStatus::OK;
}

SICALLBACK BoneCreateMenu_Init( CRef& in_ctxt )
{
	Context ctxt( in_ctxt );
	MenuItem menuItem;
	Menu menu = ctxt.GetSource();
	menu.AddCommandItem( Translate(L"Draw Bones"), L"BoneCreateTool", menuItem );
	return true;
}

SICALLBACK XSIUnloadPlugin( const PluginRegistrar& in_reg )
{
	CString strPluginName;
	strPluginName = in_reg.GetName();
	Application().LogMessage(strPluginName + L" has been unloaded.",siVerboseMsg);
	return CStatus::OK;
}

SICALLBACK BoneCreateTool_Init( CRef& in_ctxt )
{
	BoneCreateTool *l_pTool = new BoneCreateTool;
	if ( !l_pTool ) return CStatus::Fail;
	ToolContext l_ctxt( in_ctxt );
	l_ctxt.PutUserData( CValue((CValue::siPtrType)l_pTool) );
	return CStatus::OK;
}

SICALLBACK BoneCreateTool_Term( CRef& in_ctxt )
{
	ToolContext l_ctxt( in_ctxt );
	BoneCreateTool *l_pTool = (BoneCreateTool *)(CValue::siPtrType)l_ctxt.GetUserData();
	if ( !l_pTool ) return CStatus::Fail;
	delete l_pTool;
	l_ctxt.PutUserData( CValue((CValue::siPtrType)NULL) ); // Clear user data
	return CStatus::OK;
}

////////////////////////////////////////////////////////////////////////////////
// Command callbacks
////////////////////////////////////////////////////////////////////////////////

SICALLBACK BoneCreateTool_UpdateBone_Init( CRef& in_ctxt )
{
	Context ctxt( in_ctxt );
	Command cmd = ctxt.GetSource();
	ArgumentArray args = cmd.GetArguments();

	args.Add(L"OldBone", CValue(L"") );
	args.Add(L"NewBone", CValue(L"") );
	args.Add(L"OldRootBone", CValue(L"") );
	args.Add(L"NewRootBone", CValue(L"") );
	args.Add(L"RootPos", CValue(CVector3()));

	return CStatus::OK;
}

SICALLBACK BoneCreateTool_UpdateBone_Execute( CRef& in_ctxt )
{
	Context l_ctxt( in_ctxt );
	BoneCreateTool_UpdateBone *l_pCmd = new BoneCreateTool_UpdateBone;
	if ( !l_pCmd ) return CStatus::OK;
	bool bUndoRequired = l_ctxt.GetAttribute( L"UndoRequired" );
	l_pCmd->Execute( l_ctxt );
	if ( bUndoRequired )
		l_ctxt.PutAttribute( L"UndoRedoData", (CValue::siPtrType)l_pCmd );
	else
		delete l_pCmd; // No undo required
	return CStatus::OK;
}

SICALLBACK BoneCreateTool_UpdateBone_TermUndoRedo( CRef& in_ctxt )
{
	Context l_ctxt( in_ctxt );
	BoneCreateTool_UpdateBone *l_pCmd = (BoneCreateTool_UpdateBone *)(CValue::siPtrType)l_ctxt.GetAttribute(L"UndoRedoData");
	if ( !l_pCmd ) return CStatus::OK;
	delete l_pCmd;
	l_ctxt.PutAttribute( L"UndoRedoData", (CValue::siPtrType)NULL ); // Probably not needed...
	return CStatus::OK;
}

SICALLBACK BoneCreateTool_UpdateBone_Undo( CRef& in_ctxt )
{
	Context l_ctxt( in_ctxt );
	BoneCreateTool_UpdateBone *l_pCmd = (BoneCreateTool_UpdateBone *)(CValue::siPtrType)l_ctxt.GetAttribute(L"UndoRedoData");
	if ( !l_pCmd ) return CStatus::OK;
	l_pCmd->Undo( l_ctxt );
	return CStatus::OK;
}

SICALLBACK BoneCreateTool_UpdateBone_Redo( CRef& in_ctxt )
{
	Context l_ctxt( in_ctxt );
	BoneCreateTool_UpdateBone *l_pCmd = (BoneCreateTool_UpdateBone *)(CValue::siPtrType)l_ctxt.GetAttribute(L"UndoRedoData");
	if ( !l_pCmd ) return CStatus::OK;
	l_pCmd->Redo( l_ctxt );
	return CStatus::OK;
}

// Use a macro to simplify callback setup and forwarding...
#define DECLARE_TOOL_CALLBACK(TOOL,CALLBACK) \
SICALLBACK TOOL##_##CALLBACK( ToolContext& in_ctxt ) { \
	TOOL *l_pTool = (TOOL *)(CValue::siPtrType)in_ctxt.GetUserData(); \
	return ( l_pTool ? l_pTool->CALLBACK( in_ctxt ) : CStatus::Fail ); }

DECLARE_TOOL_CALLBACK( BoneCreateTool, Setup );
DECLARE_TOOL_CALLBACK( BoneCreateTool, Cleanup );
DECLARE_TOOL_CALLBACK( BoneCreateTool, Activate );
DECLARE_TOOL_CALLBACK( BoneCreateTool, Deactivate );
DECLARE_TOOL_CALLBACK( BoneCreateTool, MouseDown );
DECLARE_TOOL_CALLBACK( BoneCreateTool, MouseDrag );
DECLARE_TOOL_CALLBACK( BoneCreateTool, MouseUp );
DECLARE_TOOL_CALLBACK( BoneCreateTool, Draw );
