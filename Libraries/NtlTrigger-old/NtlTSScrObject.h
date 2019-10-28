#ifndef _NTL_TSSCROBJECT_H_
#define _NTL_TSSCROBJECT_H_


#include "NtlTSRTTI.h"
#include "NtlTSScrProperty.h"


/** 
	Script object
	Script �� ���ؼ� ��ü�� �ڵ������ϱ� ���ؼ��� ���� �����ϰ��� �ϴ� Ŭ������ �Ʒ� Ŭ������
	��ӹ޾� �����ؾ� ��

	( ���� )
	��ũ��Ʈ���� ��Ÿ�� �� ��ü ������ �����ϱ� ���ؼ��� ��� �޴� Ŭ�������� TSRTTI �� ����ؾ�
	��Ÿ�� �� ��ü�� ���� ������ �� ����
*/


class CNtlTSScrObject
{
	NTL_TS_DECLARE_RTTI

// Constructions and Destructions
public:
	virtual ~CNtlTSScrObject( void ) { return; }

// Implementations
protected:
	virtual	CNtlTSScrObject*			GetParentForScript( void ) = 0;
	virtual	void						SetParentForScript( CNtlTSScrObject* pParent ) = 0;

	virtual	CNtlTSScrObject*			BeginChildForScript( void ) = 0;
	virtual	CNtlTSScrObject*			NextChildForScript( void ) = 0;

	virtual	void						AttachChildForScript( CNtlTSScrObject* pChild ) = 0;

public:
	virtual	void						ApplyScriptDataForScript( const CNtlTSScrProperty& clProperty ) = 0;
	virtual	void						TakeScriptDataForScript( CNtlTSScrProperty& clProperty ) = 0;

public:
	virtual void						MakeAllObjectList( std::vector<CNtlTSScrObject*>& defObjList ) = 0;

	friend class CNtlTSScrParser;
	friend class CNtlTSScrSaver;
};


#endif