#include "Command_ExecLocalCmd.h"
#include <cassert>

#include <cstdio>

#define BUF_SIZE sizeof(wchar_t) * 1024000
Command_ExecLocalCmd::Command_ExecLocalCmd() : BaseCommand(TEXT("ExecLocalShell"), 1, { TEXT("es"),TEXT("exec"),TEXT("executeshell") }) {
	this->output = NULL;
}

LRESULT Command_ExecLocalCmd::ExecCmd(vector<wstring> args) {
	assert(args.size() == 1);

	wchar_t* buf = (wchar_t*)malloc(BUF_SIZE);
	ZeroMemory(buf, BUF_SIZE);

	this->output = new wstring();
	FILE* fp = NULL;

	if ((fp = _wpopen(args[0].c_str(), TEXT("r"))) != NULL) {
		while (fgetws(buf, BUF_SIZE / sizeof(wchar_t), fp)) {
			this->output->append(buf);
			free(buf);
			buf = (wchar_t*)malloc(BUF_SIZE);
			ZeroMemory(buf, BUF_SIZE);
		}
		_pclose(fp);
	}

	
	free(buf);
	return 0;
}


wstring Command_ExecLocalCmd::getOutput() {
	if (this->output == NULL) return TEXT("");
	return *(this->output);
}

Command_ExecLocalCmd::~Command_ExecLocalCmd() {
	if(this->output!=NULL) free(this->output);
}