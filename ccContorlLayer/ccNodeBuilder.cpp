#include "ccNodeBuilder.h"


CCNodeBuilder::CCNodeBuilder()
{
    mRoot = NULL;
    mNode = NULL;
}

CCNodeBuilder::~CCNodeBuilder()
{
    while(mNodeCreatorStack.size()>0)
    {
        CCNodeCreator* pCreator = mNodeCreatorStack.back();
        CC_SAFE_RELEASE(pCreator);
        mNodeCreatorStack.pop_back();
    }
    while(mNodeStack.size()>0)
    {
        CCNode* pNode = mNodeStack.back();
        CC_SAFE_RELEASE(pNode);
        mNodeStack.pop_back();
    }
}

bool CCNodeBuilder::init()
{
    return true;
}

void CCNodeBuilder::push_back(CCNodeCreator* pCreator, CCNode* pNode)
{
    CC_SAFE_RETAIN(pCreator);
    mNodeCreatorStack.push_back(pCreator);

    CC_SAFE_RETAIN(pNode);
    mNodeStack.push_back(pNode);
}

void CCNodeBuilder::pop_back()
{
    if(mNodeCreatorStack.size()>0)
    {
        CCNodeCreator* pCreator = mNodeCreatorStack.back();
        CC_SAFE_RELEASE(pCreator);
        mNodeCreatorStack.pop_back();
    }
    if(mNodeStack.size()>0)
    {
        CCNode* pNode = mNodeStack.back();
        CC_SAFE_RELEASE(pNode);
        mNodeStack.pop_back();
    }
}

bool CCNodeBuilder::initByXmlFile(CCNode* root, const char* xmlResFile)
{
    bool bRet = false;
    unsigned long len = 0;
    unsigned char* mFileContent = CCFileUtils::sharedFileUtils()->getFileData(xmlResFile, "rb", &len);
    if(mFileContent)
	{
	    std::string str = std::string((char*)mFileContent, len);
        bRet = initByXmlContent(root, (char*)str.c_str(), len);
        delete[] mFileContent;
	}

    return bRet;
}

bool CCNodeBuilder::initByXmlContent(CCNode* root, const char* xmlResContent,int len)
{
    //if(mRoot)
    //    CC_SAFE_RELEASE_NULL(mRoot);

    mRoot = root;
    CCXmlParser xmlParser(this);
    xmlParser.parse(xmlResContent, len);

    return true;
}
CCNode* CCNodeBuilder::createNodeByXmlFile(const char* xmlResFile, Json* jsonFile)
{
    unsigned long len = 0;
    unsigned char* mFileContent = CCFileUtils::sharedFileUtils()->getFileData(xmlResFile, "r", &len);
    if(mFileContent)
    {
		std::string str = std::string((char*)mFileContent, len);
		str = ccXmlAttrParse::transXmlByParams(str.c_str(), jsonFile);
		delete[] mFileContent;
        return createNodeByXmlContent((char*)str.c_str());
    }
    return NULL;
}
CCNode* CCNodeBuilder::createNodeByXmlContent(const char* xmlResContent, int len)
{
    CCXmlParser xmlParser(this);
    xmlParser.parse(xmlResContent, len);
    return mNode;
}

void CCNodeBuilder::startElement(const std::string& strName)
{
    CCNodeCreator* pCreator = CCNodeCreatorFactory::shared()->getNodeCreator(strName.c_str());
    pCreator->setDelegate(mRoot);

    CCNode* pNode = pCreator->createNode();
    if(pNode != NULL) push_back(pCreator, pNode);
    if(mRoot == NULL && mNode == NULL)
        mNode = pNode;
}

void CCNodeBuilder::endElement(const std::string& strName)
{
    CCNodeCreator* pCreator = mNodeCreatorStack.back();
    CCNode* pNode = mNodeStack.back();
    if(pNode == NULL || pCreator == NULL)
        return;

    if(mNodeCreatorStack.size() < 2)
    {
        if(mRoot != NULL && mNode == NULL)
            mRoot->addChild(pNode);
    }
    else
    {
        std::list<CCNode*>::iterator it = mNodeStack.end();
        --it;
        --it;
        CCNode* pParentNode = *it;

        std::list<CCNodeCreator*>::iterator cit = mNodeCreatorStack.end();
        --cit;
        --cit;
        CCNodeCreator* pParentCreator = *cit;
        pParentCreator->setParent(pParentNode, pNode);
    }
    pCreator->endNode(pNode);
    pop_back();
}

void CCNodeBuilder::attribute(const std::string& strName, const std::string& strValue)
{
    CCNode* pNode = mNodeStack.back();
    CCNodeCreator* pCreator = mNodeCreatorStack.back();
    pCreator->setAttribute(pNode, strName.c_str(), strValue.c_str(), true);
}

void CCNodeBuilder::characters(const std::string& strValue)
{
    attribute("character", strValue);
}
