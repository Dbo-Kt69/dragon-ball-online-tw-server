#pragma once

#include "NtlPacketCommon.h"
#include "NtlCharacter.h"
#include "NtlSystemTool.h"
#include "NtlAdmin.h"
#include "NtlMail.h"
#include "NtlPetition.h"
#include "NtlRankBattle.h"
#include "NtlReport.h"

enum eOPCODE_PS
{
	PS_OPCODE_BEGIN = 61000,

	PS_HEARTBEAT = PS_OPCODE_BEGIN,

	PS_LOGIN_RES,					// �α��� ��û ����
	PS_CHANGE_PASSWORD_RES,			// �н����� ���� ����

	PS_SERVERFARM_NAME_RES,			// ������ �̸� ����

	PS_SEARCH_PC_DATA_INFO_START,	// [6/26/2008 SGpro]
	PS_SEARCH_PC_DATA_INFO,			// [6/26/2008 SGpro]
	PS_SEARCH_PC_DATA_RES,			// ĳ���� ã�� ����
	PS_PC_DATA_RES,					// ĳ���� ���� ����

	PS_CHARACTER_LOGIN_INFO_RES,	// �α��� ���� ��û
	PS_CHARACTER_KICK_INFO_RES,		// ű ���� ��û
	PS_CHARACTER_KICK_RES,			// ĳ���͸� ű ��Ų��. (���� ���)
	PS_CHARACTER_CHANGE_NAME_RES,		// ĳ������ �̸��� ����
	PS_CHARNAME_MODIFY_GMTOOL_RES,		// [5/22/2007 SGpro]

	PS_CHAR_CHANGE_BIND_LOCATION_RES,// ���ε� ��ġ ����
	PS_CHAR_CHANGE_CUR_LOCATION_RES,// ���� ��ġ ����
	PS_CHAR_SKILL_DELETE_RES,			// ��ų ����
	PS_CHAR_HTBSKILL_DELETE_RES,		// HTB ��ų ����
	PS_CHAR_BUFFSKILL_DELETE_RES,		// Buff ��ų ����

	PS_SKILL_DELETE_RES,			// ��ų ����
	PS_HTB_SKILL_DELETE_RES,		// HTB ��ų ����
	PS_BUFF_DELETE_RES,				// ���� ����

	PS_ITEM_CREATE_RES,				// ������ ���� ����
	PS_ITEM_DELETE_RES,				// ������ ���� ����
	PS_ITEM_CHANGE_INFO_RES,		// ������ ���� ����

	PS_PUNISHMENT_INFO_START,		// ���� ���� ����
	PS_PUNISHMENT_INFO_INFO,		// ���� ����
	PS_PUNISHMENT_INFO_RES,			// ���� ���� ������ ��
	PS_PUNISHMENT_RES,				// �����ϱ� ����

	PS_REPEAT_NOTICE_LIST_START_NFY, // ���� ���� �˸�
	PS_REPEAT_NOTICE_INFO,			// ���� ����
	PS_REPEAT_NOTICE_LIST_RES,		// ���� ���� ����Ʈ ������ �Ϸ���� �� ������ ����
	PS_REPEAT_NOTICE_ADD_RES,		// ���� �߰�
	PS_REPEAT_NOTICE_CHANGE_RES,	// ���� ����
	PS_REPEAT_NOTICE_DELETE_RES,	// ���� ����
	PS_REALTIME_NOTICE_RES,			// �ǽð� ����

	PS_SERVER_STATUS_RES,			// ���� ���� ����	
	PS_SERVER_CONTROL_TURN_ON_RES,	// ���� ���� ��û ����
	PS_SERVER_CONTROL_TURN_OFF_RES,	// ���� ���� ��û ����
	PS_SERVER_LOCK_RES,				// ����/������/���� ä�� ��� ���� ��û ����
	PS_SERVER_UNLOCK_RES,			// ����/������/���� ä�� ��� ���� ��û ����
	PS_SERVER_USER_ALL_KICK_RES,		// ���� ���� ������� ���� logout ����
	PS_SERVER_AGENT_PATCH_RES,			// Server Agent ��ġ ��û�� ���� ����

	PS_SEARCH_ACCOUNTID_RES,			// ���̵� ���� ������ ã�´�

	PS_GM_CREATE_RES,				// GM ���� ����
	PS_GM_DELETE_RES,				// GM ���� ����
	PS_GM_CHANGE_INFO_RES,			// GM ���� ����
	PS_GM_CHANGE_ACCOUNTID_RES,		// GM ACCOUNTID ���� ����
	PS_GM_CHANGE_PASSWORD_RES,		// GM �н����� ����
	PS_GM_LIST_INFO,				// GM ����
	PS_GM_LIST_RES,					// GM ����Ʈ �˻�

	PS_GROUP_CREATE_RES,				// Group ����
	PS_GROUP_DELETE_RES,				// Group ����
	PS_GROUP_CHANGE_TOOL_AUTHORITY_RES,	// Group �� �� ���� ����
	PS_GROUP_CHANGE_COMMAND_AUTHORITY_RES,	// Group�� Ŀ�ǵ� ���� ����
	PS_GROUP_CHANGE_LEVEL_RES,			// Group ���� ����
	PS_GROUP_LOAD_TOOL_AUTHORITY_RES,		// Group Tool Authority ��û ����
	PS_GROUP_LIST_RES,					// Group ����Ʈ ��û
	PS_GROUP_CHANGE_ETC_AUTHORITY_RES,

	PS_FILTERING_LOAD_LIST_START,		// ����Ʈ ����
	PS_FILTERING_LOAD_LIST_DATA,		// ����Ʈ ������
	PS_FILTERING_LOAD_LIST_END,			// ����Ʈ ����
	PS_FILTERING_ADD_STRING_RES,		// ���ڿ� �߰�
	PS_FILTERING_DELETE_STRING_RES,		// ���ڿ� ����
	PS_FILTERING_FIND_STRING_RES,		// ���ڿ� ã��
	PS_FILTERING_CHANGE_STRING_RES,		// ���ڿ� ����
	PS_FILTERING_ADD_STRING_PKG_RES,	// �������� ���ڿ� �߰�
	PS_FILTERING_CLEAR_RES,				// ��� ���ڿ� ����
	
	PS_QUEST_ITEM_CREATE_RES,			// ����Ʈ ������ ���� [5/17/2007 SGpro]
	PS_QUEST_ITEM_DELETE_RES,			// ����Ʈ ������ ���� [5/17/2007 SGpro]
	PS_QUEST_ITEM_UPDATE_RES,			// ����Ʈ ������ ���� [5/17/2007 SGpro]

	PS_PROGRESS_QUEST_DELETE_RES,		// �������� ����Ʈ ���� [5/17/2007 SGpro]

	PS_SCHEDULE_ADD_RES,				// ���� ������ ���
	PS_SCHEDULE_DEL_RES,
	PS_SCHEDULE_UPDATE_RES,
	PS_SCHEDULE_LOAD_RES,				// ���� ������ �ε�

	PS_MAIL_LOADINFO_RES,				// [10/4/2007 SGpro]
	PS_MAIL_LOAD_DATA,					// [10/8/2007 SGpro]
	PS_MAIL_DEL_RES,					// [10/4/2007 SGpro]

	PS_ACCOUNTCOMMENTLOAD_RES,			// [10/11/2007 SGpro]
	PS_ACCOUNTCOMMENTUPDATE_RES,		// [10/11/2007 SGpro]

	//PS_SCHEDULELOAD_RES,				// [10/12/2007 SGpro]
	//PS_SCHEDULEUPDATE_RES,			// [10/12/2007 SGpro]
	
	PS_SERVER_GROUP_STATUS_INFO,		// [11/20/2007 SGpro]
	PS_SERVER_STATUS_INFO,				// [11/21/2007 SGpro]
	
	PS_ZENNYUPDATE_RES,					// [4/18/2008 SGpro]

	PS_GUILD_SEARCH_START,				// [7/1/2008 SGpro]
	PS_GUILD_SEARCH_INFO,				// [7/1/2008 SGpro]
	PS_GUILD_SEARCH_RES,				// [4/22/2008 SGpro]

	PS_GUILD_INFO_START,				// [4/22/2008 SGpro]
	PS_GUILD_INFO_MEMBER_INFO,			// [4/22/2008 SGpro]
	PS_GUILD_INFO_ITEM_INFO,			// [4/22/2008 SGpro]
	PS_GUILD_INFO_RES,					// [4/22/2008 SGpro]

	PS_GUILD_INFO_UPDATE_RES,			// [4/22/2008 SGpro]
	PS_GUILD_MASTER_MODIFY_RES,			// [4/22/2008 SGpro]
	PS_GUILD_SECONDMASTER_DEPRIVATION_RES,		// [4/22/2008 SGpro]
	PS_GUILD_SECONDMASTER_APPOINTMENT_RES,		// [4/22/2008 SGpro]
	PS_GUILD_MEMBER_SECEDE_RES,					// [4/22/2008 SGpro]

	PS_GUILD_ITEM_DELETE_RES,					// [4/22/2008 SGpro]
	PS_GUILD_ZENNY_MODIFY_RES,					// [4/22/2008 SGpro]
	PS_GUILD_CHAR_KICK_RES,

	PS_CHAR_DUPLICATE_RES,
	PS_CHAR_RESCUE_RES,

	PS_PETITION_LIST_START,						// (SP_PETITION_LIST_REQ) 1/3[5/7/2008 SGpro]
	PS_PETITION_LIST_INFO,						// (SP_PETITION_LIST_REQ) 2/3[5/7/2008 SGpro]
	PS_PETITION_LIST_RES,						// (SP_PETITION_LIST_REQ) 3/3[5/7/2008 SGpro]
	PS_PETITION_LIST_NFY,						// [5/7/2008 SGpro]

	PS_PETITION_DATALOAD_START,					// (SP_PETITION_DATALOAD_REQ) 1/7 [5/16/2008 SGpro]
	PS_PETITION_DATALOAD_COUNSEL_INFO,			// (SP_PETITION_DATALOAD_REQ) 2/7 [5/16/2008 SGpro]
	PS_PETITION_DATALOAD_LOG_INFO,	// (SP_PETITION_DATALOAD_REQ) 6/7 [5/16/2008 SGpro]
	PS_PETITION_DATALOAD_RES,					// (SP_PETITION_DATALOAD_REQ) 7/7 [5/16/2008 SGpro]

	PS_PETITION_GM_INSERT_RES,					// [5/7/2008 SGpro]
	PS_PETITION_START_RES,						// [5/7/2008 SGpro]
	PS_PETITION_INIT_RES,						// [5/7/2008 SGpro]
	PS_PETITION_RESERVE_RES,					// [5/7/2008 SGpro]
	PS_PETITION_FINISH_RES,						// [5/7/2008 SGpro]
	PS_PETITION_CHANGECATEGORY_RES,				// [5/8/2008 SGpro]
	PS_PETITION_GM_CHATTING_START_RES,			// [5/8/2008 SGpro]
	PS_PETITION_GM_CHATTING_END_RES,			// [5/8/2008 SGpro]
	PS_PETITION_SEARCH_RES,						// [5/15/2008 SGpro]
	PS_PETITION_CHAT_START_RES,					// [ by sooshia 2008-10-15 ]
	PS_PETITION_CHAT_GM_SAY_RES,				// gm->user [ by sooshia 2008-10-16 ]
	PS_PETITION_CHAT_USER_SAY_NFY,				// user->gm [ by sooshia 2008-10-16 ]
	PS_PETITION_CHAT_USER_END_NFY,				// [ by sooshia 2008-10-18 ]

	PS_CHANGEHONOR_RES,							// [6/23/2008 SGpro]
	//PS_CHANGEAMULET_RES,						// [6/23/2008 SGpro]

	PS_CHANGEMUDOSA_RES,						// [ by sooshia 2008-8-6 ]
	PS_CHANGERANKPOINT_RES,						// [ by sooshia 2008-08-07 ]

	PS_CHARACTERDELETE_RES,						// [6/26/2008 SGpro]
	PS_CHARACTERRESCUE_RES,						// [6/26/2008 SGpro]

	PS_GM_SERVER_COMMAND_RES,					// [6/30/2008 SGpro]

	PS_SERVER_COMMAND_START,
	PS_SERVER_COMMAND_INFO,
	PS_SERVER_COMMAND_END,

	PS_PLAYER_ENTER_NFY,
	PS_PLAYER_LEAVE_NFY,
	PS_CHARACTER_WATCH_RES,

	PS_SAME_USER_LOGIN_NFY,						// �ߺ� �α��� �˸�
	PS_MASTERSERVER_DISCONNECTED_NFY,			// ������ ������ ���������� �˸�
	PS_MASTERSERVER_CONNECTED_NFY,				// ������ ������ ����Ǿ����� �˸�
	PS_CHARACTER_INIT_SKILL_RES,
	PS_GAME_LOG_LIST_START,
	PS_GAME_LOG_LIST_DATA_READY_REQ,
	PS_GAME_LOG_LIST_DATA,
	PS_GAME_LOG_LIST_RES,
	PS_SERVER_STATUS_LOCALSETTING_INFO_RES,
	PS_SERVER_STATUS_LOCALSETTING_EDIT_RES,
	PS_CHARACTER_CHANGE_SP_RES,
	PS_CHARACTER_SKILL_ADD_RES,
	PS_CHARACTER_HTB_ADD_RES,
	PS_CHARACTER_CHANGE_EXP_RES,
	PS_CHARACTER_CHANGE_LEVEL_RES,
	PS_MULTI_MAIL_HISTORY_START_NFY,
	PS_MULTI_MAIL_HISTORY_READY_REQ,
	PS_MULTI_MAIL_HISTORY_DATA_NFY,
	PS_MULTI_MAIL_HISTORY_RES,

	PS_MULTI_MAIL_SEND_RES,

	PS_GM_COMMAND_LOG_LIST_START, // itzrnb
	PS_GM_COMMAND_LOG_LIST_DATA_READY_REQ,
	PS_GM_COMMAND_LOG_LIST_DATA,
	PS_GM_COMMAND_LOG_LIST_RES,

	PS_IP_MANAGE_SAMEIP_SEARCH_START,
	PS_IP_MANAGE_SAMEIP_SEARCH_DATA,
	PS_IP_MANAGE_SAMEIP_SEARCH_RES,

	PS_IP_MANAGE_SAMEIP_USER_LIST_START,
	PS_IP_MANAGE_SAMEIP_USER_LIST_DATA,
	PS_IP_MANAGE_SAMEIP_USER_LIST_RES,

	PS_IP_MANAGE_INFO_SEARCH_START,
	PS_IP_MANAGE_INFO_SEARCH_DATA,
	PS_IP_MANAGE_INFO_SEARCH_RES,

	PS_IP_MANAGE_INFO_EDIT_RES,

	PS_GM_LOG_LIST_START,
	PS_GM_LOG_LIST_DATA_READY_REQ,
	PS_GM_LOG_LIST_DATA,
	PS_GM_LOG_LIST_RES,


	PS_OPCODE_DUMMY,
	PS_OPCODE_END = PS_OPCODE_DUMMY - 1
};


//------------------------------------------------------------------
//
//------------------------------------------------------------------
const char * NtlGetPacketName_PS(WORD wOpCode);
//------------------------------------------------------------------


#pragma pack(1)

//------------------------------------------------------------------
BEGIN_PROTOCOL(PS_HEARTBEAT)
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(PS_LOGIN_RES)
	WORD					wResultCode;								// ���

	ACCOUNTID				gmAccountID;								// GM Account ID
	WCHAR					wszUser[NTL_MAX_SIZE_USERID_UNICODE + 1];	// ID
	DWORD					dwGroupSerial;								// Group Serial
	ACCOUNTID				accountID;									// Account ID(���ӿ��� ���)
	WORD					wLVersion;
	WORD					wRVersion; // by sooshia 07/22/2008 L,R �������� �и�
	bool					bIsMasterServerOn;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(PS_CHANGE_PASSWORD_RES)
	WORD					wResultCode;								// ���

	WCHAR					wszUserID[NTL_MAX_SIZE_USERID_UNICODE + 1];	// �н����带 ������ ID
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(PS_SERVERFARM_NAME_RES)
	WORD					wResultCode;			// ���

	BYTE					byServerFarmCount;		// �������� ����
	sSERVERFARM_NAME		asServerFarmName[1];	// ���� ���� ����
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(PS_SEARCH_PC_DATA_INFO_START)
	BYTE					byUseType;				// �� ������ � �뵵�� ����� ������ eSEARCH_USE_TYPE
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(PS_SEARCH_PC_DATA_INFO)
	BYTE					byUseType;				// �� ������ � �뵵�� ����� ������ eSEARCH_USE_TYPE
	sCHARSEARCH_ENTITY		sCharacterData;		// ��� ����Ÿ
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(PS_SEARCH_PC_DATA_RES)
	ACCOUNTID				accountID;				// ���ٸ��Ⱑ ���������� �Ǹ鼭 AccountID�� �ʿ����� [4/16/2008 SGpro]
	WORD					wResultCode;
	BYTE					byUseType;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(PS_PC_DATA_RES)
	WORD					wResultCode;

	SERVERFARMID			serverFarmID;			// ������ ID

	ACCOUNTID				accountID;

	sDBO_TIME				tCreateTime;				//ĳ���� ������
	sDBO_TIME				tRecentEnd;					//���� �α׾ƿ� �ð�
	int						nIP;						//���� ���� IP

	WCHAR					wszUserID[NTL_MAX_SIZE_USERID_UNICODE + 1];
	sPC_DATA				sPcData;
	sQUEST_COMPLETE_DATA	sQuestCompleteData;		// ����Ʈ �Ϸ� ����
	sRANKBATTLE_SCORE_INFO	sRankBattleScoreInfo; // [ by sooshia 2008-08-07 ]

	BYTE					byInvenItemCount;			// ĳ���Ͱ� ������ �ִ� ������
	BYTE					bySkillCount;
	BYTE					byBuffCount;
	BYTE					byHTBSkillCount;
	BYTE					byQuestProgressCount;		// ����Ʈ ���� ����
	BYTE					byQuestInventoryCount;		// ����Ʈ ������ ����
	BYTE					byQuickSlotCount;
	WCHAR					wszGuildName[NTL_MAX_SIZE_GUILD_NAME_IN_UNICODE + 1];

	sITEM_DATA				asInvenItemData[1];
	sSKILL_DATA				asSkill[1];
	sBUFF_DATA				asBuff[1];
	sHTB_SKILL_DATA			asHTBSkill[1];
	sQUEST_PROGRESS_DATA	asQuestProgress[1];
	sQUEST_INVENTORY_DATA	asQuestInventory[1];
	sQUICK_SLOT_DATA		asQuickSlotData[1];

	sITEM_DATA *			GetInvenItemDataPtr(int nCount = 0) { return &asInvenItemData[nCount]; }
	sSKILL_DATA *			GetSkillDataPtr(int nCount = 0) { return ( (sSKILL_DATA*) GetInvenItemDataPtr(byInvenItemCount) ) + nCount; }
	sBUFF_DATA *			GetBuffDataPtr(int nCount = 0) { return ( (sBUFF_DATA *) GetSkillDataPtr(bySkillCount) ) + nCount; }
	sHTB_SKILL_DATA *		GetHTBSkillDataPtr(int nCount = 0) { return ( (sHTB_SKILL_DATA *) GetBuffDataPtr(byBuffCount) ) + nCount; }
	sQUEST_PROGRESS_DATA *	GetQuestProgressDataPtr(int nCount = 0) { return ( (sQUEST_PROGRESS_DATA *) GetHTBSkillDataPtr(byHTBSkillCount) ) + nCount; }
	sQUEST_INVENTORY_DATA *	GetQuestInventoryDataPtr(int nCount = 0) { return ( (sQUEST_INVENTORY_DATA *) GetQuestProgressDataPtr(byQuestProgressCount) ) + nCount; }
	sQUICK_SLOT_DATA*		GetQuickSlotDataPtr(int nCount = 0) { return ( (sQUICK_SLOT_DATA *) GetQuestInventoryDataPtr(byQuestInventoryCount) )+ nCount; }
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(PS_CHARACTER_LOGIN_INFO_RES)
	WORD				wResultCode;

	ACCOUNTID			accountId;			// User Account ID
	BYTE				byState;			// ���� ���� ���� : eNTL_USER_CONNECTION_STATE
	WCHAR				wszStartTime[NTL_GM_TOOL_MAX_DATE_STRING_LENGTH + 1];		// Start Time
	BYTE				byServerIndex;		// Server Index
	BYTE				byServerFarmID;		// Server Farm ID
	BYTE				byChannelID;		// Channel ID
	CHARACTERID			charID;				// �������� CharacterID Default 0 
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(PS_CHARACTER_KICK_INFO_RES)
	WORD				wResultCode;
	ACCOUNTID			accountId;
	bool				bIsBlock;
	DWORD				dwStartTime;		// ���� �ð�
	BYTE				byPeriodType;		// �Ⱓ Ÿ��(day, minute) : ePUNISH_PERIOD_DAY
	DWORD				dwPeriod;			// �Ⱓ
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(PS_CHARACTER_KICK_RES)
	WORD				wResultCode;

	SERVERFARMID		serverFarmId;
	ACCOUNTID			accountId;
	CHARACTERID			charId;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(PS_CHARACTER_CHANGE_NAME_RES)
	WORD					wResultCode;

	SERVERFARMID			serverFarmID;
	ACCOUNTID				accountID;
	CHARACTERID				charID;
	WCHAR					wszCharName[NTL_MAX_SIZE_CHAR_NAME_UNICODE + 1];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( PS_CHARNAME_MODIFY_GMTOOL_RES )
	WORD				wResultCode;
	SERVERFARMID		serverFarmID; 
	ACCOUNTID			accountID; 
	CHARACTERID			charID;	
	WCHAR				wszCharName[NTL_MAX_SIZE_CHAR_NAME_UNICODE + 1];
	bool				bBlockStringCheck;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(PS_CHAR_CHANGE_BIND_LOCATION_RES)
	WORD					wResultCode;

	ACCOUNTID				accountID;
	SERVERFARMID			serverFarmID;
	CHARACTERID				charID;
	TBLIDX					worldTblidx;
	WORLDID					worldId;
	sVECTOR3				vBindLoc;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(PS_CHAR_CHANGE_CUR_LOCATION_RES)
	WORD					wResultCode;

	ACCOUNTID				accountID;
	SERVERFARMID			serverFarmID;
	CHARACTERID				charID;
	TBLIDX					worldTblidx;
	WORLDID					worldId;
	sVECTOR3				vLoc;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(PS_CHAR_SKILL_DELETE_RES)
	WORD					wResultCode;
	CHARACTERID				charId;
	BYTE					bySlot;
	TBLIDX					skillId;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(PS_CHAR_HTBSKILL_DELETE_RES)
	WORD					wResultCode;
	SERVERFARMID			serverFarmId;
	CHARACTERID				charId;
	TBLIDX					skillId;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(PS_CHAR_BUFFSKILL_DELETE_RES)
	WORD					wResultCode;
	CHARACTERID				charId;
	TBLIDX					sourceTblidx;
	BYTE					bySourceType;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(PS_SKILL_DELETE_RES)
	WORD				wResultCode;

	SERVERFARMID		serverFarmId;		// Server Farm ID
	CHARACTERID			charId;				// Character ID
	BYTE				bySlot;				// Skill �� �ִ� Slot
	TBLIDX				skillId;			// Skill �� Table Index
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(PS_HTB_SKILL_DELETE_RES)
	WORD				wResultCode;

	SERVERFARMID		serverFarmId;		// Server Farm ID
	CHARACTERID			charId;				// Character ID
	TBLIDX				skillId;			// Skill �� Table Index
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(PS_BUFF_DELETE_RES)
	WORD				wResultCode;

	CHARACTERID			charId;				// Character ID
	TBLIDX				sourceTblidx;		// Buff�� Table Index
	BYTE				bySourceType;		// Buff�� Type : eDBO_OBJECT_SOURCE
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(PS_ITEM_CREATE_RES)
	WORD					wResultCode;

	SERVERFARMID			serverFarmID;
	sITEM_DATA				sItem;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(PS_ITEM_DELETE_RES)
	WORD					wResultCode;

	SERVERFARMID			serverFarmID;
	CHARACTERID				charID;
	sITEM_DELETE_DATA		sItem;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(PS_ITEM_CHANGE_INFO_RES)
	WORD					wResultCode;

	SERVERFARMID			serverFarmID;
	sITEM_DATA				sItem;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(PS_PUNISHMENT_INFO_START)
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(PS_PUNISHMENT_INFO_INFO)
	sPUNISHMENT_ENTITY		sPunishmentInfo;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(PS_PUNISHMENT_INFO_RES)
	WORD					wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(PS_PUNISHMENT_RES)
	WORD			wResultCode;

	BYTE			byApply;			// ePUNISH_APPLY_TYPE

	BYTE			byPunishType;		// eGM_PUNISH_PASSIVE_TYPE
	ACCOUNTID		accountID;			// ���� ���϶� ���
	CHARACTERID		charID;				// ĳ���� ���϶� ���

	BYTE			byPeriodType;		// Punish Period Type : ePUNISH_PERIOD_DAY
	DWORD			dwPeriod;			// �Ⱓ

	// ����
	BYTE			byReasonType;
	WCHAR			wszReason[NTL_MAX_PUNISH_REASON_LENGTH+1];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(PS_REPEAT_NOTICE_LIST_START_NFY)
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(PS_REPEAT_NOTICE_INFO)
	sGM_REPEAT_NOTICE_ENTITY		noticeInfo;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(PS_REPEAT_NOTICE_LIST_RES)
	WORD						wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(PS_REPEAT_NOTICE_ADD_RES)
	WORD						wResultCode;

	sGM_REPEAT_NOTICE_ENTITY	sNotice;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(PS_REPEAT_NOTICE_CHANGE_RES)
	WORD						wResultCode;

	sGM_REPEAT_NOTICE_ENTITY	sNotice;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(PS_REPEAT_NOTICE_DELETE_RES)
	WORD						wResultCode;

	DWORD						dwSerial;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(PS_REALTIME_NOTICE_RES)
	WORD					wResultCode;
	BYTE					byNoticeType;	// eSERVER_TEXT_TYPE
	SERVERFARMID			serverFarmID;
	BYTE					byChannelID;
	WCHAR					pszNotice[NTL_MAX_LENGTH_OF_CHAT_MESSAGE_UNICODE+1];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(PS_SERVER_STATUS_RES)
	WORD					wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(PS_SERVER_CONTROL_TURN_ON_RES)
	WORD					wResultCode;

	BYTE					byServerType;
	SERVERFARMID			serverFarmId;
	BYTE					byServerChannelIndex;
	BYTE					byServerIndex;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(PS_SERVER_CONTROL_TURN_OFF_RES)
	WORD					wResultCode;

	BYTE					byServerType;
	SERVERFARMID			serverFarmId;
	BYTE					byServerChannelIndex;
	BYTE					byServerIndex;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(PS_SERVER_LOCK_RES)
	WORD					wResultCode;

	BYTE					byServerType;
	SERVERFARMID			serverFarmId;
	BYTE					byServerChannelIndex;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(PS_SERVER_UNLOCK_RES)
	WORD					wResultCode;

	BYTE					byServerType;
	SERVERFARMID			serverFarmId;
	BYTE					byServerChannelIndex;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(PS_SERVER_USER_ALL_KICK_RES)
	WORD					wResultCode;

	BYTE					byServerType;
	SERVERFARMID			serverFarmId;
	BYTE					byServerChannelIndex;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(PS_SERVER_AGENT_PATCH_RES)
	WORD					wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(PS_SEARCH_ACCOUNTID_RES)
	WORD					wResultCode;

	WCHAR					wszUserID[NTL_MAX_SIZE_USERID_UNICODE + 1];
	ACCOUNTID				accountID;
	BYTE					byUseType;	// eGM_ACCOUNTID_INFO_USE_TYPE
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(PS_GM_CREATE_RES)
	WORD					wResultCode;

	WCHAR					wszUser[NTL_MAX_SIZE_USERID_UNICODE + 1];
	WCHAR					wszPass[NTL_MAX_SIZE_USERPW_UNICODE + 1];
	DWORD					dwGroupSerial;
	uGM_TOOL_IP_ADDRESS		uIPAddress;	// ���� ���� ip

	WCHAR					wszName[NTL_MAX_SIZE_TOOL_USERNAME_UNICODE + 1];
	WCHAR					wszPartName[NTL_MAX_SIZE_TOOL_PARTNAME_UNICODE + 1];
	WCHAR					wszComment[NTL_MAX_SIZE_TOOL_COMMENT_UNICODE + 1];

	ACCOUNTID				accountID;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(PS_GM_DELETE_RES)
	WORD					wResultCode;

	ACCOUNTID				gmAccountID;
	ACCOUNTID				accountID;	//Game Serial
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(PS_GM_CHANGE_INFO_RES)
	WORD					wResultCode;

	ACCOUNTID				gmAccoundID;								// �����ų GM�� AccountID
	ACCOUNTID				accountID;
	DWORD					dwGroupSerial;
	uGM_TOOL_IP_ADDRESS		uIPAddress;
	WCHAR					wszName[NTL_MAX_SIZE_TOOL_USERNAME_UNICODE + 1];
	WCHAR					wszPartName[NTL_MAX_SIZE_TOOL_PARTNAME_UNICODE + 1];
	WCHAR					wszComment[NTL_MAX_SIZE_TOOL_COMMENT_UNICODE + 1];
	WCHAR					wszGMName[NTL_MAX_SIZE_TOOL_GM_NAME_UNICODE + 1];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(PS_GM_CHANGE_ACCOUNTID_RES)
	WORD					wResultCode;

	ACCOUNTID				gmAccoundID;								// �����ų GM�� AccountID
	ACCOUNTID				newAccountID;								// Game Server������ GM ID
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(PS_GM_CHANGE_PASSWORD_RES)
	WORD					wResultCode;

	ACCOUNTID				gmAccoundID;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(PS_GM_LIST_INFO)
	sGM_ENTITY				asGmList;										// GM ����
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(PS_GM_LIST_RES)
	WORD					wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(PS_GROUP_CREATE_RES)
	WORD					wResultCode;

	WCHAR					wszGroupName[NTL_MAX_SIZE_TOOL_GROUPNAME_UNICODE + 1];	// Group Name
	BYTE					byGroupLevel;									// Group Level
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(PS_GROUP_DELETE_RES)
	WORD					wResultCode;

	DWORD					dwGroupSerial;									// ������ �׷� �ø���
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(PS_GROUP_CHANGE_TOOL_AUTHORITY_RES)
	WORD					wResultCode;

	DWORD					dwGroupSerial;									// ������ �׷�
	sGM_TOOL_AUTH_FLAG		sToolAuth;										// ����
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(PS_GROUP_CHANGE_COMMAND_AUTHORITY_RES)
	WORD					wResultCode;

	DWORD					dwGroupSerial;									// ������ �׷�
	sGM_COMMAND_AUTH_FLAG	sCommandAuth;									// ����
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(PS_GROUP_CHANGE_LEVEL_RES)
	WORD					wResultCode;

	DWORD					dwGroupSerial;									// ������ �׷�
	BYTE					byGroupLevel;									// ������ ����
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(PS_GROUP_LOAD_TOOL_AUTHORITY_RES)
	WORD					wResultCode;

	DWORD					dwGroupSerial;
	sGM_TOOL_AUTH_FLAG		sToolAuthFlag;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(PS_GROUP_LIST_RES)
	WORD					wResultCode;

	DWORD					dwGroupCount;
	sGM_GROUP_ENTITY		aGroupList[1];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(PS_GROUP_CHANGE_ETC_AUTHORITY_RES)
	WORD					wResultCode;

	DWORD					dwGroupSerial;									// ������ �׷�
	sGM_ETC_AUTH_FLAG		sEtcAuth;										// ����
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(PS_FILTERING_LOAD_LIST_START)
	WORD					wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(PS_FILTERING_LOAD_LIST_DATA)
	WORD					wCount;
	sBLOCK_STRING_DATA		asString[1];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(PS_FILTERING_LOAD_LIST_END)
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(PS_FILTERING_ADD_STRING_RES)
	WORD					wResultCode;

	sBLOCK_STRING_DATA		sString;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(PS_FILTERING_DELETE_STRING_RES)
	WORD					wResultCode;

	sBLOCK_STRING_DATA		sString;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(PS_FILTERING_FIND_STRING_RES)
	WORD					wResultCode;

	WORD					wCount;
	sBLOCK_STRING_DATA		asString[1];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(PS_FILTERING_CHANGE_STRING_RES)
	WORD					wResultCode;

	sBLOCK_STRING_DATA		sCurString;
	sBLOCK_STRING_DATA		sNewString;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(PS_FILTERING_ADD_STRING_PKG_RES)
	WORD						wResultCode;

	WORD						wCount;
	sBLOCK_STRING_DATA			asString[1];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(PS_FILTERING_CLEAR_RES)
	WORD						wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
// [5/17/2007 SGpro]
BEGIN_PROTOCOL( PS_QUEST_ITEM_CREATE_RES )
	WORD				wResultCode;
	SERVERFARMID		serverFarmID;
	CHARACTERID			charId;				// Character ID
	TBLIDX				tblidx;
	BYTE				byCurStackCount;
	BYTE				byPos;				// �κ��丮������ �������� ��ġ by ju-hyeong
END_PROTOCOL()
//------------------------------------------------------------------
// [5/17/2007 SGpro]
BEGIN_PROTOCOL( PS_QUEST_ITEM_DELETE_RES )
	WORD				wResultCode;
	SERVERFARMID		serverFarmID;
	CHARACTERID			charId;				// Character ID
	TBLIDX				tblidx;
	BYTE				byPos;				// �κ��丮������ �������� ��ġ by ju-hyeong
END_PROTOCOL()
//------------------------------------------------------------------
// [5/17/2007 SGpro]
BEGIN_PROTOCOL( PS_QUEST_ITEM_UPDATE_RES )
	WORD				wResultCode;
	SERVERFARMID		serverFarmID;
	CHARACTERID			charId;				// Character ID
	TBLIDX				tblidx;
	BYTE				byCurStackCount;
	BYTE				byPos;				// �κ��丮������ �������� ��ġ by ju-hyeong
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( PS_PROGRESS_QUEST_DELETE_RES )
	WORD				wResultCode;
	SERVERFARMID		serverFarmID;
	CHARACTERID			charId;
	QUESTID				questId;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( PS_SCHEDULE_ADD_RES )
	WORD				wResultCode;
	SERVERFARMID		serverFarmID;
	BYTE				byEventType;		//eSCHEDULE_EVENT_TYPE
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( PS_SCHEDULE_DEL_RES )
	WORD				wResultCode;
	SERVERFARMID		serverFarmID;
	BYTE				byEventType;		//eSCHEDULE_EVENT_TYPE
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( PS_SCHEDULE_UPDATE_RES )
	WORD				wResultCode;
	SERVERFARMID		serverFarmID;
	BYTE				byEventType;		//eSCHEDULE_EVENT_TYPE
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( PS_SCHEDULE_LOAD_RES )
	WORD				wResultCode;
	SERVERFARMID		serverFarmID;
	BYTE				byEventType;		//eSCHEDULE_EVENT_TYPE
	__int64				nStartTime;
	__int64				nEndTime;
	int					nMainTerm;
	int					nSubTerm;
	BYTE				byTermType;			//eSCHEDULE_TERM_TYPE
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( PS_MAIL_LOADINFO_RES )
	WORD				wResultCode;
	SERVERFARMID		serverFarmID;
	CHARACTERID			charId;
END_PROTOCOL()
//-----------------------------------------------------------------------------------
BEGIN_PROTOCOL( PS_MAIL_LOAD_DATA )
	sMAIL_NEW_GM_PROFILE sData;		
	BYTE	byTextSize;
	WCHAR	wszText[NTL_MAX_LENGTH_OF_MAIL_MESSAGE_IN_UNICODE + 1];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( PS_MAIL_DEL_RES )
	WORD				wResultCode;
	SERVERFARMID		serverFarmID;
	CHARACTERID			charId;
	MAILID				mailID;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( PS_ACCOUNTCOMMENTLOAD_RES )
	WORD						wResultCode;
	sGM_PACKET_ACCOUNT_COMMENT	sAccountComment;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( PS_ACCOUNTCOMMENTUPDATE_RES )
	WORD						wResultCode;
	sGM_PACKET_ACCOUNT_COMMENT	sAccountComment;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( PS_SERVER_GROUP_STATUS_INFO )
	sSERVERGROUPSTATUS_ENTITY	sServerGroupStatusList;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(PS_SERVER_STATUS_INFO)
	sSERVERSTATUS_ENTITY	sServerStatusList;
	char					szRecentModifiedDate[NTL_MAX_LENGTH_OF_RECENT_DATE + 1];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(PS_ZENNYUPDATE_RES)
	WORD			wResultCode;
	BYTE			byUpdateType; //eCONTAINER_TYPE
	SERVERFARMID	serverfarmID;
	ACCOUNTID		accountID;
	CHARACTERID		charID;
	DWORD			dwZenny;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( PS_GUILD_SEARCH_START )
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( PS_GUILD_SEARCH_INFO )
	sDBO_GMTOOL_GUILD_SEARCH_DATA	sGuildData;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( PS_GUILD_SEARCH_RES )		//3
	WORD				wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( PS_GUILD_INFO_START )		//1
	WORD				wMemberCount;
	WORD				wItemCount;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( PS_GUILD_INFO_MEMBER_INFO )	//2
	sDBO_GMTOOL_GUILD_MEMBER_DATA sGuildMember;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( PS_GUILD_INFO_ITEM_INFO )	//3
	sITEM_DATA			sItemData;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( PS_GUILD_INFO_RES )			//4
	WORD					wResultCode;
	sDBO_GMTOOL_GUILD_DATA	sGuildInfo;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( PS_GUILD_INFO_UPDATE_RES )
	WORD				wResultCode;
	SERVERFARMID		serverFarmID;
	GUILDID				guildId;
	sDBO_GUILD_CAHNGE_INFO		sInfo;
	BYTE				byUpdateType;	// eDBO_GUILD_UPDATE_TYPE
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( PS_GUILD_MASTER_MODIFY_RES )
	WORD				wResultCode;
	SERVERFARMID		serverFarmID;
	GUILDID				guildId;
	CHARACTERID			charId;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( PS_GUILD_SECONDMASTER_DEPRIVATION_RES )
	WORD				wResultCode;
	SERVERFARMID		serverFarmID;
	GUILDID				guildId;
	CHARACTERID			charId;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( PS_GUILD_SECONDMASTER_APPOINTMENT_RES )
	WORD				wResultCode;
	SERVERFARMID		serverFarmID;
	GUILDID				guildId;
	CHARACTERID			charId;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( PS_GUILD_MEMBER_SECEDE_RES )
	WORD				wResultCode;
	SERVERFARMID		serverFarmID;
	GUILDID				guildId;
	CHARACTERID			charId;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( PS_GUILD_ITEM_DELETE_RES )
	WORD				wResultCode;
	SERVERFARMID		serverFarmID;
	GUILDID				guildId;
	sITEM_DELETE_DATA	sItem;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( PS_GUILD_ZENNY_MODIFY_RES )
	WORD				wResultCode;
	SERVERFARMID			serverFarmID;
	GUILDID					guildId;
	DWORD					dwZenny;
	BYTE					byUpdateType; //eCONTAINER_TYPE
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( PS_GUILD_CHAR_KICK_RES )
	WORD				wResultCode;
	BYTE				byPunishType;		// eGM_PUNISH_PASSIVE_TYPE

	BYTE				byPeriodType;		// Punish Period Type : ePUNISH_PERIOD_DAY
	DWORD				dwPeriod;			// �Ⱓ
	// ����
	BYTE				byReasonType;
	WCHAR				wszReason[NTL_MAX_PUNISH_REASON_LENGTH+1];
	bool				bApply;					// true : ����, false : ����

	GUILDID				guildId;
	BYTE				byCount;
	ACCOUNTID			aAccountID[DBO_MAX_MEMBER_IN_GUILD];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( PS_CHAR_DUPLICATE_RES )
	WORD				wResultCode;
	SERVERFARMID		serverFarmID;
	ACCOUNTID			accountID;				// GM ����
	CHARACTERID			originalCharID;			// ������ Character
	CHARACTERID			outCharID;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(PS_CHAR_RESCUE_RES)
	WORD				wResultCode;
	SERVERFARMID		serverFarmID;
	CHARACTERID			charID;					// ������ character
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( PS_PETITION_LIST_START )
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( PS_PETITION_LIST_INFO )
	sPETITIONLISTDATA	sPetitionData;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( PS_PETITION_LIST_RES )
	WORD				wResultCode;
	int					nPageCount;//��������
	int					nPeitionListCount;
	int					nCurrentPage;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( PS_PETITION_LIST_NFY )
	sPETITIONLISTDATA		sPetitionData;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( PS_PETITION_DATALOAD_START )
	int						nLogCount;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( PS_PETITION_DATALOAD_COUNSEL_INFO )
	sPETITIONDATA			sPetitionData;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( PS_PETITION_DATALOAD_LOG_INFO )
	sPETITION_COUNSELDATA	sPetitionCounselData;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( PS_PETITION_DATALOAD_RES )
	WORD					wResultCode;
	BYTE					byDataLoadType; //ePETITIONDATALOADTYPE
	bool					bImmediatelyConsultStart;//true�̸� ��� ������ �ٷ� �Ѵ�
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( PS_PETITION_GM_INSERT_RES )
	WORD				wResultCode;
	PETITIONID			petitionID;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( PS_PETITION_START_RES )
	WORD				wResultCode;
	PETITIONID			petitionID;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( PS_PETITION_INIT_RES )
	WORD				wResultCode;	
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( PS_PETITION_RESERVE_RES )
	WORD				wResultCode;
	PETITIONID			petitionID;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( PS_PETITION_FINISH_RES )
	WORD				wResultCode;
	PETITIONID			petitionID;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( PS_PETITION_CHANGECATEGORY_RES )
	WORD				wResultCode;
	PETITIONID			petitionID;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( PS_PETITION_GM_CHATTING_START_RES )
	WORD				wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( PS_PETITION_GM_CHATTING_END_RES )
	WORD				wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( PS_PETITION_SEARCH_RES )
	WORD				wResultCode;
	PETITIONID			petitionID;
	GMACCOUNTID			gmAccountID;
	CHARACTERID			gmCharacterID;
	SERVERFARMID		serverfarmID;
	ACCOUNTID			userAccountID;
	CHARACTERID			userCharacterID;
	WCHAR				awchCharacterName[NTL_MAX_SIZE_CHAR_NAME_UNICODE + 1];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( PS_CHANGEHONOR_RES )
	WORD				wResultCode;
	SERVERFARMID		serverFarmID;
	CHARACTERID			charId;
	DWORD				dwNewHonorPoint;
END_PROTOCOL()
//------------------------------------------------------------------
//BEGIN_PROTOCOL( PS_CHANGEAMULET_RES )
//	WORD				wResultCode;
//	SERVERFARMID		serverFarmID;
//	CHARACTERID			charId;
//	DWORD				dwNewAmuletPoint;
//END_PROTOCOL()
////------------------------------------------------------------------
BEGIN_PROTOCOL( PS_CHANGEMUDOSA_RES )
	WORD				wResultCode;
	SERVERFARMID		serverFarmID;
	CHARACTERID			charId;
	DWORD				dwNewMudosaPoint;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( PS_CHANGERANKPOINT_RES )
	WORD				wResultCode;
	SERVERFARMID		serverFarmID;
	CHARACTERID			charId;
	DWORD				dwNewRankPoint;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( PS_CHARACTERDELETE_RES )
	WORD				wResultCode;
	SERVERFARMID		serverFarmID;
	CHARACTERID			charId;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( PS_CHARACTERRESCUE_RES )
	WORD				wResultCode;
	SERVERFARMID		serverFarmID;
	CHARACTERID			charId;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( PS_GM_SERVER_COMMAND_RES )
	SERVERFARMID		serverfarmID;
	SERVERCHANNELID		serverchannelID;
	SERVERINDEX			serverIndex;
	WORD				wMessageLengthInUnicode;
	WCHAR				awchMessage[NTL_MAX_LENGTH_OF_CHAT_MESSAGE_UNICODE + 1];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(PS_SERVER_COMMAND_START)
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(PS_SERVER_COMMAND_INFO)
	WORD				wMessageLengthInUnicode;
	WCHAR				awchMessage[NTL_MAX_LENGTH_OF_CHAT_MESSAGE_UNICODE + 1];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(PS_SERVER_COMMAND_END)
	WORD				wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(PS_PLAYER_ENTER_NFY)
	ACCOUNTID			userAccountID;
	SERVERFARMID		serverFarmID;
	WCHAR				CharacterName[NTL_MAX_SIZE_CHAR_NAME_UNICODE+1];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(PS_PLAYER_LEAVE_NFY)
	ACCOUNTID			userAccountID;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(PS_CHARACTER_WATCH_RES)
	bool				bIsConnecting;
	ACCOUNTID			userAccountID;
	SERVERFARMID		serverFarmID;
	WCHAR				CharacterName[NTL_MAX_SIZE_CHAR_NAME_UNICODE+1];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(PS_SAME_USER_LOGIN_NFY)
	int						nIP; //���� ������ ���� IP
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(PS_MASTERSERVER_DISCONNECTED_NFY)
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(PS_MASTERSERVER_CONNECTED_NFY)
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( PS_PETITION_CHAT_START_RES )
	WORD				wResultCode;
	ACCOUNTID			userAccountID;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( PS_PETITION_CHAT_GM_SAY_RES )
	WORD				wResultCode;
	ACCOUNTID			userAccountID;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( PS_PETITION_CHAT_USER_SAY_NFY )
	ACCOUNTID			userAccountID;
	WORD				wMessageLengthInUnicode;
	WCHAR				awchMessage[NTL_MAX_LENGTH_OF_CHAT_MESSAGE_UNICODE + 1];
	WCHAR				CharacterName[NTL_MAX_SIZE_CHAR_NAME_UNICODE+1];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( PS_PETITION_CHAT_USER_END_NFY )
	ACCOUNTID			userAccountID;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( PS_CHARACTER_INIT_SKILL_RES )
	WORD				wResultCode;
	BYTE				byNewClass;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( PS_GAME_LOG_LIST_START )
	int				nLogCount;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( PS_GAME_LOG_LIST_DATA_READY_REQ )
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( PS_GAME_LOG_LIST_DATA )
	sDBO_TIME		logTime;
	DWORD			dwReportType;
	SERVERFARMID	ServerFarmID;
	int				nIP;
	WCHAR			wszReportName[NTL_MAX_LENGTH_REPORT_NAME_UNICODE + 1];

	ACCOUNTID		idAccount;
	CHARACTERID		idCharacter;
	WCHAR			wszAccountID[NTL_MAX_SIZE_USERID_UNICODE + 1];
	WCHAR			wszCharName[NTL_MAX_SIZE_CHAR_NAME_UNICODE +1];

	BYTE			byLevel;
	DWORD			dwEXP;

	TBLIDX			idTid;
	PARTYID			idParty;
	GUILDID			idGuild;
	TBLIDX			idSerial;

	int				nCount1;
	int				nCount2;
	int				nSum;

	TBLIDX			idTargetObject;
	WCHAR			wszTargetObject[NTL_MAX_LENGTH_REPORT_NAME_UNICODE +1];

	float			fPositionX;
	float			fPositionY;
	float			fPositionZ;

	DWORD			dwParameter[NTL_REPORT_LOG_PARAMATER_MAX];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( PS_GAME_LOG_LIST_RES )
	WORD				wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( PS_SERVER_STATUS_LOCALSETTING_INFO_RES )
	int					nFileLength;
	char				szFileName[NTL_MAX_SIZE_FILE_NAME + 1];
	char				szFileContent[NTL_MAX_SIZE_LOCALSETTING_FILE + 1];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( PS_SERVER_STATUS_LOCALSETTING_EDIT_RES )
	WORD				wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( PS_CHARACTER_CHANGE_SP_RES )
	WORD				wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( PS_CHARACTER_SKILL_ADD_RES )
	WORD				wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( PS_CHARACTER_HTB_ADD_RES )
	WORD				wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( PS_CHARACTER_CHANGE_EXP_RES )
	WORD				wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( PS_CHARACTER_CHANGE_LEVEL_RES )
	WORD				wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( PS_MULTI_MAIL_HISTORY_START_NFY )
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( PS_MULTI_MAIL_HISTORY_READY_REQ )
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( PS_MULTI_MAIL_HISTORY_DATA_NFY )
	int					m_nHistoryNumber;
	WCHAR				m_wszText[NTL_MAX_LENGTH_OF_MAIL_MESSAGE + 1];
	sDBO_TIME			m_timeMailSent;
	ACCOUNTID			m_idGMAccount;
	int					m_nSentCount;
	TBLIDX				m_nItemNo;
	DWORD				m_dwZenny;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( PS_MULTI_MAIL_HISTORY_RES )
	WORD				wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( PS_MULTI_MAIL_SEND_RES )
	int					m_nFailCount;
	WCHAR				wszTargetName[NTL_MAX_COUNT_MULTI_MAIL][NTL_MAX_SIZE_CHAR_NAME_UNICODE + 1];	// ���� ĳ�� �̸�
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( PS_GM_COMMAND_LOG_LIST_START )
	int				nLogCount;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( PS_GM_COMMAND_LOG_LIST_DATA_READY_REQ )
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( PS_GM_COMMAND_LOG_LIST_DATA )
	sDBO_TIME		logTime;
	SERVERFARMID	ServerFarmID;	
	WCHAR			wszAccountID[NTL_MAX_SIZE_USERID_UNICODE + 1];
	WCHAR			wszCommand[NTL_MAX_LENGTH_OF_CHAT_MESSAGE + 1];
	WCHAR			wszTargetCharName[NTL_MAX_SIZE_CHAR_NAME_UNICODE + 1];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( PS_GM_COMMAND_LOG_LIST_RES )
	WORD				wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( PS_IP_MANAGE_SAMEIP_SEARCH_START )
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( PS_IP_MANAGE_SAMEIP_SEARCH_DATA )
	int				nIP;
	int				nCount;
	BYTE			byIPType;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( PS_IP_MANAGE_SAMEIP_SEARCH_RES )
	WORD				wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( PS_IP_MANAGE_SAMEIP_USER_LIST_START )
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( PS_IP_MANAGE_SAMEIP_USER_LIST_DATA )
	int					nIP;
	ACCOUNTID			idAccount;
	WCHAR				awchUserID[ NTL_MAX_SIZE_USERID_UNICODE + 1];
	SERVERFARMID		serverfarmID;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( PS_IP_MANAGE_SAMEIP_USER_LIST_RES )
	WORD				wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( PS_IP_MANAGE_INFO_SEARCH_START )
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( PS_IP_MANAGE_INFO_SEARCH_DATA )
	int					nIP;
	BYTE				byIPType;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( PS_IP_MANAGE_INFO_SEARCH_RES )
	WORD					wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( PS_IP_MANAGE_INFO_EDIT_RES )
	WORD					wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( PS_GM_LOG_LIST_START )
	int				nLogCount;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( PS_GM_LOG_LIST_DATA_READY_REQ )
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( PS_GM_LOG_LIST_DATA )
	sDBO_TIME			sLogTime;
	eGM_REPORT_TYPE		type;
	SERVERFARMID		serverfarmID;
	WCHAR				wszAccountID[NTL_MAX_SIZE_USERID_UNICODE + 1];
	WCHAR				wszTargetID[NTL_MAX_SIZE_USERID_UNICODE + 1];
	int					nTargetID; // ���� ����
	WCHAR				wszTargetName[NTL_MAX_SIZE_GUILD_NAME_IN_UNICODE + 1]; // ���� �� Ÿ���� ���ĸ�
	WCHAR				wszBeforeAction[255]; // ���� define �� ����
	WCHAR				wszAfterAction[255];
	WCHAR				wszObjectName[NTL_MAX_LENGTH_REPORT_NAME_UNICODE + 1];
	TBLIDX				tblIdx;
	int					nSerial;
	int					nResult;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( PS_GM_LOG_LIST_RES )
	WORD				wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
#pragma pack()
