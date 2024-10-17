#include <stdio.h>
#include <stdlib.h>


struct ProyectoDeLey {
    int id;                     // Identificador único del proyecto
    char titulo[256];          // Título del proyecto de ley
    char descripcion[1024];    // Descripción del proyecto
    char autor[256];           // Autor del proyecto (Presidente, parlamentarios, ciudadanía)
    int estado;                // Estado del proyecto (0: Iniciado, 1: En Comisión, 2: Aprobado en Cámara de Origen, ...)
};



struct Parlamentario {
    int id;                     // Identificador único del parlamentario
    char nombre[256];           // Nombre del parlamentario
    char partido[256];          // Partido político al que pertenece
    char camara[256];           // Cámara a la que pertenece (Diputados o Senado)
};




struct Comision {
    int id;                     // Identificador único de la comisión
    char nombre[256];           // Nombre de la comisión
    struct Parlamentario *miembros;     // Lista de miembros de la comisión (lista enlazada)
    int numMiembros;            // Número de miembros
};




struct Camara{
    int id;                     // Identificador único de la cámara
    char nombre[256];           // Nombre de la cámara (Cámara de Diputados o Senado)
    struct ProyectoDeLey *proyectos;   // Proyectos en la cámara (lista doblemente enlazada)
    int numProyectos;           // Número de proyectos en la cámara
};




struct ComisionMixta{
    int id;                     // Identificador único de la comisión mixta
    struct Comision *comisionDiputados; // Comisión de diputados
    struct Comision *comisionSenadores;  // Comisión de senadores
    struct ProyectoDeLey *proyecto;     // Proyecto de ley en discusión
};




struct Promulgacion{
    int id;                     // Identificador único del proceso de promulgación
    struct ProyectoDeLey *proyecto;    // Proyecto de ley a promulgar
    int estado;                // Estado del proceso (0: Pendiente, 1: Promulgado, 2: Veto)
    char observaciones[1024];    // Observaciones del Presidente en caso de veto
};



struct NodoProyecto {
    struct ProyectoDeLey proyecto;
    struct NodoProyecto *izquierdo; // Subárbol izquierdo
    struct NodoProyecto *derecho;    // Subárbol derecho
};

struct ArbolProyecto{
    struct NodoProyecto *raiz;               // Raíz del árbol
};






int main(void) {
    printf("Hello, World!\n");
    return 0;
}
