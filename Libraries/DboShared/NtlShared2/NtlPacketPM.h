#pragma once

#include "NtlPacketCommon.h"

enum eOPCODE_PM
{
	PM_OPCODE_BEGIN = 21000,

	PM_NOTIFY_SERVER_BEGIN = PM_OPCODE_BEGIN,
	PM_HEARTBEAT,

	PM_SERVERFARM_NAME_REQ,				// ������ �̸� ��û

	PM_SERVER_CONTROL_TURN_ON_REQ,		// ���� ���μ��� ���� ��û
	PM_SERVER_CONTROL_TURN_OFF_REQ,		// ���� ���μ��� ���� ��û
	PM_SERVER_LOCK_REQ,					// ����/������/���� ä�� ��� ���� ��û
	PM_SERVER_UNLOCK_REQ,				// ����/������/���� ä�� ��� ���� ��û
	PM_SERVER_USER_ALL_KICK_REQ,		// ���� ���� ������� ���� logout
	PM_SERVER_AGENT_PATCH_REQ,			// Server Agent ��ġ�� ��û
	PM_SERVER_COMMAND_REQ,				// server command
	PM_SERVER_CONTROL_TURN_OFF_ALL_NFY,
	PM_REPORT_LOAD,
	PM_SERVER_STATUS_LOCALSETTING_INFO_REQ,
	PM_SERVER_STATUS_LOCALSETTING_EDIT_REQ,
	
	PM_PING_REQ, // by itzrnb 08/05/2009

	PM_OPCODE_DUMMY,
	PM_OPCODE_END = PM_OPCODE_DUMMY - 1
};

//------------------------------------------------------------------
//
//------------------------------------------------------------------
const char * NtlGetPacketName_PM(WORD wOpCode);
//------------------------------------------------------------------

#pragma pack(1)

//------------------------------------------------------------------
BEGIN_PROTOCOL(PM_NOTIFY_SERVER_BEGIN)
DWORD				dwMaxLoad;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(PM_HEARTBEAT)
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(PM_SERVERFARM_NAME_REQ)
ACCOUNTID			gmAccountId;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(PM_SERVER_CONTROL_TURN_ON_REQ)
ACCOUNTID			gmAccountId;
BYTE				byServerType;
SERVERFARMID		serverFarmId;
BYTE				byServerChannelIndex;
BYTE				byServerIndex;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(PM_SERVER_CONTROL_TURN_OFF_REQ)
ACCOUNTID			gmAccountId;
BYTE				byServerType;
SERVERFARMID		serverFarmId;
BYTE				byServerChannelIndex;
BYTE				byServerIndex;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(PM_SERVER_LOCK_REQ)
ACCOUNTID			gmAccountId;
BYTE				byServerType;
SERVERFARMID		serverFarmId;
BYTE				byServerChannelIndex;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(PM_SERVER_UNLOCK_REQ)
ACCOUNTID			gmAccountId;
BYTE				byServerType;
SERVERFARMID		serverFarmId;
BYTE				byServerChannelIndex;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(PM_SERVER_USER_ALL_KICK_REQ)
GMACCOUNTID			gmAccountId;
BYTE				byServerType;
SERVERFARMID		serverFarmId;
BYTE				byServerChannelIndex;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(PM_SERVER_AGENT_PATCH_REQ)
GMACCOUNTID			gmAccountId;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(PM_SERVER_COMMAND_REQ)
ACCOUNTID			managerID;		      // GM ID
BYTE				byServerType; // eNtlServerType
SERVERFARMID		serverfarmID;
SERVERCHANNELID		serverchannelID;
SERVERINDEX			serverIndex;
WORD				wMessageLengthInUnicode;
WCHAR				awchCommand[NTL_MAX_LENGTH_OF_CHAT_MESSAGE_UNICODE + 1];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(PM_SERVER_CONTROL_TURN_OFF_ALL_NFY)
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(PM_REPORT_LOAD)
DWORD		dwProcessUsage;			// Process Usage
DWORD		dwSystemUsage;			// System Usage
DWORD		dwMemoryUsage;			// Memory Usage
DWORD		dwPing;					// by itzrnb 08/05/2009
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(PM_SERVER_STATUS_LOCALSETTING_INFO_REQ)
ACCOUNTID			managerID;		      // GM ID
BYTE				byServerType; // eNtlServerType
SERVERFARMID		serverfarmID;
SERVERCHANNELID		serverchannelID;
SERVERINDEX			serverIndex;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(PM_SERVER_STATUS_LOCALSETTING_EDIT_REQ)
ACCOUNTID			managerID;		      // GM ID
BYTE				byServerType; // eNtlServerType
SERVERFARMID		serverfarmID;
SERVERCHANNELID		serverchannelID;
SERVERINDEX			serverIndex;
int					nFileLength;
char				szFileContent[NTL_MAX_SIZE_LOCALSETTING_FILE + 1];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(PM_PING_REQ)
DWORD				dwTick;
END_PROTOCOL()
//------------------------------------------------------------------

#pragma pack()