#include <stdio.h>
#include "mpi.h"
#include <math.h>
int main(int argc, char **argv){
	int p;
	int n;
	int tag=50;
	double sum, term, pi;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &p);
	MPI_Comm_size(MPI_COMM_WORLD, &n);
	MPI_Status status;
	if(p==0){ 
		term = pow(-1,p)/(2*p+1);
		sum += term;
		MPI_Send(&sum, 1, MPI_DOUBLE ,p+1 ,tag, MPI_COMM_WORLD);
		
	} 
	if((p>0)&&(p<n-1)){ 
		MPI_Recv(&sum, 1, MPI_DOUBLE, p-1, tag, MPI_COMM_WORLD, &status);

		term = pow(-1,p)/(2*p+1);
		sum += term;

		MPI_Send(&sum, 1, MPI_DOUBLE,p+1,tag,MPI_COMM_WORLD);
	
	}
	if(p==n-1)
	{	
		MPI_Recv(&sum, 1, MPI_DOUBLE, p-1, tag, MPI_COMM_WORLD, &status);
		pi = 4 * sum;
		printf("\nPI = %.6lf\n n wynosi: %d\n", pi,n);	
	}

	MPI_Finalize();
	return 0;
}