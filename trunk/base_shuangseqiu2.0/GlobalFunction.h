#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#if !defined(AFX_GRADIENT_H__B34ED849_B7C4_4462_A257_41000D0D7213__INCLUDED_)
#define AFX_GRADIENT_H__B34ED849_B7C4_4462_A257_41000D0D7213__INCLUDED_

//#include "stdafx.h"
//#pragma comment(lib, "Msimg32.lib")	//ΪAPI��GradientFill����

//�������
void GradientFillRect(HDC hdc, const CRect &rt, COLORREF crColor[], int fillType);

//�������
void GradientFillRect(HDC hdc, const CRect &rt,COLORREF crColor1,COLORREF crColor2,int fillType);


//HSLɫ�ʽṹ
struct COLOR_HSL
{   
    float m_Hue;              // ɫ�࣬ȡֵ[0,360]   
    float m_Saturation;       // ���Ͷȣ�ȡֵ[0,1]   
    float m_Luminance;        // ���ȣ�[0,1]
}; 

//RGBɫ��ת����HSLɫ��
void RGB2HSL(COLORREF* RGB,DWORD ColorCount,COLOR_HSL* HSL);

//HSLɫ��ת����RGBɫ��
void HSL2RGB(COLOR_HSL* HSL,DWORD ColorCount,COLORREF* RGB);

#endif // !defined(AFX_GRADIENT_H__B34ED849_B7C4_4462_A257_41000D0D7213__INCLUDED_)