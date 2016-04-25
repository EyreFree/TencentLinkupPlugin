
// LianliankanDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Lianliankan.h"
#include "LianliankanEx.h"
#include "LianliankanDlg.h"
#include "afxdialogex.h"

//#include <vld.h>		//�ڴ�й¶���

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CLianliankanDlg �Ի���




CLianliankanDlg::CLianliankanDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLianliankanDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLianliankanDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST1, m_list);
}

BEGIN_MESSAGE_MAP(CLianliankanDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CLianliankanDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CLianliankanDlg::OnBnClickedButtonStop)
	ON_BN_CLICKED(IDCANCEL, &CLianliankanDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CLianliankanDlg ��Ϣ�������

BOOL CLianliankanDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	is_run = false;
	m_list.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	m_list.InsertColumn(0,_T("�¼�"),LVCFMT_LEFT,124,0);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CLianliankanDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CLianliankanDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CLianliankanDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CLianliankanDlg::OnBnClickedOk()
{
	if(!is_run)
	{
		hThread = ::CreateThread (
					NULL,					// Ĭ�ϰ�ȫ����
					NULL,					// Ĭ�϶�ջ��С
					ThreadCheat,			// �߳���ڵ�ַ��ִ���̵߳ĺ�����
					NULL,					// ���������Ĳ���
					0,						// ָ���߳���������
					&dwThreadId);			// �����̵߳�ID��

		if((::WaitForSingleObject(hThread, 500)) == WAIT_TIMEOUT )
		{
			m_list.InsertItem(0,_T("��ʼ"));
		}
		else
		{
			m_list.InsertItem(0,_T("����ʧ��~��"));
			MessageBox(_T("���ھ����ȡʧ�ܣ�"),_T("Error��"),MB_ICONSTOP);
		}
	}
}


void CLianliankanDlg::OnBnClickedButtonStop()
{
	if(is_run)
	{
		is_run = false;
		::CloseHandle(hThread);

		m_list.InsertItem(0,_T("����"));
	}
}


void CLianliankanDlg::OnBnClickedCancel()
{
	is_run = false;
	::CloseHandle(hThread);

	CDialogEx::OnCancel();
}
