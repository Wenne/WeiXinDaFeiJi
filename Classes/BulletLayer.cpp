#include "BulletLayer.h"

Bullet* Bullet::create(PlayerLayer *temp)
{
	Bullet *pRet = new Bullet(temp); 
	if (pRet && pRet->init()) 
	{ 
	pRet->autorelease(); 
	return pRet; 
	} 
	else 
	{ 
	delete pRet; 
	pRet = NULL; 
	return NULL; 
	} 
}


Bullet::Bullet(PlayerLayer *temp)
{
	_player = temp;
}

Bullet::~Bullet()
{

}

bool Bullet::init()
{
	if (!Node::init())
	{
		return false;
	}

	this->initBullet();

	this->schedule(schedule_selector(Bullet::spawBullet), 1.0 / 5);

	return true;
}

void Bullet::initBullet()
{
	for (int i = 0; i < BULLET_NUM; i++)
	{
		Sprite* bullet = Sprite::createWithSpriteFrameName("bullet1.png");
		bullet->setVisible(false);
        bullet->setTag(0);
		this->addChild(bullet);
		_bulletsArray.pushBack(bullet);
	}
}

Sprite* Bullet::getAvailableBulletSprite()
{
	for (auto&sp : _bulletsArray)
	{
		if (!sp->getTag()&&!sp->isVisible())
		{
            sp->setTag(1);
            return sp;
		}
	}
	return nullptr;
}

void Bullet::spawBullet(float dt)
{

	Vec2 playerPosition = _player->getPlayerPlanePositon();
	auto bulletPosition = Vec2(playerPosition.x, playerPosition.y + _player->getPlayerPlaneContentSize().height / 2);

    Sprite* bullet = getAvailableBulletSprite();
	Size screenSize = Director::getInstance()->getVisibleSize();

	if (bullet)
	{
		bullet->setVisible(true);
		bullet->setPosition(bulletPosition);
		float moveOffset = screenSize.height + bullet->getContentSize().height / 2 - playerPosition.y;
		auto moveBy = MoveBy::create(moveOffset / VELOCITY_OF_BULLET, Vec2(0, moveOffset));
		auto toggleVisibility = Hide::create();
		auto action = Sequence::createWithTwoActions(moveBy, toggleVisibility);
		bullet->runAction(action);
        bullet->setTag(0);
	}
	
}

Vector<Sprite*> Bullet:: getBulletsArray()
{
	return _bulletsArray;
}

void Bullet::removeBullet(Sprite* bullet)
{
	bullet->stopAllActions();
	bullet->setVisible(false);
    bullet->setTag(0);
}

void Bullet::stopSpawBullet()
{
	this->unschedule(schedule_selector(Bullet::spawBullet));
}


void Bullet::spawDoubleBullet(float dt)
{
    Vec2 playerPosition = _player->getPlayerPlanePositon();
	auto bulletPosition = Vec2(playerPosition.x, playerPosition.y + _player->getPlayerPlaneContentSize().height / 2);
    
    Sprite* bullet = getAvailableBulletSprite();
    Sprite* bullet2 = getAvailableBulletSprite();
	Size screenSize = Director::getInstance()->getVisibleSize();
    
    
    if (bullet2)
	{
		bullet2->setVisible(true);
		bullet2->setPosition(bulletPosition);
        bullet2->setPositionX(bulletPosition.x+20);
		float moveOffset = screenSize.height + bullet2->getContentSize().height / 2 - playerPosition.y;
		auto moveBy = MoveBy::create(moveOffset / VELOCITY_OF_BULLET, Vec2(0, moveOffset));
		auto toggleVisibility = Hide::create();
		auto action = Sequence::createWithTwoActions(moveBy, toggleVisibility);
		bullet2->runAction(action);
        
	}

	if (bullet)
	{
		bullet->setVisible(true);
		bullet->setPosition(bulletPosition);
        bullet->setPositionX(bulletPosition.x-20);
		float moveOffset = screenSize.height + bullet->getContentSize().height / 2 - playerPosition.y;
		auto moveBy = MoveBy::create(moveOffset / VELOCITY_OF_BULLET, Vec2(0, moveOffset));
		auto toggleVisibility = Hide::create();
		auto action = Sequence::createWithTwoActions(moveBy, toggleVisibility);
		bullet->runAction(action);
        
	}
    bullet2->setTag(0);
    bullet->setTag(0);
}


void Bullet::spawDoubleBullets()
{
    this->unschedule(schedule_selector(Bullet::spawBullet));
    this->schedule(schedule_selector(Bullet::spawDoubleBullet),0.2);
}

void Bullet::spawBullets()
{
    this->unschedule(schedule_selector(Bullet::spawDoubleBullet));
    this->schedule(schedule_selector(Bullet::spawBullet),0.2);
}

void Bullet::stopDoubleBullet()
{
    this->unschedule(schedule_selector(Bullet::spawDoubleBullet));
}


