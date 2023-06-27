#include "MenuGenerator.h"
#include <iostream>
#include "DefaultStartValues.h"

void MenuGenerator::ShowStartUpMenu()
{
	std::cout << "----Main menu----" << std::endl;
	std::cout << "1. Log in" << std::endl;
	std::cout << "2. Exit" << std::endl;
	std::cout << "Enter number: ";
}

void MenuGenerator::ShowLogInMenu()
{
	std::cout << "----Log in----" << std::endl;
}

void MenuGenerator::ShowAdminMenu()
{
	std::cout << "----Admin menu----" << std::endl;
	std::cout << "1. Add admin" << std::endl;
	std::cout << "2. Add player" << std::endl;
	std::cout << "3. Delete player" << std::endl;
	std::cout << "4. Player info" << std::endl;
	std::cout << "5. Admin info" << std::endl;
	std::cout << "6. Add hero to market" << std::endl;
	std::cout << "7. Remove hero from market" << std::endl;
	std::cout << "8. Log out" << std::endl;
	std::cout << "Enter number: ";
}

void MenuGenerator::ShowPlayerDialog()
{
	std::cout << "----Player menu----" << std::endl;
	std::cout << "1. Play league" << std::endl;
	std::cout << "2. Quick battle" << std::endl;
	std::cout << "3. Players info" << std::endl;
	std::cout << "4. Ranklist" << std::endl;
	std::cout << "5. Market" << std::endl;
	std::cout << "6. Your heroes" << std::endl;
	std::cout << "7. Personal data" << std::endl;
	std::cout << "8. Settings" << std::endl;
	std::cout << "9. Log out" << std::endl;
	std::cout << "Enter number: ";
}

void MenuGenerator::ShowPlayersInfoPlayer(void (*playersDataPredicate)(bool isAdmin), bool isAdmin)
{
	std::cout << "----Players info----" << std::endl;
	playersDataPredicate(isAdmin);
	std::cout << "Enter any key for back: ";
}

void MenuGenerator::ShowRanklistMenu()
{
	std::cout << "----Ranklist type choose----" << std::endl;
	std::cout << "1. Top three players" << std::endl;
	std::cout << "2. Global classation" << std::endl;
	std::cout << "3. Back" << std::endl;
	std::cout << "Choose number: ";
}

void MenuGenerator::ShowPersonalData(const Player* player)
{
	Player pl;
	std::cout << "----Personal data----" << std::endl;
	player->getFullData();
	std::cout << "Enter any key for back: ";
}

void MenuGenerator::ShowMarket(void(*showMarketPredicate)())
{
	std::cout << "----Market----" << std::endl;
	showMarketPredicate();
}

void MenuGenerator::ShowMarketMenu()
{
	std::cout << "----Menu----" << std::endl;
	std::cout << "1. Buy a hero" << std::endl;
	std::cout << "2. Back" << std::endl;
	std::cout << "Enter number: ";
}

void MenuGenerator::ShowBuyHeroMenu(void(*predicateHeroes)(), double money)
{
	std::cout << "----Buy your new hero!----" << std::endl;
	std::cout << "Heroes: " << std::endl;
	predicateHeroes();
	std::cout << "Your balance is: " << money << "$" << std::endl;
	std::cout << "Enter the name of hero you want to buy (or \"none\" for back): ";

}

void MenuGenerator::ShowPlayerHeroes(void(*predicateHeroes)(unsigned id), unsigned countHeroes, unsigned id)
{
	predicateHeroes(id);
	if (countHeroes != 0)
	{
		std::cout << "----Hero operations----" << std::endl;
		std::cout << "1. Upgrade hero" << std::endl;
		std::cout << "2. Back" << std::endl;
		std::cout << "Enter number: ";
	}
}

void MenuGenerator::ShowChooseHeroToUpgradeMenu(void(*predicateHeroes)(unsigned id), unsigned id)
{
	std::cout << "----Choose your hero----" << std::endl;
	predicateHeroes(id);
	std::cout << "Enter heroname or \"none\" for back: ";
}

void MenuGenerator::ShowUpgradeHeroMenu(const MyString& heroName, const SuperHero* hero,
	double balance, double cost)
{
	std::cout << "----Upgrade " << heroName << "----" << std::endl;
	hero->getAllData();
	std::cout << "Your balance: " << balance << "$" << std::endl;
	std::cout << "Upgrade ammount: " << DefaultValues::UPGRADE_POWER_POINTS_AMMOUNT << " stamina" << std::endl;
	std::cout << "Your upgrade will cost: " << cost << "$" << std::endl;
	std::cout << "----Upgrade menu----" << std::endl;
	std::cout << "1. Upgrade" << std::endl;
	std::cout << "2. Back" << std::endl;
	std::cout << "Enter number: ";
}

void MenuGenerator::ShowSettingsPlayer()
{
	std::cout << "----Settings----" << std::endl;
	std::cout << "1. Change theme" << std::endl;
	std::cout << "2. Back" << std::endl;
	std::cout << "Enter index command:  ";
}

void MenuGenerator::ShowThemes()
{
	std::cout << "--Change theme--" << std::endl;
	std::cout << "1. Harmony" << std::endl;
	std::cout << "2. Colourful" << std::endl;
	std::cout << "3. Spring" << std::endl;
	std::cout << "4. Default" << std::endl;
	std::cout << "5. Back" << std::endl;
	std::cout << "Enter theme index: ";
}

void MenuGenerator::ShowLeagueMenu()
{
	std::cout << "----League menu----" << std::endl;
	std::cout << "1. Play" << std::endl;
	std::cout << "2. Search for opponents" << std::endl;
	std::cout << "3. Back" << std::endl;
	std::cout << "Enter number: ";
}

