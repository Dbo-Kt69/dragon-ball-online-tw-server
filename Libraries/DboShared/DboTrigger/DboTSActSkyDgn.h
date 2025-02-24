#ifndef _DBO_TSACTSKYDGN_H_
#define _DBO_TSACTSKYDGN_H_


#include "DboTSCoreDefine.h"


/**
Portal action
*/


class CDboTSActSkyDgn : public CNtlTSAction
{
	NTL_TS_DECLARE_RTTI

		// Member variables
protected:
	unsigned int						m_uiType;
	unsigned int						m_uiIdx;

	// Constructions
public:
	CDboTSActSkyDgn(void);

// Methods
public:
	virtual unsigned int				GetEntityType(void) const { return DBO_ACT_TYPE_ID_ACT_SKYDGN; }

	unsigned int						GetType(void) const;
	void								SetType(unsigned int uiType);

	unsigned int						GetIdx(void) const;
	void								SetIdx(unsigned int uiWorldIdx);

// Implementations
protected:
	// 스크립트로 부터 컴포넌트 객체의 데이터를 로딩 및 입력 시키기 위한 함수
	virtual	void						ApplyScriptDataForScript(const CNtlTSScrProperty& clProperty);
	virtual	void						TakeScriptDataForScript(CNtlTSScrProperty& clProperty);
};

inline unsigned int CDboTSActSkyDgn::GetType(void) const
{
	return m_uiType;
}

inline unsigned int CDboTSActSkyDgn::GetIdx(void) const
{
	return m_uiIdx;
}

#endif