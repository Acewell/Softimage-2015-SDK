//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file SIBCQuaternion.h
	\brief Defines the CSIBCQuaternion class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

//***************************************************************************************
// Includes
//***************************************************************************************
#include <float.h>
#include <SIBCUtil.h>
#include <SIBCMatrix.h>
#include <SIBCVector.h>


//***************************************************************************************
// Defines
//***************************************************************************************
#ifndef __CSIBCQUATERNION_H__
#define __CSIBCQUATERNION_H__

//***************************************************************************************
// CSIBCQuaternion | Implementation of a Quaternion class.
//***************************************************************************************

/*! \brief Generic class representing quaternions.

	The notation used in this quaternion class <TT>(W, X, Y, Z)</TT> makes the quaternions closely
	related to 4D vectors (See CSIBCVector4D). In general, the quaternion can be thought
	of as a scalar plus a vector, where the \c W component is the vector, and \c X, \c Y and \c Z are
	the coefficients of the \c I, \c J and \c K matrices respectively.

	The components of the CSIBCQuaternion class are represented by single precision floating-point
	numbers. Its corresponding double precision class, CSIBCQuaterniond, has much more
	functionality, such as the ability to interpolate and multiply quaternions.

*/
class XSICOREEXPORT CSIBCQuaternion
{
    public:

		/*! Default Constructor.
			Sets all components of the quaternion to zero, except W, which is set to one.
			\sa CSIBCQuaternion::Init()
		*/
        CSIBCQuaternion() :
            m_fW(1.0), m_fX(0.0), m_fY(0.0), m_fZ(0.0) {}

		/*! Copy Copnstructor.
			Copies the data from \p in_quat to the new quaternion.
			\param[in]	in_quat	Quaternion containing data to copy to this quaternion.
			\sa CSIBCQuaternion::operator=
			\sa CSIBCQuaternion::Init(CSIBCQuaternion &)
		*/
        CSIBCQuaternion(const CSIBCQuaternion &in_quat) { *this = in_quat; }

        ~CSIBCQuaternion() {}

		/*! Initializes the quaternion components values all to zero, except \c W, which is
			set to one.
			\retval	SI_Error::SI_SUCCESS The quaternion was properly initialized.
			\sa CSIBCQuaternion::CSIBCQuaternion()
			\sa CSIBCQuaternion::Init
		*/
        inline SI_Error Init();

		/*! Initializes the quaternion component values to those of \p in_quat.
			\param[in]	in_quat	The quaternion from which to copy initialization values.
			\retval	SI_Error::SI_SUCCESS The quaternion was properly initialized.
			\sa CSIBCQuaternion::CSIBCQuaternion(CSIBCQuaternion &)
			\sa CSIBCQuaternion::Init
		*/
        SI_Error Init(CSIBCQuaternion &in_quat);

		/*! Initializes the quaternion components values to the values given.
			\param[in]	in_dX	The new value for the X component of the quaternion.
			\param[in]	in_dY	The new value for the Y component of the quaternion.
			\param[in]	in_dZ	The new value for the Z component of the quaternion.
			\param[in]	in_dW	The new value for the W component of the quaternion.
			\retval	SI_Error::SI_SUCCESS The quaternion was properly initialized.
			\sa CSIBCQuaternion::Init
			\sa CSIBCQuaternion::Set
		*/
        SI_Error Init(SI_Float in_dX,
                      SI_Float in_dY,
                      SI_Float in_dZ,
                      SI_Float in_dW);

		/*! Initializes the quaternion to the quaternion represented by the euler rotations
			given by the euler angles (pitch-roll-yaw) of the parameters.
			\param[in]	in_dX	Value for the pitch euler angle, for the quaternion value.
			\param[in]	in_dY	Value for the roll euler angle, for the quaternion value.
			\param[in]	in_dZ	Value for the yaw euler angle, for the quaternion value.
			\retval	SI_Error::SI_SUCCESS The quaternion was properly initialized.
			\sa CSIBCQuaternion::Init
		*/
        SI_Error Init(SI_Float in_dX, SI_Float in_dY, SI_Float in_dZ);

		/*! Returns the X component of the quaternion.
			\return	The X component of the quaternion.
			\sa CSIBCQuaternion::GetY
			\sa CSIBCQuaternion::GetZ
			\sa CSIBCQuaternion::GetW
			\sa CSIBCQuaternion::SetX
		*/
        SI_Float GetX() const { return m_fX; }

		/*! Returns the Y component of the quaternion.
			\return	The Y component of the quaternion.
			\sa CSIBCQuaternion::GetX
			\sa CSIBCQuaternion::GetZ
			\sa CSIBCQuaternion::GetW
			\sa CSIBCQuaternion::SetY
		*/
        SI_Float GetY() const { return m_fY; }

		/*! Returns the Z component of the quaternion.
			\return	The Z component of the quaternion.
			\sa CSIBCQuaternion::GetX
			\sa CSIBCQuaternion::GetY
			\sa CSIBCQuaternion::GetW
			\sa CSIBCQuaternion::SetZ
		*/
        SI_Float GetZ() const { return m_fZ; }

		/*! Returns the W component of the quaternion.
			\return	The W component of the quaternion.
			\sa CSIBCQuaternion::GetX
			\sa CSIBCQuaternion::GetY
			\sa CSIBCQuaternion::GetZ
			\sa CSIBCQuaternion::SetW
		*/
        SI_Float GetW() const { return m_fW; }

		/*! Sets the X component of the quaternion.
			\param[in]	in_dX	The new values for the X component of the quaternion.
			\retval	SI_Error::SI_SUCCESS The quaternion was properly set.
			\sa CSIBCQuaternion::Set
			\sa CSIBCQuaternion::SetY
			\sa CSIBCQuaternion::SetZ
			\sa CSIBCQuaternion::SetW
			\sa CSIBCQuaternion::GetX
		*/
		inline SI_Error SetX(SI_Float in_dX);

		/*! Sets the Y component of the quaternion.
			\param[in]	in_dY	The new values for the Y component of the quaternion.
			\retval	SI_Error::SI_SUCCESS The quaternion was properly set.
			\sa CSIBCQuaternion::Set
			\sa CSIBCQuaternion::SetX
			\sa CSIBCQuaternion::SetZ
			\sa CSIBCQuaternion::SetW
			\sa CSIBCQuaternion::GetY
		*/
        inline SI_Error SetY(SI_Float in_dY);

		/*! Sets the Z component of the quaternion.
			\param[in]	in_dZ	The new values for the Z component of the quaternion.
			\retval	SI_Error::SI_SUCCESS The quaternion was properly set.
			\sa CSIBCQuaternion::Set
			\sa CSIBCQuaternion::SetX
			\sa CSIBCQuaternion::SetY
			\sa CSIBCQuaternion::SetW
			\sa CSIBCQuaternion::GetZ
		*/
        inline SI_Error SetZ(SI_Float in_dZ);

		/*! Sets the W component of the quaternion.
			\param[in]	in_dW	The new values for the W component of the quaternion.
			\retval	SI_Error::SI_SUCCESS The quaternion was properly set.
			\sa CSIBCQuaternion::Set
			\sa CSIBCQuaternion::SetX
			\sa CSIBCQuaternion::SetY
			\sa CSIBCQuaternion::SetZ
			\sa CSIBCQuaternion::GetW
		*/
        inline SI_Error SetW(SI_Float in_dW);

		/*! Returns the rotation matrix corresponding to this quaternion. The quaternion must
			be a unit quaternion for this operation to succeed.
			\param[out]	out_mat	Reference to the matrix object to receive the rotation matrix.
			\retval	SI_Error::SI_SUCCESS The quaternion was properly converted.
			\retval	SI_Error::SI_ERR_ERROR_MSG The quaternion was not a unit quaternion.
			\sa CSIBCQuaternion::GetXYZRotation
			\sa CSIBCQuaternion::GetAxisAngle
		*/
		SI_Error GetMatrix(CSIBCMatrix4x4 &out_mat);

		/*! Returns the euler rotation angles (pitch-roll-yaw) represented by this quaternion.
			\param[out]	out_vect	Vector to receive the euler rotation angles.
			\retval	SI_Error::SI_SUCCESS The quaternion was properly converted.
			\sa CSIBCQuaternion::GetMatrix
			\sa CSIBCQuaternion::GetAxisAngle
		*/
        inline SI_Error GetXYZRotation(CSIBCVector3D &out_vect);

		/*! Returns the euler rotation angles (pitch-roll-yaw) represented by this quaternion.
			\param[out]	out_vect	Vector to receive the euler rotation angles.
			\param[in]	in_dX		Ignored.
			\param[in]	in_dY		Ignored.
			\param[in]	in_dZ		Ignored.
			\retval	SI_Error::SI_SUCCESS The quaternion was properly converted.
			\sa CSIBCQuaternion::GetMatrix
			\sa CSIBCQuaternion::GetAxisAngle
		*/
        SI_Error GetXYZRotation(SI_Float in_dX,
                                SI_Float in_dY,
                                SI_Float in_dZ,
                                CSIBCVector3D &out_vect);

		/*! Returns the axis of rotation, and rotation angle about the axis, that is
			represented by this quaternion.
			\param[out]	out_vAxis	Receives the axis of rotation.
			\param[out]	out_fAngle	Receives the angle of rotation about the axis (in radians).
			\retval	SI_Error::SI_SUCCESS The quaternion was properly converted.
			\retval	SI_Error::SI_ERR_ERROR_MSG The quaternion could not be converted, axis components
				and angle are all zero.
			\sa CSIBCQuaternion::GetXYZRotation
		*/
		SI_Error GetAxisAngle(CSIBCVector3D &out_vAxis,
                              float &out_fAngle);

		/*! Sets all components of the quaternion.
			\param[in]	in_dX	Value for the X component of the quaternion.
			\param[in]	in_dY	Value for the Y component of the quaternion.
			\param[in]	in_dZ	Value for the Z component of the quaternion.
			\param[in]	in_dW	Value for the W component of the quaternion.
			\retval	SI_Error::SI_SUCCESS The quaternion was properly set.
			\sa CSIBCQuaternion::SetX
			\sa CSIBCQuaternion::SetY
			\sa CSIBCQuaternion::SetZ
			\sa CSIBCQuaternion::SetW
		*/
        inline SI_Error Set(SI_Float in_dX,
                            SI_Float in_dY,
                            SI_Float in_dZ,
                            SI_Float in_dW);

		/*! Sets this quaternion equal to \p in_quat.
			\param[in]	in_quat	Quaternion to set this quaternion equal to.
			\sa CSIBCQuaternion::Init(CSIBCQuaternion &)
		*/
        inline void operator=(const CSIBCQuaternion &in_quat);

		/*! Tests to see whether this quaternion is valid. If the quaternion is invalid,
			an assertion will occur.
			\retval	SI_Error::SI_SUCCESS The quaternion is valid.
		*/
        inline SI_Error SelfTest();

    protected:

    private:

        // Attributes
        SI_Float m_fX, m_fY, m_fZ, m_fW;
};


#endif



