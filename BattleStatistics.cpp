#include "BattleStatistics.h"

void BattleStatistics::addStatistics(BattleResult result, Player* attackingPlayer, Player* attackedPlayer,
	const SuperHero* heroToPlayWith, const SuperHero* heroToAttack)
{
	BattleTimeline* timeline = new BattleTimeline();;
	timeline->result = result;
	timeline->attacking = attackingPlayer;
	timeline->attacked = attackedPlayer;
	timeline->heroToPlayWith = heroToPlayWith;
	timeline->heroToAttack = heroToAttack;
	_queue.push(timeline);
	_count++;
}
void BattleStatistics::addNewPoints(unsigned newPointsAttacker, unsigned newPointsAttacked)
{
	_newPointsAttacker.push(newPointsAttacker);
	_newPointsAttacked.push(newPointsAttacked);
}
const BattleStatistics::BattleTimeline* BattleStatistics::removeStatistics()
{
	const BattleTimeline* result = _queue.peek();
	_queue.pop();
	_count--;
	return result;
}
unsigned BattleStatistics::removeNewPointsAttacker()
{
	unsigned points = _newPointsAttacker.peek();
	_newPointsAttacker.pop();
	return points;
}
unsigned BattleStatistics::removeNewPointsAttacked()
{
	unsigned points = _newPointsAttacked.peek();
	_newPointsAttacked.pop();
	return points;
}

unsigned BattleStatistics::getCount() const
{
	return _count;
}

bool BattleStatistics::getIsQuickBattle()const
{
	return _isQuickBattle;
}

BattleStatistics::BattleTimeline* BattleStatistics::getBattleStatistics()const
{
	return _queue.peek();
}

void BattleStatistics::setTypeOfBattle(bool isQuick)
{
	_isQuickBattle = isQuick;
}

void BattleStatistics::setNewHeroToPlayWith(const SuperHero* heroToPlayWith)
 {
	MyQueue<BattleTimeline*> newQueue;
	while (!_queue.isEmpty())
	{
		BattleTimeline* curr = _queue.peek();
		_queue.pop();
		if (_queue.isEmpty())
		{
			curr->heroToPlayWith = heroToPlayWith;
		}
		newQueue.push(curr);
	}
	_queue = newQueue;
}
void BattleStatistics::setNewHeroToAttack(const SuperHero* heroToAttack)
{
	MyQueue<BattleTimeline*> newQueue;
	size_t counter = 0;
	while (!_queue.isEmpty())
	{
		BattleTimeline* curr = _queue.peek();
		_queue.pop();
		if (counter == 0)
		{
			curr->heroToAttack = heroToAttack;
		}
		newQueue.push(curr);
	}
	_queue = newQueue;
}