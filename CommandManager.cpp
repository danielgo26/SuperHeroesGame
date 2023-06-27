#include "CommandManager.h"
#include <iostream>

CommandManager& CommandManager::getInstance()
{
	static CommandManager cm;
	return cm;
}

void CommandManager::startApplication()
{
	receiveCommand();
}

CommandType CommandManager::getTypeRoot() const
{
	return _lastCommand->getType();
}

void CommandManager::executeCommand()
{
	_lastCommand->execute();
}

void CommandManager::manageCommands(Command* command)
{
	if (command->getType() == CommandType::WrongInput)
	{
		command->execute();
		delete command;
		//here we make that "jump" in order for better user interface
		if (_lastCommand->getType() == CommandType::LogIn)
		{
			removeCommand();
		}
	}
	//here we "jump" directly to start up menu, because the log in menu is like an intermediate command
	else if (command->getType() == CommandType::LogOut)
	{
		//manage LogOut command
		addCommand(command);
		executeCommand();
		removeCommand();
		//remove player/admin menu
		removeCommand();
		//remove log in menu
		removeCommand();
	}
	else if (command->getType() == CommandType::Back)
	{
		//delete the back command first
		delete command;
		//remove the last command
		removeCommand();
	}
	else
	{
		addCommand(command);
	}
}
void CommandManager::receiveCommand()
{
	//execute the curr command in the hierarchy
	executeCommand();
	//check for end of application
	if (_lastCommand->getType() == CommandType::ExitApp)
	{
		removeCommand();
		return;
	}
	//wait for the return command from the factory
	Command* _commandOperating = CommandFactory::getInstance().getCommand(getTypeRoot());
	//manage that returned command - add it in the tree or just execute it
	manageCommands(_commandOperating);
	//recursion
	receiveCommand();

}
Command* CommandManager::getLastCommand()
{
	return _lastCommand;
}
Command* CommandManager::getBeforeLastCommand()
{
	Command* currCommand = &_root;
	if (currCommand->getCommand() == nullptr)
	{
		return nullptr;
	}
	while (true)
	{
		if (currCommand->getCommand()->getCommand() == nullptr)
		{
			return currCommand;
		}
		currCommand = currCommand->getCommand();
	}
}

void CommandManager::addCommand(Command* command)
{
	if (!command)
	{
		throw std::invalid_argument("Command was nullptr!");
	}
	//here we use dynamic cast, so we know that last command is complex, because if not - we cannot end up here!
	ComplexCommand* lastCommand = dynamic_cast<ComplexCommand*>(getLastCommand());
	lastCommand->setCommand(command);
	_lastCommand = command;
}
void CommandManager::removeCommand()
{
	Command* beforeLastCommand = getBeforeLastCommand();
	if (beforeLastCommand != nullptr)
	{
		Command* cmd = beforeLastCommand->getCommand();
		delete cmd;
		//here if the command is before last <=> it is a complex one
		(dynamic_cast<ComplexCommand*>(beforeLastCommand))->setCommand(nullptr);
		_lastCommand = beforeLastCommand;
	}
}