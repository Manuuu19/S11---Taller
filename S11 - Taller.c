#include <stdio.h>
#include <string.h>

#define MAX_LIBROS 10

struct Libro {
    int id;
    char titulo[100];
    char autor[50];
    int anio;
    char estado[15];
};

struct Libro biblioteca[MAX_LIBROS];
int cantidadLibros = 0;

void registrarLibro();
void mostrarLibros();
void buscarLibro();
void actualizarEstado();
void eliminarLibro();
int existeID(int id);

int main() {
    int opcion;

    do {
        printf("\n--- GESTION DE BIBLIOTECA ---\n");
        printf("1. Registrar libro\n");
        printf("2. Mostrar lista de libros\n");
        printf("3. Buscar libro\n");
        printf("4. Actualizar estado (Prestado/Disponible)\n");
        printf("5. Eliminar libro\n");
        printf("6. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch(opcion) {
            case 1: registrarLibro(); break;
            case 2: mostrarLibros(); break;
            case 3: buscarLibro(); break;
            case 4: actualizarEstado(); break;
            case 5: eliminarLibro(); break;
            case 6: printf("Saliendo...\n"); break;
            default: printf("Opcion incorrecta.\n");
        }
    } while(opcion != 6);

    return 0;
}

int existeID(int id) {
    int i;
    for (i = 0; i < cantidadLibros; i++) {
        if (biblioteca[i].id == id) {
            return 1;
        }
    }
    return 0;
}

void registrarLibro() {
    if (cantidadLibros >= MAX_LIBROS) {
        printf("La biblioteca esta llena.\n");
        return;
    }

    struct Libro nuevoLibro;
    
    printf("\n--- Nuevo Libro ---\n");
    printf("ID del libro: ");
    scanf("%d", &nuevoLibro.id);

    if (existeID(nuevoLibro.id)) {
        printf("Error: Ya existe ese ID.\n");
        return;
    }

    // El espacio antes de %[^\n] sirve para limpiar el buffer y leer espacios
    printf("Titulo: ");
    scanf(" %[^\n]", nuevoLibro.titulo);

    printf("Autor: ");
    scanf(" %[^\n]", nuevoLibro.autor);

    printf("Anio: ");
    scanf("%d", &nuevoLibro.anio);
    
    strcpy(nuevoLibro.estado, "Disponible");

    biblioteca[cantidadLibros] = nuevoLibro;
    cantidadLibros++;
    printf("Libro guardado.\n");
}

void mostrarLibros() {
    int i;
    if (cantidadLibros == 0) {
        printf("\nNo hay libros.\n");
        return;
    }

    printf("\n%-5s %-30s %-20s %-6s %-15s\n", "ID", "TITULO", "AUTOR", "ANIO", "ESTADO");
    for (i = 0; i < cantidadLibros; i++) {
        printf("%-5d %-30s %-20s %-6d %-15s\n", 
            biblioteca[i].id, 
            biblioteca[i].titulo, 
            biblioteca[i].autor, 
            biblioteca[i].anio, 
            biblioteca[i].estado);
    }
}

void buscarLibro() {
    int op, i, idBusq, encontrado = 0;
    char tituloBusq[100];

    printf("\nBuscar por: 1. ID, 2. Titulo: ");
    scanf("%d", &op);

    if (op == 1) {
        printf("Ingrese ID: ");
        scanf("%d", &idBusq);
        
        for (i = 0; i < cantidadLibros; i++) {
            if (biblioteca[i].id == idBusq) {
                printf("\nEncontrado:\nID: %d\nTitulo: %s\nAutor: %s\nEstado: %s\n", 
                    biblioteca[i].id, biblioteca[i].titulo, biblioteca[i].autor, biblioteca[i].estado);
                encontrado = 1;
            }
        }
    } else if (op == 2) {
        printf("Ingrese Titulo: ");
        scanf(" %[^\n]", tituloBusq);

        for (i = 0; i < cantidadLibros; i++) {
            if (strcmp(biblioteca[i].titulo, tituloBusq) == 0) {
                printf("\nEncontrado:\nID: %d\nTitulo: %s\nAutor: %s\nEstado: %s\n", 
                    biblioteca[i].id, biblioteca[i].titulo, biblioteca[i].autor, biblioteca[i].estado);
                encontrado = 1;
            }
        }
    }

    if (encontrado == 0) {
        printf("No se encontro el libro.\n");
    }
}

void actualizarEstado() {
    int idBusq, i, encontrado = 0;
    printf("\nIngrese ID del libro: ");
    scanf("%d", &idBusq);

    for (i = 0; i < cantidadLibros; i++) {
        if (biblioteca[i].id == idBusq) {
            encontrado = 1;
            if (strcmp(biblioteca[i].estado, "Disponible") == 0) {
                strcpy(biblioteca[i].estado, "Prestado");
            } else {
                strcpy(biblioteca[i].estado, "Disponible");
            }
            printf("Nuevo estado: %s\n", biblioteca[i].estado);
            break;
        }
    }

    if (encontrado == 0) printf("Libro no existe.\n");
}

void eliminarLibro() {
    int idBusq, i, j, encontrado = 0;
    printf("\nIngrese ID a eliminar: ");
    scanf("%d", &idBusq);

    for (i = 0; i < cantidadLibros; i++) {
        if (biblioteca[i].id == idBusq) {
            encontrado = 1;
            // Movemos los libros para llenar el hueco
            for (j = i; j < cantidadLibros - 1; j++) {
                biblioteca[j] = biblioteca[j + 1];
            }
            cantidadLibros--;
            printf("Libro eliminado.\n");
            break;
        }
    }

    if (encontrado == 0) printf("Libro no existe.\n");
}