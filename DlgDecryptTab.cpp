// DlgDecryptTab.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "AES_Project.h"
#include "DlgDecryptTab.h"
#include "afxdialogex.h"
#include "AES_ProjectDlg.h"


// CDlgDecryptTab ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CDlgDecryptTab, CDialogEx)

CDlgDecryptTab::CDlgDecryptTab(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgDecryptTab::IDD, pParent)
    , m_decryptKeyText(_T(""))
    , m_decryptIVText(_T(""))
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

    DDX_Control(pDX, IDC_COMBO_KEYLENGTH2, m_comboDecryptKeyLength);
    DDX_Control(pDX, IDC_DECRYPT_KEY, m_decryptKey);
    DDX_Text(pDX, IDC_DECRYPT_KEY, m_decryptKeyText);
    DDV_MaxChars(pDX, m_decryptKeyText, keyLimit_dec);

    DDX_Control(pDX, IDC_DECRYPT_IV, m_decryptIV);
    DDX_Text(pDX, IDC_DECRYPT_IV, m_decryptIVText);
	DDV_MaxChars(pDX, m_decryptIVText, 16);
}


BEGIN_MESSAGE_MAP(CDlgDecryptTab, CDialogEx)
    ON_BN_CLICKED(IDC_DECRYPT, &CDlgDecryptTab::OnBnClickedDecrypt)
    ON_BN_CLICKED(IDC_DECRYPT_FILE_BTN, &CDlgDecryptTab::OnBnClickedDecryptFileBtn)
    ON_CBN_SELCHANGE(IDC_COMBO_DECRYPT_MODE, &CDlgDecryptTab::OnCbnSelchangeComboDecryptMode)
    ON_CBN_SELCHANGE(IDC_COMBO_KEYLENGTH2, &CDlgDecryptTab::OnCbnSelchangeComboKeylength2)
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
    DoDecrypt();
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


BOOL CDlgDecryptTab::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

    // Ű ���� �޺� �ڽ�
    m_comboDecryptKeyLength.AddString(_T("16"));
    m_comboDecryptKeyLength.AddString(_T("32"));
    m_comboDecryptKeyLength.SetCurSel(0);

    // ��� �޺� �ڽ�
    m_comboDecModelList.AddString(_T("CBC"));
    m_comboDecModelList.AddString(_T("ECB"));
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


// ��ȣȭ ���� �Լ�
void CDlgDecryptTab::DoDecrypt()
{
    // ���, �е� ���� �� ��������
    // ������ ���
    CString modSelected;
    m_comboDecModelList.GetLBText(m_comboDecModelList.GetCurSel(), modSelected);

    // ������ �е�
    CString padSelected;
    m_comboDecPaddingList.GetLBText(m_comboDecPaddingList.GetCurSel(), padSelected);

    // input�� �Է��� ���ڿ�
    CString str;
    GetDlgItemText(IDC_PLAINTEXT2, str);

    // ���ڿ� �˻�
    if (str == "")
    {
        AfxMessageBox(_T("Need PlainText!"));
        return;
    }

    // -------- KEY, IV �ʱ�ȭ -------- //
    CString keyInput;
    m_decryptKey.GetWindowText(keyInput);
    CString ivInput;
    m_decryptIV.GetWindowText(ivInput);

    // Ű ��
    byte *KEY;
    KEY = new byte[keyInput.GetLength() + 1];
    KEY = (byte*)(LPCTSTR)keyInput;

    // IV ��
    byte *IV;
    IV = new byte[ivInput.GetLength() + 1];
    IV = (byte*)(LPCTSTR)ivInput;


    // ------- ��ȣȭ ���� ���� -------- //
    // ��� �Լ� ����
    CAES_Module *tmd2 = new CAES_Module();
    tmd2->DoDecryptResult<CryptoPP::AES>(str, modSelected, padSelected, KEY, IV);   // ��ȣȭ ����
    // -------- ��ȣȭ ���� --------- // 

    // ---------- ��� ��� ------------- //
    // ����� ȹ��
    CString result;
    result = tmd2->GetDecResult().c_str();

    SetDecResultText(result);    // �ؽ�Ʈ �� ���

    AfxMessageBox(_T("Decrypted"));
}


void CDlgDecryptTab::OnCbnSelchangeComboDecryptMode()
{
    // ECB ��忡�� IV �� �̻������ ��Ȱ��.
    // ������ ���
    CString modSelected;
    m_comboDecModelList.GetLBText(m_comboDecModelList.GetCurSel(), modSelected);

    if (modSelected == "ECB")
    {
        m_decryptIV.EnableWindow(false);
    }
    else
    {
        m_decryptIV.EnableWindow(true);
    }
}


void CDlgDecryptTab::OnCbnSelchangeComboKeylength2()
{
    // TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

    // Ű ���� ����
    m_comboDecryptKeyLength.GetLBText(m_comboDecryptKeyLength.GetCurSel(), keyLengthSelected_dec);
    if (keyLengthSelected_dec == "16")
    {
        OutputDebugString(_T("16\n"));
        keyLimit_dec = 16;

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
    else if (keyLengthSelected_dec == "32")
    {
        OutputDebugString(_T("32\n"));
        keyLimit_dec = 32;
    }
    // DoDataExchange() ȣ���
    UpdateData();
}
