#include "StdAfx.h"
#include "LandMarkTable.h"
#include "Serializer.h"


WCHAR* LandMarkTable::m_pwszSheetList[] =
{
	L"Table_Data_KOR",
	NULL
};

LandMarkTable::LandMarkTable(void)
{
	Init();
}

LandMarkTable::~LandMarkTable(void)
{
	Destroy();
}

bool LandMarkTable::Create(DWORD dwCodePage)
{
	return Table::Create(dwCodePage);
}

void LandMarkTable::Destroy()
{
	Table::Destroy();
}

void LandMarkTable::Init()
{
}

void* LandMarkTable::AllocNewTable(WCHAR* pwszSheetName, DWORD dwCodePage)
{
	if (0 == wcscmp(pwszSheetName, L"Table_Data_KOR"))
	{
		sLAND_MARK_TBLDAT* pLand = new sLAND_MARK_TBLDAT;
		if (NULL == pLand)
			return NULL;

		CPINFO cpInfo;
		if (false == GetCPInfo(dwCodePage, &cpInfo))
		{
			delete pLand;
			return NULL;
		}

		m_dwCodePage = dwCodePage;
		return pLand;
	}

	return NULL;
}

bool LandMarkTable::DeallocNewTable(void* pvTable, WCHAR* pwszSheetName)
{
	if (0 == wcscmp(pwszSheetName, L"Table_Data_KOR"))
	{
		sLAND_MARK_TBLDAT* pLand = (sLAND_MARK_TBLDAT*)pvTable;
		if (FALSE != IsBadReadPtr(pLand, sizeof(*pLand)))
			return false;

		delete pLand;

		return true;
	}

	return false;
}

bool LandMarkTable::AddTable(void * pvTable, bool bReload)
{
	UNREFERENCED_PARAMETER(bReload);

	sLAND_MARK_TBLDAT* pTbldat = (sLAND_MARK_TBLDAT*)pvTable;

	if (false == m_mapTableList.insert(std::pair<TBLIDX, sTBLDAT*>(pTbldat->tblidx, pTbldat)).second)
	{
		Table::CallErrorCallbackFunction(L"[File] : %s\r\n Table Tblidx[%u] is Duplicated ", m_wszXmlFileName, pTbldat->tblidx);
		_ASSERTE(0);
		return false;
	}


	return true;
}

bool LandMarkTable::SetTableData(void* pvTable, WCHAR* pwszSheetName, std::wstring* pstrDataName, BSTR bstrData)
{

	if (0 == wcscmp(pwszSheetName, L"Table_Data_KOR"))
	{
		sLAND_MARK_TBLDAT* pLand = (sLAND_MARK_TBLDAT*)pvTable;

		if (0 == wcscmp(pstrDataName->c_str(), L"Tblidx"))
		{
			CheckNegativeInvalid(pstrDataName->c_str(), bstrData);
			pLand->tblidx = READ_DWORD(bstrData);
		}		
		else
		{
			Table::CallErrorCallbackFunction(L"[File] : %s\n[Error] : Unknown field name found!(Field Name = %s)", m_wszXmlFileName, pstrDataName->c_str());
			return false;
		}
	}
	else
	{
		return false;
	}

	return true;
}


sTBLDAT* LandMarkTable::FindData(TBLIDX tblidx)
{
	if (0 == tblidx)
		return NULL;

	TABLEIT iter;
	iter = m_mapTableList.find(tblidx);
	if (End() == iter)
		return NULL;

	return (sTBLDAT*)(iter->second);
}

bool LandMarkTable::LoadFromBinary(Serializer& serializer, bool bReload)
{
	if (false == bReload)
	{
		Reset();
	}

	BYTE byMargin = 1;
	serializer >> byMargin;

	bool bLoop = true;
	do
	{
		sLAND_MARK_TBLDAT* pTableData = new sLAND_MARK_TBLDAT;
		if (NULL == pTableData)
		{
			//- yoshiki : To log system!
			Destroy();
			return false;
		}

		if (false == pTableData->LoadFromBinary(serializer))
		{
			delete pTableData;
			bLoop = false;
			break;
		}

		//  [4/26/2008 zeroera] : 설명 : 실패하더라도 Load의 종료여부는 File Loading에서 결정한다
		if (false == AddTable(pTableData, bReload))
		{
			delete pTableData;
		}

	} while (false != bLoop);

	return true;
}

bool LandMarkTable::SaveToBinary(Serializer& serializer)
{
	serializer.Refresh();

	BYTE byMargin = 1;
	serializer << byMargin;

	TABLE::iterator iter;
	for (iter = Begin(); End() != iter; iter++)
	{
		sLAND_MARK_TBLDAT* pTableData = (sLAND_MARK_TBLDAT*)(iter->second);

		pTableData->SaveToBinary(serializer);
	}

	return true;
}