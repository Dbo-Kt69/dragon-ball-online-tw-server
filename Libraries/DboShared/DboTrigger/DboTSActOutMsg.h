#ifndef _DBO_TSACTOUTMSG_H_
#define _DBO_TSACTOUTMSG_H_

#include "DboTSCoreDefine.h"

/**
	Message out action
	�뵵 : Client quest, client trigger
	���� : Ŭ���̾�Ʈ �������� ���Ǵ� NPC ��ȭ
*/

class CDboTSActOutMsg : public CNtlTSAction
{
	NTL_TS_DECLARE_RTTI

	// Member variables
protected:
	unsigned int						m_uiMsgIdx;
	// Constructions
public:
	CDboTSActOutMsg(void);

	// Methods
public:
	virtual unsigned int				GetEntityType(void) const { return DBO_ACT_TYPE_ID_ACT_NPCCONV; }
	unsigned int						GetMsgIdx(void) const;
	void								SetMsgIdx(unsigned int uiMsjIdx);

	// Implementations
protected:
	// ��ũ��Ʈ�� ���� ������Ʈ ��ü�� �����͸� �ε� �� �Է� ��Ű�� ���� �Լ�
	virtual	void						ApplyScriptDataForScript(const CNtlTSScrProperty& clProperty);
	virtual	void						TakeScriptDataForScript(CNtlTSScrProperty& clProperty);
};

inline unsigned int CDboTSActOutMsg::GetMsgIdx(void) const
{
	return m_uiMsgIdx;
}
#endif
