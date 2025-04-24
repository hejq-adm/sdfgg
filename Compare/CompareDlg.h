#pragma once
#include "Resource.h"
// CCompareDlg 对话框
#include "..\\Interface\\ICompareInInterface.h"

#include "LeftView.h"
#include "CenterView.h"
#include "RightView.h"

class CCompareDlg : public CDialogEx , ICompareInInterface
{
	DECLARE_DYNAMIC(CCompareDlg)

public:
	CCompareDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCompareDlg();
	static CCompareDlg* m_pCompareDlg;

// 对话框数据
	enum { IDD = IDD_COMPARE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	CFrameWnd *m_pFrame;
	CSplitterWnd m_wndSplitter;

public:
	static CLeftView *m_pLeftView;
	static CCenterView* m_pCenterView;
	static CRightView *m_pRightView;
	
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
private:
	void TakeLayout(void);
private://从ICompareInInterface重载而来的函数
	void ShowCompareWindow(bool bShow=true);
	void CompareImage(CString strLeftImage,CString strRightImage);
	bool OnInitialEngine();
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
