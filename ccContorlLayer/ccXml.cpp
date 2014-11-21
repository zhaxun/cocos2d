#include "ccXml.h"

CCXmlHandler::~CCXmlHandler()
{
}

CCXmlParser::CCXmlParser(CCXmlHandler* pHandler)
{
	m_pHandler = pHandler;
}

CCXmlParser::~CCXmlParser()
{
}

char* CCXmlParser::skipWhite(char* p)
{
	while(*p==' ' || *p=='\r' || *p=='\n' || *p=='\t')
		++p;
	return p;
}

char* CCXmlParser::skipTo(char* p, char ch)
{
	while(*p != ch) ++p;
	return p;
}

std::string CCXmlParser::readString(char** p, const char* brkstr)
{
	char* pStart;
	char* pEnd = strpbrk(*p, brkstr);
	if(pEnd==NULL)
		return std::string();

	pStart = *p;
	*p = pEnd;
	return std::string(pStart, pEnd-pStart);
}

std::string CCXmlParser::readCharacters(char** p)
{
	char* pStart = *p;
	char* pEnd = 0;
	pEnd = strpbrk(*p, "<");
	if(pEnd && memcmp(pEnd, (void*)"<![CDATA[", 9) == 0)
	{
		*p = pEnd + 9;
		pEnd = strpbrk(*p, "<");
	}

	if(pEnd==NULL)
		return std::string();
	*p = pEnd;
	return std::string(pStart, pEnd-pStart);
}

void CCXmlParser::parse(const char* strxml, int len)
{
	if(strxml == NULL)
		return;

	if(len == 0) len = strlen(strxml);

	//skip utf8 file head
	char* p = (char*)strxml;
	char* begin = p;
	if(memcmp((void*)p, (void*)"\xEF\xBB\xBF", 3) == 0)
	    p += 3;


	/* start document */
	m_pHandler->startDocument();

	/* parse node */
	while(*p && (p - begin) < len)
	{
		p = skipWhite(p);
		if(*p == '<')
		{
			//<
			++p;
			if(p[0] == '?' || p[0] == '!')
			{
				p = skipTo(p, '>');
				//>
				++p;
				continue;
			}
			else if(p[0] == '/')
			{
				++p;
				std::string name = readString(&p, ">");
				m_pHandler->endElement(name);
				//>
				++p;
			}
			else
			{
				std::string name = readString(&p, "\t />");
				m_pHandler->startElement(name);
				p = skipWhite(p);
				if(*p != '>' && *p != '/')
				{
					//´æÔÚÊôÐÔ
					while(*p != '>' && *p != '/')
					{
						p = skipWhite(p);
						std::string attrName = readString(&p, " =");
						p = skipTo(p, '=');
						char* pTemp = strpbrk(p, "\"'");
						if (pTemp)
							p = pTemp;
						else
						{
							m_pHandler->endDocument();
							return;
						}
						++p;
						std::string attrValue = readString(&p, "\"'");
						++p;
						if(attrName.length()>0 && attrValue.length()>0)
							m_pHandler->attribute(attrName, attrValue/*attrValue.entityDecode()*/);
						p = skipWhite(p);
					}
				}
				if(*p == '/')
				{
					++p;
					m_pHandler->endElement(name);
				}
				//>
				++p;
			}
		}
		else
		{
			p = skipWhite(p);
			if (*p)
			{
				std::string strText = readCharacters(&p);
				if (strText.length() > 0)
					m_pHandler->characters(/*strText.textDecode()*/strText);
                else
                    break;
			}
		}
	}
	/* end document */
	m_pHandler->endDocument();
}
