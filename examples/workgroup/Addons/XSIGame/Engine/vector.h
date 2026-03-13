#ifndef _vector3_H_
#define _vector3_H_

#include "engine.h"
#include <math.h>

#define EPSILON		1.0e-5f


class ENGINE_API vector3 
{

public:
	//
	// constructors
	//
	vector3(float ix=0, float iy=0, float iz=0) : x(ix), y(iy), z(iz) { }
	vector3(const vector3 &c) : x(c.x), y(c.y), z(c.z) { }

	// copy

	const vector3& operator = (const vector3& c)
	{	x = c.x;
		y = c.y;
		z = c.z;
		return *this;
	}

	//
	// various ops
	//
	const vector3& operator += (const vector3& c)
	{	x += c.x;
		y += c.y;
		z += c.z;
		return *this;
	}

	const vector3 &operator -= (const vector3& c)
	{	x -= c.x;
		y -= c.y;
		z -= c.z;
		return *this;
	}

	const vector3 operator - (const vector3& c) const
	{	return vector3(x - c.x, y - c.y, z - c.z);
	}

	const vector3 operator - () const
	{	return vector3(-x, -y, -z);
	}

	const vector3 operator + (const vector3& c) const
	{	return vector3(x + c.x, y + c.y, z + c.z);
	}

	const vector3 operator + () const
	{	return vector3(*this);
	}

	const bool operator == (const vector3& c) const
	{	return (x == c.x && y == c.y && z == c.z);
	}

	const bool operator != (const vector3& c) const
	{	return !(*this == c);
	}

	const vector3& operator *= (const float d)
	{	x *= d;
		y *= d;
		z *= d;
		return *this;
	}
	const vector3 operator / (const vector3& c) const
	{	return vector3(x / c.x, y / c.y, z / c.z);
	}
	const vector3 &operator /= (const vector3& c)
	{	x /= c.x;
		y /= c.y;
		z /= c.z;
		return *this;
	}

	const vector3 operator * (const vector3& c) const
	{	return vector3(x * c.x, y * c.y, z * c.z);
	}
	const vector3& operator *= (const vector3& c)
	{	x *= c.x;
		y *= c.y;
		z *= c.z;
		return *this;
	}
	const vector3 operator * (const float d) const
	{	return vector3(x * d, y * d, z * d);
	}

	const vector3 operator / (const float d) const
	{	const float _d = 1.0f / d;
		return vector3(x * _d, y * _d, z * _d);
	}
	const vector3& operator /= (const float d)
	{	const float _d = 1.0f / d;
		x *= _d;
		y *= _d;
		z *= _d;
		return *this;
	}

	// dot
	const float operator % (const vector3& c) const
	{	return x*c.x + y*c.y + z*c.z;
	}

	//	cross
	const vector3 operator ^ (const vector3& c) const
	{	return vector3(
				y * c.z - c.y * z,
				z * c.x - c.z * x,
				x * c.y - c.x * y);
	}
	const vector3& operator ^= (const vector3& c)
	{	return *this = *this ^ c;
	}

	const float Lenght()
	{	return (float)sqrt(x*x + y*y + z*z);
	}
	const float LenghtSquared()
	{	return (x*x + y*y + z*z);
	}

	const float Distance( const vector3& c)
	{	
		vector3 t = *this - c;
		t*=t;
		return (float)sqrt(t.x + t.y + t.z);
	}

	const float DistanceSquared( const vector3& c)
	{	
		vector3 t = *this - c;
		t*=t;
		return (t.x + t.y + t.z);

	}

	const float inline Angle(const vector3& Normal) const
	{	return (float)acos(*this % Normal);
	}
	
//	const vector3 inline Reflection(const vector3& Normal) const
//	{	const vector3 V(*this | 1);
//		return (V - Normal * 2.0 * (V % Normal)) * !*this;
//	}
	
	const vector3 inline Rotate(const float dAngle, const vector3& Normal) const
	{	const float dCos = (float)cos(dAngle);
		const float dSin = (float)sin(dAngle);
		return vector3(
				*this * dCos +
				((Normal * *this) * (1.0f - dCos)) * Normal +
				(*this ^ Normal) * dSin);
	}

public:

	float	x;
	float	y;
	float	z;


};


#endif
