#include"Common.h"
#include"Sys.h"
#include"cmd_console_tools.h"
using namespace std;
DiskDriver g_DiskDriver;
BufferManager g_BufferManager;
OpenFileTable g_OpenFileTable;
SuperBlock g_SuperBlock;
FileSystem g_FileSystem;
INodeTable g_INodeTable;
FileManager g_FileManager;
User g_User;
vector<string> Args;
int main() {
	User* user = &g_User;
	cct_cls(), showInfo();
	printHelp("help");
	cout << "[/ ]$ ";
	while (1) {
		getCommond(Args);
		if (Args.empty()) {
			cout << "[" << user->curDirPath << " ]$ ";
			continue;
		}
		execute(Args);
	}
	cct_setcolor(0, COLOR_GREEN);
	return 0;
}

