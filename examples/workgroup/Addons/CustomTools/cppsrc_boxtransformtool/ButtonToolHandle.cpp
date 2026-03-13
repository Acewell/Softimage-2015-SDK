///////////////////////////////////////////////////////////////////////////
//
// File: ButtonToolHandle.cpp
//
// Description: Helper class for dimension text handles
//
// Copyright 2010 Autodesk, Inc. All rights reserved.
// Use of this software is subject to the terms of the Autodesk license
// agreement provided at the time of installation or download, or which
// otherwise accompanies this software in either electronic or hard copy
// form.
//
///////////////////////////////////////////////////////////////////////////
#include "ButtonToolHandle.h"

ButtonToolHandle::~ButtonToolHandle()
{}

ButtonToolHandle::ButtonToolHandle( BoxTransformToolDelegate * in_pTool, ToolHandleID in_ID, ToolButton * in_button )
:	m_pButton( in_button )
,	m_bWasSelected( false )
{
	Setup( in_pTool, in_ID );
}

void ButtonToolHandle::MouseDown( ToolContext &in_ctxt )
{
	LONG x, y;
	m_bWasSelected = m_pButton->IsSelected();
	if ( !m_bWasSelected && in_ctxt.GetMousePosition( x, y ) == CStatus::OK )
	{
		m_pButton->SetSelected( true );
	}
}

void ButtonToolHandle::MouseDrag( ToolContext &in_ctxt )
{
	LONG x, y;
	if ( !m_bWasSelected && in_ctxt.GetMousePosition( x, y ) == CStatus::OK )
	{
		m_pButton->SetSelected( m_pButton->IsPointInside( in_ctxt, x, y ) );
	}
}

void ButtonToolHandle::MouseUp( ToolContext &in_ctxt )
{
	LONG x, y;
	if ( !m_bWasSelected && in_ctxt.GetMousePosition( x, y ) == CStatus::OK )
	{
		m_pButton->SetSelected( false );
		if ( m_pButton->IsPointInside( in_ctxt, x, y ) )
		{
			m_pTool->SelectToolButton( HandleID() );
		}
	}
}

void ButtonToolHandle::Draw( ToolContext &in_ctxt )
{
	if ( in_ctxt.IsActiveView() )
	{
		m_pButton->Draw( in_ctxt );
	}
}
