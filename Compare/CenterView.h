#pragma once

#ifdef _DEBUG
#pragma comment(lib,"..\\Debug\\DspImage.lib")
#else
#pragma comment(lib,"..\\Release\\DspImage.lib")
#endif

#include "..\\DspImage\\DspImage.h"
// CCenterView 视图

#include "ShareView.h"

class CCenterView : public CView , CShareView
{
	DECLARE_DYNCREATE(CCenterView)

protected:
	CCenterView();           // 动态创建所使用的受保护的构造函数
	virtual ~CCenterView();
public:
	static CCenterView* m_pCenterView;

public:
	virtual void OnDraw(CDC* pDC);      // 重写以绘制该视图
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
private:
	bool	m_lButtonDown;//鼠标左键是否按下
	CPoint	m_lButtonDownPoint;//鼠标左键按下的点
	CMenu	m_Menu;
public:
	CDC		m_Image_Left_DC;
	CDC		m_Image_Right_DC;
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	bool Draw(CDC* pDC);
	void SetImage(CString strFileName);
	virtual void OnInitialUpdate();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	void CompareImage(void);
public:
	CRect GetRepeatArea(CRect Rect1,CRect Rect2);//计算两个区域的的重复区域
	CRect RectAndRect(CRect Rect1, CRect Rect2);//两个区域与运算
	void ImageCopy(CImage* pImgSrc,CRect RectSrc,CImage *pImgDrt);//CImage拷贝
	afx_msg void OnCompareOrigineImage();
	afx_msg void OnCompareReflexImage();
	afx_msg void OnCompareTranslateImage();
	afx_msg void OnCompareWhiteImage();
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnCompareOrigineLefitDigImage();
	afx_msg void OnCompareOrigineLeftImage();
	afx_msg void OnCompareOrigineRightDigImage();
	afx_msg void OnCompareOrigineRightImage();
	afx_msg void OnCompareReflexLeftDigImage();
	afx_msg void OnCompareReflexLeftImage();
	afx_msg void OnCompareReflexRightDigImage();
	afx_msg void OnCompareReflexRightImage();
	afx_msg void OnCompareTranslateLeftDigImage();
	afx_msg void OnCompareTranslateLeftImage();
	afx_msg void OnCompareTranslateRightDigImage();
	afx_msg void OnCompareTranslateRightImage();
	afx_msg void OnCompareWhiteLeftDigImage();
	afx_msg void OnCompareWhiteLeftImage();
	afx_msg void OnCompareWhiteRightDigImage();
	afx_msg void OnCompareWhiteRightImage();
};


