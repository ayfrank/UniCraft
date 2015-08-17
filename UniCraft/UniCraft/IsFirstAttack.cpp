#include "IsFirstAttack.h"


IsFirstAttack::IsFirstAttack(Tactic* waveAttack)
{
	this->waveAttack = waveAttack;
}


IsFirstAttack::~IsFirstAttack()
{
}

bool IsFirstAttack::operation()
{
	return (dynamic_cast<WaveAttack*>(waveAttack))->isFirstAttack();
}
