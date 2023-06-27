#pragma once
#include "Command.h"
#include "Enums.h"

class ComplexCommand : public Command
{
	Command* _command = nullptr;
public:
	Command* getCommand() const override;
	void setCommand(Command* command);
	~ComplexCommand();
};