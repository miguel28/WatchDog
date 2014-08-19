/*
 *  MK_Math.cpp
 *  MKGLibrary
 *
 *  Created by Miguel Silva on 08/10/13.
 *  Copyright 2013 ITCJ. All rights reserved.
 *
 */

#include "MK_Math.h"
#include <stdio.h>

Vector3f::Vector3f()
{
	X = Y = Z = 0.0f;
}

Vector3f::Vector3f(float Length, float angle)
{
	float RadAngle = ToRadians(angle);
	X = Length * sinf(RadAngle);
	Y = 0.0f; 
	Z = Length * cosf(RadAngle);
}

Vector3f::Vector3f(float _X, float _Y, float _Z)
{
	X = _X;
	Y = _Y;
	Z = _Z;
}

inline Vector3f operator+(const Vector3f& l, const Vector3f& r)
{
    Vector3f Ret(l.X + r.X,
                 l.Y + r.Y,
                 l.Z + r.Z);
	
    return Ret;
}

inline Vector3f operator-(const Vector3f& l, const Vector3f& r)
{
    Vector3f Ret(l.X - r.X,
                 l.Y - r.Y,
                 l.Z - r.Z);
	
    return Ret;
}

inline Vector3f operator*(const Vector3f& l, float f)
{
    Vector3f Ret(l.X * f,
                 l.Y * f,
                 l.Z * f);
	
    return Ret;
}


Vector3f& Vector3f::operator+=(const Vector3f& r)
{
	X += r.X;
	Y += r.Y;
	Z += r.Z;
	
	return *this;
}

Vector3f& Vector3f::operator-=(const Vector3f& r)
{
	X -= r.X;
	Y -= r.Y;
	Z -= r.Z;
	
	return *this;
}

Vector3f& Vector3f::operator*=(float f)
{
	X *= f;
	Y *= f;
	Z *= f;
	
	return *this;
}

Vector3f Vector3f::Cross(const Vector3f& v) const
{
    const float _x = Y * v.Z - Z * v.Y;
    const float _y = Z * v.X - X * v.Z;
    const float _z = X * v.Y - Y * v.X;
	
    return Vector3f(_x, _y, _z);
}

Vector3f& Vector3f::Normalize()
{
    const float length = sqrtf((X * X) + (Y * Y) + (Z * Z));
	
    X /= length;
    Y /= length;
    Z /= length;
	
    return *this;
}

float Vector3f::Length()
{
	float xx = X * X;
	float yy = Y * Y;
	float zz = Z * Z;
	return sqrtf(xx + yy + zz);
}

Vector3f Vector3f::Rotate(float angle)
{
	Vector3f retVector;
	float Rad = ToRadians(-angle);
	retVector.X = (X*cosf(Rad)) - (Z*sinf(Rad));
	retVector.Y = 0.0f;
	retVector.Z = (X*sinf(Rad)) + (Z*cosf(Rad));
	return retVector;
}

void Vector3f::Print()
{
	printf("Vector %.02f, %.02f, %.02f", X, Y, Z);
}

float ToRadians(float angle)
{
	return angle*M_PI/180.0f;
}

/*
Vector3f RotateVector(Vector2f vector, float angle)
{
	Vector3f retVector;
	float Rad = ToRadians(-angle);
	retVector.X = (vector.X*cosf(Rad)) - (vector.Y*sinf(Rad));
	retVector.Y = 0.0f;
	retVector.Z = (vector.X*sinf(Rad)) + (vector.Y*cosf(Rad));
	return retVector;
}

Vector3f Add(Vector3f vect1, Vector3f vect2)
{
	Vector3f retVector;
	retVector.X = vect1.X + vect2.X;
	retVector.Y = vect1.Y + vect2.Y;
	retVector.Z = vect1.Z + vect2.Z;
	
	return retVector;
}*/