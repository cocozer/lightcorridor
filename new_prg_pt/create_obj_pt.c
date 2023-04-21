#include "create_obj_pt.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

unsigned int vertex_number;
float* vertex_coord;
float* normal_coord;

void createCoordinates(unsigned int* sz_pt) {
    // Vous devez fixer :
    // - le nombre de sommets (vertex_number)
    // - le tableau des coordonnees des sommets (vertex_coord)
    // - le tableau des coordonnees des normales (normal_coord)
    // Vous pouvez changer :
    // - la taille des points GL affichés à l'écran (sz_pt)

    *sz_pt = 5; // A CHANGER EVENTUELLEMENT

    int vertex_par_arrete = 18;
	float echelle = 0.05;

    vertex_number = 10 * vertex_par_arrete * vertex_par_arrete; // A CHANGER
    
    vertex_coord = (float*) calloc(sizeof(float),3*vertex_number);
    normal_coord = (float*) calloc(sizeof(float),3*vertex_number);

    // CONSTRUIRE LES TABLEAUX
	int count = 0;
	//int county = 0;
	//int countz = 0;
    for(int x=0; x<vertex_par_arrete; x++) {
		for(int y=0; y<vertex_par_arrete; y++) {
			for(int z=0; z<vertex_par_arrete; z++) {
				if((y==0 || y==vertex_par_arrete-1)||(z==0 || z==vertex_par_arrete-1)||(x==0 || x==vertex_par_arrete-1)){
					vertex_coord[count++] = x*echelle;
					vertex_coord[count++] = y*echelle;
					vertex_coord[count++] = z*echelle;
					}
				
				if(y==0){
					normal_coord[count-3] = 0;
					normal_coord[count-2] = 1;
					normal_coord[count-1] = 0;
				}
				if(y==vertex_par_arrete-1){
					normal_coord[count-3] = 0;
					normal_coord[count-2] = -1;
					normal_coord[count-1] = 0;
				}
				
				if(x==0){
					normal_coord[count-3] = 1;
					normal_coord[count-2] = 0;
					normal_coord[count-1] = 0;
				}
				if(x==vertex_par_arrete-1){
					normal_coord[count-3] = -1;
					normal_coord[count-2] = 0;
					normal_coord[count-1] = 0;
				}

				if(z==0){
					normal_coord[count-3] = 0;
					normal_coord[count-2] = 0;
					normal_coord[count-1] = 1;
				}
				if(z==vertex_par_arrete-1){
					normal_coord[count-3] = 0;
					normal_coord[count-2] = 0;
					normal_coord[count-1] = -1;
				}
			}
		}
	}
}
