#include "pch.h"
#include "CMySocket.h"
#include "MFC_ChatClientDlg.h"
#include "MFC_ChatClient.h"

CMySocket::CMySocket()
{


}

CMySocket::~CMySocket()
{
}

void CMySocket::OnConnect(int nErrorCode)
{
	TRACE("   ====   CMySocket OnConnect  连接了，并且成功！ ====");
	CMFCChatClientDlg* dlg = (CMFCChatClientDlg*)AfxGetApp()->GetMainWnd();

	//CString str;
	//dlg->m_tm = CTime::GetCurrentTime();
	//str = dlg->m_tm.Format("%X");
	//str += _T(" 与服务器连接成功");
	CString strMsg = _T("与服务器连接成功!");
	CString strInfo = _T(" ");
	CString strShow = dlg->CatStringShow(strInfo, strMsg);

	dlg->m_list.AddString(strShow);  //将str添加到m_list控件里面就是将其显示出来
	dlg->m_list.UpdateData(FALSE);

	CAsyncSocket::OnSend(nErrorCode);
}

void CMySocket::OnReceive(int nErrorCode)
{
	//TRACE("   ====  CMySocket OnReceive ====");

	//step1 接收数据到buf
	//TRACE("客户端  收到数据  触发 。。。。。。。。。");
	CMFCChatClientDlg* dlg = (CMFCChatClientDlg*)AfxGetApp()->GetMainWnd();
	char szRecvBuf[SEND_MAX_BUF] = { 0 };
	Receive(szRecvBuf, SEND_MAX_BUF, 0);   //const char *接收！！
	TRACE("客户端 收到的数据 是%s", szRecvBuf);

	//step2 显示数据
	USES_CONVERSION;
	CString strRecvMsg = A2W(szRecvBuf);
	CString strInfo = _T(" 服务器端:  ");
	CString strShow = dlg->CatStringShow(strInfo, strRecvMsg);
	dlg->m_list.AddString(strShow);

	//自动回复消息功能 IDC_AUTOAPPLY
	if (((CButton*)dlg->GetDlgItem(IDC_AUTOANS_CHK))->GetCheck())
	{

		//自动回复，先读编辑框的内容
		CString strAutoAnsMsg;
		dlg->GetDlgItemText(IDC_AUTOAPLLY_EDIT1, strAutoAnsMsg);
		if (strAutoAnsMsg.GetLength() <= 0)
		{
			return;
		}
		//如果两次收到的消息相同


		//格式+封装
		CString strName;
		dlg->GetDlgItemText(IDC_NAME_EDIT, strName);
		//要发送的核心内容: 用户名 + [自动回复] + 消息
		CString strMsg = strName +  L"[自动回复]" + strAutoAnsMsg;
		//时间 + 核心内容
		strShow = dlg->CatStringShow(L"", strMsg);
		TRACE("客户端 自动回复的内容是：%s", strShow);

		char* szSenfBuf = T2A(strMsg);
		//格式化&封装 完成就开始发送
		dlg->m_client->Send(szSenfBuf, SEND_MAX_BUF, 0);

		//客户端消息显示区显示内容
		dlg->m_list.AddString(strShow);
	}
	//dlg->UpdateData(FALSE);

	CAsyncSocket::OnReceive(nErrorCode);
}
