#include "BattleManager.h"
#include <windows.h>

const SuperHero* BattleManager::_heroToPlayWith = nullptr;
Player* BattleManager::_playerAttacking = nullptr;
Player* BattleManager::_playerToAttack = nullptr;
const SuperHero* BattleManager::_heroToAttack = nullptr;
vector<const Player*> BattleManager::_playersInBattle;
BattleStatistics BattleManager::_battleStatistics;
BattleResult BattleManager::_currBattleResult = BattleResult::Undefined;

const SuperHero* BattleManager::getHeroToPlayWith()
{
	return _heroToPlayWith;
}
Player* BattleManager::getPlayerToAttack()
{
	return _playerToAttack;
}
const SuperHero* BattleManager::getHeroToAttack()
{
	return _heroToAttack;
}
BattleStatistics& BattleManager::getBattleStatistics()
{
	return _battleStatistics;
}

const vector<const Player*>& BattleManager::getPlayersInBattle()
{
	return _playersInBattle;
}

void BattleManager::addStatistics(BattleResult result, Player* attackingPlayer, Player* attackedPlayer,
	const SuperHero* heroToPlayWith, const SuperHero* heroToAttack)
{
	_battleStatistics.addStatistics(result, attackingPlayer, attackedPlayer, heroToPlayWith, heroToAttack);
}

void BattleManager::addPlayerInBattle(unsigned id)
{
	const Player* player = Game::getPlayerById(id);
	if (player != nullptr)
	{
		//check if that player has already been added
		for (size_t i = 0; i < _playersInBattle.size(); i++)
		{
			if (_playersInBattle[i]->getId() == id)
			{
				return;
			}
		}
		_playersInBattle.push_back(player);
		return;
	}
	throw std::invalid_argument("Unexisting player!");
}
void BattleManager::removePlayerFromBattle(unsigned id)
{
	for (size_t i = 0; i < _playersInBattle.size(); i++)
	{
		if (_playersInBattle[i]->getId() == id)
		{
			for (size_t j = i; j < _playersInBattle.size() - 1; j++)
			{
				_playersInBattle[j] = _playersInBattle[j + 1];
			}
			_playersInBattle.pop_back();
			return;
		}
	}
	throw std::invalid_argument("Unexisting player!");
}
void BattleManager::setHeroToPlayWith(const SuperHero* hero)
{
	_heroToPlayWith = hero;
}
void BattleManager::setAttackingPlayer(Player* player)
{
	_playerAttacking = player;
}
void BattleManager::setPlayerToAttack(Player* player)
{
	_playerToAttack = player;
}
void BattleManager::setHeroToAttack(const SuperHero* hero)
{
	_heroToAttack = hero;
}

void BattleManager::getOpponent(MyString& usernameOpp)
{
	if (Game::getPlayersCount() == 1)
	{
		system("cls");
		std::cout << "No other players available!" << std::endl;
		std::cout << "Wait until some more players log in! End of battle!" << std::endl;
		BattleManager::addStatistics(BattleResult::NoAvailablePlayers, _playerAttacking, _playerToAttack,
			nullptr, nullptr);
		_currBattleResult = BattleResult::NoAvailablePlayers;
		return;
	}
	while (true)
	{
		std::cout << "----Opponents---" << std::endl;
		size_t countOpponents = 1;
		for (size_t i = 0; i < BattleManager::getPlayersInBattle().size(); i++)
		{
			if (_playerAttacking->getId() != BattleManager::getPlayersInBattle()[i]->getId())
			{
				std::cout << countOpponents++ << ". "
					<< BattleManager::getPlayersInBattle()[i]->getUsername() << std::endl;
			}
		}
		std::cout << "Choose opponent (\"username\"): ";
		std::cin >> usernameOpp;
		system("cls");
		try
		{
			Game::setPlayerToAttack(usernameOpp, _playerAttacking->getId());
			break;
		}
		catch (const std::invalid_argument& ex)
		{
			system("cls");
			std::cout << "Player " << usernameOpp << " does not exist in the system!" << std::endl;
			std::cout << "Choose player more carefully!" << std::endl;
		}
	}
}
void BattleManager::getOpponentHero(MyString& heronameOpp, const MyString& usernameOpp)
{
	system("cls");
	std::cout << "***********************************************" << std::endl;
	std::cout << "Battle started against " << usernameOpp << "!" << std::endl;
	if (Game::getPlayerByUsername(usernameOpp)->getAllHeroes().size() == 0)
	{
		while (true)
		{
			std::cout << "Opps... Your opponent does not have any heroes!" << std::endl;
			std::cout << "Now he isn't able to defend himself. The battle is almost yours!" << std::endl;
			std::cout << "Here you should choose - show dignity and leave in peace or destroy him...." << std::endl;
			std::cout << "The choice is yours!" << std::endl;
			std::cout << "Enter \"next\" to continue or \"stop\" to end battle: ";
			char input[1024];
			std::cin.getline(input, 1024);
			system("cls");
			if (strcmp(input, "stop") == 0)
			{
				BattleManager::addStatistics(BattleResult::BattleStopped, _playerAttacking, _playerToAttack,
					nullptr, nullptr);
				_currBattleResult = BattleResult::BattleStopped;
				std::cout << "You leave " << usernameOpp << " in peace!" << std::endl;
				return;
			}
			else if (strcmp(input, "next") == 0)
			{
				BattleManager::addStatistics(BattleResult::AttackedPlayerWithoutHeroes, _playerAttacking, _playerToAttack,
					nullptr, nullptr);
				_currBattleResult = BattleResult::AttackedPlayerWithoutHeroes;
				break;
			}
			else
			{
				system("cls");
				std::cout << "Wrong command! Enter again!" << std::endl;
			}
		}
	}
	else
	{
		while (true)
		{
			std::cout << "----Opponent's heroes----" << std::endl;
			Game::getPlayerByUsername(usernameOpp)->getRestrictedHeroesData();
			std::cout << "Choose hero to attack (\"heroname\"): ";
			std::cin >> heronameOpp;
			try
			{
				Game::setHeroToAttack(heronameOpp);
				break;
			}
			catch (const std::invalid_argument& ex)
			{
				system("cls");
				std::cout << usernameOpp << " does not have hero " << heronameOpp << "!" << std::endl;
				std::cout << "Enter heroname more carefully: " << std::endl;
			}
		}
	}
}
void BattleManager::getHeroToAttackWith(MyString& heronameWarrior, const MyString& heronameOpp, const MyString& usernameOpp)
{
	system("cls");
	std::cout << "***********************************************" << std::endl;
	if (Game::getPlayerByUsername(usernameOpp)->getAllHeroes().size() != 0)
	{
		std::cout << "The hero " << heronameOpp << " of "
			<< usernameOpp << " successfully chosen!" << std::endl;
	}

	while (true)
	{
		if (_playerAttacking->getAllHeroes().size() == 0)
		{
			std::cout << "All of your heroes were killed!" << std::endl;
			std::cout << "Your turn is skipped! Be more carefull entering the league next time!" << std::endl;
			BattleManager::addStatistics(BattleResult::CannotBattle, _playerAttacking, _playerToAttack,
				nullptr, _heroToAttack);
			_currBattleResult = BattleResult::CannotBattle;
			return;
		}
		std::cout << "----Choose your warrior----" << std::endl;
		_playerAttacking->getHeroesData();
		std::cout << "Choose a hero to fight with: ";
		std::cin >> heronameWarrior;

		try
		{
			Game::setHeroToPlayWith(heronameWarrior, _playerAttacking->getId());
			std::cout << heronameWarrior << " is getting ready for battle! Wait him..";
			for (size_t i = 0; i < 6; i++)
			{
				Sleep(400);
				std::cout << ".";
			}
			std::cout << std::endl;
			std::cout << heronameWarrior << " is ready for battle! Wish him luck..";
			for (size_t i = 0; i < 4; i++)
			{
				Sleep(400);
				std::cout << ".";
			}
			std::cout << std::endl;
			break;
		}
		catch (const std::invalid_argument& ex)
		{
			system("cls");
			std::cout << "You do NOT have " << heronameWarrior << " in your army!" << std::endl;
			std::cout << "Enter the heroname more carefully!" << std::endl;
		}
	}
	system("cls");
}

void BattleManager::setBattle()
{
	if (_battleStatistics.getIsQuickBattle())
	{
		_playerAttacking = Game::getLoggedPlayer();
	}
	if (_playerAttacking->getAllHeroes().size() == 0)
	{
		std::cout << "All of your heroes were killed!" << std::endl;
		std::cout << "Your turn is skipped! Be more carefull entering the league next time!" << std::endl;
		BattleManager::addStatistics(BattleResult::CannotBattle, _playerAttacking, _playerToAttack,
			nullptr, nullptr);
		_currBattleResult = BattleResult::CannotBattle;
		return;
	}
	MyString usernameOpp, heronameOpp, heronameWarrior;
	getOpponent(usernameOpp);
	if (Game::getPlayersCount() > 1)
	{
		getOpponentHero(heronameOpp, usernameOpp);

		if (_currBattleResult != BattleResult::BattleStopped)
		{
			getHeroToAttackWith(heronameWarrior, heronameOpp, usernameOpp);
		}
	}
}

static Power getDominantPower(Power a, Power b)
{
	if (a == Power::none || b == Power::none)
	{
		throw std::invalid_argument("The hero has no power!");
	}
	if (a == b)
	{
		return Power::none;
	}
	if (a == Power::fire && b == Power::earth
		|| a == Power::earth && b == Power::water
		|| a == Power::water && b == Power::fire)
	{
		return a;
	}
	else
	{
		return b;
	}

}
void BattleManager::executeBattle()
{
	if (_currBattleResult == BattleResult::AttackedPlayerWithoutHeroes)
	{
		_battleStatistics.setNewHeroToPlayWith(_heroToPlayWith);
		BattleManager::getBattleStatistics().addNewPoints(_heroToPlayWith->getPowerPoints(), 0);
	}
	else if (_currBattleResult == BattleResult::BattleStopped
		|| _currBattleResult == BattleResult::NoAvailablePlayers
		|| _currBattleResult == BattleResult::CannotBattle)
	{
		BattleManager::getBattleStatistics().addNewPoints(0, 0);
	}
	//if it is skipped, cannot play, stopped or attacked without heros we have already added them in setBattle
	else if (_battleStatistics.getCount() != 1 || !_battleStatistics.getIsQuickBattle())
	{
		if (_heroToPlayWith == nullptr || _heroToAttack == nullptr)
		{
			return;
		}
		//get the dominant one
		Power dominantPower = getDominantPower(_heroToPlayWith->getKindOfPower(), _heroToAttack->getKindOfPower());
		unsigned competePowerPointsAttacker = _heroToPlayWith->getPowerPoints();
		unsigned competePowerPointsAttacked = _heroToAttack->getPowerPoints();
		if (_heroToPlayWith->getKindOfPower() == dominantPower)
			competePowerPointsAttacker *= 2;
		else if (_heroToAttack->getKindOfPower() == dominantPower)
			competePowerPointsAttacked *= 2;
		BattleManager::getBattleStatistics().addNewPoints(competePowerPointsAttacker, competePowerPointsAttacked);
		//compare powers
		if (competePowerPointsAttacker > competePowerPointsAttacked)
		{
			BattleManager::addStatistics(BattleResult::AttackingPlayerWins, _playerAttacking, _playerToAttack,
				_heroToPlayWith, _heroToAttack);
		}
		else if (competePowerPointsAttacker < competePowerPointsAttacked)
		{
			BattleManager::addStatistics(BattleResult::AttackedPlayerWins, _playerAttacking, _playerToAttack,
				_heroToPlayWith, _heroToAttack);
		}
		else
		{
			BattleManager::addStatistics(BattleResult::EqualPowers, _playerAttacking, _playerToAttack,
				_heroToPlayWith, _heroToAttack);
		}
	}
}

void BattleManager::receiveBattleRezults()
{
	std::cout << "----Battle results----" << std::endl;

	const BattleStatistics::BattleTimeline* battleTimeline = _battleStatistics.removeStatistics();
	BattleResult result = battleTimeline->result;
	int count = Game::getBattleStatistics().getCount();
	Player* currAttackingPlayer = battleTimeline->attacking;
	Player* currAttackedPlayer = battleTimeline->attacked;
	const SuperHero* currHeroToPlayWith = battleTimeline->heroToPlayWith;
	const SuperHero* currHeroToAttack = battleTimeline->heroToAttack;
	unsigned newPointsAttacker;
	unsigned newPointsAttacked;
	newPointsAttacker = _battleStatistics.removeNewPointsAttacker();
	newPointsAttacked = _battleStatistics.removeNewPointsAttacked();

	switch (result)
	{
	case BattleResult::AttackedPlayerWithoutHeroes:
	{
		try
		{
			currAttackingPlayer->getHeroById(currHeroToPlayWith->getId());
		}
		catch (const std::invalid_argument& ex)
		{
			std::cout << "The hero you want to play with was killed by the other players in the league!" << std::endl;
			std::cout << "Summary..........." << std::endl;
			std::cout << "Hero killed!" << std::endl;
			return;
		}
		double differenceMoney = currAttackedPlayer->getMoney() - newPointsAttacker;
		double moneyWon = 0;
		//winner
		if (differenceMoney < 0)
		{
			currAttackingPlayer->changeMoney(currAttackedPlayer->getMoney());//we get all the money
			moneyWon = currAttackedPlayer->getMoney();
		}
		else
		{
			currAttackingPlayer->changeMoney(newPointsAttacker);
			moneyWon = newPointsAttacker;
		}
		//here we remove some xp because we attack an opponent without heroes
		currAttackingPlayer->changePoints(-DefaultValues::LOST_XP_FROM_INDIRECT_BATTLE);
		//loser
		//here we do not remove xp!
		currAttackedPlayer->changeMoney(-(int)newPointsAttacker);
		//battle result
		std::cout << currAttackingPlayer->getUsername() << " wins this battle against "
			<< currAttackedPlayer->getUsername() << "!" << std::endl;
		//summary
		std::cout << "Summary..........." << std::endl;
		std::cout << currAttackingPlayer->getUsername() << " steal " << moneyWon << "$ from " <<
			currAttackedPlayer->getUsername() << std::endl;
		std::cout << "Even though he won the \"battle\" he lose " << DefaultValues::LOST_XP_FROM_INDIRECT_BATTLE
			<< " xp, because he does not show dignity!" << std::endl;
		std::cout << "A great warrior is who knows not how to kill, but when to spare..." << std::endl;
	}
	break;
	case BattleResult::AttackedPlayerWins:
	{
		try
		{
			//if our hero was killed during the round
			currAttackingPlayer->getHeroById(currHeroToPlayWith->getId());
		}
		catch (const std::invalid_argument& ex)
		{
			std::cout << "The hero you want to play with was killed by the other players in the league!" << std::endl;
			std::cout << "Summary..........." << std::endl;
			std::cout << "Hero killed!" << std::endl;
			return;
		}
		try
		{
			//if we attack already dead hero
			currAttackedPlayer->getHeroById(currHeroToAttack->getId());
		}
		catch (const std::invalid_argument& ex)
		{
			std::cout << "The hero you want to attack was already dead!" << std::endl;
			std::cout << "Summary..........." << std::endl;
			std::cout << "Nothing is lost, but nothing is won too!" << std::endl;
			return;
		}
		double differenceMoney = newPointsAttacked - newPointsAttacker;
		//winner
		currAttackedPlayer->changeMoney(differenceMoney);
		currAttackedPlayer->changePoints(DefaultValues::WON_XP_FROM_DIRECT_BATTLE);
		//loser
		currAttackingPlayer->changeMoney(-2 * differenceMoney);
		currAttackingPlayer->removeHero(currHeroToPlayWith->getId());
		//Game::removeHeroOwner(currHeroToPlayWith->getId());
		currAttackingPlayer->changePoints(-DefaultValues::LOST_XP_FROM_DIRECT_BATTLE);
		//battle result
		std::cout << currAttackedPlayer->getUsername() << " wins this battle against "
			<< currAttackingPlayer->getUsername() << "!" << std::endl;
		//summary
		std::cout << "Summary..........." << std::endl;
		std::cout << currAttackedPlayer->getUsername() << " won " << differenceMoney << "$ and "
			<< DefaultValues::WON_XP_FROM_DIRECT_BATTLE << "xp!" << std::endl;
		std::cout << currAttackingPlayer->getUsername() << " lost " << differenceMoney * 2 << "$ and "
			<< DefaultValues::LOST_XP_FROM_DIRECT_BATTLE << "xp!" << std::endl;
		std::cout << currHeroToPlayWith->getHeroName() << " was killed in the battle! " << std::endl;
	}
	break;
	case BattleResult::AttackingPlayerWins:
	{
		try
		{
			//if our hero was killed during the round
			currAttackingPlayer->getHeroById(currHeroToPlayWith->getId());
		}
		catch (const std::invalid_argument& ex)
		{
			std::cout << "The hero you want to play with was killed by the other players in the league!" << std::endl;
			std::cout << "Summary..........." << std::endl;
			std::cout << "Hero killed!" << std::endl;
			return;
		}
		try
		{
			//if we attack already dead hero
			currAttackedPlayer->getHeroById(currHeroToAttack->getId());
		}
		catch (const std::invalid_argument& ex)
		{
			std::cout << "The hero you want to attack was already dead!" << std::endl;
			std::cout << "Summary..........." << std::endl;
			std::cout << "Nothing is lost, but nothing is won too!" << std::endl;
			return;
		}
		double differenceMoney = newPointsAttacker - newPointsAttacked;
		//winner
		currAttackingPlayer->changeMoney(differenceMoney);
		currAttackingPlayer->changePoints(DefaultValues::WON_XP_FROM_DIRECT_BATTLE);
		//loser
		if (currHeroToAttack->getTactics() != Tactics::defence)//the attacked does not loose money
		{
			currAttackedPlayer->changeMoney(-differenceMoney);
		}
		currAttackedPlayer->removeHero(currHeroToAttack->getId());
		//Game::removeHeroOwner(currAttackedPlayer->getId());
		currAttackedPlayer->changePoints(-DefaultValues::LOST_XP_FROM_DIRECT_BATTLE);
		//battle result
		std::cout << currAttackingPlayer->getUsername() << " wins this battle against "
			<< currAttackedPlayer->getUsername() << "!" << std::endl;
		//summary
		std::cout << "Summary..........." << std::endl;
		std::cout << currAttackingPlayer->getUsername() << " won " << differenceMoney << "$ and "
			<< DefaultValues::WON_XP_FROM_DIRECT_BATTLE << "xp!" << std::endl;
		if (currHeroToAttack->getTactics() != Tactics::defence)
		{
			std::cout << currAttackedPlayer->getUsername() << " lost " << differenceMoney
				<< "$(its hero wasn't in a defence positon) and "
				<< DefaultValues::LOST_XP_FROM_DIRECT_BATTLE << "xp!" << std::endl;
		}
		else
		{
			std::cout << currAttackedPlayer->getUsername()
				<< "did not lost any money (its hero was in a defence position), but lost "
				<< DefaultValues::LOST_XP_FROM_DIRECT_BATTLE << "xp!" << std::endl;
		}
		std::cout << currHeroToAttack->getHeroName() << " was killed in the battle!" << std::endl;
	}
	break;
	case BattleResult::EqualPowers:
	{
		if (currHeroToAttack == nullptr)//so someone has killed it
		{
			std::cout << "The hero you want to play with was killed by the other players in the league!" << std::endl;
			std::cout << "Summary..........." << std::endl;
			std::cout << "Hero killed!" << std::endl;
			return;
		}
		currAttackingPlayer->changeMoney(-DefaultValues::LOST_MONEY_FROM_DRAW);
		//battle result
		std::cout << "No one wins! The fighting heros had the same powers!" << std::endl;
		//summary
		std::cout << currAttackingPlayer->getUsername() << " loses "
			<< DefaultValues::LOST_MONEY_FROM_DRAW << "$ during the battle!" << std::endl;
	}
	break;
	case BattleResult::SkippedTurn://for league
	{
		currAttackingPlayer->changePoints(-DefaultValues::LOST_XP_FROM_SKIPPED_ROUND);
		//battle result
		std::cout << currAttackingPlayer->getUsername() << " skipped his turn!" << std::endl;
		//summary
		std::cout << "Summary..........." << std::endl;
		std::cout << currAttackingPlayer->getUsername() << " skipped his turn!" << std::endl;
		std::cout << DefaultValues::LOST_XP_FROM_SKIPPED_ROUND << "xp!" << std::endl;
	}
	break;
	case BattleResult::CannotBattle://for league
	{
		//battle rezult
		std::cout << currAttackingPlayer->getUsername() << " do not have heroes to fight with! " << std::endl;
		//summary
		std::cout << "Summary..........." << std::endl;
		std::cout << currAttackingPlayer->getUsername()
			<< " cannot fight, because all of his heroes were killed!" << std::endl;
		std::cout << "Nothing is lost!" << std::endl;
	}
	break;
	case BattleResult::BattleStopped:
	{
		currAttackingPlayer->changePoints(DefaultValues::WON_XP_FROM_INDIRECT_BATTLE);
		//battle rezult
		std::cout << "Battle is stopped!" << std::endl;
		//summary
		std::cout << "Summary..........." << std::endl;
		std::cout << currAttackingPlayer->getUsername() << " show dignity and courage!" << std::endl;
		std::cout << "He may not win some money, but he will receive a present from the kings!!!" << std::endl;
		std::cout << currAttackingPlayer->getUsername()
			<< " won " << DefaultValues::WON_XP_FROM_INDIRECT_BATTLE << "xp!" << std::endl;
	}
	break;
	case BattleResult::NoAvailablePlayers:
	{
		std::cout << "Battle not occured!" << std::endl;
	}
	break;
	default:
		break;
	}
	_playerAttacking = nullptr;
	_playerToAttack = nullptr;
	_heroToAttack = nullptr;
	_heroToPlayWith = nullptr;
	delete battleTimeline;
}

void BattleManager::clearPlayersInBattle()
{
	if (_battleStatistics.getCount() == 0)
	{
		size_t countPlayers = _playersInBattle.size();
		for (size_t i = 0; i < countPlayers; i++)
		{
			removePlayerFromBattle(_playersInBattle[0]->getId());
		}
	}
}

BattleManager::~BattleManager()
{
	delete _heroToPlayWith;
	delete _playerToAttack;
	delete _heroToAttack;
}