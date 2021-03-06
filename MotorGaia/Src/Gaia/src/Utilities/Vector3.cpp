#include "Vector3.h"

#include "Quaternion.h"
#include <btBulletDynamicsCommon.h>
#include "MathUtils.h"

const Vector3 Vector3::ZERO					= Vector3(0.0, 0.0, 0.0);
const Vector3 Vector3::IDENTITY				= Vector3(1.0, 1.0, 1.0);
const Vector3 Vector3::NEGATIVE_IDENTITY	= Vector3(-1.0, -1.0, -1.0);
const Vector3 Vector3::RIGHT				= Vector3(1.0, 0.0, 0.0);
const Vector3 Vector3::NEGATIVE_RIGHT		= Vector3(-1.0, 0.0, 0.0);
const Vector3 Vector3::UP					= Vector3(0.0, 1.0, 0.0);
const Vector3 Vector3::NEGATIVE_UP			= Vector3(0.0, -1.0, 0.0);
const Vector3 Vector3::FORWARD				= Vector3(0.0, 0.0, 1.0);
const Vector3 Vector3::NEGATIVE_FORWARD		= Vector3(0.0, 0.0, -1.0);

Vector3::Vector3()
{
	x = 0;
	y = 0;
	z = 0;
}

Vector3::Vector3(double x, double y, double z) : x(x), y(y), z(z)
{

}

Vector3::~Vector3()
{
}

bool Vector3::operator==(const Vector3& v) const
{
	CHECK_VALID(v);
	CHECK_VALID(*this);
	return (v.x == x) && (v.y == y) && (v.z == z);
}

bool Vector3::operator!=(const Vector3& v) const
{
	CHECK_VALID(src);
	CHECK_VALID(*this);
	return (v.x != x) || (v.y != y) || (v.z != z);
}

Vector3& Vector3::operator+=(const Vector3& v)
{
	CHECK_VALID(*this);
	CHECK_VALID(v);
	x += v.x; y += v.y; z += v.z;
	return *this;
}

Vector3& Vector3::operator-=(const Vector3& v)
{
	CHECK_VALID(*this);
	CHECK_VALID(v);
	x -= v.x; y -= v.y; z -= v.z;
	return *this;
}

Vector3& Vector3::operator*=(double n)
{
	x *= n;
	y *= n;
	z *= n;
	CHECK_VALID(*this);
	return *this;
}

Vector3& Vector3::operator*=(const Vector3& v)
{
	CHECK_VALID(v);
	x *= v.x;
	y *= v.y;
	z *= v.z;
	CHECK_VALID(*this);
	return *this;
}

Vector3& Vector3::operator+=(double n)
{
	x += n;
	y += n;
	z += n;
	CHECK_VALID(*this);
	return *this;
}

Vector3& Vector3::operator-=(double n)
{
	x -= n;
	y -= n;
	z -= n;
	CHECK_VALID(*this);
	return *this;
}

Vector3& Vector3::operator/=(double n)
{
	Assert(n != 0.f);
	double d = 1.0f / n;
	x *= d;
	y *= d;
	z *= d;
	CHECK_VALID(*this);
	return *this;
}

Vector3& Vector3::operator/=(const Vector3& v)
{
	CHECK_VALID(v);
	Assert(v.x != 0.f && v.y != 0.f && v.z != 0.f);
	x /= v.x;
	y /= v.y;
	z /= v.z;
	CHECK_VALID(*this);
	return *this;
}

Vector3& Vector3::operator=(const Vector3& v)
{
	CHECK_VALID(v);
	x = v.x; y = v.y; z = v.z;
	return *this;
}

Vector3 Vector3::operator+(const Vector3& v) const
{
	Vector3 res;
	res.x = x + v.x;
	res.y = y + v.y;
	res.z = z + v.z;
	return res;
}

Vector3 Vector3::operator-(const Vector3& v) const
{
	Vector3 res;
	res.x = x - v.x;
	res.y = y - v.y;
	res.z = z - v.z;
	return res;
}

Vector3 Vector3::operator*(double n) const
{
	Vector3 res;
	res.x = x * n;
	res.y = y * n;
	res.z = z * n;
	return res;
}

Vector3 Vector3::operator*(const Vector3& v) const
{
	Vector3 res;
	res.x = x * v.x;
	res.y = y * v.y;
	res.z = z * v.z;
	return res;
}

Vector3 Vector3::operator/(double n) const
{
	Vector3 res;
	res.x = x / n;
	res.y = y / n;
	res.z = z / n;
	return res;
}

Vector3 Vector3::operator/(const Vector3& v) const
{
	Vector3 res;
	res.x = x / v.x;
	res.y = y / v.y;
	res.z = z / v.z;
	return res;
}

void Vector3::normalize()
{
	*this /= magnitude();
}

Vector3 Vector3::normalized() const
{
	if (*this == Vector3::ZERO) return *this;
	Vector3 aux = *this / magnitude();
	return aux;
}

Vector3 Vector3::cross(const Vector3& v)
{
	return Vector3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
}

double Vector3::dot(const Vector3& v)
{
	return x * v.x + y * v.y + z * v.z;
}

Vector3& Vector3::set(double x, double y, double z)
{
	this->x = x;
	this->y = y;
	this->z = z;
	return *this;
}

Vector3 Vector3::rotateAroundPivot(const Vector3& point, const Vector3& pivot, const Vector3& angles)
{
	Vector3 v = { point.x - pivot.x,point.y - pivot.y, point.z - pivot.z };
	Quaternion q = Quaternion::AnglesToQuaternion(angles.z, angles.y, angles.x), q1 = q.inverse(), aux = { 0,v.x,v.y,v.z }, aux1;
	aux1 = Quaternion::hamilton(q, aux);
	aux1 = Quaternion::hamilton(aux1, q1);
	v = { std::round(aux1.x),std::round(aux1.y),std::round(aux1.z) };
	return (v + pivot);
}

std::string Vector3::toString() const
{
	return std::to_string(x) + " " + std::to_string(y) + " " + std::to_string(z);
}

void Vector3::rotateAroundAxis(Vector3 axis, double degrees)
{
	double theta = degrees * DEG_TO_RAD;

	double cos_theta = cos(theta);
	double sin_theta = sin(theta);

	Vector3 rotated = (*this * cos_theta) + (axis.cross(*this) * sin_theta) + (axis * axis.dot(*this) * (1 - cos_theta));

	*this = rotated;
}

// percentage has to be a value between 0 and 1
void Vector3::lerp(const Vector3& v, double percentage)
{
	lerp(v, { percentage,percentage,percentage });
}

void Vector3::lerp(const Vector3& v, const Vector3& percentage)
{
	*this = { x + (v.x - x) * percentage.x, y + (v.y - y) * percentage.y, z + (v.z - z) * percentage.z };
}

double Vector3::magnitudeSquared() const
{
	return x * x + y * y + z * z;
}

double Vector3::magnitude() const
{
	return sqrt(magnitudeSquared());
}


Vector3 Vector3::operator+(const btVector3& v)
{
	return Vector3(x + v.x(), y + v.y(), z + v.z());
}

btVector3 operator+(const btVector3& p1, const Vector3& p2)
{
	return btVector3(btScalar(p1.x() + p2.x), btScalar(p1.y() + p2.y), btScalar(p1.z() + p2.z));
}
