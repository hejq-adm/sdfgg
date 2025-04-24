// RightView.cpp : 实现文件
//

#include "stdafx.h"
#include "Compare.h"
#include "RightView.h"

#include "CompareDlg.h"

// CRightView
CRightView* CRightView::m_pRightView=NULL;

IMPLEMENT_DYNCREATE(CRightView, CView)

CRightView::CRightView()
{
	if(CCompareDlg::m_pRightView==NULL)
	{
		CCompareDlg::m_pRightView=this;
		m_pRightView=this;
		m_pImage=NULL;
		m_lButtonDown=false;//软件启动时，鼠标左键没有按下
	}
}

CRightView::~CRightView()
{
}

BEGIN_MESSAGE_MAP(CRightView, CView)
	ON_WM_LBUTTONDOWN()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()


// CRightView 绘图

void CRightView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 在此添加绘制代码
	Draw(pDC);
}


// CRightView 诊断

#ifdef _DEBUG
void CRightView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CRightView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CRightView 消息处理程序


void CRightView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_lButtonDown=true;
	m_lButtonDownPoint=point;
	SetFocus();
	SetCapture();
	CView::OnLButtonDown(nFlags, point);
}


void CRightView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
//	GetClientRect(m_Rect);
	Invalidate();
	// TODO: 在此处添加消息处理程序代码
}


BOOL CRightView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	Draw(pDC);
	return TRUE;
//	return CView::OnEraseBkgnd(pDC);
}


bool CRightView::Draw(CDC* pDC)
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


void CRightView::SetImage(CString strFileName)
{
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

void CRightView::OnInitialUpdate()
{
	__super::OnInitialUpdate();
	GetClientRect(m_Rect);
	// TODO: 在此添加专用代码和/或调用基类
}


void CRightView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	
	if(m_lButtonDown)
	{
		m_lButtonDown=false;
		ReleaseCapture();
	}
	__super::OnLButtonUp(nFlags, point);
}


void CRightView::OnMouseMove(UINT nFlags, CPoint point)
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


BOOL CRightView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
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
CPoint CRightView::GetImageLeftTop()
{
	return CPoint(m_Point.x+m_Point_All.x,m_Point.y+m_Point_All.y);
}

CPoint CRightView::GetImageRightTop()
{
	return CPoint(m_Point.x+m_Point_All.x+m_pImage->GetWidth()+m_Size.cx,m_Point.y+m_Point_All.y);
}
CPoint CRightView::GetImageLeftBottom()
{
	return CPoint(m_Point.x+m_Point_All.x,m_Point.y+m_Point_All.y+m_pImage->GetHeight()+m_Size.cy);
}
CPoint CRightView::GetImageRightBottom()
{
	return CPoint(m_Point.x+m_Point_All.x+m_pImage->GetWidth()+m_Size.cx,m_Point.y+m_Point_All.y+m_pImage->GetHeight()+m_Size.cy);
}

CSize CRightView::GetImageSize()
{
	return CSize(m_pImage->GetWidth()+m_Size.cx,m_pImage->GetHeight()+m_Size.cy);
}

CRect CRightView::GetImageArea()
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

COLORREF CRightView::GetPixelFromPoint(CPoint pt)//根据坐标获取像RGB值
{
	CPoint point=GetImageLeftTop();
	int x=pt.x-point.x;
	int y=pt.y-point.y;
	BYTE* pByte=(BYTE*)m_pImage->GetPixelAddress(x,y);

	COLORREF clr=RGB(pByte[0],pByte[1],pByte[2]);
	return clr;
}

void CRightView::MyInvalidate(int nFlag)
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


void CRightView::SetImageOriginal()
{
	m_pImage=m_DspImage.GetOrigenImage();
	Invalidate();
}

void CRightView::SetImageOriginalLeft()
{
	m_pImage=m_DspImage.GetOrigenImageLeft();
	Invalidate();
}

void CRightView::SetImageOriginalRight()
{
	m_pImage=m_DspImage.GetOrigenImageRight();
	Invalidate();
}

void CRightView::SetImageOriginalLeftDig()
{
	m_pImage=m_DspImage.GetOrigenImageLeftDig();
	Invalidate();
}

void CRightView::SetImageOriginalRightDig()
{
	m_pImage=m_DspImage.GetOrigenImageRightDig();
	Invalidate();
}

void CRightView::SetImageWhite()
{
	m_pImage=m_DspImage.GetWhiteImage();
	Invalidate();
}

void CRightView::SetImageWhiteLeft()
{
	m_pImage=m_DspImage.GetWhiteImageLeft();
	Invalidate();
}

void CRightView::SetImageWhiteRight()
{
	m_pImage=m_DspImage.GetWhiteImageRight();
	Invalidate();
}

void CRightView::SetImageWhiteLeftDig()
{
	m_pImage=m_DspImage.GetWhiteImageLeftDig();
	Invalidate();
}

void CRightView::SetImageWhiteRightDig()
{
	m_pImage=m_DspImage.GetWhiteImageRightDig();
	Invalidate();
}

void CRightView::SetImageTranslate()
{
	m_pImage=m_DspImage.GetTranslateImage();
	Invalidate();
}

void CRightView::SetImageTranslateLeft()
{
	m_pImage=m_DspImage.GetTranslateImageLeft();
	Invalidate();
}

void CRightView::SetImageTranslateRight()
{
	m_pImage=m_DspImage.GetTranslateImageRight();
	Invalidate();
}

void CRightView::SetImageTranslateLeftDig()
{
	m_pImage=m_DspImage.GetTranslateImageLeftDig();
	Invalidate();
}

void CRightView::SetImageTranslateRightDig()
{
	m_pImage=m_DspImage.GetTranslateImageRightDig();
	Invalidate();
}

void CRightView::SetImageReflex()
{
	m_pImage=m_DspImage.GetReflexImage();
	Invalidate();
}

void CRightView::SetImageReflexLeft()
{
	m_pImage=m_DspImage.GetReflexImageLeft();
	Invalidate();
}

void CRightView::SetImageReflexRight()
{
	m_pImage=m_DspImage.GetReflexImageRight();
	Invalidate();
}

void CRightView::SetImageReflexLeftDig()
{
	m_pImage=m_DspImage.GetReflexImageLeftDig();
	Invalidate();
}

void CRightView::SetImageReflexRightDig()
{
	m_pImage=m_DspImage.GetReflexImageRightDig();
	Invalidate();
}