#ifndef _NTL_NAVI_H_
#define _NTL_NAVI_H_


#include "NtlNaviDefine.h"

//////////////////////////////////////////////////////////////////////////
//
// ��ã�� �ΰ� �ý���
//
//////////////////////////////////////////////////////////////////////////


class INtlNaviLog
{
public:
	virtual ~INtlNaviLog( void ) { return; }


public:
	virtual void Log( const char* pLog, ... )														= 0;
};


//////////////////////////////////////////////////////////////////////////
//
// ��ã�� �������̽�
//
//////////////////////////////////////////////////////////////////////////

class CNtlNaviPEWorld;
class iMesh;

class INtlNavi
{
public:
	virtual ~INtlNavi( void ) { return; }


public:
	//////////////////////////////////////////////////////////////////////////
	//
	// Navigation library ���� ���� �������̽�
	//
	//////////////////////////////////////////////////////////////////////////

	virtual bool					Create( INtlNaviLog* pLog,
											const char* pPathDllName,
											bool bThreadLoading )									= 0;

	virtual void					Delete( void )													= 0;


	//////////////////////////////////////////////////////////////////////////
	//
	// Tool ���� �������̽�
	//
	//////////////////////////////////////////////////////////////////////////

	virtual bool					ImportWorldToolData( const char* pRootFolder )					= 0;

	virtual void					GetListImportedWorldIDList( vecdef_WorldIDList& vecOut )		= 0;

	virtual bool					ExportPathEngineData( const char* pRootFolder )					= 0;

	virtual bool					ExportPathEngineDataSelect( const char* pRootFolder, mapdef_ExportList& list ) = 0;

	virtual bool					UpdateToolData( void )											= 0;

	virtual int						GetWorldVertexCount( NAVI_INST_HANDLE hHandle )					= 0;

	virtual int						GetWorldVertexCount( unsigned int uiWorldID )					= 0;

	virtual bool					GetWorldVertexToBuffer( NAVI_INST_HANDLE hHandle, sNAVI_VERTEX* pBuffer )		= 0;

	virtual bool					GetWorldVertexToBuffer( unsigned int uiWorldID, sNAVI_VERTEX* pBuffer )			= 0;

	virtual iMesh*					GetNearestMesh( NAVI_INST_HANDLE hHandle, sNAVI_POS& vPos )						= 0;


	//////////////////////////////////////////////////////////////////////////
	//
	// Game ���� �������̽�
	//
	//////////////////////////////////////////////////////////////////////////

	// �н� ���� �����͸� �ε��Ѵ�
	virtual bool					LoadPathEngineData( const char* pRootFolder,
														vecdef_WorldIDList& defWorldIDList,
														unsigned char byLoadFlags )					= 0;

	// �ε��� �Ϸ�Ǵ� �������� Main-Thread �� Block �Ѵ�
	// �ε� �Ϸ� ���� �Ʒ� �����ϴ� �Լ����� ����ϴ� �Ϳ� ���� ����� å�� ���� �ʴ´�
	virtual bool					WaitUntilLoadingFinish( unsigned int uiWaitTime,
															unsigned int& uiResult )				= 0;

	// �ε� �ð� ��ȯ
	// ��ȯ�� -> 0xffffffff				: �ε� ����
	//			 0xffffffff �̿��� ��	: �ε� �ð�
	virtual unsigned int			GetLoadingTime( void )											= 0;

	// ���� �н������� ����ϰ� �ִ� �޸� ��
	virtual unsigned long			GetTotalMemory( void )											= 0;

	// Instance handler ����
	virtual NAVI_INST_HANDLE		CreateInstanceHandler( unsigned int uiWorldID )					= 0;

	// Instance handler ����
	virtual void					DeleteInstanceHandler( NAVI_INST_HANDLE hHandle )				= 0;

	// �Ӽ� �����Ͱ� �����ϴ����� �˻��Ѵ�
	virtual bool					IsPropDataLoaded( unsigned int uiWorldID )						= 0;

	// �н� �����Ͱ� �����ϴ����� �˻��Ѵ�
	virtual bool					IsPathDataLoaded( unsigned int uiWorldID )						= 0;

	// NPC, Mob�� ũ�� ( �ݰ� ) ���� ����
	virtual bool					CanSupportAgent( NAVI_INST_HANDLE hHandle, float fAgentRadius )	= 0;

	// ��
	virtual unsigned int			GetTextAllIndex( NAVI_INST_HANDLE hHandle,
													 float x,
													 float z )										= 0;

	// ��
	virtual unsigned int			GetZoneIndex( NAVI_INST_HANDLE hHandle,
												  float x,
												  float z )											= 0;

	// �ش� ��ġ�� ��� �Ӽ�
	virtual unsigned int			GetAttribute( NAVI_INST_HANDLE hHandle,
												  float x,
												  float z )											= 0;

	// �⺻ �Ӽ��� ���� ����
	virtual bool					IsBasicAttributeSet( NAVI_INST_HANDLE hHandle,
														 float x,
														 float z,
														 eDBO_WORLD_ATTR_BASIC eAttrBasic )			= 0;

	// ��ȯ ���� NAVI_FLT_MAX �̸� Invalid
	virtual float					GetHeight( NAVI_INST_HANDLE hHandle,
											   float x,
											   float y,
											   float z )											= 0;

	// ��ȯ ���� NAVI_FLT_MAX �̸� Invalid
	virtual float					GetGuaranteedHeight( NAVI_INST_HANDLE hHandle,
														 float x,
														 float y,
														 float z )									= 0;


	// ���� ������ ���� ��ġ ��ȯ
	virtual bool					FindNearestPos( NAVI_INST_HANDLE hHandle,
													float fAgentRadius,
													sNAVI_POS& sSrcPos )							= 0;

	// �浹 �׽�Ʈ
	virtual eCOL_TEST_RESULT		CollisionTest( NAVI_INST_HANDLE hHandle,
												   float fAgentRadius,
												   sNAVI_POS& sSrcPos,
												   sNAVI_POS& sDestPos )							= 0;

	// �浹 �׽�Ʈ : ù��° �浹 ��ġ�� ���
	virtual eCOL_TEST_RESULT		FirstCollisionTest( NAVI_INST_HANDLE hHandle,
													float fAgentRadius, 
													sNAVI_POS& sSrcPos, 
													sNAVI_POS& sDestPos, 
													sNAVI_POS& sFirstCollisionPos )					= 0;

	// �� ã��
	virtual bool					FindPath( NAVI_INST_HANDLE hHandle,
											  float fAgentRadius,
											  sNAVI_POS& sSrcPos,
											  sNAVI_POS& sDestPos,
											  vecdef_NaviPosList& defNaviPosList )					= 0;
};


// ���� ������ ��ã�� �������̽� ���
INtlNavi* GetNaviEngine( void );


#endif