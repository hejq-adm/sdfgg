#pragma once


class CShareView
{
public:
	CShareView(void);
	~CShareView(void);
//	static CRect	m_Rect;
	static CPoint		m_Point_All;//�Ա�ͼƬ�����Ͻ�����
	static CSize		m_Size;
	void InvalidateAllView();
};

