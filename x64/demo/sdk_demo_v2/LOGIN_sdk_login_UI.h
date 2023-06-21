#pragma once
#include "sdk_util.h"
#include "UIlib.h"
#include "resource.h"
#include "LOGIN_login_with_sso_workflow.h"
#include "LOGIN_join_meeting_only_workflow.h"
#include "LOGIN_restapi_without_login_workflow.h"
#include "sdk_demo_app_common.h"
/////////////////////////
enum loginTabPage
{
	login_RestAPI_Page,
	login_UseSSO_Page,
	login_JoinMeetingOnly_Page
};

class CSDKLoginUIMgr;
class CSDKLoginWithSSOUIGroup
{
public:
	CSDKLoginWithSSOUIGroup();
	virtual ~CSDKLoginWithSSOUIGroup();
	void InitWindow(CPaintManagerUI& ui_mgr, CSDKLoginUIMgr* main_frame_);
	void UninitWindow();
	void Show();
	void Hide();
	void Notify( TNotifyUI& msg );

	void DoLoginWithSSOBtnClick();

protected:
	CVerticalLayoutUI* m_loginWithSSOPage;
	CRichEditUI*	   m_editSSOtoken;
	CSDKLoginUIMgr*	   m_parentFrame;
	CSDKLoginWithSSOFlow   m_loginSSOWorkFlow;
	CButtonUI*		   m_btnLogin;
	CButtonUI* m_btnGetSSOLoginUrl;
	CRichEditUI* m_editPrefixOfVanityUrl;
};

class CSDKLoginCBHandler : public ZOOM_SDK_NAMESPACE::IAuthServiceEvent
{
public:
	CSDKLoginCBHandler();
	virtual ~CSDKLoginCBHandler();
	void SetUIEvent(CSDKLoginUIMgr* main_frame_);
	virtual void onAuthenticationReturn(ZOOM_SDK_NAMESPACE::AuthResult ret) {};
	virtual void onLoginReturnWithReason(ZOOM_SDK_NAMESPACE::LOGINSTATUS ret, ZOOM_SDK_NAMESPACE::IAccountInfo* pAccountInfo, ZOOM_SDK_NAMESPACE::LoginFailReason reason);
	virtual void onLogout();
	virtual void onZoomIdentityExpired();
	virtual void onZoomAuthIdentityExpired() {}
	virtual void onNotificationServiceStatus(ZOOM_SDK_NAMESPACE::SDKNotificationServiceStatus status) {}

protected:
	CSDKLoginUIMgr* m_parentFrame;
};

class CSDKWithoutLoginStartJoinMeetingUIGroup :public CSDKJoinMeetingOnlyFlowUIEvent
{
public:
	CSDKWithoutLoginStartJoinMeetingUIGroup();
	virtual ~CSDKWithoutLoginStartJoinMeetingUIGroup();
	void InitWindow(CPaintManagerUI& ui_mgr, CSDKLoginUIMgr* main_frame_);
	void UninitWindow();
	void Cleanup();
	void Show();
	void Hide();
	void Notify(TNotifyUI& msg);

	void DoWithoutLoginStartJoinMeetingBtnClick();
public:
	virtual void onMeetingStatusChanged(ZOOM_SDK_NAMESPACE::MeetingStatus status, int iResult = 0);
	virtual void onMeetingStatisticsWarningNotification(ZOOM_SDK_NAMESPACE::StatisticsWarningType type) {};
	virtual void onMeetingParameterNotification(const ZOOM_SDK_NAMESPACE::MeetingParameter* meeting_param) {};
	virtual void onSuspendParticipantsActivities() {};
  
protected:
	CVerticalLayoutUI* m_WithoutLoginStartJoinMeetingPage;
	CRichEditUI*	   m_editMeetingNumber;
	CRichEditUI*	   m_editScreenName;
	CRichEditUI*	   m_editMeetingPassword;
	CButtonUI*		   m_btnJoin;
	CSDKLoginUIMgr*	   m_parentFrame;
	CSDKWithoutLoginStartJoinMeetingFlow  m_withoutLoginJoinMeetingWorkFlow;
	bool m_bInMeeting;
};

class CSDKRestAPIUserUIGroup : public CSDKRestAPIUserUIEvent
{
public:
	CSDKRestAPIUserUIGroup();
	virtual ~CSDKRestAPIUserUIGroup();
	void InitWindow(CPaintManagerUI& ui_mgr, CSDKLoginUIMgr* main_frame_);
	void UninitWindow();
	void Cleanup();
	void Show();
	void Hide();
	void Notify(TNotifyUI& msg);

	void DoWithoutLoginStartMeetingBtnClick();
	void DoWithoutLoginJoinMeetingBtnClick();
public:
	virtual void onMeetingStatusChanged(ZOOM_SDK_NAMESPACE::MeetingStatus status, int iResult = 0);
	//handle the following status later. Just ignore them for a moment
	virtual void onMeetingStatisticsWarningNotification(ZOOM_SDK_NAMESPACE::StatisticsWarningType type) {};
	virtual void onMeetingParameterNotification(const ZOOM_SDK_NAMESPACE::MeetingParameter* meeting_param) {};
	virtual void onSuspendParticipantsActivities() {};

private:
	CVerticalLayoutUI* m_WithoutLoginRestAPIPage;
	CRichEditUI*	   m_editRestAPIUserZAK;
	CRichEditUI*	   m_editMeetingNumber;
	CRichEditUI*	   m_editScreenName;

	CButtonUI*		   m_btnStartMeeting;
	CButtonUI*         m_btnJoinMeeting;
	CSDKLoginUIMgr*  m_parentFrame;
	CSDKRestAPIUserWorkFlow  m_RestAPIUserWorkFlow;
	bool m_bInMeeting;
};

class CSDKLoginUIMgr : 
	public CWindowWnd, 
	public INotifyUI
{
public:
	CSDKLoginUIMgr();
	virtual ~CSDKLoginUIMgr();

	void SetEvent(CSDKDemoAppEvent* pAppEvent);
public:
	virtual LPCTSTR		GetWindowClassName() const   {   return _T("zSDKDemoUI");  }
	UINT GetClassStyle() const { return UI_CLASSSTYLE_FRAME | CS_DBLCLKS ; };
	virtual UINT		GetSkinRes()				 {	 return IDXML_LOGINFRAME_UI; };
	UILIB_RESOURCETYPE GetResourceType() const{	return UILIB_RESOURCE; }

	virtual void		InitWindow();
	virtual void		OnFinalMessage(HWND) {}

	virtual void		Notify( TNotifyUI& msg );
	virtual LRESULT		HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

	LRESULT OnClose(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);

	void SwitchToWaitingPage(const wchar_t* waiting_message, bool show);
	void ShowErrorMessage(const wchar_t* error_message);
	void SwitchToPage(loginTabPage nPage);

	CSDKDemoAppEvent* GetAppEvent();
	void SetCurrentPage(CVerticalLayoutUI* current_) {m_currentPage = current_;}

	bool LogOut();
	void ChangeUIforLoginFailed();
	void ChangeUIforJoinFailed();

	void NotifyAuthDone();
    void SwitchToPage(SwitchToLoginUIType);

	void CleanUp();

protected:
	CPaintManagerUI m_PaintManager;
	CSDKLoginWithSSOUIGroup m_LoginWithSSOUIGroup;
	CSDKWithoutLoginStartJoinMeetingUIGroup m_WithoutLoginStartJoinMeetingUIGroup;
	CSDKRestAPIUserUIGroup m_RestAPIUserUIGroup;
	CSDKLoginCBHandler     m_LoginCBHandler;
	CSDKDemoAppEvent* m_pAppEvent;
	CVerticalLayoutUI* m_waitingPage;
	CLabelUI*          m_waitingLabelUI;
	CGifAnimUI*		   m_gifWaiting;
	CVerticalLayoutUI* m_currentPage;

	COptionUI* m_btnRestAPI;
	COptionUI* m_btnLoginWithSSO;
	COptionUI* m_btnJoinMeetingOnly;
	CVerticalLayoutUI* m_panel_login_content;

	CVerticalLayoutUI* m_sso_login_page;
	CVerticalLayoutUI* m_restApi_login_page;
	CVerticalLayoutUI* m_only_join_page;
};
