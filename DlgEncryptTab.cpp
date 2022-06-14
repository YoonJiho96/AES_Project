// DlgEncryptTab.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "AES_Project.h"
#include "DlgEncryptTab.h"
#include "afxdialogex.h"


// CDlgEncryptTab ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CDlgEncryptTab, CDialogEx)

CDlgEncryptTab::CDlgEncryptTab(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgEncryptTab::IDD, pParent)
{
    SetBackgroundColor(RGB(255, 255, 255));
}

CDlgEncryptTab::~CDlgEncryptTab()
{
}

void CDlgEncryptTab::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_ENCRYPT_FILE_PATH, m_encryptFilePath);
    DDX_Control(pDX, IDC_PLAINTEXT, m_encryptPlainTxt);
    DDX_Control(pDX, IDC_ENCRYPT_RESULT, m_encryptResultTxt);
}


BEGIN_MESSAGE_MAP(CDlgEncryptTab, CDialogEx)
    ON_EN_CHANGE(IDC_PLAINTEXT, &CDlgEncryptTab::OnEnChangePlaintext)
    ON_EN_CHANGE(IDC_ENCRYPT_RESULT, &CDlgEncryptTab::OnEnChangeDecryptResult)
    ON_BN_CLICKED(IDC_ENCRYPT, &CDlgEncryptTab::OnBnClickedEncrypt)
    ON_BN_CLICKED(IDC_ENCRYPT_FILE_BTN, &CDlgEncryptTab::OnBnClickedEncryptFileBtn)
END_MESSAGE_MAP()


// CDlgEncryptTab �޽��� ó�����Դϴ�.
BOOL CDlgEncryptTab::PreTranslateMessage(MSG* pMsg)
{
    if (pMsg->message == WM_KEYDOWN)
    {
        if (pMsg->wParam == VK_ESCAPE)
            return TRUE;
        // �ؽ�Ʈ ��ü ����
        else if (pMsg->wParam == 'A' && GetKeyState(VK_CONTROL) < 0)
        {
            CWnd *pWnd = GetFocus();
            if (pWnd)
            {
                if (pWnd == GetDlgItem(IDC_PLAINTEXT) || pWnd == GetDlgItem(IDC_ENCRYPT_RESULT))
                {
                    ((CEdit*)pWnd)->SetSel(0, -1);
                }
            }
        }
    }
    return CDialog::PreTranslateMessage(pMsg);
}


// ��ȣȭ ���� ����
void CDlgEncryptTab::OnBnClickedEncryptFileBtn()
{
    // ���� ���� ���̾�α�
    TCHAR szFilter[] = _T("Image (*.BMP, *.GIF, *.JPG) | *.BMP;*.GIF;*.JPG | All Files(*.*)|*.*||");
    CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, szFilter);
    if (IDOK == dlg.DoModal()) 
    {
        CString strPathName = dlg.GetPathName();
        m_encryptFilePath.SetWindowTextW(strPathName);
    }
}


// ��ȣȭ �ϱ� ��ư Ŭ��
void CDlgEncryptTab::OnBnClickedEncrypt()
{
    // TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

    // �ؽ�Ʈ���� �������� ����
    OutputDebugString(_T("��ư ���� ����\n"));

    CAES_Module *tmd = new CAES_Module();
    tmd->Test<CryptoPP::AES>();
    /*
    CString str;
    GetDlgItemText(IDC_PLAINTEXT, str);
    OutputDebugString(str);
    */
    AfxMessageBox(_T("Encrypted"));
}


void CDlgEncryptTab::OnEnChangePlaintext()
{
    // TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
    // CDialogEx::OnInitDialog() �Լ��� ������ 
    //�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
    // �� �˸� �޽����� ������ �ʽ��ϴ�.

    // TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void CDlgEncryptTab::OnEnChangeDecryptResult()
{
    // TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
    // CDialogEx::OnInitDialog() �Լ��� ������ 
    //�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
    // �� �˸� �޽����� ������ �ʽ��ϴ�.

    // TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}
