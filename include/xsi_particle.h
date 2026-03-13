//*****************************************************************************
/*!
   \file xsi_particle.h
   \brief Particle class declaration.

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//*****************************************************************************

#if (_MSC_VER > 1000) || defined(SGI_COMPILER)
#pragma once
#endif

#ifndef __XSIPARTICLE_H__
#define __XSIPARTICLE_H__

#include <xsi_siobject.h>
#include <xsi_value.h>
#include <xsi_status.h>
#include <xsi_vector3.h>
#include <xsi_rotation.h>
#include <xsi_color.h>

namespace XSI {


//*****************************************************************************
/*! \class Particle xsi_particle.h

	\brief Represents one particle in a particle cloud.

	Particles are accessible via ParticleCloudPrimitive::GetParticle.

	\sa ParticleCloud, ParticleCloudPrimitive, X3DObject::AddParticleCloud
	\deprecated 8.0 (2010) Legacy particles are kept for backward compatibility.

	\eg Creates the initial state for a particle simulation
	\code
		using namespace XSI;
		Application app ;

		CValueArray args(2) ;
		CValue outArg;

		args[0] = (LONG) siSphereType ;
		app.ExecuteCommand( L"CreateParticleType", args, outArg ) ;

		Property myParType = args[1] ;
		myParType.PutName( CString(L"CustomParType") ) ;

		CRefArray particleTypeArray ;
		particleTypeArray.Add( myParType ) ;

		// Create a particle cloud.  This has no emittor, and no particle operator
		// so the cloud state is completely the responsibility of the plug-in
		// and will not change even if the current frame is changed
		ParticleCloud myParticleCloud ;
		app.GetActiveSceneRoot().AddParticleCloud(
									particleTypeArray,
									L"MyCloud",
									myParticleCloud ) ;

		ParticleCloudPrimitive myParticlePrim = myParticleCloud.GetActivePrimitive() ;

		// Our "CustomParType" will automatically be used because
		// we specified it in the call to AddParticleCloud
		myParticlePrim.AddParticles( 1000, CRef() ) ;

		// Position the particles in a 3D grid
		for ( LONG i = 0 ; i < 10 ; i++ )
		{
			for ( LONG j = 0 ; j < 10 ; j++ )
			{
				for ( LONG k = 0 ; k < 10 ; k++ )
				{
					LONG index = i*100 + j*10 + k ;
					Particle oParticle = myParticlePrim.GetParticle(index) ;
					oParticle.PutPosition( MATH::CVector3(-5 + i, -3 +j, k)) ;

					//Sets different ages so that the particles
					//will die during the playback
					oParticle.PutAge( 1 + j * 10 ) ;
					oParticle.PutAgeLimit( 100 ) ;
				}
			}
		}

		// Call the CreateParticleCloud command to create a new
		// cloud which uses our "static" cloud as the initial state

		// This new cloud will include a particle operator so
		// it will perform a simulation, allowing us to see the
		// age change for the particles.
		args[0] = myParticleCloud ; // Where to add the particle cloud
		args[1] = CValue() ; // No emitter necessary, particles already exist
		app.ExecuteCommand( L"CreateParticleCloud", args, outArg ) ;

		// Sets some attributes on the new cloud's particle type
		CValueArray & NewParticleClouds = outArg ;
		ParticleCloud myNewCloud = NewParticleClouds[0] ;
		ParticleCloudPrimitive myNewCloudPrim = myNewCloud.GetActivePrimitive() ;
		Property myNewCloudParType = myNewCloudPrim.GetParticleTypes().GetItem(0) ;

		myNewCloudParType.PutParameterValue( L"Size", 0.3 ) ;
		myNewCloudParType.PutParameterValue( L"Red", 0.99 ) ;
		myNewCloudParType.PutParameterValue( L"Green", 0.00 ) ;
		myNewCloudParType.PutParameterValue( L"Blue", 0.10 ) ;
		myNewCloudParType.PutParameterValue( L"Alpha", 0.50 ) ;

		// Hide the original cloud (we could also delete it)
		args.Resize(1) ;
		args[0] = myParticleCloud ;
		app.ExecuteCommand( L"ToggleVisibility", args, outArg ) ;

		// Start playing to show the particles disappearing
		args.Resize(0) ;
		app.ExecuteCommand( L"PlayForwardsFromStart", args, outArg ) ;
  	\endcode

*/
//*****************************************************************************

class SICPPSDKDECL Particle : public SIObject
{
public:
	/*! Default constructor. */
	Particle();

	/*! Default destructor. */
	~Particle();

	/*! Constructor.
	\param in_ref constant reference object.
	*/
	Particle(const CRef& in_ref);

	/*! Copy constructor.
	\param in_obj constant class object.
	*/
	Particle(const Particle& in_obj);

	/*! Returns true if a given class type is compatible with this API class.
	\param in_ClassID class type.
	\return true if the class is compatible, false otherwise.
	*/
	bool IsA( siClassID in_ClassID) const;

	/*! Returns the type of the API class.
	\return The class type.
	*/
	siClassID GetClassID() const;

	/*! Creates an object from another object. The newly created object is set to
	empty if the input object is not compatible.
	\param in_obj constant class object.
	\return The new Particle object.
	*/
	Particle& operator=(const Particle& in_obj);

	/*! Creates an object from a reference object. The newly created object is
	set to empty if the input reference object is not compatible.
	\param in_ref constant class object.
	\return The new Particle object.
	*/
	Particle& operator=(const CRef& in_ref);

	/*! Returns the index of the particle in the particle collection. A particle's index can change
	throughout a simulation when particles are added or removed from the cloud.
	\return The index of the particle
	*/
	LONG GetIndex() const;

	/*!	Returns the particle's ID. A particle ID is a number that uniquely identifies the particle
	within a cloud. It is invariant throughout the simulation.
	\return The particle ID
	*/
	LONG GetID() const;

	/*! Returns the type ID for the particle.  A cloud can contain particles from multiple particle types.
	\return The type ID for the particle
	\sa Particle::PutTypeID, ParticleCloudPrimitive::GetParticleTypes
	*/
	LONG GetTypeID() const;

	/*! Changes the type ID of the particle.
	\param in_TypeID The new type ID for the particle
	\sa Particle::GetTypeID
	*/
	CStatus PutTypeID(LONG in_TypeID);

	/*! Returns the particle position
	\return The position of the particle
	\sa Particle::GetVelocity
	*/
	MATH::CVector3 GetPosition()  const;

	/*! Sets the particle position
	\param in_vect The position of the particle
	\sa Particle::GetVelocity
	*/
	CStatus PutPosition(const MATH::CVector3& in_vect);

	/*! Returns the particle velocity
	\return The speed of the particle
	\sa Particle::PutVelocity
	*/
	MATH::CVector3 GetVelocity()  const;

	/*! Sets the particle velocity
	\param in_vect The speed of the particle
	\sa Particle::GetVelocity
	*/
	CStatus PutVelocity(const MATH::CVector3& in_vect);

	/*! Returns the particle angular velocity
	\return The speed of the particle's rotation
	\sa Particle::PutAngularVelocity
	*/
	MATH::CRotation GetAngularVelocity()  const;

	/*! Sets the particle angular velocity
	\param in_vect The speed of the particle's rotation
	\sa Particle::GetAngularVelocity
	*/
	CStatus PutAngularVelocity(const MATH::CRotation& in_vect);

	/*! Returns the particle rotation
	\return The particle's rotation
	\sa Particle::PutRotation
	*/
	MATH::CVector3 GetRotation()  const;

	/*! Sets the particle rotation
	\param in_vect The particle's rotation
	\sa Particle::GetRotation
	*/
	CStatus PutRotation(const MATH::CVector3& in_vect);

	/*! Returns the distance that the particle has travelled since birth.
	\return The particle's path length
	*/
	double GetPathLength() const ;

	/*! Returns the particle's age (frames since the particles birth).  This can be a useful
	function in a custom operator for detecting if a particle is freshly born to run special
	initialization code.
	\return The particle's age
	\sa Particle::PutAge
	*/
	LONG GetAge() const ;

	/*! Sets the particle's age (in frames)
	\param in_age The particle's age
	\sa Particle::GetAge
	*/
	CStatus PutAge( LONG in_age ) ;

	/*! Returns the particle life span (in frames)
	\return The particle's lifespan
	\sa Particle::PutAgeLimit
	*/
	LONG GetAgeLimit() const;

	/*! Sets the particle life span
	\param in_agelimit The particle's lifespan
	\sa Particle::GetAgeLimit
	*/
	CStatus PutAgeLimit(LONG in_agelimit);

	/*! Returns the random number generator seed for the particle
	\return The number to use as a seed
	\sa Particle::PutSeed
	*/
	LONG GetSeed() const;

	/*! Sets the random number generator seed of the particle
	\param in_seed The number to use as a seed
	\sa Particle::GetSeed
	*/
	CStatus PutSeed(LONG in_seed);

	/*! Returns the particle's color
	\return The particle color
	\sa Particle::PutColor
	*/
	CColor GetColor( ) const ;

	/*! Sets the particle's color
	\param in_vColor The color to set, normalized with each component in the range \c 0 to \c 1
	\sa Particle::GetColor
	*/
	CStatus PutColor( const CColor & in_vColor ) ;

	/*! Returns the parametric surface coordinates where the particle was emitted. As these are
	parametric coordinates, they make more sense when the emitters are NURBS curves or surfaces.
	\return The parametric surface coordinates on the emitter where the particle is emitted
	\sa Particle::PutUVW
	*/
	MATH::CVector3 GetUVW()  const;

	/*! Sets the parametric surface coordinates on the emitter where the particle is emitted.  As
	these are parametric coordinates, they make more sense when the emitters are NURBS curves or surfaces.
	\param in_vect Parametric surface coordinates where the particle was emitted
	\sa Particle::GetUVW
	*/
	CStatus PutUVW(const MATH::CVector3& in_vect);

	/*! Returns the sprite index for the particle. The sprite index refers to a frame in the image clip
	associated with the particle's particle type property. You can set the image clip to be used by the
	particle via the particletype. The sprite index is only used when the particle type's shape type is
	set to sprite.
	\return The sprite index
	\sa ParticleCloudPrimitive::GetParticleTypes, Particle::GetTypeID, Particle::GetSpriteAngle,
		Particle::PutSpriteIndex
	*/
	LONG GetSpriteIndex() const;

	/*! Sets the sprite index of the particle.
	\param in_index The frame in the image clip associated with the particle's \c ParticleType property
	\sa Particle::GetSpriteIndex
	*/
	CStatus PutSpriteIndex(LONG in_index);

	/*! Returns the particle sprite angle. The sprite angle is the amount of rotation of the particle in
	the camera plane. The rotation is expressed in degrees and increases counter-clockwise.
	\return The sprite angle
	\sa Particle::PutSpriteAngle
	*/
	double GetSpriteAngle() const;

	/*! Sets the particle sprite angle.
	\param in_angle Amount of rotation of the particle in the camera plane
	\sa Particle::GetSpriteAngle
	*/
	CStatus PutSpriteAngle(double in_angle);

	/*! Returns the particle's size
	\return The particle size
	\sa Particle::PutSize
	*/
	double GetSize() const ;

	/*! Sets the particle's size
	\param in_size Size of the particle
	\sa Particle::GetSize
	*/
	CStatus PutSize( double in_size ) ;

	/*! Returns the particle's mass
	\return The particle mass
	\sa Particle::PutMass
	*/
	double GetMass() const;

	/*! Sets the particle's mass
	\param in_mass Mass controls how a particle is influenced by some forces
	\sa Particle::GetMass
	*/
	CStatus PutMass(double in_mass);

	/*! Returns the particle's density
	\return The particle density
	*/
	double GetDensity() const;

	/*! Returns the pressure on the particle
	\return The particle pressure
	*/
	double GetPressure() const;

	/*! Returns an array of references to the user-defined particle attributes.
	\return Array of references to ParticleAttribute objects.
	\sa ParticleAttribute, ParticleType::AddAttribute
	\since 4.0
	*/
	CRefArray GetAttributes() const;

	private:
	Particle * operator&() const;
	Particle * operator&();
};

};
#endif // __XSIPARTICLE_H__
