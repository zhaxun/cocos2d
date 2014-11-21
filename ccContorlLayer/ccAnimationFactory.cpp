#include "ccAnimationFactory.h"
#include "ccAnimateSpx.h"

//CCAnimationFactory* CCAnimationFactory::mInstance = NULL;
REG_GARBO_DEFINE(CCAnimationFactory)

CCAnimationFactory::CCAnimationFactory()
{
}

CCAnimationFactory::~CCAnimationFactory()
{
}

CCAnimationFactory* CCAnimationFactory::shared()
{
    if(mInstance == NULL)
    {
        mInstance = new CCAnimationFactory();
        if(mInstance==NULL)
        {
            return NULL;
        }
    }
    return mInstance;
}

CCAnimation* CCAnimationFactory::getAnimationByName(const char* name)
{
    return CCAnimationCache::sharedAnimationCache()->animationByName(name);
}

bool CCAnimationFactory::cacheAnimations(const char* jsonFile, CCAnimateSpx* pAnimateSpx)
{
    Json* pJson = CCJsonHelper::loadJsonFromFile(jsonFile);
    Json* value = Json_getItem(pJson, "animations");
    int size = Json_getSize(value);
    if( size== 0)
        return false;

    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(
                                                Json_getString(pJson, "plist", ""));
    CCAnimation* animation=NULL;
    Json *c = value->child;
	while (c > 0)
	{
        CCString* pStrAniName = CCString::createWithFormat("%s::%s", jsonFile, Json_getString(c, "name", ""));
        animation = CCAnimationCache::sharedAnimationCache()->animationByName(pStrAniName->getCString());
        if(animation && pAnimateSpx)
        {
            pAnimateSpx->addAnimate(Json_getString(c, "name", ""), animation);

            std::string strPos = Json_getString(c, "position", "");
            pAnimateSpx->setActPos(pStrAniName->getCString(),ccXmlAttrParse::toPoint(strPos.c_str()));

        }
        else
        {
            animation = CCAnimation::create();



            std::string strDelay = Json_getString(c, "delay", "1.0");
            animation->setDelayPerUnit(ccXmlAttrParse::toFloat(strDelay.c_str()));

            Json* frames=Json_getItem(c, "frames");
            int n = Json_getSize(frames);
            for(int i=0; i<n; i++)
            {
                Json* pJson = Json_getItemAt(frames, i);
                CCSpriteFrame* frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pJson->valuestring);
                animation->addSpriteFrame(frame);
            }
            CCAnimationCache::sharedAnimationCache()->addAnimation(animation, pStrAniName->getCString());
            if(pAnimateSpx)
            {
                pAnimateSpx->addAnimate(Json_getString(c, "name", ""), animation);
                std::string strPos = Json_getString(c, "position", "");
                pAnimateSpx->setActPos(pStrAniName->getCString(),ccXmlAttrParse::toPoint(strPos.c_str()));
            }
        }
	    c = c->next;
	}
    CCJsonHelper::unloadJson(pJson);
    return true;
}

bool CCAnimationFactory::cacheAnimations(Json* pJson, const char* jsonFile, CCAnimateSpx* pAnimateSpx)
{
    Json* value = Json_getItem(pJson, "animations");
    int size = Json_getSize(value);
    if( size== 0)
        return false;

    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(
                                                Json_getString(pJson, "plist", ""));
    CCAnimation* animation=NULL;
    Json *c = value->child;
	while (c > 0)
	{
        CCString* pStrAniName = CCString::createWithFormat("%s::%s", jsonFile, Json_getString(c, "name", ""));
        animation = CCAnimationCache::sharedAnimationCache()->animationByName(pStrAniName->getCString());
        if(animation && pAnimateSpx)
        {
            pAnimateSpx->addAnimate(Json_getString(c, "name", ""), animation);

            std::string strPos = Json_getString(c, "position", "");
            pAnimateSpx->setActPos(Json_getString(c, "name", ""),ccXmlAttrParse::toPoint(strPos.c_str()));
        }
        else
        {
            animation = CCAnimation::create();
            std::string strDelay = Json_getString(c, "delay", "1.0");
            animation->setDelayPerUnit(ccXmlAttrParse::toFloat(strDelay.c_str()));
            Json* frames=Json_getItem(c, "frames");
            int n = Json_getSize(frames);
            for(int i=0; i<n; i++)
            {
                Json* pJson = Json_getItemAt(frames, i);
                CCSpriteFrame* frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pJson->valuestring);
                animation->addSpriteFrame(frame);
            }
            CCAnimationCache::sharedAnimationCache()->addAnimation(animation, pStrAniName->getCString());
            if(pAnimateSpx)
            {
                pAnimateSpx->addAnimate(Json_getString(c, "name", ""), animation);
                std::string strPos = Json_getString(c, "position", "");
                pAnimateSpx->setActPos(Json_getString(c, "name", ""),ccXmlAttrParse::toPoint(strPos.c_str()));
            }
        }
	    c = c->next;
	}
    return true;
}

bool CCAnimationFactory::removeAnimations(const char* jsonFile)
{
    Json* pJson = CCJsonHelper::loadJsonFromFile(jsonFile);
    Json* value = Json_getItem(pJson, "animations");
    int size = Json_getSize(value);
    if(size == 0)
        return false;

    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile(Json_getString(pJson, "plist", ""));
    while(size--)
    {
        Json* pJson = Json_getItemAt(value, size);
        CCAnimationCache::sharedAnimationCache()->removeAnimationByName(
                    Json_getString(pJson,"name",""));
    }
    CCJsonHelper::unloadJson(pJson);
    return true;
}
bool CCAnimationFactory::purgeSharedAnimationCache()
{
    CCAnimationCache::sharedAnimationCache()->purgeSharedAnimationCache();
    return true;
}


