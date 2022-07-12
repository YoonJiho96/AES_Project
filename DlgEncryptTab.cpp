// DlgEncryptTab.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "AES_Project.h"
#include "DlgEncryptTab.h"
#include "afxdialogex.h"
#include "AES_ProjectDlg.h"
#include <string.h>


// CDlgEncryptTab 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDlgEncryptTab, CDialogEx)

CDlgEncryptTab::CDlgEncryptTab(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgEncryptTab::IDD, pParent)
    , m_encryptKeyText(_T(""))
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

    // 키 길이 설정에 따른 정의
    DDX_Control(pDX, IDC_ENCRYPT_KEY, m_encryptKey);
    DDX_Text(pDX, IDC_ENCRYPT_KEY, m_encryptKeyText);
    DDV_MaxChars(pDX, m_encryptKeyText, keyLimit);
    DDX_Text(pDX, IDC_ENCRYPT_IV, m_encryptIVText);
	DDV_MaxChars(pDX, m_encryptIVText, 16);
}


BEGIN_MESSAGE_MAP(CDlgEncryptTab, CDialogEx)
    ON_BN_CLICKED(IDC_ENCRYPT, &CDlgEncryptTab::OnBnClickedEncrypt)
    ON_BN_CLICKED(IDC_ENCRYPT_FILE_BTN, &CDlgEncryptTab::OnBnClickedEncryptFileBtn)
    ON_CBN_SELCHANGE(IDC_COMBO_KEYLENGTH, &CDlgEncryptTab::OnCbnSelchangeComboKeylength)
    ON_CBN_SELCHANGE(IDC_COMBO_ENCRYPT_MODE, &CDlgEncryptTab::OnCbnSelchangeComboEncryptMode)
END_MESSAGE_MAP()


// CDlgEncryptTab 메시지 처리기입니다.
BOOL CDlgEncryptTab::PreTranslateMessage(MSG* pMsg)
{
    if (pMsg->message == WM_KEYDOWN)
    {
        if (pMsg->wParam == VK_ESCAPE)
            return TRUE;
        // 텍스트 전체 선택 (ctrl + A)
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


// 암호화 파일 열기
void CDlgEncryptTab::OnBnClickedEncryptFileBtn()
{
    // 파일 열기 다이얼로그
    TCHAR szFilter[] = _T("Image (*.BMP, *.GIF, *.JPG) | *.BMP;*.GIF;*.JPG | All Files(*.*)|*.*||");
    CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, szFilter);
    if (IDOK == dlg.DoModal()) 
    {
        CString strPathName = dlg.GetPathName();
        m_encryptFilePath.SetWindowTextW(strPathName);
    }
}


// 암호화 하기 버튼 클릭
void CDlgEncryptTab::OnBnClickedEncrypt()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

    OutputDebugString(_T("버튼 동작 시작\n"));

    // 텍스트인지 파일인지 구분

    DoEncrypt();
}


BOOL CDlgEncryptTab::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // TODO:  여기에 추가 초기화 작업을 추가합니다.

    // 키 길이
    m_comboEncryptKeyLength.AddString(_T("16"));
    m_comboEncryptKeyLength.AddString(_T("32"));
    m_comboEncryptKeyLength.SetCurSel(0);
    keyLenghtSelected = "16";

    // 모드 콤보 박스
    m_comboEncModeList.AddString(_T("CBC"));
    m_comboEncModeList.AddString(_T("ECB"));
    m_comboEncModeList.SetCurSel(0);

    // 패딩 콤보 박스
    m_comboEncPadding.AddString(_T("DEFAULT_PADDING"));
    m_comboEncPadding.AddString(_T("ZEROS_PADDING"));
    m_comboEncPadding.AddString(_T("PKCS_PADDING"));
    m_comboEncPadding.AddString(_T("ONE_AND_ZEROS_PADDING"));
    m_comboEncPadding.AddString(_T("W3C_PADDING"));
    // m_comboEncPadding.AddString(_T("NO_PADDING"));
    m_comboEncPadding.SetCurSel(0);


    return TRUE;  // return TRUE unless you set the focus to a control
    // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


// 암호화 동작 함수
void CDlgEncryptTab::DoEncrypt()
{
    // ------ 모드, 패딩 설정 값 가져오기 ------ //
    // 선택한 모드
    CString modSelected;
    m_comboEncModeList.GetLBText(m_comboEncModeList.GetCurSel(), modSelected);

    // 선택한 패딩
    CString padSelected;
    m_comboEncPadding.GetLBText(m_comboEncPadding.GetCurSel(), padSelected);

    // ------- Plain Text 초기화 ------ //
    // input에 입력한 문자열
    CString str;
    GetDlgItemText(IDC_PLAINTEXT, str);

    // 문자열 검사
    if (str == "")
    {
        AfxMessageBox(_T("Need PlainText!"));
        return;
    }

    // -------- KEY, IV 초기화 -------- //
    CString keyInput;
    m_encryptKey.GetWindowText(keyInput);
    CString ivInput;
    m_encryptIV.GetWindowText(ivInput);

    // 길이 조절 -> UI 내에서 제한을 둬서 필요 여부 고려.
    /*
    CString curKeyLen;
    m_comboEncryptKeyLength.GetLBText(m_comboEncryptKeyLength.GetCurSel(), curKeyLen);

    byte KEY[CryptoPP::AES::DEFAULT_KEYLENGTH] = { 0, };
    if (curKeyLen == "32")
    {
        byte Temp[CryptoPP::AES::MAX_KEYLENGTH] = { 0, };
        memcpy(Temp, KEY, 32);
    }
    */

    // 키 값
    byte *KEY;
    KEY = new byte[keyInput.GetLength() + 1];
    KEY = (byte*)(LPCTSTR)keyInput;

    // IV 값
    byte *IV;
    IV = new byte[ivInput.GetLength() + 1];
    IV = (byte*)(LPCTSTR)ivInput;

    // 암호화 결과
    CString result;

    // ------- 암호화 동작 실행 -------- //
    // 모듈 함수 실행
    CAES_Module *tmd2 = new CAES_Module();

    // 암호화 실행
    tmd2->DoEncryptResult<CryptoPP::AES>(str, modSelected, padSelected, KEY, IV);
    // -------- 암호화 종료 --------- // 


    // 결과 받기
    result = tmd2->GetEncResult().c_str();


    // ---------- 결과 출력 ------------- //
    // 암호문 결과 출력
    // 방법 1
    //CEdit *p = (CEdit *)GetDlgItem(IDC_ENCRYPT_RESULT);
    //p->SetWindowText(result);
    
    // 방법 2
    SetEncResultText(result);
    // --------- 출력 종료 -------------- //


    // ------ 복호탭에 결과 출력 -------- //
    // 메인 프레임 접근 -> 거기서 정의된 탭을 통해 다른 창 접근
    CAES_ProjectDlg *pFrame = (CAES_ProjectDlg *)AfxGetMainWnd();
    pFrame->d_tab->SetDecEncryptedText(result);

    AfxMessageBox(_T("Encrypted"));
}


// 키 입력시 동작
void CDlgEncryptTab::OnCbnSelchangeComboKeylength()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

    // 키 길이 설정
    m_comboEncryptKeyLength.GetLBText(m_comboEncryptKeyLength.GetCurSel(), keyLenghtSelected);
    if (keyLenghtSelected == "16")
    {
        OutputDebugString(_T("16\n"));
        keyLimit = 16;

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
    else if (keyLenghtSelected == "32")
    {
        OutputDebugString(_T("32\n"));
        keyLimit = 32;
    }
    // DoDataExchange() 호출용
    UpdateData();
}

void CDlgEncryptTab::OnCbnSelchangeComboEncryptMode()
{
    // ECB 모드에서 IV 값 미사용으로 비활성.
    // 선택한 모드
    CString modSelected;
    m_comboEncModeList.GetLBText(m_comboEncModeList.GetCurSel(), modSelected);

    if (modSelected == "ECB")
    {
        m_encryptIV.EnableWindow(false);
    }
    else
    {
        m_encryptIV.EnableWindow(true);
    }
}
