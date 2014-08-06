#include "Enemy.h"

Enemy::Enemy()
{
	_life = 0;
	_isPlayAnimation = false;
}

Enemy::~Enemy()
{

}

Enemy* Enemy::create()
{
	Enemy* pRet = new Enemy;
	pRet->autorelease();
	return pRet;
}

void Enemy::bindSprite(Sprite* sprite, int life)//绑定敌机，并传入生命值
{
	_sprite = sprite;
	_life = life;
	this->addChild(_sprite);
}


Sprite* Enemy::getSprite()
{
	return _sprite;
}


int Enemy::getLife()//获取生命
{
	return _life;
}


void Enemy::loseLife()//生命值-1
{
	_life--;
}


Rect Enemy::getBoundingBox()//获取敌机大小
{
	Rect rect = _sprite->boundingBox();
	Point pos = this->convertToWorldSpace(rect.origin);
	Rect enemyRect(pos.x, pos.y, rect.size.width, rect.size.height);
	return enemyRect;
}

bool Enemy::IsPlayAnimation()
{
	return _isPlayAnimation;
}

void Enemy::setIsPlayAnimation(bool state)
{
	this->_isPlayAnimation = state;

}

void Enemy::setLife(int life)
{
	_life = life;
}