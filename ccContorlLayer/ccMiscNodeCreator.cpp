#include "ccMiscNodeCreator.h"

/**<  class CCProgressTimerCreator  */
CCProgressTimerCreator* CCProgressTimerCreator::create()
{
    CCProgressTimerCreator* pCreator = new CCProgressTimerCreator();
    if(pCreator) pCreator->autorelease();
    return pCreator;
}
CCProgressTimer* CCProgressTimerCreator::createNode()
{
    CCProgressTimer* pProgressTimer = new CCProgressTimer();
    if(pProgressTimer)
    {
        pProgressTimer->autorelease();
        return pProgressTimer;
    }
    CC_SAFE_DELETE(pProgressTimer);
    return NULL;
}
void CCProgressTimerCreator::endNode(CCNode* pNode)
{
    CCProgressTimer* pProgressTimer = (CCProgressTimer*)pNode;
    if(FIND_OBJ_BYKEY(mAttrMap, "file"))
        pProgressTimer->initWithSprite(CCSprite::create(mAttrMap["file"].c_str()));
    else if(FIND_OBJ_BYKEY(mAttrMap, "plist"))
        pProgressTimer->initWithSprite(CCSprite::createWithSpriteFrameName(mAttrMap["plist"].c_str()));

    CCNodeCreator::setAttribute(pNode);
}
void CCProgressTimerCreator::setAttribute(CCNode* pNode, const char* strName, const char* strValue, bool bCache)
{
    if(bCache)
        mAttrMap[strName] = strValue;

    else
    {
        CCProgressTimer* pProgressTimer = (CCProgressTimer*)pNode;
        if(strcmp(strName, "file") == 0 || strcmp(strName, "plist") == 0 )
            return;

        if(strcmp(strName, "type") == 0)
            pProgressTimer->setType((CCProgressTimerType)ccXmlAttrParse::toInt(strValue));

        if(strcmp(strName, "percent") == 0)
            pProgressTimer->setPercentage(ccXmlAttrParse::toFloat(strValue));

        if(strcmp(strName, "midpos") == 0)
            pProgressTimer->setMidpoint(ccXmlAttrParse::toPoint(strValue));

        if(strcmp(strName, "rate") == 0)
            pProgressTimer->setBarChangeRate(ccXmlAttrParse::toPoint(strValue));

        if(strcmp(strName, "reverse") == 0)
            pProgressTimer->setReverseProgress(ccXmlAttrParse::toBool(strValue));

        if(strcmp(strName, "anchor") == 0)
            pProgressTimer->setAnchorPoint(ccXmlAttrParse::toPoint(strValue));

        if(strcmp(strName, "color") == 0)
            pProgressTimer->setColor(ccXmlAttrParse::toColor3B(strValue));

        else
            CCNodeRGBACreator::setAttribute(pNode, strName, strValue, bCache);
    }
}

REG_NODE_CREATOR("CCProgressTimer",CCProgressTimerCreator)


/************************************************************************/
/**<  class CCMotionStreakCreator  */
CCMotionStreakCreator* CCMotionStreakCreator::create()
{
    CCMotionStreakCreator* pCreator = new CCMotionStreakCreator();
    if(pCreator) pCreator->autorelease();
    return pCreator;
}
CCMotionStreak* CCMotionStreakCreator::createNode()
{
    CCMotionStreak* pProgressTimer = new CCMotionStreak();
    if(pProgressTimer)
    {
        pProgressTimer->autorelease();
        return pProgressTimer;
    }
    CC_SAFE_DELETE(pProgressTimer);
    return NULL;
}

void CCMotionStreakCreator::endNode(CCNode* pNode)
{
    CCMotionStreak* pMotionStreak = (CCMotionStreak*)pNode;
    pMotionStreak->initWithFade(ccXmlAttrParse::toFloat(mAttrMap["fade"].c_str()),
                                ccXmlAttrParse::toFloat(mAttrMap["segment"].c_str()),
                                ccXmlAttrParse::toFloat(mAttrMap["stroke"].c_str()),
                                ccXmlAttrParse::toColor3B(mAttrMap["color"].c_str()),
                                mAttrMap["file"].c_str());
    CCNodeCreator::setAttribute(pNode);
}

void CCMotionStreakCreator::setAttribute(CCNode* pNode, const char* strName, const char* strValue, bool bCache)
{
    if(bCache)
        mAttrMap[strName] = strValue;

    else
    {
        CCMotionStreak* pMotionStreak = (CCMotionStreak*)pNode;
        if(strcmp(strName, "file") == 0
           ||strcmp(strName, "fade") == 0
           ||strcmp(strName, "segment") == 0
           ||strcmp(strName, "stroke") == 0
           ||strcmp(strName, "color") == 0)
            return;

        else if(strcmp(strName, "blend") == 0)
        {
            CCPoint p = ccXmlAttrParse::toPoint(strValue);
            ccBlendFunc blend;
            blend.src = p.x;
            blend.dst = p.y;
            pMotionStreak->setBlendFunc(blend);
        }

        else
            CCNodeRGBACreator::setAttribute(pNode, strName, strValue,bCache);
    }
}

REG_NODE_CREATOR("CCMotionStreak",CCMotionStreakCreator)
