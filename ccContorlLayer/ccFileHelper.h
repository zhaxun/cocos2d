#ifndef _CC_FILEHELPER_H_
#define _CC_FILEHELPER_H_

#include <cocos2d.h>
#include <cocos-ext.h>
#include <spine/Json.h>
#include <CocoStudio/Json/lib_json/json_lib.h>

USING_NS_CC;
USING_NS_CC_EXT;

#define SaveStringToXML CCUserDefault::sharedUserDefault()->setStringForKey
#define SaveIntegerToXML CCUserDefault::sharedUserDefault()->setIntegerForKey
#define SaveBooleanToXML CCUserDefault::sharedUserDefault()->setBoolForKey
#define LoadStringFromXML CCUserDefault::sharedUserDefault()->getStringForKey
#define LoadIntegerFromXML CCUserDefault::sharedUserDefault()->getIntegerForKey
#define LoadBooleanFromXML CCUserDefault::sharedUserDefault()->getBoolForKey

class CCFileHelper
{
public:
    //获取文件完整路径
    static const std::string getFullPath(const char *path);
    static const std::string getWritePath(const char *path);
    static void encode(char* buff);

};

class CCJsonHelper : public CCFileHelper
{
public:
    /********************************************************/
    /***********************For Json ************************/
    //load json from file
    static Json* loadJsonFromFile(std::string jsonFile);
    //release json object from memory
    static void unloadJson(Json* json);
    static void setValueAt(int item, Json* json, Json* jsonValue);
    static void setValue(std::string key, Json* json, Json* jsonValue);


    /********************************************************/
    /***********************For CSJson **********************/
    //通过文件读入json文件，转换为Value
    static bool loadCsJsonFormFile(const char* filePath, CSJson::Value& root);
    //修改value的值，有一定的格式，可以自己写
    static bool setCsJsonValue(CSJson::Value& root, const char* key, CSJson::Value& value);
    //保存Jscon文件，需要指定路径
    static bool saveCsJson(const char* path,CSJson::Value &value);

};

#endif // _CC_FILEHELPER_H_
