#include <stdio.h>
#include "mpi.h"
#include <math.h>
double wzor(double x)
{
	return x*x;
}
int main(int argc, char **argv){
	int p;
	int n;
	double a=1;
	double b=5;
	double wynik=0;
	int tag=50;
	double temp1, temp2, temp3;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &p);
	MPI_Comm_size(MPI_COMM_WORLD, &n);
	MPI_Status status;
	temp3=n;
	double h=((b-a)/ temp3);
	temp1=p;
	temp2=n-1;
	if(p==0){ 
		MPI_Recv(&wynik, 1, MPI_DOUBLE, p+1, tag, MPI_COMM_WORLD, &status);
		
		wynik += wzor(a + ((temp1 / temp2) * (b - a))) + wzor(a + (((temp1 + 1) / temp2) * (b - a)));
		wynik = (wynik * h) / 2;
		printf("wynik to: %f\n",wynik);
		
	} 
	if((p>0)&&(p<n-1)){ 
		MPI_Recv(&wynik, 1, MPI_DOUBLE, p+1, tag, MPI_COMM_WORLD, &status);

		wynik += wzor(a + ((temp1 / temp2) * (b - a))) + wzor(a + (((temp1 + 1) / temp2) * (b - a)));
		MPI_Send(&wynik, 1, MPI_DOUBLE,p-1,tag,MPI_COMM_WORLD);
	}
	if(p==n-1)
	{	
		wynik += wzor(a + ((temp1 / temp2) * (b - a))) + wzor(a + (((temp1 + 1) / temp2) * (b - a)));
		MPI_Send(&wynik, 1, MPI_DOUBLE,p-1,tag,MPI_COMM_WORLD);	
	}

	MPI_Finalize();
	return 0;
}