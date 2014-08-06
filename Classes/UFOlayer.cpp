//
//  UFOlayer.cpp
//  WeiXinDaFeiJi
//
//  Created by Mac on 14-8-4.
//
//

#include "UFOlayer.h"

UFO::UFO()
{
    
}

UFO::~UFO()
{
    
}

bool UFO::init()
{
    if(!Layer::init())
    {
        return false;
    }
    
    this->initUfoBombs();
    this->initUfoBullet();
    
    this->schedule(schedule_selector(UFO::spawUfoBomb),30);
    this->schedule(schedule_selector(UFO::spawUfoBullet),40);
    
    
    
    return true;
}

void UFO::initUfoBullet()
{
    for(int i=1;i<5;i++)
    {
        auto sprite = Sprite::createWithSpriteFrameName("ufo1.png");
        this->addChild(sprite);
        sprite->setVisible(false);
        _UFOBulletArray.pushBack(sprite);
        sprite->setTag(UFO_BULLET);
    }
}

void UFO::initUfoBombs()
{
    for(int i=1;i<5;i++)
    {
        auto sprite = Sprite::createWithSpriteFrameName("ufo2.png");
        this->addChild(sprite);
        sprite->setVisible(false);
        _UFOBombArray.pushBack(sprite);
        sprite->setTag(UFO_BOMB);
    }
}

void UFO::spawUfoBomb(float dt)
{
    for(auto& UfoBomb :_UFOBombArray)
    {
        if(!UfoBomb->isVisible())
        {
            Size bombSize = UfoBomb->getContentSize();
			Size visibleSize = Director::getInstance()->getVisibleSize();
			int minX = bombSize.width / 2;
			int maxX = visibleSize.width - bombSize.width / 2;
			int rangeX = maxX - minX;
			int actualX = (rand() % rangeX) + minX;
            
			UfoBomb->setPosition(Vec2(actualX, visibleSize.height + bombSize.height / 2));
			UfoBomb->setVisible(true);
            
            auto move1 = MoveBy::create(0.5f, Point(0, -150));
            auto move2 = MoveBy::create(0.3f, Point(0, 100));
            auto move3 = MoveBy::create(1.0f, Point(0,0-visibleSize.height-bombSize.height/2));
            
            auto actionDone = Hide::create();
            
            auto actionSequence = Sequence::create(move1,move2,move3,actionDone, NULL);
            
            UfoBomb->runAction(actionSequence);
            
            return;

        }
        
    }
    
}


void UFO::spawUfoBullet(float dt)
{
    for(auto& UfoBullet :_UFOBulletArray)
    {
        if(!UfoBullet->isVisible())
        {
            Size BulletSize = UfoBullet->getContentSize();
			Size visibleSize = Director::getInstance()->getVisibleSize();
			int minX = BulletSize.width / 2;
			int maxX = visibleSize.width - BulletSize.width / 2;
			int rangeX = maxX - minX;
			int actualX = (rand() % rangeX) + minX;
            
			UfoBullet->setPosition(Vec2(actualX, visibleSize.height + BulletSize.height / 2));
			UfoBullet->setVisible(true);
            
            auto move1 = MoveBy::create(0.5f, Point(0, -150));
            auto move2 = MoveBy::create(0.3f, Point(0, 100));
            auto move3 = MoveBy::create(1.0f, Point(0,0-visibleSize.height-BulletSize.height/2));
            
            auto actionDone = Hide::create();
            
            auto actionSequence = Sequence::create(move1,move2,move3,actionDone, NULL);
            
            UfoBullet->runAction(actionSequence);
            
            return;
            
        }
        
    }

}



void UFO::remove(Sprite *ufo)
{
    ufo->setVisible(false);
}

Vector<Sprite*>  UFO:: getUfoBombArray()
{
    return _UFOBombArray;
}

Vector<Sprite*>  UFO:: getUfoBulletArray()
{
    return _UFOBulletArray;
}















