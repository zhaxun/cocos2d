#ifndef _CC_LAYERCREATOR_H_
#define _CC_LAYERCREATOR_H_


#include "CCNodeCreator.h"
#include "CCNodeCreatorFactory.h"
#include "ccNodeBuilder.h"


/**********************************************
            CCLayerCreator
***********************************************/
class CCLayerCreator : public CCNodeCreator
{
public:
    static CCLayerCreator* create();
    virtual ~CCLayerCreator(){}
    virtual CCLayer* createNode();
    virtual void endNode(CCNode* pNode);
    virtual void setAttribute(CCNode* pLayer, const char* strName, const char* strValue, bool bCache);
};

/**********************************************
            CCLayerRGBACreator
***********************************************/
class CCLayerRGBACreator : public CCLayerCreator
{
public:
    static CCLayerRGBACreator* create();
    virtual ~CCLayerRGBACreator(){}
    virtual CCLayerRGBA* createNode();
    virtual void endNode(CCNode* pNode);
    virtual void setAttribute(CCNode* pNode, const char* strName, const char* strValue, bool bCache);
};
/**********************************************
            CCLayerColorCreator
***********************************************/
class CCLayerColorCreator : public CCLayerRGBACreator
{
public:
    static CCLayerColorCreator* create();
    virtual ~CCLayerColorCreator(){}
    virtual CCLayerColor* createNode();
    virtual void endNode(CCNode* pNode);
    virtual void setAttribute(CCNode* pNode, const char* strName, const char* strValue, bool bCache);
};
#endif // _CC_LAYERCREATOR_H_
