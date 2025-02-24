#pragma once
#include "table.h"
#include "NtlVector.h"
#include "NtlObject.h"

#include "NtlSharedDef.h"
#include "ObjectTable.h"

// Object
#pragma pack(push, 4)
struct sDYNAMIC_OBJECT_TBLDAT : public sTBLDAT
{
public:
	sDYNAMIC_OBJECT_TBLDAT(void)
	{
		byStateType = eDBO_DYNAMIC_OBJECT_TYPE_NONE;
		bValidityAble = true;
	}

public:
	bool			bValidityAble;
	BYTE			byType;
	char			szModelName[MAX_LENGTH_MODEL_NAME + 1];
	// Object state 관련 변수들
	BYTE			byStateType;
	TBLIDX			spawnAnimation;
	TBLIDX			idleAnimation;
	TBLIDX			despawnAnimation;
	TBLIDX			state1Animation;
	TBLIDX			state2Animation;
	BYTE			byBoundaryDistance;
	BYTE			byDespawnDistance;
public:

	virtual int GetDataSize()
	{
		return sizeof(*this) - sizeof(void*);
	}
};
#pragma pack(pop)

class DynamicObjectTable : public Table
{
	// Member variables
protected:
	static WCHAR* m_pwszSheetList[];

	// Constructions and Destructions
public:
	DynamicObjectTable(void);
	virtual ~DynamicObjectTable(void);

	// Methods
public:
	bool			Create(DWORD dwCodePage);
	void			Destroy(void);

	sTBLDAT*		FindData(TBLIDX tblidx);

	// Implementations
protected:
	void			Init(void);
	WCHAR**			GetSheetListInWChar(void) { return &m_pwszSheetList[0]; }
	void*			AllocNewTable(WCHAR* pwszSheetName, DWORD dwCodePage);
	bool			DeallocNewTable(void* pvTable, WCHAR* pwszSheetName);
	bool			AddTable(void* pvTable, bool bReload);
	bool			SetTableData(void* pvTable, WCHAR* pwszSheetName, std::wstring* pstrDataName, BSTR bstrData);

public:

	virtual bool				LoadFromBinary(Serializer& serializer, bool bReload);

	virtual bool				SaveToBinary(Serializer& serializer);

private:

	DWORD			m_dwObjectSequence;
};