#include "StdAfx.h"
#include "QuestRewardSelectTable.h"
#include "Serializer.h"

WCHAR* QuestRewardSelectTable::m_pwszSheetList[] =
{
	L"Table_Data_KOR",
	NULL
};


QuestRewardSelectTable::QuestRewardSelectTable(void)
{
	Init();
}

QuestRewardSelectTable::~QuestRewardSelectTable(void)
{
	Destroy();
}

bool QuestRewardSelectTable::Create(DWORD dwCodePage)
{
	return Table::Create(dwCodePage);
}

void QuestRewardSelectTable::Destroy()
{
	Table::Destroy();
}

void QuestRewardSelectTable::Init()
{
}

void* QuestRewardSelectTable::AllocNewTable(WCHAR* pwszSheetName, DWORD dwCodePage)
{
	if (0 == wcscmp(pwszSheetName, L"Table_Data_KOR"))
	{
		sQUEST_REWARD_SELECT_TBLDAT* pQuestRewardSelect = new sQUEST_REWARD_SELECT_TBLDAT;
		if (NULL == pQuestRewardSelect)
			return NULL;

		CPINFO cpInfo;
		if (false == GetCPInfo(dwCodePage, &cpInfo))
		{
			delete pQuestRewardSelect;
			return NULL;
		}

		m_dwCodePage = dwCodePage;
		return pQuestRewardSelect;
	}

	return NULL;
}

bool QuestRewardSelectTable::DeallocNewTable(void* pvTable, WCHAR* pwszSheetName)
{
	if (0 == wcscmp(pwszSheetName, L"Table_Data_KOR"))
	{
		sQUEST_REWARD_SELECT_TBLDAT* pQuestRewardSelect = (sQUEST_REWARD_SELECT_TBLDAT*)pvTable;
		if (FALSE != IsBadReadPtr(pQuestRewardSelect, sizeof(*pQuestRewardSelect)))
			return false;

		delete pQuestRewardSelect;

		return true;
	}

	return false;
}

bool QuestRewardSelectTable::AddTable(void* pvTable, bool bReload)
{
	UNREFERENCED_PARAMETER(bReload);

	sQUEST_REWARD_SELECT_TBLDAT* pQuestRewardSelect = (sQUEST_REWARD_SELECT_TBLDAT*)pvTable;

	if (false == m_mapTableList.insert(std::pair<TBLIDX, sTBLDAT*>(pQuestRewardSelect->tblidx, pQuestRewardSelect)).second)
	{
		Table::CallErrorCallbackFunction(L"[File] : %s\r\n Table Tblidx[%u] is Duplicated ", m_wszXmlFileName, pQuestRewardSelect->tblidx);
		_ASSERTE(0);
		return false;
	}

	return true;
}

bool QuestRewardSelectTable::SetTableData(void* pvTable, WCHAR* pwszSheetName, std::wstring* pstrDataName, BSTR bstrData)
{
	if (0 == wcscmp(pwszSheetName, L"Table_Data_KOR"))
	{
		sQUEST_REWARD_SELECT_TBLDAT* pQuestRewardSelect = (sQUEST_REWARD_SELECT_TBLDAT*)pvTable;

		if (0 == wcscmp(pstrDataName->c_str(), L"Tblidx"))
		{
			pQuestRewardSelect->tblidx = READ_TBLIDX(bstrData);
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


sTBLDAT* QuestRewardSelectTable::FindData(TBLIDX tblidx)
{
	if (0 == tblidx)
		return NULL;

	TABLEIT iter;
	iter = m_mapTableList.find(tblidx);
	if (End() == iter)
		return NULL;

	return (sTBLDAT*)(iter->second);
}

bool QuestRewardSelectTable::LoadFromBinary(Serializer& serializer, bool bReload)
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
		sQUEST_REWARD_SELECT_TBLDAT* pTableData = new sQUEST_REWARD_SELECT_TBLDAT;
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

bool QuestRewardSelectTable::SaveToBinary(Serializer& serializer)
{
	serializer.Refresh();

	BYTE byMargin = 1;
	serializer << byMargin;

	TABLE::iterator iter;
	for (iter = Begin(); End() != iter; iter++)
	{
		sQUEST_REWARD_SELECT_TBLDAT* pTableData = (sQUEST_REWARD_SELECT_TBLDAT*)(iter->second);

		pTableData->SaveToBinary(serializer);
	}

	return true;
}