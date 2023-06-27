#pragma once
#include "User.h"
#include "Enums.h"

class Admin :public User
{
public:
	Admin() = default;
	Admin(const MyString& firstName, const MyString& lastName, const MyString& email,
		const MyString& username, const MyString& password);

	void getAllPlayersData()const;
	void getPlayerData(const MyString& username)const;
	void getAllAdminsData()const;
	void getAdminData(const MyString& username)const;

	void addPlayer(const MyString& firstName, const MyString& lastName, const MyString& email,
		const MyString& username, const MyString& password);
	void addAdmin(const MyString& firstName, const MyString& lastName, const MyString& email,
		const MyString& username, const MyString& password);
	void addNewHeroToMarket(const MyString& firstName, const MyString& lastName, const MyString& heroName,
		Power kindOfPower, unsigned powerPoints, double price);

	void modifyPriceOfHero(unsigned heroId, double price);

	void deletePlayer(unsigned id);
	void deleteHeroFromMarket(unsigned id);

	void getData() const;
};