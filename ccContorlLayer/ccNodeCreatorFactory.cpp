#include "ccNodeCreatorFactory.h"

//CCNodeCreatorFactory* CCNodeCreatorFactory::mInstance = NULL;
REG_GARBO_DEFINE(CCNodeCreatorFactory)
//CCNodeCreatorFactory::CCNodeCreatorFactoryGarbo CCNodeCreatorFactory::mGarbo;

CCNodeCreatorFactory::CCNodeCreatorFactory()
{
}

CCNodeCreatorFactory::~CCNodeCreatorFactory()
{
}

CCNodeCreatorFactory* CCNodeCreatorFactory::shared()
{
    if(mInstance == NULL)
    {
        mInstance = new CCNodeCreatorFactory();
        if(mInstance==NULL)
        {
            return NULL;
        }
    }
    return mInstance;
}

bool CCNodeCreatorFactory::regNodeCreator(const char* name,  CCNodeCreatorNew pNodeCreatorNew)
{
    m_clsMap[name] = pNodeCreatorNew;

    return true;
}

CCNodeCreator* CCNodeCreatorFactory::getNodeCreator(const char* name)
{
    std::map<std::string, CCNodeCreatorNew>::iterator it;
    it = m_clsMap.find(name);
    if(it != m_clsMap.end())
    {
        CCNodeCreatorNew pNew = it->second;
        return pNew();
    }
    return NULL;
}
