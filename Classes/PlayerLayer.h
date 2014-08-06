#pragma  once

#include "cocos2d.h"

#define PLAYER_TAG 10000

USING_NS_CC;

class PlayerLayer :public Layer
{
public:
	PlayerLayer();
	~PlayerLayer();

	Vec2 getPlayerPlanePositon();

	Size getPlayerPlaneContentSize();

	virtual bool onTouchBegan(Touch *touch, Event *unused_event);
	virtual void onTouchMoved(Touch *touch, Event *unused_event);
	
	Sprite* getPlayerPlane();

	void playPlayerBlowAnimation();

	virtual bool init();

	CREATE_FUNC(PlayerLayer);

	
private:


	CC_SYNTHESIZE(bool, _isAlive, isAlive);

	Sprite *_playerplane;

	void MoveTo(Vec2 location);

	void createPlayerPlane();
};