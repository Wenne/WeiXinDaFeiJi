#pragma  once

#include "cocos2d.h"
#include "Enemy.h"

enum enemyType
{
	ENEMY_MIN=1,
	ENEMY_MED,
	ENEMY_MAX
};


const int ENEMY_MIN_LIFE = 1;
const int ENEMY_MED_LIFE = 7;
const int ENEMY_MAX_LIFE = 20;

const int ENEMY_MIN_COUNT = 30;
const int ENEMY_MED_COUNT = 10;
const int ENEMY_MAX_COUNT = 5;



class EnemyLayer :public Layer
{
public:
	EnemyLayer();
	~EnemyLayer();


	virtual bool init();
	CREATE_FUNC(EnemyLayer);

	Animate* playAnimation(std::string formatstring, int count);
	void playEnemyExplosionAnimation(Enemy* enemy, int enemyType);

	Vector<Enemy*> getEnemyArray1();
	Vector<Enemy*> getEnemyArray2();
	Vector<Enemy*> getEnemyArray3();
	
	void stopAllEnemiesSpaw();
    
    int  removeAllenemies();



private:
	Vector<Enemy*> _enemyArray1;
	Vector<Enemy*> _enemyArray2;
	Vector<Enemy*> _enemyArray3;


	float _minDuration, _maxDuration;

	CC_SYNTHESIZE(float, _enemy1SpawRate, _enemy1SpawRate);
	CC_SYNTHESIZE(float, _enemy2SpawRate, _enemy2SpawRate);
	CC_SYNTHESIZE(float, _enemy3SpawRate, _enemy3SpawRate);

	float _timeSum1;
	float _timeSum2;
	float _timeSum3;



	void initEnemy1();
	void spawEnemy1(float dt);

	void initEnemy2();
	void spawEnemy2(float dt);

	void initEnemy3();
	void spawEnemy3(float dt);


	void spawEnemy(float dt);

	Enemy* getAvailableEnemy(int tag);


};