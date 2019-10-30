#ifndef _DBO_TSLEVELCHECK_H
#define _DBO_TSLEVELCHECK_H


#include "DboTSCoreDefine.h"


/**
	Check level
*/


class CDboTSLevelCheck : public CNtlTSCond
{
	NTL_TS_DECLARE_RTTI

// Member variables
/*
protected:*/

// Constructions
public:
	CDboTSLevelCheck(void);

// Methods
public:
	virtual unsigned int				GetEntityType(void) const { return DBO_COND_TYPE_ID_LEVEL_CHECK; }

// Implementations
protected:
	// ��ũ��Ʈ�� ���� ������Ʈ ��ü�� �����͸� �ε� �� �Է� ��Ű�� ���� �Լ�
	virtual	void						ApplyScriptDataForScript(const CNtlTSScrProperty& clProperty);
	virtual	void						TakeScriptDataForScript(CNtlTSScrProperty& clProperty);
};

#endif