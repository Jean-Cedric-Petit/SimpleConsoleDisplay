/*
 * Created on Tue Nov 15 2022
 *
 * Copyright (c) 2022 - Naoki Takei
 * 
 * Attention: Pour compiler, la commande est ci-dessous.
 * gcc.exe file.c -o file.exe -lm -lmsimg32
 * 
 * Si on veut utiliser SetPixel, ne pas oublier de rajouter -lgdi32 
 * 
 * Le but est de voir une autre fonction, qui fait un carré a l'aide de 2 sommets(Vertices)
 */

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


void DrawRect(int x0,int y0,int x1,int y1,int COLOR,HDC hdc);
void DrawRect2(int x0,int y0,int x1,int y1,int COLOR1,int COLOR2,HDC hdc);
int ShortToUInt16(int shortA);

int main() 
{
    
    printf("\e[?25l");//permet de cacher le curseur de la console
    system("cls");
    //Get a console handle
    HWND myconsole = GetConsoleWindow();
    //Get a handle to device context
    HDC mydc = GetDC(myconsole);

    PAINTSTRUCT ps;
    int R=255;
    int G=255;
    int B=255;
    int alpha=128;
    int color=R+(G<<8)+(B<<16)+(alpha<<24);

    DrawRect(200,200,400,201,color,mydc);//Est ce que ca dessine une ligne ?
    DrawRect(600,200,700,400,((255<<24)+(G<<8)),mydc);

    DrawRect2(500,500,700,700,((255<<24)+(B<<16)),((255<<24)+R),mydc);

    EndPaint(myconsole, &ps);
    ReleaseDC(myconsole, mydc);//Comme pour la gestion de fichier ou de la mémoire, il faut "rendre l'espace de travail" une fois l'utilisaion fini.
    getchar();//Permet de ne pas fermer la fenetre instantanément.
    printf("\e[?25h");//permet de réapparaitre le curseur.
    return 0;
}


void DrawRect(int x0,int y0,int x1,int y1,int COLOR,HDC hdc){ 
    TRIVERTEX vertex[2] ;
    vertex[0].x     = x0;
    vertex[0].y     = y0;
    vertex[0].Red   = ShortToUInt16(COLOR&0xff);
    vertex[0].Green = ShortToUInt16((COLOR>>8)&0xff);
    vertex[0].Blue  = ShortToUInt16((COLOR>>16)&0xff);
    vertex[0].Alpha = 0x0000;

    vertex[1].x     = x1;
    vertex[1].y     = y1; 
    vertex[1].Red   = ShortToUInt16(COLOR&0xff);
    vertex[1].Green = ShortToUInt16((COLOR>>8)&0xff);
    vertex[1].Blue  = ShortToUInt16((COLOR>>16)&0xff);
    vertex[1].Alpha = 0x0000;

    GRADIENT_RECT gRect;
    gRect.UpperLeft  = 0;
    gRect.LowerRight = 1;

    GradientFill(hdc, vertex, 2, &gRect, 1, GRADIENT_FILL_RECT_H);
}

void DrawRect2(int x0,int y0,int x1,int y1,int COLOR1,int COLOR2,HDC hdc){ 
    TRIVERTEX vertex[2] ;
    vertex[0].x     = x0;
    vertex[0].y     = y0;
    vertex[0].Red   = ShortToUInt16(COLOR1&0xff);
    vertex[0].Green = ShortToUInt16((COLOR1>>8)&0xff);
    vertex[0].Blue  = ShortToUInt16((COLOR1>>16)&0xff);
    vertex[0].Alpha = 0x0000;

    vertex[1].x     = x1;
    vertex[1].y     = y1; 
    vertex[1].Red   = ShortToUInt16(COLOR2&0xff);
    vertex[1].Green = ShortToUInt16((COLOR2>>8)&0xff);
    vertex[1].Blue  = ShortToUInt16((COLOR2>>16)&0xff);
    vertex[1].Alpha = 0x0000;

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