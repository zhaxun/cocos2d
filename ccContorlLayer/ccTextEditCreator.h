#ifndef _CC_TEXTEDITCREATOR_H_
#define _CC_TEXTEDITCREATOR_H_

#include "CCNodeCreator.h"
#include "CCNodeCreatorFactory.h"
#include "ccNodeBuilder.h"
#include "ccLabelCreator.h"

/**<class CCTextFieldTTFCreator     */
class CCTextFieldTTFCreator : public CCLabelTTFCreator
{
public:
    static CCTextFieldTTFCreator* create();
    virtual ~CCTextFieldTTFCreator() {}
    virtual CCTextFieldTTF* createNode();
    virtual void endNode(CCNode* pNode);
    virtual void setAttribute(CCNode* pSprite, const char* strName, const char* strValue, bool bCache);
};

#endif // _CC_TEXTEDITCREATOR_H_
