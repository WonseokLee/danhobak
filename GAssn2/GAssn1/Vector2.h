#pragma once

class Vector2
{
public:
	float x;
	float y;

	Vector2( double x = 0.0, double y = 0.0 );
	Vector2& operator=( Vector2& );

	friend Vector2 operator+( Vector2&, Vector2& );
	friend Vector2 operator+=( Vector2&, Vector2& );
	friend Vector2 operator-( Vector2&, Vector2& );
	friend Vector2 operator-=( Vector2&, Vector2& );
	friend Vector2 operator*( double, Vector2& );
	friend Vector2 operator*( Vector2&, double );
	friend Vector2 operator*=( Vector2&, double );
	friend Vector2 operator/( Vector2&, double );
	friend Vector2 operator/=( Vector2&, double );
};
