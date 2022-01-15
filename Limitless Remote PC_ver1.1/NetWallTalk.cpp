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

// ������ �ʱ⿡�� ����Ʈ������ ������ �Ѵ�.
CNetWallTalk::CNetWallTalk()
{   
    m_bIsServer = TRUE;                                                         // �⺻�� ������ ��Ѵ�.
    m_byteReceiveData = new BYTE[NET_MAX_RECEIVE_SIZE];                         // ���۸� �ʱ�ȭ �Ѵ�.
    m_nSocketPort = NET_DEFAULT_SOCKET_PORT;                                    // �⺻ ������Ʈ�� �ʱ�ȭ �Ѵ�.
    m_szIPAddress = NET_DEFAULT_SOCKET_IP;                                      // �⺻ IP��巹���� �ʱ�ȭ �Ѵ�.
    m_wndParent = NULL;                                                         // �⺻ �θ�Ŭ������ �ʱ�ȭ �Ѵ�.

    m_pSubNetWallTalk = NULL;                                                   // ��������϶� ������ �Ǵ� ����Ŭ���� 
    m_nReceiveDataSize = 0;                                                     // ������ �������� ������ 

    m_IsConnected = FALSE;                                                      // �ʱ��� ������¸� False�� �����Ѵ�.
    m_bCreated = FALSE;                                                         // ������ �����Ǿ����� �˷��ִ� ���� 
	Sleep(50);
}

// ������ �ʱⰪ�� �Է��Ҽ� �ִ�.
CNetWallTalk::CNetWallTalk(BOOL bServer, UINT nPort, CString szIPAddress)
{
    m_bIsServer = bServer;                                                      // ���带 �����Ѵ�.
    m_byteReceiveData = new BYTE[NET_MAX_RECEIVE_SIZE];                         // ���Ź��۸� �ʱ�ȭ �Ѵ�.
    m_nSocketPort = nPort;                                                      // ��Ʈ�� �ʱ�ȭ �Ѵ�.
    m_szIPAddress = szIPAddress;                                                // IP�ּҸ� �ʱ�ȭ �Ѵ�.
    m_wndParent = NULL;                                                         // �⺻ �θ�Ŭ������ �ʱ�ȭ �Ѵ�.

    m_pSubNetWallTalk = NULL;                                                   // ���� ����϶� ������ �Ǵ� ����Ŭ���� 
    m_nReceiveDataSize = 0;                                                     // ������ �������� ������ 

    m_IsConnected = FALSE;                                                      // �ʱ��� ������¸� False�� �����Ѵ�.
    m_bCreated = FALSE;                                                         // ������ �����Ǿ����� �˷��ִ� ���� 
	Sleep(50);
}

CNetWallTalk::~CNetWallTalk()
{
    delete [] m_byteReceiveData;                                                   // ���Ź��۸� �����.

    if(TRUE == m_IsConnected)               // ��������� ��� 
    {
        if(TRUE == m_bIsServer)             // ���� ����� ��� 
        {
            SubClose();                 // ��������� ���Ḧ �����Ѵ�.                      
        }
        else                                // Ŭ���̾�Ʈ ����� ��� 
        {
            // Ư���� �������� ���׿�...
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

// ������ ��Ʈ�� �����ϴ� �Լ� 
BOOL CNetWallTalk::SetSocketPort(UINT nSocketPort)
{

    if(TRUE == m_bIsServer)           // ���� ����� ��� 
    {
        //
        // ������ ��� CSocket::Create()�� ��Ʈ�� �����ϱ� ������ 
        // 
        //
        if(TRUE == m_bCreated)                      // �̹� ������ ������ �Ǿ� �ִ� ��쿡�� 
        {
            return FALSE;
        }
    }
    else                            // Ŭ���̾�Ʈ ����� ��� 
    {
        //
        // Ŭ���̾�Ʈ�� ��� CSocket::Create()�ÿ��� �����ϴ� ���� ����
        // CSocket::Connect()�Ҷ� ��Ʈ�� �����Ѵ�.
        //
        if(TRUE == m_IsConnected)
        {
            return FALSE;
        }
    }

    m_nSocketPort = nSocketPort;

    return TRUE;
}

// ������ ���� ��� �Լ� 
UINT CNetWallTalk::GetSocketPort()
{
    return m_nSocketPort;
}

void CNetWallTalk::SetSAction(BOOL bSet)													// ���� ���� ����.
{
	m_pSubNetWallTalk->SetServerAction = bSet;
}

// �����ϴ� ��带 �ٲٴ� �Լ� 
// ������ ������ �Ǿ����� ���� �ٲپ� �־�� �Ѵ�.
BOOL CNetWallTalk::SetModeChange(BOOL bIsServer)
{
    if(TRUE == m_bCreated)                      // �̹� ������ ������ �Ǿ� �ִ� �����ΰ�� 
    {
        return FALSE;
    }

    m_bIsServer = bIsServer;                    // ��带 �����Ѵ�. TRUE = �������                   
                                                //                  FALSE = Ŭ���̾�Ʈ ��� 
    return TRUE;
}

// IP��巹���� �����ϴ� �Լ� 
BOOL CNetWallTalk::SetIPAddress(CString szIPAddress)
{

    if(TRUE == m_bIsServer)           // ���� ����� ��� 
    {
        if(TRUE == m_bCreated)                      // �̹� ������ ������ �Ǿ� �ִ� ��쿡�� 
        {
            return FALSE;
        }
    }
    else                            // Ŭ���̾�Ʈ ����� ��� 
    {
        if(TRUE == m_IsConnected)                   // �̹� ������ �Ǿ� �ִ� ��� 
        {
            return FALSE;
        }
    }
    

    m_szIPAddress = szIPAddress;

    return TRUE;
}

// IP��巹���� �����ϴ� �Լ� 
CString CNetWallTalk::GetIPAddress()
{
    return m_szIPAddress;
}

// ��������϶��� �߻��ϴ� �Լ� 
void CNetWallTalk::OnAccept(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
    if(NULL == m_pSubNetWallTalk)               // ����Ǿ��� ������ ���� ��� 
    {
        m_pSubNetWallTalk = new CSubNetWallTalk(this, m_byteReceiveData, &m_nReceiveDataSize);
    
	    if(!CSocket::Accept(*m_pSubNetWallTalk))                    // ��������� ���ῡ �����Ͽ��� ��� 
	    {
            AfxMessageBox(_T("Error : Accept() in socket"));
            delete m_pSubNetWallTalk;
		    m_pSubNetWallTalk = NULL;
            return;
	    }
        else
        {
            m_IsConnected = TRUE;                       // ���� ����� ��쿡�� �̶��� ������ �Ǿ��ٰ� �Ǵ�.
	        m_wndParent->SendMessage(NET_MSG_ACCEPT, WPARAM(nErrorCode), NULL);                 // ��������� �������� �˸�    
     }

        CSocket::OnAccept(nErrorCode);
    }
    else                                // �̹� ����Ǿ��� ������ �ִ� ��� 
    {
        CSubNetWallTalk *SubNetWallTalk = new CSubNetWallTalk(this, m_byteReceiveData, &m_nReceiveDataSize);

        if(!CSocket::Accept(*SubNetWallTalk))                    // ��������� ���ῡ �����Ͽ��� ��� 
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
// Ŭ���̾�Ʈ ��忡�� �߻��� �Ǿ����� �Լ� 
void CNetWallTalk::OnClose(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CSocket::OnClose(nErrorCode);

    m_IsConnected = FALSE;                              // ������ �������� False�� �����Ѵ�.
	SetAction = TRUE;
    m_wndParent->SendMessage(NET_MSG_CLOSE, WPARAM(nErrorCode), NULL);                  // ������ ����Ǿ��ٰ� �˸�
	CSocket::OnClose(nErrorCode);
}

// Ŭ���̾�Ʈ�� ������ �Ǿ��� ��쿡�� �߻��ϴ� �Լ� 
void CNetWallTalk::OnReceive(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	m_nReceiveDataSize = (UINT)Receive(m_byteReceiveData, NET_MAX_RECEIVE_SIZE);        // �����͸� �����Ѵ�
	SetClientAction = TRUE;
	SetAction = TRUE;

    m_wndParent->PostMessage(NET_MSG_RECEIVE, WPARAM(nErrorCode), NULL);                // �����͸� �����ߴٰ� �˸�
       
	CSocket::OnReceive(nErrorCode);
}

BOOL CNetWallTalk::GetServerAction()
{
	BOOL bRet = FALSE;

    if(FALSE == m_IsConnected)              // ������°� �ƴ� ���� �������� �ʴ´�.
    {
        return FALSE;
    }
	bRet = m_pSubNetWallTalk->SetServerAction;

	return bRet;
}
/////////////////////////////////////////////////////////////////////////////
// CSubNetWallTalk

// ������ 
CSubNetWallTalk::CSubNetWallTalk(CSocket *pwndParant, BYTE* pReceiveDataPtr, UINT* pReceiveDataSize)
{
    m_pwndParent = pwndParant;                                                  // �θ�Ŭ������ �ڵ��� �����´�.
    m_pReceiveData = pReceiveDataPtr;                                           // ������ ������ �����͸� �����Ѵ�.
    m_pReceiveDataSize = pReceiveDataSize;                                      // ������ �����ͻ���� ������ ���������� 
}

// �Ҹ��� 
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

// �����Ͱ� ���ŵǾ��� ��쿡 ȣ���ϴ� �Լ�
void CSubNetWallTalk::OnReceive(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	*m_pReceiveDataSize = (UINT)Receive(m_pReceiveData, NET_MAX_RECEIVE_SIZE);      // �����͸� �����Ѵ�.

	SetServerAction = TRUE;
	((CNetWallTalk*)m_pwndParent)->SetSAction(SetServerAction);
    ((CNetWallTalk*)m_pwndParent)->m_wndParent->SendMessage(NET_MSG_RECEIVE_SERVER, WPARAM(nErrorCode), NULL);
                                                                                   // �θ� �������ڵ�� �޼����� �����Ѵ�.
	CSocket::OnReceive(nErrorCode);
}

// ������ ����Ǿ��� ��� ȣ��Ǵ� �Լ� 
void CSubNetWallTalk::OnClose(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
    
	CSocket::OnClose(nErrorCode);

    ((CNetWallTalk*)m_pwndParent)->m_wndParent->SendMessage(NET_MSG_CLOSE, WPARAM(nErrorCode), NULL);	// �θ� ������ �ڵ�� �޼����� �����Ѵ�.
    ((CNetWallTalk*)m_pwndParent)->SubClose();                                      // ���� ó���� �Ѵ�.
}

// ������ �������� ����� �����ϴ� �Լ� 
UINT CNetWallTalk::GetReceiveDataSize()
{
    return m_nReceiveDataSize;
}

// ������ �����ϴ� �κ� 
BOOL CNetWallTalk::Create(CWnd *pParentWnd)
{
    if(TRUE == m_bIsServer)                         // �������� �������� ��� 
    {    
        if(TRUE == m_bCreated)                      // �̹̻����� �Ǿ��� �ִ� ��쿡�� 
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
    else                                            // Ŭ���̾�Ʈ ���� �������� ��� 
    {
        if(TRUE == m_IsConnected)                   // �̹� ������ �Ǿ� �ִ� ���¶�� 
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
        m_IsConnected = TRUE;           // Ŭ���̾�Ʈ ����� ��쿡�� �̶� ������ �Ǿ��� �Ǵ�.
    }

    m_wndParent = pParentWnd;
    m_bCreated = TRUE;                  // ������ ������ �Ǹ� True

    return TRUE;
}

// �����͸� �������� ���� �Լ� 
int CNetWallTalk::GetReceiveData(BYTE *pData, UINT nBufSize)
{
    int RetVal;

    if(GetReceiveDataSize() == 0)           // ������ �����Ͱ� ���� ��� 
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
    
    m_nReceiveDataSize = 0;                 // �ѹ� �о�� ����� 0���� �ʱ�ȭ ���ѳ��´�.

    return RetVal;
}

// �����͸� �����ϴ� �Լ�
BOOL CNetWallTalk::SendData(BYTE *pSendData, UINT nDataSize)
{

    if(FALSE == m_IsConnected)              // ������°� �ƴ� ���� �������� �ʴ´�.
    {
        return FALSE;
    }

    if(TRUE == m_bIsServer)                 // ��������ΰ�� 
    {
        m_pSubNetWallTalk->SendData(pSendData, nDataSize);
    }
    else                                    // Ŭ���ξ�Ʈ ����ΰ�� 
    {
        m_nBytesBufferSize = (int)nDataSize;
        m_szSendData = pSendData;
        m_nBytesSent = Send(m_szSendData, m_nBytesBufferSize);
    }
    
    return TRUE;
}

// ������Ͽ��� �����͸� �����ϴ� �Լ� 
void CSubNetWallTalk::SendData(BYTE *pSendData, UINT nDataSize)
{
    m_nBytesBufferSize = (int)nDataSize;
    m_szSendData = pSendData;
    m_nBytesSent = Send(m_szSendData, m_nBytesBufferSize);
}

// ��������� �����߿� �����ϴ� �Լ� 
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

// ��������� �����ϴ� �Լ� 
void CNetWallTalk::SubClose()
{
    delete m_pSubNetWallTalk;
    m_pSubNetWallTalk = NULL;

    m_IsConnected = FALSE;                  // ������ �������ٰ� �����Ѵ�.
}

// ���� �����Ǹ� �˾Ƴ��� �Լ� 
CString CNetWallTalk::GetLocalIP()
{
    WSADATA wsaData;
    char name[255];

    CString ip; // ���⿡ lcoal ip�� ����˴ϴ�.

    PHOSTENT hostinfo;

    if( WSAStartup( MAKEWORD( 2, 0 ), &wsaData ) == 0 )
    {
        if( gethostname ( name, sizeof(name)) == 0)
		{
// 			if ((hostinfo = gethostbyname(name)) != NULL)
// 			{
// 				ip = inet_ntoa(*(struct in_addr *)*hostinfo->h_addr_list);
// 			}

			//20200721 YWCho : 64��Ʈ ������ �Լ� ��ü 
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

// ������ �����Ǿ� �ִ� ����
BOOL CNetWallTalk::IsCreated()
{	
    return m_bCreated;
}
// ���� ����Ǿ����� �˻縦 �ϴ� �Լ� 
BOOL CNetWallTalk::IsConnected()
{	
    return m_IsConnected;
}

// Ŭ���̾�Ʈ�� ��Ʈ�� �˾Ƴ���.
UINT CNetWallTalk::GetClientPort()
{
    UINT RetVal;

    if(TRUE == m_bIsServer)                 // ���� ����� ��� 
    {
        if(TRUE == m_IsConnected)       // ��������� ��� 
        {
            RetVal = GetSocketPort();
        }
        else                            // ������°� �ƴҰ�� 
        {
            RetVal = 0;
        }
    }
    else                                    // Ŭ���̾�Ʈ ����� ��� 
    {
        RetVal = GetSocketPort();
    }

    return RetVal;
}

// �������� ��Ʈ�� �˾Ƴ���.
UINT CNetWallTalk::GetServerPort()
{
    UINT RetVal;

    if(TRUE == m_bIsServer)                 // ���� ����� ��� 
    {
        RetVal = GetSocketPort();
    }
    else                                    // Ŭ���̾�Ʈ ����� ��� 
    {
        if(TRUE == m_IsConnected)       // ��������� ��� 
        {
            RetVal = GetSocketPort();
        }
        else                            // ������°� �ƴҰ�� 
        {
            RetVal = 0;
        }
    }

    return RetVal;
}

// Ŭ���̾�Ʈ�� IP��巹���� �˾Ƴ���.
CString CNetWallTalk::GetClientIPAddress()
{

    CString RetVal;

    if(TRUE == m_bIsServer)                 // ���� ����� ��� 
    {
        if(TRUE == m_IsConnected)       // ��������� ��� 
        {
            UINT TempPort;

            m_pSubNetWallTalk->GetPeerName(RetVal, TempPort);
        }
        else                            // ���� ���°� �ƴҰ�� 
        {
            RetVal = "";
        }
    }
    else                                    // Ŭ���̾�Ʈ ����� ��� 
    {
        RetVal = GetLocalIP();
    }

    return RetVal;
}

// �������� IP��巹���� �˾Ƴ���.
CString CNetWallTalk::GetServerIPAddress()
{
    CString RetVal;

    if(TRUE == m_bIsServer)                 // ���� ����� ��� 
    {
        RetVal = GetLocalIP();
    }
    else                                    // Ŭ���̾�Ʈ ����� ��� 
    {
        if(TRUE == m_IsConnected)       // ��������� ��� 
        {
            RetVal = GetIPAddress();
        }
        else                            // ���� ���°� �ƴҰ�� 
        {
            RetVal = "";
        }
    }

    return RetVal;
}

// ������ Port�� �����ϴ� �Լ� 
BOOL CNetWallTalk::SetServerPort(UINT nPort)
{

    return SetSocketPort(nPort);

}

// ������ IP��巹���� �����ϴ� �Լ� 
BOOL CNetWallTalk::SetServerIPAddress(CString sIPAddress)
{
    return SetIPAddress(sIPAddress);
}

