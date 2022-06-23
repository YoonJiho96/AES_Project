// DlgDecryptTab.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "AES_Project.h"
#include "DlgDecryptTab.h"
#include "afxdialogex.h"


// CDlgDecryptTab ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CDlgDecryptTab, CDialogEx)

CDlgDecryptTab::CDlgDecryptTab(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgDecryptTab::IDD, pParent)
{
    SetBackgroundColor(RGB(255, 255, 255));
}

CDlgDecryptTab::~CDlgDecryptTab()
{
}

void CDlgDecryptTab::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_DECRYPT_FILE_PATH, m_decryptFilePath);
    DDX_Control(pDX, IDC_PLAINTEXT2, m_decryptCryptTxt);
    DDX_Control(pDX, IDC_DECRYPT_RESULT, m_decryptResultTxt);
    DDX_Control(pDX, IDC_COMBO_DECRYPT_MODE, m_comboDecModelList);
    DDX_Control(pDX, IDC_COMBO_DECRYPT_PADDING, m_comboDecPaddingList);
}


BEGIN_MESSAGE_MAP(CDlgDecryptTab, CDialogEx)
    ON_BN_CLICKED(IDC_DECRYPT, &CDlgDecryptTab::OnBnClickedDecrypt)
    ON_EN_CHANGE(IDC_PLAINTEXT2, &CDlgDecryptTab::OnEnChangePlaintext2)
    ON_EN_CHANGE(IDC_DECRYPT_RESULT, &CDlgDecryptTab::OnEnChangeDecryptResult)
    ON_BN_CLICKED(IDC_DECRYPT_FILE_BTN, &CDlgDecryptTab::OnBnClickedDecryptFileBtn)
    ON_EN_CHANGE(IDC_DECRYPT_FILE_PATH, &CDlgDecryptTab::OnEnChangeDecryptFilePath)
END_MESSAGE_MAP()


// CDlgDecryptTab �޽��� ó�����Դϴ�.
BOOL CDlgDecryptTab::PreTranslateMessage(MSG* pMsg)
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
                if (pWnd == GetDlgItem(IDC_PLAINTEXT2) || pWnd == GetDlgItem(IDC_DECRYPT_RESULT))
                {
                    ((CEdit*)pWnd)->SetSel(0, -1);
                }
            }
        }
    }

    return CDialog::PreTranslateMessage(pMsg);
}

// ��ȣȭ ��ư Ŭ��
void CDlgDecryptTab::OnBnClickedDecrypt()
{
    // TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void CDlgDecryptTab::OnBnClickedDecryptFileBtn()
{
    // TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
    // TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
    TCHAR szFilter[] = _T("Image (*.BMP, *.GIF, *.JPG) | *.BMP;*.GIF;*.JPG | All Files(*.*)|*.*||");
    CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, szFilter);
    if (IDOK == dlg.DoModal())
    {
        CString strPathName = dlg.GetPathName();
        m_decryptFilePath.SetWindowTextW(strPathName);
    }
}


void CDlgDecryptTab::OnEnChangePlaintext2()
{
    // TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
    // CDialogEx::OnInitDialog() �Լ��� ������ 
    //�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
    // �� �˸� �޽����� ������ �ʽ��ϴ�.

    // TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void CDlgDecryptTab::OnEnChangeDecryptResult()
{
    // TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
    // CDialogEx::OnInitDialog() �Լ��� ������ 
    //�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
    // �� �˸� �޽����� ������ �ʽ��ϴ�.

    // TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void CDlgDecryptTab::OnEnChangeDecryptFilePath()
{
    // TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
    // CDialogEx::OnInitDialog() �Լ��� ������ 
    //�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
    // �� �˸� �޽����� ������ �ʽ��ϴ�.

    // TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


BOOL CDlgDecryptTab::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

    // ��� �޺� �ڽ�
    m_comboDecModelList.AddString(_T("ECB"));
    m_comboDecModelList.AddString(_T("CBC"));
    m_comboDecModelList.SetCurSel(0);

    // �е� �޺� �ڽ�
    m_comboDecPaddingList.AddString(_T("DEFAULT_PADDING"));
    m_comboDecPaddingList.AddString(_T("ZEROS_PADDING"));
    m_comboDecPaddingList.AddString(_T("PKCS_PADDING"));
    m_comboDecPaddingList.AddString(_T("ONE_AND_ZEROS_PADDING"));
    m_comboDecPaddingList.AddString(_T("W3C_PADDING"));
    // m_comboDecPaddingList.AddString(_T("NO_PADDING"));
    m_comboDecPaddingList.SetCurSel(0);

    return TRUE;  // return TRUE unless you set the focus to a control
    // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

/*
// ��ȣȭ ���� �Լ�
void CDlgDecryptTab::DoDecrypt()
{
    // ���, �е� ���� �� ��������
    // ������ ���
    CString modSelected;
    m_comboEncModeList.GetLBText(m_comboEncModeList.GetCurSel(), modSelected);

    // ������ �е�
    CString padSelected;
    m_comboEncPadding.GetLBText(m_comboEncPadding.GetCurSel(), padSelected);

    // input�� �Է��� ���ڿ�
    CString str;
    GetDlgItemText(IDC_PLAINTEXT, str);

    //CAES_Module *tmd = new CAES_Module();
    //tmd->Test<CryptoPP::AES>(str);
    CString result;

    // ------- ��ȣȭ ���� ���� -------- //
    // ��� �Լ� ����
    CAES_Module *tmd2 = new CAES_Module();
    // ���� �ִ� ����
    // result = ((new CAES_Module)->testEncyp2(str, modSelected, ((new CAES_Module)->GetPaddingSch(padSelected)))).c_str();
    // ���� ���� ����
    tmd2->testEncyp<CryptoPP::AES>(str, modSelected, padSelected);

    // ��� �ޱ�
    result = tmd2->GetEncResult().c_str();
    // -------- ��ȣȭ ���� --------- // 


    // ---------- ��� ��� ------------- //
    // ��ȣ�� ��� ���
    CEdit *p = (CEdit *)GetDlgItem(IDC_ENCRYPT_RESULT);
    p->SetWindowText(result);


    // �ٸ� ��ȭâ�̶� �� �Ǵ°ǰ�?
    CString result2;
    result2 = tmd2->GetDecResult().c_str();

    CEdit *q = (CEdit *)GetDlgItem(IDC_DECRYPT_RESULT);
    q->SetWindowText(result2);

    AfxMessageBox(_T("Encrypted"));
}

*/


