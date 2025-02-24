#include <GameSocket.h>
#include <Define.h>
#include <Logger.h>
#include <Opcodes.h>
#include <Packet.h>
#include "WorldSession.h"
#include <Game\Object\Player.h>
#include <Game\Object\Mob.h>
#include <Game\Object\Npc.h>
#include <World.h>
#include <Packet\Game\PacketGU.h>
#include <Packet\Game\PacketUG.h>
#include <Packet\Community\PacketUT.h>
#include <Packet\Community\PacketTU.h>
#include <Game\Maps\MapManager.h>
#include <mysqlconn_wrapper.h>
#include <XmlParser2/XmlParser2.h>
#include <ctime>

//----------------------------------------
//	Parcket parser
//----------------------------------------
void			WorldSession::PacketParser(Packet& packet)
{
	//std::lock_guard<std::mutex> guard(m_recvQueueLock);

	PACKETDATA *header = (PACKETDATA*)packet.GetPacketHeader();

		switch (header->wOpCode)
	{
#pragma region (WORKING PACKET)
	case Opcodes::UG_ENTER_WORLD:
	{
		sLog.outError("UG_ENTER_WORLD");
		SendNetMarbleMemberShipNfy();
		SendWorldEnter();
		SendEnterWorldComplete();
		_player->UpdateState(eCHARSTATE::CHARSTATE_SPAWNING);
		break;
	}
	case Opcodes::UG_GAME_LEAVE_REQ:
	{
		sLog.outError("UG_GAME_LEAVE_REQ");
		SendGameLeave(packet);
		break;
	}
	case Opcodes::UG_CHAR_EXIT_REQ:
	{
		sLog.outError("UG_CHAR_EXIT_REQ");
		SendGameLeave(packet, true);
		break;
	}
	case Opcodes::UG_GAME_EXIT_REQ:
	{
		sLog.outError("UG_GAME_EXIT_REQ");
		SendGameExit(packet);//SendGameLeave(packet, false);
		break;
	}
	case Opcodes::UG_CHAR_BIND_REQ:
	{
		sLog.outError("UG_CHAR_BIND_REQ");
		sUG_CHAR_BIND_REQ * req = (sUG_CHAR_BIND_REQ*)packet.GetPacketBuffer();
		sGU_CHAR_BIND_RES res;

		sDB.AddNewBind(_player->GetCharacterID(), _player->GetWorldID(), req->bindObjectTblidx);

		res.wPacketSize = sizeof(sGU_CHAR_BIND_RES) - 2;
		res.wOpCode = GU_CHAR_BIND_RES;
		res.wResultCode = GAME_SUCCESS;
		res.byBindType = DBO_BIND_TYPE_FIRST;
		res.bindObjectTblidx = req->bindObjectTblidx;
		res.bindWorldId = _player->GetWorldID();

		_player->GetPcProfile()->byBindType = res.byBindType;
		_player->GetPcProfile()->bindObjectTblidx = res.bindObjectTblidx;
		_player->GetPcProfile()->bindWorldId = res.bindWorldId;

		SendPacket((char*)&res, sizeof(sGU_CHAR_BIND_RES));
		break;
	}
	case Opcodes::UG_PORTAL_ADD_REQ:
	{
		SendAddPortal(packet);
		break;
	}
	case Opcodes::UG_PORTAL_REQ:
	{
		SendPortalTeleport(packet);
		break;
	}
	case Opcodes::UG_CHAR_SERVER_CHANGE_REQ:
	{
		sLog.outError("UG_CHAR_SERVER_CHANGE_REQ");
		SendEnterWorldTeleport();
		break;
	}
	case Opcodes::UG_CHAR_TARGET_FACING:
	{
		sLog.outError("UG_CHAR_TARGET_FACING");
		sUG_CHAR_TARGET_FACING *req = (sUG_CHAR_TARGET_FACING*)packet.GetPacketBuffer();
		_player->SetTarget(req->hTarget);
		break;
	}
	case Opcodes::UG_LOADING_COMPLETE_NFY:
	{
		sLog.outError("UG_LOADING_COMPLETE_NFY");
		/* ADD PLAYER TO MAP */
		break;
	}
	case Opcodes::UG_CHAR_READY_TO_SPAWN:
	{
		sLog.outError("UG_CHAR_READY_TO_SPAWN");
		Map* m;
		if ((m = sMapMgr.CreateMap(_player->GetWorldID())) == NULL)
		{
			//sLog.outError("Map not found: %d", _player->GetWorldTableID());
			LogoutPlayer(false);
			requestToLogout = true;
			break;
		}
		//sLog.outDebug("Map created / loaded: %d", m->GetId());
		m->Add(_player);
		_player->SetIsReady(true);
		_player->SetState(eCHARSTATE::CHARSTATE_STANDING);
		break;
	}
	case Opcodes::UG_CHAR_READY:
	{
		sLog.outError("UG_CHAR_READY");
		sUG_CHAR_READY res;
		res.byAvatarType = 0;
		res.wOpCode = UG_CHAR_READY;
		res.wPacketSize = sizeof(sUG_CHAR_READY) - 2;
		SendPacket((char*)&res, sizeof(sUG_CHAR_READY));
		break;
	}

#pragma region MOVEMENT
	case Opcodes::UG_CHAR_CHANGE_HEADING:
	{
		//sLog.outError("UG_CHAR_CHANGE_HEADING");
		SendCharHeadChanging(packet);
		break;
	}
	case Opcodes::UG_CHAR_TOGG_SITDOWN:
	{
		//sLog.outError("UG_CHAR_TOGG_SITDOWN");
		SendCharToggleSitDown(packet);
		break;
	}
	case Opcodes::UG_CHAR_MOVE:
	{
		//sLog.outError("UG_CHAR_MOVE");
		SendCharMove(packet);
		break;
	}
	case Opcodes::UG_CHAR_AIR_MOVE_SYNC:
	{
		//sLog.outError("UG_CHAR_AIR_MOVE_SYNC");
		SendCharMoveSync(packet);
		break;
	}
	case Opcodes::UG_CHAR_JUMP:
	{
		//sLog.outError("UG_CHAR_JUMP");
		SendCharJump(packet);
		break;
	}
	case Opcodes::UG_CHAR_JUMP_END:
	{
		//sLog.outError("UG_CHAR_JUMP_END");
		SendCharJumpEnd(packet);
		break;
	}
	case Opcodes::UG_CHAR_DEST_MOVE:
	{
		//sLog.outError("UG_CHAR_DEST_MOVE");
		SendCharDestLoc(packet);
		break;
	}
#pragma endregion END_MOVEMENT

#pragma region SKILL_SLOT_BUFF_HTB
	case Opcodes::UG_QUICK_SLOT_UPDATE_REQ:
	{
		sLog.outError("UG_QUICK_SLOT_UPDATE_REQ");
		SendUpdateQuickSlots(packet);
		break;
	}
	case Opcodes::UG_SOCIAL_ACTION:
	{
		sLog.outError("UG_SOCIAL_ACTION");
		SendSocialSkill(packet);
		break;
	}
#pragma endregion END_SKILL_SLOT_BUFF_HTB

#pragma region ITEM
	case Opcodes::UG_SHOP_ITEM_IDENTIFY_REQ:
	{
		sLog.outDetail("UG_ITEM_IDENTIFY_REQ");
		sUG_SHOP_ITEM_IDENTIFY_REQ* req = (sUG_SHOP_ITEM_IDENTIFY_REQ*)packet.GetPacketBuffer();

		sGU_SHOP_ITEM_IDENTIFY_RES res;

		res.wOpCode = GU_SHOP_ITEM_IDENTIFY_RES;
		res.wPacketSize = sizeof(sGU_SHOP_ITEM_IDENTIFY_RES) - 2;
		res.wResultCode = GAME_SUCCESS;
		res.hNpchandle = req->hNpchandle;
		res.byPlace = req->byPlace;
		res.byPos = req->byPos;
		sLog.outDebug("BUSCANDO ITEM...");
		sITEM_PROFILE* item = _player->GetInventoryManager()->GetItemAtPlaceAndPost(req->byPlace, req->byPos);
		sLog.outDebug("ITEM ENCOTNRADO!");
		res.sItemData.handle = item->handle;
		//res.sItemData.unknown1 = 0;
		//res.sItemData.unknown2 = 0;
		res.sItemData.itemId = 0;
		res.sItemData.itemNo = item->tblidx;
		res.sItemData.charId = _player->GetCharacterID();
		res.sItemData.byPlace = item->byPlace; // eCONTAINER_TYPE
		res.sItemData.byPosition = item->byPos;
		res.sItemData.byStackcount = item->byStackcount;
		res.sItemData.byRank = item->byRank;
		res.sItemData.byCurrentDurability = item->byCurDur;
		res.sItemData.bNeedToIdentify = false;//item->bNeedToIdentify;
		res.sItemData.byGrade = item->byGrade;
		res.sItemData.byBattleAttribute = item->byBattleAttribute; // eBATTLE_ATTRIBUTE
		res.sItemData.byRestrictType = item->byRestrictType; // eITEM_RESTRICT_TYPE
		memcpy(res.sItemData.awchMaker, item->awchMaker, sizeof item->awchMaker);
		res.sItemData.aOptionTblidx = item->aOptionTblidx;
		res.sItemData.aOptionTblidx1 = item->aOptionTblidx1;
		memcpy(res.sItemData.aitemEffect, item->aitemEffect, sizeof item->aitemEffect); // by Szczeepan
		memcpy(res.sItemData.aitemExtraEffect, item->aitemExtraEffect, sizeof item->aitemExtraEffect); // by Szczeepan
		res.sItemData.byDurationType = item->byDurationType; //eDURATIONTYPE
		res.sItemData.nUseStartTime = item->nUseStartTime;
		res.sItemData.nUseEndTime = item->nUseEndTime;
		res.sItemData.unk = 0;
		sLog.outDebug("ENVIANDO PAQUETE...");
		SendPacket((char*)&res, sizeof(sGU_SHOP_ITEM_IDENTIFY_RES));
		sLog.outDebug("PAQUETE ENVIADO");
		break;
	}
	/* is this working as it don't handle HLS & Event etc item ? */
	case Opcodes::UG_ITEM_MOVE_REQ:
	{
		sLog.outError("UG_ITEM_MOVE_REQ");
		SendItemMove(packet);
		break;
	}
	case Opcodes::UG_ITEM_MOVE_STACK_REQ:
	{
		sLog.outError("UG_ITEM_MOVE_STACK_REQ");
		SendItemMoveStack(packet);
		
		break;
	}
	case Opcodes::UG_ITEM_DELETE_REQ:
	{
		sLog.outError("UG_ITEM_DELETE_REQ");
		SendRemoveItem(packet);
		break;
	}
	case Opcodes::UG_SHOP_BUY_REQ:
	{
		sLog.outError("UG_SHOP_BUY_REQ");
		SendShopBuy(packet);
		break;
	}
	case Opcodes::UG_SHOP_SELL_REQ:
	{
		sLog.outError("UG_SHOP_SELL_REQ");
		SendShopSell(packet);
		break;
	}
	case Opcodes::UG_SHOP_START_REQ:
	{
		sLog.outError("UG_SHOP_START_REQ");
		SendShopRequest(packet, true);
		//sLog.outPacketFile(&packet);
		break;
	}
	case Opcodes::UG_SHOP_END_REQ:
	{
		sLog.outError("UG_SHOP_END_REQ");
		SendShopRequest(packet, false);
		break;
	}
	case Opcodes::UG_ITEM_EXCHANGE_REQ:
	{
		sLog.outError("UG_ITEM_EXCHANGE_REQ");
		SendShopItemChange(packet);
		break;
	}
#pragma endregion END_ITEM

#pragma region FIGHT
	case Opcodes::UG_CHAR_TOGG_FIGHTING:
	{
		sLog.outError("UG_CHAR_TOGG_FIGHTING");
		sUG_CHAR_TOGG_FIGHTING *req = (sUG_CHAR_TOGG_FIGHTING*)packet.GetPacketBuffer();
		SendToggleAutoAttack(req->bFightMode);
		break;
	}
#pragma endregion END_FIGHT

#pragma endregion END

#pragma	region	PACKET_IN_PROGRESS
	case Opcodes::UG_BUFF_DROP_REQ:
	{
		sLog.outError("UG_BUFF_DROP_REQ");
		sUG_BUFF_DROP_REQ* req = (sUG_BUFF_DROP_REQ*)packet.GetPacketBuffer();
		sGU_BUFF_DROP_RES DropBuff;

		DropBuff.wOpCode = GU_BUFF_DROP_RES;
		DropBuff.wPacketSize = sizeof(sGU_BUFF_DROP_RES) - 2;
		DropBuff.wResultCode = GAME_SUCCESS;

		SendPacket((char*)&DropBuff, sizeof(sGU_BUFF_DROP_RES));

		BuffTimeInfo* buff = _player->GetAttributesManager()->GetBuff(req->tblidx);
		if (buff)
		{
			_player->SetUnsetBuffEffect(buff->skillInfo, 0, false);
			_player->SetUnsetBuffEffect(buff->skillInfo, 1, false);

			_player->GetAttributesManager()->DeleteBuff(buff->BuffID);

			SendDropBuff(buff->PlayerHandle, buff->BuffID, eDBO_OBJECT_SOURCE::DBO_OBJECT_SOURCE_SKILL);
		}

		/*sGU_BUFF_DROPPED DropedBuff;

		DropedBuff.wOpCode = GU_BUFF_DROPPED;
		DropedBuff.wPacketSize = sizeof(sGU_BUFF_DROPPED) - 2;
		DropedBuff.bySourceType = 0; //eDBO_OBJECT_SOURCE::DBO_OBJECT_SOURCE_SKILL
		DropedBuff.hHandle = _player->GetHandle();
		DropedBuff.Slot = 0;
		DropedBuff.tblidx = req->tblidx;
		SendPacket((char*)&DropedBuff, sizeof(sGU_BUFF_DROPPED));

		_player->ExecuteEffectCalculation(req->tblidx, true);*/
		for (int i = 0; i <= 32; i++)
		{
			if (_player->GetAttributesManager()->sBuffTimeInfo[i].BuffID == req->tblidx)
			{
				_player->GetAttributesManager()->sBuffTimeInfo[i].BuffIsActive = false;
				_player->GetAttributesManager()->sBuffTimeInfo[i].BuffEndTime = INVALID_TBLIDX;
				_player->GetAttributesManager()->sBuffTimeInfo[i].BuffTime = INVALID_TBLIDX;
				_player->GetAttributesManager()->sBuffTimeInfo[i].BuffID = INVALID_TBLIDX;				
			}			
		}
		break;
	}
	case Opcodes::UG_CROSSFIRE_REQ: // F keyboard
	{
		sLog.outError("UG_CROSSFIRE_REQ");
		break;
	}
	case Opcodes::UG_SKILL_TARGET_LIST:
	{
		sUG_SKILL_TARGET_LIST* req = (sUG_SKILL_TARGET_LIST*)packet.GetPacketBuffer();
		sLog.outError("UG_SKILL_TARGET_LIST");
		sLog.outError("Target count:%u \n\r", req->byApplyTargetCount);
		break;
	}
	case Opcodes::UG_GIFT_SHOP_START_REQ:
	{
		sLog.outError("UG_GIFT_SHOP_START_REQ");
		sGU_GIFT_SHOP_START_RES GiftStart;
		
		GiftStart.wOpCode = GU_GIFT_SHOP_START_RES;
		GiftStart.wPacketSize = sizeof(sGU_GIFT_SHOP_START_RES) - 2;		
		GiftStart.wResultCode = GAME_SUCCESS;		
		GiftStart.unknown = _player->GetPcProfile()->sLocalize.WP_Point;
		GiftStart.WpPoit = _player->GetPcProfile()->sLocalize.WP_Point;//show WpPoit too
		
		SendPacket((char*)&GiftStart, sizeof(sGU_GIFT_SHOP_START_RES));

		sGU_GIFT_SHOP_TAB_INFO_NFY GiftTab;
		
		GiftTab.wOpCode = GU_GIFT_SHOP_TAB_INFO_NFY;
		GiftTab.wPacketSize = sizeof(sGU_GIFT_SHOP_TAB_INFO_NFY) - 2;		
		GiftTab.TabID = 0;
		GiftTab.TotalItemCount = 72;
		wcscpy_s(GiftTab.TabName, DBO_MAX_GIFT_TAB_NAME + 1, (L"Dev"));
		const int ItemList[12][6] = {
			{ 7001426,7001427,7001428,7001429,7001430,7001431},
			{ 7001432,7001433,7001434,7001435,7001436,7001437},
			{ 7001438,7001439,7001440,7001450,7001451,7001452},
			{ 7001453,7001454,7001455,7001456,7001457,7001458},
			{ 7001459,7001460,7001461,7001462,7001463,7001464},
			{ 7001465,7001466,7001467,7001468,7001469,7001470},
			{ 11140309,11140314,11120219,11120117,11120118,11120119},
			{ 11120120,11120121,11120122,11120123,11120124,11120125},
			{ 11120126,11120127,11120128,11120129,11120130,11120131},
			{ 11120132,11120133,11120134,11120135,11120136,11120137},
			{ 11120138,11120139,11120140,11120141,11120142,11120143},
			{ 11120144,11120145,11120146,11120147,11120148,11120154},
		};
		for (int i = 0; i <= GiftTab.TotalItemCount; i++)
		{

			GiftTab.ItemProfile[i].ItemID = ItemList[0][i];
			GiftTab.ItemProfile[i].Price = 0;
		}		

		SendPacket((char*)&GiftTab, sizeof(sGU_GIFT_SHOP_TAB_INFO_NFY));
		
		break;
	}
	case Opcodes::UG_GIFT_SHOP_BUY_REQ:
	{
		sLog.outError("UG_GIFT_SHOP_BUY_REQ");
		sUG_GIFT_SHOP_BUY_REQ *req = (sUG_GIFT_SHOP_BUY_REQ*)packet.GetPacketBuffer();
		sGU_GIFT_SHOP_BUY_RES GiftShopBuy;

		GiftShopBuy.wOpCode = GU_GIFT_SHOP_BUY_RES;
		GiftShopBuy.wPacketSize = sizeof(sGU_GIFT_SHOP_BUY_RES) - 2;
		GiftShopBuy.wResultCode = GAME_SUCCESS;
		GiftShopBuy.WpPoit = 0;
		const int ItemList[12][6] = {
			{ 7001426,7001427,7001428,7001429,7001430,7001431 },
			{ 7001432,7001433,7001434,7001435,7001436,7001437 },
			{ 7001438,7001439,7001440,7001450,7001451,7001452 },
			{ 7001453,7001454,7001455,7001456,7001457,7001458 },
			{ 7001459,7001460,7001461,7001462,7001463,7001464 },
			{ 7001465,7001466,7001467,7001468,7001469,7001470 },
			{ 11140309,11140314,11120219,11120117,11120118,11120119 },
			{ 11120120,11120121,11120122,11120123,11120124,11120125 },
			{ 11120126,11120127,11120128,11120129,11120130,11120131 },
			{ 11120132,11120133,11120134,11120135,11120136,11120137 },
			{ 11120138,11120139,11120140,11120141,11120142,11120143 },
			{ 11120144,11120145,11120146,11120147,11120148,11120154 },
		};
		for (int i = 0; i < req->byBuyCount; i++)
		{
			sITEM_PROFILE createdItem;
			WORD result = _player->GetInventoryManager()->PerformShopBuy(ItemList[req->sBuyData[i].byMerchantTab][req->sBuyData[i].byItemPos], req->sBuyData[i].byStack, createdItem);
			if (result == GAME_SUCCESS && createdItem.tblidx != INVALID_TBLIDX)
			{
				//sLog.outDetail("Item Created\n");
				SendItemCreate(&createdItem);
			}
		}		


		SendPacket((char*)&GiftShopBuy, sizeof(sGU_GIFT_SHOP_BUY_RES));
		break;
	}
	case Opcodes::UG_SHOP_GAMBLE_BUY_REQ:
	{
		sLog.outError("UG_SHOP_GAMBLE_BUY_REQ");
		sUG_SHOP_GAMBLE_BUY_REQ *req = (sUG_SHOP_GAMBLE_BUY_REQ*)packet.GetPacketBuffer();
		sGU_SHOP_GAMBLE_BUY_RES res;
		sITEM_PROFILE createdItem;
		int CreatedItem;
		for (auto it = sTBM.GetItemMixMachineTable()->Begin(); it != sTBM.GetItemMixMachineTable()->End(); it++)
		{
			sITEM_MIX_MACHINE_TBLDAT* pMusoData = (sITEM_MIX_MACHINE_TBLDAT*)it->second;
			if (pMusoData != NULL)
			{
				CreatedItem = pMusoData->aBuiltInRecipeTblidx[0];
			}
		}
		WORD result = _player->GetInventoryManager()->PerformShopBuy(6003020, 1, createdItem);
		if (result == GAME_SUCCESS && createdItem.tblidx != INVALID_TBLIDX)
		{
			//sLog.outDetail("Item Created\n");
			SendItemCreate(&createdItem);
		}
		res.handle = req->handle;
		res.hItem = createdItem.handle;
		res.wOpCode = GU_SHOP_GAMBLE_BUY_RES;
		res.wPacketSize = sizeof(sGU_SHOP_GAMBLE_BUY_RES) - 2;
		res.wResultCode = GAME_SUCCESS;		
		
		SendPacket((char*)&res, sizeof(sGU_SHOP_GAMBLE_BUY_RES));
		break;
	}
	case Opcodes::UG_CHARTITLE_SELECT_REQ:
	{
		sLog.outError("UG_CHARTITLE_SELECT_REQ");
		sUG_CHARTITLE_SELECT_REQ *req = (sUG_CHARTITLE_SELECT_REQ*)packet.GetPacketBuffer();
		//Active the Title Sellected			
		sql::ResultSet* result = sDB.executes("SELECT * FROM `titlelist` WHERE `characterID` = '%d' AND `TitleID` = '%d'", _player->GetCharacterID(), req->TitleID);
		if (result == NULL)
			return;		
		if (result->rowsCount() <= 0)
		{
			sGU_CHARTITLE_SELECT_RES SelectTitle;

			SelectTitle.wOpCode = GU_CHARTITLE_SELECT_RES;
			SelectTitle.wPacketSize = sizeof(sGU_CHARTITLE_SELECT_RES) - 2;
			SelectTitle.wResultCode = GAME_SUCCESS;
			SelectTitle.TitleID = -1;
			_player->GetPcProfile()->sMarking.dwCode = -1;

			SendPacket((char*)&SelectTitle, sizeof(sGU_CHARTITLE_SELECT_RES));

			//Send Title Selected to all Players
			sGU_CHARTITLE_SELECT_NFY SelectTitleNfy;

			SelectTitleNfy.wOpCode = GU_CHARTITLE_SELECT_NFY;
			SelectTitleNfy.wPacketSize = sizeof(sGU_CHARTITLE_SELECT_NFY) - 2;

			SelectTitleNfy.TitleID = -1;
			SelectTitleNfy.handle = _player->GetHandle();

			_player->SendToPlayerList((char*)&SelectTitleNfy, sizeof(sGU_CHARTITLE_SELECT_NFY));			
		}
		else
		{
			sGU_CHARTITLE_SELECT_RES SelectTitle;

			SelectTitle.wOpCode = GU_CHARTITLE_SELECT_RES;
			SelectTitle.wPacketSize = sizeof(sGU_CHARTITLE_SELECT_RES) - 2;
			SelectTitle.wResultCode = GAME_SUCCESS;
			SelectTitle.TitleID = req->TitleID;
			_player->GetPcProfile()->sMarking.dwCode = req->TitleID;

			SendPacket((char*)&SelectTitle, sizeof(sGU_CHARTITLE_SELECT_RES));

			//Send Title Selected to all Players
			sGU_CHARTITLE_SELECT_NFY SelectTitleNfy;

			SelectTitleNfy.wOpCode = GU_CHARTITLE_SELECT_NFY;
			SelectTitleNfy.wPacketSize = sizeof(sGU_CHARTITLE_SELECT_NFY) - 2;

			SelectTitleNfy.TitleID = req->TitleID;
			SelectTitleNfy.handle = _player->GetHandle();

			_player->SendToPlayerList((char*)&SelectTitleNfy, sizeof(sGU_CHARTITLE_SELECT_NFY));

		}
		delete result;
		break;
	}
	case Opcodes::UG_DROPITEM_INFO_REQ:
	{
		sLog.outError("UG_DROPITEM_INFO_REQ");
		sUG_DROPITEM_INFO_REQ *req = (sUG_DROPITEM_INFO_REQ*)packet.GetPacketBuffer();
		sGU_DROPITEM_INFO_RES DropInfo;
		memset(&DropInfo, 0, sizeof(sGU_DROPITEM_INFO_RES));
		DropInfo.wOpCode = GU_DROPITEM_INFO_RES;
		DropInfo.wPacketSize = sizeof(sGU_DROPITEM_INFO_RES) - 2;

		DropInfo.ItemDropInfo.handle = req->handle;
		DropInfo.ItemDropInfo.unk = 0;
		//DropInfo.ItemDropInfo.unknown1 = 0;
		//DropInfo.ItemDropInfo.unknown2 = 0;

		SendPacket((char*)&DropInfo, sizeof(sGU_DROPITEM_INFO_RES));
		break;
	}
	case Opcodes::UG_ULTIMATE_DUNGEON_ENTER_REQ:
	{
		sLog.outError("UG_ULTIMATE_DUNGEON_ENTER_REQ");
		sUG_ULTIMATE_DUNGEON_ENTER_REQ *req = (sUG_ULTIMATE_DUNGEON_ENTER_REQ*)packet.GetPacketBuffer();
		SendDangeonTeleport(req->handle, req->Dificulty);
		break;
	}
		case Opcodes::UG_ZENNY_PICK_REQ:
		{
			sLog.outError("UG_ZENNY_PICK_REQ");
			sUG_ZENNY_PICK_REQ *req = (sUG_ZENNY_PICK_REQ*)packet.GetPacketBuffer();
			SendPickUp(req->handle);
			break;
		}
		case Opcodes::UG_ITEM_PICK_REQ:
		{
			sLog.outError("UG_ITEM_PICK_REQ");
			sUG_ITEM_PICK_REQ *req = (sUG_ITEM_PICK_REQ*)packet.GetPacketBuffer();
			SendPickUp(req->handle);
			break;
		}
		case Opcodes::UG_CHAR_LOCATION_SYNC:
		{
			sLog.outError("UG_CHAR_LOCATION_SYNC");
			break;
		}
		case Opcodes::UG_TUTORIAL_HINT_UPDATE_REQ:
		{
			sUG_TUTORIAL_HINT_UPDATE_REQ *req = (sUG_TUTORIAL_HINT_UPDATE_REQ*)packet.GetPacketBuffer();
			sLog.outError("UG_TUTORIAL_HINT_UPDATE_REQ: %d", req->dwTutorialHint);
			break;
		}
		case Opcodes::UG_AUTH_KEY_FOR_COMMUNITY_SERVER_REQ:
		{
			sLog.outError("UG_CHAR_LOCATION_SYNC");
			sGU_AUTH_KEY_FOR_COMMUNITY_SERVER_RES res;
			
			res.wOpCode = GU_AUTH_KEY_FOR_COMMUNITY_SERVER_RES;
			res.wResultCode = GAME_SUCCESS;
			res.wPacketSize = sizeof(sGU_AUTH_KEY_FOR_COMMUNITY_SERVER_RES) - 2;
			memcpy(res.abyAuthKey, "SE@WASDE#$RFWD@F", MAX_SIZE_AUTH_KEY);

			SendPacket((char*)&res, sizeof(sGU_AUTH_KEY_FOR_COMMUNITY_SERVER_RES));
			break;
		}
		case Opcodes::UG_CHAR_NPCSERVER_MOVE_SYNC:
		{
			sLog.outError("UG_CHAR_NPCSERVER_MOVE_SYNC");
			/*sGU_CHAR_SERVER_CHANGE_RES res;

			std::string addr = sXmlParser.GetChildStr("CharServerList", "CharServer1", "IP");
			int port = sXmlParser.GetChildInt("CharServerList", "CharServer1", "Port");

			memcpy(res.serverInfo.szCharacterServerIP, addr.c_str(), strlen(addr.c_str()));
			res.serverInfo.wCharacterServerPortForClient = port;
			memcpy(res.achAuthKey, "Dbo", strlen("Dbo"));
			res.serverInfo.dwLoad = 0;

			res.wOpCode = GU_CHAR_SERVER_CHANGE_RES;
			res.wPacketSize = sizeof(sGU_CHAR_SERVER_CHANGE_RES) - 2;
			res.wResultCode = GAME_SUCCESS;

			SendPacket((char*)&res, sizeof(sGU_CHAR_SERVER_CHANGE_RES));*/
			break;
		}
		case Opcodes::UG_WAR_FOG_UPDATE_REQ:
		{
			SendFogOfWarRes(packet);
			break;
		}
		case Opcodes::UG_WORLD_MAP_STATUS:
		{
			// what to do here ?
			sLog.outError("UG_WORLD_MAP_STATUS");
			break;
		}
		case Opcodes::UG_CHAR_READY_FOR_COMMUNITY_SERVER_NFY:
		{
			sLog.outError("UG_CHAR_READY_FOR_COMMUNITY_SERVER_NFY");
			break;
		}
		// NOT WORKING BECAUSE THIS HANDLE TARGET OF TARGET TOO AND IT IS NOT MADE
		case Opcodes::UG_CHAR_TARGET_SELECT:
		{
			sLog.outError("UG_CHAR_TARGET_SELECT");
			sUG_CHAR_TARGET_SELECT *req = (sUG_CHAR_TARGET_SELECT*)packet.GetPacketBuffer();
			SendTargetSelection(req->hTarget);
			break;
		}
		case Opcodes::UG_SCOUTER_ACTIVATION_REQ:
		{
			sLog.outError("UG_SCOUTER_ACTIVATION_REQ");
			sUG_SCOUTER_ACTIVATION_REQ *req = (sUG_SCOUTER_ACTIVATION_REQ*)packet.GetPacketBuffer();
			sGU_SCOUTER_ACTIVATION_RES res;
			memset(&res, 0, sizeof(sGU_SCOUTER_ACTIVATION_RES));
			res.wOpCode = GU_SCOUTER_ACTIVATION_RES;
			res.wPacketSize = sizeof(sGU_SCOUTER_ACTIVATION_RES) - 2;
			res.hTarget = req->handle;
			res.wResultCode = GAME_SUCCESS;
				
			Player* PlayerInfo = static_cast<Player*>(_player->GetFromList(_player->GetTarget()));
			if (PlayerInfo != NULL)
			{
				res.PowerLevel = PlayerInfo->GetPowerLevel();
				res.DoggeRate = PlayerInfo->GetPcProfile()->avatarAttribute.wLastDodgeRate;//Dogge Rate
				res.HitRate = PlayerInfo->GetPcProfile()->avatarAttribute.wLastAttackRate; //HitRate
			}
			Mob* MobInfo = static_cast<Mob*>(_player->GetFromList(_player->GetTarget()));
			if (MobInfo != NULL && MobInfo->GetIsDead() == false && MobInfo->GetInitialSpawn())
			{
				res.PowerLevel = MobInfo->GetPowerLevel();
				res.DoggeRate = MobInfo->GetMobData().Dodge_rate;//Dogge Rate
				res.HitRate = MobInfo->GetMobData().Attack_rate; //HitRate
			}
			Npc* NpcInfo = static_cast<Npc*>(_player->GetFromList(_player->GetTarget()));
			if (NpcInfo != NULL)
			{
				res.PowerLevel = NpcInfo->GetNpcData().UniqueID;
				res.DoggeRate = NpcInfo->GetNpcData().Dodge_rate;//Dogge Rate
				res.HitRate = NpcInfo->GetNpcData().Attack_rate; //HitRate
			}					
				
			SendPacket((char*)&res, sizeof(sGU_SCOUTER_ACTIVATION_RES));
			break;
		}		
// -------------- QUEST ----------
		case Opcodes::UG_TS_CONFIRM_STEP_FOR_USE_ITEM_REQ:
		{
			sUG_TS_CONFIRM_STEP_FOR_USE_ITEM_REQ* req = (sUG_TS_CONFIRM_STEP_FOR_USE_ITEM_REQ*)packet.GetPacketBuffer();
			sGU_TS_CONFIRM_STEP_RES res;
			res.wOpCode = GU_TS_CONFIRM_STEP_RES;
			res.wPacketSize = sizeof(sGU_TS_CONFIRM_STEP_RES) - 2;
			res.byTsType = req->byTsType;
			res.wResultCode = RESULT_SUCCESS;
			res.tId = req->tId;
			res.tcCurId = req->tcCurId;
			res.tcNextId = req->tcNextId;
			res.dwParam = 0;
			SendPacket((char*)&res, sizeof(sGU_TS_CONFIRM_STEP_RES));
			sLog.outError("UG_TS_CONFIRM_STEP_FOR_USE_ITEM_REQ");
			break;
		}
		case Opcodes::UG_TS_UPDATE_STATE:
		{
			sLog.outError("UG_TS_UPDATE_STATE");
			break;
		}
		case Opcodes::UG_TS_EXCUTE_TRIGGER_OBJECT:
		{
			sLog.outError("UG_TS_EXCUTE_TRIGGER_OBJECT");
			SendTsExcuteTriggerObject(packet);
			break;
		}
		case Opcodes::UG_TS_CONFIRM_STEP_REQ:
		{
			sLog.outError("UG_TS_CONFIRM_STEP_REQ");
			//sLog.outDebug("~~~~~~~~~ UG_TS_CONFIRM_STEP_REQ ~~~~~~~~~");
			SendQuestAcept(packet);			
			break;
		}
		case Opcodes::UG_QUEST_ITEM_DELETE_REQ:
		{
			SendQuestItemDelete(packet);
			break;
		}
		case Opcodes::UG_QUEST_ITEM_MOVE_REQ:
		{
			SendQuestItemMove(packet);
			break;
		}
		case Opcodes::UG_QUEST_GIVEUP_REQ:
		{
			sLog.outError("UG_QUEST_GIVEUP_REQ");
			SendQuestGiveUp(packet);
			break;
		}
		case Opcodes::UG_QUEST_OBJECT_VISIT_REQ:
		{
			sLog.outError("UG_QUEST_OBJECT_VISIT_REQ");
			sUG_QUEST_OBJECT_VISIT_REQ* req = (sUG_QUEST_OBJECT_VISIT_REQ*)packet.GetPacketBuffer();

			//New system
			QuestData* quest = _player->GetQuestManager()->FindQuestById(req->qId);
			if (quest)
			{
				sLog.outDebug("new QuestId %d req->qId %d", quest->QuestID, req->qId);
				if (quest->QuestID == req->qId)
				{
					for (int slot = 0; slot < quest->uEvtData.MAX_VISIT_EVT; slot++)
					{
						sLog.outDebug("new req->objectTblidx %d player ObjTblidx %d", req->objectTblidx, quest->uEvtData.sVisitEvt[slot].uiObjTblIdx);
						if (req->objectTblidx == quest->uEvtData.sVisitEvt[slot].uiObjTblIdx)
						{
							quest->uEvtData.sVisitEvt[slot].bCompleted = true;

							SendQuestSVRevtUpdateNotify(req->qId, quest->tcId, quest->taId, quest->evtDataType, slot, &quest->uEvtData);
							break;
						}

					}
				}
			}
			//NEw System

			/*for (int i = 0; i < 30; i++)
			{
				sLog.outDebug("QuestId %d req->qId %d", _player->GetAttributesManager()->QuestDat[i].QuestID, req->qId);
				if (_player->GetAttributesManager()->QuestDat[i].QuestID == req->qId)
				{
					for (int slot = 0; slot < _player->GetAttributesManager()->QuestDat[i].uEvtData.MAX_VISIT_EVT; slot++)
					{
						sLog.outDebug("req->objectTblidx %d player ObjTblidx %d", req->objectTblidx, _player->GetAttributesManager()->QuestDat[i].uEvtData.sVisitEvt[slot].uiObjTblIdx);
						if (req->objectTblidx == _player->GetAttributesManager()->QuestDat[i].uEvtData.sVisitEvt[slot].uiObjTblIdx)
						{
							_player->GetAttributesManager()->QuestDat[i].uEvtData.sVisitEvt[slot].bCompleted = true;

							SendQuestSVRevtUpdateNotify(req->qId,
								_player->GetAttributesManager()->QuestDat[i].tcId,
								_player->GetAttributesManager()->QuestDat[i].taId,
								_player->GetAttributesManager()->QuestDat[i].evtDataType,
								slot,
								&_player->GetAttributesManager()->QuestDat[i].uEvtData);
							break;
						}
						
					}
					
					break;
				}
				
			}*/
			

			sGU_QUEST_OBJECT_VISIT_RES res;
			res.wOpCode = GU_QUEST_OBJECT_VISIT_RES;
			res.wPacketSize = sizeof(sGU_QUEST_OBJECT_VISIT_RES) - 2;
			res.wResultCode = GAME_SUCCESS;
			res.qId = req->qId;
			res.worldId = req->worldId;
			res.byObjType = req->byObjType;
			res.objectTblidx = req->objectTblidx;
			SendPacket((char*)&res, sizeof(sGU_QUEST_OBJECT_VISIT_RES));
			break;
		}
// -------------- QUEST ----------
		case Opcodes::UG_SKILL_LEARN_REQ:
		{
			sLog.outError("UG_SKILL_LEARN_REQ");
			sUG_SKILL_LEARN_REQ *req = (sUG_SKILL_LEARN_REQ*)packet.GetPacketBuffer();
			LearnSkill(req->skillTblidx);
			break;
		}
		case Opcodes::UG_SKILL_UPGRADE_REQ:
		{
			sLog.outError("UG_SKILL_UPGRADE_REQ");
			UpgradeSkill(packet);
			break;
		}
		case Opcodes::UG_CHAR_SKILL_REQ:
		{
			sLog.outError("UG_CHAR_SKILL_REQ");		
			if (_player->GetState()->sCharStateBase.dwConditionFlag == eCHARCONDITION_FLAG::CHARCOND_SKILL_INABILITY_FLAG ||
				_player->GetState()->sCharStateBase.dwConditionFlag == eCHARCONDITION_FLAG::CHARCOND_BATTLE_INABILITY_FLAG)
			{
				sGU_CHAR_SKILL_RES sSkil;
				sSkil.wPacketSize = sizeof(sGU_CHAR_SKILL_RES) - 2;
				sSkil.wOpCode = GU_CHAR_SKILL_RES;
				sSkil.wResultCode = GAME_SKILL_CANT_CAST_NOW;
				SendPacket((char*)&sSkil, sizeof(sGU_CHAR_SKILL_RES));
			}
			else
			{
				if (_player->GetIsSkillCasting() == true)
				{
					sGU_CHAR_SKILL_RES sSkil;
					sSkil.wPacketSize = sizeof(sGU_CHAR_SKILL_RES) - 2;
					sSkil.wOpCode = GU_CHAR_SKILL_RES;
					sSkil.wResultCode = GAME_SKILL_CANT_CAST_NOW;
					SendPacket((char*)&sSkil, sizeof(sGU_CHAR_SKILL_RES));
				}
				else
				UseSkill(packet);
			}			
			break;
		}
		case Opcodes::UG_CHAR_REVIVAL_REQ:
		{
			sLog.outError("UG_CHAR_REVIVAL_REQ");
			_player->SetIsDead(false);
			_player->SetIsFighting(false);
			sGU_UPDATE_CHAR_LP LPs;
			LPs.wOpCode = GU_UPDATE_CHAR_LP;
			LPs.wPacketSize = sizeof(sGU_UPDATE_CHAR_LP) - 2;
			_player->GetPcProfile()->dwCurLP = _player->GetPcProfile()->avatarAttribute.wLastMaxLP %20;
			LPs.dwLpEpEventId = 0;
			LPs.handle = _player->GetHandle();
			LPs.wCurLP = _player->GetPcProfile()->dwCurLP;
			LPs.wMaxLP = _player->GetPcProfile()->avatarAttribute.wLastMaxLP;
			SendPacket((char*)&LPs, sizeof(sGU_UPDATE_CHAR_LP));
			_player->SendToPlayerList((char*)&LPs, sizeof(sGU_UPDATE_CHAR_LP));

			sGU_CHAR_REVIVAL_RES revive;
			revive.wOpCode = GU_CHAR_REVIVAL_RES;
			revive.wPacketSize = sizeof(sGU_CHAR_REVIVAL_RES) - 2;
			revive.wResultCode = GAME_SUCCESS;
			SendPacket((char*)&revive, sizeof(sGU_CHAR_REVIVAL_RES));	
			_player->TeleportToPopo();
			
						
			break;
		}
		case Opcodes::UG_CHAR_ATTACK_BEGIN:
		{
			//sLog.outError("UG_CHAR_ATTACK_BEGIN on target: %d", _player->GetTarget());
			//_player->SetState(eCHARSTATE::CHARSTATE_STANDING);
			SendToggleAutoAttack(true);
			
			sGU_CHAR_IS_BATTLECOMBATING battle;

			battle.wOpCode = GU_CHAR_IS_BATTLECOMBATING;
			battle.wPacketSize = sizeof(sGU_CHAR_IS_BATTLECOMBATING) - 2;
			battle.a = 0x00;
			battle.b = 0x00;
			battle.c = 0x00;
			battle.fight = true;

			SendPacket((char*)&battle, sizeof(sGU_CHAR_IS_BATTLECOMBATING));

			break;
		}
		case Opcodes::UG_CHAR_ATTACK_END:
		{
			//sLog.outError("UG_CHAR_ATTACK_END");
			sUG_CHAR_ATTACK_END* req = (sUG_CHAR_ATTACK_END *)packet.GetPacketBuffer();
			if (req->byType == 0)
			{
				if (req->byAvatarType == OBJTYPE_PC)
				{					
					SendToggleAutoAttack(false);

					sGU_CHAR_IS_BATTLECOMBATING battle;

					battle.wOpCode = GU_CHAR_IS_BATTLECOMBATING;
					battle.wPacketSize = sizeof(sGU_CHAR_IS_BATTLECOMBATING) - 2;
					battle.a = 0x00;
					battle.b = 0x00;
					battle.c = 0x00;
					battle.fight = false;

					SendPacket((char*)&battle, sizeof(sGU_CHAR_IS_BATTLECOMBATING));
				}
			}
			break;
		}
		
		case Opcodes::UG_QUICK_SLOT_DEL_REQ:
		{
			//sLog.outError("UG_QUICK_SLOT_DEL_REQ");
			SendRemoveQuickSlots(packet);
			break;
		}
		
		case Opcodes::UG_SHOP_NETPYITEM_START_REQ:
		{
			SendNetPyStart(packet);
			break;
		}
		case Opcodes::UG_SHOP_NETPYITEM_BUY_REQ:
		{
			SendNetPyBuy(packet);
			break;
		}
		case Opcodes::UG_SHOP_NETPYITEM_END_REQ:
		{
			SendNetPyEnd(packet);
			break;
		}
		case Opcodes::UG_CASHITEM_HLSHOP_REFRESH_REQ:
		{			
			SendAvatarItemCashInfo();
			break;
		}
		case Opcodes::UG_CASHITEM_HLSHOP_START_REQ:
		{
			SendHLSShopStart(packet);
			break;
		}
		case Opcodes::UG_CASHITEM_HLSHOP_END_REQ:
		{
			SendHLSShopEnd(packet);
			break;
		}
		case Opcodes::UG_CASHITEM_START_REQ:
		{
			SendCashItemStart(packet);
			break;
		}
		case Opcodes::UG_CASHITEM_BUY_REQ:
		{
			SendCashItemBuy(packet);
			break;
		}
		case Opcodes::UG_CASHITEM_END_REQ:
		{
			SendCashItemEnd(packet);
			break;
		}
		case Opcodes::UG_CASHITEM_MOVE_REQ:
		{
			SendCashItemMove(packet);
			break;
		}
		case Opcodes::UG_CHAR_FOLLOW_MOVE:
		{			
			SendCharFollowMove(packet);
			break;
		}
		case Opcodes::UG_CHAR_FOLLOW_MOVE_SYNC:
		{			
			SendCharSyncFollow(packet);
			break;
		}
		case Opcodes::UG_PERFORMANCE_DATA_NFY:
		{
			sLog.outDebug("~~~~~~~~~ UG_PERFORMANCE_DATA_NFY ~~~~~~~~~");
			break;
		}
		case Opcodes::UG_TUTORIAL_PLAY_QUIT_REQ:
		{
			sLog.outError("UG_TUTORIAL_PLAY_QUIT_REQ");
			break;
		}
		case Opcodes::UG_CHAR_DIRECT_PLAY_ACK:
		{
			sLog.outError("UG_CHAR_DIRECT_PLAY_ACK");
			sUG_CHAR_DIRECT_PLAY_ACK* req = (sUG_CHAR_DIRECT_PLAY_ACK*)packet.GetPacketBuffer();

			sGU_CHAR_DIRECT_PLAY res;

			res.wOpCode = GU_CHAR_DIRECT_PLAY;
			res.wPacketSize = sizeof(sGU_CHAR_DIRECT_PLAY) - 2;
			res.hSubject = _player->GetHandle();
			res.bSynchronize = false;
			res.byPlayMode = 1;
			res.directTblidx = 1000;

			SendPacket((char*)&res, sizeof(sGU_CHAR_DIRECT_PLAY));
			break;
		}
		case Opcodes::UG_SCS_CHECK_START_RES:
		{
			sLog.outError("UG_SCS_CHECK_START_RES");
			sGU_SCS_CHECK_REQ BotCheck;
			
			BotCheck.wOpCode = GU_SCS_CHECK_REQ;
			BotCheck.wPacketSize = sizeof(sGU_SCS_CHECK_REQ) - 2;
			BotCheck.byType = 0;							

			SendPacket((char*)&BotCheck, sizeof(sGU_SCS_CHECK_REQ));			
			break;
		}
		case Opcodes::UG_SCS_CHECK_RES:
		{
			sLog.outError("UG_SCS_CHECK_RES");			
			break;
		}
		case Opcodes::UG_SERVER_COMMAND:
		{
			ExecuteServerCommand(packet);
			break;
		}		
		case Opcodes::UG_CHAR_AIR_MOVE:
		{
			SendAirJMove(packet);
			break;
		}
		case Opcodes::UG_CHAR_AIR_JUMP:
		{			
			SendAirJumpMove(packet);
			break;
		}
		case Opcodes::UG_CHAR_AIR_DASH:
		{			
			SendAirDashMove(packet);
			break;
		}
		case Opcodes::UG_CHAR_AIR_FALLING:
		{
			SendAirFalling(packet);
			break;
		}
		case Opcodes::UG_CHAR_AIR_END:
		{
			SendAirEnd(packet);			
			break;
		}
		case UG_HTB_START_REQ:
		{
			sUG_HTB_START_REQ* req = (sUG_HTB_START_REQ*)packet.GetPacketBuffer();

			sGU_HTB_START_RES HTBStart;		

			HTBStart.wOpCode = GU_HTB_START_RES;
			HTBStart.wPacketSize = sizeof(sGU_HTB_START_RES) - 2;
			HTBStart.wResultCode = GAME_SUCCESS;
			HTBStart.bySkillSlot = req->bySkillSlot;
			SendPacket((char*)&HTBStart, sizeof(sGU_HTB_START_RES));
			int skillID = _player->HTBID;
			sGU_UPDATE_CHAR_STATE state;

			state.wPacketSize = sizeof(sGU_UPDATE_CHAR_STATE) - 2;
			state.wOpCode = GU_UPDATE_CHAR_STATE;

			state.handle = _player->GetHandle();
			state.sCharState.sCharStateBase.byStateID = eCHARSTATE::CHARSTATE_HTB;
		
			state.sCharState.sCharStateBase.vCurLoc.x = _player->GetVectorPosition().x;
			state.sCharState.sCharStateBase.vCurLoc.y = _player->GetVectorPosition().y - 15;
			state.sCharState.sCharStateBase.vCurLoc.z = _player->GetVectorPosition().z;
			state.sCharState.sCharStateBase.vCurDir.x = _player->GetVectorOriantation().x;
			state.sCharState.sCharStateBase.vCurDir.y = _player->GetVectorOriantation().y;
			state.sCharState.sCharStateBase.vCurDir.z = _player->GetVectorOriantation().x;
			state.sCharState.sCharStateBase.dwConditionFlag = 0;
			//	res.sCharState.sCharStateBase.bFightMode = false;
			state.sCharState.sCharStateBase.dwStateTime = 2;
			/////////////////////////////////////////////////////////////////////////////////////////
			HTBSetTable * dat = sTBM.GetHTBSetTable();
			sHTB_SET_TBLDAT * tbldat = reinterpret_cast<sHTB_SET_TBLDAT*>(dat->FindData(skillID));
			SkillTable * skillTable = sTBM.GetSkillTable();
			sSKILL_TBLDAT * skillDataOriginal = reinterpret_cast<sSKILL_TBLDAT*>(skillTable->FindData(skillID));
			if (tbldat)
			{
				printf("is Valid \n");
				state.sCharState.sCharStateDetail.sCharStateHTB.hTarget = req->hTarget;
				state.sCharState.sCharStateDetail.sCharStateHTB.byStepCount = tbldat->bySetCount;
				state.sCharState.sCharStateDetail.sCharStateHTB.byCurStep = 1;
				state.sCharState.sCharStateDetail.sCharStateHTB.byResultCount = 0;
				state.sCharState.sCharStateDetail.sCharStateHTB.bIsSuccess = true;
				state.sCharState.sCharStateDetail.sCharStateHTB.HTBId = skillID;
		
				//Extract from Client Code
				int byResultCount = 0;
				for (int i = 0; i < tbldat->bySetCount; ++i)
				{
					if (tbldat->aHTBAction[i].skillTblidx != INVALID_TBLIDX)
					{
						state.sCharState.sCharStateDetail.sCharStateHTB.aHTBSkillResult[byResultCount].byStep = i;
						state.sCharState.sCharStateDetail.sCharStateHTB.aHTBSkillResult[byResultCount].sSkillResult.byAttackResult = BATTLE_ATTACK_RESULT_HIT;
						state.sCharState.sCharStateDetail.sCharStateHTB.aHTBSkillResult[byResultCount].sSkillResult.effectResult[0].Value1 = skillDataOriginal->SkillValue[0];
						state.sCharState.sCharStateDetail.sCharStateHTB.aHTBSkillResult[byResultCount].sSkillResult.effectResult[1].Value2 = skillDataOriginal->SkillValue[1];
						state.sCharState.sCharStateDetail.sCharStateHTB.aHTBSkillResult[byResultCount].sSkillResult.vShift.x = _player->GetVectorPosition().x;
						state.sCharState.sCharStateDetail.sCharStateHTB.aHTBSkillResult[byResultCount].sSkillResult.vShift.y = _player->GetVectorPosition().y - 15;
						state.sCharState.sCharStateDetail.sCharStateHTB.aHTBSkillResult[byResultCount].sSkillResult.vShift.z = _player->GetVectorPosition().z;
						state.sCharState.sCharStateDetail.sCharStateHTB.aHTBSkillResult[byResultCount].sSkillResult.byBlockedAction = 255;
				
						state.sCharState.sCharStateDetail.sCharStateHTB.byResultCount++;
						byResultCount++;
					}
				}
			}

			sWorld.SendToAll((char*)&state, sizeof(sGU_UPDATE_CHAR_STATE));
			break;
		}
		case Opcodes::UG_CHAR_MOVE_COLLISION:
		case Opcodes::UG_CHAR_MOVE_COLLISION_END:
		{			
			_player->SetFlying(false);			
			break;
		}
		case Opcodes::UG_CHAR_CHARGE:
		{
			sUG_CHAR_CHARGE* req = (sUG_CHAR_CHARGE*)packet.GetPacketBuffer();
			if (req->bCharge == true)
			{
				_player->SetState(CHARSTATE_CHARGING);
				_player->GetAttributesManager()->IsPowerUp = true;
				_player->GetAttributesManager()->RPTimer = GetTickCount();
				SendAvatarRPIncreaseStartNotify();
			}
			else
			{
				_player->SetState(CHARSTATE_STANDING);
				_player->GetAttributesManager()->IsPowerUp = false;
				SendAvatarRPIncreaseStopNotify();
			}			
			break;
		}
		//To Work
		case Opcodes::UG_CHAR_DASH_KEYBOARD:
		{			
			sLog.outError("UG_CHAR_DASH_KEYBOARD");
			SendCharDashKeyboard(packet);
			break;
		}
		case Opcodes::UG_CHAR_DASH_MOUSE:
		{			
			sLog.outError("UG_CHAR_DASH_MOUSE");
			SendCharDashMouse(packet);
			break;
		}
		case Opcodes::UG_CHAR_FALLING:
		{
			sLog.outError("UG_CHAR_FALLING");		
			break;
		}

#pragma	endregion	END_PACKET_IN_PROGRESS

#pragma region    SANGAWKU_PACKETS_IN_PROGRESS
		//Got delay at Load Items so it not work perfect
		case Opcodes::UG_MAIL_START_REQ:
		{
			sLog.outDebug("UG_MAIL_START_REQ");
			_player->StartMail(packet);
			_player->LoadMail(packet);
			sLog.outPacketFile(&packet);
			break;
		}

		case Opcodes::UG_MAIL_READ_REQ:
		{
			sLog.outDebug("UG_MAIL_READ_REQ");
			_player->ReadMail(packet);			
			break;
		}

		case Opcodes::UG_MAIL_LOAD_REQ:
		{
			sLog.outDebug("UG_MAIL_LOAD_REQ");
			_player->LoadMail(packet);			
			break;
		}

		case Opcodes::UG_MAIL_SEND_REQ:
		{
			sLog.outDebug("UG_MAIL_SEND_REQ");
			_player->SendMail(packet);			
			break;
		}

		case Opcodes::UG_MAIL_DEL_REQ:
		{
			sLog.outDebug("UG_MAIL_DEL_REQ");
			_player->DeletMail(packet);		
			break;
		}

		case Opcodes::UG_MAIL_ITEM_RECEIVE_REQ:
		{
			sLog.outDebug("UG_MAIL_ITEM_RECEIVE_REQ");			
			break;
		}
		case Opcodes::UG_MAIL_MULTI_DEL_REQ:
		{
			sLog.outDebug("UG_MAIL_MULTI_DEL_REQ");			
			break;
		}
		case Opcodes::UG_MAIL_RETURN_REQ:
		{
			sLog.outDebug("UG_MAIL_RETURN_REQ");			
			break;
		}

		case Opcodes::UG_MAIL_RELOAD_REQ:
		{
			sLog.outDebug("UG_MAIL_RELOAD_REQ");
			_player->ReloadMail(packet);			
			break;
		}
		case Opcodes::UG_MAIL_LOCK_REQ:
		{
			sLog.outDebug("UG_MAIL_LOCK_REQ");		
			break;
		}
		case Opcodes::UG_BANK_LOAD_REQ:
		{		
			sLog.outDebug("UG_BANK_LOAD_REQ");
			_player->SendBankLoad(packet);			
			_player->SendBankInfo(packet);			
			break;
		}
		case Opcodes::UG_BANK_START_REQ:
		{
			sLog.outDebug("UG_BANK_START_REQ");
			_player->SendBankStart(packet);
			break;
		}
		case Opcodes::UG_BANK_MOVE_REQ:
		{
			sLog.outDebug("UG_BANK_MOVE_REQ");
			//CClientSession::SendBankMoveReq(pPacket, app);
			break;
		}	
		case Opcodes::UG_BANK_MOVE_STACK_REQ:
		{
			sLog.outDebug("UG_BANK_MOVE_STACK_REQ");
			//CClientSession::SendBankStackReq(pPacket, app);
			break;
		}	
		case Opcodes::UG_BANK_END_REQ:
		{
			sLog.outDebug("UG_BANK_END_REQ");
			_player->SendBankEnd(packet);
			break;
		}
		case Opcodes::UG_BANK_ZENNY_REQ:
		{
			sLog.outDebug("UG_BANK_ZENNY_REQ");
			//CClientSession::SendBankMoneyReq(pPacket, app);
			break;
		}
		case Opcodes::UG_BANK_BUY_REQ:
		{
			sLog.outDebug("UG_BANK_BUY_REQ");
			//CClientSession::SendBankBuyReq(pPacket, app);
			
			break;
		}
		case Opcodes::UG_BANK_ITEM_DELETE_REQ:
		{
			sLog.outDebug("UG_BANK_ITEM_DELETE_REQ");
			//CClientSession::SendBankDeleteReq(pPacket, app);
			break;
		}
		case Opcodes::UG_TENKAICHIDAISIJYOU_SELL_REQ:
		{
			sLog.outError("UG_TENKAICHIDAISIJYOU_SELL_REQ");			
			_player->AucionHouseSell(packet);		
			break;
		}
		case Opcodes::UG_TENKAICHIDAISIJYOU_SELL_CANCEL_REQ:
		{
			sLog.outError("UG_TENKAICHIDAISIJYOU_SELL_CANCEL_REQ");
			_player->AucionHouseSellCancel(packet);		
			break;
		}
		case Opcodes::UG_TENKAICHIDAISIJYOU_BUY_REQ:
		{
			sLog.outError("UG_TENKAICHIDAISIJYOU_BUY_REQ");
			sLog.outPacketFile(&packet);			
			break;
		}
		case Opcodes::UG_TENKAICHIDAISIJYOU_LIST_REQ:
		{			
			sLog.outError("UG_TENKAICHIDAISIJYOU_LIST_REQ");		
			_player->AucionHouseList(packet);
			break;
		}

#pragma endregion END_OF_SANGAWKU_PACKETS

#pragma region    MARCO_RAFAEL_PACKETS_IN_PROGRESS
		case Opcodes::UG_QUICK_TELEPORT_LOAD_REQ:
		{
			sUG_QUICK_TELEPORT_LOAD_REQ* req = (sUG_QUICK_TELEPORT_LOAD_REQ *)packet.GetPacketBuffer();				

			sGU_QUICK_TELEPORT_LOAD_RES res;
			memset(&res, 0, sizeof(sGU_QUICK_TELEPORT_LOAD_RES));
			res.wOpCode = GU_QUICK_TELEPORT_LOAD_RES;
			res.wPacketSize = sizeof(sGU_QUICK_TELEPORT_LOAD_RES) - 2;
			sql::ResultSet* result = sDB.executes("SELECT * FROM QuickTeleporter WHERE CharacterID = '%d';", _player->GetCharacterID());
			if (result == NULL)
				return;
			if (result->rowsCount() <= 0)
			{	
				res.wResultCode = GAME_SUCCESS;
				SendPacket((char*)&res, sizeof(sGU_QUICK_TELEPORT_LOAD_RES));
				delete result;
				return;
			}
			res.BeginCount = result->rowsCount();
			int i = 0;
			while (true)
			{
				res.wResultCode = GAME_SUCCESS;
				res.TeleportInfo[i].TeleportID = result->getInt("TeleportID");
				res.TeleportInfo[i].WorldID = result->getInt("WorldID");
				res.TeleportInfo[i].Loc[0] = static_cast<float>(result->getDouble("Loc_x"));//result->getInt("Loc_x");
				res.TeleportInfo[i].Loc[1] = static_cast<float>(result->getDouble("Loc_y"));
				res.TeleportInfo[i].Loc[2] = static_cast<float>(result->getDouble("Loc_z"));
				res.TeleportInfo[i].Year = result->getInt("Year");
				res.TeleportInfo[i].Moch = result->getInt("Moch");
				res.TeleportInfo[i].Day = result->getInt("Day");
				res.TeleportInfo[i].Hour = result->getInt("Hour");
				res.TeleportInfo[i].Minute = result->getInt("Minute");
				res.TeleportInfo[i].Secound = result->getInt("Secound");
				res.TeleportInfo[i].unk2 = 0;
				res.TeleportInfo[i].MapTBLIDX = result->getInt("MapTBLIDX");
				i++;
				if (result->next())
					continue;
				else
					break;
			}
			delete result;
			SendPacket((char*)&res, sizeof(sGU_QUICK_TELEPORT_LOAD_RES));
			break;
		}
		case Opcodes::UG_QUICK_TELEPORT_UPDATE_REQ:
		{
			sUG_QUICK_TELEPORT_UPDATE_REQ* req = (sUG_QUICK_TELEPORT_UPDATE_REQ *)packet.GetPacketBuffer();
			
			sGU_QUICK_TELEPORT_UPDATE_RES res;

			res.wOpCode = GU_QUICK_TELEPORT_UPDATE_RES;
			res.wPacketSize = sizeof(sGU_QUICK_TELEPORT_UPDATE_RES) - 2;
			res.wResultCode = GAME_SUCCESS;
			res.TeleportInfo.TeleportID = req->TeleportID2;
			res.TeleportInfo.WorldID = _player->GetWorldID();
			res.TeleportInfo.Loc[0] = _player->GetVectorPosition().x;
			res.TeleportInfo.Loc[1] = _player->GetVectorPosition().y;
			res.TeleportInfo.Loc[2] = _player->GetVectorPosition().z;

			std::time_t t = std::time(0);
			std::tm* now = std::localtime(&t);
			res.TeleportInfo.Year = now->tm_year + 1900;
			res.TeleportInfo.Moch = now->tm_mon + 1;
			res.TeleportInfo.Day = now->tm_mday;
			res.TeleportInfo.Hour = now->tm_hour;
			res.TeleportInfo.Minute = now->tm_min;
			res.TeleportInfo.Secound = now->tm_sec;

			res.TeleportInfo.unk2 = 0;
			res.TeleportInfo.MapTBLIDX = _player->GetWorldTableID();
			//Need Change it bacause if i isave 2x same slot it do 2 insert for the same ID
			sDB.SaveQuickTeleport(_player->charid, res.TeleportInfo.TeleportID, _player->GetWorldID(), res.TeleportInfo.Loc[0], res.TeleportInfo.Loc[1], res.TeleportInfo.Loc[2], res.TeleportInfo.Year, res.TeleportInfo.Moch, res.TeleportInfo.Day, res.TeleportInfo.Hour, res.TeleportInfo.Minute, res.TeleportInfo.Secound, res.TeleportInfo.MapTBLIDX);
			SendPacket((char*)&res, sizeof(sGU_QUICK_TELEPORT_UPDATE_RES));

			break;
		}
		case Opcodes::UG_QUICK_TELEPORT_DEL_REQ:
		{
			sUG_QUICK_TELEPORT_DEL_REQ* req = (sUG_QUICK_TELEPORT_DEL_REQ *)packet.GetPacketBuffer();
			
			sGU_QUICK_TELEPORT_DEL_RES res;

			res.wOpCode = GU_QUICK_TELEPORT_DEL_RES;
			res.wPacketSize = sizeof(sGU_QUICK_TELEPORT_DEL_RES) - 2;
			res.wResultCode = GAME_SUCCESS;
			res.TeleportInfo.TeleportID = req->TeleportID2;
			
			SendPacket((char*)&res, sizeof(sGU_QUICK_TELEPORT_DEL_RES));
			sql::ResultSet* result1 = sDB.executes("DELETE FROM `QuickTeleporter` WHERE `CharacterID` = '%d' AND TeleportID = '%d';", _player->charid, req->TeleportID2);
			if (result1 != NULL)
				delete result1;

			break;
		}
		case Opcodes::UG_QUICK_TELEPORT_USE_REQ:
		{
			sUG_QUICK_TELEPORT_USE_REQ* req = (sUG_QUICK_TELEPORT_USE_REQ *)packet.GetPacketBuffer();
			sGU_QUICK_TELEPORT_USE_RES res;

			res.wOpCode = GU_QUICK_TELEPORT_USE_RES;
			res.wPacketSize = sizeof(sGU_QUICK_TELEPORT_USE_RES) - 2;	
			res.TeleportID = req->TeleportID2;
			sql::ResultSet* result = sDB.executes("SELECT * FROM QuickTeleporter WHERE CharacterID = '%d' AND TeleportID = '%d';", _player->charid, req->TeleportID2);
			if (result == NULL)
				return;
			if (result->rowsCount() <= 0)
			{
				res.wResultCode = QUERY_FAIL;
				SendPacket((char*)&res, sizeof(sGU_QUICK_TELEPORT_USE_RES));
				delete result;
				return;
			}			
			res.wResultCode = GAME_SUCCESS;
			SendPacket((char*)&res, sizeof(sGU_QUICK_TELEPORT_USE_RES));

			_player->SetIsReady(false);

			sGU_CHAR_TELEPORT_RES Teleport;
			memset(&Teleport, 0, sizeof(sGU_CHAR_TELEPORT_RES));
			Teleport.wOpCode = GU_CHAR_TELEPORT_RES;
			Teleport.wPacketSize = sizeof(sGU_CHAR_TELEPORT_RES) - 2;
			Teleport.wResultCode = GAME_SUCCESS;
			Teleport.vNewLoc.x = static_cast<float>(result->getDouble("Loc_x"));
			Teleport.vNewLoc.y = static_cast<float>(result->getDouble("Loc_y"));
			Teleport.vNewLoc.z = static_cast<float>(result->getDouble("Loc_z"));
			Teleport.vNewDir.x = _player->GetVectorOriantation().x;
			Teleport.vNewDir.y = _player->GetVectorOriantation().y;
			Teleport.vNewDir.z = _player->GetVectorOriantation().z;
			Teleport.unk = INVALID_TBLIDX;
			Teleport.bIsToMoveAnotherServer = false;
			
			_player->Relocate(Teleport.vNewLoc.x, Teleport.vNewLoc.y, Teleport.vNewLoc.z, Teleport.vNewDir.x, Teleport.vNewDir.y, Teleport.vNewDir.z);
			_player->SetWorldID(1);
			_player->SetWorldTableID(1);
			_player->GetState()->sCharStateDetail.sCharStateTeleporting.byTeleportType = eTELEPORT_TYPE::TELEPORT_TYPE_TELEPOPO;
			_player->SetState(eCHARSTATE::CHARSTATE_TELEPORTING);			
			SendPacket((char*)&Teleport, sizeof(sGU_CHAR_TELEPORT_RES));
			/*Map* map = _player->GetMap();
			map->Remove(_player, false);
			_player->ClearListAndReference();*/
			break;
		}
		case Opcodes::UG_CHAR_TELEPORT_REQ:
		{
			sLog.outDetail("----------------UG_CHAR_TELEPORT_REQ---------------");
			SendCharTeleportRes(packet);
			break;
		}
		case Opcodes::UG_PARTY_CREATE_REQ: // Create party with name you want
		{
			sUG_PARTY_CREATE_REQ *req = (sUG_PARTY_CREATE_REQ*)packet.GetPacketBuffer();

			sGU_PARTY_CREATE_RES res;

			memset(&res, 0, sizeof(sGU_PARTY_CREATE_RES));
			res.wOpCode = GU_PARTY_CREATE_RES;
			res.wPacketSize = sizeof(sGU_PARTY_CREATE_RES) - 2;
			res.wResultCode = GAME_SUCCESS;
			wcscpy_s(res.wszPartyName, 16 + 1, req->wszPartyName);

			SendPacket((char*)&res, sizeof(sGU_PARTY_CREATE_RES));

			break;
		}
		case Opcodes::UG_PARTY_LEAVE_REQ: // Remove the party
		{
			sUG_PARTY_LEAVE_REQ* req = (sUG_PARTY_LEAVE_REQ *)packet.GetPacketBuffer();

			sGU_PARTY_LEAVE_RES res;
			res.wOpCode = GU_PARTY_LEAVE_RES;
			res.wPacketSize = sizeof(sGU_PARTY_LEAVE_RES) - 2;
			res.wResultCode = GAME_SUCCESS;
			sLog.outError("UG_PARTY_LEAVE_REQ");
			SendPacket((char*)&res, sizeof(sGU_PARTY_LEAVE_RES)); 

			break;
		}
		case Opcodes::UG_PARTY_INVITE_REQ: 
		{
			sUG_PARTY_INVITE_REQ *req = (sUG_PARTY_INVITE_REQ*)packet.GetPacketBuffer();
			Player* PlayerInfo = static_cast<Player*>(_player->GetFromList(req->hTarget));
			if (PlayerInfo != NULL)
			{
				sGU_PARTY_INVITE_RES res;
				memset(&res, 0, sizeof(sGU_PARTY_INVITE_RES));
				res.wOpCode = GU_PARTY_INVITE_RES;
				res.wPacketSize = sizeof(sGU_PARTY_INVITE_RES) - 2;
				res.wResultCode = GAME_SUCCESS;
				wcscpy_s(res.wszTargetName, 16 + 1, PlayerInfo->GetPcProfile()->awchName);
				SendPacket((char*)&res, sizeof(sGU_PARTY_INVITE_RES));

				sGU_PARTY_INVITE_NFY res1;
				memset(&res1, 0, sizeof(sGU_PARTY_INVITE_NFY));
				res1.wOpCode = GU_PARTY_INVITE_NFY;
				res1.wPacketSize = sizeof(sGU_PARTY_INVITE_NFY) - 2;				
				wcscpy_s(res1.wszInvitorPcName, 16 + 1, _player->GetPcProfile()->awchName);				
				PlayerInfo->SendPacket((char*)&res1, sizeof(sGU_PARTY_INVITE_NFY));
				PlayerInfo->GetAttributesManager()->PartyLeader = _player->GetHandle();

				//sLog.outError("UG_PARTY_INVITE_REQ");
			}
			break;
		}
		case Opcodes::UG_PARTY_RESPONSE_INVITATION:
		{
			sUG_PARTY_RESPONSE_INVITATION *req = (sUG_PARTY_RESPONSE_INVITATION*)packet.GetPacketBuffer();
			Player* PlayerInfo = static_cast<Player*>(_player->GetFromList(_player->GetAttributesManager()->PartyLeader));
			if (PlayerInfo != NULL)
			{
				if (req->byResponse == eINVITATION_RESPONSE::INVITATION_RESPONSE_ACCEPT)
				{
					sGU_PARTY_RESPONSE_INVITATION_RES res;
					memset(&res, 0, sizeof(sGU_PARTY_RESPONSE_INVITATION_RES));
					res.wOpCode = GU_PARTY_RESPONSE_INVITATION_RES;
					res.wPacketSize = sizeof(sGU_PARTY_RESPONSE_INVITATION_RES) - 2;
					res.wResultCode = GAME_SUCCESS;
					SendPacket((char*)&res, sizeof(sGU_PARTY_RESPONSE_INVITATION_RES));

					sGU_PARTY_CREATE_RES res1;
					memset(&res1, 0, sizeof(sGU_PARTY_CREATE_RES));
					res1.wOpCode = GU_PARTY_CREATE_RES;
					res1.wPacketSize = sizeof(sGU_PARTY_CREATE_RES) - 2;
					res1.wResultCode = GAME_SUCCESS;
					wcscpy_s(res1.wszPartyName, 16 + 1, L"Unnamed");
					PlayerInfo->SendPacket((char*)&res1, sizeof(sGU_PARTY_CREATE_RES));

					sGU_PARTY_MEMBER_JOINED_NFY res2;
					//memset(&res2, 0, sizeof(sGU_PARTY_MEMBER_JOINED_NFY));
					res2.wOpCode = GU_PARTY_MEMBER_JOINED_NFY;
					res2.wPacketSize = sizeof(sGU_PARTY_MEMBER_JOINED_NFY) - 2;

					res2.memberInfo.hHandle = _player->GetHandle();
					wcscpy_s(res2.memberInfo.awchMemberName, 16 + 1, _player->GetPcProfile()->awchName);
					res2.memberInfo.byRace = _player->GetAttributesManager()->PlayerRaceID;
					res2.memberInfo.byClass = _player->GetAttributesManager()->PlayerClassID;
					res2.memberInfo.byLevel = _player->GetPcProfile()->byLevel;
					res2.memberInfo.wCurLP = _player->GetPcProfile()->dwCurLP;
					res2.memberInfo.wMaxLP = _player->GetPcProfile()->avatarAttribute.wLastMaxLP;
					res2.memberInfo.wCurEP = _player->GetPcProfile()->wCurEP;
					res2.memberInfo.wMaxEP = _player->GetPcProfile()->avatarAttribute.wLastMaxEP;
					res2.memberInfo.dwZenny = _player->GetPcProfile()->dwZenny;
					res2.memberInfo.worldId = _player->GetWorldID();
					res2.memberInfo.worldTblidx = _player->GetWorldID();
					res2.memberInfo.vCurLoc = _player->GetVectorPosition();
					res2.memberInfo.IsOnline = 0;
					PlayerInfo->SendPacket((char*)&res2, sizeof(sGU_PARTY_MEMBER_JOINED_NFY));
					//Send to Others Players in party

					sGU_PARTY_INFO res3;
					memset(&res3, 0, sizeof(sGU_PARTY_INFO));
					res3.wOpCode = GU_PARTY_INFO;
					res3.wPacketSize = sizeof(sGU_PARTY_INFO) - 2;
					wcscpy_s(res3.awchPartyName, 16 + 1, L"Unnamed");
					res3.PartyID = 1;
					res3.hLeader = PlayerInfo->GetHandle();
					res3.byItemLootingMethod = 1;
					res3.byZennyLootingMethod = 1;
					res3.unk = 2;
					res3.byMemberInfoCount = 1;
					res3.memberInfo[0].hHandle = PlayerInfo->GetHandle();
					wcscpy_s(res3.memberInfo[0].awchMemberName, 16 + 1, PlayerInfo->GetPcProfile()->awchName);
					res3.memberInfo[0].byRace = PlayerInfo->GetAttributesManager()->PlayerRaceID;
					res3.memberInfo[0].byClass = PlayerInfo->GetAttributesManager()->PlayerClassID;
					res3.memberInfo[0].byLevel = PlayerInfo->GetPcProfile()->byLevel;
					res3.memberInfo[0].wCurLP = PlayerInfo->GetPcProfile()->dwCurLP;
					res3.memberInfo[0].wMaxLP = PlayerInfo->GetPcProfile()->avatarAttribute.wLastMaxLP;
					res3.memberInfo[0].wCurEP = PlayerInfo->GetPcProfile()->wCurEP;
					res3.memberInfo[0].wMaxEP = PlayerInfo->GetPcProfile()->avatarAttribute.wLastMaxEP;
					res3.memberInfo[0].dwZenny = PlayerInfo->GetPcProfile()->dwZenny;
					res3.memberInfo[0].worldId = PlayerInfo->GetWorldID();
					res3.memberInfo[0].worldTblidx = PlayerInfo->GetWorldID();
					res3.memberInfo[0].vCurLoc = PlayerInfo->GetVectorPosition();
					res3.memberInfo[0].IsOnline = 0;
					SendPacket((char*)&res3, sizeof(sGU_PARTY_INFO));
					// so shit :o

				}
			}
			break;
		}
		case Opcodes::UG_TRADE_START_REQ:
		{
			//sLog.outError("UG_TRADE_START_REQ");
			sUG_TRADE_START_REQ* req = (sUG_TRADE_START_REQ *)packet.GetPacketBuffer();				
			// Get Target session 
			Player* PlayerInfo = static_cast<Player*>(_player->GetFromList(req->hTarget));
			if (PlayerInfo != NULL)
			{			
			sGU_TRADE_OK_REQ res;

			res.wOpCode = GU_TRADE_OK_REQ;
			res.wPacketSize = sizeof(sGU_TRADE_OK_REQ) - 2;
			res.handle = _player->GetHandle();	

			PlayerInfo->SendPacket((char*)&res, sizeof(sGU_TRADE_OK_REQ));				
			}
			break;
		}
		case Opcodes::UG_TRADE_OK_RES:
		{
			sUG_TRADE_OK_RES* req = (sUG_TRADE_OK_RES *)packet.GetPacketBuffer();
			sGU_TRADE_START_NFY res;
			sGU_TRADE_START_RES res1;
			Player* PlayerInfo = static_cast<Player*>(_player->GetFromList(req->handle));
			if (req->byOK == true && PlayerInfo != NULL)
			{
				res.wOpCode = GU_TRADE_START_NFY;
				res.wPacketSize = sizeof(sGU_TRADE_START_NFY) - 2;
				res.handle = req->handle;
				res.hTarget = _player->GetHandle();
				res.byEmptyInven = 12;
				res.wResultCode = GAME_SUCCESS;

				res1.wOpCode = GU_TRADE_START_RES;
				res1.wPacketSize = sizeof(sGU_TRADE_START_RES) - 2;
				res1.handle = _player->GetHandle();
				res1.hTarget = req->handle;
				res1.byEmptyInven = 12;
				res1.wResultCode = GAME_SUCCESS;

				SendPacket((char*)&res1, sizeof(sGU_TRADE_START_RES));
				PlayerInfo->SendPacket((char*)&res, sizeof(sGU_TRADE_START_NFY));				
			}
			else if(req->byOK == false && PlayerInfo != NULL)
			{
				res1.wOpCode = GU_TRADE_START_RES;
				res1.wPacketSize = sizeof(sGU_TRADE_START_RES) - 2;
				res1.handle = _player->GetHandle();
				res1.hTarget = req->handle;
				res1.byEmptyInven = 12;
				res1.wResultCode = GAME_TRADE_DENY;
				SendPacket((char*)&res1, sizeof(sGU_TRADE_START_RES));
				PlayerInfo->SendPacket((char*)&res1, sizeof(sGU_TRADE_START_RES));
			}
			break;
		}
		case Opcodes::UG_TRADE_CANCEL_REQ:
		{
			sUG_TRADE_CANCEL_REQ* req = (sUG_TRADE_CANCEL_REQ *)packet.GetPacketBuffer();
			sGU_TRADE_CANCEL_RES res;
			sGU_TRADE_CANCEL_NFY res1;
			Player* PlayerInfo = static_cast<Player*>(_player->GetFromList(req->hTarget));
			if (PlayerInfo != NULL)
			{
				res.wOpCode = GU_TRADE_CANCEL_RES;
				res.wPacketSize = sizeof(sGU_TRADE_CANCEL_RES) - 2;
				res.hTarget = _player->GetHandle();
				res.wResultCode = GAME_SUCCESS;

				res1.wOpCode = GU_TRADE_CANCEL_NFY;
				res1.wPacketSize = sizeof(sGU_TRADE_CANCEL_NFY) - 2;
				res1.hTarget = req->hTarget;
				res1.wResultCode = GAME_SUCCESS;

				SendPacket((char*)&res, sizeof(sGU_TRADE_CANCEL_RES));
				PlayerInfo->SendPacket((char*)&res1, sizeof(sGU_TRADE_CANCEL_NFY));
			}
			break;
		}
		case Opcodes::UG_TRADE_DENY_REQ:
		{
			sUG_TRADE_DENY_REQ* req = (sUG_TRADE_DENY_REQ *)packet.GetPacketBuffer();
			sGU_TRADE_DENY_RES res;
			
			res.wOpCode = GU_TRADE_DENY_RES;
			res.wPacketSize = sizeof(sGU_TRADE_DENY_RES) - 2;
			res.bIsDeny = req->bIsDeny;
			res.wResultCode = GAME_SUCCESS;

			SendPacket((char*)&res, sizeof(sGU_TRADE_DENY_RES));

			break;
		}
		//Need Change trade Bacause i not know how create one List...
		case Opcodes::UG_TRADE_ADD_REQ:
		{
			sUG_TRADE_ADD_REQ* req = (sUG_TRADE_ADD_REQ *)packet.GetPacketBuffer();
			sGU_TRADE_ADD_RES res;
			sGU_TRADE_ADD_NFY res1;
			memset(&res1, 0, sizeof(sGU_TRADE_ADD_NFY));
			sITEM_PROFILE *Item = NULL;
			Item = _player->inventoryManager.GetItemByHandle(req->hItem);
			Player* PlayerInfo = static_cast<Player*>(_player->GetFromList(req->hTarget));
			if (PlayerInfo != NULL && Item != NULL && PlayerInfo->GetAttributesManager()->tradecount <= 12)
			{
				res.wOpCode = GU_TRADE_ADD_RES;
				res.wPacketSize = sizeof(sGU_TRADE_ADD_RES) - 2;
				res.byCount = req->byCount;
				res.hItem = req->hItem;
				res.wResultCode = GAME_SUCCESS;

				res1.wOpCode = GU_TRADE_ADD_NFY;
				res1.wPacketSize = sizeof(sGU_TRADE_ADD_NFY) - 2;				
				res1.hItem = req->hItem;	
				res1.byCount = req->byCount;
				//res1.sItem.handle =  Item->handle;
				res1.sItem.itemId = 0;
				res1.sItem.itemNo = Item->tblidx;
				res1.sItem.charId = _player->charid;
				res1.sItem.byStackcount = req->byCount;
				res1.sItem.byRank = Item->byRank;
				res1.sItem.byCurrentDurability = Item->byCurDur;
				res1.sItem.byGrade = Item->byGrade;
				res1.sItem.byPlace = Item->byPlace;
				res1.sItem.byPosition = Item->byPos;
				res1.sItem.bNeedToIdentify = false;					
				PlayerInfo->GetAttributesManager()->Tradeinvent[PlayerInfo->GetAttributesManager()->tradecount] = res1.sItem;
				PlayerInfo->GetAttributesManager()->tradecount = PlayerInfo->GetAttributesManager()->tradecount + 1;

				
				SendPacket((char*)&res, sizeof(sGU_TRADE_ADD_RES));				
				PlayerInfo->SendPacket((char*)&res1, sizeof(sGU_TRADE_ADD_NFY));
			}			

			break;
		}
		//Need Change trade Bacause i not know how create one List...
		case Opcodes::UG_TRADE_END_REQ:
		{
			sUG_TRADE_END_REQ* req = (sUG_TRADE_END_REQ *)packet.GetPacketBuffer();
			sGU_TRADE_END_RES res;
			sGU_TRADE_END_NFY res2;
			Player* PlayerInfo = static_cast<Player*>(_player->GetFromList(req->hTarget));
			if (req->bIsSet == true && PlayerInfo != NULL)
			{
				_player->GetAttributesManager()->PlayerTradeOK = true;
				res.wOpCode = GU_TRADE_END_RES;
				res.wPacketSize = sizeof(sGU_TRADE_END_RES) - 2;
				res.hTarget = _player->GetHandle();
				res.dwPacketCount = req->dwPacketCount;
				res.bIsSet = true;
				res.wResultCode = GAME_SUCCESS;

				res2.wOpCode = GU_TRADE_END_NFY;
				res2.wPacketSize = sizeof(sGU_TRADE_END_NFY) - 2;
				res2.hTarget = PlayerInfo->GetHandle();
				res2.bIsSet = true;
				res2.wResultCode = GAME_SUCCESS;			
				//printf("trade %d \n", PlayerInfo->GetAttributesManager()->PlayerTradeOK);
				if ( PlayerInfo->GetAttributesManager()->PlayerTradeOK == true)
				{
					// move items
					for (int i = 0; i <= _player->GetAttributesManager()->tradecount; i++)
					{
						//printf("Player Info Item %d \n", PlayerInfo->GetAttributesManager()->Tradeinvent[i].itemNo);
						//printf("_player Item %d \n", _player->GetAttributesManager()->Tradeinvent[i].itemNo);
						sITEM_PROFILE createdItem;
						WORD result = _player->GetInventoryManager()->PerformShopBuy(_player->GetAttributesManager()->Tradeinvent[i].itemNo, _player->GetAttributesManager()->Tradeinvent[i].byStackcount, createdItem);
						if (result == GAME_SUCCESS && createdItem.tblidx != INVALID_TBLIDX)
						{
							//sLog.outDetail("Item Created\n");
							sGU_ITEM_CREATE create;

							create.wOpCode = GU_ITEM_CREATE;
							create.wPacketSize = sizeof(sGU_ITEM_CREATE) - 2;

							create.bIsNew = true;
							create.sItemData.handle = create.handle = createdItem.handle;
							create.sItemData.unk = 0;
							//create.sItemData.unknown1 = 0;
							//create.sItemData.unknown2 = 0;

							for (int i = 0; i < 6; i++)
							{
								create.sItemData.aitemEffect[i].dwValue = createdItem.aitemEffect[i].dwValue;
								create.sItemData.aitemEffect[i].wType = createdItem.aitemEffect[i].wType;

							}
							for (int i = 0; i < 2; i++)
							{
								create.sItemData.aitemExtraEffect[i].dwValue = createdItem.aitemExtraEffect[i].dwValue;
								create.sItemData.aitemExtraEffect[i].wType = createdItem.aitemExtraEffect[i].wType;
							}
														
							create.sItemData.awchMaker[i] = createdItem.awchMaker[i];

							create.sItemData.bNeedToIdentify = false;
							create.sItemData.byBattleAttribute = createdItem.byBattleAttribute;
							create.sItemData.byCurrentDurability = createdItem.byCurDur;
							create.sItemData.byDurationType = createdItem.byDurationType;
							create.sItemData.byGrade = createdItem.byGrade;
							create.sItemData.byPlace = createdItem.byPlace;
							create.sItemData.byPosition = createdItem.byPos;
							create.sItemData.byRank = createdItem.byRank;
							create.sItemData.byRestrictType = createdItem.byRestrictType;
							create.sItemData.byStackcount = createdItem.byStackcount;
							create.sItemData.charId = _player->GetCharacterID();
							create.sItemData.itemId = createdItem.handle;
							create.sItemData.itemNo = createdItem.tblidx;

							create.sItemData.aOptionTblidx = INVALID_TBLIDX;
							create.sItemData.aOptionTblidx1 = INVALID_TBLIDX;

							_player->SendPacket((char*)&create, sizeof(sGU_ITEM_CREATE));
							sITEM_PROFILE*itm = PlayerInfo->GetInventoryManager()->GetItemAtPlaceAndPost(_player->GetAttributesManager()->Tradeinvent[i].byPlace, _player->GetAttributesManager()->Tradeinvent[i].byPosition);
							if (itm != NULL)
							{
								sGU_ITEM_DELETE itmDelete;
								itmDelete.wOpCode = GU_ITEM_DELETE;
								itmDelete.wPacketSize = sizeof(sGU_ITEM_DELETE) - 2;

								itmDelete.bySrcPlace = _player->GetAttributesManager()->Tradeinvent[i].byPlace;
								itmDelete.bySrcPos = _player->GetAttributesManager()->Tradeinvent[i].byPosition;
								//itmDelete.hSrcItem = _player->GetAttributesManager()->Tradeinvent[i].handle;
								PlayerInfo->SendPacket((char*)&itmDelete, sizeof(sGU_ITEM_DELETE));
								itm->byPlace = INVALID_TBLIDX;
								itm->byPos = INVALID_TBLIDX;
								itm->tblidx = INVALID_TBLIDX;
							}
						}						
						
					}
					for (int i = 0; i <= PlayerInfo->GetAttributesManager()->tradecount; i++)
					{
					//	printf("Player Info Item %d \n", PlayerInfo->GetAttributesManager()->Tradeinvent[i].itemNo);
					//	printf("_player Item %d \n", _player->GetAttributesManager()->Tradeinvent[i].itemNo);
						sITEM_PROFILE createdItem1;
						WORD result1 = PlayerInfo->GetInventoryManager()->PerformShopBuy(PlayerInfo->GetAttributesManager()->Tradeinvent[i].itemNo, PlayerInfo->GetAttributesManager()->Tradeinvent[i].byStackcount, createdItem1);
						if (result1 == GAME_SUCCESS && createdItem1.tblidx != INVALID_TBLIDX)
						{
							//sLog.outDetail("Item Created\n");
							sGU_ITEM_CREATE create;

							create.wOpCode = GU_ITEM_CREATE;
							create.wPacketSize = sizeof(sGU_ITEM_CREATE) - 2;

							create.bIsNew = true;
							create.sItemData.handle = create.handle = createdItem1.handle;
							create.sItemData.unk = 0;
							//create.sItemData.unknown1 = 0;
							//create.sItemData.unknown2 = 0;

							for (int i = 0; i < 6; i++)
							{
								create.sItemData.aitemEffect[i].dwValue = createdItem1.aitemEffect[i].dwValue;
								create.sItemData.aitemEffect[i].wType = createdItem1.aitemEffect[i].wType;

							}
							for (int i = 0; i < 2; i++)
							{
								create.sItemData.aitemExtraEffect[i].dwValue = createdItem1.aitemExtraEffect[i].dwValue;
								create.sItemData.aitemExtraEffect[i].wType = createdItem1.aitemExtraEffect[i].wType;
							}
							for (int i = 0; i < 17; i++)
								create.sItemData.awchMaker[i] = createdItem1.awchMaker[i];

							create.sItemData.bNeedToIdentify = false;
							create.sItemData.byBattleAttribute = createdItem1.byBattleAttribute;
							create.sItemData.byCurrentDurability = createdItem1.byCurDur;
							create.sItemData.byDurationType = createdItem1.byDurationType;
							create.sItemData.byGrade = createdItem1.byGrade;
							create.sItemData.byPlace = createdItem1.byPlace;
							create.sItemData.byPosition = createdItem1.byPos;
							create.sItemData.byRank = createdItem1.byRank;
							create.sItemData.byRestrictType = createdItem1.byRestrictType;
							create.sItemData.byStackcount = createdItem1.byStackcount;
							create.sItemData.charId = PlayerInfo->GetCharacterID();
							create.sItemData.itemId = createdItem1.handle;
							create.sItemData.itemNo = createdItem1.tblidx;

							create.sItemData.aOptionTblidx = INVALID_TBLIDX;
							create.sItemData.aOptionTblidx1 = INVALID_TBLIDX;

							PlayerInfo->SendPacket((char*)&create, sizeof(sGU_ITEM_CREATE));
							sITEM_PROFILE*itm = _player->GetInventoryManager()->GetItemAtPlaceAndPost(PlayerInfo->GetAttributesManager()->Tradeinvent[i].byPlace, PlayerInfo->GetAttributesManager()->Tradeinvent[i].byPosition);
							if (itm != NULL)
							{
								sGU_ITEM_DELETE itmDelete;
								itmDelete.wOpCode = GU_ITEM_DELETE;
								itmDelete.wPacketSize = sizeof(sGU_ITEM_DELETE) - 2;

								itmDelete.bySrcPlace = PlayerInfo->GetAttributesManager()->Tradeinvent[i].byPlace;
								itmDelete.bySrcPos = PlayerInfo->GetAttributesManager()->Tradeinvent[i].byPosition;
								//itmDelete.hSrcItem = PlayerInfo->GetAttributesManager()->Tradeinvent[i].handle;
								SendPacket((char*)&itmDelete, sizeof(sGU_ITEM_DELETE));
								itm->byPlace = INVALID_TBLIDX;
								itm->byPos = INVALID_TBLIDX;
								itm->tblidx = INVALID_TBLIDX;
							}
						}
						

					}
					for (int j = 0; j < 13; j++)
					{
						_player->GetAttributesManager()->Tradeinvent[j].itemNo = INVALID_TBLIDX;
						PlayerInfo->GetAttributesManager()->Tradeinvent[j].itemNo = INVALID_TBLIDX;						
					}					
					_player->GetAttributesManager()->tradecount = 0;
					_player->GetAttributesManager()->PlayerTradeOK = false;
					PlayerInfo->GetAttributesManager()->PlayerTradeOK = false;
				}
				SendPacket((char*)&res, sizeof(sGU_TRADE_END_RES));
				PlayerInfo->SendPacket((char*)&res2, sizeof(sGU_TRADE_END_NFY));
			}
			break;
		}
		case Opcodes::UG_FREEBATTLE_CHALLENGE_REQ:
		{
			sUG_FREEBATTLE_CHALLENGE_REQ* req = (sUG_FREEBATTLE_CHALLENGE_REQ *)packet.GetPacketBuffer();
			sGU_FREEBATTLE_CHALLENGE_RES res;
			sGU_FREEBATTLE_ACCEPT_REQ res2;
			Player* PlayerInfo = static_cast<Player*>(_player->GetFromList(req->hTarget));
			if (PlayerInfo != NULL)
			{
				if (PlayerInfo->GetAttributesManager()->PlayerInFreeBatle == false)
				{
					res.wOpCode = GU_FREEBATTLE_CHALLENGE_RES;
					res.wPacketSize = sizeof(sGU_FREEBATTLE_CHALLENGE_RES) - 2;
					res.hTarget = req->hTarget;
					res.wResultCode = GAME_SUCCESS;

					res2.wOpCode = GU_FREEBATTLE_ACCEPT_REQ;
					res2.wPacketSize = sizeof(sGU_FREEBATTLE_ACCEPT_REQ) - 2;
					res2.hChallenger = _player->GetHandle();


					PlayerInfo->SendPacket((char*)&res2, sizeof(sGU_FREEBATTLE_ACCEPT_REQ));
					//save the handle of chelenger to send on free balte acept client not send me it "case not do it batle just start for one player"
					PlayerInfo->GetAttributesManager()->FreeBatleChellenger = _player->GetHandle();
					_player->GetAttributesManager()->FreeBatleChellenger = req->hTarget;
				}
				else
				{
					res.wOpCode = GU_FREEBATTLE_CHALLENGE_RES;
					res.wPacketSize = sizeof(sGU_FREEBATTLE_CHALLENGE_RES) - 2;
					res.hTarget = req->hTarget;
					res.wResultCode = GAME_FREEBATTLE_TARGET_ALREADY_HAS_MATCH;
					SendPacket((char*)&res, sizeof(sGU_FREEBATTLE_CHALLENGE_RES));
				}
			}
			break;
		}
		case Opcodes::UG_FREEBATTLE_ACCEPT_RES:
		{
			//sLog.outPacketFile(&packet);
			sUG_FREEBATTLE_ACCEPT_RES* req = (sUG_FREEBATTLE_ACCEPT_RES *)packet.GetPacketBuffer();
			sGU_FREEBATTLE_START_NFY res;
			sGU_FREEBATTLE_START_NFY res2;
			//Get chellenger Info 
			Player* PlayerInfo = static_cast<Player*>(_player->GetFromList(_player->GetAttributesManager()->FreeBatleChellenger));
			//bug Know when player log out other player still in duel
			//need Chek if player leave batle area into an timer 
			if (req->byAccept == true && PlayerInfo != NULL)
			{
				_player->GetAttributesManager()->PlayerInFreeBatle = true;
				PlayerInfo->GetAttributesManager()->PlayerInFreeBatle = true;

				res.wOpCode = GU_FREEBATTLE_START_NFY;
				res.wPacketSize = sizeof(sGU_FREEBATTLE_START_NFY) - 2;
				res.hTarget = PlayerInfo->GetHandle();
				res.vRefreeLoc = _player->GetVectorPosition();
				res.vRefreeLoc.x += 5;
				res.vRefreeLoc.z -= 2;

				res2.wOpCode = GU_FREEBATTLE_START_NFY;
				res2.wPacketSize = sizeof(sGU_FREEBATTLE_START_NFY) - 2;
				res2.hTarget = _player->GetHandle();
				res2.vRefreeLoc = PlayerInfo->GetVectorPosition();
				res2.vRefreeLoc.x += 5;
				res2.vRefreeLoc.z -= 2;

				_player->GetAttributesManager()->vRefreeLoc = res.vRefreeLoc;
				PlayerInfo->GetAttributesManager()->vRefreeLoc = res2.vRefreeLoc;
				SendPacket((char*)&res, sizeof(sGU_FREEBATTLE_START_NFY));
				PlayerInfo->SendPacket((char*)&res2, sizeof(sGU_FREEBATTLE_START_NFY));
				//_player->SendToPlayerList((char*)&res, sizeof(sGU_FREEBATTLE_START_NFY));
			}
			else if (req->byAccept == false && PlayerInfo != NULL)
			{
				sGU_FREEBATTLE_CANCEL_NFY cancel;

				_player->GetAttributesManager()->PlayerInFreeBatle = false;
				PlayerInfo->GetAttributesManager()->PlayerInFreeBatle = false;

				cancel.wOpCode = GU_FREEBATTLE_CANCEL_NFY;
				cancel.wPacketSize = sizeof(sGU_FREEBATTLE_CANCEL_NFY) - 2;
				cancel.wResultCode = GAME_FREEBATTLE_CHALLENGE_ACCEPT_DENIED;
			
				PlayerInfo->SendPacket((char*)&cancel, sizeof(sGU_FREEBATTLE_CANCEL_NFY));
			}
			break;
		}
		case Opcodes::UG_ITEM_DISASSEMBLE_REQ:
		{
			//sLog.outError("UG_ITEM_DISASSEMBLE_REQ");
			sUG_ITEM_DISASSEMBLE_REQ* req = (sUG_ITEM_DISASSEMBLE_REQ *)packet.GetPacketBuffer();
			sITEM_PROFILE *Item = NULL;
			sITEM_TBLDAT *ItemData = NULL;
			sLAND_MARK_TBLDAT *DisambleData = NULL;
			Item = _player->inventoryManager.GetItemAtPlaceAndPost(req->Place, req->Pos);
			if (Item != NULL)
			{
				//Get Item Data
				if ((ItemData = (sITEM_TBLDAT*)sTBM.GetItemTable()->FindData(Item->tblidx)) == NULL)
				{
					ItemData = (sCASHITEM_TBLDAT*)sTBM.GetCashItemTable()->FindData(Item->tblidx);
				}
				if (ItemData != NULL)
				{
					//Delet the Dissamble Item 
					sGU_ITEM_DELETE itmDelete;
					itmDelete.wOpCode = GU_ITEM_DELETE;
					itmDelete.wPacketSize = sizeof(sGU_ITEM_DELETE) - 2;
					itmDelete.bySrcPlace = Item->byPlace;
					itmDelete.bySrcPos = Item->byPos;
					itmDelete.hSrcItem = Item->handle;
					
					
					
					sGU_ITEM_DISASSEMBLE_RES res;
					res.wOpCode = GU_ITEM_DISASSEMBLE_RES;
					res.wPacketSize = sizeof(sGU_ITEM_DISASSEMBLE_RES) - 2;

					//Need Load RDF here
					DisambleData = (sLAND_MARK_TBLDAT*)sTBM.GetLandMarkTable()->FindData(Item->tblidx);					
					BYTE QtdItem = rand() % 3;
					if (DisambleData != NULL)
					{

						//create the craft Item	
						for (int i = 0; i <= QtdItem; i++)
						{
							BYTE Amount = rand() % 10;
							sITEM_PROFILE createdItem;
							WORD result = _player->GetInventoryManager()->PerformShopBuy(DisambleData->RewardItemID[i], Amount, createdItem);
							if (result == GAME_SUCCESS && createdItem.tblidx != INVALID_TBLIDX)
							{
								SendItemCreate(&createdItem);
								res.ResultCode = GAME_SUCCESS;
								res.HItem[i] = createdItem.handle;
							}
						}
					}
					else
					{
						printf("Item not foud \n");
					}
					Item->byPlace = INVALID_TBLIDX;
					Item->byPos = INVALID_TBLIDX;
					Item->tblidx = INVALID_TBLIDX;
					SendPacket((char*)&itmDelete, sizeof(sGU_ITEM_DELETE));
					SendPacket((char*)&res, sizeof(sGU_ITEM_DISASSEMBLE_RES));
				}
			}
				break;
		}
		case Opcodes::UG_VEHICLE_DIRECT_PLAY_CANCEL_NFY:
		{
		//	sLog.outError("UG_VEHICLE_DIRECT_PLAY_CANCEL_NFY");
			sUG_VEHICLE_DIRECT_PLAY_CANCEL_NFY* req = (sUG_VEHICLE_DIRECT_PLAY_CANCEL_NFY *)packet.GetPacketBuffer();
			
			break;
		}
		case Opcodes::UG_VEHICLE_ENGINE_START_REQ:
		{
			//sLog.outError("UG_VEHICLE_ENGINE_START_REQ");
			sUG_VEHICLE_ENGINE_START_REQ* req = (sUG_VEHICLE_ENGINE_START_REQ *)packet.GetPacketBuffer();
			sGU_VEHICLE_ENGINE_START_RES res;

			res.wOpCode = GU_VEHICLE_ENGINE_START_RES;
			res.wPacketSize = sizeof(sGU_VEHICLE_ENGINE_START_RES) - 2;
			res.wResultCode = GAME_SUCCESS;		
			
			SendPacket((char*)&res, sizeof(sGU_VEHICLE_ENGINE_START_RES));

			sGU_VEHICLE_ENGINE_START_NFY res1;

			res1.wOpCode = GU_VEHICLE_ENGINE_START_NFY;
			res1.wPacketSize = sizeof(sGU_VEHICLE_ENGINE_START_NFY) - 2;
			res1.hDriverHandle = _player->GetHandle();			

			SendPacket((char*)&res1, sizeof(sGU_VEHICLE_ENGINE_START_NFY));
			//_player->GetState()->sCharStateBase.aspectState.sAspectStateBase.byAspectStateId = eASPECTSTATE::ASPECTSTATE_VEHICLE;
			_player->GetState()->sCharStateBase.aspectState.sAspectStateDetail.sVehicle.bIsEngineOn = true;
			//_player->GetState()->sCharStateBase.aspectState.sAspectStateDetail.sVehicle.hVehicleItem = INVALID_TBLIDX;
			//_player->GetState()->sCharStateBase.aspectState.sAspectStateDetail.sVehicle.idVehicleTblidx = INVALID_TBLIDX;
			//_player->UpdateAspectState(eASPECTSTATE::ASPECTSTATE_VEHICLE);
			
			break;
		}
		case Opcodes::UG_VEHICLE_ENGINE_STOP_REQ:
		{
			//sLog.outError("UG_VEHICLE_ENGINE_STOP_REQ");
			sUG_VEHICLE_ENGINE_STOP_REQ* req = (sUG_VEHICLE_ENGINE_STOP_REQ *)packet.GetPacketBuffer();

			sGU_VEHICLE_ENGINE_STOP_RES res;

			res.wOpCode = GU_VEHICLE_ENGINE_STOP_RES;
			res.wPacketSize = sizeof(sGU_VEHICLE_ENGINE_STOP_RES) - 2;
			res.wResultCode = GAME_SUCCESS;			

			SendPacket((char*)&res, sizeof(sGU_VEHICLE_ENGINE_STOP_RES));

			sGU_VEHICLE_ENGINE_STOP_NFY res1;

			res1.wOpCode = GU_VEHICLE_ENGINE_STOP_NFY;
			res1.wPacketSize = sizeof(sGU_VEHICLE_ENGINE_STOP_NFY) - 2;
			res1.hDriverHandle = _player->GetHandle();
			res1.dwFuelRemain = 0;

			SendPacket((char*)&res1, sizeof(sGU_VEHICLE_ENGINE_STOP_NFY));
			_player->SendToPlayerList((char*)&res1, sizeof(sGU_VEHICLE_ENGINE_STOP_NFY));

			//_player->GetState()->sCharStateBase.aspectState.sAspectStateBase.byAspectStateId = eASPECTSTATE::ASPECTSTATE_VEHICLE;
			_player->GetState()->sCharStateBase.aspectState.sAspectStateDetail.sVehicle.bIsEngineOn = false;
			//_player->GetState()->sCharStateBase.aspectState.sAspectStateDetail.sVehicle.hVehicleItem = INVALID_TBLIDX;
			//_player->GetState()->sCharStateBase.aspectState.sAspectStateDetail.sVehicle.idVehicleTblidx = INVALID_TBLIDX;
			//_player->UpdateAspectState(eASPECTSTATE::ASPECTSTATE_VEHICLE);
			
			break;
		}
		case Opcodes::UG_VEHICLE_END_REQ:
		{		
			//sLog.outError("UG_VEHICLE_END_REQ");
			sUG_VEHICLE_END_REQ* req = (sUG_VEHICLE_END_REQ *)packet.GetPacketBuffer();

			sGU_VEHICLE_END_RES res;

			res.wOpCode = GU_VEHICLE_END_RES;
			res.wPacketSize = sizeof(sGU_VEHICLE_END_RES) - 2;
			res.wResultCode = GAME_SUCCESS;			

			SendPacket((char*)&res, sizeof(sGU_VEHICLE_END_RES));		

			sGU_VEHICLE_END_NFY res1;

			res1.wOpCode = GU_VEHICLE_END_NFY;
			res1.wPacketSize = sizeof(sGU_VEHICLE_END_NFY) - 2;
			res1.hDriverHandle = _player->GetHandle();			
			res1.wResultCode = GAME_SUCCESS;
			SendPacket((char*)&res1, sizeof(sGU_VEHICLE_END_NFY));
			_player->SendToPlayerList((char*)&res1, sizeof(sGU_VEHICLE_END_NFY));

			
			_player->GetState()->sCharStateBase.aspectState.sAspectStateBase.byAspectStateId = eASPECTSTATE::ASPECTSTATE_INVALID;
			_player->GetState()->sCharStateBase.aspectState.sAspectStateDetail.sVehicle.bIsEngineOn = false;
			_player->GetState()->sCharStateBase.aspectState.sAspectStateDetail.sVehicle.hVehicleItem = INVALID_TBLIDX;
			_player->GetState()->sCharStateBase.aspectState.sAspectStateDetail.sVehicle.idVehicleTblidx = INVALID_TBLIDX;
			_player->SetState(eCHARSTATE::CHARSTATE_STANDING);
			_player->UpdateAspectState(eASPECTSTATE::ASPECTSTATE_INVALID);

			break;
		}
		case Opcodes::UG_VEHICLE_STUNT_NFY:
		{
			//sLog.outError("UG_VEHICLE_STUNT_NFY");
			sUG_VEHICLE_STUNT_NFY* req = (sUG_VEHICLE_STUNT_NFY *)packet.GetPacketBuffer();

			sGU_VEHICLE_STUNT_NFY res;

			res.wOpCode = GU_VEHICLE_STUNT_NFY;
			res.wPacketSize = sizeof(sGU_VEHICLE_STUNT_NFY) - 2;
			res.hDriverHandle = GAME_SUCCESS;		
			SendPacket((char*)&res, sizeof(sGU_VEHICLE_STUNT_NFY));
			_player->SendToPlayerList((char*)&res, sizeof(sGU_VEHICLE_STUNT_NFY));

			break;
		}
		case Opcodes::UG_SKILL_LEARN_BY_ITEM_REQ:
		{
			//sLog.outError("UG_SKILL_LEARN_BY_ITEM_REQ");
			_player->SendLearnSkillByItem(packet);
			break;
		}
		case Opcodes::UG_ITEM_UPGRADE_WORK_REQ:
		{
			//sLog.outError("UG_ITEM_UPGRADE_WORK_REQ");
			_player->SendItemUpgrade(packet);
			break;
		}
		case Opcodes::UG_ITEM_UPGRADE_BY_COUPON_REQ:
		{
			//sLog.outError("UG_ITEM_UPGRADE_BY_COUPON_REQ");
			//sLog.outPacketFile(&packet);
			_player->SendItemUpgradeByCoupon(packet);
			break;
		}
		case Opcodes::UG_ITEM_USE_REQ://Use Item
		{
			//sLog.outError("UG_ITEM_USE_REQ");
			_player->HandleItemUse(packet);
			//sLog.outPacketFile(&packet);
			break;
		}
		case Opcodes::UG_ITEM_SOCKET_DESTROY_BEAD_REQ: // Remove Doggi Ball
		{
			//sLog.outError("UG_ITEM_SOCKET_DESTROY_BEAD_REQ");
			//_player->ItemSoketDestroy(packet);
			break;
		}
		case Opcodes::UG_ITEM_SOCKET_INSERT_BEAD_REQ: // Doggi Ball
		{
			//sLog.outError("UG_ITEM_SOCKET_INSERT_BEAD_REQ");
			//_player->ItemSoketInsert(packet);
			break;
		}
		case Opcodes::UG_ITEM_CHANGE_OPTION_REQ: // Equipament Box
		{
			//sLog.outError("UG_ITEM_CHANGE_OPTION_REQ");
			_player->ItemOptionsChange(packet);
			//sLog.outPacketFile(&packet);
			break;
		}
		case Opcodes::UG_SKILL_INIT_REQ: // Skill Reset NPC
		{
			//sLog.outError("UG_SKILL_INIT_REQ");
			ResetSkill(packet);
			//sLog.outPacketFile(&packet);
			break;
		}
		case Opcodes::UG_DRAGONBALL_CHECK_REQ:
		{
			//sLog.outError("UG_DRAGONBALL_CHECK_REQ");
			//sLog.outPacketFile(&packet);
			SendDragonBallsCheck(packet);
			break;
		}
		case Opcodes::UG_DRAGONBALL_REWARD_REQ:
		{
			//sLog.outError("UG_DRAGONBALL_REWARD_REQ");
			SendShenlongReward(packet);
			break;
		}
		case Opcodes::UG_SHOP_EVENTITEM_START_REQ:
		{
			sLog.outError("UG_SHOP_EVENTITEM_START_REQ");
			sUG_SHOP_EVENTITEM_START_REQ *req = (sUG_SHOP_EVENTITEM_START_REQ*)packet.GetPacketBuffer();
			sGU_SHOP_EVENTITEM_START_RES ShopEventStart;

			ShopEventStart.wOpCode = GU_SHOP_EVENTITEM_START_RES;
			ShopEventStart.wPacketSize = sizeof(sGU_SHOP_EVENTITEM_START_RES) - 2;
			ShopEventStart.handle = req->handle;
			ShopEventStart.byType = 1;
			ShopEventStart.wResultCode = GAME_SUCCESS;
			SendPacket((char*)&ShopEventStart, sizeof(sGU_SHOP_EVENTITEM_START_RES));
			break;
		}
		case Opcodes::UG_SHOP_EVENTITEM_BUY_REQ:
		{
			SendShopEventBuy(packet);
			break;
		}
		case Opcodes::UG_SHOP_EVENTITEM_END_REQ:
		{
			sUG_SHOP_EVENTITEM_END_REQ *req = (sUG_SHOP_EVENTITEM_END_REQ*)packet.GetPacketBuffer();
			sGU_SHOP_EVENTITEM_END_RES ShopEnd;

			ShopEnd.wOpCode = GU_SHOP_EVENTITEM_END_RES;
			ShopEnd.wPacketSize = sizeof(sGU_SHOP_EVENTITEM_END_RES) - 2;

			ShopEnd.wResultCode = GAME_SUCCESS;
			SendPacket((char*)&ShopEnd, sizeof(sGU_SHOP_EVENTITEM_END_RES));
			break;
		}
		case Opcodes::UG_BUDOKAI_MUDOSA_INFO_REQ:
		{
			sUG_BUDOKAI_MUDOSA_INFO_REQ *req = (sUG_BUDOKAI_MUDOSA_INFO_REQ*)packet.GetPacketBuffer();
			sGU_BUDOKAI_MUDOSA_INFO_RES info;

			info.wOpCode = GU_BUDOKAI_MUDOSA_INFO_RES;
			info.wPacketSize = sizeof(sGU_BUDOKAI_MUDOSA_INFO_RES) - 2;
			info.byMudosaCount = 2;
			info.aMudosaInfo[0].wCurrentUserCount = 0;
			wcscpy_s(info.aMudosaInfo[0].wszMudosaName, BUDOKAI_MAX_MUDOSA_NAME_IN_UNICODE + 1, (L" Budokay "));
			info.aMudosaInfo[1].wCurrentUserCount = 0;
			wcscpy_s(info.aMudosaInfo[1].wszMudosaName, BUDOKAI_MAX_MUDOSA_NAME_IN_UNICODE + 1, (L" Budokay "));
			info.wResultCode = GAME_SUCCESS;
			SendPacket((char*)&info, sizeof(sGU_BUDOKAI_MUDOSA_INFO_RES));
			break;
		}
		case Opcodes::UG_BUDOKAI_MUDOSA_TELEPORT_REQ: // Opening Path for cc and dungeons
		{
			sUG_BUDOKAI_MUDOSA_TELEPORT_REQ *req = (sUG_BUDOKAI_MUDOSA_TELEPORT_REQ*)packet.GetPacketBuffer();
			sGU_BUDOKAI_MUDOSA_TELEPORT_RES info;

			info.wOpCode = GU_BUDOKAI_MUDOSA_TELEPORT_RES;
			info.wPacketSize = sizeof(sGU_BUDOKAI_MUDOSA_TELEPORT_RES) - 2;

			info.wResultCode = GAME_SUCCESS;
			SendPacket((char*)&info, sizeof(sGU_BUDOKAI_MUDOSA_TELEPORT_RES));

			sGU_AVATAR_WORLD_INFO res1;
			WorldTable *WorldTable = sTBM.GetWorldTable();
			sWORLD_TBLDAT *world = NULL;

			res1.wOpCode = GU_AVATAR_WORLD_INFO;
			res1.wPacketSize = sizeof(sGU_AVATAR_WORLD_INFO) - 2;

			res1.byDojoCount = 0;
			for (int n = 0; n < DBO_MAX_COUNT_DOJO_IN_WORLD; n++)
			{
				res1.sDojoData[n].guildId = 0xffffffff;
				res1.sDojoData[n].dojoTblidx = 0xffffffff;
			}
			world = (sWORLD_TBLDAT*)sTBM.GetWorldTable()->FindData(101);
			res1.worldInfo.worldID = 101;
			_player->SetWorldID(101);
			res1.worldInfo.tblidx = world->tblidx;
			res1.worldInfo.sRuleInfo.byRuleType = world->byWorldRuleType;
			_player->GetState()->sCharStateDetail.sCharStateTeleporting.byTeleportType = eTELEPORT_TYPE::TELEPORT_TYPE_BUDOKAI;
			res1.vCurLoc.x = world->vStart1Loc.x;
			res1.vCurLoc.y = world->vStart1Loc.y;
			res1.vCurLoc.z = world->vStart1Loc.z;
			res1.vCurDir.x = world->vStart1Dir.x;
			res1.vCurDir.y = world->vStart1Dir.y;
			res1.vCurDir.z = world->vStart1Dir.z;
			_player->SetWorldTableID(world->tblidx);
			_player->Relocate(res1.vCurLoc.x, res1.vCurLoc.y, res1.vCurLoc.z, res1.vCurDir.x, res1.vCurDir.y, res1.vCurDir.z);
			res1.worldInfo.hTriggerObjectOffset = HANDLE_TRIGGER_OBJECT_OFFSET;

			SendPacket((char*)&res1, sizeof(sGU_AVATAR_WORLD_INFO));
			break;
		}
		case Opcodes::UG_RANKBATTLE_INFO_REQ:
		{
			//sLog.outError("UG_MASCOT_SKILL_ADD_REQ");
			sUG_RANKBATTLE_INFO_REQ *req = (sUG_RANKBATTLE_INFO_REQ*)packet.GetPacketBuffer();

			sGU_RANKBATTLE_INFO_RES RankInfo;
			RankInfo.wOpCode = GU_RANKBATTLE_INFO_RES;
			RankInfo.wPacketSize = sizeof(sGU_RANKBATTLE_INFO_RES) - 2;
			RankInfo.wResultCode = GAME_SUCCESS;
			RankInfo.byBattleMode = 60;
			RankInfo.dwRemainTime = 0;
			RankInfo.byArenaCount = 2;
			for (int i = 0; i <= RankInfo.byArenaCount; i++)
			{
				RankInfo.asArenaInfo[i].wRegisterCount = sWorld.PlayerRankcount;
				RankInfo.asArenaInfo[i].rankBattleTblidx = 1012;
			}
			SendPacket((char*)&RankInfo, sizeof(sGU_RANKBATTLE_INFO_RES));

			break;
		}
		case Opcodes::UG_RANKBATTLE_JOIN_REQ:
		{
			sUG_RANKBATTLE_JOIN_REQ *req = (sUG_RANKBATTLE_JOIN_REQ*)packet.GetPacketBuffer();

			sGU_RANKBATTLE_JOIN_RES RankJoin;
			RankJoin.wOpCode = GU_RANKBATTLE_JOIN_RES;
			RankJoin.wPacketSize = sizeof(sGU_RANKBATTLE_JOIN_RES) - 2;
			RankJoin.wResultCode = GAME_SUCCESS;
			RankJoin.byArenaCount = 1;
			RankJoin.dwRemainTime = 0;
			RankJoin.hBoardObject = req->hBoardObject;
			RankJoin.rankBattleTblidx = req->rankBattleTblidx;
			RankJoin.asArenaInfo[0].rankBattleTblidx = 1012;
			RankJoin.asArenaInfo[0].wRegisterCount = sWorld.PlayerRankcount + 1;
			

			sGU_RANKBATTLE_JOIN_NFY RankJoinnFY;
			RankJoinnFY.wOpCode = GU_RANKBATTLE_JOIN_NFY;
			RankJoinnFY.wPacketSize = sizeof(sGU_RANKBATTLE_JOIN_NFY) - 2;
			RankJoinnFY.rankBattleTblidx = req->rankBattleTblidx;
			

			sWorld.PlayerRankcount += 1;
			int FreeSlot = 0;
			for (int i = 0; i <= 100; i++)
			{
				if (sWorld.InfoRank[i].PlayerHandle == 0 || sWorld.InfoRank[i].PlayerHandle == INVALID_TBLIDX)
				{
					FreeSlot = i;
				}
				if (sWorld.InfoRank[i].PlayerHandle == _player->GetHandle())
				{
					sWorld.PlayerRankcount -= 1;
					RankJoin.wResultCode = ResultCodes::GAME_GAMERULE_REG_ALREADY_JOINED_IN_RANKBATTLE;
				}
			}

			sWorld.InfoRank[FreeSlot].PlayerHandle = _player->GetHandle();
			sWorld.InfoRank[FreeSlot].PlayerLevel = _player->GetPcProfile()->byLevel;
			sWorld.InfoRank[FreeSlot].MapTblidx = 12000;
			sWorld.InfoRank[FreeSlot].isInvited = false;


			SendPacket((char*)&RankJoin, sizeof(sGU_RANKBATTLE_JOIN_RES));
			SendPacket((char*)&RankJoinnFY, sizeof(sGU_RANKBATTLE_JOIN_NFY));
			break;
		}
		case Opcodes::UG_TELEPORT_CONFIRM_REQ:
		{
			sUG_TELEPORT_CONFIRM_REQ *req = (sUG_TELEPORT_CONFIRM_REQ*)packet.GetPacketBuffer();

			sGU_TELEPORT_CONFIRM_RES TeleportConfirm;
			TeleportConfirm.wOpCode = GU_TELEPORT_CONFIRM_RES;
			TeleportConfirm.wPacketSize = sizeof(sGU_TELEPORT_CONFIRM_RES) - 2;
			TeleportConfirm.wResultCode = ResultCodes::GAME_CAN_NOT_TELEPORT;
			TeleportConfirm.bTeleport =req->bTeleport;
			TeleportConfirm.byTeleportIndex = req->byTeleportIndex;
			TeleportConfirm.bClearInterface = true;
			SendPacket((char*)&TeleportConfirm, sizeof(sGU_TELEPORT_CONFIRM_RES));

			if (req->bTeleport == true)
			{
				sGU_CHAR_TELEPORT_RES teleport;
				_player->SetIsReady(false);

				sWORLD_TBLDAT *world = (sWORLD_TBLDAT*)sTBM.GetWorldTable()->FindData(12000);
				teleport.wResultCode = GAME_SUCCESS;
				teleport.wOpCode = GU_CHAR_TELEPORT_RES;
				teleport.wPacketSize = sizeof(sGU_CHAR_TELEPORT_RES) - 2;
				teleport.unk = INVALID_TBLIDX;
				if (world != NULL)
				{
					if (12000 != _player->GetWorldID())
					{
						teleport.bIsToMoveAnotherServer = true;
						teleport.sWorldInfo.worldID = world->tblidx;
						teleport.sWorldInfo.tblidx = world->tblidx;
						teleport.sWorldInfo.sRuleInfo.byRuleType = world->byWorldRuleType;
						teleport.sWorldInfo.hTriggerObjectOffset = HANDLE_TRIGGER_OBJECT_OFFSET;
						_player->GetState()->sCharStateDetail.sCharStateTeleporting.byTeleportType = eTELEPORT_TYPE::TELEPORT_TYPE_RANKBATTLE;
					}
					else
					{
						teleport.bIsToMoveAnotherServer = false;

					}
					teleport.vNewDir.x = world->vStart1Dir.x;
					teleport.vNewDir.y = world->vStart1Dir.y;
					teleport.vNewDir.z = world->vStart1Dir.z;
					teleport.vNewLoc.x = world->vStart1Loc.x;
					teleport.vNewLoc.y = world->vStart1Loc.y;
					teleport.vNewLoc.z = world->vStart1Loc.z;


					_player->SetState(eCHARSTATE::CHARSTATE_TELEPORTING);


					_player->SetWorldID(world->tblidx);
					_player->SetWorldTableID(world->tblidx);
					_player->Relocate(teleport.vNewLoc.x, teleport.vNewLoc.y, teleport.vNewLoc.z, teleport.vNewDir.x, teleport.vNewDir.y, teleport.vNewDir.z);


					SendPacket((char*)&teleport, sizeof(sGU_CHAR_TELEPORT_RES));
				}
				sGU_CHAR_DIRECT_PLAY rank;
				rank.wOpCode = GU_CHAR_DIRECT_PLAY;
				rank.wPacketSize = sizeof(sGU_CHAR_DIRECT_PLAY) - 2;
				rank.hSubject = _player->GetHandle();
				rank.directTblidx = 12000;
				SendPacket((char*)&rank, sizeof(sGU_CHAR_DIRECT_PLAY));
				
			}
			break;
		}
		case Opcodes::UG_MASCOT_SKILL_ADD_REQ:
		{
			//sLog.outPacketFile(&packet);
			//sLog.outError("UG_MASCOT_SKILL_ADD_REQ");
			sUG_MASCOT_SKILL_ADD_REQ *req = (sUG_MASCOT_SKILL_ADD_REQ*)packet.GetPacketBuffer();
			//Need Find how get SlotID / Skill Table			
			sGU_MASCOT_SKILL_ADD_RES MascotSkillAdd;
			MascotSkillAdd.wOpCode = GU_MASCOT_SKILL_ADD_RES;
			MascotSkillAdd.wPacketSize = sizeof(sGU_MASCOT_SKILL_ADD_RES) - 2;
			MascotSkillAdd.ResultCode = GAME_SUCCESS;
			MascotSkillAdd.PetSlot = _player->GetAttributesManager()->PetInUse;
			MascotSkillAdd.SkillSlot = req->Place;
			MascotSkillAdd.SkillID = 314011;
			SendPacket((char*)&MascotSkillAdd, sizeof(sGU_MASCOT_SKILL_ADD_RES));
			
			break;
		}	
		case Opcodes::UG_MASCOT_SUMMON_REQ_EX:
		{
			//sLog.outError("UG_MASCOT_SUMMON_REQ_EX");
			sUG_MASCOT_SUMMON_REQ_EX *req = (sUG_MASCOT_SUMMON_REQ_EX*)packet.GetPacketBuffer();
			sGU_MASCOT_SUMMON_EX_RES Summon_mascot;
			Summon_mascot.wOpCode = GU_MASCOT_SUMMON_EX_RES;
			Summon_mascot.wPacketSize = sizeof(sGU_MASCOT_SUMMON_EX_RES) - 2;
			Summon_mascot.ResultCode = GAME_SUCCESS;
			Summon_mascot.PetSlot = req->Place;
			_player->GetAttributesManager()->PetInUse = req->Place;
			SendPacket((char*)&Summon_mascot, sizeof(sGU_MASCOT_SUMMON_EX_RES));

			break;
		}
		case Opcodes::UG_MASCOT_UNSUMMON_REQ_EX:
		{
			//sLog.outError("UG_MASCOT_UNSUMMON_REQ_EX");
			sUG_MASCOT_UNSUMMON_REQ_EX *req = (sUG_MASCOT_UNSUMMON_REQ_EX*)packet.GetPacketBuffer();
			sGU_MASCOT_UNSUMMON_EX_RES unsumon_mascot;
			unsumon_mascot.wOpCode = GU_MASCOT_UNSUMMON_EX_RES;
			unsumon_mascot.wPacketSize = sizeof(sGU_MASCOT_UNSUMMON_EX_RES) - 2;
			unsumon_mascot.ResultCode = GAME_SUCCESS;
			unsumon_mascot.PetSlot = req->Place;
			_player->GetAttributesManager()->PetInUse = INVALID_BYTE;
			SendPacket((char*)&unsumon_mascot, sizeof(sGU_MASCOT_UNSUMMON_EX_RES));

			break;
		}
		case Opcodes::UG_MASCOT_DELETE_REQ_EX:
		{
			
			sUG_MASCOT_DELETE_REQ_EX *req = (sUG_MASCOT_DELETE_REQ_EX*)packet.GetPacketBuffer();
		//	sLog.outError("UG_MASCOT_DELETE_REQ_EX %d ",req->Place);
			sGU_MASCOT_DELETE_EX_RES DeletMascot;
			DeletMascot.wOpCode = GU_MASCOT_DELETE_EX_RES;
			DeletMascot.wPacketSize = sizeof(sGU_MASCOT_DELETE_EX_RES) - 2;
			DeletMascot.ResultCode = GAME_SUCCESS;
			DeletMascot.PetSlot = req->Place;
			SendPacket((char*)&DeletMascot, sizeof(sGU_MASCOT_DELETE_EX_RES));
			sql::ResultSet* result = sDB.executes("DELETE FROM `MascotInfo` WHERE `CharID` = '%d' AND `Slot` = '%d';", _player->charid, req->Place);
			if (result != NULL)
				delete result;
			break;
		}
		case Opcodes::UG_DOJO_CREATE_REQ: 
		{
			//Prevent Game Crash
			//sLog.outError("UG_DOJO_CREATE_REQ");
			sUG_DOJO_CREATE_REQ *req = (sUG_DOJO_CREATE_REQ*)packet.GetPacketBuffer();
			sGU_DOJO_CREATE_RES CreateDojo;

			CreateDojo.wOpCode = GU_DOJO_CREATE_RES;
			CreateDojo.wPacketSize = sizeof(sGU_DOJO_CREATE_RES) - 2;
			CreateDojo.wResultCode = COMMUNITY_DOJO_MAKE_FAIL;

			SendPacket((char*)&CreateDojo, sizeof(sGU_DOJO_CREATE_RES));

			break;
		}
		case Opcodes::UG_DOJO_FUNCTION_ADD_REQ:
		{
			//Prevent Game Crash
			//sLog.outError("UG_DOJO_FUNCTION_ADD_REQ");
			sUG_DOJO_FUNCTION_ADD_REQ *req = (sUG_DOJO_FUNCTION_ADD_REQ*)packet.GetPacketBuffer();
			sGU_DOJO_FUNCTION_ADD_RES CreateDojo;

			CreateDojo.wOpCode = GU_DOJO_FUNCTION_ADD_RES;
			CreateDojo.wPacketSize = sizeof(sGU_DOJO_FUNCTION_ADD_RES) - 2;
			CreateDojo.wResultCode = GAME_SUCCESS;
			CreateDojo.byFunction = 0;
			SendPacket((char*)&CreateDojo, sizeof(sGU_DOJO_FUNCTION_ADD_RES));

			break;
		}
		case Opcodes::UG_TRANSFORM_CANCEL_REQ:
		{
			sUG_TRANSFORM_CANCEL_REQ *req = (sUG_TRANSFORM_CANCEL_REQ*)packet.GetPacketBuffer();
			sGU_TRANSFORM_CANCEL_RES TransformCancel;

			TransformCancel.wOpCode = GU_TRANSFORM_CANCEL_RES;
			TransformCancel.wPacketSize = sizeof(sGU_TRANSFORM_CANCEL_RES) - 2;
			TransformCancel.wResultCode = GAME_SUCCESS;
			SendPacket((char*)&TransformCancel, sizeof(sGU_TRANSFORM_CANCEL_RES));
			if (_player->GetState()->sCharStateBase.aspectState.sAspectStateBase.byAspectStateId == eASPECTSTATE::ASPECTSTATE_KAIOKEN)
			{
			//	int grade = 250 * _player->GetState()->sCharStateBase.aspectState.sAspectStateDetail.sKaioken.byRepeatingCount;
			//	_player->GetAttributesManager()->SetLastPhysicalOffence(grade * -1);
			//	_player->GetAttributesManager()->SetLastEnergyOffence(grade * -1);				
			}		
			_player->GetState()->sCharStateBase.aspectState.sAspectStateBase.byAspectStateId = eASPECTSTATE::ASPECTSTATE_INVALID;
			_player->GetState()->sCharStateBase.aspectState.sAspectStateDetail.sVehicle.bIsEngineOn = false;
			_player->GetState()->sCharStateBase.aspectState.sAspectStateDetail.sVehicle.hVehicleItem = INVALID_TBLIDX;
			_player->GetState()->sCharStateBase.aspectState.sAspectStateDetail.sVehicle.idVehicleTblidx = INVALID_TBLIDX;
			_player->UpdateAspectState(eASPECTSTATE::ASPECTSTATE_INVALID);
			break;
		}
		/////GUILD PACKETS---------------------------------------------------////
		case Opcodes::UG_GUILD_INVITE_REQ:
		{			
			sLog.outError("UG_GUILD_INVITE_REQ");
			InvitePlayertoGuild(packet);
			break;
		}
		case Opcodes::UG_GUILD_CREATE_REQ:
		{
			sLog.outError("UG_GUILD_CREATE_REQ");
			CreateNewGuild(packet);
			break;
		}
		//In dev
		case UG_GUILD_GIVE_ZENNY:
		{
			sLog.outError("UG_GUILD_GIVE_ZENNY");
			GUILD_GIVE_ZENNY(packet);
			break;
		}
		case UG_GUILD_FUNCTION_ADD_REQ:
		{
			sLog.outError("UG_GUILD_FUNCTION_ADD_REQ");
			GUILD_FUNCTION_ADD_REQ(packet);
			break;
		}
		case UG_GUILD_CREATE_MARK_REQ:
		{
			sLog.outError("UG_GUILD_CREATE_MARK_REQ");
			GUILD_CREATE_MARK_REQ(packet);
			break;
		}

		/////----------------------------------------------------------------////
		case Opcodes::UG_HOIPOIMIX_ITEM_CREATE_EX_REQ:
		{
			SendHoiPoiMixCreate(packet);
			
			break;
		}
		/*case UG_BATTLE_DUNGEON_ENTER_REQ: // not working yet, character stuck.
		{			
			sGU_AVATAR_WORLD_INFO res1;
			WorldTable *WorldTable = sTBM.GetWorldTable();
			sWORLD_TBLDAT *world = NULL;		

			res1.wOpCode = GU_AVATAR_WORLD_INFO;
			res1.wPacketSize = sizeof(sGU_AVATAR_WORLD_INFO) - 2;

			res1.byDojoCount = 7;
			for (int n = 0; n < DBO_MAX_COUNT_DOJO_IN_WORLD; n++)
			{
				res1.sDojoData[n].guildId = 0xffffffff;
				res1.sDojoData[n].dojoTblidx = 0xffffffff;
			}				
				world = (sWORLD_TBLDAT*)sTBM.GetWorldTable()->FindData(910000);
				res1.worldInfo.worldID = 910000;
				_player->SetWorldID(910000);			
			if (world != NULL)
			{
				res1.worldInfo.tblidx = world->tblidx;
				res1.worldInfo.sRuleInfo.byRuleType = world->byWorldRuleType;
				_player->GetState()->sCharStateDetail.sCharStateTeleporting.byTeleportType = eTELEPORT_TYPE::TELEPORT_TYPE_DUNGEON;
				res1.vCurLoc.x = world->vStart1Loc.x;
				res1.vCurLoc.y = world->vStart1Loc.y;
				res1.vCurLoc.z = world->vStart1Loc.z;
				res1.vCurDir.x = world->vStart1Dir.x;
				res1.vCurDir.y = world->vStart1Dir.y;
				res1.vCurDir.z = world->vStart1Dir.z;
				_player->SetWorldTableID(world->tblidx);
				_player->Relocate(res1.vCurLoc.x, res1.vCurLoc.y, res1.vCurLoc.z, res1.vCurDir.x, res1.vCurDir.y, res1.vCurDir.z);
				res1.worldInfo.hTriggerObjectOffset = 100000;

				SendPacket((char*)&res1, sizeof(sGU_AVATAR_WORLD_INFO));
			}
			break;
		}*/
#pragma endregion END_OF_MARCO_RAFAEL_PACKETS
		default:
		{

			//Log every OpCode
			sLog.outError("OpCode received :: %d", header->wOpCode);

			try
			{
				sLog.outPacketFile(&packet);
//				sLog.outDebug("Unhandle packet received: %s", header->wOpCode);
			}
			catch (exception* e)
			{
				printf(e->what());
			}
			break;
		}
	}
}
