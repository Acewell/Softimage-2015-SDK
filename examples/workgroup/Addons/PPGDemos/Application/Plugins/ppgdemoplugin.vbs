'	Copyright 2008 Autodesk, Inc.  All rights reserved.  
'	Use of this software is subject to the terms of the Autodesk license agreement 
'	provided at the time of installation or download, or which otherwise accompanies 
'	this software in either electronic or hard copy form.   

option explicit

function XSILoadPlugin( in_reg )
	in_reg.Author = "Softimage"
	in_reg.Name = "Softimage PPG Layout Demos - VBS"
	in_reg.Major = 1
	in_reg.Minor = 0 

	in_reg.RegisterCommand "PPGMultiFCurve", "PPGMultiFCurve" 
end function

function PPGMultiFCurve_Execute()

	'Example showing how the FCurve control can
	'be customized via SetUIAttribute
	'All editors show the same curve 
	'but the presentation differs

	dim oCustomProperty, oLayout, oLayoutItem

	set oCustomProperty = ActiveSceneRoot.AddProperty(_
				"CustomProperty",false,"FCurves")

	oCustomProperty.AddFCurveParameter "curve1" 
	oCustomProperty.AddFCurveParameter "curve2" 
	oCustomProperty.AddFCurveParameter "curve3" 
	oCustomProperty.AddFCurveParameter "curve4" 

	set oLayout = oCustomProperty.PPGLayout

	oLayout.AddRow
	oLayout.AddFCurve "curve1", 150
	oLayout.AddFCurve "curve2"
	oLayout.EndRow

	oLayout.AddRow
	oLayout.AddFCurve "curve3", 150
	oLayout.AddFCurve "curve4", 150
	oLayout.EndRow


	'Now set attributes
	set oLayoutItem = oLayout.Item("curve2")
	oLayoutItem.SetAttribute "NoGrid", true
	oLayoutItem.SetAttribute "NoRulerX", true
	oLayoutItem.SetAttribute "NoRulerY", true
	'In order to line up nicely with the 
	'other curve in the row set a smaller size (because
	'the ruler is not showing
	oLayoutItem.SetAttribute "CY", 125


	set oLayoutItem = oLayout.Item("curve3")
	oLayoutItem.SetAttribute "ViewMinX", -100
	oLayoutItem.SetAttribute "ViewMaxX", 100
	oLayoutItem.SetAttribute "ViewMinY", 0
	oLayoutItem.SetAttribute "ViewMaxY", 150
	oLayoutItem.SetAttribute "LabelX", "My X-Axis Label"
	oLayoutItem.SetAttribute "LabelY", "My Y-Axis Label"
	oLayoutItem.SetAttribute "ColorNonBijective", true
	oLayoutItem.SetAttribute "Ghosting", true

	'Grid spacing is mostly only a hint to the editor.
	'It will ignore values that are too small
	set oLayoutItem = oLayout.Item("curve4")
	oLayoutItem.SetAttribute "GridSpaceX", 25
	oLayoutItem.SetAttribute "GridSpaceY", 25

	'Snap Grid is independent of the visible grid
	oLayoutItem.SetAttribute "SnapX", 10
	oLayoutItem.SetAttribute "SnapY", 10

	InspectObj oCustomProperty

end function