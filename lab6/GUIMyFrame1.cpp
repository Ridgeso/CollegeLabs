#include "GUIMyFrame1.h"
#include <utility>

GUIMyFrame1::GUIMyFrame1(wxWindow* parent)
	: MyFrame1( parent )
{
	m_staticText1->SetLabel(_(L"Jasno\u015B\u0107"));
	m_b_threshold->SetLabel(_(L"Pr\u00F3g 128"));
	this->SetBackgroundColour(wxColor(192, 192, 192));
	m_scrolledWindow->SetScrollbars(25, 25, 52, 40);
	m_scrolledWindow->SetBackgroundColour(wxColor(192, 192, 192));
}

void GUIMyFrame1::m_scrolledWindow_update( wxUpdateUIEvent& event )
{
	Repaint();
}

int GetPixelCoord(int y, int x, int width)
{
	return (y * width + x) * 3;
}

void GUIMyFrame1::m_b_grayscale_click( wxCommandEvent& event )
{
	// TO DO: Konwersja do skali szarosci
	Img_Cpy = Img_Org.Copy();
	unsigned char* orgPixel = Img_Org.GetData();
	unsigned char* cpyPixel = Img_Cpy.GetData();
	
	for (int l = 0; l < Img_Org.GetHeight() * Img_Org.GetWidth(); l++)
	{
		unsigned char Y = (char)(0.299 * (double)orgPixel[0] + 0.587 * (double)orgPixel[1] + 0.114 * (double)orgPixel[2]);

		cpyPixel[0] = Y;
		cpyPixel[1] = Y;
		cpyPixel[2] = Y;

		orgPixel += 3;
		cpyPixel += 3;
	}
}

void GUIMyFrame1::m_b_blur_click( wxCommandEvent& event )
{
	// TO DO: Rozmywanie obrazu (blur)
	Img_Cpy = Img_Org.Copy();
	const int blureLevel = 5;

	int maxHeight= Img_Org.GetHeight();
	int maxWidth = Img_Org.GetWidth();
	unsigned char* orgPixel = Img_Org.GetData();
	unsigned char* cpyPixel = Img_Cpy.GetData();
	
	auto getAvrageSum = [orgPixel, blureLevel, maxHeight, maxWidth](int y, int x, int chanel) -> int
	{
		int sum = 0;
		int pixelCount = 0;

		for (int yb = y - blureLevel; yb <= y + blureLevel; yb++)
		{
			if (yb < 0 || maxHeight <= yb) continue;

			for (int xb = x - blureLevel; xb <= x + blureLevel; xb++)
			{
				if (xb < 0 || maxWidth<= xb) continue;

				sum += orgPixel[GetPixelCoord(yb, xb, maxWidth) + chanel];
				pixelCount++;
			}
		}
		return sum / pixelCount;
	};

	for (int y = 0; y < maxHeight; y++)
		for (int x = 0; x < maxWidth; x++)
		{
			int bluredR = getAvrageSum(y, x, 0);
			int bluredG = getAvrageSum(y, x, 1);
			int bluredB = getAvrageSum(y, x, 2);

			cpyPixel[0] = bluredR;
			cpyPixel[1] = bluredG;
			cpyPixel[2] = bluredB;

			cpyPixel += 3;
		}
}

void GUIMyFrame1::m_b_mirror_click( wxCommandEvent& event )
{
	// TO DO: Odbicie lustrzane
	Img_Cpy = Img_Org.Copy();
	unsigned char* orgPixel = Img_Org.GetData() + (Img_Org.GetWidth() - 1) * 3;
	unsigned char* cpyPixel = Img_Cpy.GetData();

	for (int y = 0; y < Img_Org.GetHeight(); y++)
	{
		for (int x = 0; x < Img_Org.GetWidth(); x++)
		{
			cpyPixel[0] = orgPixel[0];
			cpyPixel[1] = orgPixel[1];
			cpyPixel[2] = orgPixel[2];

			orgPixel -= 3;
			cpyPixel += 3;
		}
		orgPixel = Img_Org.GetData() + ((y + 1) * Img_Org.GetWidth() - 1) * 3;
	}
}

void GUIMyFrame1::m_b_replace_click( wxCommandEvent& event )
{
	// TO DO: Zamiana kolorow 
	Img_Cpy = Img_Org.Copy();
	unsigned char* orgPixel = Img_Org.GetData();
	unsigned char* cpyPixel = Img_Cpy.GetData();

	for (int l = 0; l < Img_Org.GetHeight() * Img_Org.GetWidth(); l++)
	{
		if (orgPixel[0] == 254 && orgPixel[1] == 0 && orgPixel[2] == 0)
		{
			cpyPixel[0] = 0;
			cpyPixel[1] = 0;
			cpyPixel[2] = 255;
		}
		else
		{
			cpyPixel[0] = orgPixel[0];
			cpyPixel[1] = orgPixel[1];
			cpyPixel[2] = orgPixel[2];
		}

		orgPixel += 3;
		cpyPixel += 3;
	}
}

void GUIMyFrame1::m_b_rescale_click( wxCommandEvent& event )
{
	// TO DO: Zmiana rozmiarow do 320x240
	wxClientDC dc(m_scrolledWindow);
	dc.Clear();
	
	Img_Cpy.Resize({ 320, 240 }, { 0, 0 });
	const int smallWidth = 320, smallHeight = 240;
	int resX = Img_Org.GetWidth() / smallWidth;
	int resY = Img_Org.GetHeight() / smallHeight;
	unsigned char* OrgData = Img_Org.GetData();
	unsigned char* CpyData = Img_Cpy.GetData();
	
	for (int y = 0; y < smallHeight; y++)
	{
		for (int x = 0; x < smallWidth; x++)
		{
			int orgPixelCoord = GetPixelCoord(y * resY, x * resX, Img_Org.GetWidth());
			int copyPixelCoord = GetPixelCoord(y, x, Img_Cpy.GetWidth());

			CpyData[copyPixelCoord + 0] = OrgData[orgPixelCoord + 0];
			CpyData[copyPixelCoord + 1] = OrgData[orgPixelCoord + 1];
			CpyData[copyPixelCoord + 2] = OrgData[orgPixelCoord + 2];
		}
	}
}

void GUIMyFrame1::m_b_rotate_click( wxCommandEvent& event )
{
	// TO DO: Obrot o 30 stopni
	Img_Cpy = Img_Org.Rotate(30 * M_PI / 180.0, { Img_Org.GetWidth() / 2, Img_Org.GetHeight() / 2 });
}

void GUIMyFrame1::m_b_rotate_hue_click( wxCommandEvent& event )
{
	// TO DO: Przesuniecie Hue o 180 stopni
	Img_Cpy = Img_Org.Copy();
	const float angle = 180.f / 360.f;
	auto Hue2RGB = [](float v1, float v2, float vH) -> float
	{
		if (vH < 0) vH += 1;
		if (vH > 1) vH -= 1;
		if ((6 * vH) < 1) return (v1 + (v2 - v1) * 6.f * vH);
		if ((2 * vH) < 1) return (v2);
		if ((3 * vH) < 2) return (v1 + (v2 - v1) * ((2.f / 3.f) - vH) * 6.f);
		return (v1);
	};
	unsigned char* orgPixel = Img_Org.GetData();
	unsigned char* cpyPixel = Img_Cpy.GetData();

	for (int l = 0; l < Img_Org.GetHeight() * Img_Org.GetWidth(); l++)
	{
		int r = orgPixel[0];
		int g = orgPixel[1];
		int b = orgPixel[2];


		float H, S, L;
		float varR = (r / 255.f);
		float varG = (g / 255.f);
		float varB = (b / 255.f);

		float varMin = std::min({ varR, varG, varB });
		float varMax = std::max({ varR, varG, varB });
		float delMax = varMax - varMin;

		L = (varMax + varMin) / 2.f;

		if (delMax == 0)
		{
			H = 0;
			S = 0;
		}
		else
		{
			if (L < 0.5) S = delMax / (varMax + varMin);
			else S = delMax / (2 - varMax - varMin);

			float delR = (((varMax - varR) / 6.f) + (delMax / 2.f)) / delMax;
			float delG = (((varMax - varG) / 6.f) + (delMax / 2.f)) / delMax;
			float delB = (((varMax - varB) / 6.f) + (delMax / 2.f)) / delMax;

			if (varR == varMax) H = delB - delG;
			else if (varG == varMax) H = (1.f / 3.f) + delR - delB;
			else if (varB == varMax) H = (2.f / 3.f) + delG - delR;
			if (H < 0) H += 1;
			if (H > 1) H -= 1;
		}
		H += angle;
		if (H > 1) H -= 1;

		if (S == 0)
		{

			r = L * 255.f;
			g = L * 255.f;
			b = L * 255.f;
		}
		else
		{
			float var1, var2;
			if (L < 0.5) var2 = L * (1 + S);
			else var2 = (L + S) - (S * L);

			var1 = 2 * L - var2;

			r = 255 * Hue2RGB(var1, var2, H + (1.f / 3.f));
			g = 255 * Hue2RGB(var1, var2, H);
			b = 255 * Hue2RGB(var1, var2, H - (1.f / 3.f));
		}

		cpyPixel[0] = r;
		cpyPixel[1] = g;
		cpyPixel[2] = b;

		orgPixel += 3;
		cpyPixel += 3;
	}
}

void GUIMyFrame1::m_b_mask_click( wxCommandEvent& event )
{
	// TO DO: Ustawienie maski obrazu
	Img_Cpy = Img_Org.Copy();
	unsigned char* orgPixel = Img_Org.GetData();
	unsigned char* cpyPixel = Img_Cpy.GetData();
	unsigned char* maskPixel= Img_Mask.GetData();
	
	for (int l = 0; l < Img_Org.GetHeight() * Img_Org.GetWidth(); l++)
	{
		if (*maskPixel == 255)
		{
			cpyPixel[0] = orgPixel[0];
			cpyPixel[1] = orgPixel[1];
			cpyPixel[2] = orgPixel[2];
		}
		else
		{
			cpyPixel[0] = 0;
			cpyPixel[1] = 0;
			cpyPixel[2] = 0;
		}

		orgPixel += 3;
		cpyPixel += 3;
		maskPixel += 3;
	}
}

void GUIMyFrame1::m_s_brightness_scroll( wxScrollEvent& event )
{
	// Tutaj, w reakcji na zmiane polozenia suwaka, wywolywana jest funkcja
	// Brightness(...), ktora zmienia jasnosc. W tym miejscu nic nie
	// zmieniamy. Do uzupelnienia pozostaje funkcja Brightness(...)
	Brightness(m_s_brightness->GetValue() - 100);
	Repaint();
}

void GUIMyFrame1::m_s_contrast_scroll( wxScrollEvent& event )
{
	// Tutaj, w reakcji na zmiane polozenia suwaka, wywolywana jest funkcja
	// Contrast(...), ktora zmienia kontrast. W tym miejscu nic nie
	// zmieniamy. Do uzupelnienia pozostaje funkcja Contrast(...)
	Contrast(m_s_contrast->GetValue() - 100);
	Repaint();
}

void GUIMyFrame1::m_b_prewitt_click( wxCommandEvent& event )
{
	// TO DO: Pionowa maska Prewitta
	Img_Cpy = Img_Org.Copy();
	wxImage Img_Temp = Img_Org.ConvertToGreyscale();

	const int prewittMaskX[3][3] = { { -1, -1, -1}, {  0,  0,  0 }, {  1,  1,  1 } };
	const int prewittMaskY[3][3] = { { -1,  0,  1}, { -1,  0,  1 }, { -1,  0,  1 } };

	int maxHeight = Img_Temp.GetHeight();
	int maxWidth = Img_Temp.GetWidth();
	unsigned char* tempPixel = Img_Temp.GetData();
	unsigned char* cpyPixel = Img_Cpy.GetData();
	
	auto GetGradient = [maxWidth, maxHeight, tempPixel, prewittMaskY, prewittMaskX](int y, int x) -> std::pair<int, int>
	{
		int gy1 = 0, gy2 = 0;
		for (int yg = -1; yg < 2; yg++)
		{
			if (y + yg < 0 || maxHeight <= y + yg) continue;

			for (int xg = -1; xg < 2; xg++)
			{
				if (x + xg < 0 || maxWidth <= x + xg) continue;

				int coord = GetPixelCoord(y + yg, x + xg, maxWidth);
				gy1 += prewittMaskY[yg + 1][xg + 1] * tempPixel[coord];
				gy2 += prewittMaskY[yg + 1][2 - xg - 1] * tempPixel[coord];
			}
		}
		return { gy1, gy2 };
	};

	for (int y = 0; y < maxHeight; y++)
		for (int x = 0; x < maxWidth; x++)
		{
			auto [gy1, gy2] = GetGradient(y, x);
			//int g = std::sqrt(gy1 * gy1 + gy2 * gy2);
			//int g = std::sqrt(gy1 * gy1);
			int g = gy1;
			if (g > 255) g = 255;
			if (g < 0) g = 0;
			cpyPixel[0] = g;
			cpyPixel[1] = g;
			cpyPixel[2] = g;

			cpyPixel += 3;
		}
}

void GUIMyFrame1::m_b_threshold_click( wxCommandEvent& event )
{
	// TO DO: Prog o wartosci 128 dla kazdego kanalu niezaleznie
	Img_Cpy = Img_Org.Copy();
	unsigned char* orgPixel = Img_Org.GetData();
	unsigned char* cpyPixel = Img_Cpy.GetData();

	for (int l = 0; l < Img_Org.GetHeight() * Img_Org.GetWidth(); l++)
	{
		cpyPixel[0] = orgPixel[0] > 128 ? 255 : 0;
		cpyPixel[1] = orgPixel[1] > 128 ? 255 : 0;
		cpyPixel[2] = orgPixel[2] > 128 ? 255 : 0;

		orgPixel += 3;
		cpyPixel += 3;
	}
}


void GUIMyFrame1::Contrast(int value)
{
	// TO DO: Zmiana kontrastu obrazu. value moze przyjmowac wartosci od -100 do 100
	Img_Cpy = Img_Org.Copy();
	unsigned char* orgPixel = Img_Org.GetData();
	unsigned char* cpyPixel = Img_Cpy.GetData(); 
	
	float v = (value + 100.f) / (-63.f * value / 64.f + 100.f);

	for (int l = 0; l < Img_Org.GetHeight() * Img_Org.GetWidth(); l++)
	{
		int r = ((orgPixel[0] / 255.f - 0.5f) * v + 0.5f) * 255;
		int g = ((orgPixel[1] / 255.f - 0.5f) * v + 0.5f) * 255;
		int b = ((orgPixel[2] / 255.f - 0.5f) * v + 0.5f) * 255;

		if		(r < 0)	  r = 0;
		else if (r > 255) r = 255;
		if		(g < 0)   g = 0;
		else if (g > 255) g = 255;
		if		(b < 0)   b = 0;
		else if (b > 255) b = 255;

		cpyPixel[0] = (unsigned char)r;
		cpyPixel[1] = (unsigned char)g;
		cpyPixel[2] = (unsigned char)b;

		orgPixel += 3;
		cpyPixel += 3;
	}
}

void GUIMyFrame1::Repaint()
{
	wxBitmap bitmap(Img_Cpy);          // Tworzymy tymczasowa bitmape na podstawie Img_Cpy
	wxClientDC dc(m_scrolledWindow);   // Pobieramy kontekst okna
	m_scrolledWindow->DoPrepareDC(dc); // Musimy wywolac w przypadku wxScrolledWindow, zeby suwaki prawidlowo dzialaly
	dc.DrawBitmap(bitmap, 0, 0, true); // Rysujemy bitmape na kontekscie urzadzenia
}

void GUIMyFrame1::Brightness(int value)
{
	// TO DO: Zmiana jasnosci obrazu. value moze przyjmowac wartosci od -100 do 100
	Img_Cpy = Img_Org.Copy();
	unsigned char* orgPixel = Img_Org.GetData();
	unsigned char* cpyPixel = Img_Cpy.GetData();

	for (int l = 0; l < Img_Org.GetHeight() * Img_Org.GetWidth(); l++)
	{
		int r = orgPixel[0] + value;
		int g = orgPixel[1] + value;
		int b = orgPixel[2] + value;
		
		if (r < 0) r = 0;
		else if (r > 255) r = 255;
		if (g < 0) g = 0;
		else if (g > 255) g = 255;
		if (b < 0) b = 0;
		else if (b > 255) b = 255;

		cpyPixel[0] = (unsigned char)r;
		cpyPixel[1] = (unsigned char)g;
		cpyPixel[2] = (unsigned char)b;
	
		orgPixel += 3;
		cpyPixel += 3;
	}
}