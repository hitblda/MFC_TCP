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
	CString str;
	dlg->m_tm = CTime::GetCurrentTime();
	str = dlg->m_tm.Format("%X");
	str += _T(" 与服务器连接成功");
	dlg->m_list.AddString(str);  //将str添加到m_list控件里面就是将其显示出来
	dlg->m_list.UpdateData(FALSE);

	CAsyncSocket::OnSend(nErrorCode);
}

void CMySocket::OnReceive(int nErrorCode)
{
	TRACE("   ====  CMySocket OnReceive ====");

	//step1 接收数据到buf
	TRACE("客户端  收到数据  触发 。。。。。。。。。");
	CMFCChatClientDlg* dlg = (CMFCChatClientDlg*)AfxGetApp()->GetMainWnd();
	char szRecvBuf[200] = { 0 };
	Receive(szRecvBuf, 200, 0);   //const char *接收！！
	TRACE("客户端 收到的数据 是%s", szRecvBuf);

	//step2 显示数据
	USES_CONVERSION;
	CString strRecvMsg = A2W(szRecvBuf);
	CString strTime;
	dlg->m_tm = CTime::GetCurrentTime();
	strTime = dlg->m_tm.Format("%X");

	//接收到的内容：时间 客户端 内容
	strRecvMsg = strTime + _T(" 服务器端: ") + strRecvMsg;
	dlg->m_list.AddString(strRecvMsg);
	//dlg->UpdateData(FALSE);

	CAsyncSocket::OnReceive(nErrorCode);
}
