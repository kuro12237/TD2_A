#include "KillCounter.h"

KillCounter* KillCounter::GetInstance()
{
	static KillCounter instance;
	return &instance;
}
