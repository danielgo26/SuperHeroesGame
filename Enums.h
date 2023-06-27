#pragma once
//for all of the enum classes -> one class(namespace) or several ones???//PROJECT
enum class Role
{
	admin,
	player
};
enum class Tactics
{
	attack,
	defence,
	none
};
enum class Power
{
	fire,
	earth,
	water,
	none
};

enum class CommandType
{
	WrongInput,
	StartUp,
	ExitApp,
	Back,
	LogIn,
	AdminDialog,
	PlayerDialog,
	PlayersInfoPlayer,
	ChooseTypeRanklist,
	TopThreePlayers,
	GlobalClassation,
	PersonalData,
	Market,
	BuyHero,
	ViewPlayerHeroes,
	ChooseHeroToUpgrade,
	UpgradeHero,
	VerifyUpgradeHero,
	LogOut,
	SettingsPlayer,
	ChooseTheme,
	ChangeTheme,
	QuickBattle,
	LeagueBattle,
	LeagueBattleSetting,
	LogInForLeague,
	AddAdmin,
	AddPlayer,
	DeletePlayer,
	PlayersInfo,
	AdminsInfo,
	AddHero,
	RemoveHero
};

enum class Theme
{
	Default,
	Harmony,
	Colourful,
	Spring,
	FirstPlace,
	SecondPlace,
	ThirdPlace,
	ErrorMessage
};

enum class BattleResult
{
	AttackingPlayerWins,
	AttackedPlayerWins,
	AttackedPlayerWithoutHeroes,
	EqualPowers,
	SkippedTurn,//the player skipped its turn - for league
	CannotBattle,//the player does not have heroes now - for league
	BattleStopped,//when we can attack but we do not want to and stop the battle
	NoAvailablePlayers,
	Undefined
};