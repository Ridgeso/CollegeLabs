#include "GUIMyFrame1.h"
#include <wx/dcmemory.h>
#include <wx/dcbuffer.h>

extern float FunctionData[100][3];
extern int NoPoints;

GUIMyFrame1::GUIMyFrame1( wxWindow* parent )
	: MyFrame1( parent )
{
	m_MemoryBitmap.Create(500, 500, 24);
	m_Image.Create(500, 500);

	float angle = m_s_rotation->GetValue() / 360.f * M_PI;
	m_Rotation[0][0] = cosf(angle);
	m_Rotation[0][1] = -sinf(angle);
	m_Rotation[1][0] = sinf(angle);
	m_Rotation[1][1] = cosf(angle);

	PrepareData(0);
	Repaint();
}

void GUIMyFrame1::m_button1_click( wxCommandEvent& event )
{
	PrepareData(NoPoints == 1 ? 0 : 1);
	Repaint();
}

void GUIMyFrame1::m_button2_click( wxCommandEvent& event )
{
	PrepareData(NoPoints == 2 ? 0 : 2);
	Repaint();
}

void GUIMyFrame1::m_button3_click( wxCommandEvent& event )
{
	PrepareData(NoPoints == 3 ? 0 : 3);
	Repaint();
}

void GUIMyFrame1::m_button4_click( wxCommandEvent& event )
{
	PrepareData(NoPoints == 4 ? 0 : 4);
	Repaint();
}

void GUIMyFrame1::m_cb_color_click( wxCommandEvent& event )
{
	Repaint();
}

void GUIMyFrame1::m_s_rotation_onscroll( wxScrollEvent& event )
{
	m_st_rotation->SetLabel(wxString::Format("Obrot: %d stopni.",m_s_rotation->GetValue()));

	float angle = m_s_rotation->GetValue() / 360.f * M_PI;
	m_Rotation[0][0] = cosf(angle);
	m_Rotation[0][1] = -sinf(angle);
	m_Rotation[1][0] = sinf(angle);
	m_Rotation[1][1] = cosf(angle);

	Repaint();
}

void GUIMyFrame1::m_s_tilt_onscroll( wxScrollEvent& event )
{
// TODO: Implement m_s_tilt_onscroll
}

void GUIMyFrame1::Repaint()
{
	wxMemoryDC memDC(m_MemoryBitmap);
	memDC.SetBackground(*wxWHITE_BRUSH);
	memDC.Clear();
	memDC.SetPen(*wxBLACK_PEN);
	memDC.SetBrush(*wxTRANSPARENT_BRUSH);

	for (int i = 0; i < NoPoints; i++)
	{
		m_Terrain[i][0] = m_Rotation[0][0] * FunctionData[i][0] + m_Rotation[0][1] * FunctionData[i][1];
		m_Terrain[i][1] = m_Rotation[1][0] * FunctionData[i][0] + m_Rotation[1][1] * FunctionData[i][1];
		m_Terrain[i][2] = FunctionData[i][2];
	}

	float minS = m_Terrain[0][2], maxS = m_Terrain[0][2];
	for (int i = 1; i < NoPoints; i++)
	{
		if (m_Terrain[i][2] < minS)
			minS = m_Terrain[i][2];
		if (m_Terrain[i][2] > maxS)
			maxS = m_Terrain[i][2];
	}

	//auto ShepardData = new float[500 * 500];
	////auto ShepardData = new unsigned char[500 * 500 * 3];
	//for (int y = 0; y < 500; y++)
	//	for (int x = 0; x < 500; x++)
	//	{
	//		float val = Shepard(m_Terrain, x / 100.0 - 2.5, -y / 100.0 + 2.5);
	//		val = (val - minS) / (maxS - minS);
	//		ShepardData[y * 500 + x] = val;
	//		//if (m_cb_color->GetValue())
	//		//{
	//		//	ShepardData[(y * 500 + x) * 3 + 0] = (unsigned char)(255u * val);
	//		//	ShepardData[(y * 500 + x) * 3 + 1] = 0u;
	//		//	ShepardData[(y * 500 + x) * 3 + 2] = (unsigned char)(255u * (1.f - val));
	//		//}
	//		//else
	//		//{
	//		//	ShepardData[(y * 500 + x) * 3 + 0] = (unsigned char)(255u * val);
	//		//	ShepardData[(y * 500 + x) * 3 + 1] = (unsigned char)(255u * val);
	//		//	ShepardData[(y * 500 + x) * 3 + 2] = (unsigned char)(255u * val);
	//		//}
	//	}
	//memDC.DrawBitmap(wxBitmap(wxImage(500, 500, ShepardData)), 0, 0);

	for (int y = 50; y <= 450; y++)
	{
		int mappedY = 500 * (y - 50) / 400;
		
		int px = 50 * (y - 50) / 400;
		for (int x = 25 + px; x <= 425 + px; x++)
		{
			int mappedX = 500 * (x - 25 - px) / 400;

			//float column = ShepardData[mappedY * 500 + mappedX];
			float column = Shepard(m_Terrain, mappedX / 100.f - 2.5f, -mappedY / 100.f + 2.5f);
			column = (column - minS) / (maxS - minS);
			
			int columnHeight = (int)(25.f * column);
			if (columnHeight <= 0) columnHeight = 1;
			if (columnHeight > 25) columnHeight = 25;

			wxColor currColor;
			if (m_cb_color->GetValue())
				currColor = wxColor(255u * column, 0u, 255u * (1 - column));
			else
				currColor = wxColor(255u * column, 255u * column, 255u * column);
			memDC.SetPen(wxPen(currColor));

			memDC.DrawLine(x, y, x, y - columnHeight);
		}
	}
	//delete[] ShepardData;

	wxClientDC dc(m_panel1);
	m_panel1->PrepareDC(dc);
	dc.Blit(0, 0, 500, 500, &memDC, 0, 0);
}