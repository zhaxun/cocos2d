#include "CCLayerLoading.h"
#include "CCNodeCreator.h"
#include "CCAnimationFactory.h"
#include "ccFileHelper.h"


CCScene* CCLayerLoading::scene(std::string xmlFile)
{
    CCScene *scene = CCScene::create();
    CCLayer *pLayer = new CCLayerLoading(xmlFile.c_str());

    if (pLayer && pLayer->init())
        pLayer->autorelease();
    else
        CC_SAFE_DELETE(pLayer);
    scene->addChild(pLayer);
    return scene;
}

CCLayerLoading::CCLayerLoading(const char* xmlfile)
{
    mCurrentNum = 0;
    mTotalNum = 100;
    mXmlFile = xmlfile;
    mNextScene = NULL;
}

CCScene* CCLayerLoading::scene(std::string xmlFile, CCScene* pNextScene)
{
    CCScene *scene = CCScene::create();
    CCLayer *pLayer = new CCLayerLoading(xmlFile.c_str(), pNextScene);

    if (pLayer && pLayer->init())
        pLayer->autorelease();
    else
        CC_SAFE_DELETE(pLayer);
    scene->addChild(pLayer);
    return scene;
}

CCLayerLoading::CCLayerLoading(const char* xmlfile, CCScene* pNextScene)
{
    mCurrentNum = 0;
    mTotalNum = 100;
    mXmlFile = xmlfile;
    mNextScene = pNextScene;
    CC_SAFE_RETAIN(mNextScene);
}

CCLayerLoading::~CCLayerLoading()
{
    CC_SAFE_RELEASE(mNextScene);
    CCJsonHelper::unloadJson(mLoadingJson);
}

bool CCLayerLoading::init()
{
    if (!CCLayer::init())
        return false;

    CCSize size = CCDirector::sharedDirector()->getWinSize();

    m_pLabelLoading = CCLabelTTF::create("Loading...", "Arial", 25);
    m_pLabelPercent = CCLabelTTF::create("0%", "Arial", 25) ;
    m_pLabelLoading->setPosition(ccp(size.width / 2, size.height / 2 + 50));
    m_pLabelPercent->setPosition(ccp(size.width / 2, size.height / 2));
    this->addChild(m_pLabelLoading);
    this->addChild(m_pLabelPercent);

    parseConfigFile();

    return true;
}

void CCLayerLoading::parseConfigFile()
{
    mLoadingJson = CCJsonHelper::loadJsonFromFile(mXmlFile);
    Json* pJson = Json_getItem(mLoadingJson, "loading");
    mTotalNum = Json_getSize(pJson);
}

void CCLayerLoading::onEnter()
{
    CCLayer::onEnter();
    scheduleUpdate();
}

void CCLayerLoading::onExit()
{
    CCLayer::onExit();
    unscheduleUpdate();
}

void CCLayerLoading::update(float fDelta)
{
    loadingResources();
    updateLoading();
}

void CCLayerLoading::onEnterTransitionDidFinish()
{
    CCLayer::onEnterTransitionDidFinish();
}

void CCLayerLoading::updateLoading()
{
    char tmp[10];
    sprintf(tmp, "%d%%", (int)(((float)mCurrentNum / mTotalNum) * 100));
    m_pLabelPercent->setString(tmp);
}

void CCLayerLoading::loadingResources()
{
    if (mCurrentNum == mTotalNum)
    {
        if(mNextScene)
            CCDirector::sharedDirector()->replaceScene(mNextScene);
    }
    else
    {
        Json* pJson = Json_getItem(mLoadingJson, "loading");
        Json* value = pJson->child;
        int n = 0;
        while(n < mCurrentNum)
        {
            value = value->next;
            n++;
        }
        std::string strType = Json_getString(value, "type", "");
        std::string strFile = Json_getString(value, "file", "");
        loadingResources(strType, strFile);
        mCurrentNum++;
    }
}

void CCLayerLoading::loadingResources(std::string type, std::string file)
{
    if(file.compare("") == 0)
        return;

    if(type.compare("animation") == 0)
        CCAnimationFactory::shared()->cacheAnimations(file.c_str());

    else if(type.compare("spriteframe") == 0)
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(file.c_str());

    else if(type.compare("texture") == 0)
        CCTextureCache::sharedTextureCache()->addImage(file.c_str());
    else
        loadResource(type, file);
}

void CCLayerLoading::loadResource(std::string type, std::string file)
{
    //override me, if you need loading other resource!
}
