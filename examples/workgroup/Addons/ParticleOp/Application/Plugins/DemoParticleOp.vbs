'DemoParticleOp.vbs
'
'This command creates a cloud, moves the particles to initial positions,
'and then demonstrates the Example Particle Operator
'
'	Copyright 2008 Autodesk, Inc.  All rights reserved.  
'	Use of this software is subject to the terms of the Autodesk license agreement 
'	provided at the time of installation or download, or which otherwise accompanies 
'	this software in either electronic or hard copy form.   

option explicit

'Total number of particles will be this value cubed, eg 3 => 27 particles
const g_ParticlesPerSide = 3
const g_ParticleInitialSpacing = 1

dim g_NumberOfParticles
g_NumberOfParticles = g_ParticlesPerSide * g_ParticlesPerSide * g_ParticlesPerSide 

function XSILoadPlugin( in_reg )
	in_reg.Author = "Softimage"
	in_reg.Name = "DemoParticleOp"
	in_reg.Email = ""
	in_reg.URL = ""
	in_reg.Major = 1
	in_reg.Minor = 0

	in_reg.RegisterCommand "DemoParticleOp"
	'RegistrationInsertionPoint - do not remove this line

	XSILoadPlugin = true
end function

function XSIUnloadPlugin( in_reg )
	XSIUnloadPlugin = true
end function

function DemoParticleOp_Init( ctxt )
	dim oCmd
	set oCmd = ctxt.Source
	oCmd.Description = ""
	oCmd.ReturnValue = true

	DemoParticleOp_Init = true
end function

function DemoParticleOp_Execute(  )
	dim oCloud, oEmitter, oCluster, oOps, oOp

	NewScene ,false
	set oCloud = CreateParticleCloud().Item( 0 )

	'Use an emitter to create our particles
	set oEmitter= CreatePrim( "Sphere", "MeshSurface", "ParticleEmitter" )
	AddParticleEmitter oCloud, oEmitter 

	'At 1 second the number of particles specified by the
	'emission rate will have been reached
	SetValue oEmitter & ".ParticleEmitter_emission.Rate", g_NumberOfParticles
	SetValue "PlayControl.Current", 30

	'Now get rid of the emitter and freeze the cloud - we will
	'simulate the particles ourselves
	FreezeObj oCloud
	DeleteObj oEmitter
	oEmitter = Empty

	SetValue "PlayControl.Current", 1

	SelectObj oCloud
	set oCloud = selection(0)

	'Move particles to initial positions - a 3d grid

	dim pos, cnt, i, j, k
	
	set pos = XSIMath.CreateVector3
	cnt = 0

	for i = 0 to g_ParticlesPerSide - 1
   		pos.y = 0
		for j = 0 to g_ParticlesPerSide - 1
			pos.z = 0
			for k = 0 to g_ParticlesPerSide - 1				
				oCloud.Particles.Item( cnt ).Position = pos
				pos.z = pos.z + g_ParticleInitialSpacing	
				cnt = cnt + 1
			next
			pos.y = pos.y + g_ParticleInitialSpacing
		next
		pos.x = pos.x + g_ParticleInitialSpacing
	next

	on error resume next
	set oOp = ApplyParticleOp(oCloud.ActivePrimitive)
	
	if err <> 0 then
		logmessage "The ParticleOp example is not properly installed. " & _
				"Please try re-installing the addon file"
		exit function
	end if 

	on error goto 0

	
	'Start the simulation going right away and show the user
	'that they can tweak the behavior with the property page controls.
	InspectObj oOp
	SetValue "PlayControl.Loop", True
	PlayForwardsFromStart


	DemoParticleOp_Execute = true
end function

