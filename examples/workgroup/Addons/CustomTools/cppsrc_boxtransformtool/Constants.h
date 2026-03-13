#ifndef CONSTANTS_INCLUDED
#define CONSTANTS_INCLUDED
///////////////////////////////////////////////////////////////////////////
//
// File: Constants.h
//
// Description: Box Transform tool constants
//
// Copyright 2010 Autodesk, Inc. All rights reserved.
// Use of this software is subject to the terms of the Autodesk license
// agreement provided at the time of installation or download, or which
// otherwise accompanies this software in either electronic or hard copy
// form.
//
///////////////////////////////////////////////////////////////////////////
#ifndef linux
#define WIN32_LEAN_AND_MEAN
#include <windows.h> // Needed for OpenGL on windows
#endif
#include <sicppsdk.h>
#include <GL/gl.h>
#include <GL/glu.h>

// Macros for handling packed colors
#define RGBA_R(rgba)					(GLubyte)((rgba) & 0xFF)
#define RGBA_G(rgba)					(GLubyte)(((rgba) >>  8) & 0xFF)
#define RGBA_B(rgba)					(GLubyte)(((rgba) >> 16) & 0xFF)
#define RGBA_A(rgba)					(GLubyte)(((rgba) >> 24) & 0xFF)
#define RGBA_COLOR(r, g, b, a)			(ULONG)(((a) << 24) | ((b) << 16) | ((g) << 8) | (r))
inline  void SetGLColor(ULONG c)		{ glColor4ub( RGBA_R(c), RGBA_G(c), RGBA_B(c), RGBA_A(c)); }

// Color constants
#define kInvalidIndex					-1
#define kBBoxColor						RGBA_COLOR(153, 153, 153, 255)
#define kSelectedHandleColor			RGBA_COLOR(255, 255,   0, 255)
#define kTranslateHandleColor			RGBA_COLOR(  0,   0, 255, 255)
#define kScaleHandleColor				RGBA_COLOR(  0,   0, 255, 255)
#define kCenterOutlineColor				RGBA_COLOR(  0,   0,   0, 255)
#define kCenterFillColor				RGBA_COLOR(255, 255, 255, 255)
#define kRotateXAxisColor				RGBA_COLOR(255,   0,   0, 255)
#define kRotateYAxisColor				RGBA_COLOR(  0, 255,   0, 255)
#define kRotateZAxisColor				RGBA_COLOR(  0,   0, 255, 255)
#define kRotateStickBallColor			RGBA_COLOR(  0, 255, 255, 255)
#define kRotateStickLineColor			RGBA_COLOR(255, 255, 255, 255)
#define kRotateWheelColor				RGBA_COLOR(  0,   0, 255, 255)
#define kScalingHandleColor				RGBA_COLOR(  0,   0, 255, 255)
#define kDimensionTextColor				RGBA_COLOR(230, 230, 230, 220)
#define kDimensionBackColor				RGBA_COLOR(125, 140, 155, 200)

// Other constants
#define kPickSize						14	 // pixels
#define kHandleDragThreshold			5	 // pixels
#define kGestureDragThreshold			10	 // pixels
#define kTranslateHandleSize			7	 // pixels
#define kCenterSize						10	 // pixels
#define kCenterInnerRingSize			8	 // pixels
#define kCenterInnerCircleSize			4	 // pixels
#define kRotateHandleArcResolution		4	 // subdivs
#define kRotateHandleRadius				25	 // pixels 
#define kRotateHandleConeSlices			10	 // Nb of slices when drawing cones
#define kRotateHandleConeStacks			1	 // Nb of stacks when drawing cones
#define kRotateHandleMinBBoxSize		100	 // We do not render the rotation handles if bbox is smaller than this amount of pixels
#define kRotateStickLength				50	 // Desired size of the stick, in pixels
#define kRotateStickSphereRadius		12	 // Desired radius for the end sphere (pixels)
#define kRotateStickSphereSlices		12	 // Nb of slices when drawing the sphere
#define kRotateStickSphereStacks		12	 // Nb of stacks when drawing the sphere
#define kScaleHandleSize				12	 // pixels
#define kRotateStickMinBBoxSize			100	 // We do not render the rotation stick if bbox is smaller than this amount of pixels
#define kRotateWheelOuterRadius			50.0 // pixels 
#define kRotateWheelInnerRadius			2.0	 // pixels 
#define kRotateWheelSides				4	 // Nb sides in the torus
#define kRotateWheelRings				32	 // Nb rings in the torus 
#define kRotateWidgetSize				75.0 // The size of the rotation widget when rotating (percentage of the bbox or the rotation wheel)
#define kRotateStickGestureThreshold	(5.0/180.0*M_PI) // The rotation, in radians, that is needed around X or Y to choose this axis
#define kDimensionMinBBoxSize			100	 // We do not render the dimensions if bbox is smaller than this amount of pixels
#define kDimensionMinEdgeSize			20	 // We do not render the dimensions if edge is smaller than this amount of pixels
#define kDimensionTextOffset			12	 // pixels
#define kDimensionTextMargin			2	 // pixels
#define kDimensionEditMargin			4	 // pixels
#define kCOS45							0.7071067811865475244008443621049

// Shortcut Key constants
#define kSwitchModeKey					0x09 // VK_TAB

// Handle constants
enum ToolHandleID
{
	kInvalidHandleID = -1,

	////////////////////////////////////////////////////////////
	// Mode buttons
	kButtonHandleMinID,
	kTranslateButtonID = kButtonHandleMinID,
	kRotateScaleButtonID,
	kButtonHandleMaxID = kRotateScaleButtonID,

	////////////////////////////////////////////////////////////
	// Translate Handles
	kTranslateHandleMinID,
	// Translate corner handles (NOTE: has same ordering as bbox corner enum)
	kTranslateCornerMinID = kTranslateHandleMinID,
	kTranslateLeftBottomFrontID = kTranslateCornerMinID,
	kTranslateLeftBottomBackID,
	kTranslateLeftTopFrontID,
	kTranslateLeftTopBackID,
	kTranslateRightBottomFrontID,
	kTranslateRightBottomBackID,
	kTranslateRightTopFrontID,
	kTranslateRightTopBackID,
	kTranslateCornerMaxID = kTranslateRightTopBackID,
	// Translate edge handles (NOTE: has same ordering as bbox edge enum)
	kTranslateEdgeMinID,
	kTranslateLeftBottomID = kTranslateEdgeMinID,
	kTranslateLeftTopID,
	kTranslateRightBottomID,
	kTranslateRightTopID,
	kTranslateLeftFrontID,
	kTranslateLeftBackID,
	kTranslateRightFrontID,
	kTranslateRightBackID,
	kTranslateBottomFrontID,
	kTranslateBottomBackID,
	kTranslateTopFrontID,
	kTranslateTopBackID,
	kTranslateEdgeMaxID = kTranslateTopBackID,
	// Center translate handle
	kTranslateCenterID,
	kTranslateHandleMaxID = kTranslateCenterID,

	////////////////////////////////////////////////////////////
	// Rotate handles
	kRotateHandleMinID,
	// Rotate edge handles (NOTE: has same ordering as bbox edge enum)
	kRotateEdgeMinID = kRotateHandleMinID,
	kRotateLeftBottomID = kRotateEdgeMinID,
	kRotateLeftTopID,
	kRotateRightBottomID,
	kRotateRightTopID,
	kRotateLeftFrontID,
	kRotateLeftBackID,
	kRotateRightFrontID,
	kRotateRightBackID,
	kRotateBottomFrontID,
	kRotateBottomBackID,
	kRotateTopFrontID,
	kRotateTopBackID,
	kRotateEdgeMaxID = kRotateTopBackID,
	// Rotation stick handles
	kRotateStickID,
	kRotateWheelID,
	kRotateHandleMaxID = kRotateWheelID,

	////////////////////////////////////////////////////////////
	// Scale handles
	kScaleHandleMinID,
	// Scale corner handles (NOTE: has same ordering as bbox corner enum)
	kScaleCornerMinID = kScaleHandleMinID,
	kScaleLeftBottomFrontID = kScaleCornerMinID,
	kScaleLeftBottomBackID,
	kScaleLeftTopFrontID,
	kScaleLeftTopBackID,
	kScaleRightBottomFrontID,
	kScaleRightBottomBackID,
	kScaleRightTopFrontID,
	kScaleRightTopBackID,
	kScaleCornerMaxID = kScaleRightTopBackID,
	kScaleHandleMaxID = kScaleCornerMaxID,

	////////////////////////////////////////////////////////////
	// Scale dimension handles
	kDimensionScaleXID,
	kDimensionScaleYID,
	kDimensionScaleZID,

	// End marker
	kHandleCount
};

// Debugging macros
#define VectorAsString(v)	CString(L"<" + CValue(v.GetX()).GetAsText() + L", " + CValue(v.GetY()).GetAsText() + L", " + CValue(v.GetZ()).GetAsText() + L">")
#define DumpVector3(m, v)	Application().LogMessage(m + VectorAsString(v))
#define DumpBBox(m, b)		Application().LogMessage(m + CString(L"min=") + VectorAsString(b.GetMin()) + L", max=" + VectorAsString(b.GetMax()))

#endif // CONSTANTS_INCLUDED
