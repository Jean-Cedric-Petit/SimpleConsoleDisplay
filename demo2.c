/*
 * Created on Tue Nov 13 2022
 *
 * Copyright (c) 2022 - Naoki Takei
 * 
 * Rappel: Pour compiler, la commande est ci-dessous.
 * gcc.exe file.c -o file.exe -lm -lgdi32
 * 
 * Le but est d'essayer de faire un rendu de plusieur "images" basiques a l'aide de la fonction SetPixel().
 * On peut donc voir les limitations de celle ci.
 */
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define X0 100
#define Y0 100
#define LARGEUR 500
#define HAUTEUR 500

int main() 
{
    printf("\e[?25l");//permet de cacher le curseur de la console
    system("cls");
    HWND myconsole = GetConsoleWindow();
    HDC mydc = GetDC(myconsole);
    COLORREF COLOR=RGB(255,255,255); 
    int frame=0;
    
    //On veut donc faire défiler des images à la suite.
    while(frame<1000){
        system("cls");//Une expérience intéressante est de commenter cette ligne. Les pixels vont ils se décaler a cause du printf("\n") ?
        printf("\t\t\t\t\t\t\t\tframe:%d/1000\n",frame);
        for(int y=Y0;y<HAUTEUR+Y0;y++){
            for(int x=X0;x<LARGEUR+X0;x++){
                switch (frame%8)//Permet de permuter la couleur entre chaque rendu
                {
                case 0:
                    COLOR=RGB(255,255,255); 
                    break;
                case 1:
                    COLOR=RGB(255,0,0); 
                    break;
                case 2:
                    COLOR=RGB(255,255,0); 
                    break;
                case 3:
                    COLOR=RGB(0,255,0); 
                    break;
                case 4:
                    COLOR=RGB(0,255,255); 
                    break;
                case 5:
                    COLOR=RGB(0,0,255); 
                    break;
                case 6:
                    COLOR=RGB(255,0,255); 
                    break;
                case 7:
                    COLOR=RGB(128,128,128); 
                    break;
                default:
                    break;
                }
                SetPixel(mydc,x,y,COLOR);
            }
        }
        frame++;
        Sleep(16);//60fps ?
        //En fait cette ligne est inutile car le processus d'afficher chaque pixel individuellement est tellement lent.
        //Donc on arrivera jamais a faire 60 images par seconde.
    }
    ReleaseDC(myconsole, mydc);
    getchar();
    printf("\e[?25h");//permet de réapparaitre le curseur.
    return 0;
}