// CompareDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Compare.h"
#include "CompareDlg.h"
#include "afxdialogex.h"

CCompareDlg* CCompareDlg::m_pCompareDlg=NULL;
CLeftView* CCompareDlg::m_pLeftView=NULL;
CCenterView* CCompareDlg::m_pCenterView=NULL;
CRightView* CCompareDlg::m_pRightView=NULL;
// CCompareDlg 对话框

IMPLEMENT_DYNAMIC(CCompareDlg, CDialogEx)

CCompareDlg::CCompareDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCompareDlg::IDD, pParent)
{
	if(m_pCompareDlg==NULL)
	{
		m_pCompareDlg=this;
	}
}

CCompareDlg::~CCompareDlg()
{
}

void CCompareDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCompareDlg, CDialogEx)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CCompareDlg 消息处理程序


int CCompareDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (__super::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	CCreateContext ccc;
	ccc.m_pNewViewClass      = RUNTIME_CLASS(CLeftView);
	ccc.m_pCurrentDoc           = NULL;
	ccc.m_pNewDocTemplate = NULL;
	ccc.m_pLastView              = NULL;
	ccc.m_pCurrentFrame       = NULL;
	// Because the CFrameWnd needs a window class, we will create
	// a new one. I just copied the sample from MSDN Help.
	// When using it in your project, you may keep CS_VREDRAW and
	// CS_HREDRAW and then throw the other three parameters.
	CString strMyClass = AfxRegisterWndClass(CS_VREDRAW |
		CS_HREDRAW,
		::LoadCursor(NULL, IDC_ARROW),
		(HBRUSH) ::GetStockObject(WHITE_BRUSH),
		::LoadIcon(NULL, IDI_APPLICATION));

	m_pFrame = new CFrameWnd;
	m_pFrame->Create(strMyClass,_T(""), WS_CHILD,CRect(0,0,1,1), this);
	m_pFrame->ShowWindow(SW_SHOW);
	m_pFrame->MoveWindow(0,0,300,300);
	m_wndSplitter.CreateStatic(m_pFrame,1, 3);
	m_wndSplitter.CreateView(0,0, RUNTIME_CLASS(CLeftView),
		CSize(100,100), &ccc);
	m_wndSplitter.CreateView(0,1, RUNTIME_CLASS(CCenterView),
		CSize(100,100), &ccc);
	m_wndSplitter.CreateView(0,2, RUNTIME_CLASS(CRightView),
		CSize(100,100), &ccc);
//	m_wndSplitter.EnableWindow(false);
	return 0;
}


void CCompareDlg::OnSize(UINT nType, int cx, int cy)
{
	__super::OnSize(nType, cx, cy);
	TakeLayout();
	// TODO: 在此处添加消息处理程序代码
}


BOOL CCompareDlg::OnInitDialog()
{
	__super::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CRect rect(0,0,100,100);
	m_pFrame->MoveWindow(&rect);
	m_pFrame->ShowWindow(SW_SHOW);
	m_wndSplitter.MoveWindow(0,0, rect.Width(), rect.Height());
	m_wndSplitter.ShowWindow(SW_SHOW);

// 	m_pLeftView->SetImage(_T("C:\\Users\\kf178\\Desktop\\TestFile\\20150907\\00005.bmp"));
// 	m_pRightView->SetImage(_T("C:\\Users\\kf178\\Desktop\\TestFile\\20150907\\00006.bmp"));
// 
// 	m_pLeftView->SetImage(_T("C:\\Users\\kf178\\Desktop\\TestFile\\20150907\\00008.bmp"));
// 	m_pRightView->SetImage(_T("C:\\Users\\kf178\\Desktop\\TestFile\\20150907\\00001.bmp"));
// 
// 	m_pLeftView->SetImage(_T("C:\\Users\\kf178\\Desktop\\TestFile\\20150907\\00003.bmp"));
// 	m_pRightView->SetImage(_T("C:\\Users\\kf178\\Desktop\\TestFile\\20150907\\00004.bmp"));

	TakeLayout();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CCompareDlg::TakeLayout(void)
{
	if(m_pFrame!=NULL && m_pFrame->m_hWnd && m_wndSplitter.m_hWnd)
	{
		CRect Rect;
		GetClientRect(Rect);
		int Step=Rect.Width()/3;
		m_wndSplitter.SetColumnInfo(0,Step,10);
		m_wndSplitter.SetColumnInfo(1,Step,10);
		m_wndSplitter.SetColumnInfo(2,Step,10);
		Rect.left+=3;
		Rect.top+=3;
		Rect.right-=3;
		Rect.bottom-=3;
		m_pFrame->MoveWindow(Rect);
		m_wndSplitter.MoveWindow(Rect);
	}
}

void CCompareDlg::ShowCompareWindow(bool bShow/* =true */)
{
	ShowWindow(bShow);
	SetForegroundWindow();
}

void CCompareDlg::CompareImage(CString strLeftImage,CString strRightImage)
{
	m_pLeftView->SetImage(strLeftImage);
	m_pRightView->SetImage(strRightImage);
	CCenterView::m_pCenterView->CompareImage();
}

bool CCompareDlg::OnInitialEngine()
{
	return Create(IDD,NULL)?true:false;
}

BOOL CCompareDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类

	return __super::PreTranslateMessage(pMsg);
}


void CCompareDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
// 	m_pLeftView->SetImage(_T("C:\\Users\\kf178\\Desktop\\TestFile\\20150907\\00003.bmp"));
// 	m_pRightView->SetImage(_T("C:\\Users\\kf178\\Desktop\\TestFile\\20150907\\00004.bmp"));
	__super::OnLButtonDown(nFlags, point);
}
