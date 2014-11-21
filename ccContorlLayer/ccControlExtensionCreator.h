#ifndef _CC_CONTROLEXTENSIONCREATOR_H_
#define _CC_CONTROLEXTENSIONCREATOR_H_

#include "CCNodeCreator.h"
#include "CCNodeCreatorFactory.h"
#include "ccNodeBuilder.h"
#include "ccLayerCreator.h"

/**<class CCControlCreator     */
class CCControlCreator :public CCLayerRGBACreator
{
public:
    static CCControlCreator* create();
    virtual ~CCControlCreator() {}
    virtual CCControl* createNode();
    virtual void endNode(CCNode* pNode);
    virtual void setAttribute(CCNode* pSprite, const char* strName, const char* strValue, bool bCache);

    void addTargetWithActionForControlEvents(CCNode* pNode);
    CCLabelTTF* createTTFLabel(std::string str);
    CCLabelBMFont* createBMFontLabel(std::string str);
    CCScale9Sprite* createSprite(std::string str);
};

/**<class CCControlButtonCreator     */
class CCControlButtonCreator :public CCControlCreator
{
public:
    static CCControlButtonCreator* create();
    virtual ~CCControlButtonCreator() {}
    virtual CCControlButton* createNode();
    virtual void endNode(CCNode* pNode);
    virtual void setAttribute(CCNode* pSprite, const char* strName, const char* strValue, bool bCache);
};

/**<class CCEditBoxCreator     */
class CCEditBoxCreator : public CCControlButtonCreator
{
public:
    static CCEditBoxCreator* create();
    virtual ~CCEditBoxCreator() {}
    virtual CCEditBox* createNode();
    virtual void endNode(CCNode* pNode);
    virtual void setAttribute(CCNode* pSprite, const char* strName, const char* strValue, bool bCache);
};

/**<class CCControlSliderCreator     */
class CCControlSliderCreator : public CCControlCreator
{
public:
    static CCControlSliderCreator* create();
    virtual ~CCControlSliderCreator() {}
    virtual CCControlSlider* createNode();
    virtual void endNode(CCNode* pNode);
    virtual void setAttribute(CCNode* pSprite, const char* strName, const char* strValue, bool bCache);
};

/**<class CCControlPotentiometerCreator     */
class CCControlPotentiometerCreator : public CCControlCreator
{
public:
    static CCControlPotentiometerCreator* create();
    virtual ~CCControlPotentiometerCreator() {}
    virtual CCControlPotentiometer* createNode();
    virtual void endNode(CCNode* pNode);
    virtual void setAttribute(CCNode* pSprite, const char* strName, const char* strValue, bool bCache);
};

/**<class CCControlStepperCreator     */
class CCControlStepperCreator : public CCControlCreator
{
public:
    static CCControlStepperCreator* create();
    virtual ~CCControlStepperCreator() {}
    virtual CCControlStepper* createNode();
    virtual void endNode(CCNode* pNode);
    virtual void setAttribute(CCNode* pSprite, const char* strName, const char* strValue, bool bCache);
};

/**<class CCControlSwitchCreator*/
class CCControlSwitchCreator : public CCControlCreator
{
public:
    static CCControlSwitchCreator* create();
    virtual ~CCControlSwitchCreator() {}
    virtual CCControlSwitch* createNode();
    virtual void endNode(CCNode* pNode);
    virtual void setAttribute(CCNode* pSprite, const char* strName, const char* strValue, bool bCache);
};

#endif // CC_CONTROLEXTENSIONCREATOR_H_
