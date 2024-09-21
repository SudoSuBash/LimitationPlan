#include "Command_Unlock.h"

Command_Unlock::Command_Unlock() 
	: BaseCommand(TEXT("unlock"), 1, { TEXT("ulk"),TEXT("unlock")}) {
}

LRESULT Command_Unlock::ExecCmd(vector<wstring> arg, vector<any>& ret) {
	return 0;
}
