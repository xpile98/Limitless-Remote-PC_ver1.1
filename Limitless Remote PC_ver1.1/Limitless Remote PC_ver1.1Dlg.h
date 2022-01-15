
// Limitless Remote PC_ver1.1Dlg.h : 헤더 파일
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CLimitlessRemotePC_ver11Dlg 대화 상자
class CLimitlessRemotePC_ver11Dlg : public CDialogEx
{
// 생성입니다.
public:
	CLimitlessRemotePC_ver11Dlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LIMITLESSREMOTEPC_VER11_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.
	void ClickPrevious();
	void ClickNext();
	void Send_hold_connection();
	void ChangeUI(bool bIsConnected);
	void OnTrayMenuDialogOpen();
	void OnTrayMenuExit();

// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CIPAddressCtrl m_ctrlIp;
	afx_msg void OnBnClickedButtonConnect();
	afx_msg void OnBnClickedButtonVolUp();
	afx_msg void OnBnClickedButtonVolDn();
	afx_msg void OnBnClickedButtonLeft();
	afx_msg void OnBnClickedButtonRight();
	afx_msg void OnBnClickedButtonUp();
	afx_msg void OnBnClickedButtonDown();
	afx_msg void OnBnClickedButtonPower();
	int m_nRadio_Mode;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	bool bOnlyOneFlag;
	int nTimerCount;
	virtual BOOL DestroyWindow();
	afx_msg void OnBnClickedButtonTrayAdd();
	afx_msg LRESULT CLimitlessRemotePC_ver11Dlg::OnTaryNotifyAction(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT CLimitlessRemotePC_ver11Dlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam);

	afx_msg void OnBnClickedButtonInfo();
};
