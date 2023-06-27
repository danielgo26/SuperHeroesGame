#pragma once
#include "MyQueue.hpp"
#include "Enums.h"
#include "Player.h"

class BattleStatistics
{
	struct BattleTimeline;
	MyQueue<BattleTimeline*> _queue;//to keep and the playing players, and heroes
	MyQueue<unsigned> _newPointsAttacker;
	MyQueue<unsigned> _newPointsAttacked;
	unsigned _count = 0;
	bool _isQuickBattle = true;
public:
	struct BattleTimeline
	{
		BattleResult result;
		Player* attacking = nullptr;
		Player* attacked = nullptr;
		const SuperHero* heroToPlayWith = nullptr;
		const SuperHero* heroToAttack = nullptr;
	};
	unsigned getCount() const;
	bool getIsQuickBattle()const;
	BattleTimeline* getBattleStatistics()const;

	void addStatistics(BattleResult result, Player* attackingPlayer, Player* attackedPlayer,
		const SuperHero* heroToPlayWith, const SuperHero* heroToAttack);
	void addNewPoints(unsigned newPointsAttacker, unsigned newPointsAttacked);
	const BattleTimeline* removeStatistics();
	unsigned removeNewPointsAttacker();
	unsigned removeNewPointsAttacked();

	void setTypeOfBattle(bool isQuick);
	void setNewHeroToPlayWith(const SuperHero* heroToPlayWith);
	void setNewHeroToAttack(const SuperHero* heroToAttack);
};