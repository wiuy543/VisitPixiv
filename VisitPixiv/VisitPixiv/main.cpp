/*By：石小髦 部分代码参考自网络*/
#include <iostream>
#include <fstream>
#include <cstdio> 
#include <Windows.h>
#include <string>
#include <WTypes.h>
#include <Winbase.h>
#pragma comment( linker, "/subsystem:windows /entry:mainCRTStartup" )  //无控制台窗口运行程序  
using namespace std;
int main()
{
	//p站的代理地址
	string hosts_p[] = {
		"#Pixiv",
		"210.129.120.41 pixiv.net",
		"210.129.120.41 www.pixiv.net",
		"210.129.120.41 accounts.pixiv.net",
		"210.129.120.41 touch.pixiv.net",
		"210.129.120.43 www.pixiv.net",
		"210.129.120.43 accounts.pixiv.net",
		"210.129.120.43 touch.pixiv.net",
		"210.129.120.44 www.pixiv.net",
		"210.129.120.44 accounts.pixiv.net",
		"210.129.120.44 touch.pixiv.net",
		"210.140.131.146 source.pixiv.net",
		"210.140.131.147 imgaz.pixiv.net",
		"210.129.120.44 app-api.pixiv.net",
		"210.129.120.48 oauth.secure.pixiv.net",
		"210.129.120.41 dic.pixiv.net",
		"210.140.131.153 comic.pixiv.net",
		"210.129.120.43 factory.pixiv.net",
		"74.120.148.207 g-client-proxy.pixiv.net",
		"210.140.170.179 sketch.pixiv.net",
		"210.129.120.43 payment.pixiv.net",
		"210.129.120.41 sensei.pixiv.net",
		"210.140.131.144 novel.pixiv.net",
		"210.129.120.44 en-dic.pixiv.net",
		"210.140.131.145 i1.pixiv.net",
		"210.140.131.145 i2.pixiv.net",
		"210.140.131.145 i3.pixiv.net",
		"210.140.131.145 i4.pixiv.net",
		"210.140.131.159 d.pixiv.org",
		"210.140.92.135 pixiv.pximg.net",
		"210.140.92.136 i.pximg.net",
		"#Pixiv End"
	};

	//取得当前系统hosts文件的位置
	char system_path[MAX_PATH];
	GetSystemDirectory(system_path, MAX_PATH);
	char hosts_name[100];
	sprintf_s(hosts_name, "%s%s", system_path ,"\\drivers\\etc\\hosts");

	DWORD   dwAttribute = ::GetFileAttributes(hosts_name);
	DWORD   wrAttribute = dwAttribute;
	ofstream outf;
	ifstream inf;

	//判断是否设置过代理地址
	inf.open(hosts_name, ios::in);
	string line;
	while (getline(inf, line))
	{
		cout << line;
		if (line == "#Pixiv")//找标记
		{
			MessageBox(NULL, "已经设置，不必重复运行本程序。。。", "一键上p站 By@石小髦", MB_OK + 32);
			return 0;
		}
	}
	inf.close();

	//去掉hosts文件的只读属性
	if (dwAttribute   &   FILE_ATTRIBUTE_READONLY)
	{
		wrAttribute = dwAttribute & ~FILE_ATTRIBUTE_READONLY;
		SetFileAttributes(hosts_name, wrAttribute);
	}

	string join;
	join = string("本系统hosts文件路径：") + hosts_name + "\n将要设置本地域名，如果杀毒软件弹出窗口，请选择允许/信任\n所以。。。你确定操作吗？";
	if (MessageBox(NULL , join.c_str() , "一键上p站 By@石小髦", MB_OKCANCEL + 32) == IDCANCEL)
	{
		return 0;
	}
	
	outf.open(hosts_name, ios::app);//追加
	for(string n:hosts_p)//一行一行地追加到文件尾
	{
		outf << "\n" << n;
	}
	outf << "\n";
	outf.close();
	MessageBox(NULL, "设置成功，请打开浏览器访问“pixiv.net”\n(应该可以上了吧。。。)", "一键上p站 By@石小髦", MB_OK + 32);
	SetFileAttributes(hosts_name, dwAttribute);//恢复只读属性
	return 0;
}