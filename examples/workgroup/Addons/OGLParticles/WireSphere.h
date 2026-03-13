//
//	Copyright 2008 Autodesk, Inc.  All rights reserved.  
//	Use of this software is subject to the terms of the Autodesk license agreement 
//	provided at the time of installation or download, or which otherwise accompanies 
//	this software in either electronic or hard copy form.   

#ifndef WIRE_SPHERE_H
#define WIRE_SPHERE_H

#include "Mesh.h"

class WireSphereMesh : public Mesh
{
public:
	WireSphereMesh();

	virtual void render(LONG id, LONG iLayoutType) const;
	virtual void setState(VOID*  in_pGeometry) const;
	virtual void unsetState(VOID*  in_pGeometry) const;
};


#endif
