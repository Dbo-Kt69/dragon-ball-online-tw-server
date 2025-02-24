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
	// 스크립트로 부터 컴포넌트 객체의 데이터를 로딩 및 입력 시키기 위한 함수
	virtual	void						ApplyScriptDataForScript( const CNtlTSScrProperty& clProperty );
	virtual	void						TakeScriptDataForScript( CNtlTSScrProperty& clProperty );
};

inline unsigned int CDboTSSlotMachine::GetST(void) const
{
	return m_uiST;
}

#endif