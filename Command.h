#pragma once
#include "Enums.h"

class Command
{
public:
	virtual CommandType getType()const = 0;
	virtual Command* getCommand() const = 0;
	virtual void execute() = 0;
	virtual Command* clone()const = 0;
	virtual ~Command() = default;
};