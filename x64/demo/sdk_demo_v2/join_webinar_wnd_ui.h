#pragma once

#include "meeting_service_components/meeting_configuration_interface.h"

class CJoinWebinarWndUI : public CWindowWnd, 
	                     public INotifyUI, 
	                     public IDialogBuilderCallback,
						 public IMessageFilterUI
{
public:
	CJoinWebinarWndUI();
	virtual ~CJoinWebinarWndUI();

	void SetRegisterHandler(ZOOM_SDK_NAMESPACE::IWebinarNeedRegisterHandler* handler);

	UILIB_RESOURCETYPE GetResourceType();
	LPCTSTR GetResourceID() const;
protected:
	virtual CDuiString GetSkinFolder() { return _T(""); }
	virtual CDuiString GetSkinFile();
	virtual LPCTSTR  GetWindowClassName() const { return  _T("CJoinWebnarWnd"); }
	virtual void Notify(TNotifyUI& msg);
	virtual LRESULT  HandleMessage(UINT uMsg, WPARAM wParam, LPARAM IParam);
	virtual LRESULT  MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	virtual void InitWindow();
	virtual CControlUI* CreateControl(LPCTSTR pstrClass) { return nullptr; }
private:
	LRESULT OnCreate();
	void DoJoinBtnClick();
	void DoCancelBtnClick();
	void DoCloseBtnClick();
private:

	CPaintManagerUI m_PaintManager;

	ZOOM_SDK_NAMESPACE::IWebinarNeedRegisterHandler* register_handler_;

	CRichEditUI* m_pEditEmail;
	CRichEditUI* m_pEditName;
};