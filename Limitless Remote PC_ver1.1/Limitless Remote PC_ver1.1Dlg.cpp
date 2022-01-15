
// Limitless Remote PC_ver1.1Dlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "Limitless Remote PC_ver1.1.h"
#include "Limitless Remote PC_ver1.1Dlg.h"
#include "afxdialogex.h"
#include "ClientPC.h"
#include "HelpDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define WM_TRAY_NOTIFICATION WM_APP+10
enum {
	TRAY_BALLOON = 0
};
// CLimitlessRemotePC_ver11Dlg 대화 상자



CLimitlessRemotePC_ver11Dlg::CLimitlessRemotePC_ver11Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_LIMITLESSREMOTEPC_VER11_DIALOG, pParent)
	, m_nRadio_Mode(0), nTimerCount(0), bOnlyOneFlag(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
}

void CLimitlessRemotePC_ver11Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IPADDRESS1, m_ctrlIp);
	DDX_Radio(pDX, IDC_RADIO1, m_nRadio_Mode);
}

void CLimitlessRemotePC_ver11Dlg::ClickPrevious()
{
	UpdateData(TRUE);
	if (m_nRadio_Mode == 0)		//volume plus
		OnBnClickedButtonVolUp();
	else if (m_nRadio_Mode == 1)	//left
		OnBnClickedButtonLeft();
	else if (m_nRadio_Mode == 2)	//up
		OnBnClickedButtonUp();
}

void CLimitlessRemotePC_ver11Dlg::ClickNext()
{
	UpdateData(TRUE);
	if (m_nRadio_Mode == 0)		//volume minus
		OnBnClickedButtonVolDn();
	else if (m_nRadio_Mode == 1)	//right
		OnBnClickedButtonRight();
	else if (m_nRadio_Mode == 2)	//down
		OnBnClickedButtonDown();
}

void CLimitlessRemotePC_ver11Dlg::Send_hold_connection()
{
	m_ClientPc->SendData(_T("<DHCC_SIMPLE>hold_connection;cmd;0;0;</DHCC_SIMPLE>"));
}

void CLimitlessRemotePC_ver11Dlg::ChangeUI(bool bIsConnected)
{
	GetDlgItem(IDC_RADIO1)->EnableWindow(bIsConnected);
	GetDlgItem(IDC_RADIO2)->EnableWindow(bIsConnected);
	GetDlgItem(IDC_RADIO3)->EnableWindow(bIsConnected);
	GetDlgItem(IDC_BUTTON_POWER)->EnableWindow(bIsConnected);
	GetDlgItem(IDC_BUTTON_LEFT)->EnableWindow(bIsConnected);
	GetDlgItem(IDC_BUTTON_RIGHT)->EnableWindow(bIsConnected);
}

void CLimitlessRemotePC_ver11Dlg::OnTrayMenuDialogOpen()
{
	OnTaryNotifyAction(0, WM_LBUTTONDBLCLK);
}

void CLimitlessRemotePC_ver11Dlg::OnTrayMenuExit()
{
	DestroyWindow();
}

BEGIN_MESSAGE_MAP(CLimitlessRemotePC_ver11Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, &CLimitlessRemotePC_ver11Dlg::OnBnClickedButtonConnect)
	ON_BN_CLICKED(IDC_BUTTON_LEFT, &CLimitlessRemotePC_ver11Dlg::ClickPrevious)
	ON_BN_CLICKED(IDC_BUTTON_RIGHT, &CLimitlessRemotePC_ver11Dlg::ClickNext)
	ON_BN_CLICKED(IDC_BUTTON_POWER, &CLimitlessRemotePC_ver11Dlg::OnBnClickedButtonPower)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_TRAY_ADD, &CLimitlessRemotePC_ver11Dlg::OnBnClickedButtonTrayAdd)
	ON_MESSAGE(WM_TRAY_NOTIFICATION, OnTaryNotifyAction)
	ON_COMMAND(ID_TRAYMENU_EXIT, OnTrayMenuExit)
	ON_COMMAND(ID_TRAYMENU_DIALOG_OPEN, OnTrayMenuDialogOpen)

	ON_BN_CLICKED(IDC_BUTTON_INFO, &CLimitlessRemotePC_ver11Dlg::OnBnClickedButtonInfo)
END_MESSAGE_MAP()


// CLimitlessRemotePC_ver11Dlg 메시지 처리기

BOOL CLimitlessRemotePC_ver11Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	m_ClientPc = new CClientPC;
	m_ClientPc->SetHandle(this, this->m_hWnd);

	m_nRadio_Mode = 0;
	UpdateData(FALSE);

	m_ctrlIp.SetAddress(172, 30, 1, 1);

	SetTimer(TMR_UPDATE_STATUS, 500, NULL);

	RegisterHotKey(this->m_hWnd, 26000, MOD_ALT | MOD_CONTROL | MOD_NOREPEAT, 0x50);  //F4 + p
	RegisterHotKey(this->m_hWnd, 26001, MOD_ALT | MOD_CONTROL | MOD_NOREPEAT, VK_LEFT);  //F4 + p
	RegisterHotKey(this->m_hWnd, 26002, MOD_ALT | MOD_CONTROL | MOD_NOREPEAT, VK_RIGHT);  //F4 + p
	//::SetWindowPos(GetSafeHwnd(), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);


	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CLimitlessRemotePC_ver11Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CLimitlessRemotePC_ver11Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CLimitlessRemotePC_ver11Dlg::OnBnClickedButtonConnect()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_ClientPc->IsConnected())
	{
		m_ClientPc->DisconnectSocket();
		//m_ctrlStaticSocketState.SetWindowText(_T("DisConnected"));
	}
	else
	{
		CString sAddress, strPort;
		BOOL bRet = FALSE;

		UpdateData(TRUE);
		BYTE fi1, fi2, fi3, fi4;
		m_ctrlIp.GetAddress(fi1, fi2, fi3, fi4);
		sAddress.Format(_T("%d.%d.%d.%d"), fi1, fi2, fi3, fi4);
		bRet = m_ClientPc->InitSocket(false, 13793, sAddress);

		if (bRet == 0)
		{
			long err = GetLastError();
			//m_ctrlStaticSocketState.SetWindowText(_T("Connect Failed"));
			AfxMessageBox(_T("Connect Failed"));
		}
		else
		{
			//m_ctrlStaticSocketState.SetWindowText(_T("Server Connected"));
			ChangeUI(true);
			bOnlyOneFlag = false;
			AfxMessageBox(_T("Connect Connected"));
		}

		//AddDataPCMessageList_Client();
	}
}


void CLimitlessRemotePC_ver11Dlg::OnBnClickedButtonVolUp()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_ClientPc->SendData_LimitlessRemoteAPK(_T("VolumeP"));
}


void CLimitlessRemotePC_ver11Dlg::OnBnClickedButtonVolDn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_ClientPc->SendData_LimitlessRemoteAPK(_T("VolumeM"));
}


void CLimitlessRemotePC_ver11Dlg::OnBnClickedButtonLeft()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_ClientPc->SendData_LimitlessRemoteAPK(_T("Left"));
}


void CLimitlessRemotePC_ver11Dlg::OnBnClickedButtonRight()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_ClientPc->SendData_LimitlessRemoteAPK(_T("Right"));
}


void CLimitlessRemotePC_ver11Dlg::OnBnClickedButtonUp()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_ClientPc->SendData_LimitlessRemoteAPK(_T("Up"));
}


void CLimitlessRemotePC_ver11Dlg::OnBnClickedButtonDown()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_ClientPc->SendData_LimitlessRemoteAPK(_T("Down"));
}


void CLimitlessRemotePC_ver11Dlg::OnBnClickedButtonPower()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_ClientPc->SendData_LimitlessRemoteAPK(_T("Power"));
}


BOOL CLimitlessRemotePC_ver11Dlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (NULL != pMsg)
	{
		if (WM_KEYDOWN == pMsg->message)
		{
			if (VK_RETURN == pMsg->wParam ||
				VK_ESCAPE == pMsg->wParam)
			{
				return false;
			}
			else if (VK_LEFT == pMsg->wParam)
			{
				ClickPrevious();
				GotoDlgCtrl(GetDlgItem(IDC_BUTTON_LEFT));
				return false;
			}
			else if (VK_RIGHT == pMsg->wParam)
			{
				ClickNext();
				GotoDlgCtrl(GetDlgItem(IDC_BUTTON_RIGHT));
				return false;
			}
			else if (0x50 == pMsg->wParam)		//p
			{
				OnBnClickedButtonPower();
				GotoDlgCtrl(GetDlgItem(IDC_BUTTON_POWER));
				return false;
			}
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CLimitlessRemotePC_ver11Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nIDEvent == TMR_UPDATE_STATUS)
	{
		if (m_ClientPc->IsConnected())
		{
			if (nTimerCount < 20)
				nTimerCount++;
			else
			{
				nTimerCount = 0;
				Send_hold_connection();
			}
			SetDlgItemText(IDC_BUTTON_CONNECT, _T("Disconnect"));
		}
		else
		{
			if (bOnlyOneFlag == false)
			{
				m_ClientPc->DisconnectSocket();
				ChangeUI(false);
				bOnlyOneFlag = true;
			}
			SetDlgItemText(IDC_BUTTON_CONNECT, _T("Connect"));
		}
	}

	//else if (nIDEvent == TRAY_BALLOON)
	//{
	//	//_tprintf(_T("TRAY_BALLOON\n"));
	//	MSG msg = { 0 };
	//	GetMessage(&msg, NULL, 0, 0);
	//	if (msg.message == WM_HOTKEY)
	//	{
	//		_tprintf(_T("WM_HOTKEY received\n"));
	//	}
	//}


	CDialogEx::OnTimer(nIDEvent);
}


BOOL CLimitlessRemotePC_ver11Dlg::DestroyWindow()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	KillTimer(TMR_UPDATE_STATUS);
	m_ClientPc->DisconnectSocket();

	NOTIFYICONDATA nid;
	ZeroMemory(&nid, sizeof(nid));
	nid.cbSize = sizeof(nid);
	nid.uID = 0;
	nid.hWnd = GetSafeHwnd();
	BOOL bRet = ::Shell_NotifyIcon(NIM_DELETE, &nid);

	return CDialogEx::DestroyWindow();
}


void CLimitlessRemotePC_ver11Dlg::OnBnClickedButtonTrayAdd()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	NOTIFYICONDATA nid;
	ZeroMemory(&nid, sizeof(nid));
	nid.cbSize = sizeof(NOTIFYICONDATA);
	nid.uID = 0; // 트레이 구조체 아이디.
	nid.uFlags = NIF_ICON | NIF_TIP | NIF_MESSAGE;
	nid.hWnd = m_hWnd;
	nid.hIcon = AfxGetApp()->LoadIconW(IDI_ICON1);
	nid.uCallbackMessage = WM_TRAY_NOTIFICATION;
	lstrcpy(nid.szTip, _T("우클릭하여 메뉴 보기"));
	::Shell_NotifyIcon(NIM_ADD, &nid);
	
	SetTimer(TRAY_BALLOON, 1, NULL);
	AfxGetApp()->m_pMainWnd->ShowWindow(SW_HIDE); // 다이얼로그는 숨는다.
}

LRESULT CLimitlessRemotePC_ver11Dlg::OnTaryNotifyAction(WPARAM wParam, LPARAM lParam)
{
	switch (lParam)
	{
	case WM_RBUTTONDOWN:
	{
		CPoint ptMouse;
		::GetCursorPos(&ptMouse);
		CMenu menu;
		menu.LoadMenu(IDR_MENU1);
		CMenu *pMenu = menu.GetSubMenu(0); //활성화 할 메뉴 지정
		pMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, ptMouse.x, ptMouse.y, AfxGetMainWnd());
	}
	break;
	case WM_LBUTTONDBLCLK:
	{
		NOTIFYICONDATA nid;
		ZeroMemory(&nid, sizeof(nid));
		nid.cbSize = sizeof(nid);
		nid.uID = 0;
		nid.hWnd = GetSafeHwnd();
		BOOL bRet = ::Shell_NotifyIcon(NIM_DELETE, &nid); //트레이아이콘 제거
		if (!bRet)
		{
			::AfxMessageBox(_T("트레이아이콘 제거실패"));
			return -1;
		}
		AfxGetApp()->m_pMainWnd->ShowWindow(SW_SHOW); //윈도우 활성화
		KillTimer(TRAY_BALLOON);
	}
	break;
	}
	return 1;
}

LRESULT CLimitlessRemotePC_ver11Dlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == WM_HOTKEY) {
		// 시스템 전역 단축키가 눌러진 경우                
		if (wParam == 26000) {
			//_tprintf(_T("HOTKEY1\n"));
			OnBnClickedButtonPower();
		}
		else if (wParam == 26001) {
			//_tprintf(_T("HOTKEY2\n"));
			ClickPrevious();
		}
		else if (wParam == 26002) {
			//_tprintf(_T("HOTKEY3\n"));
			ClickNext();
		}
	}
	return CDialogEx::WindowProc(message, wParam, lParam);
}


void CLimitlessRemotePC_ver11Dlg::OnBnClickedButtonInfo()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CHelpDialog dlg;
	dlg.DoModal();
}
