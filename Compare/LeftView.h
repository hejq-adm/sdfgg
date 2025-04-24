#pragma once

#ifdef _DEBUG
#pragma comment(lib,"..\\Debug\\DspImage.lib")
#else
#pragma comment(lib,"..\\Release\\DspImage.lib")
#endif

#include "..\\DspImage\\DspImage.h"
// CLeftView ��ͼ

#include "ShareView.h"

class CLeftView : public CView , CShareView
{
	DECLARE_DYNCREATE(CLeftView)

protected:
	CLeftView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CLeftView();
public:
	static CLeftView*	m_pLeftView;

public:
	virtual void OnDraw(CDC* pDC);      // ��д�Ի��Ƹ���ͼ
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
private:
	bool	m_lButtonDown;//�������Ƿ���
	CPoint	m_lButtonDownPoint;//���������µĵ�
public:
	CDspImage	m_DspImage;
	CImage*		m_pImage;
	CRect		m_Rect;
	CPoint		m_Point;
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	bool Draw(CDC* pDC);
	void SetImage(CString strFileName);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnNcMouseMove(UINT nHitTest, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	virtual void OnInitialUpdate();
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
public:
	//��ȡͼ���ĸ��ǵ�����
	CPoint	GetImageLeftTop();
	CPoint	GetImageRightTop();
	CPoint	GetImageLeftBottom();
	CPoint	GetImageRightBottom();
	CSize	GetImageSize();//��ȡͼ�񳤿�
	CRect	GetImageArea();//��ȡͼ����DC�ϵľ�������
	COLORREF	GetPixelFromPoint(CPoint pt);//���������ȡ��RGBֵ
	void	MyInvalidate(int nFlag);
public:
	void SetImageOriginal();
	void SetImageOriginalLeft();
	void SetImageOriginalRight();
	void SetImageOriginalLeftDig();
	void SetImageOriginalRightDig();

	void SetImageWhite();
	void SetImageWhiteLeft();
	void SetImageWhiteRight();
	void SetImageWhiteLeftDig();
	void SetImageWhiteRightDig();

	void SetImageTranslate();
	void SetImageTranslateLeft();
	void SetImageTranslateRight();
	void SetImageTranslateLeftDig();
	void SetImageTranslateRightDig();

	void SetImageReflex();
	void SetImageReflexLeft();
	void SetImageReflexRight();
	void SetImageReflexLeftDig();
	void SetImageReflexRightDig();
};


