#ifndef CC_NODE_CREATORF_FACTORY_H
#define CC_NODE_CREATORF_FACTORY_H

#include <cocos2d.h>
#include "ccNodeCreator.h"

USING_NS_CC;

typedef CCNodeCreator* (*CCNodeCreatorNew)();

class CCNodeCreatorFactory : public CCObject
{
protected:
    CCNodeCreatorFactory();

public:
    virtual ~CCNodeCreatorFactory();
    static CCNodeCreatorFactory* shared();

    bool regNodeCreator(const char* name, CCNodeCreatorNew pNodeCreatorNew);
    CCNodeCreator* getNodeCreator(const char* name);

private:
    //static CCNodeCreatorFactory* mInstance;
    std::map<std::string, CCNodeCreatorNew> m_clsMap;

    REG_GARBO(CCNodeCreatorFactory)
};



#define REG_NODE_CREATOR(name, kClass) struct stReg##kClass \
{\
    stReg##kClass()\
    {\
        CCNodeCreatorFactory::shared()->regNodeCreator(name, (CCNodeCreatorNew)kClass::create); \
    }\
} instReg##kClass;

#endif // CC_NODE_CREATORF_FACTORY_H
