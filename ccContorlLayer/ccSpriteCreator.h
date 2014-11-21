#ifndef _CC_SPRITECREATOR_H_
#define _CC_SPRITECREATOR_H_

#include "CCNodeCreator.h"
#include "CCNodeCreatorFactory.h"
#include "ccNodeBuilder.h"

/**<class CCSpriteCreator     */
class CCSpriteCreator : public CCNodeRGBACreator
{
public:
    static CCSpriteCreator* create();
    virtual ~CCSpriteCreator() {}
    virtual CCSprite* createNode();
    virtual void endNode(CCNode* pNode);
    virtual void setAttribute(CCNode* pSprite, const char* strName, const char* strValue, bool bCache);
};

/**<  CCScale9SpriteCreator         */
class CCScale9SpriteCreator : public CCNodeRGBACreator
{
public:
    static CCScale9SpriteCreator* create();
    virtual ~CCScale9SpriteCreator() {}
    virtual CCScale9Sprite* createNode();
    virtual void endNode(CCNode* pNode);
    virtual void setAttribute(CCNode* pSprite, const char* strName, const char* strValue, bool bCache);
};

/**<  CCSpriteBatchNodeCreator */
class CCSpriteBatchNodeCreator : public CCNodeCreator
{
public:
    static CCSpriteBatchNodeCreator* create();
    virtual ~CCSpriteBatchNodeCreator() {}
    virtual CCSpriteBatchNode* createNode();
    virtual void endNode(CCNode* pNode);
    virtual void setAttribute(CCNode* pSprite, const char* strName, const char* strValue, bool bCache);
};

#endif // _CC_SPRITECREATOR_H_
