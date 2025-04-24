// CenterView.cpp : 实现文件
//

#include "stdafx.h"
#include "Compare.h"
#include "CenterView.h"

#include "CompareDlg.h"

// CCenterView

DWORD CompareImageThread(LPVOID lParam);//比较图片的后台线程

CCenterView* CCenterView::m_pCenterView=NULL;

IMPLEMENT_DYNCREATE(CCenterView, CView)

CCenterView::CCenterView()
{
	if(CCompareDlg::m_pCenterView==NULL)
	{
		CCompareDlg::m_pCenterView=this;
		m_pCenterView=this;
		m_lButtonDown=false;//软件启动时，鼠标左键没有按下
		m_Menu.LoadMenu(IDR_POPUP_MENU);

	}
}

CCenterView::~CCenterView()
{
}

BEGIN_MESSAGE_MAP(CCenterView, CView)
	ON_WM_LBUTTONDOWN()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEWHEEL()
	ON_COMMAND(IDM_COMPARE_ORIGINE_IMAGE, &CCenterView::OnCompareOrigineImage)
	ON_COMMAND(IDM_COMPARE_REFLEX_IMAGE, &CCenterView::OnCompareReflexImage)
	ON_COMMAND(IDM_COMPARE_TRANSLATE_IMAGE, &CCenterView::OnCompareTranslateImage)
	ON_COMMAND(IDM_COMPARE_WHITE_IMAGE, &CCenterView::OnCompareWhiteImage)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(IDM_COMPARE_ORIGINE_LEFIT_DIG_IMAGE, &CCenterView::OnCompareOrigineLefitDigImage)
	ON_COMMAND(IDM_COMPARE_ORIGINE_LEFT_IMAGE, &CCenterView::OnCompareOrigineLeftImage)
	ON_COMMAND(IDM_COMPARE_ORIGINE_RIGHT_DIG_IMAGE, &CCenterView::OnCompareOrigineRightDigImage)
	ON_COMMAND(IDM_COMPARE_ORIGINE_RIGHT_IMAGE, &CCenterView::OnCompareOrigineRightImage)
	ON_COMMAND(IDM_COMPARE_REFLEX_LEFT_DIG_IMAGE, &CCenterView::OnCompareReflexLeftDigImage)
	ON_COMMAND(IDM_COMPARE_REFLEX_LEFT_IMAGE, &CCenterView::OnCompareReflexLeftImage)
	ON_COMMAND(IDM_COMPARE_REFLEX_RIGHT_DIG_IMAGE, &CCenterView::OnCompareReflexRightDigImage)
	ON_COMMAND(IDM_COMPARE_REFLEX_RIGHT_IMAGE, &CCenterView::OnCompareReflexRightImage)
	ON_COMMAND(IDM_COMPARE_TRANSLATE_LEFT_DIG_IMAGE, &CCenterView::OnCompareTranslateLeftDigImage)
	ON_COMMAND(IDM_COMPARE_TRANSLATE_LEFT_IMAGE, &CCenterView::OnCompareTranslateLeftImage)
	ON_COMMAND(IDM_COMPARE_TRANSLATE_RIGHT_DIG_IMAGE, &CCenterView::OnCompareTranslateRightDigImage)
	ON_COMMAND(IDM_COMPARE_TRANSLATE_RIGHT_IMAGE, &CCenterView::OnCompareTranslateRightImage)
	ON_COMMAND(IDM_COMPARE_WHITE_LEFT_DIG_IMAGE, &CCenterView::OnCompareWhiteLeftDigImage)
	ON_COMMAND(IDM_COMPARE_WHITE_LEFT_IMAGE, &CCenterView::OnCompareWhiteLeftImage)
	ON_COMMAND(IDM_COMPARE_WHITE_RIGHT_DIG_IMAGE, &CCenterView::OnCompareWhiteRightDigImage)
	ON_COMMAND(IDM_COMPARE_WHITE_RIGHT_IMAGE, &CCenterView::OnCompareWhiteRightImage)
END_MESSAGE_MAP()


// CCenterView 绘图

void CCenterView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 在此添加绘制代码
	Draw(pDC);
}


// CCenterView 诊断

#ifdef _DEBUG
void CCenterView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CCenterView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CCenterView 消息处理程序

#include "..\\Interface\\IOutputInInterface.h"
#include "..\\Interface\\ICompareOutInterface.h"
void CCenterView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_lButtonDown=true;
	m_lButtonDownPoint=point;
	SetCapture();
//	IOutputInInterface* pOutputInterface=(IOutputInInterface*)ICompareOutInterface::m_pOutInstance->QueryInterface(IID_IPublicOutputInterface);
//	pOutputInterface->ShowPublicOutputWindow(true);
//	CLeftView::m_pLeftView->SetImageWhiteLeft();
	CView::OnLButtonDown(nFlags, point);
}


void CCenterView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
//	GetClientRect(m_Rect);
	Invalidate();
	// TODO: 在此处添加消息处理程序代码
}


BOOL CCenterView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	Draw(pDC);
	return TRUE;
//	return CView::OnEraseBkgnd(pDC);
}


bool CCenterView::Draw(CDC* pDC)
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

	if(m_Image_Right_DC.m_hDC)
	{
		mDC.FillRect(Rect,&CBrush(RGB(0,0,0)));//绘制背景

		CLeftView *pLeftView=CLeftView::m_pLeftView;
		CRightView *pRightView=CRightView::m_pRightView;

		CRect rRect=pRightView->GetImageArea();

		CRect lRect=pLeftView->GetImageArea();

		CRect rc=RectAndRect(rRect,lRect);
		rc.left=0;
		rc.top=0;

		CDC memDC;
		memDC.CreateCompatibleDC(&mDC);
		CBitmap mBmp;
		mBmp.CreateCompatibleBitmap(&mDC,rc.Width(),rc.Height());
		memDC.SelectObject(mBmp);

		//memDC.BitBlt(rRect.left,rRect.top,rRect.Width(),rRect.Height(),&m_Image_Right_DC,0,0,SRCCOPY);
		memDC.StretchBlt(rRect.left,rRect.top,rRect.Width(),rRect.Height(),&m_Image_Right_DC,0,0,pLeftView->m_pImage->GetWidth(),pLeftView->m_pImage->GetHeight(),SRCCOPY);
		//memDC.BitBlt(lRect.left,lRect.top,lRect.Width(),lRect.Height(),&m_Image_Left_DC,0,0,SRCINVERT);
		memDC.StretchBlt(lRect.left,lRect.top,lRect.Width(),lRect.Height(),&m_Image_Left_DC,0,0,pLeftView->m_pImage->GetWidth(),pLeftView->m_pImage->GetHeight(),SRCINVERT);

		mDC.BitBlt(0,0,rc.Width(),rc.Height(),&memDC,0,0,SRCCOPY);

		memDC.DeleteDC();
		mBmp.DeleteObject();
	}

	pDC->BitBlt(0,0,Rect.Width(),Rect.Height(),&mDC,0,0,SRCCOPY);
	mDC.DeleteDC();
	mBitmap.DeleteObject();
	return true;
}


void CCenterView::SetImage(CString strFileName)
{
//	m_DspImage.LoadImageA(strFileName);
}


void CCenterView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	// TODO: 在此添加专用代码和/或调用基类
}


void CCenterView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(m_lButtonDown)
	{
		CRect Rect;
		GetClientRect(Rect);
		int hStep=m_lButtonDownPoint.x-point.x;
		int vStep=m_lButtonDownPoint.y-point.y;
		m_Point_All.x-=hStep;
		m_Point_All.y-=vStep;
		m_lButtonDownPoint=point;
		InvalidateAllView();
	}
	__super::OnMouseMove(nFlags, point);
}


void CCenterView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(m_lButtonDown)
	{
		m_lButtonDown=false;
		ReleaseCapture();
	}
	__super::OnLButtonUp(nFlags, point);
}


BOOL CCenterView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
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


void CCenterView::CompareImage(void)
{
	CLeftView *pLeftView=CLeftView::m_pLeftView;
	CRightView *pRightView=CRightView::m_pRightView;

	if(m_Image_Left_DC.m_hDC)
	{
		m_Image_Left_DC.Detach();
	}
	if(m_Image_Right_DC.m_hDC)
	{
		m_Image_Right_DC.Detach();
	}

	//有效判断
	if(pLeftView->m_pImage==NULL || pLeftView->m_pImage->IsNull())
	{
		Invalidate();
		return ;
	}

	if(pRightView->m_pImage==NULL || pRightView->m_pImage->IsNull())
	{
		Invalidate();
		return ;
	}

	CImage lImage;
	ImageCopy(pLeftView->m_pImage,CRect(0,0,pLeftView->m_pImage->GetWidth(),pLeftView->m_pImage->GetHeight()),&lImage);
	CImage rImage;
	ImageCopy(pRightView->m_pImage,CRect(0,0,pRightView->m_pImage->GetWidth(),pRightView->m_pImage->GetHeight()),&rImage);

	CImage *pImage=&lImage;
	int nColorTab=pImage->GetMaxColorTableEntries();
	RGBQUAD *pRgb=new RGBQUAD[nColorTab];
	pImage->GetColorTable(0,nColorTab,pRgb);
	for(int index=0;index<nColorTab;index++)
	{
		pRgb[index].rgbRed=0;
		//pRgb[index].rgbGreen=0;
		pRgb[index].rgbBlue=0;
	}
	pImage->SetColorTable(0,nColorTab,pRgb);
	delete[] pRgb;

	pImage=&rImage;
	nColorTab=pImage->GetMaxColorTableEntries();
	pRgb=new RGBQUAD[nColorTab];
	pImage->GetColorTable(0,nColorTab,pRgb);
	for(int index=0;index<nColorTab;index++)
	{
		pRgb[index].rgbRed=0;
		//pRgb[index].rgbGreen=0;
		pRgb[index].rgbBlue=0;
	}
	pImage->SetColorTable(0,nColorTab,pRgb);
	delete[] pRgb;

	pImage=&lImage;
	CRect Rect(0,0,pLeftView->m_pImage->GetWidth(),pLeftView->m_pImage->GetHeight());
	m_Image_Left_DC.CreateCompatibleDC(GetDC());
	CBitmap mBitmap1;
	mBitmap1.CreateCompatibleBitmap(GetDC(),Rect.Width(),Rect.Height());
	m_Image_Left_DC.SelectObject(mBitmap1);
	pImage->Draw(m_Image_Left_DC,Rect);
	mBitmap1.DeleteObject();

	pImage=&rImage;
	Rect.right=pRightView->m_pImage->GetWidth();
	Rect.bottom=pRightView->m_pImage->GetHeight();
	m_Image_Right_DC.CreateCompatibleDC(GetDC());
	CBitmap mBitmap2;
	mBitmap2.CreateCompatibleBitmap(GetDC(),Rect.Width(),Rect.Height());
	m_Image_Right_DC.SelectObject(mBitmap2);
	pImage->Draw(m_Image_Right_DC,Rect);
	mBitmap2.DeleteObject();

	CDC mDC;
	mDC.CreateCompatibleDC(&m_Image_Right_DC);
	CBitmap mBitmap3;
	mBitmap3.CreateCompatibleBitmap(&m_Image_Right_DC,Rect.Width(),Rect.Height());
	mDC.SelectObject(mBitmap3);
	mDC.FillRect(Rect,&CBrush(RGB(0,0,0)));
	mDC.BitBlt(0,0,Rect.Width(),Rect.Height(),&m_Image_Right_DC,0,0,SRCINVERT);
	mBitmap3.DeleteObject();

	m_Image_Right_DC.FillRect(Rect,&CBrush(RGB(0x01,0,0)));
	m_Image_Right_DC.BitBlt(0,0,Rect.Width(),Rect.Height(),&mDC,0,0,SRCINVERT);
//恢复图像显示的位置
	m_Point_All=CPoint(0,0);
	m_Size=CSize(0,0);
	pLeftView->m_Point=CPoint(0,0);
	pRightView->m_Point=CPoint(0,0);
	Invalidate();

}

CRect CCenterView::GetRepeatArea(CRect Rect1,CRect Rect2)//计算两个区域的的重复区域
{
	CRect Rect;
	Rect.left=Rect1.left<Rect2.left?Rect2.left:Rect1.left;
	Rect.top=Rect1.top<Rect2.top?Rect2.top:Rect1.top;
	Rect.right=Rect1.right>Rect2.right?Rect2.right:Rect1.right;
	Rect.bottom=Rect1.bottom>Rect2.bottom?Rect2.bottom:Rect1.bottom;
	return Rect;
}


DWORD CompareImageThread(LPVOID lParam)
{
	return 0;
}

void CCenterView::ImageCopy(CImage* pImgSrc,CRect RectSrc,CImage *pImgDrt)
{
	int MaxColors = pImgSrc->GetMaxColorTableEntries();
	RGBQUAD *ColorTab=new RGBQUAD[MaxColors];

	CDC* pDCsrc,*pDCdrc;
	if(!pImgDrt->IsNull())
	{
		pImgDrt->Destroy();
	}
	pImgDrt->Create(RectSrc.Width(),RectSrc.Height(),pImgSrc->GetBPP(),0);

	if(pImgSrc->IsIndexed())
	{
		pImgSrc->GetColorTable(0,MaxColors,ColorTab);
		pImgDrt->SetColorTable(0,MaxColors,ColorTab);
	}

	pDCsrc=CDC::FromHandle(pImgSrc->GetDC());
	pDCdrc=CDC::FromHandle(pImgDrt->GetDC());

	pDCdrc->BitBlt(0,0,RectSrc.Width(),RectSrc.Height(),pDCsrc,RectSrc.left,RectSrc.top,SRCCOPY);
	pImgSrc->ReleaseDC();
	pImgDrt->ReleaseDC();
	delete[] ColorTab;
}

CRect CCenterView::RectAndRect(CRect Rect1, CRect Rect2)
{
	CRect Rect;
	Rect.left=Rect1.left>Rect2.left?Rect2.left:Rect1.left;
	Rect.top=Rect1.top>Rect2.top?Rect2.top:Rect1.top;
	Rect.right=Rect1.right<Rect2.right?Rect2.right:Rect1.right;
	Rect.bottom=Rect1.bottom<Rect2.bottom?Rect2.bottom:Rect1.bottom;
	return Rect;
}


void CCenterView::OnCompareOrigineImage()
{
	// TODO: 在此添加命令处理程序代码
	CLeftView::m_pLeftView->SetImageOriginal();
	CRightView::m_pRightView->SetImageOriginal();
	CompareImage();
}


void CCenterView::OnCompareReflexImage()
{
	// TODO: 在此添加命令处理程序代码
	CLeftView::m_pLeftView->SetImageReflex();
	CRightView::m_pRightView->SetImageReflex();
	CompareImage();
}


void CCenterView::OnCompareTranslateImage()
{
	// TODO: 在此添加命令处理程序代码
	CLeftView::m_pLeftView->SetImageReflex();
	CRightView::m_pRightView->SetImageReflex();
	CompareImage();
}


void CCenterView::OnCompareWhiteImage()
{
	// TODO: 在此添加命令处理程序代码
	CLeftView::m_pLeftView->SetImageWhite();
	CRightView::m_pRightView->SetImageWhite();
	CompareImage();
}


void CCenterView::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{
	// TODO: 在此处添加消息处理程序代码
	m_Menu.GetSubMenu(0)->TrackPopupMenu(TPM_RIGHTBUTTON,point.x,point.y,this);
}


void CCenterView::OnCompareOrigineLefitDigImage()
{
	// TODO: 在此添加命令处理程序代码
	CLeftView::m_pLeftView->SetImageOriginalLeftDig();
	CRightView::m_pRightView->SetImageOriginalLeftDig();
	CompareImage();
}


void CCenterView::OnCompareOrigineLeftImage()
{
	// TODO: 在此添加命令处理程序代码
	CLeftView::m_pLeftView->SetImageOriginalLeft();
	CRightView::m_pRightView->SetImageOriginalLeft();
	CompareImage();
}


void CCenterView::OnCompareOrigineRightDigImage()
{
	// TODO: 在此添加命令处理程序代码
	CLeftView::m_pLeftView->SetImageOriginalRightDig();
	CRightView::m_pRightView->SetImageOriginalRightDig();
	CompareImage();
}


void CCenterView::OnCompareOrigineRightImage()
{
	// TODO: 在此添加命令处理程序代码
	CLeftView::m_pLeftView->SetImageOriginalRight();
	CRightView::m_pRightView->SetImageOriginalRight();
	CompareImage();
}


void CCenterView::OnCompareReflexLeftDigImage()
{
	// TODO: 在此添加命令处理程序代码
	CLeftView::m_pLeftView->SetImageReflexLeftDig();
	CRightView::m_pRightView->SetImageReflexLeftDig();
	CompareImage();
}


void CCenterView::OnCompareReflexLeftImage()
{
	// TODO: 在此添加命令处理程序代码
	CLeftView::m_pLeftView->SetImageReflexLeft();
	CRightView::m_pRightView->SetImageReflexLeft();
	CompareImage();
}


void CCenterView::OnCompareReflexRightDigImage()
{
	// TODO: 在此添加命令处理程序代码
	CLeftView::m_pLeftView->SetImageReflexRightDig();
	CRightView::m_pRightView->SetImageReflexRightDig();
	CompareImage();
}


void CCenterView::OnCompareReflexRightImage()
{
	// TODO: 在此添加命令处理程序代码
	CLeftView::m_pLeftView->SetImageReflexRight();
	CRightView::m_pRightView->SetImageReflexRight();
	CompareImage();
}


void CCenterView::OnCompareTranslateLeftDigImage()
{
	// TODO: 在此添加命令处理程序代码
	CLeftView::m_pLeftView->SetImageTranslateLeftDig();
	CRightView::m_pRightView->SetImageTranslateLeftDig();
	CompareImage();
}


void CCenterView::OnCompareTranslateLeftImage()
{
	// TODO: 在此添加命令处理程序代码
	CLeftView::m_pLeftView->SetImageTranslateLeft();
	CRightView::m_pRightView->SetImageTranslateLeft();
	CompareImage();
}


void CCenterView::OnCompareTranslateRightDigImage()
{
	// TODO: 在此添加命令处理程序代码
	CLeftView::m_pLeftView->SetImageTranslateRightDig();
	CRightView::m_pRightView->SetImageTranslateRightDig();
	CompareImage();
}


void CCenterView::OnCompareTranslateRightImage()
{
	// TODO: 在此添加命令处理程序代码
	CLeftView::m_pLeftView->SetImageTranslateRight();
	CRightView::m_pRightView->SetImageTranslateRight();
	CompareImage();
}


void CCenterView::OnCompareWhiteLeftDigImage()
{
	// TODO: 在此添加命令处理程序代码
	CLeftView::m_pLeftView->SetImageWhiteLeftDig();
	CRightView::m_pRightView->SetImageWhiteLeftDig();
	CompareImage();
}


void CCenterView::OnCompareWhiteLeftImage()
{
	// TODO: 在此添加命令处理程序代码
	CLeftView::m_pLeftView->SetImageWhiteLeft();
	CRightView::m_pRightView->SetImageWhiteLeft();
	CompareImage();
}


void CCenterView::OnCompareWhiteRightDigImage()
{
	// TODO: 在此添加命令处理程序代码
	CLeftView::m_pLeftView->SetImageWhiteRightDig();
	CRightView::m_pRightView->SetImageWhiteRightDig();
	CompareImage();
}


void CCenterView::OnCompareWhiteRightImage()
{
	// TODO: 在此添加命令处理程序代码
	CLeftView::m_pLeftView->SetImageWhiteRight();
	CRightView::m_pRightView->SetImageWhiteRight();
	CompareImage();
}
