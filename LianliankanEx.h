
//����ͷ�ļ�---------------------------------------------------------

#include <windows.h>
#include <stdio.h>


//�궨��-------------------------------------------------------------

#define false 0
#define true 1


//ȫ�ֱ���-----------------------------------------------------------

HWND hwnd;
HANDLE hThread;
DWORD dwThreadId;
bool is_run;


//�����ж�-----------------------------------------------------------

bool Is_run()
{
	return is_run;
}


//��������-----------------------------------------------------------

void Connection(int m,int n,int i,int j)
{
	long lParam,llParam;
	lParam=((193+m*35)<<16)+(24+n*32);
	llParam=((193+i*35)<<16)+(24+j*32);
	SendMessage(hwnd,WM_LBUTTONDOWN,MK_LBUTTON,lParam);		//����WM_LBUTTONDOWN��Ϣ
	SendMessage(hwnd,WM_LBUTTONUP,0,lParam);
	SendMessage(hwnd,WM_LBUTTONDOWN,MK_LBUTTON,llParam);
	SendMessage(hwnd,WM_LBUTTONUP,0,llParam);
}


//��������-----------------------------------------------------------

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
					Connection(m,n,i,j);					//�������Ӻ���
				}
			}
		}
	}
}


//������-------------------------------------------------------------

bool Start()
{
	DWORD id=0;

	while(Is_run())
	{
		hwnd = FindWindow(NULL,_T("QQ��Ϸ - ��������ɫ��"));
		if( hwnd == NULL)									//��ȡ���ھ��
		{
			return false;
		}
		while(Is_run())										//�����ж�
		{
			contrast();										//���öԱȺ���
		}
		Sleep(500);
	}
	return true;
}


//�̺߳���-----------------------------------------------------------

DWORD WINAPI ThreadCheat(LPVOID lpParamSocket)
{
	is_run = true;
	if(Start() == false)
	{
		is_run = false;
	}
	return 0;
}