#include "ccLayerCreator.h"


/**********************************************
            CCLayerCreator
***********************************************/
CCLayerCreator* CCLayerCreator::create()
{
    CCLayerCreator* pCreator = new CCLayerCreator();
    if(pCreator) pCreator->autorelease();
    return pCreator;
}

CCLayer* CCLayerCreator::createNode()
{
    return CCLayer::create();
}

void CCLayerCreator::endNode(CCNode* pNode)
{
    CCNodeCreator::setAttribute(pNode);
}

void CCLayerCreator::setAttribute(CCNode* layer, const char* strName, const char* strValue, bool bCache)
{
    if(bCache)
        mAttrMap[strName] = strValue;

    else
    {
        CCLayer* pLayer = (CCLayer*)layer;
        if(strcmp(strName, "touchpriority") == 0)
            pLayer->setTouchPriority(ccXmlAttrParse::toInt(strValue));

        else
            CCNodeCreator::setAttribute((CCNode*)pLayer, strName, strValue, bCache);
    }
}


REG_NODE_CREATOR("CCLayer",CCLayerCreator)



/**********************************************
            CCLayerRGBACreator
***********************************************/
CCLayerRGBACreator* CCLayerRGBACreator::create()
{
    CCLayerRGBACreator* pCreator = new CCLayerRGBACreator();
    if(pCreator) pCreator->autorelease();
    return pCreator;
}

CCLayerRGBA* CCLayerRGBACreator::createNode()
{
    return CCLayerRGBA::create();;
}

void CCLayerRGBACreator::endNode(CCNode* pNode)
{
    CCNodeCreator::setAttribute(pNode);
}

void CCLayerRGBACreator::setAttribute(CCNode* pNode, const char* strName, const char* strValue, bool bCache)
{
    if(bCache)
        mAttrMap[strName] = strValue;

    else
    {
        CCLayerRGBA* pLayerRGBA = (CCLayerRGBA*)pNode;
        if(strcmp(strName, "color") == 0)
            pLayerRGBA->setColor(ccXmlAttrParse::toColor3B(strValue));

        else if(strcmp(strName, "opacity") == 0)
            pLayerRGBA->setOpacity(ccXmlAttrParse::toInt(strValue));

        else
            CCLayerCreator::setAttribute(pNode, strName, strValue, bCache);
    }
}

REG_NODE_CREATOR("CCLayerRGBA",CCLayerRGBACreator)

/**********************************************
            CCLayerColor
***********************************************/

CCLayerColorCreator* CCLayerColorCreator::create()
{
    CCLayerColorCreator* pCreator = new CCLayerColorCreator();
    if(pCreator) pCreator->autorelease();
    return pCreator;
}

CCLayerColor* CCLayerColorCreator::createNode()
{
    return CCLayerColor::create();;
}

void CCLayerColorCreator::endNode(CCNode* pNode)
{
    ((CCLayerColor*)pNode)->initWithColor(ccXmlAttrParse::toColor4B(mAttrMap["color"].c_str()),
                                          ccXmlAttrParse::toInt(mAttrMap["width"].c_str()),
                                          ccXmlAttrParse::toInt(mAttrMap["height"].c_str()));
    CCNodeCreator::setAttribute(pNode);
}

void CCLayerColorCreator::setAttribute(CCNode* pNode, const char* strName, const char* strValue, bool bCache)
{
    if(bCache)
        mAttrMap[strName] = strValue;

    else
    {
        CCLayerColor* pLayer = (CCLayerColor*)pNode;
        if(strcmp(strName, "color") == 0
            ||strcmp(strName, "width") == 0
            ||strcmp(strName, "height") == 0)
            return;

        else
            CCLayerRGBACreator::setAttribute(pNode, strName, strValue, bCache);
    }
}

REG_NODE_CREATOR("CCLayerColor",CCLayerColorCreator)
