#include <stdio.h>
#include "image_ppm.h"

int pixel_plus_petit_voisin(OCTET *ImgIn, int i, int j, int nH, int nW) {
    int min = ImgIn[(i-1)*nW+(j-1)];

    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if ((i+dx) >= 0 && (i+dx) < nW && (j+dy) >= 0 && (j+dy) < nH){ 
                if (ImgIn[(i+dx)*nW+(j+dy)] < min ) {
                    min = ImgIn[(i+dx)*nW+(j+dy)];
                } 
            } 
        } 
    } 
    return min;
}

void erosion(OCTET *ImgIn, OCTET *ImgOut, int nH, int nW) {
   for (int i=0; i < nH; i++) {
        for (int j=0; j < nW; j++){
            ImgOut[i*nW+j] = pixel_plus_petit_voisin(ImgIn, i, j, nH, nW);
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

   erosion(ImgIn, ImgOut, nH, nW);

   ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);
   free(ImgIn); free(ImgOut);

   return 1;
}