#ifndef _CC_ANIMATION_FACTORY_H_
#define _CC_ANIMATION_FACTORY_H_

#include <cocos2d.h>
#include "ccNodeCreator.h"
#include "ccFileHelper.h"

USING_NS_CC;

class CCAnimateSpx;
class CCAnimationFactory : public CCObject
{
protected:
    CCAnimationFactory();


public:
    virtual ~CCAnimationFactory();
    static CCAnimationFactory* shared();
    bool cacheAnimations(const char* jsonFile, CCAnimateSpx* pAnimateSpx = NULL);
    bool cacheAnimations(Json* pJson, const char* jsonFile = "", CCAnimateSpx* pAnimateSpx = NULL);
    bool removeAnimations(const char* jsonFile);
    bool purgeSharedAnimationCache();

    CCAnimation* getAnimationByName(const char* name);
private:
    //static CCAnimationFactory* mInstance;
    REG_GARBO(CCAnimationFactory)
};

#endif // _CC_ANIMATION_FACTORY_H_
