#pragma once

#include "MathHelper.h"

class Camera
{
public:
	static Camera* Get();
	
	void OnNewFrame();
	
	void SetPosition(const Vector3& position);
	void SetDirection(const Vector3& rotation);
	void SetNearPlane(float nearPlane);
	void SetFarPlane(float farPlane);
	void SetFOV(float fov);

	Matrix4 GetViewMatrix() const;
	Matrix4 GetProjectionMatrix() const;
	
	const Vector3& GetPosition() const;
	const Vector3& GetDirection() const;

private:
	Vector3 mPosition;
	Vector3 mDirection;
	float mNearPlane = 0.01f;
	float mFarPlane = 100.0f;
	float mFOV = 60.0f * MathHelper::gDegToRad;
};
