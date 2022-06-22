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
    DDX_Control(pDX, IDC_COMBO_ENCRYPT_MODE, m_comboEncModeList);
    DDX_Control(pDX, IDC_COMBO_ENCRYPT_PADDING, m_comboEncPadding);
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
        // �ؽ�Ʈ ��ü ���� (ctrl + A)
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

    OutputDebugString(_T("��ư ���� ����\n"));

    // �ؽ�Ʈ���� �������� ����

    DoEncrypt();
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


BOOL CDlgEncryptTab::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

    // ��� �޺� �ڽ�
    m_comboEncModeList.AddString(_T("ECB"));
    m_comboEncModeList.AddString(_T("CBC"));
    m_comboEncModeList.SetCurSel(0);

    // �е� �޺� �ڽ�
    m_comboEncPadding.AddString(_T("NO_PADDING"));
    m_comboEncPadding.AddString(_T("ZEROS_PADDING"));
    m_comboEncPadding.AddString(_T("PKCS_PADDING"));
    m_comboEncPadding.AddString(_T("ONE_AND_ZEROS_PADDING"));
    m_comboEncPadding.AddString(_T("DEFAULT_PADDING"));
    m_comboEncPadding.SetCurSel(0);


    return TRUE;  // return TRUE unless you set the focus to a control
    // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CDlgEncryptTab::DoEncrypt()
{
    // ���, �е� ���� �� ��������
    // ������ ���
    CString modSelected;
    m_comboEncModeList.GetLBText(m_comboEncModeList.GetCurSel(), modSelected);

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
    tmd2->testEncyp<CryptoPP::AES>(str, modSelected, tmd2->GetPaddingSch(padSelected));

    // ��� �ޱ�
    result = tmd2->strResult.c_str();
    // -------- ��ȣȭ ���� --------- // 


    // ---------- ��� ��� ------------- //
    // ��ȣ�� ��� ���
    CEdit *p = (CEdit *)GetDlgItem(IDC_ENCRYPT_RESULT);
    p->SetWindowText(result);

    AfxMessageBox(_T("Encrypted"));
}