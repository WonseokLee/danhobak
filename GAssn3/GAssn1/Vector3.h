#pragma once

class Vector3
{
public:
	float x;
	float y;

	Vector3( double x = 0.0, double y = 0.0 );
	Vector3& operator=( Vector3& );

	friend Vector3 operator+( Vector3&, Vector3& );
	friend Vector3 operator+=( Vector3&, Vector3& );
	friend Vector3 operator-( Vector3&, Vector3& );
	friend Vector3 operator-=( Vector3&, Vector3& );
	friend Vector3 operator*( double, Vector3& );
	friend Vector3 operator*( Vector3&, double );
	friend Vector3 operator*=( Vector3&, double );
	friend Vector3 operator/( Vector3&, double );
	friend Vector3 operator/=( Vector3&, double );
};
