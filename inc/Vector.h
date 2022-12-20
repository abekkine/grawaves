#ifndef VECTOR_H
#define VECTOR_H

typedef double Scalar;

class Vector 
{
public:
    Vector();
    Vector( double x, double y, double z );
    void Set( double x, double y, double z );
    // Assignment
    Vector& operator=(const Vector &rhs);
    // Addition
    Vector operator+(const Vector &rhs);
    // Substraction
    Vector operator-(const Vector &rhs);
    // Multiplication by a scalar
    Vector operator*(const Scalar &rhs);
    // Division by a scalar
    Vector operator/(const Scalar &rhs);
    // Dot product
    Scalar operator|(const Vector &rhs);
    // Cross product
    Vector operator^(const Vector &rhs);
    // Magnitude
    Scalar operator~();
    // Unit
    Vector operator!();
    ~Vector();

    double x;
    double y;
    double z;
};

#endif

