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
    CString m_encryptKeyText;        // Ű�� �Էµ� ��
    CString keyLenghtSelected;      // ���� ���õ� Ű ����
    int keyLimit = 16;              // �⺻ Ű ����
    
    // IV ����
    CEdit m_encryptIV;              // 
    CString m_encryptIVText;        // IV�� �Էµ� ��
public:
    virtual BOOL OnInitDialog();
    afx_msg void OnBnClickedEncrypt();
    afx_msg void OnBnClickedEncryptFileBtn();
    afx_msg void OnCbnSelchangeComboKeylength();
    afx_msg void OnCbnSelchangeComboEncryptMode();

    void CDlgEncryptTab::DoEncrypt();       // ��ư Ŭ�� ����
    void CDlgEncryptTab::DoEncrypt_back();
    void SetEncPlainText(LPCTSTR str) { m_encryptPlainTxt.SetWindowTextW(str); }    // �� �Է�ĭ �� ����
    void SetEncResultText(LPCTSTR str) { m_encryptResultTxt.SetWindowTextW(str); }  // ��� ���ĭ �� ����

    void CheckKeyInput();       // �Է��� KEY �� ��ȿ Ȯ��
    void CheckIvInput();        // �Է��� IV �� ��ȿ Ȯ��

    void CDlgEncryptTab::DoEncryptText();
    void CDlgEncryptTab::DoEncryptFile();
    void CDlgEncryptTab::WriteEncryptFile(CString result);
};
