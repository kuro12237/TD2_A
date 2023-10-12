#pragma once
#include"Pch.h"
#include"WorldTransform.h"

struct Particle_param
{
	bool IsAllive_;
	WorldTransform worldTransform_;
	Vector4 color_;
};