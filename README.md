# PRiR_LAB6_2
Projekt 2 z laboratoriów numer 6 z PRiR. Program oblicza przybliżenie całki y=x^2 w przedziale <a,b> gdzie n to liczba procesów, używając 2 metod(trapezów i prostokątów). Program jest napisany w języku c z wykorzystaniem MPI aby można było wykorzystać wątki. Dane są przesyłane od procesu n-1 aż do procesu 0.

Opis kodu:

Import bibliotek

    #include<stdio.h>
    #include<stdlib.h>
    #include<math.h>
    #include "mpi.h"
    
Funkcja zwracająca wartość funkcji x^2
    
    double f_x(double x) {//y=x^2
      return x * x;
    }
    
Funkcja main

Stowrzenie i inicjalizacja zmiennych

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
      
if sprawdzający czy proces jest = n-1. Jeśli tak to ustawia wartości dla zmiennych oraz rozpoczęcie obliczeń dla metod trapezów i prostokątów. Na koniec if'a wysyłane są wszystkie potrzebne dane do procesu o 1 mniejszego.
      
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
      
if sprawdzający czy proces jest mniejszy od n-1 i większy lub równy 0. Jeśli tak to odbiera zmienne z procesu o 1 większego. Następnie sprawdza czy proces jest = 0 jeśli tak to dokonuje ostatnich obliczeń zgdnie ze wzorami i wyświetla wyniki obliczeń. W przeciwnym wypadku  dokonuje obliczeń zgodnie z wozrmi metod i wysyła wartości do procesu o 1 mniejszego.
      
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
