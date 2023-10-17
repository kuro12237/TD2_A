#pragma once
#include"Pch.h"
#include"WorldTransform.h"

struct Particle_param
{
	WorldTransform worldTransform_;
	WorldTransform uvTransform_;
	Vector4 color_;
	bool isAlive = false;
};