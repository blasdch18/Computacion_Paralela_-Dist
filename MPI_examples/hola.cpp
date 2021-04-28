#include<stdio.h>
#include<mpi.h>

int main(int argc, char** argv)
{
    int size, rank;
    /*      Inicializa el proceso en MPI, bloquea la ejecución 
            hasta que todos los procesos hayan sido inicializados.     */
    MPI_Init(&argc, &argv);//    MPI_Init(<pointer_to_int>, <pointer_to_char*>)
    /*      Obtiene el número de procesos ejecutados en el grupo MPI_COMM_WORLD, 
            éste es el grupo por default. Se pueden crear subgrupos de procesos.     */
    MPI_Comm_size(MPI_COMM_WORLD, &size); //     MPI_Comm_size(MPI_COMM_WORLD, <pointer_to_int>)
    /*      Obtiene el número de rango del proceso actual, los rangos van de 0 a size−1 .     */
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); //    MPI_Comm_rank(MPI_COMM_WORLD, <pointer_to_int>)
    printf("Hola mundo (size = %i, rank = %i)\n", size, rank);
    //  Termina la conección MPI, bloquea la ejecución hasta que todos los procesos terminen.
    MPI_Finalize();  
    
    return 0;
}