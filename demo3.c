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
 * Le but est de trouver une alternative qui fait des formes géométriques beaucoup plus rapidement que gerer individuellement chaque pixel.
 * 
 */

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


void DrawTriangle(int x0,int y0,int x1,int y1,int x2,int y2,int COLOR,HDC dc);
void DrawTriangle3(int x0,int y0,int x1,int y1,int x2,int y2,int COLOR1,int COLOR2,int COLOR3,HDC dc);
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
    int alpha=255;
    int color=R+(G<<8)+(B<<16)+(alpha<<24);
    DrawTriangle(200,200,100,400,300,400,color,mydc);

    DrawTriangle3(500,500,600,200,700,500,((255<<24)+(B<<16)),((255<<24)+(G<<8)),((255<<24)+R),mydc);

    EndPaint(myconsole, &ps);
    ReleaseDC(myconsole, mydc);//Comme pour la gestion de fichier ou de la mémoire, il faut "rendre l'espace de travail" une fois l'utilisaion fini.
    getchar();//Permet de ne pas fermer la fenetre instantanément.
    printf("\e[?25h");//permet de réapparaitre le curseur.
    return 0;
}

//Dessine un triangle d'une couleur unique.
void DrawTriangle(int x0,int y0,int x1,int y1,int x2,int y2,int COLOR,HDC dc){
    TRIVERTEX vertex[3];
    vertex[0].x     = x0;
    vertex[0].y     = y0;
    vertex[0].Red   = ShortToUInt16(COLOR&0xff);
    vertex[0].Green = ShortToUInt16((COLOR>>8)&0xff);
    vertex[0].Blue  = ShortToUInt16((COLOR>>16)&0xff);
    vertex[0].Alpha = 0;

    vertex[1].x     = x1;
    vertex[1].y     = y1;
    vertex[1].Red   = ShortToUInt16(COLOR&0xff);
    vertex[1].Green = ShortToUInt16((COLOR>>8)&0xff);
    vertex[1].Blue  = ShortToUInt16((COLOR>>16)&0xff);
    vertex[1].Alpha = 0;

    vertex[2].x     = x2;
    vertex[2].y     = y2; 
    vertex[2].Red   = ShortToUInt16(COLOR&0xff);
    vertex[2].Green = ShortToUInt16((COLOR>>8)&0xff);
    vertex[2].Blue  = ShortToUInt16((COLOR>>16)&0xff);
    vertex[2].Alpha = 0;

    GRADIENT_TRIANGLE gTriangle;
    gTriangle.Vertex1 = 0;
    gTriangle.Vertex2 = 1;
    gTriangle.Vertex3 = 2;

    GradientFill(dc, vertex, 3, &gTriangle, 1, GRADIENT_FILL_TRIANGLE);
}

//On associe a chaque sommet du triangle(Vertex) une couleur.
void DrawTriangle3(int x0,int y0,int x1,int y1,int x2,int y2,int COLOR1,int COLOR2,int COLOR3,HDC dc){

    TRIVERTEX vertex[3];
    vertex[0].x     = x0;
    vertex[0].y     = y0;
    vertex[0].Red   = ShortToUInt16(COLOR1&0xff);
    vertex[0].Green = ShortToUInt16((COLOR1>>8)&0xff);
    vertex[0].Blue  = ShortToUInt16((COLOR1>>16)&0xff);
    vertex[0].Alpha = 0; //On pourrait rajouter de la transparence. A voir pour plus tard.

    vertex[1].x     = x1;
    vertex[1].y     = y1;
    vertex[1].Red   = ShortToUInt16(COLOR2&0xff);
    vertex[1].Green = ShortToUInt16((COLOR2>>8)&0xff);
    vertex[1].Blue  = ShortToUInt16((COLOR2>>16)&0xff);
    vertex[1].Alpha = 0;

    vertex[2].x     = x2;
    vertex[2].y     = y2; 
    vertex[2].Red   = ShortToUInt16(COLOR3&0xff);
    vertex[2].Green = ShortToUInt16((COLOR3>>8)&0xff);
    vertex[2].Blue  = ShortToUInt16((COLOR3>>16)&0xff);
    vertex[2].Alpha = 0;

    GRADIENT_TRIANGLE gTriangle;
    gTriangle.Vertex1 = 0;//indice de l'element dans l'array Vertex.
    gTriangle.Vertex2 = 1;
    gTriangle.Vertex3 = 2;

    GradientFill(dc, vertex, 3, &gTriangle, 1, GRADIENT_FILL_TRIANGLE);
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