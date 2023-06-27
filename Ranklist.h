#pragma once
#include "Vector.hpp"
class Ranklist//singelton
{
	Ranklist() = default;
	vector<unsigned> _playersId;
	vector<unsigned> _ranklist;
public:
	Ranklist(const Ranklist& other) = delete;
	Ranklist& operator=(const Ranklist& other) = delete;
	static Ranklist& getInstance();

	unsigned getCountPlayersIn()const;
	void addPlayer(unsigned id, unsigned points);
	void updatePlayer(unsigned id, unsigned points);
	vector<unsigned> getRanklistPlayersId() const;
	vector<unsigned> getRanklistPlayersPoints() const;
};