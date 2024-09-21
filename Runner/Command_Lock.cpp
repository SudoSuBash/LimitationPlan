#include "Command_Lock.h"
Command_Lock::Command_Lock() : BaseCommand(TEXT("lock"), 1, { TEXT("lck"),TEXT("lock") }) {

}

LRESULT Command_Lock::ExecCmd(vector<wstring> args) {

	return 0;
}