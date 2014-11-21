#ifndef _CC_LABELCREATOR_H_
#define _CC_LABELCREATOR_H_

#include "CCNodeCreator.h"
#include "ccSpriteCreator.h"
#include "CCNodeCreatorFactory.h"
#include "ccNodeBuilder.h"

/**<  class CCLabelTTFCreator */
class CCLabelTTFCreator : public CCSpriteCreator
{
public:
    static CCLabelTTFCreator* create();
    virtual ~CCLabelTTFCreator(){}
    virtual CCLabelTTF* createNode();
    virtual void endNode(CCNode* pNode);
    virtual void setAttribute(CCNode* pNode, const char* strName, const char* strValue, bool bCache);
};

/**<  class CCLabelBMFontCreator */
class CCLabelBMFontCreator : public CCSpriteBatchNodeCreator
{
public:
    static CCLabelBMFontCreator* create();
    virtual ~CCLabelBMFontCreator();
    virtual CCLabelBMFont* createNode();
    virtual void endNode(CCNode* pNode);
    virtual void setAttribute(CCNode* pNode, const char* strName, const char* strValue, bool bCache);
};

/**<  class CCLabelAtlasCreator */
class CCLabelAtlasCreator : public CCNodeRGBACreator
{
public:
    static CCLabelAtlasCreator* create();
    virtual ~CCLabelAtlasCreator();
    virtual CCLabelAtlas* createNode();
    virtual void endNode(CCNode* pNode);
    virtual void setAttribute(CCNode* pNode, const char* strName, const char* strValue, bool bCache);
};

#endif // _CC_LABELCREATOR_H_
