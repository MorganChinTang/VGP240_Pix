#pragma once

#include "Vector2.h"
#include "Vector3.h"
#include "Matrix4.h"
#include "Ray.h"
#include "Sphere.h"

namespace MathHelper
{
	constexpr float gDegToRad = 3.14159f / 180.0f;
	bool IsEqual(float a, float b);

	void FlattenVectorScreenCoords(Vector3& v);
	float MagnitudeSquared(Vector2 v);
	float MagnitudeSquared(Vector3 v);
	float Magnitude(Vector2 v); 
	float Magnitude(Vector3 v); 
	Vector2 Normalize(Vector2 v); 
	Vector3 Normalize(Vector3 v); 
	float Dot(Vector2 a, Vector2 b); 
	float Dot(Vector3 a, Vector3 b); 
	Vector3 Cross(Vector3 a, Vector3 b);
	
	//week4
	Vector3 Transformcoord(const Vector3& v, const Matrix4& m);
	Vector3 TransformNormal(const Vector3& v, const Matrix4& m);

	Matrix4 Inverse(const Matrix4& m);
	Matrix4 Transpose(const Matrix4& m);
	Matrix4 Adjoint(const Matrix4& m);
	float Determinant(const Matrix4& m);

	bool Intersect(const Ray& ray, const Sphere& sphere, float& distance);
}