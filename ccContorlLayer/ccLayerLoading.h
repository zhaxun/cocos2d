#ifndef _LOADING_LAYER_H_
#define _LOADING_LAYER_H_

#include <cocos2d.h>
#include <cocos-ext.h>
#include <spine/Json.h>
USING_NS_CC;
USING_NS_CC_EXT;

class CCLayerLoading :  public CCLayer
{
public:
    static CCScene* scene(std::string xmlFile);
    static CCScene* scene(std::string xmlFile, CCScene* pNextScene);

    CCLayerLoading(const char* xmlfile);
    CCLayerLoading(const char* xmlfile, CCScene* pNextScene);
    virtual ~CCLayerLoading();

    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    virtual void onEnterTransitionDidFinish();

    virtual void parseConfigFile();
    virtual void loadingResources();
    virtual void loadingResources(std::string type, std::string file);
    virtual void loadResource(std::string type, std::string file);
    virtual void updateLoading();
    virtual void update(float fDelta);

protected:
    cocos2d::CCLabelTTF *m_pLabelLoading;
    cocos2d::CCLabelTTF *m_pLabelPercent;

    int mCurrentNum;
    int mTotalNum;

    std::string mXmlFile;
    CCScene* mNextScene;
    Json* mLoadingJson;
};
#endif //_LOADING_LAYER_H_
