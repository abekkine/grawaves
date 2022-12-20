#include <math.h>
#include <Vector.h>

Vector::Vector()
{
    Set( 0.0, 0.0, 0.0 );
}

Vector::Vector( double x, double y, double z )
{
    Set( x, y, z );
}

Vector::~Vector()
{
}

void Vector::Set( double x, double y, double z )
{
    Vector::x = x;
    Vector::y = y;
    Vector::z = z;
}

// Assignment
Vector& Vector::operator=(const Vector &rhs)
{
    if( this != &rhs )
    {
        this->x = rhs.x;
        this->y = rhs.y;
        this->z = rhs.z;
    }

    return *this;
}

// Addition
Vector Vector::operator+(const Vector &rhs)
{
    Vector result = *this;

    result.x += rhs.x;
    result.y += rhs.y;
    result.z += rhs.z;

    return result;
}

// Substraction
Vector Vector::operator-(const Vector &rhs)
{
    Vector result = *this;

    result.x -= rhs.x;
    result.y -= rhs.y;
    result.z -= rhs.z;

    return result;
}

// Multiplication by a scalar
Vector Vector::operator*(const Scalar &rhs)
{
    Vector result = *this;

    result.x *= rhs;
    result.y *= rhs;
    result.z *= rhs;

    return result;
}

// Division by a scalar
Vector Vector::operator/(const Scalar &rhs)
{
    Vector result = *this;

    result.x /= rhs;
    result.y /= rhs;
    result.z /= rhs;

    return result;
}

// Dot product
Scalar Vector::operator|(const Vector &rhs)
{
    Scalar result;

    result = (this->x * rhs.x);
    result += (this->y * rhs.y);
    result += (this->z * rhs.z);

    return result;
}

// Cross product
Vector Vector::operator^(const Vector &rhs)
{
    Vector result;

    result.x = this->y * rhs.z - this->z * rhs.y;
    result.y = this->z * rhs.x - this->x * rhs.z;
    result.z = this->x * rhs.y - this->y * rhs.x;

    return result;
}

// Magnitude
Scalar Vector::operator~()
{
    return sqrt( this->x*this->x + this->y*this->y + this->z*this->z );
}

// Unit
Vector Vector::operator!()
{
    Vector result = *this;
    Scalar magnitude = ~result;

    result.x /= magnitude;
    result.y /= magnitude;
    result.z /= magnitude;

    return result;
}

