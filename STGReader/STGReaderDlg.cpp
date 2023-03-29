
// STGReaderDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "STGReader.h"
#include "STGReaderDlg.h"
#include "afxdialogex.h"
#include "ChmFile.h"
#include <vector>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

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

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}


void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CSTGReaderDlg dialog



CSTGReaderDlg::CSTGReaderDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_STGREADER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSTGReaderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST4, ObjTableList);
}

BEGIN_MESSAGE_MAP(CSTGReaderDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_FILE_OPEN, &CSTGReaderDlg::OnBnClickedOpenFile)
	ON_BN_CLICKED(IDCANCEL, &CSTGReaderDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CSTGReaderDlg message handlers

BOOL CSTGReaderDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	ObjTableList.SetExtendedStyle(ObjTableList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	ObjTableList.InsertColumn(0, _T("Номер"), LVCFMT_LEFT, 70);
	ObjTableList.InsertColumn(1, _T("Площадь"), LVCFMT_LEFT, 200);
	ObjTableList.InsertColumn(2, _T("Высота"), LVCFMT_LEFT, 200);
	ObjTableList.InsertColumn(3, _T("Концентрация"), LVCFMT_LEFT, 200);
	ObjTableList.InsertColumn(4, _T("Компонент"), LVCFMT_LEFT, 300);

	return TRUE;  //return TRUE;  // return TRUE  unless you set the focus to a control
}


void CSTGReaderDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSTGReaderDlg::OnPaint()
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

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSTGReaderDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CSTGReaderDlg::OnBnClickedOpenFile()
{
	CFileDialog fileDlg(TRUE, _T("stg"), _T(""), OFN_FILEMUSTEXIST, _T("STG Files (*.stg)|*.stg||"), this);
	if (fileDlg.DoModal() == IDOK)
	{
		CString filePath = fileDlg.GetPathName();
		CChmFile stgFile;
		stgFile.ReadChmFile(filePath);
		obj_peeks = stgFile.peeks;
		ObjTableList.DeleteAllItems();

		for (size_t i = 0; i < obj_peeks.size(); i++)
		{
			CString obj;
			obj.Format(_T("%d"), i + 1);
			ObjTableList.InsertItem(i, obj);

			obj.Format(_T("%.0f"), obj_peeks[i].GetHeight());
			ObjTableList.SetItemText(i, 1, obj);

			obj.Format(_T("%.0f"), stgFile.peeks[i].GetArea());
			ObjTableList.SetItemText(i, 2, obj);

			obj.Format(_T("%.2f"), stgFile.peeks[i].GetConcent());
			ObjTableList.SetItemText(i, 3, obj);

			obj.Format(_T("%s"), stgFile.peeks[i].GetComment());
			ObjTableList.SetItemText(i, 4, obj);
		}
	}
}


void CSTGReaderDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}
