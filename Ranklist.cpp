#include "Ranklist.h"
#include <iostream>

Ranklist& Ranklist::getInstance()
{
	static Ranklist s;
	return s;
}

unsigned Ranklist::getCountPlayersIn()const
{
	return _playersId.size();
}

void Ranklist::addPlayer(unsigned id, unsigned points)
{
	for (size_t i = 0; i < _playersId.size(); i++)
	{
		if (_ranklist[i] < points)
		{
			_playersId.push_back(_playersId[_playersId.size() - 1]);
			_ranklist.push_back(_playersId[_playersId.size() - 1]);
			for (size_t j = _playersId.size() - 1; j > i; j--)
			{
				_playersId[j] = _playersId[j - 1];
				_ranklist[j] = _ranklist[j - 1];
			}
			_playersId[i] = id;
			_ranklist[i] = points;
			return;
		}
	}
	_playersId.push_back(id);
	_ranklist.push_back(points);
}
void Ranklist::updatePlayer(unsigned id, unsigned points)
{
	bool found = false;
	for (size_t i = 0; i < _playersId.size(); i++)
	{
		if (_playersId[i] == id)
		{
			_ranklist[i] = points;
			size_t indexToGo = _playersId.size() - 1;
			for (size_t j = 0; j < _playersId.size(); j++)
			{
				int a = _ranklist[j];
				if (_ranklist[j] < points)
				{
					indexToGo = j;
					if (indexToGo > i)
					{
						indexToGo = j - 1;
					}
					break;
				}
			}
			if (indexToGo > i)//we downgrade 
			{
				for (size_t j = i; j < indexToGo; j++)
				{
					_playersId[j] = _playersId[j + 1];
					_ranklist[j] = _ranklist[j + 1];
				}
			}
			else if (indexToGo < i)//we upgrade
			{
				for (size_t j = i; j > indexToGo; j--)
				{
					_playersId[j] = _playersId[j - 1];
					_ranklist[j] = _ranklist[j - 1];
				}
			}
			_playersId[indexToGo] = id;
			_ranklist[indexToGo] = points;
			return;
		}
	}
	throw std::invalid_argument("No such player!");
}
vector<unsigned> Ranklist::getRanklistPlayersId() const
{
	return _playersId;
}
vector<unsigned> Ranklist::getRanklistPlayersPoints() const
{
	return _ranklist;
}