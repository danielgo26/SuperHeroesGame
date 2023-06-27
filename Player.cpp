#include "Player.h"
#include "Game.h"

Player::Player(const MyString& firstName, const MyString& lastName, const MyString& email,
	const MyString& username, const MyString& password) :
	User(firstName, lastName, email, username, password, Role::player) {}

double Player::getMoney()const
{
	return _money;
}
int Player::getHeroIndexByName(const MyString& heroName)const
{
	for (size_t i = 0; i < _heroes.size(); i++)
	{
		if (strcmp(_heroes[i].getHeroName().c_str(), heroName.c_str()) == 0)
		{
			return i;
		}
	}
	return -1;
}
const SuperHero& Player::getHeroByName(const MyString& name) const
{
	for (size_t i = 0; i < _heroes.size(); i++)
	{
		if (_heroes[i].getHeroName() == name)
		{
			return _heroes[i];
		}
	}
	throw std::invalid_argument("That hero does not exist in this player's list!");
}
const SuperHero& Player::getHeroById(unsigned id)const
{
	for (size_t i = 0; i < _heroes.size(); i++)
	{
		if (_heroes[i].getId() == id)
		{
			return _heroes[i];
		}
	}
	throw std::invalid_argument("That hero does not exist in this player's list!");
}
const vector<SuperHero>& Player::getAllHeroes() const
{
	return _heroes;
}
unsigned Player::getPoints() const
{
	return _points;
}

bool Player::containsHero(const MyString& heroName) const
{
	try
	{
		getHeroByName(heroName);
	}
	catch (const std::invalid_argument& ex)
	{
		return false;
	}
	catch (...)
	{
		return false;
	}
	return true;
}

void Player::changeMoney(double amount)
{
	_money += amount;
	if (_money < 0)
	{
		_money = 0;
	}
}
void Player::changePoints(int points)
{
	if (points < 0 && -points > _points)
		_points = 0;
	else
		_points += points;
}

void Player::addNewHero(const SuperHero newHero)
{
	if (!containsHero(newHero.getHeroName()))
	{
		_heroes.push_back(newHero);
		_heroPowerPoints.push_back(newHero.getPowerPoints());
		Game::addHeroOwner(newHero.getId(), this->getId());
		return;
	}
	throw std::invalid_argument("That hero is already added!");
}
void Player::removeHero(unsigned id)
{
	for (size_t i = 0; i < _heroes.size(); i++)
	{
		if (_heroes[i].getId() == id)
		{
			for (size_t j = i; j < _heroes.size() - 1; j++)
			{
				_heroes[j] = _heroes[j + 1];
				_heroPowerPoints[j] = _heroPowerPoints[j + 1];
			}
			_heroes.pop_back();
			_heroPowerPoints.pop_back();
			Game::removeHeroOwner(id);
			return;
		}
	}
}
void Player::upgradeHero(const MyString& heroName, size_t powerToBeAdded)
{
	int heroIndex = getHeroIndexByName(heroName);
	if (heroIndex == -1)
		throw std::invalid_argument("That hero does not exist in this player's list!");

	unsigned newPowerPoints = _heroes[heroIndex].getPowerPoints() + powerToBeAdded;
	_heroes[heroIndex].setPowerPoints(newPowerPoints);
	_heroPowerPoints[heroIndex] = newPowerPoints;
}

void Player::changeHeroTactics(const MyString& heroName, Tactics newTactic)
{
	int indexHero = getHeroIndexByName(heroName);
	if (indexHero == -1)
		throw std::invalid_argument("That hero does not exist in this player's list!");

	_heroes[indexHero].changeTactics(newTactic);
}

void Player::getHeroesData() const
{
	std::cout << "---------------------------------------" << std::endl;
	if (_heroes.size() == 0)
	{
		std::cout << "[No heroes in the army!]" << std::endl;
	}
	for (size_t i = 0; i < _heroes.size(); i++)
	{
		std::cout << i + 1 << ". ";
		_heroes[i].getPlayerUnspecificData();
		std::cout << "		Power points: " << _heroPowerPoints[i];
		unsigned oldHeroPoints = Game::getHeroByHeroname(_heroes[i].getHeroName())->getPowerPoints();
		if (_heroPowerPoints[i] > oldHeroPoints)
		{
			std::cout << " (upgraded from " << oldHeroPoints << " stamina)";
		}
		std::cout << std::endl;
	}
	std::cout << "---------------------------------------" << std::endl;
}
void Player::getRestrictedData() const
{
	std::cout << "Player " << getUsername() << " :" << std::endl;
	std::cout << "Balance: " << getMoney() << "$" << std::endl;
	std::cout << "Heroes owned" << "(" << _heroes.size() << "):" << std::endl;
	std::cout << "---------------------------------------" << std::endl;
	for (size_t i = 0; i < _heroes.size(); i++)
	{
		std::cout << i + 1 << ". " << _heroes[i].getHeroName() << " - ";
		SuperHero::printKindOfPower(_heroes[i].getKindOfPower());
		std::cout << std::endl;
	}
	std::cout << "---------------------------------------" << std::endl;
}
void Player::getRestrictedHeroesData() const
{
	std::cout << "Heroes owned" << "(" << _heroes.size() << "):" << std::endl;
	std::cout << "---------------------------------------" << std::endl;
	for (size_t i = 0; i < _heroes.size(); i++)
	{
		std::cout << i + 1 << ". " << _heroes[i].getHeroName() << " - ";
		SuperHero::printKindOfPower(_heroes[i].getKindOfPower());
		std::cout << std::endl;
	}
	std::cout << "---------------------------------------" << std::endl;
}
void Player::getFullData() const
{
	std::cout << "Player " << getUsername() << std::endl;
	User::getData();
	std::cout << "Password: " << getPassword() << std::endl;
	std::cout << "Money: " << _money << "$   Points: " << _points << "xp" << std::endl;
	std::cout << "Heroes owned" << "(" << _heroes.size() << "):" << std::endl;
	getHeroesData();
}
void Player::getAllPlayersData() const
{
	Game::getAllPlayersData(false);
}