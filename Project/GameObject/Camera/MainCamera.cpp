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
	

	//�Ǐ]����obj��rt��Get
	MainCamera::GetInstance()->viewProjection.translation_ = w.translate;
	MainCamera::GetInstance()->viewProjection.rotation_ = w.rotation;
	MainCamera::GetInstance()->viewProjection.rotation_.x = w.rotation.x + 0.3f;

	//�J������obj����ǂ̈ʂ̋����ɒu����
	Vector3 offset = { 0.0f,3.0f,-50.0f };
	Vector3 Lerp = VectorTransform::Lerp(w.translate, MainCamera::GetInstance()->viewProjection.translation_,1.0f);

	//��]�s��̍���
	Matrix4x4 rotateXMatrix = 	MatrixTransform::RotateXMatrix(MainCamera::GetInstance()->viewProjection.rotation_.x);
	Matrix4x4 rotateYMatrix = 	MatrixTransform::RotateYMatrix(MainCamera::GetInstance()->viewProjection.rotation_.y);
	Matrix4x4 rotateZMatrix = 	MatrixTransform::RotateZMatrix(MainCamera::GetInstance()->viewProjection.rotation_.z);
	Matrix4x4 rotateMatrix = MatrixTransform::Multiply(rotateXMatrix, MatrixTransform::Multiply(rotateYMatrix, rotateZMatrix));
	//�I�t�Z�b�g���J�����̉�]�ɍ��킹�ĉ�]������
	offset = VectorTransform::TransformNormal(offset, rotateMatrix);

	

	MainCamera::GetInstance()->viewProjection.translation_ = VectorTransform::Add(Lerp ,offset);
	Shake();
	MainCamera::GetInstance()->viewProjection.UpdateMatrix();
}

void MainCamera::Shake()
{
	if (!MainCamera::GetInstance()->IsShake)
	{
		return;
	}
	if (MainCamera::GetInstance()->CameraShakeRadious.x >=-0.1f&&MainCamera::GetInstance()->CameraShakeRadious.y<=0.1f)
	{
		MainCamera::GetInstance()->CameraShakeRadious = { -1.0f,1.0f };
		MainCamera::GetInstance()->IsShake = false;
		return;
	}

	mt19937 randomEngine(MainCamera::GetInstance()->seedGenerator());

	uniform_real_distribution<float>distribution(MainCamera::GetInstance()->CameraShakeRadious.x, MainCamera::GetInstance()->CameraShakeRadious.y);

	MainCamera::GetInstance()->CameraShakeRadious.x += 0.05f;
	MainCamera::GetInstance()->CameraShakeRadious.y -= 0.05f;
	Vector3 randpos = { distribution(randomEngine),distribution(randomEngine), distribution(randomEngine) };
	MainCamera::GetInstance()->viewProjection.translation_ = VectorTransform::Add(MainCamera::GetInstance()->viewProjection.translation_, randpos);
}
