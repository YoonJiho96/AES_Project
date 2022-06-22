#pragma once
#include "afxwin.h"


// CDlgEncryptTab ��ȭ �����Դϴ�.

class CDlgEncryptTab : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgEncryptTab)

public:
	CDlgEncryptTab(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDlgEncryptTab();
    virtual BOOL PreTranslateMessage(MSG* pMsg);
    
// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG_ENCRYPT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnEnChangePlaintext();
    afx_msg void OnEnChangeCrypttext();
    afx_msg void OnBnClickedEncrypt();
    afx_msg void OnEnChangeDecryptResult();
    afx_msg void OnBnClickedEncryptFileBtn();
    CEdit m_encryptFilePath;        // ���� ����
    CEdit m_encryptPlainTxt;        // �Է��� ��
    CEdit m_encryptResultTxt;       // ��ȣȭ ���
    CComboBox m_comboEncModeList;
    virtual BOOL OnInitDialog();
    CComboBox m_comboEncPadding;
    void CDlgEncryptTab::DoEncrypt();
    CString GetInputStr();
};
