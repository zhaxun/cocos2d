#include "ccFileHelper.h"


const std::string CCFileHelper::getFullPath(const char* path)
{
    return CCFileUtils::sharedFileUtils()->fullPathForFilename(path);
}

const std::string CCFileHelper::getWritePath(const char* path)
{
    std::string str = path;
    str = str.substr(str.find("/"), str.length()-1);
    return CCFileUtils::sharedFileUtils()->getWritablePath() + str;
}

Json* CCJsonHelper::loadJsonFromFile(std::string jsonFile)
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

void CCJsonHelper::unloadJson(Json* json)
{
    Json_dispose(json);
}

bool CCJsonHelper::loadCsJsonFormFile(const char* filePath, CSJson::Value& root)
{
    CSJson::Reader reader;
    unsigned long ilength;
    char *pBuffer = NULL;
    if(CCFileUtils::sharedFileUtils()->isFileExist(getWritePath(filePath)))
        pBuffer = (char*)CCFileUtils::sharedFileUtils()->getFileData(
                                    getWritePath(filePath).c_str(),
                                    "rb", &ilength);
    else
        pBuffer = (char *)CCFileUtils::sharedFileUtils()->getFileData(filePath,"rb",&ilength);
    bool bRet = reader.parse(pBuffer,root);
    delete[] pBuffer;
    return bRet;
}

void CCJsonHelper::setValueAt(int item, Json* json, Json* jsonValue)
{
    Json* pJson = Json_getItemAt(json, item);
    CC_SAFE_DELETE(pJson->child);
    pJson->child = jsonValue;
}

void CCJsonHelper::setValue(std::string key, Json* json, Json* jsonValue)
{
    Json* pJson = Json_getItem(json, key.c_str());
    CC_SAFE_DELETE(pJson->child);
    pJson->child = jsonValue;
}



bool CCJsonHelper::saveCsJson(const char* path, CSJson::Value& value)
{
    FILE *fp;
    CSJson::StyledWriter write;

    std::string strTmp = write.write(value);
    fp = fopen(getWritePath(path).c_str(), "wb");
    if(!fp)
    {
        return false;
    }
/*
    for(int i=0; i<strTmp.length(); i++)
        strTmp[i]^=170;
*/
    CCFileUtils::sharedFileUtils()->encode((unsigned char*)strTmp.c_str(), strTmp.length());

    fwrite(strTmp.c_str(),1,strTmp.length(),fp);

    fclose(fp);

    return true;
}

bool CCJsonHelper::setCsJsonValue(CSJson::Value& root, const char* key, CSJson::Value& value)
{
    CSJson::Value nValue = root[key];
    if(nValue != CSJson::Value::jsonNull)
    {
        root[key] = value;
        return true;
    }
    return false;
}
