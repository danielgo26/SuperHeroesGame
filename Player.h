#pragma once
#include "User.h"
#include "Vector.hpp"
#include "SuperHero.h"
#include "Enums.h"
#include "DefaultStartValues.h"

class Player :public User
{
	vector<SuperHero> _heroes;
	vector<unsigned> _heroPowerPoints;
	double _money = DefaultValues::PLAYER_MONEY;
	unsigned _points = 0;
	int getHeroIndexByName(const MyString& heroName)const;	
public:
	Player() = default;
	Player(const MyString& firstName, const MyString& lastName, const MyString& email,
		const MyString& username, const MyString& password);

	double getMoney()const;
	const SuperHero& getHeroByName(const MyString& name) const;
	const SuperHero& getHeroById(unsigned id)const;
	const vector<SuperHero>& getAllHeroes() const;
	bool containsHero(const MyString& heroName) const;
	unsigned getPoints() const;

	void changeMoney(double amount);
	void changePoints(int points);
	//make a copy, bcs the player can upgrade its own hero, but that does not affect the market
	void addNewHero(const SuperHero newHero);
	void removeHero(unsigned id);
	void upgradeHero(const MyString& heroName, size_t powerToBeAdded);
	void changeHeroTactics(const MyString& heroName, Tactics newTactic);

	void getHeroesData() const;
	void getRestrictedData() const;
	void getRestrictedHeroesData() const;
	void getFullData() const;
	void getAllPlayersData() const;
};