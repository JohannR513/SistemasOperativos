#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILES 100
#define MAX_FILENAME_LENGTH 100 
#define MAX_USERS 100
#define MAX_USERNAME_LENGTH 100

typedef struct {
    char filename[ MAX_FILENAME_LENGTH ];
} File;

typedef struct {
    File files[ MAX_FILES ];
    int file_count;
} Directory;

typedef struct {
    File files[ MAX_FILES ];
    char username[ MAX_USERNAME_LENGTH ];
    Directory ufd;
    Directory data;
    Directory apps;
    int file_count;
} UserDirectory;

typedef struct {
    UserDirectory directories[ MAX_USERS ];
    int user_count;
    char username[ MAX_USERNAME_LENGTH ];
    UserDirectory ufd;
} MasterDirectory;

MasterDirectory mfd[ MAX_USERS ]; 
int user_count = 0;

int create_user( char *username ) {
    if ( user_count == MAX_USERS ) {
        printf( "Error: No se pueden crear más usuarios.\n" );
        return 0;
    }
    
    strcpy( mfd[ user_count ].username, username );
    user_count++;
    return 1;
}

int create_file( char *username, char *filename ) {
    for ( int i = 0; i < user_count; i++ ) {
        if ( strcmp( mfd[ i ].username, username ) == 0 ) {
            if ( mfd[ i ].ufd.file_count == MAX_FILES ) {
                printf( "Error: El usuario %s no puede tener más archivos.\n", username );
                return 0;
            }
            strcpy( mfd[ i ].ufd.files[ mfd[ i ].ufd.file_count ].filename, filename );
            mfd[ i ].ufd.file_count++;
            return 1;            
        }
    }
    
    printf( "Error: Usuario %s no encontrado.\n", username );
    return 0;
}

int delete_file( char *username, char *filename ) {
    for ( int i = 0; i < user_count; i++ ) {
        if ( strcmp( mfd[ i ].username, username ) == 0 ) {
            for ( int j = 0; j < mfd[ i ].ufd.file_count; j++ ) {
                if ( strcmp( mfd[ i ].ufd.files[ j ].filename, filename ) == 0 ) {
                    for ( int k = j; k < mfd[ i ].ufd.file_count - 1; k++ ) {
                        strcpy( mfd[ i ].ufd.files[ k ].filename, mfd[ i ].ufd.files[ k + 1 ].filename );
                    }
                    mfd[ i ].ufd.file_count--;
                    return 1; // indicar que el archivo se eliminó con éxito
                }
            }
            printf( "Error: Archivo no encontrado.\n" );
            return 0; // indicar que no se pudo eliminar el archivo
        }
    }
    printf( "Error: Usuario %s no encontrado.\n", username );
    return 0; // indicar que no se pudo eliminar el archivo
}

int search_file( char *username, char *filename ) {
    for ( int i = 0; i < user_count; i++ ) {
        if ( strcmp( mfd[ i ].username, username ) == 0 ) {
            for ( int j = 0; j < mfd[ i ].ufd.file_count; j++ ) {
                if ( strcmp( mfd[ i ].ufd.files[ j ].filename, filename ) == 0 ) {
                    printf( "Archivo encontrado: %s\n", filename );
                    return 1; // indicar que se encontró el archivo
                }
            }
            printf( "Archivo no encontrado: %s\n", filename );
            return 0; // indicar que no se encontró el archivo
        }
    }
    printf( "Error: Usuario %s no encontrado.\n", username );
    return 0; // indicar que no se encontró el usuario
}

void list_files( char *username ) {
    for ( int i = 0; i < user_count; i++ ) {
        if ( strcmp( mfd[ i ].username, username ) == 0 ) {
            printf( "Archivos en el directorio de usuario %s:\n", username );
            for ( int j = 0; j < mfd[ i ].ufd.file_count; j++ ) {
                printf( "%s\n", mfd[ i ].ufd.files[ j ].filename );
            }
            return;
        }
    }
    printf( "Error: Usuario %s no encontrado.\n", username );
}

int main() {
    int option;
    char filename[ MAX_FILENAME_LENGTH ];
    char username[ MAX_USERNAME_LENGTH ];
    
    while ( 1 ) {
        printf( "\nMenú:\n" );
        printf( "1. Crear usuario\n" );
        printf( "2. Crear archivo\n" ); 
        printf( "3. Eliminar archivo\n" );
        printf( "4. Buscar archivo\n" );
        printf( "5. Listar archivos\n" );
        printf( "6. Salir\n" );
        printf( "Seleccione una opción: " );
        scanf( "%d", &option );

        switch ( option ) {
            case 1:
                printf( "Ingrese el nombre de usuario: " );
                scanf( "%s", username );
                create_user( username );
                break;
            case 2: 
                printf( "Ingrese el nombre de usuario: " );
                scanf( "%s", username );
                printf( "Ingrese el nombre del archivo: " );
                scanf( "%s", filename ); 
                create_file( username, filename );
                break;
            case 3:
                printf( "Ingrese el nombre de usuario: " );
                scanf( "%s", username );
                printf( "Ingrese el nombre del archivo: " );
                scanf( "%s", filename ); 
                delete_file( username, filename );
                break;
            case 4:
                printf( "Ingrese el nombre de usuario: " );
                scanf( "%s", username );
                printf( "Ingrese el nombre del archivo: " );
                scanf( "%s", filename );
                search_file( username, filename );
                break;
            case 5:
                printf( "Ingrese el nombre de usuario: " );
                scanf( "%s", username );
                list_files( username );
                break;
            case 6:
                exit( 0 );
            default:
                printf( "Opción inválida.\n" );
                break;
        }
    }
}