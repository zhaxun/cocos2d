#ifndef _CCANIMATE_SPX_H_
#define _CCANIMATE_SPX_H_
#include "cocos2d.h"

USING_NS_CC;

class CCAnimateSpx :
	public CCNode
{
public:
	CCAnimateSpx(void);
	~CCAnimateSpx(void);
	static CCAnimateSpx* create();
	static CCAnimateSpx* create(const char* jsonFile);
	static CCAnimateSpx* create(CCSpriteBatchNode** node, const char* jsonFile);
	virtual bool init(){};
	virtual bool init(const char* jsonFile);
	virtual bool init(CCSpriteBatchNode** node, const char* jsonFile);
    virtual void switchAnimate(const char* animateName);

    virtual const CCPoint& getPosition();

    virtual void setSkewX(float f);
    virtual void setSkew(float f);
    virtual void setPosition(const CCPoint& point);
    virtual void setAnchorPoint(const CCPoint& point);
    virtual void setRotation(float f);
    virtual void setScaleX(float f);
    virtual void setScaleY(float f);
    virtual void setFlipX(bool b);
    virtual void setFlipY(bool b);
    virtual void setActPos(const char* aimateName,const CCPoint& point);
public:
    void addAnimate(const char* animateName, CCAnimation* pAnimation);
    void removeAnimate();
    CCAnimation* getAnimationByName(const char* aimateName);
	CCSprite* getAnimateSprite();
	CCRect getBoundingBox();

protected:
	CCSprite*   mSprite;
    std::map<std::string, CCAnimation*> mAnimateMap;
};

#endif // _CCANIMATE_SPX_H_
