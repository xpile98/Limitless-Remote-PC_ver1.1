
// Limitless Remote PC_ver1.1Dlg.h : ��� ����
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CLimitlessRemotePC_ver11Dlg ��ȭ ����
class CLimitlessRemotePC_ver11Dlg : public CDialogEx
{
// �����Դϴ�.
public:
	CLimitlessRemotePC_ver11Dlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LIMITLESSREMOTEPC_VER11_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.
	void ClickPrevious();
	void ClickNext();
	void Send_hold_connection();
	void ChangeUI(bool bIsConnected);
	void OnTrayMenuDialogOpen();
	void OnTrayMenuExit();

// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
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
