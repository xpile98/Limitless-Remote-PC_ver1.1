// NetWallTalk.cpp : implementation file
//

#include "stdafx.h"
#include "NetWallTalk.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CNetWallTalk *m_planSocket;
/////////////////////////////////////////////////////////////////////////////
// CNetWallTalk

// 생성자 초기에는 디폴트값으로 셋팅을 한다.
CNetWallTalk::CNetWallTalk()
{   
    m_bIsServer = TRUE;                                                         // 기본은 서버로 운영한다.
    m_byteReceiveData = new BYTE[NET_MAX_RECEIVE_SIZE];                         // 버퍼를 초기화 한다.
    m_nSocketPort = NET_DEFAULT_SOCKET_PORT;                                    // 기본 소켓포트를 초기화 한다.
    m_szIPAddress = NET_DEFAULT_SOCKET_IP;                                      // 기본 IP어드레스를 초기화 한다.
    m_wndParent = NULL;                                                         // 기본 부모클래스를 초기화 한다.

    m_pSubNetWallTalk = NULL;                                                   // 서버모드일때 생성이 되는 서브클래스 
    m_nReceiveDataSize = 0;                                                     // 수신한 데이터의 사이즈 

    m_IsConnected = FALSE;                                                      // 초기의 연결상태를 False로 설정한다.
    m_bCreated = FALSE;                                                         // 소켓이 생성되었는지 알려주는 변수 
	Sleep(50);
}

// 생성자 초기값을 입력할수 있다.
CNetWallTalk::CNetWallTalk(BOOL bServer, UINT nPort, CString szIPAddress)
{
    m_bIsServer = bServer;                                                      // 운영모드를 설정한다.
    m_byteReceiveData = new BYTE[NET_MAX_RECEIVE_SIZE];                         // 수신버퍼를 초기화 한다.
    m_nSocketPort = nPort;                                                      // 포트를 초기화 한다.
    m_szIPAddress = szIPAddress;                                                // IP주소를 초기화 한다.
    m_wndParent = NULL;                                                         // 기본 부모클래스를 초기화 한다.

    m_pSubNetWallTalk = NULL;                                                   // 서버 모드일때 생성이 되는 서브클래스 
    m_nReceiveDataSize = 0;                                                     // 수신한 데이터의 사이즈 

    m_IsConnected = FALSE;                                                      // 초기의 연결상태를 False로 설정한다.
    m_bCreated = FALSE;                                                         // 소켓이 생성되었는지 알려주는 변수 
	Sleep(50);
}

CNetWallTalk::~CNetWallTalk()
{
    delete [] m_byteReceiveData;                                                   // 수신버퍼를 지운다.

    if(TRUE == m_IsConnected)               // 연결상태일 경우 
    {
        if(TRUE == m_bIsServer)             // 서버 모드일 경우 
        {
            SubClose();                 // 서브소켓의 종료를 유도한다.                      
        }
        else                                // 클라이언트 모드일 경우 
        {
            // 특별히 해줄일이 읍네요...
        }
        
    }
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CNetWallTalk, CSocket)
	//{{AFX_MSG_MAP(CNetWallTalk)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CNetWallTalk member functions

// 소케의 포트를 설정하는 함수 
BOOL CNetWallTalk::SetSocketPort(UINT nSocketPort)
{

    if(TRUE == m_bIsServer)           // 서버 모드일 경우 
    {
        //
        // 서버의 경우 CSocket::Create()시 포트를 설정하기 때문에 
        // 
        //
        if(TRUE == m_bCreated)                      // 이미 소켓이 생성이 되어 있는 경우에는 
        {
            return FALSE;
        }
    }
    else                            // 클라이언트 모드일 경우 
    {
        //
        // 클라이언트의 경우 CSocket::Create()시에는 설정하는 것이 없고
        // CSocket::Connect()할때 포트를 설정한다.
        //
        if(TRUE == m_IsConnected)
        {
            return FALSE;
        }
    }

    m_nSocketPort = nSocketPort;

    return TRUE;
}

// 소켓의 포를 얻는 함수 
UINT CNetWallTalk::GetSocketPort()
{
    return m_nSocketPort;
}

void CNetWallTalk::SetSAction(BOOL bSet)													// 소켓 동작 상태.
{
	m_pSubNetWallTalk->SetServerAction = bSet;
}

// 동작하는 모드를 바꾸는 함수 
// 소켓이 생성이 되어지기 전에 바꾸어 주어야 한다.
BOOL CNetWallTalk::SetModeChange(BOOL bIsServer)
{
    if(TRUE == m_bCreated)                      // 이미 소켓이 생성이 되어 있는 상태인경우 
    {
        return FALSE;
    }

    m_bIsServer = bIsServer;                    // 모드를 셋팅한다. TRUE = 서버모드                   
                                                //                  FALSE = 클라이언트 모드 
    return TRUE;
}

// IP어드레스를 설정하는 함수 
BOOL CNetWallTalk::SetIPAddress(CString szIPAddress)
{

    if(TRUE == m_bIsServer)           // 서버 모드일 경우 
    {
        if(TRUE == m_bCreated)                      // 이미 소켓이 생성이 되어 있는 경우에는 
        {
            return FALSE;
        }
    }
    else                            // 클라이언트 모드일 경우 
    {
        if(TRUE == m_IsConnected)                   // 이미 연결이 되어 있는 경우 
        {
            return FALSE;
        }
    }
    

    m_szIPAddress = szIPAddress;

    return TRUE;
}

// IP어드레스를 리턴하는 함수 
CString CNetWallTalk::GetIPAddress()
{
    return m_szIPAddress;
}

// 서버모드일때만 발생하는 함수 
void CNetWallTalk::OnAccept(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
    if(NULL == m_pSubNetWallTalk)               // 연결되어진 소켓이 없는 경우 
    {
        m_pSubNetWallTalk = new CSubNetWallTalk(this, m_byteReceiveData, &m_nReceiveDataSize);
    
	    if(!CSocket::Accept(*m_pSubNetWallTalk))                    // 서브소켓의 연결에 실패하였을 경우 
	    {
            AfxMessageBox(_T("Error : Accept() in socket"));
            delete m_pSubNetWallTalk;
		    m_pSubNetWallTalk = NULL;
            return;
	    }
        else
        {
            m_IsConnected = TRUE;                       // 서버 모드일 경우에는 이때에 연결이 되었다고 판단.
	        m_wndParent->SendMessage(NET_MSG_ACCEPT, WPARAM(nErrorCode), NULL);                 // 서브소켓을 연결함을 알림    
     }

        CSocket::OnAccept(nErrorCode);
    }
    else                                // 이미 연결되어진 소켓이 있는 경우 
    {
        CSubNetWallTalk *SubNetWallTalk = new CSubNetWallTalk(this, m_byteReceiveData, &m_nReceiveDataSize);

        if(!CSocket::Accept(*SubNetWallTalk))                    // 서브소켓의 연결에 실패하였을 경우 
	    {
            AfxMessageBox(_T("Error : Accept() in socket"));
            return;
	    }

        CSocket::OnAccept(nErrorCode);

        delete SubNetWallTalk;
        //SubNetWallTalk.Close();
        return;
    }

}
void CNetWallTalk::OnConnect(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class

	switch(nErrorCode)
	{
	case WSAETIMEDOUT:
		//SendMessage(m_hEQWnd, WM_SOCKDATA_CLOSE, 0, 0);
		break;
	}
	m_wndParent->SendMessage(NET_MSG_CONNECT, WPARAM(nErrorCode), NULL);
	CSocket::OnConnect(nErrorCode);
}
// 클라이언트 모드에서 발생이 되어지는 함수 
void CNetWallTalk::OnClose(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CSocket::OnClose(nErrorCode);

    m_IsConnected = FALSE;                              // 연결이 끊어지면 False를 셋팅한다.
	SetAction = TRUE;
    m_wndParent->SendMessage(NET_MSG_CLOSE, WPARAM(nErrorCode), NULL);                  // 소켓이 종료되었다고 알림
	CSocket::OnClose(nErrorCode);
}

// 클라이언트로 생성이 되었을 경우에만 발생하는 함수 
void CNetWallTalk::OnReceive(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	m_nReceiveDataSize = (UINT)Receive(m_byteReceiveData, NET_MAX_RECEIVE_SIZE);        // 데이터를 수신한다
	SetClientAction = TRUE;
	SetAction = TRUE;

    m_wndParent->PostMessage(NET_MSG_RECEIVE, WPARAM(nErrorCode), NULL);                // 데이터를 수신했다고 알림
       
	CSocket::OnReceive(nErrorCode);
}

BOOL CNetWallTalk::GetServerAction()
{
	BOOL bRet = FALSE;

    if(FALSE == m_IsConnected)              // 연결상태가 아닌 경우는 전송하지 않는다.
    {
        return FALSE;
    }
	bRet = m_pSubNetWallTalk->SetServerAction;

	return bRet;
}
/////////////////////////////////////////////////////////////////////////////
// CSubNetWallTalk

// 생성자 
CSubNetWallTalk::CSubNetWallTalk(CSocket *pwndParant, BYTE* pReceiveDataPtr, UINT* pReceiveDataSize)
{
    m_pwndParent = pwndParant;                                                  // 부모클래스의 핸들을 가져온다.
    m_pReceiveData = pReceiveDataPtr;                                           // 수신한 버퍼의 포인터를 저장한다.
    m_pReceiveDataSize = pReceiveDataSize;                                      // 수신한 데이터사이즈를 저장한 변수포인터 
}

// 소멸자 
CSubNetWallTalk::~CSubNetWallTalk()
{
    
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CSubNetWallTalk, CSocket)
	//{{AFX_MSG_MAP(CSubNetWallTalk)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CSubNetWallTalk member functions

// 데이터가 수신되었을 경우에 호출하는 함수
void CSubNetWallTalk::OnReceive(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	*m_pReceiveDataSize = (UINT)Receive(m_pReceiveData, NET_MAX_RECEIVE_SIZE);      // 데이터를 수신한다.

	SetServerAction = TRUE;
	((CNetWallTalk*)m_pwndParent)->SetSAction(SetServerAction);
    ((CNetWallTalk*)m_pwndParent)->m_wndParent->SendMessage(NET_MSG_RECEIVE_SERVER, WPARAM(nErrorCode), NULL);
                                                                                   // 부모 윈도우핸들로 메세지를 전송한다.
	CSocket::OnReceive(nErrorCode);
}

// 소켓이 종료되었을 경우 호출되는 함수 
void CSubNetWallTalk::OnClose(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
    
	CSocket::OnClose(nErrorCode);

    ((CNetWallTalk*)m_pwndParent)->m_wndParent->SendMessage(NET_MSG_CLOSE, WPARAM(nErrorCode), NULL);	// 부모 윈도우 핸들로 메세지를 전송한다.
    ((CNetWallTalk*)m_pwndParent)->SubClose();                                      // 제거 처리를 한다.
}

// 수신한 데이터의 사이즈를 리턴하는 함수 
UINT CNetWallTalk::GetReceiveDataSize()
{
    return m_nReceiveDataSize;
}

// 소켓을 생성하는 부분 
BOOL CNetWallTalk::Create(CWnd *pParentWnd)
{
    if(TRUE == m_bIsServer)                         // 서버모드로 동작중일 경우 
    {    
        if(TRUE == m_bCreated)                      // 이미생성이 되어져 있는 경우에는 
        {
            return FALSE;
        }

        if (!CSocket::Create(m_nSocketPort, SOCK_STREAM))
	    {
//		    AfxMessageBox("Error : Create() in socket");
		    return FALSE;
	    }

	    if (!CSocket::Listen())
	    {
//		    AfxMessageBox("Error : Listen() in socket");
		    return FALSE;
	    }
    }
    else                                            // 클라이언트 모드로 동작중일 경우 
    {
        if(TRUE == m_IsConnected)                   // 이미 연결이 되어 있는 상태라면 
        {
            return FALSE;
        }

        if (!CSocket::Create())
	    {
//		    AfxMessageBox("Error : CSocket::Create() in socket");
		    return FALSE;
	    }

	    if (!CAsyncSocket::Connect(m_szIPAddress, m_nSocketPort))
	    {
            CSocket::Close();
//		    AfxMessageBox("Error : CSocket::Connect() in socket");
		    return FALSE;
	    }
        m_IsConnected = TRUE;           // 클라이언트 모드일 경우에는 이때 연결이 되었다 판단.
    }

    m_wndParent = pParentWnd;
    m_bCreated = TRUE;                  // 소켓이 생성이 되면 True

    return TRUE;
}

// 데이터를 가져가기 위한 함수 
int CNetWallTalk::GetReceiveData(BYTE *pData, UINT nBufSize)
{
    int RetVal;

    if(GetReceiveDataSize() == 0)           // 수신한 데이터가 없는 경우 
    {
        return -1;
    }

    if(nBufSize > GetReceiveDataSize())
    {
        RetVal = (int)GetReceiveDataSize();
    }
    else
    {
        RetVal = (int)nBufSize;
    }
    
    memcpy(pData, m_byteReceiveData, RetVal);
    
    m_nReceiveDataSize = 0;                 // 한번 읽어가면 사이즈를 0으로 초기화 시켜놓는다.

    return RetVal;
}

// 데이터를 전송하는 함수
BOOL CNetWallTalk::SendData(BYTE *pSendData, UINT nDataSize)
{

    if(FALSE == m_IsConnected)              // 연결상태가 아닌 경우는 전송하지 않는다.
    {
        return FALSE;
    }

    if(TRUE == m_bIsServer)                 // 서버모드인경우 
    {
        m_pSubNetWallTalk->SendData(pSendData, nDataSize);
    }
    else                                    // 클라인언트 모드인경우 
    {
        m_nBytesBufferSize = (int)nDataSize;
        m_szSendData = pSendData;
        m_nBytesSent = Send(m_szSendData, m_nBytesBufferSize);
    }
    
    return TRUE;
}

// 서브소켓에서 데이터를 전송하는 함수 
void CSubNetWallTalk::SendData(BYTE *pSendData, UINT nDataSize)
{
    m_nBytesBufferSize = (int)nDataSize;
    m_szSendData = pSendData;
    m_nBytesSent = Send(m_szSendData, m_nBytesBufferSize);
}

// 서브소켓의 전송중에 발행하는 함수 
void CSubNetWallTalk::OnSend(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
    while (m_nBytesSent < m_nBytesBufferSize)
    {
        int dwBytes;

        if ((dwBytes = Send((BYTE*)m_szSendData + m_nBytesSent,
            m_nBytesBufferSize - m_nBytesSent)) == SOCKET_ERROR)
        {
            if (GetLastError() == WSAEWOULDBLOCK) break;
            else
            {
                TCHAR szError[256];
                wsprintf(szError, _T("Server Socket failed to send: %d"), GetLastError());
                Close();
                AfxMessageBox (szError);
            }
        }
        else
        {
            m_nBytesSent += dwBytes;
        }
    }

    if(m_nBytesSent == m_nBytesBufferSize)
    {
        m_nBytesSent = m_nBytesBufferSize = 0;
    }

	CSocket::OnSend(nErrorCode);
}

void CNetWallTalk::OnSend(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	while (m_nBytesSent < m_nBytesBufferSize)
    {
        int dwBytes;

        if ((dwBytes = Send((BYTE*)m_szSendData + m_nBytesSent,
            m_nBytesBufferSize - m_nBytesSent)) == SOCKET_ERROR)
        {
            if (GetLastError() == WSAEWOULDBLOCK) break;
            else
            {
                TCHAR szError[256];
                wsprintf(szError, _T("Server Socket failed to send: %d"), GetLastError());
                Close();
                AfxMessageBox (szError);
            }
        }
        else
        {
            m_nBytesSent += dwBytes;
        }
    }

    if(m_nBytesSent == m_nBytesBufferSize)
    {
        m_nBytesSent = m_nBytesBufferSize = 0;
    }

	CSocket::OnSend(nErrorCode);
}

// 서브소켓을 제거하는 함수 
void CNetWallTalk::SubClose()
{
    delete m_pSubNetWallTalk;
    m_pSubNetWallTalk = NULL;

    m_IsConnected = FALSE;                  // 연결이 끊어졌다고 셋팅한다.
}

// 로컬 아이피를 알아내는 함수 
CString CNetWallTalk::GetLocalIP()
{
    WSADATA wsaData;
    char name[255];

    CString ip; // 여기에 lcoal ip가 저장됩니다.

    PHOSTENT hostinfo;

    if( WSAStartup( MAKEWORD( 2, 0 ), &wsaData ) == 0 )
    {
        if( gethostname ( name, sizeof(name)) == 0)
		{
// 			if ((hostinfo = gethostbyname(name)) != NULL)
// 			{
// 				ip = inet_ntoa(*(struct in_addr *)*hostinfo->h_addr_list);
// 			}

			//20200721 YWCho : 64비트 미지원 함수 대체 
			//gethostbyname -> getaddrinfo
			//inet_ntoa -> inet_ntop
			struct addrinfo * _addrinfo;
			struct addrinfo * _res;
			char _address[INET6_ADDRSTRLEN];
			getaddrinfo(_address, NULL, NULL, &_addrinfo);
			//inet_ntop(AF_INET, &((struct sockaddr_in *)_res->ai_addr)->sin_addr, _address, sizeof(_address));

			for (_res = _addrinfo; _res != NULL; _res = _res->ai_next) {

				if (_res->ai_family == AF_INET) {

					if (NULL == inet_ntop(AF_INET,
						&((struct sockaddr_in *)_res->ai_addr)->sin_addr,
						_address,
						sizeof(_address))
						) {
						perror("inet_ntop");
						return _T("inet_ntop is NULL");
					}

					printf("%s\n", _address);
				}
			}

			WideCharToMultiByte(CP_ACP, 0, ip, -1, _address, 255, NULL, NULL);



// 			struct addrinfo * _addrinfo;
// 			struct addrinfo * _res;
// 			char _address[INET6_ADDRSTRLEN];
// 			int errcode = 0;
// 
// 			if (argc < 2) {
// 				printf("Usage: %s [host]\n", argv[0]);
// 				return EXIT_FAILURE;
// 			}
// 
// 			errcode = getaddrinfo(argv[1], NULL, NULL, &_addrinfo);
// 			if (errcode != 0) {
// 				printf("getaddrinfo: %s\n", gai_strerror(errcode));
// 				return EXIT_FAILURE;
// 			}
// 
// 			for (_res = _addrinfo; _res != NULL; _res = _res->ai_next) {
// 
// 				if (_res->ai_family == AF_INET) {
// 
// 					if (NULL == inet_ntop(AF_INET,
// 						&((struct sockaddr_in *)_res->ai_addr)->sin_addr,
// 						_address,
// 						sizeof(_address))
// 						) {
// 						perror("inet_ntop");
// 						return EXIT_FAILURE;
// 					}
// 
// 					printf("%s\n", _address);
// 				}
// 			}




        }      
        WSACleanup( );
    } 

    return ip;
}

// 소켓이 생성되어 있는 생태
BOOL CNetWallTalk::IsCreated()
{	
    return m_bCreated;
}
// 현재 연결되었는지 검사를 하는 함수 
BOOL CNetWallTalk::IsConnected()
{	
    return m_IsConnected;
}

// 클라이언트의 포트를 알아낸다.
UINT CNetWallTalk::GetClientPort()
{
    UINT RetVal;

    if(TRUE == m_bIsServer)                 // 서버 모드인 경우 
    {
        if(TRUE == m_IsConnected)       // 연결상태일 경우 
        {
            RetVal = GetSocketPort();
        }
        else                            // 연결상태가 아닐경우 
        {
            RetVal = 0;
        }
    }
    else                                    // 클라이언트 모드인 경우 
    {
        RetVal = GetSocketPort();
    }

    return RetVal;
}

// 서버쪽의 포트를 알아낸다.
UINT CNetWallTalk::GetServerPort()
{
    UINT RetVal;

    if(TRUE == m_bIsServer)                 // 서버 모드인 경우 
    {
        RetVal = GetSocketPort();
    }
    else                                    // 클라이언트 모드인 경우 
    {
        if(TRUE == m_IsConnected)       // 연결상태일 경우 
        {
            RetVal = GetSocketPort();
        }
        else                            // 연결상태가 아닐경우 
        {
            RetVal = 0;
        }
    }

    return RetVal;
}

// 클라이언트의 IP어드레스를 알아낸다.
CString CNetWallTalk::GetClientIPAddress()
{

    CString RetVal;

    if(TRUE == m_bIsServer)                 // 서버 모드인 경우 
    {
        if(TRUE == m_IsConnected)       // 연결상태일 경우 
        {
            UINT TempPort;

            m_pSubNetWallTalk->GetPeerName(RetVal, TempPort);
        }
        else                            // 연경 상태가 아닐경우 
        {
            RetVal = "";
        }
    }
    else                                    // 클라이언트 모드인 경우 
    {
        RetVal = GetLocalIP();
    }

    return RetVal;
}

// 서버쪽의 IP어드레스를 알아낸다.
CString CNetWallTalk::GetServerIPAddress()
{
    CString RetVal;

    if(TRUE == m_bIsServer)                 // 서버 모드인 경우 
    {
        RetVal = GetLocalIP();
    }
    else                                    // 클라이언트 모드인 경우 
    {
        if(TRUE == m_IsConnected)       // 연결상태일 경우 
        {
            RetVal = GetIPAddress();
        }
        else                            // 연결 상태가 아닐경우 
        {
            RetVal = "";
        }
    }

    return RetVal;
}

// 서버의 Port를 설정하는 함수 
BOOL CNetWallTalk::SetServerPort(UINT nPort)
{

    return SetSocketPort(nPort);

}

// 서버의 IP어드레스를 설정하는 함수 
BOOL CNetWallTalk::SetServerIPAddress(CString sIPAddress)
{
    return SetIPAddress(sIPAddress);
}

