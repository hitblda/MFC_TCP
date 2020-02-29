
// MFC_ChatClientDlg.h: 头文件
//

#pragma once
#include "CMySocket.h"

#define SEND_MAX_BUF  1024

// CMFCChatClientDlg 对话框
class CMFCChatClientDlg : public CDialogEx
{
// 构造
public:
	CMFCChatClientDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_CHATCLIENT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnEnChangeEdit1();

	afx_msg void OnLbnSelchangeList1();

	afx_msg void OnBnClickedClear();
	afx_msg void OnBnClickedConnectBtn();

	CString CatStringShow(CString strInfo, CString strMsg);

	CMySocket* m_client;
	CListBox m_list;

	//CTime m_tm;  //实时时间  //已经作为临时变量
	CEdit m_input;
	afx_msg void OnBnClickedSendBtn();
	afx_msg void OnBnClickedChangnamebtn();
	afx_msg void OnBnClickedClearBtn();
};
