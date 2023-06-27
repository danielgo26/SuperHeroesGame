#pragma once
#include "MyString.h"
#include "Enums.h"

class SuperHero
{
	static unsigned idGenerator;
	unsigned _id;
	MyString _firstName;
	MyString _lastName;
	MyString _heroName;
	Power _kindOfPower = Power::none;
	unsigned _powerPoints = 0;
	double _price = 0;
	Tactics _tactic = Tactics::none;
	
public:
	SuperHero() = default;
	SuperHero(const MyString& firstName, const MyString& lastName, const MyString& heroName,
		Power kindOfPower, unsigned powerPoints, double price, Tactics tactic);

	unsigned getId() const;
	const MyString& getFirstName()const;
	const MyString& getLastName()const;
	const MyString& getHeroName()const;
	Power getKindOfPower() const;
	unsigned getPowerPoints() const;
	double getPrice()const;
	Tactics getTactics() const;

	void setFirstName(const MyString& firstName);
	void setLastName(const MyString& lastName);
	void setHeroName(const MyString& heroName);
	void setPowerPoints(double powerPoints);
	void setPrice(double price);
	void changeTactics(Tactics tactic);
	static void printKindOfPower(Power power);
	void getAllData() const;
	void getPlayerUnspecificData()const;
	void getMarketData()const;
};