#pragma once
#include "Game.h"

class BattleManager
{
	static const SuperHero* _heroToPlayWith;
	static Player* _playerAttacking;
	static Player* _playerToAttack;
	static const SuperHero* _heroToAttack;
	static BattleStatistics _battleStatistics;
	static BattleResult _currBattleResult;
	//here we just point to players we do not create new ones
	static vector<const Player*> _playersInBattle;

	BattleManager() = delete;
	BattleManager(const BattleManager& other) = delete;
	BattleManager(BattleManager&& other) = delete;
	BattleManager& operator=(const BattleManager& other) = delete;
	BattleManager& operator=(BattleManager&& other) = delete;

	static void getOpponent(MyString& usernameOpp);
	static void getOpponentHero(MyString& heronameOpp, const MyString& usernameOpp);
	static void getHeroToAttackWith(MyString& heronameWarrior, const MyString& heronameOpp, const MyString& usernameOpp);
public:
	static const SuperHero* getHeroToPlayWith();
	static Player* getPlayerToAttack();
	static const SuperHero* getHeroToAttack();
	static BattleStatistics& getBattleStatistics();

	static const vector<const Player*>& getPlayersInBattle();

	static void addStatistics(BattleResult result,
		Player* attackingPlayer, Player* attackedPlayer, const SuperHero* heroToPlayWith, const SuperHero* heroToAttack);

	static void addPlayerInBattle(unsigned id);
	static void removePlayerFromBattle(unsigned id);
	static void setHeroToPlayWith(const SuperHero* hero);
	static void setAttackingPlayer(Player* player);
	static void setPlayerToAttack(Player* player);
	static void setHeroToAttack(const SuperHero* hero);

	static void clearPlayersInBattle();
	static void setBattle();
	static void executeBattle();
	static void receiveBattleRezults();
	~BattleManager();
};