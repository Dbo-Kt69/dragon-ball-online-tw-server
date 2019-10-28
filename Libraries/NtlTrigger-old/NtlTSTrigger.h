#ifndef _NTL_TSTRIGGER_H_
#define _NTL_TSTRIGGER_H_


#include "NtlTSEntity.h"


class CNtlTSGroup;


/**
	Trigger entity
*/


class CNtlTSTrigger : public CNtlTSEntity
{
	NTL_TS_DECLARE_RTTI

// Declarations
public:
	typedef stdext::hash_map<NTL_TS_TG_ID, CNtlTSGroup*> hashdef_GroupList;

// Member variables
protected:
	NTL_TS_T_ID							m_tID;

	bool								m_bCanRepeat;
	bool								m_bCanShare;
	bool								m_bOutStateMsg;

	hashdef_GroupList					m_GroupList;
	hashdef_GroupList::iterator			m_itGroupList;

	unsigned int						m_uiTitle;		// Ʈ������ ����

// Constructions and Destructions
public:
	CNtlTSTrigger( void );
	virtual ~CNtlTSTrigger( void );

// Methods
public:
	virtual unsigned int				GetEntityType( void ) const { return NTL_TSENTITY_TYPE_TRIGGER_BEGIN; }

	// Trigger id
	NTL_TS_T_ID							GetID( void ) const;
	NTL_TS_T_ID							SetID( NTL_TS_T_ID tID );

	// �ݺ� ����Ʈ
	bool								IsRepeatQuest( void ) const;
	void								SetRepeatQuest( bool bCanRepeat );

	// ���� ���� ����Ʈ
	bool								IsShareQuest( void ) const;
	void								SetShareQuest( bool bCanShare );

	// ���� �޽��� ���
	bool								IsOutStateMsg( void ) const;
	void								SetOutStateMsg( bool bOutStateMsg );

	// Group
	CNtlTSGroup*						GetGroup( NTL_TS_TG_ID tgId );
	void								AttachGroup( CNtlTSGroup* pGroup );

	// Title
	unsigned int						GetTitle( void ) const;
	void								SetTitle( unsigned int uiTitle );

	// �ڽ� �� �ڽ� Entity�鿡 ���� Ž�� �� ����
	virtual	NTL_TSRESULT				SearchAll( CNtlTSRecv* pTSRecv, void* pParam );
	virtual	NTL_TSRESULT				SearchTarget( NTL_TS_TG_ID tgID, NTL_TS_TC_ID tcID, CNtlTSRecv* pTSRecv, void* pParam );

	NTL_TSRESULT						RunTarget( NTL_TS_TG_ID tgID, NTL_TS_TC_ID tcID, CNtlTSRecv* pTSRecv, void* pParam );

// Implementations
protected:
	// ��ũ��Ʈ���� ���Ǵ� �ڽ� ���� �Լ���
	virtual	CNtlTSScrObject*			BeginChildForScript( void );
	virtual	CNtlTSScrObject*			NextChildForScript( void );
	virtual	void						AttachChildForScript( CNtlTSScrObject* pChild );

	// ��ũ��Ʈ�� ���� ������Ʈ ��ü�� �����͸� �ε� �� �Է� ��Ű�� ���� �Լ�
	virtual	void						ApplyScriptDataForScript( const CNtlTSScrProperty& clProperty );
	virtual	void						TakeScriptDataForScript( CNtlTSScrProperty& clProperty );

public:
	virtual void						MakeAllObjectList( std::vector<CNtlTSScrObject*>& defObjList );
};


inline NTL_TS_T_ID CNtlTSTrigger::GetID( void ) const
{
	return m_tID;
}

inline bool CNtlTSTrigger::IsShareQuest( void ) const
{
	return m_bCanShare;
}

inline bool CNtlTSTrigger::IsRepeatQuest( void ) const
{
	return m_bCanRepeat;
}

inline bool CNtlTSTrigger::IsOutStateMsg( void ) const
{
	return m_bOutStateMsg;
}

inline unsigned int CNtlTSTrigger::GetTitle( void ) const
{
	return m_uiTitle;
}


#endif