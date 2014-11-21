#ifndef _CC_MENUCREATOR_H_
#define _CC_MENUCREATOR_H_


#include "CCNodeCreator.h"
#include "CCNodeCreatorFactory.h"
#include "ccNodeBuilder.h"
#include "ccLayerCreator.h"

/**------------------------------------------
 * class CCMenuItemCreator
 *------------------------------------------*/
class CCMenuItemCreator : public CCNodeRGBACreator
{
public:
    static CCMenuItemCreator* create();
    virtual ~CCMenuItemCreator() {}
    virtual CCMenuItem* createNode();
    virtual void endNode(CCNode* pNode);
    virtual void setAttribute(CCNode* pMenu, const char* strName, const char* strValue, bool bCache);
};

/**------------------------------------------
 * class CCMenuItemSpriteCreator
 *------------------------------------------*/
class CCMenuItemSpriteCreator : public CCMenuItemCreator
{
public:
    static CCMenuItemSpriteCreator* create();
    virtual ~CCMenuItemSpriteCreator() {}
    virtual CCMenuItemSprite* createNode();
    virtual void endNode(CCNode* pNode);
};

/**------------------------------------------
 * class CCMenuItemToggleCreator
 *------------------------------------------*/
class CCMenuItemToggleCreator : public CCMenuItemCreator
{
public:
    static CCMenuItemToggleCreator* create();
    virtual ~CCMenuItemToggleCreator() {}
    virtual CCMenuItemToggle* createNode();
    virtual void setParent(CCNode* pParent, CCNode* pChild);
    virtual void endNode(CCNode* pNode);
    virtual void setAttribute(CCNode* pMenu, const char* strName, const char* strValue, bool bCache);
};

/**------------------------------------------
 * class CCMenuCreator
 *------------------------------------------*/
class CCMenuCreator : public CCLayerRGBACreator
{
public:
    static CCMenuCreator* create();
    virtual ~CCMenuCreator() {}
    virtual CCMenu* createNode();
    virtual void setAttribute(CCNode* pMenu, const char* strName, const char* strValue, bool bCache);
};

#endif // _CC_MENUCREATOR_H_
