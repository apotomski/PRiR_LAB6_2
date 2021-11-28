#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "mpi.h"

double f_x(double x) {//y=x^2
	return x * x;
}

int main(int argc, char **argv) {
	int n, p, tag = 20;
	double Twynik;
	double Pwynik;
	int a,b,i;
	a = 2;
	b = 8;
	double dx;;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &p);
	MPI_Comm_size(MPI_COMM_WORLD, &n);
	MPI_Status status;
	
	if(p == n-1) {
		Twynik = 0;
		Pwynik = 0;
		dx = (double)(b - a) / n;
		i = 1;
		Twynik += f_x(a + i * dx); 
		Pwynik += f_x(a + i * dx); 
		i += 1;
		
		MPI_Send(&Twynik, 1, MPI_DOUBLE, p-1, tag, MPI_COMM_WORLD);
		MPI_Send(&Pwynik, 1, MPI_DOUBLE, p-1, tag, MPI_COMM_WORLD);
		MPI_Send(&i, 1, MPI_INT, p-1, tag, MPI_COMM_WORLD);
		MPI_Send(&dx, 1, MPI_DOUBLE, p-1, tag, MPI_COMM_WORLD);
		MPI_Send(&a, 1, MPI_INT, p-1, tag, MPI_COMM_WORLD);
		MPI_Send(&b, 1, MPI_INT, p-1, tag, MPI_COMM_WORLD);
		
	}
	if((p < n-1) && (p >= 0)) {
		MPI_Recv(&i, 1, MPI_INT, p+1, tag, MPI_COMM_WORLD, &status);
		MPI_Recv(&a, 1, MPI_INT, p+1, tag, MPI_COMM_WORLD, &status);
		MPI_Recv(&b, 1, MPI_INT, p+1, tag, MPI_COMM_WORLD, &status);
		MPI_Recv(&dx, 1, MPI_DOUBLE, p+1, tag, MPI_COMM_WORLD, &status);
		MPI_Recv(&Twynik, 1, MPI_DOUBLE, p+1, tag, MPI_COMM_WORLD, &status);
		MPI_Recv(&Pwynik, 1, MPI_DOUBLE, p+1, tag, MPI_COMM_WORLD, &status);
		
		if(p == 0) {
			Twynik += f_x(a) / 2;
			Twynik += f_x(b) / 2;
			Twynik *= dx;
			printf("Metoda trapezow wynik = %lf", Twynik);
			
			Pwynik *= dx;
			printf("Metoda prostokatow wynik = %lf", Pwynik);
		}
		else {
			Twynik += f_x(a + i * dx); 
			Pwynik += f_x(a + i * dx); 
			i += 1;
			
			MPI_Send(&Twynik, 1, MPI_DOUBLE, p-1, tag, MPI_COMM_WORLD);
			MPI_Send(&Pwynik, 1, MPI_DOUBLE, p-1, tag, MPI_COMM_WORLD);
			MPI_Send(&i, 1, MPI_INT, p-1, tag, MPI_COMM_WORLD);
			MPI_Send(&dx, 1, MPI_DOUBLE, p-1, tag, MPI_COMM_WORLD);
			MPI_Send(&a, 1, MPI_INT, p-1, tag, MPI_COMM_WORLD);
			MPI_Send(&b, 1, MPI_INT, p-1, tag, MPI_COMM_WORLD);
		}
	}
	
	
	
	MPI_Finalize();
	return 0;
}
