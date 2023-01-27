#include <stdio.h>
#include "dilatation.h"
#include "erosion.h"

void ouverture_2_image(OCTET *nomImageEntree, OCTET *nomImageSortie, int tailleH, int tailleW) {

   OCTET *ImgTemp;
   allocation_tableau(ImgTemp, OCTET, tailleH*tailleW);

   for (int k = 0; k < 3; k++){ 
        ecrire_image_erosion(nomImageEntree, ImgTemp, tailleH, tailleW);
    } 
    for (int k = 0; k < 3; k++){ 
        ecrire_image_dilatation(ImgTemp, nomImageSortie, tailleH, tailleW);
    }

} 