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

	//CString str;
	//dlg->m_tm = CTime::GetCurrentTime();
	//str = dlg->m_tm.Format("%X");
	//str += _T(" ����������ӳɹ�");
	CString strMsg = _T("����������ӳɹ�!");
	CString strInfo = _T(" ");
	CString strShow = dlg->CatStringShow(strInfo, strMsg);

	dlg->m_list.AddString(strShow);  //��str��ӵ�m_list�ؼ�������ǽ�����ʾ����
	dlg->m_list.UpdateData(FALSE);

	CAsyncSocket::OnSend(nErrorCode);
}

void CMySocket::OnReceive(int nErrorCode)
{
	//TRACE("   ====  CMySocket OnReceive ====");

	//step1 �������ݵ�buf
	//TRACE("�ͻ���  �յ�����  ���� ������������������");
	CMFCChatClientDlg* dlg = (CMFCChatClientDlg*)AfxGetApp()->GetMainWnd();
	char szRecvBuf[SEND_MAX_BUF] = { 0 };
	Receive(szRecvBuf, SEND_MAX_BUF, 0);   //const char *���գ���
	TRACE("�ͻ��� �յ������� ��%s", szRecvBuf);

	//step2 ��ʾ����
	USES_CONVERSION;
	CString strRecvMsg = A2W(szRecvBuf);
	CString strInfo = _T(" ��������:  ");
	CString strShow = dlg->CatStringShow(strInfo, strRecvMsg);
	dlg->m_list.AddString(strShow);

	//�Զ��ظ���Ϣ���� IDC_AUTOAPPLY
	if (((CButton*)dlg->GetDlgItem(IDC_AUTOANS_CHK))->GetCheck())
	{

		//�Զ��ظ����ȶ��༭�������
		CString strAutoAnsMsg;
		dlg->GetDlgItemText(IDC_AUTOAPLLY_EDIT1, strAutoAnsMsg);
		if (strAutoAnsMsg.GetLength() <= 0)
		{
			return;
		}
		//��������յ�����Ϣ��ͬ


		//��ʽ+��װ
		CString strName;
		dlg->GetDlgItemText(IDC_NAME_EDIT, strName);
		//Ҫ���͵ĺ�������: �û��� + [�Զ��ظ�] + ��Ϣ
		CString strMsg = strName +  L"[�Զ��ظ�]" + strAutoAnsMsg;
		//ʱ�� + ��������
		strShow = dlg->CatStringShow(L"", strMsg);
		TRACE("�ͻ��� �Զ��ظ��������ǣ�%s", strShow);

		char* szSenfBuf = T2A(strMsg);
		//��ʽ��&��װ ��ɾͿ�ʼ����
		dlg->m_client->Send(szSenfBuf, SEND_MAX_BUF, 0);

		//�ͻ�����Ϣ��ʾ����ʾ����
		dlg->m_list.AddString(strShow);
	}
	//dlg->UpdateData(FALSE);

	CAsyncSocket::OnReceive(nErrorCode);
}
