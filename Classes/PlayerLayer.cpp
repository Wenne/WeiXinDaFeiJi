#include "PlayerLayer.h"

PlayerLayer::PlayerLayer()
{
	_isAlive = true;
}

PlayerLayer::~PlayerLayer()
{

}

void PlayerLayer::createPlayerPlane()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	_playerplane = Sprite::createWithSpriteFrameName("hero1.png");
	_playerplane->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + _playerplane->getContentSize().height / 2));
	this->addChild(_playerplane, 0, PLAYER_TAG);

	Blink *blink = Blink::create(1, 3);

	Animation* animation = Animation::create();
	animation->setDelayPerUnit(0.08f);
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->spriteFrameByName("hero1.png"));
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->spriteFrameByName("hero2.png"));
	Animate* animate = Animate::create(animation);

	_playerplane->runAction(blink);
	_playerplane->runAction(RepeatForever::create(animate));
}

bool PlayerLayer::init()
{
	if (!Node::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	this->createPlayerPlane();

	auto touchListenr = EventListenerTouchOneByOne::create();
	touchListenr->onTouchBegan = CC_CALLBACK_2(PlayerLayer::onTouchBegan, this);
	touchListenr->onTouchMoved = CC_CALLBACK_2(PlayerLayer::onTouchMoved, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListenr, this);
	

	return true;
}


Vec2 PlayerLayer::getPlayerPlanePositon()
{
	return _playerplane->getPosition();
}
Size PlayerLayer::getPlayerPlaneContentSize()
{
	return _playerplane->getContentSize();
}

bool PlayerLayer::onTouchBegan(Touch *touch, Event *unused_event)
{
	return true;
}

void PlayerLayer::onTouchMoved(Touch *touch, Event *unused_event)
{
	if (_isAlive)
	{
		Vec2 beginPoint = touch->getLocation();
		
		Rect planeRect = _playerplane->boundingBox();
		
		planeRect.origin.x -= 15;
		planeRect.origin.y -= 15;
		planeRect.size.width += 30;
		planeRect.size.height += 30;

		if (planeRect.containsPoint(beginPoint))
		{
			Vec2 endPoint = touch->getPreviousLocation();
			Vec2 offSet = ccpSub(beginPoint, endPoint);
			Vec2 toPoint = ccpAdd(_playerplane->getPosition(), offSet); 
			this->MoveTo(toPoint); 
		}
	}
}


void PlayerLayer::MoveTo(Vec2 location)
{
	if (_isAlive && !Director::getInstance()->isPaused())
	{
		Vec2 actualPoint;
		Size winSize = Director::getInstance()->getWinSize();
		Size planeSize = _playerplane->getContentSize();
		if (location.x<planeSize.width / 2)
		{
			location.x = planeSize.width / 2;
		}
		if (location.x>winSize.width - planeSize.width / 2)
		{
			location.x = winSize.width - planeSize.width / 2;
		}
		if (location.y<planeSize.height / 2)
		{
			location.y = planeSize.height / 2;
		}
		if (location.y>winSize.height - planeSize.height / 2)
		{
			location.y = winSize.height - planeSize.height / 2;
		}
		_playerplane->setPosition(location);
	}
}

Sprite* PlayerLayer::getPlayerPlane()
{
	return _playerplane;
}

void PlayerLayer::playPlayerBlowAnimation()
{
	auto animation = Animation::create();
	for (int i = 1; i < 5; i++)
	{
		char szName[100] = { 0 };
		sprintf(szName,"hero_blowup_n%d.png", i);
		auto spriteFrame = SpriteFrameCache::getInstance()->spriteFrameByName(szName);
		animation->addSpriteFrame(spriteFrame);
	}
	// should last 2.8 seconds. And there are 14 frames.
	animation->setDelayPerUnit(0.08f);
	animation->setRestoreOriginalFrame(true);

	auto animate = Animate::create(animation);
	auto hiddenAction = Hide::create();
	auto actionDone = CallFunc::create([=]()
	{
		_playerplane->setVisible(false);
	});

	auto action = Sequence::create(animate, actionDone, nullptr);

	_playerplane->runAction(action);
}