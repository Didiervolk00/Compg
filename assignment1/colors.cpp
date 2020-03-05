/*
 * Didier Volk
 * 0973139
 * 5-3-2020
 */

#include <iostream>
#include <math.h>
#include <algorithm>

using namespace std;

typedef struct 
{
    float R;
    float G;
    float B;
} RGB;

typedef struct 
{
    float C;
    float M;
    float Y;
    float K;
} CMYK;

typedef struct 
{
    float H;
    float S;
    float L;
} HSL;

void RGBtoCMY(RGB rgb) 
{
    cout << "R = " << rgb.R << endl;
    cout << "G = " << rgb.G << endl;
    cout << "B = " << rgb.B << endl;

    cout << " " << endl;

    float C = 1.00f - (rgb.R);
    cout << "C = " << C << endl;
    float M = 1.00f - (rgb.G);
    cout << "M = " << M << endl;
    float Y = 1.00f - (rgb.B);
    cout << "Y = " << Y << endl;
}


void CMYtoRGB(CMYK cmyk) 
{
    cout << "C = " << cmyk.C << endl;
    cout << "M = " << cmyk.M << endl;
    cout << "Y = " << cmyk.Y << endl;

    cout << " " << endl;

    float R = (1.00f - cmyk.C);
    float G = (1.00f - cmyk.M);
    float B = (1.00f - cmyk.Y);

    cout << "R = " << R << endl;

    cout << "G = " << G << endl;

    cout << "B = " << B << endl;
}


void RGBtoHSL(RGB rgb) 
{
    float S = 0;
    float H = 0;

    float Ra = rgb.R;
    float Ga = rgb.G;
    float Ba = rgb.B;

    float cMin = min({Ra, Ga, Ba});
    float cMax = max({Ra, Ga, Ba});

    float delta = cMax - cMin;

    float L = (cMax + cMin) / 2;

    if (delta == 0) 
    {
        S = 0;
    } 
    else 
    {
        S = delta / (1 - (abs((2 * L - 1))));
    }

    if (delta == 0) 
    {
        H = 0;
    } 
    else if (cMax == Ra) 
    {
        H = 60 * (fmod((Ga - Ba) / delta, 6));
    } 
    else if (cMax == Ga) 
    {
        H = 60 * (((Ba - Ra) / delta) + 2);
    } 
    else if (cMax == Ba) 
    {
        H = 60 * (((Ra - Ga) / delta) + 4);
    }

    if (H < 0) 
    {
        H += 360;
    }

    cout << "H = " << H << endl;
    cout << "S = " << S << endl;
    cout << "L = " << L << endl;

}

void HSLtoRGB(HSL hsl) 
{
    float h = hsl.H;
    float s = hsl.S;
    float l = hsl.L;

    float C = 0;
    float X = 0;
    float m = 0;

    float hh = 0;

    float R = 0;
    float G = 0;
    float B = 0;

    C = (1 - abs(2 * l - 1)) * s;
    hh = h / 60;
    X = C * (1 - abs(fmod(hh, 2) - 1));

    if (hh >= 0 && hh < 1) 
    {
        R = C;
        G = X;
    } 
    else if (hh >= 1 && hh < 2) 
    {
        R = X;
        G = C;
    } 
    else if (hh >= 2 && hh < 3) 
    {
        G = C;
        B = X;
    } 
    else if (hh >= 3 && hh < 4) 
    {
        G = X;
        B = C;
    } 
    else if (hh >= 4 && hh < 5) 
    {
        R = X;
        B = C;
    } 
    else
    {
        R = C;
        B = X;
    }

    m = l - (C / 2);

    R += m;
    G += m;
    B += m;

    cout << "R = " << R << endl;

    cout << "G = " << G << endl;

    cout << "B = " << B << endl;
}

void rgba2rgb(RGB achtergrond, RGB rgb1, float a) 
{
    float R = (1 - a) * achtergrond.R + a * rgb1.R;
    float G = (1 - a) * achtergrond.G + a * rgb1.G;
    float B = (1 - a) * achtergrond.B + a * rgb1.B;

    cout << "R = " << R << endl;
    cout << "G = " << G << endl;
    cout << "B = " << B << endl;
    cout << "a = " << (a + 1) / 2 << endl;
}


int main() 
{
    cout << "Color code conversion program" << endl;

    RGB rgb1;
    rgb1.R = 0.8;
    rgb1.G = 0.2;
    rgb1.B = 0.45;

    RGBtoCMY(rgb1);

    cout << " " << endl;

    CMYK cmyk1;
    cmyk1.C = 0.6;
    cmyk1.M = 0.2;
    cmyk1.Y = 0.9;

    CMYtoRGB(cmyk1);

    cout << " " << endl;

    HSL hsl1;

    hsl1.H = 110;
    hsl1.S = 1;
    hsl1.L = 0.50;

    RGBtoHSL(rgb1);

    cout << " " << endl;

    HSLtoRGB(hsl1);

    return 0;
}