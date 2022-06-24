#pragma once
#include "afxwin.h"


// CDlgDecryptTab 대화 상자입니다.

class CDlgDecryptTab : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgDecryptTab)

public:
	CDlgDecryptTab(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDlgDecryptTab();
    virtual BOOL PreTranslateMessage(MSG* pMsg);

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_DECRYPT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
private:
    CEdit m_decryptFilePath;        // 파일 열기
    CEdit m_decryptCryptTxt;        // 암호화된 텍스트
    CEdit m_decryptResultTxt;       // 복호화된 텍스트
    CComboBox m_comboDecModelList;
    CComboBox m_comboDecPaddingList;
    CComboBox m_comboDecryptKeyLength;
public:
    virtual BOOL OnInitDialog();
    afx_msg void OnEnChangePlaintext();
    afx_msg void OnBnClickedDecrypt();
    afx_msg void OnEnChangePlaintext2();
    afx_msg void OnEnChangeDecryptResult();
    afx_msg void OnBnClickedDecryptFileBtn();
    afx_msg void OnEnChangeDecryptFilePath();
    void CDlgDecryptTab::DoDecrypt();
    void SetDecEncryptedText(LPCTSTR str) { m_decryptCryptTxt.SetWindowTextW(str); }
    void SetDecResultText(LPCTSTR str) { m_decryptResultTxt.SetWindowTextW(str); }
};
