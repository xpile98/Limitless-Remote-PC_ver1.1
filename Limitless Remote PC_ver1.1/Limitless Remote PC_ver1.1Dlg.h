
// Limitless Remote PC_ver1.1Dlg.h : ��� ����
//

#pragma once


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


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};
