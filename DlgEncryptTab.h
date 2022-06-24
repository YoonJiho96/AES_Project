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
private:
    CEdit m_encryptFilePath;        // ���� ����
    CEdit m_encryptPlainTxt;        // �Է��� ��
    CEdit m_encryptResultTxt;       // ��ȣȭ ���

    CComboBox m_comboEncModeList;
    CComboBox m_comboEncPadding;
    CComboBox m_comboEncryptKeyLength;
    
    // Ű ����
    CEdit m_encryptKey;             // Ű �Է� ĭ
    CString keyLenghtSelected;      // ���� ���õ� Ű ����
    CString m_keyLengthText;        // Ű�� �Էµ� ��
    int keyLimit = 16;              // �⺻ Ű ����
    
    // IV ����
    CEdit m_encryptIV;
public:
    virtual BOOL OnInitDialog();
    afx_msg void OnEnChangePlaintext();
    afx_msg void OnEnChangeCrypttext();
    afx_msg void OnBnClickedEncrypt();
    afx_msg void OnEnChangeDecryptResult();
    afx_msg void OnBnClickedEncryptFileBtn();
    afx_msg void OnEnChangeEncryptFilePath();
    afx_msg void OnCbnSelchangeComboKeylength();
    void CDlgEncryptTab::DoEncrypt();       // ��ư Ŭ�� ����
    void SetEncPlainText(LPCTSTR str) { m_encryptPlainTxt.SetWindowTextW(str); }    // �� �Է�ĭ �� ����
    void SetEncResultText(LPCTSTR str) { m_encryptResultTxt.SetWindowTextW(str); }  // ��� ���ĭ �� ����
    CString m_encryptIVText;
};
