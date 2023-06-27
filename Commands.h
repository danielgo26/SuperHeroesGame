#pragma once
#include "ComplexCommand.h"
#include "SimpleCommand.h"
#include "MyString.h"
#include "Command.h"

struct WrongInputCommand :SimpleCommand
{
	void execute() override;
	Command* clone() const override;
	CommandType getType()const override;
};

struct StartUpCommand : ComplexCommand
{
	void execute() override;
	Command* clone() const override;
	CommandType getType()const override;
};

struct LogInCommand : ComplexCommand
{
	void execute() override;
	Command* clone() const override;
	CommandType getType()const override;
};

struct ExitApplication : ComplexCommand
{
	void execute() override;
	Command* clone() const override;
	CommandType getType()const override;
};

struct AdminDialog : ComplexCommand
{
	void execute() override;
	Command* clone() const override;
	CommandType getType()const override;
};

struct PlayerDialog : ComplexCommand
{
	void execute() override;
	Command* clone() const override;
	CommandType getType()const override;
};

struct PlayersInfoPlayer :SimpleCommand
{
	void execute() override;
	Command* clone() const override;
	CommandType getType()const override;
};

struct BackCommand :SimpleCommand
{
	void execute() override;
	Command* clone() const override;
	CommandType getType()const override;
};

struct ChooseTypeRanklist : ComplexCommand
{
	void execute() override;
	Command* clone() const override;
	CommandType getType()const override;
};

struct TopThreePlayers : ComplexCommand//complex?
{
	void execute() override;
	Command* clone() const override;
	CommandType getType()const override;
};

struct GlobalClassation : ComplexCommand
{
	void execute() override;
	Command* clone() const override;
	CommandType getType()const override;
};

struct PersonalData : ComplexCommand
{
	void execute() override;
	Command* clone() const override;
	CommandType getType()const override;
};

struct GoToMarket :ComplexCommand
{
	void execute() override;
	Command* clone() const override;
	CommandType getType()const override;
};

struct BuyHero :SimpleCommand
{
	void execute() override;
	Command* clone() const override;
	CommandType getType()const override;
};

struct ViewPlayerHeroes :ComplexCommand
{
	void execute() override;
	Command* clone() const override;
	CommandType getType()const override;
};

struct ChooseHeroToUpgrade : ComplexCommand
{
	void execute() override;
	Command* clone() const override;
	CommandType getType()const override;
};

struct UpgradeHero : ComplexCommand
{
	void execute() override;
	Command* clone() const override;
	CommandType getType()const override;
};

struct VerifyUpgradeHero : SimpleCommand
{
	void execute() override;
	Command* clone() const override;
	CommandType getType()const override;
};

struct LogOut :SimpleCommand
{
	void execute() override;
	Command* clone() const override;
	CommandType getType()const override;
};

struct SettingsPlayer : ComplexCommand
{
	void execute() override;
	Command* clone() const override;
	CommandType getType()const override;
};

struct ChooseTheme :ComplexCommand
{
	void execute() override;
	Command* clone() const override;
	CommandType getType()const override;
};

struct ChangeTheme :SimpleCommand
{
	void execute() override;
	Command* clone() const override;
	CommandType getType()const override;
};

struct QuickBattle : SimpleCommand
{
	void execute() override;
	Command* clone() const override;
	CommandType getType()const override;
};

struct LeagueBattle : SimpleCommand
{
	void execute() override;
	Command* clone() const override;
	CommandType getType()const override;
};

struct LogInForLeague :SimpleCommand
{
	void execute() override;
	Command* clone() const override;
	CommandType getType()const override;
};

struct LeagueBattleSetting : ComplexCommand
{
	void execute() override;
	Command* clone() const override;
	CommandType getType()const override;
};

//admins

struct AddAdmin : SimpleCommand
{
	void execute() override;
	Command* clone() const override;
	CommandType getType()const override;
};

struct AddPlayer : SimpleCommand
{
	void execute() override;
	Command* clone() const override;
	CommandType getType()const override;
};

struct DeletePlayer : SimpleCommand
{
	void execute() override;
	Command* clone() const override;
	CommandType getType()const override;
};

struct PlayersInfo : ComplexCommand
{
	void execute() override;
	Command* clone() const override;
	CommandType getType()const override;
};

struct AdminsInfo : SimpleCommand
{
	void execute() override;
	Command* clone() const override;
	CommandType getType()const override;
};


struct AddHero : SimpleCommand
{
	void execute() override;
	Command* clone() const override;
	CommandType getType()const override;
};

struct RemoveHero :SimpleCommand
{
	void execute() override;
	Command* clone() const override;
	CommandType getType()const override;
};
