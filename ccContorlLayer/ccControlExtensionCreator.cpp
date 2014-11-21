#include "ccControlExtensionCreator.h"

/**<class CCControlCreator     */
CCControlCreator* CCControlCreator::create()
{
    CCControlCreator* pCreator = new CCControlCreator();
    if(pCreator) pCreator->autorelease();
    return pCreator;
}

CCControl* CCControlCreator::createNode()
{
    CCControl *pRet = new CCControl();
    if(pRet)
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}
void CCControlCreator::addTargetWithActionForControlEvents(CCNode* pNode)
{
    CCControl *pControl = (CCControl*)pNode;
    CCControlEvent event = 0;
    int n = kControlEventTotalNumber;
    do{
        n--;
        event |= 1 << n;
    }while(n);
    pControl->addTargetWithActionForControlEvents(mRootDelegate,
                                                  cccontrol_selector(CCControlLayer::controlTouchCallback),/*CCNodeBuilder::share()->getControlHandler(),*/
                                                  event);
}
CCLabelTTF* CCControlCreator::createTTFLabel(std::string str)
{
    CC_STR_MAP nAttrMap = ccXmlAttrParse::parseAttr(str.c_str());

    //CCNode* pRet = CCLabelTTF::create("Touch Me!", "Arial", 30);
    CCLabelTTF* pRet = CCLabelTTF::create(nAttrMap["text"].c_str(), nAttrMap["font_name"].c_str(),
                                                ccXmlAttrParse::toInt(nAttrMap["font_size"].c_str()));
    pRet->setTag(ccXmlAttrParse::toInt(nAttrMap["tag"].c_str()));
    pRet->setColor(ccXmlAttrParse::toColor3B(nAttrMap["font_color"].c_str()));
    return pRet;
}

CCLabelBMFont* CCControlCreator::createBMFontLabel(std::string str)
{
    CC_STR_MAP nAttrMap = ccXmlAttrParse::parseAttr(str.c_str());
    CCLabelBMFont* pRet = CCLabelBMFont::create(nAttrMap["text"].c_str(),
                                          nAttrMap["file"].c_str(),
                                          ccXmlAttrParse::toFloat(nAttrMap["width"].c_str()),
                                          (CCTextAlignment)ccXmlAttrParse::toInt(nAttrMap["align"].c_str()),
                                          ccXmlAttrParse::toPoint(nAttrMap["offset"].c_str()) );
    pRet->setTag(ccXmlAttrParse::toInt(nAttrMap["tag"].c_str()));
    pRet->setColor(ccXmlAttrParse::toColor3B(nAttrMap["font_color"].c_str()));
    return pRet;
}

CCScale9Sprite* CCControlCreator::createSprite(std::string str)
{
    CC_STR_MAP nAttrMap = ccXmlAttrParse::parseAttr(str.c_str());
    CCScale9Sprite* pRet = CCScale9Sprite::create(nAttrMap["file"].c_str(),
                           ccXmlAttrParse::toRect(nAttrMap["rect"].c_str()),
                           ccXmlAttrParse::toRect(nAttrMap["inrect"].c_str()) );
    pRet->setTag(ccXmlAttrParse::toInt(nAttrMap["tag"].c_str()));
    return pRet;
}

void CCControlCreator::endNode(CCNode* pNode)
{
    addTargetWithActionForControlEvents(pNode);
    CCNodeCreator::setAttribute(pNode);
}

void CCControlCreator::setAttribute(CCNode* pNode, const char* strName, const char* strValue, bool bCache)
{
    if(bCache)
        mAttrMap[strName] = strValue;
    else
    {
        CCControl* pControl = (CCControl*)pNode;
        if(strcmp(strName, "enable") == 0)
            pControl->setEnabled(ccXmlAttrParse::toBool(strValue));
        else if(strcmp(strName, "selected") == 0)
            pControl->setSelected(ccXmlAttrParse::toBool(strValue));
        else if(strcmp(strName, "highlight") == 0)
            pControl->setHighlighted(ccXmlAttrParse::toBool(strValue));
        else if(strcmp(strName, "bOpacityModifyRGB") == 0)
            pControl->setOpacityModifyRGB(ccXmlAttrParse::toBool(strValue));


        CCLayerRGBACreator::setAttribute(pNode, strName, strValue, bCache);
    }
}

REG_NODE_CREATOR("CCControl",CCControlCreator)


/**<class CCControlButtonCreator     */
CCControlButtonCreator* CCControlButtonCreator::create()
{
    CCControlButtonCreator* pCreator = new CCControlButtonCreator();
    if(pCreator) pCreator->autorelease();
    return pCreator;
}

CCControlButton* CCControlButtonCreator::createNode()
{
    CCControlButton *pRet = new CCControlButton();
    if(pRet)
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

void CCControlButtonCreator::endNode(CCNode* pNode)
{
    CCControlButton *pControlButton = (CCControlButton *)pNode;
    CCNode *label[4] = {NULL};
    CCScale9Sprite *sprite[4] = {NULL};
    std::string key[3][4] ={
        {"bg_normal","bg_highlight","bg_disable","bg_select",},
        {"ttf_normal","ttf_highlight","ttf_disable","ttf_select",},
        {"bmf_normal","bmf_highlight","bmf_disable","bmf_select"}};

    for(int i=0; i<4; i++)
    {
        if(FIND_OBJ_BYKEY(mAttrMap, key[0][i]))
            sprite[i] = createSprite(mAttrMap[key[0][i]]);
        if(FIND_OBJ_BYKEY(mAttrMap, key[1][i]))
            label[i] = createTTFLabel(mAttrMap[key[1][i]]);
        if(FIND_OBJ_BYKEY(mAttrMap, key[2][i]))
            label[i] = createBMFontLabel(mAttrMap[key[2][i]]);
    }

    pControlButton->initWithLabelAndBackgroundSprite(label[0], sprite[0]);
    for(int n=1; n<4; n++)
    {
        if(label[n] != NULL)
            pControlButton->setTitleLabelForState(label[n], (CCControlState)(1 << n));
        if(sprite[n] != NULL)
            pControlButton->setBackgroundSpriteForState(sprite[n], (CCControlState)(1 << n));
    }

    addTargetWithActionForControlEvents(pNode);
    CCNodeCreator::setAttribute(pNode);
}

void CCControlButtonCreator::setAttribute(CCNode* pNode, const char* strName, const char* strValue, bool bCache)
{
    if(bCache)
        mAttrMap[strName] = strValue;

    else
    {
        CCControlButton* pControlButton = (CCControlButton*)pNode;
        if(strcmp(strName, "title") == 0
            ||strcmp(strName, "font_name") == 0
            ||strcmp(strName, "font_size") == 0
            ||strcmp(strName, "bg") == 0
            ||strcmp(strName, "bg_tag") == 0
            ||strcmp(strName, "bg_rect") == 0
            ||strcmp(strName, "bg_inrect") == 0)
            return;

        else if(strcmp(strName, "adjustbg") == 0)
            pControlButton->setAdjustBackgroundImage(ccXmlAttrParse::toBool(strValue));
        else if(strcmp(strName, "p_size") == 0)
            pControlButton->setPreferredSize(ccXmlAttrParse::toSize(strValue));

        CCControlCreator::setAttribute(pNode, strName, strValue, bCache);
    }
}

REG_NODE_CREATOR("CCControlButton",CCControlButtonCreator)


/**<class CCEditBoxCreator     */
CCEditBoxCreator* CCEditBoxCreator::create()
{
    CCEditBoxCreator* pCreator = new CCEditBoxCreator();
    if(pCreator) pCreator->autorelease();
    return pCreator;
}

CCEditBox* CCEditBoxCreator::createNode()
{
    CCEditBox* pNode = new CCEditBox();
    if(pNode)
    {
        pNode->setDelegate(dynamic_cast<CCEditBoxDelegate*>(mRootDelegate));
        pNode->autorelease();
        return pNode;
    }
    CC_SAFE_DELETE(pNode);
    return NULL;
}

void CCEditBoxCreator::endNode(CCNode* pNode)
{
    CCEditBox* pEditBox = (CCEditBox*)pNode;
    CCSize nSize = ccXmlAttrParse::toSize(mAttrMap["size"].c_str());
    CCScale9Sprite* pNormal9SpriteBg = NULL;
    CCScale9Sprite* pPressed9SpriteBg = NULL;
    CCScale9Sprite* pDisabled9SpriteBg = NULL;
    CC_STR_ITOR it = mAttrMap.find("spr9_normal");
    if(it != mAttrMap.end())
    {
        pNormal9SpriteBg = CCScale9Sprite::create(mAttrMap["spr9_normal"].c_str(),
                            ccXmlAttrParse::toRect(mAttrMap["spr9_rect"].c_str()),
                            ccXmlAttrParse::toRect(mAttrMap["spr9_inrect"].c_str()));
        pNormal9SpriteBg->setTag(ccXmlAttrParse::toInt(mAttrMap["tag_normal"].c_str()));
    }
    it = mAttrMap.find("spr9_press");
    if(it != mAttrMap.end())
    {
        pPressed9SpriteBg = CCScale9Sprite::create(mAttrMap["spr9_press"].c_str(),
                            ccXmlAttrParse::toRect(mAttrMap["spr9_rect"].c_str()),
                            ccXmlAttrParse::toRect(mAttrMap["spr9_inrect"].c_str()));
        pNormal9SpriteBg->setTag(ccXmlAttrParse::toInt(mAttrMap["tag_press"].c_str()));
    }
    it = mAttrMap.find("spr9_disable");
    if(it != mAttrMap.end())
    {
        pDisabled9SpriteBg = CCScale9Sprite::create(mAttrMap["spr9_disable"].c_str(),
                                                    ccXmlAttrParse::toRect(mAttrMap["spr9_rect"].c_str()),
                                                    ccXmlAttrParse::toRect(mAttrMap["spr9_inrect"].c_str()));
        pDisabled9SpriteBg->setTag(ccXmlAttrParse::toInt(mAttrMap["tag_disable"].c_str()));
    }
    if(pNormal9SpriteBg) pEditBox->initWithSizeAndBackgroundSprite(nSize, pNormal9SpriteBg);
    if(pPressed9SpriteBg) pEditBox->setBackgroundSpriteForState(pPressed9SpriteBg, CCControlStateHighlighted);
    if(pDisabled9SpriteBg) pEditBox->setBackgroundSpriteForState(pDisabled9SpriteBg, CCControlStateDisabled);

    addTargetWithActionForControlEvents(pNode);
    CCNodeCreator::setAttribute(pNode);
}

void CCEditBoxCreator::setAttribute(CCNode* pNode, const char* strName, const char* strValue, bool bCache)
{
    if(bCache)
        mAttrMap[strName] = strValue;

    else
    {
        CCEditBox* pEditBox = (CCEditBox*)pNode;
        if(strcmp(strName, "font_color") == 0)
            pEditBox->setFontColor(ccXmlAttrParse::toColor3B(strValue));
        else if(strcmp(strName, "font_name") == 0)
            pEditBox->setFontName(strValue);
        else if(strcmp(strName, "font_size") == 0)
            pEditBox->setFontSize(ccXmlAttrParse::toInt(strValue));
        else if(strcmp(strName, "text") == 0)
            pEditBox->setText(strValue);

        else if(strcmp(strName, "ph_text") == 0)
            pEditBox->setPlaceHolder(strValue);
        else if(strcmp(strName, "ph_font_color") == 0)
            pEditBox->setPlaceholderFontColor(ccXmlAttrParse::toColor3B(strValue));
        else if(strcmp(strName, "ph_font_name") == 0)
            pEditBox->setPlaceholderFontName(strValue);
        else if(strcmp(strName, "ph_font_size") == 0)
            pEditBox->setPlaceholderFontSize(ccXmlAttrParse::toInt(strValue));

        else if(strcmp(strName, "input_flag") == 0)
            pEditBox->setInputFlag((EditBoxInputFlag)ccXmlAttrParse::toInt(strValue));
        else if(strcmp(strName, "input_mode") == 0)
            pEditBox->setInputMode((EditBoxInputMode)ccXmlAttrParse::toInt(strValue));
        else if(strcmp(strName, "max_length") == 0)
            pEditBox->setMaxLength(ccXmlAttrParse::toInt(strValue));
        else if(strcmp(strName, "return_type") == 0)
            pEditBox->setReturnType((KeyboardReturnType)ccXmlAttrParse::toInt(strValue));

        else
            CCControlButtonCreator::setAttribute(pNode, strName, strValue, bCache);
    }
}

REG_NODE_CREATOR("CCEditBox",CCEditBoxCreator)



/**<class CCControlSliderCreator     */
CCControlSliderCreator* CCControlSliderCreator::create()
{
    CCControlSliderCreator* pCreator = new CCControlSliderCreator();
    if(pCreator) pCreator->autorelease();
    return pCreator;
}

CCControlSlider* CCControlSliderCreator::createNode()
{
    CCControlSlider* pNode = new CCControlSlider();
    if(pNode)
    {
        pNode->autorelease();
        return pNode;
    }
    CC_SAFE_DELETE(pNode);
    return NULL;
}

void CCControlSliderCreator::endNode(CCNode* pNode)
{
    CCControlSlider* pControlSlider = (CCControlSlider*)pNode;

    if(FIND_OBJ_BYKEY(mAttrMap, "spr_bg") && FIND_OBJ_BYKEY(mAttrMap, "spr_progress")
       &&FIND_OBJ_BYKEY(mAttrMap, "spr_thumb"))
        pControlSlider->initWithSprites(CCSprite::create(mAttrMap["spr_bg"].c_str()),
                                    CCSprite::create(mAttrMap["spr_progress"].c_str()),
                                    CCSprite::create(mAttrMap["spr_thumb"].c_str()));


    addTargetWithActionForControlEvents(pNode);
    CCNodeCreator::setAttribute(pNode);
}

void CCControlSliderCreator::setAttribute(CCNode* pNode, const char* strName, const char* strValue, bool bCache)
{
    if(bCache)
        mAttrMap[strName] = strValue;

    else
    {
        CCControlSlider* pControlSlider = (CCControlSlider*)pNode;
        if(strcmp(strName, "spr_bg") == 0
           ||strcmp(strName, "spr_progress") == 0
           ||strcmp(strName, "spr_thumb") == 0)
            return;

        else if(strcmp(strName, "max_value") == 0)
            pControlSlider->setMaximumValue(ccXmlAttrParse::toFloat(strValue));
        else if(strcmp(strName, "min_value") == 0)
            pControlSlider->setMinimumValue(ccXmlAttrParse::toFloat(strValue));
        else if(strcmp(strName, "value") == 0)
            pControlSlider->setValue(ccXmlAttrParse::toFloat(strValue));

        else
            CCControlCreator::setAttribute(pNode, strName, strValue, bCache);
    }
}

REG_NODE_CREATOR("CCControlSlider",CCControlSliderCreator)



/**<class CCControlPotentiometerCreator     */
CCControlPotentiometerCreator* CCControlPotentiometerCreator::create()
{
    CCControlPotentiometerCreator* pCreator = new CCControlPotentiometerCreator();
    if(pCreator) pCreator->autorelease();
    return pCreator;
}

CCControlPotentiometer* CCControlPotentiometerCreator::createNode()
{
    CCControlPotentiometer* pNode = new CCControlPotentiometer();
    if(pNode)
    {
        pNode->autorelease();
        return pNode;
    }
    CC_SAFE_DELETE(pNode);
    return NULL;
}

void CCControlPotentiometerCreator::endNode(CCNode* pNode)
{
    CCControlPotentiometer* pControlPotentiometer = (CCControlPotentiometer*)pNode;
      if(FIND_OBJ_BYKEY(mAttrMap, "spr_bg") && FIND_OBJ_BYKEY(mAttrMap, "spr_progress")
       &&FIND_OBJ_BYKEY(mAttrMap, "spr_thumb"))
       {
            CCSprite *backgroundSprite      = CCSprite::create(mAttrMap["spr_bg"].c_str());
            CCSprite *thumbSprite           = CCSprite::create(mAttrMap["spr_thumb"].c_str());
            CCProgressTimer *progressTimer  = CCProgressTimer::create(CCSprite::create(mAttrMap["spr_progress"].c_str()));
            pControlPotentiometer->initWithTrackSprite_ProgressTimer_ThumbSprite(backgroundSprite, progressTimer, thumbSprite);
       }

    addTargetWithActionForControlEvents(pNode);
    CCNodeCreator::setAttribute(pNode);
}

void CCControlPotentiometerCreator::setAttribute(CCNode* pNode, const char* strName, const char* strValue, bool bCache)
{
    if(bCache)
        mAttrMap[strName] = strValue;

    else
    {
        CCControlPotentiometer* pControlPotentiometer = (CCControlPotentiometer*)pNode;
        if(strcmp(strName, "spr_bg") == 0
           ||strcmp(strName, "spr_progress") == 0
           ||strcmp(strName, "spr_thumb") == 0)
            return;

        else if(strcmp(strName, "max_value") == 0)
            pControlPotentiometer->setMaximumValue(ccXmlAttrParse::toFloat(strValue));
        else if(strcmp(strName, "min_value") == 0)
            pControlPotentiometer->setMinimumValue(ccXmlAttrParse::toFloat(strValue));
        else if(strcmp(strName, "value") == 0)
            pControlPotentiometer->setValue(ccXmlAttrParse::toFloat(strValue));

        else
            CCControlCreator::setAttribute(pNode, strName, strValue, bCache);
    }
}

REG_NODE_CREATOR("CCControlPotentiometer",CCControlPotentiometerCreator)



/**<class CCControlStepperCreator     */
CCControlStepperCreator* CCControlStepperCreator::create()
{
    CCControlStepperCreator* pCreator = new CCControlStepperCreator();
    if(pCreator) pCreator->autorelease();
    return pCreator;
}

CCControlStepper* CCControlStepperCreator::createNode()
{
    CCControlStepper* pNode = new CCControlStepper();
    if(pNode)
    {
        pNode->autorelease();
        return pNode;
    }
    CC_SAFE_DELETE(pNode);
    return NULL;
}

void CCControlStepperCreator::endNode(CCNode* pNode)
{
    CCControlStepper* pControlStepper = (CCControlStepper*)pNode;
    if(FIND_OBJ_BYKEY(mAttrMap, "spr_minus") && FIND_OBJ_BYKEY(mAttrMap, "spr_plus"))
    {
        CCSprite *minusSprite       = CCSprite::create(mAttrMap["spr_minus"].c_str());
        CCSprite *plusSprite        = CCSprite::create(mAttrMap["spr_plus"].c_str());
        pControlStepper->initWithMinusSpriteAndPlusSprite(minusSprite, plusSprite);
    }

    addTargetWithActionForControlEvents(pNode);
    CCNodeCreator::setAttribute(pNode);
}

void CCControlStepperCreator::setAttribute(CCNode* pNode, const char* strName, const char* strValue, bool bCache)
{
    if(bCache)
        mAttrMap[strName] = strValue;

    else
    {
        CCControlStepper* pControlStepper = (CCControlStepper*)pNode;
        if(strcmp(strName, "spr_minus") == 0
           ||strcmp(strName, "spr_plus") == 0)
            return;

        else if(strcmp(strName, "max_value") == 0)
            pControlStepper->setMaximumValue(ccXmlAttrParse::toFloat(strValue));
        else if(strcmp(strName, "min_value") == 0)
            pControlStepper->setMinimumValue(ccXmlAttrParse::toFloat(strValue));
        else if(strcmp(strName, "value") == 0)
            pControlStepper->setValue(ccXmlAttrParse::toFloat(strValue));

        else if(strcmp(strName, "step") == 0)
            pControlStepper->setStepValue(ccXmlAttrParse::toFloat(strValue));

        else if(strcmp(strName, "repeat") == 0)
            if(strcmp(strValue, "0"))
                pControlStepper->stopAutorepeat();
            else
                pControlStepper->startAutorepeat();

        else
            CCControlCreator::setAttribute(pNode, strName, strValue, bCache);
    }
}

REG_NODE_CREATOR("CCControlStepper",CCControlStepperCreator)




/**<class CCControlSwitchCreator*/
CCControlSwitchCreator* CCControlSwitchCreator::create()
{
    CCControlSwitchCreator* pCreator = new CCControlSwitchCreator();
    if(pCreator) pCreator->autorelease();
    return pCreator;
}

CCControlSwitch* CCControlSwitchCreator::createNode()
{
    CCControlSwitch* pNode = new CCControlSwitch();
    if(pNode)
    {
        pNode->autorelease();
        return pNode;
    }
    CC_SAFE_DELETE(pNode);
    return NULL;
}

void CCControlSwitchCreator::endNode(CCNode* pNode)
{
    CCControlSwitch* pControlSwitch = (CCControlSwitch*)pNode;
      if(FIND_OBJ_BYKEY(mAttrMap, "spr_mask") && FIND_OBJ_BYKEY(mAttrMap, "spr_on")
         && FIND_OBJ_BYKEY(mAttrMap, "spr_off") && FIND_OBJ_BYKEY(mAttrMap, "spr_thumb"))
       {
            CCSprite *maskSprite       = CCSprite::create(mAttrMap["spr_mask"].c_str());
            CCSprite *onSprite        = CCSprite::create(mAttrMap["spr_on"].c_str());
            CCSprite *offSprite        = CCSprite::create(mAttrMap["spr_off"].c_str());
            CCSprite *thumbSprite        = CCSprite::create(mAttrMap["spr_thumb"].c_str());
            CCLabelTTF *onLabel     = NULL;
            CCLabelTTF *offLabel     = NULL;
            if(FIND_OBJ_BYKEY(mAttrMap, "ttf_on")) onLabel = createTTFLabel(mAttrMap["ttf_on"]);
            if(FIND_OBJ_BYKEY(mAttrMap, "ttf_off")) offLabel = createTTFLabel(mAttrMap["ttf_off"]);
            pControlSwitch->initWithMaskSprite(maskSprite,onSprite,offSprite,thumbSprite,onLabel,offLabel);
       }

    addTargetWithActionForControlEvents(pNode);
    CCNodeCreator::setAttribute(pNode);
}

void CCControlSwitchCreator::setAttribute(CCNode* pNode, const char* strName, const char* strValue, bool bCache)
{
    if(bCache)
        mAttrMap[strName] = strValue;

    else
    {
        CCControlSwitch* pControlSwitch = (CCControlSwitch*)pNode;
        if(strcmp(strName, "spr_mask") == 0
           ||strcmp(strName, "spr_on") == 0
           ||strcmp(strName, "spr_off") == 0
           ||strcmp(strName, "spr_thumb") == 0
           ||strcmp(strName, "ttf_on") == 0
           ||strcmp(strName, "ttf_off") == 0)
            return;

        else if(strcmp(strName, "is_on") == 0)
           pControlSwitch->setOn(ccXmlAttrParse::toBool(strValue));

        else
            CCControlCreator::setAttribute(pNode, strName, strValue, bCache);
    }
}

REG_NODE_CREATOR("CCControlSwitch",CCControlSwitchCreator)

