#ifndef _CC_XML_H_
#define _CC_XML_H_

#include <cocos2d.h>
USING_NS_CC;
class CCXmlHandler
{
public:
	virtual ~CCXmlHandler();
	virtual void startDocument() = 0;
	virtual void endDocument() = 0;
	virtual void startElement(const std::string& strName) = 0;
	virtual void endElement(const std::string& strName) = 0;
	virtual void attribute(const std::string& strName, const std::string& strValue) = 0;
	virtual void characters(const std::string& strValue) = 0;
};

class CCXmlParser : public CCObject
{
public:
    CCXmlParser(CCXmlHandler* pHandler);
    virtual ~CCXmlParser();

	void parse(const char* strxml, int len=0);
	char* skipWhite(char* p);
	char* skipTo(char* p, char ch);
	std::string readString(char** p, const char* brkstr);
	std::string readCharacters(char** p);
protected:
	CCXmlHandler* m_pHandler;
};

#endif // _CC_XML_H_
