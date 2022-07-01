// DlgDecryptTab.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "AES_Project.h"
#include "DlgDecryptTab.h"
#include "afxdialogex.h"
#include "AES_ProjectDlg.h"


// CDlgDecryptTab 대화 상자입니다.

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


// CDlgDecryptTab 메시지 처리기입니다.
BOOL CDlgDecryptTab::PreTranslateMessage(MSG* pMsg)
{
    if (pMsg->message == WM_KEYDOWN)
    {
        if (pMsg->wParam == VK_ESCAPE)
            return TRUE;
        // 텍스트 전체 선택
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

// 복호화 버튼 클릭
void CDlgDecryptTab::OnBnClickedDecrypt()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    DoDecrypt();
}


void CDlgDecryptTab::OnBnClickedDecryptFileBtn()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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

    // TODO:  여기에 추가 초기화 작업을 추가합니다.

    // 키 길이 콤보 박스
    m_comboDecryptKeyLength.AddString(_T("16"));
    m_comboDecryptKeyLength.AddString(_T("32"));
    m_comboDecryptKeyLength.SetCurSel(0);

    // 모드 콤보 박스
    m_comboDecModelList.AddString(_T("CBC"));
    m_comboDecModelList.AddString(_T("ECB"));
    m_comboDecModelList.SetCurSel(0);

    // 패딩 콤보 박스
    m_comboDecPaddingList.AddString(_T("DEFAULT_PADDING"));
    m_comboDecPaddingList.AddString(_T("ZEROS_PADDING"));
    m_comboDecPaddingList.AddString(_T("PKCS_PADDING"));
    m_comboDecPaddingList.AddString(_T("ONE_AND_ZEROS_PADDING"));
    m_comboDecPaddingList.AddString(_T("W3C_PADDING"));
    // m_comboDecPaddingList.AddString(_T("NO_PADDING"));
    m_comboDecPaddingList.SetCurSel(0);

    return TRUE;  // return TRUE unless you set the focus to a control
    // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


// 복호화 동작 함수
void CDlgDecryptTab::DoDecrypt()
{
    // 모드, 패딩 설정 값 가져오기
    // 선택한 모드
    CString modSelected;
    m_comboDecModelList.GetLBText(m_comboDecModelList.GetCurSel(), modSelected);

    // 선택한 패딩
    CString padSelected;
    m_comboDecPaddingList.GetLBText(m_comboDecPaddingList.GetCurSel(), padSelected);

    // input에 입력한 문자열
    CString str;
    GetDlgItemText(IDC_PLAINTEXT2, str);

    // 문자열 검사
    if (str == "")
    {
        AfxMessageBox(_T("Need PlainText!"));
        return;
    }

    // -------- KEY, IV 초기화 -------- //
    CString keyInput;
    m_decryptKey.GetWindowText(keyInput);
    CString ivInput;
    m_decryptIV.GetWindowText(ivInput);

    // 키 값
    byte *KEY;
    KEY = new byte[keyInput.GetLength() + 1];
    KEY = (byte*)(LPCTSTR)keyInput;

    // IV 값
    byte *IV;
    IV = new byte[ivInput.GetLength() + 1];
    IV = (byte*)(LPCTSTR)ivInput;


    // ------- 암호화 동작 실행 -------- //
    // 모듈 함수 실행
    CAES_Module *tmd2 = new CAES_Module();
    tmd2->DoDecryptResult<CryptoPP::AES>(str, modSelected, padSelected, KEY, IV);   // 복호화 실행
    // -------- 암호화 종료 --------- // 

    // ---------- 결과 출력 ------------- //
    // 결과값 획득
    CString result;
    result = tmd2->GetDecResult().c_str();

    SetDecResultText(result);    // 텍스트 값 출력

    AfxMessageBox(_T("Decrypted"));
}


void CDlgDecryptTab::OnCbnSelchangeComboDecryptMode()
{
    // ECB 모드에서 IV 값 미사용으로 비활성.
    // 선택한 모드
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
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

    // 키 길이 설정
    m_comboDecryptKeyLength.GetLBText(m_comboDecryptKeyLength.GetCurSel(), keyLengthSelected_dec);
    if (keyLengthSelected_dec == "16")
    {
        OutputDebugString(_T("16\n"));
        keyLimit_dec = 16;

        // 입력한 키
        CString str;
        GetDlgItemText(IDC_ENCRYPT_KEY, str);

        // 길이 제한
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
    // DoDataExchange() 호출용
    UpdateData();
}
