#pragma once
#ifndef VECTOR3_H
#define VECTOR3_H

class btVector3;

struct Vector3
{
	double x;
	double y;
	double z;

	Vector3();
	Vector3(double x, double y, double z);


	void normalize();

	Vector3 operator +=(const Vector3 p);
	Vector3 operator -=(const Vector3 p);
	bool operator == (const Vector3 p) const;
	Vector3 operator = (const Vector3 p);

	Vector3& operator /= (const Vector3& p);
	Vector3& operator *= (const Vector3& p);
	Vector3& operator /= (const double d);
	Vector3& operator *= (const double d);

	double magnitudeSquared();
	double magnitude();
	Vector3& normalized();

};

Vector3 operator +(const Vector3& p1, const Vector3& p2);
Vector3 operator +(const Vector3& p1, const btVector3& p2);
btVector3 operator +(const btVector3& p1, const Vector3& p2 );
Vector3 operator -(const Vector3& p1, const Vector3& p2);
Vector3 operator *(const Vector3& p1, const Vector3& p2);
Vector3 operator /(const Vector3& p1, const Vector3& p2);
Vector3 operator *(const Vector3& p1, const double d);
Vector3 operator /(const Vector3& p1, const double d);


#endif