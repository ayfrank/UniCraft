#include "IsNotFirstAttack.h"


IsNotFirstAttack::IsNotFirstAttack(Tactic* waveAttack)
{
	this->waveAttack = waveAttack;
}



IsNotFirstAttack::~IsNotFirstAttack()
{
}

bool IsNotFirstAttack::operation()
{
	return !(dynamic_cast<WaveAttack*>(waveAttack))->isFirstAttack();
}
