#include "CommandFactory.h"
#include "Commands.h"
#include <iostream>
#include "MenuGenerator.h"
#include "Game.h"
#include "ThemeManager.h"
#include "GeneralFunctions.h"

CommandFactory& CommandFactory::getInstance()
{
	static CommandFactory cf;
	return cf;
}

Command* CommandFactory::getCommand(CommandType type) const
{
	if (type == CommandType::StartUp)
	{
		MyString input;
		std::cin >> input;
		system("cls");

		int n = GeneralFunctions::convertStringToNumber(input);
		switch (n)
		{
		case 1:
			return new LogInCommand();
		case 2:
			return new ExitApplication();
		default:
			return new WrongInputCommand();
		}
	}
	else if (type == CommandType::LogIn)
	{
		if (Game::getLoggedAdmin() != nullptr)
		{
			return new AdminDialog();
		}
		else if (Game::getLoggedPlayer() != nullptr)
		{
			return new PlayerDialog();
		}
		else
			return new WrongInputCommand();
	}
	else if (type == CommandType::AdminDialog)
	{
		MyString input;
		std::cin >> input;
		system("cls");

		int n = GeneralFunctions::convertStringToNumber(input);
		switch (n)
		{
		case 1:
			return new AddAdmin();
		case 2:
			return new AddPlayer();
		case 3:
			return new DeletePlayer();
		case 4:
			return new PlayersInfo();
		case 5:
			return new AdminsInfo();
		case 6:
			return new AddHero();
		case 7:
			return new RemoveHero();
		case 8:
			return new LogOut();
		default:
			return new WrongInputCommand();
			break;
		}
	}
	else if (type == CommandType::PlayerDialog)
	{
		MyString input;
		std::cin >> input;
		system("cls");

		int n = GeneralFunctions::convertStringToNumber(input);
		switch (n)
		{
		case 1:
			if (Game::getPlayerHeroesCount(Game::getLoggedPlayer()->getId()) == 0)
			{
				std::cout << "Cannot play battles until you have a hero in your army!" << std::endl;
				return new WrongInputCommand();
			}
			Game::getBattleStatistics().setTypeOfBattle(false);
			return new LeagueBattleSetting();
		case 2:
			if (Game::getPlayerHeroesCount(Game::getLoggedPlayer()->getId()) == 0)
			{
				std::cout << "Cannot play battles until you have a hero in your army!" << std::endl;
				return new WrongInputCommand();
			}
			Game::getBattleStatistics().setTypeOfBattle(true);
			return new QuickBattle();
		case 3:
			return new PlayersInfoPlayer();
		case 4:
			return new ChooseTypeRanklist();
		case 5:
			return new GoToMarket();
		case 6:
			return new ViewPlayerHeroes();
		case 7:
			return new PersonalData();
		case 8:
			return new SettingsPlayer();
		case 9:
			return new LogOut();
		default:
			return new WrongInputCommand();
		}
	}
	else if (type == CommandType::PlayersInfoPlayer)
	{
		char input[1024];
		std::cin.getline(input, 1024);
		system("cls");
		return new BackCommand;
	}
	else if (type == CommandType::PersonalData)
	{
		char input[1024];
		std::cin.getline(input, 1024);;
		system("cls");
		return new BackCommand();
	}
	else if (type == CommandType::ChooseTypeRanklist)
	{
		MyString input;
		std::cin >> input;
		system("cls");

		int n = GeneralFunctions::convertStringToNumber(input);
		switch (n)
		{
		case 1:
			return new TopThreePlayers();
		case 2:
			return new GlobalClassation();
		case 3:
			return new BackCommand();
		default:
			return new WrongInputCommand();
			break;
		}
	}
	else if (type == CommandType::TopThreePlayers || type == CommandType::GlobalClassation)
	{
		char input[1024];
		std::cin.getline(input, 1024);
		system("cls");
		return new BackCommand();
	}
	else if (type == CommandType::Market)
	{
		if (Game::getHeroesFromMarketCount() == 0)
		{
			std::cout << "Press any key for back: ";
			char input[1024];
			std::cin.getline(input, 1024);
			system("cls");
			return new BackCommand();
		}
		MyString input;
		std::cin >> input;
		system("cls");

		int n = GeneralFunctions::convertStringToNumber(input);
		switch (n)
		{
		case 1:
			return new BuyHero();
		case 2:
			return new BackCommand();
		default:
			return new WrongInputCommand();
		}
	}
	else if (type == CommandType::BuyHero)
	{
		MyString heroname;
		std::cin >> heroname;
		system("cls");
		if (strcmp(heroname.c_str(), "none") == 0)
		{
			return new BackCommand();
		}
		const SuperHero* hero = Game::getHeroByHeroname(heroname);
		if (hero == nullptr || !Game::isHeroFree(hero->getId()))
		{
			return new WrongInputCommand();
		}
		else
		{
			if (Game::getLoggedPlayer()->getMoney() < hero->getPrice())
			{
				std::cout << "Not enough money! Play some more battles and come again!" << std::endl;
				return new WrongInputCommand();
			}
			else
			{
				Game::getLoggedPlayer()->changeMoney(-hero->getPrice());
				Game::getLoggedPlayer()->addNewHero(*hero);
				std::cout << heroname << " successfully bought!" << std::endl;
				return new BackCommand();
			}
		}

	}
	else if (type == CommandType::ViewPlayerHeroes)
	{
		if (Game::getPlayerHeroesCount(Game::getLoggedPlayer()->getId()) == 0)
		{
			std::cout << "Press any key for back: ";
			char input[1024];
			std::cin.getline(input, 1024);
			system("cls");
			return new BackCommand();
		}
		MyString input;
		std::cin >> input;
		system("cls");

		int n = GeneralFunctions::convertStringToNumber(input);
		switch (n)
		{
		case 1:
			return new ChooseHeroToUpgrade();
		case 2:
			return new  BackCommand();
		default:
			return new WrongInputCommand();
		}
	}
	else if (type == CommandType::ChooseHeroToUpgrade)
	{
		MyString heroname;
		std::cin >> heroname;
		system("cls");

		if (strcmp(heroname.c_str(), "none") == 0)
		{
			Game::removeHeroToPlayWith();
			return new BackCommand();
		}
		//here we use that field in order to keep the user's choice
		try
		{
			Game::setHeroToPlayWith(heroname, Game::getLoggedPlayer()->getId());
		}
		catch (const std::invalid_argument& ex)
		{
			return new WrongInputCommand();
		}
		return new UpgradeHero();
	}
	else if (type == CommandType::UpgradeHero)
	{
		MyString input;
		std::cin >> input;
		system("cls");

		int n = GeneralFunctions::convertStringToNumber(input);
		switch (n)
		{
		case 1:
			return new VerifyUpgradeHero();
		case 2:
			return new BackCommand();
		default:
			return new WrongInputCommand();
		}
	}
	else if (type == CommandType::VerifyUpgradeHero)
	{
		return new BackCommand();
	}
	else if (type == CommandType::SettingsPlayer)
	{
		MyString input;
		std::cin >> input;
		system("cls");

		int n = GeneralFunctions::convertStringToNumber(input);
		switch (n)
		{
		case 1:
			return new ChooseTheme();
		case 2:
			return new BackCommand();
		default:
			return new WrongInputCommand();
		}
	}
	else if (type == CommandType::ChooseTheme)
	{
		MyString input;
		std::cin >> input;
		system("cls");

		int n = GeneralFunctions::convertStringToNumber(input);
		switch (n)
		{
		case 1:
			Game::setTheme(Theme::Harmony);
			return new ChangeTheme();
		case 2:
			Game::setTheme(Theme::Colourful);
			return new ChangeTheme();
		case 3:
			Game::setTheme(Theme::Spring);
			return new ChangeTheme();;
		case 4:
			Game::setTheme(Theme::Default);
			return new ChangeTheme();;
			break;
		case 5:
			return new BackCommand();
		default:
			return new WrongInputCommand();
			break;
		}
	}
	else if (type == CommandType::ChangeTheme)
	{
		return new BackCommand();
	}
	else if (type == CommandType::QuickBattle)
	{
		char input[1024];
		std::cin.getline(input, 1024);
		system("cls");
		return new BackCommand();
	}
	else if (type == CommandType::LeagueBattleSetting)
	{
		MyString input;
		std::cin >> input;
		system("cls");

		int n = GeneralFunctions::convertStringToNumber(input);
		switch (n)
		{
		case 1:
			return new LeagueBattle();
		case 2:
			return new LogInForLeague();
		case 3:
			Game::clearPlayersFromBattle();
			return new BackCommand();
		default:
			return new WrongInputCommand();
			break;
		}
	}
	else if (type == CommandType::LogInForLeague)
	{
		return new BackCommand();
	}
	else if (type == CommandType::LeagueBattle)
	{
		char input[1024];
		std::cin.getline(input, 1024);
		system("cls");
		return new BackCommand();
	}
	else if (type == CommandType::AddAdmin)
	{
		return new BackCommand;
	}
	else if (type == CommandType::AddPlayer)
	{
		return new BackCommand;
	}
	else if (type == CommandType::DeletePlayer)
	{
		return new BackCommand;
	}
	else if (type == CommandType::PlayersInfo)
	{
		char input[1024];
		std::cin.getline(input, 1024);
		system("cls");
		return new BackCommand;
	}
	else if (type == CommandType::AdminsInfo)
	{
		char input[1024];
		std::cin.getline(input, 1024);
		system("cls");
		return new BackCommand;
	}
	else if (type == CommandType::AddHero)
	{
		return new BackCommand;
	}
	else if (type == CommandType::RemoveHero)
	{
		return new BackCommand;
	}
}