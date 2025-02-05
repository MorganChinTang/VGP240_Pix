#include "MatrixStack.h"


MatrixStack* MatrixStack::Get()
{
	static MatrixStack sInstance;
	return &sInstance;
}

void MatrixStack::OnNewFrame()
{
	mCombineTransform = Matrix4::Identity();
	mMatrices.clear();
}

void MatrixStack::PushTranslation(const Vector3& d)
{
	Matrix4 translationMatrix = Matrix4::Translation(d);
	mMatrices.push_back(translationMatrix);
	mCombineTransform = translationMatrix * mCombineTransform;
}

void MatrixStack::PushRotationX(float rad)
{
	Matrix4 rotationMatrix = Matrix4::RotationX(rad);
	mMatrices.push_back(rotationMatrix);
	mCombineTransform = rotationMatrix * mCombineTransform;
}

void MatrixStack::PushRotationY(float rad)
{
	Matrix4 rotationMatrix = Matrix4::RotationY(rad);
	mMatrices.push_back(rotationMatrix);
	mCombineTransform = rotationMatrix * mCombineTransform;
}

void MatrixStack::PushRotationZ(float rad)
{
	Matrix4 rotationMatrix = Matrix4::RotationZ(rad);
	mMatrices.push_back(rotationMatrix);
	mCombineTransform = rotationMatrix * mCombineTransform;
}

void MatrixStack::PushScaling(const Vector3& s)
{
	Matrix4 scalingMatrix = Matrix4::Scale(s);
	mMatrices.push_back(scalingMatrix);
	mCombineTransform = scalingMatrix * mCombineTransform;
}

void MatrixStack::PopMatrix()
{
	if(!mMatrices.empty())
	{
		Matrix4 matrix = mMatrices.back();
		mMatrices.pop_back();
		mCombineTransform = MathHelper::Inverse(matrix) * mCombineTransform;
	}
}

const Matrix4& MatrixStack::GetTransform() const
{
	return mCombineTransform;
}
