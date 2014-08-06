#pragma  once


#include "cocos2d.h"
#include "BackgroundLayer.h"
#include "PlayerLayer.h"
#include "BulletLayer.h"
#include "EnemyLayer.h"
#include "UFOlayer.h"
#include "ControlLayer.h"
#include "GameOverScene.h"




USING_NS_CC;

class GameScene :public Scene
{
public:
	GameScene();
	~GameScene();

	virtual bool init();

	CREATE_FUNC(GameScene);
    
private:

	BackgroundLayer *_background;

	PlayerLayer* _player;

	Bullet* _bullet;

	EnemyLayer* _enemy;
    
    UFO *_ufo;
    
    ControlLayer *_controlLayer;
    
    

	void initLayer();
	void initScoreLabel();

	void onEnemyBulletCollsionDetection(Vector<Sprite*> BulletArray,Vector<Enemy*> EnemyArray, int enemyType);

	void onEnemyPlayerCollsionDetection(Sprite* player, Vector<Enemy*> EnemyArray, int enemyType);
    
    void onUfoPlayerCollsionDectection(Sprite *player,Vector<Sprite*> ufoArray,int ufoType);
    
    void useBomb();
    
    void updatebombLabel();

    
    void initbombUfo();
    
   

	void gameLoop(float dt);

	Label* _label;

	void updateScore();

	int _score;
    int _highestHistoryScore;

	int _level;
    
    int _bulletType;
    
    float _doubleBulletTime;
    
    Sprite* _bombSprite;
    
    Label* _bombLable;
    
    int _bombNum;
    
    Menu *_bombButton;
    
    void gameover();

};