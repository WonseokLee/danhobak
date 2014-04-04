#include "Vector2.h"

Vector2::Vector2( double x, double y )
{
	this->x = x;
	this->y = y;
}
Vector2 operator+( Vector2& left, Vector2& right )
{
	return Vector2( left.x + right.x , left.y + right.y );
}
Vector2 operator*( double coef, Vector2& vector )
{
	return Vector2( coef * vector.x , coef * vector.y );
}
Vector2 operator*( Vector2& vector, double coef )
{
	return Vector2( coef * vector.x , coef * vector.y );
}
