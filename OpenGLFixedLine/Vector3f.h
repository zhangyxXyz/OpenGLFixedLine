#pragma once
#include <cmath>
class Vector3f
{
public:
	Vector3f() = default;
	Vector3f(float x, float y, float z);
	~Vector3f();
public:
	union
	{
		struct
		{
			float x;
			float y;
			float z;
		};
		float v[3];
	};
	Vector3f operator*(float scaler) const;
	Vector3f operator+(const Vector3f& r) const;
	Vector3f operator-(const Vector3f& r) const;
	Vector3f operator^(const Vector3f& r) const;
	float operator*(const Vector3f&r) const;
	void operator=(const Vector3f& r);
	void Normalize();
	float Magnitude() const;
};

