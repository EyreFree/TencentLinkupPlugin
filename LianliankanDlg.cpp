
// LianliankanDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Lianliankan.h"
#include "LianliankanEx.h"
#include "LianliankanDlg.h"
#include "afxdialogex.h"

//#include <vld.h>		//内存泄露检测

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	// 实现
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


// CLianliankanDlg 对话框




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


// CLianliankanDlg 消息处理程序

BOOL CLianliankanDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	is_run = false;
	m_list.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	m_list.InsertColumn(0,_T("事件"),LVCFMT_LEFT,124,0);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CLianliankanDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CLianliankanDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CLianliankanDlg::OnBnClickedOk()
{
	if(!is_run)
	{
		hThread = ::CreateThread (
					NULL,					// 默认安全属性
					NULL,					// 默认堆栈大小
					ThreadCheat,			// 线程入口地址（执行线程的函数）
					NULL,					// 传给函数的参数
					0,						// 指定线程立即运行
					&dwThreadId);			// 返回线程的ID号

		if((::WaitForSingleObject(hThread, 500)) == WAIT_TIMEOUT )
		{
			m_list.InsertItem(0,_T("开始"));
		}
		else
		{
			m_list.InsertItem(0,_T("启动失败~！"));
			MessageBox(_T("窗口句柄获取失败！"),_T("Error！"),MB_ICONSTOP);
		}
	}
}


void CLianliankanDlg::OnBnClickedButtonStop()
{
	if(is_run)
	{
		is_run = false;
		::CloseHandle(hThread);

		m_list.InsertItem(0,_T("结束"));
	}
}


void CLianliankanDlg::OnBnClickedCancel()
{
	is_run = false;
	::CloseHandle(hThread);

	CDialogEx::OnCancel();
}
