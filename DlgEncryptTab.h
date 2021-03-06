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
private:
    CEdit m_encryptFilePath;        // 파일 열기
    CEdit m_encryptPlainTxt;        // 입력한 평문
    CEdit m_encryptResultTxt;       // 암호화 결과

    CComboBox m_comboEncModeList;
    CComboBox m_comboEncPadding;
    CComboBox m_comboEncryptKeyLength;
    
    // 키 설정
    CEdit m_encryptKey;             // 키 입력 칸
    CString m_encryptKeyText;        // 키에 입력된 값
    CString keyLenghtSelected;      // 현재 선택된 키 길이
    int keyLimit = 16;              // 기본 키 길이
    
    // IV 설정
    CEdit m_encryptIV;              // 
    CString m_encryptIVText;        // IV에 입력된 값
public:
    virtual BOOL OnInitDialog();
    afx_msg void OnBnClickedEncrypt();
    afx_msg void OnBnClickedEncryptFileBtn();
    afx_msg void OnCbnSelchangeComboKeylength();
    afx_msg void OnCbnSelchangeComboEncryptMode();

    void CDlgEncryptTab::DoEncrypt();       // 버튼 클릭 동작
    void CDlgEncryptTab::DoEncrypt_back();
    void SetEncPlainText(LPCTSTR str) { m_encryptPlainTxt.SetWindowTextW(str); }    // 평문 입력칸 값 설정
    void SetEncResultText(LPCTSTR str) { m_encryptResultTxt.SetWindowTextW(str); }  // 결과 출력칸 값 설정

    void CheckKeyInput();       // 입력한 KEY 값 유효 확인
    void CheckIvInput();        // 입력한 IV 값 유효 확인

    void CDlgEncryptTab::DoEncryptText();
    void CDlgEncryptTab::DoEncryptFile();
    void CDlgEncryptTab::WriteEncryptFile(CString result);
};
