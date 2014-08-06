#include "GameScene.h"

GameScene::GameScene()
{
	_score = 0;
	_level = 1;
    _bulletType=BULLET_SINGLE;
    _doubleBulletTime=0;
    _bombLable=nullptr;
    _bombSprite=nullptr;
    _bombNum=0;
    _highestHistoryScore=0;
}

GameScene::~GameScene()
{

}

void GameScene::initLayer()
{
	//add background;
	_background = BackgroundLayer::create();
    _highestHistoryScore=_background->getHighestHistoryScore();
	this->addChild(_background);

	//add player
	_player = PlayerLayer::create();
	this->addChild(_player);

	//add bullet
	_bullet = Bullet::create(_player);
	this->addChild(_bullet);

	//add Enemy
	_enemy = EnemyLayer::create();
	this->addChild(_enemy);
    
    _ufo=UFO::create();
    this->addChild(_ufo);
    
    _controlLayer=ControlLayer::create();
    this->addChild(_controlLayer);
    
}

bool GameScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	

	//init Layer;
	this->initLayer();

	this->initScoreLabel();

    this->initbombUfo();

	this->schedule(schedule_selector(GameScene::gameLoop), 1.0 / 60);

	return true;
}

void GameScene::initScoreLabel()
{
	_label = Label::create("Score:0","微软雅黑", 40);
	_label->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2, Director::getInstance()->getVisibleSize().height - _label->getContentSize().height / 2));
	this->addChild(_label);
}

void GameScene::gameLoop(float dt)
{
	this->onEnemyBulletCollsionDetection(_bullet->getBulletsArray(), _enemy->getEnemyArray1(), ENEMY_MIN);
	this->onEnemyBulletCollsionDetection(_bullet->getBulletsArray(), _enemy->getEnemyArray2(), ENEMY_MED);
	this->onEnemyBulletCollsionDetection(_bullet->getBulletsArray(), _enemy->getEnemyArray3(), ENEMY_MAX);
	this->updateScore();
    this->updatebombLabel();

	this->onEnemyPlayerCollsionDetection(_player->getPlayerPlane(), _enemy->getEnemyArray1(), ENEMY_MIN);
	this->onEnemyPlayerCollsionDetection(_player->getPlayerPlane(), _enemy->getEnemyArray2(), ENEMY_MED);
	this->onEnemyPlayerCollsionDetection(_player->getPlayerPlane(), _enemy->getEnemyArray3(), ENEMY_MAX);
    
    if(_doubleBulletTime >DOUBLE_BULLET_TIME)
    {
        _bulletType = BULLET_SINGLE;
        _bullet->spawBullets();
    }
    
    
    if(_bulletType==BULLET_SINGLE)
    {
        _doubleBulletTime=0;
    }
    else
    {
        _doubleBulletTime+=dt;
    }
    
    
    
    this->onUfoPlayerCollsionDectection(_player->getPlayerPlane(), _ufo->getUfoBulletArray(), UFO_BULLET);
    this->onUfoPlayerCollsionDectection(_player->getPlayerPlane(), _ufo->getUfoBombArray(), UFO_BOMB);

	if (!_player->getisAlive())
	{
        
       
        
        this->gameover();
        
        
	}
    
	if (_score > _level * 70 + 70)
	{
		_level++;
		if (_enemy->get_enemy1SpawRate() > 0.1)
		{
			_enemy->set_enemy1SpawRate(_enemy->get_enemy1SpawRate() - 0.1);
		}

		if (_enemy->get_enemy2SpawRate() > 0.3)
		{
			_enemy->set_enemy2SpawRate(_enemy->get_enemy2SpawRate() - 0.2);
		}

		if (_enemy->get_enemy3SpawRate() > 15)
		{
			_enemy->set_enemy3SpawRate(_enemy->get_enemy3SpawRate() - 10);
		}
		
	}



}

void GameScene::gameover()
{
    if(_score>_highestHistoryScore)
    {
        UserDefault::getInstance()->setIntegerForKey("HighestScore", _score);
    }
    
    _enemy->stopAllEnemiesSpaw();
    _bullet->stopSpawBullet();
    _bullet->stopDoubleBullet();
    
    
    
    auto gameover = Gameover::create(_score);
    auto transition = TransitionSlideInB::create(1.0,gameover);
    Director::getInstance()->replaceScene(transition);

}

void GameScene::onEnemyBulletCollsionDetection(Vector<Sprite*> BulletArray, Vector<Enemy*> EnemyArray, int enemyType)
{
	for (auto& bullet : BulletArray)
	{
		if (bullet->isVisible())
		{
			for (auto& enemy : EnemyArray)
			{
				if (enemy->isVisible())
				{
					Rect bulletRect = bullet->getBoundingBox();
					Rect enemyRect = enemy->getBoundingBox();
					if (!enemy->IsPlayAnimation()&& enemyRect.intersectsRect(bulletRect))
					{
						enemy->loseLife();
						_bullet->removeBullet(bullet);
						if (enemy->getLife() == 0)
						{
							if (enemyType == ENEMY_MIN)
							{
								
								enemy->stopAllActions();
								_enemy->playEnemyExplosionAnimation(enemy, ENEMY_MIN);
								enemy->setLife(ENEMY_MIN_LIFE);
								_score++;
							}
							else if (enemyType == ENEMY_MED)
							{
								enemy->stopAllActions();
								_enemy->playEnemyExplosionAnimation(enemy, ENEMY_MED);
								enemy->setLife(ENEMY_MED_LIFE);
								_score+=10;
							}
							else if (enemyType == ENEMY_MAX)
							{
								enemy->stopAllActions();
								_enemy->playEnemyExplosionAnimation(enemy, ENEMY_MAX);
								enemy->setLife(ENEMY_MAX_LIFE);
								_score+=50;
							}
						}
					}
				}
			}
		}
	}
}

void GameScene::onEnemyPlayerCollsionDetection(Sprite* player, Vector<Enemy*> EnemyArray, int enemyType)
{
	for (auto& enemy : EnemyArray)
	{
		if (enemy->isVisible()&&
			_player->getisAlive()&&
			enemy->getBoundingBox().intersectsRect(_player->getPlayerPlane()->getBoundingBox()))
		{
			enemy->stopAllActions();
			_enemy->playEnemyExplosionAnimation(enemy, enemyType);
			_player->playPlayerBlowAnimation();
			enemy->setLife(ENEMY_MIN_LIFE);
			_player->setisAlive(false);
		}
	}
}


void GameScene::updateScore()
{
	_label->setString(StringUtils::format("Score:%d", _score));
}


void GameScene::onUfoPlayerCollsionDectection(cocos2d::Sprite *player, Vector<cocos2d::Sprite *> ufoArray, int ufoType)
{
    for(auto& ufo:ufoArray)
    {
        if(ufo->isVisible()&&
           _player->getisAlive()&&
           ufo->getBoundingBox().intersectsRect(player->getBoundingBox()))
        {
            if(ufoType==UFO_BOMB)
            {
                _bombNum++;
            }
            else
            {
               
                _bullet->spawDoubleBullets();
                _bulletType=BULLET_DOUBLE;
            }
            
            _ufo->remove(ufo);
        }
    }
}




void GameScene::initbombUfo()
{
    _bombSprite =Sprite::createWithSpriteFrameName("bomb.png");
   
    
    auto useBombItem  = MenuItemImage::create("bomb.png","bomb.png",CC_CALLBACK_0(GameScene::useBomb,this));
    useBombItem->setPosition(Vec2(_bombSprite->getContentSize().width,_bombSprite->getContentSize().height/2));
    _bombButton = Menu::create(useBombItem,NULL);
    _bombButton->setPosition(Vec2::ZERO);
    this->addChild(_bombButton);

     _bombLable = Label::create("0", "微软雅黑", 40);
     _bombLable->setPosition(Vec2(_bombSprite->getContentSize().width+50,_bombSprite->getContentSize().height/2));
    this->addChild(_bombLable);
    _bombLable->setVisible(false);
}


void GameScene::updatebombLabel()
{
    _bombLable->setString(StringUtils::format("%d",_bombNum));
    if(_bombNum>0)
    {
        _bombLable->setVisible(true);
        _bombButton->setVisible(true);
    }
    else
    {
        _bombLable->setVisible(false);
        _bombButton->setVisible(false);
    }
}

void GameScene::useBomb()
{
    _bombNum--;
    _score=_score+_enemy->removeAllenemies();
    
}









