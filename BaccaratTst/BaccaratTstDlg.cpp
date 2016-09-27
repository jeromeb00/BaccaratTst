//
// BaccaratTstDlg.cpp : implementation file
///////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BaccaratTst.h"
#include "BaccaratTstDlg.h"
#include "afxdialogex.h"
#include <algorithm>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;

//
// CAboutDlg dialog used for App About
///////////////////////////////////////////////////////////////////////////////
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

///////////////////////////////////////////////////////////////////////////////
// Notes:
//
CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

///////////////////////////////////////////////////////////////////////////////
// Notes:
//
void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

//
// CBaccaratTstDlg dialog
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Notes:
//
CBaccaratTstDlg::CBaccaratTstDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_BACCARATTST_DIALOG, pParent)
	, mResults(_T(""))
	, mNbDeck(8)
	, mNbShoe(10)
	, mnBankWin(0)
	, mnPlayerWin(0)
	, mnTotalGames(0)
	, mnPlayerBankTie(0)
	, mbCut(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

///////////////////////////////////////////////////////////////////////////////
// Notes:
//
void CBaccaratTstDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_NB_DECK, mNbDeck);
	DDV_MinMaxInt(pDX, mNbDeck, 1, 10);
	DDX_Text(pDX, IDC_NB_SHOE, mNbShoe);
	DDV_MinMaxInt(pDX, mNbShoe, 1, 1000);
	DDX_Text(pDX, IDC_RESULT, mstResult);
	DDX_Control(pDX, IDC_RESULT, mResultCtrl);
}

BEGIN_MESSAGE_MAP(CBaccaratTstDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_NB_SHOE, &CBaccaratTstDlg::OnEnChangeNbShoe)
	ON_EN_CHANGE(IDC_NB_DECK, &CBaccaratTstDlg::OnEnChangeNbDeck)
END_MESSAGE_MAP()


// CBaccaratTstDlg message handlers

///////////////////////////////////////////////////////////////////////////////
// Notes:
//
BOOL CBaccaratTstDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	CDataExchange dx(this, FALSE);
	DoDataExchange(&dx);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

///////////////////////////////////////////////////////////////////////////////
// Notes:
//
void CBaccaratTstDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

///////////////////////////////////////////////////////////////////////////////
// Notes:
//
void CBaccaratTstDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

///////////////////////////////////////////////////////////////////////////////
// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CBaccaratTstDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

///////////////////////////////////////////////////////////////////////////////
// Notes:
//
void CBaccaratTstDlg::OnEnChangeNbDeck()
{
	mstResult.Empty();
	mResultCtrl.SetWindowText(L"");
}

///////////////////////////////////////////////////////////////////////////////
// Notes:
//
void CBaccaratTstDlg::OnEnChangeNbShoe()
{
	mstResult.Empty();
	mResultCtrl.SetWindowText(L"");
}

///////////////////////////////////////////////////////////////////////////////
// Notes:
//
void CBaccaratTstDlg::OnOK()
{
	CDataExchange dx(this, TRUE);
	DoDataExchange(&dx);

	Execute();

	dx.m_bSaveAndValidate = FALSE;
	DoDataExchange(&dx);
}

///////////////////////////////////////////////////////////////////////////////
// Notes:
//
void CBaccaratTstDlg::SetupShoe()
{
	mShoe.clear();
	for (int i = 0; i < mNbDeck; i++)
	{
		for (int j = 0; j < 52; j++)
		{
			mShoe.push_back((j % 13) + 1);
		}
	}
	random_shuffle(mShoe.begin(), mShoe.end());

	int nCutIdx = mNbDeck * 52 - 17;
	mShoe[nCutIdx] += 100;
	mbCut = false;
}

///////////////////////////////////////////////////////////////////////////////
// Notes:
//
char CBaccaratTstDlg::Evaluate(deque<char>& deck)
{
	char sum = 0;
	deque<char>::iterator it = deck.begin();
	while (it != deck.end())
	{
		sum += *it;
		it++;
	}
	return (sum % 10);
}

///////////////////////////////////////////////////////////////////////////////
// Notes:
//
char CBaccaratTstDlg::DealCard(deque<char>& deck)
{
	char card = mShoe[0];
	mbCut |= (card >= 100);
	char cardEff = card % 100;
	if (cardEff >= 10)
		cardEff = 0;
	deck.push_back(cardEff);
	mShoe.pop_front();
	return card;
}

///////////////////////////////////////////////////////////////////////////////
// Notes:
//
void CBaccaratTstDlg::StatUpdate(char evalPlayer, char evalBank)
{
	mnTotalGames++;
	mnPlayerWin += (evalPlayer > evalBank);
	mnBankWin += (evalBank > evalPlayer);
	mnPlayerBankTie += (evalBank == evalPlayer);
}

///////////////////////////////////////////////////////////////////////////////
// Notes:
//
bool CBaccaratTstDlg::IsBankFancyHit(int evalBank, char card3)
{
	if (evalBank > 6)
		return false;

	if (evalBank < 3)
		return true;

	if (evalBank == 3)
		return (card3 != 8);

	if (evalBank == 4)
		return (card3 >= 2) && (card3 <= 7);

	if (evalBank == 5)
		return (card3 >= 4) && (card3 <= 7);

	if (evalBank == 6)
		return (card3 >= 6) && (card3 <= 7);

	return false;
}

///////////////////////////////////////////////////////////////////////////////
// Notes:
//
void CBaccaratTstDlg::Play()
{
	bool bPlay = true;

	deque<char> deckPlayer, deckBank;

	char card = mShoe[0];
	for (char i = 0; i <= card; i++)
	{
		mShoe.pop_front();
	}

	while (bPlay)
	{
		deckPlayer.clear();
		deckBank.clear();

		DealCard(deckPlayer);
		if (mbCut)
		{
			bPlay = false;
		}
		DealCard(deckPlayer);
		DealCard(deckBank);
		DealCard(deckBank);

		char evalPlayer = Evaluate(deckPlayer);
		char evalBank = Evaluate(deckBank);

		if ((evalPlayer < 8) && (evalBank < 8))
		{
			if (evalPlayer > 5)
			{
				if (evalBank <= 5)
				{
					DealCard(deckBank);
				}
			}
			else
			{
				char card3 = DealCard(deckPlayer);
				if (IsBankFancyHit(evalBank, card3))
				{
					DealCard(deckBank);
				}
			}
			evalBank = Evaluate(deckBank);
			evalPlayer = Evaluate(deckPlayer);
		}
		StatUpdate(evalPlayer, evalBank);
	}
}

///////////////////////////////////////////////////////////////////////////////
// Notes:
//
void CBaccaratTstDlg::Execute()
{
	mstResult.Empty();
	mnBankWin = 0;
	mnPlayerWin = 0;
	mnTotalGames = 0;
	mnPlayerBankTie = 0;

	for (int i = 0; i < mNbShoe; i++)
	{
		SetupShoe();
		Play();
	}

	mstResult.Format(L"Total Games:\t%i\r\nBank Wins:\t%i\r\nPlayer Wins:\t%i\r\nTies:\t\t%i",
						mnTotalGames, mnBankWin, mnPlayerWin, mnPlayerBankTie);
}
