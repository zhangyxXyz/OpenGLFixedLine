#include "Vector3f.h"



Vector3f::Vector3f(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}


Vector3f::~Vector3f()
{
}

Vector3f Vector3f::operator*(float scaler) const
{
	return Vector3f(x*scaler, y*scaler, z*scaler);
}

Vector3f Vector3f::operator+(const Vector3f & r) const
{
	return Vector3f(x + r.x, y + r.y, z + r.z);
}

Vector3f Vector3f::operator-(const Vector3f & r) const
{
	return Vector3f(x - r.x, y - r.y, z - r.z);
}

Vector3f Vector3f::operator^(const Vector3f & r) const
{
	//cross product
	return Vector3f(y*r.z - z*r.y, x*r.z - z*r.z, x*r.y - y*r.x);
}

float Vector3f::operator*(const Vector3f & r) const
{
	// dot product
	return x*r.x + y*r.y + z*r.z;
}

void Vector3f::operator=(const Vector3f & r)
{
	x = r.x;
	y = r.y;
	z = r.z;
}

void Vector3f::Normalize()
{
	float len = Magnitude();
	x /= len;
	y /= len;
	z /= len;
}

float Vector3f::Magnitude() const
{
	return sqrt(x*x + y*y + z*z);
}
