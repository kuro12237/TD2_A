#include "MainCamera.h"

MainCamera* MainCamera::GetInstance()
{
	static MainCamera instance;
	return &instance;
}

void MainCamera::Initialize()
{
	MainCamera::GetInstance()->viewProjection.Initialize();
	MainCamera::GetInstance()->viewProjection.UpdateMatrix();
}

void MainCamera::Update(WorldTransform w)
{
	//追従するobjのrtをGet
	MainCamera::GetInstance()->viewProjection.translation_ = w.translate;
	MainCamera::GetInstance()->viewProjection.rotation_ = w.rotation;
	MainCamera::GetInstance()->viewProjection.rotation_.x = w.rotation.x + 0.3f;

	//カメラをobjからどの位の距離に置くか
	Vector3 offset = { 0.0f,3.0f,-50.0f };
	Vector3 Lerp = VectorTransform::Lerp(w.translate, MainCamera::GetInstance()->viewProjection.translation_,1.0f);

	//回転行列の合成
	Matrix4x4 rotateXMatrix = 	MatrixTransform::RotateXMatrix(MainCamera::GetInstance()->viewProjection.rotation_.x);
	Matrix4x4 rotateYMatrix = 	MatrixTransform::RotateYMatrix(MainCamera::GetInstance()->viewProjection.rotation_.y);
	Matrix4x4 rotateZMatrix = 	MatrixTransform::RotateZMatrix(MainCamera::GetInstance()->viewProjection.rotation_.z);
	Matrix4x4 rotateMatrix = MatrixTransform::Multiply(rotateXMatrix, MatrixTransform::Multiply(rotateYMatrix, rotateZMatrix));
	//オフセットをカメラの回転に合わせて回転させる
	offset = VectorTransform::TransformNormal(offset, rotateMatrix);

	MainCamera::GetInstance()->viewProjection.translation_ = VectorTransform::Add(Lerp ,offset);
	MainCamera::GetInstance()->viewProjection.UpdateMatrix();
}
