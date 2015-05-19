#include "StateLayer.h"

USING_NS_CC;

StateLayer::StateLayer(void)
{
}


StateLayer::~StateLayer(void)
{
}

bool StateLayer::init()
{
	if(!Layer::init())
	{
		return false;
	}
	return true;
}