
// MFC_ChatClientDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFC_ChatClient.h"
#include "MFC_ChatClientDlg.h"
#include "afxdialogex.h"
#include <atlbase.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCChatClientDlg 对话框



CMFCChatClientDlg::CMFCChatClientDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFC_CHATCLIENT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

}

void CMFCChatClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MSG_LIST1, m_list);
	DDX_Control(pDX, IDC_SENDMSG_EDIT, m_input);
}

BEGIN_MESSAGE_MAP(CMFCChatClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CONNECT_BTN, &CMFCChatClientDlg::OnBnClickedConnectBtn)
	ON_BN_CLICKED(IDC_SEND_BTN, &CMFCChatClientDlg::OnBnClickedSendBtn)
	ON_BN_CLICKED(IDC_ChangNameBtn, &CMFCChatClientDlg::OnBnClickedChangnamebtn)
	ON_BN_CLICKED(IDC_CLEAR_BTN, &CMFCChatClientDlg::OnBnClickedClearBtn)
END_MESSAGE_MAP()


// CMFCChatClientDlg 消息处理程序

BOOL CMFCChatClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	//初始化对话框里面的原始值
	GetDlgItem(IDC_PORT_EDIT)->SetWindowTextW(_T("8000"));
	GetDlgItem(IDC_IPADDRESS1)->SetWindowTextW(_T("127.0.0.1"));

	/********************************************************************/
	//	读取配置文件	

	//获取当前路径
	WCHAR wszName[MAX_PATH] = { 0 }; //LPCWSTR 类型字符串
	WCHAR wszPath[MAX_PATH] = { 0 };
	GetCurrentDirectoryW(MAX_PATH, wszPath);
//	TRACE("###strPath = %ls", wszPath);

	CString strFilePath;
	strFilePath.Format(L"%ls//Test.ini", wszPath);  //ini是配置文件
	DWORD dwNum = GetPrivateProfileStringW(_T("CLIENT"), _T("NAME"),NULL, 
		wszName, MAX_PATH, strFilePath);

	//是否读到，给出日志
//	TRACE("### wszName =%ls , strFilePath = %ls", wszName, strFilePath);
	if (dwNum <= 0)
	{
		TRACE("###  配置文件不存在 ！自动设置名称 ");
		WritePrivateProfileStringW(_T("CLIENT"), _T("NAME"), L"YourName", strFilePath);
		SetDlgItemText(IDC_NAME_EDIT, L"YourName");
		UpdateData(FALSE); //更新控件中的内容
	}
	else
	{
		//将读到的内容放到控件中
		SetDlgItemText(IDC_NAME_EDIT, wszName);
		UpdateData(FALSE); //更新控件中的内容
	}

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCChatClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCChatClientDlg::OnPaint()
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
HCURSOR CMFCChatClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMFCChatClientDlg::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CMFCChatClientDlg::OnBnClickedConnectBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	TRACE("##Connect ........... ");

	//Step1 获取IP和端口
	CString strPort, strIP;
	//从控件获取
	GetDlgItem(IDC_PORT_EDIT)->GetWindowTextW(strPort);
	GetDlgItem(IDC_IPADDRESS1)->GetWindowTextW(strIP);

	//CString 转char*
	USES_CONVERSION;
	LPCSTR szPort = (LPCSTR)T2A(strPort);
	LPCSTR szIP = (LPCSTR)T2A(strIP);

	TRACE("szPort = %s , szIP = %s", szPort, szIP);

	int iPort = _ttoi(strPort);  //把CString类型的转换为数字

	//创建一个对象
	m_client = new CMySocket;
	if (!m_client->Create())
	{
		TRACE("m_client Create failed %d", GetLastError());  //容错处理
		return;
	}
	
	if (m_client->Connect(strIP, iPort) == SOCKET_ERROR)   //因为连接不是马上就完成
	{
		TRACE("m_client Create failed %d", GetLastError());  //容错处理
		return;
	}
	//连接的时候会触发CMySocket里面的 回调函数
}

CString CMFCChatClientDlg::CatStringShow(CString strInfo,CString strMsg)
{
	//消息内容：时间  我  内容
	CString strTime;
	CTime tmNow = CTime::GetCurrentTime();
	strTime = tmNow.Format("%X");
	CString strShow = strTime;
	//strShow += L" " + strInfo;
	strShow += L" " + strMsg;
	return strShow;
}


void CMFCChatClientDlg::OnBnClickedSendBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	
	//Step1 获取编辑框的内容
	CString strTmpMsg;
	GetDlgItem(IDC_SENDMSG_EDIT)->GetWindowTextW(strTmpMsg);
	CString strName;
	GetDlgItemTextW(IDC_NAME_EDIT, strName);
	strName = strName + L":";
	strTmpMsg = strName + strTmpMsg;

	USES_CONVERSION;
	char* szSendBuf = T2A(strTmpMsg);

	//step2 发送给服务器端
	m_client->Send(szSendBuf, SEND_MAX_BUF, 0);

	//Step3 显示到列表框
	//CString strInfo = _T(" 我: ");
	CString strShow = CatStringShow(strName, strTmpMsg);

	m_list.AddString(strShow);
	UpdateData(FALSE);
	
	//清空编辑框
	GetDlgItem(IDC_SENDMSG_EDIT)->SetWindowTextW(_T(""));
}


void CMFCChatClientDlg::OnBnClickedChangnamebtn()
{
	// TODO: 在此添加控件通知处理程序代码
	WCHAR strPath[MAX_PATH] = { 0 };
	CString strName;
	GetDlgItemText(IDC_NAME_EDIT, strName); //把控件上面的内容读取到变量strName
	if (strName.GetLength() <= 0)
	{
		MessageBox(L"昵称不能为空 ！");
		return;
	}

	/*如果修改的名字和已经有的名字重复，就不修改*/
	CString strFilePath;
	WCHAR wszName[MAX_PATH] = { 0 };
	//获取当前路径
	GetCurrentDirectoryW(MAX_PATH, strPath);
	strFilePath.Format(L"%ls//Test.ini", strPath);  //ini是配置文件
	GetPrivateProfileStringW(_T("CLIENT"), _T("NAME"), NULL, wszName, MAX_PATH, strFilePath);
	if (strName == wszName)
	{
		MessageBox(L"名字一样，没有修改！");
		return;
	}

	if (IDOK == AfxMessageBox(L"真的要修改昵称吗？", MB_OKCANCEL))
	{
	//保存昵称
//		TRACE("###strPath = %ls", strPath);

		//将获取的控件名字写入路径里面
		WritePrivateProfileStringW(_T("CLIENT"), _T("NAME"), strName, strFilePath);
		//第一个参数：项名
		//第二个参数：键名
		//第三个参数：写入的内容
		//第四个参数：文件路径
		TRACE("###strName = %ls", strName);
	}
}


void CMFCChatClientDlg::OnBnClickedClearBtn()
{
	m_list.ResetContent();
	// TODO: 在此添加控件通知处理程序代码
}
