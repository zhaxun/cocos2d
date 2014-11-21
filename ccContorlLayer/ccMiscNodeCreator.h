#ifndef _CC_MISCNODECREATOR_H_
#define _CC_MISCNODECREATOR_H_

#include "CCNodeCreator.h"
#include "CCNodeCreatorFactory.h"
#include "ccNodeBuilder.h"

/**<  class CCProgressTimerCreator  */
class CCProgressTimerCreator : public CCNodeRGBACreator
{
public:
    static CCProgressTimerCreator* create();
    virtual ~CCProgressTimerCreator(){}
    virtual CCProgressTimer* createNode();
    virtual void endNode(CCNode* pNode);
    virtual void setAttribute(CCNode* pNode, const char* strName, const char* strValue, bool bCache);
};

/************************************************************************/
/**<  class CCMotionStreakCreator  */

class CCMotionStreakCreator : public CCNodeRGBACreator
{
public:
    static CCMotionStreakCreator* create();
    virtual ~CCMotionStreakCreator(){}
    virtual CCMotionStreak* createNode();
    virtual void endNode(CCNode* pNode);
    virtual void setAttribute(CCNode* pNode, const char* strName, const char* strValue, bool bCache);
};

#endif // _CC_MISCNODECREATOR_H_
