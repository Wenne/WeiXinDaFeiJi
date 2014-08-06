#include "EnemyLayer.h"

EnemyLayer::EnemyLayer()
{
	_minDuration = 2;
	_maxDuration = 4;
	_enemy1SpawRate = 2.5;
	_enemy2SpawRate = 5;
	_enemy3SpawRate = 100;
	_timeSum1 = 0;
	_timeSum2 = 0;
	_timeSum3 = 0;
}

EnemyLayer::~EnemyLayer()
{

}

bool EnemyLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	this->initEnemy1();
	this->initEnemy2();
	this->initEnemy3();

	this->schedule(schedule_selector(EnemyLayer::spawEnemy), 1.0/60);

	return true;
}

void EnemyLayer::spawEnemy(float dt)
{
	_timeSum1 += dt;
	_timeSum2 += dt;
	_timeSum3 += dt;

	if (_timeSum1 >= _enemy1SpawRate)
	{
		_timeSum1 = 0;
		this->spawEnemy1(dt);
	}

	if (_timeSum2 >= _enemy2SpawRate)
	{
		_timeSum2 = 0;
		this->spawEnemy2(dt);
	}

	if (_timeSum3 >= _enemy3SpawRate)
	{
		_timeSum3 = 0;
		this->spawEnemy3(dt);
	}
}

void EnemyLayer::stopAllEnemiesSpaw()
{
	this->unschedule(schedule_selector(EnemyLayer::spawEnemy));
}

void EnemyLayer::initEnemy1()
{
	for (int i = 0; i < ENEMY_MIN_COUNT; i++)
	{
		auto enemy1 = Enemy::create();
		enemy1->bindSprite(Sprite::createWithSpriteFrameName("enemy1.png"), ENEMY_MIN_LIFE);
		this->addChild(enemy1);

		enemy1->setVisible(false);

		enemy1->getSprite()->setTag(ENEMY_MIN);


		_enemyArray1.pushBack(enemy1);

	}
}

void EnemyLayer::spawEnemy1(float dt)
{
	
		auto enemy1 = getAvailableEnemy(ENEMY_MIN);
		if (enemy1)
		{
			enemy1->setLife(ENEMY_MIN_LIFE);
			Size enemy1Size = enemy1->getSprite()->getContentSize();
			Size visibleSize = Director::getInstance()->getVisibleSize();
			int minX = enemy1Size.width / 2;
			int maxX = visibleSize.width - enemy1Size.width / 2;
			int rangeX = maxX - minX;
			int actualX = (rand() % rangeX) + minX;

			enemy1->setPosition(ccp(actualX, visibleSize.height + enemy1Size.height / 2));
			enemy1->setVisible(true);


			//根据游戏难度给minDuration,maxDuration赋值

			int rangeDuration = _maxDuration - _minDuration;
			float actualDuration = CCRANDOM_0_1()*rangeDuration + _minDuration;

			auto actionMove = MoveBy::create(actualDuration, Vec2(0, enemy1->getSprite()->getPositionY() - visibleSize.height - enemy1Size.height));
			auto actionDone = Hide::create();

			auto action = Sequence::createWithTwoActions(actionMove, actionDone);

			enemy1->runAction(action);
		}
	
	
	

}

void EnemyLayer::initEnemy2()
{
	for (int i = 0; i < ENEMY_MED_COUNT; i++)
	{
		auto enemy2 = Enemy::create();
		enemy2->bindSprite(Sprite::createWithSpriteFrameName("enemy2.png"), ENEMY_MED_LIFE);
		this->addChild(enemy2);

		enemy2->setVisible(false);

		enemy2->getSprite()->setTag(ENEMY_MED);

		_enemyArray2.pushBack(enemy2);
	}
}

void EnemyLayer::spawEnemy2(float dt)
{

		auto enemy2 = getAvailableEnemy(ENEMY_MED);
		if (enemy2)
		{
			enemy2->setLife(ENEMY_MED_LIFE);
			Size enemy2Size = enemy2->getSprite()->getContentSize();
			Size visibleSize = Director::getInstance()->getVisibleSize();
			int minX = enemy2Size.width / 2;
			int maxX = visibleSize.width - enemy2Size.width / 2;
			int rangeX = maxX - minX;
			int actualX = (rand() % rangeX) + minX;

			enemy2->setPosition(ccp(actualX, visibleSize.height + enemy2Size.height / 2));
			enemy2->setVisible(true);



			int rangeDuration = _maxDuration - _minDuration;
			float actualDuration = CCRANDOM_0_1()*rangeDuration + _minDuration;
			actualDuration = actualDuration;

			auto actionMove = MoveBy::create(actualDuration, Vec2(0, enemy2->getSprite()->getPositionY() - visibleSize.height - enemy2Size.height));
			auto actionDone = Hide::create();

			auto action = Sequence::createWithTwoActions(actionMove, actionDone);

			enemy2->runAction(action);
		}

	

}

void EnemyLayer::initEnemy3()
{
	for (int i = 0; i < ENEMY_MAX_COUNT; i++)
	{
		auto enemy3 = Enemy::create();
		enemy3->bindSprite(Sprite::createWithSpriteFrameName("enemy3_n1.png"), ENEMY_MAX_LIFE);
		this->addChild(enemy3);

		enemy3->setVisible(false);

		enemy3->getSprite()->setTag(ENEMY_MAX);

		_enemyArray3.pushBack(enemy3);
	}
}

void EnemyLayer::spawEnemy3(float dt)
{
	
		auto enemy3 = getAvailableEnemy(ENEMY_MAX);

		if (enemy3)
		{
			enemy3->setLife(ENEMY_MAX_LIFE);
			Size enemy3Size = enemy3->getSprite()->getContentSize();
			Size visibleSize = Director::getInstance()->getVisibleSize();
			int minX = enemy3Size.width / 2;
			int maxX = visibleSize.width - enemy3Size.width / 2;
			int rangeX = maxX - minX;
			int actualX = (rand() % rangeX) + minX;

			enemy3->setPosition(ccp(actualX, visibleSize.height + enemy3Size.height / 2));
			enemy3->setVisible(true);

			Animation* animation = Animation::create();
			animation->setDelayPerUnit(0.08f);
			animation->addSpriteFrame(SpriteFrameCache::getInstance()->spriteFrameByName("enemy3_n1.png"));
			animation->addSpriteFrame(SpriteFrameCache::getInstance()->spriteFrameByName("enemy3_n2.png"));
			Animate* animate = Animate::create(animation);

			enemy3->getSprite()->runAction(RepeatForever::create(animate));


			//根据游戏难度给minDuration,maxDuration赋值

			int rangeDuration = _maxDuration - _minDuration;
			float actualDuration = CCRANDOM_0_1()*rangeDuration*1.3 + _minDuration;
			actualDuration = actualDuration * 2;

			auto actionMove = MoveBy::create(actualDuration, Vec2(0, enemy3->getSprite()->getPositionY() - visibleSize.height - enemy3Size.height));

			auto actionDone = Hide::create();

			auto action = Sequence::create(actionMove, actionDone, NULL);

			enemy3->runAction(action);
		
	}
	


}

Enemy* EnemyLayer::getAvailableEnemy(int tag)
{
	if (tag == ENEMY_MIN)
	{
		for (auto&sp : _enemyArray1)
		{
			if (!sp->isVisible())
			{
				return sp;
			}
		}
		return nullptr;
	}
	else if (tag == ENEMY_MED)
	{
		for (auto&sp : _enemyArray2)
		{
			if (!sp->isVisible())
			{
				return sp;
			}
		}
		return nullptr;
	}
	else
	{
		for (auto&sp : _enemyArray3)
		{
			if (!sp->isVisible())
			{
				return sp;
			}
		}
		return nullptr;
	}
}

Animate* EnemyLayer::playAnimation(std::string formatstring, int count)
{
	auto animation = Animation::create();
	for (int i = 1; i < count + 1; i++)
	{
		char szName[100] = { 0 };
		sprintf(szName, formatstring.c_str(), i);
		auto spriteFrame = SpriteFrameCache::getInstance()->spriteFrameByName(szName);
		animation->addSpriteFrame(spriteFrame);
	}
	// should last 2.8 seconds. And there are 14 frames.
	animation->setDelayPerUnit(0.08f);
	animation->setRestoreOriginalFrame(true);

	auto animate = Animate::create(animation);

	return animate;
}

void EnemyLayer::playEnemyExplosionAnimation(Enemy* enemy, int enemyType)
{
	int frame = 4;

	if (enemyType == ENEMY_MAX)
	{
		frame = 6;
	}

	auto animationName = StringUtils::format("enemy%d", enemyType);
	enemy->setIsPlayAnimation(true);


	auto animation = this->playAnimation(animationName + "_down%d.png", frame);
	auto hiddenAction = Hide::create();
	auto acionDone = CallFunc::create([=](){
		enemy->setVisible(false);
		enemy->getSprite()->stopAllActions();
		enemy->setIsPlayAnimation(false);
	});

	auto action = Sequence::create(animation, acionDone,nullptr);
	
	enemy->getSprite()-> runAction(action);
}


Vector<Enemy*> EnemyLayer::getEnemyArray1()
{
	return _enemyArray1;
}


Vector<Enemy*> EnemyLayer::getEnemyArray2()
{
	return _enemyArray2;
}

Vector<Enemy*> EnemyLayer::getEnemyArray3()
{
	return _enemyArray3;
}

int EnemyLayer::removeAllenemies()
{
    int scoreTemp=0;
    for(auto *sp1:_enemyArray1)
    {
        if(sp1->isVisible()&&!sp1->IsPlayAnimation())
        {
            sp1->stopAllActions();
            this->playEnemyExplosionAnimation(sp1, ENEMY_MIN);
            sp1->setLife(ENEMY_MIN_LIFE);
            scoreTemp++;
        }
    }
    for(auto *sp2:_enemyArray2)
    {
        if(sp2->isVisible()&&!sp2->IsPlayAnimation())
        {
            sp2->stopAllActions();
            this->playEnemyExplosionAnimation(sp2, ENEMY_MED);
            sp2->setLife(ENEMY_MED_LIFE);
            scoreTemp+=10;
        }
    }
    for(auto *sp3:_enemyArray3)
    {
        if(sp3->isVisible()&&!sp3->IsPlayAnimation())
        {
            sp3->stopAllActions();
            this->playEnemyExplosionAnimation(sp3, ENEMY_MAX);
            sp3->setLife(ENEMY_MAX_LIFE);
            scoreTemp+=50;
        }
    }
    return scoreTemp;
}
