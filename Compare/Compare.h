// Compare.h : Compare DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CCompareApp
// �йش���ʵ�ֵ���Ϣ������� Compare.cpp
//

class CCompareApp : public CWinApp
{
public:
	CCompareApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
