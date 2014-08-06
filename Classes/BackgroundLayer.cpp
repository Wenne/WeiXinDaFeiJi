#include "BackgroundLayer.h"

BackgroundLayer::BackgroundLayer()
{

}

BackgroundLayer::~BackgroundLayer()
{

}

bool BackgroundLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
    
    
	
	_background1 = Sprite::createWithSpriteFrameName("background.png");
	_background1->setAnchorPoint(Vec2::ZERO);
	_background1->setPosition(Vec2::ZERO);
	this->addChild(_background1);

	_background2 = Sprite::createWithSpriteFrameName("background.png");
	_background2->setAnchorPoint(Vec2::ZERO);
	_background2->setPosition(Vec2(_background1->getPositionX(), _background1->getPositionY() + _background1->getContentSize().height));
	this->addChild(_background2);

	this->schedule(schedule_selector(BackgroundLayer::moveBackground), 1.0 / 60);
	return true;
}



void BackgroundLayer::moveBackground(float dt)
{
	if (_background2->getPositionY() == 0)
	{
		_background1->setPositionY(0);
	}
	_background1->setPositionY(_background1->getPositionY() - 2);
	_background2->setPositionY(_background1->getPositionY() + _background1->getContentSize().height - 2);

}





bool BackgroundLayer::isHaveSaveFile()
{
    if(!UserDefault::getInstance()->getBoolForKey("isHaveSaveFileXml"))
    {
        UserDefault::getInstance()->setBoolForKey("isHaveSaveFileXml", true);
        UserDefault::getInstance()->setIntegerForKey("HighestScore", 0);
        UserDefault::getInstance()->flush();
        return false;
    }
    else
    {
        return true;
    }
}

int BackgroundLayer::getHighestHistoryScore()
{
    if(this->isHaveSaveFile())
    {
        return UserDefault::getInstance()->getIntegerForKey("HighestScore");
    }
    else
    {
        return 0;
    }
}
