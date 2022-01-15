#if !defined(AFX_NETWALLTALK_H__99D3879B_8C8E_42C2_8438_607F2E6F9241__INCLUDED_)
#define AFX_NETWALLTALK_H__99D3879B_8C8E_42C2_8438_607F2E6F9241__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NetWallTalk.h : header file
//

#define NET_MAX_RECEIVE_SIZE            4096                // �����͸� ������ �ִ� ������ 
#define NET_DEFAULT_SOCKET_PORT         1212                // ����Ʈ�� �����ϴ� ��Ʈ ��ȣ 
#define NET_DEFAULT_SOCKET_IP           _T("192.168.10.110")         // ����Ʈ�� �����ϴ� IP ��巹�� 

#define NET_MSG_ACCEPT                  WM_USER + 1         // ������忡�� Ŭ���̾�Ʈ�� �������� ��� 
#define NET_MSG_CLOSE                   WM_USER + 2         // ������ �����Ҷ�
#define NET_MSG_RECEIVE                 WM_USER + 3         // �����͸� �����Ͽ��� ��� 
#define NET_MSG_RECEIVE_SERVER          WM_USER + 4         // �����͸� �����Ͽ��� ��� 
#define	NET_MSG_CONNECT					WM_USER + 5
#define	NET_MSG_SEND					WM_USER + 6
/////////////////////////////////////////////////////////////////////////////
// CSubNetWallTalk command target

class CSubNetWallTalk : public CSocket
{
// Attributes
public:

// Operations
public:
	CSubNetWallTalk(CSocket *pwndParant, BYTE* pReceiveDataPtr, UINT* pReceiveDataSize);
                                                                        // ������ 
	virtual ~CSubNetWallTalk();                                         // �Ҹ��� 

	BOOL SetServerAction;										// ���� ���� ����.
   
// Overrides
public:
	void SendData(BYTE* pSendData, UINT nDataSize);                     // �����͸� �����ϴ� �Լ� 
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSubNetWallTalk)
	public:
	virtual void OnReceive(int nErrorCode);                             // ������ ���Žÿ� �߻��ϴ� �Լ� 
	virtual void OnClose(int nErrorCode);                               // ���� ����ÿ� �߻��ϴ� �Լ� 
	virtual void OnSend(int nErrorCode);                                // ������ ���۽ÿ� �߻��ϴ� �Լ� 
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CSubNetWallTalk)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
	BYTE* m_szSendData;                                                         // ������ ������ ����������
	int m_nBytesBufferSize;                                                     // ������ �ѵ����� ������ 
	int m_nBytesSent;                                                           // ������ ������ ������ 

	UINT* m_pReceiveDataSize;                                                   // ������ ������ ������ 
	BYTE* m_pReceiveData;                                                       // ���ŵ����� ������� 
	CSocket* m_pwndParent;                                                      // �θ�Ŭ������ �ڵ� 
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CNetWallTalk command target

class CNetWallTalk : public CSocket
{
// Attributes
public:

// Operations
public:
	CNetWallTalk();                                                         // ������                             
    CNetWallTalk(BOOL bServer, UINT nPort = NET_DEFAULT_SOCKET_PORT, CString szIPAddress=NET_DEFAULT_SOCKET_IP);
                                                                            // ������ �� 
	virtual ~CNetWallTalk();                                                // �Ҹ��� 

// Overrides
public:
	
	// �����Լ� (������峪 Ŭ���̾�Ʈ ����϶�)
    static CString GetLocalIP();                                            // ������ ��ǻ���� ���� IP�� ��� �Լ� 

    BOOL SetModeChange(BOOL bIsServer=TRUE);                                // ���۸�带 �����ϴ� �Լ� 
    BOOL SetServerIPAddress(CString sIPAddress);                            // ������ IP��巹���� �����ϴ� �Լ� 
	BOOL SetServerPort(UINT nPort);                                         // ������ Port�� �����ϴ� �Լ� 

    BOOL Create(CWnd* pParentWnd);                                          // ������ �����ϴ� �Լ� 
	BOOL IsCreated();
    BOOL IsConnected();                                                     // ������ �Ǿ������� �˻�� �Լ�
    
    CString GetServerIPAddress();                                           // ������ IP��巹���� ��� �Լ� 
	CString GetClientIPAddress();                                           // Ŭ���̾�Ʈ�� IP��巹���� ��� �Լ� 
	UINT GetServerPort();                                                   // ������ ��Ʈ�� ��� �Լ� 
	UINT GetClientPort();                                                   // Ŭ���̾�Ʈ�� ��Ʈ�� ��� �Լ� 

	BOOL SendData(BYTE* pSendData, UINT nDataSize);                         // �����͸� �����ϴ� �Լ� 
    int GetReceiveData(BYTE* pData, UINT nBufSize);                         // ���ŵ����͸� �������� �Լ� 
	UINT GetReceiveDataSize();                                              // ������ ������ ����� �����ϴ� �Լ� 
	BOOL SetAction;															// ���� ���� ����.
// 	BOOL SetServerAction;													// ?? ?? ??.
	BOOL SetClientAction;													// ���� ���� ����.

    // ������忡�� ����ϴ� �Լ� 
	void SubClose();                                                        // ��������� �ݴ� �Լ� (Reserved)
	void SetSAction(BOOL bSet = FALSE);										// ���� ���� ����.
	BOOL GetServerAction();													// ���� ���� ����.
	
    CWnd* m_wndParent;                                                      // ��Ŭ������ ȣ���ϴ� �θ�Ŭ���� (Reserved)

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNetWallTalk)
	public:
	virtual void OnAccept(int nErrorCode);                                  // ������忡�� ���������� ���� �� ��� 
	virtual void OnClose(int nErrorCode);                                   // Ŭ���̾�Ʈ��忡�� ���� �Ǿ��� ��� 
	virtual void OnReceive(int nErrorCode);                                 // Ŭ���̾�Ʈ ��忡�� �����͸� �������� ��� 
	virtual void OnConnect(int nErrorCode);
	virtual void OnSend(int nErrorCode);                                    // �����͸� �����ϴ� �߿� ȣ��Ǿ����� �Լ� 
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CNetWallTalk)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
	
    /*
        m_IsConnected : ������ ����� ���¸� ǥ���ϴ� ���� 
        m_bCreated    : ������ �����Ǿ� �ִ� ���� 
                        ��������� ��� Listen���±����� ���Ѵ�.
                        Ŭ���̾�Ʈ����� ���� m_IsConnected�� ���¿� ���� �����̴�.
    */
    BOOL m_bCreated;                                            // ������ ������ �Ǿ� �ִ� ���� 
	BOOL m_IsConnected;                                         // ������¸� �˷��ش�.
	BYTE* m_szSendData;                                         // �������� �ϴ� �����͸� �ִ� �κ� 
	int m_nBytesBufferSize;                                     // ���������ϴ� ������ ������ 
	int m_nBytesSent;                                           // �̹̺��� ������ ������ 
	UINT m_nReceiveDataSize;                                    // ������ �������� ������ 
	CSubNetWallTalk* m_pSubNetWallTalk;                         // ��������϶��� �����ϴ� ���� Ŭ����

	BYTE* m_byteReceiveData;                                    // �����͸� �����Ͽ��� ��쿡 �����ϴ� ���� 
	UINT m_nSocketPort;                                         // �����ϰ��� �ϴ� ��Ʈ ��ȣ 
	
	BOOL m_bIsServer;                                           // ���������� Ȯ���ϴ� boolean
	CString m_szIPAddress;                                      // �����ϰ��� �ϴ� IP ��巹��
    
    CString GetIPAddress();                                                 // IP��巹���� ��ȯ�ϴ� �Լ� 
	BOOL SetIPAddress(CString szIPAddress=NET_DEFAULT_SOCKET_IP);           // IP��巹���� �����ϴ� �Լ� 
	UINT GetSocketPort();                                                   // ������Ʈ�� ��� �Լ� 
	BOOL SetSocketPort(UINT nSocketPort=NET_DEFAULT_SOCKET_PORT);           // ������Ʈ��  �����ϴ� �Լ� 
};

/////////////////////////////////////////////////////////////////////////////
extern CNetWallTalk *m_planSocket;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NETWALLTALK_H__99D3879B_8C8E_42C2_8438_607F2E6F9241__INCLUDED_)
