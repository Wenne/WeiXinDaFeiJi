#pragma once

#include "cocos2d.h"

USING_NS_CC;

class Enemy :public Node
{

public:
	Enemy();
	~Enemy();

	static Enemy* create();

	
	void bindSprite(Sprite* sprite, int life);

	Sprite* getSprite();

	int getLife();

	void loseLife();

	void setLife(int life);
	
	Rect getBoundingBox();

	bool IsPlayAnimation();

	void setIsPlayAnimation(bool state);

private:

	int _life;
	Sprite* _sprite;
	bool _isPlayAnimation;

};