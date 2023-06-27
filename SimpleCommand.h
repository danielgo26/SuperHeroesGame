#pragma once
#include "Command.h"

class SimpleCommand : public Command
{
public:
	Command* getCommand() const override;
};