#include "ComplexCommand.h"

Command* ComplexCommand::getCommand() const
{
	return _command;
}
void ComplexCommand::setCommand(Command* command)
{
	_command = command;
}

ComplexCommand::~ComplexCommand()
{
	delete _command;
}
