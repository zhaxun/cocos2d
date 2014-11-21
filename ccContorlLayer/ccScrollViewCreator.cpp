#include "ccScrollViewCreator.h"
#include "ccControlLayer.h"

/**<  class CCScrollViewCreator */
CCScrollViewCreator* CCScrollViewCreator::create()
{
    CCScrollViewCreator* pCreator = new CCScrollViewCreator();
    if(pCreator) pCreator->autorelease();
    return pCreator;
}

CCScrollView* CCScrollViewCreator::createNode()
{
    return CCScrollView::create();
}

void CCScrollViewCreator::setParent(CCNode* pParent, CCNode* pChild)
{
    ((CCScrollView*)pParent)->setContainer(pChild);
}

void CCScrollViewCreator::endNode(CCNode* pNode)
{
    CCScrollView* pScrollView =  (CCScrollView* )pNode;
    pScrollView->setDelegate(dynamic_cast<CCScrollViewDelegate*>(mRootDelegate));
    CCNodeCreator::setAttribute(pNode);
}

void CCScrollViewCreator::setAttribute(CCNode* pNode, const char* strName, const char* strValue, bool bCache)
{
    CCScrollView* pScrollView = (CCScrollView*)pNode;
    if(bCache)
        mAttrMap[strName] = strValue;

    else
    {
        if(strcmp(strName, "offset") == 0)
            pScrollView->setContentOffset(ccXmlAttrParse::toPoint(strValue));

        else if(strcmp(strName, "direction") == 0)
            pScrollView->setDirection((CCScrollViewDirection)ccXmlAttrParse::toInt(strValue));

        else if(strcmp(strName, "view_size") == 0)
            pScrollView->setViewSize(ccXmlAttrParse::toSize(strValue));

        else if(strcmp(strName, "touch") == 0)
            pScrollView->setTouchEnabled(ccXmlAttrParse::toBool(strValue));

        else if(strcmp(strName, "bounceable") == 0)
            pScrollView->setBounceable(ccXmlAttrParse::toBool(strValue));
        else
            CCLayerCreator::setAttribute(pNode, strName, strValue, bCache);
    }
}

REG_NODE_CREATOR("CCScrollView",CCScrollViewCreator)


/**<  class CCTableViewCreator */
CCTableViewCreator* CCTableViewCreator::create()
{
    CCTableViewCreator* pCreator = new CCTableViewCreator();
    if(pCreator) pCreator->autorelease();
    return pCreator;
}

CCTableView* CCTableViewCreator::createNode()
{
    CCTableView* pTableView = new CCTableView();
    if(pTableView)
    {
        pTableView->autorelease();
        return pTableView;
    }
    CC_SAFE_DELETE(pTableView);
    return NULL;
}

void CCTableViewCreator::endNode(CCNode* pNode)
{
    CCTableView* pTableView = (CCTableView*)pNode;
    pTableView->initWithViewSize(ccXmlAttrParse::toSize(mAttrMap["view_size"].c_str()), NULL);
    pTableView->setDataSource(dynamic_cast<CCTableViewDataSource*>(mRootDelegate));
    pTableView->setDelegate(dynamic_cast<CCTableViewDelegate*>(mRootDelegate));

    CCNodeCreator::setAttribute(pNode);
}

void CCTableViewCreator::setAttribute(CCNode* pNode, const char* strName, const char* strValue, bool bCache)
{
    CCTableView* pTableView = (CCTableView*)pNode;
    if(bCache)
        mAttrMap[strName] = strValue;

    else
    {
        if(strcmp(strName, "fill_order") == 0)
            pTableView->setVerticalFillOrder((CCTableViewVerticalFillOrder)ccXmlAttrParse::toInt(strValue));

        else
            CCScrollViewCreator::setAttribute(pNode, strName, strValue, bCache);
    }
}

REG_NODE_CREATOR("CCTableView",CCTableViewCreator)



/**<  class CCTableViewCellCreator */
CCTableViewCellCreator* CCTableViewCellCreator::create()
{
    CCTableViewCellCreator* pCreator = new CCTableViewCellCreator();
    if(pCreator) pCreator->autorelease();
    return pCreator;
}

CCTableViewCell* CCTableViewCellCreator::createNode()
{
    CCTableViewCell* pCell = new CCTableViewCell();
    if(pCell)
    {
        pCell->autorelease();
        return pCell;
    }
    CC_SAFE_DELETE(pCell);
    return NULL;
}

void CCTableViewCellCreator::endNode(CCNode* pNode)
{
    CCTableViewCell* pTableViewCell =  (CCTableViewCell* )pNode;

    CCNodeCreator::setAttribute(pNode);
}

void CCTableViewCellCreator::setAttribute(CCNode* pNode, const char* strName, const char* strValue, bool bCache)
{
    CCTableViewCell* pTableViewCell = (CCTableViewCell*)pNode;
    if(bCache)
        mAttrMap[strName] = strValue;

    else
    {
        if(strcmp(strName, "index") == 0)
            pTableViewCell->setObjectID(ccXmlAttrParse::toInt(strValue));

        else
            CCNodeCreator::setAttribute(pNode, strName, strValue, bCache);
    }
}

REG_NODE_CREATOR("CCTableViewCell",CCTableViewCellCreator)
