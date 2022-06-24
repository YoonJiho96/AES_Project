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

    // 키 길이 설정에 따른 정의
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


void CDlgEncryptTab::OnEnChangePlaintext()
{
    // TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
    // CDialogEx::OnInitDialog() 함수를 재지정 
    //하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
    // 이 알림 메시지를 보내지 않습니다.

    // TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CDlgEncryptTab::OnEnChangeDecryptResult()
{
    // TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
    // CDialogEx::OnInitDialog() 함수를 재지정 
    //하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
    // 이 알림 메시지를 보내지 않습니다.

    // TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CDlgEncryptTab::OnEnChangeEncryptFilePath()
{
    // TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
    // CDialogEx::OnInitDialog() 함수를 재지정 
    //하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
    // 이 알림 메시지를 보내지 않습니다.

    // TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
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
    // 모드, 패딩 설정 값 가져오기
    // 선택한 모드
    CString modSelected;
    m_comboEncModeList.GetLBText(m_comboEncModeList.GetCurSel(), modSelected);

    // 선택한 패딩
    CString padSelected;
    m_comboEncPadding.GetLBText(m_comboEncPadding.GetCurSel(), padSelected);

    // 키 길이, 블록 크기 설정


    // input에 입력한 문자열
    CString str;
    GetDlgItemText(IDC_PLAINTEXT, str);

    if (str == "")
    {
        AfxMessageBox(_T("Need PlainText!"));
        return;
    }

    // 암호화 결과
    CString result;

    // ------- 암호화 동작 실행 -------- //
    // 모듈 함수 실행
    CAES_Module *tmd2 = new CAES_Module();
    // 리턴 있는 버전
    // result = ((new CAES_Module)->testEncyp2(str, modSelected, ((new CAES_Module)->GetPaddingSch(padSelected)))).c_str();
    // 리턴 없는 버전
    tmd2->testEncyp<CryptoPP::AES>(str, modSelected, padSelected);

    // 결과 받기
    result = tmd2->GetEncResult().c_str();
    // -------- 암호화 종료 --------- // 


    // ---------- 결과 출력 ------------- //
    // 암호문 결과 출력
    // 방법 1
    //CEdit *p = (CEdit *)GetDlgItem(IDC_ENCRYPT_RESULT);
    //p->SetWindowText(result);
    
    // 방법 2
    SetEncResultText(result);


    // 다른 대화창에 결과 출력
    // 다른 대화창이라 안 되는건가? 
    //CString result2;
    //result2 = tmd2->GetDecResult().c_str();
    CAES_ProjectDlg *pFrame = (CAES_ProjectDlg *)AfxGetMainWnd();
    pFrame->d_tab->SetDecEncryptedText(result);

    AfxMessageBox(_T("Encrypted"));
}


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

void setKeyLength(CString k)
{
    
}