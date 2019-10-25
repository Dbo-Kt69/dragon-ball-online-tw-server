#ifndef _DBO_TSCHECKPROGQUEST_H_
#define _DBO_TSCHECKPROGQUEST_H_


#include "DboTSCoreDefine.h"


/**
	Check progress quest condition
*/


class CDboTSCheckProgQuest : public CNtlTSCond
{
	NTL_TS_DECLARE_RTTI

// Member variables
protected:
	NTL_TS_T_ID							m_tQuestID;
	std::vector<NTL_TS_T_ID>			m_vecNotIdList;

// Constructions
public:
	CDboTSCheckProgQuest( void );

// Methods
public:
	virtual unsigned int				GetEntityType( void ) const { return DBO_COND_TYPE_ID_CHECK_PROG_QUEST; }

	NTL_TS_T_ID							GetQuestID( void ) const;
	void								SetQuestID( NTL_TS_T_ID tQID );

	const std::vector<NTL_TS_T_ID>&		GetNotIdList(void) const;
	bool								SetNotIdList(const std::string& strIDList);
	void								ClearNotIdList(void);


// Implementations
protected:
	// ��ũ��Ʈ�� ���� ������Ʈ ��ü�� �����͸� �ε� �� �Է� ��Ű�� ���� �Լ�
	virtual	void						ApplyScriptDataForScript( const CNtlTSScrProperty& clProperty );
	virtual	void						TakeScriptDataForScript( CNtlTSScrProperty& clProperty );
};


inline NTL_TS_T_ID CDboTSCheckProgQuest::GetQuestID( void ) const
{
	return m_tQuestID;
}

inline const std::vector<NTL_TS_T_ID>& CDboTSCheckProgQuest::GetNotIdList(void) const
{
	return m_vecNotIdList;
}
#endif