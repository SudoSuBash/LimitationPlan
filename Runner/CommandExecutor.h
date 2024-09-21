#pragma once
#include "BaseCommand.h"

class CommandExecutor
{
public:
	CommandExecutor();

	LRESULT registerNewCmd(BaseCommand* cmd);

	LRESULT execCmd(std::wstring str, vector<any>& ret);

private:
	vector<BaseCommand*> commands;
	LRESULT execCmdArgs(wstring trigger, vector<wstring> args, vector<any>& ret);
};

