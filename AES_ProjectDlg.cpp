
// AES_ProjectDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "AES_Project.h"
#include "AES_ProjectDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
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


// CAES_ProjectDlg ��ȭ ����



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


// CAES_ProjectDlg �޽��� ó����

BOOL CAES_ProjectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
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

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

    // �� ������ �߰�
    CRect rect;
    encrypt_tab.GetWindowRect(rect);

    encrypt_tab.InsertItem(0, _T("Encryption"));        // ��ȣȭ ��
    encrypt_tab.InsertItem(1, _T("Decryption"));        // ��ȣȭ ��

    encrypt_tab.SetCurSel(0);

    // ��ȣȭ ��
    e_tab = new CDlgEncryptTab;
    e_tab->Create(IDD_DIALOG_ENCRYPT, &encrypt_tab);
    e_tab->MoveWindow(2, 24, rect.Width()-6, rect.Height()-28);     // �� �׵θ� ���̰� ����
    e_tab->ShowWindow(SW_SHOW);

    // ��ȣȭ ��
    d_tab = new CDlgDecryptTab;
    d_tab->Create(IDD_DIALOG_DECRYPT, &encrypt_tab);
    d_tab->MoveWindow(2, 24, rect.Width()-6, rect.Height()-28);
    d_tab->ShowWindow(SW_HIDE);
    
	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CAES_ProjectDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CAES_ProjectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CAES_ProjectDlg::OnBnClickedCancel()
{
    // TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
    CDialogEx::OnCancel();
}


void CAES_ProjectDlg::OnBnClickedOk()
{
    // TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
    CDialogEx::OnOK();
}


void CAES_ProjectDlg::OnSelchangeAestab(NMHDR *pNMHDR, LRESULT *pResult)
{
    // TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
