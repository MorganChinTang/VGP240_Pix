#pragma once
#include"Light.h"

class DirectionalLight : public Light
{
public:
	X::Color ComputeLightColor(const Vector3& position, const Vector3& normal) override;

	void SetDirection(const Vector3& direction);

	Vector3 mDirection;
};

class PointLight : public Light
{
public:
	X::Color ComputeLightColor(const Vector3& position, const Vector3& normal) override;
	void SetPosition(const Vector3& position);
	void SetAttenuation(float constant, float linear, float quadratic);
private:
	Vector3 mPosition;
	float mConstant;
	float mLinear;
	float mQuadratic;
	float mAttenConst;
	float mAttenLinear;
	float mAttenQuad;
};
