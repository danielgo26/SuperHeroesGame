#include "Commands.h"
#include <iostream>
#include "MenuGenerator.h"
#include "Game.h"
#include "ThemeManager.h"
#include <windows.h>
#include "GeneralFunctions.h"

void WrongInputCommand::execute()
{
	ThemeManager::getInstance().changeTheme(Theme::ErrorMessage);
	std::cout << "Wrong input!" << std::endl;
	if (Game::getLoggedPlayer() == nullptr)
		ThemeManager::getInstance().changeTheme(Theme::Default);
	else
		ThemeManager::getInstance().changeTheme(Game::getTheme());
}
Command* WrongInputCommand::clone() const
{
	return new WrongInputCommand(*this);
}
CommandType  WrongInputCommand::getType()const
{
	return CommandType::WrongInput;
}

void StartUpCommand::execute()
{
	ThemeManager::getInstance().changeTheme(Theme::Default);

	if (Game::getAdminsCount() == 0)
	{
		Game::addAdmin("admin", "admin", "admin", "admin", "admin");//0
		//Game::addPlayer("a", "a", "a", "a", "1Aa");//1
		//Game::addPlayer("b", "b", "b", "b", "2Bb");//2
		//Game::addPlayer("c", "c", "c", "c", "3Cc");//2
		//Game::addHero("op", "op", "obelisk", Power::earth, 100, 10);//0
		//Game::addHero("op2", "op2", "obelisk2", Power::earth, 100, 10);//1
		//Game::addHero("op3", "op3", "obelisk3", Power::earth, 100, 10);//2
		//Game::addHero("op4", "op4", "obelisk4", Power::earth, 100, 10);//2
	}

	MenuGenerator::ShowStartUpMenu();
}
Command* StartUpCommand::clone() const
{
	return new StartUpCommand(*this);
}
CommandType StartUpCommand::getType() const
{
	return CommandType::StartUp;
}

void LogInCommand::execute()
{
	std::cout << "----Log in----" << std::endl;
	std::cout << "Enter username: ";
	MyString username;
	std::cin >> username;
	std::cout << "Enter password: ";
	MyString password;
	std::cin >> password;
	Game::logIn(username, password);

	if (Game::getLoggedAdmin() != nullptr)
	{
		system("cls");
		std::cout << "Admin " << username << " successfully logged!" << std::endl;
	}
	else if (Game::getLoggedPlayer() != nullptr)
	{
		ThemeManager::getInstance().changeTheme(Game::getTheme());
		system("cls");
		std::cout << "Player " << username << " successfully logged!" << std::endl;
		//if the player has no money - the game gives him
		if (Game::getLoggedPlayer()->getAllHeroes().size() == 0
			&& Game::getHeroesFromMarketCount() != 0)
		{
			double cheapestHeroPrice = Game::getCheapestHeroPrice();
			double playersMoney = Game::getLoggedPlayer()->getMoney();
			if (playersMoney < cheapestHeroPrice)
			{
				Game::getLoggedPlayer()->changeMoney(cheapestHeroPrice - playersMoney);
				std::cout << "You does not have enough money! The kings made you a present, giving you "
					<< cheapestHeroPrice - playersMoney << "$!" << std::endl;
				std::cout << "Spend them for your first hero, before someone steal it from you!" << std::endl;
			}
		}
	}
	else
	{
		system("cls");
		ThemeManager::getInstance().changeTheme(Theme::ErrorMessage);
		std::cout << "User " << username << " does not exist in the system! ";
		ThemeManager::getInstance().changeTheme(Theme::Default);
	}
}
Command* LogInCommand::clone() const
{
	return new LogInCommand(*this);
}
CommandType LogInCommand::getType() const
{
	return CommandType::LogIn;
}

void ExitApplication::execute()
{
	system("cls");
	std::cout << "Goodbye..";
	for (size_t i = 0; i < 6; i++)
	{
		Sleep(300);
		std::cout << ".";
	}
	std::cout << std::endl;
}
Command* ExitApplication::clone() const
{
	return new ExitApplication(*this);
}
CommandType ExitApplication::getType() const
{
	return CommandType::ExitApp;
}

void AdminDialog::execute()
{
	MenuGenerator::ShowAdminMenu();
}
Command* AdminDialog::clone() const
{
	return new AdminDialog(*this);
}
CommandType AdminDialog::getType() const
{
	return CommandType::AdminDialog;
}

void PlayerDialog::execute()
{
	MenuGenerator::ShowPlayerDialog();
}
Command* PlayerDialog::clone() const
{
	return new PlayerDialog(*this);
}
CommandType PlayerDialog::getType() const
{
	return CommandType::PlayerDialog;
}

void PlayersInfoPlayer::execute()
{
	MenuGenerator::ShowPlayersInfoPlayer(Game::getAllPlayersData, false);
}
Command* PlayersInfoPlayer::clone() const
{
	return new PlayersInfoPlayer(*this);
}
CommandType PlayersInfoPlayer::getType() const
{
	return CommandType::PlayersInfoPlayer;
}

void BackCommand::execute()
{
	system("cls");
}
Command* BackCommand::clone()const
{
	return new BackCommand(*this);
}
CommandType BackCommand::getType()const
{
	return CommandType::Back;
}

void ChooseTypeRanklist::execute()
{
	MenuGenerator::ShowRanklistMenu();
}
Command* ChooseTypeRanklist::clone() const
{
	return new ChooseTypeRanklist(*this);
}
CommandType ChooseTypeRanklist::getType()const
{
	return CommandType::ChooseTypeRanklist;
}

static void printAlignment(size_t countIntervals)
{
	for (size_t i = 0; i < countIntervals; i++)
	{
		std::cout << " ";
	}
}
void TopThreePlayers::execute()
{
	std::cout << "----Top three players----" << std::endl;
	const vector<Game::PlayerScore>* playersOrder = Game::getPlayersInRanklist();
	size_t printedTextLengths[3]{ 0 };
	size_t i = 0;
	for (; i < playersOrder->size(); i++)
	{
		switch (i)
		{
		case 0:
		{
			printAlignment(20);
			ThemeManager::getInstance().changeTheme(Theme::FirstPlace);

			std::cout << i + 1 << ". " << (*playersOrder)[i].player->getUsername()
				<< ": score - " << (*playersOrder)[i].score;

			printedTextLengths[i] = strlen((*playersOrder)[i].player->getUsername().c_str()) + 13;
			ThemeManager::getInstance().changeTheme(Theme::Default);
			std::cout << std::endl;
		}
		break;
		case 1:
		{
			printAlignment(12);
			ThemeManager::getInstance().changeTheme(Theme::SecondPlace);

			printedTextLengths[i] = strlen((*playersOrder)[i].player->getUsername().c_str()) + 13;
			int freeSpace = 16 + printedTextLengths[i - 1];
			int spaceFromBothSides = (freeSpace - printedTextLengths[i]) / 2;
			printedTextLengths[i] += spaceFromBothSides * 2;
			printAlignment(spaceFromBothSides);
			std::cout << i + 1 << ". " << (*playersOrder)[i].player->getUsername()
				<< ": score - " << (*playersOrder)[i].score;
			printAlignment(spaceFromBothSides);


			ThemeManager::getInstance().changeTheme(Theme::Default);
			std::cout << std::endl;
		}
		break;
		case 2:
		{
			printAlignment(4);
			ThemeManager::getInstance().changeTheme(Theme::ThirdPlace);
			printedTextLengths[i] = strlen((*playersOrder)[i].player->getUsername().c_str()) + 13;
			int freeSpace = 16 + printedTextLengths[i - 1];
			int spaceFromBothSides = (freeSpace - printedTextLengths[i]) / 2;
			printAlignment(spaceFromBothSides);
			std::cout << i + 1 << ". " << (*playersOrder)[i].player->getUsername()
				<< ": score - " << (*playersOrder)[i].score;
			printAlignment(spaceFromBothSides);
			ThemeManager::getInstance().changeTheme(Theme::Default);
			std::cout << std::endl;
		}
		break;
		default:
			break;
		}
	}
	ThemeManager::getInstance().changeTheme(Game::getTheme());
	delete playersOrder;
	if (i == 0)
	{
		std::cout << "No players in the system!" << std::endl;
	}
	else if (i < 3)
	{
		std::cout << "No more players! Only " << i << std::endl;
	}
	std::cout << "Enter any key for back: ";
}
Command* TopThreePlayers::clone() const
{
	return new TopThreePlayers(*this);
}
CommandType TopThreePlayers::getType()const
{
	return CommandType::TopThreePlayers;
}

void GlobalClassation::execute()
{
	std::cout << "----Global classation----" << std::endl;
	const vector<Game::PlayerScore>* playersOrder = Game::getPlayersInRanklist();
	size_t i = 0;
	for (; i < playersOrder->size(); i++)
	{
		std::cout << i + 1 << ". " << (*playersOrder)[i].player->getUsername()
			<< ": score - " << (*playersOrder)[i].score << std::endl;
	}
	delete playersOrder;
	if (i == 0)
	{
		std::cout << "No players in the system!" << std::endl;
	}
	std::cout << "Enter any key for back: ";
}
Command* GlobalClassation::clone() const
{
	return new GlobalClassation(*this);
}
CommandType GlobalClassation::getType()const
{
	return CommandType::GlobalClassation;
}

void PersonalData::execute()
{
	MenuGenerator::ShowPersonalData(Game::getLoggedPlayer());
}
Command* PersonalData::clone() const
{
	return new PersonalData(*this);
}
CommandType PersonalData::getType()const
{
	return CommandType::PersonalData;
}

void GoToMarket::execute()
{
	MenuGenerator::ShowMarket(Game::getHeroesFromMarket);
	if (Game::getHeroesFromMarketCount() != 0)
	{
		MenuGenerator::ShowMarketMenu();
	}
}
Command* GoToMarket::clone()const
{
	return new GoToMarket(*this);
}
CommandType GoToMarket::getType()const
{
	return CommandType::Market;
}

void BuyHero::execute()
{
	MenuGenerator::ShowBuyHeroMenu(Game::getHeroesFromMarket, Game::getLoggedPlayer()->getMoney());
}
Command* BuyHero::clone() const
{
	return new BuyHero(*this);
}
CommandType BuyHero::getType()const
{
	return CommandType::BuyHero;
}

void ViewPlayerHeroes::execute()
{
	unsigned playerId = Game::getLoggedPlayer()->getId();
	MenuGenerator::ShowPlayerHeroes(Game::getAllPlayerHeroes, Game::getPlayerHeroesCount(playerId), playerId);
}
Command* ViewPlayerHeroes::clone() const
{
	return new ViewPlayerHeroes(*this);
}
CommandType ViewPlayerHeroes::getType()const
{
	return CommandType::ViewPlayerHeroes;
}

void ChooseHeroToUpgrade::execute()
{
	unsigned playerId = Game::getLoggedPlayer()->getId();
	MenuGenerator::ShowChooseHeroToUpgradeMenu(Game::getAllPlayerHeroes, playerId);
}
Command* ChooseHeroToUpgrade::clone() const
{
	return new ChooseHeroToUpgrade(*this);
}
CommandType ChooseHeroToUpgrade::getType()const
{
	return CommandType::ChooseHeroToUpgrade;
}

void UpgradeHero::execute()
{
	//here we get the hero from the player's list, because it is upgraded. The hero in Game is always the same
	MenuGenerator::ShowUpgradeHeroMenu(Game::getHeroToPlayWith()->getHeroName(),
		&Game::getLoggedPlayer()->getHeroByName(Game::getHeroToPlayWith()->getHeroName()),
		Game::getLoggedPlayer()->getMoney(),
		Game::generateHeroUpgradeTax(Game::getHeroToPlayWith()->getId()));
}
Command* UpgradeHero::clone() const
{
	return new UpgradeHero(*this);
}
CommandType UpgradeHero::getType()const
{
	return CommandType::UpgradeHero;
}

void VerifyUpgradeHero::execute()
{
	double costUpgration = Game::generateHeroUpgradeTax(Game::getHeroToPlayWith()->getId());
	unsigned powerToBeAdded = DefaultValues::UPGRADE_POWER_POINTS_AMMOUNT;

	if (Game::getLoggedPlayer()->getMoney() < costUpgration)
	{
		ThemeManager::getInstance().changeTheme(Theme::ErrorMessage);
	std:cout << "You do not have enough money to add " << powerToBeAdded << " stamina to " <<
		Game::getHeroToPlayWith()->getHeroName() << std::endl;
	ThemeManager::getInstance().changeTheme(Theme::Default);
	std::cout << "Win some battles and come later..." << std::endl;
	}
	else
	{
		try
		{
			Game::getLoggedPlayer()->upgradeHero(Game::getHeroToPlayWith()->getHeroName(), powerToBeAdded);
		}
		catch (const std::invalid_argument& ex)
		{
			std::cout << ex.what() << std::endl;
			std::cout << "Press any key for back: ";
			return;
		}
		Game::getLoggedPlayer()->changeMoney(-costUpgration);
		Game::increaseCountUpgradesOfHero(Game::getHeroToPlayWith()->getId());
		std::cout << "Hero successfully upgraded! Added " << powerToBeAdded << " more stamina!" << std::endl;
	}
}
Command* VerifyUpgradeHero::clone() const
{
	return new VerifyUpgradeHero(*this);
}
CommandType VerifyUpgradeHero::getType()const
{
	return CommandType::VerifyUpgradeHero;
}

void LogOut::execute()
{
	User* userToLogOut = nullptr;
	if (Game::getLoggedAdmin())
	{
		userToLogOut = Game::getLoggedAdmin();
	}
	else
	{
		userToLogOut = Game::getLoggedPlayer();
	}
	Game::logOut();
	ThemeManager::getInstance().changeTheme(Theme::Default);
	system("cls");
	std::cout << "User " << userToLogOut->getUsername() << " successfully log out!" << std::endl;
}
Command* LogOut::clone() const
{
	return new LogOut(*this);
}
CommandType LogOut::getType()const
{
	return CommandType::LogOut;
}

void SettingsPlayer::execute()
{
	MenuGenerator::ShowSettingsPlayer();
}
Command* SettingsPlayer::clone() const
{
	return new SettingsPlayer(*this);
}
CommandType SettingsPlayer::getType()const
{
	return CommandType::SettingsPlayer;
}

void ChooseTheme::execute()
{
	MenuGenerator::ShowThemes();
}
Command* ChooseTheme::clone() const
{
	return new ChooseTheme(*this);
}
CommandType ChooseTheme::getType()const
{
	return CommandType::ChooseTheme;
}

void ChangeTheme::execute()
{
	ThemeManager::getInstance().changeTheme(Game::getTheme());
	system("cls");
	std::cout << "Theme successfully changed with ";
	ThemeManager::getInstance().printThemeName(Game::getTheme());
	std::cout << " theme!" << std::endl;
}
Command* ChangeTheme::clone() const
{
	return new ChangeTheme(*this);
}
CommandType ChangeTheme::getType()const
{
	return CommandType::ChangeTheme;
}

void QuickBattle::execute()
{
	std::cout << "----Quick battle----" << std::endl;
	Game::addAllPlayersInBattle();
	Game::setBattle();

	if (Game::getBattleStatistics().getCount() == 0 ||
		(Game::getBattleStatistics().getBattleStatistics()->result != BattleResult::BattleStopped &&
			Game::getBattleStatistics().getBattleStatistics()->result != BattleResult::NoAvailablePlayers))
	{
		std::cout << "***********************************************" << std::endl;
		std::cout << "************* Battle started! ****************" << std::endl;
		std::cout << "***********************************************" << std::endl;
		std::cout << std::endl;
		std::cout << "Wait until the battle ends..";
		for (size_t i = 0; i < 12; i++)
		{
			Sleep(300);
			std::cout << ".";
		}
		system("cls");
	}
	Game::executeBattle();
	Game::getBattleResults();
	Game::clearPlayersFromBattle();
	std::cout << "Enter any key for back: ";
}
Command* QuickBattle::clone() const
{
	return new QuickBattle(*this);
}
CommandType QuickBattle::getType()const
{
	return CommandType::QuickBattle;
}

void LeagueBattle::execute()
{
	std::cout << "----League battle----" << std::endl;
	std::cout << "";

	if (Game::getPlayersInBattle().size() <= 1)
	{
		std::cout << "You are alone in the league! Search for opponents!" << std::endl;
		std::cout << "Enter any key for back: ";
		return;
	}

	std::cout << "League starting with " << Game::getPlayersInBattle().size() << " players! Good luck!" << std::endl;
	std::cout << "Starting..";
	for (size_t i = 0; i < 8; i++)
	{
		Sleep(300);
		std::cout << "..";
	}
	std::cout << std::endl;

	ThemeManager::getInstance().changeTheme(Theme::Default);

	for (size_t i = 0; i < DefaultValues::ROUNDS_IN_LEAGUE; i++)
	{
		std::cout << "Round " << i + 1 << std::endl;
		for (size_t j = 0; j < Game::getPlayersInBattle().size(); j++)
		{
			std::cout << "Turn to: " << Game::getPlayersInBattle()[j]->getUsername() << std::endl;
			Game::setAttackingPlayer(Game::getPlayersInBattle()[j]->getUsername());
			Game::setBattle();

			Game::executeBattle();
			std::cout << "Your turn has ended!" << std::endl;
		}
		std::cout << "Round " << i + 1 << " ended! Time to show the results from the round...." << std::endl;
		std::cout << std::endl;
		for (size_t i = 0; i < Game::getPlayersInBattle().size(); i++)
		{
			Game::getBattleResults();
		std:cout << "****************************************" << std::endl;
		}

		std::cout << "Each player receives " << DefaultValues::MONEY_PER_ROUND_LEAGUE << "$ from this round!" << std::endl;
		Game::receiveMoneyFromLeague();

		if (i < DefaultValues::ROUNDS_IN_LEAGUE - 1)
		{
			std::cout << "Ready for next round? Enter any key: ";
			char input[1024];
			std::cin.getline(input, 1024);
			system("cls");
		}
		else
		{
			Game::clearPlayersFromBattle();
			std::cout << "League ended!" << std::endl;
		}
	}

	ThemeManager::getInstance().changeTheme(Game::getTheme());

	std::cout << "Enter any key for back: ";
}
Command* LeagueBattle::clone() const
{
	return new LeagueBattle(*this);
}
CommandType LeagueBattle::getType()const
{
	return CommandType::LeagueBattle;
}

void LogInForLeague::execute()
{
	std::cout << "----League menu----" << std::endl;
	Game::addPlayerInBattle(Game::getLoggedPlayer()->getId());
	std::cout << "By now " << Game::getPlayersInBattle().size() << " players are in the league!" << std::endl;
	std::cout << std::endl;

	//check if no other players
	if (Game::getPlayersCount() == 1)
	{
		std::cout << "No other players available! Try again later!" << std::endl;
		return;
	}

	std::cout << "Searching for opponents...." << std::endl;
	std::cout << std::endl;

	std::cout << "----Log in----" << std::endl;
	std::cout << "Enter username: ";
	MyString username;
	std::cin >> username;
	std::cout << "Enter password: ";
	MyString password;
	std::cin >> password;
	system("cls");

	const Player* loggedPlayer = Game::getPlayerByUsername(username);
	if (loggedPlayer == nullptr)
	{
		ThemeManager::getInstance().changeTheme(Theme::ErrorMessage);
		std::cout << "Unexisting player!" << std::endl;
		ThemeManager::getInstance().changeTheme(Theme::Default);
	}
	else if (strcmp(loggedPlayer->getPassword().c_str(), password.c_str()) != 0)
	{
		ThemeManager::getInstance().changeTheme(Theme::ErrorMessage);
		std::cout << "Wrong password!" << std::endl;
		ThemeManager::getInstance().changeTheme(Theme::Default);
	}
	else
	{
		//first we check if the player is not already in the league
		const vector<const Player*> playersInBattle = Game::getPlayersInBattle();
		bool alreadyInTheLeague = false;
		for (size_t i = 0; i < playersInBattle.size(); i++)
		{
			if (playersInBattle[i]->getId() == loggedPlayer->getId())
			{
				std::cout << username << " already in the league!" << std::endl;
				alreadyInTheLeague = true;
				break;
			}
		}
		if (!alreadyInTheLeague)
		{
			//check for heroes!
			if (loggedPlayer->getAllHeroes().size() == 0)
			{
				std::cout << username << " cannot fight in the league! He does not have any heroes!" << std::endl;
			}
			else
			{
				Game::addPlayerInBattle(loggedPlayer->getId());
				std::cout << "Player " << username << " successfully logged! He is ready for battle!" << std::endl;
			}
		}
	}
}
Command* LogInForLeague::clone() const
{
	return new LogInForLeague(*this);
}
CommandType LogInForLeague::getType()const
{
	return CommandType::LogInForLeague;
}

void LeagueBattleSetting::execute()
{
	MenuGenerator::ShowLeagueMenu();
}
Command* LeagueBattleSetting::clone() const
{
	return new LeagueBattleSetting(*this);
}
CommandType LeagueBattleSetting::getType()const
{
	return CommandType::LeagueBattleSetting;
}

void AddAdmin::execute()
{
	std::cout << "----Add admin----" << std::endl;
	std::cout << "Enter first name:";
	MyString firstName;
	std::cin >> firstName;
	std::cout << "Enter last name:";
	MyString lastName;
	std::cin >> lastName;
	std::cout << "Enter email:";
	MyString email;
	std::cin >> email;
	std::cout << "Enter username:";
	MyString username;
	std::cin >> username;
	std::cout << "Enter password:";
	MyString password;
	std::cin >> password;
	const Admin* admin = Game::getAdminByUsername(username);
	const Player* player = Game::getPlayerByUsername(username);
	system("cls");
	if (admin == nullptr && player == nullptr)
	{
		Game::addAdmin(firstName, lastName, email, username, password);
		std::cout << "Admin successfully added!" << std::endl;
	}
	else
	{
		std::cout << "User " << username << " already exists!" << std::endl;
	}

}
Command* AddAdmin::clone() const
{
	return new AddAdmin(*this);
}
CommandType AddAdmin::getType()const
{
	return CommandType::AddAdmin;
}

void AddPlayer::execute()
{
	std::cout << "----Add Player----" << std::endl;
	std::cout << "Enter first name:";
	MyString firstName;
	std::cin >> firstName;
	std::cout << "Enter last name:";
	MyString lastName;
	std::cin >> lastName;
	std::cout << "Enter email:";
	MyString email;
	std::cin >> email;
	std::cout << "Enter username:";
	MyString username;
	std::cin >> username;
	std::cout << "Enter password:";
	MyString password;
	std::cin >> password;
	const Admin* admin = Game::getAdminByUsername(username);
	const Player* player = Game::getPlayerByUsername(username);
	system("cls");
	if (admin == nullptr && player == nullptr)
	{
		try
		{
			Game::addPlayer(firstName, lastName, email, username, password);
		}
		catch (const std::invalid_argument& ex)
		{
			std::cout << "Try again!" << std::endl;
			return;
		}

		std::cout << "Player successfully added!" << std::endl;
	}
	else
	{
		std::cout << "User " << username << " already exists!" << std::endl;
	}
}
Command* AddPlayer::clone() const
{
	return new AddPlayer(*this);
}
CommandType AddPlayer::getType()const
{
	return CommandType::AddPlayer;
}

void DeletePlayer::execute()
{
	std::cout << "----Delete player----" << std::endl;
	Game::getAllPlayersUsernames();

	std::cout << "Enter username: ";
	MyString username;
	std::cin >> username;
	system("cls");
	const Player* player = Game::getPlayerByUsername(username);
	if (player == nullptr)
	{
		ThemeManager::getInstance().changeTheme(Theme::ErrorMessage);
		std::cout << "Unexisting player!" << std::endl;
		ThemeManager::getInstance().changeTheme(Theme::Default);
	}
	else
	{
		std::cout << "Deleted successfully!" << std::endl;
		Game::deletePlayer(player->getId());
	}
}
Command* DeletePlayer::clone() const
{
	return new DeletePlayer(*this);
}
CommandType DeletePlayer::getType()const
{
	return CommandType::DeletePlayer;
}

void PlayersInfo::execute()
{
	std::cout << "----Players info----" << std::endl;
	Game::getAllPlayersData(true);
	std::cout << "Enter any key for back: ";
}
Command* PlayersInfo::clone() const
{
	return new PlayersInfo(*this);
}
CommandType PlayersInfo::getType()const
{
	return CommandType::PlayersInfo;
}

void AdminsInfo::execute()
{
	std::cout << "----Admins info----" << std::endl;
	Game::getAllAdminsData();
	std::cout << "Enter any key for back: ";
}
Command* AdminsInfo::clone() const
{
	return new AdminsInfo(*this);
}
CommandType AdminsInfo::getType()const
{
	return CommandType::AdminsInfo;
}

void AddHero::execute()
{
	std::cout << "----Add Hero----" << std::endl;
	std::cout << "Enter first name: ";
	MyString firstName;
	std::cin >> firstName;
	std::cout << "Enter last name: ";
	MyString lastName;
	std::cin >> lastName;
	std::cout << "Enter heroname: ";
	MyString heroname;
	std::cin >> heroname;
	std::cout << "Power types: " << std::endl;
	std::cout << "1. Earth" << std::endl;
	std::cout << "2. Fire" << std::endl;
	std::cout << "3. Water" << std::endl;
	std::cout << "Enter kind of power(choose index): ";
	MyString kindOfPower;
	std::cin >> kindOfPower;
	Power power;
	if (strcmp(kindOfPower.c_str(), "1") == 0)
	{
		power = Power::earth;
	}
	else if (strcmp(kindOfPower.c_str(), "2") == 0)
	{
		power = Power::fire;
	}
	else if (strcmp(kindOfPower.c_str(), "3") == 0)
	{
		power = Power::water;
	}
	else
	{
		system("cls");
		ThemeManager::getInstance().changeTheme(Theme::ErrorMessage);
		std::cout << "Invalid index!" << std::endl;
		ThemeManager::getInstance().changeTheme(Theme::Default);
		return;
	}
	std::cout << "Enter power points: ";
	MyString inputPoints;
	std::cin >> inputPoints;
	int powerPoints = 0;
	try
	{
		powerPoints = GeneralFunctions::convertStringToNumber(inputPoints);
	}
	catch (const std::invalid_argument& ex)
	{
		system("cls");
		ThemeManager::getInstance().changeTheme(Theme::ErrorMessage);
		std::cout << "Invalid number!" << std::endl;
		ThemeManager::getInstance().changeTheme(Theme::Default);
		return;
	}
	if (powerPoints <= 0)
	{
		system("cls");
		std::cout << "Power points could not be <= 0!" << std::endl;
		return;
	}
	std::cout << "Enter price: ";
	MyString inputPrice;
	std::cin >> inputPrice;
	double price = 0;
	try
	{
		price = GeneralFunctions::convertStringToDouble(inputPrice);
	}
	catch (const std::invalid_argument& ex)
	{
		system("cls");
		ThemeManager::getInstance().changeTheme(Theme::ErrorMessage);
		std::cout << "Price was not a correct floating-point number!" << std::endl;
		ThemeManager::getInstance().changeTheme(Theme::Default);
		return;
	}

	if (price < 0.000001)
	{
		system("cls");
		ThemeManager::getInstance().changeTheme(Theme::ErrorMessage);
		std::cout << "Invalid price! Price shouldn't be <= 0!" << std::endl;
		ThemeManager::getInstance().changeTheme(Theme::Default);
		return;
	}
	const SuperHero* hero = Game::getHeroByHeroname(heroname);
	system("cls");
	if (hero == nullptr)
	{
		Game::addHero(firstName, lastName, heroname, power, powerPoints, price);
		std::cout << "Hero successfully added!" << std::endl;
	}
	else
	{
		std::cout << "Hero " << heroname << " already exists!" << std::endl;
	}
}
Command* AddHero::clone() const
{
	return new AddHero(*this);
}
CommandType AddHero::getType()const
{
	return CommandType::AddHero;
}

void RemoveHero::execute()
{
	std::cout << "----Remove hero----" << std::endl;
	Game::getAllFreeHeroesHeronames();

	std::cout << "Enter heroname: ";
	MyString heroname;
	std::cin >> heroname;
	system("cls");
	const SuperHero* hero = Game::getHeroByHeroname(heroname);
	if (hero == nullptr)
	{
		system("cls");
		ThemeManager::getInstance().changeTheme(Theme::ErrorMessage);
		std::cout << "Unexisting hero!" << std::endl;
		ThemeManager::getInstance().changeTheme(Theme::Default);
		return;
	}
	else
	{
		Game::deleteHero(hero->getId());
	}
}
Command* RemoveHero::clone() const
{
	return new RemoveHero(*this);
}
CommandType RemoveHero::getType()const
{
	return CommandType::RemoveHero;
}
