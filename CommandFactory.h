#pragma once
#include "Command.h"
#include "Enums.h"

class CommandFactory
{
	CommandFactory() = default;
	CommandFactory(const CommandFactory& other) = delete;
	CommandFactory& operator=(CommandFactory& other) = delete;
public:
	static CommandFactory& getInstance();
	Command* getCommand(CommandType type) const;
};