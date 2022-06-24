// DlgEncryptTab.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "AES_Project.h"
#include "DlgEncryptTab.h"
#include "afxdialogex.h"
#include "AES_ProjectDlg.h"
#include <string.h>


// CDlgEncryptTab ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CDlgEncryptTab, CDialogEx)

CDlgEncryptTab::CDlgEncryptTab(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgEncryptTab::IDD, pParent)
    , m_keyLengthText(_T(""))
    , m_encryptIVText(_T(""))
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
    DDX_Control(pDX, IDC_COMBO_KEYLENGTH, m_comboEncryptKeyLength);
    DDX_Control(pDX, IDC_ENCRYPT_IV, m_encryptIV);

    // Ű ���� ������ ���� ����
    DDX_Control(pDX, IDC_ENCRYPT_KEY, m_encryptKey);
    DDX_Text(pDX, IDC_ENCRYPT_KEY, m_keyLengthText);
    DDV_MaxChars(pDX, m_keyLengthText, keyLimit);
    DDX_Text(pDX, IDC_ENCRYPT_IV, m_encryptIVText);
	DDV_MaxChars(pDX, m_encryptIVText, 16);
}


BEGIN_MESSAGE_MAP(CDlgEncryptTab, CDialogEx)
    ON_EN_CHANGE(IDC_PLAINTEXT, &CDlgEncryptTab::OnEnChangePlaintext)
    ON_EN_CHANGE(IDC_ENCRYPT_RESULT, &CDlgEncryptTab::OnEnChangeDecryptResult)
    ON_BN_CLICKED(IDC_ENCRYPT, &CDlgEncryptTab::OnBnClickedEncrypt)
    ON_BN_CLICKED(IDC_ENCRYPT_FILE_BTN, &CDlgEncryptTab::OnBnClickedEncryptFileBtn)
    ON_EN_CHANGE(IDC_ENCRYPT_FILE_PATH, &CDlgEncryptTab::OnEnChangeEncryptFilePath)
    ON_CBN_SELCHANGE(IDC_COMBO_KEYLENGTH, &CDlgEncryptTab::OnCbnSelchangeComboKeylength)
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


void CDlgEncryptTab::OnEnChangeEncryptFilePath()
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

    // Ű ����
    m_comboEncryptKeyLength.AddString(_T("16"));
    m_comboEncryptKeyLength.AddString(_T("32"));
    m_comboEncryptKeyLength.SetCurSel(0);
    keyLenghtSelected = "16";

    // ��� �޺� �ڽ�
    m_comboEncModeList.AddString(_T("CBC"));
    m_comboEncModeList.AddString(_T("ECB"));
    m_comboEncModeList.SetCurSel(0);

    // �е� �޺� �ڽ�
    m_comboEncPadding.AddString(_T("DEFAULT_PADDING"));
    m_comboEncPadding.AddString(_T("ZEROS_PADDING"));
    m_comboEncPadding.AddString(_T("PKCS_PADDING"));
    m_comboEncPadding.AddString(_T("ONE_AND_ZEROS_PADDING"));
    m_comboEncPadding.AddString(_T("W3C_PADDING"));
    // m_comboEncPadding.AddString(_T("NO_PADDING"));
    m_comboEncPadding.SetCurSel(0);


    return TRUE;  // return TRUE unless you set the focus to a control
    // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


// ��ȣȭ ���� �Լ�
void CDlgEncryptTab::DoEncrypt()
{
    // ���, �е� ���� �� ��������
    // ������ ���
    CString modSelected;
    m_comboEncModeList.GetLBText(m_comboEncModeList.GetCurSel(), modSelected);

    // ������ �е�
    CString padSelected;
    m_comboEncPadding.GetLBText(m_comboEncPadding.GetCurSel(), padSelected);

    // Ű ����, ��� ũ�� ����


    // input�� �Է��� ���ڿ�
    CString str;
    GetDlgItemText(IDC_PLAINTEXT, str);

    if (str == "")
    {
        AfxMessageBox(_T("Need PlainText!"));
        return;
    }

    // ��ȣȭ ���
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
    // ��� 1
    //CEdit *p = (CEdit *)GetDlgItem(IDC_ENCRYPT_RESULT);
    //p->SetWindowText(result);
    
    // ��� 2
    SetEncResultText(result);


    // �ٸ� ��ȭâ�� ��� ���
    // �ٸ� ��ȭâ�̶� �� �Ǵ°ǰ�? 
    //CString result2;
    //result2 = tmd2->GetDecResult().c_str();
    CAES_ProjectDlg *pFrame = (CAES_ProjectDlg *)AfxGetMainWnd();
    pFrame->d_tab->SetDecEncryptedText(result);

    AfxMessageBox(_T("Encrypted"));
}


void CDlgEncryptTab::OnCbnSelchangeComboKeylength()
{
    // TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

    // Ű ���� ����
    m_comboEncryptKeyLength.GetLBText(m_comboEncryptKeyLength.GetCurSel(), keyLenghtSelected);
    if (keyLenghtSelected == "16")
    {
        OutputDebugString(_T("16\n"));
        keyLimit = 16;

        // �Է��� Ű
        CString str;
        GetDlgItemText(IDC_ENCRYPT_KEY, str);

        // ���� ����
        if (str.GetLength() > 16)
        {
            string left = string(CT2CA(str));
            left = left.substr(0, 16);
            str = left.c_str();
            SetDlgItemText(IDC_ENCRYPT_KEY, str);
        }
    }
    else if (keyLenghtSelected == "32")
    {
        OutputDebugString(_T("32\n"));
        keyLimit = 32;
    }
    // DoDataExchange() ȣ���
    UpdateData();
}

void setKeyLength(CString k)
{
    
}