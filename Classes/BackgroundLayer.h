#pragma  once

#include "cocos2d.h"

USING_NS_CC;

class BackgroundLayer :public Layer
{
public:
	BackgroundLayer();
	~BackgroundLayer();


	virtual bool init();
    
    bool isHaveSaveFile();
    
    int  getHighestHistoryScore();


	CREATE_FUNC(BackgroundLayer);
private:

	void moveBackground(float dt);

	Sprite *_background1;
	Sprite *_background2;

};