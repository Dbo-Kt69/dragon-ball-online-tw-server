#pragma once

#include "NtlPacketCommon.h"
#include "NtlAdmin.h"
#include "NtlSystemTool.h"
#include "NtlItem.h"
#include "NtlGuild.h"
#include "NtlPetition.h"
#include "NtlReport.h"

enum eOPCODE_SP
{
	SP_OPCODE_BEGIN = 61500,

	SP_HEARTBEAT = SP_OPCODE_BEGIN,

	SP_NOTIFY_SERVER_BEGIN,

	SP_LOGIN_REQ,						// �α��� ��û
	SP_CHANGE_PASSWORD_REQ,				// �н����� ���� ��û

	SP_SERVERFARM_NAME_REQ,				// ������ �̸� ��û

	SP_SEARCH_PC_DATA_REQ,				// ĳ���� �˻�
	SP_PC_DATA_REQ,						// ĳ���� ���� ��û

	SP_CHARACTER_LOGIN_INFO_REQ,		// �α��� ���� ��û
	SP_CHARACTER_KICK_INFO_REQ,			// ű ���� ��û
	SP_CHARACTER_KICK_REQ,				// ĳ���͸� ű ��Ų��. (���� ���)
	SP_CHARACTER_CHANGE_NAME_REQ,		// ĳ������ �̸��� ����
	SP_CHAR_CHANGE_BIND_LOCATION_REQ,	// ���ε� ��ġ ����
	SP_CHAR_CHANGE_CUR_LOCATION_REQ,	// ���� ��ġ ����
	SP_CHARNAME_MODIFY_GMTOOL_REQ,		// [5/22/2007 SGpro]

	SP_SKILL_DELETE_REQ,				// ��ų ����
	SP_HTB_SKILL_DELETE_REQ,			// HTB ��ų ����
	SP_BUFF_DELETE_REQ,					// ���� ����

	SP_ITEM_CREATE_REQ,					// ������ ����
	SP_ITEM_DELETE_REQ,					// ������ ����
	SP_ITEM_CHANGE_INFO_REQ,			// ������ ���� ����

	SP_PUNISHMENT_INFO_REQ,				// ���� ����
	SP_PUNISHMENT_REQ,					// ����� ����

	SP_REPEAT_NOTICE_LIST_REQ,			// ����Ʈ ��û
	SP_REPEAT_NOTICE_ADD_REQ,			// ���� �߰�
	SP_REPEAT_NOTICE_CHANGE_REQ,		// ���� ����
	SP_REPEAT_NOTICE_DELETE_REQ,		// ���� ����
	SP_REALTIME_NOTICE_REQ,				// �ǽð� ����

	SP_SERVER_STATUS_REQ,				// ���� ���� ��û			

	SP_SERVER_CONTROL_TURN_ON_REQ,		// ���� ���μ��� ���� ��û
	SP_SERVER_CONTROL_TURN_OFF_REQ,		// ���� ���μ��� ���� ��û
	SP_SERVER_LOCK_REQ,					// ����/������/���� ä�� ��� ���� ��û
	SP_SERVER_UNLOCK_REQ,				// ����/������/���� ä�� ��� ���� ��û
	SP_SERVER_USER_ALL_KICK_REQ,		// ���� ���� ������� ���� logout
	SP_SERVER_AGENT_PATCH_REQ,			// Server Agent ��ġ�� ��û

	SP_SEARCH_ACCOUNTID_REQ,			// ���̵� ���� ������ ã�´�

	SP_GM_CREATE_REQ,					// GM ���� ��û
	SP_GM_DELETE_REQ,					// GM ���� ��û
	SP_GM_CHANGE_INFO_REQ,				// GM ���� ����
	SP_GM_CHANGE_ACCOUNTID_REQ,			// GM �� ���� ������ Account ID�� �����Ų��.
	SP_GM_CHANGE_PASSWORD_REQ,			// GM �н����� ����
	SP_GM_LIST_REQ,						// GM ����Ʈ �˻�

	SP_GROUP_CREATE_REQ,				// Group ����
	SP_GROUP_DELETE_REQ,				// Group ����
	SP_GROUP_CHANGE_TOOL_AUTHORITY_REQ,	// Group �� �� ���� ����
	SP_GROUP_CHANGE_COMMAND_AUTHORITY_REQ,	// Group�� Ŀ�ǵ� ���� ����
	SP_GROUP_CHANGE_LEVEL_REQ,			// Group ���� ����
	SP_GROUP_LOAD_TOOL_AUTHORITY_REQ,	// Group Tool Authority ��û
	SP_GROUP_LIST_REQ,					// Group ����Ʈ ��û

	SP_FILTERING_LOAD_LIST_REQ,			// ����Ʈ �ε�
	SP_FILTERING_ADD_STRING_REQ,		// ���ڿ� �߰�
	SP_FILTERING_DELETE_STRING_REQ,		// ���ڿ� ����
	SP_FILTERING_FIND_STRING_REQ,		// ���ڿ� ã��
	SP_FILTERING_CHANGE_STRING_REQ,		// ���ڿ� ����
	SP_FILTERING_ADD_STRING_PKG_REQ,	// �������� ���ڿ� �߰�
	SP_FILTERING_CLEAR_REQ,				// ��� ���ڿ� ����

	SP_QUEST_ITEM_CREATE_REQ,			// ����Ʈ ������ ���� [5/17/2007 SGpro]
	SP_QUEST_ITEM_DELETE_REQ,			// ����Ʈ ������ ���� [5/17/2007 SGpro]
	SP_QUEST_ITEM_UPDATE_REQ,			// ����Ʈ ������ ���� [5/17/2007 SGpro]
	
	SP_PROGRESS_QUEST_DELETE_REQ,		// �������� ����Ʈ ���� [5/17/2007 SGpro]

	SP_SCHEDULE_ADD_REQ,				// ���� ������ ���
	SP_SCHEDULE_DEL_REQ,
	SP_SCHEDULE_UPDATE_REQ,
	SP_SCHEDULE_LOAD_REQ,				// ���� ������ �ε�
	
	SP_MAIL_LOADINFO_REQ,				// [10/4/2007 SGpro]
	SP_MAIL_DEL_REQ,					// [10/4/2007 SGpro]

	SP_ACCOUNTCOMMENTLOAD_REQ,			// [10/11/2007 SGpro]
	SP_ACCOUNTCOMMENTUPDATE_REQ,		// [10/11/2007 SGpro]
	
	//SP_SCHEDULELOAD_REQ,				// [10/12/2007 SGpro]
	//SP_SCHEDULEUPDATE_REQ,			// [10/12/2007 SGpro]
	SP_GROUP_CHANGE_ETC_AUTHORITY_REQ,
	SP_ZENNYUPDATE_REQ,					// [4/18/2008 SGpro]
	
	SP_GUILD_SEARCH_REQ,				// [4/22/2008 SGpro]
	SP_GUILD_INFO_REQ,					// [4/22/2008 SGpro]
	SP_GUILD_INFO_UPDATE_REQ,			// [4/22/2008 SGpro]
	SP_GUILD_MASTER_MODIFY_REQ,			// [4/22/2008 SGpro]
	SP_GUILD_SECONDMASTER_DEPRIVATION_REQ,		// [4/22/2008 SGpro]
	SP_GUILD_SECONDMASTER_APPOINTMENT_REQ,		// [4/22/2008 SGpro]
	SP_GUILD_MEMBER_SECEDE_REQ,					// [4/22/2008 SGpro]
	SP_GUILD_ITEM_DELETE_REQ,					// [4/22/2008 SGpro]
	SP_GUILD_ZENNY_MODIFY_REQ,					// [4/22/2008 SGpro]
	SP_GUILD_CHAR_KICK_REQ,

	SP_CHAR_DUPLICATE_REQ,
	SP_CHAR_RESCUE_REQ,

	SP_PETITION_LIST_REQ,						// [5/7/2008 SGpro]
	SP_PETITION_DATALOAD_REQ,					// [5/7/2008 SGpro]
	SP_PETITION_GM_INSERT_REQ,					// [5/7/2008 SGpro]
	SP_PETITION_START_REQ,						// [5/7/2008 SGpro]
	SP_PETITION_INIT_REQ,						// [5/7/2008 SGpro]
	SP_PETITION_RESERVE_REQ,					// [5/7/2008 SGpro]
	SP_PETITION_FINISH_REQ,						// [5/7/2008 SGpro]
	SP_PETITION_CHANGECATEGORY_REQ,				// [5/8/2008 SGpro]
	SP_PETITION_CHAT_START_REQ,					// [ by sooshia 2008-10-15 ]
	SP_PETITION_CHAT_GM_SAY_REQ,				// [ by sooshia 2008-10-16 ]
	SP_PETITION_CHAT_GM_END_NFY,				// [ by sooshia 2008-10-18 ]

	SP_CHANGEHONOR_REQ,							// [6/23/2008 SGpro]
	//SP_CHANGEAMULET_REQ,						// [6/23/2008 SGpro]
	SP_CHANGEMUDOSAPOINT_REQ,					// [ by sooshia 2008-8-6 ]
	SP_CHANGERANKPOINT_REQ,						// [ by sooshia 2008-8-6 ]

	SP_CHARACTERDELETE_REQ,						// [6/26/2008 SGpro]
	SP_CHARACTERRESCUE_REQ,						// [6/26/2008 SGpro]

	SP_GM_SERVER_COMMAND_REQ,					// [6/30/2008 SGpro]

	SP_SERVER_COMMAND_REQ,						// [7/28/2008 SGpro]
	SP_CHARACTER_WATCH_REQ,						// [ by sooshia 2008-09-18 ]
	SP_CHARACTER_WATCH_END_NFY,					// [ by sooshia 2008-09-22 ]
	SP_CHARACTER_INIT_SKILL_REQ,
	SP_GAME_LOG_LIST_REQ,
	SP_GAME_LOG_LIST_DATA_READY_RES,
	SP_SERVER_STATUS_LOCALSETTING_INFO_REQ,
	SP_SERVER_STATUS_LOCALSETTING_EDIT_REQ,
	SP_CHARACTER_CHANGE_SP_REQ,
	SP_CHARACTER_SKILL_ADD_REQ,
	SP_CHARACTER_HTB_ADD_REQ,
	SP_CHARACTER_CHANGE_LEVEL_REQ,
	SP_CHARACTER_CHANGE_EXP_REQ,
	
	SP_MULTI_MAIL_SEND_REQ,
	SP_MULTI_MAIL_HISTORY_REQ,
	SP_MULTI_MAIL_HISTORY_READY_RES,
	SP_GM_COMMAND_LOG_LIST_REQ,
	SP_GM_COMMAND_LOG_LIST_DATA_READY_RES,
	SP_IP_MANAGE_SAMEIP_SEARCH_REQ,
	SP_IP_MANAGE_SAMEIP_USER_LIST_REQ,
	SP_IP_MANAGE_INFO_SEARCH_REQ,
	SP_IP_MANAGE_INFO_EDIT_REQ,

	SP_GM_LOG_LIST_REQ,
	SP_GM_LOG_LIST_DATA_READY_RES,

	SP_PUNISHMENT_MULTI_REQ,

	SP_OPCODE_DUMMY,
	SP_OPCODE_END = SP_OPCODE_DUMMY - 1
};


//------------------------------------------------------------------
//
//------------------------------------------------------------------
const char * NtlGetPacketName_SP(WORD wOpCode);
//------------------------------------------------------------------


#pragma pack(1)

//------------------------------------------------------------------
BEGIN_PROTOCOL(SP_HEARTBEAT)
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(SP_NOTIFY_SERVER_BEGIN)
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(SP_LOGIN_REQ)
	WCHAR			wszUserID[NTL_MAX_SIZE_USERID_UNICODE + 1];
	WCHAR			wszUserPWD[NTL_MAX_SIZE_USERPW_UNICODE + 1];
	WORD			wKaioshinLVersion;
	WORD			wKaioshinRVersion; // by sooshia 07/22/2008 L,R �������� �и�
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(SP_CHANGE_PASSWORD_REQ)
	WCHAR			wszUserID[NTL_MAX_SIZE_USERID_UNICODE + 1];		// ������ ID
	WCHAR			wszCurPWD[NTL_MAX_SIZE_USERPW_UNICODE + 1];		// ���� �н�����
	WCHAR			wszNewPWD[NTL_MAX_SIZE_USERPW_UNICODE + 1];		// ������ �н�����
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(SP_SERVERFARM_NAME_REQ)
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(SP_SEARCH_PC_DATA_REQ)
	BYTE			byUseType;			// � �뵵�� ����� ������? eSEARCH_USE_TYPE

	SERVERFARMID	serverFarmID;		// INVALID_SERVERFARMID �� ��쿡�� ��ü ����
	BYTE			bySearchType;		// User Serial, User ID, Character Serial, Character Name
	BYTE			byDelType;			// eDEL_TYPE - NtlCharacter.h
	union
	{
		ACCOUNTID		accountId;
		WCHAR			wszUserID[NTL_MAX_SIZE_USERID_UNICODE + 1];
		CHARACTERID		charId;
		WCHAR			wszCharName[NTL_MAX_SIZE_CHAR_NAME_UNICODE + 1];
	};
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(SP_PC_DATA_REQ)
	SERVERFARMID		serverFarmId;
	ACCOUNTID			accountId;
	CHARACTERID			charId;
	BYTE				byDelType;			// eDEL_TYPE - NtlCharacter.h
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(SP_CHARACTER_LOGIN_INFO_REQ)
	ACCOUNTID			accountId;				// ��û�� User Account ID
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(SP_CHARACTER_KICK_REQ)
	ACCOUNTID			accountId;				// User Account ID
	bool				bApply;					// true : ����, false : ����
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(SP_CHARACTER_KICK_INFO_REQ)
	ACCOUNTID			accountId;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(SP_CHARACTER_CHANGE_NAME_REQ)
	SERVERFARMID		serverFarmID;
	ACCOUNTID			accountID;
	CHARACTERID			charID;
	WCHAR				wszCharName[NTL_MAX_SIZE_CHAR_NAME_UNICODE + 1];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(SP_CHAR_CHANGE_BIND_LOCATION_REQ)
	ACCOUNTID			accountID;
	SERVERFARMID		serverFarmID;
	WCHAR				wszAccountName[NTL_MAX_SIZE_CHAR_NAME_UNICODE + 1];
	CHARACTERID			charID;
	WCHAR				wszCharName[NTL_MAX_SIZE_CHAR_NAME_UNICODE + 1];
	WORLDID				oldWorldId;
	WCHAR				wszOldWorldName[NTL_MAX_SIZE_WORLD_NAME_UNICODE + 1];
	sVECTOR3			vOldBindLoc;
	WORLDID				worldId;
	WCHAR				wszWorldName[NTL_MAX_SIZE_WORLD_NAME_UNICODE + 1];
	sVECTOR3			vBindLoc;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(SP_CHAR_CHANGE_CUR_LOCATION_REQ)
	ACCOUNTID			accountID;
	SERVERFARMID		serverFarmID;
	WCHAR				wszAccountName[NTL_MAX_SIZE_CHAR_NAME_UNICODE + 1];
	CHARACTERID			charID;
	WCHAR				wszCharName[NTL_MAX_SIZE_CHAR_NAME_UNICODE + 1];
	WORLDID				oldWorldId;
	WCHAR				wszOldWorldName[NTL_MAX_SIZE_WORLD_NAME_UNICODE + 1];
	sVECTOR3			vOldLoc;
	TBLIDX				worldTblidx;
	WORLDID				worldId;
	WCHAR				wszWorldName[NTL_MAX_SIZE_WORLD_NAME_UNICODE + 1];
	sVECTOR3			vLoc;
END_PROTOCOL()
//------------------------------------------------------------------
//  [5/22/2007 SGpro]
BEGIN_PROTOCOL( SP_CHARNAME_MODIFY_GMTOOL_REQ )
	SERVERFARMID	serverFarmID; 
	ACCOUNTID		accountID; 
	WCHAR			wszAccountName[NTL_MAX_SIZE_CHAR_NAME_UNICODE + 1];
	CHARACTERID		charID;	
	WCHAR			wszOldCharName[NTL_MAX_SIZE_CHAR_NAME_UNICODE + 1];
	WCHAR			wszCharName[NTL_MAX_SIZE_CHAR_NAME_UNICODE + 1];
	bool			bBlockStringCheck;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(SP_SKILL_DELETE_REQ)
	SERVERFARMID		serverFarmId;		// Server Farm ID
	WCHAR				wszAccountName[NTL_MAX_SIZE_CHAR_NAME_UNICODE + 1];
	CHARACTERID			charId;				// Character ID
	WCHAR				wszCharName[NTL_MAX_SIZE_CHAR_NAME_UNICODE + 1];
	BYTE				bySlot;				// Skill �� �ִ� Slot
	TBLIDX				skillId;			// Skill �� Table Index
	WCHAR				wszSkillName[NTL_MAX_LENGTH_SKILL_NAME_TEXT + 1];
	TBLIDX  			oldSkillId;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(SP_HTB_SKILL_DELETE_REQ)
	SERVERFARMID		serverFarmId;		// Server Farm ID
	WCHAR				wszAccountName[NTL_MAX_SIZE_CHAR_NAME_UNICODE + 1];
	CHARACTERID			charId;				// Character ID
	WCHAR				wszCharName[NTL_MAX_SIZE_CHAR_NAME_UNICODE + 1];
	TBLIDX				skillId;			// Skill �� Table Index
	WCHAR				wszSkillName[NTL_MAX_LENGTH_SKILL_NAME_TEXT + 1];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(SP_BUFF_DELETE_REQ)
	SERVERFARMID		serverFarmId;		// Server Farm ID
	WCHAR				wszAccountName[NTL_MAX_SIZE_CHAR_NAME_UNICODE + 1];
	CHARACTERID			charId;				// Character ID
	WCHAR				wszCharName[NTL_MAX_SIZE_CHAR_NAME_UNICODE + 1];
	TBLIDX				sourceTblidx;		// Buff�� Table Index
	BYTE				bySourceType;		// Buff�� Type : eDBO_OBJECT_SOURCE
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(SP_ITEM_CREATE_REQ)
	SERVERFARMID		serverFarmID;
	WCHAR				wszAccountName[NTL_MAX_SIZE_CHAR_NAME_UNICODE + 1];
	WCHAR				wszCharName[NTL_MAX_SIZE_CHAR_NAME_UNICODE + 1];
	WCHAR				wszItemName[NTL_MAX_LENGTH_ITEM_NAME_TEXT + 1];
	sITEM_DATA			sItem;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(SP_ITEM_DELETE_REQ)
	SERVERFARMID		serverFarmID;
	WCHAR				wszAccountName[NTL_MAX_SIZE_CHAR_NAME_UNICODE + 1];
	CHARACTERID			charID;
	WCHAR				wszCharName[NTL_MAX_SIZE_CHAR_NAME_UNICODE + 1];
	WCHAR				wszItemName[NTL_MAX_LENGTH_ITEM_NAME_TEXT + 1];
	sITEM_DELETE_DATA	sItem;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(SP_ITEM_CHANGE_INFO_REQ)
	SERVERFARMID		serverFarmID;
	sITEM_DATA			sItem;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(SP_PUNISHMENT_INFO_REQ)
	SERVERFARMID	serverFarmID;
	ACCOUNTID		accountID;
	int				nMultiMode; // 0=normal, 1=multi
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(SP_PUNISHMENT_REQ)
	SERVERFARMID	serverFarmID;

	BYTE			byApply;			// ePUNISH_APPLY_TYPE

	BYTE			byPunishType;		// eGM_PUNISH_PASSIVE_TYPE
	ACCOUNTID		accountID;			// ���� ���϶� ���
	WCHAR			wszAccountName[NTL_MAX_SIZE_USERID_UNICODE];
	CHARACTERID		charID;				// ĳ���� ���϶� ���
	WCHAR			awchName[NTL_MAX_SIZE_CHAR_NAME_UNICODE + 1];

	// �Ⱓ
	BYTE			byPeriodType;
	DWORD			dwPeriod;			// �Ⱓ

	// ����
	BYTE			byReasonType;
	WCHAR			wszReason[NTL_MAX_PUNISH_REASON_LENGTH + 1];
	WCHAR			wszPunishmentContent[NTL_MAX_LENGTH_BEFORE_AFTER_STATUS + 1];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(SP_REPEAT_NOTICE_LIST_REQ)
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(SP_REPEAT_NOTICE_ADD_REQ)
	sGM_REPEAT_NOTICE_ENTITY	sNotice;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(SP_REPEAT_NOTICE_CHANGE_REQ)
	sGM_REPEAT_NOTICE_ENTITY	sNotice;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(SP_REPEAT_NOTICE_DELETE_REQ)
	DWORD						dwSerial;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(SP_REALTIME_NOTICE_REQ)
	BYTE			byNoticeType;			// eSERVER_TEXT_TYPE
	SERVERFARMID	serverFarmID;
	BYTE			byChannelID;
	WCHAR			wszNotice[NTL_MAX_LENGTH_OF_CHAT_MESSAGE_UNICODE+1];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(SP_SERVER_STATUS_REQ)
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(SP_SERVER_CONTROL_TURN_ON_REQ)
	BYTE				byServerType;
	SERVERFARMID		serverFarmId;
	BYTE				byServerChannelIndex;
	BYTE				byServerIndex;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(SP_SERVER_CONTROL_TURN_OFF_REQ)
	BYTE				byServerType;
	SERVERFARMID		serverFarmId;
	BYTE				byServerChannelIndex;
	BYTE				byServerIndex;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(SP_SERVER_LOCK_REQ)
	BYTE				byServerType;//���� ������ ������, ĳ��, ����
	SERVERFARMID		serverFarmId;//����, ĳ��- �ǹ̾���, ���� - ���� ���´�, �κ�����(��� ����)
	BYTE				byServerChannelIndex; // �κ������ �ǹ̰� ����. (Ư�� �������� �������� Ư�� ä�θ� ������, �κ����� (��� ä��))
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(SP_SERVER_UNLOCK_REQ)
	BYTE				byServerType;
	SERVERFARMID		serverFarmId;
	BYTE				byServerChannelIndex;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(SP_SERVER_USER_ALL_KICK_REQ)
	BYTE				byServerType;
	SERVERFARMID		serverFarmId;
	BYTE				byServerChannelIndex;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(SP_SERVER_AGENT_PATCH_REQ)
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(SP_GM_CREATE_REQ)
	WCHAR				wszUser[NTL_MAX_SIZE_USERID_UNICODE + 1];
	WCHAR				wszPass[NTL_MAX_SIZE_USERPW_UNICODE + 1];
	DWORD				dwGroupSerial;
	uGM_TOOL_IP_ADDRESS	uIPAddress;	// ���� ���� ip

	WCHAR				wszName[NTL_MAX_SIZE_TOOL_USERNAME_UNICODE + 1];
	WCHAR				wszPartName[NTL_MAX_SIZE_TOOL_PARTNAME_UNICODE + 1];
	WCHAR				wszComment[NTL_MAX_SIZE_TOOL_COMMENT_UNICODE + 1];
	WCHAR				wszGMName[NTL_MAX_SIZE_CHAR_NAME_UNICODE + 1];

	ACCOUNTID			accountID;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(SP_GM_DELETE_REQ)
	ACCOUNTID			gmAccountID;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(SP_GM_CHANGE_INFO_REQ)
	ACCOUNTID			gmAccountID;								// �����ų GM�� AccountID
	ACCOUNTID			accountID;									// Game �������� ������Ʈ�� ����
	DWORD				dwGroupSerial;
	uGM_TOOL_IP_ADDRESS	uIPAddress;	// ���� ���� ip
	WCHAR				wszName[NTL_MAX_SIZE_TOOL_USERNAME_UNICODE + 1];
	WCHAR				wszPartName[NTL_MAX_SIZE_TOOL_PARTNAME_UNICODE + 1];
	WCHAR				wszComment[NTL_MAX_SIZE_TOOL_COMMENT_UNICODE + 1];
	WCHAR				wszGMName[NTL_MAX_SIZE_TOOL_GM_NAME_UNICODE + 1];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(SP_GM_CHANGE_ACCOUNTID_REQ)
	ACCOUNTID			gmAccountID;								// �����ų GM�� AccountID

	ACCOUNTID			newAccountID;								// Game Server������ GM ID
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(SP_GM_CHANGE_PASSWORD_REQ)
	ACCOUNTID			gmAccountID;									// �����ų GM�� AccountID
	WCHAR				wszPassword[NTL_MAX_SIZE_USERPW_UNICODE + 1];	// ������ password
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(SP_GM_LIST_REQ)
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(SP_GROUP_CREATE_REQ)
	WCHAR				wszGroupName[NTL_MAX_SIZE_TOOL_GROUPNAME_UNICODE + 1];	// Group Name
	BYTE				byGroupLevel;									// Group Level
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(SP_GROUP_DELETE_REQ)
	DWORD				dwGroupSerial;									// ������ �׷� �ø���
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(SP_GROUP_CHANGE_TOOL_AUTHORITY_REQ)
	DWORD				dwGroupSerial;									// ������ �׷�
	sGM_TOOL_AUTH_FLAG	sToolAuth;										// ����
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(SP_GROUP_CHANGE_COMMAND_AUTHORITY_REQ)
	DWORD					dwGroupSerial;								// ������ �׷�
	sGM_COMMAND_AUTH_FLAG	sCommandAuth;								// ����
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(SP_GROUP_CHANGE_LEVEL_REQ)
	DWORD				dwGroupSerial;									// ������ �׷�
	BYTE				byGroupLevel;									// ������ ����
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(SP_GROUP_LOAD_TOOL_AUTHORITY_REQ)
	DWORD				dwGroupSerial;									// ������ �׷�
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(SP_GROUP_LIST_REQ)
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(SP_SEARCH_ACCOUNTID_REQ)
	WCHAR				wszUserID[NTL_MAX_SIZE_USERID_UNICODE + 1];
	BYTE				byUseType;	// eGM_ACCOUNTID_INFO_USE_TYPE
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(SP_FILTERING_LOAD_LIST_REQ)
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(SP_FILTERING_ADD_STRING_REQ)
	sBLOCK_STRING_DATA	sString;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(SP_FILTERING_DELETE_STRING_REQ)
	sBLOCK_STRING_DATA	sString;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(SP_FILTERING_FIND_STRING_REQ)
	sBLOCK_STRING_DATA	sString;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(SP_FILTERING_CHANGE_STRING_REQ)
	sBLOCK_STRING_DATA	sCurString;
	sBLOCK_STRING_DATA	sNewString;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(SP_FILTERING_ADD_STRING_PKG_REQ)
	WORD						wCount;
	sBLOCK_STRING_DATA			asString[1];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(SP_FILTERING_CLEAR_REQ)
END_PROTOCOL()
//------------------------------------------------------------------
// [5/17/2007 SGpro]
BEGIN_PROTOCOL( SP_QUEST_ITEM_CREATE_REQ )
	SERVERFARMID		serverFarmID;
	WCHAR				wszAccountName[NTL_MAX_SIZE_USERID_UNICODE + 1];
	CHARACTERID			charId;				// Character ID
	WCHAR				wszCharName[NTL_MAX_SIZE_CHAR_NAME_UNICODE + 1];
	TBLIDX				tblidx;
	WCHAR				wszItemName[NTL_MAX_LENGTH_ITEM_NAME_TEXT + 1];
	BYTE				byCurStackCount;
	BYTE				byPos;				// �κ��丮������ �������� ��ġ by ju-hyeong
END_PROTOCOL()
//------------------------------------------------------------------
// [5/17/2007 SGpro]
BEGIN_PROTOCOL( SP_QUEST_ITEM_DELETE_REQ )
	SERVERFARMID		serverFarmID;
	WCHAR				wszAccountName[NTL_MAX_SIZE_USERID_UNICODE + 1];
	CHARACTERID			charId;				// Character ID
	WCHAR				wszCharName[NTL_MAX_SIZE_CHAR_NAME_UNICODE + 1];
	TBLIDX				tblidx;
	WCHAR				wszItemName[NTL_MAX_LENGTH_ITEM_NAME_TEXT + 1];
	BYTE				byPos;				// �κ��丮������ �������� ��ġ by ju-hyeong
END_PROTOCOL()
//------------------------------------------------------------------
// [5/17/2007 SGpro]
BEGIN_PROTOCOL( SP_QUEST_ITEM_UPDATE_REQ )
	SERVERFARMID		serverFarmID;
	WCHAR				wszAccountName[NTL_MAX_SIZE_USERID_UNICODE + 1];
	CHARACTERID			charId;				// Character ID
	WCHAR				wszCharName[NTL_MAX_SIZE_CHAR_NAME_UNICODE + 1];
	TBLIDX				tblidx;
	WCHAR				wszItemName[NTL_MAX_LENGTH_ITEM_NAME_TEXT + 1];
	BYTE				byPrevStackCount;
	BYTE				byCurStackCount;
	BYTE				byPos;				// �κ��丮������ �������� ��ġ by ju-hyeong
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( SP_PROGRESS_QUEST_DELETE_REQ )
	SERVERFARMID		serverFarmID;
	WCHAR				wszAccountName[NTL_MAX_SIZE_USERID_UNICODE + 1];
	CHARACTERID			charId;
	WCHAR				wszCharName[NTL_MAX_SIZE_CHAR_NAME_UNICODE + 1];
	QUESTID				questId;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( SP_SCHEDULE_ADD_REQ )
	SERVERFARMID		serverFarmID;
	BYTE				byEventType;		//eSCHEDULE_EVENT_TYPE
	__int64				nStartTime;
	__int64				nEndTime;
	int					nMainTerm;
	int					nSubTerm;
	BYTE				byTermType;			//eSCHEDULE_TERM_TYPE
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( SP_SCHEDULE_DEL_REQ )
	SERVERFARMID		serverFarmID;
	BYTE				byEventType;		//eSCHEDULE_EVENT_TYPE
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( SP_SCHEDULE_UPDATE_REQ )
	SERVERFARMID		serverFarmID;
	BYTE				byEventType;		//eSCHEDULE_EVENT_TYPE
	__int64				nStartTime;
	__int64				nEndTime;
	int					nMainTerm;
	int					nSubTerm;
	BYTE				byTermType;			//eSCHEDULE_TERM_TYPE
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( SP_SCHEDULE_LOAD_REQ )
	SERVERFARMID		serverFarmID;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( SP_MAIL_LOADINFO_REQ )
	SERVERFARMID		serverFarmID;
	CHARACTERID			charId;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( SP_MAIL_DEL_REQ )
	SERVERFARMID		serverFarmID;
	WCHAR				wszAccountName[NTL_MAX_SIZE_CHAR_NAME_UNICODE + 1];
	CHARACTERID			charId;
	WCHAR				wszCharName[NTL_MAX_SIZE_CHAR_NAME_UNICODE + 1];
	MAILID				mailID;
	bool				bIsUnconditionalDelete;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( SP_ACCOUNTCOMMENTLOAD_REQ )
	ACCOUNTID			accountID;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( SP_ACCOUNTCOMMENTUPDATE_REQ )
	sGM_PACKET_ACCOUNT_COMMENT	sAccountComment;
END_PROTOCOL()
//------------------------------------------------------------------
//BEGIN_PROTOCOL( SP_SCHEDULELOAD_REQ )
//	SERVERFARMID		serverFarmID;
//	CHARACTERID			charId;
//END_PROTOCOL()
////------------------------------------------------------------------
//BEGIN_PROTOCOL( SP_SCHEDULEUPDATE_REQ )
//	SERVERFARMID		serverFarmID;
//	CHARACTERID			charId;
//END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( SP_GROUP_CHANGE_ETC_AUTHORITY_REQ )
	DWORD					dwGroupSerial;	// ������ �׷�
	sGM_ETC_AUTH_FLAG		sEtcAuth;		// ����
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( SP_ZENNYUPDATE_REQ )
	BYTE					byUpdateType; //eCONTAINER_TYPE
	SERVERFARMID			serverFarmID;
	WCHAR				wszAccountName[NTL_MAX_SIZE_CHAR_NAME_UNICODE + 1];
	ACCOUNTID				accountID;
	CHARACTERID				charID;
	WCHAR					wszCharName[NTL_MAX_SIZE_CHAR_NAME_UNICODE + 1];
	DWORD					dwOldZenny;	
	DWORD					dwZenny;	
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( SP_GUILD_SEARCH_REQ )
	SERVERFARMID		serverFarmID;
	BYTE				bySearchType;			// 0: GuildName ���� 1: ������ �̸�
	WCHAR				wszName[NTL_MAX_SIZE_GUILD_NAME_IN_UNICODE + 1];
	WCHAR				wszMasterName[NTL_MAX_SIZE_CHAR_NAME_UNICODE + 1];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( SP_GUILD_INFO_REQ )
	SERVERFARMID		serverFarmID;
	GUILDID				guildId;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( SP_GUILD_INFO_UPDATE_REQ )
	SERVERFARMID		serverFarmID;
	GUILDID				guildId;
	sDBO_GUILD_CAHNGE_INFO		sBeforeInfo;
	sDBO_GUILD_CAHNGE_INFO		sInfo;
	BYTE				byUpdateType;	// eDBO_GUILD_UPDATE_TYPE
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( SP_GUILD_MASTER_MODIFY_REQ )
	SERVERFARMID		serverFarmID;
	GUILDID				guildId;
	CHARACTERID			charId;					// Neo Leader
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( SP_GUILD_SECONDMASTER_DEPRIVATION_REQ )
	SERVERFARMID		serverFarmID;
	GUILDID				guildId;
	CHARACTERID			charId;					// ���� �α渶�� ���� �Ǵ� ��� 
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( SP_GUILD_SECONDMASTER_APPOINTMENT_REQ )
	SERVERFARMID		serverFarmID;
	GUILDID				guildId;
	CHARACTERID			charId;					// ���� �Ӹ�Ǵ� �α渶
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( SP_GUILD_MEMBER_SECEDE_REQ )
	SERVERFARMID		serverFarmID;
	GUILDID				guildId;
	CHARACTERID			charId;					// ���� �����ε� ��Ż�Ǵ� ���
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( SP_GUILD_ITEM_DELETE_REQ )
	SERVERFARMID		serverFarmID;
	GUILDID				guildId;
	WCHAR				wszGuildName[NTL_MAX_SIZE_GUILD_NAME + 1];
	sITEM_DELETE_DATA	sItem;
	WCHAR				wszItemName[NTL_MAX_LENGTH_ITEM_NAME_TEXT + 1];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( SP_GUILD_ZENNY_MODIFY_REQ )
	SERVERFARMID			serverFarmID;
	GUILDID					guildId;
	WCHAR					wszGuildName[NTL_MAX_SIZE_GUILD_NAME + 1];
	DWORD					dwOldZenny;
	DWORD					dwZenny;
	BYTE					byUpdateType; //eCONTAINER_TYPE  Tool Res �ʿ��� ��
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(SP_GUILD_CHAR_KICK_REQ)
	bool					bApply;					// true : ����, false : ����
	GUILDID					guildId;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(SP_CHAR_DUPLICATE_REQ)
	SERVERFARMID		serverFarmID;
	WCHAR				wszUser[NTL_MAX_SIZE_USERID_UNICODE + 1];		 // GM ID	
	WCHAR				wszName[NTL_MAX_SIZE_TOOL_USERNAME_UNICODE + 1]; // GM ���� ĳ�� �̸�
	ACCOUNTID			accountID;				// GM ����
	CHARACTERID			originalCharID;			// ������ Character
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(SP_CHAR_RESCUE_REQ)
	SERVERFARMID		serverFarmID;
	CHARACTERID			charID;					// ������ character
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( SP_PETITION_LIST_REQ )
	int					nCurrentPage;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( SP_PETITION_DATALOAD_REQ )
	PETITIONID			petitionID;
	bool				bImmediatelyConsultStart;//true�̸� �������� ��� �����Ѵ�
	BYTE				byDataLoadType; //ePETITIONDATALOADTYPE
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( SP_PETITION_GM_INSERT_REQ )
	SERVERFARMID		serverFarmID;
	WCHAR				awchUserCharName[NTL_MAX_SIZE_CHAR_NAME_UNICODE + 1];
	WCHAR				awchQuestionContent[NTL_MAX_SIZE_QUESTION_CONTENT_UNICODE + 1];
	PETITIONCATEGORY	nCategory1;//ePETITIONSYSTEM_CATEGORY_1
	PETITIONCATEGORY	nCategory2;//ePETITIONSYSTEM_CATEGORY_2
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( SP_PETITION_START_REQ )
	PETITIONID			petitionID;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( SP_PETITION_INIT_REQ )
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( SP_PETITION_RESERVE_REQ )
	PETITIONID			petitionID;
	WCHAR				awchNote[NTL_MAX_SIZE_NOTE_UNICODE + 1];//���
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( SP_PETITION_FINISH_REQ )
	PETITIONID			petitionID;
	ACCOUNTID			userAccountID;
	SERVERFARMID		serverFarmID;
	BYTE				byFinishType;//ePETITIONFINISHTYPE
	PETITIONCATEGORY	nNewCategory1; //ePETITIONSYSTEM_CATEGORY_1
	PETITIONCATEGORY	nNewCategory2; //ePETITIONSYSTEM_CATEGORY_2
	WCHAR				awchPetitionResultText[NTL_MAX_SIZE_PETITION_RESULTTEXT_UNICODE + 1];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( SP_PETITION_CHANGECATEGORY_REQ )
	PETITIONID			petitionID;
	PETITIONCATEGORY	nNewCategory1;//ePETITIONSYSTEM_CATEGORY_1
	PETITIONCATEGORY	nNewCategory2;//ePETITIONSYSTEM_CATEGORY_2
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( SP_CHANGEHONOR_REQ )
	SERVERFARMID		serverFarmID;
	WCHAR				wszAccountName[NTL_MAX_SIZE_CHAR_NAME_UNICODE + 1];
	CHARACTERID			charId;
	WCHAR				wszCharName[NTL_MAX_SIZE_USERID_UNICODE	+ 1];
	DWORD				dwHonorPoint;
	DWORD				dwNewHonorPoint;
END_PROTOCOL()
//------------------------------------------------------------------
// [ by sooshia 2008-8-6 ]
BEGIN_PROTOCOL( SP_CHANGEMUDOSAPOINT_REQ )
	SERVERFARMID		serverFarmID;
	WCHAR				wszAccountName[NTL_MAX_SIZE_CHAR_NAME_UNICODE + 1];
	CHARACTERID			charId;
	WCHAR				wszCharName[NTL_MAX_SIZE_USERID_UNICODE + 1];
	DWORD				dwMudosaPoint;
	DWORD				dwNewMudosaPoint;
END_PROTOCOL()
//------------------------------------------------------------------
// [ by sooshia 2008-8-6 ]
BEGIN_PROTOCOL( SP_CHANGERANKPOINT_REQ )
	SERVERFARMID		serverFarmID;
	WCHAR				wszAccountName[NTL_MAX_SIZE_CHAR_NAME_UNICODE + 1];
	CHARACTERID			charId;
	WCHAR				wszCharName[NTL_MAX_SIZE_USERID_UNICODE + 1];
	DWORD				dwRankPoint;
	DWORD				dwNewRankPoint;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( SP_CHARACTERDELETE_REQ )
	SERVERFARMID		serverFarmID;
	WCHAR				wszAccountName[NTL_MAX_SIZE_USERID_UNICODE + 1];
	CHARACTERID			charId;
	WCHAR				wszCharName[NTL_MAX_SIZE_USERID_UNICODE + 1];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( SP_CHARACTERRESCUE_REQ )
	SERVERFARMID		serverFarmID;
	CHARACTERID			charId;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( SP_GM_SERVER_COMMAND_REQ )
	BYTE				byServerType; // eNtlServerType
	SERVERFARMID		serverfarmID;
	SERVERCHANNELID		serverchannelID;
	SERVERINDEX			serverIndex;
	WORD				wMessageLengthInUnicode;
	WCHAR				awchCommand[NTL_MAX_LENGTH_OF_CHAT_MESSAGE_UNICODE + 1];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( SP_SERVER_COMMAND_REQ )
	BYTE				byServerType; // eNtlServerType
	SERVERFARMID		serverfarmID;
	SERVERCHANNELID		serverchannelID;
	SERVERINDEX			serverIndex;
	WORD				wMessageLengthInUnicode;
	WCHAR				awchCommand[NTL_MAX_LENGTH_OF_CHAT_MESSAGE_UNICODE + 1];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( SP_CHARACTER_WATCH_REQ )
	ACCOUNTID			userAccountID;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( SP_CHARACTER_WATCH_END_NFY )
	ACCOUNTID			userAccountID;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( SP_PETITION_CHAT_START_REQ )
	PETITIONID			petitionID;
	ACCOUNTID			userAccountID;
	bool				bNeedSatisfactionRate;
	SERVERFARMID		serverfarmID;
	WCHAR				awchGMCharName_Consult[NTL_MAX_SIZE_CHAR_NAME_UNICODE + 1];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( SP_PETITION_CHAT_GM_SAY_REQ )
	ACCOUNTID			userAccountID;
	SERVERFARMID		serverfarmID;
	WORD				wMessageLengthInUnicode;
	WCHAR				awchMessage[NTL_MAX_LENGTH_OF_CHAT_MESSAGE_UNICODE + 1];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( SP_PETITION_CHAT_GM_END_NFY )
	ACCOUNTID			userAccountID;
	SERVERFARMID		serverfarmID;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( SP_CHARACTER_INIT_SKILL_REQ )
	SERVERFARMID		serverfarmID;
	CHARACTERID			charId;
	DWORD				dwNewSP;
	BYTE				byCurClass;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( SP_GAME_LOG_LIST_REQ )
	SERVERFARMID serverFarmID;
	BYTE bySearchOption;
	WCHAR wszSearchName[NTL_MAX_LENGTH_REPORT_NAME+1];
	DWORD dwLogType1;
	DWORD dwLogType2;
	sDBO_TIME timeBegin;
	sDBO_TIME timeEnd;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( SP_GAME_LOG_LIST_DATA_READY_RES )
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( SP_SERVER_STATUS_LOCALSETTING_INFO_REQ )
	BYTE				byServerType; // eNtlServerType
	SERVERFARMID		serverfarmID;
	SERVERCHANNELID		serverchannelID;
	SERVERINDEX			serverIndex;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( SP_SERVER_STATUS_LOCALSETTING_EDIT_REQ )
	BYTE				byServerType; // eNtlServerType
	SERVERFARMID		serverfarmID;
	SERVERCHANNELID		serverchannelID;
	SERVERINDEX			serverIndex;
	int					nFileLength;
	char				szFileContent[NTL_MAX_SIZE_LOCALSETTING_FILE + 1];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( SP_CHARACTER_CHANGE_SP_REQ )
	SERVERFARMID		serverfarmID;
	CHARACTERID			charId;
	DWORD				dwNewSP;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( SP_CHARACTER_SKILL_ADD_REQ )
	SERVERFARMID		serverfarmID;
	WCHAR				wszAccountName[NTL_MAX_SIZE_CHAR_NAME_UNICODE + 1];
	TBLIDX				skillID;
	WCHAR				wszSkillName[NTL_MAX_LENGTH_SKILL_NAME_TEXT + 1];
	CHARACTERID			charID;
	WCHAR				wszCharName[NTL_MAX_SIZE_CHAR_NAME_UNICODE + 1];
	WORD				wNeedSP;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( SP_CHARACTER_HTB_ADD_REQ )
	SERVERFARMID		serverfarmID;
	WCHAR				wszAccountName[NTL_MAX_SIZE_CHAR_NAME_UNICODE + 1];
	TBLIDX				skillID;
	WCHAR				wszSkillName[NTL_MAX_LENGTH_SKILL_NAME_TEXT + 1];
	CHARACTERID			charID;
	WCHAR				wszCharName[NTL_MAX_SIZE_CHAR_NAME_UNICODE + 1];
	WORD				wNeedSP;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( SP_CHARACTER_CHANGE_LEVEL_REQ )
	SERVERFARMID		serverfarmID;
	WCHAR				wszAccountName[NTL_MAX_SIZE_CHAR_NAME_UNICODE + 1];
	CHARACTERID			charId;
	WCHAR				wszCharName[NTL_MAX_SIZE_CHAR_NAME_UNICODE + 1];
	BYTE				byLevel;
	BYTE				byNewLevel;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( SP_CHARACTER_CHANGE_EXP_REQ )
	SERVERFARMID		serverfarmID;
	WCHAR				wszAccountName[NTL_MAX_SIZE_CHAR_NAME_UNICODE + 1];
	CHARACTERID			charId;
	WCHAR				wszCharName[NTL_MAX_SIZE_CHAR_NAME_UNICODE + 1];
	DWORD				dwExp;
	DWORD				dwNewExp;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( SP_MULTI_MAIL_SEND_REQ )
	SERVERFARMID				serverfarmID;
	WCHAR						wszTargetName[NTL_MAX_COUNT_MULTI_MAIL][NTL_MAX_SIZE_CHAR_NAME_UNICODE + 1];	// ���� ĳ�� �̸�
	int							nTargetCount;
	WCHAR						wszText[NTL_MAX_LENGTH_OF_MAIL_MESSAGE_IN_UNICODE + 1];// ���ϳ���
	WCHAR						wszItemName[NTL_MAX_LENGTH_ITEM_NAME_TEXT + 1];
	BYTE  						byTextSize;
	eMAIL_TYPE 					eMailType;// eMAIL_TYPE
	eMAIL_SENDER_TYPE			eSenderType;//eMAIL_SENDER_TYPE
	sITEM_DATA					sItemData;//����������
	DWORD						dwZenny;
	BYTE						byDay;// ��ȿ���ᳯ¥ �ִ� 10��
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(SP_MULTI_MAIL_HISTORY_REQ)
	SERVERFARMID				serverfarmID;
	sDBO_TIME timeBegin;
	sDBO_TIME timeEnd;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(SP_MULTI_MAIL_HISTORY_READY_RES)
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(SP_GM_COMMAND_LOG_LIST_REQ)
	SERVERFARMID serverFarmID;
	WCHAR wszSearchAccountID[NTL_MAX_SIZE_USERID_UNICODE+1];
	sDBO_TIME timeBegin;
	sDBO_TIME timeEnd;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(SP_GM_COMMAND_LOG_LIST_DATA_READY_RES)
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(SP_IP_MANAGE_SAMEIP_SEARCH_REQ)
	SERVERFARMID	serverFarmID;
	sDBO_TIME		timeBegin;
	sDBO_TIME		timeEnd;
	BYTE			byIPType;
	DWORD			dwConnectingCount;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(SP_IP_MANAGE_SAMEIP_USER_LIST_REQ)
	SERVERFARMID	serverFarmID;
	sDBO_TIME		timeBegin;
	sDBO_TIME		timeEnd;
	int				nIP;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(SP_IP_MANAGE_INFO_SEARCH_REQ)
	uGM_TOOL_IP_ADDRESS	uIPAddress;
	bool				bIsIPWith3Field;
	BYTE				byIPType;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(SP_IP_MANAGE_INFO_EDIT_REQ)
	BYTE				byEditType; // byEditType 0=add, 1=modify, 2=remove
	uGM_TOOL_IP_ADDRESS	uIPAddress;
	BYTE				byIPType;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(SP_GM_LOG_LIST_REQ)
	eGM_REPORT_TYPE		reportType;	
	SERVERFARMID		serverFarmID;
	WCHAR				wszAccountID[NTL_MAX_SIZE_USERID_UNICODE + 1];
	sDBO_TIME			sBeginTime;
	sDBO_TIME			sEndTime;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(SP_GM_LOG_LIST_DATA_READY_RES)	
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(SP_PUNISHMENT_MULTI_REQ)
	WCHAR			wszTargetAccount[100][NTL_MAX_SIZE_USERID_UNICODE + 1]; // 100���� �ٲٷ��� KAIOSHIN_MAX_PUNISHMENT_MULTI �̰ŵ� �ٲٽÿ�.
	int				nTargetCount;

	BYTE			byApply;			// ePUNISH_APPLY_TYPE
	BYTE			byPunishType;		// eGM_PUNISH_PASSIVE_TYPE
	
	// �Ⱓ
	BYTE			byPeriodType;
	DWORD			dwPeriod;
	
	// ����
	BYTE			byReasonType;
	WCHAR			wszReason[NTL_MAX_PUNISH_REASON_LENGTH+1];
END_PROTOCOL()
//------------------------------------------------------------------
#pragma pack()