#include "ccAnimateSpx.h"
#include "ccAnimationFactory.h"
#include "ccNodeCreator.h"
#include "ccFileHelper.h"
#include <spine/Json.h>

CCAnimateSpx::CCAnimateSpx(void)
{
    mSprite = NULL;
}

CCAnimateSpx::~CCAnimateSpx(void)
{
    removeAnimate();
}

CCAnimateSpx* CCAnimateSpx::create()
{
    CCAnimateSpx* pRet=new CCAnimateSpx;
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

CCAnimateSpx* CCAnimateSpx::create(const char* jsonFile)
{
    CCAnimateSpx* pRet=new CCAnimateSpx;
    if (pRet && pRet->init(jsonFile))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

CCAnimateSpx* CCAnimateSpx::create(CCSpriteBatchNode** node, const char* jsonFile)
{
    CCAnimateSpx* pRet=new CCAnimateSpx;
    if (pRet && pRet->init(node, jsonFile))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

bool CCAnimateSpx::init(const char* jsonFile)
{
    Json* pJson = CCJsonHelper::loadJsonFromFile(jsonFile);
    CCAnimationFactory::shared()->cacheAnimations(pJson, jsonFile, this);

    std::string strFrame = Json_getString(pJson, "defaultFrame", "");
    if(!strFrame.empty())
        mSprite = CCSprite::createWithSpriteFrameName(strFrame.c_str());
    else
        mSprite = CCSprite::create();
    addChild(mSprite);
    CCJsonHelper::unloadJson(pJson);
    return true;
}

bool CCAnimateSpx::init(CCSpriteBatchNode** node, const char* jsonFile)
{
    Json* pJson = CCJsonHelper::loadJsonFromFile(jsonFile);
    CCAnimationFactory::shared()->cacheAnimations(pJson, jsonFile, this);

    std::string strImage = Json_getString(pJson, "image", "");
    if(*node == NULL)
        *node = CCSpriteBatchNode::create(strImage.c_str());
    mSprite = CCSprite::create(strImage.c_str());
    (*node)->addChild(mSprite);
    CCJsonHelper::unloadJson(pJson);
    return true;
}

void CCAnimateSpx::addAnimate(const char* animateName, CCAnimation* pAnimation)
{
    std::map<std::string, CCAnimation*>::iterator it = mAnimateMap.find(animateName);
    if(it != mAnimateMap.end())
    {
        CC_SAFE_RELEASE(it->second);
        mAnimateMap.erase(it);
    }

    mAnimateMap[animateName] = pAnimation;
    CC_SAFE_RETAIN(pAnimation);
}

void CCAnimateSpx::removeAnimate()
{
    std::map<std::string, CCAnimation*>::iterator it = mAnimateMap.begin();
    while(it != mAnimateMap.end())
    {
        CC_SAFE_RELEASE(it->second);
        it++;
    }
}

CCAnimation* CCAnimateSpx::getAnimationByName(const char* animateName)
{
    std::map<std::string, CCAnimation*>::iterator it = mAnimateMap.find(animateName);
    if(it != mAnimateMap.end())
        return it->second;
    return NULL;
}

CCSprite* CCAnimateSpx::getAnimateSprite()
{
	return mSprite;
}

CCRect CCAnimateSpx::getBoundingBox()
{
    CCRect rect = mSprite->boundingBox();
    return CCRectApplyAffineTransform(rect, nodeToWorldTransform());
}

void CCAnimateSpx::switchAnimate(const char* animateName)
{
    if(mSprite == NULL || mAnimateMap[animateName] == NULL)
        return;

    CCAnimate* animate=CCAnimate::create(mAnimateMap[animateName]);
    mSprite->stopAllActions();
    mSprite->runAction(CCRepeatForever::create(animate));
}

void CCAnimateSpx::setSkewX(float f)
{
    //CCNode::setSkewX(f);
    if(mSprite)
       mSprite->setSkewX(f);
}

void CCAnimateSpx::setSkew(float f)
{
    //CCNode::setSkewY(f);
    if(mSprite)
       mSprite->setSkewY(f);
}

const CCPoint& CCAnimateSpx::getPosition()
{
    return mSprite->getPosition();
}

void CCAnimateSpx::setPosition(const CCPoint& point)
{
    //CCNode::setPosition(point);
    if(mSprite)
       mSprite->setPosition(point);
}

void CCAnimateSpx::setAnchorPoint(const CCPoint& point)
{
    //CCNode::setAnchorPoint(point);
    if(mSprite)
       mSprite->setAnchorPoint(point);
}

void CCAnimateSpx::setRotation(float f)
{
    //CCNode::setRotation(f);
    if(mSprite)
       mSprite->setRotation(f);
}

void CCAnimateSpx::setScaleX(float f)
{
    //CCNode::setScaleX(f);
    if(mSprite)
       mSprite->setScaleX(f);
}

void CCAnimateSpx::setScaleY(float f)
{
    //CCNode::setScaleY(f);
    if(mSprite)
       mSprite->setScaleY(f);
}

void CCAnimateSpx::setFlipX(bool b)
{
    if(mSprite)
       mSprite->setFlipX(b);
}
void CCAnimateSpx::setFlipY(bool b)
{
    if(mSprite)
        mSprite->setFlipY(b);
}

void CCAnimateSpx::setActPos(const char* aimateName,const CCPoint& point)
{

}
