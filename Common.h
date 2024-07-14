#pragma once
#include"Buf.h"
#include"BufferManager.h"
#include"DiskDriver.h"
#include"File.h"
#include"FileManager.h"
#include"FileSystem.h"
#include"INode.h"
#include"OpenFileManager.h"
#include"User.h"
#include"Utils.h"
#include"cmd_console_tools.h"
using namespace std;
const int CMD_NUM = 31;
const string TTips =

"                                                                                             \n"
" ███████╗ ██╗ ██╗      ███████╗ ███████╗ ██╗   ██╗ ███████╗ ████████╗ ███████╗ ███╗     ███╗ \n"
" ██╔════╝ ██║ ██║      ██╔════╝ ██╔════╝ ╚██╗ ██╔╝ ██╔════╝ ╚══██╔══╝ ██╔════╝ ████╗   ████║ \n"
" █████╗   ██║ ██║      █████╗   ███████╗  ╚████╔╝  ███████╗    ██║    █████╗   ██ ╔████ ╔██║ \n"
" ██╔══╝   ██║ ██║      ██╔══╝   ╚════██║   ╚██╔╝   ╚════██║    ██║    ██╔══╝   ██║ ╚██╔╝ ██║ \n"
" ██║      ██║ ███████╗ ███████╗ ███████║    ██║    ███████║    ██║    ███████╗ ██║  ╚═╝  ██║ \n"
" ╚═╝      ╚═╝ ╚══════╝ ╚══════╝ ╚══════╝    ╚═╝    ╚══════╝    ╚═╝    ╚══════╝ ╚═╝       ╚═╝ \n"
" +-----------------------------------------------------------------------------------------+ \n"
" |                              学号 : 1850772   姓名 : 张哲源                             | \n"
" +-----------------------------------------------------------------------------------------+ \n"
;

const string HHelp =
" +-----------------------------------------------------------------------------------------+ \n"
" | 指令            | help - 显示在线帮助手册                                               | \n"
" | 描述            | 帮助用户使用相应命令                                                  | \n"
" | 使用方式        | help [命令]                                                           | \n"
" | 参数            | 命令如下：                                                            | \n"
" |                 | help        : 手册                                                    | \n"
" |                 | fformat     : 格式化                                                  | \n"
" |                 | exit        : 正确退出                                                | \n"
" |                 | mkdir       : 新建目录                                                | \n"
" |                 | cd          : 改变目录                                                | \n"
" |                 | ls          : 列出目录及文件                                          | \n"
" |                 | create      : 新建文件                                                | \n"
" |                 | delete      : 删除文件                                                | \n"
" |                 | open        : 打开文件                                                | \n"
" |                 | close       : 关闭文件                                                | \n"
" |                 | seek        : 移动读写指针                                            | \n"
" |                 | write       : 写入文件                                                | \n"
" |                 | read        : 读取文件                                                | \n"
" |                 | autotest    : 自动测试                                                | \n"
" | 使用示例        | help mkdir                                                            | \n"
" +-----------------------------------------------------------------------------------------+ \n"

;
const string FFormat =
" +------------------------------------------------------------------+\n"
" | 指令            | fformat - 进行文件系统格式化                   |\n"
" | 描述            | 将整个文件系统进行格式化，即清空所有文件及目录!|\n"
" | 使用方式        | fformat                                        |\n"
" | 参数            | 无                                             |\n"
" | 使用示例        | fformat                                        |\n"
" +------------------------------------------------------------------+\n"
;

const string EExit =
" +------------------------------------------------------------------+\n"
" | 指令            | exit - 退出文件系统                            |\n"
" | 描述            | 若要退出程序，最好通过exit命令。此时正常退出会 |\n"
" |                 | 调用析构函数，若有在内存中未更新到磁盘上的缓存 |\n"
" |                 | 会及时更新保证正 确性, 若使用ctrl + C 终止会导 |\n"
" |                 | 致无法调用析构,再次启动时可能出现错误!         |\n"
" |                 |                                                |\n"
" | 使用方式        | exit                                           |\n"
" | 参数            | 无                                             |\n"
" | 使用示例        | exit                                           |\n"
" +------------------------------------------------------------------+\n"
;
const string MMkdir =
" +------------------------------------------------------------------+\n"
" | 指令            | mkdir - 建立目录                               |\n"
" | 描述            | 新建一个目录。若出现错误，会有相应错误提示!    |\n"
" | 使用方式        | mkdir <目录名>                                 |\n"
" | 参数            | <目录名> 可以是相对路径，也可以是绝对路径      |\n"
" | 使用示例        | mkdir     dirName                              |\n"
" |                 | mkdir     ../dirName                           |\n"
" |                 | mkdir     ../../dirName                        |\n"
" |                 | mkdir  /dirName                                |\n"
" |                 | mkdir  /dir1/dirName                           |\n"
" +------------------------------------------------------------------+\n"
;
const string LLs =
" +------------------------------------------------------------------+\n"
" | 指令            | ls - 列目录内容                                |\n"
" | 描述            | 列出当前目录中包含的文件名或目录名。若出现错误 |\n"
" |                 | 会有相应错误提示!                              |\n"
" | 使用方式        | ls                                             |\n"
" | 参数            | 无                                             |\n"
" | 使用示例        | ls                                             |\n"
" +------------------------------------------------------------------+\n"
;
const string CCd =
" +------------------------------------------------------------------+\n"
" | 指令            | cd - 改变当前目录                              |\n"
" | 描述            | 改变当前工作目录。若出现错误，会有相应错误提示!|\n"
" | 使用方式        | cd <目录名>                                    |\n"
" | 参数            | <目录名>可以是相对路径，也可以是绝对路径       |\n"
" | 使用示例        | cd dirName                                     |\n"
" |                 | cd ../dirName                                  |\n"
" |                 | cd ../../dirName                               |\n"
" |                 | cd /dirName                                    |\n"
" |                 | cd /dir1/dirName                               |\n"
" +------------------------------------------------------------------+\n"
;
const string CCreate =
" +------------------------------------------------------------------+\n"
" | 指令            | create - 新建文件                              |\n"
" | 描述            | 新建一个文件。若出现错误，会有相应错误提示!    |\n"
" | 使用方式        | create <文件名> <选项>                         |\n"
" | 参数            | <文件名> 可以包含相对路径或绝对路径            |\n"
" |                 | <选项> -r 只读属性                             |\n"
" |                 | <选项> -w 只写属性                             |\n"
" |                 | <选项> -rw == -r -w 读写属性                   |\n"
" | 使用示例        | create newFileName -rw                         |\n"
" |                 | create ../newFileName -rw                      |\n"
" |                 | create ../../newFileName -rw                   |\n"
" |                 | create /newFileName -rw                        |\n"
" |                 | create /dir1/newFileName -rw                   |\n"
" +------------------------------------------------------------------+\n"
;
const string RRm =
" +------------------------------------------------------------------+\n"
" | 指令            | delete - 删除文件                              |\n"
" | 描述            | 删除一个文件。若出现错误，会有相应错误提示!    |\n"
" | 使用方式        | delete <文件名>                                |\n"
" | 参数            | <文件名> 可以包含相对路径或绝对路径            |\n"
" | 使用示例        | delete fileName                                |\n"
" |                 | delete ../fileName                             |\n"
" |                 | delete ../../fileName                          |\n"
" |                 | delete /fileName                               |\n"
" |                 | delete /dir1/fileName                          |\n"
" +------------------------------------------------------------------+\n"
;
const string OOpen =
" +------------------------------------------------------------------+\n"
" | 指令            | open - 打开文件                                |\n"
" | 描述            | 类Unix|Linux函数open，打开一个文件。若要进行   |\n"
" |                 | 文件的读写必须先open。                         |\n"
" |                 | 若出现错误，会有相应错误提示!                  |\n"
" | 使用方式        | open <文件名> <选项>                           |\n"
" | 参数            | <文件名> 可以包含相对路径或绝对路径            |\n"
" |                 | <选项> -r 只读属性                             |\n"
" |                 | <选项> -w 只写属性                             |\n"
" |                 | <选项> -rw == -r -w 读写属性                   |\n"
" | 使用示例        | open fileName -r                               |\n"
" |                 | open ../fileName -w                            |\n"
" |                 | open ../../fileName -rw                        |\n"
" |                 | open /fileName -r -w                           |\n"
" |                 | open /dir1/fileName -rw                        |\n"
" +------------------------------------------------------------------+\n"
;

const string CClose =
" +------------------------------------------------------------------+\n"
" | 指令            | close - 关闭文件                               |\n"
" | 描述            | 类Unix|Linux函数close，关闭一个文件。          |\n"
" | 描述            | 可以对已经打开的文件进行关闭                   |\n"
" |                 | 若出现错误，会有相应错误提示!                  |\n"
" | 使用方式        | close <file descriptor>                        |\n"
" | 参数            | <file descriptor> 文件描述符                   |\n"
" | 使用示例        | close 1                                        |\n"
" +------------------------------------------------------------------+\n"
;

const string SSeek =
" +------------------------------------------------------------------+\n"
" | 指令            | seek - 移动读写指针                            |\n"
" | 描述            | 类Unix|Linux函数fseek，写入一个已经打开的文件  |\n"
" |                 | 若出现错误，会有相应错误提示!                  |\n"
" | 使用方式        | seek <file descriptor> <offset> <origin>       |\n"
" | 参数            | <file descriptor> open返回的文件描述符         |\n"
" |                 | <offset> 指定从 <origin> 开始的偏移量 可正可负 |\n"
" |                 | <origin> 指定起始位置 可为0(SEEK_SET),         |\n"
" |                 | 1(SEEK_CUR), 2(SEEK_END)                       |\n"
" | 使用示例        | seek 1 500 0                                   |\n"
" +------------------------------------------------------------------+\n"
;
const string WWrite =
" +------------------------------------------------------------------+\n"
" | 指令            | write - 写入文件                               |\n"
" | 描述            | 类Unix|Linux函数write，写入一个已经打开的文件中|\n"
" | 描述            | 若出现错误，会有相应错误提示!                  |\n"
" | 使用方式        | write <file descriptor> <InFileName> <size>    |\n"
" | 参数            |<file descriptor> open返回的文件描述符          |\n"
" |                 |<InFileName>指定写入内容为文件InFileName中的内容|\n"
" |                 |<size> 指定写入字节数，大小为 <size>            |\n"
" | 使用示例        | write 1 InFileName 123                         |\n"
" +------------------------------------------------------------------+\n"
;
const string RRead =
" +------------------------------------------------------------------+\n"
" | 指令            | read - 读取文件                                |\n"
" | 描述            | 类Unix|Linux函数read，从一个已经打开的文件中   |\n"
" |                 | 读若出现错误，会有相应错误提示!                |\n"
" | 使用方式        | read <file descriptor>[-o <OutFileName>]<size> |\n"
" | 参数            | <file descriptor> open返回的文件描述符         |\n"
" |                 | [-o <OutFileName>] -o 指定输出方式为文件，     |\n"
" |                 | 文件名为 <OutFileName> 默认为shell             |\n"
" |                 | <size> 指定读取字节数，大小为 <size>           |\n"
" | 使用示例        | read 1 -o OutFileName 123                      |\n"
" |                 | read 1 123                                     |\n"
" +------------------------------------------------------------------+\n"
;
const string AAutoTest =
" +------------------------------------------------------------------+\n"
" | 指令            | autoTest1/2/3 - 自动测试                       |\n"
" | 描述            | 帮助测试，在系统启动初期帮助测试               |\n"
" |                 | 由于写的时候写死了fd，因此只有系统刚启动时     |\n"
" |                 | 可以对得上fd，保证测试正确                     |\n"
" |                 | autotest1 autotest2 autotest3                  |\n"
" |                 | 都需要在启动初期或fformat后才能确保正确        |\n"
" | 使用方式        | autotest1                                      |\n"
" | 参数            | 无                                             |\n"
" | 使用示例        | autotest2                                      |\n"
" +------------------------------------------------------------------+\n";
;

const string TestCmd1[] = {
		"mkdir test1",
		"cd test1",
		"mkdir dir1",
		"mkdir /test1/dir2",
		"ls",
		"cd dir1",
		"ls",
		"create file1 -rw",
		"ls",
		"open file1 -rw",
		"write 4 testFile.txt 2519",
		"seek 4 0 0",
		"read 4 -o readOut1.txt 1000",
		"seek 4 1000 0",
		"read 4 -o readOut1.txt 1000",
		"seek 4 0 1",
		"read 4 50",
		"seek 4 0 0",
		"close 4",
		"cd /",
		"ls",
		"####"
};

const string TestCmd2[] = {
		"mkdir test2",
		"cd test2",
		"create Jerry -rw",
		"ls",
		"open Jerry -rw",
		"write 2 testFile.txt 800",
		"seek 2 500 0",
		"read 2 -o abc 300",
		"write 2 abc 300",
		"seek 2 0 0",
		"read 2 -o readOut2.txt 1100",
		"ls",
		"cd /",
		"ls",
		"####"
};

const string TestCmd3[] = {
		"mkdir /bin",
		"mkdir /etc",
		"mkdir /home",
		"mkdir /dev",
		"ls",
		"cd home",
		"ls",
		"create texts -rw",
		"ls",
		"create photos -rw",
		"ls",
		"create /home/reports -rw",
		"ls",

		"open texts -rw",
		"write 7 ReadMe.txt 413",
		"seek 7 0 0",
		"read 7 -o ReadMeCopy.txt 413",
		"close 7",

		"open photos -rw",
		"write 7 photo.png 1305209",
		"seek 7 0 0",
		"read 7 -o out.png 1305209",
		"close 7",
		
		"open reports -rw",
		"write 7 Report.pdf 3345703 ",
		"seek 7 0 0",
		"read 7 -o out.pdf 3345703 ",
		"close 7",
		"ls",
		"####"
};
