//*****************************************************************************
/*!
   \file xsi_color4f.h
   \brief CColor4f class declaration.

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//*****************************************************************************

#if (_MSC_VER > 1000) || defined(SGI_COMPILER)
#pragma once
#endif

#ifndef __XSICOLOR4F_H__
#define __XSICOLOR4F_H__

#include "sicppsdk.h"
#include <xsi_math.h>

namespace XSI {

namespace MATH {

//*****************************************************************************
/*! \class CColor4f xsi_color4f.h
	\brief A color class represented by single floating values. CColor4f supports
	the RGBA, HSVA and HLSA color models.
 */
//*****************************************************************************
class CColor4f
{
public:
	/*! Defines the color model types supported.
	*/
	enum Type
	{
		siRGBA,
		siHSVA,
		siHLSA,
	};

	/*! Default constructor. */
	SICPPSDK_INLINE CColor4f();

	/*! Constructor.
	\param in_R Red component
	\param in_G Green component
	\param in_B Blue component
	\param in_A Alpha component
	*/
	SICPPSDK_INLINE CColor4f(float in_R, float in_G, float in_B, float in_A);

	/*! Constructor. Creates a new object of a specific color type .
	\param in_Arg1 Component 1
	\param in_Arg2 Component 2
	\param in_Arg3 Component 3
	\param in_A Alpha component
	\param in_eColorType Color type
	*/
	SICPPSDK_INLINE CColor4f(float in_Arg1, float in_Arg2, float in_Arg3, float in_A, Type in_eColorType );

	/*! Copy constructor. Cretaes a new object as a RGBA type.
	\param in_color CColor4f object.
	 */
	SICPPSDK_INLINE CColor4f( const CColor4f& in_color );

	/*! Destructor. */
	~CColor4f() {};

	/*! Set the object with new values.
	\param in_R Red component
	\param in_G Green component
	\param in_B Blue component
	\param in_A Alpha component
	*/
	SICPPSDK_INLINE void Set(float in_R,float in_G,float in_B,float in_A);

	/*! Set the object with new values for a specific type.
	\param in_Arg1 Component 1
	\param in_Arg2 Component 2
	\param in_Arg3 Component 3
	\param in_A Alpha component
	\param in_eColorType Color type
	*/
	SICPPSDK_INLINE void Set( float in_Arg1, float in_Arg2, float in_Arg3, float in_A, Type in_eColorType );

	/*! Set the object's red component.
	\param in_R value
	\return Reference to new value
	*/
	SICPPSDK_INLINE float& PutR( const float in_R );

	/*! Set the object's green component.
	\param in_G value
	\return Reference to new value
	*/
	SICPPSDK_INLINE float& PutG( const float in_G );

	/*! Set the object's blue component.
	\param in_B value
	\return Reference to new value
	*/
	SICPPSDK_INLINE float& PutB( const float in_B );

	/*! Set the object's alpha component.
	\param in_A value
	\return Reference to new value
	*/
	SICPPSDK_INLINE float& PutA( const float in_A );

	/*! Returns the object's RGBA values.
	\retval out_R Red component
	\retval out_G Green component
	\retval out_B Blue component
	\retval out_A Alpha component
	*/
	SICPPSDK_INLINE void GetAsRGBA( float &out_R, float &out_G, float &out_B, float &out_A ) const;

	/*! Returns the object's HLSA values.
	\retval out_H Hue component
	\retval out_L Luminance component
	\retval out_S Saturation component
	\retval out_A Alpha component
	*/
	SICPPSDK_INLINE void GetAsHLSA( float &out_H, float &out_L, float &out_S, float &out_A ) const;

	/*! Returns the object's HSVA values.
	\retval out_H Hue component
	\retval out_S Saturation component
	\retval out_V Value component
	\retval out_A Alpha component
	*/
	SICPPSDK_INLINE void GetAsHSVA( float &out_H, float &out_S, float &out_V, float &out_A) const;

	/*! Return the object's hue component.
	\return Component value.
	*/
	SICPPSDK_INLINE float GetH() const;

	/*! Return the object's luminence component.
	\return Component value.
	*/
	SICPPSDK_INLINE float GetL() const;

	/*! Return the object's saturation component from the HSVA color space.
	\return Component value.
	*/
	SICPPSDK_INLINE float GetS_HSVA() const;

	/*! Return the object's saturation component from the HLSA color space.
	\return Component value.
	*/
	SICPPSDK_INLINE float GetS_HLSA() const;

	/*! Return the object's value component.
	\return Component value.
	*/
	SICPPSDK_INLINE float GetV() const;

	/*! Return the object's red component.
	\return Component value.
	*/
	SICPPSDK_INLINE float& GetR();

	/*! Return the object's green component.
	\return Component value.
	*/
	SICPPSDK_INLINE float& GetG();

	/*! Return the object's blue component.
	\return Component value.
	*/
	SICPPSDK_INLINE float& GetB();

	/*! Return the object's alpha component.
	\return Component value.
	*/
	SICPPSDK_INLINE float& GetA();

	/*! Return a pointer to the color component array.
	\return Component array.
	*/
	SICPPSDK_INLINE float* GetRGBA();

	/*! Return a reference on the object's red component.
	\return Reference to component value.
	*/
	SICPPSDK_INLINE const float& GetR()const;

	/*! Return a reference on the object's green component.
	\return Reference to component value.
	*/
	SICPPSDK_INLINE const float& GetG()const;

	/*! Return a reference on the object's blue component.
	\return Reference to component value.
	*/
	SICPPSDK_INLINE const float& GetB()const;

	/*! Return a reference on the object's alpha component.
	\return Reference to component value.
	*/
	SICPPSDK_INLINE const float& GetA()const;

	/*! Return a read-only pointer the color component array.
	\return Pointer to component array.
	*/
	SICPPSDK_INLINE const float* GetRGBA()const;

	/*! float cast operator which returns a pointer to the color component array.
	\return Pointer to component array.
	*/
	SICPPSDK_INLINE operator float*();

	/*! Performs exact comparison of two colors.
	\param in_rColor4f Color to compare against
	*/
	SICPPSDK_INLINE bool operator==(const CColor4f& in_rColor4f )const;

	/*! Inequality operator tests the strict inequality of this color with in_rColor4f.
	\param in_rColor4f Color to test against.
	*/
	SICPPSDK_INLINE bool operator!=(const CColor4f& in_rColor4f )const ;

	/*! Less than operator. Performs a comparison with a specified CColor4f to determine if this CColor4f is
	less than the specified CColor4f. The comparison is arbitrary and not geometrically meaningful, it's only purpose is
	to make CColor4f compliant with stl for sorting operations.
	\param in_rColor4f CColor4f to compare.
	\return true if this CColor4f is less than the specified CColor4f, false otherwise.
	\since 7.5
	*/
	SICPPSDK_INLINE bool operator < (const CColor4f& in_rColor4f )const;

	/*! Returns true if all component are less than a specific tolerance value.
	\param in_fEpsilon Tolerance to test against
	\return True is the color is null, false otherwise.
	*/
	SICPPSDK_INLINE bool IsNull(float in_fEpsilon) const;

	/*! Adds input color values to this object.
	\param in_col Color to add.
	\return A reference to this color.
	*/
	SICPPSDK_INLINE CColor4f& Add(const CColor4f& in_col);

	/*! Scales this color with a factor value.
	\param in_fFactor Multiply factor.
	\return A reference to this color.
	*/
	SICPPSDK_INLINE CColor4f& Mul(float in_fFactor);

	/*! Multiplies this color with an input color (this.R *= c.R, this.G *= c.G, etc...)
	\param in_col Color operand.
	\return A reference to this color.
	*/
	SICPPSDK_INLINE CColor4f& Mul( const CColor4f& in_col );

	/*! Subtracts the input color from this one.
	\param in_col Multiply factor.
	\return A reference to this color.
	*/
	SICPPSDK_INLINE CColor4f& Sub( const CColor4f& in_col );

	/*! Negates this color (this = - this).
	\return A reference to this color.
	*/
	SICPPSDK_INLINE CColor4f& Negate();

	/*! Sets all color components to 0.
	\return A reference to this color.
	*/
	SICPPSDK_INLINE void PutNull();

	/*! Returns the brightness value.
	\return Float value.
	*/
	SICPPSDK_INLINE float GetBrightness()const;

	/*! Returns the brightness value multiplied with the alpha component.
	\return Float value.
	*/
	SICPPSDK_INLINE float GetBrightnessWithAlpha()const;

	/*! Returns the grayscale value.
	\return Float value.
	*/
	SICPPSDK_INLINE float GetGrayscale()const;

	/*! Returns the grayscale value multiplied with the alpha component.
	\return Float value.
	*/
	SICPPSDK_INLINE float GetGrayscaleWithAlpha()const;

	/*! Inverts the component values for this color.
	\return A reference to this color.
	*/
	SICPPSDK_INLINE CColor4f& InverseRGB();

	private:
	SICPPSDK_INLINE LONG RoundDown(float a) const;
	SICPPSDK_INLINE void MinMax( float& out_fMin, float& out_fMax ) const;
	SICPPSDK_INLINE bool AreAlmostEqual(const CColor4f& in_c1,const CColor4f& in_c2,const float in_fEpsilon = MicroEPS);

	enum Component
	{
		R=0,G,B,A,N
	};
	float m_RGBA[4];
};

SICPPSDK_INLINE CColor4f::CColor4f()
{
	m_RGBA[R] = 0.0f;
	m_RGBA[G] = 0.0f;
	m_RGBA[B] = 0.0f;
	m_RGBA[A] = 0.0f;
}

SICPPSDK_INLINE CColor4f::CColor4f(float in_R, float in_G, float in_B, float in_A)
{
	m_RGBA[R] = in_R;
	m_RGBA[G] = in_G;
	m_RGBA[B] = in_B;
	m_RGBA[A] = in_A;
}

SICPPSDK_INLINE CColor4f::CColor4f(float in_Arg1, float in_Arg2, float in_Arg3, float in_A, Type in_eColorType )
{
	Set( in_Arg1, in_Arg2, in_Arg3, in_A, in_eColorType );
}

SICPPSDK_INLINE CColor4f::CColor4f( const CColor4f& in_color )
{
	const float* pRGBA = in_color.GetRGBA();
	if (pRGBA)
	{
		Set( pRGBA[R], pRGBA[G], pRGBA[B], pRGBA[A], siRGBA );
	}
}

SICPPSDK_INLINE void CColor4f::Set(float in_R,float in_G,float in_B,float in_A)
{
	GetR()=in_R;
	GetG()=in_G;
	GetB()=in_B;
	GetA()=in_A;
}

SICPPSDK_INLINE float& CColor4f::PutR( const float in_R ){return m_RGBA[R] = in_R;}
SICPPSDK_INLINE float& CColor4f::PutG( const float in_G ){return m_RGBA[G] = in_G;}
SICPPSDK_INLINE float& CColor4f::PutB( const float in_B ){return m_RGBA[B] = in_B;}
SICPPSDK_INLINE float& CColor4f::PutA( const float in_A ){return m_RGBA[A] = in_A;}

SICPPSDK_INLINE void CColor4f::Set( float in_Arg1, float in_Arg2, float in_Arg3, float in_A, Type in_eColorType )
{
	m_RGBA[A] = in_A;

	switch( in_eColorType )
	{
		case siRGBA:
		{
			m_RGBA[R] = in_Arg1;
			m_RGBA[G] = in_Arg2;
			m_RGBA[B] = in_Arg3;
			break;
		}
		case siHSVA:
		{
			if (in_Arg2 == 0.0)
			{
				m_RGBA[R] = in_Arg3;
				m_RGBA[G] = in_Arg3;
				m_RGBA[B] = in_Arg3;
			}
			else
			{
				in_Arg1 *= (float)( 360.0/60.0 );

				ULONG  l_ulHueI = (ULONG)RoundDown(in_Arg1);
				float l_fHueF = in_Arg1 - l_ulHueI;

				float l_fP = in_Arg3 * (1.0f - in_Arg2);
				float l_fQ = in_Arg3 * (1.0f - (in_Arg2*l_fHueF));
				float l_fT = in_Arg3 * (1.0f - (in_Arg2*(1.0f-l_fHueF)));

				switch (l_ulHueI)
				{
					case 0 :
					case 6 : m_RGBA[R] = in_Arg3; m_RGBA[G] = l_fT; m_RGBA[B] = l_fP;
						break;
					case 1 : m_RGBA[R] = l_fQ; m_RGBA[G] = in_Arg3; m_RGBA[B] = l_fP;
						break;
					case 2 : m_RGBA[R] = l_fP; m_RGBA[G] = in_Arg3; m_RGBA[B] = l_fT;
						break;
					case 3 : m_RGBA[R] = l_fP; m_RGBA[G] = l_fQ; m_RGBA[B] = in_Arg3;
						break;
					case 4 : m_RGBA[R] = l_fT; m_RGBA[G] = l_fP; m_RGBA[B] = in_Arg3;
						break;
					case 5 : m_RGBA[R] = in_Arg3; m_RGBA[G] = l_fP; m_RGBA[B] = l_fQ;
						break;
				}
			}

			break;
		}
		case siHLSA:
		{
			float l_fMax;

			if (in_Arg2 <= 0.5)
				l_fMax = in_Arg2 * (1.0f + in_Arg3);
			else
				l_fMax = in_Arg2 + in_Arg3 - (in_Arg2 * in_Arg3);

			if (l_fMax == 0.0f)
			{
				m_RGBA[R] = m_RGBA[G] = m_RGBA[B] = 0.0f;
			}
			else
			{
				in_Arg1 *= (float)( 360.0/60.0 );

				ULONG l_ulHueI = (ULONG)RoundDown(in_Arg1);
				float l_fHueF = in_Arg1 - l_ulHueI;

				float l_fMin  = 2.0f*in_Arg2 - l_fMax;
				float l_fQ    = l_fMax - ((l_fMax-l_fMin)*l_fHueF);
				float l_fT    = l_fMin + ((l_fMax-l_fMin)*l_fHueF);

				switch (l_ulHueI)
				{
					case 0 :
					case 6 : m_RGBA[R] = l_fMax; m_RGBA[G] = l_fT; m_RGBA[B] = l_fMin;
						break;
					case 1 : m_RGBA[R] = l_fQ; m_RGBA[G] = l_fMax; m_RGBA[B] = l_fMin;
						break;
					case 2 : m_RGBA[R] = l_fMin; m_RGBA[G] = l_fMax; m_RGBA[B] = l_fT;
						break;
					case 3 : m_RGBA[R] = l_fMin; m_RGBA[G] = l_fQ; m_RGBA[B] = l_fMax;
						break;
					case 4 : m_RGBA[R] = l_fT; m_RGBA[G] = l_fMin; m_RGBA[B] = l_fMax;
						break;
					case 5 : m_RGBA[R] = l_fMax; m_RGBA[G] = l_fMin; m_RGBA[B] = l_fQ;
						break;
				}
			}
			break;
		}
		default:
			assert( false );
	}
}

SICPPSDK_INLINE void CColor4f::GetAsRGBA( float &out_fRed, float &out_fGreen, float &out_fBlue, float &out_fAlpha ) const
{
	out_fRed = m_RGBA[R]; out_fGreen = m_RGBA[G]; out_fBlue = m_RGBA[B]; out_fAlpha = m_RGBA[A];
}

SICPPSDK_INLINE void CColor4f::GetAsHLSA( float &out_fHue, float &out_fLuminance, float &out_fSaturation, float &out_fAlpha ) const
{
	out_fAlpha = m_RGBA[A];

	float l_fMax , l_fMin;
	MinMax( l_fMin, l_fMax );
	float l_fDelta = l_fMax - l_fMin;

	out_fLuminance = (l_fMin + l_fMax) / 2.0f;

	if (l_fDelta == 0.0)
		out_fSaturation = 0.0;
	else
	{
		if (out_fLuminance <= 0.5f)
			out_fSaturation = l_fDelta / (l_fMin + l_fMax);
		else
			out_fSaturation = l_fDelta / (2.0f - (l_fMin + l_fMax));
	}

	if (out_fSaturation == 0.0f)
		out_fHue = 0;
	else
	{
		if (m_RGBA[R] == l_fMax)
			out_fHue = (m_RGBA[G]-m_RGBA[B])/l_fDelta;
		else if (m_RGBA[G] == l_fMax)
			out_fHue = 2+(m_RGBA[B]-m_RGBA[R])/l_fDelta;
		else
			out_fHue = 4+(m_RGBA[R]-m_RGBA[G])/l_fDelta;

		out_fHue *= 60;

		if (out_fHue < 0)
			out_fHue += 360.0;

		out_fHue = out_fHue / 360.0f;
	}
}

SICPPSDK_INLINE void CColor4f::GetAsHSVA( float &out_fHue, float &out_fSaturation, float &out_fValue, float &out_fAlpha ) const
{
	out_fAlpha = m_RGBA[A];

	float l_fMax , l_fMin;
	MinMax( l_fMin, l_fMax );
	float l_fDelta = l_fMax - l_fMin;

	out_fValue = l_fMax;

	if (l_fMax == 0.0)
		out_fSaturation = 0.0;
	else
		out_fSaturation = l_fDelta/l_fMax;

	if (out_fSaturation == 0.0)
	{
		out_fHue = 0;
	}
	else
	{
		if (m_RGBA[R] == l_fMax)
			out_fHue = (m_RGBA[G]-m_RGBA[B])/l_fDelta;
		else if (m_RGBA[G] == l_fMax)
			out_fHue = 2+(m_RGBA[B]-m_RGBA[R])/l_fDelta;
		else
			out_fHue = 4+(m_RGBA[R]-m_RGBA[G])/l_fDelta;

		out_fHue *= 60;

		if (out_fHue < 0)
			out_fHue += 360.0;

		out_fHue = out_fHue / 360.0f;
	}

}

SICPPSDK_INLINE float CColor4f::GetH() const
{
	float l_fMax , l_fMin;
	MinMax( l_fMin, l_fMax );
	float l_fDelta = l_fMax - l_fMin;

	if (l_fMax == 0.0f || l_fDelta == 0.0f)
	{
		return 0.0f;
	}
	else
	{
		float l_fHue;
		if (m_RGBA[R] == l_fMax)
			l_fHue = (m_RGBA[G]-m_RGBA[B])/l_fDelta;
		else if (m_RGBA[G] == l_fMax)
			l_fHue = 2+(m_RGBA[B]-m_RGBA[R])/l_fDelta;
		else
			l_fHue = 4+(m_RGBA[R]-m_RGBA[G])/l_fDelta;

		l_fHue *= 60;

		if (l_fHue < 0)
			l_fHue += 360.0;

		l_fHue = l_fHue / 360.0f;

		return l_fHue;
	}
}

SICPPSDK_INLINE float CColor4f::GetL() const
{
	float l_fMax , l_fMin;
	MinMax( l_fMin, l_fMax );

	return (l_fMin + l_fMax) / 2.0f;
}

SICPPSDK_INLINE float CColor4f::GetS_HSVA() const
{
	float l_fMax , l_fMin;
	MinMax( l_fMin, l_fMax );
	float l_fDelta = l_fMax - l_fMin;

	// calculate Saturation
	if (l_fMax == 0.0)
		return 0.0;
	else
		return l_fDelta / l_fMax;
}

SICPPSDK_INLINE float CColor4f::GetS_HLSA() const
{
	float l_fMax , l_fMin;
	MinMax( l_fMin, l_fMax );
	float l_fDelta = l_fMax - l_fMin;

	// calculate Saturation
	if (l_fDelta == 0.0)
		return 0.0;
	else
	{
		float l_fSumMinMax = l_fMin + l_fMax ;
		if ( l_fSumMinMax <= 1.0f )
			return l_fDelta / l_fSumMinMax;
		else
			return l_fDelta / (2.0f - l_fSumMinMax);
	}
}

SICPPSDK_INLINE float CColor4f::GetV() const
{
	if( m_RGBA[R] > m_RGBA[G] )
	{
		if( m_RGBA[R] > m_RGBA[B] )
			return m_RGBA[R];
		else
			return m_RGBA[B];
	}
	else
	{
		if( m_RGBA[G] > m_RGBA[B] )
			return m_RGBA[G];
		else
			return m_RGBA[B];
	}
}

SICPPSDK_INLINE float& CColor4f::GetR(){return m_RGBA[R];}
SICPPSDK_INLINE float& CColor4f::GetG(){return m_RGBA[G];}
SICPPSDK_INLINE float& CColor4f::GetB(){return m_RGBA[B];}
SICPPSDK_INLINE float& CColor4f::GetA(){return m_RGBA[A];}

SICPPSDK_INLINE float* CColor4f::GetRGBA(){return m_RGBA;}

SICPPSDK_INLINE const float& CColor4f::GetR()const{return m_RGBA[R];}
SICPPSDK_INLINE const float& CColor4f::GetG()const{return m_RGBA[G];}
SICPPSDK_INLINE const float& CColor4f::GetB()const{return m_RGBA[B];}
SICPPSDK_INLINE const float& CColor4f::GetA()const{return m_RGBA[A];}

SICPPSDK_INLINE const float* CColor4f::GetRGBA()const{return m_RGBA;}

SICPPSDK_INLINE CColor4f::operator float*(){return &(m_RGBA[0]);}

SICPPSDK_INLINE bool CColor4f::operator==(const CColor4f& in_rColor4f )const
{
	return	(m_RGBA[R] == in_rColor4f.m_RGBA[R]) &&
			(m_RGBA[G] == in_rColor4f.m_RGBA[G]) &&
			(m_RGBA[B] == in_rColor4f.m_RGBA[B]) &&
			(m_RGBA[A] == in_rColor4f.m_RGBA[A]);
}

SICPPSDK_INLINE bool CColor4f::operator!=(const CColor4f& in_rColor4f )const
{
	return !(	(m_RGBA[R] == in_rColor4f.m_RGBA[R]) &&
				(m_RGBA[G] == in_rColor4f.m_RGBA[G]) &&
				(m_RGBA[B] == in_rColor4f.m_RGBA[B]) &&
				(m_RGBA[A] == in_rColor4f.m_RGBA[A]));
}

SICPPSDK_INLINE bool CColor4f::operator < (const CColor4f& in_rColor4f )const
{
	if (m_RGBA[A] != in_rColor4f.m_RGBA[A]) return m_RGBA[A] < in_rColor4f.m_RGBA[A];
	if (m_RGBA[B] != in_rColor4f.m_RGBA[B]) return m_RGBA[B] < in_rColor4f.m_RGBA[B];
	if (m_RGBA[G] != in_rColor4f.m_RGBA[G]) return m_RGBA[G] < in_rColor4f.m_RGBA[G];
	if (m_RGBA[R] != in_rColor4f.m_RGBA[R]) return m_RGBA[R] < in_rColor4f.m_RGBA[R];
	return false;
}

SICPPSDK_INLINE bool CColor4f::IsNull(float in_fEpsilon) const
{
	return	fabsf( GetR() ) <= in_fEpsilon &&
			fabsf( GetG() ) <= in_fEpsilon &&
			fabsf( GetB() ) <= in_fEpsilon &&
			fabsf( GetA() ) <= in_fEpsilon;}

SICPPSDK_INLINE CColor4f& CColor4f::Add(const CColor4f& in_col)
{
	GetR() += in_col.GetR();
	GetG() += in_col.GetG();
	GetB() += in_col.GetB();
	GetA() += in_col.GetA();
	return *this;
}

SICPPSDK_INLINE CColor4f& CColor4f::Mul(float in_fFactor)
{
	GetR()*=in_fFactor;
	GetB()*=in_fFactor;
	GetG()*=in_fFactor;
	GetA()*=in_fFactor;
	return *this;
}

SICPPSDK_INLINE CColor4f& CColor4f::Sub( const CColor4f& in_col )
{
	GetR() -= in_col.GetR();
	GetG() -= in_col.GetG();
	GetB() -= in_col.GetB();
	GetA() -= in_col.GetA();
	return *this;
}

SICPPSDK_INLINE CColor4f& CColor4f::Mul( const CColor4f& in_col )
{
	GetR() *= in_col.GetR();
	GetG() *= in_col.GetG();
	GetB() *= in_col.GetB();
	GetA() *= in_col.GetA();
	return *this;
}

SICPPSDK_INLINE CColor4f& CColor4f::Negate()
{
	GetR()=-GetR();
	GetG()=-GetG();
	GetB()=-GetB();
	GetA()=-GetA();
	return *this;
}

SICPPSDK_INLINE void CColor4f::PutNull()
{
	GetR()=0;
	GetG()=0;
	GetB()=0;
	GetA()=0;
}

SICPPSDK_INLINE float CColor4f::GetBrightness()const
{
	return (GetR()+GetG()+GetB())*(1.0f/3.0f);
}

SICPPSDK_INLINE float CColor4f::GetBrightnessWithAlpha()const
{
	return GetBrightness()*GetA();
}

SICPPSDK_INLINE float CColor4f::GetGrayscale()const
{
	return GetR()*0.3f+GetG()*0.59f+GetB()*0.11f;
}

SICPPSDK_INLINE float CColor4f::GetGrayscaleWithAlpha()const
{
	return GetGrayscale()*GetA();
}

SICPPSDK_INLINE CColor4f& CColor4f::InverseRGB()
{
	GetR()=1.0f-GetR();
	GetG()=1.0f-GetG();
	GetB()=1.0f-GetB();
	return *this;
}

SICPPSDK_INLINE LONG CColor4f::RoundDown(float a) const
{
	return (((a)<0) ? (((a)==(LONG)(a))?((LONG)(a)):((LONG)((a)-1))) : ((LONG)(a)));
}

SICPPSDK_INLINE void CColor4f::MinMax( float& out_fMin, float& out_fMax ) const
{
	if( m_RGBA[R] > m_RGBA[G] )
	{
		if( m_RGBA[R] > m_RGBA[B] )
		{
			out_fMax = m_RGBA[R];

			if( m_RGBA[B] > m_RGBA[G] )
				out_fMin = m_RGBA[G];
			else
				out_fMin = m_RGBA[B];
		}
		else
		{
			out_fMax = m_RGBA[B];
			out_fMin = m_RGBA[G];
		}
	}
	else
	{
		if( m_RGBA[G] > m_RGBA[B] )
		{
			out_fMax = m_RGBA[G];

			if( m_RGBA[B] > m_RGBA[R] )
				out_fMin = m_RGBA[R];
			else
				out_fMin = m_RGBA[B];
		}
		else
		{
			out_fMax = m_RGBA[B];
			out_fMin = m_RGBA[R];
		}
	}
}

SICPPSDK_INLINE bool CColor4f::AreAlmostEqual
(
	const CColor4f& in_c1,
	const CColor4f& in_c2,
	const float in_fEpsilon
)
{
	return	fabs( in_c1.GetR()-in_c2.GetR()) <= in_fEpsilon &&
			fabs( in_c1.GetG()-in_c2.GetG()) <= in_fEpsilon &&
			fabs(in_c1.GetB()-in_c2.GetB()) <= in_fEpsilon &&
			fabs(in_c1.GetA()-in_c2.GetA()) <= in_fEpsilon;
}

};
};

#endif // __XSICOLOR4F_H__
