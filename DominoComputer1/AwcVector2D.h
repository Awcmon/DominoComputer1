#ifndef AWCVECTOR2_H_INCLUDED
#define AWCVECTOR2_H_INCLUDED

#include <math.h>
#include <iostream>
//#include "AwcUtility.h"

#ifdef BOX2D_H
	#include "Box2D/Box2D.h"
#endif

extern float Rad2Deg(float Value);

class Vector2D
{
public:
	float x, y;
	//Constructor
	Vector2D::Vector2D();
	Vector2D(float _x, float _y);
	//Overloads
	Vector2D operator+(const Vector2D &v);
	Vector2D operator-(const Vector2D &v);
	Vector2D operator*(float fl);
	Vector2D operator/(float fl);
	bool operator==(const Vector2D &v);
	bool operator!=(const Vector2D &v);
	friend std::ostream& operator<<(std::ostream& os, const Vector2D &v);
	//Funcs
	float Length();
	float LengthSqr();
	Vector2D Normalized();
	float Normalize();
	float ToAngle();
	float DotProduct(Vector2D _v);
	bool InBetween(Vector2D pos1, Vector2D pos2);
	Vector2D Projection(Vector2D axis);
};

float dotProduct(Vector2D _v1, Vector2D _v2);
Vector2D projection(Vector2D pos, Vector2D axis);

#ifdef BOX2D_H
	Vector2D b2a(b2Vec2 bv);
	b2Vec2 a2b(Vector2D av);
#endif

#endif // AWCVECTOR2_H_INCLUDED
