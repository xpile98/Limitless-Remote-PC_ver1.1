#if !defined(AFX_NETWALLTALK_H__99D3879B_8C8E_42C2_8438_607F2E6F9241__INCLUDED_)
#define AFX_NETWALLTALK_H__99D3879B_8C8E_42C2_8438_607F2E6F9241__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NetWallTalk.h : header file
//

#define NET_MAX_RECEIVE_SIZE            4096                // 데이터를 수신할 최대 사이즈 
#define NET_DEFAULT_SOCKET_PORT         1212                // 디폴트로 설정하는 포트 번호 
#define NET_DEFAULT_SOCKET_IP           _T("192.168.10.110")         // 디폴트러 설정하는 IP 어드레스 

#define NET_MSG_ACCEPT                  WM_USER + 1         // 서버모드에서 클라이언트가 접속했을 경우 
#define NET_MSG_CLOSE                   WM_USER + 2         // 소켓을 종료할때
#define NET_MSG_RECEIVE                 WM_USER + 3         // 데이터를 수신하였을 경우 
#define NET_MSG_RECEIVE_SERVER          WM_USER + 4         // 데이터를 수신하였을 경우 
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
                                                                        // 생성자 
	virtual ~CSubNetWallTalk();                                         // 소멸자 

	BOOL SetServerAction;										// 소켓 동작 상태.
   
// Overrides
public:
	void SendData(BYTE* pSendData, UINT nDataSize);                     // 데이터를 전송하는 함수 
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSubNetWallTalk)
	public:
	virtual void OnReceive(int nErrorCode);                             // 데이터 수신시에 발생하는 함수 
	virtual void OnClose(int nErrorCode);                               // 소켓 종료시에 발생하는 함수 
	virtual void OnSend(int nErrorCode);                                // 데이터 전송시에 발생하는 함수 
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CSubNetWallTalk)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
	BYTE* m_szSendData;                                                         // 전송할 데이터 버퍼포인터
	int m_nBytesBufferSize;                                                     // 전송할 총데이터 사이즈 
	int m_nBytesSent;                                                           // 전송한 데이터 사이즈 

	UINT* m_pReceiveDataSize;                                                   // 수신한 데이터 사이즈 
	BYTE* m_pReceiveData;                                                       // 수신데이터 저장버퍼 
	CSocket* m_pwndParent;                                                      // 부모클래스의 핸들 
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
	CNetWallTalk();                                                         // 생성자                             
    CNetWallTalk(BOOL bServer, UINT nPort = NET_DEFAULT_SOCKET_PORT, CString szIPAddress=NET_DEFAULT_SOCKET_IP);
                                                                            // 생성자 투 
	virtual ~CNetWallTalk();                                                // 소멸자 

// Overrides
public:
	
	// 공통함수 (서버모드나 클라이언트 모드일때)
    static CString GetLocalIP();                                            // 현재의 컴퓨터의 로컬 IP를 얻는 함수 

    BOOL SetModeChange(BOOL bIsServer=TRUE);                                // 동작모드를 설정하는 함수 
    BOOL SetServerIPAddress(CString sIPAddress);                            // 서버의 IP어드레스를 설정하는 함수 
	BOOL SetServerPort(UINT nPort);                                         // 서버의 Port를 설정하는 함수 

    BOOL Create(CWnd* pParentWnd);                                          // 소켓을 생성하는 함수 
	BOOL IsCreated();
    BOOL IsConnected();                                                     // 연결이 되었는지를 검사는 함수
    
    CString GetServerIPAddress();                                           // 서버의 IP어드레스를 얻는 함수 
	CString GetClientIPAddress();                                           // 클라이언트의 IP어드레스를 얻는 함수 
	UINT GetServerPort();                                                   // 서버의 포트를 얻는 함수 
	UINT GetClientPort();                                                   // 클라이언트의 포트를 얻는 함수 

	BOOL SendData(BYTE* pSendData, UINT nDataSize);                         // 데이터를 전송하는 함수 
    int GetReceiveData(BYTE* pData, UINT nBufSize);                         // 수신데이터를 가져가는 함수 
	UINT GetReceiveDataSize();                                              // 수신한 데이터 사이즈를 리턴하는 함수 
	BOOL SetAction;															// 소켓 동작 상태.
// 	BOOL SetServerAction;													// ?? ?? ??.
	BOOL SetClientAction;													// 소켓 동작 상태.

    // 서버모드에서 사용하는 함수 
	void SubClose();                                                        // 서브소켓을 닫는 함수 (Reserved)
	void SetSAction(BOOL bSet = FALSE);										// 소켓 동작 상태.
	BOOL GetServerAction();													// 소켓 동작 상태.
	
    CWnd* m_wndParent;                                                      // 이클래스를 호출하는 부모클래스 (Reserved)

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNetWallTalk)
	public:
	virtual void OnAccept(int nErrorCode);                                  // 서버모드에서 서버소켓을 생성 할 경우 
	virtual void OnClose(int nErrorCode);                                   // 클라이언트모드에서 종료 되었을 경우 
	virtual void OnReceive(int nErrorCode);                                 // 클라이언트 모드에서 데이터를 수신했을 경우 
	virtual void OnConnect(int nErrorCode);
	virtual void OnSend(int nErrorCode);                                    // 데이터를 전송하는 중에 호출되어지는 함수 
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CNetWallTalk)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
	
    /*
        m_IsConnected : 소켓이 연결된 상태를 표시하는 변수 
        m_bCreated    : 소켓이 생성되어 있는 생태 
                        서버모드의 경우 Listen상태까지를 말한다.
                        클라이언트모드의 경우는 m_IsConnected의 상태와 같은 상태이다.
    */
    BOOL m_bCreated;                                            // 소켓이 생성이 되어 있는 상태 
	BOOL m_IsConnected;                                         // 연결상태를 알려준다.
	BYTE* m_szSendData;                                         // 보내고자 하는 데이터를 넣는 부분 
	int m_nBytesBufferSize;                                     // 보내고자하는 버퍼의 사이즈 
	int m_nBytesSent;                                           // 이미보낸 버퍼의 사이즈 
	UINT m_nReceiveDataSize;                                    // 수신한 데이터의 사이즈 
	CSubNetWallTalk* m_pSubNetWallTalk;                         // 서버모드일때에 생성하는 서브 클래스

	BYTE* m_byteReceiveData;                                    // 데이터를 수신하였을 경우에 저장하는 버퍼 
	UINT m_nSocketPort;                                         // 접속하고자 하는 포트 번호 
	
	BOOL m_bIsServer;                                           // 서버인지를 확인하는 boolean
	CString m_szIPAddress;                                      // 접속하고자 하는 IP 어드레스
    
    CString GetIPAddress();                                                 // IP어드레스를 반환하는 함수 
	BOOL SetIPAddress(CString szIPAddress=NET_DEFAULT_SOCKET_IP);           // IP어드레스를 설정하는 함수 
	UINT GetSocketPort();                                                   // 소켓포트를 얻는 함수 
	BOOL SetSocketPort(UINT nSocketPort=NET_DEFAULT_SOCKET_PORT);           // 소켓포트를  설정하는 함수 
};

/////////////////////////////////////////////////////////////////////////////
extern CNetWallTalk *m_planSocket;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NETWALLTALK_H__99D3879B_8C8E_42C2_8438_607F2E6F9241__INCLUDED_)
