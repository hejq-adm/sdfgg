#include "StdAfx.h"
#include "ShareView.h"

#include "CompareDlg.h"

//CRect CShareView::m_Rect;
CPoint CShareView::m_Point_All;
CSize  CShareView::m_Size;


CShareView::CShareView(void)
{
	m_Point_All.x=0;
	m_Point_All.y=0;
}


CShareView::~CShareView(void)
{
}

void CShareView::InvalidateAllView()
{
	CCompareDlg::m_pRightView->Invalidate();
	CCompareDlg::m_pLeftView->Invalidate();
	
	CCompareDlg::m_pCenterView->Invalidate();
}

