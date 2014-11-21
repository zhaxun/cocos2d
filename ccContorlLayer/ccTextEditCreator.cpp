#include "ccTextEditCreator.h"

/**<class CCTextFieldTTFCreator     */
CCTextFieldTTFCreator* CCTextFieldTTFCreator::create()
{
    CCTextFieldTTFCreator* pCreator = new CCTextFieldTTFCreator();
    if(pCreator) pCreator->autorelease();
    return pCreator;
}

CCTextFieldTTF* CCTextFieldTTFCreator::createNode()
{
    CCTextFieldTTF *pRet = new CCTextFieldTTF();
    if(pRet)
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

void CCTextFieldTTFCreator::endNode(CCNode* pNode)
{
    CCTextFieldTTF* pTextFieldTTF = (CCTextFieldTTF*)pNode;
    std::string placeholder,fontName;
    CCSize dimensions;
    CCTextAlignment alignment;
    float fontSize;
    CC_STR_ITOR it = mAttrMap.find("placeholder");
    if(it != mAttrMap.end())    placeholder = mAttrMap["placeholder"];
    it = mAttrMap.find("size");
    if(it != mAttrMap.end())    dimensions = ccXmlAttrParse::toSize(mAttrMap["size"].c_str());
    it = mAttrMap.find("align");
    if(it != mAttrMap.end())    alignment = (CCTextAlignment)ccXmlAttrParse::toInt(mAttrMap["align"].c_str());
    it = mAttrMap.find("font_name");
    if(it != mAttrMap.end())    fontName = mAttrMap["font_name"];
    it = mAttrMap.find("font_size");
    if(it != mAttrMap.end())    fontSize = ccXmlAttrParse::toInt(mAttrMap["font_size"].c_str());

    pTextFieldTTF->initWithPlaceHolder(placeholder.c_str(),
                                    dimensions,
									alignment,
									fontName.c_str(),
									fontSize);

    CCNodeCreator::setAttribute(pNode);
}

void CCTextFieldTTFCreator::setAttribute(CCNode* pNode, const char* strName, const char* strValue, bool bCache)
{
    if(bCache)
        mAttrMap[strName] = strValue;

    else
    {
        CCTextFieldTTF* pTextFieldTTF = (CCTextFieldTTF*)pNode;
        if(strcmp(strName, "placeholder") == 0
           ||strcmp(strName, "align") == 0
           ||strcmp(strName, "font_name") == 0
           ||strcmp(strName, "font_size")==0
           ||strcmp(strName, "size")==0)
            return;

        else
            CCLabelTTFCreator::setAttribute(pNode, strName, strValue, bCache);
    }
}

REG_NODE_CREATOR("CCTextFieldTTF",CCTextFieldTTFCreator)



