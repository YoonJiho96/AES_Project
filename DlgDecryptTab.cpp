// DlgDecryptTab.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "AES_Project.h"
#include "DlgDecryptTab.h"
#include "afxdialogex.h"


// CDlgDecryptTab 대화 상자입니다.

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


void CDlgDecryptTab::OnEnChangePlaintext2()
{
    // TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
    // CDialogEx::OnInitDialog() 함수를 재지정 
    //하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
    // 이 알림 메시지를 보내지 않습니다.

    // TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CDlgDecryptTab::OnEnChangeDecryptResult()
{
    // TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
    // CDialogEx::OnInitDialog() 함수를 재지정 
    //하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
    // 이 알림 메시지를 보내지 않습니다.

    // TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CDlgDecryptTab::OnEnChangeDecryptFilePath()
{
    // TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
    // CDialogEx::OnInitDialog() 함수를 재지정 
    //하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
    // 이 알림 메시지를 보내지 않습니다.

    // TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


BOOL CDlgDecryptTab::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // TODO:  여기에 추가 초기화 작업을 추가합니다.

    // 모드 콤보 박스
    m_comboDecModelList.AddString(_T("ECB"));
    m_comboDecModelList.AddString(_T("CBC"));
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

/*
// 복호화 동작 함수
void CDlgDecryptTab::DoDecrypt()
{
    // 모드, 패딩 설정 값 가져오기
    // 선택한 모드
    CString modSelected;
    m_comboEncModeList.GetLBText(m_comboEncModeList.GetCurSel(), modSelected);

    // 선택한 패딩
    CString padSelected;
    m_comboEncPadding.GetLBText(m_comboEncPadding.GetCurSel(), padSelected);

    // input에 입력한 문자열
    CString str;
    GetDlgItemText(IDC_PLAINTEXT, str);

    //CAES_Module *tmd = new CAES_Module();
    //tmd->Test<CryptoPP::AES>(str);
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
    CEdit *p = (CEdit *)GetDlgItem(IDC_ENCRYPT_RESULT);
    p->SetWindowText(result);


    // 다른 대화창이라 안 되는건가?
    CString result2;
    result2 = tmd2->GetDecResult().c_str();

    CEdit *q = (CEdit *)GetDlgItem(IDC_DECRYPT_RESULT);
    q->SetWindowText(result2);

    AfxMessageBox(_T("Encrypted"));
}

*/


