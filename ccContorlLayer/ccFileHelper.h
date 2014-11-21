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
    //��ȡ�ļ�����·��
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
    //ͨ���ļ�����json�ļ���ת��ΪValue
    static bool loadCsJsonFormFile(const char* filePath, CSJson::Value& root);
    //�޸�value��ֵ����һ���ĸ�ʽ�������Լ�д
    static bool setCsJsonValue(CSJson::Value& root, const char* key, CSJson::Value& value);
    //����Jscon�ļ�����Ҫָ��·��
    static bool saveCsJson(const char* path,CSJson::Value &value);

};

#endif // _CC_FILEHELPER_H_
