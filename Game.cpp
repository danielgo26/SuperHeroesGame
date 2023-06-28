#include "Game.h"
#include "BattleManager.h"
#include "ThemeManager.h"

vector<Admin> Game::_admins;
vector<Player> Game::_players;
vector<SuperHero> Game::_heroes;
vector<int> Game::_heroesOwners;
vector<unsigned> Game::_countHeroesUpgraded;
Admin* Game::_loggedAdmin = nullptr;
Player* Game::_loggedPlayer = nullptr;
unsigned Game::_heroesInMarketCount = 0;
vector<Theme> Game::_playersCurrThemes;

int Game::getPlayerIndexById(unsigned id)
{
	for (size_t i = 0; i < _players.size(); i++)
	{
		if (_players[i].getId() == id)
		{
			return i;
		}
	}
	return -1;
}
int Game::getAdminIndexById(unsigned id)
{
	for (size_t i = 0; i < _admins.size(); i++)
	{
		if (_admins[i].getId() == id)
		{
			return i;
		}
	}
	return -1;
}
int Game::getHeroIndexById(unsigned id)
{
	for (size_t i = 0; i < _heroes.size(); i++)
	{
		if (_heroes[i].getId() == id)
		{
			return i;
		}
	}
	return -1;
}

void Game::getHeroesFromMarket()
{
	size_t counter = 0;
	std::cout << "****************************************************" << std::endl;
	for (size_t i = 0; i < _heroes.size(); i++)
	{
		if (counter > 0)
		{
			std::cout << "-----------------------------------------------------" << std::endl;
		}
		if (_heroesOwners[i] == -1)
		{
			counter++;
			_heroes[i].getMarketData();
		}
	}
	if (counter == 0)
	{
		ThemeManager::getInstance().changeTheme(Theme::ErrorMessage);
		std::cout << "No heroes in market! Wait until new ones are added!" << std::endl;
		ThemeManager::getInstance().changeTheme(Game::getTheme());
	}
	std::cout << "****************************************************" << std::endl;
	_heroesInMarketCount = counter;
}
unsigned Game::getHeroesFromMarketCount()
{
	return _heroesInMarketCount;
}
void Game::getAllPlayerHeroes(unsigned id)
{
	int indexPlayer = getPlayerIndexById(id);
	if (indexPlayer == -1)
	{
		throw std::invalid_argument("Unexisting player!");
	}
	std::cout << "----Your heroes----" << std::endl;
	_players[indexPlayer].getHeroesData();
}
unsigned Game::getPlayerHeroesCount(unsigned id)
{
	int playerIndex = getPlayerIndexById(id);
	if (playerIndex == -1)
	{
		throw std::invalid_argument("Unexisting player!");
	}
	return _players[playerIndex].getAllHeroes().size();
}

const Player* Game::getPlayerByUsername(const MyString& playerUsername)
{
	for (size_t i = 0; i < _players.size(); i++)
	{
		if (strcmp(_players[i].getUsername().c_str(), playerUsername.c_str()) == 0)
		{
			return &_players[i];
		}
	}
	return nullptr;
}
const Admin* Game::getAdminByUsername(const MyString& adminUsername)
{
	for (size_t i = 0; i < _admins.size(); i++)
	{
		if (strcmp(_admins[i].getUsername().c_str(), adminUsername.c_str()) == 0)
		{
			return &_admins[i];
		}
	}
	return nullptr;
}
const SuperHero* Game::getHeroByHeroname(const MyString& heroname)
{
	for (size_t i = 0; i < _heroes.size(); i++)
	{
		if (strcmp(_heroes[i].getHeroName().c_str(), heroname.c_str()) == 0)
		{
			return &_heroes[i];
		}
	}
	return nullptr;
}
const Player* Game::getPlayerById(unsigned id)
{
	int indexPlayer = getPlayerIndexById(id);
	return (indexPlayer == -1 ? nullptr : &_players[indexPlayer]);
}
const Admin* Game::getAdminById(unsigned id)
{
	int indexAdmin = getAdminIndexById(id);
	return (indexAdmin == -1 ? nullptr : &_admins[indexAdmin]);
}
const SuperHero* Game::getHeroById(unsigned id)
{
	int indexHero = getHeroIndexById(id);
	return (indexHero == -1 ? nullptr : &_heroes[indexHero]);
}
bool Game::isHeroFree(unsigned id)
{
	for (size_t i = 0; i < _heroes.size(); i++)
	{
		if (_heroes[i].getId() == id)
		{
			return _heroesOwners[i] == -1;
		}
	}
	return false;
}

Admin* Game::getLoggedAdmin()
{
	return _loggedAdmin;
}
Player* Game::getLoggedPlayer()
{
	return _loggedPlayer;
}
const SuperHero* Game::getHeroToPlayWith()
{
	return BattleManager::getHeroToPlayWith();
}

unsigned Game::getPlayersCount()
{
	return _players.size();
}
unsigned Game::getAdminsCount()
{
	return _admins.size();
}

void Game::getAllPlayersData(bool isAdmin)
{
	size_t counter = 0;
	if (isAdmin)
	{
		for (size_t i = 0; i < _players.size(); i++)
		{
			_players[i].getFullData();
			counter++;
		}
	}
	else
	{
		for (size_t i = 0; i < _players.size(); i++)
		{
			if (_loggedPlayer->getId() != _players[i].getId())
			{
				_players[i].getRestrictedData();
				counter++;
			}
		}
	}
	if (counter == 0)
	{
		std::cout << "[No other players in the system!]" << std::endl;
	}
}
void Game::getAllAdminsData()
{
	size_t counter = 0;
	for (size_t i = 0; i < _admins.size(); i++)
	{
		if (_loggedAdmin->getId() != _admins[i].getId())
		{
			_admins[i].getData();
			counter++;
		}
	}
	if (counter == 0)
	{
		std::cout << "[No other admins in the system!]" << std::endl;
	}
}

void Game::getAllPlayersUsernames()
{
	std::cout << "--All players--" << std::endl;
	std::cout << "-----------------" << std::endl;
	size_t i = 0;
	for (; i < _players.size(); i++)
	{
		if (i != 0)
		{
			std::cout << "-----------------" << std::endl;
		}
		std::cout << _players[i].getUsername() << std::endl;
	}
	if (i == 0)
	{
		std::cout << "[No players in the system]" << std::endl;
	}
	std::cout << "-----------------" << std::endl;
}
void Game::getAllFreeHeroesHeronames()
{
	bool count = 0;
	std::cout << "--Free heroes--" << std::endl;
	std::cout << "-----------------" << std::endl;
	for (size_t i = 0; i < _heroes.size(); i++)
	{
		if (i != 0 && count > 0)
		{
			std::cout << "-----------------" << std::endl;
		}
		if (_heroesOwners[i] == -1)
		{
			count++;
			std::cout << _heroes[i].getHeroName() << std::endl;
		}
	}
	if (count == 0)
	{
		std::cout << "[no free heroes]" << std::endl;
	}
	std::cout << "-----------------" << std::endl;
}

BattleStatistics& Game::getBattleStatistics()
{
	return BattleManager::getBattleStatistics();
}

void Game::addPlayerInBattle(unsigned id)
{
	BattleManager::addPlayerInBattle(id);
}
void Game::addAllPlayersInBattle()
{
	for (size_t i = 0; i < _players.size(); i++)
	{
		BattleManager::addPlayerInBattle(_players[i].getId());
	}
}
void Game::removePlayerFromBattle(unsigned id)
{
	BattleManager::removePlayerFromBattle(id);
}
const vector<const Player*>& Game::getPlayersInBattle()
{
	return BattleManager::getPlayersInBattle();
}

void Game::receiveMoneyFromLeague()
{
	for (size_t i = 0; i < BattleManager::getPlayersInBattle().size(); i++)
	{
		int currPlayerId = BattleManager::getPlayersInBattle()[i]->getId();
		_players[getPlayerIndexById(currPlayerId)].changeMoney(DefaultValues::MONEY_PER_ROUND_LEAGUE);
	}
}
double Game::getCheapestHeroPrice()
{
	if (getHeroesFromMarketCount() == 0)
	{
		return 0;
	}
	double cheapestHeroPrice = INT32_MAX;
	for (size_t i = 0; i < _heroes.size(); i++)
	{
		if (_heroesOwners[i] == -1 && cheapestHeroPrice > _heroes[i].getPrice())
		{
			cheapestHeroPrice = _heroes[i].getPrice();
		}
	}
	return cheapestHeroPrice;
}

void Game::setHeroToPlayWith(const MyString& heroname, unsigned loggedPlayerId)
{
	const SuperHero* heroFromGame = getHeroByHeroname(heroname);
	if (heroFromGame == nullptr
		|| _heroesOwners[getHeroIndexById(heroFromGame->getId())] != loggedPlayerId)
	{
		throw std::invalid_argument("Unexisting hero!");
	}
	const SuperHero* heroFromPlayer = &getPlayerById(loggedPlayerId)->getHeroByName(heroname);
	BattleManager::setHeroToPlayWith(heroFromPlayer);
}
void Game::setAttackingPlayer(const MyString& username)
{
	const Player* player = getPlayerByUsername(username);
	if (player == nullptr)
	{
		throw std::invalid_argument("Unexisting player!");
	}
	for (size_t i = 0; i < BattleManager::getPlayersInBattle().size(); i++)
	{
		if (BattleManager::getPlayersInBattle()[i]->getId() == player->getId())
		{
			BattleManager::setAttackingPlayer(&_players[Game::getPlayerIndexById(player->getId())]);
			return;
		}
	}
	throw std::invalid_argument("That player does not take part in the battle!");
}
void Game::setPlayerToAttack(const MyString& username, unsigned loggedPlayerId)
{
	const Player* player = getPlayerByUsername(username);
	if (player == nullptr || player->getId() == loggedPlayerId)
	{
		throw std::invalid_argument("Unexisting player!");
	}
	for (size_t i = 0; i < BattleManager::getPlayersInBattle().size(); i++)
	{
		if (BattleManager::getPlayersInBattle()[i]->getId() == player->getId())
		{
			BattleManager::setPlayerToAttack(&_players[Game::getPlayerIndexById(player->getId())]);
			return;
		}
	}
	throw std::invalid_argument("That player does not take part in the battle!");
}
void Game::setHeroToAttack(const MyString& heroname)
{
	const SuperHero* heroFromGame = getHeroByHeroname(heroname);
	if (heroFromGame == nullptr
		|| _heroesOwners[getHeroIndexById(heroFromGame->getId())] != BattleManager::getPlayerToAttack()->getId())
	{
		throw std::invalid_argument("Unexisting hero!");
	}
	const SuperHero* heroFromPlayer = &BattleManager::getPlayerToAttack()->getHeroByName(heroname);
	BattleManager::setHeroToAttack(heroFromPlayer);
}

void Game::removeHeroToPlayWith()
{
	BattleManager::setHeroToPlayWith(nullptr);
}

Theme Game::getTheme()
{
	if (_loggedPlayer == nullptr)
	{
		return Theme::Default;
	}
	int indexLoggedPlayer = getPlayerIndexById(_loggedPlayer->getId());
	if (indexLoggedPlayer == -1)
	{
		return Theme::Default;
	}
	return _playersCurrThemes[indexLoggedPlayer];
}
void Game::setTheme(Theme theme)
{
	int indexLoggedPlayer = getPlayerIndexById(_loggedPlayer->getId());
	_playersCurrThemes[indexLoggedPlayer] = theme;
}

static bool isUsernameCorrect(const MyString& username)
{
	return strlen(username.c_str()) <= 16;
}
static bool isPasswordCorrect(const MyString& password)
{
	size_t index = 0;
	bool hasCapitalLetter = false;
	bool hasLowerLetter = false;
	bool hasDigit = false;
	while (password[index] != '\0')
	{
		if (password[index] >= 'A' && password[index] <= 'Z')
		{
			hasCapitalLetter = true;
		}
		else if (password[index] >= 'a' && password[index] <= 'z')
		{
			hasLowerLetter = true;
		}
		else if (password[index] >= '0' && password[index] <= '9')
		{
			hasDigit = true;
		}
		index++;
	}
	return hasCapitalLetter && hasLowerLetter && hasDigit;
}
static bool isVerifiedUser(const MyString& username, const MyString& password)
{
	if (!isUsernameCorrect(username))
	{
		ThemeManager::getInstance().changeTheme(Theme::ErrorMessage);
		std::cout << "Incorrect username! Username should be not more than 16 symbols!" << std::endl;
		ThemeManager::getInstance().changeTheme(Theme::Default);
		return false;
	}
	if (!isPasswordCorrect(password))
	{
		ThemeManager::getInstance().changeTheme(Theme::ErrorMessage);
		std::cout << "Incorrect password! Password should contain at least:" << std::endl;
		std::cout << "- 1 capital letter, " << std::endl;
		std::cout << "- 1 lower letter, " << std::endl;
		std::cout << "- 1 digit. " << std::endl;
		ThemeManager::getInstance().changeTheme(Theme::Default);
		return false;
	}
	return true;
}
void Game::addPlayer(const MyString& firstName, const MyString& lastName, const MyString& email,
	const MyString& username, const MyString& password)//check if already existing
{
	if (getPlayerByUsername(username) != nullptr)
	{
		throw std::invalid_argument("That player is already existing!");
	}
	if (!isVerifiedUser(username, password))
		throw std::invalid_argument("Invalid username or password!");

	_players.push_back(Player(firstName, lastName, email, username, password));
	_playersCurrThemes.push_back(Theme::Default);
}
void Game::addAdmin(const MyString& firstName, const MyString& lastName, const MyString& email,
	const MyString& username, const MyString& password)//check if already existing
{
	if (getAdminByUsername(username) != nullptr)
	{
		throw std::invalid_argument("That admin is already existing!");
	}
	_admins.push_back(Admin(firstName, lastName, email, username, password));
}
void Game::addHero(const MyString& firstName, const MyString& lastName, const MyString& heroname,
	Power kindOfPower, unsigned powerPoints, double price)//check if already existing
{
	if (getHeroByHeroname(heroname) != nullptr)
	{
		throw std::invalid_argument("That hero is already existing!");
	}
	_heroes.push_back(SuperHero(firstName, lastName, heroname, kindOfPower, powerPoints, price, Tactics::none));
	_heroesOwners.push_back(-1);
	_countHeroesUpgraded.push_back(0);
	_heroesInMarketCount++;
}
void Game::addHeroOwner(unsigned heroId, unsigned ownerId)
{
	int heroIndex = getHeroIndexById(heroId);
	if (getPlayerIndexById(ownerId) == -1)
	{
		throw std::invalid_argument("Unexisting player!");
	}
	if (heroIndex == -1)
	{
		throw std::invalid_argument("Unexisting hero!");
	}
	if (_heroesOwners[heroIndex] != -1)
	{
		throw std::invalid_argument("The hero is already taken!");
	}
	_heroesInMarketCount--;
	_heroesOwners[heroIndex] = ownerId;
}

void Game::modifyPriceOfHero(unsigned id, double newPrice)//only these in market
{
	int heroIndex = getHeroIndexById(id);
	if (heroIndex == -1)
	{
		throw std::invalid_argument("Unexisting hero!");
	}
	if (_heroesOwners[heroIndex] != -1)
	{
		throw std::invalid_argument("That hero is already bought!");
	}
	_heroes[heroIndex].setPrice(newPrice);
}

double Game::generateHeroUpgradeTax(unsigned indexHero)
{
	int indexHeroToUpgrade = getHeroIndexById(indexHero);
	if (indexHeroToUpgrade == -1)
	{
		throw std::invalid_argument("Unexisting hero!");
	}
	double taxForUpgrade = DefaultValues::START_TAX_HERO_UPGRADE
		+ DefaultValues::START_TAX_HERO_UPGRADE
		* _countHeroesUpgraded[indexHeroToUpgrade]
		* DefaultValues::TAX_HERO_UPDATE_KOEF;

	return taxForUpgrade;
}
void Game::increaseCountUpgradesOfHero(unsigned indexHero)
{
	int indexHeroToUpgrade = getHeroIndexById(indexHero);
	if (indexHeroToUpgrade == -1)
	{
		throw std::invalid_argument("Unexisting hero!");
	}
	_countHeroesUpgraded[indexHeroToUpgrade]++;
}
void Game::deletePlayer(unsigned id)
{
	int playerIndex = getPlayerIndexById(id);
	if (playerIndex == -1)
	{
		throw std::invalid_argument("Unexisting player!");
	}
	for (size_t i = 0; i < _heroesOwners.size(); i++)
	{
		if (_heroesOwners[i] == id)
		{
			_heroesOwners[i] = -1;
			_countHeroesUpgraded[i] = 0;
			_heroesInMarketCount++;
		}
	}
	for (size_t i = playerIndex; i < _players.size() - 1; i++)
	{
		_players[i] = _players[i + 1];
		_playersCurrThemes[i] = _playersCurrThemes[i + 1];
	}
	_players.pop_back();
	_playersCurrThemes.pop_back();

}
void Game::deleteAdmin(unsigned id)
{
	int indexAdmin = getAdminIndexById(id);
	if (indexAdmin == -1)
	{
		throw std::invalid_argument("Unexisting admin!");
	}
	for (size_t i = indexAdmin; i < _admins.size() - 1; i++)
	{
		_admins[i] = _admins[i + 1];
	}
	_admins.pop_back();
}
void Game::deleteHero(unsigned id)//only if has no owner!
{
	int heroIndex = getHeroIndexById(id);
	if (heroIndex == -1)
	{
		throw std::invalid_argument("Unexisting hero!");
	}
	if (_heroesOwners[heroIndex] == -1)
	{
		for (size_t i = heroIndex; i < _heroes.size() - 1; i++)
		{
			_heroes[i] = _heroes[i + 1];
			_heroesOwners[i] = _heroesOwners[i + 1];
			_countHeroesUpgraded[i] = _countHeroesUpgraded[i + 1];
		}
		_heroes.pop_back();
		_heroesOwners.pop_back();
		_countHeroesUpgraded.pop_back();
		_heroesInMarketCount--;
		std::cout << "Deleted successfully!" << std::endl;
	}
	else
	{
		std::cout << "Cannot delete " << _heroes[heroIndex].getHeroName() << "!" << std::endl;
		std::cout << "The hero is used by " << getPlayerById(_heroesOwners[heroIndex])->getUsername()
			<< "!" << std::endl;
	}
}
void Game::removeHeroOwner(unsigned heroId)
{
	int heroIndex = getHeroIndexById(heroId);
	if (heroIndex == -1)
	{
		throw std::invalid_argument("Unexisting hero!");
	}
	if (_heroesOwners[heroIndex] != -1)
	{
		_heroesOwners[heroIndex] = -1;
		_countHeroesUpgraded[heroIndex] = 0;
		_heroesInMarketCount++;
	}
}

const vector<Game::PlayerScore>* Game::getPlayersInRanklist()
{
	vector<PlayerScore>* playersScores = new vector<PlayerScore>();
	for (size_t i = 0; i < _players.size(); i++)
	{
		PlayerScore score;
		score.player = &_players[i];
		playersScores->push_back(score);
	}

	for (size_t i = 0; i < playersScores->size() - 1; i++)
	{
		double currPlayerScore = (*playersScores)[i].player->getPoints() * DefaultValues::XP_SCORE_COEF
			+ (*playersScores)[i].player->getMoney() * DefaultValues::MONEY_SORE_COEF;
		(*playersScores)[i].score = currPlayerScore;
		for (size_t j = i + 1; j < _players.size(); j++)
		{
			double nextPlayerScore = (*playersScores)[j].player->getPoints() * DefaultValues::XP_SCORE_COEF
				+ (*playersScores)[j].player->getMoney() * DefaultValues::MONEY_SORE_COEF;
			(*playersScores)[j].score = nextPlayerScore;
			if (currPlayerScore < nextPlayerScore)
			{
				double tmp = (*playersScores)[i].score;
				(*playersScores)[i].player = &_players[j];
				(*playersScores)[i].score = (*playersScores)[j].score;
				(*playersScores)[j].player = &_players[i];
				(*playersScores)[j].score = tmp;
			}
		}
	}
	return playersScores;
}

void Game::setBattle()
{
	BattleManager::setBattle();
}
void Game::executeBattle()
{
	BattleManager::executeBattle();
}
void Game::getBattleResults()
{
	BattleManager::receiveBattleRezults();
}

void Game::clearPlayersFromBattle()
{
	BattleManager::clearPlayersInBattle();
}

void Game::logIn(const MyString username, const MyString password)
{
	for (size_t i = 0; i < _admins.size(); i++)
	{
		if (strcmp(_admins[i].getUsername().c_str(), username.c_str()) == 0
			&& strcmp(_admins[i].getPassword().c_str(), password.c_str()) == 0)
		{
			_loggedAdmin = &_admins[i];
			return;
		}
	}
	for (size_t i = 0; i < _players.size(); i++)
	{
		if (strcmp(_players[i].getUsername().c_str(), username.c_str()) == 0
			&& strcmp(_players[i].getPassword().c_str(), password.c_str()) == 0)
		{
			_loggedPlayer = &_players[i];
			int indexLoggedPlayer = getPlayerIndexById(_loggedPlayer->getId());
			setTheme(_playersCurrThemes[indexLoggedPlayer]);
			return;
		}
	}
}
void Game::logOut()
{
	if (_loggedPlayer)
	{
		_loggedPlayer = nullptr;
	}
	else
	{
		_loggedAdmin = nullptr;
	}

}

Game::~Game()
{
	delete _loggedAdmin;
	delete _loggedPlayer;
}