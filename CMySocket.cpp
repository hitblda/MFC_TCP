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
	TRACE("   ====   CMySocket OnConnect  �����ˣ����ҳɹ��� ====");
	CMFCChatClientDlg* dlg = (CMFCChatClientDlg*)AfxGetApp()->GetMainWnd();
	CString str;
	dlg->m_tm = CTime::GetCurrentTime();
	str = dlg->m_tm.Format("%X");
	str += _T(" ����������ӳɹ�");
	dlg->m_list.AddString(str);  //��str��ӵ�m_list�ؼ�������ǽ�����ʾ����
	dlg->m_list.UpdateData(FALSE);

	CAsyncSocket::OnSend(nErrorCode);
}

void CMySocket::OnReceive(int nErrorCode)
{
	TRACE("   ====  CMySocket OnReceive ====");

	//step1 �������ݵ�buf
	TRACE("�ͻ���  �յ�����  ���� ������������������");
	CMFCChatClientDlg* dlg = (CMFCChatClientDlg*)AfxGetApp()->GetMainWnd();
	char szRecvBuf[200] = { 0 };
	Receive(szRecvBuf, 200, 0);   //const char *���գ���
	TRACE("�ͻ��� �յ������� ��%s", szRecvBuf);

	//step2 ��ʾ����
	USES_CONVERSION;
	CString strRecvMsg = A2W(szRecvBuf);
	CString strTime;
	dlg->m_tm = CTime::GetCurrentTime();
	strTime = dlg->m_tm.Format("%X");

	//���յ������ݣ�ʱ�� �ͻ��� ����
	strRecvMsg = strTime + _T(" ��������: ") + strRecvMsg;
	dlg->m_list.AddString(strRecvMsg);
	//dlg->UpdateData(FALSE);

	CAsyncSocket::OnReceive(nErrorCode);
}
