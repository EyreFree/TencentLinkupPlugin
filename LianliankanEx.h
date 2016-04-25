
//包含头文件---------------------------------------------------------

#include <windows.h>
#include <stdio.h>


//宏定义-------------------------------------------------------------

#define false 0
#define true 1


//全局变量-----------------------------------------------------------

HWND hwnd;
HANDLE hThread;
DWORD dwThreadId;
bool is_run;


//结束判定-----------------------------------------------------------

bool Is_run()
{
	return is_run;
}


//连接两点-----------------------------------------------------------

void Connection(int m,int n,int i,int j)
{
	long lParam,llParam;
	lParam=((193+m*35)<<16)+(24+n*32);
	llParam=((193+i*35)<<16)+(24+j*32);
	SendMessage(hwnd,WM_LBUTTONDOWN,MK_LBUTTON,lParam);		//发送WM_LBUTTONDOWN消息
	SendMessage(hwnd,WM_LBUTTONUP,0,lParam);
	SendMessage(hwnd,WM_LBUTTONDOWN,MK_LBUTTON,llParam);
	SendMessage(hwnd,WM_LBUTTONUP,0,llParam);
}


//暴力消除-----------------------------------------------------------

void contrast()
{
	int m=0,n=0,i=0,j=0;
	for(m=0;m<11;m++)
	{
		for(n=0;n<19;n++)
		{
			for(i=0;i<11;i++)
			{
				for(j=0;j<19&&Is_run();j++)
				{
					Connection(m,n,i,j);					//调用连接函数
				}
			}
		}
	}
}


//主函数-------------------------------------------------------------

bool Start()
{
	DWORD id=0;

	while(Is_run())
	{
		hwnd = FindWindow(NULL,_T("QQ游戏 - 连连看角色版"));
		if( hwnd == NULL)									//获取窗口句柄
		{
			return false;
		}
		while(Is_run())										//结束判定
		{
			contrast();										//调用对比函数
		}
		Sleep(500);
	}
	return true;
}


//线程函数-----------------------------------------------------------

DWORD WINAPI ThreadCheat(LPVOID lpParamSocket)
{
	is_run = true;
	if(Start() == false)
	{
		is_run = false;
	}
	return 0;
}