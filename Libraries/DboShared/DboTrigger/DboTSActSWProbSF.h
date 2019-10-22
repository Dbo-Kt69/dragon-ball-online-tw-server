#ifndef _DBO_TSACTSWPROBSF_H_
#define _DBO_TSACTSWPROBSF_H_


#include "DboTSCoreDefine.h"


/**
	Switch probability success fail
*/


class CDboTSActSWProbSF : public CNtlTSAction
{
	NTL_TS_DECLARE_RTTI

// Member variables
protected:
	float								m_fProbility;	// Ȯ�� ( 0 ~ 1 ) ����
	unsigned int						m_uiSuccessBID;	// ������ �б� ID
	unsigned int						m_uiFailBID;	// ���н� �б� ID

// Constructions
public:
	CDboTSActSWProbSF( void );

// Methods
public:
	virtual unsigned int				GetEntityType( void ) const { return DBO_ACT_TYPE_ID_ACT_SWPROBSF; }

	float								GetProbility( void ) const;
	void								SetProbility( float fProbility );

	unsigned int						GetSuccessBID( void ) const;
	void								SetSuccessBID( unsigned int uiBID );

	unsigned int						GetFailBID( void ) const;
	void								SetFailBID( unsigned int uiBID );

// Implementations
protected:
	// ��ũ��Ʈ�� ���� ������Ʈ ��ü�� �����͸� �ε� �� �Է� ��Ű�� ���� �Լ�
	virtual	void						ApplyScriptDataForScript( const CNtlTSScrProperty& clProperty );
	virtual	void						TakeScriptDataForScript( CNtlTSScrProperty& clProperty );
};


inline float CDboTSActSWProbSF::GetProbility( void ) const
{
	return m_fProbility;
}


inline unsigned int CDboTSActSWProbSF::GetSuccessBID( void ) const
{
	return m_uiSuccessBID;
}


inline unsigned int CDboTSActSWProbSF::GetFailBID( void ) const
{
	return m_uiFailBID;
}


#endif