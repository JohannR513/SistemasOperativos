#include <stdio.h>
#include <stdlib.h>
/*Johann Ruano*/
enum Method { FirstFit = 1, BestFit = 2, WorstFit = 3 }; // Define un enumerador para los diferentes métodos de asignación de memoria

typedef struct {
    int size;
    int allocated;
} MemoryPartition; // Define una estructura para representar una partición de memoria

void allocate_memory( int method, MemoryPartition *partitions, int n_partitions, int *processes, int n_processes ) {
    for ( int i = 0; i < n_processes; i++ ) { // Para cada proceso que necesita asignación de memoria
        int selected_partition = -1;

        for ( int j = 0; j < n_partitions; j++ ) { // Para cada partición de memoria disponible
            int available_size = partitions[ j ].size - partitions[ j ].allocated; // Calcula el tamaño disponible en la partición

            if ( available_size >= processes[ i ] ) { // Si el tamaño disponible es suficiente para el proceso
                if ( method == FirstFit ) { // Si se utiliza el método First Fit
                    selected_partition = j; // Selecciona la primera partición disponible
                    break;
                } else if ( method == BestFit ) { // Si se utiliza el método Best Fit
                    if ( selected_partition == -1 || available_size < ( partitions[ selected_partition ].size - partitions[ selected_partition ].allocated ) ) { // Si esta partición es mejor que la anteriormente seleccionada
                        selected_partition = j; // Selecciona esta partición
                    }
                } else if ( method == WorstFit ) { // Si se utiliza el método Worst Fit
                    if ( selected_partition == -1 || available_size > ( partitions[ selected_partition ].size - partitions[ selected_partition ].allocated ) ) { // Si esta partición es peor que la anteriormente seleccionada
                        selected_partition = j; // Selecciona esta partición
                    }
                }
            }
        }

        if ( selected_partition != -1 ) { // Si se encontró una partición adecuada para el proceso
            partitions[ selected_partition ].allocated += processes[ i ]; // Asigna la memoria del proceso a la partición seleccionada
            printf( "P%d -> %d is put in %d, %d partition.\n", i, processes[ i ], partitions[ selected_partition ].size, selected_partition + 1 ); // Muestra un mensaje de que el proceso ha sido asignado a una partición específica
        } else { // Si no se encontró una partición adecuada para el proceso
            printf( "P%d -> %d can't be assigned.\n", i, processes[ i ] ); // Muestra un mensaje de que el proceso no pudo ser asignado a ninguna partición disponible
        }
    }
}

int main() {
    int method;
    printf( "Method (1=FirstFit, 2=BestFit, 3=WorstFit): " );
    scanf( "%d", &method );

    int n_partitions;
    printf( "Number of memory partitions in order: " );
    scanf( "%d", &n_partitions );

    // Se reserva espacio en memoria para las particiones y se inicializan sus valores
    MemoryPartition *partitions = malloc( n_partitions * sizeof( MemoryPartition ) );
    for ( int i = 0; i < n_partitions; i++ ) {
        printf( "Free memory size for partition %d: ", i + 1 );
        scanf( "%d", &partitions[i].size );
        partitions[ i ].allocated = 0;
    }

    int n_processes;
    printf( "Number of processes in order of arrival: " );
    scanf( "%d", &n_processes );

    // Se reserva espacio en memoria para los procesos y se solicita su tamaño al usuario
    int *processes = malloc( n_processes * sizeof( int ) );
    for (int i = 0; i < n_processes; i++ ) {
        printf( "Size request for process %d: ", i );
        scanf( "%d", &processes[ i ] );
    }

    // Se llama a la función que asigna la memoria a los procesos
    allocate_memory( method, partitions, n_partitions, processes, n_processes );

    // Se libera el espacio de memoria reservado para las particiones y los procesos
    free( partitions );
    free( processes );

    return 0;
}
