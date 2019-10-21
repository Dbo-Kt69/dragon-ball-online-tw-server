#pragma once

#include "NtlPacketCommon.h"
#include "NtlAdmin.h"
#include "NtlSystemTool.h"
#include "NtlItem.h"


enum eOPCODE_SM
{
	SM_OPCODE_BEGIN = 21000,

	SM_NOTIFY_SERVER_BEGIN = SM_OPCODE_BEGIN,
	SM_HEARTBEAT,

	SM_LOGIN_REQ,						// �α��� ��û
	SM_CHANGE_PASSWORD_REQ,				// �н����� ���� ��û

	SM_SERVER_STATUS_REQ,				// ���� ���� ��û

	SM_SERVER_CONTROL_TURN_ON_REQ,		// ���� ���μ��� ���� ��û
	SM_SERVER_CONTROL_TURN_OFF_REQ,		// ���� ���μ��� ���� ��û

	SM_OPCODE_DUMMY,
	SM_OPCODE_END = SM_OPCODE_DUMMY - 1
};


//------------------------------------------------------------------
//
//------------------------------------------------------------------
const char * NtlGetPacketName_SM(WORD wOpCode);
//------------------------------------------------------------------


#pragma pack(1)

//------------------------------------------------------------------
BEGIN_PROTOCOL(SM_NOTIFY_SERVER_BEGIN)
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(SM_HEARTBEAT)
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(SM_LOGIN_REQ)
	WCHAR			wszUserID[NTL_MAX_SIZE_USERID_UNICODE + 1];
	WCHAR			wszUserPWD[NTL_MAX_SIZE_USERPW_UNICODE + 1];
	WORD			wKaioshinVersion;
	
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(SM_CHANGE_PASSWORD_REQ)
	WCHAR			wszUserID[NTL_MAX_SIZE_USERID_UNICODE + 1];		// ������ ID
	WCHAR			wszCurPWD[NTL_MAX_SIZE_USERPW_UNICODE + 1];		// ���� �н�����
	WCHAR			wszNewPWD[NTL_MAX_SIZE_USERPW_UNICODE + 1];		// ������ �н�����
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(SM_SERVER_STATUS_REQ)
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(SM_SERVER_CONTROL_TURN_ON_REQ)
	BYTE				byServerType;
	SERVERFARMID		serverFarmId;
	BYTE				byServerChannelIndex;
	BYTE				byServerIndex;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(SM_SERVER_CONTROL_TURN_OFF_REQ)
	BYTE				byServerType;
	SERVERFARMID		serverFarmId;
	BYTE				byServerChannelIndex;
	BYTE				byServerIndex;
END_PROTOCOL()
//------------------------------------------------------------------
#pragma pack()