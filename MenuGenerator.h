#pragma once
#include "Superhero.h"
#include "Player.h"

class MenuGenerator
{
	MenuGenerator() = delete;
	MenuGenerator(const MenuGenerator& other) = delete;
	MenuGenerator(MenuGenerator&& other) = delete;
	MenuGenerator& operator=(const MenuGenerator& other) = delete;
	MenuGenerator& operator=(MenuGenerator&& other) = delete;

public:
	static void ShowStartUpMenu();
	static void ShowLogInMenu();
	static void ShowAdminMenu();
	static void ShowPlayerDialog();
	static void ShowPlayersInfoPlayer(void (*playersDataPredicate)(bool isAdmin), bool isAdmin);
	static void ShowRanklistMenu();
	static void ShowMarket(void(*showMarketPredicate)());
	static void ShowPersonalData(const Player* player);
	static void ShowMarketMenu();
	static void ShowBuyHeroMenu(void(*predicateHeroes)(), double money);
	static void ShowPlayerHeroes(void(*predicateHeroes)(unsigned id), unsigned countHeroes, unsigned id);
	static void ShowChooseHeroToUpgradeMenu(void(*predicateHeroes)(unsigned id), unsigned id);
	static void ShowUpgradeHeroMenu(const MyString& heroName, const SuperHero* hero,
		double balance, double cost);
	static void ShowSettingsPlayer();
	static void ShowThemes();
	static void ShowLeagueMenu();
};