#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_ESTUDIANTES 100
#define MAX_MATERIAS 20
#define MAX_NOMBRE 50
#define MAX_APELLIDO 50
#define MAX_DNI 10
#define MAX_EMAIL 50
#define MAX_DIRECCION 100
#define MAX_TELEFONO 15

typedef struct {
    char nombre[MAX_NOMBRE];
    char apellido[MAX_APELLIDO];
    char dni[MAX_DNI];
    char email[MAX_EMAIL];
    char direccion[MAX_DIRECCION];
    char telefono[MAX_TELEFONO];
    char contactoEmergencia[MAX_TELEFONO];
    int legajo;
    float notas[MAX_MATERIAS];
    int inasistencias[MAX_MATERIAS];
    int materiasCursadas[MAX_MATERIAS];
} Estudiante;

Estudiante estudiantes[MAX_ESTUDIANTES];
int contadorEstudiantes = 0;

// Prototipos
int validarEmail(const char *email);
int validarDNI(const char *dni);
void mostrarMenu();
void mostrarMaterias(int anio);
void ingresarNotas(int index, int anio);
void mostrarEstudiante(int index);
void cargarEstudiante();
void editarEstudiante();
void guardarEnArchivo();

int validarEmail(const char *email) {
    const char *arroba = strchr(email, '@');
    const char *punto = strrchr(email, '.');
    return (arroba && punto && punto > arroba && arroba != email && *(punto + 1) != '\0');
}

int validarDNI(const char *dni) {
    if (strlen(dni) != 8) return 0;
    for (int i = 0; dni[i]; i++) {
        if (!isdigit(dni[i])) return 0;
    }
    return 1;
}

void mostrarMenu() {
    printf("\n========================================\n");
    printf("         MENU DE ADMINISTRACION         \n");
    printf("========================================\n");
    printf("1. Cargar Estudiante\n");
    printf("2. Mostrar Datos\n");
    printf("3. Editar Estudiante\n");
    printf("4. Guardar en archivo\n");
    printf("5. Salir\n");
    printf("========================================\n");
}

void mostrarMaterias(int anio) {
    if (anio == 1) {
        printf("\nMaterias de Primer Anio:\n");
        printf("1. Programacion I\n2. Arquitectura y Sistemas Operativos\n3. Matematica\n4. Organizacion Empresarial\n5. Programacion II\n6. Probabilidad y Estadistica\n7. Base de Datos I\n8. Ingles I\n");
    } else {
        printf("\nMaterias de Segundo Anio:\n");
        printf("1. Programacion III\n2. Base de Datos II\n3. Metodologia de Sistemas I\n4. Ingles II\n5. Programacion IV\n6. Metodologia de Sistemas II\n7. Introduccion al Analisis de Datos\n8. Legislacion\n9. Gestion de Desarrollo de Software\n");
    }
}

void ingresarNotas(int index, int anio) {
    int materia;
    char continuar;
    do {
        mostrarMaterias(anio);
        printf("Seleccione la materia (numero): ");
        scanf("%d", &materia);
        materia--;

        int offset = (anio == 2) ? 8 : 0;
        if (materia >= 0 && materia < (anio == 1 ? 8 : 9)) {
            float n1, n2, n3;
            printf("Ingrese Nota 1: "); scanf("%f", &n1);
            printf("Ingrese Nota 2: "); scanf("%f", &n2);
            printf("Ingrese Nota 3: "); scanf("%f", &n3);
            estudiantes[index].notas[materia + offset] = (n1 + n2 + n3) / 3.0;
            printf("Ingrese Inasistencias: ");
            scanf("%d", &estudiantes[index].inasistencias[materia + offset]);
            estudiantes[index].materiasCursadas[materia + offset] = 1;
        }
        printf("Desea cargar otra materia? (s/n): ");
        scanf(" %c", &continuar);
    } while (continuar == 's' || continuar == 'S');
}

void mostrarEstudiante(int index) {
    printf("\n--- Datos del Estudiante ---\n");
    printf("Legajo: %d\nDNI: %s\nNombre: %s\nApellido: %s\nEmail: %s\nDireccion: %s\nTelefono: %s\nEmergencia: %s\n",
           estudiantes[index].legajo, estudiantes[index].dni, estudiantes[index].nombre,
           estudiantes[index].apellido, estudiantes[index].email, estudiantes[index].direccion,
           estudiantes[index].telefono, estudiantes[index].contactoEmergencia);
    for (int i = 0; i < MAX_MATERIAS; i++) {
        if (estudiantes[index].materiasCursadas[i]) {
            printf("Materia %d: Nota = %.2f | Inasistencias = %d\n", i + 1, estudiantes[index].notas[i], estudiantes[index].inasistencias[i]);
        }
    }
}

void cargarEstudiante() {
    Estudiante nuevo;
    nuevo.legajo = contadorEstudiantes + 1;

    do {
        printf("Ingrese DNI (8 dígitos numéricos): ");
        scanf("%s", nuevo.dni);
        if (!validarDNI(nuevo.dni)) {
            printf("DNI inválido. Intente nuevamente.\n");
        }
    } while (!validarDNI(nuevo.dni));

    printf("Ingrese Nombre: "); scanf("%s", nuevo.nombre);
    printf("Ingrese Apellido: "); scanf("%s", nuevo.apellido);

    do {
        printf("Ingrese Email: ");
        scanf("%s", nuevo.email);
        if (!validarEmail(nuevo.email)) {
            printf("Email invalido. Intente nuevamente.\n");
        }
    } while (!validarEmail(nuevo.email));

    printf("Ingrese Direccion: "); scanf("%s", nuevo.direccion);

    int valido = 0;
    while (!valido) {
        printf("Ingrese Telefono personal (10 digitos): ");
        scanf("%s", nuevo.telefono);

        if (strlen(nuevo.telefono) != 10) {
            printf("\nTelefono invalido. Debe tener exactamente 10 digitos.\n");
            continue;
        }

        valido = 1;
        for (int i = 0; i < 10; i++) {
            if (!isdigit(nuevo.telefono[i])) {
                printf("\nTelefono invalido. Solo se permiten numeros.\n");
                valido = 0;
                break;
            }
        }
    }

    valido = 0;
    while (!valido) {
        printf("Ingrese Telefono de emergencia (10 digitos): ");
        scanf("%s", nuevo.contactoEmergencia);

        if (strlen(nuevo.contactoEmergencia) != 10) {
            printf("\nTelefono invalido. Debe tener exactamente 10 digitos.\n");
            continue;
        }

        valido = 1;
        for (int i = 0; i < 10; i++) {
            if (!isdigit(nuevo.contactoEmergencia[i])) {
                printf("\nTelefono invalido. Solo se permiten numeros.\n");
                valido = 0;
                break;
            }
        }
    }

    for (int i = 0; i < MAX_MATERIAS; i++) {
        nuevo.notas[i] = 0;
        nuevo.inasistencias[i] = 0;
        nuevo.materiasCursadas[i] = 0;
    }

    estudiantes[contadorEstudiantes] = nuevo;

    char continuar = 's';
    while (continuar == 's' || continuar == 'S') {
        int anio;
        printf("Cargar materias de que anio? (1 o 2): ");
        scanf("%d", &anio);
        ingresarNotas(contadorEstudiantes, anio);
        printf("Desea cargar materias de otro anio? (s/n): ");
        scanf(" %c", &continuar);
    }

    mostrarEstudiante(contadorEstudiantes);
    contadorEstudiantes++;
}

void editarEstudiante() {
    char dni[MAX_DNI];
    printf("Ingrese el DNI del estudiante a editar: ");
    scanf("%s", dni);
    for (int i = 0; i < contadorEstudiantes; i++) {
        if (strcmp(estudiantes[i].dni, dni) == 0) {
            printf("Estudiante encontrado:\n");
            mostrarEstudiante(i);
            printf("Nuevo Email: "); scanf("%s", estudiantes[i].email);
            printf("Nuevo Telefono: "); scanf("%s", estudiantes[i].telefono);
            printf("Nuevo Telefono emergencia: "); scanf("%s", estudiantes[i].contactoEmergencia);
            int anio;
            printf("Editar materias de que anio (1 o 2): ");
            scanf("%d", &anio);
            ingresarNotas(i, anio);
            return;
        }
    }
    printf("Estudiante no encontrado.\n");
}

void guardarEnArchivo() {
    FILE *file = fopen("informe_estudiantes.txt", "w");
    if (!file) {
        printf("Error al abrir el archivo.\n");
        return;
    }
    for (int i = 0; i < contadorEstudiantes; i++) {
        fprintf(file, "Legajo: %d\nDNI: %s\nNombre: %s %s\nEmail: %s\nTelefono: %s\nEmergencia: %s\n",
                estudiantes[i].legajo, estudiantes[i].dni, estudiantes[i].nombre,
                estudiantes[i].apellido, estudiantes[i].email, estudiantes[i].telefono,
                estudiantes[i].contactoEmergencia);
        for (int j = 0; j < MAX_MATERIAS; j++) {
            if (estudiantes[i].materiasCursadas[j]) {
                fprintf(file, "Materia %d: Nota %.2f - Inasistencias %d\n",
                        j + 1, estudiantes[i].notas[j], estudiantes[i].inasistencias[j]);
            }
        }
        fprintf(file, "\n");
    }
    fclose(file);
    printf("Informe guardado en 'informe_estudiantes.txt'.\n");
}

int main() {
    int opcion;
    do {
        mostrarMenu();
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        switch (opcion) {
        case 1: cargarEstudiante(); break;
        case 2:
            for (int i = 0; i < contadorEstudiantes; i++) {
                mostrarEstudiante(i);
            }
            break;
        case 3: editarEstudiante(); break;
        case 4: guardarEnArchivo(); break;
        case 5: printf("Saliendo...\n"); break;
        default: printf("Opcion no valida.\n");
        }
    } while (opcion != 5);
    return 0;
}
