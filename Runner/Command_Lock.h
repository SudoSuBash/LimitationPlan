#pragma once
#include "BaseCommand.h"
class Command_Lock :
    public BaseCommand
{
public:
    Command_Lock();

    LRESULT ExecCmd(vector<wstring> args, vector<any>& ret);

};

