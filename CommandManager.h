#pragma once
#include "CommandFactory.h"
#include "MenuGenerator.h"
#include "Commands.h"

class CommandManager//singelton
{
	StartUpCommand _root;
	Command* _lastCommand = &_root;
	CommandManager() = default;
	CommandManager(const CommandManager& other) = delete;
	CommandManager& operator=(const CommandManager& other) = delete;

	void executeCommand();
	CommandType getTypeRoot() const;
	void receiveCommand();
	void addCommand(Command* command);
	void removeCommand();
	void manageCommands(Command* command);
	Command* getLastCommand();
	Command* getBeforeLastCommand();
public:
	static CommandManager& getInstance();
	void startApplication();
};