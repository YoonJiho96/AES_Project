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
}


BEGIN_MESSAGE_MAP(CDlgDecryptTab, CDialogEx)
    ON_BN_CLICKED(IDC_DECRYPT, &CDlgDecryptTab::OnBnClickedDecrypt)
    ON_EN_CHANGE(IDC_PLAINTEXT2, &CDlgDecryptTab::OnEnChangePlaintext2)
    ON_EN_CHANGE(IDC_DECRYPT_RESULT, &CDlgDecryptTab::OnEnChangeDecryptResult)
    ON_BN_CLICKED(IDC_DECRYPT_FILE_BTN, &CDlgDecryptTab::OnBnClickedDecryptFileBtn)
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


