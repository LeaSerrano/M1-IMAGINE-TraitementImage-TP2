#include <stdio.h>
#include "image_ppm.h"
#include <climits>

int pixel_plus_grand_voisin(OCTET *ImgIn, int i, int j, int nH, int nW) {
    int max = INT_MIN;

    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if ((i+dx) >= 0 && (i+dx) < nW && (j+dy) >= 0 && (j+dy) < nH){ 
                /*if (dx == -1 && dy == -1) {
                    max = ImgIn[(i-1)*nW+(j-1)];
                }*/
                if (ImgIn[(i+dx)*nW+(j+dy)] > max ) {
                    max = ImgIn[(i+dx)*nW+(j+dy)];
                } 
            } 
        } 
    } 
    return max;
}

void dilatation(OCTET *ImgIn, OCTET *ImgOut, int nH, int nW) {
    for (int i=0; i < nH; i++) {
        for (int j=0; j < nW; j++){
            ImgOut[i*nW+j] = pixel_plus_grand_voisin(ImgIn, i, j, nH, nW);
        }
    }   
}

int pixel_plus_petit_voisin(OCTET *ImgIn, int i, int j, int nH, int nW) {
    int min = INT_MAX;

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
   
   lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;

   int nTaille3 = nTaille * 3;
  
   allocation_tableau(ImgIn, OCTET, nTaille3);
   lire_image_ppm(cNomImgLue, ImgIn, nH * nW);
   allocation_tableau(ImgOut, OCTET, nTaille3);

    OCTET *tabIdR, *tabIdG, *tabIdB;

    allocation_tableau(tabIdR, OCTET, nTaille);
    allocation_tableau(tabIdG, OCTET, nTaille);
    allocation_tableau(tabIdB, OCTET, nTaille);

    planR(tabIdR, ImgIn, nTaille);
    planV(tabIdG, ImgIn, nTaille);
    planB(tabIdB, ImgIn, nTaille);

    OCTET *traitementR, *traitementG, *traitementB;

    allocation_tableau(traitementR, OCTET, nTaille);
    allocation_tableau(traitementG, OCTET, nTaille);
    allocation_tableau(traitementB, OCTET, nTaille);

    OCTET *traitementRTemp, *traitementGTemp, *traitementBTemp;
   allocation_tableau(traitementRTemp, OCTET, nTaille);
   allocation_tableau(traitementGTemp, OCTET, nTaille);
   allocation_tableau(traitementBTemp, OCTET, nTaille);
      
    erosion(tabIdR, traitementRTemp, nH, nW);
    dilatation(traitementRTemp, traitementR, nH, nW);

    erosion(tabIdG, traitementGTemp, nH, nW);
    dilatation(traitementGTemp, traitementG, nH, nW);

    erosion(tabIdB, traitementBTemp, nH, nW);
    dilatation(traitementBTemp, traitementB, nH, nW);

   for (int elt=0; elt < nTaille*3; elt+=3)
    {
      ImgOut[elt] = traitementR[elt/3];
      ImgOut[elt+1] = traitementG[elt/3];
      ImgOut[elt+2] = traitementB[elt/3];
    }

   ecrire_image_ppm(cNomImgEcrite, ImgOut,  nH, nW);
   free(ImgIn); free(ImgOut);

   return 1;
}