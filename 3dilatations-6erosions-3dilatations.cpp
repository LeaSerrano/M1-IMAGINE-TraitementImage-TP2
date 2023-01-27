#include <stdio.h>
#include "image_ppm.h"

bool pixel_noir_voisin(OCTET *ImgIn, int i, int j, int nH, int nW) {
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if ((i+dx) >= 0 && (i+dx) < nW && (j+dy) >= 0 && (j+dy) < nH){ 
                if (ImgIn[(i+dx)*nW+(j+dy)] == 0) {
                    return true;
                } 
            } 
        } 
    } 
    return false;
}

void dilatation(OCTET *ImgIn, OCTET *ImgOut, int nH, int nW) {
  for (int i=0; i < nH; i++) {
        for (int j=0; j < nW; j++){
            if (pixel_noir_voisin(ImgIn, i, j, nH, nW) == true) {
                ImgOut[i*nW+j] = 0;
            } 
            else {
                ImgOut[i*nW+j] = 255;
            }
        }
    } 
}

bool pixel_blanc_voisin(OCTET *ImgIn, int i, int j, int nH, int nW) {
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if ((i+dx) >= 0 && (i+dx) < nW && (j+dy) >= 0 && (j+dy) < nH){ 
                if (ImgIn[(i+dx)*nW+(j+dy)] == 255) {
                    return true;
                } 
            } 
        } 
    } 
    return false;
}

void erosion(OCTET *ImgIn, OCTET *ImgOut, int nH, int nW) {
   for (int i=0; i < nH; i++) {
        for (int j=0; j < nW; j++){
            if (pixel_blanc_voisin(ImgIn, i, j, nH, nW) == true) {
                ImgOut[i*nW+j] = 255;
            } 
            else {
                ImgOut[i*nW+j] = 0;
            }
        }
    }  
}

int main(int argc, char* argv[])
{
  char cNomImgLue[250], cNomImgEcrite[250];
  int nH, nW, nTaille;
  
  if (argc != 3) 
     {
       printf("Usage: ImageIn.pgm ImageOut.pgm \n"); 
       exit (1) ;
     }
   
   sscanf (argv[1],"%s",cNomImgLue) ;
   sscanf (argv[2],"%s",cNomImgEcrite);

   OCTET *ImgIn, *ImgOut;
   
   lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;
  
   allocation_tableau(ImgIn, OCTET, nTaille);
   lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
   allocation_tableau(ImgOut, OCTET, nTaille);

   OCTET *ImgTemp1, *ImgTemp2, *ImgTemp3, *ImgTemp4, *ImgTemp5, *ImgTemp6, *ImgTemp7, *ImgTemp8, *ImgTemp9, *ImgTemp10, *ImgTemp11;
   allocation_tableau(ImgTemp1, OCTET, nH*nW);
   allocation_tableau(ImgTemp2, OCTET, nH*nW);
   allocation_tableau(ImgTemp3, OCTET, nH*nW);
   allocation_tableau(ImgTemp4, OCTET, nH*nW);
   allocation_tableau(ImgTemp5, OCTET, nH*nW);
   allocation_tableau(ImgTemp6, OCTET, nH*nW);
   allocation_tableau(ImgTemp7, OCTET, nH*nW);
   allocation_tableau(ImgTemp8, OCTET, nH*nW);
   allocation_tableau(ImgTemp9, OCTET, nH*nW);
   allocation_tableau(ImgTemp10, OCTET, nH*nW);
   allocation_tableau(ImgTemp11, OCTET, nH*nW);

   dilatation(ImgIn, ImgTemp1, nH, nW);
   dilatation(ImgTemp1, ImgTemp2, nH, nW);
   dilatation(ImgTemp2, ImgTemp3, nH, nW);

   erosion(ImgTemp3, ImgTemp4, nH, nW);
   erosion(ImgTemp4, ImgTemp5, nH, nW);
   erosion(ImgTemp5, ImgTemp6, nH, nW);

   erosion(ImgTemp6, ImgTemp7, nH, nW);
   erosion(ImgTemp7, ImgTemp8, nH, nW);
   erosion(ImgTemp8, ImgTemp9, nH, nW);

   dilatation(ImgTemp9, ImgTemp10, nH, nW);
   dilatation(ImgTemp10, ImgTemp11, nH, nW);
   dilatation(ImgTemp11, ImgOut, nH, nW);
   
   ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);
   free(ImgIn); free(ImgOut);

   return 1;
}