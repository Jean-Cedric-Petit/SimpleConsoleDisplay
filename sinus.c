/*
 * Created on Tue Nov 15 2022
 *
 * Copyright (c) 2022 - Naoki Takei
 * 
 * Attention: Pour compiler, la commande est ci-dessous.
 * gcc.exe file.c -o file.exe -lm -lgdi32 -lmsimg32
 * 
 * Le but est de faire un graphe!
 * 
 */

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define X0 50
#define Y0 100 //Offset en Y.

#define height 500
#define width 2000

#define N 15 //Pour le signal carré; précision/limite de la somme des sinus...

//On hérite les anciennes fonctions qu'on a ecrit.

void DrawTriangle(int x0,int y0,int x1,int y1,int x2,int y2,int COLOR,HDC dc);
void DrawTriangle3(int x0,int y0,int x1,int y1,int x2,int y2,int COLOR1,int COLOR2,int COLOR3,HDC dc);
void DrawRect(int x0,int y0,int x1,int y1,int COLOR,HDC hdc);
void DrawRect2(int x0,int y0,int x1,int y1,int COLOR1,int COLOR2,HDC hdc);

void DrawQuad(int x0,int y0, int x1,int y1, int x2,int y2, int x3,int y3,int COLOR,HDC hdc); 
void DrawQuadA(int *x,int *y,int *COLOR,HDC hdc);

int ShortToUInt16(int shortA);

double fourier_sum(int n,int L,double x);

int main() 
{
    
    printf("\e[?25l");//permet de cacher le curseur de la console
    system("cls");
    //Get a console handle
    HWND myconsole = GetConsoleWindow();
    //Get a handle to device context
    HDC mydc = GetDC(myconsole);
    PAINTSTRUCT ps;

    COLORREF RED = RGB(255,0,0); 
    COLORREF GREEN = RGB(0,255,0);
    //On dessine les axes.
    //32 bits à 1 => Tout blanc : 4294967295
    DrawRect(X0,height+Y0,X0-1,Y0-1,4294967295,mydc);//Axe Y Positif
    DrawRect(X0,height+Y0,X0-1,height*2+Y0+1,4294967295,mydc);//Axe Y négatif
    DrawRect(X0,height+Y0,width+X0,height+Y0-1,4294967295,mydc);//Axe X strictement positif.
    int y=0;
    int y2=0;
    int x=X0;
    for(double i=X0;i<width+X0;i+=0.01){
        y=-1*height*cos((i-X0)/X0)+Y0+height;//Car l'axe y est a l'envers en Computer Graphics d'où le -1.
        //y2=-1*fourier_sum(N,X0,i)*height/4+Y0+height;

        SetPixel(mydc,x,y,RED);
        //SetPixel(mydc,x,y2,GREEN);

        x=(int)i;//Meilleur précision avec i pour le calcul de y. ca permet de faire des meilleurs graphes.
    }

    EndPaint(myconsole, &ps);
    ReleaseDC(myconsole, mydc);//Comme pour la gestion de fichier ou de la mémoire, il faut "rendre l'espace de travail" une fois l'utilisaion fini.
    getchar();//Permet de ne pas fermer la fenetre instantanément.
    printf("\e[?25h");//permet de réapparaitre le curseur.
    return 0;
}

//
// FONCTIONS
//

void DrawRect(int x0,int y0,int x1,int y1,int COLOR,HDC hdc){ 
    TRIVERTEX vertex[2] ;
    vertex[0].x     = x0;
    vertex[0].y     = y0;
    vertex[0].Red   = ShortToUInt16(COLOR&0xff);
    vertex[0].Green = ShortToUInt16((COLOR>>8)&0xff);
    vertex[0].Blue  = ShortToUInt16((COLOR>>16)&0xff);
    vertex[0].Alpha = ShortToUInt16((COLOR>>24)&0xff);;

    vertex[1].x     = x1;
    vertex[1].y     = y1; 
    vertex[1].Red   = ShortToUInt16(COLOR&0xff);
    vertex[1].Green = ShortToUInt16((COLOR>>8)&0xff);
    vertex[1].Blue  = ShortToUInt16((COLOR>>16)&0xff);
    vertex[1].Alpha = ShortToUInt16((COLOR>>24)&0xff);

    GRADIENT_RECT gRect;
    gRect.UpperLeft  = 0;
    gRect.LowerRight = 1;

    GradientFill(hdc, vertex, 2, &gRect, 1, GRADIENT_FILL_RECT_H);
}

int ShortToUInt16(int shortA){
    if(shortA==255){return 65535;}
    int bit1,bit2,bit3,bit4,bit5,bit6,bit7,bit8;
    bit1=(shortA&0x1);
    bit2=(shortA&0x2);
    bit3=(shortA&0x4);
    bit4=(shortA&0x8);
    bit5=(shortA&0x10);
    bit6=(shortA&0x20);
    bit7=(shortA&0x40);
    bit8=(shortA&0x80);
    return (bit1<<1)+(bit2<<2)+(bit3<<3)+(bit4<<4)+(bit5<<5)+(bit6<<6)+(bit7<<7)+(bit8<<8);
}

double fourier_sum(int n,int L,double x){
    double ret=0.0;
    for(int i=1;i<n;i+=2){
        ret+=(sin(i*M_PI*x/L)/i);
    }
    return (4/M_PI)*ret;
}