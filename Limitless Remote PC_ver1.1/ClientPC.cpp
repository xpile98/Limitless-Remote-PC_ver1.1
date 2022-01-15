#include "stdafx.h"
#include "ClientPC.h"

CClientPC *m_ClientPc = NULL;

CClientPC::CClientPC()
{
	m_bIsServer = true;
	m_bIsConnectRetry = false;
	m_strServerIP = _T("127.0.0.1");
	m_nPortID = 3000;
}


CClientPC::~CClientPC()
{
}


int CClientPC::SetHandle(CWnd * pWnd, HWND hWnd)
{
	RECT	rect;
	m_wndParent = pWnd;

	if (!Create(NULL, _T("LANCOM"), WS_BORDER | WS_DISABLED, rect, pWnd, 0))
	{
		return -1;
	}

	return 0;
}

int CClientPC::InitSocket(bool isServer, int nPortID, CString strServerIP)
{
	int ret = 1;
	CString strTmp;
	m_bIsServer = isServer;
	m_nPortID = nPortID;
	m_strServerIP = strServerIP;

	if (m_bIsServer)
	{
		if (m_planSocket == NULL)
		{
			m_planSocket = new CNetWallTalk(TRUE, nPortID, strServerIP);

			if (!m_planSocket->Create(this))
			{
				ret = DisconnectSocket();
				return ret;
			}
		}
	}
	else
	{
		if (m_planSocket == NULL)
		{
			m_planSocket = new CNetWallTalk(FALSE, nPortID, strServerIP);

			if (!m_planSocket->Create(this))
			{
				ret = DisconnectSocket();
				return ret;
			}
		}
	}

	m_IsSet = TRUE;
	m_bIsConnectRetry = false;

	return ret;
}

bool CClientPC::CloseSocket()
{
	if (m_bIsServer)
	{
		m_planSocket->SubClose();
	}

	if (m_planSocket != NULL)
	{
		m_planSocket->Close();
		delete m_planSocket;
		m_planSocket = NULL;
		m_IsSet = FALSE;
	}
	return true;
}

int CClientPC::DisconnectSocket()
{
	//Close µÇ¸é FALSE RETURN;
	if (m_planSocket != NULL)
	{
		m_planSocket->Close();

		delete m_planSocket;
		m_planSocket = NULL;
		m_IsSet = FALSE;
	}

	//if (m_bIsConnectRetry)
	//	SetTimer(TMR_ACCURA_CONNECT, 1500, NULL);

	return m_IsSet;
}

BOOL CClientPC::IsConnected()
{
	if (m_planSocket == NULL)
		return FALSE;

	return m_planSocket->IsConnected();
}

void CClientPC::SendData(CString strMsg)
{
	CString strSendMsg;
	//strSendMsg.Format(_T("%c%s%c",(BYTE)STX,strMsg,(BYTE)ETX);
	strSendMsg.Format(_T("%s"), strMsg);

	if (m_planSocket == NULL)
		return;

	BYTE* bySendMsg = new BYTE[strSendMsg.GetLength()];
	//	memcpy(bySendMsg, (unsigned char*)(LPCTSTR)strSendMsg, strSendMsg.GetLength());
	//	WideCharToMultiByte(CP_ACP, 0, strSendMsg, -1, (char*)bySendMsg, -1, NULL, NULL);
	// 	for (int i = 0; i < strSendMsg.GetLength(); i++)
	// 		bySendMsg[i] = (unsigned char)strSendMsg.GetBuffer(i);
	//	strcpy(bySendMsg, strSendMsg.GetBuffer(0));

	size_t CharactersConverted = 0;
	wcstombs_s(&CharactersConverted, (char*)bySendMsg, strSendMsg.GetLength() + 1, strSendMsg, _TRUNCATE);



	// 	memcpy(byte, (VOID*)LPCTSTR(strTemp), str.GetLength());	
	// 	WideCharToMultiByte(CP_ACP, 0, bySendMsg, -1, strSendMsg, -1, NULL, NULL);
	//	m_planSocket->SendData((BYTE*)(LPCTSTR)strSendMsg, strSendMsg.GetLength());
	m_planSocket->SendData(bySendMsg, strSendMsg.GetLength());
	m_wndParent->SendMessage(NET_MSG_SEND);
}

void CClientPC::SendData_LimitlessRemoteAPK(CString strKey)
{
	CString strPressDown;
	CString strPressUp;

	strPressDown.Format(_T("<DHCC_SIMPLE>%s;PRESSDOWN;0;0;</DHCC_SIMPLE>"), strKey);
	strPressUp.Format(_T("<DHCC_SIMPLE>%s;PRESSUP;0;0;</DHCC_SIMPLE>"), strKey);

	SendData(strPressDown);
	SendData(strPressUp);
}