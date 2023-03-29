
// STGReaderDlg.h : header file
//

#pragma once
#include <vector>
#include "Cmpeeks.h"

// CSTGReaderDlg dialog
class CSTGReaderDlg : public CDialogEx
{
// Construction
public:
	CSTGReaderDlg(CWnd* pParent = nullptr);	// standard constructor
	afx_msg void OnBnClickedOpenFile();
	

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_STGREADER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	std::vector<cmpeek> obj_peeks;
	CListCtrl ObjTableList;
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
};
