#pragma once
#include "afxwin.h"


// CDlgEncryptTab 대화 상자입니다.

class CDlgEncryptTab : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgEncryptTab)

public:
	CDlgEncryptTab(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDlgEncryptTab();
    virtual BOOL PreTranslateMessage(MSG* pMsg);
    
// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_ENCRYPT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnEnChangePlaintext();
    afx_msg void OnEnChangeCrypttext();
    afx_msg void OnBnClickedEncrypt();
    afx_msg void OnEnChangeDecryptResult();
    afx_msg void OnBnClickedEncryptFileBtn();
    CEdit m_encryptFilePath;        // 파일 열기
    CEdit m_encryptPlainTxt;        // 입력한 평문
    CEdit m_encryptResultTxt;       // 암호화 결과
    CComboBox m_comboEncModeList;
    virtual BOOL OnInitDialog();
    CComboBox m_comboEncPadding;
    void CDlgEncryptTab::DoEncrypt();
    CString GetInputStr();
};
