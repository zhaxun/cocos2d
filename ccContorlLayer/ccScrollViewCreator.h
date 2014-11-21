#ifndef _CC_SCROLLVIEWCREATOR_H_
#define _CC_SCROLLVIEWCREATOR_H_

#include "CCNodeCreatorFactory.h"
#include "ccNodeBuilder.h"
#include "ccLayerCreator.h"

/**<  class CCScrollViewCreator */
class CCScrollViewCreator : public CCLayerCreator
{
public:
    static CCScrollViewCreator* create();
    virtual ~CCScrollViewCreator(){}
    virtual CCScrollView* createNode();
    virtual void setParent(CCNode* pParent, CCNode* pChild);
    virtual void endNode(CCNode* pNode);
    virtual void setAttribute(CCNode* pNode, const char* strName, const char* strValue, bool bCache);
};

/**<  class CCTableViewCreator */
class CCTableViewCreator : public CCScrollViewCreator
{
public:
    static CCTableViewCreator* create();
    virtual ~CCTableViewCreator(){}
    virtual CCTableView* createNode();
    virtual void endNode(CCNode* pNode);
    virtual void setAttribute(CCNode* pNode, const char* strName, const char* strValue, bool bCache);
};

/**<  class CCTableViewCellCreator */
class CCTableViewCellCreator : public CCNodeCreator
{
public:
    static CCTableViewCellCreator* create();
    virtual ~CCTableViewCellCreator(){}
    virtual CCTableViewCell* createNode();
    virtual void endNode(CCNode* pNode);
    virtual void setAttribute(CCNode* pNode, const char* strName, const char* strValue, bool bCache);
};

#endif // _CC_SCROLLVIEWCREATOR_H_
