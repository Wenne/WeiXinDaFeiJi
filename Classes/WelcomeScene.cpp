#include "WelcomeScene.h"
#include "WelcomeLayer.h"

USING_NS_CC;

bool WelcomeScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	
	auto layer = WelcomeLayer::create();
	if (layer)
	{
		this->addChild(layer);
	}

	
	return true;
}