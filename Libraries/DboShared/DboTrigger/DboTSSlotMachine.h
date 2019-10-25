#ifndef _DBO_TSSLOTMACHINE_H_
#define _DBO_TSSLOTMACHINE_H_


#include "DboTSCoreDefine.h"


/**
	Slot machine
*/


class CDboTSSlotMachine : public CNtlTSEvent
{
	NTL_TS_DECLARE_RTTI

// Member variables
protected:
	unsigned int						m_uiST;

// Constructions
public:
	CDboTSSlotMachine( void );

// Methods
public:
	virtual unsigned int				GetEntityType( void ) const { return DBO_EVENT_TYPE_ID_SLOTMACHINE; }

	unsigned int						GetST(void) const;
	void								SetST(unsigned int uiST);

// Implementations
protected:
	// ��ũ��Ʈ�� ���� ������Ʈ ��ü�� �����͸� �ε� �� �Է� ��Ű�� ���� �Լ�
	virtual	void						ApplyScriptDataForScript( const CNtlTSScrProperty& clProperty );
	virtual	void						TakeScriptDataForScript( CNtlTSScrProperty& clProperty );
};

inline unsigned int CDboTSSlotMachine::GetST(void) const
{
	return m_uiST;
}

#endif