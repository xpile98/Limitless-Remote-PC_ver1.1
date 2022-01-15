#pragma once
#include "afxwin.h"
#include "NetWallTalk.h"

#define	MAX_LENGTH			1024
#define OK_RESPONSE			0
#define MSG_MAX_COUNT		100
#define	TMR_UPDATE_STATUS	1001
#define STX					0x02
#define ETX					0x03

typedef struct tagRECVDATA_INFO
{
	CString		strCMD;
	CString		strParam[20];
	int			nParamCnt;

} RECVDATA_INFO;

class CClientPC :
	public CWnd
{
public:
	CClientPC();
	~CClientPC();

	// Attributes
private:
	CWnd*	m_wndParent;						// ��Ŭ������ ȣ���ϴ� �θ�Ŭ���� (Reserved)

public:
	bool	m_bIsServer;
	BOOL	m_IsSet;							// ������ �Ǿ����� �˻��ϴ� ����
	bool	m_bIsConnectRetry;
	int		m_nPortID;
	CString	m_strServerIP;

	// Operations
public:
	// INIT
	int		SetHandle(CWnd* pWnd, HWND hWnd);
	//int		InitSocket(bool isServer);
	int		InitSocket(bool isServer, int nPortID, CString strServerIP = NET_DEFAULT_SOCKET_IP);
	bool	CloseSocket();
	int		DisconnectSocket();
	//void	RetryConnect();

	//BOOL	IsCreated();
	BOOL	IsConnected();
	bool	IsServer() { return m_bIsServer; }


	//void	AddDataPCMessageList_Server();
	//void	AddDataPCMessageList_Client();

	// RECEIVE
	//CString m_strReceiveMsgAll;
	//RECVDATA_INFO m_sRecvData;
	//CString GetReceiveData() { return m_strReceiveMsgAll; }
	//void	ReceiveDataParsing(CString strRecvData);

	// SEND
	//CString m_SendMsg;


	void SendData(CString strMsg);
	void SendData_LimitlessRemoteAPK(CString strKey);

	//Longrun
	//void SendMsg_Client_Connected(bool bConnected);
	//void SendMsg_Device_Connected(int nDevNum, bool bConnected);
	//void SendMsg_Receive_Do_Measure_Colorimeter(int nDevNum, bool bOk);

protected:
	//afx_msg void OnTimer(UINT_PTR nIDEvent);
	//afx_msg LRESULT OnSockConnect(WPARAM wParam, LPARAM lParam);
	//afx_msg LRESULT OnSockClose(WPARAM wParam, LPARAM lParam);	    // ���� ����(����, Ŭ���̾�Ʈ ����� ��� onClose���Ž�)
	//afx_msg LRESULT OnSockReceiveClient(WPARAM wParam, LPARAM lParam);	// ������ ���Ž�(����, Ŭ���̾�Ʈ ����� ��� onReceive���Ž�)
	//afx_msg LRESULT OnSockReceiveServer(WPARAM wParam, LPARAM lParam);	// ������ ���Ž�(����, Ŭ���̾�Ʈ ����� ��� onReceive���Ž�)
	//afx_msg LRESULT OnSockAccept(WPARAM wParam, LPARAM lParam);	    // ������ ���Ž�(����, Ŭ���̾�Ʈ ����� ��� onReceive���Ž�)
																	
	//DECLARE_MESSAGE_MAP()


};

extern CClientPC *m_ClientPc;
