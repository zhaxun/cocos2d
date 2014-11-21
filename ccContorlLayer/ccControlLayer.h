#ifndef _CCCONTORL_LAYER_H_
#define _CCCONTORL_LAYER_H_

#include "cocos2d.h"
#include "cocos-ext.h"
#include <spine/Json.h>

USING_NS_CC_EXT;
USING_NS_CC;

class CCControlLayer :  public CCLayer,
                    public CCEditBoxDelegate,
                    public CCTextFieldDelegate,
                    public CCIMEDelegate,
                    public CCTableViewDelegate,
                    public CCTableViewDataSource
{
public:
    CCControlLayer(const char* xmlfile);
    virtual ~CCControlLayer();
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    virtual void onEnterTransitionDidFinish();

    void releaseCaches();
    void menuItemCallback(CCObject* pSender);
    void controlTouchCallback(CCObject* pSender, CCControlEvent event);
    void setDataSourceTemplate(int tableViewTag, std::string strTemplate);


    /**  CCMenuItem点击事件回调   **/
    virtual void onMenuItemClick(CCMenuItem* pSender){}
    /**  CCControl触摸事件回调   **/
    virtual void onControlTouchEvent(CCObject* pSender, CCControlEvent event);

    /**  CCEditBoxDelegate事件委托        **/
    virtual void editBoxEditingDidBegin(cocos2d::extension::CCEditBox* editBox){};
    virtual void editBoxEditingDidEnd(cocos2d::extension::CCEditBox* editBox){};
    virtual void editBoxTextChanged(cocos2d::extension::CCEditBox* editBox, const std::string& text){};
    virtual void editBoxReturn(cocos2d::extension::CCEditBox* editBox){};

    /**  CCTextFieldDelegate事件委托  **/
    virtual bool onTextFieldAttachWithIME(CCTextFieldTTF * pSender){return true;}
    virtual bool onTextFieldDetachWithIME(CCTextFieldTTF * pSender){return true;}
    virtual bool onTextFieldInsertText(CCTextFieldTTF * pSender, const char * text, int nLen){return true;}
    virtual bool onTextFieldDeleteBackward(CCTextFieldTTF * pSender, const char * delText, int nLen){return true;}
    virtual bool onDraw(CCTextFieldTTF * pSender){return true;}

    /**  CCIMEDelegate事件委托        **/
    virtual void keyboardWillShow(CCIMEKeyboardNotificationInfo& info)   {CC_UNUSED_PARAM(info);}
    virtual void keyboardDidShow(CCIMEKeyboardNotificationInfo& info)    {CC_UNUSED_PARAM(info);}
    virtual void keyboardWillHide(CCIMEKeyboardNotificationInfo& info)   {CC_UNUSED_PARAM(info);}
    virtual void keyboardDidHide(CCIMEKeyboardNotificationInfo& info)    {CC_UNUSED_PARAM(info);}

    /** CCTableView事件委托**/
    virtual void scrollViewDidScroll(CCScrollView* view) {};
    virtual void scrollViewDidZoom(CCScrollView* view) {};
    //CCTableViewDelegate
    virtual void tableCellTouched(CCTableView* table, CCTableViewCell* cell){};
    virtual void tableCellHighlight(CCTableView* table, CCTableViewCell* cell){};
    virtual void tableCellUnhighlight(CCTableView* table, CCTableViewCell* cell){};
    virtual void tableCellWillRecycle(CCTableView* table, CCTableViewCell* cell){};

    /**CCTableViewDataSource*/
    //need to override the virtual function of base class
    virtual CCSize tableCellSizeForIndex(CCTableView *table, unsigned int idx);
    virtual CCSize cellSizeForTable(CCTableView *table);
    virtual CCTableViewCell* tableCellAtIndex(CCTableView *table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(CCTableView *table);
    virtual void tableCellContentAtIndex(CCTableView *table, unsigned int idx, CCTableViewCell* cell, Json* json){};
    /**CCTableViewDataSource*/

    void setCallFun(CCCallFunc* pFunc);

protected:
    CCCallFunc* mCallFunc;
    std::string mXmlFile;
    std::map<int, std::string> mDSTemplateMap;
    std::map<int, Json*> mJsonMap;
    bool mMenuClicked;
};
#endif //_CCCONTORL_LAYER_H_
