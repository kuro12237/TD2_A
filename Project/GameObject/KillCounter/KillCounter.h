#pragma once
#include"Pch.h"


class KillCounter
{
public:
	
	static KillCounter* GetInstance();

	static void ClearCount() { KillCounter::GetInstance()->count = 0; }
	static void AddCount(uint32_t t = 1) { KillCounter::GetInstance()->count+=t; }

	static uint32_t GetCount() { return KillCounter::GetInstance()->count; }
private:
	uint32_t count = 0;
};

