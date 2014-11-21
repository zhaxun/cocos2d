#include "ccNodeCreator.h"
#include "ccNodeCreatorFactory.h"
#include "ccNodeBuilder.h"
#include "ccControlLayer.h"
#include <string>

void ccXmlAttrParse::debug(std::string str, std::string path)
{
    do
    {
        FILE *fp = fopen(path.c_str(), "wb");
        CC_BREAK_IF(!fp);

        fwrite(str.c_str(),str.length(),1,fp);
        fclose(fp);
    }
    while (0);
}

bool ccXmlAttrParse::toBool(const char* str)
{
    return strtol(str,NULL,10) <= 0 ? false : true;
}
CCPoint ccXmlAttrParse::toPoint(const char* str)
{
    char* end= NULL;
    float x = strtod(str, &end);
    float y = strtod(end+1, NULL);
    return ccp(x,y);
}

CCSize ccXmlAttrParse::toSize(const char* str)
{
    char* end= NULL;
    float x = strtod(str, &end);
    float y = strtod(end+1, NULL);
    return CCSizeMake(x,y);
}

int ccXmlAttrParse::toInt(const char* str)
{
    return strtol(str,NULL,10);
}

unsigned long ccXmlAttrParse::toULong(const char* str)
{
    return strtoul(str,NULL,10);
}

float ccXmlAttrParse::toFloat(const char* str)
{
    return strtod(str,NULL);
}

CCRect ccXmlAttrParse::toRect(const char* str)
{
    char* end= NULL;
    float x = strtod(str, &end);
    float y = strtod(end+1, &end);
    float w = strtod(end+1, &end);
    float h = strtod(end+1, NULL);
    return CCRectMake(x,y,w,h);
}

ccColor3B ccXmlAttrParse::toColor3B(const char* str)
{
    char tmp[4] = {0};
    unsigned char r ,g , b ;
    const char* p = str;

    if(*p++ == '#')
    {
        //r
        memcpy(tmp, p, 2);
        r = strtol(tmp, 0, 16);
        //g
        p+=2;
        memset(tmp, 0, sizeof(tmp));
        memcpy(tmp, p, 2);
        g = strtol(tmp, 0, 16);
        //b
        p+=2;
        memset(tmp, 0, sizeof(tmp));
        memcpy(tmp, p, 2);
        b = strtol(tmp, 0, 16);
    }

    return ccc3(r,g,b);
}

ccColor4B ccXmlAttrParse::toColor4B(const char* str)
{
    char tmp[4] = {0};
    unsigned char r,g,b,a;
    const char* p = str;

    if(*p++ == '#')
    {
        //r
        memcpy(tmp, p, 2);
        r = strtol(tmp, 0, 16);
        //g
        p+=2;
        memset(tmp, 0, sizeof(tmp));
        memcpy(tmp, p, 2);
        g = strtol(tmp, 0, 16);
        //b
        p+=2;
        memset(tmp, 0, sizeof(tmp));
        memcpy(tmp, p, 2);
        b = strtol(tmp, 0, 16);
        //a
        p+=2;
        memset(tmp, 0, sizeof(tmp));
        memcpy(tmp, p, 2);
        a = strtol(tmp, 0, 16);
    }

    return ccc4(r,g,b,a);
}

ccBlendFunc ccXmlAttrParse::toBlendFunc(const char* str)
{
    char* p = (char*)str;
    ccBlendFunc blendFunc = kCCBlendFuncDisable;
    std::string strSrc = ccXmlAttrParse::readString(&p, "|");
    std::string strDst = ++p;
    //GL_ZERO, GL_ONE, GL_DST_COLOR, GL_ONE_MINUS_DST_COLOR, GL_SRC_ALPHA_SATURATE,
    //GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_DST_ALPHA, GL_ONE_MINUS_DST_ALPHA
    if(strSrc.compare("GL_ZERO") == 0)   blendFunc.src = GL_ZERO;
    else if(strSrc.compare("GL_ONE") == 0)   blendFunc.src = GL_ONE;
    else if(strSrc.compare("GL_DST_COLOR") == 0)   blendFunc.src = GL_DST_COLOR;
    else if(strSrc.compare("GL_ONE_MINUS_DST_COLOR") == 0)   blendFunc.src = GL_ONE_MINUS_DST_COLOR;
    else if(strSrc.compare("GL_SRC_ALPHA_SATURATE") == 0)   blendFunc.src = GL_SRC_ALPHA_SATURATE;
    else if(strSrc.compare("GL_SRC_ALPHA") == 0)   blendFunc.src = GL_SRC_ALPHA;
    else if(strSrc.compare("GL_ONE_MINUS_SRC_ALPHA") == 0)   blendFunc.src = GL_ONE_MINUS_SRC_ALPHA;
    else if(strSrc.compare("GL_DST_ALPHA") == 0)   blendFunc.src = GL_DST_ALPHA;
    else if(strSrc.compare("GL_ONE_MINUS_DST_ALPHA") == 0)   blendFunc.src = GL_ONE_MINUS_DST_ALPHA;

    //{GL_ZERO, GL_ONE, GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR, GL_SRC_ALPHA,
    //GL_ONE_MINUS_SRC_ALPHA, GL_DST_ALPHA, GL_ONE_MINUS_DST_ALPHA};
    if(strDst.compare("GL_ZERO") == 0)   blendFunc.dst = GL_ZERO;
    else if(strDst.compare("GL_ONE") == 0)   blendFunc.dst = GL_ONE;
    else if(strDst.compare("GL_SRC_COLOR") == 0)   blendFunc.dst = GL_SRC_COLOR;
    else if(strDst.compare("GL_ONE_MINUS_SRC_COLOR") == 0)   blendFunc.dst = GL_ONE_MINUS_SRC_COLOR;
    else if(strDst.compare("GL_SRC_ALPHA") == 0)   blendFunc.dst = GL_SRC_ALPHA;
    else if(strDst.compare("GL_ONE_MINUS_SRC_ALPHA") == 0)   blendFunc.dst = GL_ONE_MINUS_SRC_ALPHA;
    else if(strDst.compare("GL_DST_ALPHA") == 0)   blendFunc.dst = GL_DST_ALPHA;
    else if(strDst.compare("GL_ONE_MINUS_DST_ALPHA") == 0)   blendFunc.dst = GL_ONE_MINUS_DST_ALPHA;

    return blendFunc;
}

char* ccXmlAttrParse::skipWhite(char* p)
{
    while(*p==' ' || *p=='\r' || *p=='\n' || *p=='\t')
        ++p;
    return p;
}

char* ccXmlAttrParse::skipTo(char* p, char ch)
{
    while(*p != ch) ++p;
    return p;
}

std::string ccXmlAttrParse::readString(char** p, const char* brkstr)
{
    char* pStart;
    char* pEnd = strpbrk(*p, brkstr);
    if(pEnd==NULL)
        return std::string();

    pStart = *p;
    *p = pEnd;
    return std::string(pStart, pEnd-pStart);
}


char* ccXmlAttrParse::parseFileType(const char* str)
{
    char* p = (char*)strpbrk(str, ".");
    return p;
}

CC_STR_MAP ccXmlAttrParse::parseAttr(const char* str)
{
    CC_STR_MAP nAttrMap;
    char* p = (char*)str;
    while(*p)
    {
        p = ccXmlAttrParse::skipWhite(p);
        //parseName
        std::string strName = ccXmlAttrParse::readString(&p, "=");
        ++p;
        std::string strValue = ccXmlAttrParse::readString(&p, "^");
        if(strValue.empty())
            strValue += p;
        ++p;
        nAttrMap[strName] = strValue;
    }

    return nAttrMap;
}
/*
void ccXmlAttrParse::setValueAt(int item, Json* json, Json* jsonValue)
{
    Json* pJson = Json_getItemAt(json, item);
    CC_SAFE_DELETE(pJson->child);
    pJson->child = jsonValue;
}

void ccXmlAttrParse::setValue(std::string key, Json* json, Json* jsonValue)
{
    Json* pJson = Json_getItem(json, key.c_str());
    CC_SAFE_DELETE(pJson->child);
    pJson->child = jsonValue;
}

Json* ccXmlAttrParse::loadJsonFromFile(std::string jsonFile)
{
    unsigned long size;
    Json* json = NULL;
    const char* file = NULL;
    if(CCFileUtils::sharedFileUtils()->isFileExist(getWritePath(jsonFile.c_str())))
        file = (char*)CCFileUtils::sharedFileUtils()->getFileData(
                                    getWritePath(jsonFile.c_str()).c_str(),
                                    "rb", &size);
    else
        file = (char*)CCFileUtils::sharedFileUtils()->getFileData(jsonFile.c_str(), "rb", &size);
    std::string str = std::string((char*)file, size);
    json = Json_create(str.c_str());
    delete[] file;
    return json;
}

bool ccXmlAttrParse::loadCsJsonFormFile(const char* filePath, CSJson::Value& root)
{
    CSJson::Reader reader;
    unsigned long ilength;
    char *pBuffer = NULL;
    if(CCFileUtils::sharedFileUtils()->isFileExist(getWritePath(filePath)))
        pBuffer = (char*)CCFileUtils::sharedFileUtils()->getFileData(
                                    getWritePath(filePath).c_str(),
                                    "rb", &ilength);
    else
        pBuffer = (char *)CCFileUtils::sharedFileUtils()->getFileData(filePath,"rt+",&ilength);
    bool bRet = reader.parse(pBuffer,root);
    return bRet;
}

const std::string ccXmlAttrParse::getFullPath(const char* path)
{
    return CCFileUtils::sharedFileUtils()->fullPathForFilename(path);
}

const std::string ccXmlAttrParse::getWritePath(const char* path)
{
    std::string str = path;
    str = str.substr(str.find("/"), str.length()-1);
    return CCFileUtils::sharedFileUtils()->getWritablePath() + str;
    //return CCFileUtils::sharedFileUtils()->fullPathForFilename(path);
}

bool ccXmlAttrParse::saveCsJson(const char* path, CSJson::Value& value)
{
    FILE *fp;
    CSJson::StyledWriter write;

    std::string strTmp = write.write(value);
    const char *charTmp = strTmp.c_str();

//    fp = fopen(getFullPath(path).c_str(),"w");
//    if(!fp)
//    {
        fp = fopen(getWritePath(path).c_str(), "w");
        if(!fp)
        {
            return false;
        }
//    }
    fputs(charTmp,fp);

    fclose(fp);

    return true;
}

bool ccXmlAttrParse::setCsJsonValue(CSJson::Value& root, const char* key, CSJson::Value& value)
{
    CSJson::Value nValue = root[key];
    if(nValue != CSJson::Value::jsonNull)
    {
        root[key] = value;
        return true;
    }
    return false;
}

void ccXmlAttrParse::unloadJson(Json* json)
{
    Json_dispose(json);
}
*/
std::string ccXmlAttrParse::transXmlByParams(const char* xml, Json* jsonFile)
{
    std::string transXml="";
    std::string temp;
    char* p = (char*)xml;
    while(*p)
    {
        temp = ccXmlAttrParse::readString(&p, "[");
        if(temp.empty())
        {
            transXml += p;
            break;
        }
        else
            transXml += temp;
        ++p;
        std::string strName = ccXmlAttrParse::readString(&p, "]");
        ++p;
        if(!strName.empty())
        {
            transXml += "\"";
            std::string s = Json_getString(jsonFile, strName.c_str(),"");
            transXml += s;
            transXml += "\"";
        }
    }
    return transXml;
}

///////////////////////////////////////////////////////////////////
CCNodeCreator* CCNodeCreator::create()
{
    CCNodeCreator* pCreator = new CCNodeCreator();
    if(pCreator)
    {
        pCreator->autorelease();
    }
    return pCreator;
}

CCNodeCreator::~CCNodeCreator()
{
}

CCNode* CCNodeCreator::createNode()
{
    CCNode* pNode = CCNode::create();
    return pNode;
}

void CCNodeCreator::endNode(CCNode* pNode)
{
    setAttribute(pNode);
}

void CCNodeCreator::setParent(CCNode* parent, CCNode* pNode)
{
    parent->addChild(pNode);
}

void CCNodeCreator::setAttribute(CCNode* pNode, const char* strName, const char* strValue, bool bCache)
{
    if(bCache)
        mAttrMap[strName] = strValue;

    else
    {
        if(strcmp(strName, "tag") == 0)
            pNode->setTag(ccXmlAttrParse::toInt(strValue));

        else if(strcmp(strName, "visible") == 0)
            pNode->setVisible(ccXmlAttrParse::toBool(strValue));

        else if(strcmp(strName, "zorder") == 0)
            pNode->setZOrder(ccXmlAttrParse::toInt(strValue));

        else if(strcmp(strName, "size") == 0)
            pNode->setContentSize(ccXmlAttrParse::toSize(strValue));

        else if(strcmp(strName, "skewx") == 0)
            pNode->setSkewX(ccXmlAttrParse::toFloat(strValue));

        else if(strcmp(strName, "skewy") == 0)
            pNode->setSkewY(ccXmlAttrParse::toFloat(strValue));

        else if(strcmp(strName, "pos") == 0)
            pNode->setPosition(ccXmlAttrParse::toPoint(strValue));

        else if(strcmp(strName, "anchor") == 0)
            pNode->setAnchorPoint(ccXmlAttrParse::toPoint(strValue));

        else if(strcmp(strName, "rotate") == 0)
            pNode->setRotation(ccXmlAttrParse::toFloat(strValue));

        else if(strcmp(strName, "scale") == 0)
            pNode->setScale(ccXmlAttrParse::toFloat(strValue));

        else if(strcmp(strName, "scalex") == 0)
            pNode->setScaleX(ccXmlAttrParse::toFloat(strValue));

        else if(strcmp(strName, "scaley") == 0)
            pNode->setScaleY(ccXmlAttrParse::toFloat(strValue));

        else if(strcmp(strName, "datasource") == 0)
            ((CCControlLayer*)mRootDelegate)->setDataSourceTemplate(
                ccXmlAttrParse::toInt(mAttrMap["tag"].c_str()), strValue);

    }
}

void CCNodeCreator::setAttribute(CCNode* pNode)
{
    CC_STR_ITOR it = mAttrMap.begin();
    while(it != mAttrMap.end())
    {
        setAttribute(pNode, it->first.c_str(), it->second.c_str(), false);
        it++;
    }
}

void CCNodeCreator::setDelegate(CCNode* pNode)
{
    mRootDelegate = pNode;
}

CCNodeRGBACreator* CCNodeRGBACreator::create()
{
    CCNodeRGBACreator* pCreator = new CCNodeRGBACreator();
    if(pCreator) pCreator->autorelease();
    return pCreator;
}
CCNodeRGBA* CCNodeRGBACreator::createNode()
{
    return CCNodeRGBA::create();
}

void CCNodeRGBACreator::endNode(CCNode* pNode)
{
    CCNodeCreator::setAttribute(pNode);
}

void CCNodeRGBACreator::setAttribute(CCNode* node, const char* strName, const char* strValue, bool bCache)
{
    CCNodeRGBA* pNode = (CCNodeRGBA*)node;

    if(bCache)
        mAttrMap[strName] = strValue;

    else
    {
        if(strcmp(strName, "opacity") == 0)
            pNode->setOpacity(ccXmlAttrParse::toInt(strValue));

        else if(strcmp(strName, "color") == 0)
            pNode->setColor(ccXmlAttrParse::toColor3B(strValue));

        else if(strcmp(strName, "cascade_color") == 0)
            pNode->setCascadeColorEnabled(ccXmlAttrParse::toBool(strValue));

        else if(strcmp(strName, "cascade_opacity") == 0)
            pNode->setCascadeOpacityEnabled(ccXmlAttrParse::toBool(strValue));

        else
            CCNodeCreator::setAttribute(pNode, strName, strValue, bCache);
    }
}


CCAtlasNodeCreator* CCAtlasNodeCreator::create()
{
    CCAtlasNodeCreator* pCreator = new CCAtlasNodeCreator();
    if(pCreator) pCreator->autorelease();
    return pCreator;
}

CCAtlasNodeCreator::~CCAtlasNodeCreator()
{
}

CCAtlasNode* CCAtlasNodeCreator::createNode()
{
    CCAtlasNode * pNode = new CCAtlasNode();
    if(pNode)
    {
        pNode->autorelease();
    }
    return pNode;
}

void CCAtlasNodeCreator::endNode(CCNode* pNode)
{

    CCAtlasNode* pAtlasNode = (CCAtlasNode*)pNode;
    pAtlasNode->initWithTileFile(mAttrMap["file"].c_str(),
                                 ccXmlAttrParse::toInt(mAttrMap["item_w"].c_str()),
                                 ccXmlAttrParse::toInt(mAttrMap["item_h"].c_str()),
                                 ccXmlAttrParse::toInt(mAttrMap["items"].c_str()) );
    CCNodeCreator::setAttribute(pNode);
}

void CCAtlasNodeCreator::setAttribute(CCNode* node, const char* strName, const char* strValue, bool bCache)
{
    CCAtlasNode* pNode = (CCAtlasNode*)node;

    if(bCache)
        mAttrMap[strName] = strValue;

    else
    {
        if(strcmp(strName, "file") == 0
                ||strcmp(strName, "item_w") == 0
                ||strcmp(strName, "item_h") == 0
                ||strcmp(strName, "items") == 0)
            return;

        else
            CCNodeRGBACreator::setAttribute(pNode, strName, strValue, bCache);
    }
}

REG_NODE_CREATOR("CCAtlasNodeRGBA",CCAtlasNodeCreator)
REG_NODE_CREATOR("CCNodeRGBA",CCNodeRGBACreator)
REG_NODE_CREATOR("CCNode",CCNodeCreator)

