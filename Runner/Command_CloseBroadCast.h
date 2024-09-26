#pragma once
#include "BaseCommand.h"
class Command_CloseBc :
    public BaseCommand
{
public:
    Command_CloseBc();

    LRESULT ExecCmd(vector<wstring> args, vector<any>& ret);
};

