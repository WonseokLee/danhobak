#include "Vector3.h"

Vector3::Vector3( double x, double y, double z)
{
	this->x = (float)x;
	this->y = (float)y;
	this->z = (float)z;
}
Vector3& Vector3::operator=( Vector3& other )
{
	this->x = other.x;
	this->y = other.y;
	this->z = other.z;
	return *this;
}
Vector3 operator+( Vector3& left, Vector3& right )
{
	return Vector3( left.x + right.x , left.y + right.y , left.z + right.z);
}
Vector3 operator+=( Vector3& left, Vector3& right )
{
	return left + right;
}
Vector3 operator-( Vector3& left, Vector3& right )
{
	return Vector3( left.x - right.x , left.y - right.y , left.z - right.z);
}
Vector3 operator-=( Vector3& left, Vector3& right )
{
	return left - right;
}
Vector3 operator*( double coef, Vector3& vector )
{
	return Vector3( coef * vector.x , coef * vector.y , coef * vector.z);
}
Vector3 operator*( Vector3& vector, double coef )
{
	return Vector3( coef * vector.x , coef * vector.y , coef * vector.z);
}
Vector3 operator*=( Vector3& vector, double coef )
{
	return vector * coef;
}
Vector3 operator/( Vector3& vector, double coef )
{
	return Vector3( coef / vector.x , coef / vector.y , coef / vector.z);
}
Vector3 operator/=( Vector3& vector, double coef )
{
	return vector / coef;
}
