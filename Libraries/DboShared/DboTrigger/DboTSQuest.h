#ifndef _DBO_TSQUEST_H
#define _DBO_TSQUEST_H


#include "DboTSCoreDefine.h"


/**
	Quest
*/


class CDboTSQuest : public CNtlTSCond
{
	NTL_TS_DECLARE_RTTI

	// Constructions
public:
	CDboTSQuest(void);

// Methods
public:
	virtual unsigned int				GetEntityType(void) const { return DBO_COND_TYPE_ID_CHECK_LVL; }

// Implementations
protected:
	// ��ũ��Ʈ�� ���� ������Ʈ ��ü�� �����͸� �ε� �� �Է� ��Ű�� ���� �Լ�
	virtual	void						ApplyScriptDataForScript(const CNtlTSScrProperty& clProperty);
	virtual	void						TakeScriptDataForScript(CNtlTSScrProperty& clProperty);
};

#endif