
// Limitless Remote PC_ver1.1Dlg.h : 헤더 파일
//

#pragma once


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


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};
