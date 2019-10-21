#pragma once

#include "NtlPacketCommon.h"
#include "NtlCharacter.h"
#include "NtlSystemTool.h"
#include "NtlAdmin.h"


enum eOPCODE_MS
{
	MS_OPCODE_BEGIN = 24000,

	MS_HEARTBEAT = MS_OPCODE_BEGIN,

	MS_LOGIN_RES,					// �α��� ��û ����
	MS_CHANGE_PASSWORD_RES,			// �н����� ���� ����

	MS_SERVER_STATUS_RES,			// ���� ���� ����
	MS_SERVER_CONTROL_TURN_ON_RES,	// ���� ���� ��û ����
	MS_SERVER_CONTROL_TURN_OFF_RES,	// ���� ���� ��û ����

	MS_OPCODE_DUMMY,
	MS_OPCODE_END = MS_OPCODE_DUMMY - 1
};


//------------------------------------------------------------------
//
//------------------------------------------------------------------
const char * NtlGetPacketName_MS(WORD wOpCode);
//------------------------------------------------------------------


#pragma pack(1)

//------------------------------------------------------------------
BEGIN_PROTOCOL(MS_HEARTBEAT)
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(MS_LOGIN_RES)
	WORD					wResultCode;								// ���

	ACCOUNTID				gmAccountID;								// GM Account ID
	WCHAR					wszUser[NTL_MAX_SIZE_USERID_UNICODE + 1];	// ID
	DWORD					dwGroupSerial;								// Group Serial
	ACCOUNTID				accountID;									// Account ID(���ӿ��� ���)
	WORD					wKaioshinVersion;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(MS_CHANGE_PASSWORD_RES)
	WORD					wResultCode;								// ���

	WCHAR					wszUserID[NTL_MAX_SIZE_USERID_UNICODE + 1];	// �н����带 ������ ID
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(MS_SERVER_STATUS_RES)
	WORD					wResultCode;

	WORD					wCount;
	sSERVERSTATUS_ENTITY	aServerStatusList[1];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(MS_SERVER_CONTROL_TURN_ON_RES)
	WORD					wResultCode;

	BYTE				byServerType;
	SERVERFARMID			serverFarmId;
	BYTE					byServerChannelIndex;
	BYTE					byServerIndex;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(MS_SERVER_CONTROL_TURN_OFF_RES)
	WORD					wResultCode;

	BYTE				byServerType;
	SERVERFARMID			serverFarmId;
	BYTE					byServerChannelIndex;
	BYTE					byServerIndex;
END_PROTOCOL()
//------------------------------------------------------------------
#pragma pack()