// HelpDialog.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Limitless Remote PC_ver1.1.h"
#include "HelpDialog.h"
#include "afxdialogex.h"


// CHelpDialog 대화 상자입니다.

IMPLEMENT_DYNAMIC(CHelpDialog, CDialogEx)

CHelpDialog::CHelpDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_HELP, pParent)
{

}

CHelpDialog::~CHelpDialog()
{
}

void CHelpDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CHelpDialog, CDialogEx)
END_MESSAGE_MAP()


// CHelpDialog 메시지 처리기입니다.
