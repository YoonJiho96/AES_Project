
// AES_ProjectDlg.h : 헤더 파일
//

#pragma once
#include "afxcmn.h"
#include "DlgEncryptTab.h"
#include "DlgDecryptTab.h"

// CAES_ProjectDlg 대화 상자
class CAES_ProjectDlg : public CDialogEx
{
// 생성입니다.
public:
	CAES_ProjectDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.
    virtual BOOL PreTranslateMessage(MSG* pMsg);
    CDlgEncryptTab* e_tab;
    CDlgDecryptTab* d_tab;
// 대화 상자 데이터입니다.
	enum { IDD = IDD_AES_PROJECT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedCancel();
    afx_msg void OnBnClickedOk();
    afx_msg void OnBnClickedEncrypt();      // 암호화
    afx_msg void OnBnClickedDecrypt();      // 복호화
    afx_msg void OnEnChangePlaintext();
    CTabCtrl encrypt_tab;
    afx_msg void OnSelchangeAestab(NMHDR *pNMHDR, LRESULT *pResult);
};
