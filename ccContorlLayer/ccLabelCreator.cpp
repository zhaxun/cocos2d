#include "ccLabelCreator.h"


/**<  class CCLabelTTFCreator */
CCLabelTTFCreator* CCLabelTTFCreator::create()
{
    CCLabelTTFCreator* pCreator = new CCLabelTTFCreator();
    if(pCreator) pCreator->autorelease();
    return pCreator;
}
CCLabelTTF* CCLabelTTFCreator::createNode()
{
    return CCLabelTTF::create();
}

void CCLabelTTFCreator::endNode(CCNode* pNode)
{
    CCNodeCreator::setAttribute(pNode);
}

void CCLabelTTFCreator::setAttribute(CCNode* label, const char* strName, const char* strValue, bool bCache)
{
    CCLabelTTF* pLabel = (CCLabelTTF*)label;
    if(bCache)
        mAttrMap[strName] = strValue;

    else
    {
        if(strcmp(strName, "text") == 0)
            pLabel->setString(strValue);

        else if(strcmp(strName, "font_size") == 0)
            pLabel->setFontSize(ccXmlAttrParse::toInt(strValue));

        else if(strcmp(strName, "font_name") == 0)
            pLabel->setFontName(strValue);

        else if(strcmp(strName, "font_color") == 0)
            pLabel->setColor(ccXmlAttrParse::toColor3B(strValue));

        else if(strcmp(strName, "dimension") == 0)
            pLabel->setDimensions(ccXmlAttrParse::toSize(strValue));

        else if(strcmp(strName, "align_h") == 0)
            pLabel->setHorizontalAlignment((CCTextAlignment)ccXmlAttrParse::toInt(strValue));

        else if(strcmp(strName, "align_v") == 0)
            pLabel->setVerticalAlignment((CCVerticalTextAlignment)ccXmlAttrParse::toInt(strValue));
        else if(strcmp(strName, "stroke_color") == 0)
            pLabel->enableStroke(ccXmlAttrParse::toColor3B(strValue),3,true);
        else
            CCSpriteCreator::setAttribute(pLabel, strName, strValue, bCache);
    }
}

REG_NODE_CREATOR("CCLabelTTF",CCLabelTTFCreator)


/**<  class CCLabelBMFontCreator */
CCLabelBMFontCreator* CCLabelBMFontCreator::create()
{
    CCLabelBMFontCreator* pCreator = new CCLabelBMFontCreator();
    if(pCreator)
        pCreator->autorelease();
    return pCreator;
}

CCLabelBMFontCreator::~CCLabelBMFontCreator()
{
}

CCLabelBMFont* CCLabelBMFontCreator::createNode()
{
    CCLabelBMFont* pNode = new CCLabelBMFont();
    if(pNode)
    {
        pNode->autorelease();
        return pNode;
    }
    CC_SAFE_DELETE(pNode);
    return NULL;
}

void CCLabelBMFontCreator::endNode(CCNode* pNode)
{
    CCLabelBMFont* pLabelBMFont = (CCLabelBMFont*)pNode;
    pLabelBMFont->initWithString(mAttrMap["text"].c_str(),
                            mAttrMap["file"].c_str(),
                             ccXmlAttrParse::toFloat(mAttrMap["width"].c_str()),
                             (CCTextAlignment)ccXmlAttrParse::toInt(mAttrMap["align"].c_str()),
                             ccXmlAttrParse::toPoint(mAttrMap["offset"].c_str()) );
    CCNodeCreator::setAttribute(pNode);
}

void CCLabelBMFontCreator::setAttribute(CCNode* label, const char* strName, const char* strValue, bool bCache)
{
    CCLabelBMFont* pLabel = (CCLabelBMFont*)label;
    if(bCache)
        mAttrMap[strName] = strValue;

    else
    {
        if(strcmp(strName, "text") == 0
           ||strcmp(strName, "file") == 0
           ||strcmp(strName, "width") == 0
           ||strcmp(strName, "align") == 0
           ||strcmp(strName,"offset") == 0)
            return;

        else if(strcmp(strName,"color") == 0)
            pLabel->setColor(ccXmlAttrParse::toColor3B(strValue));

        else
            CCSpriteBatchNodeCreator::setAttribute(pLabel, strName, strValue, bCache);
    }
}

REG_NODE_CREATOR("CCLabelBMFont",CCLabelBMFontCreator)


/**<  class CCLabelAtlasCreator */
CCLabelAtlasCreator* CCLabelAtlasCreator::create()
{
    CCLabelAtlasCreator* pCreator = new CCLabelAtlasCreator();
    if(pCreator)
        pCreator->autorelease();
    return pCreator;
}

CCLabelAtlasCreator::~CCLabelAtlasCreator()
{
}

CCLabelAtlas* CCLabelAtlasCreator::createNode()
{
    CCLabelAtlas* pNode = new CCLabelAtlas();
    if(pNode)
    {
        pNode->autorelease();
        return pNode;
    }
    CC_SAFE_DELETE(pNode);
    return NULL;
}

void CCLabelAtlasCreator::endNode(CCNode* pNode)
{
    CCLabelAtlas* pLabelAtlas = (CCLabelAtlas*)pNode;

    pLabelAtlas->initWithString(mAttrMap["text"].c_str(),
                                mAttrMap["file"].c_str(),
                                 ccXmlAttrParse::toULong(mAttrMap["item_w"].c_str()),
                                 ccXmlAttrParse::toULong(mAttrMap["item_h"].c_str()),
                                 mAttrMap["start_ch"].c_str()[0]);
    CCNodeCreator::setAttribute(pNode);
}

void CCLabelAtlasCreator::setAttribute(CCNode* node, const char* strName, const char* strValue, bool bCache)
{
    if(bCache)
        mAttrMap[strName] = strValue;
    else
    {
        CCLabelAtlas* pNode = (CCLabelAtlas*)node;
        if(strcmp(strName, "text") == 0
           ||strcmp(strName, "file") == 0
           ||strcmp(strName, "item_w") == 0
           ||strcmp(strName, "item_h") == 0
           ||strcmp(strName, "start_ch") == 0)
            return;

        else
            CCNodeRGBACreator::setAttribute(pNode, strName, strValue, bCache);
    }
}

REG_NODE_CREATOR("CCLabelAtlas",CCLabelAtlasCreator)
