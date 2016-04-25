// Loading.cpp : 实现文件
//

#include "stdafx.h"
#include "Lianliankan.h"
#include "Loading.h"
#include "afxdialogex.h"


// CLoading 对话框

IMPLEMENT_DYNAMIC(CLoading, CDialogEx)

CLoading::CLoading(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLoading::IDD, pParent)
{
	turn = - 15;
}

CLoading::~CLoading()
{
}

void CLoading::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CLoading, CDialogEx)
	ON_WM_TIMER()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CLoading 消息处理程序


void CLoading::OnTimer(UINT_PTR nIDEvent)
{
	if(25 == turn)
	{
		OnOK();
	}

	++turn;

	if( turn>0 )
	{
		SetLayeredWindowAttributes(0, 250 - turn * 10 , LWA_ALPHA);
	}

	CDialogEx::OnTimer(nIDEvent);
}


BOOL CLoading::OnInitDialog() 
{
	CDialog::OnInitDialog();

	//设置窗口半透明风格

	ModifyStyleEx(0, WS_EX_LAYERED);

	//倒数第二个参数为透明度1~255，值越大透明度越低

	SetLayeredWindowAttributes(0, 255, LWA_ALPHA);

	SetTimer(1,50,NULL);

	return TRUE;
}

void CLoading::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	CRect rc;
	GetWindowRect(&rc);					//获得窗口矩形

	//设置主窗体圆角矩形风格

	CRgn rgn;
	rc -= rc.TopLeft();					//根据窗口矩形创建一个圆角矩形最后两个是形成圆角的大小
	rgn.CreateRoundRectRgn(rc.left, rc.top, rc.right, rc.bottom, 50, 50);
	SetWindowRgn(rgn, TRUE);
	rgn.DeleteObject();
}
