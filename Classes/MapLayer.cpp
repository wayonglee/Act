#include "MapLayer.h"

USING_NS_CC;

MapLayer::MapLayer(void)
{
}


MapLayer::~MapLayer(void)
{
}

bool MapLayer::init()
{
	if(!Layer::init())
	{
		return false;
	}
	TMXTiledMap *map = TMXTiledMap::create("res/mymap.tmx");
	map->setPosition(Vec2(0,0));
	this->addChild(map,0,1);
	return true;
}