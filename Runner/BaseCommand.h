#pragma once
#include <string>
#include <Windows.h>
#include <vector>

using std::vector;
using std::wstring;

class BaseCommand
{
public:
	virtual LRESULT ExecCmd(vector<wstring> args) = 0;
	wstring getName();
	uint32_t getId();

	BOOL isInTrigger(wstring trigger);
protected:
	BaseCommand(std::wstring name,uint32_t id,vector<wstring> trigger);
private:
	wstring name;
	uint32_t id;
	vector<wstring> trigger;
};

