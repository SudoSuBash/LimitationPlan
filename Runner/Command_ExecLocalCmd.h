#pragma once
#include "BaseCommand.h"
class Command_ExecLocalCmd :
    public BaseCommand
{
public:
    Command_ExecLocalCmd();

    LRESULT ExecCmd(vector<wstring> args);

    wstring getOutput();

    ~Command_ExecLocalCmd();
private:
    wstring* output;
};

