#pragma once
#include <vector>
#include <string>
#include "BaseCommand.h"

using std::vector;
using std::wstring;
class CommandExecutor
{
public:


	CommandExecutor();

	LRESULT registerNewCmd(BaseCommand* cmd);

	LRESULT execCmd(wstring trigger, vector<wstring> args);
private:
	vector<BaseCommand*> commands;
};

