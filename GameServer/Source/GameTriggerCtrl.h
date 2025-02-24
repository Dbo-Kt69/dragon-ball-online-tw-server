#pragma once
#include "DboTSCore.h"
class CGameTriggerCtrl : public CDboTSTCtrl
{
	NTL_TS_DECLARE_RTTI
private:
	//Containers
	void CheckContCond(CDboTSContGCond* pCond, CNtlTSCont* pParent);
	void CheckContStart(CDboTSContStart* pStart, CNtlTSCont* pParent);
	void CheckContAct(CDboTSContGAct* pAct, CNtlTSCont* pParent, CNtlTSCont* pNextCont);
	void CheckContReward(CDboTSContReward* pReward, CNtlTSCont* pParent);
	void CheckContEnd(CDboTSContEnd* pEnd, CNtlTSCont* pParent);
	void CheckContUserSel(CDboTSContUsrSel* pUserSel, CNtlTSCont* pParent);
	void CheckContNarration(CDboTSContNarration* pNarration, CNtlTSCont* pParent);
	void CheckContProposal(CDboTSContProposal* pProposal, CNtlTSCont* pParent);
	void CheckDialogOpen(CDboTSDialogOpen* pDialog, CNtlTSCont* pParent);
	void CheckContSwitch(CDboTSContSwitch* pSwitch, CNtlTSCont* pParent);
	void CheckContUnifiedNarration(CDboTSContUnifiedNarration* pUnifiedNarration, CNtlTSCont* pParent);

	//Actions
	void SendActPortal(CDboTSActPortal* pActPortal);
	void SendActSkyDgn(CDboTSActSkyDgn* pActSkyDgn);
	void SendActWaitTime(CDboTSActTWaitTS* pActTime);
	void SendActTLQ(CDboTSActTLQ* pACtTLQ);
	void SendActBroadMsg(CDboTSActBroadMsg* pActBroadMsg);
	void SendActConcCheck(CDboTSActConcCheck* pActConcCheck);
	void SendActCustomEvt(CDboTSActCustomEvt* pActCustomEvt);
	void SendActDir(CDboTSActDir* pActDir);
	void SendActMail(CDboTSActMail* pActMail);
	void SendActDirIndicator(CDboTSActDirIndicator* pActDirIndicator);
	void SendActDojo(CDboTSActDojo* pActDojo);
	void SendActDoSkill(CDboTSActDoSkill* pActDoSkill);
	void SendActDrop(CDboTSActDrop* pActDrop);
	void SendActEscort(CDboTSActEscort* pActEscort);
	void SendActETimerE(CDboTSActETimerE* pActETimerE);
	void SendActETimerS(CDboTSActETimerS* pActETimerS);
	void SendActExCGroup(CDboTSActExcCGroup* pActExCGroup);
	void SendActHint(CDboTSActHint* pActHint);
	void SendActInSSM(CDboTSActInSSM* pActInSSM);
	void SendActItem(CDboTSActItem* pActItem);
	void SendActMiniNarration(CDboTSActMiniNarration* pActMiniNarration);
	void SendActNPCConv(CDboTSActNPCConv* pActNPCConv);
	void SendActAvatarDead(CDboTSActAvatarDead* pActAvatarDead);
	void SendActOutMsg(CDboTSActOutMsg* pActNPCConv);
	void SendActObjConv(CDboTSActObjConv* pActObjConv);
	void SendActObjState(CDboTSActObjState* pActObjState);
	void SendActObjWPS(CDboTSActObjWPS* pActObjWPS);
	void SendActOPCam(CDboTSActOPCam* pActOPCam);
	void SendActOpenWindow(CDboTSActOpenWindow* pActOpenWindow);
	void SendActOPObject(CDboTSActOPObject* pActOPObject);
	void SendActPCConv(CDboTSActPCConv* pActPCConv);
	void SendActPIDgn(CDboTSActPIDgn* pActPIDgn);
	void SendActQItem(CDboTSActQItem* pActQItem);
	void SendActRegCTiming(CDboTSActRegCTiming* pActRegCTiming);
	void SendActRegQInfo(CDboTSActRegQInfo* pActRegQInfo);
	void SendActRmvCoupon(CDboTSActRmvCoupon* pActRmvCoupon);
	void SendActSendSvrEvt(CDboTSActSendSvrEvt* pActSendSvrEvt);
	void SendActSkipCont(CDboTSActSkipCont* pActSkipCont);
	void SendActSToCEvt(CDboTSActSToCEvt* pActSToCEvt);
	void SendActWPSFD(CDboTSActWPSFD* pActSToCEvt);
	void SendActSWProbSF(CDboTSActSWProbSF* pActSWProbSF);

	//Events
	void SendEvtBindStone(CDboTSBindStone* pEvtBindStone);
	void SendEvtBudokai(CDboTSBudokai* pEvtBudokai);
	void SendEvtClickMob(CDboTSClickMob* pEvtClickMob);
	void SendEvtClickNPC(CDboTSClickNPC* pEvtClickNPC);
	void SendEvtClickObject(CDboTSClickObject* pEvtClickObject);
	void SendEvtColObject(CDboTSColObject* pEvtColObject);
	void SendEvtColRgn(CDboTSColRgn* pEvtColRgn);
	void SendEvtFreeBattle(CDboTSFreeBattle* pEvtFreeBattle);
	void SendEvtHoipoiMix(CDboTSHoipoiMix* pEvtHoipoiMix);
	void SendEvtItemEquip(CDboTSItemEquip* pEvtItemEquip);
	void SendEvtItemGet(CDboTSItemGet* pEvtItemGet);
	void SendEvtItemIdentity(CDboTSItemIdentity* pEvtItemIdentity);
	void SendEvtItemUpgrade(CDboTSItemUpgrade* pEvtItemUpgrade);
	void SendEvtItemUse(CDboTSItemUse* pEvtItemUse);
	void SendEvtParty(CDboTSParty* pEvtParty);
	void SendEvtPrivateShop(CDboTSPrivateShop* pEvtPrivateShop);
	void SendEvtRB(CDboTSRB* pEvtRB);
	void SendEvtRcvSvrEvt(CDboTSRcvSvrEvt* pEvtRcvSvrEvt);
	void SendEvtScoutUse(CDboTSScoutUse* pEvtScoutUse);
	void SendEvtSearchQuest(CDboTSSearchQuest* pEvtSearchQuest);
	void SendEvtSkillUse(CDboTSSkillUse* pEvtSkillUse);
	void SendEvtSlotMachine(CDboTSSlotMachine* pEvtSlotMachine);
	void SendEvtTeleport(CDboTSTeleport* pEvtTeleport);
	void SendEvtUseMail(CDboTSUseMail* pEvtUseMail);
	//Others
	void CheckRewardTypeAndSend(sREWARD_INFO* m_pDefRwd, sREWARD_INFO* m_pSelRwd);
public:
	CGameTriggerCtrl();
	~CGameTriggerCtrl();
	NTL_TS_T_ID tID;//Get trigger getId()
	NTL_TS_TG_ID tgID;//((CNtlTSGroup*)pContUsr->GetParent())->GetID()
	NTL_TS_TG_ID tcID;//pContUsr->GetID();

	void CheckContainer(CNtlTSCont* pCurtCont, CNtlTSCont* pNextCont, CNtlTSTrigger* pTrigger, CDboTSTCtrl* pTriggerCtrl);	
};

