/*
 * Created on Tue Nov 13 2022
 *
 * Copyright (c) 2022 - Naoki Takei
 * 
 * gcc.exe file.c -o file.exe -lm -lgdi32
 * 
 * Le but est de créer un canvas où l'on peut afficher nos pixels.
 * Il y a un petit probleme en (0,0) à cause du curseur.
 * Il faut donc faire un changement de référentiel, un offset, X0 et Y0.
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
    //Get a console handle
    HWND myconsole = GetConsoleWindow();
    //Get a handle to device context
    HDC mydc = GetDC(myconsole);

    int pixel =0;

    //Couleur.
    COLORREF COLOR= RGB(0,0,0);//couleur noire. 
    int R=0;
    int G=0;
    int B=0;
    //Dessine.
    for(int x=X0;x<LARGEUR+X0;x++){
        for(int y=Y0;y<HAUTEUR+Y0;y++){

            R=(x-X0)*255.0/LARGEUR;
            G=255-((((float)(y-Y0)/(2*HAUTEUR))+((float)(x-X0)/(LARGEUR*2)))*255);
            B=(y-Y0)*255.0/HAUTEUR;

            COLOR=RGB(R,G,B);//On change la couleur en fonction de la position du pixel.
            SetPixel(mydc,x,y,COLOR); //SetPixel(InstanceDeLaConsole,x,y,couleur du pixel).
        }
    }

    ReleaseDC(myconsole, mydc);//Comme pour la gestion de fichier ou de la mémoire, il faut "rendre l'espace de travail" une fois l'utilisaion fini.
    getchar();//Permet de ne pas fermer la fenetre instantanément.
    printf("\e[?25h");//permet de réapparaitre le curseur.
    return 0;
}