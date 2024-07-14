#pragma once
#include"Sys.h"
#include"cmd_console_tools.h"
using namespace std;

void printHelp(string op);
void printErr(const string msg1, const int bg_color = 0, const int ft_color = COLOR_GREEN);
void getCommond(vector<string>& args);
void execute(const vector<string>& args);
void autoTest1();
void autoTest2();
void autoTest3();

void setDefaultColor();
void showInfo();
void pause(const char * msg);
