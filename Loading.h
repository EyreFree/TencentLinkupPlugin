#pragma once


// CLoading �Ի���

class CLoading : public CDialogEx
{
	DECLARE_DYNAMIC(CLoading)

public:
	CLoading(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLoading();

// �Ի�������
	enum { IDD = IDD_LOADING };

public:
	int turn;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
