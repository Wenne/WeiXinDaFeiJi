#include "WelcomeLayer.h"
#include "GameScene.h"



USING_NS_CC;

bool WelcomeLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();



	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("shoot.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("shoot_background.plist");

	auto background = Sprite::createWithSpriteFrameName("background.png");
	background->setAnchorPoint(Vec2::ZERO);
	background->setPosition(Vec2::ZERO);
	this->addChild(background);

	auto copyRight = Sprite::createWithSpriteFrameName("shoot_copyright.png");
	copyRight->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height / 3*2));
	this->addChild(copyRight);


	auto gameLoading = Sprite::createWithSpriteFrameName("game_loading1.png");
	gameLoading->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 7*3));
	this->addChild(gameLoading);


	auto animation = Animation::create();
	animation->setDelayPerUnit(0.5f);
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("game_loading1.png"));
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("game_loading2.png"));
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("game_loading3.png"));
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("game_loading4.png"));
	auto animate = Animate::create(animation);



	auto animationDone = CallFunc::create(
		[=](){
		auto scene = GameScene::create();
		auto transition = TransitionSlideInB::create(1, scene);
		Director::getInstance()->replaceScene(transition);

		});

	auto sequence = Sequence::create(animate, animationDone, NULL);


	gameLoading->runAction(sequence);
	return true;
}


