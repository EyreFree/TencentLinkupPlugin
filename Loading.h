#pragma once


// CLoading 对话框

class CLoading : public CDialogEx
{
	DECLARE_DYNAMIC(CLoading)

public:
	CLoading(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLoading();

// 对话框数据
	enum { IDD = IDD_LOADING };

public:
	int turn;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
