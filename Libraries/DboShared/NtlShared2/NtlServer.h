//***********************************************************************************
//
//	File		:	NtlServer.h
//
//	Begin		:	2008-05-13
//
//	Copyright	:	�� NTL-Inc Co., Ltd
//
//	Author		:	
//
//	Desc		:	
//
//***********************************************************************************

#pragma once
#include "NtlBudokai.h"

#define BEGIN_SVR_RELAY_DATA(datatype)						\
	struct s##datatype :public sSERVER_RELAY_DATA_HEADER	\
	{														\
		s##datatype() :										\
		sSERVER_RELAY_DATA_HEADER(datatype)					\
		{}

#define END_SVR_RELAY_DATA()	};


// Game Server -> Community -> Game Server type
enum eSERVER_RELAY_DATA_TYPE
{
	// õ�����Ϲ���ȸ
	G2G_BUDOKAI_SET_WAIT_TIME,			// ���� �������� ������ ��� �ð� ����
	G2G_BUDOKAI_CLEAR,					// õ�����Ϲ���ȸ �ʱ�ȭ
	G2G_BUDOKAI_SET_OPEN_TIME,			// õ�����Ϲ���ȸ ���� �ð� ����(�̹� ����)
	G2G_BUDOKAI_RESET_OPEN_TIME_NFY,	// ���� �ð� �缳�� �˸�(õ�����Ϲ���ȸ ä�� -> ��ä��)

	G2G_BUDOKAI_CHANNEL_STATE_INFO_REQ,	// õ�����Ϲ���ȸ�� ���� ���� ���� ��û
	G2G_BUDOKAI_CHANNEL_STATE_INFO_RES,	// õ�����Ϲ���ȸ�� ���� ���� ���� ����
	G2G_RANKBATTLE_ALLOW_NFY,			// ��ũ��Ʋ�� lock/unlock ��Ų��.
	G2G_RANKPOINT_RESET_NFY,			// ��ũ����Ʈ�� ���µ�
	G2G_BUDOKAI_JOIN_STATE_LIST,		// ��� PC�� õ�����Ϲ���ȸ ���� ����
	G2G_BUDOKAI_PRIZEWINNER_NAME_REQ,
	G2G_BUDOKAI_PRIZEWINNER_NAME_RES,
};


//-----------------------------------------------------------------------------------
//
#pragma pack(1)

struct sSERVER_RELAY_DATA_HEADER
{
	sSERVER_RELAY_DATA_HEADER(eSERVER_RELAY_DATA_TYPE eDataType) : wDataType((WORD)eDataType) {}

	WORD wDataType;		// eSERVER_RELAY_DATA_TYPE
};


//---------------------------------------------------------------------------------------
// Data
//---------------------------------------------------------------------------------------
BEGIN_SVR_RELAY_DATA( G2G_BUDOKAI_SET_WAIT_TIME )
	BYTE						byMatchType;
	BUDOKAITIME					tmSetTime;
END_SVR_RELAY_DATA()
//---------------------------------------------------------------------------------------
BEGIN_SVR_RELAY_DATA( G2G_BUDOKAI_CLEAR )
END_SVR_RELAY_DATA()
//---------------------------------------------------------------------------------------
BEGIN_SVR_RELAY_DATA( G2G_BUDOKAI_SET_OPEN_TIME )
	BUDOKAITIME					tmOpenTime;
END_SVR_RELAY_DATA()
//---------------------------------------------------------------------------------------
BEGIN_SVR_RELAY_DATA( G2G_BUDOKAI_RESET_OPEN_TIME_NFY )
	BUDOKAITIME					tmOpenTime;
	BUDOKAITIME					tmRemainTime;
END_SVR_RELAY_DATA()
//---------------------------------------------------------------------------------------
BEGIN_SVR_RELAY_DATA( G2G_BUDOKAI_CHANNEL_STATE_INFO_REQ )
END_SVR_RELAY_DATA()
//---------------------------------------------------------------------------------------
BEGIN_SVR_RELAY_DATA( G2G_BUDOKAI_CHANNEL_STATE_INFO_RES )
	BUDOKAITIME							tmDefaultOpenTime;
	bool								bRankbattleAllow;
	sBUDOKAI_UPDATE_STATE_INFO			sStateInfo;
	sBUDOKAI_UPDATE_MATCH_STATE_INFO	aMatchStateInfo[MAX_BUDOKAI_MATCH_TYPE];
END_SVR_RELAY_DATA()
//---------------------------------------------------------------------------------------
BEGIN_SVR_RELAY_DATA( G2G_RANKBATTLE_ALLOW_NFY )
	bool	bAllow;
	WORD	wReasonCode;
END_SVR_RELAY_DATA()
//---------------------------------------------------------------------------------------
BEGIN_SVR_RELAY_DATA( G2G_RANKPOINT_RESET_NFY )
	BYTE byMinLevel;
	BYTE byMaxLevel;
END_SVR_RELAY_DATA()
//---------------------------------------------------------------------------------------
BEGIN_SVR_RELAY_DATA( G2G_BUDOKAI_JOIN_STATE_LIST )
	BYTE						byMatchType;	// eBUDOKAI_MATCH_TYPE
	BYTE						byDataCount;
	sBUDOKAI_JOIN_STATE_DATA	aJoinStateData[BUDOkAI_MAX_PLAYER_JOIN_STATE_DATA_COUNT];
END_SVR_RELAY_DATA()
//---------------------------------------------------------------------------------------
BEGIN_SVR_RELAY_DATA( G2G_BUDOKAI_PRIZEWINNER_NAME_REQ )
	HOBJECT						hPc;
	CHARACTERID					charId;
	BYTE						byMatchType;	// eBUDOKAI_MATCH_TYPE
END_SVR_RELAY_DATA()
//---------------------------------------------------------------------------------------
BEGIN_SVR_RELAY_DATA( G2G_BUDOKAI_PRIZEWINNER_NAME_RES )
	WORD						wResultCode;

	HOBJECT						hPc;
	CHARACTERID					charId;
	BYTE						byMatchType;	// eBUDOKAI_MATCH_TYPE

	WCHAR						wszWinner[NTL_MAX_SIZE_CHAR_NAME_UNICODE + 1];
	WCHAR						wszSecondWinner[NTL_MAX_SIZE_CHAR_NAME_UNICODE + 1];

	WCHAR						wszWinnerTeam[NTL_MAX_LENGTH_BUDOKAI_TEAM_NAME_IN_UNICODE + 1];
	WCHAR						wszSecondWinnerTeam[NTL_MAX_LENGTH_BUDOKAI_TEAM_NAME_IN_UNICODE + 1];
END_SVR_RELAY_DATA()
//---------------------------------------------------------------------------------------



//---------------------------------------------------------------------------------------
// CServerRelayData
//---------------------------------------------------------------------------------------
class CServerRelayData
{
public:
	enum eDEFINE
	{
		MAX_DATA_SIZE = 3072,
	};

	CServerRelayData() {wDataSize = 0; pData = NULL;}
	CServerRelayData(WORD wArraySize)
	{
		if( MAX_DATA_SIZE < wArraySize )
		{
			_ASSERT(0);
			return;
		}

		pData = new BYTE [wArraySize];
		if( NULL == pData )
		{
			_ASSERT(0);
			return;
		}
		wDataSize = wArraySize;
	}

	~CServerRelayData() { if(NULL != pData) { delete [] pData; pData = NULL; } }


	WORD	GetSize() { return wDataSize;}
	BYTE *	GetData() { return pData; }

public:

	WORD	wDataSize;

	BYTE *	pData;
};


#pragma pack()
//-----------------------------------------------------------------------------------
