#pragma once
#include "BaseCommand.h"

class Command_Broadcast :
    public BaseCommand
{
public:
    Command_Broadcast();

    LRESULT ExecCmd(vector<wstring> args);

};

