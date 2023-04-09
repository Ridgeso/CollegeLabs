#include <wx/dc.h>
#include <memory>

#include "ChartClass.h"
#include "vecmat.h"

ChartClass::ChartClass(std::shared_ptr<ConfigClass> c)
{
    cfg = std::move(c);
    x_step = 200;
}

void ChartClass::Set_Range()
{
    double xmin = 9999.9, xmax = -9999.9, ymin = 9999.9, ymax = -9999.9;
    double x, y, step;
    int i;

    xmin=cfg->Get_x_start();
    xmax=cfg->Get_x_stop();

    step=(cfg->Get_x_stop()-cfg->Get_x_start())/(double)x_step;
    x=cfg->Get_x_start();

    for (i=0;i<=x_step;i++)
    {
        y=GetFunctionValue(x);
        if (y>ymax) ymax=y;
        if (y<ymin) ymin=y;
        x=x+step;
    }

    y_min=ymin;
    y_max=ymax;
    x_min=xmin;
    x_max=xmax;
}

double ChartClass::GetFunctionValue(double x)
{
    switch (cfg->Get_F_type())
    {
        case 1:  return x * x;
        case 2:  return 0.5 * exp(4 * x - 3 * x * x);
        default: return x + sin(x * 4.0);
    }
}

void ChartClass::ClipLine(const wxRect& boundaries, Vector& p1, Vector& p2)
{
    auto Intersection = [boundaries](Vector& p)
    {
        return (boundaries.GetBottom() < p.GetY()) << 3 |
               (boundaries.GetTop()    > p.GetY()) << 2 |
               (boundaries.GetRight()  < p.GetX()) << 1 |
               (boundaries.GetLeft()   > p.GetX()) << 0;
    };

    for (int i = 0; i < 2; i++)
    {
        int p1Inte = Intersection(p1);
        int p2Inte = Intersection(p2);

        if ((p1Inte | p2Inte) == 0)
            return;
        if ((p1Inte & p2Inte) != 0)
        {
            p1.Set(0, 0);
            p2.Set(0, 0);
            return;
        }

        if (p1Inte == 0)
        {
            p1Inte = p2Inte;
            Vector tmp = p1;
            p1 = p2;
            p2 = tmp;
        }

        if (p1Inte & 0b0001)
            p1.Set(
                boundaries.GetLeft(),
                p1.GetY() + (p2.GetY() - p1.GetY()) / (p2.GetX() - p1.GetX()) * (boundaries.GetLeft() - p1.GetX())
            );
        if (p1Inte & 0b0010)
            p1.Set(
                boundaries.GetRight(),
                p1.GetY() + (p2.GetY() - p1.GetY()) / (p2.GetX() - p1.GetX()) * (boundaries.GetRight() - p1.GetX())
            );
        if (p1Inte & 0b0100)
            p1.Set(
                p1.GetX() + (p2.GetX() - p1.GetX()) / (p2.GetY() - p1.GetY()) * (boundaries.GetTop() - p1.GetY()),
                boundaries.GetTop()
            );
        if (p1Inte & 0b1000)
            p1.Set(
                p1.GetX() + (p2.GetX() - p1.GetX()) / (p2.GetY() - p1.GetY()) * (boundaries.GetBottom() - p1.GetY()),
                boundaries.GetBottom()
            );
    }
}

void ChartClass::Draw(wxDC *dc, int w, int h)
{
    dc->SetBackground(wxBrush(*wxWHITE));
    dc->Clear();
    dc->SetPen(wxPen(*wxRED));
    wxRect chartRect = { 10, 10, w - 20, h - 20 };
    dc->DrawRectangle(chartRect);

    dc->SetPen(wxPen(*wxBLUE));

    // Matma
    Vector center;
    center.Set(
        chartRect.GetX() + chartRect.GetWidth() / 2.0 + cfg->Get_dX(),
        chartRect.GetY() + chartRect.GetHeight() / 2.0 + cfg->Get_dY()
    );
    double funcStep = (cfg->Get_x_stop() - cfg->Get_x_start()) / x_step;

    float Sx = chartRect.GetWidth() / (cfg->Get_x1() - cfg->Get_x0());
    float Sy = chartRect.GetHeight() / (cfg->Get_y0() - cfg->Get_y1());

    Matrix translation;
    translation.data[0][0] = 1;
    translation.data[1][1] = 1;
    translation.data[0][2] = chartRect.GetX() - Sx * cfg->Get_x0(); // + cfg->Get_dX();
    translation.data[1][2] = chartRect.GetY() - Sy * cfg->Get_y1(); // + cfg->Get_dY();
    
    Matrix translationDiff;
    translationDiff.data[0][0] = 1;
    translationDiff.data[1][1] = 1;
    translationDiff.data[0][2] = cfg->Get_dX();
    translationDiff.data[1][2] = cfg->Get_dY();

    Matrix rotateOrigin;
    rotateOrigin.data[0][0] = cfg->RotateScreenCenter() ?  cos(cfg->Get_Alpha() / 180.0 * M_PI) : 1;
    rotateOrigin.data[0][1] = cfg->RotateScreenCenter() ?  sin(cfg->Get_Alpha() / 180.0 * M_PI) : 0;
    rotateOrigin.data[1][0] = cfg->RotateScreenCenter() ? -sin(cfg->Get_Alpha() / 180.0 * M_PI) : 0;
    rotateOrigin.data[1][1] = cfg->RotateScreenCenter() ?  cos(cfg->Get_Alpha() / 180.0 * M_PI) : 1;

    Matrix rotateCenter;
    rotateCenter.data[0][0] = !cfg->RotateScreenCenter() ?  cos(cfg->Get_Alpha() / 180.0 * M_PI) : 1;
    rotateCenter.data[0][1] = !cfg->RotateScreenCenter() ?  sin(cfg->Get_Alpha() / 180.0 * M_PI) : 0;
    rotateCenter.data[1][0] = !cfg->RotateScreenCenter() ? -sin(cfg->Get_Alpha() / 180.0 * M_PI) : 0;
    rotateCenter.data[1][1] = !cfg->RotateScreenCenter() ?  cos(cfg->Get_Alpha() / 180.0 * M_PI) : 1;

    Matrix scale;
    scale.data[0][0] = Sx;
    scale.data[1][1] = Sy;
    
    Matrix ortho = translation * rotateOrigin * translationDiff * scale;
    #define transformPoint(point) rotateCenter * (ortho * point - center) + center
    
    // Points
    Vector axisX[2];
    axisX[0].Set(cfg->Get_x_start(), 0);
    axisX[1].Set(cfg->Get_x_stop(), 0);
    Vector arrowX[4];
    arrowX[0].Set(cfg->Get_x_stop() - 0.1, 0.05);
    arrowX[1].Set(cfg->Get_x_stop(), 0);
    arrowX[2].Set(cfg->Get_x_stop(), 0);
    arrowX[3].Set(cfg->Get_x_stop() - 0.1, -0.05);

    axisX[0] = transformPoint(axisX[0]);
    axisX[1] = transformPoint(axisX[1]);
    arrowX[0] = transformPoint(arrowX[0]);
    arrowX[1] = transformPoint(arrowX[1]);
    arrowX[2] = transformPoint(arrowX[2]);
    arrowX[3] = transformPoint(arrowX[3]);

    Vector axisY[2];
    axisY[0].Set(0, Get_Y_min());
    axisY[1].Set(0, Get_Y_max());
    Vector arrowY[4];
    arrowY[0].Set(0.05, Get_Y_max() - 0.1);
    arrowY[1].Set(0, Get_Y_max());
    arrowY[2].Set(0, Get_Y_max());
    arrowY[3].Set(-0.05, Get_Y_max() - 0.1);

    axisY[0] = transformPoint(axisY[0]);
    axisY[1] = transformPoint(axisY[1]);
    arrowY[0] = transformPoint(arrowY[0]);
    arrowY[1] = transformPoint(arrowY[1]);
    arrowY[2] = transformPoint(arrowY[2]);
    arrowY[3] = transformPoint(arrowY[3]);

    Vector chartMarks[6];
    chartMarks[0].Set(cfg->Get_x_start() / 2, 0);
    chartMarks[1].Set(cfg->Get_x_stop() / 3, 0);
    chartMarks[2].Set(cfg->Get_x_stop() / 3 * 2, 0);
    chartMarks[3].Set(0, Get_Y_min() / 2);
    chartMarks[4].Set(0, Get_Y_max() / 3);
    chartMarks[5].Set(0, Get_Y_max() / 3 * 2);

    // Przycinanie
    ClipLine(chartRect, axisX[0], axisX[1]);
    ClipLine(chartRect, axisY[0], axisY[1]);
    
    ClipLine(chartRect, arrowX[0], arrowX[1]);
    ClipLine(chartRect, arrowX[2], arrowX[3]);
    ClipLine(chartRect, arrowY[0], arrowY[1]);
    ClipLine(chartRect, arrowY[2], arrowY[3]);

    // Rysowanie
    wxPoint arrows[] = {
        // X
        { (int)axisX[0].GetX(), (int)axisX[0].GetY() },
        { (int)axisX[1].GetX(), (int)axisX[1].GetY() },
        // Y
        { (int)axisY[0].GetX(), (int)axisY[0].GetY() },
        { (int)axisY[1].GetX(), (int)axisY[1].GetY() },
        // X arrow
        { (int)arrowX[0].GetX(), (int)arrowX[0].GetY() },
        { (int)arrowX[1].GetX(), (int)arrowX[1].GetY() },
        { (int)arrowX[2].GetX(), (int)arrowX[2].GetY() },
        { (int)arrowX[3].GetX(), (int)arrowX[3].GetY() },
        // Y arrow
        { (int)arrowY[0].GetX(), (int)arrowY[0].GetY() },
        { (int)arrowY[1].GetX(), (int)arrowY[1].GetY() },
        { (int)arrowY[2].GetX(), (int)arrowY[2].GetY() },
        { (int)arrowY[3].GetX(), (int)arrowY[3].GetY() }
    };
    for (int i = 0; i < sizeof(arrows) / sizeof(wxPoint); i += 2)
        dc->DrawLine(arrows[i], arrows[i + 1]);

    for (int i = 0; i < 6; i++)
    {
        Vector bs, be;
        wxString chartText;
        if (i < 3)
        {
            bs.Set(chartMarks[i].GetX(), chartMarks[i].GetY() - 0.05);
            be.Set(chartMarks[i].GetX(), chartMarks[i].GetY() + 0.05);
            chartText = wxString::Format(_("%.2f"), chartMarks[i].GetX());
        }
        else
        {
            bs.Set(chartMarks[i].GetX() - 0.05, chartMarks[i].GetY());
            be.Set(chartMarks[i].GetX() + 0.05, chartMarks[i].GetY());
            chartText = wxString::Format(_("%.2f"), chartMarks[i].GetY());
        }
        chartMarks[i] = transformPoint(chartMarks[i]);
        bs = transformPoint(bs);
        be = transformPoint(be);
        dc->DrawLine(
            bs.GetX(), bs.GetY(),
            be.GetX(), be.GetY()
        );
        dc->DrawRotatedText(chartText, chartMarks[i].GetX(), chartMarks[i].GetY(), cfg->Get_Alpha());
    }

    dc->SetPen(wxPen(*wxGREEN));
    Vector p1, p2;
    for (double x = cfg->Get_x_start() + funcStep; x < cfg->Get_x_stop(); x += funcStep)
    {
        p1.Set(x, GetFunctionValue(x));
        p2.Set(x + funcStep, GetFunctionValue(x + funcStep));
        p1 = transformPoint(p1);
        p2 = transformPoint(p2);

        ClipLine(chartRect, p1, p2);
        dc->DrawLine(
            p1.GetX(), p1.GetY(),
            p2.GetX(), p2.GetY()
        );
    }
}

double ChartClass::Get_Y_min()
{
    Set_Range();
    return y_min;
}

double ChartClass::Get_Y_max()
{
    Set_Range();
    return y_max;
}
