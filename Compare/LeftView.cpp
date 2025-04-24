// LeftView.cpp : 实现文件
//

#include "stdafx.h"
#include "Compare.h"
#include "LeftView.h"

#include "CompareDlg.h"

// CLeftView

CLeftView* CLeftView::m_pLeftView=NULL;

IMPLEMENT_DYNCREATE(CLeftView, CView)

CLeftView::CLeftView()
{
	if(CCompareDlg::m_pLeftView==NULL)
	{
		CCompareDlg::m_pLeftView=this;
		m_pLeftView=this;
		m_pImage=NULL;
		m_lButtonDown=false;//软件启动时，鼠标左键没有按下
	}
}

CLeftView::~CLeftView()
{
}

BEGIN_MESSAGE_MAP(CLeftView, CView)
	ON_WM_LBUTTONDOWN()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONUP()
	ON_WM_NCMOUSEMOVE()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()


// CLeftView 绘图

void CLeftView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 在此添加绘制代码
	Draw(pDC);
}


// CLeftView 诊断

#ifdef _DEBUG
void CLeftView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CLeftView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CLeftView 消息处理程序


void CLeftView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_lButtonDown=true;
	m_lButtonDownPoint=point;
	SetFocus();
	SetCapture();
	CView::OnLButtonDown(nFlags, point);
}


void CLeftView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
//	GetClientRect(m_Rect);
	Invalidate();
	// TODO: 在此处添加消息处理程序代码
}


BOOL CLeftView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	Draw(pDC);
	return TRUE;
//	return CView::OnEraseBkgnd(pDC);
}


bool CLeftView::Draw(CDC* pDC)
{
	CDC mDC;
	mDC.CreateCompatibleDC(pDC);
	CRect Rect;
	GetClientRect(Rect);
	CBitmap mBitmap;
	mBitmap.CreateCompatibleBitmap(pDC,Rect.Width(),Rect.Height());
	mDC.SelectObject(mBitmap);

	mDC.SetBkMode(TRANSPARENT);//设备DC背景透明

	mDC.FillRect(Rect,&CBrush(GetSysColor(COLOR_BTNFACE)));//绘制背景

	if(m_pImage!=NULL && !m_pImage->IsNull())
	{
		CPoint pt=GetImageLeftTop();
		CRect r;
		r.left=pt.x;
		r.top=pt.y;
		r.right=r.left+m_pImage->GetWidth()+m_Size.cx;
		r.bottom=r.top+m_pImage->GetHeight()+m_Size.cy;
		m_pImage->Draw(mDC,r);
	}

	pDC->BitBlt(0,0,Rect.Width(),Rect.Height(),&mDC,0,0,SRCCOPY);
	mDC.DeleteDC();
	mBitmap.DeleteObject();
	return true;
}

void CLeftView::SetImage(CString strFileName)
{
	m_Point.x=0;
	m_Point.y=0;
	m_DspImage.LoadImageA(strFileName);
	m_pImage=m_DspImage.GetOrigenImage();

	int nLeft=(m_Rect.Width()-m_pImage->GetWidth())/2;
	int nTop=(m_Rect.Height()-m_pImage->GetHeight())/2;
	m_Rect.left=nLeft;
	m_Rect.top=nTop;
	m_Rect.right=m_Rect.left+m_pImage->GetWidth();
	m_Rect.bottom=m_Rect.top+m_pImage->GetHeight();

	Invalidate();
}


void CLeftView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(m_lButtonDown)
	{
		m_lButtonDown=false;
		ReleaseCapture();
	}
	__super::OnLButtonUp(nFlags, point);
}


void CLeftView::OnNcMouseMove(UINT nHitTest, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	
	__super::OnNcMouseMove(nHitTest, point);
}


void CLeftView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(m_lButtonDown)
	{
		CRect Rect;
		GetClientRect(Rect);
		int hStep=m_lButtonDownPoint.x-point.x;
		int vStep=m_lButtonDownPoint.y-point.y;
		m_Point.x-=hStep;
		m_Point.y-=vStep;
		m_lButtonDownPoint=point;
		MyInvalidate(1);
	}
	__super::OnMouseMove(nFlags, point);
}


void CLeftView::OnInitialUpdate()
{
	__super::OnInitialUpdate();
	GetClientRect(m_Rect);
	// TODO: 在此添加专用代码和/或调用基类
}


BOOL CLeftView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_Size.cy+=zDelta;
	m_Size.cx+=zDelta;
	if(m_Size.cx<0)
	{
		m_Size.cx=0;
		m_Size.cy=0;
	}
	InvalidateAllView();
	return __super::OnMouseWheel(nFlags, zDelta, pt);
}

//获取图像四个角的坐标
CPoint CLeftView::GetImageLeftTop()
{
	return CPoint(m_Point.x+m_Point_All.x,m_Point.y+m_Point_All.y);
}

CPoint CLeftView::GetImageRightTop()
{
	return CPoint(m_Point.x+m_Point_All.x+m_pImage->GetWidth()+m_Size.cx,m_Point.y+m_Point_All.y);
}
CPoint CLeftView::GetImageLeftBottom()
{
	return CPoint(m_Point.x+m_Point_All.x,m_Point.y+m_Point_All.y+m_pImage->GetHeight()+m_Size.cy);
}
CPoint CLeftView::GetImageRightBottom()
{
	return CPoint(m_Point.x+m_Point_All.x+m_pImage->GetWidth()+m_Size.cx,m_Point.y+m_Point_All.y+m_pImage->GetHeight()+m_Size.cy);
}

CSize CLeftView::GetImageSize()
{
	return CSize(m_pImage->GetWidth()+m_Size.cx,m_pImage->GetHeight()+m_Size.cy);
}

CRect CLeftView::GetImageArea()
{
	CRect Rect;
	CPoint pt=GetImageLeftTop();
	Rect.left=pt.x;
	Rect.top=pt.y;
	pt=GetImageRightBottom();
	Rect.right=pt.x;
	Rect.bottom=pt.y;
	return Rect;
}

COLORREF CLeftView::GetPixelFromPoint(CPoint pt)//根据坐标获取像RGB值
{
	CPoint point=GetImageLeftTop();
	int x=pt.x=point.x;
	int y=pt.y-point.y;
	BYTE* pByte=(BYTE*)m_pImage->GetPixelAddress(x,y);

	COLORREF clr=RGB(pByte[0],pByte[1],pByte[2]);
	return clr;
}

void CLeftView::MyInvalidate(int nFlag)
{
	if(nFlag==0)
	{
		Invalidate();
	}
	else if(nFlag==1)
	{
		Invalidate();
		CCenterView::m_pCenterView->Invalidate();
	}
	else
	{
		InvalidateAllView();
	}
}

void CLeftView::SetImageOriginal()
{
	m_pImage=m_DspImage.GetOrigenImage();
	Invalidate();
}

void CLeftView::SetImageOriginalLeft()
{
	m_pImage=m_DspImage.GetOrigenImageLeft();
	Invalidate();
}

void CLeftView::SetImageOriginalRight()
{
	m_pImage=m_DspImage.GetOrigenImageRight();
	Invalidate();
}

void CLeftView::SetImageOriginalLeftDig()
{
	m_pImage=m_DspImage.GetOrigenImageLeftDig();
	Invalidate();
}

void CLeftView::SetImageOriginalRightDig()
{
	m_pImage=m_DspImage.GetOrigenImageRightDig();
	Invalidate();
}

void CLeftView::SetImageWhite()
{
	m_pImage=m_DspImage.GetWhiteImage();
	Invalidate();
}

void CLeftView::SetImageWhiteLeft()
{
	m_pImage=m_DspImage.GetWhiteImageLeft();
	Invalidate();
}

void CLeftView::SetImageWhiteRight()
{
	m_pImage=m_DspImage.GetWhiteImageRight();
	Invalidate();
}

void CLeftView::SetImageWhiteLeftDig()
{
	m_pImage=m_DspImage.GetWhiteImageLeftDig();
	Invalidate();
}

void CLeftView::SetImageWhiteRightDig()
{
	m_pImage=m_DspImage.GetWhiteImageRightDig();
	Invalidate();
}

void CLeftView::SetImageTranslate()
{
	m_pImage=m_DspImage.GetTranslateImage();
	Invalidate();
}

void CLeftView::SetImageTranslateLeft()
{
	m_pImage=m_DspImage.GetTranslateImageLeft();
	Invalidate();
}

void CLeftView::SetImageTranslateRight()
{
	m_pImage=m_DspImage.GetTranslateImageRight();
	Invalidate();
}

void CLeftView::SetImageTranslateLeftDig()
{
	m_pImage=m_DspImage.GetTranslateImageLeftDig();
	Invalidate();
}

void CLeftView::SetImageTranslateRightDig()
{
	m_pImage=m_DspImage.GetTranslateImageRightDig();
	Invalidate();
}

void CLeftView::SetImageReflex()
{
	m_pImage=m_DspImage.GetReflexImage();
	Invalidate();
}

void CLeftView::SetImageReflexLeft()
{
	m_pImage=m_DspImage.GetReflexImageLeft();
	Invalidate();
}

void CLeftView::SetImageReflexRight()
{
	m_pImage=m_DspImage.GetReflexImageRight();
	Invalidate();
}

void CLeftView::SetImageReflexLeftDig()
{
	m_pImage=m_DspImage.GetReflexImageLeftDig();
	Invalidate();
}

void CLeftView::SetImageReflexRightDig()
{
	m_pImage=m_DspImage.GetReflexImageRightDig();
	Invalidate();
}
