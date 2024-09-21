#include "Command_Broadcast.h"

Command_Broadcast::Command_Broadcast() : BaseCommand(TEXT("broadcast"), 1, { TEXT("br"),TEXT("broadcast") }) {

}

LRESULT Command_Broadcast::ExecCmd(vector<wstring> args, vector<any>& ret) {
	return 0;
}