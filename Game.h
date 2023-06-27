#pragma once
#include "Vector.hpp"
#include "MyString.h"
#include "Enums.h"
#include "Player.h"
#include "Admin.h"
#include "BattleStatistics.h"

class Game
{
	static vector<SuperHero> _heroes;
	static vector<int> _heroesOwners;
	static vector<Player> _players;
	static vector<Admin> _admins;

	static Admin* _loggedAdmin;
	static Player* _loggedPlayer;

	//how many times current hero was upgraded
	static vector<unsigned> _countHeroesUpgraded;
	static unsigned _heroesInMarketCount;

	static vector<Theme> _playersCurrThemes;

	Game() = delete;
	Game(const Game& other) = delete;
	Game(Game&& other) = delete;
	Game& operator=(const Game& other) = delete;
	Game& operator=(Game&& other) = delete;

	static int getPlayerIndexById(unsigned id);
	static int getAdminIndexById(unsigned id);
	static int getHeroIndexById(unsigned id);

public:
	static const Player* getPlayerByUsername(const MyString& playerUsername);
	static const Admin* getAdminByUsername(const MyString& adminUsername);
	static const SuperHero* getHeroByHeroname(const MyString& heroname);
	static const Player* getPlayerById(unsigned id);
	static const Admin* getAdminById(unsigned id);
	static const SuperHero* getHeroById(unsigned id);
	static bool isHeroFree(unsigned id);

	static Admin* getLoggedAdmin();
	static Player* getLoggedPlayer();
	static const SuperHero* getHeroToPlayWith();;

	static void getHeroesFromMarket();
	static unsigned getHeroesFromMarketCount();
	static void getAllPlayerHeroes(unsigned id);
	static unsigned getPlayerHeroesCount(unsigned id);
	static unsigned getPlayersCount();
	static unsigned getAdminsCount();

	static void getAllPlayersData(bool isAdmin);
	static void getAllAdminsData();

	static void getAllPlayersUsernames();
	static void getAllFreeHeroesHeronames();

	static BattleStatistics& getBattleStatistics();

	static void addPlayerInBattle(unsigned id);
	static void addAllPlayersInBattle();
	static void removePlayerFromBattle(unsigned id);
	static const vector<const Player*>& getPlayersInBattle();
	
	static void receiveMoneyFromLeague();
	static double getCheapestHeroPrice();

	static void setHeroToPlayWith(const MyString& heroname, unsigned id);
	static void setAttackingPlayer(const MyString& username);
	static void setPlayerToAttack(const MyString& username, unsigned id);
	static void setHeroToAttack(const MyString& heroname);
	static void removeHeroToPlayWith();

	static void clearPlayersFromBattle();

	static Theme getTheme();
	static void setTheme(Theme theme);

	static void addPlayer(const MyString& firstName, const MyString& lastName, const MyString& email,
		const MyString& username, const MyString& password);//check if already existing
	static void addAdmin(const MyString& firstName, const MyString& lastName, const MyString& email,
		const MyString& username, const MyString& password);//check if already existing
	static void addHero(const MyString& firstName, const MyString& lastName, const MyString& heroname,
		Power kindOfPower, unsigned powerPoints, double price);//check if already existing
	static void addHeroOwner(unsigned heroId, unsigned ownerId);

	static void modifyPriceOfHero(unsigned id, double price);//only these in market

	static double generateHeroUpgradeTax(unsigned heroIndex);
	static void increaseCountUpgradesOfHero(unsigned indexHero);

	static void deletePlayer(unsigned id);
	static void deleteAdmin(unsigned id);
	static void deleteHero(unsigned id);//if has no owner!
	static void removeHeroOwner(unsigned heroId);

	struct PlayerScore
	{
		const Player* player = nullptr;
		double score = 0;
	};
	static const vector<PlayerScore>* getPlayersInRanklist();

	static void setBattle();
	static void executeBattle();
	static void getBattleResults();

	static void logIn(const MyString username, const MyString password);
	static void logOut();

	~Game();
};