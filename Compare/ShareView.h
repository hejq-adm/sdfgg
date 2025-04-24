#pragma once


class CShareView
{
public:
	CShareView(void);
	~CShareView(void);
//	static CRect	m_Rect;
	static CPoint		m_Point_All;//对比图片的左上角坐标
	static CSize		m_Size;
	void InvalidateAllView();
};

