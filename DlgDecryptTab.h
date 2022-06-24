#pragma once
#include "afxwin.h"


// CDlgDecryptTab ��ȭ �����Դϴ�.

class CDlgDecryptTab : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgDecryptTab)

public:
	CDlgDecryptTab(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDlgDecryptTab();
    virtual BOOL PreTranslateMessage(MSG* pMsg);

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG_DECRYPT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
private:
    CEdit m_decryptFilePath;        // ���� ����
    CEdit m_decryptCryptTxt;        // ��ȣȭ�� �ؽ�Ʈ
    CEdit m_decryptResultTxt;       // ��ȣȭ�� �ؽ�Ʈ
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
