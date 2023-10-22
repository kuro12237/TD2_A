#pragma once

#include"Model.h"
#include"WorldTransform.h"


struct SkydomeElemnt {
	unique_ptr<Model>model = nullptr;
	WorldTransform worldTansform{};
};


/// <summary>
/// “V‹…
/// </summary>
class Skydome {
public:

	/// <summary>
	/// ‰Šú‰»ˆ—
	/// </summary>
	void Initialize();


	/// <summary>
	/// XVˆ—
	/// </summary>
	void Update();


	/// <summary>
	/// •`‰æˆ—
	/// </summary>
	void Draw(ViewProjection viewProjection);


private:

	SkydomeElemnt skydome_;

	float initScale_ = 70.0f;

	Vector4 modelColor_ = { 1.0f, 1.0f, 1.0f, 1.0f };
};