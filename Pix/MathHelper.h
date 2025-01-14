#pragma once

#include "Vector2.h"
#include "Vector3.h"

namespace MathHelper
{
	bool IsEqual(float a, float b);

	float MagnitudeSquared(Vector2 v);
	float MagnitudeSquared(Vector3 v);
	float Magnitude(Vector2 v); 
	float Magnitude(Vector3 v); 
	Vector2 Normalize(Vector2 v); 
	Vector3 Normalize(Vector3 v); 
	float Dot(Vector2 a, Vector2 b); 
	float Dot(Vector3 a, Vector3 b); 
	Vector3 Cross(Vector3 a, Vector3 b);
}