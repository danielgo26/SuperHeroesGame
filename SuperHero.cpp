#include "SuperHero.h"
unsigned SuperHero::idGenerator = 0;

SuperHero::SuperHero(const MyString& firstName, const MyString& lastName, const MyString& heroName,
	Power kindOfPower, unsigned powerPoints, double price, Tactics tactic)
	:_id(idGenerator++), _firstName(firstName), _lastName(lastName), _heroName(heroName), _kindOfPower(kindOfPower),
	_powerPoints(powerPoints), _price(price), _tactic(tactic) {}

unsigned SuperHero::getId() const
{
	return _id;
}
const MyString& SuperHero::getFirstName()const
{
	return _firstName;
}
const MyString& SuperHero::getLastName()const
{
	return _lastName;
}
const MyString& SuperHero::getHeroName()const
{
	return _heroName;
}
Power SuperHero::getKindOfPower() const
{
	return _kindOfPower;
}
unsigned SuperHero::getPowerPoints() const
{
	return _powerPoints;
}
double SuperHero::getPrice()const
{
	return _price;
}
Tactics SuperHero::getTactics() const
{
	return _tactic;
}

void SuperHero::setFirstName(const MyString& firstName)
{
	_firstName = firstName;
}
void SuperHero::setLastName(const MyString& lastName)
{
	_lastName = lastName;
}
void SuperHero::setHeroName(const MyString& heroName)
{
	_heroName = heroName;
}
void SuperHero::setPowerPoints(double powerPoints)
{
	_powerPoints = powerPoints;
}
void SuperHero::setPrice(double price)
{
	_price = price;
}
void SuperHero::changeTactics(Tactics tactic)
{
	_tactic = tactic;
}

void SuperHero::printKindOfPower(Power power)
{
	switch (power)
	{
	case Power::fire:
		std::cout << "Fire";
		break;
	case Power::water:
		std::cout << "Water";
		break;
	case Power::earth:
		std::cout << "Earth";
		break;
	case Power::none:
		std::cout << "None";
		break;
	default:
		break;
	}
}
static void printTactics(Tactics tactic)
{
	switch (tactic)
	{
	case Tactics::attack:
		std::cout << "Attack";
		break;
	case Tactics::defence:
		std::cout << "Defence";
		break;
	case Tactics::none:
		std::cout << "None";
		break;
	default:
		break;
	}
}
void SuperHero::getAllData() const
{
	getPlayerUnspecificData();
	std::cout << "		Power points: " << _powerPoints <<" stamina"<< std::endl;
	std::cout << "		Position: ";
	printTactics(_tactic);
	std::cout << std::endl;
}
void SuperHero::getPlayerUnspecificData()const
{
	std::cout << "	Hero " << _heroName << std::endl;
	std::cout << "		Identity: " << _firstName << " " << _lastName << std::endl;
	std::cout << "		Buyed for " << _price << "$" << std::endl;
	std::cout << "		Power: ";
	printKindOfPower(_kindOfPower);
	std::cout << std::endl;
}
void SuperHero::getMarketData()const
{
	std::cout << "	Hero " << _heroName << std::endl;
	std::cout << "		Identity: " << _firstName << " " << _lastName << std::endl;
	std::cout << "		Power: ";
	printKindOfPower(_kindOfPower);
	std::cout << "  Power points: " << _powerPoints <<" stamina"<< std::endl;
	std::cout << "	Price: " << _price << "$" << std::endl;
}