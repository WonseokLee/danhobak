#include "Vector2.h"
#include <cmath>

Vector2::Vector2()
{
	this->x = this->y = 0;
}
Vector2::Vector2( double xy )
{
	this->x = this->y = (float)xy;
}
Vector2::Vector2( double x, double y )
{
	this->x = (float)x;
	this->y = (float)y;
}
float Vector2::size()
{
	return sqrt(x*x+y*y);
}
Vector2& Vector2::operator=( Vector2& other )
{
	this->x = other.x;
	this->y = other.y;
	return *this;
}
Vector2 operator+( Vector2& left, Vector2& right )
{
	return Vector2( left.x + right.x , left.y + right.y );
}
Vector2 operator+=( Vector2& left, Vector2& right )
{
	return left + right;
}
Vector2 operator-( Vector2& left, Vector2& right )
{
	return Vector2( left.x - right.x , left.y - right.y );
}
Vector2 operator-=( Vector2& left, Vector2& right )
{
	return left - right;
}
Vector2 operator*( double coef, Vector2& vector )
{
	return Vector2( coef * vector.x , coef * vector.y );
}
Vector2 operator*( Vector2& vector, double coef )
{
	return Vector2( coef * vector.x , coef * vector.y );
}
Vector2 operator*=( Vector2& vector, double coef )
{
	return vector * coef;
}
Vector2 operator/( Vector2& vector, double coef )
{
	return Vector2( coef / vector.x , coef / vector.y );
}
Vector2 operator/=( Vector2& vector, double coef )
{
	return vector / coef;
}
