#include <stdio.h>
#include <stdbool.h>
/*Johann Ruano */
void mft( int memorySize, int blockSize, int numProcesses, int processSizes[] ) {
    int memoryAllocated = 0; // variable que almacena la cantidad 6de memoria asignada
    int internalFragmentation = 0; // variable que almacena la fragmentación interna
    int externalFragmentation = 0; // variable que almacena la fragmentación externa
    bool allocated[ numProcesses ]; // array booleano que indica si un proceso ha sido asignado a memoria
    for ( int i = 0; i < numProcesses; i++ ) {
        allocated[ i ] = false;
    }
    for ( int i = 0; i < numProcesses; i++ ) {
        if ( processSizes[ i ] <= blockSize && memoryAllocated + blockSize <= memorySize ) {
            memoryAllocated += blockSize; // se asigna memoria al proceso
            internalFragmentation += blockSize - processSizes[ i ]; // se calcula la fragmentación interna
            printf( "P%d -> %d is put in %d, %d fragmentation.\n", i, processSizes[ i ], blockSize, blockSize - processSizes[ i ] );
            allocated[ i ] = true;
        } else {
            printf( "P%d -> %d Not allocated.\n", i, processSizes[ i ] );
        }
    }
    externalFragmentation = memorySize - memoryAllocated; // se calcula la fragmentación externa
    printf( "Memory allocated: %d\n", memoryAllocated );
    printf( "Internal fragmentation: %d\n", internalFragmentation );
    printf( "External fragmentatiom: %d\n", externalFragmentation );
}

void mvt( int memorySize, int numProcesses, int processSizes[] ) {
    int memoryAllocated = 0; // variable que almacena la cantidad de memoria asignada
    int internalFragmentation = -1; // se inicializa en -1 ya que no hay fragmentación interna en este método
    int externalFragmentation = 0; // variable que almacena la fragmentación externa
    bool allocated[ numProcesses ]; // array booleano que indica si un proceso ha sido asignado a memoria
    for ( int i = 0; i < numProcesses; i++ ) {
        allocated[ i ] = false;
    }
    for ( int i = 0; i < numProcesses; i++ ) {
        if ( processSizes[ i ] <= memorySize - memoryAllocated ) {
            memoryAllocated += processSizes[ i ]; // se asigna memoria al proceso
            printf( "P%d -> %d is put in Mem.\n", i, processSizes[ i ] );
            allocated[ i ] = true;
        } else {
            printf( "P%d -> %d Not allocated.\n", i, processSizes[ i ] );
        }
    }
    externalFragmentation = memorySize - memoryAllocated; // se calcula la fragmentación externa
    printf( "Memory allocated: %d\n", memoryAllocated );
    printf( "Internal fragmentation: %d\n", internalFragmentation );
    printf( "External fragmentatiom: %d\n", externalFragmentation );
}

int main() {
    int method;
    printf( "Enter method (1 = MFT, 2 = MVT): " );
    scanf(  "%d", &method);
    
    int memorySize;
    printf( "Total memory: " );
    scanf( "%d", &memorySize );
    
    int blockSize = -1;
    if ( method == 1 ) {
        printf( "Enter block size: " );
        scanf( "%d", &blockSize );
    }
    
    int numProcesses;
    printf( "Enter number of processes: " );
    scanf( "%d", &numProcesses );
    
    int processSizes[ numProcesses ];
    for ( int i = 0; i < numProcesses; i++ ) {
        printf( "Enter size of process %d: ", i );
        scanf( "%d", &processSizes[ i ] );
    }
    
    if ( method == 1 ) {
        mft( memorySize, blockSize, numProcesses, processSizes );
    } else if ( method == 2 ) {
        mvt( memorySize, numProcesses, processSizes );
    }
    
    return 0;
}