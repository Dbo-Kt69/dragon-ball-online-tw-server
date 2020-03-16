#pragma once

#include "Table.h"

#pragma pack(push, 4)
struct sITEM_ENCHANT_TBLDAT : public sTBLDAT
{
public:
	WCHAR awName[40 + 1];
	TBLIDX tbxSystemEffect;
	BYTE	bySetType;
	BYTE	byRvType;
	BYTE	ByExclIdex;
	BYTE	byMinLevel;
	BYTE	byMaxLevel;
	BYTE	byFrequency;
	WORD	wEnchantValue;
	BYTE	byKind;
	DWORD	dwEquip;
	BYTE	byGroupNo;
	WORD	wMaxValue;
	BYTE	bIsSuperior;
	BYTE	bIsExcellent;
	BYTE	bIsRare;
	BYTE	bIsLegendary;

protected:

	virtual int GetDataSize()
	{
		return sizeof(*this) - sizeof(void*);
	}
};
#pragma pack(pop)

class ItemEnchantTable : public Table
{
public:
	ItemEnchantTable(void);
	virtual ~ItemEnchantTable(void);

	bool Create(DWORD dwCodePage);
	void Destroy();

	sTBLDAT* FindData(TBLIDX tblidx);

	virtual bool LoadFromBinary(Serializer& serializer, bool bReload);
	virtual bool SaveToBinary(Serializer& serializer);

protected:
	void Init();

	WCHAR** GetSheetListInWChar() { return &(ItemEnchantTable::m_pwszSheetList[0]); }
	void* AllocNewTable(WCHAR* pwszSheetName, DWORD dwCodePage);
	bool DeallocNewTable(void* pvTable, WCHAR* pwszSheetName);
	bool AddTable(void* pvTable, bool bReload);
	bool SetTableData(void* pvTable, WCHAR* pwszSheetName, std::wstring* pstrDataName, BSTR bstrData);

	// WARNING :
	// The value of 'm' in the variable 'afRate[m][n]' means tblidx.
	// For example, if you want to get data whose tblidx is 6, you must use 'm_afRate[6]' instead of 'm_afRate[5]'.
	// The value of 'n' in the variable 'afRate[m][n]' means an index.
	// For example, if you want to get value of 'fRate2', you must use 'm_afRate[m][2]' instead of 'm_afRate[m][1]'.
	// m_afRate[m][n]������ m�� tblidx�� ���մϴ�.
	// ���� ���, tblidx�� 6�� ���� ����Ÿ�� ���� ������ m_afRate[5]�� �ƴ� m_afRate[6]�� ����ؾ� �մϴ�.
	// m_afRate[m][n]������ n�� �ε����� ���մϴ�.
	// ���� ���, fRate2�� ���� ���� ������ m_afRate[m][1]�� �ƴ� m_afRate[m][2]�� ����ؾ� �մϴ�.
	// by YOSHIKI(2009-07-13)

private:
	static WCHAR* m_pwszSheetList[];
};