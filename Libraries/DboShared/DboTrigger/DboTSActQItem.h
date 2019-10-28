#ifndef _DBO_TSACTQITEM_H_
#define _DBO_TSACTQITEM_H_


#include "DboTSCoreDefine.h"


/**
	Quest item action
	�뵵 : Server quest, server trigger pc
	���� : Quest item�� ���� �� ���� �Ѵ�
*/


struct stTS_QITEM_INFO
{
	unsigned int						uiQItemIdx;		// ���� �� ������ ����Ʈ �������� �ε���
	int									nQItemCnt;		// ���� �� ������ ����Ʈ �������� ����
	float								fProbability;	// ���� Ȯ��
};


class CDboTSActQItem : public CNtlTSAction
{
	NTL_TS_DECLARE_RTTI

// Declarations
public:
	enum { eMAX_TS_QITEM_COUNT = 3 };

// Member variables
protected:
	eQITEM_TYPE							m_eQItemType;
	stTS_QITEM_INFO						m_stQItemInfo[eMAX_TS_QITEM_COUNT];

// Constructions
public:
	CDboTSActQItem( void );

// Methods
public:
	virtual unsigned int				GetEntityType( void ) const { return DBO_ACT_TYPE_ID_ACT_QITEM; }

	eQITEM_TYPE							GetQItemType( void ) const;
	void								SetQItemType( eQITEM_TYPE eQItemType );

	const stTS_QITEM_INFO&				GetQItemInfo( int nIdx ) const;
	void								SetQItemInfo( int nIdx, const stTS_QITEM_INFO& stQItemInfo );

// Implementations
protected:
	// ��ũ��Ʈ�� ���� ������Ʈ ��ü�� �����͸� �ε� �� �Է� ��Ű�� ���� �Լ�
	virtual	void						ApplyScriptDataForScript( const CNtlTSScrProperty& clProperty );
	virtual	void						TakeScriptDataForScript( CNtlTSScrProperty& clProperty );
};


inline eQITEM_TYPE CDboTSActQItem::GetQItemType( void ) const
{
	return m_eQItemType;
}

inline const stTS_QITEM_INFO& CDboTSActQItem::GetQItemInfo( int nIdx ) const
{
	return m_stQItemInfo[nIdx];
}


#endif