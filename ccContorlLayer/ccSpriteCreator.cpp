#include "ccSpriteCreator.h"

/**<class CCSpriteCreator     */
CCSpriteCreator* CCSpriteCreator::create()
{
    CCSpriteCreator* pCreator = new CCSpriteCreator();
    if(pCreator) pCreator->autorelease();
    return pCreator;
}

CCSprite* CCSpriteCreator::createNode()
{
    return CCSprite::create();
}

void CCSpriteCreator::endNode(CCNode* pNode)
{
    CCSprite* pSprite = (CCSprite*)pNode;
    if(FIND_OBJ_BYKEY(mAttrMap, "file"))
        pSprite->initWithFile(mAttrMap["file"].c_str());
    else if(FIND_OBJ_BYKEY(mAttrMap, "plist"))
        pSprite->initWithSpriteFrameName(mAttrMap["plist"].c_str());
    CCNodeCreator::setAttribute(pNode);
}

void CCSpriteCreator::setAttribute(CCNode* pNode, const char* strName, const char* strValue, bool bCache)
{
    CCSprite* pSprite = (CCSprite*)pNode;

    if(bCache)
        mAttrMap[strName] = strValue;

    else
    {
        if(strcmp(strName, "file") == 0 || strcmp(strName, "plist") == 0)
            return;

        else if(strcmp(strName, "rect") == 0)
            pSprite->setTextureRect(ccXmlAttrParse::toRect(strValue));

        else if(strcmp(strName, "flip") == 0)
        {
            if(strcmp(strValue, "1")==0)
                pSprite->setFlipX(true);
            else if(strcmp(strValue, "2")==0)
                pSprite->setFlipY(true);
        }
        else if(strcmp(strName, "blend") == 0)
            pSprite->setBlendFunc(ccXmlAttrParse::toBlendFunc(strValue));

        else
            CCNodeRGBACreator::setAttribute(pSprite, strName, strValue, bCache);
    }
}

REG_NODE_CREATOR("CCSprite",CCSpriteCreator)



/**<  CCScale9SpriteCreator         */
CCScale9SpriteCreator* CCScale9SpriteCreator::create()
{
    CCScale9SpriteCreator* pCreator = new CCScale9SpriteCreator();
    if(pCreator) pCreator->autorelease();
    return pCreator;
}

CCScale9Sprite* CCScale9SpriteCreator::createNode()
{
    CCScale9Sprite* pNode = new CCScale9Sprite();
    if(pNode)
    {
        pNode->autorelease();
        return pNode;
    }
    CC_SAFE_DELETE(pNode);
    return NULL;
}

void CCScale9SpriteCreator::endNode(CCNode* pNode)
{
    CCScale9Sprite* pScale9Sprite = (CCScale9Sprite*)pNode;
    CCArray* pArray = CCArray::create();
    CCObject* child = NULL;
    CCARRAY_FOREACH(pScale9Sprite->getChildren(), child)
    {
        pArray->addObject(child);
    }

    if(FIND_OBJ_BYKEY(mAttrMap, "file"))
    {
        /**init will remove all the child*/
        pScale9Sprite->initWithFile(mAttrMap["file"].c_str(),
                                    ccXmlAttrParse::toRect(mAttrMap["rect"].c_str()),
                                    ccXmlAttrParse::toRect(mAttrMap["inrect"].c_str()));

    }
    else if(FIND_OBJ_BYKEY(mAttrMap, "plist"))
    {
        /**init will remove all the child*/
        pScale9Sprite->initWithSpriteFrameName(mAttrMap["plist"].c_str(),
                                    ccXmlAttrParse::toRect(mAttrMap["inrect"].c_str()));
    }
    CCARRAY_FOREACH(pArray, child)
    {
        pScale9Sprite->addChild((CCNode*)child);
    }
    CCNodeCreator::setAttribute(pNode);
}

void CCScale9SpriteCreator::setAttribute(CCNode* pNode, const char* strName, const char* strValue, bool bCache)
{
    if(bCache)
        mAttrMap[strName] = strValue;

    else
    {
        CCScale9Sprite* pSprite = (CCScale9Sprite*)pNode;
        if(strcmp(strName, "file") == 0
           ||strcmp(strName, "plist") == 0
           ||strcmp(strName, "rect") == 0
           ||strcmp(strName, "inrect") == 0)
            return;

        else
            CCNodeRGBACreator::setAttribute(pSprite, strName, strValue, bCache);
    }
}

REG_NODE_CREATOR("CCScale9Sprite",CCScale9SpriteCreator)


/**<  CCSpriteBatchNodeCreator */
CCSpriteBatchNodeCreator* CCSpriteBatchNodeCreator::create()
{
    CCSpriteBatchNodeCreator* pCreator = new CCSpriteBatchNodeCreator();
    if(pCreator) pCreator->autorelease();
    return pCreator;
}

CCSpriteBatchNode* CCSpriteBatchNodeCreator::createNode()
{
    CCSpriteBatchNode *batchNode = new CCSpriteBatchNode();
    if(batchNode)
        batchNode->autorelease();
    return batchNode;
}

void CCSpriteBatchNodeCreator::endNode(CCNode* pNode)
{
    CCSpriteBatchNode* pBatchNode = (CCSpriteBatchNode*)pNode;
    pBatchNode->initWithFile(mAttrMap["file"].c_str(), kDefaultSpriteBatchCapacity);

    CCNodeCreator::setAttribute(pNode);
}

void CCSpriteBatchNodeCreator::setAttribute(CCNode* pNode, const char* strName, const char* strValue, bool bCache)
{
    if(bCache)
        mAttrMap[strName] = strValue;

    else
    {
        CCSpriteBatchNode* pBatchNode = (CCSpriteBatchNode*)pNode;
        if(strcmp(strName, "file") == 0)
            return;

        else
            CCNodeCreator::setAttribute(pBatchNode, strName, strValue, bCache);
    }
}

REG_NODE_CREATOR("CCSpriteBatchNode",CCSpriteBatchNodeCreator)


