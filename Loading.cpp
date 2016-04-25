// Loading.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Lianliankan.h"
#include "Loading.h"
#include "afxdialogex.h"


// CLoading �Ի���

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


// CLoading ��Ϣ�������


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

	//���ô��ڰ�͸�����

	ModifyStyleEx(0, WS_EX_LAYERED);

	//�����ڶ�������Ϊ͸����1~255��ֵԽ��͸����Խ��

	SetLayeredWindowAttributes(0, 255, LWA_ALPHA);

	SetTimer(1,50,NULL);

	return TRUE;
}

void CLoading::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	CRect rc;
	GetWindowRect(&rc);					//��ô��ھ���

	//����������Բ�Ǿ��η��

	CRgn rgn;
	rc -= rc.TopLeft();					//���ݴ��ھ��δ���һ��Բ�Ǿ�������������γ�Բ�ǵĴ�С
	rgn.CreateRoundRectRgn(rc.left, rc.top, rc.right, rc.bottom, 50, 50);
	SetWindowRgn(rgn, TRUE);
	rgn.DeleteObject();
}
