#include "GUIMyFrame1.h"
#include <vector>
#include <fstream>
#include "vecmat.h"

#include <iostream>

struct Point
{
    float x, y, z;
    Point(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
};

struct Color
{
    int R, G, B;
    Color(int _R, int _G, int _B) : R(_R), G(_G), B(_B) {}
};

struct Segment
{
    Point begin, end;
    Color color;
    Segment(Point _begin, Point _end, Color _color) : begin(_begin), end(_end), color(_color) {}
};

std::vector<Segment> data;

GUIMyFrame1::GUIMyFrame1( wxWindow* parent )
    : MyFrame1( parent )
{
    m_button_load_geometry->SetLabel(_("Wczytaj Geometri\u0119"));
    m_staticText25->SetLabel(_("Obr\u00F3t X:"));
    m_staticText27->SetLabel(_("Obr\u00F3t Y:"));
    m_staticText29->SetLabel(_("Obr\u00F3t Z:"));

    WxSB_TranslationX->SetRange(0, 200); WxSB_TranslationX->SetValue(100);
    WxSB_TranslationY->SetRange(0, 200); WxSB_TranslationY->SetValue(100);
    WxSB_TranslationZ->SetRange(0, 200); WxSB_TranslationZ->SetValue(100);

    WxSB_RotateX->SetRange(0, 360); WxSB_RotateX->SetValue(0);
    WxSB_RotateY->SetRange(0, 360); WxSB_RotateY->SetValue(0);
    WxSB_RotateZ->SetRange(0, 360); WxSB_RotateZ->SetValue(0);

    WxSB_ScaleX->SetRange(1, 200); WxSB_ScaleX->SetValue(100);
    WxSB_ScaleY->SetRange(1, 200); WxSB_ScaleY->SetValue(100);
    WxSB_ScaleZ->SetRange(1, 200); WxSB_ScaleZ->SetValue(100);
}

void GUIMyFrame1::WxPanel_Repaint( wxUpdateUIEvent& event )
{
    Repaint();
}

void GUIMyFrame1::m_button_load_geometry_click( wxCommandEvent& event )
{
    wxFileDialog WxOpenFileDialog(this, wxT("Choose a file"), wxT(""), wxT(""), wxT("Geometry file (*.geo)|*.geo"), wxFD_OPEN | wxFD_FILE_MUST_EXIST);

    if (WxOpenFileDialog.ShowModal() == wxID_OK)
    {
        double x1, y1, z1, x2, y2, z2;
        int r, g, b;

        std::ifstream in(WxOpenFileDialog.GetPath().ToAscii());
        if (in.is_open())
        {
            data.clear();
            while (!in.eof())
            {
                in >> x1 >> y1 >> z1 >> x2 >> y2 >> z2 >> r >> g >> b;
                data.push_back(Segment(Point(x1, y1, z1), Point(x2, y2, z2), Color(r, g, b)));
            }
            in.close();
        }
    }
}

void GUIMyFrame1::Scrolls_Updated( wxScrollEvent& event )
{
    WxST_TranslationX->SetLabel(wxString::Format(wxT("%g"), (WxSB_TranslationX->GetValue() - 100) / 50.0));
    WxST_TranslationY->SetLabel(wxString::Format(wxT("%g"), (WxSB_TranslationY->GetValue() - 100) / 50.0));
    WxST_TranslationZ->SetLabel(wxString::Format(wxT("%g"), (WxSB_TranslationZ->GetValue() - 100) / 50.0));

    WxST_RotateX->SetLabel(wxString::Format(wxT("%d"), WxSB_RotateX->GetValue()));
    WxST_RotateY->SetLabel(wxString::Format(wxT("%d"), WxSB_RotateY->GetValue()));
    WxST_RotateZ->SetLabel(wxString::Format(wxT("%d"), WxSB_RotateZ->GetValue()));

    WxST_ScaleX->SetLabel(wxString::Format(wxT("%g"), WxSB_ScaleX->GetValue() / 100.0));
    WxST_ScaleY->SetLabel(wxString::Format(wxT("%g"), WxSB_ScaleY->GetValue() / 100.0));
    WxST_ScaleZ->SetLabel(wxString::Format(wxT("%g"), WxSB_ScaleZ->GetValue() / 100.0));


    Repaint();
}

void GUIMyFrame1::Repaint()
{
    wxRect screen = WxPanel->GetRect();
    Vector4 screenSize;
    screenSize.Set(screen.GetWidth(), screen.GetHeight(), 0.0);

	wxClientDC DCC(WxPanel);
	wxBufferedDC DC(&DCC);
    DC.SetBackground(wxBrush(*wxWHITE));
    DC.Clear();

    double l = -1.0, r = 1.0;
    double b = -1.0, t = 1.0;
    double nearPlane = 1.0, farPlane = 3.0;

    Matrix4 MProjection;
    MProjection.data[0][0] = nearPlane / r;
    MProjection.data[1][1] = nearPlane / t;
    MProjection.data[2][2] = -(farPlane + nearPlane) / (farPlane - nearPlane);
    MProjection.data[3][3] = 0.0;

    MProjection.data[0][2] = (r + l) / (r - l);
    MProjection.data[1][2] = (t + b) / (t - b);

    MProjection.data[2][3] = -2.0 * farPlane * nearPlane / (farPlane - nearPlane);
    MProjection.data[3][2] = -1.0;

    Matrix4 MTranslation;
    MTranslation.data[0][0] = 1.0;
    MTranslation.data[1][1] = 1.0;
    MTranslation.data[2][2] = 1.0;
    MTranslation.data[0][3] = -(WxSB_TranslationX->GetValue() - 100) / 50.0;
    MTranslation.data[1][3] = (WxSB_TranslationY->GetValue() - 100) / 50.0;
    MTranslation.data[2][3] = (WxSB_TranslationZ->GetValue() - 100) / 50.0 + 1.0;

    Matrix4 MRotation = GetRotation();

    Matrix4 MScale;
    MScale.data[0][0] = WxSB_ScaleX->GetValue() / 100.0;
    MScale.data[1][1] = WxSB_ScaleY->GetValue() / 100.0;
    MScale.data[2][2] = WxSB_ScaleZ->GetValue() / 100.0;

    Matrix4 MBackTransformation;
    MBackTransformation.data[0][0] = screenSize.GetX() / 2.0;
    MBackTransformation.data[1][1] = screenSize.GetY() / 2.0;
    MBackTransformation.data[2][2] = 1.0;
    MBackTransformation.data[0][3] = (double)screen.GetWidth() / 2.0;
    MBackTransformation.data[1][3] = (double)screen.GetHeight() / 2.0;
    MBackTransformation.data[2][3] = 1.0;

    Matrix4 MModel = MTranslation * MRotation * MScale;

    for (const Segment& seg : data)
    {
        Vector4 p, k;
        p.Set(seg.begin.x, seg.begin.y, seg.begin.z);
        k.Set(seg.end.x, seg.end.y, seg.end.z);

        p = MModel * p;
        k = MModel * k;

		double clipMargin = 0.1;
		if ((p.GetZ() > clipMargin && k.GetZ() <= clipMargin) || (k.GetZ() > clipMargin && p.GetZ() <= clipMargin))
		{
            Vector4 outside = k.GetZ() <= clipMargin ? k : p;
            Vector4 inside = k.GetZ() <= clipMargin ? p : k;

			double clipedAt = abs((clipMargin - outside.GetZ()) / (inside.GetZ() - outside.GetZ()));
            outside.Set(
                (inside.GetX() - outside.GetX()) * clipedAt + outside.GetX(),
                (inside.GetY() - outside.GetY()) * clipedAt + outside.GetY(),
                clipMargin
            );

			p = outside;
			k = inside;
		}
        else if (p.GetZ() <= clipMargin && k.GetZ() <= clipMargin)
			continue;
		
        p = MProjection * p;
        k = MProjection * k;

        p.Set(p.GetX() / p.data[3], p.GetY() / p.data[3], 1.0);
        k.Set(k.GetX() / k.data[3], k.GetY() / k.data[3], 1.0);
        p.data[3] = 1.0;
        k.data[3] = 1.0;
    
        p = MBackTransformation * p;
        k = MBackTransformation * k;

        DC.SetPen(wxPen(wxColor(seg.color.R, seg.color.G, seg.color.B)));
        DC.DrawLine(p.GetX(), p.GetY(), k.GetX(), k.GetY());
    }
}

Matrix4 GUIMyFrame1::GetRotation()
{
    double rotX = -(double)WxSB_RotateX->GetValue() / 180.0 * M_PI;
    double rotY = (double)WxSB_RotateY->GetValue() / 180.0 * M_PI;
    double rotZ = (double)WxSB_RotateZ->GetValue() / 180.0 * M_PI;
    
    Matrix4 MRotateX, MRotateY, MRotateZ;
 
    MRotateX.data[0][0] = 1;
    MRotateX.data[1][1] =  cos(rotX);
    MRotateX.data[1][2] = -sin(rotX);
    MRotateX.data[2][1] =  sin(rotX);
    MRotateX.data[2][2] =  cos(rotX);
    
    MRotateY.data[1][1] = 1;
    MRotateY.data[0][0] =  cos(rotY);
    MRotateY.data[0][2] =  sin(rotY);
    MRotateY.data[2][0] = -sin(rotY);
    MRotateY.data[2][2] =  cos(rotY);

    MRotateZ.data[2][2] = 1;
    MRotateZ.data[0][0] =  cos(rotZ);
    MRotateZ.data[0][1] = -sin(rotZ);
    MRotateZ.data[1][0] =  sin(rotZ);
    MRotateZ.data[1][1] =  cos(rotZ);

    return MRotateZ * MRotateY * MRotateX;
}