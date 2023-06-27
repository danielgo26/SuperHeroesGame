#include "Admin.h"
#include "Player.h"
#include "Game.h"

Admin::Admin(const MyString& firstName, const MyString& lastName, const MyString& email,
	const MyString& username, const MyString& password)
	:User(firstName, lastName, email, username, password, Role::admin) {}

void Admin::addPlayer(const MyString& firstName, const MyString& lastName, const MyString& email,
	const MyString& username, const MyString& password)
{
	Game::addPlayer(firstName, lastName, email, username, password);
}

void Admin::addAdmin(const MyString& firstName, const MyString& lastName, const MyString& email,
	const MyString& username, const MyString& password)
{
	Game::addAdmin(firstName, lastName, email, username, password);
}

void Admin::addNewHeroToMarket(const MyString& firstName, const MyString& lastName, const MyString& heroName,
	Power kindOfPower, unsigned powerPoints, double price)
{
	Game::addHero(firstName, lastName, heroName, kindOfPower, powerPoints, price);
}

void Admin::modifyPriceOfHero(unsigned heroId, double price)
{
	Game::modifyPriceOfHero(heroId, price);
}

void Admin::deletePlayer(unsigned id)
{
	Game::deletePlayer(id);
}
void Admin::deleteHeroFromMarket(unsigned id)
{
	Game::deleteHero(id);
}

void Admin::getAllPlayersData()const
{
	Game::getAllPlayersData(true);
}
void Admin::getPlayerData(const MyString& username)const
{
	const Player* pl = Game::getPlayerByUsername(username);
	pl->getData();
}
void Admin::getAllAdminsData()const
{
	Game::getAllAdminsData();
}
void Admin::getAdminData(const MyString& username)const
{
	const Admin* ad = Game::getAdminByUsername(username);
	ad->getData();
}

void Admin::getData() const
{
	std::cout << "Admin " << getUsername() << std::endl;
	User::getData();
}