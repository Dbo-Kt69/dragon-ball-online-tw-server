/*****************************************************************************
* File			: NtlPathEngine.h
* Author		: Haesung, Cho
* Copyright		: (��)NTL
* Date			: 2009. 03. 10
* Abstract		: Pathengine wrapping project ( for client )
*****************************************************************************
* Desc:
* 
* �� ������Ʈ�� ���� ����ϰ� �ִ� PathEngine�� Client Ȯ���� ���ؼ� ������
* ���� ���̺귯�� ������Ʈ�̴�. Tool ���� TestPathEngine ������Ʈ�� �����Ǿ ���ȴ�.
* 
* Note1 : ��� �۾��� ����ȭ�� �Ǹ� �� ������Ʈ�� NtlNavi ������Ʈ�� ������ ��
* Note2 : NtlNavi �� ���� �۾��� ������ Tool ���� TestPathEngine ������Ʈ�� ������ ��
* Note3 : Ŭ���̾�Ʈ�� Pathengine R&D ����� SKIP ( 2009. 04 )
* 
* Worklist
* (��) 1�� : Library interface ����
* (��) 2�� : PathEngine data create module ����  ( Federation tile ���� )
* (��) 3�� : PathEngine data seamless loading module ����
* (��) 4�� : Client �� Library ���� ����
* (  ) 5�� : ����ȭ �۾�
*****************************************************************************/

#ifndef _NTL_PATHENGINE_H_
#define _NTL_PATHENGINE_H_

#pragma once

#include <Windows.h>

class iPathEngine;
class iErrorHandler;
class CNtlPathEngineLog;

#include "NtlPathSeamlessManager.h"

class CNtlPathEngine
{
public:
	CNtlPathEngine(void);
	~CNtlPathEngine(void);

	typedef iPathEngine* (__stdcall* tGetInterfaceFunction)( iErrorHandler* );

	// SingleTon
	static CNtlPathEngine*	GetInstance();

	virtual bool	Create( const char* pPathEngineDllName, BOOL bSeamless = TRUE );
	virtual void	Update( float fElapsed );
	virtual void	Destroy( void );

	iPathEngine*	GetPathEngine();

	// Seamless
	void	SeamlessAddAgentSize( int nSize );

	void	SeamlessChangeWorld( int nWorldIndex );
	void	SeamlessUpdatePosition( int nPositionX, int nPositionY, int nPositionZ );

	void	SeamlessPathFinding( 
		int nAgentSize, int nSrcPositionX, int nSrcPositionY, int nSrcPositionZ,
		int nDestPositionX, int nDestPositionY, int nDestPositionZ, std::list< cPosition >& vec );


protected:
	HINSTANCE		m_hInstance;
	iPathEngine*	m_pPathEngine;

	CNtlPathSeamlessManager			m_seamManager;
	BOOL							m_bSeamless;

	// Currently Position
	int								m_nPositionX;
	int								m_nPositionY;
	int								m_nPositionZ;
};

static CNtlPathEngine* GetNtlPathEngine()
{
	return CNtlPathEngine::GetInstance();
}

#endif