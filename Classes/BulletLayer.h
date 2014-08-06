#pragma  once


#include "cocos2d.h"
#include "PlayerLayer.h"

using namespace cocos2d;

const int VELOCITY_OF_BULLET = 400;

enum BulletState
{
	BULLET_NOT_FLY,
	BULLET_FLY
};

enum BulletType
{
    BULLET_SINGLE,
    BULLET_DOUBLE
};

const int DOUBLE_BULLET_TIME= 15;

const int BULLET_NUM = 25;


class Bullet :public Node
{
public:
	Bullet(PlayerLayer* temp);
	~Bullet();

	static Bullet* create(PlayerLayer *temp);

	virtual bool init();

	Vector<Sprite*> getBulletsArray();

	void removeBullet(Sprite* bullet);

	void stopSpawBullet();
    void stopDoubleBullet();
    
    void spawDoubleBullets();
    
    void spawBullets();
    

private:
	PlayerLayer* _player;

	void initBullet();
	
    void spawDoubleBullet(float dt);
    void spawBullet(float dt);

    
	Sprite* getAvailableBulletSprite();

	Vector<Sprite*> _bulletsArray;

};