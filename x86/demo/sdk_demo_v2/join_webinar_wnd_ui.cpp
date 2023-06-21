#include "stdafx.h"
#include "join_webinar_wnd_ui.h"
#include "resource.h"
#include <string>

CJoinWebinarWndUI::CJoinWebinarWndUI()
{
	register_handler_ = nullptr;
}

CJoinWebinarWndUI::~CJoinWebinarWndUI()
{

}

void CJoinWebinarWndUI::InitWindow()
{
	RECT rc = { 0 };
	if (!::GetClientRect(m_hWnd, &rc)) return;
	rc.right = rc.left + 500;
	rc.bottom = rc.top + 250;
	if (!::AdjustWindowRectEx(&rc, GetWindowStyle(m_hWnd), (!(GetWindowStyle(m_hWnd) & WS_CHILD) && (::GetMenu(m_hWnd) != NULL)), GetWindowExStyle(m_hWnd))) return;
	int ScreenX = GetSystemMetrics(SM_CXSCREEN);
	int ScreenY = GetSystemMetrics(SM_CYSCREEN);

	::SetWindowPos(m_hWnd, NULL, (ScreenX - (rc.right - rc.left)) / 2,
		(ScreenY - (rc.bottom - rc.top)) / 2, rc.right - rc.left, rc.bottom - rc.top, SWP_NOZORDER | SWP_SHOWWINDOW);

	m_pEditEmail = static_cast<CRichEditUI*>(m_PaintManager.FindControl(_T("edit_email")));
	m_pEditName = static_cast<CRichEditUI*>(m_PaintManager.FindControl(_T("edit_name")));

	m_PaintManager.AddMessageFilter(this);
}

UILIB_RESOURCETYPE CJoinWebinarWndUI::GetResourceType()
{
	return UILIB_RESOURCE;
}

LPCTSTR CJoinWebinarWndUI::GetResourceID() const
{
	return _T("SKINDATA");
}

CDuiString CJoinWebinarWndUI::GetSkinFile()
{
	return to_wstring(IDXML_JOIN_WEBINAR_WINDOW_UI).c_str();
}

void CJoinWebinarWndUI::Notify(TNotifyUI& msg)
{
	if (msg.sType == _T("click"))
	{
		if (_tcscmp(msg.pSender->GetName(), _T("btn_join")) == 0)
		{
			DoJoinBtnClick();
		}
		else if (_tcscmp(msg.pSender->GetName(), _T("btn_cancel")) == 0)
		{
			DoCancelBtnClick();
		}
	}
}

void CJoinWebinarWndUI::SetRegisterHandler(ZOOM_SDK_NAMESPACE::IWebinarNeedRegisterHandler* handler)
{
	register_handler_ = handler;
}

LRESULT  CJoinWebinarWndUI::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM IParam)
{
	LRESULT lRes = 0;
	BOOL bHandled = TRUE;

	if (uMsg == WM_CREATE)
	{
		OnCreate();
		return lRes;
	}

	if (m_PaintManager.MessageHandler(uMsg, wParam, IParam, lRes))
	{
		return lRes;
	}

	return __super::HandleMessage(uMsg, wParam, IParam);
}

void CJoinWebinarWndUI::DoCancelBtnClick()
{
	if (!register_handler_)
		return;

	ZOOM_SDK_NAMESPACE::IWebinarNeedRegisterHandler::WebinarNeedRegisterType register_type = register_handler_->GetWebinarNeedRegisterType();
	switch (register_type)
	{
	case ZOOMSDK::IWebinarNeedRegisterHandler::WebinarReg_NONE:
		break;
	case ZOOMSDK::IWebinarNeedRegisterHandler::WebinarReg_By_Register_Url:
		break;
	case ZOOMSDK::IWebinarNeedRegisterHandler::WebinarReg_By_Email_and_DisplayName:
	{
		ZOOM_SDK_NAMESPACE::IWebinarNeedRegisterHandlerByEmail* handler_by_email = dynamic_cast<ZOOM_SDK_NAMESPACE::IWebinarNeedRegisterHandlerByEmail*>(register_handler_);
		if (handler_by_email)
		{
			handler_by_email->Cancel();
		}
	}
	break;
	default:
		break;
	}

	register_handler_ = nullptr;
}

void CJoinWebinarWndUI::DoJoinBtnClick()
{
	if (!register_handler_ || !m_pEditEmail || !m_pEditName)
		return;

	ZOOM_SDK_NAMESPACE::IWebinarNeedRegisterHandler::WebinarNeedRegisterType register_type = register_handler_->GetWebinarNeedRegisterType();
	switch (register_type)
	{
	case ZOOMSDK::IWebinarNeedRegisterHandler::WebinarReg_NONE:
		break;
	case ZOOMSDK::IWebinarNeedRegisterHandler::WebinarReg_By_Register_Url:
		break;
	case ZOOMSDK::IWebinarNeedRegisterHandler::WebinarReg_By_Email_and_DisplayName:
	{
		ZOOM_SDK_NAMESPACE::IWebinarNeedRegisterHandlerByEmail* handler_by_email = dynamic_cast<ZOOM_SDK_NAMESPACE::IWebinarNeedRegisterHandlerByEmail*>(register_handler_);
		if (handler_by_email)
		{
			std::wstring sEmail = m_pEditEmail->GetText();
			std::wstring sName = m_pEditName->GetText();
			ZOOM_SDK_NAMESPACE::SDKError err = handler_by_email->InputWebinarRegisterEmailAndScreenName(sEmail.c_str(), sName.c_str());
		}
	}
		break;
	default:
		break;
	}

	ShowWindow(false);
}

void CJoinWebinarWndUI::DoCloseBtnClick()
{
	DoCancelBtnClick();
	ShowWindow(false);
}

LRESULT  CJoinWebinarWndUI::MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
	if (WM_SYSCOMMAND == uMsg)
	{
		if (SC_CLOSE == wParam)
		{
			bHandled = true;
			DoCloseBtnClick();
		}
	}
	return 0;
}

LRESULT CJoinWebinarWndUI::OnCreate()
{
	m_PaintManager.Init(m_hWnd);

	CDialogBuilder builder;

	if (m_PaintManager.GetResourcePath().IsEmpty())
	{
		CDuiString strResourcePath = m_PaintManager.GetCurrentPath();
		strResourcePath += GetSkinFolder().GetData();
		m_PaintManager.SetResourcePath(strResourcePath.GetData());
	}

	CControlUI* pRoot = NULL;

	if (GetResourceType() == UILIB_RESOURCE)
	{
		STRINGorID xml(_ttoi(GetSkinFile().GetData()));
		pRoot = builder.Create(xml, _T("xml"), this, &m_PaintManager);
	}
	else
		pRoot = builder.Create(GetSkinFile().GetData(), (UINT)0, this, &m_PaintManager);
	ASSERT(pRoot);
	if (pRoot == NULL)
	{
		MessageBox(NULL, _T("load xml failed"), _T("Duilib"), MB_OK | MB_ICONERROR);
		ExitProcess(1);
		return 0;
	}

	m_PaintManager.AttachDialog(pRoot);
	m_PaintManager.AddNotifier(this);

	InitWindow();
}