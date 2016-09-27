
// BaccaratTstDlg.h : header file
//

#pragma once

#include <deque>
#include "afxwin.h"

// CBaccaratTstDlg dialog
class CBaccaratTstDlg : public CDialogEx
{
// Construction
public:
	CBaccaratTstDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BACCARATTST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	std::deque<char> mShoe;
	bool mbCut;

	int mnBankWin;
	int mnPlayerWin;
	int mnTotalGames;
	int mnPlayerBankTie;

	void SetupShoe();
	void Play();
	void Execute();
	char DealCard(std::deque<char>& deck);
	char Evaluate(std::deque<char>& deck);
	void StatUpdate(char evalPlayer, char evalBank);
	bool IsBankFancyHit(int evalBank, char card3);

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeNbShoe();
	CString mResults;
	int mNbDeck;
	int mNbShoe;
	CString mstResult;
	virtual void OnOK();
	afx_msg void OnEnChangeNbDeck();
	CStatic mResultCtrl;
};
