#include "CommandExecutor.h"

#include "Command_Unlock.h"
#include "Command_Broadcast.h"
#include "Command_Lock.h"
#include "Command_ExecLocalCmd.h"
#include "Command_CloseBroadCast.h"
#include <stack>
#include <map>

#include <iostream>
#define T(q) TEXT(q)

using std::stack;
using std::map;

CommandExecutor::CommandExecutor() {
	this->registerNewCmd(new Command_Lock());
	this->registerNewCmd(new Command_Unlock());
	this->registerNewCmd(new Command_Broadcast());
	this->registerNewCmd(new Command_ExecLocalCmd());
	this->registerNewCmd(new Command_CloseBc());
}

LRESULT CommandExecutor::registerNewCmd(BaseCommand* cmd) {
	this->commands.push_back(cmd);
	return 0;
}

LRESULT  CommandExecutor::execCmd(wstring cmd, vector<any>& ret) {
	cmd.erase(0, cmd.find_first_not_of(TEXT(' ')));
	cmd.erase(cmd.find_last_not_of(TEXT(' '))+1);
	if (cmd.empty()) return -2;

	vector<wstring> cmds = vector<wstring>();
	wstring temp = T("");
	wchar_t target[2] = { '\"','\'' };

	stack<wchar_t> chrs = stack<wchar_t>();
	cmd += TEXT(" ");

	for (int i=0;i<cmd.size();i++) {
		if (cmd[i] == T('\'')) {
			if (chrs.size() == 0 || chrs.top() != '\'') {
				if(chrs.size() == 0) //不在字符串中
					chrs.push('\'');
				else
					temp += cmd[i];
			}
			else {
				chrs.pop();
			};
		}
		else if (cmd[i] == T('\"')) {
			if (chrs.size() == 0 || chrs.top() != '"') {
				if (chrs.size() == 0) //不在字符串中
					chrs.push('"');
				else
					temp += cmd[i];
			}
			else {
				chrs.pop();
			}
		} else if (cmd[i] == T(' ') && chrs.size() == 0) {
			cmds.push_back(temp);
			temp = T("");
		} else {
			temp += cmd[i];
		}
	}

	if (chrs.size() != 0) return -1;

	vector<wstring> args;
	if (cmds.size() > 1) {
		args = vector<wstring>(cmds.begin() + 1, cmds.end());
	}
	return this->execCmdArgs(cmds[0],args,ret);
}

LRESULT CommandExecutor::execCmdArgs(wstring trigger, vector<wstring> args,vector<any>& ret) {
	LRESULT res = -2;
	BaseCommand* cmd = NULL;

	for (BaseCommand* i : this->commands) {
		if (i->isInTrigger(trigger)) {
			cmd = i;
			break;
		}
	}

	
	if (cmd != NULL) {
		res = cmd->ExecCmd(args,ret);
	}
	return res;
}