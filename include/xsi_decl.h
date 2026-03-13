//*****************************************************************************
/*!
   ile xsi_decl.h 
   rief Constants and enums declarations.

   © Copyright 1998-2002 Avid Technology, Inc. and its licensors. All rights 
   reserved. This file contains confidential and proprietary information of 
   Avid Technology, Inc., and is subject to the terms of the SOFTIMAGE|XSI 
   end user license agreement (or EULA).
*/
//*****************************************************************************

#ifndef _XSIDECL_H_
#define _XSIDECL_H_

#ifndef XSIDECL
#if !defined(unix)
	#ifdef SICORESDKIMPL
		#define XSIDECL __declspec(dllexport)
	#else
		#define XSIDECL __declspec(dllimport)
	#endif
#else
#define XSIDECL
#endif
#endif

#ifdef SI_HAS_PRAGMA_ONCE
# pragma once
#endif

#include <stdlib.h>

namespace XSI {

/*! Error constants. To use with Err object. 
 *  \sa RemoveKey RemoveKeyOnKeyable RemoveKeyOnMarkedKeyable 
 */
typedef   
enum siErrorValueEnum
    {
        siErrCancelled	= 0x4c7L		/*!< Command was cancelled. */
    } 	siErrorValueEnum;

/*! Time format values which are used by siTimeFormatDefaultFrameFormat <object idref="UserPreference"/>. 
 *  \sa SetValue 
 */
typedef   
enum siDefaultTimeFormat
    {
        siDefaultFILM24	= 7,		/*!< FILM 24 frames per second. */
        siDefaultPAL25	= 8,		/*!< PAL 25 frames per second. */
        siDefaultNTSC30	= 10,		/*!< NTSC 29.97 frames per second. */
        siDefaultUserTimeFormat	= 11,		/*!< User ticks per second. */
        siDefault30	= 19		/*!< HDTV 30 frames per seconde interlaced. */
    } 	siDefaultTimeFormat;

/*! Time format values which are used by siTimeDisplayFormatUserFormat <object idref="UserPreference"/>. 
 *  \sa SetValue 
 */
typedef   
enum siDisplayTimeFormat
    {
        siDisplayMilliSeconds	= 2,		/*!< Used for display format, to show the milliseconds equivalent of a frame rate. */
        siDisplayFILM24	= 7,		/*!< FILM 24 frames per second. */
        siDisplayPAL25	= 8,		/*!< PAL 25 frames per second. */
        siDisplayNTSCDF	= 9,		/*!< NTSC Drop Frame display format. */
        siDisplayNTSC30	= 10,		/*!< NTSC 29.97 frames per second (non-drop frame). */
        siDisplaySampleRate	= 12		/*!< Corresponds to the audio sample rate. */
    } 	siDisplayTimeFormat;

/*! Different modes for SIFilter command 
 *  \sa SIFilter 
 */
typedef   
enum siFilterMode
    {
        siQuickSearch	= 0,		/*!< Look up filter from installed filters */
        siSearchFamilies	= 1,		/*!< Look up filter name in registered families */
        siSearchObjects	= 2,		/*!< Look up filter name in registered objects (not implemented) */
        siFullSearch	= 3		/*!< siSearchFamilies and siSearchObjects */
    } 	siFilterMode;

/*! Delta transformation modes for transformation commands (Translate, Rotate, Scale) 
 *  \sa Translate Rotate Scale TranslateUVW RotateUVW ScaleUVW 
 */
typedef   
enum siDeltaMode
    {
        siAbsolute	= 0,		/*!< Transformation moves the object to an absolute position */
        siRelative	= 1		/*!< Transformation moves the object a relative distance */
    } 	siDeltaMode;

/*! Texture effects bit flags, to be used in conjunction with <object idref="Texture.GetTransformValues"/> */
typedef   
enum siTextureEffectsComputation
    {
        siTextureComputeTransformation	= 1,		/*!< Uses the transformation of the Texture projection definition. */
        siTextureComputeCropping	= 2,		/*!< Uses the Image effect applied to the image clip. */
        siTextureComputeUVRemap	= 4,		/*!< Remaps the UVW domains using the data stored into the Advanced tab of the texture shader. */
        siTextureComputeFlip	= 8,		/*!< Uses the Flip information on the image clipto swap the UV values. */
        siTextureComputeRepeats	= 16,		/*!< Uses the repeat information of the texture shader.This flag applies to polygon mesh objects only. Artifacts may appear if the texture ends in the middle of a polygon. */
        siTextureComputeAlternate	= 32,		/*!< Only applies if the Repeat is on. Uses the alternate flag stored on the texture shader.  This flag applies to polygon mesh objects only. */
        siTextureComputeWrapping	= 64		/*!< Uses the flags stored on the Texture projection definition.This flag applies to polygon mesh objects only. Artifacts may appear if the texture ends in the middle of a polygon. */
    } 	siTextureEffectsComputation;

/*! Reference transformation modes for transformation commands (Translate, Rotate, Scale). <br/>Note: "COG" indicates an additional translation about the Centre-Of-Geometry. "Sym" indicates a symmetrical translation. These indicators can also be used in combination. */
typedef   
enum siRefMode
    {
        siGlobal	= 1,		/*!< Global (world) relative movement or position */
        siLocal	= 2,		/*!< Local movement relative to center of each object/component */
        siObjCtr	= 3,		/*!< By Reference movement relative to center of referenced object or an absolute position where 0,0,0 is the center of the referenced object. This corresponds to Ref mode on the MCP panel. */
        siView	= 4,		/*!< By Reference movement relative to the view.  */
        siParent	= 6,		/*!< Object/Parent movement is relative to the center of the parent (for an object) or the object (for a component). */
        siPlane	= 7,		/*!< By Reference movement relative to the active reference plane. This corresponds to Plane mode on the MCP panel. */
        siPivot	= 8,		/*!< Object/Pivot movement is relative to the object's pivot. If the object has not pivot or neutral pose, siPivot is the same as siParent. */
        siAdd	= 70,		/*!< Additive rotation when manipulating  (rotation only) */
        siGlobalCOG	= 17,		/*!< Global + COG */
        siLocalCOG	= 18,		/*!< Local + COG */
        siObjectCOG	= 19,		/*!< Object + COG */
        siViewCOG	= 20,		/*!< View + COG */
        siParentCOG	= 22,		/*!< Parent + COG */
        siPlaneCOG	= 23,		/*!< Plane + COG */
        siPivotCOG	= 24,		/*!< Pivot + COG */
        siAddCOG	= 86,		/*!< Add + COG */
        siGlobalSym	= 2049,		/*!< Global + Sym */
        siLocalSym	= 2050,		/*!< Local + Sym */
        siObjectSym	= 2051,		/*!< Object + Sym */
        siViewSym	= 2052,		/*!< View + Sym */
        siParentSym	= 2054,		/*!< Parent + Sym */
        siPlaneSym	= 2055,		/*!< Plane + Sym */
        siPivotSym	= 2056,		/*!< Pivot + Sym */
        siAddSym	= 2118,		/*!< Add + Sym */
        siGlobalSymCOG	= 2065,		/*!< Global + Sym + COG */
        siLocalSymCOG	= 2066,		/*!< Local + Sym + COG */
        siObjectSymCOG	= 2067,		/*!< Object + Sym + COG */
        siViewSymCOG	= 2068,		/*!< View + Sym + COG */
        siParentSymCOG	= 2070,		/*!< Parent + Sym + COG */
        siPlaneSymCOG	= 2071,		/*!< Plane + Sym + COG */
        siPivotSymCOG	= 2072,		/*!< Pivot + Sym + COG */
        siAddSymCOG	= 2134		/*!< Add + Sym + COG */
    } 	siRefMode;

/*! Center transformation modes for transformation commands. */
typedef   
enum siCenterMode
    {
        siObj	= 0,		/*!< Object/component will be translated */
        siCtr	= 1		/*!< Center of the object will be translated */
    } 	siCenterMode;

/*! Axes filters for transformation commands (Translate, Rotate, Scale). <br/>Note: This flag is only used for absolute transformations. */
typedef   
enum siAxesFilter
    {
        siX	= 1,		/*!< Filter in X */
        siY	= 2,		/*!< Filter in Y */
        siXY	= 3,		/*!< Filter in X &amp; Y */
        siZ	= 4,		/*!< Filter in Z */
        siXZ	= 5,		/*!< Filter in X &amp; Z */
        siYZ	= 6,		/*!< Filter in Y &amp; Z */
        siXYZ	= 7		/*!< Filter in X &amp; Y &amp; Z */
    } 	siAxesFilter;

/*! Axes filters for transformation commands (TranslateUVW, RotateUVW, ScaleUVW) */
typedef   
enum siUVWAxesFilter
    {
        siU	= 1,		/*!< Filter in U */
        siV	= 2,		/*!< Filter in V */
        siUV	= 3,		/*!< Filter in U &amp; V */
        siW	= 4,		/*!< Filter in W */
        siUW	= 5,		/*!< Filter in U &amp; W */
        siVW	= 6,		/*!< Filter in V &amp; W */
        siUVW	= 7		/*!< Filter in U &amp; V &amp; W */
    } 	siUVWAxesFilter;

/*! Transformation type filters (Translation, Rotation, Scaling) */
typedef   
enum siTransformFilter
    {
        siScl	= 1,		/*!< Scaling */
        siRot	= 2,		/*!< Rotation */
        siTrn	= 4,		/*!< Translation */
        siSR	= 8,		/*!< Scaling &amp; Rotation */
        siST	= 16,		/*!< Scaling &amp; Translation */
        siRT	= 32,		/*!< Rotation &amp; Translation */
        siSRT	= 64		/*!< Scaling &amp; Rotation &amp; Translation */
    } 	siTransformFilter;

/*! Parameter filter (Marked, Animated, Scaling, Rotation, Translation, Weight, etc..) */
typedef   
enum siParameterFilter
    {
        siNoParam	= 0,		/*!< No Parameter */
        siMarkedParam	= 1,		/*!< Marked Parameters */
        siAnimatedParam	= 3,		/*!< Animated Parameters */
        siSelectedParam	= 4,		/*!< Selected Parameters */
        siScalingParam	= 5,		/*!< Scaling Parameters */
        siRotationParam	= 6,		/*!< Rotation Parameters */
        siTranslationParam	= 7,		/*!< Translation Parameters */
        siTransformParam	= 8,		/*!< All Transform Parameters */
        siAllParam	= 128		/*!< All Parameters */
    } 	siParameterFilter;

/*! Parent-child parameter set relationships */
typedef   
enum siPSetRelationship
    {
        siContainedPSet	= 1,		/*!< Child is contained as part of parent (for example, Kinematics) */
        siSharedPSet	= 2,		/*!< Child is an inherited PSet */
        siLocalPSet	= 4,		/*!< Child is a local PSet */
        siObjectPSet	= 8,		/*!< Child is a member of the parent (for example, Object in Group) */
        siPortPSet	= 16,		/*!< Child is connected to the parent PSet (for example, Shader/Operator) */
        siParameterPSet	= 32		/*!< Child is a leaf component part of the parent (for example, Object.Name). (not implemented) */
    } 	siPSetRelationship;

/*! Property propagation types */
typedef   
enum siPropagationType
    {
        siDefaultPropagation	= 0,		/*!< Based on propagation of selection type */
        siBranchPropagation	= 1,		/*!< Branch propagation */
        siNodePropagation	= 2		/*!< Node propagation */
    } 	siPropagationType;

/*! Hierarchy options for duplication commands. */
typedef   
enum siDupHierarchy
    {
        siNodeDuplicate	= 0,		/*!< duplicate node only */
        siBranchDuplicate	= 1,		/*!< duplicate branch */
        siDefaultDuplicate	= 3		/*!< duplicate based on selection type */
    } 	siDupHierarchy;

/*! History options for duplication commands. */
typedef   
enum siDupHistory
    {
        siCurrentHistory	= 0,		/*!< Duplicate final resulting geometry of the source object */
        siOriginalHistory	= 1,		/*!< Duplicate the original geometry of the source object (not implemented) */
        siDuplicateHistory	= 2,		/*!< Duplicate whole construction history if the source object */
        siSharedHistory	= 3		/*!< Share the construction history of the source object such that changes to the source object effect the copied object (same as instance) */
    } 	siDupHistory;

/*! Parenting options for duplication commands. */
typedef   
enum siDupParent
    {
        siNoParent	= 0,		/*!< Parent the copied object under the scene root */
        siSharedParent	= 1,		/*!< Share the parent of the source object */
        siNewNullParent	= 2		/*!< Create a null to act as the parent of this object */
    } 	siDupParent;

/*! Grouping options for duplication commands. */
typedef   
enum siDupGroup
    {
        siNoGrouping	= 0,		/*!< Ignore grouping */
        siShareGrouping	= 1		/*!< Add duplicate to the same groups as the source (not implemented) */
    } 	siDupGroup;

/*! Property options for duplication commands. */
typedef   
enum siDupProperty
    {
        siDuplicateProperties	= 0,		/*!< Copy properties from the source */
        siSharedProperties	= 1,		/*!< Share properties with the source (not implemented) */
        siNoProperties	= 2		/*!< Ignore properties */
    } 	siDupProperty;

/*! Animation options for duplication commands. */
typedef   
enum siDupAnimation
    {
        siDuplicateAnimation	= 0,		/*!< Copy animation from the source and share the mixer source */
        siNoAnimation	= 1,		/*!< Ignore animation */
        siDupAnimationCopySource	= 2		/*!< Copy animation from the source and copy the mixer source */
    } 	siDupAnimation;

/*! Constraint options for duplication commands. */
typedef   
enum siDupConstraint
    {
        siDuplicateConstraints	= 0,		/*!< Copy constraints from the source */
        siShareConstraints	= 1,		/*!< Share constraints with the source (not implemented) */
        siNoConstraints	= 2		/*!< Ignore constraints */
    } 	siDupConstraint;

/*! Texture Support options for duplication commands. */
typedef   
enum siDupTextureSupport
    {
        siDuplicateSelectedTextureSupports	= 0,		/*!< Projection definition is linked to a duplicated texture support object if the object was selected for duplication, shared otherwise */
        siDuplicateTextureSupports	= 1,		/*!< Texture support object is duplicated for each projection */
        siShareTextureSupports	= 2,		/*!< Texture support object is shared by the duplicated projections */
        siFreezeAllProjections	= 3		/*!< Duplicated projections are frozen and disconnected from the texture support object */
    } 	siDupTextureSupport;

/*! Selection options for duplication commands. */
typedef   
enum siDupSelection
    {
        siSetSelection	= 0,		/*!< Set the current selection to the copied object */
        siNoSelection	= 1,		/*!< Do not change the current selection */
        siAddToSelection	= 2		/*!< Extend the current selection to include the copied object */
    } 	siDupSelection;

/*! Transform options for duplication commands. */
typedef   
enum siDupTransform
    {
        siGlobalXForm	= 0,		/*!< Apply same global transform as source object */
        siApplyRepeatXForm	= 1		/*!< Apply and repeat transform argument on duplicated objects */
    } 	siDupTransform;

/*! Keyboard modifier states */
typedef   
enum siKeyboardState
    {
        siShiftMask	= 1,		/*!< SHIFT key bit mask. */
        siCtrlMask	= 2,		/*!< CTRL key bit mask. */
        siAltMask	= 4		/*!< ALT key bit mask. */
    } 	siKeyboardState;

/*! Inspection Dialog Modes */
typedef   
enum siInspectMode
    {
        siRecycle	= 1,		/*!< Recycle dialog */
        siFollow	= 2,		/*!< Recycle dialog if object is of the same family */
        siLock	= 3,		/*!< Prevent dialog from being recycled */
        siModal	= 4,		/*!< Pop up a modal dialog */
        siLockAndForceNew	= 5		/*!< Force a new dialog to open and prevent dialog from being recycled */
    } 	siInspectMode;

/*! Constants that define the way to browse the inspection history */
typedef   
enum siInspectBrowseMode
    {
        siNext	= 1,		/*!< Browse to the next inspection in the history ( newer ) */
        siPrevious	= 2,		/*!< Browse to the previous inspection in the history ( older ) */
        siLast	= 3,		/*!< Browse to the last inspection in the history ( newest ) */
        siFirst	= 4		/*!< Browse to the first inspection in the history ( oldest ) */
    } 	siInspectBrowseMode;

/*! Animation Source Types */
typedef   
enum siSourceType
    {
        siFCurveSource	= 1,		/*!< Include fcurves */
        siExpressionSource	= 2,		/*!< Include expressions */
        siAnySource	= 4,		/*!< Any source */
        siMixerSource	= 8,		/*!< Mixer source */
        siConstraintSource	= 16,		/*!< Constraint source */
        siScriptedOperatorSource	= 32,		/*!< Scripted operator source */
        siShapeAnimationSource	= 64,		/*!< Shape animation source */
        siOverrideSource	= 128		/*!< Override source */
    } 	siSourceType;

/*! The branch flag is used to determine whether we are referring to the object as a node or as a branch. */
typedef   
enum siBranchFlag
    {
        siNode	= 0,		/*!< Node */
        siBranch	= 1,		/*!< Branch */
        siUnspecified	= 3,		/*!< Unspecified */
        siNotSelected	= 4		/*!< Not selected */
    } 	siBranchFlag;

/*! The operation mode is used to determine if we are in immediate mode or persistent mode */
typedef   
enum siOperationMode
    {
        siPersistentOperation	= 0,		/*!< Persistent Operation */
        siImmediateOperation	= 1		/*!< Immediate Operation */
    } 	siOperationMode;

/*! This mode is used to determine if we should keep, hide or delete the inputs after a generator is applied */
typedef   
enum siGeneratorInputsDisposalMode
    {
        siKeepGenOpInputs	= 0,		/*!< Keep the inputs */
        siHideGenOpInputs	= 1,		/*!< Hide the inputs */
        siDeleteGenOpInputs	= 2		/*!< Delete the inputs */
    } 	siGeneratorInputsDisposalMode;

/*! This mode is used to determine if the command should only apply to visible components */
typedef   
enum siComponentVisibilityMode
    {
        siIgnoreComponentVisibility	= 0,		/*!< Ignore Visibility */
        siCheckComponentVisibility	= 1		/*!< Check Visibility */
    } 	siComponentVisibilityMode;

/*! This indicates what to do when local materials overlap */
typedef   
enum siActionWhenLocalMaterialsOverlap
    {
        siPromptUser	= 0,		/*!< Prompt the user that local materials overlap (used by ApplyShader only) */
        siRemoveFromSelectedClusters	= 1,		/*!< Remove the common elements from the selected clusters */
        siRemoveFromExistingClusters	= 2,		/*!< Remove the common elements from the existing clusters */
        siLetLocalMaterialsOverlap	= 3,		/*!< Let the local materials overlap (used by ApplyShader only) */
        siJustReturnExistingClusters	= 4		/*!< Return the existing clusters overlapping with the selected ones (used by ClusterNonOverlapEnforcement only) */
    } 	siActionWhenLocalMaterialsOverlap;

/*! Split type for polygons */
typedef   
enum siSplitPolygonType
    {
        siByTheVertices	= 0,		/*!< Split along the vertices */
        siByTheEdgesMidPoints	= 1,		/*!< Add edges from the geometric center of a polygon to the midpoint of each edge */
        siCross	= 2,		/*!< Draw edges from the midpoint of a polygon to each of its vertices */
        siDiamond	= 3		/*!< Draw edges connecting the midpoints of a polygon's edges */
    } 	siSplitPolygonType;

/*! Constants that define the different options for updating selection list when working with topology operators. */
typedef   
enum siSelectionUpdate
    {
        siLeaveSelection	= 0,		/*!< Leave selection */
        siCleanSelection	= 1,		/*!< Clean selection */
        siUpdateSelection	= 2		/*!< Update selection */
    } 	siSelectionUpdate;

/*! Texture creation type constants. To use with the texturing commands. */
typedef   
enum siTxtCreationType
    {
        siTxtPlanarXY	= 0,		/*!< XY Planar projection. */
        siTxtPlanarXZ	= 1,		/*!< XZ Planar projection. */
        siTxtPlanarYZ	= 2,		/*!< YZ Planar projection. */
        siTxtCylindrical	= 3,		/*!< Cylindrical projection. */
        siTxtSpherical	= 4,		/*!< Spherical projection. */
        siTxtSpatial	= 5,		/*!< Spatial projection. */
        siTxtCamera	= 6,		/*!< Camera projection. */
        siTxtUV	= 7,		/*!< UV projection. */
        siTxtLollipop	= 8,		/*!< Lollipop projection. */
        siTxtPureImplicit	= 9,		/*!< Purely implicit projection. */
        siTxtCubic	= 10,		/*!< Cubic projection. */
        siTxtUniqueUV	= 11		/*!< Unique UV projection. */
    } 	siTxtCreationType;

/*! Default texture creation type constants. To use with the texturing commands. */
typedef   
enum siTxtDefaultCreationType
    {
        siTxtDefaultPlanarXY	= 0,		/*!< XY Planar projection. */
        siTxtDefaultPlanarXZ	= 1,		/*!< XZ Planar projection. */
        siTxtDefaultPlanarYZ	= 2,		/*!< YZ Planar projection. */
        siTxtDefaultCylindrical	= 3,		/*!< Cylindrical projection. */
        siTxtDefaultSpherical	= 4,		/*!< Spherical projection. */
        siTxtDefaultSpatial	= 5,		/*!< Spatial projection. */
        siTxtDefaultCubic	= 6,		/*!< Cubic projection. */
        siTxtDefaultLollipop	= 8		/*!< Lollipop projection. */
    } 	siTxtDefaultCreationType;

/*! Texture projection type constants. To use with the texturing commands. */
typedef   
enum siTxtProjType
    {
        siProjPlanar	= 0,		/*!< Planar projection. */
        siProjCylindrical	= 1,		/*!< Cylindrical projection. */
        siProjSpherical	= 2,		/*!< Spherical projection. */
        siProjLollipop	= 3,		/*!< Lollipop projection. */
        siProjSpatial	= 4,		/*!< Spatial projection. */
        siProjCubic	= 5		/*!< Cubic projection. */
    } 	siTxtProjType;

/*! Texture projection plane constants. To use with the texturing commands. */
typedef   
enum siTxtProjPlane
    {
        siPlaneXY	= 0,		/*!< XY Plane. */
        siPlaneXZ	= 1,		/*!< XZ Plane. */
        siPlaneYZ	= 2		/*!< YZ Plane. */
    } 	siTxtProjPlane;

/*! Texture support positioning constants. To use with the texturing commands. */
typedef   
enum siTxtProjFitMethod
    {
        siRelDefault	= 0,		/*!< Perform default behavior for input: siRelBestFit for subcomponents, siRelObject for objects. */
        siRelBestFit	= 1,		/*!< Choose the best fit for the projection. */
        siRelObject	= 2,		/*!< Align relative to the object's coordinate system. */
        siRelWorld	= 3,		/*!< Align relative to the world's coordinate system. */
        siRelObjectPosObject	= 4,		/*!< Align relative to the object's coordinate system, and position/scale relative to the object's bounding box. */
        siRelWorldPosObject	= 5		/*!< Align relative to the world's coordinate system, and position/scale relative to the object's bounding box. */
    } 	siTxtProjFitMethod;

/*! Actions for the ChangeUVInput command */
typedef   
enum siChangeUVInputActions
    {
        siChangeUVInputActionSwim	= 0,		/*!< Cause the UV to swim (move to top of operator stack). */
        siChangeUVInputActionStick	= 1,		/*!< If the UV operator is swimming (top of operator stack), cause the operator to stick (top of modeling). */
        siChangeUVInputActionReproject	= 2		/*!< If the UV operator is sticking (modeling region), force the operator to the top of the modeling stack. */
    } 	siChangeUVInputActions;

/*! Modes for the align command */
typedef   
enum siAlignModes
    {
        siAlignGMIN	= 0,		/*!< Global minimum bounding value of the whole selection */
        siAlignGMIDDLE	= 1,		/*!< Global center bounding value of the whole selection */
        siAlignGMAX	= 2,		/*!< Global maximum bounding value of the whole selection */
        siAlignFMIN	= 3,		/*!< Minimum bounding value of the first selected object */
        siAlignFMIDDLE	= 4,		/*!< Center bounding value of the first selected object */
        siAlignFMAX	= 5		/*!< Maximum bounding value of the first selected object */
    } 	siAlignModes;

/*! Presets for the PresetWeight command */
typedef   
enum siWeightPresets
    {
        siWeightEaseIn	= 1,		/*!< Ease-in preset */
        siWeightEaseOut	= 2,		/*!< Ease-out preset */
        siWeightLinearEaseIn	= 3,		/*!< Linear ease-in preset */
        siWeightLinearEaseOut	= 4,		/*!< Linear ease-out preset */
        siWeightExponentialIn	= 5,		/*!< Exponential-in preset */
        siWeightExponentialOut	= 6,		/*!< Exponential-out presett */
        siWeightGaussian	= 7,		/*!< Gaussian preset */
        siWeightGaussianReverse	= 8,		/*!< Reverse gaussian preset */
        siWeightSquare	= 9,		/*!< Square preset */
        siWeightSquareReverse	= 10,		/*!< Reverse square preset */
        siWeightOscillate	= 11,		/*!< Oscillation preset */
        siWeightConstant	= 12,		/*!< Constant preset */
        siWeightFlipX	= 13,		/*!< Flip X of weight curve */
        siWeightFlipY	= 14		/*!< Flip Y of weight curve */
    } 	siWeightPresets;

/*! Cut options for the <command idref="CutClip"/> command. */
typedef   
enum siCutClipOptions
    {
        siCut	= 1,		/*!< Splits the clip in two distincts clips */
        siTrimBefore	= 2,		/*!< Trims the clip keeping the tail */
        siTrimAfter	= 3		/*!< Trims the clip keeping the head */
    } 	siCutClipOptions;

/*! Edit clip options for the EditClip command */
typedef   
enum siEditClipOptions
    {
        siClipNudge	= 1,		/*!< Nudge clip */
        siClipSlip	= 2,		/*!< Slip clip */
        siClipTrim	= 3,		/*!< Trim the tail of the clip */
        siClipScale	= 4,		/*!< Scale clip */
        siClipStartAt	= 5,		/*!< Start clip at frame */
        siClipEndAt	= 6,		/*!< End clip at frame */
        siClipScaleTo	= 7,		/*!< Scale clip to frame */
        siClipTrimStart	= 8		/*!< Trim the head of the clip */
    } 	siEditClipOptions;

/*! Preset locations */
typedef   
enum siPresetLocation
    {
        siDefaultLocation	= 0,		/*!< Default location */
        siFactory	= 1,		/*!< Factory */
        siUser	= 2,		/*!< User */
        siWorkgroup	= 3,		/*!< Workgroup */
        siProject	= 4		/*!< Project */
    } 	siPresetLocation;

/*! The variant type determines the kind of value that can be stored in a parameter.<br/> Note: Only a subset of these types are fully supported and recommended for use: these are siString, siBool, siDouble, siFloat, siInt4, siInt2, siUInt4, siUInt2, siByte, and siUByte. (See <link idref="DataTypes"/> for more information). */
typedef   
enum siVariantType
    {
        siEmpty	= 0,		/*!< no type */
        siInt2	= 2,		/*!< 2 bytes signed integer number (-32768..32767) */
        siInt4	= 3,		/*!< 4 bytes signed integer number (-2147483648..2147483647) (See <link idref="Long"/>) */
        siFloat	= 4,		/*!< <link idref="Float"/>: single precision real number (-3.402823466e+38F..3.402823466e+38F) */
        siDouble	= 5,		/*!< <link idref="Double"/>: double precision real number (-1.7976931348623158e+308..1.7976931348623158e+308) */
        siString	= 8,		/*!< Text represented as a BSTR.  See <link idref="String"/>. */
        siDispatch	= 9,		/*!< dispatch object.  This is an object which exposes methods and properties to scripting.  This is the variant type of all objects in the Object Model. */
        siBool	= 11,		/*!< <link idref="Boolean"/> */
        siUnknown	= 13,		/*!< Pointer to a COM object.  This object cannot be manipulated from scripting and such an object is not normally exposed in the Object Model. */
        siByte	= 16,		/*!< byte (-128..127) */
        siUByte	= 17,		/*!< unsigned byte (0..255) */
        siUInt2	= 18,		/*!< 2 bytes unsigned integer number (0..65535) */
        siUInt4	= 19,		/*!< 4 bytes unsigned integer number (0..4294967295) */
        siInt	= 22,		/*!< signed machine integer.  This variant type is not supported, use siInt4 instead. */
        siUInt	= 23,		/*!< unsigned machine integer.  This variant type is not supported, use siUInt4 instead. */
        siWStr	= 31		/*!< Null-terminated wide character string.  This variant type is rarely encountered because siString is the recommended representation for all Softimage strings. */
    } 	siVariantType;

/*! This determines the classification of a <object idref="Parameter"/> to give Softimage some hint about its purpose. In most cases it is acceptable to use the default, siClassifUnknown. */
typedef   
enum siParamClassification
    {
        siClassifVisualization	= 1,		/*!< Parameter affects the UI visualization of an object (ex: level of detail) */
        siClassifPositioning	= 2,		/*!< Parameter affects the location, size and position of an object (ex: scaling) */
        siClassifAppearance	= 4,		/*!< Parameter affects the visual appearance of the default representation of an object (ex: color) */
        siClassifMetaData	= 8,
        siClassifModel	= 16,
        siClassifTopo	= 16481,
        siClassifGeometry	= 16449,
        siClassifUnknown	= 32768		/*!< Default classification for normal parameters. */
    } 	siParamClassification;

/*! Port choice for the <command idref="SIGetMaterialShader"/> command */
typedef   
enum siMaterialPorts
    {
        siMaterialPortSurface	= 1,		/*!< Surface shader port */
        siMaterialPortVolume	= 2,		/*!< Volume shader port */
        siMaterialPortEnvironment	= 3,		/*!< Environment shader port */
        siMaterialPortContour	= 4,		/*!< Contour shader port */
        siMaterialPortDisplacement	= 5,		/*!< Displacement shader port */
        siMaterialPortShadow	= 6,		/*!< Shadow shader port */
        siMaterialPortPhoton	= 7,		/*!< Photon shader port */
        siMaterialPortPhotonVol	= 8,		/*!< Photon volume shader port */
        siMaterialPortBumpMap	= 9		/*!< Bump map shader port */
    } 	siMaterialPorts;

/*! Defines the material shading model */
typedef   
enum siShadingModel
    {
        siUndefinedShadingModel	= -1,		/*!< Undefined shading model */
        siShadingModelConstant	= 0,		/*!< Constant shading */
        siShadingModelLambert	= 1,		/*!< Lambert shading */
        siShadingModelBlinn	= 2,		/*!< Blinn shading */
        siShadingModelPhong	= 3,		/*!< Phong shading */
        siShadingModelShadow	= 4,		/*!< Shadow shading */
        siShadingModelColorVertex	= 5		/*!< Color vertex shading */
    } 	siShadingModel;

/*! Defines the shader type */
typedef   
enum siShaderType
    {
        siShaderUnknown	= 0,		/*!< Unknown shader */
        siShader	= 1,		/*!< Normal shader */
        siShaderCompound	= 2,		/*!< Shader Compound */
        siShaderComment	= 3		/*!< Shader Comment */
    } 	siShaderType;

/*! Defines the output shader parameter types */
typedef   
enum siShaderOutputType
    {
        siUnknownOutputType	= 0,		/*!< See siUnknownParameterType */
        siBooleanOutputType	= 1,		/*!< See siBooleanParameterType */
        siIntegerOutputType	= 2,		/*!< See siIntegerParameterType */
        siScalarOutputType	= 3,		/*!< See siScalarParameterType */
        siColorOutputType	= 4,		/*!< See siColorParameterType */
        siVectorOutputType	= 5,		/*!< See siVectorParameterType */
        siTextureSpaceOutputType	= 6,		/*!< See siTextureSpaceParameterType */
        siTextureOutputType	= 7,		/*!< See siTextureParameterType */
        siStringOutputType	= 8,		/*!< See siStringParameterType */
        siFilenameOutputType	= 9,		/*!< See siStringParameterType (remapped to string) */
        siLensOutputType	= 10,		/*!< See siLensParameterType */
        siLightOutputType	= 11,		/*!< See siLightParameterType */
        siMaterialOutputType	= 12,		/*!< See siMaterialParameterType */
        siModelOutputType	= 13,		/*!< See siModelParameterType */
        siLightmapOutputType	= 20		/*!< See siLightmapParameterType */
    } 	siShaderOutputType;

/*! These represent the shader parameter data types for instantated shaders. <br/> Note: For shader parameter definitions, the <object idref="siShaderParameterDataType"/> values are used instead.*/
typedef   
enum siShaderParameterType
    {
        siUnknownParameterType	= 0,		/*!< Unknown parameter type */
        siArrayParameterType	= 25,		/*!< Array shader parameter type */
        siBooleanParameterType	= 1,		/*!< Boolean shader parameter type */
        siColorParameterType	= 4,		/*!< Color RGBA shader parameter type */
        siColor3ParameterType	= 29,		/*!< Color RGB shader parameter type */
        siCustomParameterType	= 28,		/*!< Custom shader parameter type */
        siDataParameterType	= 14,		/*!< Data shader parameter type */
        siGradientParameterType	= 26,		/*!< Gradient shader parameter type */
        siIntegerParameterType	= 2,		/*!< Integer shader parameter type */
        siLensParameterType	= 10,		/*!< Lens shader parameter type */
        siLightParameterType	= 11,		/*!< Light shader parameter type */
        siLightmapParameterType	= 20,		/*!< Lightmap shader parameter type */
        siMaterialParameterType	= 12,		/*!< Material shader parameter type */
        siMatrixParameterType	= 15,		/*!< Transform matrix 4x4 shader parameter type */
        siMatrix3ParameterType	= 24,		/*!< Transform matrix 3x3 shader parameter type */
        siModelParameterType	= 13,		/*!< Model parameter type, maps shader output type that can write to geometry shader. */
        siProfileCurveParameterType	= 21,		/*!< Profile curve parameter type. */
        siQuaternionParameterType	= 27,		/*!< Quaterninon shader parameter type */
        siRealTimeParameterType	= 16,		/*!< Realtime shader parameter type */
        siReferenceParameterType	= 17,		/*!< Reference shader parameter type, input type only. */
        siScalarParameterType	= 3,		/*!< Scalar shader parameter type; <link idref="Float"/> */
        siShaderReferenceParameterType	= 18,		/*!< Shader reference shader parameter type */
        siStringParameterType	= 8,		/*!< String shader parameter type */
        siStructParameterType	= 19,		/*!< Struct shader parameter type */
        siTextureParameterType	= 7,		/*!< Texture shader parameter type; normally a <object idref="ImageClip"/> object (in the object model) or ImageClip2 class (in the C++ API). */
        siTextureSpaceParameterType	= 6,		/*!< Texturespace shader parameter type; ; such as a vertexcolor, UV texture, weightmap <object idref="ClusterProperty"/> object or a texture map <object idref="Property"/>. */
        siVectorParameterType	= 5,		/*!< Vector3d shader parameter type */
        siVector2ParameterType	= 22,		/*!< Vector2d shader parameter type */
        siVector4ParameterType	= 23		/*!< Vector4d shader parameter type */
    } 	siShaderParameterType;

/*! Defines the <object idref="Shader"/> parameter type for a <object idref="Parameter"/> object belonging to <object idref="Shader"/>, <object idref="Material"/>, <object idref="Light"/> or <object idref="Camera"/>. Shader parameter types only apply to parameters that support the <object idref="siCapabilities#siTexturable"/> capability. This can be tested using the <object idref="Parameter.Capabilities"/> property. The output type of a shader can be checked using the <object idref="Shader.OutputType"/> property. <br/> Note: Each data type, apart from <object idref="siShaderParameterDataType#siShaderDataTypeUnknown"/>, has also an equivalent string name that can be used to create shader parameter definitions using type strings, instead of this enum. Custom port types can't be registered using those built-in string names. The string names are shown in brackets after each type's description. */
typedef   
enum siShaderParameterDataType
    {
        siShaderDataTypeUnknown	= -1,		/*!< Not a known type */
        siShaderDataTypeBoolean	= 0,		/*!< A boolean value ["boolean"] */
        siShaderDataTypeInteger	= 1,		/*!< A signed integer value ["integer"] */
        siShaderDataTypeScalar	= 2,		/*!< A scalar (floating point) value ["scalar"] */
        siShaderDataTypeVector2	= 3,		/*!< A 2-scalar component vector value ["vector2"] */
        siShaderDataTypeVector3	= 4,		/*!< A 3-scalar component vector value ["vector3"] */
        siShaderDataTypeVector4	= 5,		/*!< A 4-scalar component vector value ["vector4"] */
        siShaderDataTypeQuaternion	= 6,		/*!< A 4-scalar component quaternion value ["quaternion"] */
        siShaderDataTypeMatrix33	= 7,		/*!< A 9-scalar component matrix value ["matrix33"] */
        siShaderDataTypeMatrix44	= 8,		/*!< A 16-scalar component matrix value ["matrix44"] */
        siShaderDataTypeColor3	= 9,		/*!< A 3-scalar component color value (red, green, and blue) ["color3"] */
        siShaderDataTypeColor4	= 10,		/*!< A 4-scalar component color value (red, green, blue, and alpha) ["color4"] */
        siShaderDataTypeString	= 11,		/*!< A string value ["string"] */
        siShaderDataTypeProperty	= 16,
        siShaderDataTypeProfileCurve	= 17,		/*!< A profile curve (scalar fcurve) ["fcurve"]. */
        siShaderDataTypeGradient	= 18,		/*!< A color gradient ["gradient"] */
        siShaderDataTypeLightProfile	= 19,		/*!< A light profile parameter ["lightprofile"] */
        siShaderDataTypeReference	= 32,
        siShaderDataTypeImage	= 33,		/*!< An image input (texture map) ["image"] */
        siShaderDataTypeCustom	= 48,
        siShaderDataTypeStructure	= 64,		/*!< A strucure container ["structure"] */
        siShaderDataTypeArray	= 65		/*!< An array container ["array"] */
    } 	siShaderParameterDataType;

typedef   
enum siShaderParameterConnectionType

    {
        siShaderCnxUnknown	= -1,
        siShaderCnxInput	= 0,
        siShaderCnxOutput	= 1
    } 	siShaderParameterConnectionType;

/*! Defines the types of filters when creating a shader parameter definition of type reference(<object idref="siShaderParameterDataType#siShaderDataTypeReference"/>). When you call the SetAttribute method, pass <object idref="siShaderParameterAttribute#siReferenceFilterAttribute"/> in the first parameter and one of these values in the second parameter.*/
typedef   
enum siShaderReferenceFilterType
    {
        siUnknownReferenceFilter	= 0,		/*!< Unknown filter. */
        siObjectReferenceFilter	= 1,		/*!< Any X3DObject. */
        siCameraReferenceFilter	= 2,		/*!< Any camera primitive. */
        siLightReferenceFilter	= 3,		/*!< Any light primitive. */
        siMaterialReferenceFilter	= 4,		/*!< Any material. */
        siShaderReferenceFilter	= 5,		/*!< Any shader. */
        siGeometryReferenceFilter	= 6,		/*!< Any geometric primitive. */
        siUserDataBlobReferenceFilter	= 7		/*!< Any userdata blob. */
    } 	siShaderReferenceFilterType;

/*! Defines the flags for Shaderball Dimension used by the <object idref="ShaderballOptions"/> object. */
typedef   
enum siShaderballDimension
    {
        siShaderballDimUndefined	= 0,		/*!< Undefined. */
        siShaderballDimParametric	= 1,		/*!< Supports Parametric Shaderballs. */
        siShaderballDimSpatial	= 2,		/*!< Supports Spatial Shaderballs. */
        siShaderballDimParticle	= 4,		/*!< Supports Particle Shaderballs. */
        siShaderballDimAll	= 7		/*!< Supports all dimensions. */
    } 	siShaderballDimension;

/*! Defines the types of filters when creating a shader parameter definition of type property look-up(<object idref="siShaderParameterDataType#siShaderDataTypeProperty"/>). When you call the SetAttribute method, pass <object idref="siShaderParameterAttribute#siPropertyFilterAttribute"/> in the first parameter and one of these values in the second parameter.*/
typedef   
enum siShaderPropertyFilterType
    {
        siAnyPropertyFilter	= 0,		/*!< Any property. */
        siAnyVertexMapPropertyFilter	= 1,		/*!< Any vertex map property. */
        siUVPropertyFilter	= 2,		/*!< Texture projection property. */
        siCAVPropertyFilter	= 3,		/*!< Color-at-Vertices property. */
        siWeightMapPropertyFilter	= 4,		/*!< Weightmap property. */
        siTextureMapPropertyFilter	= 5,		/*!< Texture map property. */
        siNormalPropertyFilter	= 6		/*!< Normal property. */
    } 	siShaderPropertyFilterType;

/*! Defines the types of light */
typedef   
enum siLightType
    {
        siLightPoint	= 0,		/*!< Point light */
        siLightInfinite	= 1,		/*!< Infinite light */
        siLightSpot	= 2,		/*!< Spot light */
        siLightSun	= 3,		/*!< Sun light */
        siUndefinedLightType	= 4		/*!< Undefined light */
    } 	siLightType;

/*! Types of groups in connection sets */
typedef   
enum siCnxGroupType
    {
        siCreatedObjects	= 1		/*!< Created objects group */
    } 	siCnxGroupType;

/*! Types of connection sets */
typedef   
enum siCnxSetType
    {
        siGroupLevel	= 0,		/*!< Group level specifies objects containing the components that will be connected to the an operator's group of ports */
        siPortLevel	= 1		/*!< Port level specifies objects that will be directly connected to the operator ports */
    } 	siCnxSetType;

/*! Types of <object idref="Partition"/>s. */
typedef   
enum siPartitionType
    {
        siUnknownPartition	= 0,		/*!< Unknown partition */
        siObjectPartition	= 1,		/*!< Object partition */
        siLightPartition	= 2		/*!< Light partition */
    } 	siPartitionType;

/*! Levels of lock. Each level is a bit field. */
typedef   
enum siLockLevel
    {
        siLockLevelNone	= 0,		/*!< Not locked */
        siLockLevelConstruction	= 1,		/*!< Cannot change the hierarchy and topology */
        siLockLevelAnimation	= 2,		/*!< Cannot animate */
        siLockLevelManipulation	= 4,		/*!< Cannot change the values */
        siLockLevelNavigation	= 8,		/*!< Cannot navigate (not supported) */
        siLockLevelAll	= 0xffff		/*!< All levels */
    } 	siLockLevel;

/*! Type of lock owner. The lock owner type indicated who or why an object is locked, Users can modify only the locks of type siLockTypeUser. */
typedef   
enum siLockType
    {
        siLockTypeNone	= 0,		/*!< Not locked */
        siLockTypeSystem	= 1,		/*!< Locked by the system */
        siLockTypeUser	= 2,		/*!< Locked by a user */
        siLockTypeRefModel	= 3,		/*!< Locked by a referenced model */
        siLockTypeOverride	= 4,		/*!< Locked by an override */
        siLockTypeAll	= 0xffff		/*!< All owners (not used) */
    } 	siLockType;

/*!  These are the different levels of tags */
typedef   
enum siTags
    {
        siTagNone	= 0,		/*!< Not tagged */
        siTag1	= 1,		/*!< User-defined tag 1 */
        siTag2	= 2,		/*!< User-defined tag 2 */
        siTag3	= 4,		/*!< User-defined tag 3 */
        siTag4	= 8,		/*!< User-defined tag 4 */
        siTag5	= 16,		/*!< User-defined tag 5 */
        siTag6	= 32,		/*!< User-defined tag 6 */
        siTag7	= 64,		/*!< User-defined tag 7 */
        siTag8	= 128,		/*!< User-defined tag 8 */
        siTag9	= 256,		/*!< User-defined tag 9 */
        siTag10	= 512,		/*!< User-defined tag 10 */
        siTagAll	= 0xffff		/*!< All tags */
    } 	siTags;

/*! Type of geometry */
typedef   
enum siGeometryType
    {
        siNurbsSurfaceMesh	= 0,		/*!< Nurbs surface */
        siNurbsCurveList	= 1,		/*!< Nurbs curve */
        siPolygonMesh	= 2,		/*!< Mesh surface */
        siPointCloud	= 3		/*!< Point cloud */
    } 	siGeometryType;

/*! Types of bounding volumes */
typedef   
enum siBoundingVolume
    {
        siBoundingBox	= 0		/*!< Bounding box */
    } 	siBoundingVolume;

/*! Enumerates the different kinds of ports. */
typedef   
enum siPortType
    {
        siPortInput	= 0,		/*!< Input port. */
        siPortOutput	= 1		/*!< Output port. */
    } 	siPortType;

/*! Type of modification on a referenced model. This is a bit field, so many values can be combined. */
typedef   
enum siModificationType
    {
        siModificationTypeNone	= 0,		/*!< None */
        siModificationTypeStaticPosition	= 1,		/*!< Static Posistion */
        siModificationTypeFCurves	= 2,		/*!< Animation FCurves */
        siModificationTypeExpression	= 4,		/*!< Expressions */
        siModificationTypeConstraints	= 8,		/*!< Constraints */
        siModificationTypeAddProp	= 16,		/*!< Adding properties */
        siModificationTypeAnimMixer	= 32,		/*!< Adding Animation mixer */
        siModificationTypeGroup	= 64,		/*!< Groups */
        siModificationTypeInstance	= 128,		/*!< Instances */
        siModificationTypeOtherConnections	= 256,		/*!< Other connections */
        siModificationTypeOperators	= 512,		/*!< Operators */
        siModificationTypeClusters	= 1024,		/*!< Clusters */
        siModificationTypeClusterProperties	= 2048,		/*!< Cluster Properties */
        siModificationTypeAll	= 65535		/*!< All types */
    } 	siModificationType;

/*! Type of mixer modification on a referenced model. This is a bit field, so many values can be combined. */
typedef   
enum siModificationMixerType
    {
        siModificationMixerNone	= 0,		/*!< None */
        siModificationMixerAnimation	= 1,		/*!< Animation tracks */
        siModificationMixerShape	= 2,		/*!< Shape tracks */
        siModificationMixerAudio	= 4,		/*!< Audio tracks */
        siModificationMixerCache	= 8,		/*!< Cache tracks */
        siModificationMixerTypeAll	= 65535		/*!< All types */
    } 	siModificationMixerType;

/*! Resolution description of a file for a referenced model. <br/> Used by the AddModelSource, SetResolutionOfRefModels, and SIAddModelSource commands. */
typedef   
enum siModelResolution
    {
        siModelResolutionOffLoaded	= 0,		/*!< Model not loaded */
        siModelResolutionLowRes	= 1,		/*!< Low resolution */
        siModelResolutionMediumRes	= 2,		/*!< Medium resolution */
        siModelResolutionHighRes	= 3		/*!< High resolution */
    } 	siModelResolution;

/*! Type of parameters to gather from the input Object List.<br/>Note: This enum replaces the obsolete siSequenceType enum as of v6.0. */
typedef   
enum siParameterScope
    {
        siInputParameters	= 1,		/*!< Use the input parameters directly from the Object List */
        siAnimatedParameters	= 2,		/*!< Use only the parameters of the Object List that are animated */
        siAllAnimatedParameters	= 3		/*!< Ignore Object List and use all animated parameters in the scene (ie., every animated parameter on each object in the scene) */
    } 	siParameterScope;

/*! Type of input objects for the Sequence feature. */
typedef   
enum siSequenceType
    {
        siMarkedParams	= 1,		/*!< Marked parameters of selected objects(s) */
        siAnimParams	= 2,		/*!< Animated parameters of selected objects(s) */
        siAllAnimParams	= 3		/*!< All animated parameters of all objects in scene */
    } 	siSequenceType;

/*! Mode to use for the Sequence feature */
typedef   
enum siSequenceMode
    {
        siFCurves	= 1,		/*!< Process fcurves */
        siFCurvesAnimationSources	= 2,		/*!< Process fcurves and animation sources */
        siFCurvesClips	= 3,		/*!< Process fcurves and clips */
        siAnimationSources	= 4,		/*!< Process animation sources */
        siClips	= 5		/*!< Process clips */
    } 	siSequenceMode;

/*! Type of input objects for clip effect features */
typedef   
enum siEffectInputType
    {
        siSelectedParams	= 1,		/*!< Marked parameters of selected objects(s) */
        siAllParamsInClip	= 2,		/*!< Single clip - operate on all parameters */
        siPoseOffsetClip	= 3		/*!< Single clip - operate on pose offset */
    } 	siEffectInputType;

/*! Types of neighboring for the deprecated <object idref="Geometry_V1"/>. */
typedef   
enum siNeighborType
    {
        siAdjacent	= 1,		/*!< Adjacent neighboring */
        siGrow	= 2,		/*!< Grow neighboring */
        siNextCompo	= 3,		/*!< Next component */
        siPrevCompo	= 4,		/*!< Prev component */
        siFirstCompo	= 5,		/*!< First component */
        siLastCompo	= 6		/*!< Last component */
    } 	siNeighborType;

/*! Modes for the SelectNeighborObj command */
typedef   
enum siNavigDirection
    {
        siNavigUp	= 0,		/*!< Navigate up */
        siNavigDown	= 1,		/*!< Navigate down */
        siNavigLeft	= 2,		/*!< Navigate left */
        siNavigRight	= 3,		/*!< Navigate right */
        siNavigFirst	= 4,		/*!< Navigate to first item */
        siNavigLast	= 5		/*!< Navigate to last item */
    } 	siNavigDirection;

/*! Direction of the next Node */
typedef   
enum siNavigationDirection
    {
        siParentNode	= 1,		/*!< Ask for parent of the current node */
        siChildNode	= 2,		/*!< Ask for parent of the current node */
        siNextNode	= 3,		/*!< Ask for next sibling of the current node */
        siPreviousNode	= 4,		/*!< Ask for previous sibling of the current node */
        siFirstNode	= 5,		/*!< Ask for first sibling of the current node */
        siLastNode	= 6		/*!< Ask for last sibling of the current node */
    } 	siNavigationDirection;

/*! Direction of the next Node */
typedef   
enum siNavigationFilter
    {
        siNavigationFilterScene	= 1,		/*!< Scene */
        siNavigationFilter3DObject	= 2,		/*!< 3D Object */
        siNavigationFilterOperator	= 3,		/*!< Operator */
        siNavigationFilterPrimitive	= 4,		/*!< Primitive */
        siNavigationFilterProperty	= 5,		/*!< Container or attribute */
        siNavigationFilterCluster	= 6,		/*!< Cluster */
        siNavigationFilterObjectSubElems	= 7,		/*!< Subcomponent */
        siNavigationFilterGroup	= 8,		/*!< Group */
        siNavigationFilterGenericComObject	= 9,		/*!< Any COM Object */
        siNavigationFilterAll	= 10,		/*!< All types */
        siNavigationFilterSame	= 11		/*!< Same type */
    } 	siNavigationFilter;

/*! Sub-type of node wanted */
typedef   
enum siNavigationSubFilter
    {
        siNavigationSubFilterAll	= 0,		/*!< All types */
        siNavigationSubFilterSame	= 1		/*!< Same type */
    } 	siNavigationSubFilter;

/*! Type of views. This type is obsolete, you must use <object idref="si2DChainAlignType"/> instead. */
typedef   
enum siViewType
    {
        siNoView	= 0,		/*!< No viewport.  */
        siViewUser	= 1,		/*!< User viewport.  */
        siViewTop	= 2,		/*!< Top viewport. */
        siViewLeft	= 3,		/*!< Left viewport. */
        siViewRight	= 4		/*!< Right viewport. */
    } 	siViewType;

/*! Defines the types of alignment used for creating a 2D chain. <br/>Note: Use this enum instead of the obsolete siViewType enum. */
typedef   
enum si2DChainAlignType
    {
        si2DChainTop	= 0,		/*!< Align with top viewport.  */
        si2DChainFront	= 1,		/*!< Align with front viewport.  */
        si2DChainRight	= 2,		/*!< Align with right viewport. */
        si2DChainNormalRadian	= 3,		/*!< Align with plane normal, value must be specified in radian units. */
        si2DChainNormalDegree	= 4		/*!< Align with plane normal, value must be specified in degree units. */
    } 	si2DChainAlignType;

/*! Type of chain bones. */
typedef   
enum siChainBoneType
    {
        siChainBoneUndefined	= 0,		/*!< Undefined type */
        siChainBonePin	= 1,		/*!< Pin bone */
        siChainBoneBallJoint	= 2		/*!< Ball joint bone */
    } 	siChainBoneType;

/*! Operator connection types */
typedef   
enum siConnectionType
    {
        siReadConnection	= 1,		/*!< Read only */
        siWriteConnection	= 2,		/*!< Write only */
        siReadWriteConnection	= 3		/*!< Read/write */
    } 	siConnectionType;

/*! Bitmask for types of axes */
typedef   
enum siAxisType
    {
        siXAxis	= 1,		/*!< X axis */
        siYAxis	= 2,		/*!< Y axis */
        siZAxis	= 3		/*!< Z axis */
    } 	siAxisType;

/*! Type of knot parameterization type for NurbsCurves. */
typedef   
enum siKnotParameterization
    {
        siUniformParameterization	= 0,		/*!< Uniform */
        siNonUniformParameterization	= 1,		/*!< Non-uniform */
        siChordLengthParameterization	= 2,		/*!< Chord_length */
        siCentripetalParameterization	= 3		/*!< Centripetal */
    } 	siKnotParameterization;

/*! Types of mapping rules. */
typedef   
enum siMappingRuleType
    {
        siConnectionMappingRule	= 0,		/*!< Connection mapping rule */
        siValueMappingRule	= 1		/*!< Value mapping rule */
    } 	siMappingRuleType;

/*! Types of nurbs direction parameters. */
typedef   
enum siNurbsDirection
    {
        siUDirection	= 0,		/*!< Nurbs direction in U */
        siVDirection	= 1		/*!< Nurbs direction in V */
    } 	siNurbsDirection;

/*! Types of nurbs format. */
typedef   
enum siNurbsFormat
    {
        siSINurbs	= 0,		/*!< Softimage Nurbs format */
        siIGESNurbs	= 1		/*!< IGES Nurbs format */
    } 	siNurbsFormat;

/*! Installation path directories. */
typedef   
enum siInstallationPath
    {
        siProjectPath	= 0,		/*!< Project directory path. */
        siUserPath	= 1,		/*!< User directory path. */
        siWorkgroupPath	= 2,		/*!< Workgroup directory path. See <object idref="XSIApplication.Workgroups"/>. */
        siFactoryPath	= 3,		/*!< Factory directory path. */
        siAddonPath	= 4,		/*!< Add-on directory path. */
        siUserAddonPath	= 5,		/*!< User Add-on directory path. */
        siWorkgroupAddonPath	= 6,		/*!< Workgroup Add-on directory path. */
        siUnknownPath	= 7,		/*!< Unknown installation path. */
        siCustomPath	= 9		/*!< The custom plug-in directory path. This value maps to the XSI_PLUGINS environment variable which may contain multiple folders. */
    } 	siInstallationPath;

/*! Shape key instantiation mode. */
typedef   
enum siShapeInstanceMode
    {
        siShapeInstanceOnlyMode	= 0,		/*!< Only instance the action. */
        siShapeMixedWeightMode	= 1,		/*!< Instance in mixed weight mode. */
        siShapeTransitionMode	= 2,		/*!< Instance in transition mode. */
        siShapeTransitionCardinalMode	= 3,		/*!< Instance in transition cardinal mode. */
        siShapeBlendedWeightMode	= 4		/*!< Instance in mixed weight mode without keying the weight. */
    } 	siShapeInstanceMode;

/*! Shape key reference mode. */
typedef   
enum siShapeReferenceMode
    {
        siShapeLocalReferenceMode	= 0,		/*!< Shapes are relative to reference frame of the control vertices. */
        siShapeObjectReferenceMode	= 1,		/*!< Shapes are relative to the primitive reference frame. */
        siShapeAbsoluteReferenceMode	= 2		/*!< Shapes are absolute. */
    } 	siShapeReferenceMode;

/*! Indicates which deforms will be stored in the created shape. */
typedef   
enum siShapeContent
    {
        siShapeContentUseConstructionMode	= 0,
        siShapeContentPrimaryShape	= 1,		/*!< Store the primary shape deformations. */
        siShapeContentSecondaryShape	= 2,		/*!< Store the secondary shape deformations. */
        siShapeContentAllDeforms	= 3		/*!< Store all except for modeling deforms. */
    } 	siShapeContent;

/*! The construction mode indicates the purpose of the deformations. */
typedef   
enum siConstructionMode
    {
        siConstructionModeModeling	= 0,		/*!< The deformations are used to model the geometry. */
        siConstructionModePrimaryShape	= 1,		/*!< The deformations are used to author shapes based on the base geometry. */
        siConstructionModeAnimation	= 2,		/*!< The deformations are used to animate the geometry. */
        siConstructionModeSecondaryShape	= 3,		/*!< The deformations are used to author shapes based on the animated geometry. */
        siConstructionModeDefault	= 4		/*!< Use the current user preference. */
    } 	siConstructionMode;

/*! Resolution Plane Type for Chain joints */
typedef   
enum siResolutionPlane
    {
        siDefaultResolutionPlane	= 0,		/*!< Default resolution plane */
        siPreferredAxisPlane	= 1,		/*!< Preferred axis plane */
        siUpVectorPlane	= 2		/*!< Up-vector plane */
    } 	siResolutionPlane;

/*! Texture creation type constants. To use with the texturing commands. */
typedef   
enum siTextureProjectionType
    {
        siTexturePlanarXY	= 0,		/*!< XY Planar projection. */
        siTexturePlanarXZ	= 1,		/*!< XZ Planar projection. */
        siTexturePlanarYZ	= 2,		/*!< YZ Planar projection. */
        siTextureCylindrical	= 3,		/*!< Cylindrical projection. */
        siTextureSpherical	= 4,		/*!< Spherical projection. */
        siTextureSpatial	= 5,		/*!< Spatial projection. */
        siTextureCamera	= 6,		/*!< Camera projection. */
        siTextureUV	= 7,		/*!< UV projection. */
        siTextureLollipop	= 8,		/*!< Lollipop projection. */
        siTexturePureImplicit	= 9		/*!< Purely implicit projection. */
    } 	siTextureProjectionType;

/*! UV generation type used by the texture operator, used only if siTextureProjectionType:siTextureUV is specified as the projection type.*/
typedef   
enum siUVTextureType
    {
        siUVTexturePlanarXY	= 0,		/*!< XY Planar projection. */
        siUVTexturePlanarXZ	= 1,		/*!< XZ Planar projection. */
        siUVTexturePlanarYZ	= 2,		/*!< YZ Planar projection. */
        siUVTextureCylindrical	= 3,		/*!< Cylindrical projection. */
        siUVTextureSpherical	= 4,		/*!< Spherical projection. */
        siUVTextureSpatial	= 5,		/*!< Spatial projection. */
        siUVTextureLollipop	= 6		/*!< Lollipop projection. */
    } 	siUVTextureType;

/*! Determines the capabilities of a parameter. They can be combined by adding them: for example, to have a parameter animatable (1) and persistable (4), use 5.*/
typedef   
enum siCapabilities
    {
        siAnimatable	= 1,		/*!< Animatable */
        siReadOnly	= 2,		/*!< Cannot be written to */
        siPersistable	= 4,		/*!< Is saved with its parameter set */
        siNotInspectable	= 8,		/*!< Does not show up in the UI */
        siSilent	= 16,		/*!< For internal use only. Do not use. */
        siNotPresetPersistable	= 128,		/*!< Will not be saved in presets */
        siTexturable	= 256,		/*!< Parameter supports connection to rendering node */
        siKeyable	= 2048,		/*!< Parameter is visible in 'Keying Panel' and keyable */
        siNonKeyableVisible	= 4096		/*!< Parameter is only visible in 'Keying Panel' */
    } 	siCapabilities;

/*! Types of function curves (fcurves) */
typedef   
enum siFCurveType
    {
        siUnknownFCurve	= 0,		/*!< Unknown fcurve type */
        siDefaultFCurve	= 0,		/*!< Use the fcurve type associated with parameter type */
        siBooleanFCurve	= 10,		/*!< Boolean fcurve mapping a double parameter to {0, 1}. */
        siIntegerFCurve	= 15,		/*!< Integer fcurve. */
        siStandardFCurve	= 20,		/*!< FCurve mapping a double parameter to a double value. */
        siRawDataFCurve	= 30,		/*!< Raw data fcurve. */
        siQuaternionFCurve	= 40		/*!< Quaternion fcurve. */
    } 	siFCurveType;

/*! The extrapolation of an <object idref="FCurve"/> determines its shape before the first <object idref="FCurveKey"/> and after the last <object idref="FCurveKey"/>. Extrapolation extends the curve's ends based on the position of these two keys.*/
typedef   
enum siFCurveExtrapolation
    {
        siConstantExtrapolation	= 1,		/*!< Constant extrapolation */
        siLinearExtrapolation	= 2,		/*!< Linear extrapolation */
        siPeriodicExtrapolation	= 3,		/*!< Periodic extrapolation */
        siPeriodicRelativeExtrapolation	= 4		/*!< Constant extrapolation relative to an offset */
    } 	siFCurveExtrapolation;

/*! Function curve key constraints. The last seven tangent constraints apply only to standard function curves. FCurve key constraints can be set and retrieved via the <object idref="FCurveKey.Constraint"/> property. <br/> The constraints are not mutally exclusive for example if you have the siParameterConstraint set and clear the siLockConstraint you will also clear the siParameterConstraint. You cannot set constraints on a raw function curve. They will be ignored. */
typedef   
enum siFCurveKeyConstraint
    {
        siParameterConstraint	= 1,		/*!< If on, the parameter (or key time) is locked. */
        siLeftRightValuesConstraint	= 2,		/*!< If on, the left and right key values are locked. */
        siG1ContinuousConstraint	= 4,		/*!< If on, the left and right tangent orientations are the same. */
        siLeftRightTangentDirectionConstraint	= 8,		/*!< If on, the left and right tangent directions are locked. */
        siLeftRightTangentLengthConstraint	= 16,		/*!< If on, the left and right tangent lengths are locked. */
        siLockConstraint	= 32,		/*!< If on, the parameter, values, and tangents are locked. */
        siHorizontalTangentConstraint	= 64,		/*!< If on, the tangents are considered horizontal. */
        siExtremumHorizontalTangentConstraint	= 128,		/*!< If on, the tangents are considered as horizontal when the key is a local extremum. */
        siZeroLengthTangentConstraint	= 512,		/*!< If on, the left and right tangent lengths are constrained to be zero. */
        siSameLengthTangentConstraint	= 1024,		/*!< If on, the left and right tangent lengths are the same. */
        siNeighborTangentConstraint	= 2048,		/*!< If on, the left and right tangent point at the previous and next keys. */
        siMirrorTangentConstraint	= 4096,		/*!< If on, the left and right tangents are mirrored. */
        siAutoPlateauTangentConstraint	= 8192,		/*!< If on, the left and right tangents are automatically adjusted and plateaued based on neighbouring keys. */
        siAdjustedTangentConstraint	= 8448		/*!< If on, the tangents are adjusted automatically when neighbouring keys are created or moved. */
    } 	siFCurveKeyConstraint;

typedef   siFCurveKeyConstraint siFCurveKeyFlags;

/*! Specifies the interpolation type for a specific key on an fcurve. The interpolation determines how the value is evaluated between <object idref="FCurveKey"/>s. */
typedef   
enum siFCurveKeyInterpolation
    {
        siDefaultKeyInterpolation	= 0,		/*!< Existing function. */
        siConstantKeyInterpolation	= 1,		/*!< Constant function */
        siLinearKeyInterpolation	= 2,		/*!< Linear function */
        siCubicKeyInterpolation	= 3		/*!< Bezier cubic function */
    } 	siFCurveKeyInterpolation;

/*! Specifies the mode for changing the <object idref="FCurveKey"/> selection. */
typedef   
enum siFCurveKeySelectionMode
    {
        siSetKeySelection	= 1,		/*!< Set specified keys as new key selection (clears current key selection first) */
        siAddToKeySelection	= 2,		/*!< Add specified keys to current key selection */
        siRemoveFromKeySelection	= 3,		/*!< Remove keys from current key selection */
        siToggleKeySelection	= 4		/*!< Toggle key selection state */
    } 	siFCurveKeySelectionMode;

/*! The interpolation of an <object idref="FCurve"/> determines how values are evaluated between its <object idref="FCurveKey"/>s. This is very similar to the <object idref="siFCurveKeyInterpolation"/> enum.*/
typedef   
enum siFCurveInterpolation
    {
        siDefaultInterpolation	= 0,		/*!< Existing function */
        siConstantInterpolation	= 1,		/*!< Constant function */
        siLinearInterpolation	= 2,		/*!< Linear function */
        siCubicInterpolation	= 3		/*!< Bezier cubic function */
    } 	siFCurveInterpolation;

/*! Specifies the kind of filter used for smoothing function curves. */
typedef   
enum siFCurveSmoothFilterType
    {
        siFCurveAverageFilterType	= 1,		/*!< Moving Average filter. Use this filter to smooth the function curve by applying a moving average. The weights of the averages are uniformly distributed. */
        siFCurveGaussianFilterType	= 2		/*!< Gaussian filter. Use this filter to smooth the function curve by applying a moving average. The weights of the averages are distributed as a bell curve. This usually gives better results than the average filter. */
    } 	siFCurveSmoothFilterType;

#define	siPI	( 3.14159 )

/*! Information on the context in which a plug-in is being evaluated. */
typedef   
enum siUpdateContextState
    {
        siUpdateContextNormalEval	= 0,		/*!< Normal evaluation */
        siUpdateContextRenderEval	= 1		/*!< Evaluation during a render pass */
    } 	siUpdateContextState;

/*! Information on the direction of an argument indicating how it is passed to or from a command.<br/> Note: Output and InOut arguments are not supported by some script languages, including JScript. For this reason only siArgumentInput is supported on custom <object idref="Command"/>s.*/
typedef   
enum siArgumentFlags
    {
        siArgumentInput	= 2,		/*!< The parameter is passed as input to the command. */
        siArgumentOutput	= 4,		/*!< The parameter is used to return information from the command. */
        siArgumentInputOutput	= 6		/*!< The parameter is used to pass information both to and from a command. */
    } 	siArgumentFlags;

/*! Custom (v1.0) <object idref="Command"/>s can be defined from a pre-defined category. Each category specifies the base arguments of a command and the location of the menu item for that command in Softimage. Softimage automatically installs a menu item for each command created for a specific category. <br/> You can retrieve the type of category specified using either <object idref="SIObject.Categories"/> or <object idref="Command.Category"/> but you cannot define custom categories for this type of command. For that you need to use the alternative and more powerful, way to create custom commands and add them to <object idref="Menu"/>s: via the self-installing plug-in APIs.*/
typedef   
enum siCommandCategory
    {
        siImportCategory	= 0,
        siExportCategory	= 1,
        siSettingsCategory	= 2,
        siHelpCategory	= 3,
        siNoCategory	= 4,
        siFCurveCategory	= 5
    } 	siCommandCategory;

/*! Defines the option flags when importing a model or merging a scene. */
typedef   
enum siImportShareOptions
    {
        siImportShareOptionsNone	= 0,
        siImportShareOptionsImageClips	= 1,
        siImportShareOptionsMaterials	= 2,
        siImportShareOptionsLayers	= 4,
        siImportShareOptionsPartitions	= 8,
        siImportShareOptionsAll	= 0xffff
    } 	siImportShareOptions;

/*! This enumerator provides the identifiers for the Softimage events, they can be used for implementing C++ event handlers in order to identify the events fired by Softimage.*/
typedef   
enum siEventID
    {
        siOnBeginNewScene	= 542179328,		/*!< OnBeginNewScene event identifier. Fired when a new scene is created. */
        siOnEndNewScene	= 542179329,		/*!< OnEndNewScene event identifier. Fired when a new scene is created. */
        siOnBeginSceneOpen	= 542179330,		/*!< OnBeginSceneOpen event identifier. Fired after a user clicks OK in the Load Scene dialog box. See the list of available <article idref="ctxt_siOnBeginSceneOpen">Context Attributes</article> for this event. */
        siOnEndSceneOpen	= 542179331,		/*!< OnEndSceneOpen event identifier. Fired after the scene is loaded. See the list of available <article idref="ctxt_siOnEndSceneOpen">Context Attributes</article> for this event. */
        siOnBeginSceneSave	= 542179332,		/*!< OnBeginSceneSave event identifier. Fired when a scene is saved. */
        siOnEndSceneSave	= 542179333,		/*!< OnEndSceneSave event identifier. Fired when a scene is saved. */
        siOnBeginSceneSaveAs	= 542179334,		/*!< OnBeginSceneSaveAs event identifier. Fired when a scene is saved using File > Save As. See the list of available <article idref="ctxt_siOnBeginSceneSaveAs">Context Attributes</article> for this event. */
        siOnEndSceneSaveAs	= 542179335,		/*!< OnEndSceneSaveAs event identifier. Fired when a scene is saved using File > Save As. See the list of available <article idref="ctxt_siOnEndSceneSaveAs">Context Attributes</article> for this event. */
        siOnTerminate	= 542179336,		/*!< OnTerminate event identifier. Fired when Softimage exits.  */
        siOnSelectionChange	= 542179337,		/*!< OnSelectionChange event identifier. Fired when the selection lists change. See the list of available <article idref="ctxt_siOnSelectionChange">Context Attributes</article> for this event. This event is supported only by the <article idref="cus_displayhost" file="../custom/cus_displayhost.fm">Custom Display Host</article>. */
        siOnBeginFrame	= 542179338,		/*!< OnBeginFrame event identifier. Fired when a frame is rendered. See the list of available <article idref="ctxt_siOnBeginFrame">Context Attributes</article> for this event. */
        siOnEndFrame	= 542179339,		/*!< OnEndFrame event identifier. Fired when a frame is rendered. See the list of available <article idref="ctxt_siOnEndFrame">Context Attributes</article> for this event. */
        siOnBeginSequence	= 542179340,		/*!< OnBeginSequence event identifier. Fired before the first OnBeginFrame event when a sequence is rendered. See the list of available <article idref="ctxt_siOnBeginSequence">Context Attributes</article> for this event. */
        siOnEndSequence	= 542179341,		/*!< OnEndSequence event identifier. Fired after the last OnEndFrame event when a sequence is rendered. See the list of available <article idref="ctxt_siOnEndSequence">Context Attributes</article> for this event. */
        siOnKeyUp	= 542179342,		/*!< OnKeyUp event identifier. Fired when a user releases a key. OnKeyUp is not fired if the window with the focus handles keyboard events. See the list of available <article idref="ctxt_siOnKeyUp">Context Attributes</article> for this event. */
        siOnKeyDown	= 542179343,		/*!< OnKeyDown event identifier. Fired when a user presses a key. OnKeyDown is not fired if the window with the focus handles keyboard events. See the list of available <article idref="ctxt_siOnKeyDown">Context Attributes</article> for this event. */
        siOnValueChange	= 542179344,		/*!< OnValueChange event identifier. Fired when a parameter value or scene object is changed. See the list of available <article idref="ctxt_siOnValueChange">Context Attributes</article> for this event.Note: This event is a regular Softimage event but is also supported by the <article idref="cus_displayhost" file="../custom/cus_displayhost.fm">Custom Display Host</article>.  */
        siOnTimeChange	= 542179345,		/*!< OnTimeChange event identifier. Fired when the time line changes. See the list of available <article idref="ctxt_siOnTimeChange">Context Attributes</article> for this event. */
        siOnWindowEvent	= 542179346,		/*!< OnWindowEvent event identifier. Fired when a custom display changes position or get refreshed. This event is supported only by the <article idref="cus_displayhost" file="../custom/cus_displayhost.fm">Custom Display Host</article>. */
        siOnBeginFileExport	= 542179347,		/*!< OnBeginFileExport event identifier. This event occurs at the beginning of a file export. See the list of available <article idref="ctxt_siOnBeginFileExport">Context Attributes</article> for this event. */
        siOnEndFileExport	= 542179348,		/*!< OnEndFileExport event identifier. This event occurs at the end of a file export. See the list of available <article idref="ctxt_siOnEndFileExport">Context Attributes</article> for this event. */
        siOnBeginFileImport	= 542179349,		/*!< OnBeginFileImport event identifier. This event occurs at the beginning of a file import. See the list of available <article idref="ctxt_siOnBeginFileImport">Context Attributes</article> for this event. */
        siOnEndFileImport	= 542179350,		/*!< OnEndFileImport event identifier. This event occurs at the end of a file import. See the list of available <article idref="ctxt_siOnEndFileImport">Context Attributes</article> for this event. */
        siOnStartup	= 542179351,		/*!< OnStartup event identifier. Fired when Softimage starts. */
        siOnSourcePathChange	= 542179352,		/*!< OnSourcePathChange event identifier. Fired when a Softimage source path is changed. See the list of available <article idref="ctxt_siOnSourcePathChange">Context Attributes</article> for this event. */
        siOnObjectAdded	= 542179353,		/*!< OnObjectAdded event identifier. Fired when an object has been added to the scene. See the list of available <article idref="ctxt_siOnObjectAdded">Context Attributes</article> for this event.Note: Prior to v6.5 this was only available for the <article idref="cus_displayhost" file="../custom/cus_displayhost.fm">Custom Display Host</article>. */
        siOnObjectRemoved	= 542179354,		/*!< OnObjectRemoved event identifier. Fired when an object has been removed from the scene. See the list of available <article idref="ctxt_siOnObjectRemoved">Context Attributes</article> for this event.Note: Prior to v6.5 this was only available for the <article idref="cus_displayhost" file="../custom/cus_displayhost.fm">Custom Display Host</article>. */
        siOnTimer	= 542179355,		/*!< OnTimer event identifier. Fired when a timer elapses. */
        siOnBeginSceneSave2	= 542179356,		/*!< OnBeginSceneSave2 event identifier. Same as siOnBeginSceneSave except this version allows you to pass in the full path name of the scene via <article idref="ctxt_siOnBeginSceneSave2">Context Attributes</article>. */
        siOnEndSceneSave2	= 542179357,		/*!< OnEndSceneSave2 event identifier. Same as siOnEndSceneSave except this version allows you to pass in the full path name of the scene via <article idref="ctxt_siOnEndSceneSave2">Context Attributes</article>. */
        siOnCloseScene	= 542179358,		/*!< OnCloseScene event identifier. Fired when a scene is closing. This event occurs before a new scene or a new project is created, or before a scene is loaded. */
        siOnActivate	= 542179359,		/*!< OnActivate event identifier. Fired when the Softimage application is activated or deactivated. The Softimage application is activated when a window belonging to a different application than Softimage is about to be deactivated. This results typically from a user action such as changing the focus or closing the window. See the list of available <article idref="ctxt_siOnActivate">Context Attributes</article> for this event. */
        siOnMaximize	= 542179360,		/*!< OnMaximize event identifier. Fired when the Softimage application window is maximized. The Maximize action activates the application which therefore triggers an siOnActivate event with a state set to true. */
        siOnMinimize	= 542179361,		/*!< OnMinimize event identifier. Fired when the Softimage application window is minimized. The Minimize action de-activates the application which therefore triggers an siOnActivate event with a state set to false. */
        siOnChangeProject	= 542179362,		/*!< OnChangeProject event identifier. Fired when the project changes in Softimage. This can occur when one of the following actions takes place:  - a new project is created  - a project is activated  - a new scene is loaded  - during a crash recovery operation Note: The event is not fired when a project gets closed due to Softimage terminating. See the list of available <article idref="ctxt_siOnChangeProject">Context Attributes</article> for this event. */
        siOnRefModelModSave	= 542179363,		/*!< OnRefModelModSave event identifier. Fired just before saving the modification of the current reference model resolution. */
        siOnBeginRefModelModLoad	= 542179364,		/*!< OnRefModelPostLoad event identifier. Fired just before loading the modification of the current reference model resolution. */
        siOnEndRefModelModLoad	= 542179365,		/*!< OnEndRefModelModLoad event identifier. Fired just after loading the modification of the current reference model resolution.  */
        siOnCustomFileImport	= 542179366,		/*!< OnCustomFileImport event identifier. Fired when importing an asset with a custom file-extension. See the list of available <article idref="ctxt_siOnCustomFileImport">Context Attributes</article> for this event.  */
        siOnCustomFileExport	= 542179367,		/*!< OnCustomFileExport event identifier. Fired when exporting an asset with a custom file-extension. See the list of available <article idref="ctxt_siOnCustomFileExport">Context Attributes</article> for this event.  */
        siOnDragAndDrop	= 542179368,		/*!< OnDragAndDrop event identifier. Fired when a source is dragged over or dropped in a view and no default Softimage handlers dealt with it. See the list of available <article idref="ctxt_siOnDragAndDrop">Context Attributes</article> for this event. It is recommended to use the siOnDragAndDrop2 event instead of the siOnDragAndDrop event since it offers more flexibility to plug-ins. */
        siOnBeginPassChange	= 542179369,		/*!< OnBeginPassChange event identifier. Fired before a renderpass is changed. See the list of available <article idref="ctxt_siOnBeginPassChange">Context Attributes</article> for this event. */
        siOnEndPassChange	= 542179370,		/*!< OnEndPassChange event identifier. Fired after a renderpass has been changed. See the list of available <article idref="ctxt_siOnEndPassChange">Context Attributes</article> for this event. */
        siOnStartAnimation	= 542179371,		/*!< OnStartAnimation event identifier. Fired when animation playback has been started with the timeline play button or animation scrubbing has been started. The event can also be fired when one of these commands has been executed: <command idref="PlayBackwards"/>, <command idref="PlayBackwardsFromEnd"/>, <command idref="PlayForwards"/>, <command idref="PlayForwardsFromStart"/>, <command idref="PlayFrame"/>, <command idref="PlayRealTime"/>, or <command idref="PlayRealTimeFromStart"/>. Note: This event has no specific attributes. */
        siOnStopAnimation	= 542179372,		/*!< siOnStopAnimation event identifier. Fired after animation playback has been stopped with the timeline play button or animation scrubbing has been stopped. The event can also be fired after one of these commands has been executed: <command idref="PlaybackStop"/>, <command idref="PlayBackwards"/>, <command idref="PlayBackwardsFromEnd"/>, <command idref="PlayForwards"/>, <command idref="PlayForwardsFromStart"/>, <command idref="PlayFrame"/>, <command idref="PlayRealTime"/>, or <command idref="PlayRealTimeFromStart"/>. Note: This event has no specific attributes. */
        siOnRefModelLoad	= 542179373,		/*!< OnRefModelLoad event identifier. Fired before the current resolution gets loaded for a referenced model */
        siOnConnectShader	= 542179374,		/*!< OnConnectShader event identifier. Fired after a shader port is connected. See the list of available <article idref="ctxt_siOnConnectShader">Context Attributes</article> for this event. */
        siOnDisconnectShader	= 542179375,		/*!< OnDisconnectShader event identifier. Fired after a shader port is disconnected. See the list of available <article idref="ctxt_siOnDisconnectShader">Context Attributes</article> for this event. */
        siOnAddShaderPort	= 542179376,		/*!< OnAddShaderPort event identifier. Not implemented. */
        siOnRemoveShaderPort	= 542179377,		/*!< OnRemoveShaderPort event identifier. Not implemented.  */
        siOnCreateShader	= 542179378,		/*!< OnCreateShader event identifier. Fired after a shader is created. See the list of available <article idref="ctxt_siOnCreateShader">Context Attributes</article> for this event. */
        siOnCreateShaderDef	= 542179379,		/*!< OnCreateShaderDef event identifier. Fired after a shader definition is created. See the list of available <article idref="ctxt_siOnCreateShaderDef">Context Attributes</article> for this event.  */
        siOnCustomShaderExport	= 542179380,		/*!< siOnCustomShaderExport event identifier. Fired when exporting a shader or shader tree in the RenderTree with a custom file-extension. See the list of available <article idref="ctxt_siOnCustomShaderExport">Context Attributes</article> for this event.  */
        siOnRenderAbort	= 542179381,		/*!< OnRenderAbort event identifier. Fired when a render sequence has been aborted by the user. The event can also be sent when a render region job is re-executed as a result of a scene change. */
        siOnBeginScrubbing	= 542179382,		/*!< OnBeginScrubbing event identifier. Fired before setting a parameter value(s) with a PPG slider control. See the list of available <article idref="ctxt_siOnBeginScrubbing">Context Attributes</article> for this event. */
        siOnEndScrubbing	= 542179383,		/*!< OnEndScrubbing event identifier. Fired after a parameter value(s) have been changed with a slider control. See the list of available <article idref="ctxt_siOnEndScrubbing">Context Attributes</article> for this event. */
        siOnPreParseShaderDef	= 542179384,		/*!< OnPreParseShaderDef event identifier. Fired after a shader definition is pre parsed. See the list of available <article idref="ctxt_siOnPreParseShaderDef">Context Attributes</article> for this event.  */
        siOnPreDefineShaderDef	= 542179385,		/*!< OnPreDefineShaderDef event identifier. Fired after a shader definition is pre defined. See the list of available <article idref="ctxt_siOnPreDefineShaderDef">Context Attributes</article> for this event.  */
        siOnTimeTransportChange	= 542180328,		/*!< OnTimeTransportChange event identifier. Fired when the time transport changes. See the list of available <article idref="ctxt_siOnTimeTransportChange">Context Attributes</article> for this event. */
        siOnBeginRenderPass	= 542180329,		/*!< OnBeginRenderPass event identifier. Fired before a pass gets rendered. This callback can be used to modify the scene before the rendering starts. See the list of available <article idref="ctxt_siOnBeginRenderPass">Context Attributes</article> for this event. */
        siOnEndRenderPass	= 542180330,		/*!< OnEndRenderPass event identifier. Fired after a pass has been rendered. See the list of available <article idref="ctxt_siOnEndRenderPass">Context Attributes</article> for this event. */
        siOnBeginSceneSaveBackup	= 542180331,		/*!< OnBeginSceneSaveBackup event identifier. Fired when a scene is backup using File > Save Backup. See the list of available <article idref="ctxt_siOnBeginSceneSaveBackup">Context Attributes</article> for this event. */
        siOnEndSceneSaveBackup	= 542180332,		/*!< OnEndSceneSaveBackup event identifier. Fired when a scene is backup using File > Save Backup. See the list of available <article idref="ctxt_siOnEndSceneSaveBackup">Context Attributes</article> for this event. */
        siOnEndCommand	= 542181329,		/*!< OnEndCommand event identifier. Fired when a <object idref="Command"/> terminates. This event is fired for top-level commands only, sub-commands executed while a top-level command is running will not trigger this event. See the list of available <article idref="ctxt_siOnEndCommand">Context Attributes</article> for this event. */
        siOnNestedObjectsChange	= 542181330,		/*!< OnNestedObjectsChange event identifier.  Fired for objects that have gained or lost an object nested under it since the last UI update. This event is mainly intended to help keep a custom UI up to date. Common examples of when this event fires include when an object gains or loses a child, property, or operator; when a mixer track gains or loses a clip; when an item is added to or removed from a group or layer. If, between two UI updates, an object has a change in the objects nested underneath and is then deleted, this event will not fire for that object (see "siOnObjectRemoved" event). See the list of available <article idref="ctxt_siOnNestedObjectsChange">Context Attributes</article> for this event. */
        siOnBeginCommand	= 542181331,		/*!< OnBeginCommand event identifier. Fired before a <object idref="Command"/> is executed. This event is fired for top-level commands only, sub-commands executed while a top-level command is running will not trigger this event. See the list of available <article idref="ctxt_siOnBeginCommand">Context Attributes</article> for this event. */
        siOnDragAndDrop2	= 542181332		/*!< OnDragAndDrop event identifier. Fired when a source enters, leaves, is dragged over or is dropped into a supported view (Scene Explorer, Viewport.) See the list of available <article idref="ctxt_siOnDragAndDrop2">Context Attributes</article> for this event.  */
    } 	siEventID;

/*! Specifies the type of operation performed to update the selection. */
typedef   
enum siSelectionChangeType
    {
        siAddedToSelection	= 0,		/*!< One or more objects added to selection. */
        siRemovedFromSelection	= 1		/*!< One or more objects removed from selection. */
    } 	siSelectionChangeType;

/*! Specifies the render field setting. */
typedef   
enum siRenderFieldType
    {
        siRenderFieldNone	= 0,		/*!< No field setting. */
        siRenderFieldOdd	= 1,		/*!< Odd field setting. */
        siRenderFieldEven	= 2		/*!< Even field setting. */
    } 	siRenderFieldType;

typedef   
enum siRenderingType

    {
        siRenderSequence	= 0,		/*!< Render sequence. */
        siRenderFramePreview	= 1,		/*!< Frame preview or render region rendering. */
        siRenderEchoToMi	= 2,
        siRenderExportArchive	= 2
    } 	siRenderType;

/*! Specifies the type of rendering error. */
typedef   
enum siRenderingErrorType
    {
        siRenderNoError	= 0,		/*!< No rendering error. */
        siRenderAbort	= 1,
        siRenderFailure	= 2
    } 	siRenderingErrorType;

/*! Specifies the subdivision rule used for an approximated geometry selection. */
typedef   
enum siSubdivisionRuleType
    {
        siCatmullClark	= 0,		/*!< Catmull-Clark subdivision rule. */
        siXSIDooSabin	= 2,		/*!< XSI-Doo-Sabin subdivision rule. */
        siLinearSubdivision	= 3		/*!< Linear subdivision rule. */
    } 	siSubdivisionRuleType;

/*! Direction type for navigating geometry components. */
typedef   
enum siNavigateComponentType
    {
        siNextComponent	= 0,		/*!< next component */
        siPreviousComponent	= 1,		/*!< previous component */
        siFirstComponent	= 2,		/*!< first component */
        siLastComponent	= 3		/*!< last component */
    } 	siNavigateComponentType;

/*! Enumeration of particle render types */
typedef   
enum siParticleRenderType
    {
        siBillboardType	= 0,		/*!< Billboard render type */
        siSphereType	= 1,		/*!< Sphere render type */
        siBlobType	= 2		/*!< Blob render type */
    } 	siParticleRenderType;

/*! Enumeration of the different attributes that are available on the FCurveEditor object. */
typedef   
enum siFCurveEditorAttribute
    {
        siRegionStartFrame	= 0,		/*!< If a region has been selected this returns the start frame.  If no region has been selected then 0.0 is returned. */
        siRegionEndFrame	= 1,		/*!< End frame of the region selection, or 0.0 if no region has been selected. */
        siRegionMin	= 2,		/*!< Minimum value of the keys in the region, or 0.0 if no region has been selected. */
        siRegionMax	= 3		/*!< Maximum value of the keys in the region, or 0.0 if no region has been selected. */
    } 	siFCurveEditorAttribute;

/*! Determines the severity types of a message implemented with the C++ API.  They can be combined. */
typedef   
enum siSeverityType
    {
        siFatalMsg	= 1,		/*!< Fatal error has occurred; possibly leading to an unstable system state. Displayed as Message Box and in History window. */
        siErrorMsg	= 2,		/*!< An error has occurred; possibly leading data loss. Displayed in History window and Status Bar. */
        siWarningMsg	= 4,		/*!< An error has occurred but is recoverable. Displayed in History window and Status Bar. */
        siInfoMsg	= 8,		/*!< Log an information message. Displayed in History window and Status Bar. */
        siVerboseMsg	= 16,		/*!< Log a diagnostic information message. Displayed in History window. */
        siCommentMsg	= 32		/*!< Log an information message without a prefix to describe its type */
    } 	siSeverityType;

/*! Information which is passed to the custom compiled operators through its Init and Term functions. */
typedef   
enum siCustomCompiledOpFlags
    {
        siDLLLoadingUnloading	= 1		/*!< Flag passed to the operator in the Init or Term to notify that the DLL is Offloading/Reloading . */
    } 	siCustomCompiledOpFlags;

/*! A device driver contains a set of channels that can be configured. This enumeration is the type of action to perform for a channel.*/
typedef   
enum siChannelAction
    {
        siChannelActionNone	= 0,		/*!< Nothing to do with the channel. */
        siChannelActionDrive	= 1,		/*!< Drive a parameter of a scene object. If you choose this type of action, you can set the <object idref="Channel.Target"/> property to any valid expression (for example, "current.kine.local.posx").  */
        siChannelActionCommand	= 2,		/*!< Fire a command. If you choose this type of action, you can set the <object idref="Channel.Target"/> property to the name of the command to launch through this channel. This can be either a native Softimage command or a custom command.  */
        siChannelActionSpecial	= 3		/*!< Other action (Special). If you choose this type of action, you can set the <object idref="Channel.Target"/> property to any of these special keywords:TIMELINE (drives the timeline)TIME_START (goes to the first frame)TIME_END (goes to the last frame)TIME_STEP_FORWARD (goes to the next frame)TIME_STEP_BACK (goes to the previous frame)TIME_STOP (stops the playback)TIME_PLAY_NORMAL (real time playback from current frame)TIME_PLAY_FRAME (real time playback from first frame)TIME_PLAY_SLIDE (plays all frames from current frame on)TIME_SPECIFY,&lt;frame&gt;ACTIVATE,&lt;driver_ID&gt; (enables a device driver)DEACTIVATE,&lt;driver_ID&gt; (disables a device driver) */
    } 	siChannelAction;

/*! Specifies how to select objects in a hierarchy. */
typedef   
enum siSelectMode
    {
        siSelectDefault	= 0,		/*!< Select the object as is. */
        siSelectNode	= 1,		/*!< Select the object in node. */
        siSelectBranch	= 2,		/*!< Select the object and its children. */
        siSelectTree	= 3,		/*!< Select the entire hierarchy of objects. */
        siSelectModel	= 4		/*!< Select the model and the hierarchy of objects. If that model is the scene root then this is the same as siSelectTree. */
    } 	siSelectMode;

/*! Specifies the filter to use in a transient explorer. */
typedef   
enum siTransientExplorerFilter
    {
        siSEFilterAllNodes	= 0,		/*!< Display all nodes. */
        siSEFilterAllNodesNoParams	= 1,		/*!< Display all nodes without leaf nodes. */
        siSEFilterGeometryOperators	= 2,		/*!< Display the operators and primitives. */
        siSEFilterObjectsOnly	= 3,		/*!< Display the objects. */
        siSEFilterAllProperties	= 4,		/*!< Display all the properties. */
        siSEFilterPropertiesAndPrimitives	= 5,		/*!< Display all the properties and primitives. */
        siSEFilterMaterialsAndShaders	= 6,		/*!< Display all the materials and shaders. */
        siSEFilterModelsOnly	= 7,		/*!< Display only the models. */
        siSEFilterGroupsOnly	= 8,		/*!< Display only the groups. */
        siSEFilterImageClips	= 9		/*!< Display only the image clips. */
    } 	siTransientExplorerFilter;

/*! The class ID of Softimage objects. This enumerator is used by the C++ API to manage references between the object model and C++. For example, the CRef::IsA function uses the class ID to determine whether or not the class type is compatible with the underlying reference object. */
typedef   
enum siClassID
    {
        siObjectID	= 0,		/*!< Generic object id. */
        siUnknownClassID	= 0,		/*!< Unknown object id. */
        siSIObjectID	= 1,		/*!< SIObject object id. */
        siOGLMaterialID	= 2,		/*!< OGLMaterial object id. */
        siOGLTextureID	= 3,		/*!< OGLTexture object id. */
        siOGLLightID	= 4,		/*!< OGLLight object id. */
        siApplicationID	= 5,		/*!< Application object id. */
        siArgumentID	= 6,		/*!< Argument object id. */
        siCommandID	= 7,		/*!< Command object id. */
        siClipID	= 8,		/*!< Clip object id. */
        siShapeClipID	= 9,		/*!< ShapeClip object id. */
        siSubComponentID	= 10,		/*!< SubComponent object id. */
        siFacetID	= 11,		/*!< Facet object id. */
        siNurbsSurfaceID	= 12,		/*!< NurbsSurfaceFace object id. */
        siPointID	= 13,		/*!< Point object id. */
        siControlPointID	= 14,		/*!< ControlPoint object id. */
        siNurbsCurveControlPointID	= 15,		/*!< NurbsCurveControlPoint object id. */
        siNurbsCurveListControlPointID	= 16,		/*!< NurbsCurveListControlPoint object id. */
        siNurbsSurfaceControlPointID	= 17,		/*!< NurbsSurfaceControlPoint object id. */
        siNurbsCurveID	= 18,		/*!< NurbsCurve object id. */
        siSampleID	= 19,		/*!< Sample object id. */
        siNurbsSampleID	= 20,		/*!< NurbsSample object id. */
        siPolygonNodeID	= 21,		/*!< PolygonNode object id. */
        siGeometryID	= 22,		/*!< Geometry object id. */
        siNurbsSurfaceMeshID	= 23,		/*!< NurbsSurfaceMesh object id. */
        siNurbsCurveListID	= 24,		/*!< NurbsCurveList object id. */
        siPolygonMeshID	= 25,		/*!< PolygonMesh object id. */
        siSegmentID	= 26,		/*!< Segment object id. */
        siConnectionPointID	= 27,		/*!< ConnectionPoint object id. */
        siConstructionHistoryID	= 28,		/*!< ConstructionHistory object id. */
        siDictionaryID	= 29,		/*!< Dictionary object id. */
        siEventInfoID	= 30,		/*!< EventInfo object id. */
        siFCurveID	= 31,		/*!< FCurve object id. */
        siNestedFCurveID	= 32,		/*!< NestedFCurve object id. */
        siFCurveKeyID	= 33,		/*!< FCurveKey object id. */
        siFileBrowserID	= 34,		/*!< FileBrowser object id. */
        siImageID	= 35,		/*!< Image object id. */
        siMappedItemID	= 36,		/*!< MappedItem object id. */
        siPortID	= 37,		/*!< Port object id. */
        siInputPortID	= 38,		/*!< InputPort object id. */
        siSelectionID	= 39,		/*!< Selection object id. */
        siStaticSourceID	= 40,		/*!< StaticSource object id. */
        siTriangleID	= 41,		/*!< Triangle object id. */
        siTriangleVertexID	= 42,		/*!< TriangleVertex object id. */
        siUpdateContextID	= 43,		/*!< UpdateContext object id. */
        siParameterID	= 44,		/*!< Parameter object id. */
        siCompoundParameterID	= 45,		/*!< CompoundParameter object id. */
        siProjectID	= 46,		/*!< Project object id. */
        siProjectItemID	= 47,		/*!< ProjectItem object id. */
        siActionSourceID	= 48,		/*!< ActionSource object id. */
        siExpressionID	= 49,		/*!< Expression object id. */
        siImageClipID	= 50,		/*!< ImageClip object id. */
        siSceneID	= 51,		/*!< Scene object id. */
        siShaderID	= 52,		/*!< Shader object id. */
        siOperatorID	= 53,		/*!< Operator object id. */
        siEnvelopeID	= 54,		/*!< Envelope object id. */
        siPrimitiveID	= 55,		/*!< Primitive object id. */
        siParticleCloudPrimitiveID	= 56,		/*!< ParticleCloudPrimitive object id. */
        siPropertyID	= 57,		/*!< Property object id. */
        siClusterPropertyID	= 58,		/*!< ClusterProperty object id. */
        siConstraintID	= 59,		/*!< Constraint object id. */
        siConstraintWithUpVectorID	= 60,		/*!< ConstraintWithUpVector object id. */
        siCustomPropertyID	= 61,		/*!< CustomProperty object id. */
        siJointID	= 62,		/*!< Joint object id. */
        siKinematicsID	= 63,		/*!< Kinematics object id. */
        siMaterialID	= 64,		/*!< Material object id. */
        siStaticKinematicStateID	= 65,		/*!< StaticKinematicState object id. */
        siSceneItemID	= 66,		/*!< SceneItem object id. */
        siClusterID	= 67,		/*!< Cluster object id. */
        siGroupID	= 68,		/*!< Group object id. */
        siLayerID	= 69,		/*!< Layer object id. */
        siPassID	= 70,		/*!< Pass object id. */
        siUserGroupID	= 71,		/*!< UserGroup object id. */
        siX3DObjectID	= 72,		/*!< X3DObject object id. */
        siParticleCloudID	= 73,		/*!< ParticleCloud object id. */
        siModelID	= 74,		/*!< Model object id. */
        siChainElementID	= 75,		/*!< ChainElement object id. */
        siChainRootID	= 76,		/*!< ChainRoot object id. */
        siChainBoneID	= 77,		/*!< ChainBone object id. */
        siChainEffectorID	= 78,		/*!< ChainEffector object id. */
        siDirectedID	= 79,		/*!< Directed object id. */
        siCameraID	= 80,		/*!< Camera object id. */
        siLightID	= 81,		/*!< Light object id. */
        siNullID	= 82,		/*!< Null object id. */
        siRigID	= 83,		/*!< Rig object id. */
        siCameraRigID	= 84,		/*!< CameraRig object id. */
        siLightRigID	= 85,		/*!< LightRigobject id. */
        siKinematicStateID	= 86,		/*!< KinematicState object id. */
        siTrackID	= 87,		/*!< Track object id. */
        siUserDataMapID	= 88,		/*!< UserDataMap object id. */
        siFxTreeID	= 89,		/*!< FxTree object id. */
        siFxOperatorID	= 90,		/*!< FxOperator object id. */
        siTriangleCollectionID	= 91,		/*!< TriangleCollection object id. */
        siTriangleVertexCollectionID	= 92,		/*!< TriangleVertexCollection object id. */
        siSampleCollectionID	= 93,		/*!< SampleCollection object id. */
        siPolygonNodeCollectionID	= 94,		/*!< PolygonNodeCollection object id. */
        siPointCollectionID	= 95,		/*!< PointCollection object id. */
        siFacetCollectionID	= 97,		/*!< FacetCollection object id. */
        siVertexID	= 98,		/*!< Vertex object id. */
        siVertexCollectionID	= 99,		/*!< VertexCollection object id. */
        siEdgeID	= 100,		/*!< Edge object id. */
        siEdgeCollectionID	= 101,		/*!< EdgeCollection object id. */
        siPolygonFaceID	= 102,		/*!< PolygonFace object id. */
        siPolygonFaceCollectionID	= 103,		/*!< PolygonFaceCollection object id. */
        siDataSourceID	= 104,		/*!< DataSource object id. */
        siAnimationSourceID	= 105,		/*!< AnimationSource object id. */
        siOutputPortID	= 106,		/*!< OuptputPort object id. */
        siProxyParameterID	= 107,		/*!< Proxy Parameter object id. */
        siDeviceCollectionID	= 108,		/*!< Device collection object id. */
        siDeviceID	= 109,		/*!< Device object id. */
        siChannelID	= 110,		/*!< Channel object id. */
        siKnotCollectionID	= 111,		/*!< KnotCollection object id. */
        siControlPointCollectionID	= 112,		/*!< ControlPointCollection object id. */
        siNurbsCurveCollectionID	= 113,		/*!< NurbsCurveCollection object id. */
        siNurbsSurfaceCollectionID	= 114,		/*!< NurbsSurfaceCollection object id. */
        siNurbsSampleCollectionID	= 115,		/*!< NurbsSampleCollection object id. */
        siTextureID	= 116,		/*!< Texture object id. */
        siUserDataBlobID	= 117,		/*!< UserDataBlob object id. */
        siParticleID	= 118,		/*!< Particle object id. */
        siAddonID	= 119,		/*!< Addon object id. */
        siPPGLayoutID	= 120,		/*!< PPGLayout object id. */
        siPPGItemID	= 121,		/*!< PPGItem object id. */
        siPreferencesID	= 122,		/*!< Preferences object id. */
        siParticleTypeID	= 123,		/*!< ParticleType object id. */
        siParticleAttributeID	= 124,		/*!< ParticleAttribute object id. */
        siGridDataID	= 125,		/*!< GridData object id. */
        siTextureLayerID	= 126,		/*!< TextureLayer object id. */
        siTextureLayerPortID	= 127,		/*!< TextureLayerPort object id. */
        siCustomOperatorID	= 128,		/*!< CustomOperator object id. */
        siPortGroupID	= 129,		/*!< PortGroup object id. */
        siDesktopID	= 130,		/*!< Desktop object id. */
        siLayoutID	= 131,		/*!< Layout object id. */
        siUIObjectID	= 132,		/*!< UIObject object id. */
        siUIPersistableID	= 133,		/*!< UIPersistable object id. */
        siViewID	= 134,		/*!< View object id. */
        siArrayParameterID	= 135,		/*!< ArrayParameter object id. */
        siViewContextID	= 137,		/*!< X3DObject object id. */
        siContextID	= 138,		/*!< Context object id. */
        siPPGEventContextID	= 139,		/*!< PPGEventContext id. */
        siClipEffectID	= 140,		/*!< ClipEffect object id. */
        siClipEffectItemID	= 141,		/*!< ClipEffectItem object id. */
        siShapeKeyID	= 142,		/*!< ShapeKey object id. */
        siSourceID	= 143,		/*!< Source object id. */
        siTimeControlID	= 144,		/*!< TimeControl object id. */
        siTransitionID	= 145,		/*!< Transition object id. */
        siAnimationSourceItemID	= 146,		/*!< AnimationSourceItem object id. */
        siClipContainerID	= 147,		/*!< ClipContainer object id. */
        siArgumentHandlerID	= 148,		/*!< Argument Handler object id. */
        siMenuID	= 149,		/*!< Menu object id. */
        siMenuItemID	= 150,		/*!< MenuItem object id. */
        siPluginID	= 151,		/*!< Plugin object id. */
        siPluginItemID	= 152,		/*!< PluginItem object id. */
        siPluginRegistrarID	= 153,		/*!< PluginRegistrar object id. */
        siFilterID	= 154,		/*!< Filter object id. */
        siUIToolkitID	= 155,		/*!< UIToolkit object id. */
        siProgressBarID	= 156,		/*!< ProgressBar object id. */
        siParamDefID	= 157,		/*!< ParamDef object id. */
        siFactoryID	= 158,		/*!< Factory object id. */
        siCommandCollectionID	= 159,		/*!< Command object id. */
        siArgumentCollectionID	= 160,		/*!< Argument Collection id. */
        siGraphicSequencerContextID	= 161,		/*!< Graphic Sequencer Core id. */
        siClipRelationID	= 162,		/*!< ClipRelation object id. */
        siMixerID	= 163,		/*!< Mixer object id. */
        siLibraryID	= 164,		/*!< Library id. */
        siSimulationEnvironmentID	= 165,		/*!< SimulationEnvironment object id. */
        siGridWidgetID	= 166,		/*!< GridWidget object id. */
        siGeometryAccessorID	= 167,		/*!< Geometry accessor object id. */
        siEnvelopeWeightID	= 168,		/*!< EnvelopeWeight property object id. */
        siMeshBuilderID	= 169,		/*!< MeshBuilder object id. */
        siSegmentCollectionID	= 170,
        siFileReferenceID	= 171,		/*!< X3DObject object id. */
        siClusterPropertyBuilderID	= 172,		/*!< ClusterPropertyBuilder object id. */
        siMaterialLibraryID	= 173,		/*!< MaterialLibrary id. */
        siHairPrimitiveID	= 174,		/*!< HairPrimitive object id. */
        siRenderHairAccessorID	= 175,		/*!< RenderHairAccessor object id. */
        siPointLocatorDataID	= 176,		/*!< PointLocatorData object id. */
        siCollectionItemID	= 177,		/*!< CollectionItem object id. */
        siOperatorContextID	= 178,		/*!< Operator context object id. */
        siPointCloudID	= 179,		/*!< PointCloud object id. */
        siRigidBodyAccessorID	= 180,		/*!< RigidBodyAccessor object id. */
        siRigidConstraintAccessorID	= 181,		/*!< RigidConstraintAccessor object id. */
        siDeltaID	= 182,		/*!< Delta object id. */
        siActionDeltaID	= 183,		/*!< ActionDelta object id. */
        siActionDeltaItemID	= 184,		/*!< ActionDeltaItem object id. */
        siTimerEventID	= 185,		/*!< TimerEvent object id. */
        siPassContainerID	= 186,		/*!< PassContainer object id. */
        siRenderChannelID	= 187,		/*!< RenderChannel object id. */
        siSceneRenderPropertyID	= 188,		/*!< SceneRenderProperty object id. */
        siFramebufferID	= 189,		/*!< Framebuffer object id. */
        siRendererContextID	= 190,		/*!< RendererContext object id. */
        siRendererID	= 191,		/*!< Renderer object id. */
        siTimeTransportID	= 192,		/*!< TimeTransport object id. */
        siTimeTransportContextID	= 193,		/*!< TimeTransportContext object id. */
        siICENodeID	= 194,		/*!< ICENode object id. */
        siICECompoundNodeID	= 195,		/*!< ICECompoundNode object id. */
        siICENodePortID	= 196,		/*!< ICENodePort object id. */
        siICETreeID	= 197,		/*!< ICETree object id. */
        siICENodeContainerID	= 198,		/*!< ICENodeContainer object id. */
        siICENodeInputPortID	= 199,		/*!< ICENodeInputPort object id. */
        siICENodeOutputPortID	= 200,		/*!< ICENodeOutputPort object id. */
        siICEDataProviderNodeID	= 201,		/*!< ICEDataProviderNode object id. */
        siICEDataModifierNodeID	= 202,		/*!< ICEDataModifierNode object id. */
        siICENodeDefID	= 203,		/*!< ICENodeDef object id. */
        siICENodeContextID	= 204,		/*!< ICENodeContext object id. */
        siICEAttributeID	= 205,		/*!< ICEAttribute object id. */
        siPartitionID	= 206,		/*!< Partition object id. */
        siOverrideID	= 207,		/*!< Override object id. */
        siHardwareShaderContextID	= 208,		/*!< Hardware Shader Context Object id. */
        siValueMapID	= 209,		/*!< ValueMap object id. */
        siShaderParamDefID	= 210,		/*!< ShaderParamDef object id. */
        siShaderParamDefOptionsID	= 211,		/*!< ShaderParamDefOptions object id. */
        siShaderballOptionsID	= 212,		/*!< ShaderballOptions object id. */
        siShaderParamDefContainerID	= 213,		/*!< ShaderParamDefContainer object id. */
        siMetaShaderRendererDefID	= 214,		/*!< MetaShaderRendererDef object id. */
        siShaderDefID	= 215,		/*!< ShaderDef object id. */
        siShaderStructParamDefID	= 216,		/*!< ShaderStructParamDef object id. */
        siShaderArrayParamDefID	= 217,		/*!< ShaderArrayParamDef object id. */
        siShaderParameterID	= 218,		/*!< ShaderParameter object id. */
        siShaderArrayItemParameterID	= 219,		/*!< ShaderArrayItemParameter object id. */
        siShaderArrayParameterID	= 220,		/*!< ShaderArrayParameter object id. */
        siShaderCompoundParameterID	= 221,		/*!< ShaderCompoundParameter object id. */
        siRenderTreeNodeID	= 222,		/*!< RenderTreeNode object id. */
        siShaderBaseID	= 223,		/*!< ShaderBase object id. */
        siShaderContainerID	= 224,		/*!< ShaderContainer object id. */
        siShaderCompoundID	= 225,		/*!< ShaderCompound object id. */
        siShaderCommentID	= 226,		/*!< ShaderComment object id. */
        siShaderDefManagerID	= 227,		/*!< ShaderDefManager object id. */
        siHardwareSurfaceID	= 228,		/*!< HardwareSurface object id. */
        siGraphicDriverID	= 229,		/*!< Graphic Driver object id. */
        siHairGeometryID	= 230,		/*!< HairGeometry object id. */
        siPointCloudGeometryID	= 231,		/*!< PointCloudGeometry object id. */
        siSchematicNodeID	= 232,		/*!< SchematicNode object id. */
        siSchematicID	= 233,		/*!< Schematic object id. */
        siSchematicNodeCollectionID	= 234,		/*!< SchematicNodeCollection object id. */
        siUVPropertyID	= 235,		/*!< UVProperty property object id. */
        siToolContextID	= 236,		/*!< ToolContext object id. */
        siPickBufferID	= 237,		/*!< PickBuffer object id. */
        siMemoCameraID	= 238,		/*!< MemoCamera object id. */
        siMemoCameraCollectionID	= 239,		/*!< MemoCameraCollection object id. */
        siAnnotationID	= 250,		/*!< Annotation object id. */
        siCustomPrimitiveID	= 251,		/*!< CustomPrimitive object id. */
        siCustomPrimitiveContextID	= 252		/*!< CustomPrimitiveContext object id. */
    } 	siClassID;

/*! This enumeration type specifies how the BlendInPresets command will apply the new shaders to the parameters selected by the command. */
typedef   
enum siBlendInPresetModes
    {
        siBlendInPreset	= 0,		/*!< Blend the new shaders in with any existing shaders on the ports, or the parameter value if there are no shaders. */
        siReplaceAndBlendInPreset	= 1,		/*!< Remove any existing shaders from the parameters, and blend with the parameter value.  */
        siReplaceNoBlend	= 2		/*!< Remove any existing shaders and connect the new shaders directly to the parameters, without blending. */
    } 	siBlendInPresetModes;

/*! This enumeration type specifies how the texture-layer blending commands will apply the new shaders to the parameters selected by the command.*/
typedef   
enum siBlendInTextureLayersModes
    {
        siBlendInTextureLayers	= 0,		/*!< Blend the new shaders in with any existing shaders on the ports, or the parameter value if there are no shaders. */
        siReplaceAndBlendInTextureLayers	= 1,		/*!< Remove any existing shaders and layers from the parameters, and blend with the parameter value.  */
        siReplaceAndNoBlendInTextureLayers	= 2		/*!< Remove any existing shaders and layers and connect the new shaders directly to the parameters, without blending. */
    } 	siBlendInTextureLayersModes;

/*! This enumeration type specifies what kind of shader port connections you are interested in when using the <command idref="RemoveAllShadersFromCnxPoint"/> command.*/
typedef   
enum siShaderCnxPointType
    {
        siShaderCnxPointNone	= 0,		/*!< Reference none of the connections on a parameter. (not normally used) */
        siShaderCnxPointBasePorts	= 1,		/*!< Reference only regular shader connections (not including texture layer port connections). "Regular connections" refers to connections of one shader to another. */
        siShaderCnxPointTextureLayerPorts	= 2,		/*!< Reference texture layer port connections only. */
        siShaderCnxPointAll	= 65535		/*!< Reference all types of shader connections, including both regular and texture layer port connections. */
    } 	siShaderCnxPointType;

/*! This enumeration type specifies the type of item supported by add-ons. Depending on which type you use with the <object idref="Addon.AddItem"/> method, you need to supply only a name, or a path and file name, or you may be able to use either as indicated below.*/
typedef   
enum siAddonItemType
    {
        siLayoutAddonItemType	= 1,
        siToolbarAddonItemType	= 2,
        siKeyMapAddonItemType	= 3,
        siScriptCmdAddonItemType	= 4,
        siPresetAddonItemType	= 5,
        siSpdlAddonItemType	= 6,
        siLibraryAddonItemType	= 7,
        siOtherAddonItemType	= 8,
        siEventAddonItemType	= 9,
        siDeviceAddonItemType	= 10,
        siShelfAddonItemType	= 11,
        siPluginAddonItemType	= 12,
        siHelpAddonItemType	= 13,
        siViewAddonItemType	= 14
    } 	siAddonItemType;

/*! Types of Columns supported by siControlGrid (see <object idref="siPPGControlType"/>and <object idref="GridData.SetColumnType"/>)*/
typedef 
enum siGridWidgetColumnType
    {
        siColumnStandard	= 0,		/*!< A column of text.  Numeric values are shown in decimal format without a slider. */
        siColumnBool	= 1,		/*!< A check mark is shown if the value of the zero is non-zero */
        siColumnCombo	= 2,		/*!< The value of the cell is chosen from a drop down list */
        siColumnInt	= 3,		/*!< The value of the cell is an integer number */
        siColumnFloat	= 4,		/*!< The value of the cell is a floating point number */
        siColumnImageClip	= 5,		/*!< The value of the cell is an image clip, represented by a thumbnail */
        siColumnColor	= 6,		/*!< The value of the cell is a color */
        siColumnVector	= 7,		/*!< The value of the cell is an array of doubles of dimension 2, 3 or 4 depending on the column definition */
        siColumnButton	= 8,		/*!< The value of the cell is a button label, represented by a button */
        siColumnFile	= 9,		/*!< The value of the cell is a file/folder name */
        siColumnShaderBall	= 10,		/*!< The value of the cell is a material, represented by a shader ball */
        siColumnMultiLine	= 11		/*!< A column of text that can span over multiple lines */
    } 	siGridWidgetColumnType;

/*! Selection Mode for the cells of the GridWidget, see siUIGridSelectionMode in <object idref="siPPGItemAttribute"/>.*/
typedef 
enum siGridSelectionMode
    {
        siSelectionCell	= 0,
        siSelectionHeader	= 1,		/*!< Entire columns or rows are selected by clicking in the header cells */
        siSelectionNone	= 2		/*!< Nothing can be selected */
    } 	siGridSelectionMode;

/*! Multi selection behavior control. */
typedef 
enum siGridDataMultiSelectionMode
    {
        siCellSelection	= 0,		/*!< One cell at a time will be selected */
        siColumnSelection	= 1,		/*!< Selection will be restrained to a single column */
        siGlobalSelection	= 2		/*!< No restriction on multi-selection (default)  */
    } 	siGridDataMultiSelectionMode;

/*! Polygon cluster contour stretching method used to generate texture coordinates as part of the <command idref="GenerateUVSetByContourStretching"/> and <command idref="ModifyUVSetByContourStretching"/> commands.*/
typedef   
enum siTxtContourStretchingMethod
    {
        siContourStretchingWalkingOnMesh	= 0,		/*!< Texture coordinates obtained by accumulated distance from contours while walking along mesh edges. */
        siContourStretchingSpatialDistance	= 1,		/*!< Texture coordinates obtained by accumulated spatial distance from contours to the mesh vertices. */
        siContourStretchingReqularQuads	= 2,		/*!< Texture coordinates obtained by accumulated distances along grid lines obtained from contours. */
        siContourStretchingProjectionOnSurface	= 3		/*!< Texture coordinates obtained by projection on a parameteric surface built from contours. */
    } 	siTxtContourStretchingMethod;

/*! The list of scopes supported by the Scene Explorer. */
typedef   
enum siExplorerScope
    {
        siExplorerScopeDefault	= 0,		/*!< Default scope. */
        siExplorerScopeProject	= 1,		/*!< Project (Content Container) scope. */
        siExplorerScopePreferences	= 2,		/*!< Preferences scope. */
        siExplorerScopeScene	= 3,		/*!< Scene scope. */
        siExplorerScopeLayers	= 4,		/*!< Layers scope. */
        siExplorerScopePasses	= 5,		/*!< Passes scope. */
        siExplorerScopeEnvironments	= 6,		/*!< Environments scope. */
        siExplorerScopeParTypes	= 7,		/*!< The Particle Types scope is no longer supported. */
        siExplorerScopeSelection	= 8,		/*!< Selection scope. */
        siExplorerScopeCustom	= 9,		/*!< Custom scope. */
        siExplorerScopeCurrentLayer	= 10,		/*!< Current Layer scope. */
        siExplorerScopeCurrentPass	= 11,		/*!< Current Pass scope. */
        siExplorerScopeCurrentEnvironment	= 12,		/*!< The Current Environment scope is no longer supported. */
        siExplorerScopeCurrentParType	= 13,		/*!< Current Particle Type scope. */
        siExplorerScopeSourcesClips	= 14,		/*!< Sources and Clips scope. */
        siExplorerScopeSourcesClipsAnimation	= 15,		/*!< Sources and Clips (Animation Only) scope. */
        siExplorerScopeSourcesClipsAudio	= 16,		/*!< Sources and Clips (Audio Only) scope. */
        siExplorerScopeSourcesClipsImages	= 17,		/*!< Sources and Clips (Images Only) scope. */
        siExplorerScopeSourcesClipsMaterials	= 18,		/*!< Sources and Clips (Materials Only) scope. */
        siExplorerScopeSourcesClipsModels	= 19,		/*!< The Sources and Clips (Models Only) scope is no longer supported. */
        siExplorerScopeCommands	= 20		/*!< The Commands scope is no longer supported. */
    } 	siExplorerScope;

/*! States for the time change notification <link idref="CTimeChangeNotification" file="cpp_ref"/>for <article idref="cus_displayhost" file="../custom/cus_displayhost.fm">Custom Displays</article>.*/
typedef   
enum siTimeState
    {
        siTimeStateNull	= 0,		/*!< Null state. */
        siTimeStateStop	= 0x1,		/*!< Stop state. */
        siTimeStatePreStop	= 0x2,		/*!< Pre-Stop state. */
        siTimeStatePlay	= 0x4,		/*!< Play state. */
        siTimeStatePrePlay	= 0x8,		/*!< Pre-Play state. */
        siTimeStateRecord	= 0x10,		/*!< Record state. */
        siTimeStatePreRecord	= 0x20,		/*!< Pre-Record state. */
        siTimeStateFast	= 0x40,		/*!< Fast state. */
        siTimeStatePreFast	= 0x80,		/*!< Pre-Fast state. */
        siTimeStatePreRoll	= 0x100,		/*!< Pre-Roll state. */
        siTimeStateStep	= 0x200,		/*!< Step state. */
        siTimeStatePostStep	= 0x400,		/*!< Post-Step state. */
        siTimeStatePause	= 0x800,		/*!< Pause state. */
        siTimeStatePrePause	= 0x1000,		/*!< Pre-Pause state. */
        siTimeStateSeek	= 0x2000,		/*!< Seek state. */
        siTimeNotifyTime	= 0x4000,		/*!< Time notification. */
        siTimeNotifyScrub	= 0x10000,		/*!< Scrub notification. */
        siTimeNotifySeek	= 0x20000,		/*!< Seek notification. */
        siTimeNotifyPortChange	= 0x40000,		/*!< Port Change notification. */
        siTimeNotifyFrameDrop	= 0x80000		/*!< Frame Drop notification. */
    } 	siTimeState;

/*! Types of display callbacks defined for the <article idref="cus_graphicsequencer" file="../custom/cus_graphicsequencer.fm">Graphic Sequencer</article>.*/
typedef   
enum siDisplayCallback
    {
        siUndefined	= 0,		/*!< Undefined. */
        siPreBeginFrame	= 1,		/*!< Fired just before a new frame begins. */
        siBeginFrame	= 2,		/*!< Fired when a new frame begins. */
        siPostBeginFrame	= 3,		/*!< Fired after the frame has begun. */
        siPrePass	= 4,		/*!< Fired before each XGS display pass. */
        siPass	= 5,		/*!< Fired XGS display pass callback. */
        siPostPass	= 6,		/*!< Fired after each XGS display pass. */
        siPreEndFrame	= 7,		/*!< Fired just before the frame ends. */
        siEndFrame	= 8,		/*!< Fired when the frame ends. */
        siPostEndFrame	= 9,		/*!< Fired after the frame has ended. */
        siRenderFrame	= 10		/*!< Fired after MentalRay renders a frame, or after a render region is finished rendering a frame. */
    } 	siDisplayCallback;

/*! Type of object passed to an Open <article idref="cus_displayhost" file="../custom/cus_graphicsequencer.fm">Graphic Sequencer</article> callback.*/
typedef   
enum siXGSClassType
    {
        siXGSPluginManager	= 0		/*!< The Open Graphic Sequencer plug-in manager. */
    } 	siXGSClassType;

/*! Flags for <article idref="cus_displayhost" file="../custom/cus_graphicsequencer.fm">Graphic Sequencer</article> callbacks.*/
typedef   
enum siXGSFlag
    {
        siInactive	= 0,		/*!< Callback is inactive. */
        siActive	= 1		/*!< Callback is active. */
    } 	siXGSFlag;

/*! Pass flags for <article idref="cus_displayhost" file="legacy">Graphic Sequencer</article> callbacks.*/
typedef   
enum siXGSPassFlag
    {
        siInsertBefore	= 0,		/*!< Insert before a callback. */
        siInsertAfter	= 1,		/*!< Insert after a callback. */
        siInsertBeforeAll	= 2,		/*!< Insert before all callbacks. */
        siInsertAfterAll	= 3		/*!< Insert after all callbacks. */
    } 	siXGSPassFlag;

/*! XGS state types defined for the <article idref="cus_graphicsequencer" file="../custom/cus_graphicsequencer.fm">Graphic Sequencer</article>.*/
typedef   
enum siXGSStateType
    {
        siXGSUnknown	= 0,		/*!< Unknown type. */
        siXGSInteger	= 1,		/*!< Integer state type. */
        siXGSFloat	= 2,		/*!< Float state type. */
        siXGSHandle	= 3,		/*!< Handle state type. */
        siXGSVector4	= 4,		/*!< Vector4 state type. */
        siXGSMatrix4	= 5		/*!< Matrix4 state type. */
    } 	siXGSStateType;

/*! Viewport display modes used by the <link idref="CGraphicSequencer" file="cpp_ref"/> classfor the <article idref="cus_graphicsequencer" file="../custom/cus_graphicsequencer.fm">Graphic Sequencer</article>.*/
typedef   
enum siViewMode
    {
        siAll	= 0,		/*!< All modes. */
        siBoundingBoxMode	= 12,		/*!< Bounding box. */
        siWireframe	= 13,		/*!< Wireframe. */
        siDepthCue	= 14,		/*!< Depth Cue. */
        siHiddenLineRemoval	= 15,		/*!< Hidden Line Removal. */
        siConstant	= 16,		/*!< Constant. */
        siShaded	= 17,		/*!< Shaded. */
        siTextured	= 18,		/*!< Textured. */
        siTexturedDecal	= 19,		/*!< Textured Decal. */
        siCustom	= 20,		/*!< Custom view. */
        siRealtimePortMaterial	= 21		/*!< Realtime. */
    } 	siViewMode;

/*! The available types for user defined per particle <object idref="ParticleAttribute"/>. */
typedef   
enum siParticleAttributeType
    {
        siPAVector4	= 0,		/*!< Type of vector containing 4 double-precision floating-point values. */
        siPAVector3	= 1,		/*!< Type of vector containing 3 double-precision floating-point values. */
        siPAFloat	= 2,		/*!< Floating-point type. */
        siPAInt	= 3,		/*!< Integer type. */
        siPAULong	= 4,		/*!< ULONG integer type. */
        siPAUShort	= 5,		/*!< Unsigned short integer type. */
        siPABool	= 6,		/*!< Boolean type. */
        siPAUndefined	= 7		/*!< Error type returned when requesting the type for an undefined attribute. */
    } 	siParticleAttributeType;

/*! This is the enumeration of the different ways an asset in Softimage can be stored. Assets can be either <object idref="ActionSource"/> objects or deltas. <br/> Note: This enum replaces the obsolete siSourceStorageType enum. */
typedef   
enum siAssetStorageType
    {
        siAssetStorageTypeInternal	= 0,		/*!< The asset is saved in the scene file. */
        siAssetStorageTypeExternalDotXSIBin	= 1,		/*!< The asset is saved in a dotXSI file (.xsi) of type binary. */
        siAssetStorageTypeExternalDotXSIText	= 2,		/*!< The source is saved in a dotXSI file (.xsi) of type text. */
        siAssetStorageTypeExternalBin	= 3,		/*!< The asset is saved in a binary native Softimage file (.eani). */
        siAssetStorageTypeExternalXSIA	= 4		/*!< The asset is saved in a delta file (.xsia). */
    } 	siAssetStorageType;

/*! This enum has been replaced by <object idref="siAssetStorageType"/>.  */
typedef   
enum siSourceStorageType
    {
        siSourceStorageTypeInternal	= 0,		/*!< The source is saved in the scene file. */
        siSourceStorageTypeExternalDotXSIBin	= 1,		/*!< The source is saved in a dotXSI file (.eani) of type binary. */
        siSourceStorageTypeExternalDotXSIText	= 2,		/*!< The source is saved in a dotXSI file (.xsi) of type text. */
        siSourceStorageTypeExternalBin	= 3		/*!< The asset is saved in a binary native Softimage file (.eani). */
    } 	siSourceStorageType;

/*! This is an enumeration of how an asset in Softimage can be treated when stored externally. Assets can be either <object idref="ActionSource"/> objects or deltas. <br/> Note: This enum replaces the obsolete siActionStatus enum.*/
typedef   
enum siAssetStatus
    {
        siAssetStatusOffloaded	= 0,		/*!< The asset is offloaded on disk. */
        siAssetStatusPartiallyLoaded	= 1,		/*!< The asset contains portions that are offloaded. See <object idref="ActionSource.PartialOffload"/> */
        siAssetStatusLoaded	= 2		/*!< The asset is loaded. */
    } 	siAssetStatus;

/*! This enum has been replaced by <object idref="siAssetStatus"/>. */
typedef   
enum siActionStatus
    {
        siActionStatusOffloaded	= 0,		/*!< The action source is offloaded on disk. */
        siActionStatusPartiallyLoaded	= 1,		/*!< The action source contains section that are offloaded. See method <object idref="ActionSource.PartialOffload"/> */
        siActionStatusLoaded	= 2		/*!< The action source is loaded. */
    } 	siActionStatus;

/*! Specifies the different type of filters that are used for implementing and categorizing custom <object idref="Filter"/>s. Custom filters of types siFilter3DObject, siFilterSubComponentEdge, siFilterSubComponentPoint, siFilterSubComponentPolygon and siFilterProperty are automatically added to the Main Command Panel filter menus and integrated with the selection tool. */
typedef   
enum siFilterType
    {
        siFilterUndefined	= 0,		/*!< Undefined filter type. */
        siFilterObject	= 1,		/*!< Represents generic filters that are not object-specific. */
        siFilter3DObject	= 2,		/*!< Kind of filter used with 3D objects. */
        siFilterProperty	= 3,		/*!< Kind of filter used with property objects. */
        siFilterSubComponentEdge	= 4,		/*!< Kind of filter used with the edge sub components of a geometry. */
        siFilterSubComponentPoint	= 5,		/*!< Kind of filter used with the point sub components of a geometry. */
        siFilterSubComponentPolygon	= 6,		/*!< Kind of filter used with the polygon sub components of a geometry. */
        siFilterSubComponentKnot	= 7		/*!< Kind of filter used with the knot sub components of a geometry. */
    } 	siFilterType;

/*! Determines the capabilities of a command. */
typedef   
enum siCommandCapabilities
    {
        siSupportsKeyAssignment	= 8,
        siCannotBeUsedInBatch	= 256,
        siUndoable	= 262144,
        siNoLogging	= 8388608,
        siAllowNotifications	= 1073741824
    } 	siCommandCapabilities;

/*! Determines the severity types of a message implemented in a scripting language.  They can be combined. */
typedef   
enum siSeverity
    {
        siFatal	= 1,		/*!< Fatal error has occurred; possibly leading to an unstable system state. Displayed as Message Box and in History window. */
        siError	= 2,		/*!< An error has occurred; possibly leading data loss. Displayed in History window and Status Bar. */
        siWarning	= 4,		/*!< An error has occurred but is recoverable. Displayed in History window and Status Bar. */
        siInfo	= 8,		/*!< Log an information message. Displayed in History window and Status Bar. */
        siVerbose	= 16,		/*!< Log a diagnostic information message. Displayed in History window. */
        siComment	= 32		/*!< Log an information message without adding a prefix to describe its type */
    } 	siSeverity;

/*! Flags values supported by the <object idref="XSIUIToolkit.MsgBox"/> command. These are identical the arguments supported by the VBScript MsgBox() and Win32 ::MessageBox() functions. */
typedef   
enum siMsgBoxFlags
    {
        siMsgOkOnly	= 0,		/*!< Display OK button only. */
        siMsgOkCancel	= 1,		/*!< Display OK and Cancel buttons. */
        siMsgAbortRetryIgnore	= 2,		/*!< Display Abort, Retry, and Ignore buttons. */
        siMsgYesNoCancel	= 3,		/*!< Display Yes, No, and Cancel buttons. */
        siMsgYesNo	= 4,		/*!< Display Yes and No buttons. */
        siMsgRetryCancel	= 5,		/*!< Display Retry and Cancel buttons. */
        siMsgCritical	= 16,		/*!< Display Critical Message icon.  */
        siMsgQuestion	= 32,		/*!< Display Query icon. */
        siMsgExclamation	= 48,		/*!< Display Warning Message icon. */
        siMsgInformation	= 64,		/*!< Display Information Message icon. */
        siMsgDefaultButton1	= 0,		/*!< First button is default. */
        siMsgDefaultButton2	= 256,		/*!< Second button is default. */
        siMsgDefaultButton3	= 512		/*!< Third button is default. */
    } 	siMsgBoxFlags;

/*! Return values from <object idref="XSIUIToolkit.MsgBox"/> that indicates which button was pressed by the user. */
typedef   
enum siMsgButtonPressed
    {
        siMsgOk	= 1,		/*!< OK */
        siMsgCancel	= 2,		/*!< Cancel */
        siMsgAbort	= 3,		/*!< Abort */
        siMsgRetry	= 4,		/*!< Retry */
        siMsgIgnore	= 5,		/*!< Ignore */
        siMsgYes	= 6,		/*!< Yes */
        siMsgNo	= 7		/*!< No */
    } 	siMsgButtonPressed;

/*! Specifies the view state information of the <object idref="View"/> object, such as whether the view is closed, whether the view is minimized, and whether the view is in a normal state. */
typedef   
enum siViewState
    {
        siNormal	= 0,		/*!< Normal */
        siClosed	= 1,		/*!< Closed */
        siMinimized	= 2		/*!< Minimized */
    } 	siViewState;

/*! Types of toolbar controls to use when building a toolbar. Toolbar controls help you to tweak the appearance of your toolbar by adding some cosmetic features, such as separators and line breaks. */
typedef   
enum siToolbarControl
    {
        siTBCtrlBlankSeparator	= 0,		/*!< Blank separator */
        siTBCtrlGroupHeader	= 1,		/*!< Group header */
        siTBCtrlLineBreak	= 2,		/*!< Line break */
        siTBCtrlMenu	= 3,		/*!< Cascading command menu button */
        siTBCtrlPreset	= 4,		/*!< Cascading command preset menu button */
        siTBCtrlLineSeparator	= 5		/*!< Line separator */
    } 	siToolbarControl;

/*! Specifies the type of time applicability of a <object idref="ClipEffect"/> on a <object idref="Clip"/>. */
typedef   
enum siTimeReferenceType
    {
        siOriginalClip	= 0,		/*!< The effect will repeat itself over time. */
        siExtrapolatedClip	= 1		/*!< the effect spans over extrapolation. */
    } 	siTimeReferenceType;

/*! Specifies a reduction to apply to an image. For example a 800x400 image reduced by a 4x1 ratio will have a resolution of 200x100. */
typedef   
enum siImageRatio
    {
        siImageRatio1x1	= 0,		/*!< Full resolution issue. */
        siImageRatio2x1	= 1,		/*!< Image reduced to 1/2 resolution (e.g. 1/4 the memory consumption). */
        siImageRatio4x1	= 2,		/*!< Image reduced to 1/4 resolution. */
        siImageRatio8x1	= 3,		/*!< Image reduced to 1/8 resolution. */
        siImageRatio16x1	= 4,		/*!< Image reduced to 1/16 resolution. */
        siImageRatioThumbnail	= 5		/*!< Image reduced to Thumbnail resolution. */
    } 	siImageRatio;

/*! The siTimeControlExtrapolationType determines how a <object idref="Clip"/> contributes to the animation outside of the frames on which it is defined. */
typedef   
enum siTimeControlExtrapolationType
    {
        siTimeControlExtrapolationNone	= 0,		/*!< Results in no extrapolation. Use this to delete an extrapolation. */
        siTimeControlExtrapolationHold	= 1,		/*!< Results in the first or last values being held for the number of frames specified by <object idref="TimeControl.ExtrapolationBeforeValue"/> or <object idref="TimeControl.ExtrapolationAfterValue"/>. */
        siTimeControlExtrapolationCycle	= 2,		/*!< Repeats the clip for the number of times specified by <object idref="TimeControl.ExtrapolationBeforeValue"/> or <object idref="TimeControl.ExtrapolationAfterValue"/>. */
        siTimeControlExtrapolationBounce	= 3		/*!< Repeats the clip forward, then backward, and so on for the number of times specified by <object idref="TimeControl.ExtrapolationBeforeValue"/> or <object idref="TimeControl.ExtrapolationAfterValue"/>.  */
    } 	siTimeControlExtrapolationType;

/*! Specifies the style of a menu item. */
typedef   
enum siMenuItemStyle
    {
        siMenuItemUndefined	= 0,		/*!< Undefined menu item style. */
        siMenuItem	= ( siMenuItemUndefined + 1 ) ,		/*!< Regular menu item. */
        siMenuItemSubmenu	= ( siMenuItem + 1 ) ,		/*!< Defines item as a submenu. */
        siMenuItemSeparator	= ( siMenuItemSubmenu + 1 ) ,		/*!< Defines item as a separator. */
        siMenuItemSection	= ( siMenuItemSeparator + 1 ) 		/*!< Defines item as a colored section separator with a label. */
    } 	siMenuItemStyle;

/*! Identifies the location of a custom menu. */
typedef   
enum siMenuAnchorPoints
    {
        siMenuUndefinedID	= 0,		/*!< Undefined menu id. */
        siMenuTbGetPrimitiveCurveID	= 1,		/*!< Get &gt; Primitive &gt; Curve menu. */
        siMenuTbGetPrimitivePolygonMeshBasicID	= ( siMenuTbGetPrimitiveCurveID + 1 ) ,		/*!< Basic section (Cone, Cube, ..., Torus) in the Get &gt; Primitive &gt; Polygon Mesh menu. */
        siMenuTbGetPrimitivePolygonMeshHedronID	= ( siMenuTbGetPrimitivePolygonMeshBasicID + 1 ) ,		/*!< Hedron section (Dodecahedron, Icosahedron, ..., Rhombicosidodecahedron) in the Get &gt; Primitive &gt; Polygon Mesh menu. */
        siMenuTbGetPrimitivePolygonMeshID	= ( siMenuTbGetPrimitivePolygonMeshHedronID + 1 ) ,		/*!< Get &gt; Primitive &gt; Polygon Mesh menu. */
        siMenuTbGetPrimitiveSurfaceID	= ( siMenuTbGetPrimitivePolygonMeshID + 1 ) ,		/*!< Get &gt; Primitive &gt; Surface menu. */
        siMenuTbGetPrimitiveImplicitCurveID	= ( siMenuTbGetPrimitiveSurfaceID + 1 ) ,		/*!< Curve section (Arc, Circle, ..., Square) in the Get &gt; Primitive &gt; Implicit menu. */
        siMenuTbGetPrimitiveImplicitID	= ( siMenuTbGetPrimitiveImplicitCurveID + 1 ) ,		/*!< Get &gt; Primitive &gt; Implicit menu. */
        siMenuTbGetPrimitiveControlObjectID	= ( siMenuTbGetPrimitiveImplicitID + 1 ) ,		/*!< Get &gt; Primitive &gt; Control Object menu. */
        siMenuTbGetPrimitiveModelID	= ( siMenuTbGetPrimitiveControlObjectID + 1 ) ,		/*!< Get &gt; Primitive &gt; Model menu . */
        siMenuTbGetPrimitiveID	= ( siMenuTbGetPrimitiveModelID + 1 ) ,		/*!< Get &gt; Primitive menu. */
        siMenuTbGetCameraID	= ( siMenuTbGetPrimitiveID + 1 ) ,		/*!< Get &gt; Primitive &gt; Camera menu. */
        siMenuTbGetLightID	= ( siMenuTbGetCameraID + 1 ) ,		/*!< Get &gt; Primitive &gt; Light menu. */
        siMenuTbGetMaterialID	= ( siMenuTbGetLightID + 1 ) ,		/*!< Get &gt; Material menu. */
        siMenuTbGetMaterialBasicID	= ( siMenuTbGetMaterialID + 1 ) ,		/*!< Basic (Phong, Lambert, ..., Toon) section in the Get &gt; Material menu. */
        siMenuTbGetMaterialSimpleID	= ( siMenuTbGetMaterialBasicID + 1 ) ,		/*!< Simple section in the Get &gt; Material menu. */
        siMenuTbGetMaterialRealTimeID	= ( siMenuTbGetMaterialSimpleID + 1 ) ,		/*!< Realtime section (OGL Combined,...) in the Get &gt; Material menu. */
        siMenuTbGetPropertyID	= ( siMenuTbGetMaterialRealTimeID + 1 ) ,		/*!< Get &gt; Property menu. */
        siMenuTbGetPropertyTextureProjectionID	= ( siMenuTbGetPropertyID + 1 ) ,		/*!< Get &gt; Property &gt; Texture Projection menu. */
        siMenuTbGetPropertyTextureMapID	= ( siMenuTbGetPropertyTextureProjectionID + 1 ) ,		/*!< Get &gt; Property &gt; Texture Map menu. */
        siMenuTbGetPropertyTextureID	= ( siMenuTbGetPropertyTextureMapID + 1 ) ,		/*!< Texture section in the Get &gt; Property menu. */
        siMenuTbGetPropertyUserDataMapID	= ( siMenuTbGetPropertyTextureID + 1 ) ,		/*!< Get &gt; Property &gt; User Data Map menu. */
        siMenuTbGetPropertyMapPaintID	= ( siMenuTbGetPropertyUserDataMapID + 1 ) ,		/*!< Get &gt; Property &gt; Map Paint Tools menu. */
        siMenuTbGetPropertyPSetID	= ( siMenuTbGetPropertyMapPaintID + 1 ) ,		/*!< Property section (Ultimapper, TextProp, ..., Tangent) in the Get &gt; Property menu. */
        siMenuTbDeformSpatialID	= ( siMenuTbGetPropertyPSetID + 1 ) ,		/*!< Spatial section (Bend, Bulge, ..., Fold) in the Modify &gt; Deform menu. */
        siMenuTbDeformID	= ( siMenuTbDeformSpatialID + 1 ) ,		/*!< dify &gt; Deform menu. */
        siMenuTbCreateSkeletonID	= ( siMenuTbDeformID + 1 ) ,		/*!< Create &gt; Skeleton menu. */
        siMenuTbCreateSkeletonDrawID	= ( siMenuTbCreateSkeletonID + 1 ) ,		/*!< Draw section (2D Chain, 3D Chain) in the Create &gt; Skeleton menu. */
        siMenuTbCreateSkeletonInspectID	= ( siMenuTbCreateSkeletonDrawID + 1 ) ,		/*!< Inspect section (Inspect Chain Properties) in the Create &gt; Skeleton menu. */
        siMenuTbModelCreateCurveID	= 100,		/*!< Create &gt; Curve menu (Model toolbar). */
        siMenuTbModelCreateSurfaceMeshID	= ( siMenuTbModelCreateCurveID + 1 ) ,		/*!< Create &gt; Surf. Mesh menu. */
        siMenuTbModelCreatePolygonMeshID	= ( siMenuTbModelCreateSurfaceMeshID + 1 ) ,		/*!< Create &gt; Poly. Mesh menu. */
        siMenuTbModelCreateModelID	= ( siMenuTbModelCreatePolygonMeshID + 1 ) ,		/*!< Create &gt; Model menu. */
        siMenuTbModelCreateTextID	= ( siMenuTbModelCreateModelID + 1 ) ,		/*!< Create &gt; Text menu. */
        siMenuTbModelModifyComponentID	= ( siMenuTbModelCreateTextID + 1 ) ,		/*!< Modify &gt; Component menu. */
        siMenuTbModelModifyCurveID	= ( siMenuTbModelModifyComponentID + 1 ) ,		/*!< Modify &gt; Curve menu. */
        siMenuTbModelModifySurfaceMeshID	= ( siMenuTbModelModifyCurveID + 1 ) ,		/*!< Modify &gt; Surf. Mesh menu. */
        siMenuTbModelModifyPolygonMeshID	= ( siMenuTbModelModifySurfaceMeshID + 1 ) ,		/*!< Modify &gt; Poly. Mesh menu. */
        siMenuTbModelModifyModelID	= ( siMenuTbModelModifyPolygonMeshID + 1 ) ,		/*!< Modify &gt; Model menu. */
        siMenuTbAnimateCreateParameterID	= 200,		/*!< Create &gt; Parameter menu. */
        siMenuTbAnimateCreateParameterCustomPSetID	= ( siMenuTbAnimateCreateParameterID + 1 ) ,		/*!< Custom Property Wizard section in the Create &gt; Parameter menu. */
        siMenuTbAnimateCreateParameterCustomParamID	= ( siMenuTbAnimateCreateParameterCustomPSetID + 1 ) ,		/*!< Custom Parameter section in the Create &gt; Parameter menu. */
        siMenuTbAnimateCreateParameterExpressionID	= ( siMenuTbAnimateCreateParameterCustomParamID + 1 ) ,		/*!< Expression section in the Create &gt; Parameter menu. */
        siMenuTbAnimateCreateParameterProxyID	= ( siMenuTbAnimateCreateParameterExpressionID + 1 ) ,		/*!< Proxy Parameter section in the Create &gt; Parameter menu. */
        siMenuTbAnimateCreateCurveID	= ( siMenuTbAnimateCreateParameterProxyID + 1 ) ,		/*!< Create &gt; Curve menu (Animate toolbar). */
        siMenuTbAnimateCreatePathID	= ( siMenuTbAnimateCreateCurveID + 1 ) ,		/*!< Create &gt; Path menu. */
        siMenuTbAnimateCreateCharacterID	= ( siMenuTbAnimateCreatePathID + 1 ) ,		/*!< Create &gt; Character menu. */
        siMenuTbAnimateDeformShapeID	= ( siMenuTbAnimateCreateCharacterID + 1 ) ,		/*!< Deform &gt; Shape menu. */
        siMenuTbAnimateDeformShapeKeyID	= ( siMenuTbAnimateDeformShapeID + 1 ) ,		/*!< Shape Key section in the Deform &gt; Shape menu. */
        siMenuTbAnimateDeformEnvelopeID	= ( siMenuTbAnimateDeformShapeKeyID + 1 ) ,		/*!< Deform &gt; Envelope menu. */
        siMenuTbAnimateActionsStoreID	= ( siMenuTbAnimateDeformEnvelopeID + 1 ) ,		/*!< Actions &gt; Store menu. */
        siMenuTbAnimateActionsApplyID	= ( siMenuTbAnimateActionsStoreID + 1 ) ,		/*!< Actions &gt; Apply menu. */
        siMenuTbAnimateActionsTemplatesID	= ( siMenuTbAnimateActionsApplyID + 1 ) ,		/*!< Actions &gt; Templates menu. */
        siMenuTbAnimateToolsPlotID	= ( siMenuTbAnimateActionsTemplatesID + 1 ) ,		/*!< Tools &gt; Plot menu. */
        siMenuTbAnimateToolsDevicesID	= ( siMenuTbAnimateToolsPlotID + 1 ) ,		/*!< Tools &gt; Devices menu. */
        siMenuTbAnimateToolsImportID	= ( siMenuTbAnimateToolsDevicesID + 1 ) ,		/*!< Import section in the Tools &gt; Import/Export menu. */
        siMenuTbAnimateToolsExportID	= ( siMenuTbAnimateToolsImportID + 1 ) ,		/*!< Export section in the Tools &gt; Import/Export menu. */
        siMenuTbAnimateToolsMotorID	= ( siMenuTbAnimateToolsExportID + 1 ) ,		/*!< MOTOR section in the Tools &gt; Import/Export menu. */
        siMenuTbRenderRegionID	= 300,		/*!< Render &gt; Region menu. */
        siMenuTbRenderPreviewID	= ( siMenuTbRenderRegionID + 1 ) ,		/*!< Obsolete - menu no longer exists. */
        siMenuTbRenderRenderID	= ( siMenuTbRenderPreviewID + 1 ) ,		/*!< Render &gt; Render menu. */
        siMenuTbRenderExportMIID	= ( siMenuTbRenderRenderID + 1 ) ,		/*!< Obsolete - renamed siMenuTbRenderExportID. */
        siMenuTbRenderPassEditID	= ( siMenuTbRenderExportMIID + 1 ) ,		/*!< Render &gt; Pass &gt; Edit menu. */
        siMenuTbRenderPassEditNewPassID	= ( siMenuTbRenderPassEditID + 1 ) ,		/*!< Render &gt; Pass &gt; Edit &gt; New Pass menu. */
        siMenuTbRenderPassPartitionID	= ( siMenuTbRenderPassEditNewPassID + 1 ) ,		/*!< Render &gt; Pass &gt; Partition menu. */
        siMenuTbRenderExportID	= ( siMenuTbRenderPassPartitionID + 1 ) ,		/*!< Render &gt; Export menu. */
        siMenuTbICEParticlesCreateID	= 320,		/*!< Menu the ICE module toolbar */
        siMenuTbICEParticlesOnEmissionID	= ( siMenuTbICEParticlesCreateID + 1 ) ,		/*!< Menu the ICE module toolbar */
        siMenuTbICEParticlesAfterEmissionID	= ( siMenuTbICEParticlesOnEmissionID + 1 ) ,		/*!< Menu the ICE module toolbar */
        siMenuTbICEParticlesForceID	= ( siMenuTbICEParticlesAfterEmissionID + 1 ) ,		/*!< Menu the ICE module toolbar */
        siMenuTbICEParticlesCollisionID	= ( siMenuTbICEParticlesForceID + 1 ) ,		/*!< Menu the ICE module toolbar */
        siMenuTbICEParticlesSimulationID	= ( siMenuTbICEParticlesCollisionID + 1 ) ,		/*!< Menu the ICE module toolbar */
        siMenuTbICEParticlesModelLibraryID	= ( siMenuTbICEParticlesSimulationID + 1 ) ,		/*!< Menu the ICE module toolbar */
        siMenuTbICEDeformCreateID	= 340,		/*!< Menu the ICE module toolbar */
        siMenuTbICEDeformSimulateID	= ( siMenuTbICEDeformCreateID + 1 ) ,		/*!< Menu the ICE module toolbar */
        siMenuTbICEKinematicsEffectsID	= 360,		/*!< Menu the ICE module toolbar */
        siMenuTbICEKinematicsConstrainID	= ( siMenuTbICEKinematicsEffectsID + 1 ) ,		/*!< Menu the ICE module toolbar */
        siMenuTbICECrowdFXActorsID	= 380,		/*!< Menu the ICE module toolbar */
        siMenuTbICECrowdFXSimulationID	= ( siMenuTbICECrowdFXActorsID + 1 ) ,		/*!< Menu the ICE module toolbar */
        siMenuTbICECrowdFXCrowdID	= ( siMenuTbICECrowdFXSimulationID + 1 ) ,		/*!< Menu the ICE module toolbar */
        siMenuTbGetForceID	= 400,		/*!< Get &gt; Force menu (Simulate toolbar). */
        siMenuTbCreateParticlesID	= ( siMenuTbGetForceID + 1 ) ,		/*!< Create &gt; Particles menu (Simulate toolbar). */
        siMenuTbCreateParticlesFluidID	= ( siMenuTbCreateParticlesID + 1 ) ,		/*!< Create &gt; Particles &gt; Fluid menu (Simulate toolbar). */
        siMenuTbCreateParticlesExplosionID	= ( siMenuTbCreateParticlesFluidID + 1 ) ,		/*!< Create &gt; Particles &gt; Explosion menu (Simulate toolbar). */
        siMenuTbCreateParticlesNewPTypeID	= ( siMenuTbCreateParticlesExplosionID + 1 ) ,		/*!< Create &gt; Particles &gt; New Particle Type menu (Simulate toolbar). */
        siMenuTbCreateRigidBodyID	= ( siMenuTbCreateParticlesNewPTypeID + 1 ) ,		/*!< Create &gt; Rigid Body menu (Simulate toolbar). */
        siMenuTbCreateRigidBodyConstraintID	= ( siMenuTbCreateRigidBodyID + 1 ) ,		/*!< Create &gt; Rigid Body &gt; Rigid Constraint menu (Simulate toolbar). */
        siMenuTbCreateClothID	= ( siMenuTbCreateRigidBodyConstraintID + 1 ) ,		/*!< Create &gt; Cloth menu (Simulate toolbar). */
        siMenuTbModifyParticlesID	= ( siMenuTbCreateClothID + 1 ) ,		/*!< Modify &gt; Particles menu (Simulate toolbar). */
        siMenuTbModifyRigidBodyID	= ( siMenuTbModifyParticlesID + 1 ) ,		/*!< Modify &gt; Rigid Body menu (Simulate toolbar). */
        siMenuTbModifyEnvironmentID	= ( siMenuTbModifyRigidBodyID + 1 ) ,		/*!< Modify &gt; Environment menu (Simulate toolbar). */
        siMenuTbCreateSoftBodyID	= ( siMenuTbModifyEnvironmentID + 1 ) ,		/*!< Create &gt; Soft Body menu (Simulate toolbar). */
        siMenuTbICECreateID	= ( siMenuTbCreateSoftBodyID + 1 ) ,		/*!< ICE &gt; Particles &gt; Create menu (ICE toolbar). */
        siMenuTbICEEditID	= ( siMenuTbICECreateID + 1 ) ,		/*!< ICE &gt; Particles &gt; Simulation menu (ICE toolbar). */
        siMenuMainFileSceneID	= 1000,		/*!< Scene section in the File menu on the main menu bar. */
        siMenuMainFileProjectID	= ( siMenuMainFileSceneID + 1 ) ,		/*!< Project section in the File menu on the main menu bar. */
        siMenuMainFileExportID	= ( siMenuMainFileProjectID + 1 ) ,		/*!< File &gt; Export menu on the main menu bar. */
        siMenuMainFileImportID	= ( siMenuMainFileExportID + 1 ) ,		/*!< File &gt; Import menu on the main menu bar. */
        siMenuMainWindowID	= ( siMenuMainFileImportID + 1 ) ,		/*!< Windows menu on the main menu bar. */
        siMenuMainHelpID	= ( siMenuMainWindowID + 1 ) ,		/*!< Help menu on the main menu bar. */
        siMenuMainApplicationID	= ( siMenuMainHelpID + 1 ) ,		/*!< Do not use. The Application menu was removed in Softimage v5.0. Existing menus that use this anchor point are added to the View menu on the main menu bar. */
        siMenuMainApplicationPropertySetsID	= ( siMenuMainApplicationID + 1 ) ,		/*!< Do not use. The Application menu was removed in Softimage v5.0. Existing menus that use this anchor point are added to the View menu on the main menu bar. */
        siMenuMainApplicationLayoutsID	= ( siMenuMainApplicationPropertySetsID + 1 ) ,		/*!< Do not use. The Application menu was removed in Softimage v5.0. Existing menus that use this anchor point are added to the View &gt; Layouts menu on the main menu bar. */
        siMenuMainApplicationViewsID	= ( siMenuMainApplicationLayoutsID + 1 ) ,		/*!< Do not use. The Application menu was removed in Softimage v5.0. Existing menus that use this anchor point are added to the View menu on the main menu bar. */
        siMenuMainApplicationToolbarsID	= ( siMenuMainApplicationViewsID + 1 ) ,		/*!< Do not use. The Application menu was removed in Softimage v5.0. Existing menus that use this anchor point are added to the View menu on the main menu bar. */
        siMenuMainApplicationCommandsID	= ( siMenuMainApplicationToolbarsID + 1 ) ,		/*!< Do not use. The Application menu was removed in Softimage v5.0. Existing menus that use this anchor point are added to the View menu on the main menu bar. */
        siMenuMainApplicationKeyMappingsID	= ( siMenuMainApplicationCommandsID + 1 ) ,		/*!< Do not use. The Application menu was removed in Softimage v5.0. Existing menus that use this anchor point are added to the View menu on the main menu bar. */
        siMenuMainApplicationPreferencesID	= ( siMenuMainApplicationKeyMappingsID + 1 ) ,		/*!< Do not use. The Application menu was removed in Softimage v5.0. Existing menus that use this anchor point are added to the Preferences section of the File menu on the main menu bar. */
        siMenuMainTopLevelID	= ( siMenuMainApplicationPreferencesID + 1 ) ,		/*!< The main menu bar. Menus registered with this identifier are added to the Softimage main menu bar as top-level menus. */
        siMenuMainFileCrosswalkID	= ( siMenuMainTopLevelID + 1 ) ,		/*!< File &gt; Crosswalk menu on the main menu bar. */
        siMenuMCPSelectTopID	= 2000,		/*!< Top of Select menu in the MCP. */
        siMenuMCPSelectBottomID	= ( siMenuMCPSelectTopID + 1 ) ,		/*!< Bottom of Select menu in the MCP. */
        siMenuMCPSelectExploreBtnID	= ( siMenuMCPSelectBottomID + 1 ) ,		/*!< Explore menu in the MCP. */
        siMenuMCPSelectSelBtnContextID	= ( siMenuMCPSelectExploreBtnID + 1 ) ,		/*!< Context menu displayed when a user right-clicks the Selection button in the MCP. */
        siMenuMCPTransformTopID	= ( siMenuMCPSelectSelBtnContextID + 1 ) ,		/*!< Top of Transform menu in the MCP. */
        siMenuMCPTransformBottomID	= ( siMenuMCPTransformTopID + 1 ) ,		/*!< Bottom of Transform menu in the MCP. */
        siMenuMCPSnapID	= ( siMenuMCPTransformBottomID + 1 ) ,		/*!< Snap menu in the MCP. */
        siMenuMCPConstrainID	= ( siMenuMCPSnapID + 1 ) ,		/*!< Constrain menu in the MCP. */
        siMenuMCPEditID	= ( siMenuMCPConstrainID + 1 ) ,		/*!< Edit menu in the MCP. */
        siMenuMCPAnimationID	= ( siMenuMCPEditID + 1 ) ,		/*!< Animation menu in the MCP. */
        siMenuMCPPlaybackID	= ( siMenuMCPAnimationID + 1 ) ,		/*!< Playback menu in the MCP. */
        siMenuVMViewTypeID	= 3000,		/*!< View type menu in the View Manager. See <article idref="ViewManagerAttributes">View Manager Attributes</article> for a list of attributes you can use with this custom menu hook. */
        siMenuVMCameraID	= ( siMenuVMViewTypeID + 1 ) ,		/*!< Camera menu in the View Manager. See <article idref="ViewManagerAttributes">View Manager Attributes</article> for a list of attributes you can use with this custom menu hook. */
        siMenuVMVisibilityID	= ( siMenuVMCameraID + 1 ) ,		/*!< Visibility menu in the View Manager. See <article idref="ViewManagerAttributes">View Manager Attributes</article> for a list of attributes you can use with this custom menu hook. */
        siMenuVMDisplayID	= ( siMenuVMVisibilityID + 1 ) ,		/*!< Display menu in the View Manager. See <article idref="ViewManagerAttributes">View Manager Attributes</article> for a list of attributes you can use with this custom menu hook. */
        siMenu3DViewClusterContextID	= 3100,		/*!< Context menu for a cluster in a 3D view. */
        siMenu3DViewComponentContextID	= ( siMenu3DViewClusterContextID + 1 ) ,		/*!< Context menu for subcomponents (such as points, edges, and polygons) in a 3D view. */
        siMenu3DViewComponentEditContextID	= ( siMenu3DViewComponentContextID + 1 ) ,		/*!< Edit section of the context menu for subcomponents in a 3D view. */
        siMenu3DViewGeneralContextID	= ( siMenu3DViewComponentEditContextID + 1 ) ,		/*!< Context menu displayed when a user right-clicks a blank area of a 3D view. */
        siMenu3DViewObjectContextID	= ( siMenu3DViewGeneralContextID + 1 ) ,		/*!< Context menu for an object in a 3D view. */
        siMenu3DViewObjectEditContextID	= ( siMenu3DViewObjectContextID + 1 ) ,		/*!< Edit section of the context menu for an object in a 3D view. */
        siMenu3DViewObjectGroupContextID	= ( siMenu3DViewObjectEditContextID + 1 ) ,		/*!< Group section of the context menu for an object in a 3D view. */
        siMenu3DViewObjectMeshContextID	= ( siMenu3DViewObjectGroupContextID + 1 ) ,		/*!< Mesh section of the context menu for an object in a 3D view. */
        siMenu3DViewObjectSelectContextID	= ( siMenu3DViewObjectMeshContextID + 1 ) ,		/*!< Select section of the context menu for an object in a 3D view. */
        siMenuSEGeneralContextID	= 3200,		/*!< Context menu displayed when a user right-clicks an object (such as a Property, Parameter, or Primtive) that does not have a specific context menu. */
        siMenuSELayersContextID	= ( siMenuSEGeneralContextID + 1 ) ,		/*!< Context menu displayed for Layer objects in the Scene Explorer. */
        siMenuSEPassesContextID	= ( siMenuSELayersContextID + 1 ) ,		/*!< Context menu displayed for Pass objects in the Scene Explorer. */
        siMenuSEPartitionsContextID	= ( siMenuSEPassesContextID + 1 ) ,		/*!< Context menu displayed for Partition objects in the Scene Explorer. */
        siMenuSEObjectContextID	= ( siMenuSEPartitionsContextID + 1 ) ,		/*!< Context menu displayed for 3D objects in the Scene Explorer. */
        siMenuSEGroupContextID	= ( siMenuSEObjectContextID + 1 ) ,		/*!< Context menu displayed for Groups in the Scene Explorer. */
        siMenuSEAnimContextID	= ( siMenuSEGroupContextID + 1 ) ,		/*!< Context menu displayed for animated parameters in the Scene Explorer. */
        siMenuSEClusterContextID	= ( siMenuSEAnimContextID + 1 ) ,		/*!< Context menu displayed for clusters in the Scene Explorer. */
        siMenuSEOperatorContextID	= ( siMenuSEClusterContextID + 1 ) ,		/*!< Context menu displayed for operators in the Scene Explorer. */
        siMenuSEConstraintContextID	= ( siMenuSEOperatorContextID + 1 ) ,		/*!< Context menu displayed for constraints in the Scene Explorer. */
        siMenuSEPreferenceContextID	= ( siMenuSEConstraintContextID + 1 ) ,		/*!< Context menu displayed for preferences in the Scene Explorer. */
        siMenuSEMaterialContextID	= ( siMenuSEPreferenceContextID + 1 ) ,		/*!< Context menu displayed for Materials in the Scene Explorer. */
        siMenuSEModelContextID	= ( siMenuSEMaterialContextID + 1 ) ,		/*!< Context menu displayed for Models in the Scene Explorer. */
        siMenuPluginMgrPluginFileID	= 3300,		/*!< File menu on the Plug-ins and Items tabs of the Plug-in Manager. See <article idref="PluginManagerAttributes">Plug-in Manager Attributes</article> for a list of attributes you can use with this custom menu hook. */
        siMenuPluginMgrTreeFileID	= ( siMenuPluginMgrPluginFileID + 1 ) ,		/*!< File menu on the Tree tab of the Plug-in Manager. See <article idref="PluginManagerAttributes">Plug-in Manager Attributes</article> for a list of attributes you can use with this custom menu hook. */
        siMenuPluginMgrContextPluginID	= ( siMenuPluginMgrTreeFileID + 1 ) ,		/*!< Context menu for plug-ins listed on the Tree and Plug-ins tabs of the Plugin Manager. See <article idref="PluginManagerAttributes">Plug-in Manager Attributes</article> for a list of attributes you can use with this custom menu hook. */
        siMenuPluginMgrContextPluginLocationID	= ( siMenuPluginMgrContextPluginID + 1 ) ,		/*!< Context menu in the Plug-in Manager for an add-on or other location where plug-ins can be stored. See <article idref="PluginManagerAttributes">Plug-in Manager Attributes</article> for a list of attributes you can use with this custom menu hook. */
        siMenuPluginMgrContextUserRootID	= ( siMenuPluginMgrContextPluginLocationID + 1 ) ,		/*!< Context menu for the User Root node in the plug-in tree. See <article idref="PluginManagerAttributes">Plug-in Manager Attributes</article> for a list of attributes you can use with this custom menu hook. */
        siMenuPluginMgrContextFactoryRootID	= ( siMenuPluginMgrContextUserRootID + 1 ) ,		/*!< Context menu for the Factory Root node in the plug-in tree. See <article idref="PluginManagerAttributes">Plug-in Manager Attributes</article> for a list of attributes you can use with this custom menu hook. */
        siMenuPluginMgrContextWorkgroupRootID	= ( siMenuPluginMgrContextFactoryRootID + 1 ) ,		/*!< Context menu for the Workgroup Root node in the plug-in tree. See <article idref="PluginManagerAttributes">Plug-in Manager Attributes</article> for a list of attributes you can use with this custom menu hook. */
        siMenuPluginMgrContextAddonID	= ( siMenuPluginMgrContextWorkgroupRootID + 1 ) ,		/*!< Context menu for the add-ons listed in the plug-in tree. See <article idref="PluginManagerAttributes">Plug-in Manager Attributes</article> for a list of attributes you can use with this custom menu hook. */
        siMenuPluginMgrContextCustomLocationID	= ( siMenuPluginMgrContextAddonID + 1 ) ,		/*!< Context menu for the Root node of a custom folder in the plug-in tree. See <article idref="PluginManagerAttributes">Plug-in Manager Attributes</article> for a list of attributes you can use with this custom menu hook. */
        siMenuPluginMgrSPDLFileID	= ( siMenuPluginMgrContextCustomLocationID + 1 ) ,		/*!< File menu on the SPDLs tab of the Plug-in Manager. See <article idref="PluginManagerAttributes">Plug-in Manager Attributes</article> for a list of attributes you can use with this custom menu hook. */
        siMenuPluginMgrContextSPDLID	= ( siMenuPluginMgrSPDLFileID + 1 ) ,		/*!< Context menu for the plug-ins listed on the SPDLs tab of the Plugin Manager. See <article idref="PluginManagerAttributes">Plug-in Manager Attributes</article> for a list of attributes you can use with this custom menu hook. */
        siMenuPluginMgrContextSPDLLocationID	= ( siMenuPluginMgrContextSPDLID + 1 ) ,		/*!< Context menu for the SPDLs Root node in the plug-in tree. See <article idref="PluginManagerAttributes">Plug-in Manager Attributes</article> for a list of attributes you can use with this custom menu hook. */
        siMenuPluginMgrContextPluginItemID	= ( siMenuPluginMgrContextSPDLLocationID + 1 ) ,		/*!< Context menu for the plug-ins listed on the Items tab of the Plugin Manager. See <article idref="PluginManagerAttributes">Plug-in Manager Attributes</article> for a list of attributes you can use with this custom menu hook. */
        siMenuPluginMgrContextViewLocationID	= ( siMenuPluginMgrContextPluginItemID + 1 ) ,		/*!< Context menu for the Views Root node in the plug-in tree. See <article idref="PluginManagerAttributes">Plug-in Manager Attributes</article> for a list of attributes you can use with this custom menu hook. */
        siMenuPluginMgrContextViewID	= ( siMenuPluginMgrContextViewLocationID + 1 ) ,		/*!< Context menu for view plug-ins listed in the plug-in tree. See <article idref="PluginManagerAttributes">Plug-in Manager Attributes</article> for a list of attributes you can use with this custom menu hook. */
        siMenuPluginMgrContextToolbarLocationID	= ( siMenuPluginMgrContextViewID + 1 ) ,		/*!< Context menu for the Toolbars Root node in the plug-in tree. See <article idref="PluginManagerAttributes">Plug-in Manager Attributes</article> for a list of attributes you can use with this custom menu hook. */
        siMenuPluginMgrContextToolbarID	= ( siMenuPluginMgrContextToolbarLocationID + 1 ) ,		/*!< Context menu for the toolbar plug-ins listed in the plug-in tree. See <article idref="PluginManagerAttributes">Plug-in Manager Attributes</article> for a list of attributes you can use with this custom menu hook. */
        siMenuWorkgroupMgrFileID	= 3350,		/*!< File menu on the Workgroups tab of the Plug-in Manager. See <article idref="PluginManagerAttributes">Plug-in Manager Attributes</article> for a list of attributes you can use with this custom menu hook. */
        siMenuWorkgroupMgrContextID	= ( siMenuWorkgroupMgrFileID + 1 ) ,		/*!< Context menu for a selected workgroup. See <article idref="PluginManagerAttributes">Plug-in Manager Attributes</article> for a list of attributes you can use with this custom menu hook. */
        siMenuScriptEditContextID	= 3400,		/*!< Context menu for the editing pane of a script editor or a text editor. See <article idref="ScriptEditorAttributes">Script Editor Attributes</article> for a list of attributes you can use with this custom menu hook. */
        siMenuScriptHistoryContextID	= 3401,		/*!< Context menu for the history pane of a script editor. See <article idref="ScriptHistoryAttributes">Script History Attributes</article> for a list of attributes you can use with this custom menu hook. */
        siMenuFCurveEditorTopLevelID	= 3500,		/*!< Menus registered with this identifier are added to the FCurve Editor toolbar as top-level menus. See <article idref="FCurveEditorAttributes">FCurve Editor Attributes</article> for a list of attributes you can use with this custom menu hook. */
        siMenuFCurveEditorFileID	= ( siMenuFCurveEditorTopLevelID + 1 ) ,		/*!< File menu in the FCurve Editor. See <article idref="FCurveEditorAttributes">FCurve Editor Attributes</article> for a list of attributes you can use with this custom menu hook. */
        siMenuFCurveEditorEditID	= ( siMenuFCurveEditorFileID + 1 ) ,		/*!< Edit menu in the FCurve Editor. See <article idref="FCurveEditorAttributes">FCurve Editor Attributes</article> for a list of attributes you can use with this custom menu hook. */
        siMenuFCurveEditorViewID	= ( siMenuFCurveEditorEditID + 1 ) ,		/*!< View menu in the FCurve Editor. See <article idref="FCurveEditorAttributes">FCurve Editor Attributes</article> for a list of attributes you can use with this custom menu hook. */
        siMenuFCurveEditorKeysID	= ( siMenuFCurveEditorViewID + 1 ) ,		/*!< Keys menu in the FCurve Editor. See <article idref="FCurveEditorAttributes">FCurve Editor Attributes</article> for a list of attributes you can use with this custom menu hook. */
        siMenuFCurveEditorCurvesID	= ( siMenuFCurveEditorKeysID + 1 ) ,		/*!< Curves menu in the FCurve Editor. See <article idref="FCurveEditorAttributes">FCurve Editor Attributes</article> for a list of attributes you can use with this custom menu hook. */
        siMenuFCurveEditorSelectID	= ( siMenuFCurveEditorCurvesID + 1 ) ,		/*!< Select menu in the FCurve Editor. See <article idref="FCurveEditorAttributes">FCurve Editor Attributes</article> for a list of attributes you can use with this custom menu hook. */
        siMenuPropertyPageContextID	= 3600,		/*!< Context menu for the top area of a Property Page. */
        siMenuPropertyPageAnimContextID	= ( siMenuPropertyPageContextID + 1 ) ,		/*!< Context menu displayed for animatable parameters in a Property Page. */
        siMenuShapeManagerEditID	= 3700,		/*!< Edit menu in the Shape Manager. See <article idref="ShapeManagerAttributes">Shape Manager Attributes</article> for a list of attributes you can use with this custom menu hook. */
        siMenuShapeManagerCreateContextSingleSelectionID	= ( siMenuShapeManagerEditID + 1 ) ,		/*!< Context menu for the Create tab of the Shape Manager when a single shape is selected. See <article idref="ShapeManagerAttributes">Shape Manager Attributes</article> for a list of attributes you can use with this custom menu hook. */
        siMenuShapeManagerCreateContextMultiSelectionID	= ( siMenuShapeManagerCreateContextSingleSelectionID + 1 ) ,		/*!< Context menu for the Create tab of the Shape Manager when multiple shapes are selected. See <article idref="ShapeManagerAttributes">Shape Manager Attributes</article> for a list of attributes you can use with this custom menu hook. */
        siMenuShapeManagerAnimateContextSingleSelectionID	= ( siMenuShapeManagerCreateContextMultiSelectionID + 1 ) ,		/*!< Context menu for the Animate tab of the Shape Manager when only a single shape is selected. See <article idref="ShapeManagerAttributes">Shape Manager Attributes</article> for a list of attributes you can use with this custom menu hook. */
        siMenuShapeManagerAnimateContextMultiSelectionID	= ( siMenuShapeManagerAnimateContextSingleSelectionID + 1 ) ,		/*!< Context menu for the Animate tab of the Shape Manager when multiple shapes are selected. See <article idref="ShapeManagerAttributes">Shape Manager Attributes</article> for a list of attributes you can use with this custom menu hook. */
        siMenuShapeManagerAnimateID	= ( siMenuShapeManagerAnimateContextMultiSelectionID + 1 ) ,		/*!< Animate menu in the Shape Manager. See <article idref="ShapeManagerAttributes">Shape Manager Attributes</article> for a list of attributes you can use with this custom menu hook. */
        siMenuRenderRegionContextID	= 3800,		/*!< Context menu for the Render Region. */
        siMenuMaterialPanelMaterialID	= 3900,		/*!< Material menu in the Material Panel. */
        siMenuTextureEditorToolsID	= 4000,		/*!< Tools menu in the Texture Editor. See <article idref="TextureEditorAttributes">Texture Editor Attributes</article> for a list of attributes you can use with this custom menu hook. */
        siMenuRenderTreeToolsID	= 4100,		/*!< Tools menu in the RenderTree.  See <article idref="RenderTreeAttributes">Render Tree Attributes</article> for a list of attributes you can use with this custom menu hook. */
        siMenuICEViewToolsID	= ( siMenuRenderTreeToolsID + 1 ) ,		/*!< Tools menu in the ICE view. See <article idref="RenderTreeAttributes">ICE Tree Attributes</article> for a list of attributes you can use with this custom menu hook. */
        siMenuRTNodeContextID	= ( siMenuICEViewToolsID + 1 ) ,		/*!< Context menu displayed for shader/materials in the RenderTree. See <article idref="RenderTreeAttributes">Render Tree Attributes</article> for a list of attributes you can use with this custom menu hook. */
        siMenuICENodeContextID	= ( siMenuRTNodeContextID + 1 ) ,		/*!< Context menu displayed for ICE Nodes in the ICE view. See <article idref="RenderTreeAttributes">ICE Tree Attributes</article> for a list of attributes you can use with this custom menu hook. */
        siMenuICENodePortContextID	= ( siMenuICENodeContextID + 1 ) ,		/*!< Context menu displayed for ICE Node Ports in the ICE view. See <article idref="RenderTreeAttributes">ICE Tree Attributes</article> for a list of attributes you can use with this custom menu hook. */
        siMenuRenderTreeTopLevelID	= ( siMenuICENodePortContextID + 1 ) ,		/*!< The RenderTree main toolbar. Menus registered with this identifier are added to the RenderTree toolbar as top-level menus. See <article idref="RenderTreeAttributes">Render Tree Attributes</article> for a list of attributes you can use with this custom menu hook. */
        siMenuICEViewTopLevelID	= ( siMenuRenderTreeTopLevelID + 1 ) ,		/*!< The ICE view main toolbar. Menus registered with this identifier are added to the ICE view toolbar as top-level menus. See <article idref="RenderTreeAttributes">ICE Tree Attributes</article> for a list of attributes you can use with this custom menu hook. */
        siMenuTextEditorWidgetEditID	= 4200,		/*!< Edit menu in the Text Editor Widget. See <article idref="ScriptEditorAttributes">Text Editor Attributes</article> for a list of attributes you can use with this custom menu hook. */
        siMenuTextEditorContextID	= ( siMenuTextEditorWidgetEditID + 1 ) ,		/*!< Context menu in the edit pane of a Text Editor Widget. See <article idref="ScriptEditorAttributes">Text Editor Attributes</article> for a list of attributes you can use with this custom menu hook. */
        siMenuTextureSpaceProjectionID	= 4300,		/*!< Texture Space &gt; New &gt; Texture Projection menu. */
        siMenuSchematicViewID	= 4400,		/*!< View menu in the Schematic. */
        siMenuSchematicViewContextID	= 4401,		/*!< Context menu for the Schematic when clicking in the background. */
        siMenuSchematicNodeContextID	= 4402,		/*!< Context menu displayed for nodes in the Schematic. */
        siMenuSchematicViewTopLevelID	= 4403,		/*!< Menus registered with this identifier are added to the Schematic view toolbar as top-level menus. */
        siMenuSceneLayerManagerLayersID	= 4500,		/*!< Layers menu in the Scene Layer Manager. */
        siMenuSceneLayerManagerContextID	= ( siMenuSceneLayerManagerLayersID + 1 ) ,		/*!< Context menu displayed for layer rows in the Scene Layer Manager. */
        siMenuMaterialManagerTopLevelID	= 4600,		/*!< Material Manager main toolbar. Menus registered with this identifier are added to the Material Manager toolbar as top-level menus. See <article idref="MaterialManagerAttributes">Material Manager Attributes</article> for a list of attributes you can use with this custom menu hook. */
        siMenuAnimMixerEditID	= 4700,		/*!< Edit menu in the Animation Mixer. See <article idref="AnimationMixerAttributes">Animation Mixer Attributes</article> for a list of attributes you can use with this custom menu hook. */
        siMenuAnimMixerViewID	= ( siMenuAnimMixerEditID + 1 ) ,		/*!< View menu in the Animation Mixer. See <article idref="AnimationMixerAttributes">Animation Mixer Attributes</article> for a list of attributes you can use with this custom menu hook. */
        siMenuAnimMixerTrackID	= ( siMenuAnimMixerViewID + 1 ) ,		/*!< Track menu in the Animation Mixer. See <article idref="AnimationMixerAttributes">Animation Mixer Attributes</article> for a list of attributes you can use with this custom menu hook. */
        siMenuAnimMixerClipID	= ( siMenuAnimMixerTrackID + 1 ) ,		/*!< Clip menu in the Animation Mixer. See <article idref="AnimationMixerAttributes">Animation Mixer Attributes</article> for a list of attributes you can use with this custom menu hook. */
        siMenuAnimMixerMixID	= ( siMenuAnimMixerClipID + 1 ) ,		/*!< Mix menu in the Animation Mixer. See <article idref="AnimationMixerAttributes">Animation Mixer Attributes</article> for a list of attributes you can use with this custom menu hook. */
        siMenuAnimMixerEffectID	= ( siMenuAnimMixerMixID + 1 ) ,		/*!< Effect menu in the Animation Mixer. See <article idref="AnimationMixerAttributes">Animation Mixer Attributes</article> for a list of attributes you can use with this custom menu hook. */
        siMenuShaderCodeEditContextID	= 4800,		/*!< Context menu displayed for the Shader Code Editor. */
        siMenuWeightEditorFileID	= 10000,		/*!< File menu in the Weight Editor. See <article idref="WeightEditorAttributes">Weight Editor Attributes</article> for a list of attributes you can use with this custom menu hook. */
        siMenuWeightEditorEditID	= 10001,		/*!< Edit menu in the Weight Editor. See <article idref="WeightEditorAttributes">Weight Editor Attributes</article> for a list of attributes you can use with this custom menu hook. */
        siMenuWeightEditorViewID	= 10002,		/*!< View menu in the Weight Editor. See <article idref="WeightEditorAttributes">Weight Editor Attributes</article> for a list of attributes you can use with this custom menu hook. */
        siMenuScriptedOpEditContextID	= 10100		/*!< Context menu displayed for both text editors in the Scripted Operator Editor. See <article idref="ScriptedOpEditorAttributes">Scripted Operator Editor Attributes</article> for a list of attributes you can use with this custom menu hook. */
    } 	siMenuAnchorPoints;

/*! This enum specifies the operator port flags. These flags are used to determine the behaviour and characteristics of the port. */
typedef   
enum siPortFlags
    {
        siDefaultPort	= 0,		/*!< The port is a regular port and must be connected. */
        siOptionalInputPort	= 16,		/*!< The port is optional as does not need to be connected. */
        siCreatedOutputPort	= 256,		/*!< The object connected to the output port is created when the operator is connected (not implemented for custom operators). */
        siBranchGroupPort	= 1024		/*!< The port can be connected to a group of a hierarchy of objects. */
    } 	siPortFlags;

/*! This enum specifies what has changed during a <link idref="CWindowNotification" file="cpp_ref"/> for the <article idref="cus_displayhost" file="../custom/cus_displayhost.fm">Custom Display Host</article>. */
typedef   
enum siWindowChangeState
    {
        siWindowSize	= 1,		/*!< The size or position of the window has changed. */
        siWindowPaint	= 2,		/*!< The window is being repainted. */
        siWindowSetFocus	= 3,		/*!< The window is getting the focus. */
        siWindowLostFocus	= 4		/*!< The window lost the focus. */
    } 	siWindowChangeState;

/*! This enum is used to determine the type of a file for the <article idref="ctxt_siOnBeginFileExport">OnBeginFileExport</article>, <article idref="ctxt_siOnBeginFileImport">OnBeginFileImport</article>, <article idref="ctxt_siOnEndFileExport">OnEndFileExport</article>, <article idref="ctxt_siOnEndFileImport">OnEndFileImport</article>, <article idref="ctxt_siOnCustomFileExport">OnCustomFileExport</article>, and <article idref="ctxt_siOnCustomFileImport">OnCustomFileImport</article> events. */
typedef   
enum siFileType
    {
        siFileTypeDefault	= 0,		/*!< Unknown type. */
        siFileTypeScene	= 1,		/*!< Scene. */
        siFileTypeModel	= 2,		/*!< Model. */
        siFileTypeImage	= 3,		/*!< Image. */
        siFileTypeAudio	= 4,		/*!< Audio. */
        siFileTypeSI3D	= 5,		/*!< SI3D scenes. */
        siFileTypeScript	= 6,		/*!< Script. */
        siFileTypeFcurve	= 7,		/*!< Animation file. */
        siFileTypeExpression	= 8,		/*!< Expression. */
        siFileTypeRenderPicture	= 9,		/*!< Rendered Pictures. */
        siFileTypeAction	= 10,		/*!< Action files (.eani). */
        siFileTypeShader	= 11,		/*!< Shader file. */
        siFileTypeBackup	= 12,		/*!< Scene Backup. */
        siFileTypeMI	= 13,		/*!< Mental Image (.mi) file. */
        siFileTypeIgnore	= 14,		/*!< Internal info. */
        siFileTypeSimulation	= 15,		/*!< Simulation cache. */
        siFileTypeReferencedModel	= 16,		/*!< Referenced model. */
        siFileTypeQuery	= 17,		/*!< Query. */
        siFileTypeSynoptic	= 18,		/*!< Synoptic. */
        siFileTypeDotXSI	= 19,		/*!< dotXSI. */
        siFileTypeRenderMap	= 20,		/*!< Render Map. */
        siFileTypeAddon	= 21,		/*!< Addon. */
        siFileTypeMatLib	= 22,		/*!< Material Library. */
        siFileTypeThumbnail	= 23,		/*!< Thumbnail. */
        siFileTypeMixer	= 24,		/*!< Mixer (.mixer). */
        siFileTypeIges	= 25,		/*!< IGES. */
        siFileTypeComposites	= 26,		/*!<  */
        siFileTypeDelta	= 27,		/*!< Model Delta. */
        siFileTypeCache	= 28,		/*!< Cache file. */
        siFileTypeICECompounds	= 29,		/*!< ICE Compound file. */
        siFileTypeRTCompounds	= 30,		/*!< RT Compound file. */
        siFileTypeCustom	= 31,		/*!< Custom. */
        siFileTypeLast	= 32		/*!< Number of items total. */
    } 	siFileType;

/*! This enum specifies the type of clusters in Softimage. */
typedef   
enum siClusterType
    {
        siClusterVertexType	= 0,		/*!< Vertex cluster type. */
        siClusterNodeType	= 1,		/*!< Node cluster type. */
        siClusterEdgeType	= 2,		/*!< Edge cluster type. */
        siClusterPolygonType	= 3		/*!< Polygon cluster type. */
    } 	siClusterType;

/*! This enum specifies the type of cluster properties in Softimage. */
typedef   
enum siClusterPropertyType
    {
        siClusterPropertyEnvelopeWeightType	= 0,		/*!< Vertex cluster property envelope weight type. */
        siClusterPropertyShapeKeyType	= 1,		/*!< Vertex cluster property Shape Key type. */
        siClusterPropertyWeightMapType	= 2,		/*!< Vertex cluster property Weight Map type. */
        siClusterPropertyUVType	= 3,		/*!< Node cluster property UV type. */
        siClusterPropertyVertexColorType	= 4,		/*!< Node cluster property vertex color type. */
        siClusterPropertyUserNormalType	= 5,		/*!< Node cluster property user normal type. */
        siClusterPropertyUserMotionType	= 6		/*!< Vertex cluster property User Motion type. */
    } 	siClusterPropertyType;

/*! This enum specifies the mode of manipulation of a curve isopoint in Softimage. */
typedef   
enum siCurveIsopointManipMode
    {
        siCurveIsopointPositionManipMode	= 0,
        siCurveIsopointPositionAndTangentsManipMode	= 1,
        siCurveIsopointFwdTangentManipMode	= 2,
        siCurveIsopointBwdTangentManipMode	= 3,
        siCurveIsopointFwdThenBwdTangentManipMode	= 4,
        siCurveIsopointBwdThenFwdTangentManipMode	= 5,
        siCurveIsopointCVManipMode	= 6
    } 	siCurveIsopointManipMode;

/*! This enum specifies the type of alignment for a tangent of a curve knot in Softimage. */
typedef   
enum siCurveKnotTangentAlignment
    {
        siCurveKnotAlignFwdTangentWithBwd	= 0,		/*!< Align the forward tangent with the backward tangent. */
        siCurveKnotAlignBwdTangentWithFwd	= 1,		/*!< Align the backward tangent with the forward tangent. */
        siCurveKnotAlignFwdAndBwdTangentsTogether	= 2,		/*!< Rotate the forward and backward tangents by the same angle so they become aligned. */
        siCurveKnotLinearizeNextSegment	= 3,		/*!< Align all the control points between this bezier knot and the next one so the curve segment becomes a line. */
        siCurveKnotLinearizePrevSegment	= 4,		/*!< Align all the control points between this bezier knot and the previous one so the curve segment becomes a line. */
        siCurveKnotLinearizeBothSegments	= 5,		/*!< Equivalent of doing siCurveKnotLinearizePrevSegment and siCurveKnotLinearizeNextSegment. */
        siCurveKnotLinearizeInterSegments	= 6,		/*!< Align all the control points between consecutive knots. */
        siCurveKnotMakeCorner	= 7		/*!< Rotate both tangents enough to cause a significant discontinuity but with minimum curve distortion. */
    } 	siCurveKnotTangentAlignment;

/*! Specifies the rigid body dynamics engine used for simulation. There can be only one rigid body dynamics engine per <object idref="SimulationEnvironment"/>. */
typedef   
enum siRBDEngine
    {
        siPhysXEngine	= 0,		/*!< PhyX by NVIDIA engine */
        siOpenDynamicsEngine	= 1		/*!< ODE engine */
    } 	siRBDEngine;

/*! Keyable attribute types */
typedef   
enum siKeyableAttributeType
    {
        siKeyableAttributeClear	= 0,		/*!< Clear the keyable/non-keyable visible capabilities */
        siKeyableAttributeKeyable	= 1,		/*!< Set the keyable capability */
        siKeyableAttributeNonKeyableVisible	= 2		/*!< Set the non-keyable visible capability */
    } 	siKeyableAttributeType;

/*! Indicates the method to use for finding closest locations on a geometry. */
typedef   
enum siClosestLocationMethod
    {
        siClosestVertexOrKnot	= 0,
        siClosestSurface	= 1,
        siClosestSmoothedSurface	= 2,
        siClosestSurfaceRaycastIntersection	= 3		/*!< Finds the surface intersection through raycasting. */
    } 	siClosestLocationMethod;

/*! Indicates the method to use for computing normals on a geometry. These only apply to <object idref="PolygonMesh"/> objects (for <object idref="NurbsSurfaceMesh"/> the normal is always the exact surface normal). */
typedef   
enum siNormalComputationMethod
    {
        siInterpolatedVertexGeometricNormals	= 0,
        siInterpolatedVertexAngleBasedGeometricNormals	= 1,
        siInterpolatedShadingNormals	= 2,
        siInterpolatedAngleBasedNodeShadingNormals	= 3
    } 	siNormalComputationMethod;

/*! Type of line to use when intersecting a line with a geometry */
typedef   
enum siLineIntersectionType
    {
        siSemiLineIntersection	= 0,		/*!< Finds the intersection of a semi line with a geometry. */
        siLineIntersection	= 1,		/*!< Finds the intersection of an infinite line with a geometry. */
        siSegmentIntersection	= 2		/*!< Finds the intersection of a line segment with a geometry. */
    } 	siLineIntersectionType;

/*! This enumeration lists the allowed bit depths for each channel of an image with the specified channel types. Not all bit depths are allowed for all channel types. */
typedef   
enum siImageBitDepth
    {
        siImageBitDepthUnknown	= -1,		/*!< Unknown image bit depth. Only returned if an error occured. */
        siImageBitDepthInteger1	= 0,		/*!< Integer, 1 bit per channel. */
        siImageBitDepthInteger2	= 1,		/*!< Integer, 2 bits per channel. */
        siImageBitDepthInteger4	= 2,		/*!< Integer, 4 bits per channel. */
        siImageBitDepthInteger8	= 3,		/*!< Integer, 8 bits per channel. */
        siImageBitDepthInteger16	= 4,		/*!< Integer, 16 bits per channel. */
        siImageBitDepthInteger32	= 5,		/*!< Integer, 32 bits per channel. */
        siImageBitDepthFloat16	= 20,		/*!< Floating point, 16 bits per channel (half float). */
        siImageBitDepthFloat32	= 21		/*!< Floating point, 32 bits per channel (full float). */
    } 	siImageBitDepth;

/*! This enum lists the allowed channel types in writable images and framebuffers.  */
typedef   
enum siImageChannelType
    {
        siImageRGBAChannelType	= 0,		/*!< Combined color and alpha type. */
        siImageRGBChannelType	= 1,		/*!< Color only type. */
        siImageAlphaChannelType	= 2,		/*!< Alpha only type. */
        siImageIntensityChannelType	= 3,		/*!< RGB intensity type. */
        siImageRGBEChannelType	= 4,		/*!< Color with fourth channel as exponent type. */
        siImageDepthChannelType	= 5,		/*!< Depth value type. */
        siImageNormalChannelType	= 6,		/*!< Normal vector type. */
        siImageMotionChannelType	= 7,		/*!< Motion vector type. */
        siImageTagChannelType	= 8		/*!< Object tag type. */
    } 	siImageChannelType;

/*! This enumeration lists the allowed filters for user-selectable channel types in the UI. */
typedef   
enum siImageChannelFilter
    {
        siImageRGBAChannelFilter	= 1,		/*!< Combined color and alpha filter. */
        siImageRGBChannelFilter	= 2,		/*!< Color only filter. */
        siImageColorChannelFilter	= 3,		/*!< Color with optional alpha filter. */
        siImageAlphaChannelFilter	= 4,		/*!< Alpha only filter. */
        siImageIntensityChannelFilter	= 8,		/*!< RGB intensity filter. */
        siImageRGBEChannelFilter	= 16,		/*!< Color with fourth channel as exponent filter. */
        siImageDepthChannelFilter	= 32,		/*!< Depth value filter. */
        siImageNormalChannelFilter	= 64,		/*!< Normal vector filter. */
        siImageMotionChannelFilter	= 128,		/*!< Motion vector filter. */
        siImageTagChannelFilter	= 256,		/*!< Object tag filter. */
        siImageChannelFilterAll	= 511		/*!< All. */
    } 	siImageChannelFilter;

/*! Indicates the method to use for calculating the center of a bounding volume. */
typedef   
enum siVolumeCenterMethod
    {
        siVolumeCenterMethodCOG	= 0,		/*!< Use center of gravity (averaged location of all points). */
        siVolumeCenterMethodBBoxCenter	= 1,		/*!< Use center of the bounding box. */
        siVolumeCenterMethodObjectCenter	= 2		/*!< Use the object's local center. */
    } 	siVolumeCenterMethod;

/*! Indicates the method to use for calculating the long axis of a bounding cylinder. */
typedef   
enum siBoundingCapsuleMethod
    {
        siBoundingCapsuleMethodXAxis	= 0,		/*!< Use the object's local X axis */
        siBoundingCapsuleMethodYAxis	= 1,		/*!< Use the object's local Y axis */
        siBoundingCapsuleMethodZAxis	= 2,		/*!< Use the object's local Z axis */
        siBoundingCapsuleMethodBestAxis	= 3		/*!< Use the tightest fitting axis */
    } 	siBoundingCapsuleMethod;

/*! Specifies the source path being set for the <article idref="ctxt_siOnSourcePathChange">OnSourcePathChange</article> event. */
typedef   
enum siSourcePathType
    {
        siSourcePathImageSource	= 0,		/*!< An image source's source path is being changed. */
        siSourcePathWritableImageSource	= 1,		/*!< A writable image source's source path is being changed. */
        siSourcePathModelSource	= 3		/*!< A model source's source path is being changed. */
    } 	siSourcePathType;

/*! Describes whether <object idref="Model"/> is referenced, local (regular) or an instance. */
typedef   
enum siModelKind
    {
        siModelKind_Regular	= 0,		/*!< Regular local model (not referenced, specific to the scene). */
        siModelKind_Reference	= 1,		/*!< Referenced model (exported model linked to an external file). */
        siModelKind_Instance	= 2		/*!< Instanced model (instance of another model in the scene). */
    } 	siModelKind;

/*! Used as a convenient list of identifiers for the different viewports of the view manager. The first three are special identifiers for commands and methods that use the enumeration and do not refer to a specific viewport. */
typedef   
enum siViewport
    {
        siViewportFocussed	= -3,		/*!< Refers to the viewport that has the focus (indicated by a light gray border). */
        siViewportCurrent	= -2,		/*!< Refers to the viewport that is currently under the cursor. */
        siViewportAll	= -1,		/*!< Refers to all viewports. This value is only accepted as an argument if the command or method can use it. */
        siViewportA	= 0,		/*!< This identifies viewport A, which, in a 4-viewport view, is the upper left viewport (by default the top camera). */
        siViewportB	= 1,		/*!< This identifies viewport B, which, in a 4-viewport view, is the upper right viewport (by default the scene camera). */
        siViewportC	= 2,		/*!< This identifies viewport C, which, in a 4-viewport view, is the lower left viewport (by default the front camera). */
        siViewportD	= 3		/*!< This identifies viewport D, which, in a 4-viewport view, is the lower right viewport (by default the right camera). */
    } 	siViewport;

/*! This enumeration represents the list of display types for the render region. These display types affect any framebuffer being viewed. */
typedef   
enum siRenderRegionDisplayType
    {
        siRenderRegionDisplayRGBA	= 0,		/*!< Show the full RGB contents of the framebuffer, alpha composed on top of the viewport's contents. */
        siRenderRegionDisplayRGB	= 1,		/*!< Show the full RGB contents of the framebuffer with no alpha compositing. */
        siRenderRegionDisplayAlpha	= 2,		/*!< Show only the alpha channel of the framebuffer with no alpha compositing. */
        siRenderRegionDisplayRed	= 3,		/*!< Show only the red channel of the framebuffer with no alpha compositing. */
        siRenderRegionDisplayGreen	= 4,		/*!< Show only the green channel of the framebuffer with no alpha compositing. */
        siRenderRegionDisplayBlue	= 5		/*!< Show only the blue channel of the framebuffer with no alpha compositing. */
    } 	siRenderRegionDisplayType;

/*! Type of delta modification on a referenced model. */
typedef   
enum siModificationDeltaType
    {
        siModificationDeltaActiveResolution	= 0,		/*!< Store the active resolution of a sub-reference model.  */
        siModificationDeltaRemoveAnimation	= 1,		/*!< Store animation removals on the current reference model. */
        siModificationDeltaConstraint	= 2,		/*!< Store <object idref="Constraint"/>s. */
        siModificationDeltaUpVectorConstraint	= 3,		/*!< Store up vector constraints. */
        siModificationDeltaOperator	= 4,		/*!< Store <object idref="Operator"/>s. */
        siModificationDeltaExpression	= 5,		/*!< Store <object idref="Expression"/>s. */
        siModificationDeltaStaticValue	= 6,		/*!< Store static values. */
        siModificationDeltaFCurve	= 7,		/*!< Store <object idref="FCurve"/>s. */
        siModificationDeltaGroupRelation	= 8,		/*!< Store group relations (Objects added to a group, a layer or a pass). */
        siModificationDeltaCluster	= 9,		/*!< Clusters on Geometry. */
        siModificationDeltaClusterProperty	= 10,		/*!< Cluster Properties on Geometry. */
        siModificationDeltaProperty	= 11		/*!< Added Properties. */
    } 	siModificationDeltaType;

/*! Specifies the relative location where new node ports will be added. */
typedef   
enum siNodePortDataInsertionLocation
    {
        siNodePortDataInsertionLocationBegining	= 0,		/*!< Insert the new port as the first in the port group instances. */
        siNodePortDataInsertionLocationEnd	= ( siNodePortDataInsertionLocationBegining + 1 ) ,		/*!< Insert the new port as the last in the port group instances. */
        siNodePortDataInsertionLocationBefore	= ( siNodePortDataInsertionLocationEnd + 1 ) ,		/*!< Insert the new port just before the specified one. */
        siNodePortDataInsertionLocationAfter	= ( siNodePortDataInsertionLocationBefore + 1 ) 		/*!< Insert the new port just after the specified one. */
    } 	siNodePortDataInsertionLocation;

/*! Defines the possible actions that trigger calling the <article idref="cb_Property_PPGEvent" file="../custom/cus_self.fm">PPGEvent</article> callback function. */
typedef   
enum siPPGEventID
    {
        siUndefinedPPGEvent	= 0,		/*!< Unknown event. */
        siOnInit	= 1,
        siOnClosed	= 2,
        siParameterChange	= 3,
        siButtonClicked	= 4,
        siTabChange	= 5,
        siGridDataEvent	= 6
    } 	siPPGEventID;

/*! The process types that a rendering engine can perform. These types are used both when a render engine is registered, to indicate to Softimage which process type it can perform, and when the render engine's <article idref="cb_Renderer_Process">Process</article> callback is called to indicate which type of processing Softimage wants it to perform at that point. */
typedef   
enum siRenderProcessType
    {
        siRenderProcessRender	= 0,		/*!< The render engine can render an image. */
        siRenderProcessExportArchive	= 1,		/*!< The render engine can export the scene data given to an archive format for later off-line rendering. */
        siRenderProcessExportObjectArchive	= 2,		/*!< The render engine can export the objects given to an archive format to use with stand-in objects. */
        siRenderProcessGenerateRenderMap	= 3		/*!< The render engine can generate render maps. */
    } 	siRenderProcessType;

/*! Query codes that a rendering engine needs to respond to if it supports object archives and stand-ins, via registering itself with a <object idref="siRenderProcessType#siRenderProcessExportObjectArchive"/> process type, and multiple display bit depths. <br/> These query codes are used in conjunction with the renderer <article idref="callbacks#cb_Renderer_Query">query callback</article> and have no meaning outside of it since the query results are returned through specific context attributes. */
typedef   
enum siRenderQueryType
    {
        siRenderQueryArchiveIsValid	= 0,
        siRenderQueryArchiveProxies	= 1,		/*!< Returns the filenames of the display proxies for the given archive. */
        siRenderQueryArchiveBBox	= 2,		/*!< Returns the bounding box of a stand-in at a given frame. */
        siRenderQueryArchiveFrameRange	= 3,		/*!< Returns the frame range of a multi-frame object archive. */
        siRenderQueryDisplayBitDepths	= 4,		/*!< Returns a list of display bit depths that the rendering engine supports. */
        siRenderQueryWantDirtyList	= 5,		/*!< Returns a boolean indicating whether a dirty list is required or not. */
        siRenderQueryVersionString	= 6,
        siRenderQueryHasPreMulAlphaOutput	= 7,		/*!< Returns a boolean indicating whether the fragments returned from the renderer is pre-multiplied with alpha. This is used for color correction in the preview windows. */
        siRenderQuerySupportsProgressivePreview	= 8		/*!< Returns a boolean indicating whether the renderer supports a progressive render mode for previews. This also determines whether the user interfaces for the render region and render preview will have the "Progressive" toggle enabled. */
    } 	siRenderQueryType;

/*! Quality levels that a rendering engine's renderer properties can be set to, or queried for.<br/> These quality levels are used in conjunction with the renderer <article idref="callbacks#cb_Renderer_Quality">quality callback</article> and have no meaning outside of it since the quality levels are used through a specific context attribute. */
typedef   
enum siRenderQualityType
    {
        siRenderQualityTypeLowest	= 0,		/*!< Lowest quality level. Used only for very quick updates. */
        siRenderQualityTypeLow	= 1,		/*!< Low quality level. This is the default level for shader balls. */
        siRenderQualityTypeMedium	= 2,		/*!< Medium quality level. Normal working level for the render region. */
        siRenderQualityTypeHigh	= 3,		/*!< High quality level. Suitable for test renders. */
        siRenderQualityTypeHighest	= 4		/*!< Highest quality level. Suitable for final renders. */
    } 	siRenderQualityType;

/*! When a render engine registers, it provides a list of specific properties that Softimage should create for it. <br/> Note: At this time, only the render options property is supported. */
typedef   
enum siRenderPropertyType
    {
        siRenderPropertyOptions	= 0		/*!< A render options property for the rendering engine. */
    } 	siRenderPropertyType;

/*! Controls when the camera's shutter opens and closes when generating motion blur for render. */
typedef   
enum siRenderShutterType
    {
        siRenderShutterCenterOnFrame	= 0,		/*!< The mid-point of the shutter open period is centered on the frame being rendered, with the open and close shutter equally distant on either side of the frame. */
        siRenderShutterEndOnFrame	= 1,		/*!< The shutter should close on the current frame, and open at "shutter speed" frames before the current frame. */
        siRenderShutterStartOnFrame	= 2		/*!< The shutter should open on the current frame, and close at "shutter speed" frames past the current frame. */
    } 	siRenderShutterType;

/*! Controls how the render frame list is computed for passes. This enum can also be used for scene render options, but siRenderFrameSourceGlobalOptions is an invalid value.*/
typedef   
enum siRenderFrameSource
    {
        siRenderFrameSourceFrameRange	= 0,		/*!< Computes the frame list from a frame range with step. */
        siRenderFrameSourceFrameSet	= 1,		/*!< Computes the frame list from a frame set. */
        siRenderFrameSourceTimeline	= 2,		/*!< Use timeline's frame range. */
        siRenderFrameSourceGlobalOptions	= 3		/*!< Use a scene render options settings. */
    } 	siRenderFrameSource;

/*! Possible actions for the drag and drop notification. */
typedef   
enum siDragAndDropAction
    {
        siSourceDragAction	= 0,		/*!< Drag source validation. */
        siSourceDropAction	= 0x1		/*!< Source drop. */
    } 	siDragAndDropAction;

/*! Possible actions for the drag and drop 2 notification. */
typedef   
enum siDragAndDropAction2
    {
        siDragOverAction	= 0,		/*!< Drag over. The source object is being dragged over a supported target view (Scene Explorer, Viewport.) */
        siDropAction	= 1,		/*!< Drop. The source object was dropped into a supported target view (Scene Explorer, Viewport.) */
        siDragEnterAction	= 2,		/*!< Drag enter. The source object entered a supported target view (Scene Explorer, Viewport.) */
        siDragLeaveAction	= 3		/*!< Drag leave. The source object left a supported target view (Scene Explorer, Viewport.) */
    } 	siDragAndDropAction2;

/*! Bitmask of the possible mouse and keyboard modifiers for the drag and drop 2 event. */
typedef   
enum siDragAndDropModifiers
    {
        siDragModifierLButton	= 1,		/*!< The left mouse button is down. */
        siDragModifierRButton	= 2,		/*!< The right mouse button is down. */
        siDragModifierShift	= 4,		/*!< The shift key is down. */
        siDragModifierCtrl	= 8,		/*!< The control key is down. */
        siDragModifierMButton	= 16,		/*!< The middle mouse button is down. */
        siDragModifierAlt	= 32		/*!< The alt key is down. */
    } 	siDragAndDropModifiers;

/*! Possible mouse icons when a drag operation is accepted by a drag and drop 2 event. */
typedef   
enum siDropEffect
    {
        siDropEffectCopy	= 0x1,		/*!< Copy. The mouse icon will have a rectangle and a plus sign (+) under the standard icon. */
        siDropEffectMove	= 0x2,		/*!< Move. The mouse icon will have a rectangle under the standard icon. */
        siDropEffectLink	= 0x4		/*!< Link. The mouse icon will have a rectangle and a link sign (arrow) under the standard icon. */
    } 	siDropEffect;

/*! Sets the importance of an annotation message. */
typedef   
enum siAnnotationImportance
    {
        siAnnotationLow	= 0,		/*!< Low importance annotation. */
        siAnnotationNormal	= 1,		/*!< Normal importance annotation. */
        siAnnotationHigh	= 2		/*!< High importance annotation. */
    } 	siAnnotationImportance;

/*! Describes how the <object idref="ICEAttribute"/> data is defined. */
typedef   
enum siICEAttributeCategory
    {
        siICEAttributeCategoryUnknown	= 0,		/*!< Unknown category. */
        siICEAttributeCategoryBuiltin	= 1,		/*!< Built-in attribute. */
        siICEAttributeCategoryCustom	= 2		/*!< User-defined attribute. */
    } 	siICEAttributeCategory;

/*! Defines the threading models available for <link idref="ICENode" file="cpp"/> evaluation. */
typedef   
enum siICENodeThreadingModel
    {
        siICENodeUnknownThreading	= 0,		/*!< Unknown model. */
        siICENodeSingleThreading	= 1,		/*!< <article idref="cus_icenodes_ICENodeProcessingSingleThread" file="../custom/cus_icenodes.fm">Single-threading model</article>. */
        siICENodeMultiThreading	= 2,		/*!< <article idref="cus_icenodes_RegularCustomICENode" file="../custom/cus_icenodes.fm">Multi-threading model</article>. */
        siICENodeMultiEvaluationPhase	= 3		/*!< <article idref="cus_icenodes_MultiPhaseCustomICENode" file="../custom/cus_icenodes.fm">Multi-phase evaluation model</article>. */
    } 	siICENodeThreadingModel;

/*! Defines the particle shape types for rendering. */
typedef   
enum siICEShapeType
    {
        siICEShapeUnknown	= -1,		/*!< Unknown type. */
        siICEShapePoint	= 0,		/*!< Point type. */
        siICEShapeSegment	= 1,		/*!< Segment type. */
        siICEShapeDisc	= 2,		/*!< Disc type. */
        siICEShapeRectangle	= 3,		/*!< Unknown type. */
        siICEShapeSphere	= 4,		/*!< Sphere type. */
        siICEShapeBox	= 5,		/*!< Box type. */
        siICEShapeCylinder	= 6,		/*!< Cylinder type. */
        siICEShapeCapsule	= 7,		/*!< Capsule type. */
        siICEShapeCone	= 8,		/*!< Cone type. */
        siICEShapeBlob	= 9,		/*!< Blob type. */
        siICEShapeInstance	= 128,		/*!< Instance type. */
        siICEShapeReference	= 129		/*!< Reference type. */
    } 	siICEShapeType;

/*! Defines the type used in rigid body dynamics. */
typedef   
enum siICERBDType
    {
        siICERBDType_BBox	= 0,		/*!< Bounding Box type. */
        siICERBDType_ConvexHull	= 1,		/*!< Convex Hull type. */
        siICERBDType_ExactShape	= 2		/*!< Exact Shape type. */
    } 	siICERBDType;

/*! This enum specifies the render verbosity settings used when rendering or exporting passes. */
typedef   
enum siRenderVerbosity
    {
        siRenderVerbosityOff	= 0,		/*!< Verbose will be forced off even if the renderer verbosity options are activated. */
        siRenderVerbosityOn	= 1,		/*!< Verbose will be forced on even if the renderer verbosity options are deactivated. */
        siRenderVerbosityDefault	= 2		/*!< Verbose options from the renderer's options will be used. */
    } 	siRenderVerbosity;

/*! Describes the scrubbing state of the TimeTransport. If you seek to a specific time you use siTTScrubInactive. If you are implementing a timeline UI you would use siTTScrubActive. */
typedef   
enum siTimeTransportSeekMode
    {
        siTTScrubActive	= 0,		/*!< User is scrubbing time */
        siTTScrubInactive	= 1,		/*!< Time transport has been requested to move to a specific time. */
        siTTScrubJog	= 2		/*!< Time is scrubbing forward as a result of jogging */
    } 	siTimeTransportSeekMode;

/*! Enumerates the supported graphics drivers. */
typedef   
enum siGraphicDriver
    {
        siNullGraphicDriver	= 0,		/*!< No video driver */
        siOpenGL20	= 1,		/*!< OpenGL 2.0 */
        siOpenGL30	= 2,		/*!< OpenGL 3.0 */
        siDirectX9	= 3,		/*!< DirectX 9 */
        siDirectX10	= 4		/*!< DirectX 10 */
    } 	siGraphicDriver;

/*! Defines the dimension of a hardware surface. */
typedef   
enum siHardwareSurfaceDimension
    {
        siDefaultDimension	= 0,		/*!< Default dimension */
        si1D	= 1,		/*!< 1D */
        si2D	= 2,		/*!< 2D */
        si3D	= 3,		/*!< 3D */
        siRectangle	= 4,		/*!< 2D Rectangle */
        siCube	= 5		/*!< Cubic */
    } 	siHardwareSurfaceDimension;

/*! Defines the sharing capability of a resource. */
typedef   
enum siResourceSharing
    {
        siSharedResource	= 0,		/*!< Resource can be shared. */
        siExclusiveResource	= 1		/*!< Resource is exclusive and cannot be shared. */
    } 	siResourceSharing;

/*! Describes the standard vertex attribute hardware slot for a Realtime Shader. */
typedef   
enum siHardwareInputSemantic
    {
        siHardwareSemanticPosition	= 0,		/*!< Passed using glVertex */
        siHardwareSemanticNormal	= 1,		/*!< Passed using glNormal */
        siHardwareSemanticColor0	= 2,		/*!< Passed using glColor */
        siHardwareSemanticColor1	= 3,		/*!< Passed using glSecondaryColor */
        siHardwareSemanticTexcoord0	= 4,		/*!< Passed using glMultiTexCoord */
        siHardwareSemanticTexcoord1	= 5,		/*!< Passed using glMultiTexCoord */
        siHardwareSemanticTexcoord2	= 6,		/*!< Passed using glMultiTexCoord */
        siHardwareSemanticTexcoord3	= 7,		/*!< Passed using glMultiTexCoord */
        siHardwareSemanticTexcoord4	= 8,		/*!< Passed using glMultiTexCoord */
        siHardwareSemanticTexcoord5	= 9,		/*!< Passed using glMultiTexCoord */
        siHardwareSemanticTexcoord6	= 10,		/*!< Passed using glMultiTexCoord */
        siHardwareSemanticTexcoord7	= 11,		/*!< Passed using glMultiTexCoord */
        siHardwareSemanticTexcoord8	= 12,		/*!< Passed using glMultiTexCoord */
        siHardwareSemanticTexcoord9	= 13,		/*!< Passed using glMultiTexCoord */
        siHardwareSemanticTexcoord10	= 14,		/*!< Passed using glMultiTexCoord */
        siHardwareSemanticTexcoord11	= 15,		/*!< Passed using glMultiTexCoord */
        siHardwareSemanticTexcoord12	= 16,		/*!< Passed using glMultiTexCoord */
        siHardwareSemanticTexcoord13	= 17,		/*!< Passed using glMultiTexCoord */
        siHardwareSemanticTexcoord14	= 18,		/*!< Passed using glMultiTexCoord */
        siHardwareSemanticTexcoord15	= 19,		/*!< Passed using glMultiTexCoord */
        siHardwareSemanticAttr0	= 20,		/*!< Passed using glVertexAttribute */
        siHardwareSemanticAttr1	= 21,		/*!< Passed using glVertexAttribute */
        siHardwareSemanticAttr2	= 22,		/*!< Passed using glVertexAttribute */
        siHardwareSemanticAttr3	= 23,		/*!< Passed using glVertexAttribute */
        siHardwareSemanticAttr4	= 24,		/*!< Passed using glVertexAttribute */
        siHardwareSemanticAttr5	= 25,		/*!< Passed using glVertexAttribute */
        siHardwareSemanticAttr6	= 26,		/*!< Passed using glVertexAttribute */
        siHardwareSemanticAttr7	= 27,		/*!< Passed using glVertexAttribute */
        siHardwareSemanticAttr8	= 28,		/*!< Passed using glVertexAttribute */
        siHardwareSemanticAttr9	= 29,		/*!< Passed using glVertexAttribute */
        siHardwareSemanticAttr10	= 30,		/*!< Passed using glVertexAttribute */
        siHardwareSemanticAttr11	= 31,		/*!< Passed using glVertexAttribute */
        siHardwareSemanticAttr12	= 32,		/*!< Passed using glVertexAttribute */
        siHardwareSemanticAttr13	= 33,		/*!< Passed using glVertexAttribute */
        siHardwareSemanticAttr14	= 34,		/*!< Passed using glVertexAttribute */
        siHardwareSemanticAttr15	= 35,		/*!< Passed using glVertexAttribute */
        siHardwareSemanticFogcoord	= 36,		/*!< Passed using glFogCoord */
        siHardwareSemanticPsize	= 37,		/*!< Passed using glPointSize */
        siHardwareSemanticTangent	= 38,		/*!< Passed using glMultiTexCoord[6] */
        siHardwareSemanticBinormal	= 39,		/*!< Passed using glMultiTexCoord[7] */
        siHardwareSemanticWeight	= 40,		/*!< DirectX only (D3DDECLUSAGE_BLENDWEIGHT). */
        siHardwareSemanticIndice	= 41,		/*!< DirectX only (D3DDECLUSAGE_BLENDINDICES). */
        siHardwareSemanticTessfactor	= 42,		/*!< DirectX only (D3DDECLUSAGE_TESSFACTOR). */
        siHardwareSemanticDepth	= 43,		/*!< DirectX only (D3DDECLUSAGE_DEPTH). */
        siHardwareSemanticSample	= 44,		/*!< DirectX only (D3DDECLUSAGE_SAMPLE). */
        siHardwareSemanticMax	= 45		/*!< Max */
    } 	siHardwareInputSemantic;

/*! Indicates the plotting type to use when collapsing animation layers */
typedef   
enum siCollapseLayersPlottingType
    {
        siDefaultPlottingType	= 0,		/*!< Use the current user preference (animation.plotting_type) */
        siPreserveAnimation	= 1,		/*!< Preserve animation */
        siPreserveTangentHandles	= 2		/*!< Preserve tangent handles */
    } 	siCollapseLayersPlottingType;

/*! This indicates the action to perform when there is a conflict with a material */
typedef   
enum siMaterialConflictAction
    {
        siDefaultAction	= 0,		/*!< In batch mode, the material will be copied in the target material library. In interactive mode, the user is prompted to select an action to perform. */
        siShareMaterial	= 1,		/*!< Share the existing material */
        siCopyMaterial	= 2		/*!< Copy the material */
    } 	siMaterialConflictAction;

/*! Declares the supported hardware shader versions. */
typedef   
enum siHWShaderVersionID
    {
        siHWShaderV1	= 4		/*!< Hardware shader version 1 */
    } 	siHWShaderVersionID;

/*! Context flags for the <article idref="cus_graphicsequencer" file="../custom/cus_graphicsequencer.fm">Graphic Sequencer</article>.*/
typedef 
enum siXGSContextFlag
    {
        siXGSContextNormal	= ( 1L << 1 ) ,		/*!< Normal 3D viewport context. */
        siXGSContextCapture	= ( 1L << 2 ) ,		/*!< Capture rendering context. */
        siXGSContextHWRender	= ( 1L << 3 ) 		/*!< Hardware rendering context. */
    } 	siXGSContextFlag;

/*! XGS render flags for the <article idref="cus_graphicsequencer" file="../custom/cus_graphicsequencer.fm">Graphic Sequencer</article>.*/
typedef 
enum siXGSRenderFlag
    {
        siRenderDefault	= ( 1L << 1 ) ,		/*!< Render normally. */
        siRenderUnsorted	= ( 1L << 2 ) ,		/*!< Render unsorted objects. */
        siRenderSorted	= ( 1L << 3 ) ,		/*!< Render sorted objects (back to front). */
        siRenderSortedNear	= ( 1L << 4 ) ,		/*!< Render objects sorted by nearest point in bounding box. */
        siRenderSortedCenter	= ( 1L << 5 ) ,		/*!< Render objects sorted by center of bounding box. */
        siRenderSortedFar	= ( 1L << 6 ) ,		/*!< Render objects sorted by farthest point of bounding box. */
        siRenderSortFront	= ( 1L << 7 ) ,		/*!< Sorted objects are rendered from front to back (instead of the default back to front). */
        siRenderSelected	= ( 1L << 8 ) ,		/*!< Render selected objects. */
        siTexEnvReplace	= ( 1L << 9 ) ,		/*!< Replace texture. */
        siRenderNoRTSOverride	= ( 1L << 10 ) ,		/*!< Ignore realtime shader overrides when rendering. */
        siRenderNoAttributes	= ( 1L << 11 ) 		/*!< Don't display mesh attributes (vertices/edges/etc) */
    } 	siXGSRenderFlag;

/*! Determines the behavior and look of a <article idref="cus_displayhost" file="../custom/cus_displayhost.fm">Custom Display</article>.*/
typedef   
enum siCustomDisplayFlags
    {
        siSupportCommandMap	= ( 1L << 1 ) ,		/*!< Enables the Softimage keyboard shortcuts for this Custom Display. */
        siWindowNotifications	= ( 1L << 2 ) 		/*!< The Custom Display will get notified of all Window positining events such as resizing, moving, etc. */
    } 	siCustomDisplayFlags;

/*! Specifies the type of component data (vector3, boolean, color, etc.) on an <object idref="ICEAttribute"/>. */
typedef   
enum siComponentDataType
    {
        siComponentDataTypeBool	= ( 1L << 0 ) ,		/*!< A boolean */
        siComponentDataTypeLong	= ( 1L << 1 ) ,		/*!< A long integer */
        siComponentDataTypeFloat	= ( 1L << 2 ) ,		/*!< A floating point */
        siComponentDataTypeVector2	= ( 1L << 3 ) ,		/*!< A 2-point vector */
        siComponentDataTypeVector3	= ( 1L << 4 ) ,		/*!< A 3-point vector */
        siComponentDataTypeVector4	= ( 1L << 5 ) ,		/*!< A 4-point vector */
        siComponentDataTypeQuaternion	= ( 1L << 6 ) ,		/*!< A quaternion */
        siComponentDataTypeMatrix33	= ( 1L << 7 ) ,		/*!< A 3x3 matrix */
        siComponentDataTypeMatrix44	= ( 1L << 8 ) ,		/*!< A 4x4 matrix */
        siComponentDataTypeColor4	= ( 1L << 9 ) ,		/*!< An RGBA color */
        siComponentDataTypeRotation3	= ( 1L << 14 ) ,		/*!< A 3-component rotation */
        siComponentDataTypeShape	= ( 1L << 15 ) ,		/*!< Shape */
        siComponentDataTypeString	= ( 1L << 17 ) ,		/*!< String */
        siComponentDataTypeIcon	= ( 1L << 18 ) ,		/*!< Icon */
        siComponentDataTypeTopo	= ( 1L << 19 ) ,		/*!< Topo */
        siComponentDataTypeNone	= 0		/*!< None */
    } 	siComponentDataType;

/*! Specifies the context of component data (points, edges, etc.) on an <object idref="ICEAttribute"/>. */
typedef   
enum siComponentDataContext
    {
        siComponentDataContextSingleton	= ( 1L << 0 ) ,		/*!< One data per primitive. */
        siComponentDataContextComponent0D	= ( 1L << 1 ) ,		/*!< One data per point. */
        siComponentDataContextComponent1D	= ( 1L << 2 ) ,		/*!< One data per edge or line segment. */
        siComponentDataContextComponent2D	= ( 1L << 3 ) ,		/*!< One data per polygon or face. */
        siComponentDataContextComponent0D2D	= ( 1L << 4 ) ,		/*!< One sample point or polynode. */
        siComponentDataContextNone	= 0
    } 	siComponentDataContext;

/*! Specifies the structure of component data (single element or dynamic array) on an <object idref="ICEAttribute"/>. */
typedef   
enum siComponentDataStructure
    {
        siComponentDataStructureSingle	= ( 1L << 0 ) ,		/*!< One value per component data. */
        siComponentDataStructureDynamicArray	= ( 1L << 1 ) ,		/*!< Multiple values per component data. */
        siComponentDataStructureNone	= 0
    } 	siComponentDataStructure;

/*! Types of data allowed for render channels. All channel types, apart from the custom type, are interpreted by Softimage for display viewing. */
typedef   
enum siRenderChannelType
    {
        siRenderChannelUnknownType	= 0,		/*!< Unknown type. Only used as a return value in the case of an error. */
        siRenderChannelColorType	= 1,		/*!< Data is interpreted as a pre-multiplied RGB color image with an optional alpha channel. If no alpha is provided, the image is treated as fully opaque. */
        siRenderChannelGrayscaleType	= 2,		/*!< Data is interpreted as a single channel linear grayscale image. */
        siRenderChannelDepthType	= 3,		/*!< Data is interpreted as a single channel depth image, where a value of 0 indicates infinity and positive values increasing distance from the camera. */
        siRenderChannelNormalVectorType	= 4,		/*!< Data is interpreted as a three-channel, XYZ normalized vector. */
        siRenderChannelVectorType	= 5,		/*!< Data is interpreted as a three-channel, arbitrary XYZ vector or point in space. */
        siRenderChannelLabelType	= 6,		/*!< Data is interpreted as a single-channel, unique identifier value for each closest object visible to the camera. */
        siRenderChannelCustomType	= ( 1L << 31 ) 
    } 	siRenderChannelType;

/*! Defines the types of data that can be associated to a ICE node port connection. */
typedef   
enum siICENodeDataType
    {
        siICENodeDataBool	= ( 1L << 0 ) ,		/*!< <link idref="Boolean"/>. */
        siICENodeDataLong	= ( 1L << 1 ) ,		/*!< <link idref="Long"/>. */
        siICENodeDataFloat	= ( 1L << 2 ) ,		/*!< <link idref="Float"/>. */
        siICENodeDataVector2	= ( 1L << 3 ) ,		/*!< 2D vector. For the C++ API, this maps to <article idref="CVector2f" file="cpp_ref">CVector2f</article>. */
        siICENodeDataVector3	= ( 1L << 4 ) ,
        siICENodeDataVector4	= ( 1L << 5 ) ,
        siICENodeDataQuaternion	= ( 1L << 6 ) ,
        siICENodeDataMatrix33	= ( 1L << 7 ) ,
        siICENodeDataMatrix44	= ( 1L << 8 ) ,
        siICENodeDataColor4	= ( 1L << 9 ) ,
        siICENodeDataGeometry	= ( 1L << 10 ) ,		/*!< Geometry. Note: this data type is not available for Custom <object idref="ICENode"/>s output ports. */
        siICENodeDataLocation	= ( 1L << 11 ) ,		/*!< Data location. Note: this data type is not available for Custom <object idref="ICENode"/>s. */
        siICENodeDataExecute	= ( 1L << 12 ) ,		/*!< Execution logic. Note: this data type is not available for Custom <object idref="ICENode"/>s. */
        siICENodeDataReference	= ( 1L << 13 ) ,		/*!< Reference. Note: this data type is not available for Custom <object idref="ICENode"/>s. */
        siICENodeDataRotation	= ( 1L << 14 ) ,
        siICENodeDataShape	= ( 1L << 15 ) ,
        siICENodeDataCustomType	= ( 1L << 16 ) ,		/*!< Custom data type. */
        siICENodeDataString	= ( 1L << 17 ) ,		/*!< String type. */
        siICENodeDataIcon	= ( 1L << 18 ) ,		/*!< Icon. */
        siICENodeDataValue	= ( ( ( ( ( ( ( ( ( ( ( ( ( ( siICENodeDataBool | siICENodeDataLong )  | siICENodeDataFloat )  | siICENodeDataVector2 )  | siICENodeDataVector3 )  | siICENodeDataVector4 )  | siICENodeDataQuaternion )  | siICENodeDataRotation )  | siICENodeDataMatrix33 )  | siICENodeDataMatrix44 )  | siICENodeDataColor4 )  | siICENodeDataShape )  | siICENodeDataIcon )  | siICENodeDataCustomType )  | siICENodeDataString ) ,		/*!< Value (for internal use). */
        siICENodeDataInterface	= siICENodeDataGeometry,		/*!< Interface (for internal use). */
        siICENodeDataMultiComp	= ( ( ( ( ( ( ( siICENodeDataVector2 | siICENodeDataVector3 )  | siICENodeDataVector4 )  | siICENodeDataQuaternion )  | siICENodeDataRotation )  | siICENodeDataMatrix33 )  | siICENodeDataMatrix44 )  | siICENodeDataColor4 ) ,		/*!< Multi Comp (for internal use). */
        siICENodeDataArithmeticSupport	= ( ( ( ( ( ( ( ( siICENodeDataLong | siICENodeDataFloat )  | siICENodeDataVector2 )  | siICENodeDataVector3 )  | siICENodeDataVector4 )  | siICENodeDataQuaternion )  | siICENodeDataRotation )  | siICENodeDataMatrix33 )  | siICENodeDataMatrix44 ) ,		/*!< Arithmetic Support (for internal use). */
        siICENodeDataAny	= ( ( ( ( ( ( ( ( ( ( ( ( ( ( ( ( ( ( siICENodeDataBool | siICENodeDataLong )  | siICENodeDataFloat )  | siICENodeDataVector2 )  | siICENodeDataVector3 )  | siICENodeDataVector4 )  | siICENodeDataQuaternion )  | siICENodeDataRotation )  | siICENodeDataMatrix33 )  | siICENodeDataMatrix44 )  | siICENodeDataColor4 )  | siICENodeDataShape )  | siICENodeDataGeometry )  | siICENodeDataLocation )  | siICENodeDataReference )  | siICENodeDataExecute )  | siICENodeDataCustomType )  | siICENodeDataString )  | siICENodeDataIcon ) ,		/*!< Any supported type. */
        siICENodeInputDataAny	= ( ( ( ( ( ( ( ( ( ( ( ( ( ( siICENodeDataBool | siICENodeDataLong )  | siICENodeDataFloat )  | siICENodeDataVector2 )  | siICENodeDataVector3 )  | siICENodeDataVector4 )  | siICENodeDataQuaternion )  | siICENodeDataRotation )  | siICENodeDataMatrix33 )  | siICENodeDataMatrix44 )  | siICENodeDataColor4 )  | siICENodeDataShape )  | siICENodeDataCustomType )  | siICENodeDataString )  | siICENodeDataGeometry ) ,		/*!< Any supported type by the input ports on a Custom ICE Node. */
        siICENodeOutputDataAny	= ( ( ( ( ( ( ( ( ( ( ( ( ( siICENodeDataBool | siICENodeDataLong )  | siICENodeDataFloat )  | siICENodeDataVector2 )  | siICENodeDataVector3 )  | siICENodeDataVector4 )  | siICENodeDataQuaternion )  | siICENodeDataRotation )  | siICENodeDataMatrix33 )  | siICENodeDataMatrix44 )  | siICENodeDataColor4 )  | siICENodeDataShape )  | siICENodeDataCustomType )  | siICENodeDataString ) 		/*!< Any supported type by the output ports on a Custom ICE Node. This can be used as input port type definition. */
    } 	siICENodeDataType;

/*! Defines the way data are structured for ICE node connections: single data or dynamic array. */
typedef   
enum siICENodeStructureType
    {
        siICENodeStructureSingle	= ( 1L << 0 ) ,		/*!< Single data. */
        siICENodeStructureArray	= ( 1L << 1 ) ,		/*!< Array data. */
        siICENodeStructureAny	= ( siICENodeStructureSingle | siICENodeStructureArray ) 		/*!< Single or Array type. */
    } 	siICENodeStructureType;

/*! Defines the element set associated with the data for ICE node connections. In other words, which elements will be evaluated. */
typedef   
enum siICENodeContextType
    {
        siICENodeContextSingleton	= ( 1L << 0 ) ,		/*!< Only one element; for example, the transformation matrix of a geometry. */
        siICENodeContextComponent0D	= ( 1L << 1 ) ,		/*!< One element per vertex or point. */
        siICENodeContextComponent1D	= ( 1L << 2 ) ,		/*!< One element per edge or segment. */
        siICENodeContextComponent2D	= ( 1L << 3 ) ,		/*!< One element per polygon or subsurface. */
        siICENodeContextComponent0D2D	= ( 1L << 4 ) ,		/*!< One element per sampled point or polynode. */
        siICENodeContextElementGenerator	= ( 1L << 5 ) ,		/*!< Elements generated by a node. These are the special nodes that generate themselves their own evaluation context, and this context can be propagated to the connected nodes. They control how many elements will be evaluated, starting at their output. The number of output elements is not related to the number of components on the output geometry. */
        siICENodeContextSingletonOrComponent0D	= ( siICENodeContextSingleton | siICENodeContextComponent0D ) ,		/*!< One element or one element per vertex or point. */
        siICENodeContextSingletonOrComponent1D	= ( siICENodeContextSingleton | siICENodeContextComponent1D ) ,		/*!< One element or one element per edge or segment. */
        siICENodeContextSingletonOrComponent2D	= ( siICENodeContextSingleton | siICENodeContextComponent2D ) ,		/*!< One element or one element per polygon or subsurface. */
        siICENodeContextSingletonOrComponent0D2D	= ( siICENodeContextSingleton | siICENodeContextComponent0D2D ) ,		/*!< One element or one element per sampled point or polynode. */
        siICENodeContextSingletonOrElementGenerator	= ( siICENodeContextSingleton | siICENodeContextElementGenerator ) ,		/*!< One element or one element generated by a node. */
        siICENodeContextComponent0DOr1DOr2D	= ( ( siICENodeContextComponent0D | siICENodeContextComponent1D )  | siICENodeContextComponent2D ) ,		/*!< One element per: vertex or point; edge or segment; polygon or subsurface. */
        siICENodeContextNotSingleton	= ( ( ( ( siICENodeContextComponent0D | siICENodeContextComponent1D )  | siICENodeContextComponent2D )  | siICENodeContextComponent0D2D )  | siICENodeContextElementGenerator ) ,		/*!< Any element set except the singleton (one element only). */
        siICENodeContextAny	= ( ( ( ( ( siICENodeContextSingleton | siICENodeContextComponent0D )  | siICENodeContextComponent1D )  | siICENodeContextComponent2D )  | siICENodeContextComponent0D2D )  | siICENodeContextElementGenerator ) 		/*!< Any element set. */
    } 	siICENodeContextType;

/*! Determines the behavior of the auto-complete feature for a text editor widget control (see <object idref="siPPGControlType#siControlTextEditor"/>). */
typedef   
enum siAutoCompleteMode
    {
        siNone	= 0,		/*!< Turn off auto-complete. */
        siKeywords	= ( 1L << 1 ) ,		/*!< Auto-complete only keywords. */
        siCommands	= ( 1L << 2 ) 		/*!< Auto-complete names of installed commands. */
    } 	siAutoCompleteMode;

/*! Determines the availability of the File menu functions for a text editor widget control (<object idref="siPPGControlType#siControlTextEditor"/>). By default, if you display the toolbar (explicitly set the <object idref="siPPGItemAttribute#siUIToolbar"/> attribute to true), every function (entry) in the menu will be enabled. However, you can disable the loading and saving functions by setting the <object idref="siPPGItemAttribute#siUICapability"/> attribute to one of these values. <br/> Note: Using these values does not affect the Edit menu at all nor does it change the availability of the rest of the File menu functions (Recent Files, Preferences, and Print). */
typedef   
enum siTextEditorCapability
    {
        siNoSaveLoad	= 0,		/*!< Disables the following options in the File menu: New, Open, Save, Save As, Save Selection. */
        siCanSave	= ( 1L << 1 ) ,		/*!< Disables the following options in the File menu: Save, Save As, Save Selection. */
        siCanLoad	= ( 1L << 2 ) 		/*!< Disables the following options in the File menu: New, Open. */
    } 	siTextEditorCapability;

/*! Defines the supported features for a custom viewport. */
typedef   
enum siViewportFeature
    {
        siHardwareRendering	= ( 1L << 0 ) 		/*!< The viewport supports hardware rendering. */
    } 	siViewportFeature;

/*! Describes the playback mode for TimeTransport::Play() */
typedef   
enum siTimeTransportPlaybackMode
    {
        siTTPlaybackNormal	= 0,		/*!< Equivalent to Softimage TimeTransport real-time playback type.  */
        siTTPlaybackSlideShow	= 0x2		/*!< Equivalent to Softimage TimeTransport all playback type. */
    } 	siTimeTransportPlaybackMode;

/*! Describes the current state of the transport. You are pass a value in the TimeTransport callback which is a combination of these flags. */
typedef   
enum siTimeTransportState
    {
        siTTStateStop	= 0x1,		/*!< Stop */
        siTTStatePlay	= 0x4,		/*!< Play */
        siTTStateSeek	= 0x2000,		/*!< Seek */
        siTTStateTimeChange	= 0x4000,		/*!< Time change */
        siTTStateContextChange	= 0x8000,		/*!< Context change */
        siTTStateScrubChange	= 0x10000,		/*!< Scrub change */
        siTTStateSeekChange	= 0x20000,		/*!< Seek change */
        siTTStateDeviceChange	= 0x40000,		/*!< Device change */
        siTTStateFrameDropChange	= 0x80000		/*!< Frame drop change */
    } 	siTimeTransportState;

/*! Various flags that affect tool behaviour. */
typedef   
enum siToolCapabilities
    {
        siToolAllowNotifications	= 1
    } 	siToolCapabilities;

/*! ToolContext cursors. */
typedef   
enum siToolCursor
    {
        siArrowCursor	= 0,		/*!< Standard arrow cursor. */
        siCrossCursor	= 1,		/*!< Crosshair cursor. */
        siHandCursor	= 2,		/*!< Pointing hand cursor. */
        siPenCursor	= 3,		/*!< Pen cursor. */
        siDropperCursor	= 4,		/*!< Eye dropper cursor. */
        siSelectCursor	= 5,		/*!< Selection cursor. */
        siTranslateCursor	= 6,		/*!< Translate cursor. */
        siRotateCursor	= 7,		/*!< Rotate cursor. */
        siScaleCursor	= 8,		/*!< Scale cursor. */
        siZoomCursor	= 9,		/*!< Magnifying glass cursor. */
        siDragXYCursor	= 10,		/*!< 4-way arrow cursor. */
        siDragXCursor	= 11,		/*!< Horizontal arrow cursor. */
        siDragYCursor	= 12,		/*!< Vertical arrow cursor. */
        siDotCursor	= 13		/*!< Small dot cursor. */
    } 	siToolCursor;

/*! ToolContext text/menu alignment. */
typedef   
enum siAlignment
    {
        siLeftAlign	= 0,		/*!< Left-align horizontally. */
        siCenterAlign	= 1,		/*!< Center horizontally or vertically. */
        siRightAlign	= 2,		/*!< Right-align horizontally. */
        siTopAlign	= 0,		/*!< Top-align vertically. */
        siBottomAlign	= 2		/*!< Bottom-align vertically. */
    } 	siAlignment;

/*! ToolContext snapping type flags. */
typedef   
enum siSnapType
    {
        siSnapNone	= 0L,		/*!< Nothing was snapped. */
        siSnapPoint	= 0x1L,		/*!< Snap to points. */
        siSnapKnot	= 0x2L,		/*!< snap to knots. */
        siSnapCenter	= 0x4L,		/*!< Snap to centers. */
        siSnapMidPoint	= 0x8L,		/*!< Snap to mid-points. */
        siSnapBBox	= 0x20L,		/*!< Snap to bounding box points */
        siSnap0D	= 0xffffL,		/*!< Snap to any 0D feature. */
        siSnapEdge	= 0x10000L,		/*!< Snap to mesh edges. */
        siSnapCurve	= 0x20000L,		/*!< Snap to curves. */
        siSnapUIsocurve	= 0x40000L,		/*!< Snap to surface U curves. */
        siSnapVIsocurve	= 0x80000L,		/*!< Snap to surface V curves. */
        siSnapBoundary	= 0x100000L,		/*!< Snap to surface boundary curves. */
        siSnap1D	= 0xff0000L,		/*!< Snap to any 1D feature. */
        siSnapFace	= 0x1000000L,		/*!< Snap to mesh faces. */
        siSnapSurface	= 0x2000000L,		/*!< Snap to surfaces. */
        siSnap2D	= 0x3f000000L,		/*!< Snap to any 2D feature. */
        siSnapGrid	= 0x40000000L		/*!< Snap to grid. */
    } 	siSnapType;

/*! ToolContext picking mode flags. */
typedef   
enum siPickMode
    {
        siPickSingleObject	= 0,		/*!< Pick a single object. */
        siPickSingleSubComponent	= 1,		/*!< Pick a single subcomponent. */
        siPickMultipleObjects	= 2,		/*!< Pick multiple objects. */
        siPickMultipleSubComponents	= 3		/*!< Pick multiple subcomponents. */
    } 	siPickMode;

/*! ToolContext picking type flags. */
typedef   
enum siPickType
    {
        siPickRectangle	= 1,		/*!< Rectangle selection mode. */
        siPickRaycast	= 2,		/*!< Raycast selection mode. */
        siPickLasso	= 3,		/*!< Lasso selection mode. */
        siPickFreeform	= 4,		/*!< Freeform selection mode. */
        siPickRectangleRaycast	= 6		/*!< Rectangle-raycast selection mode. */
    } 	siPickType;

/*! This indicates how UVs copied from one object are pasted ontoa different object with the same topology.*/
typedef   
enum siPasteUVsMode
    {
        siDefaultPasteUVsMode	= 0,
        siPasteUVsUsingSourceIndices	= 1,		/*!< Paste the UVs using the source object UVs indices */
        siPasteUVsUsingTargetIndices	= 2		/*!< Paste the UVs using the target object UVs indices */
    } 	siPasteUVsMode;

/*! This indicates the mathematical mode when setting a new value to a current value. */
typedef   
enum siSetValueMode
    {
        siSetValueModeAbsolute	= 0,		/*!< Replaces the current value with the new value. */
        siSetValueModeAdditive	= 1,		/*!< Adds the new value to the current value. */
        siSetValueModeAddPercentage	= 2		/*!< Adds percentage of current value to current value. */
    } 	siSetValueMode;

/*! This indicates the render region refresh mode to use for render regions */
typedef   
enum siRenderRegionRefreshMode
    {
        siRenderRegionRefreshModeInteractive	= 0,		/*!< Always refresh the render region upon any render-relevant change in the scene */
        siRenderRegionRefreshModeCTRS	= 1,		/*!< Only refresh the render region refresh upon requests or changes to the camera, to the time or to the region state */
        siRenderRegionRefreshModeManual	= 2		/*!< Only refresh the render region upon explicit refresh requests */
    } 	siRenderRegionRefreshMode;

/*! This indicates the high-level editing (HLE) operation used in the FCurve Editor, when the HLE tool is enabled. */
typedef   
enum siHLEOperation
    {
        siHLEOperationAbsoluteOffset	= 0,		/*!< The HLE tool in the FCurve Editor uses the Absolute Offset operation. */
        siHLEOperationRelativeOffset	= 1,		/*!< The HLE tool in FCurve Editor uses the Relative Offset operation. */
        siHLEOperationAbsoluteScaling	= 2		/*!< The HLE tool in the FCurve Editor uses the Absolute Scaling operation. */
    } 	siHLEOperation;

/*! This indicates the operations available when processing external files. */
typedef   
enum siExternalFilesOperation
    {
        siDoNotCopyExtFiles	= 0,		/*!< The external files are not copied. */
        siCopyAllExtFiles	= 1,		/*!< All the external files are copied. */
        siCopyOnlyLocalExtFiles	= 2		/*!< Only the external files under the current project are copied. */
    } 	siExternalFilesOperation;

/*! Options to sort the items of the combo box. */
typedef   
enum siGridWidgetColumnComboItemsSort
    {
        siColumnComboItemsSortNone	= 0,		/*!< Uses the default order of the combo items specified. */
        siColumnComboItemsSortByLabel	= 1,		/*!< The combo items are sorted alphabetically order by the label. */
        siColumnComboItemsSortByValue	= 2		/*!< The combo items are sorted in ascending order by the value. */
    } 	siGridWidgetColumnComboItemsSort;


/*! Filters by boundaries (on active NURBS objects) */
extern XSIDECL const wchar_t* siBoundaryFilter;

/*! Filters by cameras */
extern XSIDECL const wchar_t* siCameraFilter;

/*! Filters by chain elements */
extern XSIDECL const wchar_t* siChainElementFilter;

/*! Filters by clusters */
extern XSIDECL const wchar_t* siClusterFilter;

/*! Filters by constraints */
extern XSIDECL const wchar_t* siConstraintFilter;

/*! Filters by control objects */
extern XSIDECL const wchar_t* siControlFilter;

/*! Filters by curves */
extern XSIDECL const wchar_t* siCurveFilter;

/*! Filters by edges (on active 3D objects) */
extern XSIDECL const wchar_t* siEdgeFilter;

/*! Filters by chain effectors */
extern XSIDECL const wchar_t* siEffectorFilter;

/*! Filters by any object */
extern XSIDECL const wchar_t* siGenericObjectFilter;

/*! Filters by any type of geometric 3D object */
extern XSIDECL const wchar_t* siGeometryFilter;

/*! Filters by groups */
extern XSIDECL const wchar_t* siGroupFilter;

/*! Filters by implicit primitives */
extern XSIDECL const wchar_t* siImplicitFilter;

/*! Filters by isopoints (on active 3D objects) */
extern XSIDECL const wchar_t* siIsopointFilter;

/*! Filters by knots (on active 3D objects) */
extern XSIDECL const wchar_t* siKnotFilter;

/*! Filters by implicit lattices */
extern XSIDECL const wchar_t* siLatticeFilter;

/*! Filters by layers */
extern XSIDECL const wchar_t* siLayerFilter;

/*! Filters by lights */
extern XSIDECL const wchar_t* siLightFilter;

/*! Filters by light partitions */
extern XSIDECL const wchar_t* siLightPartitionFilter;

/*! Filters by models */
extern XSIDECL const wchar_t* siModelFilter;

/*! Filters by nulls */
extern XSIDECL const wchar_t* siNullFilter;

/*! Filters by 3D objects only */
extern XSIDECL const wchar_t* siObjectFilter;

/*! Filters by object partitions */
extern XSIDECL const wchar_t* siObjectPartitionFilter;

/*! Filters by operators */
extern XSIDECL const wchar_t* siOperatorFilter;

/*! Filters by point clouds */
extern XSIDECL const wchar_t* siPointCloudFilter;

/*! Filters by points */
extern XSIDECL const wchar_t* siPointFilter;

/*! Filters by polygons */
extern XSIDECL const wchar_t* siPolygonFilter;

/*! Filters by polygon meshes */
extern XSIDECL const wchar_t* siPolyMeshFilter;

/*! Filters by primitives */
extern XSIDECL const wchar_t* siPrimitiveFilter;

/*! Filters by properties */
extern XSIDECL const wchar_t* siPropertyFilter;

/*! Filters by scenes */
extern XSIDECL const wchar_t* siSceneFilter;

/*! Filters by shaders. */
extern XSIDECL const wchar_t* siShaderFilter;

/*! Filters by skeleton joint properties */
extern XSIDECL const wchar_t* siSkeletonJointFilter;

/*! Filters by subcomponents */
extern XSIDECL const wchar_t* siSubComponentFilter;

/*! Filters by subsurfaces (on active 3D objects) */
extern XSIDECL const wchar_t* siSubSurfaceFilter;

/*! Filters by surface curves (on active 3D objects) */
extern XSIDECL const wchar_t* siSurfaceCurveFilter;

/*! Filters by surface meshes */
extern XSIDECL const wchar_t* siSurfaceMeshFilter;

/*! Filters by texture controls */
extern XSIDECL const wchar_t* siTextureControlFilter;

/*! Filters by trim curves (on active 3D objects) */
extern XSIDECL const wchar_t* siTrimCurveFilter;

/*! Filters by U isolines (on active 3D objects) */
extern XSIDECL const wchar_t* siUIsolineFilter;

/*! Filters by V isolines (on active 3D objects) */
extern XSIDECL const wchar_t* siVIsolineFilter;

/*! Filters by U knot curves (on active 3D objects) */
extern XSIDECL const wchar_t* siUKnotCurveFilter;

/*! Filters by V knot curves (on active 3D objects) */
extern XSIDECL const wchar_t* siVKnotCurveFilter;

/*! Filters by wave controls */
extern XSIDECL const wchar_t* siWaveFilter;

extern XSIDECL const wchar_t* siConditionalObjectFilter;


/*! TRUE to force the property dialogs to automatically pop up on object creation.
 *  Corresponds to User Preferences > Interaction > General > Automatically Popup Property Editors on Node Creation in the User Interface. 
 *  Note: This preference cannot be changed permanently via scripting. See <article idref="script_editor_RunningScripts#AutoInspect" file="files">Property Editor Automatic Inspection</article> for more information. */
extern XSIDECL const wchar_t* siAutoInspect;

/*! Toggle the Comp button in the Constrain panel.
 *  Possible values are:
 *  0 = off
 *  1 = on
 *  Corresponds to Constrain < Compensation in the main-menu. */
extern XSIDECL const wchar_t* siCompensationFlag;

/*! This preference enables or disables the custom command library cache. Disabling the cache allows developers to recompile an add-on library without having to unload it explicitly. Disabling a cache can drastically affect the performance of Softimage, therefore it is recommended to disable it only in the context of add-ons development. For performance reasons, the state of the cache is not persisted with the scene. By default the cache is enabled at startup, therefore users have to disable it at each session. */
extern XSIDECL const wchar_t* siCustomCommandLibCache;

/*! This preference enables or disables the custom operator library cache. Disabling the cache allows developers to recompile an add-on library without having to unload it explicitly. Disabling a cache can drastically affect the performance of Softimage, therefore it is recommended to disable it only in the context of add-ons development. For performance reasons, the state of the cache is not persisted with the scene. By default the cache is enabled at startup, therefore users have to disable it at each session. */
extern XSIDECL const wchar_t* siCustomOperatorLibCache;

/*! This preference enables or disables the custom display callback library cache. Disabling the cache allows developers to recompile a plug-in library without having to unload it explicitly. Disabling a cache can drastically affect the performance of Softimage, therefore it is recommended to disable it only in the context of add-ons development. For performance reasons, the state of the cache is not persisted with the scene. By default the cache is enabled at startup, therefore users have to disable it at each session. */
extern XSIDECL const wchar_t* siDisplayCallbackLibCache;

/*! This preference enables or disables the custom view library cache. Disabling the cache allows developers to recompile a plug-in library without having to unload it explicitly. Disabling a cache can drastically affect the performance of Softimage, therefore it is recommended to disable it only in the context of add-ons development. For performance reasons, the state of the cache is not persisted with the scene. By default the cache is enabled at startup, therefore users have to disable it at each session. */
extern XSIDECL const wchar_t* siDisplayLibCache;

/*! This preference enables or disables the custom display pass library cache. Disabling the cache allows developers to recompile a plug-in library without having to unload it explicitly. Disabling a cache can drastically affect the performance of Softimage, therefore it is recommended to disable it only in the context of add-ons development. For performance reasons, the state of the cache is not persisted with the scene. By default the cache is enabled at startup, therefore users have to disable it at each session. */
extern XSIDECL const wchar_t* siDisplayPassLibCache;

/*! This preference enables or disables the event library cache. Disabling the cache allows developers to recompile an add-on library without having to unload it explicitly. Disabling a cache can drastically affect the performance of Softimage, therefore it is recommended to disable it only in the context of add-ons development. For performance reasons, the state of the cache is not persisted with the scene. By default the cache is enabled at startup, therefore users have to disable it at each session. */
extern XSIDECL const wchar_t* siEventLibCache;

/*! This preference enables or disables the custom filter library cache. Disabling the cache allows developers to recompile a plug-in library without having to unload it explicitly. Disabling a cache can drastically affect the performance of Softimage, therefore it is recommended to disable it only in the context of add-ons development. For performance reasons, the state of the cache is not persisted with the scene. By default the cache is enabled at startup, therefore users have to disable it at each session. */
extern XSIDECL const wchar_t* siFilterLibCache;

/*! This preference enables or disables the custom menu library cache. Disabling the cache allows developers to recompile a plug-in library without having to unload it explicitly. Disabling a cache can drastically affect the performance of Softimage, therefore it is recommended to disable it only in the context of add-ons development. For performance reasons, the state of the cache is not persisted with the scene. By default the cache is enabled at startup, therefore users have to disable it at each session. */
extern XSIDECL const wchar_t* siMenuLibCache;

/*! This preference enables or disables the custom property library cache. Disabling the cache allows developers to recompile a plug-in library without having to unload it explicitly. Disabling a cache can drastically affect the performance of Softimage, therefore it is recommended to disable it only in the context of add-ons development. For performance reasons, the state of the cache is not persisted with the scene. By default the cache is enabled at startup, therefore users have to disable it at each session. */
extern XSIDECL const wchar_t* siPropertyLibCache;

/*! This preference enables or disables the Realtime shader library cache. Disabling the cache allows developers to recompile an add-on library without having to unload it explicitly. Disabling a cache can drastically affect the performance of Softimage, therefore it is recommended to disable it only in the context of add-ons development. For performance reasons, the state of the cache is not persisted with the scene. By default the cache is enabled at startup, therefore users have to disable it at each session. */
extern XSIDECL const wchar_t* siRTShaderLibCache;

/*! Set to True to enable command execution logging in the scripting history window. */
extern XSIDECL const wchar_t* siScrCommandLogEnabled;

/*! Use this user preference to specify the name of the file to use for logging commands and messages. Use siSrcCommandLogToFile to enable logging to file. */
extern XSIDECL const wchar_t* siScrCommandLogFileName;

/*! Use this user preference to get and set the maximum size for the scripting command/message log. */
extern XSIDECL const wchar_t* siScrCommandLogMaxSize;

/*! Set to True to log the scripting command/message to a file. Use siSrcCommandLogFileName to specify the log file name. */
extern XSIDECL const wchar_t* siScrCommandLogToFile;

/*! Set to True to allow the scripting command/message log to be of an unlimited size. */
extern XSIDECL const wchar_t* siScrCommandLogUnlimitedSize;

/*! Use this user preference to get and set the preferred scripting language. Possible values are: 
 *  "VBScript" 
 *   "JScript" 
 *  "PerlScript" 
 *  "Python"
 *   */
extern XSIDECL const wchar_t* siScrLanguage;

/*! Set to True to enable message logging in the scripting history window. */
extern XSIDECL const wchar_t* siScrMessageLogEnabled;

/*! Set to True to enable real-time message logging in the scripting history window. Messages are delivered immediately as they arrive instead of reported at the end of the command execution. */
extern XSIDECL const wchar_t* siScrRealTimeMessagingEnabled;

/*! Set to True to display time as frame. */
extern XSIDECL const wchar_t* siTimeDisplayFormatDisplayAsFrames;

/*! Set to True to use the default frame format or false for a user selected format for display purposes. */
extern XSIDECL const wchar_t* siTimeDisplayFormatDisplayUserFormat;

/*! Use this user preference to specify the user display frame format. The value will be corresponding to <object idref="siDisplayTimeFormat"/>. */
extern XSIDECL const wchar_t* siTimeDisplayFormatUserFormat;

/*! Use this user preference to specify the default frame format. The value will be corresponding to <object idref="siDefaultTimeFormat"/>. */
extern XSIDECL const wchar_t* siTimeFormatDefaultFrameFormat;

/*! Use this user preference to access the default frame rate. */
extern XSIDECL const wchar_t* siTimeFormatDefaultFrameRate;

/*! Set the Transformation Axis Mode. 
 *  The values to provide are actually bitmasks with bit zero for X, bit one for Y, and bit two for Z.
 *   */
extern XSIDECL const wchar_t* siTransformAxisMode;

/*! Set the Transformation Reference Mode. See <object idref="siRefMode"/> for a list of possible values. */
extern XSIDECL const wchar_t* siTransformRefMode;

/*! Use this user preference to specify the default current layout that will be used when starting Softimage. */
extern XSIDECL const wchar_t* siUILayoutDefault;

/*! Animation property sets */
extern XSIDECL const wchar_t* siAnimationKeyword;

/*! Cluster property sets */
extern XSIDECL const wchar_t* siClusterKeyword;

/*! Constraint property sets */
extern XSIDECL const wchar_t* siConstraintKeyword;

/*! ControlObject property sets */
extern XSIDECL const wchar_t* siControlObjectKeyword;

/*! Converter property sets */
extern XSIDECL const wchar_t* siConverterKeyword;

/*! Reuse keywords in property page dialog */
extern XSIDECL const wchar_t* siCurrentKeyword;

/*! Curve property sets */
extern XSIDECL const wchar_t* siCurveKeyword;

/*! CustomPSet property sets */
extern XSIDECL const wchar_t* siCustomPSetKeyword;

/*! Deform property sets */
extern XSIDECL const wchar_t* siDeformKeyword;

/*! Dynamics property sets */
extern XSIDECL const wchar_t* siDynamicsKeyword;

/*! Expressions property sets */
extern XSIDECL const wchar_t* siExpressionsKeyword;

/*! General property sets */
extern XSIDECL const wchar_t* siGeneralKeyword;

/*! Generator property sets */
extern XSIDECL const wchar_t* siGeneratorKeyword;

/*! Geometry property sets */
extern XSIDECL const wchar_t* siGeometryKeyword;

/*! Hair property sets */
extern XSIDECL const wchar_t* siHairKeyword;

/*! IK property sets */
extern XSIDECL const wchar_t* siIKKeyword;

/*! Kinematics property sets */
extern XSIDECL const wchar_t* siKinematicsKeyword;

/*! Mesh property sets */
extern XSIDECL const wchar_t* siMeshKeyword;

/*! Mixer property sets */
extern XSIDECL const wchar_t* siMixerKeyword;

/*! Modeling property sets */
extern XSIDECL const wchar_t* siModelingKeyword;

/*! Operators property sets */
extern XSIDECL const wchar_t* siOperatorsKeyword;

/*! Particle property sets */
extern XSIDECL const wchar_t* siParticleKeyword;

/*! Primitive property sets */
extern XSIDECL const wchar_t* siPrimitiveKeyword;

/*! Projection property sets */
extern XSIDECL const wchar_t* siProjectionKeyword;

/*! Rendering property sets */
extern XSIDECL const wchar_t* siRenderingKeyword;

/*! Simulation property sets */
extern XSIDECL const wchar_t* siSimulationKeyword;

/*! Surface property sets */
extern XSIDECL const wchar_t* siSurfaceKeyword;

/*! Topology Editor property sets */
extern XSIDECL const wchar_t* siTopologyEditorKeyword;

/*! Topology property sets */
extern XSIDECL const wchar_t* siTopologyKeyword;

/*! Viewing property sets */
extern XSIDECL const wchar_t* siViewingKeyword;

/*! boundary cluster */
extern XSIDECL const wchar_t* siBoundaryCluster;

/*! edge cluster */
extern XSIDECL const wchar_t* siEdgeCluster;

/*! face cluster */
extern XSIDECL const wchar_t* siFaceCluster;

/*! iso line U cluster */
extern XSIDECL const wchar_t* siIsoLineUCluster;

/*! iso line V cluster */
extern XSIDECL const wchar_t* siIsoLineVCluster;

/*! iso point cluster */
extern XSIDECL const wchar_t* siIsoPointCluster;

/*! knot cluster */
extern XSIDECL const wchar_t* siKnotCluster;

/*! knot curve U cluster */
extern XSIDECL const wchar_t* siKnotCurveUCluster;

/*! knot curve V cluster */
extern XSIDECL const wchar_t* siKnotCurveVCluster;

/*! polygon cluster */
extern XSIDECL const wchar_t* siPolygonCluster;

/*! polygon node cluster */
extern XSIDECL const wchar_t* siPolygonNodeCluster;

/*! sampled point cluster */
extern XSIDECL const wchar_t* siSampledPointCluster;

/*! subcurve cluster */
extern XSIDECL const wchar_t* siSubCurveCluster;

/*! subsurface cluster */
extern XSIDECL const wchar_t* siSubSurfaceCluster;

/*! surface curve cluster */
extern XSIDECL const wchar_t* siSurfaceCurveCluster;

/*! trim curve cluster */
extern XSIDECL const wchar_t* siTrimCurveCluster;

/*! vertex cluster */
extern XSIDECL const wchar_t* siVertexCluster;

/*! 0D Component family */
extern XSIDECL const wchar_t* si0DComponentFamily;

/*! 1D Component family */
extern XSIDECL const wchar_t* si1DComponentFamily;

/*! 2D Component family */
extern XSIDECL const wchar_t* si2DComponentFamily;

/*! 3D Object family */
extern XSIDECL const wchar_t* si3DObjectFamily;

/*! Assignment operator family */
extern XSIDECL const wchar_t* siAssignmentOperatorFamily;

/*! Camera family */
extern XSIDECL const wchar_t* siCameraFamily;

/*! Chain Element family */
extern XSIDECL const wchar_t* siChainElementFamily;

/*! Clusterable Component family */
extern XSIDECL const wchar_t* siClusterableComponentFamily;

/*! Cluster family */
extern XSIDECL const wchar_t* siClusterFamily;

/*! Constraint property family */
extern XSIDECL const wchar_t* siConstraintFamily;

/*! Contour Contrast shader family */
extern XSIDECL const wchar_t* siContourContrastShaderFamily;

/*! Contour shader family */
extern XSIDECL const wchar_t* siContourShaderFamily;

/*! Contour Store shader family */
extern XSIDECL const wchar_t* siContourStoreShaderFamily;

/*! Control Object family */
extern XSIDECL const wchar_t* siControlObjectFamily;

/*! Control Object Nurbs Texture family */
extern XSIDECL const wchar_t* siControlObjectNurbsTextureFamily;

/*! Control Object Texture family */
extern XSIDECL const wchar_t* siControlObjectTextureFamily;

/*! Control Object Texture Projection family */
extern XSIDECL const wchar_t* siControlObjectTextureProjectionFamily;

/*! Converter operator family */
extern XSIDECL const wchar_t* siConverterOperatorFamily;

/*! Curve Geometry family */
extern XSIDECL const wchar_t* siCurveFamily;

/*! Deform operator family */
extern XSIDECL const wchar_t* siDeformOperatorFamily;

/*! Displacement shader family */
extern XSIDECL const wchar_t* siDisplacementShaderFamily;

/*! Environment shader family */
extern XSIDECL const wchar_t* siEnvironmentShaderFamily;

/*! Fx Operator family */
extern XSIDECL const wchar_t* siFxOperatorFamily;

/*! Generator operator family */
extern XSIDECL const wchar_t* siGeneratorOperatorFamily;

/*! Geometry family */
extern XSIDECL const wchar_t* siGeometryFamily;

/*! Geometry shader family */
extern XSIDECL const wchar_t* siGeometryShaderFamily;

/*! Group family */
extern XSIDECL const wchar_t* siGroupFamily;

/*! Image Operator family */
extern XSIDECL const wchar_t* siImageOperatorFamily;

/*! Implicit Geometry family */
extern XSIDECL const wchar_t* siImplicitGeometryFamily;

/*! KineInfo property family */
extern XSIDECL const wchar_t* siKineInfoFamily;

/*! Lattice family */
extern XSIDECL const wchar_t* siLatticeFamily;

/*! Lens shader family */
extern XSIDECL const wchar_t* siLensShaderFamily;

/*! Light Photon shader family */
extern XSIDECL const wchar_t* siLightPhotonShaderFamily;

/*! Light Primitive family */
extern XSIDECL const wchar_t* siLightPrimitiveFamily;

/*! Light shader family */
extern XSIDECL const wchar_t* siLightShaderFamily;

/*! Marker operator family (mainly the construction regions) */
extern XSIDECL const wchar_t* siMarkerOperatorFamily;

/*! Material property family */
extern XSIDECL const wchar_t* siMaterialFamily;

/*! Material shader family */
extern XSIDECL const wchar_t* siMaterialShaderFamily;

/*! Mesh Geometry family */
extern XSIDECL const wchar_t* siMeshFamily;

/*! Null Primitive family */
extern XSIDECL const wchar_t* siNullPrimitiveFamily;

/*! Nurbs CurveList Geometry family */
extern XSIDECL const wchar_t* siNurbsCurveListFamily;

/*! Nurbs Surface Mesh Geometry family */
extern XSIDECL const wchar_t* siNurbsSurfaceMeshFamily;

/*! Operator family */
extern XSIDECL const wchar_t* siOperatorFamily;

/*! Output shader family */
extern XSIDECL const wchar_t* siOutputShaderFamily;

/*! Particle Control Object family */
extern XSIDECL const wchar_t* siParticleControlObjectFamily;

/*! Particle family */
extern XSIDECL const wchar_t* siParticleFamily;

/*! Pass family */
extern XSIDECL const wchar_t* siPassFamily;

/*! Patch Network family */
extern XSIDECL const wchar_t* siPatchNetworkFamily;

/*! Photon shader family */
extern XSIDECL const wchar_t* siPhotonShaderFamily;

/*! Planar Object family */
extern XSIDECL const wchar_t* siPlanarObjectFamily;

/*! Point Cloud Geometry family */
extern XSIDECL const wchar_t* siPointCloudFamily;

/*! Property family */
extern XSIDECL const wchar_t* siPropertyFamily;

/*! RealTime shader family */
extern XSIDECL const wchar_t* siRealTimeShaderFamily;

/*! Shader family */
extern XSIDECL const wchar_t* siShaderFamily;

/*! Shadow shader family */
extern XSIDECL const wchar_t* siShadowShaderFamily;

/*! SubComponent family */
extern XSIDECL const wchar_t* siSubComponentFamily;

/*! Surface Curve Geometry family */
extern XSIDECL const wchar_t* siSurfaceCurveFamily;

/*! Surface Geometry family */
extern XSIDECL const wchar_t* siSurfaceFamily;

/*! Texture shader family */
extern XSIDECL const wchar_t* siTextureShaderFamily;

/*! Topology operator family */
extern XSIDECL const wchar_t* siTopologyOperatorFamily;

/*! Virtual Component family */
extern XSIDECL const wchar_t* siVirtualComponentFamily;

/*! Virtual Curve family */
extern XSIDECL const wchar_t* siVirtualCurveFamily;

/*! Volume shader family */
extern XSIDECL const wchar_t* siVolumeShaderFamily;

/*! Two Points Constraint type */
extern XSIDECL const wchar_t* si2PntCnsType;

/*! 3D Object type */
extern XSIDECL const wchar_t* si3DObjectType;

/*! Three Points Constraint type */
extern XSIDECL const wchar_t* si3PntCnsType;

/*! Action Clip type (instanced action) */
extern XSIDECL const wchar_t* siActionClipType;

/*! Action type */
extern XSIDECL const wchar_t* siActionType;

/*! AddEdge Operator type (add an edge between an existing point and an existing edge) */
extern XSIDECL const wchar_t* siAddEdgeOpType;

/*! Add Mesh Points Operator type */
extern XSIDECL const wchar_t* siAddMeshPntOpType;

/*! Add Nurbs Curve Points Operator type */
extern XSIDECL const wchar_t* siAddNurbsCrvPntOpType;

/*! Add Nurbs Surface Points Operator type */
extern XSIDECL const wchar_t* siAddNurbsSrfPntOpType;

/*! Add Point Inside Curve Operator type */
extern XSIDECL const wchar_t* siAddPntMiddleCrvType;

/*! Add Point Inside Surface Operator type */
extern XSIDECL const wchar_t* siAddPntMiddleSrfOpType;

/*! Ambient Lighting type */
extern XSIDECL const wchar_t* siAmbientLightingType;

/*! Implicit Arc Primitive type */
extern XSIDECL const wchar_t* siArcPrimType;

/*! Attractor Control Object type (electric force) */
extern XSIDECL const wchar_t* siAttractorCtrlType;

/*! Automatic Cage Assignment Operator type */
extern XSIDECL const wchar_t* siAutoCageAssignOpType;

/*! Automatic Envelope Assignment Operator type */
extern XSIDECL const wchar_t* siAutoEnvAssignOpType;

/*! Ball Joint Constraint type */
extern XSIDECL const wchar_t* siBallJointCnsType;

/*! Base Path Constraint type */
extern XSIDECL const wchar_t* siBasePathCnsType;

/*! Bend Operator type */
extern XSIDECL const wchar_t* siBendOpType;

/*! Bevel Operator type (bevel geometry component) */
extern XSIDECL const wchar_t* siBevelOpType;

/*! Birail2Generators Operator Type */
extern XSIDECL const wchar_t* siBirail2GenOpType;

/*! Birail Operator type (generates a surface from 2 curves and a profile) */
extern XSIDECL const wchar_t* siBirailOpType;

/*! Blaster Operator type */
extern XSIDECL const wchar_t* siBlasterOpType;

/*! Blend Curves Operator type (create a blended curve between two existing curves) */
extern XSIDECL const wchar_t* siBlendCrvOpType;

/*! Blend Surfaces Operator type (blend surfaces) */
extern XSIDECL const wchar_t* siBlendSrfOpType;

/*! Boolean Generator Operator type */
extern XSIDECL const wchar_t* siBooleanGenOpType;

/*! Boolean Surface Operator type */
extern XSIDECL const wchar_t* siBooleanSrfTopoOpType;

/*! Bounding Plane Constraint type */
extern XSIDECL const wchar_t* siBPlaneCnsType;

/*! Bridge Op Operator type (bridge polygon) */
extern XSIDECL const wchar_t* siBridgeOpType;

/*! Brush Properties type */
extern XSIDECL const wchar_t* siBrushPropertiesType;

/*! Bulge Op Operator type */
extern XSIDECL const wchar_t* siBulgeOpType;

/*! Bounding Volume Constraint type */
extern XSIDECL const wchar_t* siBVolCnsType;

/*! Cage Deform Operator type */
extern XSIDECL const wchar_t* siCageDeformOpType;

/*! Camera Display type */
extern XSIDECL const wchar_t* siCamDispType;

/*! Camera Lens Flare type */
extern XSIDECL const wchar_t* siCameraLensFlareType;

/*! Camera Primitive type */
extern XSIDECL const wchar_t* siCameraPrimType;

/*! Camera Root primitive type */
extern XSIDECL const wchar_t* siCameraRootPrimType;

/*! CameraTxt Operator type (camera texture projection operator) */
extern XSIDECL const wchar_t* siCameraTxtOpType;

/*! Camera Visibility type */
extern XSIDECL const wchar_t* siCamVisType;

/*! CapOp type */
extern XSIDECL const wchar_t* siCapOpType;

/*! Center Operator type (center manipulation) */
extern XSIDECL const wchar_t* siCenterOpType;

/*! Chain Bone Primitive type */
extern XSIDECL const wchar_t* siChainBonePrimType;

/*! Chain End Effector Primitive type */
extern XSIDECL const wchar_t* siChainEffPrimType;

/*! Chain Root Primitive type */
extern XSIDECL const wchar_t* siChainRootPrimType;

/*! Implicit Circle Primitive type */
extern XSIDECL const wchar_t* siCirclePrimType;

/*! Clean Curve Operator type */
extern XSIDECL const wchar_t* siCleanCrvOpType;

/*! Clean Surface Operator type */
extern XSIDECL const wchar_t* siCleanSrfOpType;

/*! Cloth Operator type */
extern XSIDECL const wchar_t* siClothOpType;

/*! Cloth Property type */
extern XSIDECL const wchar_t* siClothPropType;

/*! Cloud Primitive type */
extern XSIDECL const wchar_t* siCloudPrimType;

/*! Cluster Color type */
extern XSIDECL const wchar_t* siClsColorType;

/*! Cluster Center Operator type (cluster center deformation) */
extern XSIDECL const wchar_t* siClsCtrOpType;

/*! Cluster Key type */
extern XSIDECL const wchar_t* siClsKeyType;

/*! Cluster Key Weight Map Operator type */
extern XSIDECL const wchar_t* siClsKeyWgtMapOpType;

/*! Cluster Pose type */
extern XSIDECL const wchar_t* siClsPoseType;

/*! Cluster Shape Combiner Operator type */
extern XSIDECL const wchar_t* siClsShapeCombinerOpType;

/*! Cluster Property UV Texture Projection type */
extern XSIDECL const wchar_t* siClsUVSpaceTxtType;

/*! CoBBoxSclOp type */
extern XSIDECL const wchar_t* siCoBBoxSclOpType;

/*! Collapse Operator type (collapse geometry component) */
extern XSIDECL const wchar_t* siCollapseOpType;

/*! Cone Primitive type */
extern XSIDECL const wchar_t* siConePrimType;

/*! CoPoseFCurveOp type */
extern XSIDECL const wchar_t* siCoPoseFCrvOpType;

/*! Copy Operator type (geometry copy operator for instances) */
extern XSIDECL const wchar_t* siCopyOpType;

/*! copyshape operator type */
extern XSIDECL const wchar_t* siCopyShapeOpType;

/*! CopyUVW Operator type */
extern XSIDECL const wchar_t* siCopyUVWOpType;

/*! Create Polygon Operator type */
extern XSIDECL const wchar_t* siCreatePolyOpType;

/*! Curve Constraint type */
extern XSIDECL const wchar_t* siCrvCnsType;

/*! Curve Creation Operator type */
extern XSIDECL const wchar_t* siCrvCreationOpType;

/*! CrvControlOp type */
extern XSIDECL const wchar_t* siCrvCtrlOpType;

/*! CrvCutOp type */
extern XSIDECL const wchar_t* siCrvCutOpType;

/*! Curve Deform Operator type */
extern XSIDECL const wchar_t* siCrvDeformOpType;

/*! NURBS Curve List Aggregate Primitive type */
extern XSIDECL const wchar_t* siCrvListAggregatePrimType;

/*! NURBS Curve List Primitive type */
extern XSIDECL const wchar_t* siCrvListPrimType;

/*! Curve To Mesh Converter Operator type (curve list to polygon mesh converter) */
extern XSIDECL const wchar_t* siCrvListToMeshOpType;

/*! Curve Net Operator type */
extern XSIDECL const wchar_t* siCrvNetOpType;

/*! Open/Close Curve Operator type (open or close a curve) */
extern XSIDECL const wchar_t* siCrvOpenCloseOpType;

/*! Reparameterize Curve Operator type */
extern XSIDECL const wchar_t* siCrvReparamOpType;

/*! Curve Shift Operator type */
extern XSIDECL const wchar_t* siCrvShiftOpType;

/*! Cube Primitive type */
extern XSIDECL const wchar_t* siCubePrimType;

/*! Custom Parameter Set type */
extern XSIDECL const wchar_t* siCustomParamSet;

/*! Cycleuvw Operator type */
extern XSIDECL const wchar_t* siCycleUVWType;

/*! Cylinder Primitive type */
extern XSIDECL const wchar_t* siCylinderPrimType;

/*! Deform By Spine Operator type (alternate envelope by spine operator) */
extern XSIDECL const wchar_t* siDeformBySpineOp2Type;

/*! Deform by spine operator type (envelope by spine) */
extern XSIDECL const wchar_t* siDeformBySpineOpType;

/*! Base Deform Operator type */
extern XSIDECL const wchar_t* siDeformOpType;

/*! Delete Component Operator type (delete geometry component) */
extern XSIDECL const wchar_t* siDeleteCompOpType;

/*! Delete Point From Curve Operator type */
extern XSIDECL const wchar_t* siDelPntCrvOpType;

/*! DGlow type */
extern XSIDECL const wchar_t* siDGlowType;

/*! Direction Constraint type */
extern XSIDECL const wchar_t* siDirCnsType;

/*! Disc Primitive type */
extern XSIDECL const wchar_t* siDiscPrimType;

/*! Display type */
extern XSIDECL const wchar_t* siDisplayType;

/*! Dissolve Component Operator type (dissolve geometry component) */
extern XSIDECL const wchar_t* siDissolveCompOpType;

/*! Distance Operator type */
extern XSIDECL const wchar_t* siDistanceOpType;

/*! Distance Constraint type */
extern XSIDECL const wchar_t* siDistCnsType;

/*! Dodecahedron Primitive type */
extern XSIDECL const wchar_t* siDodecahedronPrimType;

/*! Drag Control Primitive type */
extern XSIDECL const wchar_t* siDragCtrlPrimType;

/*! Eddy Control Primitive type */
extern XSIDECL const wchar_t* siEddyCtrlPrimType;

/*! Edit Polygon Operator type */
extern XSIDECL const wchar_t* siEditPolyOpType;

/*! Emission Property type */
extern XSIDECL const wchar_t* siEmissionPropType;

/*! Envelope Operator type */
extern XSIDECL const wchar_t* siEnvelopOpType;

/*! Envelope Selection Clusters Operator type */
extern XSIDECL const wchar_t* siEnvSelClsOpType;

/*! Envelope Weights type */
extern XSIDECL const wchar_t* siEnvWgtType;

/*! Explosion Operator type */
extern XSIDECL const wchar_t* siExplosionOpType;

/*! Extend Curve To Point Operator type */
extern XSIDECL const wchar_t* siExtendCrv2PntOpType;

/*! Extend To Curve Operator type (extend the surface to the selected curve) */
extern XSIDECL const wchar_t* siExtendToCrvOpType;

/*! Extract Curve Operator type */
extern XSIDECL const wchar_t* siExtractCrvOpType;

/*! Extract Curve Segment Operator type (extract a curve from a segment of an existing curve) */
extern XSIDECL const wchar_t* siExtractCrvSegOpType;

/*! Extract Polygons Operator type */
extern XSIDECL const wchar_t* siExtractPolyOpType;

/*! Extract Subcurve Operator type */
extern XSIDECL const wchar_t* siExtractSubCrvOpType;

/*! Extrusion 2 Profiles Operator type (extrude 2 profiles) */
extern XSIDECL const wchar_t* siExtrude2ProfsOpType;

/*! Extrude Component Axis Operator type (extrude geometry component) */
extern XSIDECL const wchar_t* siExtrudeCompAxisOpType;

/*! Extrude Component Operator type (extrude geometry component) */
extern XSIDECL const wchar_t* siExtrudeComponentOpType;

/*! Extrusion Operator type (extrude a curve to create a surface) */
extern XSIDECL const wchar_t* siExtrusionOpType;

/*! Fan Force Object type */
extern XSIDECL const wchar_t* siFanType;

/*! Fillet Curves Operator type (intersecting or not) */
extern XSIDECL const wchar_t* siFilletCrvOpType;

/*! Fillet Surfaces Operator type */
extern XSIDECL const wchar_t* siFilletSrfOpType;

/*! Fill Hole Operator type */
extern XSIDECL const wchar_t* siFillHoleOpType;

/*! Edge Filter Operator type */
extern XSIDECL const wchar_t* siFilterEdgeOpType;

/*! Polygon Filter Operator type */
extern XSIDECL const wchar_t* siFilterPolyOpType;

/*! Fit Curve Operator type (fit a new curve on to the selected curve) */
extern XSIDECL const wchar_t* siFitCrvOpType;

/*! Fit Surface Operator type (fit a new surface on to the selected surface) */
extern XSIDECL const wchar_t* siFitSrfOpType;

/*! Flip UVW Operator type */
extern XSIDECL const wchar_t* siFlipUVWOpType;

/*! Fluid Operator type */
extern XSIDECL const wchar_t* siFluidOpType;

/*! Fold Operator type */
extern XSIDECL const wchar_t* siFoldOpType;

/*! Four Sided Operator type */
extern XSIDECL const wchar_t* siFourSidedOpType;

/*! Fur Operator type (fur generator operator) */
extern XSIDECL const wchar_t* siFurOpType;

/*! Fur Primitive type */
extern XSIDECL const wchar_t* siFurPrimType;

/*! Fur Property type */
extern XSIDECL const wchar_t* siFurPropType;

/*! Fur Simulation Operator type */
extern XSIDECL const wchar_t* siFurSimOpType;

/*! Base Generator Operator type */
extern XSIDECL const wchar_t* siGeneratorOpType;

/*! Geometry Approximation type (tesselation) */
extern XSIDECL const wchar_t* siGeomApproxType;

/*! GeoShader Primitive Type */
extern XSIDECL const wchar_t* siGeoShaderPrimType;

/*! GeoTxtOp type (copy geometry xyz to uvw texture operator) */
extern XSIDECL const wchar_t* siGeoTxtOpType;

/*! Global Transform type */
extern XSIDECL const wchar_t* siGlobalType;

/*! Gravity Force Control Object type */
extern XSIDECL const wchar_t* siGravityCtrlType;

/*! Grid Primitive type */
extern XSIDECL const wchar_t* siGridPrimType;

/*! Group type (obsolete) */
extern XSIDECL const wchar_t* siGroup;

/*! Group type */
extern XSIDECL const wchar_t* siGroupType;

/*! Heal Operator type */
extern XSIDECL const wchar_t* siHealOpType;

/*! Heal UVW Operator type */
extern XSIDECL const wchar_t* siHealUVWOpType;

/*! Icosahedron Primitive type */
extern XSIDECL const wchar_t* siIcosahedronPrimType;

/*! Image Clip type */
extern XSIDECL const wchar_t* siImageClipType;

/*! Image Crop Operator type */
extern XSIDECL const wchar_t* siImageCropOpType;

/*! Image FX Operator type */
extern XSIDECL const wchar_t* siImageFXOpType;

/*! Image Object type */
extern XSIDECL const wchar_t* siImageObjectType;

/*! Image Source Operator type */
extern XSIDECL const wchar_t* siImageSourceOpType;

/*! Image Source type */
extern XSIDECL const wchar_t* siImageSourceType;

/*! Insert Curve Knot Operator type */
extern XSIDECL const wchar_t* siInsertCrvKnotOpType;

/*! Insert Surface Knot Operator type (inserts a knot in a nurbs surface) */
extern XSIDECL const wchar_t* siInsSrfKnotOpType;

/*! Intersect Surfaces Operator type (extract a curve from the intersection of two surfaces) */
extern XSIDECL const wchar_t* siIntersectSrfOpType;

/*! Inverse Curve Operator type (inverse curve direction) */
extern XSIDECL const wchar_t* siInvCrvOpType;

/*! Invert Polygon Operator type */
extern XSIDECL const wchar_t* siInvertPolyOpType;

/*! Name of the InvisiblePolygons cluster */
extern XSIDECL const wchar_t* siInvisiblePolygonsClusterName;

/*! Inverse Normals Operator type (inverse normals direction) */
extern XSIDECL const wchar_t* siInvSrfOpType;

/*! Kinematic Chain Properties type */
extern XSIDECL const wchar_t* siKineChainPropType;

/*! Kinematic Chain type */
extern XSIDECL const wchar_t* siKineChainType;

/*! Kinematic Constraint type */
extern XSIDECL const wchar_t* siKineCnsType;

/*! Kinematics Information type */
extern XSIDECL const wchar_t* siKineInfoType;

/*! Kinematic Joint type */
extern XSIDECL const wchar_t* siKineJointType;

/*! Lattice Operator type */
extern XSIDECL const wchar_t* siLatticeOpType;

/*! Lattice Primitive type */
extern XSIDECL const wchar_t* siLatticePrimType;

/*! Layers type */
extern XSIDECL const wchar_t* siLayersType;

/*! Light Lens Flare type */
extern XSIDECL const wchar_t* siLightLensFlareType;

/*! Light Primitive type */
extern XSIDECL const wchar_t* siLightPrimType;

/*! Line Constraint type */
extern XSIDECL const wchar_t* siLineCnsType;

/*! Local Transform type */
extern XSIDECL const wchar_t* siLocalType;

/*! Loft Generator Operator type */
extern XSIDECL const wchar_t* siLoftOpType;

/*! Component Map Operator type */
extern XSIDECL const wchar_t* siMapCompOpType;

/*! Mark Hard Edge/Vertex Operator type */
extern XSIDECL const wchar_t* siMarkHardEdgeVertexOpType;

/*! Material type */
extern XSIDECL const wchar_t* siMaterialType;

/*! Merge Curves Operator type */
extern XSIDECL const wchar_t* siMergeCrvOpType;

/*! Merge Meshes Operator type */
extern XSIDECL const wchar_t* siMergeMeshOpType;

/*! Merge Surfaces Operator type */
extern XSIDECL const wchar_t* siMergeSrfOpType;

/*! Mesh Local Subdivision Operator type */
extern XSIDECL const wchar_t* siMeshLocalSubdivisionOpType;

/*! Mesh Subdivision Operator type */
extern XSIDECL const wchar_t* siMeshSubdivOpType;

/*! Mesh Subdivide With Center Operator type (mesh subdivision with center) */
extern XSIDECL const wchar_t* siMeshSubdivWithCenterOpType;

/*! Mixer Animation Clip type */
extern XSIDECL const wchar_t* siMixerAnimClipType;

/*! Mixer Animation Action Track type */
extern XSIDECL const wchar_t* siMixerAnimTrackType;

/*! Mixer Audio Clip type */
extern XSIDECL const wchar_t* siMixerAudioClipType;

/*! Mixer Audio Track type */
extern XSIDECL const wchar_t* siMixerAudioTrackType;

/*! Mixer Property type */
extern XSIDECL const wchar_t* siMixerPropType;

/*! Mixer Shape Clip type */
extern XSIDECL const wchar_t* siMixerShapeClipType;

/*! Mixer Shape Track type */
extern XSIDECL const wchar_t* siMixerShapeTrackType;

/*! Mixer type (property) */
extern XSIDECL const wchar_t* siMixerType;

/*! 3D Model Clip type */
extern XSIDECL const wchar_t* siModelClipType;

/*! Model Null Primitive type */
extern XSIDECL const wchar_t* siModelNullPrimType;

/*! 3D Model type */
extern XSIDECL const wchar_t* siModelType;

/*! Motion Blur type */
extern XSIDECL const wchar_t* siMotionBlurType;

/*! Move Component Operator type */
extern XSIDECL const wchar_t* siMoveComponentOpType;

/*! N Points Constraint type */
extern XSIDECL const wchar_t* siNPntCnsType;

/*! Null Primitive type */
extern XSIDECL const wchar_t* siNullPrimType;

/*! Nurbs To Mesh Operator type */
extern XSIDECL const wchar_t* siNurbsToMeshOpType;

/*! Object To Cluster Constraint type */
extern XSIDECL const wchar_t* siObjClsCnsType;

/*! Obstacle Property type */
extern XSIDECL const wchar_t* siObstaclePropType;

/*! Octahedron Primitive type */
extern XSIDECL const wchar_t* siOctahedronPrimType;

/*! Offset Cluster Operator type */
extern XSIDECL const wchar_t* siOffsetClsOpType;

/*! Offset Curve Operator type */
extern XSIDECL const wchar_t* siOffsetCrvOpType;

/*! Offset Surface Operator type (offset a surface to create a new surface) */
extern XSIDECL const wchar_t* siOffsetSrfOpType;

/*! Open/Close Surface Operator type (open or close a surface) */
extern XSIDECL const wchar_t* siOpenCloseSrfOpType;

/*! Orientation Constraint type */
extern XSIDECL const wchar_t* siOriCnsType;

/*! Override type */
extern XSIDECL const wchar_t* siOverrideType;

/*! Particle decay type */
extern XSIDECL const wchar_t* siParDecayType;

/*! ParObstExtSparks type */
extern XSIDECL const wchar_t* siParObstExtSparksType;

/*! Particle Event type */
extern XSIDECL const wchar_t* siParticleEventType;

/*! Particles Operator type */
extern XSIDECL const wchar_t* siParticlesOpType;

/*! Path Constraint type */
extern XSIDECL const wchar_t* siPathCnsType;

/*! Pin Joint Constraint type */
extern XSIDECL const wchar_t* siPinJointCnsType;

/*! Plane Constraint type */
extern XSIDECL const wchar_t* siPlaneCnsType;

/*! Point CloudPrimitive type */
extern XSIDECL const wchar_t* siPointCloudPrimType;

/*! PolyMeshPNetOp type */
extern XSIDECL const wchar_t* siPolyMeshPNetOpType;

/*! Polygon Mesh type */
extern XSIDECL const wchar_t* siPolyMeshType;

/*! Position Constraint type */
extern XSIDECL const wchar_t* siPosCnsType;

/*! Pose Constraint type */
extern XSIDECL const wchar_t* siPoseCnsType;

/*! Project Curve Operator type (project a curve on to a surface) */
extern XSIDECL const wchar_t* siProjectCrvOpType;

/*! Proportional Modeling Operator type */
extern XSIDECL const wchar_t* siProportionalOpType;

/*! Proportional Volume Operator type */
extern XSIDECL const wchar_t* siPropVolumeOpType;

/*! Push Operator type */
extern XSIDECL const wchar_t* siPushOpType;

/*! QStretch Operator type (quick stretch) */
extern XSIDECL const wchar_t* siQStretchOpType;

/*! Randomize Operator type */
extern XSIDECL const wchar_t* siRandomizeOpType;

/*! Reference Plane type */
extern XSIDECL const wchar_t* siRefPlaneType;

/*! Relax UVW Operator type */
extern XSIDECL const wchar_t* siRelaxUVWOpType;

/*! Remove Curve Knot Operator type */
extern XSIDECL const wchar_t* siRemoveCrvKnotOpType;

/*! Remove Surface Knot Operator type (removes a knot from a nurbs surface) */
extern XSIDECL const wchar_t* siRemSrfKnotOpType;

/*! Render Map type */
extern XSIDECL const wchar_t* siRenderMapType;

/*! Revolution Operator type */
extern XSIDECL const wchar_t* siRevolutionOpType;

/*! Camera Rotoscopy type */
extern XSIDECL const wchar_t* siRotoscopeType;

/*! Scene Ambience type */
extern XSIDECL const wchar_t* siSceneAmbienceType;

/*! Scene Display Colors type */
extern XSIDECL const wchar_t* siSceneColorsType;

/*! Scaling Constraint type */
extern XSIDECL const wchar_t* siSclCnsType;

/*! SCM Fixer Operator type */
extern XSIDECL const wchar_t* siSCMFixerOpType;

/*! SCM Topology Operator type */
extern XSIDECL const wchar_t* siSCMTopologyOpType;

/*! Scripted Operator type (scripted operator host) */
extern XSIDECL const wchar_t* siScriptedOpType;

/*! Set Edge Crease Value Operator type */
extern XSIDECL const wchar_t* siSetEdgeCreaseValueOpType;

/*! Shape Action Compound Clip type (base compound clip) */
extern XSIDECL const wchar_t* siShapeActionCompoundClipType;

/*! Shape Action type */
extern XSIDECL const wchar_t* siShapeActionType;

/*! Viseme Action type */
extern XSIDECL const wchar_t* siVisemeActionType;

/*! Shear Operator type */
extern XSIDECL const wchar_t* siShearOpType;

/*! Shrink Wrap Operator type */
extern XSIDECL const wchar_t* siShrinkWrapOpType;

/*! Skeleton Controller Operator type */
extern XSIDECL const wchar_t* siSkelCtrlOpPropType;

/*! Smooth Envelope Weight Operator type */
extern XSIDECL const wchar_t* siSmoothEnvelopeWgtOpType;

/*! Snap Boundary Operator type */
extern XSIDECL const wchar_t* siSnapBoundOpType;

/*! Snap To Curves Operator type */
extern XSIDECL const wchar_t* siSnapCrvOpType;

/*! Snip Surface Operator type */
extern XSIDECL const wchar_t* siSnipSrfOpType;

/*! SoftBody Operator type */
extern XSIDECL const wchar_t* siSoftBodyOpType;

/*! Sphere Primitive type */
extern XSIDECL const wchar_t* siSpherePrimType;

/*! Deform by Spine Operator 2 type (alternate operator) */
extern XSIDECL const wchar_t* siSpineDefOp2Type;

/*! Deform by Spine Operator type */
extern XSIDECL const wchar_t* siSpineDefOpType;

/*! Spine Weight Map Operator 3 type */
extern XSIDECL const wchar_t* siSpineWgtMapOp3Type;

/*! Deform by Spine Weight Map Operator 4 type */
extern XSIDECL const wchar_t* siSpineWgtMapOp4Type;

/*! Implicit Spiral Primitive type */
extern XSIDECL const wchar_t* siSpiralPrimType;

/*! Split Edge Operator type (split some edges) */
extern XSIDECL const wchar_t* siSplitEdgeOpType;

/*! Split Polygon Operator type (split some polygons) */
extern XSIDECL const wchar_t* siSplitPolyOpType;

/*! Spot Interest Primitive type */
extern XSIDECL const wchar_t* siSpotInterestPrimType;

/*! Spot Root Primitive type */
extern XSIDECL const wchar_t* siSpotRootPrimType;

/*! Implicit Square Primitive type */
extern XSIDECL const wchar_t* siSquarePrimType;

/*! Surface Constraint type */
extern XSIDECL const wchar_t* siSrfCnsType;

/*! Surface Curve Inverse Operator type */
extern XSIDECL const wchar_t* siSrfCrvInverseOpType;

/*! Surface Curve Shift Operator type */
extern XSIDECL const wchar_t* siSrfCrvShiftOpType;

/*! SrfControlOp type */
extern XSIDECL const wchar_t* siSrfCtrlOpType;

/*! Surface Deform Operator type */
extern XSIDECL const wchar_t* siSrfDefOpType;

/*! NURBS Surface Mesh Primitive type */
extern XSIDECL const wchar_t* siSrfMeshPrimType;

/*! SurfacePQ Operator type */
extern XSIDECL const wchar_t* siSrfPQOpType;

/*! Reparameterize Surface Operator type */
extern XSIDECL const wchar_t* siSrfReparamOpType;

/*! Surface Shift Operator type */
extern XSIDECL const wchar_t* siSrfShiftOpType;

/*! Surface Subdivision Operator type */
extern XSIDECL const wchar_t* siSrfSubdivisionOpType;

/*! Surface UV Control Operator type (Nurbs UV control) */
extern XSIDECL const wchar_t* siSrfUVCtrlOpType;

/*! Stand-in Primitive type */
extern XSIDECL const wchar_t* siStandInPrimType;

/*! Start Offset Operator type */
extern XSIDECL const wchar_t* siStartOffsetOpType;

/*! Stitch Curve To Curve Operator type (stitch curves together) */
extern XSIDECL const wchar_t* siStitchCrvToCrvOpType;

/*! Stitch Curve To Surface Operator type */
extern XSIDECL const wchar_t* siStitchCrvToSrfOpType;

/*! Stitch Surfaces Operator type (stitch surfaces and curves together) */
extern XSIDECL const wchar_t* siStitchSrfOpType;

/*! Gap Stroke Operator type */
extern XSIDECL const wchar_t* siStrokeOpType;

/*! Subcomponents type */
extern XSIDECL const wchar_t* siSubCompType;

/*! Subdivide Edge Operator type */
extern XSIDECL const wchar_t* siSubdivEdgeOpType;

/*! Subdivide Polygon Operator type */
extern XSIDECL const wchar_t* siSubdivPolyOpType;

/*! Swap Surface UVs Operator type */
extern XSIDECL const wchar_t* siSwapSrfUVOpType;

/*! Symmetrize Polygon Operator type */
extern XSIDECL const wchar_t* siSymmetrizePolygon;

/*! Symmetry Constraint type */
extern XSIDECL const wchar_t* siSymmetryCnsType;

/*! Symmetry Map Genrator Operator type */
extern XSIDECL const wchar_t* siSymmetryMapOpType;

/*! Symmetry Map type */
extern XSIDECL const wchar_t* siSymmetryMapType;

/*! Synoptic View type */
extern XSIDECL const wchar_t* siSynopticViewType;

/*! Taper Operator type */
extern XSIDECL const wchar_t* siTaperOpType;

/*! Tetrahedron Primitive type */
extern XSIDECL const wchar_t* siTetrahedronPrimType;

/*! Text To CurveList Operator type */
extern XSIDECL const wchar_t* siTextToCrvListOpType;

/*! Torus Primitive type */
extern XSIDECL const wchar_t* siTorusPrimType;

/*! Trajectory Constraint type */
extern XSIDECL const wchar_t* siTrajCnsType;

/*! Transform Setup type */
extern XSIDECL const wchar_t* siTransformSetupType;

/*! Turbulence Control Primitive type */
extern XSIDECL const wchar_t* siTurbulenceCtrlPrimType;

/*! Twist Operator type */
extern XSIDECL const wchar_t* siTwistOpType;

/*! Texture Map type */
extern XSIDECL const wchar_t* siTxtMapType;

/*! Texture Projection Operator type */
extern XSIDECL const wchar_t* siTxtOpType;

/*! Texture Support type */
extern XSIDECL const wchar_t* siTxtSupportType;

/*! Up Vector Constraint type */
extern XSIDECL const wchar_t* siUpVctCnsType;

/*! User Motion Property type */
extern XSIDECL const wchar_t* siUserMotionType;

/*! User Normal Property type */
extern XSIDECL const wchar_t* siUserNormalType;

/*! UV Projection Definition type (definition of how to perform a texture projection) */
extern XSIDECL const wchar_t* siUVProjDefType;

/*! Vertex Color type */
extern XSIDECL const wchar_t* siVertexcolorType;

/*! Visibility type */
extern XSIDECL const wchar_t* siVisibilityType;

/*! Volume Deform type (implicit sphere volume) */
extern XSIDECL const wchar_t* siVolumeDeformType;

/*! Volumic Light Scene Local Property Set type */
extern XSIDECL const wchar_t* siVolumicLightSceneType;

/*! Volumic Light Effect type */
extern XSIDECL const wchar_t* siVolumicLightType;

/*! Vortex Control Object type (magnetic force) */
extern XSIDECL const wchar_t* siVortexCtrlType;

/*! Vertex Color Painter Operator type */
extern XSIDECL const wchar_t* siVtxColPainterOpType;

/*! Vertex Color Property Generator Operator type */
extern XSIDECL const wchar_t* siVtxColPropOpType;

/*! Wave Control Object type */
extern XSIDECL const wchar_t* siWaveCtrlType;

/*! Wave Operator type */
extern XSIDECL const wchar_t* siWaveOpType;

/*! Weld Edges Operator type (weld pair of edges together) */
extern XSIDECL const wchar_t* siWeldEdgesOpType;

/*! Weld Points Operator type (weld two points together) */
extern XSIDECL const wchar_t* siWeldPntOpType;

/*! Weight Map Connection Operator type */
extern XSIDECL const wchar_t* siWgtMapCnxOpType;

/*! Weight Map Generator Operator type */
extern XSIDECL const wchar_t* siWgtMapOpType;

/*! Weight Maps Mixer Operator type */
extern XSIDECL const wchar_t* siWgtMapsMixOpType;

/*! Weight Map type */
extern XSIDECL const wchar_t* siWgtMapType;

/*! Weight Painter Operator type */
extern XSIDECL const wchar_t* siWgtPainterOpType;

/*! Wind Force Object type */
extern XSIDECL const wchar_t* siWindType;

/*! Weight Stroke Operator type */
extern XSIDECL const wchar_t* siWtStrokeOpType;

extern XSIDECL const wchar_t* siControlBitmap;


extern XSIDECL const wchar_t* siControlBoolean;


extern XSIDECL const wchar_t* siControlButton;


extern XSIDECL const wchar_t* siControlCheck;


extern XSIDECL const wchar_t* siControlCombo;


extern XSIDECL const wchar_t* siControlEdit;


extern XSIDECL const wchar_t* siControlFCurve;


extern XSIDECL const wchar_t* siControlFilePath;


extern XSIDECL const wchar_t* siControlFolder;


/*! A control that shows a fully featured gradient editor. */
extern XSIDECL const wchar_t* siControlGradient;

extern XSIDECL const wchar_t* siControlGrid;


extern XSIDECL const wchar_t* siControlIconList;


extern XSIDECL const wchar_t* siControlImageClip;


extern XSIDECL const wchar_t* siControlListBox;


extern XSIDECL const wchar_t* siControlNumber;


extern XSIDECL const wchar_t* siControlRadio;


extern XSIDECL const wchar_t* siControlRGB;


extern XSIDECL const wchar_t* siControlRGBA;


extern XSIDECL const wchar_t* siControlStatic;


extern XSIDECL const wchar_t* siControlString;


extern XSIDECL const wchar_t* siControlSynoptic;


extern XSIDECL const wchar_t* siControlTextEditor;


/*! A control that shows a texture space combo box. */
extern XSIDECL const wchar_t* siControlTextureSpace;

extern XSIDECL const wchar_t* siUIAlignCenter;


extern XSIDECL const wchar_t* siUIAlignLeft;


extern XSIDECL const wchar_t* siUIAlignRight;


extern XSIDECL const wchar_t* siUIAudioFile;


extern XSIDECL const wchar_t* siUICaption;


extern XSIDECL const wchar_t* siUIColumnCnt;


extern XSIDECL const wchar_t* siUIColumnGap;


extern XSIDECL const wchar_t* siUIContinue;


extern XSIDECL const wchar_t* siUICX;


extern XSIDECL const wchar_t* siUICY;


extern XSIDECL const wchar_t* siUIDecimals;


extern XSIDECL const wchar_t* siUIFCurveColorNonBijective;


extern XSIDECL const wchar_t* siUIFCurveGhosting;


extern XSIDECL const wchar_t* siUIFCurveGridSpaceX;


extern XSIDECL const wchar_t* siUIFCurveGridSpaceY;


extern XSIDECL const wchar_t* siUIFCurveLabelX;


extern XSIDECL const wchar_t* siUIFCurveLabelY;


extern XSIDECL const wchar_t* siUIFCurveNoGrid;


extern XSIDECL const wchar_t* siUIFCurveNoRulerX;


extern XSIDECL const wchar_t* siUIFCurveNoRulerY;


extern XSIDECL const wchar_t* siUIFCurveShowTimeCursor;


extern XSIDECL const wchar_t* siUIFCurveSnapX;


extern XSIDECL const wchar_t* siUIFCurveSnapY;


extern XSIDECL const wchar_t* siUIFCurveViewMaxX;


extern XSIDECL const wchar_t* siUIFCurveViewMaxY;


extern XSIDECL const wchar_t* siUIFCurveViewMinX;


extern XSIDECL const wchar_t* siUIFCurveViewMinY;


extern XSIDECL const wchar_t* siUIFileFilter;


extern XSIDECL const wchar_t* siUIFileMustExist;


extern XSIDECL const wchar_t* siUIFilePath;


extern XSIDECL const wchar_t* siUIImageFile;


extern XSIDECL const wchar_t* siUIInitialDir;


extern XSIDECL const wchar_t* siUILabel;


extern XSIDECL const wchar_t* siUILabelMinPixels;


extern XSIDECL const wchar_t* siUILabelPercentage;


extern XSIDECL const wchar_t* siUILineCnt;


extern XSIDECL const wchar_t* siUILineGap;


extern XSIDECL const wchar_t* siUILogarithmic;


extern XSIDECL const wchar_t* siUIMultiSelectionListBox;


extern XSIDECL const wchar_t* siUINoLabel;


extern XSIDECL const wchar_t* siUINoSlider;


extern XSIDECL const wchar_t* siUIOpenFile;


extern XSIDECL const wchar_t* siUISelectionColor;


extern XSIDECL const wchar_t* siUIShowClip;


extern XSIDECL const wchar_t* siUIShowFrame;


extern XSIDECL const wchar_t* siUIButtonDisable;


extern XSIDECL const wchar_t* siUIGradientConDivot;


extern XSIDECL const wchar_t* siUIGradientMaxMarker;


extern XSIDECL const wchar_t* siUIGradientMidPoint;


extern XSIDECL const wchar_t* siUIGradientType;


extern XSIDECL const wchar_t* siUIGridColumnWidths;


extern XSIDECL const wchar_t* siUIGridHideColumnHeader;


extern XSIDECL const wchar_t* siUIGridHideRowHeader;


extern XSIDECL const wchar_t* siUIGridLockColumnHeader;


extern XSIDECL const wchar_t* siUIGridLockRowHeader;


extern XSIDECL const wchar_t* siUIGridReadOnlyColumns;


extern XSIDECL const wchar_t* siUIGridSelectionMode;


extern XSIDECL const wchar_t* siUIGridShowColumns;


extern XSIDECL const wchar_t* siUIGridLockRowHeight;


extern XSIDECL const wchar_t* siUIGridLockColumnWidth;


extern XSIDECL const wchar_t* siUIGridThumbnailSize;


extern XSIDECL const wchar_t* siUIStyle;


extern XSIDECL const wchar_t* siUISubFolder;


extern XSIDECL const wchar_t* siUISyncSlider;


extern XSIDECL const wchar_t* siUIThumbWheel;


extern XSIDECL const wchar_t* siUITreadmill;


extern XSIDECL const wchar_t* siUIItems;


extern XSIDECL const wchar_t* siUIType;


extern XSIDECL const wchar_t* siUIUseSelectionIcon;


extern XSIDECL const wchar_t* siUIValueOnly;


extern XSIDECL const wchar_t* siUIWidthPercentage;


extern XSIDECL const wchar_t* siUILineNumbering;


extern XSIDECL const wchar_t* siUIFolding;


extern XSIDECL const wchar_t* siUIBackgroundColor;


extern XSIDECL const wchar_t* siUIForegroundColor;


extern XSIDECL const wchar_t* siUIFont;


extern XSIDECL const wchar_t* siUICommentColor;


extern XSIDECL const wchar_t* siUIPreprocessorColor;


extern XSIDECL const wchar_t* siUIMarginWidth;


extern XSIDECL const wchar_t* siUICommentFont;


extern XSIDECL const wchar_t* siUIFontSize;


extern XSIDECL const wchar_t* siUIKeywords;


extern XSIDECL const wchar_t* siUIHeight;


extern XSIDECL const wchar_t* siUIHorizontalScroll;


extern XSIDECL const wchar_t* siUIVerticalScroll;


extern XSIDECL const wchar_t* siUILineWrap;


extern XSIDECL const wchar_t* siUIKeywordFile;


extern XSIDECL const wchar_t* siUIAutoComplete;


extern XSIDECL const wchar_t* siUIToolbar;


extern XSIDECL const wchar_t* siUICapability;


extern XSIDECL const wchar_t* siUITabSize;


extern XSIDECL const wchar_t* siUIUseSpacesForTab;


extern XSIDECL const wchar_t* siUIShowIndentationGuides;


extern XSIDECL const wchar_t* siUIShowWhitespace;


extern XSIDECL const wchar_t* siUIDictionary;


extern XSIDECL const wchar_t* siUIHelpButtonFile;


extern XSIDECL const wchar_t* siUIHelpFile;


/*! Reference to a topic in the Help file. Normally this is only used for internal objects. */
extern XSIDECL const wchar_t* siUIHelpID;

/*! See <object idref="PPGLayout.Language"/> */
extern XSIDECL const wchar_t* siUILanguage;

/*! See <object idref="PPGLayout.Logic"/> */
extern XSIDECL const wchar_t* siUILogic;

extern XSIDECL const wchar_t* siUILogicFile;


extern XSIDECL const wchar_t* siUILogicPrefix;


extern XSIDECL const wchar_t* siUIShowChildren;


extern XSIDECL const wchar_t* siArgHandlerAnimatableParameters;


extern XSIDECL const wchar_t* siArgHandlerCollection;


extern XSIDECL const wchar_t* siArgHandlerFrame;


extern XSIDECL const wchar_t* siArgHandlerFrameRate;


extern XSIDECL const wchar_t* siArgHandlerMarkedParameters;


extern XSIDECL const wchar_t* siArgHandlerSingleObj;


/*! Represents the filter objects that can be used with 3D objects. */
extern XSIDECL const wchar_t* siFilter3DObjectType;

extern XSIDECL const wchar_t* siFilterObjectType;


/*! Represents the filter objects that can be used with property objects. */
extern XSIDECL const wchar_t* siFilterPropertyType;

extern XSIDECL const wchar_t* siFilterSubComponentType;


/*! Represents clip objects which are instances of animation layers. */
extern XSIDECL const wchar_t* siClipAnimationLayerType;

extern XSIDECL const wchar_t* siClipAnimationType;


extern XSIDECL const wchar_t* siClipAnimCompoundType;


/*! Represents clip objects which are instances of audio files. */
extern XSIDECL const wchar_t* siClipAudioType;

/*! Represents clip objects which are instances of cache files. */
extern XSIDECL const wchar_t* siClipCacheType;

/*! Represents an <object idref="ImageClip"/> object. */
extern XSIDECL const wchar_t* siClipImageType;

/*! Represents clip objects which are the top-level container for all other clip objects. */
extern XSIDECL const wchar_t* siClipMixerType;

extern XSIDECL const wchar_t* siClipShapeCompoundType;


extern XSIDECL const wchar_t* siClipShapeType;


extern XSIDECL const wchar_t* siClipShotType;


/*! Represents the track objects which organize animation layer <object idref="Clip"/> objects. */
extern XSIDECL const wchar_t* siTrackAnimationLayerType;

extern XSIDECL const wchar_t* siTrackAnimationType;


/*! Represents the track objects which organize audio <object idref="Clip"/> objects. */
extern XSIDECL const wchar_t* siTrackAudioType;

/*! Represents the track objects which organize cache <object idref="Clip"/> objects. */
extern XSIDECL const wchar_t* siTrackCacheType;

/*! Represents the track objects which organize shape <object idref="Clip"/> objects. */
extern XSIDECL const wchar_t* siTrackShapeType;

/*! Represents the track objects which organize camera shot <object idref="Clip"/> objects. */
extern XSIDECL const wchar_t* siTrackShotType;

extern XSIDECL const wchar_t* siTransitionBridgeType;


extern XSIDECL const wchar_t* siTransitionCardinalType;


extern XSIDECL const wchar_t* siTransitionStandardType;


/*! Represents a compound animation source stored in an ActionSource. */
extern XSIDECL const wchar_t* siAnimCompoundAnimItem;

/*! Represents an <object idref="Constraint"/> stored in an ActionSource. */
extern XSIDECL const wchar_t* siConstraintAnimItem;

/*! Represents an <object idref="Expression"/> stored in an ActionSource. */
extern XSIDECL const wchar_t* siExpressionAnimItem;

/*! Represents an <object idref="FCurve"/> stored in an ActionSource. */
extern XSIDECL const wchar_t* siFCurveAnimItem;

/*! Represents a shape compound source stored in an ActionSource. */
extern XSIDECL const wchar_t* siShapeCompoundAnimItem;

/*! Represents an <object idref="ShapeKey"/> stored in an ActionSource. */
extern XSIDECL const wchar_t* siShapeKeyAnimItem;

/*! Represents an <object idref="StaticSource"/> stored in an ActionSource. */
extern XSIDECL const wchar_t* siStaticValueAnimItem;

/*! Represents a compound item in a compound clip. */
extern XSIDECL const wchar_t* siCompoundMappedItem;

extern XSIDECL const wchar_t* siConstraintMappedItem;


extern XSIDECL const wchar_t* siExpressionMappedItem;


extern XSIDECL const wchar_t* siFCurveMappedItem;


/*! Represents a shape compound item in a compound clip. */
extern XSIDECL const wchar_t* siShapeCompoundMappedItem;

extern XSIDECL const wchar_t* siShapeKeyMappedItem;


extern XSIDECL const wchar_t* siStaticValueMappedItem;


/*! Show only Action nodes. */
extern XSIDECL const wchar_t* siSEFilterActionNodes;

/*! Show All Node types. */
extern XSIDECL const wchar_t* siSEFilterAllNodeTypes;

/*! Show only Animatable parameter nodes. */
extern XSIDECL const wchar_t* siSEFilterAnimatableNodes;

/*! Show only Animated parameter nodes. */
extern XSIDECL const wchar_t* siSEFilterAnimatedNodes;

/*! Show only Cluster nodes. */
extern XSIDECL const wchar_t* siSEFilterClusterNodes;

/*! Show only Group nodes. */
extern XSIDECL const wchar_t* siSEFilterGroupNodes;

/*! Show nodes with any keyword set. */
extern XSIDECL const wchar_t* siSEFilterKeywordAll;

/*! Show nodes with Animation keyword set. */
extern XSIDECL const wchar_t* siSEFilterKeywordAnimation;

/*! Show nodes with Custom keyword set. */
extern XSIDECL const wchar_t* siSEFilterKeywordCustom;

/*! Show nodes with General keyword set. */
extern XSIDECL const wchar_t* siSEFilterKeywordGeneral;

/*! Show nodes with Kinematics keyword set. */
extern XSIDECL const wchar_t* siSEFilterKeywordKinematics;

/*! Show nodes with Modeling keyword set. */
extern XSIDECL const wchar_t* siSEFilterKeywordModeling;

/*! Show nodes with Rendering keyword set. */
extern XSIDECL const wchar_t* siSEFilterKeywordRendering;

/*! Show nodes with Viewing keyword set. */
extern XSIDECL const wchar_t* siSEFilterKeywordViewing;

/*! Show only Material nodes. */
extern XSIDECL const wchar_t* siSEFilterMaterialNodes;

/*! Show only Miscellaneous nodes. */
extern XSIDECL const wchar_t* siSEFilterMiscellaneousNodes;

/*! Show only Model nodes. */
extern XSIDECL const wchar_t* siSEFilterModelNodes;

/*! Show only Object nodes. */
extern XSIDECL const wchar_t* siSEFilterObjectNodes;

/*! Show only Operator nodes. */
extern XSIDECL const wchar_t* siSEFilterOperatorNodes;

/*! Show only regular Parameter (non-animatable) nodes. */
extern XSIDECL const wchar_t* siSEFilterParameterNodes;

/*! Show only Primitive nodes. */
extern XSIDECL const wchar_t* siSEFilterPrimitiveNodes;

/*! Show only Property nodes. */
extern XSIDECL const wchar_t* siSEFilterPropertyNodes;

/*! Show only Scene nodes. */
extern XSIDECL const wchar_t* siSEFilterSceneNodes;

/*! Show only Shader nodes. */
extern XSIDECL const wchar_t* siSEFilterShaderNodes;

/*! Represents a four channel RGB color image, where the fourth channel is the alpha matte. */
extern XSIDECL const wchar_t* siImageDataTypeRGBA;

/*! Represents a three channel, RGBA color image. */
extern XSIDECL const wchar_t* siImageDataTypeRGB;

/*! Represents a four channel, RGB color image, where the fourth channel is an exponent. Used for HDR images. */
extern XSIDECL const wchar_t* siImageDataTypeRGBE;

/*! Represents a single channel, alpha matte image. */
extern XSIDECL const wchar_t* siImageDataTypeAlpha;

/*! Represents a single channel, grayscale intensity image. */
extern XSIDECL const wchar_t* siImageDataTypeIntensity;

/*! Represents a single channel, depth value image. */
extern XSIDECL const wchar_t* siImageDataTypeDepth;

/*! Represents a three channel, vector image composed of normalized vectors. */
extern XSIDECL const wchar_t* siImageDataTypeNormal;

/*! Represents a three channel, motion vector image. */
extern XSIDECL const wchar_t* siImageDataTypeMotion;

/*! Represents a three channel image composed of arbitrary vectors. */
extern XSIDECL const wchar_t* siImageDataTypeVector;

/*! Represents a three channel image composed of arbitrary points in space. */
extern XSIDECL const wchar_t* siImageDataTypePoint;

/*! Represents a single channel, object label image. */
extern XSIDECL const wchar_t* siImageDataTypeLabel;

/*! Represents a single channel, single bit-mask image. */
extern XSIDECL const wchar_t* siImageDataTypeBitMask;

/*! Display all nodes for the selected elements. */
extern XSIDECL const wchar_t* siATFilterPresetAll;

/*! Display any type of custom parameter set for the selected elements. This includes proxy parameter sets, marking sets, and annotation properties. */
extern XSIDECL const wchar_t* siATFilterPresetCustom;

/*! Display only the general properties for the selected elements. */
extern XSIDECL const wchar_t* siATFilterPresetGeneral;

/*! Display only the modeling properties for the selected elements. */
extern XSIDECL const wchar_t* siATFilterPresetModeling;

/*! Display only the animation properties for the selected elements. */
extern XSIDECL const wchar_t* siATFilterPresetAnimation;

/*! Display only the kinematics properties for the selected elements. */
extern XSIDECL const wchar_t* siATFilterPresetKinematics;

/*! Display only the rendering properties for the selected elements. */
extern XSIDECL const wchar_t* siATFilterPresetRendering;

/*! Display only the viewing properties for the selected elements. */
extern XSIDECL const wchar_t* siATFilterPresetViewing;

/*! Display only the local transform parameters for the selected elements. */
extern XSIDECL const wchar_t* siATFilterPresetLocalTransform;

/*! Display only the position parameters for the selected elements. */
extern XSIDECL const wchar_t* siATFilterPresetPosition;

/*! Display only the position in X parameters for the selected elements. */
extern XSIDECL const wchar_t* siATFilterPresetPositionX;

/*! Display only the position in Y parameters for the selected elements. */
extern XSIDECL const wchar_t* siATFilterPresetPositionY;

/*! Display only the position in Z parameters for the selected elements. */
extern XSIDECL const wchar_t* siATFilterPresetPositionZ;

/*! Display only the rotation parameters for the selected elements. */
extern XSIDECL const wchar_t* siATFilterPresetRotation;

/*! Display only the rotation in X parameters for the selected elements. */
extern XSIDECL const wchar_t* siATFilterPresetRotationX;

/*! Display only the rotation in Y parameters for the selected elements. */
extern XSIDECL const wchar_t* siATFilterPresetRotationY;

/*! Display only the rotation in Z parameters for the selected elements. */
extern XSIDECL const wchar_t* siATFilterPresetRotationZ;

/*! Display only the scaling parameters for the selected elements. */
extern XSIDECL const wchar_t* siATFilterPresetScaling;

/*! Display only the scaling in X parameters for the selected elements. */
extern XSIDECL const wchar_t* siATFilterPresetScalingX;

/*! Display only the scaling in Y parameters for the selected elements. */
extern XSIDECL const wchar_t* siATFilterPresetScalingY;

/*! Display only the scaling in Z parameters for the selected elements. */
extern XSIDECL const wchar_t* siATFilterPresetScalingZ;

/*! Display only the color parameters for the selected elements. */
extern XSIDECL const wchar_t* siATFilterPresetColor;

/*! Filter all tagged parameters. */
extern XSIDECL const wchar_t* siATFilterTaggedAll;

/*! Filter the tagged 1 parameters. */
extern XSIDECL const wchar_t* siATFilterTagged1;

/*! Filter the tagged 2 parameters. */
extern XSIDECL const wchar_t* siATFilterTagged2;

/*! Filter the tagged 3 parameters. */
extern XSIDECL const wchar_t* siATFilterTagged3;

/*! Filter the tagged 4 parameters. */
extern XSIDECL const wchar_t* siATFilterTagged4;

/*! Filter the tagged 5 parameters. */
extern XSIDECL const wchar_t* siATFilterTagged5;

/*! Filter the tagged 6 parameters. */
extern XSIDECL const wchar_t* siATFilterTagged6;

/*! Filter the tagged 7 parameters. */
extern XSIDECL const wchar_t* siATFilterTagged7;

/*! Filter the tagged 8 parameters. */
extern XSIDECL const wchar_t* siATFilterTagged8;

/*! Filter the tagged 9 parameters. */
extern XSIDECL const wchar_t* siATFilterTagged9;

/*! Filter the tagged 10 parameters. */
extern XSIDECL const wchar_t* siATFilterTagged10;

extern XSIDECL const wchar_t* siReferenceFilterAttribute;


extern XSIDECL const wchar_t* siPropertyFilterAttribute;


extern XSIDECL const wchar_t* siCustomTypeNameAttribute;


/*! Type of filter for a shader's family. */
extern XSIDECL const wchar_t* siShaderFamilyAttribute;

extern XSIDECL const wchar_t* siDefaultConnectionAttribute;


/*! Type of filter for a writable image. */
extern XSIDECL const wchar_t* siWritableImageAttribute;

/*! Type of filter for a writable image type. */
extern XSIDECL const wchar_t* siWritableImageTypeAttribute;

/*! Type of filter to match the Red color for a RenderTree node. */
extern XSIDECL const wchar_t* siRenderTreeNodeColorRAttribute;

/*! Type of filter to match the Green color for a RenderTree node. */
extern XSIDECL const wchar_t* siRenderTreeNodeColorGAttribute;

/*! Type of filter to match the Blue color for a RenderTree node. */
extern XSIDECL const wchar_t* siRenderTreeNodeColorBAttribute;

/*! Controls which display name to use in the Render Tree layout when no layout is given. By default, the ports will use the script name. Set this attribute to true to use the display name from the PPG. */
extern XSIDECL const wchar_t* siUseRenderTreeLayoutPortDisplayNamesAttribute;

/*! When this attribute is set to true and the parameter value changes, the MetaSL viewport shader will be recompiled. This is needed when the number of light casting shadows changes or when switching light types. */
extern XSIDECL const wchar_t* siRecompileMetaSLOnValueChange;

/*! When this attribute is set to true, tangent data will be generated for this property for the MetaSL viewport shader. */
extern XSIDECL const wchar_t* siCAVTangentsAttribute;

/*! When this attribute is set to true, binormal data will be generated for this property for the MetaSL viewport shader. */
extern XSIDECL const wchar_t* siCAVBinormalsAttribute;

/*! Attribute used for defining the version of a hardware shader. */
extern XSIDECL const wchar_t* siHWShaderVersionAttribute;

extern XSIDECL const wchar_t* siHWShaderForceAttributeUpdate;


extern XSIDECL const wchar_t* siHWShaderDirtyParameterUpdate;


/*! mental ray Contour Contrast Shader */
extern XSIDECL const wchar_t* siShaderFamilyCntContrast;

/*! mental ray Contour Material */
extern XSIDECL const wchar_t* siShaderFamilyCntMat;

/*! mental ray Contour Store Shader */
extern XSIDECL const wchar_t* siShaderFamilyCntStore;

/*! mental ray Data Blob */
extern XSIDECL const wchar_t* siShaderFamilyData;

/*! mental ray Environment Shader (environment phenomenon in a material or camera) */
extern XSIDECL const wchar_t* siShaderFamilyEnvironment;

/*! mental ray Geometry Shader (geometry phenomenon) */
extern XSIDECL const wchar_t* siShaderFamilyGeometry;

/*! mental ray Lens Shader (lens phenomenon in a camera) */
extern XSIDECL const wchar_t* siShaderFamilyLens;

/*! mental ray Light Shader (light phenomenon) */
extern XSIDECL const wchar_t* siShaderFamilyLight;

/*! mental ray Lightmap Shader */
extern XSIDECL const wchar_t* siShaderFamilyLightmap;

/*! mental ray Output Shader (output phenomenon in a camera) */
extern XSIDECL const wchar_t* siShaderFamilyOutput;

/*! mental ray Material Phenomenon */
extern XSIDECL const wchar_t* siShaderFamilyPhenomMat;

/*! mental ray Photon Light Shader (photon emitter phenomenon in a light) */
extern XSIDECL const wchar_t* siShaderFamilyPhotonLight;

/*! mental ray Photon Material Shader (photon phenomenon in a material) */
extern XSIDECL const wchar_t* siShaderFamilyPhotonMat;

/*! mental ray Photon Volume Shader (photon phenomenon in a material or camera) */
extern XSIDECL const wchar_t* siShaderFamilyPhotonVolume;

/*! mental ray Shadow Material Shader (shadow phenomenon in a material) */
extern XSIDECL const wchar_t* siShaderFamilyShadowMat;

/*! mental ray State Shader */
extern XSIDECL const wchar_t* siShaderFamilyState;

/*! mental ray Surface Material Shader (material phenomenon in a material) */
extern XSIDECL const wchar_t* siShaderFamilySurfaceMat;

/*! mental ray Texture Shader (texture phenomenon) */
extern XSIDECL const wchar_t* siShaderFamilyTexture;

/*! mental ray Volume Shader (volume phenomenon in a material or camera) */
extern XSIDECL const wchar_t* siShaderFamilyVolume;

/*! Realtime Shader */
extern XSIDECL const wchar_t* siShaderFamilyRTShader;

extern XSIDECL const wchar_t* siMentalRayLightmapPortType;


extern XSIDECL const wchar_t* siMentalRayGeometryPortType;


extern XSIDECL const wchar_t* siMentalRayContourStorePortType;


extern XSIDECL const wchar_t* siMentalRayContourContrastPortType;


extern XSIDECL const wchar_t* siMentalRayPhenomenonMaterialPortType;


extern XSIDECL const wchar_t* siXGSRealTimePortType;


extern XSIDECL const wchar_t* siHWShaderPortType;


extern XSIDECL const wchar_t* siHardwareVertexPosition;


extern XSIDECL const wchar_t* siHardwareVertexNormal;


/*! Default vertex color name. */
extern XSIDECL const wchar_t* siHardwareVertexColor;

/*! Tangent */
extern XSIDECL const wchar_t* siHardwareVertexTangent;

/*! Binormal */
extern XSIDECL const wchar_t* siHardwareVertexBinormal;

/*! Texture projection */
extern XSIDECL const wchar_t* siHardwareVertexTexCoord;

/*! Weight map */
extern XSIDECL const wchar_t* siHardwareVertexWeightMap;

/*! Point velocity */
extern XSIDECL const wchar_t* siHardwareVertexPointVelocity;

/*! Orientation */
extern XSIDECL const wchar_t* siHardwareVertexOrientation;

/*! Age */
extern XSIDECL const wchar_t* siHardwareVertexAge;

/*! Radius */
extern XSIDECL const wchar_t* siHardwareVertexRadius;

/*! ID */
extern XSIDECL const wchar_t* siHardwareVertexID;

/*! Fog */
extern XSIDECL const wchar_t* siHardwareVertexFog;

/*! Weight */
extern XSIDECL const wchar_t* siHardwareVertexWeight;

/*! Index */
extern XSIDECL const wchar_t* siHardwareVertexIndice;

/*! Tesselation factor */
extern XSIDECL const wchar_t* siHardwareVertexTessfactor;

/*! Depth */
extern XSIDECL const wchar_t* siHardwareVertexDepth;

/*! Sample */
extern XSIDECL const wchar_t* siHardwareVertexSample;

/*! Let Softimage handle the creation of the attribute (useful for tangents and binormals). */
extern XSIDECL const wchar_t* siHardwareVertexAuto;

/*! Constant Boolean ICE attribute to control texture U wrapping. Valid only when used on a texture space parameter. */
extern XSIDECL const wchar_t* siICERenderPropSuffixUWrap;

/*! Constant Boolean ICE attribute to control texture V wrapping. Valid only when used on a texture space parameter. */
extern XSIDECL const wchar_t* siICERenderPropSuffixVWrap;

/*! Constant Boolean ICE attribute to control texture W wrapping. Valid only when used on a texture space parameter. */
extern XSIDECL const wchar_t* siICERenderPropSuffixWWrap;

/*! Constant Matrix44 ICE attribute to control texture matrix. Valid only when used on a texture space parameter. */
extern XSIDECL const wchar_t* siICERenderPropSuffixTransform;

/*! Constant Boolean ICE attribute to control if coordinates are homogeneous. Valid only for rendering when used on a texture space parameter. */
extern XSIDECL const wchar_t* siICERenderPropSuffixIsHomogeneous;

/*! Constant Boolean ICE attribute to control if attributes are smoothed based on the subdivision ssurface algorithm. Valid only for rendering on subdivision surface meshes. */
extern XSIDECL const wchar_t* siICERenderPropSuffixSmoothWhenSubd;


}; // XSI namespace


#endif /* _XSIDECL_H_ */
