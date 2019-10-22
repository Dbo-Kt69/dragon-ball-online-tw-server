#ifndef _DBO_TSCLICKNPC_H_
#define _DBO_TSCLICKNPC_H_


#include "DboTSCoreDefine.h"


/**
	Click NPC event
	�뵵 : Client quest, client trigger, server quest, server trigger pc
	���� : Ŭ���̾�Ʈ������ NPC�� ���õǾ��� �� �߻��ϴ� �̺��ͷν� ����
		   ���������� �ش� NPC�� ���õǾ����� �˻��ϴ� �뵵�� ����
*/


class CDboTSClickNPC : public CNtlTSEvent
{
	NTL_TS_DECLARE_RTTI

// Member variables
protected:
	unsigned int						m_uiNPCIdx;

// Constructions
public:
	CDboTSClickNPC( void );

// Methods
public:
	virtual unsigned int				GetEntityType( void ) const { return DBO_EVENT_TYPE_ID_CLICK_NPC; }

	unsigned int						GetNPCIdx( void ) const;
	void								SetNPCIdx( unsigned int uiNPCIdx );

// Implementations
protected:
	// ��ũ��Ʈ�� ���� ������Ʈ ��ü�� �����͸� �ε� �� �Է� ��Ű�� ���� �Լ�
	virtual	void						ApplyScriptDataForScript( const CNtlTSScrProperty& clProperty );
	virtual	void						TakeScriptDataForScript( CNtlTSScrProperty& clProperty );
};


inline unsigned int CDboTSClickNPC::GetNPCIdx( void ) const
{
	return m_uiNPCIdx;
}


#endif