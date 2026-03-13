//*****************************************************************************
/*!
   \file xsi_rotationf.h
   \brief CRotationf class declaration.

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//*****************************************************************************
#ifndef __XSIROTATIONF_H__
#define __XSIROTATIONF_H__

#include "sicppsdk.h"
#include "xsi_math.h"
#include "xsi_vector3f.h"
#include "xsi_vector4f.h"
#include "xsi_matrix3f.h"
#include "xsi_quaternionf.h"

namespace XSI {

namespace MATH {

//*****************************************************************************
/*! \class CRotationf xsi_rotationf.h
	\brief Provides conversion facilities for various rotation representations
	including Euler angles, Quaternion, Axis angle and rotation matrix. CRotationf is typically used for
	implementing custom ICE nodes.

	\note All angle values are expressed in radians.

	\sa CQuaternionf
 */
//*****************************************************************************
class SICPPSDKDECL CRotationf
{
public:
	/*! Defines the rotation order of a rotation for the Euler angles representation.
	*/
	enum RotationOrder
	{
		siXYZ = 0,	/*!< X, Y, Z order */
		siXZY = 1,	/*!< X, Z, Y order  */
		siYXZ = 2,	/*!< Y, X, Z order  */
		siYZX = 3,	/*!< Y, Z, X order  */
		siZXY = 4,	/*!< Z, X, Y order  */
		siZYX = 5	/*!< Z, Y, X order  */
	};

	/*! Defines the rotation representation.
	*/
	enum RotationRep
	{
		siQuaternionRot = 0,	/*!< Quaternion representation */
		siEulerRot,				/*!< Euler representation */
		siAxisAngleRot			/*!< Axis angle representation */
	};

	/*! Default constructor. */
	SICPPSDK_INLINE CRotationf();

	/*! Copy constructor.
	\param in_rotation Rotation to copy
	 */
	SICPPSDK_INLINE CRotationf( const CRotationf& in_rotation);

	/*! Constructor (from CVector3f of Euler angles).
	\param in_EulerAngles Euler angles to construct from
	\param in_RotOrder Rotation order to use
	\sa CRotationf::Set, CRotationf::SetOrder
	*/
	SICPPSDK_INLINE CRotationf( const CVector3f &in_EulerAngles, const RotationOrder in_RotOrder = siXYZ);

	/*! Constructor (from XYZ Euler angles).
	\param in_X X angle
	\param in_Y Y angle
	\param in_Z Z angle
	\param in_RotOrder Rotation order to use
	\sa CRotationf::Set, CRotationf::SetOrder
	*/
	SICPPSDK_INLINE CRotationf( const float in_X, const float in_Y, const float in_Z, const RotationOrder in_RotOrder = siXYZ);

	/*! Constructor (from a quaternion).
	\param in_Quat Quaternion to construct from
	\sa CRotationf::GetQuaternion, CRotationf::Set
	*/
	SICPPSDK_INLINE CRotationf( const CQuaternionf &in_Quat );

	/*! Constructor (using axis angle representation).
	\param in_Axis Axis of rotation
	\param in_Angle Rotation angle around the axis
	\sa CRotationf::GetAxisAngle, CRotationf::Set
	*/
	SICPPSDK_INLINE CRotationf( const CVector3f &in_Axis, const float in_Angle );

	/*! Default destructor. */
	SICPPSDK_INLINE ~CRotationf();

	/*! Assignment operator.
	\param in_rotation Rotation to copy
	\return A reference to this rotation.
	 */
	SICPPSDK_INLINE CRotationf & operator=( const CRotationf & in_rotation);

	/*! Returns the euler angles of the rotation as a CVector3f from a rotation order.
	\param in_Order Rotation order
	\return CVector3f Rotation euler angle vector
	\sa CRotationf::Set, CRotationf::GetOrder
	*/
	SICPPSDK_INLINE CVector3f GetXYZAngles(const RotationOrder in_Order) const;

	/*! Returns the Euler angles's representation of the rotation.
	\param io_X X angle
	\param io_Y Y angle
	\param io_Z Z angle
	\sa CRotationf::Set, CRotationf::GetOrder
	*/
	SICPPSDK_INLINE void GetXYZAngles( float &io_X, float &io_Y, float &io_Z ) const;

	/*! Returns the Euler angles's representation of the rotation.
	\return Euler vector
	\sa CRotationf::Set, CRotationf::GetOrder
	*/
	SICPPSDK_INLINE CVector3f GetXYZAngles( ) const;

	/*! Returns the rotation order of this rotation for the Euler angles representation.
	\return CRotationf::RotationOrder
	*/
	SICPPSDK_INLINE RotationOrder GetOrder() const;

	/*! Sets the rotation order for the Euler angles representation.
	\param in_rotOrder New rotation order to use
	\sa CRotationf::GetOrder
	*/
	SICPPSDK_INLINE void SetOrder( const RotationOrder in_rotOrder );

	/*! Returns the rotation representation of this rotation.
	\return CRotationf::RotationRep
	*/
	SICPPSDK_INLINE RotationRep GetRepresentation() const;

	/*! Sets the rotation representation for this rotation.
	\param in_rotRep Rotation representation to set
	\param in_order New rotation order to use
	\sa CRotationf::GetOrder
	*/
	SICPPSDK_INLINE void SetRepresentation( const RotationRep in_rotRep, const RotationOrder in_order = siXYZ );

	/*! Change the current rotation from a rotation order with the option of preserving the overall rotation matrix. If
	in_bCompensate is true then XYZ rotation angles will be recomputed based on the new rotation order to maintain the
	overall rotation (so the object's orientation will not change). If false (default), then the XYZ rotation angles are
	preserved but combined in a different order so the overall rotation will change (the object's orientation will change).

	\param in_order Rotation order type.
	\param in_bCompensate Compensation flag.
	\return This rotation
	\sa CRotationf::SetOrder
	*/
	SICPPSDK_INLINE CRotationf& Set( const RotationOrder in_order, const bool in_bCompensate = false );

	/*! Sets the current rotation from Euler angles.
	\param in_EulerAngles Vector containing the rotation angles
	\param in_Order Rotation order
	\return This rotation
	\sa CRotationf::GetXYZAngles, CRotationf::SetOrder
	*/
	SICPPSDK_INLINE CRotationf& Set( const CVector3f &in_EulerAngles, const RotationOrder in_Order = siXYZ);

	/*! Sets the rotation from Euler angles.
	\param in_X X angle
	\param in_Y Y angle
	\param in_Z Z angle
	\param in_Order Requested rotation order
	\return This rotation
	\sa CRotationf::GetXYZAngles, CRotationf::SetOrder
	*/
	SICPPSDK_INLINE CRotationf& Set( const float in_X, const float in_Y, const float in_Z, const RotationOrder in_Order = siXYZ);

	/*! Sets the rotation from a quaternion.
	\param in_Quat Quaternion to set from
	\return This rotation
	\sa CRotationf::GetQuaternion
	*/
	SICPPSDK_INLINE CRotationf& Set( const CQuaternionf &in_Quat);

	/*! Multiplies this rotation with another one in place.
	\param in_rot Rotation to multiply
	\return This rotation
	*/
	SICPPSDK_INLINE CRotationf& Mul( const CRotationf &in_rot );

	/*! Stores the result of the multiplication of two rotations.
	\param in_rot1 First rotation
	\param in_rot2 Second rotation
	\return This rotation
	*/
	SICPPSDK_INLINE CRotationf& Mul( const CRotationf &in_rot1, const CRotationf &in_rot2 );

	/*! Multiply in-place this rotation with a scalar.
	\param in_scalar scalar multiplier.
	\return This rotation
	*/
	SICPPSDK_INLINE CRotationf& Mul( const float in_scalar );

	/*! Left multiply in-place this rotation with a rotation.
	\param in_rot Rotation operand
	\return This rotation
	*/
	SICPPSDK_INLINE CRotationf& LeftMul( const CRotationf &in_rot );

	/*! Interpolate two rotations into this one for in_u between 0 and 1.
	\param in_rot1 Starting rotation.
	\param in_rot2 Ending rotation.
	\param in_u Interpolation factor between 0 (starting rotation) and 1 (ending rotation).
	\return This rotation.
	*/
	SICPPSDK_INLINE CRotationf& Interpolate( const CRotationf& in_rot1, const CRotationf& in_rot2, const float in_u );

	/*! Divides in-place this rotation with the specified rotation and scalar.
	\param in_rot1 Rotation divisor
	\param in_scalar Scalar multiplier.
	\return This rotation
	*/
	SICPPSDK_INLINE CRotationf& Div ( const CRotationf& in_rot1, const float in_scalar );

	/*! Divides in-place this rotation with a scalar.
	\param in_scalar scalar multiplier.
	\return This rotation
	*/
	SICPPSDK_INLINE CRotationf& Div ( const float in_scalar );

	/*! Divides in-place by a rotation. Same as Mul by Invert.
	\param in_rot Rotation operand.
	\return This rotation
	*/
	SICPPSDK_INLINE CRotationf& Div( const CRotationf& in_rot );

	/*! Divide in-place in_rot1 by in_rot2. Same as Mul by Invert.
	\param in_rot1 First rotation operand.
	\param in_rot2 Second rotation operand.
	\return This rotation
	*/
	SICPPSDK_INLINE CRotationf& Div( const CRotationf& in_rot1, const CRotationf& in_rot2 );

	/*! Inverts the rotation in place.
	\return This rotation
	*/
	SICPPSDK_INLINE CRotationf& Invert();

	/*! Stores the invert of a rotation.
	\param in_rot Rotation to invert
	\return This rotation
	*/
	SICPPSDK_INLINE CRotationf& Invert( const CRotationf &in_rot );

	/*! Returns the quaternion representation of the rotation.
	\return CQuaternionf
	\sa CRotationf::Set
	*/
	SICPPSDK_INLINE CQuaternionf GetQuaternion() const;

	/*! Sets the rotation from a quaternion.
	\param in_Quat Quaternion to set from
	\return This rotation
	\sa CRotationf::Set
	*/
	SICPPSDK_INLINE CRotationf& operator = ( const CQuaternionf &in_Quat );

	/*! Returns the axis angle representation of the rotation.
	\param io_Angle Rotation angle around the axis
	\return CVector3f Axis of rotation
	\sa CRotationf::Set
	*/
	SICPPSDK_INLINE CVector3f GetAxisAngle( float &io_Angle) const;

	/*! Sets the rotation from an axis angle.
	\param in_Axis Axis of rotation
	\param in_Angle Rotation angle around the axis
	\return This rotation
	\sa CRotationf::GetAxisAngle
	*/
	SICPPSDK_INLINE CRotationf& Set( const CVector3f &in_Axis,  const float in_Angle );

	/*! Sets the rotation to identity rotation.
	*/
	SICPPSDK_INLINE void SetIdentity();

	/*! Performs exact comparison of two quaternions.
	\note Each parameter of both quaternions must be exactly the same for a match.
	\param in_rot Rotation to compare against
	\sa CRotationf::EpsilonEquals
	*/
	SICPPSDK_INLINE bool Equals( const CRotationf &in_rot ) const;

	/*! Performs comparison between this rotation and \c in_rot within the specified epsilon value.
	\param in_rot Rotation to compare against.
	\param in_fEpsilon Tolerance value
	\sa CRotationf::EpsilonEquals
	*/
	SICPPSDK_INLINE bool EpsilonEquals( const CRotationf& in_rot, const float in_fEpsilon ) const;

	/*! Performs exact comparison of two quaternions.
	\note Each parameter of both quaternions must be exactly the same for a match.
	\param in_rot Rotation to compare against
	\sa CRotationf::EpsilonEquals, CRotationf::Equals
	*/
	SICPPSDK_INLINE bool operator == ( const CRotationf &in_rot ) const;

	/*! Inequality operator tests the strict inequality of this rotation with the rotation in_rotation.
	\param in_rot Operand rotation.
	\return true if equal else false.
	\sa CRotationf::Equals
	 */
	SICPPSDK_INLINE bool operator !=(const CRotationf & in_rot ) const;

	/*! Less than operator. Performs a comparison with a specified CRotationf to determine if this CRotationf is
	less than the specified CRotationf. The comparison is arbitrary and not geometrically meaningful, it's only purpose is
	to make CRotationf compliant with stl for sorting operations.
	\param in_rot CRotationf to compare.
	\return true if this CRotationf is less than the specified CRotationf, false otherwise.
	\since 7.5
	*/
	SICPPSDK_INLINE bool operator < ( const CRotationf& in_rot ) const;

private:
	SICPPSDK_INLINE void QuatToEuler( const CQuaternionf& in_quat, CVector3f& out_vct, const RotationOrder in_eOrder );
	SICPPSDK_INLINE void QuatToMat( const CQuaternionf& in_quat, CMatrix3f& out_mat );
	SICPPSDK_INLINE void AxisAngleToQuat( const CVector3f& in_vctAxis, const float in_fAngle, CQuaternionf& out_quat);
	SICPPSDK_INLINE void QuatToAxisAngle(const CQuaternionf& in_quat, CVector3f& out_vctAxis, float& out_fAngle );

	SICPPSDK_INLINE RotationOrder GetRotOrder() const;

	float m_X, m_Y, m_Z;
	union
	{
		float			m_W;			// Quaternion W component
		float			m_Angle;		// Angle for axis/angle
		RotationOrder	m_rotOrder;		// Euler rotation order
	};
	unsigned char m_rotRep;				// Rotation representation
};

SICPPSDK_INLINE CRotationf::CRotationf()
{
	m_X = m_Y = m_Z = 0.0;
	m_W = 1.0;
	m_rotRep = siQuaternionRot;
}

SICPPSDK_INLINE CRotationf::CRotationf( const CRotationf& in_rotation)
{
	*this = in_rotation;
}

SICPPSDK_INLINE CRotationf::CRotationf( const CQuaternionf& in_quat )
{
	Set( in_quat );
}

SICPPSDK_INLINE CRotationf::CRotationf( const CVector3f &in_Angles, const RotationOrder in_Order)
{
	Set( in_Angles, in_Order );
}

SICPPSDK_INLINE CRotationf::CRotationf( const CVector3f &in_Axis, const float in_fAngle )
{
	Set( in_Axis, in_fAngle );
}

SICPPSDK_INLINE CRotationf::CRotationf( float in_fX, float in_fY, float in_fZ, const RotationOrder in_Order )
{
	Set( in_fX, in_fY, in_fZ, in_Order );
}

SICPPSDK_INLINE CRotationf::~CRotationf()
{
}

SICPPSDK_INLINE CRotationf& CRotationf::operator=( const CRotationf & in_rotation)
{
	m_X = in_rotation.m_X;
	m_Y = in_rotation.m_Y;
	m_Z = in_rotation.m_Z;
	m_W = in_rotation.m_W;
	m_rotRep = in_rotation.m_rotRep;
	return *this;
}

SICPPSDK_INLINE CRotationf& CRotationf::Set( const CVector3f &in_AngleValues, const RotationOrder in_Order )
{
	return Set( in_AngleValues.GetX(), in_AngleValues.GetY(), in_AngleValues.GetZ(), in_Order );
}

SICPPSDK_INLINE CRotationf& CRotationf::Set
(
	const float in_fX,
	const float in_fY,
	const float in_fZ,
	const RotationOrder in_Order
)
{
	m_rotRep = siEulerRot;
	m_rotOrder = in_Order;
	m_X = in_fX; m_Y = in_fY; m_Z = in_fZ;

	return *this;
}

SICPPSDK_INLINE CRotationf& CRotationf::Set( const RotationOrder in_order, const bool in_bCompensate )
{
	if ( m_rotRep != siEulerRot )
	{
		SetRepresentation( siEulerRot, in_bCompensate ? in_order : siXYZ );
	}

	if ( in_order != m_rotRep )
	{
		if ( in_bCompensate )
		{
			CMatrix3f vRotTmp;
			CVector3f vEuler( m_X, m_Y, m_Z );
			XSI::MATH::EulerToMat( vEuler, vRotTmp, (int)m_rotOrder );

			vEuler.SetNull( );
			XSI::MATH::MatToEuler( vRotTmp, vEuler, in_order );
			vEuler.Get( m_X, m_Y, m_Z );
		}
		m_rotOrder = in_order;
	}
	return *this;
}

SICPPSDK_INLINE CRotationf& CRotationf::Set( const CQuaternionf &in_Quat )
{
	m_rotRep = siQuaternionRot;

	m_W = in_Quat.GetW();
	m_X = in_Quat.GetX();
	m_Y = in_Quat.GetY();
	m_Z = in_Quat.GetZ();

	return *this;
}

SICPPSDK_INLINE CRotationf::RotationOrder CRotationf::GetRotOrder() const
{
	return ( m_rotRep == siEulerRot ? m_rotOrder : siXYZ );
}

SICPPSDK_INLINE CVector3f CRotationf::GetXYZAngles(const RotationOrder in_Order) const
{
	CVector3f outV;
	if ( m_rotRep == siEulerRot && m_rotOrder == in_Order )
	{
		outV.Set( m_X, m_Y, m_Z );
	}
	else
	{
		CRotationf rot( *this );
		rot.Set( in_Order, true );
		outV.Set( rot.m_X, rot.m_Y, rot.m_Z );
	}
	return outV;
}

SICPPSDK_INLINE void CRotationf::GetXYZAngles( float &io_fX, float &io_fY, float &io_fZ ) const
{
	CVector3f vEuler = GetXYZAngles( GetRotOrder() );
	vEuler.Get( io_fX, io_fY, io_fZ );
}

SICPPSDK_INLINE CVector3f CRotationf::GetXYZAngles() const
{
	return GetXYZAngles( GetRotOrder() );
}

SICPPSDK_INLINE CRotationf& CRotationf::Mul( const CRotationf &in_rot )
{
	return Mul( *this, in_rot );
}

SICPPSDK_INLINE CRotationf& CRotationf::Mul( const CRotationf &in_rot1, const CRotationf &in_rot2 )
{
	CQuaternionf q1 = in_rot1.GetQuaternion();
	CQuaternionf q2 = in_rot2.GetQuaternion();
	q2.Mul( q1 ).NormalizeInPlace();
	return Set( q2 );
}

SICPPSDK_INLINE CRotationf& CRotationf::Mul( const float in_scalar )
{
	switch (m_rotRep)
	{
		case siQuaternionRot:
		case siEulerRot:
		{
			CRotationf identity;
			Interpolate( identity, *this, in_scalar );
		}
		break;

		case siAxisAngleRot:
		{
			m_Angle *= in_scalar;
		}
		break;
	}
	return *this;
}

SICPPSDK_INLINE CRotationf& CRotationf::Div( const CRotationf &in_rot )
{
	return Div( *this, in_rot );
}

SICPPSDK_INLINE CRotationf& CRotationf::Div( const float in_scalar )
{
	return Mul( 1.0f/in_scalar );
}

SICPPSDK_INLINE CRotationf& CRotationf::Div( const CRotationf &in_rot1, const CRotationf &in_rot2 )
{
	CRotationf rotInv;
	return Mul( in_rot1, rotInv.Invert(in_rot2) );
}

SICPPSDK_INLINE CRotationf& CRotationf::LeftMul( const CRotationf &in_rot )
{
	return Mul( in_rot, *this );
}

SICPPSDK_INLINE CRotationf& CRotationf::Interpolate ( const CRotationf& in_rot1, const CRotationf& in_rot2, const float in_u )
{
	CQuaternionf q1 = in_rot1.GetQuaternion();
	CQuaternionf q2 = in_rot2.GetQuaternion();
	CQuaternionf q;
	q.Slerp( q1, q2, in_u );
	return Set( q );
}

SICPPSDK_INLINE CRotationf& CRotationf::Invert( )
{
	static RotationOrder InvRotOrder[] = { siZYX, siYZX, siZXY, siXZY, siYXZ, siXYZ };

	switch (m_rotRep)
	{
		case siQuaternionRot:
			m_X = -m_X; m_Y = -m_Y; m_Z = -m_Z;
			break;
		case siEulerRot:
			m_rotOrder = InvRotOrder[m_rotOrder];
			m_X = -m_X; m_Y = -m_Y; m_Z = -m_Z;
			break;
		case siAxisAngleRot:
			m_Angle = -m_Angle;
			break;
	}
	return *this;
}

SICPPSDK_INLINE CRotationf& CRotationf::Invert( const CRotationf &in_rot )
{
	*this = in_rot;
	return Invert( );
}

SICPPSDK_INLINE CVector3f CRotationf::GetAxisAngle( float &io_fAngle ) const
{
	CVector3f out_axis;
	if ( m_rotRep == siAxisAngleRot )
	{
		out_axis.Set( m_X, m_Y, m_Z );
		io_fAngle = m_Angle;
	}
	else
	{
		CRotationf rot( *this );
		rot.SetRepresentation( siAxisAngleRot );
		out_axis.Set( rot.m_X, rot.m_Y, rot.m_Z );
		io_fAngle = rot.m_Angle;
	}
	return out_axis;
}

SICPPSDK_INLINE CRotationf& CRotationf::Set( const CVector3f &in_axis, const float in_fAngle )
{
	m_rotRep = siAxisAngleRot;
	m_Angle = in_fAngle;
	in_axis.Get( m_X, m_Y, m_Z );

	return *this;
}

SICPPSDK_INLINE void CRotationf::SetIdentity()
{
	switch (m_rotRep)
	{
		case siQuaternionRot:
			m_W = 1.0; m_X = m_Y = m_Z = 0.0;
			break;
		case siEulerRot:
			m_X = m_Y = m_Z = 0.0; m_rotOrder = siXYZ;
			break;
		case siAxisAngleRot:
			m_Angle = 0.0; m_X = 1.0; m_Y = m_Z = 0.0;
			break;
	}
}

SICPPSDK_INLINE CRotationf::RotationOrder CRotationf::GetOrder() const
{
	return m_rotOrder;
}

SICPPSDK_INLINE CRotationf::RotationRep CRotationf::GetRepresentation() const
{
	return (CRotationf::RotationRep)m_rotRep;
}

void CRotationf::SetRepresentation( const RotationRep in_rep, const RotationOrder in_order )
{
	if ( m_rotRep != in_rep )
	{
		switch( in_rep )
		{
			case siQuaternionRot:
			{
				CQuaternionf l_quat;
				switch ( m_rotRep )
				{
					case siEulerRot:
					{
						CVector3f l_euler( m_X, m_Y, m_Z );
						XSI::MATH::EulerToQuat( l_euler, l_quat, m_rotOrder );
					}
					break;
					case siAxisAngleRot:
					{
						CVector3f l_axis( m_X, m_Y, m_Z );
						if ( l_axis.GetLength() > MicroEPS )
						{
							l_axis.NormalizeInPlace();
							AxisAngleToQuat( l_axis, m_Angle, l_quat );
						}
					}
					break;
				}
				*this = l_quat;
			}
			break;

			case siEulerRot:
			{
				CVector3f l_euler;
				switch ( m_rotRep )
				{
					case siQuaternionRot:
					{
						CQuaternionf l_quat( m_W, m_X, m_Y, m_Z );
						l_quat.NormalizeInPlace();
						QuatToEuler( l_quat, l_euler, in_order );
					}
					break;
					case siAxisAngleRot:
					{
						CQuaternionf l_quat;
						CVector3f l_axis( m_X, m_Y, m_Z );
						if ( l_axis.GetLength() > MicroEPS )
						{
							l_axis.NormalizeInPlace();
							AxisAngleToQuat( l_axis, m_Angle, l_quat );
						}
						QuatToEuler( l_quat, l_euler, in_order );
					}
					break;
				}
				Set( l_euler, in_order );
			}
			break;
			case siAxisAngleRot:
			{
				float l_angle = 0;
				CVector3f l_axis;
				switch ( m_rotRep )
				{
					case siQuaternionRot:
					{
						CQuaternionf l_quat( m_W, m_X, m_Y, m_Z );
						l_quat.NormalizeInPlace();
						QuatToAxisAngle( l_quat, l_axis, l_angle );
					}
					break;

					case siEulerRot:
					{
						CQuaternionf l_quat;
						CVector3f l_euler( m_X, m_Y, m_Z );
						XSI::MATH::EulerToQuat( l_euler, l_quat, m_rotOrder );
						QuatToAxisAngle( l_quat, l_axis, l_angle );
					}
					break;
				}

				if ( l_axis.IsNull() )
				{
					l_axis.Set(1.0, 0.0, 0.0); // If axis is undefined set it to a valid axis
				}
				Set( l_axis, l_angle );
			}
			break;
		}
	}
}

SICPPSDK_INLINE CQuaternionf CRotationf::GetQuaternion() const
{
	CQuaternionf out_quat;
	if ( m_rotRep == siQuaternionRot )
	{
		out_quat.Set( m_W, m_X, m_Y, m_Z );
	}
	else
	{
		CRotationf rot( *this );
		rot.SetRepresentation( siQuaternionRot );
		out_quat.Set( rot.m_W, rot.m_X, rot.m_Y, rot.m_Z );
	}
	return out_quat;
}

SICPPSDK_INLINE CRotationf& CRotationf::operator = ( const CQuaternionf &in_Quat )
{
	return Set( in_Quat );
}

SICPPSDK_INLINE bool CRotationf::Equals( const CRotationf &in_rot ) const
{
	if (this == &in_rot) return true;

	CQuaternionf q1 = GetQuaternion();
	CQuaternionf q2 = in_rot.GetQuaternion();

	return (true == ( q1 == q2) );
}

SICPPSDK_INLINE bool CRotationf::EpsilonEquals( const CRotationf& in_rot, const float in_fEpsilon ) const
{
	CRotationf r1( *this );
	CRotationf r2( in_rot );
	if ( r1.GetRepresentation() != r2.GetRepresentation() )
	{
		r2.SetRepresentation( r1.GetRepresentation() );
	}
	switch (r1.GetRepresentation())
	{
		case siQuaternionRot:
		{
			return r1.GetQuaternion().EpsilonEquals( r2.GetQuaternion(), in_fEpsilon );
		}
		case siEulerRot:
		{
			return ( r1.GetOrder() == r2.GetOrder() && r1.GetXYZAngles().EpsilonEquals( r2.GetXYZAngles(), in_fEpsilon ) );
		}
		case siAxisAngleRot:
		{
			float a1, a2;
			CVector3f v1 = r1.GetAxisAngle( a1 );
			CVector3f v2 = r2.GetAxisAngle( a2 );
			return ( fabs( a1 - a2 ) < in_fEpsilon && v1.EpsilonEquals( v2, in_fEpsilon ) );
		}
		default:
			break;
	}
	return false;
}

SICPPSDK_INLINE bool CRotationf::operator == ( const CRotationf &in_rot ) const
{
	return Equals( in_rot );
}

SICPPSDK_INLINE bool CRotationf::operator != ( const CRotationf &in_rot ) const
{
	return ! Equals( in_rot );
}

SICPPSDK_INLINE bool CRotationf::operator < ( const CRotationf& in_rot) const
{
	if ( m_W != in_rot.m_W ) return m_W < in_rot.m_W;
	if ( m_Z != in_rot.m_Z ) return m_Z < in_rot.m_Z;
	if ( m_Y != in_rot.m_Y ) return m_Y < in_rot.m_Y;
	if ( m_X != in_rot.m_X ) return m_X < in_rot.m_X;
	if ( m_rotRep != in_rot.m_rotRep ) return m_rotRep < in_rot.m_rotRep;

	return false;
}

SICPPSDK_INLINE void CRotationf::QuatToMat( const CQuaternionf& in_quat, CMatrix3f& out_mat )
{
	float d2X, d2Y, d2Z, d2X2, d2Y2, d2Z2, d2WX, d2WY, d2WZ, d2XY, d2XZ, d2YZ;

	d2X = (float)2.0 * in_quat.GetX();
	d2Y = (float)2.0 * in_quat.GetY();
	d2Z = (float)2.0 * in_quat.GetZ();

	d2X2 = d2X * in_quat.GetX();
	d2Y2 = d2Y * in_quat.GetY();
	d2Z2 = d2Z * in_quat.GetZ();

	d2WX = d2X * in_quat.GetW();
	d2WY = d2Y * in_quat.GetW();
	d2WZ = d2Z * in_quat.GetW();
	d2XY = d2X * in_quat.GetY();
	d2YZ = d2Y * in_quat.GetZ();
	d2XZ = d2Z * in_quat.GetX();

	out_mat.SetValue( 0, 0, (float)1.0 - d2Y2 - d2Z2 );
	out_mat.SetValue( 1, 1, (float)1.0 - d2X2 - d2Z2 );
	out_mat.SetValue( 2, 2, (float)1.0 - d2X2 - d2Y2 );
	out_mat.SetValue( 0, 1, d2XY + d2WZ );
	out_mat.SetValue( 1, 0, d2XY - d2WZ );
	out_mat.SetValue( 0, 2, d2XZ - d2WY );
	out_mat.SetValue( 2, 0, d2XZ + d2WY );
	out_mat.SetValue( 1, 2, d2YZ + d2WX );
	out_mat.SetValue( 2, 1, d2YZ - d2WX );
}

SICPPSDK_INLINE void CRotationf::QuatToEuler( const CQuaternionf& in_quat, CVector3f& out_vct, const RotationOrder in_eOrder )
{
	CMatrix3f mat;
	QuatToMat( in_quat, mat );
	XSI::MATH::MatToEuler( mat, out_vct, in_eOrder);
}

SICPPSDK_INLINE void CRotationf::AxisAngleToQuat( const CVector3f& in_vctAxis, const float in_fAngle, CQuaternionf& out_quat)
{
	float fCos, fSin;
	CVector3f vct(in_vctAxis);

	fCos = cos( in_fAngle * 0.5f );
	fSin = sin( in_fAngle * 0.5f );

	vct.SetLength( fSin );
	out_quat.Set( fCos, vct.GetX(), vct.GetY(), vct.GetZ() );
}

SICPPSDK_INLINE void CRotationf::QuatToAxisAngle(const CQuaternionf& in_quat, CVector3f& out_vctAxis, float& out_fAngle )
{
	out_fAngle = (float)(2.0 * ::acos( in_quat.GetW() ));

	//from C3DRotation::GetAxisAngle();
	float fSin = (float)sin( 0.5f * out_fAngle );

	if( ::fabs( fSin ) < MicroEPS )
	{
		// If angle is almost zero, then axis of rotation is undefined.
		out_vctAxis.SetNull();
	}
	else
	{
		//Retrieve the axis of rotation
		fSin = 1.0f / fSin;
		out_vctAxis.PutX( in_quat.GetX() * fSin );
		out_vctAxis.PutY( in_quat.GetY() * fSin );
		out_vctAxis.PutZ( in_quat.GetZ() * fSin );
	}
}

};
};

#endif // __XSIROTATIONF_H__
