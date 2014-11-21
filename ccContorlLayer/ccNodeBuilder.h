#ifndef _CC_NODE_BUILDER_H_
#define _CC_NODE_BUILDER_H_

#include <cocos2d.h>
#include <list>
#include "ccXml.h"
#include "ccControlLayer.h"
#include "ccNodeCreator.h"
#include "ccNodeCreatorFactory.h"

class CCNodeBuilder : public CCObject, public CCXmlHandler
{
public:
    CCNodeBuilder();
    virtual ~CCNodeBuilder();
    CREATE_FUNC(CCNodeBuilder);

    bool init();
    bool initByXmlFile(CCNode* root, const char* xmlResFile);
    bool initByXmlContent(CCNode* root, const char* xmlResContent, int len = 0);
    CCNode* createNodeByXmlFile(const char* xmlResFile, Json* jsonFile);
    CCNode* createNodeByXmlContent(const char* xmlResContent, int len = 0);

    CCNode* getRoot(){ return mRoot; }

public:
    virtual void startDocument(){}
	virtual void endDocument(){}
	virtual void startElement(const std::string& strName);
	virtual void endElement(const std::string& strName);
	virtual void attribute(const std::string& strName, const std::string& strValue);
	virtual void characters(const std::string& strValue);

protected:
    void push_back(CCNodeCreator* pCreator, CCNode* pNode);
    void pop_back();

protected:
    std::list<CCNode*> mNodeStack;
    std::list<CCNodeCreator*> mNodeCreatorStack;

    CCNode* mRoot;
    CCNode* mNode;
};

#endif // _CC_NODE_BUILDER_H_
