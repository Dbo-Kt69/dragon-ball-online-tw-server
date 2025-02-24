#ifndef _DBO_TSACTREGQINFO_H_
#define _DBO_TSACTREGQINFO_H_


#include "DboTSCoreDefine.h"


/**
	Register quest information action
	용도 : Client quest
	설명 : 퀘스트 정보를 출력하기 위한 로직을 구현해야 됨
*/


class CDboTSActRegQInfo : public CNtlTSAction
{
	NTL_TS_DECLARE_RTTI

// Declarations
public:

	struct SQUEST_MARK_INFO
	{
		unsigned int					uiWorldTblIdx;
		float							fX, fY, fZ;
		unsigned int					uiTooltipIdx;
		unsigned int					uiPat;
	};

// Member variables
protected:
	unsigned int						m_uiTitle;
	unsigned int						m_uiArea;
	unsigned int						m_uiGoal;
	unsigned int						m_uiGrade;
	unsigned int						m_uiItem;
	eGRADE_TYPE							m_eGradeType;
	eQUEST_SORT_TYPE					m_eSort;
	unsigned int						m_uiSort;
	unsigned int						m_uiContents;
	NTL_TS_TC_ID						m_tcReward;

	SQUEST_MARK_INFO					m_sQuestMarkInfo[5];

// Constructions
public:
	CDboTSActRegQInfo( void );

// Methods
public:
	virtual unsigned int				GetEntityType( void ) const { return DBO_ACT_TYPE_ID_ACT_REGQINFO; }

	unsigned int						GetTitle( void ) const;
	void								SetTitle( unsigned int uiTitle );

	unsigned int						GetArea( void ) const;
	void								SetArea( unsigned int uiArea );

	unsigned int						GetItem(void) const;
	void								SetItem(unsigned int uiItem);

	unsigned int						GetGoal( void ) const;
	void								SetGoal( unsigned int uiGoal );

	unsigned int						GetGrade( void ) const;
	void								SetGrade( unsigned int uiGrade );

	eGRADE_TYPE							GetGradeType( void ) const;
	void								SetGradeType( eGRADE_TYPE eGradeType );

	eQUEST_SORT_TYPE					GetSortType( void ) const;
	void								SetSortType( eQUEST_SORT_TYPE eQuestType );

	unsigned int						GetSort( void ) const;
	void								SetSort( unsigned int uiSort );

	unsigned int						GetContents( void ) const;
	void								SetContents( unsigned int uiContents );

	NTL_TS_TC_ID						GetReward( void ) const;
	void								SetReward( NTL_TS_TC_ID tcId );

	int									GetMaxNumOfQuestMarkInfo( void ) const;
	const SQUEST_MARK_INFO&				GetQuestMarkInfo( int nIdx ) const;
	void								SetQuestMarkInfo( int nIdx, const SQUEST_MARK_INFO& sQuestMarkInfo );

// Implementations
protected:
	// 스크립트로 부터 컴포넌트 객체의 데이터를 로딩 및 입력 시키기 위한 함수
	virtual	void						ApplyScriptDataForScript( const CNtlTSScrProperty& clProperty );
	virtual	void						TakeScriptDataForScript( CNtlTSScrProperty& clProperty );
};


inline unsigned int CDboTSActRegQInfo::GetTitle( void ) const
{
	return m_uiTitle;
}

inline unsigned int CDboTSActRegQInfo::GetArea( void ) const
{
	return m_uiArea;
}

inline unsigned int CDboTSActRegQInfo::GetItem(void) const
{
	return m_uiItem;
}

inline unsigned int CDboTSActRegQInfo::GetGoal( void ) const
{
	return m_uiGoal;
}

inline unsigned int CDboTSActRegQInfo::GetGrade( void ) const
{
	return m_uiGrade;
}

inline eGRADE_TYPE CDboTSActRegQInfo::GetGradeType( void ) const
{
	return m_eGradeType;
}

inline eQUEST_SORT_TYPE CDboTSActRegQInfo::GetSortType( void ) const
{
	return m_eSort;
}

inline unsigned int CDboTSActRegQInfo::GetSort( void ) const
{
	return m_uiSort;
}

inline unsigned int CDboTSActRegQInfo::GetContents( void ) const
{
	return m_uiContents;
}

inline NTL_TS_TC_ID CDboTSActRegQInfo::GetReward( void ) const
{
	return m_tcReward;
}

inline int CDboTSActRegQInfo::GetMaxNumOfQuestMarkInfo( void ) const
{
	return 3;
}

inline const CDboTSActRegQInfo::SQUEST_MARK_INFO& CDboTSActRegQInfo::GetQuestMarkInfo( int nIdx ) const
{
	return m_sQuestMarkInfo[nIdx];
}


#endif