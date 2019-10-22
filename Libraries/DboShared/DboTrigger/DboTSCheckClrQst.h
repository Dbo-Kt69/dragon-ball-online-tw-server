#ifndef _DBO_TSCHECKCLRQST_H_
#define _DBO_TSCHECKCLRQST_H_


#include "DboTSCoreDefine.h"


/**
	Check cleared quest condition
	�뵵 : Client quest, client trigger, server quest, server trigger pc
	���� : ������ ������ ����Ʈ�� �ִ��� �˻��Ѵ�
*/


class CDboTSCheckClrQst : public CNtlTSCond
{
	NTL_TS_DECLARE_RTTI

// Member variables
protected:
	std::vector<NTL_TS_T_ID>			m_vecAndIdList;
	std::vector<NTL_TS_T_ID>			m_vecOrIdList;

// Constructions and Destructions
public:
	CDboTSCheckClrQst( void );

// Methods
public:
	virtual unsigned int				GetEntityType( void ) const { return DBO_COND_TYPE_ID_CHECK_CLRQST; }

	// And �� Or ���̵� �Է� �� "����;����;" ���·� �ԷµǾ�� �Ѵ�
	const std::vector<NTL_TS_T_ID>&		GetAndIdList( void ) const;
	bool								SetAndIdList( const std::string& strIDList );
	void								ClearAndIdList( void );

	const std::vector<NTL_TS_T_ID>&		GetOrIdList( void ) const;
	bool								SetOrIdList( const std::string& strIDList );
	void								ClearOrIdList( void );

// Implementations
protected:
	// ��ũ��Ʈ�� ���� ������Ʈ ��ü�� �����͸� �ε� �� �Է� ��Ű�� ���� �Լ�
	virtual	void						ApplyScriptDataForScript( const CNtlTSScrProperty& clProperty );
	virtual	void						TakeScriptDataForScript( CNtlTSScrProperty& clProperty );
};


inline const std::vector<NTL_TS_T_ID>& CDboTSCheckClrQst::GetAndIdList( void ) const
{
	return m_vecAndIdList;
}

inline const std::vector<NTL_TS_T_ID>& CDboTSCheckClrQst::GetOrIdList( void ) const
{
	return m_vecOrIdList;
}


#endif