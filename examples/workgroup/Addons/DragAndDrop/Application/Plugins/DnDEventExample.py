# This plug-in installs a siOnDragAndDrop2 Event handler
# When something gets dragged, it will:
#		* Log all the available information (verbose)
#		* Duplicate the dragged object in the scene if the dragged object is a X3DObject over a viewport
#		* Move the object around in the viewport using the event 3d coordinates
import win32com.client
from win32com.client import constants as C

#########################################################################
# Plugin load/unload.

def XSILoadPlugin( in_reg ):
	in_reg.Author = "Autodesk"
	in_reg.Name = "DnD Test Plug-in"
	in_reg.Major = 1
	in_reg.Minor = 0

	event_name = "DragAndDrop_Test"
	in_reg.RegisterEvent(event_name , C.siOnDragAndDrop2)

	#RegistrationInsertionPoint - do not remove this line

	return True

def XSIUnloadPlugin( in_reg ):
	strPluginName = in_reg.Name
	return True

#########################################################################
# Logging Helpers.

def Action2String( in_action ):
	"""
	Convert an action ID into a descriptive text.
	"""
	try:
		a2s = {
			C.siDragOverAction  : "drag over",
			C.siDropAction      : "drop",
			C.siDragEnterAction : "enter",
			C.siDragLeaveAction : "leave",
		}
		return a2s[in_action]
	except:
		# Just in case the action ID is unknown.
		return "?"

def Modifier2String( in_modifier ):
	"""
	Convert a modifier bitfield into a string
	"""
	modifiers = []
	if in_modifier & C.siDragModifierLButton :
		modifiers.append( "LMB" )
	if in_modifier & C.siDragModifierMButton :
		modifiers.append( "MMB" )
	if in_modifier & C.siDragModifierRButton :
		modifiers.append( "RMB" )
	if in_modifier & C.siDragModifierShift :
		modifiers.append( "SHIFT" )
	if in_modifier & C.siDragModifierCtrl :
		modifiers.append( "CTRL" )
	if in_modifier & C.siDragModifierAlt :
		modifiers.append( "ALT" )

	theString = ""
	for modif in modifiers:
		if len(theString) > 0:
			theString += "+"
		theString += modif
		
	return theString


#########################################################################
# Drag and Drop Helpers.

created = None

def Move(coord):
	"""
	Move the currently copied object to the given 3D coordinates.
	"""
	global created
	if created:
		try:
			created.posx = coord[0]
			created.posy = coord[1]
			created.posz = coord[2]
			Application.Refresh()
		except:
			# Just in case the copied object doesn't have kinematics.
			pass
	
def OnEnter(source, coord):
	"""
	When the dragged object enters a view, we copy the object and follow the mouse.
	"""
	global created
	created = Application.Duplicate(source)[0]
	Move(coord)

def OnDrag(source, coord):
	"""
	When the dragged object moves in a view, we move the copied object to follow the mouse.
	"""
	global created
	Move(coord)

def OnDrop(source, coord):
	"""
	When dropped, we do nothing, as the object has already been copied.
	"""
	pass

def OnLeave(source, coord):
	"""
	When the dragged object leaves a view, we delete the copied object.
	"""
	global created
	if created:
		Application.DeleteObj(created)
		created = None

#########################################################################
# Callback for the DragAndDrop event.

def DragAndDrop_Test_OnEvent(in_ctxt):
	"""
	Receive the drag-and-drop events from Softimage.
	Our implementation copies the first object in the source
	and drag it around.
	"""

	# Extract event information.
	action = in_ctxt.GetAttribute("DragAndDropAction")
	sources = list(in_ctxt.GetAttribute("DragSourceObjects"))
	targets = list(in_ctxt.GetAttribute("DragTargetObjects"))
	view = in_ctxt.GetAttribute("DragTargetView")
	mouse = in_ctxt.GetAttribute("DragMouseCoordinates")
	coord = in_ctxt.GetAttribute("Drag3DCoordinates")
	modif = in_ctxt.GetAttribute("DragModifiers")
	
	# Log everything (info/verbose), in the most human readable possible format
	sourcesStr = ""
	for source in sources:
		if len(sourcesStr) > 0:
			sourcesStr += ", "
		try:
			sourcesStr += source.Name
		except:
			sourcesStr += str( source )

	targetsStr = ""
	for target in targets:
		if len(targetsStr) > 0:
			targetsStr += ", "
		try:
			targetsStr += target.Name
		except:
			targetsStr += str( target )
			
	trace =		Action2String( action ) + " | "
	trace +=	sourcesStr + " | "
	trace +=	targetsStr + " | "
	trace +=	view.Name + " | "
	trace +=	str( mouse ) + " | "
	trace +=	str( coord ) + " | "
	trace +=	Modifier2String( modif )
	Application.LogMessage( trace, C.siVerbose )
	
	# Are we dragging a 3DO?
	source3DO = None
	try:
		if Application.ClassName( sources[0] ) == "X3DObject":
			source3DO = sources[0]
	except:
		pass
		
	# By default, we do not accept the event 
	in_ctxt.SetAttribute("DragSourceSupported", False)

	if source3DO and view and view.Type == "Viewer" :
		# We are dragging a 3DO in a viewport
		# Accept the event.
		in_ctxt.SetAttribute("DragSourceSupported", True)
		
		# Here we play with the mouse icon depending on the modifiers (ctrl, alt, shift)
		# We do not change the behavior of the plug-in depending on the modifiers though
		if modif & C.siDragModifierShift :
			in_ctxt.SetAttribute( "DragDropEffect", C.siDropEffectMove )
		if modif & C.siDragModifierCtrl :
			in_ctxt.SetAttribute( "DragDropEffect", C.siDropEffectCopy )
		if modif & C.siDragModifierAlt :
			in_ctxt.SetAttribute( "DragDropEffect", C.siDropEffectLink )

		# Process it
		try:
			a2f = {
				C.siDragOverAction  : OnDrag,
				C.siDropAction      : OnDrop,
				C.siDragEnterAction : OnEnter,
				C.siDragLeaveAction : OnLeave,
			}
			a2f[action](source3DO, coord)
		except:
			# Just in case the event ID is out of range.
			pass

	return True