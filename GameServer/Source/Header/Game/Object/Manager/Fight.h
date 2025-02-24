#ifndef __FIGHT_H
#define __FIGHT_H

#pragma once

#include <Define.h>
#include <Game\Object\Object.h>
#include <NtlBattle.h>
#include <NtlSkill.h>

class Player;
class Mob;

class FightManager
{
public:
	FightManager();
	~FightManager();

	//	------------------------------------------------------------------------
	// LOGIC
	//	------------------------------------------------------------------------
	bool					canTakeDamage(Object& Attacker, Object& Target);
	bool					HandleDamage(Object& Attacker, Object& Target);
	void					HandlePlrFight();
	bool					HandlePlrSpinAttack(Object* target, Player* player);
	void					SendCharSpecialAttacNfy(HOBJECT target, TBLIDX skillTblidx, DWORD damage);

	float					GetRandomDamagePercent(float damage, int min, int max);
	float					CalculePhysicalDamage(float attackerOffence, DWORD attackerLevel, float targetDefence);
	float					CalculeEnergyDamage(float attackerOffence, DWORD attackerLevel, float targetDefence);
	int						CalculeAttackSuccess(int attAttackRate, int defDodgeRate, BYTE attLevel, BYTE defLevel);
	int						CalculePhysicalCriticalSuccess(WORD attPhysicalCriticalRate, WORD deffPhysicalCriticalDefenceRate);
	int						CalculeEnergyCriticalSuccess(WORD attEnergyCriticalRate, WORD deffEnergyCriticalDefenceRate);
	DWORD					CalculePhysicalCriticalDamage(float damage, float PhysicalCriticalRange);
	DWORD					CalculeEnergyCriticalDamage(float damage, float energyCriticalRange);

	void					GetPlayerDamage(bool caster, eOBJTYPE ObjectTypeId);
	void					GetPlayerCriticAttack(bool caster, eOBJTYPE ObjectTypeId);
	void					GetPlayerHitChance(eOBJTYPE ObjectTypeId);
	int						GetLevelDiff();
private:
	Player*					plr;
	Player*					plrTarget;
	Mob*					mob;
	Object*					TargetInfo;
	BYTE					attackCount;

	DWORD					attackValue;
	DWORD					reflectedDamage;
	eBATTLE_ATTACK_RESULT	attackResult;
	eDBO_GUARD_TYPE			guardType;
	std::mutex				mutexFight;
};

#endif