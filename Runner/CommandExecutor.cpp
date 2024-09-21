#include "CommandExecutor.h"

#include "Command_Unlock.h"
#include "Command_Broadcast.h"
#include "Command_Lock.h"

CommandExecutor::CommandExecutor() {
	this->registerNewCmd(new Command_Unlock());
	this->registerNewCmd(new Command_Broadcast());
}

LRESULT CommandExecutor::registerNewCmd(BaseCommand* cmd) {
	this->commands.push_back(cmd);
	return 0;
}

LRESULT CommandExecutor::execCmd(wstring trigger, vector<wstring> args) {
	LRESULT res = -1;
	BaseCommand* cmd = NULL;

	for (BaseCommand* i : this->commands) {
		if (i->isInTrigger(trigger)) {
			cmd = i;
			break;
		}
	}
	if (cmd != NULL) {
		res = cmd->ExecCmd(args);
	}
	return res;
}