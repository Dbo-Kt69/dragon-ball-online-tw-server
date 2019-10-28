#ifndef _DBO_TSCLICKSIDEICON_H
#define _DBO_TSCLICKSIDEICON_H


#include "DboTSCoreDefine.h"


/**
	Click side icon
*/


class CDboTSClickSideIcon : public CNtlTSCond
{
	NTL_TS_DECLARE_RTTI

		// Member variables
protected:
	int									m_nSitype;

// Constructions
public:
	CDboTSClickSideIcon(void);

// Methods
public:
	virtual unsigned int				GetEntityType(void) const { return DBO_COND_TYPE_ID_CHECK_LVL; }

	int									GetSitype(void) const;
	void								SetSitype(int nSityp);

	// Implementations
protected:
	// ��ũ��Ʈ�� ���� ������Ʈ ��ü�� �����͸� �ε� �� �Է� ��Ű�� ���� �Լ�
	virtual	void						ApplyScriptDataForScript(const CNtlTSScrProperty& clProperty);
	virtual	void						TakeScriptDataForScript(CNtlTSScrProperty& clProperty);
};

inline int CDboTSClickSideIcon::GetSitype(void) const
{
	return m_nSitype;
}
#endif