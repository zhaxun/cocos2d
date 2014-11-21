#ifndef CC_NODE_CREATOR_H
#define CC_NODE_CREATOR_H

#include <cocos2d.h>
#include <cocos-ext.h>
#include <map>
#include <spine/Json.h>
#include <string>

#include <tr1/unordered_map>
#include <CocoStudio/Json/lib_json/json_lib.h>

#define FIND_OBJ_BYKEY(MAP, KEY)  (MAP.find(KEY) != MAP.end())
#define CC_STR_MAP  std::tr1::unordered_map<std::string, std::string>
#define CC_STR_ITOR std::tr1::unordered_map<std::string, std::string>::iterator
#define REG_GARBO(instance)\
        static instance* mInstance;\
        class instance##Garbo\
        {\
        public:\
            ~instance##Garbo()\
            {\
                CC_SAFE_DELETE(instance::mInstance);\
            };\
        };\
        static instance##Garbo mGarbo;

#define REG_GARBO_DEFINE(instance)  \
    instance* instance::mInstance = NULL;\
    instance::instance##Garbo instance::mGarbo;\


USING_NS_CC;
USING_NS_CC_EXT;

class CCNodeBuilder;
class ccXmlAttrParse
{
public:
    static void debug(std::string str, std::string path);
    static bool toBool(const char* str);
    //"x,y"
    static CCPoint toPoint(const char* str);

    //"w,h"
    static CCSize toSize(const char* str);

    //"int"
    static int toInt(const char* str);
    static unsigned long toULong(const char* str);

    //"0.6"
    static float toFloat(const char* str);

    //"x,y,w,h"
    static CCRect toRect(const char* str);

    //"#RRGGBB"
    static ccColor3B toColor3B(const char* str);

    //"#RRGGBBAA"
    static ccColor4B toColor4B(const char* str);

    //"GL_ONE|GL_ZERO"
    static ccBlendFunc toBlendFunc(const char* str);

    //"FZLBJW.TTF"
    static char* parseFileType(const char* str);
/*
    //Json file
    static Json* loadJsonFromFile(std::string jsonFile);

    static void unloadJson(Json* json);

    //通过文件读入json文件，转换为Value
    static bool loadCsJsonFormFile(const char* filePath, CSJson::Value& root);
    //获取文件完整路径
    static const std::string getFullPath(const char *path);
    static const std::string getWritePath(const char *path);
    //修改value的值，有一定的格式，可以自己写
    static bool setCsJsonValue(CSJson::Value& root, const char* key, CSJson::Value& value);
    //保存Jscon文件，需要指定路径
    static bool saveCsJson(const char* path,CSJson::Value &value);


    static void setValueAt(int item, Json* json, Json* jsonValue);

    static void setValue(std::string key, Json* json, Json* jsonValue);
*/
    /******************************************************************
        @param xml:  the xml content need to transform
        @param jsonFile:  the json of params
        @return : the transfromed string
        eg:  xml = "file=[filename]"    attrMap = "filename=Icon.png"
             return: file="Icon.png"
    ******************************************************************/
    static std::string transXmlByParams(const char* xml, Json* jsonFile);

    static CC_STR_MAP parseAttr(const char* str);

    static char* skipWhite(char* p);

    static char* skipTo(char* p, char ch);

    static std::string readString(char** p, const char* brkstr);

    static std::string myWrap(std::string str,int length);
};

class CCNodeCreator : public CCObject
{
public:
    static  CCNodeCreator* create();
    virtual ~CCNodeCreator();
    virtual CCNode* createNode();
    virtual void endNode(CCNode* pNode);
    virtual void setParent(CCNode* parent, CCNode* pNode);
    virtual void setAttribute(CCNode* pNode, const char* strName, const char* strValue, bool bCache);
    virtual void setAttribute(CCNode* pNode);
    void setDelegate(CCNode* pNode);

protected:
    CCNode*     mRootDelegate;
    CC_STR_MAP  mAttrMap;
};

class CCNodeRGBACreator : public CCNodeCreator
{
public:
    static CCNodeRGBACreator* create();
    virtual ~CCNodeRGBACreator() {};
    virtual CCNodeRGBA* createNode();
    virtual void endNode(CCNode* pNode);
    virtual void setAttribute(CCNode* pNode, const char* strName, const char* strValue, bool bCache);
};

class CCAtlasNodeCreator : public CCNodeRGBACreator
{
public:
    static CCAtlasNodeCreator* create();
    virtual ~CCAtlasNodeCreator();
    virtual CCAtlasNode* createNode();
    virtual void endNode(CCNode* pNode);
    virtual void setAttribute(CCNode* pNode, const char* strName, const char* strValue, bool bCache);
};




#endif // CC_NODE_CREATOR_H
