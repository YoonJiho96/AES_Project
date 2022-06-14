
// AES_ProjectDlg.h : ��� ����
//

#pragma once
#include "afxcmn.h"
#include "DlgEncryptTab.h"
#include "DlgDecryptTab.h"

// CAES_ProjectDlg ��ȭ ����
class CAES_ProjectDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CAES_ProjectDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.
    virtual BOOL PreTranslateMessage(MSG* pMsg);
    CDlgEncryptTab* e_tab;
    CDlgDecryptTab* d_tab;
// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_AES_PROJECT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedCancel();
    afx_msg void OnBnClickedOk();
    afx_msg void OnBnClickedEncrypt();      // ��ȣȭ
    afx_msg void OnBnClickedDecrypt();      // ��ȣȭ
    afx_msg void OnEnChangePlaintext();
    CTabCtrl encrypt_tab;
    afx_msg void OnSelchangeAestab(NMHDR *pNMHDR, LRESULT *pResult);
};
