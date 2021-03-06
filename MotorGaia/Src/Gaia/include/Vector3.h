#pragma once
#ifndef VECTOR3_H
#define VECTOR3_H

#include <string>
#include "GaiaExports.h"

#define CHECK_VALID( _v ) 0
#define Assert( _exp ) ((void)0)

class btVector3;

class GAIA_API Vector3
{
public:
	double x;
	double y;
	double z;

public:
	Vector3();
	Vector3(double x, double y, double z);
	~Vector3();

	bool operator==(const Vector3& v) const;
	bool operator!=(const Vector3& v) const;
	Vector3& operator+=(const Vector3& v);
	Vector3& operator-=(const Vector3& v);
	Vector3& operator*=(const Vector3& v);
	Vector3& operator*=(double n);
	Vector3& operator/=(const Vector3& v);
	Vector3& operator/=(double n);
	Vector3& operator+=(double n);
	Vector3& operator-=(double n);

	Vector3& operator=(const Vector3& v);
	Vector3	operator+(const Vector3& v) const;
	Vector3	operator-(const Vector3& v) const;
	Vector3	operator*(const Vector3& v) const;
	Vector3	operator/(const Vector3& v) const;
	Vector3	operator*(double n) const;
	Vector3	operator/(double n) const;

	void normalize();
	double magnitudeSquared() const;
	double magnitude() const;
	Vector3 normalized() const;
	Vector3 cross(const Vector3& v);
	double dot(const Vector3& v);

	Vector3& set(double x, double y, double z);

	void rotateAroundAxis(Vector3 axis, double degrees);
	void lerp(const Vector3& v, double percentage);
	void lerp(const Vector3& v, const Vector3& percentage);
	Vector3 rotateAroundPivot(const Vector3& point, const Vector3& pivot, const Vector3& angles);

	std::string toString() const;

	Vector3 operator+(const btVector3& v);

	// All values are zero
	static const Vector3 ZERO;
	// All values are one
	static const Vector3 IDENTITY;
	// All values are negative one
	static const Vector3 NEGATIVE_IDENTITY;
	// X Axis
	static const Vector3 RIGHT;
	// Negative X Axis
	static const Vector3 NEGATIVE_RIGHT;
	// Y Axis
	static const Vector3 UP;
	// Negative Y Axis
	static const Vector3 NEGATIVE_UP;
	// Z Axis
	static const Vector3 FORWARD;
	// Negative Z Axis
	static const Vector3 NEGATIVE_FORWARD;
};

btVector3 operator+(const btVector3& p1, const Vector3& p2);

#endif