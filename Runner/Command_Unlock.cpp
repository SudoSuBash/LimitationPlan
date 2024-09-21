#include "Command_Unlock.h"

Command_Unlock::Command_Unlock() 
	: BaseCommand(TEXT("unlock"), 1, { TEXT("ulk"),TEXT("unlock")}) {
}

LRESULT Command_Unlock::ExecCmd(vector<wstring> args) {
	return 0;
}
