//
//  UFOlayer.h
//  WeiXinDaFeiJi
//
//  Created by Mac on 14-8-4.
//
//

#ifndef WeiXinDaFeiJi_UFOlayer_h
#define WeiXinDaFeiJi_UFOlayer_h

#include "cocos2d.h"


USING_NS_CC;

enum UfoType
{
    UFO_BULLET,
    UFO_BOMB
};



class UFO : public Layer
{
public:
    UFO();
    ~UFO();
    
    CREATE_FUNC(UFO);
    
    virtual bool init();
    
    void remove(Sprite* ufo);
    
    Vector<Sprite*> getUfoBulletArray();
    Vector<Sprite*> getUfoBombArray();
    
    
private:
    
    Vector<Sprite*> _UFOBulletArray;
    Vector<Sprite*> _UFOBombArray;
    
    void initUfoBullet();
    void initUfoBombs();
    
    void spawUfoBullet(float dt);
    void spawUfoBomb(float dt);
    
};



#endif
