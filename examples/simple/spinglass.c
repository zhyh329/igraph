/* -*- mode: C -*-  */
/* 
   IGraph library.
   Copyright (C) 2006  Gabor Csardi <csardi@rmki.kfki.hu>
   MTA RMKI, Konkoly-Thege Miklos st. 29-33, Budapest 1121, Hungary
   
   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc.,  51 Franklin Street, Fifth Floor, Boston, MA 
   02110-1301 USA

*/

#include <igraph.h>

int main() {
  igraph_t g;
  igraph_real_t  modularity, temperature;
  igraph_vector_t membership, csize;
  long int i;
  
  igraph_small(&g, 5, IGRAPH_UNDIRECTED, 
	       0,1,0,2,0,3,0,4, 1,2,1,3,1,4, 2,3,2,4, 3,4,
	       5,6,5,7,5,8,5,9, 6,7,6,8,6,9, 7,8,7,9, 8,9, 0,5, -1);
  igraph_vector_init(&membership, 0);
  igraph_vector_init(&csize, 0);
  igraph_community_spinglass(&g, 
			     0, /* no weights */
			     &modularity,
			     &temperature,
			     &membership,
			     &csize,
			     2,	   /* no of spins */
			     0,    /* parallel update */
			     1.0,  /* start temperature */
			     0.01, /* stop temperature */
			     0.99, /* cooling factor */
			     IGRAPH_SPINCOMM_UPDATE_CONFIG,
			     1.0); /* gamma */

/*   printf("Modularity:  %f\n", modularity); */
/*   printf("Temperature: %f\n", temperature); */
/*   printf("Cluster sizes: "); */
/*   for (i=0; i<igraph_vector_size(&csize); i++) { */
/*     printf("%li ", (long int)VECTOR(csize)[i]); */
/*   } */
/*   printf("\n"); */
/*   printf("Membership: "); */
/*   for (i=0; i<igraph_vector_size(&membership); i++) { */
/*     printf("%li ", (long int)VECTOR(membership)[i]); */
/*   } */
/*   printf("\n"); */

  if (igraph_vector_size(&csize) != 2) {
    return 1;
  }
  if (VECTOR(csize)[0] != 5) {
    return 2;
  }

  igraph_destroy(&g);
  igraph_vector_destroy(&membership);
  igraph_vector_destroy(&csize);
  
  return 0;
}
