#include "CCControlLayer.h"
#include "ccNodeBuilder.h"
#include "ccFileHelper.h"

CCControlLayer::CCControlLayer(const char* xmlfile)
{
    mXmlFile = xmlfile;
    mCallFunc = NULL;
}

CCControlLayer::~CCControlLayer()
{
    std::map<int, Json*>::iterator it = mJsonMap.begin();
    while(it != mJsonMap.end())
    {
        Json* p = it->second;
        CCJsonHelper::unloadJson(p);
        it++;
    }
    CC_SAFE_RELEASE(mCallFunc);
}

bool CCControlLayer::init()
{
    if (!CCLayer::init())
        return false;

    CCNodeBuilder* pNodeBuilder =  CCNodeBuilder::create();
    return pNodeBuilder->initByXmlFile(this, mXmlFile.c_str());
}

void CCControlLayer::onEnter()
{
    CCLayer::onEnter();
    mMenuClicked = false;
    if(mCallFunc)
    {
        mCallFunc->execute();
        mCallFunc->release();
        mCallFunc = NULL;
    }
}

void CCControlLayer::onExit()
{
    mMenuClicked = false;
    CCLayer::onExit();
}

void CCControlLayer::onEnterTransitionDidFinish()
{
    CCLayer::onEnterTransitionDidFinish();
}

void CCControlLayer::menuItemCallback(CCObject* pSender)
{
    onMenuItemClick((CCMenuItem*)pSender);
}
void CCControlLayer::controlTouchCallback(CCObject* pSender, CCControlEvent event)
{
    onControlTouchEvent(pSender, event);
}
void CCControlLayer::onControlTouchEvent(CCObject* pSender, CCControlEvent event)
{
    if  (event & CCControlEventTouchDown)
        CCLOG("CCControlEventTouchDown");
    else if  (event & CCControlEventTouchDragInside)
        CCLOG("CCControlEventTouchDragInside");
    else if  (event & CCControlEventTouchDragOutside)
        CCLOG("CCControlEventTouchDragOutside");
    else if  (event & CCControlEventTouchDragEnter)
        CCLOG("CCControlEventTouchDragEnter");
    else if  (event & CCControlEventTouchDragExit)
        CCLOG("CCControlEventTouchDragExit");
    else if  (event & CCControlEventTouchUpInside)
        CCLOG("CCControlEventTouchUpInside");
    else if  (event & CCControlEventTouchUpOutside)
        CCLOG("CCControlEventTouchUpOutside");
    else if  (event & CCControlEventTouchCancel)
        CCLOG("CCControlEventTouchCancel");
    else if  (event & CCControlEventValueChanged)
        CCLOG("CCControlEventValueChanged");

}
void CCControlLayer::releaseCaches()
{
    CCAnimationCache::purgeSharedAnimationCache();
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();
    CCTextureCache::sharedTextureCache()->removeUnusedTextures();
}

void CCControlLayer::setCallFun(CCCallFunc* pFunc)
{
    CC_SAFE_RELEASE_NULL(mCallFunc);
    mCallFunc = pFunc;
    mCallFunc->retain();
}

/**BEGIN----------------------------For TableView DataSource-----------------*/
void CCControlLayer::setDataSourceTemplate(int tableViewTag, std::string strTemplate)
{
    mDSTemplateMap[tableViewTag] = strTemplate;
}

CCSize CCControlLayer::tableCellSizeForIndex(CCTableView *table, unsigned int idx)
{
    return cellSizeForTable(table);
};

CCSize CCControlLayer::cellSizeForTable(CCTableView *table)
{
    return CCSizeZero;
}

CCTableViewCell* CCControlLayer::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
    CCTableViewCell *cell = table->dequeueCell();
    CCString *string = CCString::createWithFormat("%d", idx);
    Json* pJson = Json_getItemAt(Json_getItem(mJsonMap[table->getTag()],"params"),idx);
    if (cell == NULL)
    {
        CCAssert(pJson!=NULL, "Json Is NULL!");
        cell = (CCTableViewCell*)CCNodeBuilder::create()->createNodeByXmlFile(
            mDSTemplateMap[table->getTag()].c_str(), pJson);
    }
    else
    {
        tableCellContentAtIndex(table, idx, cell, pJson);
    }
    CCAssert(cell!=NULL, "cell Is NULL!");
    return cell;
}

unsigned int CCControlLayer::numberOfCellsInTableView(CCTableView *table)
{
    Json* pJson = Json_getItem(mJsonMap[table->getTag()],"params");
    return Json_getSize(pJson);
}
/**END-----------------For TableView DataSource-------------------------------*/
