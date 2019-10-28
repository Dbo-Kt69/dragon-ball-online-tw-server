//***********************************************************************************
//
//	File		:	NtlDirection.h
//
//	Begin		:	2007-06-21
//
//	Copyright	:	�� NTL-Inc Co., Ltd
//
//	Author		:	Hyun Woo, Koo   ( zeroera@ntl-inc.com )
//
//	Desc		:	
//
//***********************************************************************************

#pragma once

//-----------------------------------------------------------------------------------
// Ŭ���̾�Ʈ ���� Ÿ��
//-----------------------------------------------------------------------------------
enum eDIRECTION_TYPE
{
	DIRECTION_FLASH, // 2D ����
	DIRECTION_CINEMATIC, // ���׸�ƽ ����
	DIRECTION_PLAY, // �������� ������ �ִϸ��̼ǵ��� ���� (���׸�ƽ���� �޸� ����ȭ �ȴ� ) -> ���� ����

	MAX_DIECTION_TYPE,
	INVALID_DIRECTION_TYPE = 0xFF,
};

//-----------------------------------------------------------------------------------
// ĳ���� ���� Ÿ�� ( ���·����� ����ȭ )
//-----------------------------------------------------------------------------------
enum eDIRECT_PLAY_TYPE
{
	DIRECT_PLAY_TQS_START,
	DIRECT_PLAY_TQS_ARRIVE,
	DIRECT_PLAY_TQS_LEAVE,

	DIRECT_PLAY_NORMAL,

	DIRECT_PLAY_VEHICLE,

	MAX_DIRECT_PLAY_TYPE,
	INVALID_DIRECT_PLAY_TYPE = 0xFF,
};

//-----------------------------------------------------------------------------------
// ���(Ʈ��ũ�� ������ �޽��� Ÿ�� )
//-----------------------------------------------------------------------------------
enum eTELECAST_MESSAGE_TYPE
{
	TELECAST_MESSAGE_TYPE_NORMAL,
	TELECAST_MESSAGE_TYPE_WARNING,
	TELECAST_MESSAGE_TYPE_DANGER,
    TELECAST_MESSAGE_TYPE_NOTIFY,               ///< �������� ������� ���� �޽��� (Ŭ���̾�Ʈ�������� ���)

	MAX_TELECAST_MESSAGE_TYPE,
	INVALID_TELECAST_MESSAGE_TYPE = 0xFF,
};

//-----------------------------------------------------------------------------------
// ���� �޽��� ( TMQ��� ���� �����Ȳ�� �ȳ��ϴ� �޽��� )
//-----------------------------------------------------------------------------------
enum ePROGRESS_MESSAGE_TYPE
{
	PROGRESS_MESSAGE_TYPE_TMQ,
	PGOGRESS_MESSAGE_TYPE_TMQ_STAGE,

	MAX_PROGRESS_MESSAGE_TYPE,
	INVALID_PROGRESS_MESSAGE_TYPE = 0xFF,
};

//-----------------------------------------------------------------------------------
// ���� ���� �޽���
//-----------------------------------------------------------------------------------
enum eDIRECTION_INDICATE_TYPE
{
	DIRECTION_INDICATE_TYPE_TOBJECT, // ������Ʈ�� �����Ѵ�
	DIRECTION_INDICATE_TYPE_NPC, // npc�� �����Ѵ�
	DIRECTION_INDICATE_TYPE_POINT, // �ϳ��� ������ �����Ѵ�

	MAX_DIRECTION_INDICATE_TYPE,
	INVALID_DIRECTION_INDICATE_TYPE = 0xFF,
};