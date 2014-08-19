/*
 *  MK_Math.h
 *  MKGLibrarY
 *
 *  Created bY Miguel Silva on 08/10/13.
 *  CopYright 2013 ITCJ. All rights reserved.
 *
 */

#ifndef MK_MATH_H
#define MK_MATH_H 

#include <math.h>


typedef struct
{
	float X;
	float Y;
}Vector2f;
/*
typedef struct
{
	float X;
	float Y;
	float Z;
}Vector3f;
*/

class Vector3f
{
public:
	float X;
    float Y;
    float Z;
	
    Vector3f();
	Vector3f(float Length, float angle);
    Vector3f(float _X, float _Y, float _Z);
	
	Vector3f& operator+=(const Vector3f& r);
	Vector3f& operator-=(const Vector3f& r);
	Vector3f& operator*=(float f);
	Vector3f Cross(const Vector3f& v) const;
	Vector3f& Normalize();
	float Length();
	Vector3f Rotate(float angle);
	void Print();
	
};

typedef struct
{
	float Red;
	float Green;
	float Blue;
}Color3f;


typedef struct
{
	float Red;
	float Green;
	float Blue;
	float Alpha;
}Color4f;

typedef struct
{
	float Width;
	float Height;
}Size2f;

typedef struct
{
	float Width;
	float Height;
	float Prof;
}Size3f;


float ToRadians(float angle);
//Vector3f RotateVector(Vector2f vector, float angle);
//Vector3f Add(Vector3f vect1, Vector3f vect2);


#endif

