
// AES_ProjectDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "AES_Project.h"
#include "AES_ProjectDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CAES_ProjectDlg 대화 상자



CAES_ProjectDlg::CAES_ProjectDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAES_ProjectDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAES_ProjectDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_AESTAB, encrypt_tab);
}

BEGIN_MESSAGE_MAP(CAES_ProjectDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDCANCEL, &CAES_ProjectDlg::OnBnClickedCancel)
    ON_BN_CLICKED(IDOK, &CAES_ProjectDlg::OnBnClickedOk)
    ON_NOTIFY(TCN_SELCHANGE, IDC_AESTAB, &CAES_ProjectDlg::OnSelchangeAestab)
END_MESSAGE_MAP()


// CAES_ProjectDlg 메시지 처리기

BOOL CAES_ProjectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

    // 탭 아이템 추가
    CRect rect;
    encrypt_tab.GetWindowRect(rect);

    encrypt_tab.InsertItem(0, _T("Encryption"));        // 암호화 탭
    encrypt_tab.InsertItem(1, _T("Decryption"));        // 복호화 탭

    encrypt_tab.SetCurSel(0);

    // 암호화 탭
    e_tab = new CDlgEncryptTab;
    e_tab->Create(IDD_DIALOG_ENCRYPT, &encrypt_tab);
    e_tab->MoveWindow(2, 24, rect.Width()-6, rect.Height()-28);     // 탭 테두리 보이게 조정
    e_tab->ShowWindow(SW_SHOW);

    // 복호화 탭
    d_tab = new CDlgDecryptTab;
    d_tab->Create(IDD_DIALOG_DECRYPT, &encrypt_tab);
    d_tab->MoveWindow(2, 24, rect.Width()-6, rect.Height()-28);
    d_tab->ShowWindow(SW_HIDE);
    
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

BOOL CAES_ProjectDlg::PreTranslateMessage(MSG* pMsg)
{
    switch (pMsg->message)
    {
    case WM_KEYDOWN:
        switch (pMsg->wParam)
        {
        case VK_ESCAPE:
            return TRUE;
        }
    }

    return CDialog::PreTranslateMessage(pMsg);
}

void CAES_ProjectDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CAES_ProjectDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CAES_ProjectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CAES_ProjectDlg::OnBnClickedCancel()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    CDialogEx::OnCancel();
}


void CAES_ProjectDlg::OnBnClickedOk()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    CDialogEx::OnOK();
}


void CAES_ProjectDlg::OnSelchangeAestab(NMHDR *pNMHDR, LRESULT *pResult)
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    if (IDC_AESTAB == pNMHDR->idFrom)
    {
        int select = encrypt_tab.GetCurSel();
        switch (select)
        {
        case 0:
            e_tab->ShowWindow(SW_SHOW);
            d_tab->ShowWindow(SW_HIDE);
            break;
        case 1:
            e_tab->ShowWindow(SW_HIDE);
            d_tab->ShowWindow(SW_SHOW);
            break;
        }
    }

    *pResult = 0;
}
