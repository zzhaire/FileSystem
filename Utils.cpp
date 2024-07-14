#include"Sys.h"
#include"Common.h"
#include"cmd_console_tools.h"
using namespace std;
extern BufferManager g_BufferManager;
extern OpenFileTable g_OpenFileTable;
extern FileSystem g_FileSystem;
extern INodeTable g_INodeTable;
extern FileManager g_FileManager;
extern User g_User;
extern vector<string> Args;
unordered_map<string, const string> HelpManual(
	{
		{"help"		,	HHelp	 },
		{"fformat"	,	FFormat	 },
		{"exit"		,	EExit	 },
		{"mkdir"	,	MMkdir	 },
		{"cd"		,	CCd		 },
		{"ls"		,	LLs		 },
		{"create"	,	CCreate	 },
		{"rm"		,	RRm		 },
		{"open"		,	OOpen	 },
		{"close"	,	CClose	 },
		{"seek"		,	SSeek	 },
		{"write"	,	WWrite	 },
		{"read"		,	RRead	 },
		{"autotest"	,	AAutoTest},
	}
);
void setDefaultColor() {
	cct_setcolor(0, COLOR_GREEN);
}
void printHelp(string op) {
	auto it = HelpManual.find(op);
	if (it == HelpManual.end()) {
		cout << op << "�Ȳ���ָ��,Ҳ���ǿ�ִ���ļ�\n";
		return;
	}
	cout << it->second;
}
void printErr(const string msg1,const int bg_color , const int ft_color) {
	cct_setcolor(0, COLOR_RED);
	cout << "ERROR: ";
	setDefaultColor();
	cct_setcolor(bg_color, ft_color);
	if (msg1 != "")	cout << msg1;
	setDefaultColor();
}
void getCommond(vector<string>& args)
{
	args.clear();
	string input;
	getline(cin, input);
	istringstream iss(input);
	string token;
	while (iss >> token) {
		args.push_back(token);
	}
}

void splitCommond(string input, vector<string>& args) {
	args.clear();
	stringstream iss(input);
	string token;
	while (iss >> token) {
		args.push_back(token);
	}
}

void execute(const vector<string>& args) {
	User* user = &g_User;
	string cmd, arg1, arg2, arg3;
	cmd = args[0];
	arg1 = args.size() > 1 ? args[1] : "";
	arg2 = args.size() > 2 ? args[2] : "";
	arg3 = args.size() > 3 ? args[3] : "";
	if (cmd == "help") {
		printHelp(arg1.empty() ? "help" : arg1);
	}
	else if (cmd == "fformat") {
		g_OpenFileTable.Format();
		g_INodeTable.Format();
		g_BufferManager.FormatBuffer();
		g_FileSystem.FormatDevice();
		exit(0);
	}
	else if (cmd == "exit") {
		exit(0);
	}
	else if (cmd == "mkdir") {
		user->Mkdir(arg1);
	}
	else if (cmd == "ls") {
		user->Ls();
	}
	else if (cmd == "cd") {
		user->Cd(arg1);
	}
	else if (cmd == "create") {
		//create û����Ҫģʽ�ı�Ҫ
		user->Create(arg1, arg2 + arg3);
	}
	else if (cmd == "delete") {
		user->Delete(arg1);
	}
	else if (cmd == "open") {
		user->Open(arg1, arg2);
	}
	else if (cmd == "close") {
		user->Close(arg1);
	}
	else if (cmd == "seek") {
		user->Seek(arg1, arg2, arg3);
	}
	else if (cmd == "read") {
		if (arg2 == "-o")
			user->Read(arg1, arg3, args[4]);
		else
			user->Read(arg1, "", arg2);
	}
	else if (cmd == "write") {
		user->Write(arg1, arg2, arg3);
	}
	else if (cmd == "autotest1") {
		autoTest1();
		return;
	}
	else if (cmd == "autotest2") {
		autoTest2();
		return;
	}
	else if (cmd == "autotest3") {
		autoTest3();
		return;
	}
	else if (cmd != "") {
		printErr(cmd);
		cout <<"   δʶ���ָ��"<< endl;
	}
	cout << "[" << user->curDirPath << " ]$ ";
}


void autoTest1() {
	User* user = &g_User;
	vector<string>args;
	cout <<"���Գ���1�ļ�ָ����Կ�ʼִ�У���ȷ���Ǹ�ʽ����ִ����ȷ����ȷ\n"; ;
	pause(" ���س�����ʼ����\n");
	cout << "[" << user->curDirPath << " ]$ ";
	for (int i = 0; TestCmd1[i]!="####"; i++) {
		splitCommond(TestCmd1[i], args);
		for (int i = 0; i < (int) args.size(); i++) {
			cout << args[i] << " ";
		}
		pause("");
		cout << "\n";
		execute(args);
	}
	cout << "����1ִ����ɣ��뵽��ǰĿ¼�е�readOut1.txt�в鿴���ٴν��в�������fformat��ʽ����\n";
}
void autoTest2() {
	User* user = &g_User;
	vector<string>args;
	cout << " ���Գ���2/test2/Jerry��д���Կ�ʼִ�У���ȷ���Ǹ�ʽ����ִ����ȷ����ȷ\n"; ;
	pause(" ���س�����ʼ����\n");
	cout << "[" << user->curDirPath << " ]$ ";
	for (int i = 0; TestCmd2[i] != "####"; i++) {
		splitCommond(TestCmd2[i], args);
		for (int i = 0; i < (int)args.size(); i++) {
			cout << args[i] << " ";
		}
		pause("");
		cout << "\n";
		execute(args);
	}
	cout << "����2ִ����ɣ��뵽��ǰĿ¼�е�readOut2.txt�в鿴,�ٴν��в�������fformat��ʽ����\n";

}
void autoTest3() {
	User* user = &g_User;
	vector<string>args;
	cout << " \n"; ;
	pause(" ���س�����ʼ����\n");
	cout << "[" << user->curDirPath << " ]$ ";
	for (int i = 0; TestCmd3[i] != "####"; i++) {
		splitCommond(TestCmd3[i], args);
		for (int i = 0; i < (int)args.size(); i++) {
			cout << args[i] << " ";
		}
		pause("");
		cout << "\n";
		execute(args);
	}
	cout << "����3ִ����ɣ��뵽��ǰĿ¼�е�out3.pdf��out3.png�в鿴,�ٴν��в�������fformat��ʽ����\n";

}



void showInfo()
{
	cct_setconsoleborder(120, 50);
	cct_setfontsize("����", 20);
	cct_setcolor(COLOR_BLUE, COLOR_HYELLOW );
	cout << TTips << endl;
	setDefaultColor();
}

void pause(const char * msg)
{
	cout << msg ;
	while (1)
	{
		char ch = _getch();
		if (ch == '\n' || ch == '\r')
			break;
	}
}