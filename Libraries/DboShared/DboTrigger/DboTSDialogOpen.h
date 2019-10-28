#ifndef _DBO_TSACTCONTDIALOGOPEN_H_
#define _DBO_TSACTCONTDIALOGOPEN_H_


#include "DboTSContGAct.h"


/**
Proposal container
*/


class CDboTSDialogOpen : public CNtlTSCont
{
	NTL_TS_DECLARE_RTTI

// Member variables
protected:
	unsigned int						m_uiDotype;

// Constructions and Destructions
public:
	CDboTSDialogOpen(void);

// Methods
public:
	virtual unsigned int				GetEntityType(void) const { return DBO_CONT_TYPE_ID_CONT_PROPOSAL; }

	unsigned int						GetDotype(void) const;
	void								SetDotype(unsigned int uiDotype);

	// Implementations
protected:
	// ��ũ��Ʈ�� ���� ������Ʈ ��ü�� �����͸� �ε� �� �Է� ��Ű�� ���� �Լ�
	virtual	void						ApplyScriptDataForScript(const CNtlTSScrProperty& clProperty);
	virtual	void						TakeScriptDataForScript(CNtlTSScrProperty& clProperty);
};

inline unsigned int CDboTSDialogOpen::GetDotype(void) const
{
	return m_uiDotype;
}

#endif
