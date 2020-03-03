#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

//Simulate one particle moving n steps in random directions
//Use a random number generator to decide which way to go at every step
//When the particle stops at a final location, use the memory pointed to by grid to 
//record the number of particles that stop at this final location
//Feel free to declare, implement and use other functions when needed

void one_particle(int *grid, int n)
{
	int r;
	int x = n;
	int y = n;
	int z = n;

	/*
	for(int x=0; x<2*n+1;x++){
		for(int y=0;y<2*n+1;y++){
			for(int z=0; z<2*n+1; z++){
				printf(" %d ", *(grid + x*(2*n+1)*(2*n+1) + y*(2*n+1) + z) );
			}printf("\n");
		}printf("\n");
	}*/

	for(int i = 0; i<n; i++){
//		*(grid + x*(2*n+1)*(2*n+1) + y*(2*n+1) + z) = 1;
		r = rand() % 6;
		if(r == 0){x--;}	
		if(r == 1){x++;}	
		if(r == 2){y--;}	
		if(r == 3){y++;}	
		if(r == 4){z--;}	
		if(r == 5){z++;}	
	}
	
	*(grid + x*(2*n+1)*(2*n+1) + y*(2*n+1) + z)+= 1;

}

//This function returns the fraction of particles that lie within the distance
//r*n from the origin (including particles exactly r*n away)
//The distance used here is Euclidean distance

{
	int inrn = 0;
	int total = 0;
	for(int x=0; x<2*n+1;x++){
		for(int y=0;y<2*n+1;y++){
			for(int z=0; z<2*n+1; z++){
				total += *(grid + x*(2*n+1)*(2*n+1) + y*(2*n+1) + z); 
					if(((x-n)*(x-n))+((y-n)*(y-n))+((z-n)*(z-n))<= (r*n)*(r*n))
						inrn += *(grid + x*(2*n+1)*(2*n+1) + y*(2*n+1) + z);
			}
		}
	}
//	printf("inrn = %d ", inrn);
//	printf("total = %d ", total);

	return (double)inrn / total;
}

//use this function to print results
void print_result(int *grid, int n)
{
    printf("radius density\n");
    for(int k = 1; k <= 20; k++)
    {
        printf("%.2lf   %lf\n", 0.05*k, density(grid, n, 0.05*k));
    }
}

void diffusion(int n, int m)
{
	//fill in a few line of code below

	int * grid = calloc((2*n+1)*(2*n+1)*(2*n+1), sizeof(int));
	
	for(int i = 1; i<=m; i++) {one_particle(grid, n);}

	print_result(grid, n);
	//fill in some code below
	
	free(grid);
}

int main(int argc, char *argv[])
{
	
	if(argc != 3)
	{
		printf("Usage: %s n m\n", argv[0]);
		return 0; 
	}
	int n = atoi(argv[1]);
	int m = atoi(argv[2]);

	assert(n >= 1 && n <=50);
	assert(m >= 1 && m <= 1000000);
	srand(12345);
	diffusion(n, m);
	return 0;
}
