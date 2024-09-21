#pragma once
#include "BaseCommand.h"

class Command_Unlock : public BaseCommand
{	
public:
	Command_Unlock();

	LRESULT ExecCmd(vector<wstring> args);
};

