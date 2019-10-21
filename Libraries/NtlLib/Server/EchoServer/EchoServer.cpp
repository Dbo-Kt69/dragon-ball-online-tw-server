// EchoServer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "NtlSfx.h"
#include "Protocol.h"

#include <iostream>
#include <map>
#include <list>

using namespace std;


enum APP_LOG
{
	PRINT_APP = 2,
};


// ���� Ÿ�� ����
enum SAMPLE_SESSION
{
	SESSION_CLIENT,
};


// ���� ���� ����
struct sSERVERCONFIG
{
	CNtlString		strClientAcceptAddr;
	WORD			wClientAcceptPort;
};


//-----------------------------------------------------------------------------------
//		���ӵǴ� Ŭ���̾�Ʈ ���� Ŭ����
//-----------------------------------------------------------------------------------
class CClientSession : public CNtlSession
{
public:

	CClientSession(SESSIONTYPE sessionType);

	~CClientSession();

	DWORD			GetAliveCheckTime() { return 5000; }

	void OnDispatch(CNtlPacket * pPacket);


private:

	CNtlString			m_strUserID;

};


//-----------------------------------------------------------------------------------
//		���� ���� ���� ���丮
//-----------------------------------------------------------------------------------
class CEchoSessionFactory : public CNtlSessionFactory
{
public:

	CNtlSession * CreateSession(SESSIONTYPE sessionType)
	{
		CNtlSession * pSession = NULL;
		switch( sessionType )
		{
		case SESSION_CLIENT: 
			{
				pSession = new CClientSession( sessionType );
			}
			break;

		default:
			break;
		}

		return pSession;
	}



	void DestroySession(CNtlSession * pSession)
	{
		switch( pSession->GetSessionType() )
		{
		case SESSION_CLIENT: 
			{
				SAFE_DELETE( pSession );
			}
			break;

		default:
			break;
		}
	}
};


//-----------------------------------------------------------------------------------
//		���� ���� �Ŵ���
//-----------------------------------------------------------------------------------
class CEchoSessionManager : public CNtlSessionManager
{
public:
	CEchoSessionManager()
		:CNtlSessionManager(100) {}	// �ִ� session �� 

};


//-----------------------------------------------------------------------------------
//		���� ���� ���ø����̼�
//-----------------------------------------------------------------------------------
class CEchoServer : public CNtlServerApp
{
public:

	int					OnInitApp()
	{
		m_pSessionFactory = new CEchoSessionFactory;
		m_pSessionManager = new CEchoSessionManager;

		return NTL_SUCCESS;
	}


	int					OnCreate()
	{
		int rc = 0;

		rc = m_clientAcceptor.Create( &m_network, m_config.strClientAcceptAddr, m_config.wClientAcceptPort, SESSION_CLIENT, 10, 5, 2);
		if( NTL_SUCCESS != rc )
		{
			return rc;
		}

		rc = m_network.Associate( &m_clientAcceptor );
		if( NTL_SUCCESS != rc )
		{
			return rc;
		}

		return NTL_SUCCESS;

	}


	void				OnDestroy()
	{
		SAFE_DELETE( m_pSessionFactory );
		SAFE_DELETE( m_pSessionManager );
	}


	int					OnCommandArgument(int argc, _TCHAR* argv[])
	{
		// �ʿ�� Argument �Ľ�
		return NTL_SUCCESS;
	}


	int					OnConfiguration(const char * lpszConfigFile)
	{
		CNtlIniFile file;

		int rc = file.Create( lpszConfigFile );
		if( NTL_SUCCESS != rc )
		{
			return rc;
		}


		if( !file.Read("Client Accept", "Address", m_config.strClientAcceptAddr) )
		{
			return NTL_ERR_SYS_CONFIG_FILE_READ_FAIL;
		}


		if( !file.Read("Client Accept", "Port",  m_config.wClientAcceptPort) )
		{
			return NTL_ERR_SYS_CONFIG_FILE_READ_FAIL;
		}

		return NTL_SUCCESS;
	}


	int					OnAppStart()
	{
		return NTL_SUCCESS;
	}


	void				Run()
	{
		DWORD dwTickCur, dwTickOld = ::GetTickCount();

		while( IsRunnable() )
		{		
			dwTickCur = ::GetTickCount();
			if( dwTickCur - dwTickOld >= 10000 )
			{
				NTL_PRINT(PRINT_APP, "EchoServer Run()");
				dwTickOld = dwTickCur;
			}
		}
	}


private:


	CNtlAcceptor				m_clientAcceptor;

	CNtlLog  					m_log;

	sSERVERCONFIG				m_config;



public:

	bool						Add(HSESSION hSession)
	{
		if( Find( hSession ) )
			return false;

		m_sessionList.push_back( hSession );

		return true;		
	}

	void						Remove(HSESSION hSession)
	{
		for(SESSIONIT it = m_sessionList.begin(); it != m_sessionList.end(); it++ )
		{
			if( hSession == *it )
			{
				m_sessionList.erase( it );
				break;
			}
		}
	}

	bool						Find(HSESSION hSession)
	{
		for(SESSIONIT it = m_sessionList.begin(); it != m_sessionList.end(); it++ )
		{
			if( hSession == *it )
			{
				return true;
			}
		}

		return false;
	}

	void						Broadcast(CNtlPacket * pPacket)
	{
		for( SESSIONIT it = m_sessionList.begin(); it != m_sessionList.end(); it++ )
		{
			Send( *it, pPacket );
		}
	}

	int							GetSessionCount() { return (int) m_sessionList.size(); }



private:

	typedef std::list<HSESSION> SESSIONLIST;
	typedef SESSIONLIST::iterator SESSIONIT;

	SESSIONLIST				m_sessionList;

};



//-----------------------------------------------------------------------------------
//		Ŭ���̾�Ʈ �Ҹ�
//-----------------------------------------------------------------------------------
CClientSession::CClientSession(SESSIONTYPE sessionType)
:CNtlSession(sessionType)
{
	NTL_PRINT(PRINT_APP, "CServerPassiveSession Constructor Called");
	m_bAliveCheck = false;
}

//-----------------------------------------------------------------------------------
//		Ŭ���̾�Ʈ �Ҹ�
//-----------------------------------------------------------------------------------
CClientSession::~CClientSession()
{
	NTL_PRINT(PRINT_APP, "CClientSession Destructor Called");

	CEchoServer * app = (CEchoServer*) NtlSfxGetApp();
	app->Remove( this->m_hSession );
}


//-----------------------------------------------------------------------------------
//		���� Ŭ���̾�Ʈ ����ġ
//-----------------------------------------------------------------------------------
inline void CClientSession::OnDispatch(CNtlPacket * pPacket)
{
	CEchoServer * app = (CEchoServer*) NtlSfxGetApp();

	mSAMPLE_PROTOCOL_HEADER * pHeader = (mSAMPLE_PROTOCOL_HEADER *) pPacket->GetPacketData();
	switch( pHeader->wProtocolID )
	{
	case SYSTEM_ALIVE:
		{
			this->m_dwAliveTime = 0;
		}
		break;

	case SYSTEM_PING:
		{

		}
		break;

	case SYSTEM_ECHO:
		{
			NTL_PRINT(PRINT_APP, "Client Send SYSTEM_ECHO" );

			mSYSTEM_ECHO * req = (mSYSTEM_ECHO *) pPacket->GetPacketData();

			req->dwParam = app->GetSessionCount();

			CNtlPacket packet( *pPacket );

			if( req->byEchoType )
			{
				app->Send( this->GetHandle(), &packet );
				app->Broadcast( &packet );
			}
			else
			{
				app->Send( this->GetHandle(), &packet );
			}
		}
		break;

	case CS_USER_JOIN_REQ:
		{
			NTL_PRINT(PRINT_APP, "Client Send CS_USER_JOIN_REQ" );

			app->Add( this->GetHandle() );

			CNtlPacket packet( sizeof(mCS_USER_JOIN_RES) );
			mCS_USER_JOIN_RES * res = (mCS_USER_JOIN_RES *) packet.GetPacketData();
			res->wProtocolID = CS_USER_JOIN_RES;

			packet.SetPacketLen( sizeof(mCS_USER_JOIN_RES) );
			app->Send( this->GetHandle(), &packet );
		}
		break;
	
	}
}


//-----------------------------------------------------------------------------------
//		���� ���� ����
//-----------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	NtlSetPrintFlag( PRINT_APP );

	CEchoServer app;

	int rc = app.Create(argc, argv);
	if( NTL_SUCCESS != rc )
	{
		NTL_PRINT(PRINT_APP, "Server Application Create Fail %d(%s)", rc, NtlGetErrorMessage(rc) );
		return rc;
	}

	app.Start();

	app.WaitForTerminate();

	return 0;
}
