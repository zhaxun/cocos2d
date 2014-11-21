#include "ccMenuCreator.h"

/**------------------------------------------
 * class CCMenuItemCreator
 *------------------------------------------*/
CCMenuItemCreator* CCMenuItemCreator::create()
{
    CCMenuItemCreator* pCreator = new CCMenuItemCreator();
    if(pCreator) pCreator->autorelease();
    return pCreator;
}
CCMenuItem* CCMenuItemCreator::createNode()
{
    CCMenuItem* pMenuItem = CCMenuItem::create();
    return pMenuItem;
}
void CCMenuItemCreator::endNode(CCNode* pNode)
{
    ((CCMenuItem*)pNode)->initWithTarget(mRootDelegate,
                                       menu_selector(CCControlLayer::menuItemCallback));
    CCNodeCreator::setAttribute(pNode);
}
void CCMenuItemCreator::setAttribute(CCNode* pNode, const char* strName, const char* strValue, bool bCache)
{
    CCMenuItem* pMenuItem = (CCMenuItem*)pNode;
    if(bCache)
        mAttrMap[strName] = strValue;

    else
    {
        if(strcmp(strName, "m_selected") == 0)
        {
            if(ccXmlAttrParse::toBool(strValue))
                pMenuItem->selected();
            else
                pMenuItem->unselected();
        }
        else if(strcmp(strName, "m_enable") == 0)
            pMenuItem->setEnabled(ccXmlAttrParse::toBool(strValue));

        else
            CCNodeRGBACreator::setAttribute(pMenuItem, strName, strValue, bCache);
    }
}

REG_NODE_CREATOR("CCMenuItem",CCMenuItemCreator)


/**------------------------------------------
 * class CCMenuItemSpriteCreator
 *------------------------------------------*/
CCMenuItemSpriteCreator* CCMenuItemSpriteCreator::create()
{
    CCMenuItemSpriteCreator* pCreator = new CCMenuItemSpriteCreator();

    if(pCreator)
        pCreator->autorelease();

    return pCreator;
}

CCMenuItemSprite* CCMenuItemSpriteCreator::createNode()
{
    CCMenuItemSprite *pRet = new CCMenuItemSprite();
    if(pRet)
         pRet->autorelease();

    else
        CC_SAFE_DELETE(pRet);
    return pRet;
}

void CCMenuItemSpriteCreator::endNode(CCNode* pNode)
{
    CCArray* pArray =  pNode->getChildren();
    int nCount = pArray->count();
    CCNode* pNodeNormal = nCount >= 1 ? (CCNode*)pArray->objectAtIndex(0) : NULL;
    CCNode* pNodeSelected = nCount >= 2 ? (CCNode*)pArray->objectAtIndex(1) : NULL;
    CCNode* pNodeDisabled = nCount >= 3 ? (CCNode*)pArray->objectAtIndex(2) : NULL;
    CC_SAFE_RETAIN(pNodeNormal);
    CC_SAFE_RETAIN(pNodeSelected);
    CC_SAFE_RETAIN(pNodeDisabled);

    pNode->removeAllChildren();
    ((CCMenuItemSprite*)pNode)->initWithNormalSprite(pNodeNormal, pNodeSelected, pNodeDisabled,
                                                     mRootDelegate,
                                                     menu_selector(CCControlLayer::menuItemCallback));
    CC_SAFE_RELEASE(pNodeNormal);
    CC_SAFE_RELEASE(pNodeSelected);
    CC_SAFE_RELEASE(pNodeDisabled);

    CCNodeCreator::setAttribute(pNode);
}

REG_NODE_CREATOR("CCMenuItemSprite",CCMenuItemSpriteCreator)

/**------------------------------------------
 * class CCMenuItemToggleCreator
 *------------------------------------------*/
CCMenuItemToggleCreator* CCMenuItemToggleCreator::create()
{
    CCMenuItemToggleCreator* pCreator = new CCMenuItemToggleCreator();
    if(pCreator) pCreator->autorelease();
    return pCreator;
}

CCMenuItemToggle* CCMenuItemToggleCreator::createNode()
{
    CCMenuItemToggle* pRet = CCMenuItemToggle::create();
    ((CCMenuItem*)pRet)->initWithTarget(mRootDelegate, menu_selector(CCControlLayer::menuItemCallback));
    return pRet;
}

void CCMenuItemToggleCreator::setParent(CCNode* pParent, CCNode* pChild)
{
    CCMenuItemToggle* pMenuItemToggle = (CCMenuItemToggle*)pParent;
    pMenuItemToggle->addSubItem((CCMenuItem*)pChild);
}

void CCMenuItemToggleCreator::setAttribute(CCNode* menu, const char* strName, const char* strValue, bool bCache)
{
    CCMenuItemToggle* pMenuItemToggle = (CCMenuItemToggle*)menu;
    if(bCache)
        mAttrMap[strName] = strValue;

    else
    {
        if(strcmp(strName, "selectedIndex") == 0)
            pMenuItemToggle->setSelectedIndex(ccXmlAttrParse::toInt(strValue));

        else
            CCMenuItemCreator::setAttribute((CCNode*)menu, strName, strValue, bCache);
    }
}

void CCMenuItemToggleCreator::endNode(CCNode* pNode)
{
    CCNodeCreator::setAttribute(pNode);
}

REG_NODE_CREATOR("CCMenuItemToggle",CCMenuItemToggleCreator)

/**------------------------------------------
 * class CCMenuCreator
 *------------------------------------------*/
CCMenuCreator* CCMenuCreator::create()
{
    CCMenuCreator* pCreator = new CCMenuCreator();
    if(pCreator) pCreator->autorelease();
    return pCreator;
}

CCMenu* CCMenuCreator::createNode()
{
    return CCMenu::create();
}


void CCMenuCreator::setAttribute(CCNode* menu, const char* strName, const char* strValue, bool bCache)
{
    CCMenu* pMenu = (CCMenu*)menu;
    if(bCache)
        mAttrMap[strName] = strValue;

    CCLayerRGBACreator::setAttribute((CCNode*)menu, strName, strValue, bCache);

}
REG_NODE_CREATOR("CCMenu",CCMenuCreator)
