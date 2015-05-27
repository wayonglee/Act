#include "DamageShow.h"


DamageShow::DamageShow(void)
{
}


DamageShow::~DamageShow(void)
{
}

bool DamageShow::init()
{
	if(!LabelTTF::init())
	{
		return false;
	}

	return true;
}

void DamageShow::removeSelf(float)
{
	this->removeFromParent();
	this->release();
}