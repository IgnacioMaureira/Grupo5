#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*MODIFICAR EN EL INFORME LAS FUNCIONES DE CLS*/

struct presidente {
    struct persona *persona;
    int anioMandato;
    int voto;
};

/*ARBOL BINARIO DE BUSQUEDA*/
struct nodoProyecto {
    struct proyecto *datos;
    struct nodoProyecto *izq, *der;
};

struct proyecto {
    int id;
    char *tipo;
    char *tema;
    struct persona *personaAcargo;
    int urgencia; /* 1 = Urgencia Simple, 2 = Suma Urgencia, 3 = Discusión Inmediata*/
    int estado; /* -1 = pendiente, 0 = en tramite, 1 = aprobada, 2 = rechazada *//*Agregue el estado pendiente*/
};

struct Grafo {
    int **matriz; // Puntero doble para la matriz de adyacencia
    int numVertices; // Número actual de proyectos (nodos) en el grafo
};


struct congreso {
    struct persona **senadores;
    struct persona **diputados;
    int plibreDiputados;
    int MaxDiputados;
    int plibreSenadores;
    int MaxSenadores;
};


/*lista doble*/
struct nodoCiudadano {
    struct persona *datos;
    struct nodoCiudadano *ant, *sig;
};


/* nodoBoletin LISTA SIMPLE */
struct nodoBoletin {
    struct boletin *head;
    struct nodoBoletin *sig;
};

struct boletin {
    struct proyecto *propuesta;
    int numeroBoletin;
    char *fechaVigencia;
};

struct persona {
    char rut[20];
    char nombre[50];
    int edad;
    int cargo; // 0 = ciudadano, 1 = diputado, 2 = senador, 3 = presidente, 4 = ministro
    char especialidad[20];
    int voto;
};

struct ProcesoLegislativo {
    struct presidente *presidente;
    struct congreso *congreso;
    struct nodoProyecto *propuesta;
    struct nodoCiudadano *ciudadanos;
    struct nodoBoletin *boletinEstado;
    struct persona *tribunalConstitucional[10];
    struct Grafo *grafoProyectos; // Grafo basado en urgencias
};



/*PROTOTIPADO*/
/*   FUNCIONES ADICIONALES   */
void cls();

void limpiarBuffer();

void promulgacionOVetoPresidencial(struct presidente *presidente, struct nodoProyecto *raizPropuestas, struct congreso *congreso);

/*   FUNCIONES PARA CIUDADANOS   */
struct persona* crearCiudadano();

struct nodoCiudadano *agregarCiudadano(struct nodoCiudadano *ciudadanos, struct persona *ciudadano);

struct persona *crearPersona(char *rut, char *nombre, int edad, char *especialidad, int voto);

struct nodoCiudadano *crearNodoCiudadano(struct persona *ciudadano);

struct persona *buscarCiudadanoPorRUT(struct nodoCiudadano *ciudadanos, char *rut);

void mostrarCiudadanos(struct nodoCiudadano *ciudadanos);

void eliminarCiudadano(struct nodoCiudadano **ciudadanos, char rut[20]);

void mostrarPromedioEdadCiudadanos(struct nodoCiudadano *ciudadanos);


/*   FUNCIONES PARA DIPUTADOS Y SENADORES   */
int BusquedaBinariaParlamentario(struct persona **arreglo, int plibre, char *rutBuscado);

void insertarParlamentarioOrdenado(struct persona **arreglo,int *plibre,int max ,struct persona *nuevoParlamentario);

int eliminarDiputado(struct congreso *congreso, char *rut);

void mostrarDiputados(struct congreso *congreso);

int eliminarSenador(struct congreso *congreso, char *rut);

void mostrarSenadores(struct congreso *congreso);


/*   FUNCIONES PARA PRESIDENTE   */
struct presidente *crearPresidente(struct persona *persona);

void mostrarPresidente(struct presidente *presidente);


/*   FUNCIONES PARA PROYECTOS   */
struct nodoProyecto *insertarPropuesta(struct nodoProyecto *raiz, struct proyecto *nuevaPropuesta, struct Grafo *grafo);

struct proyecto *buscarPropuesta(struct nodoProyecto *raiz, int id);

struct nodoProyecto *crearPropuesta(struct ProcesoLegislativo *pais, struct persona *autor);

void mostrarPropuesta(struct proyecto *propuesta);

void mostrarPropuestas(struct nodoProyecto *raiz);

int contarPropuestas(struct nodoProyecto *raizPropuestas);

int contarPropuestasAprobadas(struct nodoProyecto *raizPropuestas);

void mostrarPorcentajeProyectosAprobados(struct nodoProyecto *raizPropuestas);


/*   FUNCIONES PARA CAMARAS O COMISION MIXTA   */
void camaraDeOrigen(struct nodoProyecto *raizPropuestas, struct congreso *congreso);

void camaraRevisora(struct nodoProyecto *raizPropuestas, struct congreso *congreso);

void comisionMixta(struct nodoProyecto *raizPropuestas, struct congreso *congreso);


/*   FUNCIONES PARA BOLETINES   */
struct nodoBoletin *crearBoletin(struct proyecto *propuesta, char *fechaVigencia, int numeroBoletin);

struct nodoBoletin* eliminarLeyDeBoletin(struct nodoBoletin *boletinEstado, int numeroBoletin);

struct nodoBoletin* publicarLeyEnBoletin(struct nodoBoletin *boletinEstado, struct proyecto *propuesta);


/*   FUNCIONES PARA TRIBUNAL CONSTITUCIONAL   */
void ordenarTribunalPorEdad(struct persona tribunalConstitucional[], int tam);

int buscarPorEdad(struct persona tribunalConstitucional[], int tam, int edadBuscada);

void agregarMinistroTribunalConstitucional(struct persona tribunalConstitucional[], struct nodoCiudadano *ciudadanos, char rut[20]);

void eliminarMinistroTribunalConstitucional(struct persona tribunalConstitucional[10], struct nodoCiudadano *ciudadanos, char rut[20]);

void mostrarTribunalConstitucional(struct persona tribunalConstitucional[10]);

int verificarTC(struct persona tribunalConstitucional[10]);

int realizarVotacionMinistros(struct persona tribunalConstitucional[10]);

int controlConstitucionalidad(struct nodoBoletin *boletinEstado, struct proyecto *propuesta, struct persona tribunalConstitucional[10]);


/*   FUNCIONES PARA GRAFO   */
void establecerRelacion(struct Grafo *grafo, int nodo1, int nodo2, int peso);

void agregarNodoGrafo(struct Grafo *grafo);

void mostrarGrafo(struct Grafo *grafo);

struct Grafo *crearGrafo();

/*   MENUS   */
void menuAdministrar(struct ProcesoLegislativo *pais);

void administrarCiudadanos(struct ProcesoLegislativo *pais);

void administrarDiputadosoSenadores(struct ProcesoLegislativo *pais, int camara, struct persona **miembros, int pLibreMiembros, int maxMiembros);

void administrarPresidente(struct ProcesoLegislativo *pais);

void administrarProyectos(struct ProcesoLegislativo *pais);

void administrarCamaras(struct ProcesoLegislativo *pais);

void administrarBoletines(struct ProcesoLegislativo *pais);

void administrarTribunal(struct ProcesoLegislativo *pais);
/*PROTOTIPADO*/



/*FUNCIONES YA CREADAS*/
/*   FUNCIONES ADICIONALES   */
void cls() {
    int i;
    for(i = 0; i < 50; i++) {
        printf("\n");
    }
}

void limpiarBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        // Vaciar el buffer
    }
}

void promulgacionOVetoPresidencial(struct presidente *presidente, struct nodoProyecto *raizPropuestas, struct congreso *congreso) {
    int idPropuesta;
    int decisionPresidencial;
    int decisionCongreso;
    int i;
    struct proyecto *propuesta;

    // Check if president is registered
    if (presidente == NULL) {
        printf("No hay un presidente registrado.\n");
        return;
    }

    // Get proposal ID
    printf("Ingresa el ID de la propuesta a discutir para promulgacion o veto presidencial: ");
    scanf("%d", &idPropuesta);
    propuesta = buscarPropuesta(raizPropuestas, idPropuesta);

    // Validate proposal
    if (propuesta == NULL) {
        printf("Propuesta con ID %d no encontrada.\n", idPropuesta);
        return;
    }

    // Check if proposal was previously rejected
    if (propuesta->estado == 2) {
        printf("La propuesta con ID %d ya ha sido rechazada anteriormente.\n", idPropuesta);
        return;
    }

    // Presidential decision menu
    printf("El presidente %s esta evaluando la propuesta \"%s\" (ID: %d).\n", 
           presidente->persona->nombre, propuesta->tema, propuesta->id);
    printf("¿Cual es la decision del presidente?\n");
    printf("1. Promulgar la ley\n");
    printf("2. Veto total (rechazar todo el proyecto)\n");
    printf("3. Veto parcial (sugerir modificaciones a ciertos articulos)\n");
    printf("Elige una opcion: ");
    scanf("%d", &decisionPresidencial);

    if (decisionPresidencial == 1) {
        // Promulgate law
        printf("El presidente %s ha promulgado la propuesta \"%s\" como ley.\n", 
               presidente->persona->nombre, propuesta->tema);
        propuesta->estado = 1; // Approved
    }
    else if (decisionPresidencial == 2) {
        // Total veto
        printf("El presidente %s ha vetado totalmente la propuesta \"%s\".\n", 
               presidente->persona->nombre, propuesta->tema);
        printf("El proyecto ha sido rechazado por el presidente y no avanzara.\n");
        propuesta->estado = 2; // Rejected
    }
    else if (decisionPresidencial == 3) {
        // Partial veto with congressional decision
        printf("El presidente %s ha vetado parcialmente la propuesta \"%s\" y ha sugerido modificaciones.\n",
               presidente->persona->nombre, propuesta->tema);

        printf("El Congreso debe decidir si acepta las modificaciones.\n");
        printf("1. Aceptar las modificaciones del presidente\n");
        printf("2. Rechazar el veto con una mayoria de dos tercios\n");
        printf("Elige una opcion: ");
        scanf("%d", &decisionCongreso);

        if (decisionCongreso == 1) {
            printf("El Congreso ha aceptado las modificaciones. La ley ha sido promulgada con los cambios sugeridos por el presidente.\n");
            propuesta->estado = 1; // Approved
        }
        else if (decisionCongreso == 2) {
            int votosFavor = 0, votosContra = 0, votosTotales = 0;

            // Voting by deputies (now using array)
            for (i = 0; i < congreso->plibreDiputados; i++) {
                printf("El diputado %s vota a favor (1) o en contra (0) del veto presidencial?: ", 
                       congreso->diputados[i]->nombre);
                int voto;
                scanf("%d", &voto);
                limpiarBuffer();

                if (voto == 1) {
                    votosFavor++;
                } else {
                    votosContra++;
                }
                votosTotales++;
            }

            // Voting by senators (now using array traversal)
            for (i = 0; i < congreso->plibreSenadores; i++) {
                printf("El senador %s vota a favor (1) o en contra (0) del veto presidencial?: ", 
                       congreso->senadores[i]->nombre);
                int voto;
                scanf("%d", &voto);
                limpiarBuffer();

                if (voto == 1) {
                    votosFavor++;
                } else {
                    votosContra++;
                }
                votosTotales++;
            }

            // Check for two-thirds majority
            if ((votosFavor * 3) >= (votosTotales * 2) && votosContra < votosFavor) {
                printf("El Congreso ha rechazado el veto con una mayoria de dos tercios.\n");
                printf("La propuesta sera promulgada tal como fue aprobada por el Congreso.\n");
                propuesta->estado = 1; // Approved
            }
            else {
                printf("El Congreso no logro una mayoría de dos tercios. La propuesta sera modificada segun las sugerencias del presidente.\n");
                propuesta->estado = 1; // Approved with modifications
            }
        }
        else {
            printf("Opcion no valida.\n");
        }
    }
    else {
        printf("Opcion no válida. El proceso se cancela.\n");
    }
}



/*   FUNCIONES PARA CIUDADANOS   */
struct persona* crearCiudadano() {
    struct persona *nuevoCiudadano;
    char rut[20], nombre[50], especialidad[50];
    int edad, voto;

    printf("Ingresa el RUT: ");
    scanf("%19s", rut);

    printf("Ingresa el nombre: ");
    scanf("%49s", nombre);

    printf("Ingresa la edad: ");
    while (1) {
        if (scanf("%d", &edad) == 1 && edad >= 18) {
            break;
        } else {
            printf("Edad invalida. Intentalo de nuevo\n");
            // Limpiar el búfer de entrada
            while (getchar() != '\n');
        }
    }

    printf("Ingresa la especialidad: ");
    scanf("%49s", especialidad);

    voto = 0; // Inicialmente no ha votado en nada
    nuevoCiudadano = crearPersona(rut, nombre, edad, especialidad, voto);
    return nuevoCiudadano;
}

struct nodoCiudadano *agregarCiudadano(struct nodoCiudadano *ciudadanos, struct persona *ciudadano) {
    struct nodoCiudadano *nuevoCiudadano;
    struct nodoCiudadano *ultimo;

    // Primero, verificar si el ciudadano ya existe
    if (buscarCiudadanoPorRUT(ciudadanos, ciudadano->rut) != NULL) {
        printf("Ciudadano con RUT %s ya existe en el sistema\n", ciudadano->rut);
        return ciudadanos;
    }

    // Crear un nuevo nodo con el ciudadano
    nuevoCiudadano = crearNodoCiudadano(ciudadano);

    // Caso: lista vacía
    if (ciudadanos == NULL) {
        nuevoCiudadano->sig = nuevoCiudadano;  // Apunta a sí mismo
        nuevoCiudadano->ant = nuevoCiudadano;  // Apunta a sí mismo
        return nuevoCiudadano;
    }

    // Caso: lista con al menos un nodo
    ultimo = ciudadanos->ant;

    // Actualizar los enlaces
    nuevoCiudadano->sig = ciudadanos;   // Nuevo nodo apunta al primer nodo
    nuevoCiudadano->ant = ultimo;       // Nuevo nodo apunta al último nodo
    ultimo->sig = nuevoCiudadano;       // Último nodo apunta al nuevo nodo
    ciudadanos->ant = nuevoCiudadano;   // Primer nodo apunta al nuevo nodo

    printf("Ciudadano agregado exitosamente.\n");
    return ciudadanos;
}

struct persona *crearPersona(char *rut, char *nombre, int edad, char *especialidad, int voto) {

    struct persona *nuevaPersona;

    nuevaPersona = (struct persona *) malloc(sizeof(struct persona));

    strcpy(nuevaPersona->rut, rut);

    strcpy(nuevaPersona->nombre, nombre);

    nuevaPersona->edad = edad;

    nuevaPersona->cargo = 0;

    strcpy(nuevaPersona->especialidad, especialidad);

    nuevaPersona->voto = voto;

    return nuevaPersona;
}

struct nodoCiudadano *crearNodoCiudadano(struct persona *ciudadano) {
    struct nodoCiudadano *nuevoCiudadano;
    nuevoCiudadano = (struct nodoCiudadano *) malloc(sizeof(struct nodoCiudadano));
    nuevoCiudadano->datos = ciudadano;
    nuevoCiudadano->ant = nuevoCiudadano->sig = nuevoCiudadano;
    return nuevoCiudadano;
}

struct persona *buscarCiudadanoPorRUT(struct nodoCiudadano *ciudadanos, char *rut) {
    struct nodoCiudadano *rec = ciudadanos;

    /*Si la lista está vacia significa que no existen personas registradas*/
    if (rec == NULL) {
        printf("No Hay Ciudadanos Registrados.\n");
        return NULL;
    }

    do{
        /*Si se encuentra el nodo de la persona buscado se retorna el puntero hacia los datos de la persona*/
        if (strcmp(rec->datos->rut, rut) == 0) {
            return rec->datos;
        }
        rec = rec->sig;
    }while(rec != ciudadanos);

    return NULL;
}

void mostrarCiudadanos(struct nodoCiudadano *ciudadanos) {
    struct nodoCiudadano *rec = ciudadanos;
    if (ciudadanos == NULL) {
        printf("No hay ciudadanos en el sistema.\n");
        return;
    }

    do {
        printf("Nombre: %s\n", rec->datos->nombre);
        printf("RUT: %s\n", rec->datos->rut);
        printf("Edad: %d\n", rec->datos->edad);
        printf("Especialidad: %s\n", rec->datos->especialidad);
        if (rec->datos->cargo == 0) {
            printf("Cargo: Ciudadano\n\n");
        } else if (rec->datos->cargo == 1) {
            printf("Cargo: Diputado\n\n");
        } else if (rec->datos->cargo == 2) {
            printf("Cargo: Senador\n\n");
        } else if (rec->datos->cargo == 3) {
            printf("Cargo: Presidente\n\n");
        } else if (rec->datos->cargo == 4) {
            printf("Cargo: Ministro\n\n");
        }
        rec = rec->sig;
    }while (rec!=ciudadanos);
}

void eliminarCiudadano(struct nodoCiudadano **ciudadanos, char rut[20]) {
    struct nodoCiudadano *rec = *ciudadanos;
    struct nodoCiudadano *anterior = NULL;

    if (ciudadanos == NULL) {
        printf("No hay ciudadanos en el sistema.\n");
        return;
    }

    do {
        if (strcmp(rec->datos->rut, rut) == 0) {
            if (rec->sig == rec) { // Caso 1: Solo hay un nodo en la lista
                *ciudadanos = NULL;
            } else {
                if (rec == *ciudadanos) { // Caso 2: El nodo a eliminar es el primero
                    *ciudadanos = rec->sig;
                }
                // Reconectar los nodos adyacentes
                rec->ant->sig = rec->sig;
                rec->sig->ant = rec->ant;
            }
            printf("Ciudadano con RUT %s eliminado.\n", rut);
            return;
        }
        anterior = rec;
        rec = rec->sig;
    } while (rec != *ciudadanos); // Recorrer toda la lista



    printf("Ciudadano con RUT %s no encontrado.\n", rut);
    return;
}

void mostrarPromedioEdadCiudadanos(struct nodoCiudadano *ciudadanos) {
    struct nodoCiudadano *rec = ciudadanos;
    int cantidadCiudadanos = 0;
    int cantidadSobrePromedio = 0;
    int sumaEdades = 0;
    float promedioEdad;

    if (ciudadanos == NULL) {
        printf("No hay ciudadanos registrados.\n");
        return;
    }



    // Calcular suma de edades y cantidad de ciudadanos
    do {
        if (rec->datos != NULL) {
            sumaEdades += rec->datos->edad;
            cantidadCiudadanos++;
        }
        rec = rec->sig; // Avanzar al siguiente nodo
    } while (rec != ciudadanos); // Detener cuando volvemos al inicio

    if (cantidadCiudadanos == 0) {
        printf("No hay ciudadanos con edad registrada.\n");
        return;
    }

    promedioEdad = (float)sumaEdades / cantidadCiudadanos;

    // Recorrer nuevamente para contar ciudadanos sobre el promedio
    rec = ciudadanos;
    do {
        if (rec->datos != NULL && rec->datos->edad > promedioEdad) {
            cantidadSobrePromedio++;
        }
        rec = rec->sig; // Avanzar al siguiente nodo
    } while (rec != ciudadanos); // Detener cuando volvemos al inicio

    // Imprimir los resultados
    printf("\nPromedio de edad: %.2f\n", promedioEdad);
    printf("Cantidad de ciudadanos: %d\n", cantidadCiudadanos);
    printf("Porcentaje de ciudadanos sobre el promedio de edad: %.2f%%\n", (float)cantidadSobrePromedio / cantidadCiudadanos * 100);
}


/*   FUNCIONES PARA DIPUTADOS Y SENADORES   */
/*CORREGIR DECLARACIONES*/
int BusquedaBinariaParlamentario(struct persona **arreglo, int plibre, char *rutBuscado) {
    // Validaciones iniciales
    if (arreglo == NULL || rutBuscado == NULL || plibre == 0) {
        return -1;  // Arreglo vacío o inválido
    }

    // Variables para búsqueda binaria
    int inicio = 0;
    int fin = plibre - 1;
    int medio;
    int comparacion;

    // Búsqueda binaria
    while (inicio <= fin) {
        // Cálculo de punto medio para evitar overflow
        medio = inicio + (fin - inicio) / 2;

        // Comparar RUTs
        comparacion = strcmp(rutBuscado, arreglo[medio]->rut);

        // Si son iguales, encontramos el elemento
        if (comparacion == 0) {
            return medio;
        }

        // Si el RUT buscado es menor, buscar en la mitad izquierda
        if (comparacion < 0) {
            fin = medio - 1;
        }
        // Si el RUT buscado es mayor, buscar en la mitad derecha
        else {
            inicio = medio + 1;
        }
    }

    // No se encontró el elemento
    return -1;
}

void insertarParlamentarioOrdenado(struct persona **parlamentarios, int *plibreParlamentarios, int MaxParlamentarios, struct persona *nuevoParlamentario) {
    int i;

    // Verificar si hay espacio
    if (*plibreParlamentarios >= MaxParlamentarios) {
        printf("Error: arreglo lleno\n");
        return;
    }

    i = *plibreParlamentarios - 1;
    // Insertar de manera ordenada por el RUT
    while (i >= 0 && strcmp(parlamentarios[i]->rut, nuevoParlamentario->rut) > 0) {
        parlamentarios[i + 1] = parlamentarios[i];
        i--;
    }

    parlamentarios[i + 1] = nuevoParlamentario;
    (*plibreParlamentarios)++;
}

int eliminarDiputado(struct congreso *congreso, char *rut) {
    int posicionEncontrada,i;
    // Verificamos que los parámetros sean válidos
    if (congreso == NULL || rut == NULL || congreso->diputados == NULL) {
        return 0;
    }

    // Si no hay diputados, no hay nada que eliminar
    if (congreso->plibreDiputados <= 0) {
        return 0;
    }

    // Utilizamos la función de búsqueda binaria existente
    posicionEncontrada = BusquedaBinariaParlamentario(congreso->diputados,congreso->plibreDiputados ,rut);

    // Si no encontramos al diputado, retornamos 0
    if (posicionEncontrada == -1) {
        return 0;
    }

    // Desplazamos todos los elementos posteriores una posición hacia atrás
    for (i = posicionEncontrada; i < congreso->plibreDiputados - 1; i++) {
        congreso->diputados[i] = congreso->diputados[i + 1];
    }

    // Reducimos el contador de diputados
    congreso->plibreDiputados--;

    // Actualizamos también plibreDiputados si se está usando para el control del arreglo
    congreso->plibreDiputados--;

    // El último puntero lo ponemos en NULL por seguridad
    congreso->diputados[congreso->plibreDiputados] = NULL;

    return 1;
}

void mostrarDiputados(struct congreso *congreso) {
    int i;
    // Primero verificamos que el congreso y el arreglo de diputados existan
    if (congreso == NULL || congreso->diputados == NULL) {
        printf("Error: No hay un congreso válido para mostrar.\n");
        return;
    }

    // Verificamos si hay diputados para mostrar
    if (congreso->plibreDiputados <= 0) {
        printf("\n=== CÁMARA DE DIPUTADOS ===\n");
        printf("No hay diputados registrados actualmente.\n");
        printf("Capacidad máxima: %d diputados\n", congreso->MaxDiputados);
        return;
    }

    // Mostramos el encabezado con información general
    printf("\n========= CÁMARA DE DIPUTADOS =========\n");
    printf("Total de diputados: %d\n", congreso->plibreDiputados);
    printf("Capacidad máxima: %d\n", congreso->MaxDiputados);
    printf("Cupos disponibles: %d\n", congreso->MaxDiputados - congreso->plibreDiputados);
    printf("======================================\n\n");

    // Mostramos cada diputado con un formato ordenado
    for (i = 0; i < congreso->plibreDiputados; i++) {
        // Verificamos que el diputado en esta posición exista
        if (congreso->diputados[i] != NULL) {
            printf("Diputado %d:\n", i + 1);
            printf("   RUT: %s\n", congreso->diputados[i]->rut);
            printf("   Nombre: %s\n", congreso->diputados[i]->nombre);
            // Podemos agregar más campos según la estructura persona
            printf("   ------------------------\n");
        }
    }

    // Mostramos un resumen al final
    printf("\nResumen de ocupación: %d/%d diputados\n", 
           congreso->plibreDiputados, congreso->MaxDiputados);

    // Si estamos cerca de la capacidad máxima, mostramos una advertencia
    if (congreso->plibreDiputados >= congreso->MaxDiputados * 0.9) {
        printf("\n¡ADVERTENCIA: La cámara está al %d%% de su capacidad máxima!\n",
               (congreso->plibreDiputados * 100) / congreso->MaxDiputados);
    }
}

int eliminarSenador(struct congreso *congreso, char *rut) {
    int i;
    int indice;

    // Validar que el congreso y el arreglo de senadores existan
    if (congreso == NULL || congreso->senadores == NULL) {
        printf("Error: Congreso o arreglo de senadores no válido.\n");
        return 0;
    }

    // Buscar el índice del senador usando la búsqueda binaria
     indice = BusquedaBinariaParlamentario(congreso->senadores,congreso->plibreSenadores, rut);

    // Verificar si el senador fue encontrado
    if (indice == -1) {
        printf("Senador con RUT %s no encontrado.\n", rut);
        return 0;
    }

    // Resetear el cargo del senador a 0 (sin cargo)
    congreso->senadores[indice]->cargo = 0;

    // Desplazar los elementos restantes para cubrir el espacio
    for ( i = indice; i < congreso->plibreSenadores - 1; i++) {
        congreso->senadores[i] = congreso->senadores[i + 1];
    }

    // Reducir el contador de senadores
    congreso->plibreSenadores--;

    printf("Senador con RUT %s eliminado correctamente.\n", rut);
    return 1;
}

void mostrarSenadores(struct congreso *congreso) {
    int i;
    // Primero verificamos que el congreso y el arreglo de senadores existan
    if (congreso == NULL || congreso->senadores == NULL) {
        printf("Error: No hay un congreso válido para mostrar.\n");
        return;
    }
    // Verificamos si hay senadores para mostrar
    if (congreso->plibreSenadores <= 0) {
        printf("\n=== CÁMARA DE SENADORES ===\n");
        printf("No hay senadores registrados actualmente.\n");
        printf("Capacidad máxima: %d senadores\n", congreso->MaxSenadores);
        return;
    }
    // Mostramos el encabezado con información general
    printf("\n========= CÁMARA DE SENADORES =========\n");
    printf("Total de senadores: %d\n", congreso->plibreSenadores);
    printf("Capacidad máxima: %d\n", congreso->MaxSenadores);
    printf("Cupos disponibles: %d\n", congreso->MaxSenadores - congreso->plibreSenadores);
    printf("======================================\n\n");
    // Mostramos cada senador con un formato ordenado
    for (i = 0; i < congreso->plibreSenadores; i++) {
        // Verificamos que el senador en esta posición exista
        if (congreso->senadores[i] != NULL) {
            printf("Senador %d:\n", i + 1);
            printf("   RUT: %s\n", congreso->senadores[i]->rut);
            printf("   Nombre: %s\n", congreso->senadores[i]->nombre);
            // Podemos agregar más campos según la estructura persona
            printf("   ------------------------\n");
        }
    }
    // Mostramos un resumen al final
    printf("\nResumen de ocupación: %d/%d senadores\n", 
           congreso->plibreSenadores, congreso->MaxSenadores);
    // Si estamos cerca de la capacidad máxima, mostramos una advertencia
    if (congreso->plibreSenadores >= congreso->MaxSenadores * 0.9) {
        printf("\n¡ADVERTENCIA: La cámara está al %d%% de su capacidad máxima!\n",
               (congreso->plibreSenadores * 100) / congreso->MaxSenadores);
    }
}



/*   FUNCIONES PARA PRESIDENTE   */
struct presidente *crearPresidente(struct persona *persona) {
    struct presidente *nuevoPresidente;
    int anioMandato;


    if (persona->cargo == 3) {
        printf("La persona ya tiene el cargo de presidente.\n");
        return NULL;
    }
    else if (persona->cargo != 0) {
        printf("La persona ya tiene un cargo publico. No puede ser presidente.\n");
        return NULL;
    }
    persona->cargo = 3;
    printf("Ingresa el año de mandato del presidente: ");
    scanf("%d", &anioMandato);
    limpiarBuffer();

    nuevoPresidente = (struct presidente *)malloc(sizeof(struct presidente));

    nuevoPresidente->persona = persona;
    nuevoPresidente->anioMandato = anioMandato;
    nuevoPresidente->voto = 0;

    printf("Presidente agregado exitosamente.\n");

    return nuevoPresidente;
}

void mostrarPresidente(struct presidente *presidente) {
    if (presidente == NULL) {
        printf("No hay un presidente registrado.\n");
        return;
    }

    printf("\n===== Datos del Presidente =====\n");
    printf("Nombre: %s\n", presidente->persona->nombre);
    printf("Edad: %d\n", presidente->persona->edad);
    printf("Especialidad: %s\n", presidente->persona->especialidad);
    printf("Año de Mandato: %d\n", presidente->anioMandato);
    printf("================================\n");
}


/*   FUNCIONES PARA PROYECTOS   */
struct nodoProyecto *insertarPropuesta(struct nodoProyecto *raiz, struct proyecto *nuevaPropuesta, struct Grafo *grafo) {
    int i;
    int nuevoNodoIndice;
    struct proyecto *proyectoExistente = NULL;
    // Caso base: el árbol está vacío, se crea el nodo y se actualiza el grafo
    if (raiz == NULL) {
        struct nodoProyecto *nuevoNodo = (struct nodoProyecto *)malloc(sizeof(struct nodoProyecto));
        nuevoNodo->datos = nuevaPropuesta;
        nuevoNodo->izq = nuevoNodo->der = NULL;

        // Actualizar el grafo: agregar un nuevo nodo (proyecto) al grafo
        if (grafo != NULL) {
            agregarNodoGrafo(grafo);

            // Relacionar el nuevo proyecto con los ya existentes según algún criterio
            nuevoNodoIndice = grafo->numVertices - 1; // Índice del nuevo nodo
            for (i = 0; i < nuevoNodoIndice; i++) {
                // Ejemplo: relacionar proyectos con la misma urgencia
                proyectoExistente = buscarPropuesta(raiz, i); // Buscar proyectos ya existentes
                if (proyectoExistente != NULL && proyectoExistente->urgencia == nuevaPropuesta->urgencia) {
                    establecerRelacion(grafo, i, nuevoNodoIndice, 1);
                }
            }
        }

        return nuevoNodo;
    }

    // Insertar en el subárbol izquierdo o derecho según el ID
    if (nuevaPropuesta->id < raiz->datos->id) {
        raiz->izq = insertarPropuesta(raiz->izq, nuevaPropuesta, grafo);
    } else if (nuevaPropuesta->id > raiz->datos->id) {
        raiz->der = insertarPropuesta(raiz->der, nuevaPropuesta, grafo);
    } else {
        // Caso de ID duplicado
        printf("Propuesta con ID %d ya existe.\n", nuevaPropuesta->id);
    }

    return raiz;
}

struct proyecto *buscarPropuesta(struct nodoProyecto *raiz, int id) {
    if (raiz == NULL) {
        return NULL; // No encontrada
    }

    if (id == raiz->datos->id) {
        return raiz->datos;
    } else if (id < raiz->datos->id) {
        return buscarPropuesta(raiz->izq, id);
    } else {
        return buscarPropuesta(raiz->der, id);
    }
}

struct nodoProyecto *crearPropuesta(struct ProcesoLegislativo *pais, struct persona *autor) {
    struct proyecto *nuevaPropuesta = (struct proyecto *)malloc(sizeof(struct proyecto));
    char tipo[50];
    char tema[50];

    printf("Ingresa el ID de la propuesta: ");
    scanf("%d", &nuevaPropuesta->id);
    limpiarBuffer();

    printf("Ingresa el tipo de propuesta (financiero, tributario, educacion, etc.): ");
    scanf("%s", tipo);  // Usamos scanf para leer el tipo de propuesta
    nuevaPropuesta->tipo = (char *)malloc(strlen(tipo) + 1);
    strcpy(nuevaPropuesta->tipo, tipo);

    printf("Ingresa el tema de la propuesta (educacion, salud, etc.): ");
    scanf("%s", tema);  // Usamos scanf para leer el tema de la propuesta
    nuevaPropuesta->tema = (char *)malloc(strlen(tema) + 1);
    strcpy(nuevaPropuesta->tema, tema);

    nuevaPropuesta->personaAcargo = autor;

    printf("Propuesta creada exitosamente.\n");

    return insertarPropuesta(pais->propuesta, nuevaPropuesta, pais->grafoProyectos); // Insertar en el ABB
}

void mostrarPropuesta(struct proyecto *propuesta) {
    if (propuesta == NULL) {
        printf("No se encontro la propuesta con el ID especificado.\n");
    } else {
        printf("\n===== Datos de la Propuesta =====\n");
        printf("ID de la propuesta: %d\n", propuesta->id);
        printf("Tipo: %s\n", propuesta->tipo);
        printf("Tema: %s\n", propuesta->tema);
        printf("Autor: %s\n", propuesta->personaAcargo->nombre);
        if (propuesta->estado == 0) {
            printf("Estado: En tramite\n");
        } else if (propuesta->estado == 1) {
            printf("Estado: Aprobada\n");
        } else if (propuesta->estado == 2) {
            printf("Estado: Rechazada\n");
        }
        printf("=================================\n");
    }
}

void mostrarPropuestas(struct nodoProyecto *raiz) {
    if (raiz == NULL) {
        printf("No hay propuestas registradas.\n");
        return;
    }

    // Recorrido inorden (izquierda, raíz, derecha)
    if (raiz->izq != NULL) {
        mostrarPropuestas(raiz->izq); // Lado izquierdo del árbol
    }

    /* 1 = Urgencia Simple, 2 = Suma Urgencia, 3 = Discusión Inmediata*/
    // Mostrar la propuesta actual (nodo raíz)
    printf("\n===== Datos de la Propuesta =====\n");
    printf("ID de la propuesta: %d\n", raiz->datos->id);
    printf("Tipo: %s\n", raiz->datos->tipo);
    printf("Tema: %s\n", raiz->datos->tema);
    printf("Autor: %s\n", raiz->datos->personaAcargo->nombre);
    if (raiz->datos->urgencia == 1) {
        printf("Urgencia: Urgencia Simple\n");
    } else if (raiz->datos->urgencia == 2) {
        printf("Urgencia: Suma Urgencia\n");
    } else if (raiz->datos->urgencia == 3) {
        printf("Urgencia: Discusión Inmediata\n");
    }

    if (raiz->datos->estado == 0) {
        printf("Estado: En tramite\n");
    } else if (raiz->datos->estado == 1) {
        printf("Estado: Aprobada\n");
    } else if (raiz->datos->estado == 2) {
        printf("Estado: Rechazada\n");
    }
    printf("=================================\n");

    // Recorrido por el lado derecho del árbol
    if (raiz->der != NULL) {
        mostrarPropuestas(raiz->der);
    }
}

int contarPropuestas(struct nodoProyecto *raizPropuestas) {
    if (raizPropuestas == NULL) {
        return 0;
    }
    return 1 + contarPropuestas(raizPropuestas->izq) + contarPropuestas(raizPropuestas->der);
}

int contarPropuestasAprobadas(struct nodoProyecto *raizPropuestas) {
    if (raizPropuestas == NULL) {
        return 0;
    }

    if (raizPropuestas->datos != NULL && raizPropuestas->datos->estado == 1) {
        return 1 + contarPropuestasAprobadas(raizPropuestas->izq) + contarPropuestasAprobadas(raizPropuestas->der);
    } else {
        return contarPropuestasAprobadas(raizPropuestas->izq) + contarPropuestasAprobadas(raizPropuestas->der);
    }
}

void mostrarPorcentajeProyectosAprobados(struct nodoProyecto *raizPropuestas) {
    int cantidadPropuestas = contarPropuestas(raizPropuestas);
    int cantidadAprobadas = contarPropuestasAprobadas(raizPropuestas);
    float porcentajeAprobadas;

    if (cantidadPropuestas == 0) {
        printf("\nNo hay propuestas registradas.\n");
        return;
    }

    porcentajeAprobadas = ((float)cantidadAprobadas / cantidadPropuestas) * 100;
    printf("\nPorcentaje de propuestas aprobadas: %.2f%%\n", porcentajeAprobadas);
    printf("Cantidad de propuestas: %d\n", cantidadPropuestas);
    printf("Cantidad de propuestas aprobadas: %d\n", cantidadAprobadas);
}



/*   FUNCIONES PARA CAMARAS O COMISION MIXTA   */
void camaraDeOrigen(struct nodoProyecto *raizPropuestas, struct congreso *congreso) {
    // Declaraciones de variables al inicio
    struct proyecto *propuesta = NULL;
    int idPropuesta;
    int votosAFavor = 0, votosEnContra = 0;
    int i; // Variable para los bucles for

    // Solicitar ID de la propuesta
    printf("Ingresa el ID de la propuesta a discutir: ");
    scanf("%d", &idPropuesta);

    // Buscar la propuesta
    propuesta = buscarPropuesta(raizPropuestas, idPropuesta);
    if (propuesta == NULL) {
        printf("Propuesta con ID %d no encontrada.\n", idPropuesta);
        return;
    }

    // Verificar si es proyecto financiero o tributario
    if (strcmp(propuesta->tipo, "financiero") == 0 || strcmp(propuesta->tipo, "tributario") == 0) {
        printf("El proyecto de tipo %s debe ser discutido primero en la Camara de Diputados.\n", propuesta->tipo);

        // Verificar si hay diputados disponibles
        if (congreso->plibreDiputados == 0 || congreso->diputados == NULL) {
            printf("No hay diputados disponibles para votar.\n");
            return;
        }

        // Realizar votación con el arreglo de diputados
        for (i = 0; i < congreso->plibreDiputados; i++) {
            printf("El diputado %s vota a favor o en contra de la propuesta? (1 = A favor | Otro numero = En contra): ", 
                   congreso->diputados[i]->nombre);
            scanf("%d", &congreso->diputados[i]->voto);
            limpiarBuffer();

            if (congreso->diputados[i]->voto == 1) {
                votosAFavor++;
            } else {
                votosEnContra++;
            }
        }
    } else {
        printf("El proyecto de tipo %s sera discutido en el Senado.\n", propuesta->tipo);

        // Verificar si hay senadores disponibles
        if (congreso->plibreSenadores == 0 || congreso->senadores == NULL) {
            printf("No hay senadores disponibles para votar.\n");
            return;
        }

        // Realizar votación con el arreglo de senadores
        for (i = 0; i < congreso->plibreSenadores; i++) {
            printf("El senador %s vota a favor o en contra de la propuesta? (1 = A favor | Otro numero = En contra): ", 
                   congreso->senadores[i]->nombre);
            scanf("%d", &congreso->senadores[i]->voto);
            limpiarBuffer();

            if (congreso->senadores[i]->voto == 1) {
                votosAFavor++;
            } else {
                votosEnContra++;
            }
        }
    }

    // Mostrar resultados de la votación
    printf("\n═══════ RESULTADOS DE LA VOTACIÓN ═══════\n");
    printf("Votos a favor: %d\n", votosAFavor);
    printf("Votos en contra: %d\n", votosEnContra);

    if (votosAFavor > votosEnContra) {
        printf("La idea de legislar ha sido aprobada. El proyecto avanza a la siguiente etapa.\n");
        propuesta->estado = 0; // En trámite
    } else {
        printf("La idea de legislar ha sido rechazada. El proyecto no avanza.\n");
        propuesta->estado = 2; // Rechazada
    }

    // Mostrar detalle de votos
    printf("\n═══════ DETALLE DE VOTOS ═══════\n");
    if (strcmp(propuesta->tipo, "financiero") == 0 || strcmp(propuesta->tipo, "tributario") == 0) {
        printf("Votos de Diputados:\n");
        for (i = 0; i < congreso->plibreDiputados; i++) {
            printf("Diputado %s: %s\n", 
                   congreso->diputados[i]->nombre, 
                   congreso->diputados[i]->voto == 1 ? "A favor" : "En contra");
        }
    } else {
        printf("Votos de Senadores:\n");
        for (i = 0; i < congreso->plibreSenadores; i++) {
            printf("Senador %s: %s\n", 
                   congreso->senadores[i]->nombre, 
                   congreso->senadores[i]->voto == 1 ? "A favor" : "En contra");
        }
    }
}

/* Función para manejar la Cámara Revisora */
void camaraRevisora(struct nodoProyecto *raizPropuestas, struct congreso *congreso) {
    struct proyecto *propuesta;
    int idPropuesta, i;
    int votosAFavor = 0, votosEnContra = 0;
    int modificacion = 0;  // Si la Cámara Revisora propone modificaciones

    printf("Ingresa el ID de la propuesta a discutir en la Camara Revisora: ");
    scanf("%d", &idPropuesta);
    propuesta = buscarPropuesta(raizPropuestas, idPropuesta);

    // Buscar la propuesta por ID en el ABB
    if (propuesta == NULL) {
        printf("Propuesta con ID %d no encontrada.\n", idPropuesta);
        return;
    }

    if (propuesta->estado == 2) {
        printf("La propuesta con ID %d ya ha sido rechazada anteriormente.\n", idPropuesta);
        return;
    }

    printf("La propuesta con ID %d ha llegado a la Camara Revisora.\n", idPropuesta);

    // Lógica de votación en la Cámara Revisora
    if (strcmp(propuesta->tipo, "financiero") == 0 || strcmp(propuesta->tipo, "tributario") == 0) {
        // Votación de senadores con arreglo
        if (congreso->plibreSenadores == 0 || congreso->senadores == NULL) {
            printf("No hay senadores disponibles para votar.\n");
            return;
        }

        for (i = 0; i < congreso->plibreSenadores; i++) {
            printf("El senador %s vota a favor o en contra de la propuesta? (1 = A favor | Otro numero = En contra): ", 
                   congreso->senadores[i]->nombre);
            scanf("%d", &congreso->senadores[i]->voto);
            limpiarBuffer();

            if (congreso->senadores[i]->voto == 1) {
                votosAFavor++;
            } else {
                votosEnContra++;
            }
        }
    } else {
        // Votación de diputados con arreglo
        if (congreso->plibreDiputados == 0 || congreso->diputados == NULL) {
            printf("No hay diputados disponibles para votar.\n");
            return;
        }

        for (i = 0; i < congreso->plibreDiputados; i++) {
            printf("El diputado %s vota a favor o en contra de la propuesta? (1 = A favor | Otro numero = En contra): ", 
                   congreso->diputados[i]->nombre);
            scanf("%d", &congreso->diputados[i]->voto);
            limpiarBuffer();

            if (congreso->diputados[i]->voto == 1) {
                votosAFavor++;
            } else {
                votosEnContra++;
            }
        }
    }

    printf("Resultados de la votacion en la Cámara Revisora:\n");
    printf("Votos a favor: %d\n", votosAFavor);
    printf("Votos en contra: %d\n", votosEnContra);

    // Resultado en la Cámara Revisora
    if (votosAFavor > votosEnContra) {
        printf("¿La Camara Revisora propone modificaciones? (1 = Sí, Otro Numero = No): ");
        scanf("%d", &modificacion);

        if (modificacion == 1) {
            propuesta->estado = 0; // En trámite
            printf("La Camara Revisora ha propuesto modificaciones. El proyecto vuelve a la Camara de Origen.\n");
        } else {
            propuesta->estado = 0; // En trámite
            printf("La Camara Revisora ha aprobado el proyecto sin cambios. Se envia al Presidente para su promulgacion.\n");
        }
    } else {
        propuesta->estado = 2; // Rechazada
        printf("El proyecto ha sido rechazado en la Camara Revisora. No se promulga.\n");
    }

    // Mostrar detalle de votos
    printf("\n═══════ DETALLE DE VOTOS ═══════\n");
    if (strcmp(propuesta->tipo, "financiero") == 0 || strcmp(propuesta->tipo, "tributario") == 0) {
        printf("Votos de Senadores:\n");
        for (i = 0; i < congreso->plibreSenadores; i++) {
            printf("Senador %s: %s\n", 
                   congreso->senadores[i]->nombre, 
                   congreso->senadores[i]->voto == 1 ? "A favor" : "En contra");
        }
    } else {
        printf("Votos de Diputados:\n");
        for (i = 0; i < congreso->plibreDiputados; i++) {
            printf("Diputado %s: %s\n", 
                   congreso->diputados[i]->nombre, 
                   congreso->diputados[i]->voto == 1 ? "A favor" : "En contra");
        }
    }
}

// Function to handle Mixed Commission procedure
void comisionMixta(struct nodoProyecto *raizPropuestas, struct congreso *congreso) {
    struct proyecto *propuesta = NULL;
    int idPropuesta;
    int i;
    int consenso = 0;
    int votosAFavorDiputados = 0, votosEnContraDiputados = 0;
    int votosAFavorSenadores = 0, votosEnContraSenadores = 0;
    int votosAFavorTotal, votosEnContraTotal;

    // Get proposal ID
    printf("Ingresa el ID de la propuesta a enviar a la Comision Mixta: ");
    scanf("%d", &idPropuesta);
    propuesta = buscarPropuesta(raizPropuestas, idPropuesta);
    limpiarBuffer();

    // Validate proposal
    if (propuesta == NULL) {
        printf("Propuesta con ID %d no encontrada.\n", idPropuesta);
        return;
    }

    if (propuesta->estado == 2) {
        printf("La propuesta con ID %d ya ha sido rechazada anteriormente.\n", idPropuesta);
        return;
    }

    printf("\n===== Comision Mixta =====\n");
    printf("La propuesta '%s' ha sido enviada a la Comision Mixta para resolver discrepancias.\n", propuesta->tema);

    // Voting by deputies
    printf("\nVotacion de los Diputados en la Comision Mixta:\n");
    for ( i = 0; i < congreso->plibreDiputados; i++) {
        printf("El diputado %s vota a favor (1) o en contra (0) de la propuesta? ", 
               congreso->diputados[i]->nombre);
        int voto;
        scanf("%d", &voto);
        limpiarBuffer();

        if (voto == 1) {
            votosAFavorDiputados++;
        } else {
            votosEnContraDiputados++;
        }
    }

    printf("Diputados a favor: %d\n", votosAFavorDiputados);
    printf("Diputados en contra: %d\n", votosEnContraDiputados);

    // Voting by senators
    printf("\nVotacion de los Senadores en la Comision Mixta:\n");
    for (i = 0; i < congreso->plibreSenadores; i++) {
        printf("El senador %s vota a favor (1) o en contra (0) de la propuesta? ", 
               congreso->senadores[i]->nombre);
        int voto;
        scanf("%d", &voto);
        limpiarBuffer();

        if (voto == 1) {
            votosAFavorSenadores++;
        } else {
            votosEnContraSenadores++;
        }
    }

    printf("Senadores a favor: %d\n", votosAFavorSenadores);
    printf("Senadores en contra: %d\n", votosEnContraSenadores);

    // Determine consensus in Mixed Commission
    if ((votosAFavorDiputados > votosEnContraDiputados) && (votosAFavorSenadores > votosEnContraSenadores)) {
        consenso = 1;
        printf("\nLa Comision Mixta ha alcanzado un consenso. El informe sera enviado a ambas camaras para su votacion.\n");
    } else {
        propuesta->estado = 2; // Rejected
        printf("\nNo se alcanzo un consenso en la Comision Mixta. El proyecto ha sido rechazado.\n");
    }

    // If consensus is reached, send report to both chambers
    if (consenso) {
        printf("\nEl proyecto se envia a ambas camaras para su votacion final...\n");

        votosAFavorTotal = votosAFavorDiputados + votosAFavorSenadores;
        votosEnContraTotal = votosEnContraDiputados + votosEnContraSenadores;

        printf("Votos totales a favor: %d\n", votosAFavorTotal);
        printf("Votos totales en contra: %d\n", votosEnContraTotal);

        if (votosAFavorTotal > votosEnContraTotal) {
            printf("El proyecto ha sido aprobado por ambas camaras tras el consenso en la Comision Mixta.\n");
            propuesta->estado = 0; // In process
        } else {
            printf("El proyecto ha sido rechazado por ambas camaras tras la votacion final.\n");
            propuesta->estado = 2; // Rejected
        }
    }
}



/*   FUNCIONES PARA BOLETINES   */
// Función para crear un nuevo boletín
struct nodoBoletin *crearBoletin(struct proyecto *propuesta, char *fechaVigencia, int numeroBoletin) {
    struct nodoBoletin *nuevoBoletin = (struct nodoBoletin *)malloc(sizeof(struct nodoBoletin));
    struct boletin *nuevoBoletinHead = (struct boletin *)malloc(sizeof(struct boletin));

    nuevoBoletinHead->propuesta = propuesta;
    nuevoBoletinHead->numeroBoletin = numeroBoletin;

    // Asignar fecha de publicación
    nuevoBoletinHead->fechaVigencia = (char *)malloc(strlen(fechaVigencia) + 1);
    strcpy(nuevoBoletinHead->fechaVigencia, fechaVigencia);

    nuevoBoletin->head = nuevoBoletinHead;
    nuevoBoletin->sig = NULL;

    return nuevoBoletin;
}

struct nodoBoletin* eliminarLeyDeBoletin(struct nodoBoletin *boletinEstado, int numeroBoletin) {
    struct nodoBoletin *rec = boletinEstado;
    struct nodoBoletin *temp = NULL;

    if (boletinEstado == NULL) {
        printf("No hay boletines en el sistema.\n");
        return NULL;
    }

    while (rec != NULL) {
        if (rec->head->numeroBoletin == numeroBoletin) {
            if (rec == boletinEstado) { // si es el primer boletín
                temp = rec->sig;
                rec->head->fechaVigencia = NULL;
                rec->head = NULL;
                rec = NULL;
                printf("Boletin con numero %d eliminado.\n", numeroBoletin);
                return temp;
            } else {
                temp->sig = rec->sig;
                rec->head->fechaVigencia = NULL;
                rec->head = NULL;
                rec = NULL;
                printf("Boletin con numero %d eliminado.\n", numeroBoletin);
                return boletinEstado;
            }
        }
        temp = rec;
        rec = rec->sig;
    }

    printf("Boletin con numero %d no encontrado.\n", numeroBoletin);
    return boletinEstado;
}

// Función para publicar una ley en el boletín y establecer su fecha de entrada en vigencia
struct nodoBoletin* publicarLeyEnBoletin(struct nodoBoletin *boletinEstado, struct proyecto *propuesta) {
    struct nodoBoletin *nuevoBoletin = NULL;
    char fechaPublicacion[20];
    char fechaVigencia[20];
    int entradaInmediata = 0;
    int numeroBoletin = 1;  // Contador de boletines
    struct nodoBoletin *temp;

    // Solicitar fecha de publicación
    printf("Ingresa la fecha de publicacion (dd/mm/yyyy) para la ley '%s': ", propuesta->tema);
    scanf("%s", fechaPublicacion);  // Reemplazo de fgets por scanf

    // Preguntar si la ley entra en vigencia de manera inmediata
    printf("Ley '%s' promulgada. ¿La ley entra en vigencia de manera inmediata? (1 = Sí, 0 = No): ", propuesta->tema);
    scanf("%d", &entradaInmediata);
    limpiarBuffer();  // Para evitar problemas con scanf después

    if (entradaInmediata == 1) {
        strcpy(fechaVigencia, fechaPublicacion);  // Vigencia inmediata
    } else {
        printf("Ingresa la fecha de entrada en vigencia (dd/mm/yyyy): ");
        scanf("%s", fechaVigencia);  // Reemplazo de fgets por scanf
    }

    // Crear el nuevo boletín
    nuevoBoletin = crearBoletin(propuesta, fechaVigencia, numeroBoletin);

    // Agregar el boletín al final de la lista
    if (boletinEstado == NULL) {
        boletinEstado = nuevoBoletin;
    } else {
        temp = boletinEstado;
        while (temp->sig != NULL) {
            temp = temp->sig;
        }
        temp->sig = nuevoBoletin;
    }

    printf("La ley '%s' ha sido publicada en el Diario Oficial bajo el Boletin N°%d y entrara en vigencia el %s.\n",
            propuesta->tema, nuevoBoletin->head->numeroBoletin, fechaVigencia);

    return boletinEstado;
}



/*   FUNCIONES PARA TRIBUNAL CONSTITUCIONAL   */
//Insercion Binaria
void ordenarTribunalPorEdad(struct persona tribunalConstitucional[], int tam) {
    int i, j, izq, der, medio;
    struct persona valorActual;

    // Comenzamos desde el segundo elemento
    for (i = 1; i < tam; i++) {
        valorActual = tribunalConstitucional[i];

        // Usamos búsqueda binaria para encontrar la posición de inserción
        izq = 0;
        der = i - 1;

        while (izq <= der) {
            medio = (izq + der) / 2;
            if (tribunalConstitucional[medio].edad > valorActual.edad) {
                der = medio - 1;
            } else {
                izq = medio + 1;
            }
        }

        // Desplazamos los elementos mayores una posición a la derecha
        for (j = i - 1; j >= izq; j--) {
            tribunalConstitucional[j + 1] = tribunalConstitucional[j];
        }

        // Insertamos el elemento en su posición correcta
        tribunalConstitucional[izq] = valorActual;
    }
}
//Busquueda Binaria
int buscarPorEdad(struct persona tribunalConstitucional[], int tam, int edadBuscada) {
    int izquierda = 0;                // Índice inicial del subarray
    int derecha = tam - 1;// Índice final del subarray
    int medio;

    // Mientras el subarray tenga al menos un elemento
    while (izquierda <= derecha) {
        // Calculamos el punto medio del subarray actual
        medio = (izquierda + derecha) / 2;

        // Si encontramos la edad buscada, retornamos su posición
        if (tribunalConstitucional[medio].edad == edadBuscada) {
            return medio;
        }

        // Si la edad buscada es menor, descartamos la mitad derecha
        if (tribunalConstitucional[medio].edad > edadBuscada) {
            derecha = medio - 1;
        }
        // Si la edad buscada es mayor, descartamos la mitad izquierda
        else {
            izquierda = medio + 1;
        }
    }

    // Si llegamos aquí, la edad no fue encontrada
    return -1;
}

void agregarMinistroTribunalConstitucional(struct persona tribunalConstitucional[], struct nodoCiudadano *ciudadanos, char rut[20]) {
    struct persona *ministro = buscarCiudadanoPorRUT(ciudadanos, rut);
    int i;

    if(ministro == NULL) {
        printf("No se encontro un ciudadano con el RUT %s.\n", rut);
        return;
    }

    else if (ministro->cargo == 4) {
        printf("El ciudadano con RUT %s ya es ministro del Tribunal Constitucional.\n", rut);
        return;
    }
    else if (ministro->cargo != 0) {
        printf("El ciudadano con RUT %s ya tiene un cargo publico. No puede ser ministro del Tribunal Constitucional.\n", rut);
        return;
    }

    for (i = 0; i < 10; i++) {
        if (tribunalConstitucional[i].edad == 0) {
            strcpy(tribunalConstitucional[i].rut, ministro->rut);
            strcpy(tribunalConstitucional[i].nombre, ministro->nombre);
            tribunalConstitucional[i].edad = ministro->edad;
            strcpy(tribunalConstitucional[i].especialidad, ministro->especialidad);
            tribunalConstitucional[i].cargo = 4;
            ministro->cargo = 4;
            printf("Ministro del Tribunal Constitucional agregado correctamente.\n");
            return;
        }
    }
    printf ("No se pueden agregar más de 10 ministros del Tribunal Constitucional.\n");
}

void eliminarMinistroTribunalConstitucional(struct persona tribunalConstitucional[10], struct nodoCiudadano *ciudadanos, char rut[20]) {
    struct persona *ciudadano = buscarCiudadanoPorRUT(ciudadanos, rut);
    int i;

    if (ciudadano == NULL) {
        printf("No se encontro un ciudadano con el RUT %s.\n", rut);
        return;
    }

    for (i = 0; i < 10; i++) {
        if (strcmp(tribunalConstitucional[i].rut, rut) == 0) {
            tribunalConstitucional[i].edad = 0;
            strcpy(tribunalConstitucional[i].rut, "");
            strcpy(tribunalConstitucional[i].nombre, "");
            strcpy(tribunalConstitucional[i].especialidad, "");
            tribunalConstitucional[i].cargo = 0;
            ciudadano->cargo = 0;

            ordenarTribunalPorEdad(tribunalConstitucional, 10);


            printf("Ministro del Tribunal Constitucional eliminado correctamente.\n");
            return;
        }
    }
    printf("No se encontro un ministro del Tribunal Constitucional con el RUT %s.\n", rut);
}

void mostrarTribunalConstitucional(struct persona tribunalConstitucional[10]) {
    int i, encontrado = 0;

    for (i = 0; i < 10; i++) {
        if (tribunalConstitucional[i].edad != 0) {
            encontrado = 1;
            break;
        }
    }
    if (!encontrado) {
        printf("No hay ministros del Tribunal Constitucional registrados.\n");
        return;
    }

    for (i = 0; i < 10; i++) {
        if (tribunalConstitucional[i].edad != 0) {
            printf("\nNombre: %s\n", tribunalConstitucional[i].nombre);
            printf("Edad: %d\n", tribunalConstitucional[i].edad);
            printf("RUT: %s\n", tribunalConstitucional[i].rut);
            printf("Cargo: Ministro del Tribunal Constitucional\n");
            printf("Especialidad: %s\n\n", tribunalConstitucional[i].especialidad);
        }
    }
}

int verificarTC(struct persona tribunalConstitucional[10]) {
    int i;
    for (i = 0; i < 10; i++) {
        if (tribunalConstitucional->cargo == 0) {
            return 0; // no hay sufiicientes ministros
        }
    }
    return 1; // hay suficientes ministros
}

int realizarVotacionMinistros(struct persona tribunalConstitucional[10]) {
    int votosAFavor = 0, votosEnContra = 0;
    int i, voto;

    for (i = 0; i < 10; i++) {
        if (tribunalConstitucional[i].edad != 0) {
            printf("Ministro %s, ¿Aprueba la propuesta? (1 = Sí, Otro número = No): ", tribunalConstitucional[i].nombre);
            scanf("%d", &voto);
            if (voto == 1) {
                votosAFavor++;
            } else {
                votosEnContra++;
            }
        }
    }

    printf("Votos a favor: %d\n", votosAFavor);
    printf("Votos en contra: %d\n", votosEnContra);

    if (votosAFavor > votosEnContra) {
        return 1;  // Propuesta aprobada por el Tribunal Constitucional
    } else {
        return 0;  // Propuesta rechazada por el Tribunal Constitucional
    }
}

int controlConstitucionalidad(struct nodoBoletin *boletinEstado, struct proyecto *propuesta, struct persona tribunalConstitucional[10]) {
    struct nodoBoletin *rec = boletinEstado;
    int votacionMinistros = 0;

    while (rec != NULL) {
        if (rec->head->propuesta->id == propuesta->id) {
            printf("La propuesta ha sido publicada en el Boletin N°%d", rec->head->numeroBoletin);
            // Realizar votacion de los ministros del Tribunal Constitucional
            votacionMinistros = realizarVotacionMinistros(tribunalConstitucional);
            if (votacionMinistros) {
                printf("La propuesta ha sido aprobada por el Tribunal Constitucional.\n");
                return 1;  // Propuesta aprobada por el Tribunal Constitucional
            } else {
                printf("La propuesta ha sido rechazada por el Tribunal Constitucional.\n");
                propuesta->estado = 2; // Rechazada
                return 2;  // Propuesta rechazada por el Tribunal Constitucional
            }
        }
        rec = rec->sig;
    }
    printf("La propuesta no ha sido encontrada en el boletin oficial.\n");
    return 0;  // Propuesta no encontrada en el boletín
}



/*   FUNCIONES PARA GRAFO   */
void establecerRelacion(struct Grafo *grafo, int nodo1, int nodo2, int peso) {
    if (nodo1 < grafo->numVertices && nodo2 < grafo->numVertices) {
        grafo->matriz[nodo1][nodo2] = peso;
        grafo->matriz[nodo2][nodo1] = peso; // Si el grafo es no dirigido
    }
}

void agregarNodoGrafo(struct Grafo *grafo) {
    int nuevoTamano = grafo->numVertices + 1;
    int **nuevaMatriz = (int **)malloc(nuevoTamano * sizeof(int *));
    int i,j;

    // Redimensionar filas
    for ( i = 0; i < nuevoTamano; i++) {
        nuevaMatriz[i] = (int *)malloc(nuevoTamano * sizeof(int));
    }

    // Copiar valores antiguos y inicializar nueva fila y columna
    for (i = 0; i < nuevoTamano - 1; i++) {
        for (j = 0; j < nuevoTamano - 1; j++) {
            nuevaMatriz[i][j] = grafo->matriz[i][j];
        }
        nuevaMatriz[i][nuevoTamano - 1] = 0; // Nueva columna
    }

    for (j = 0; j < nuevoTamano; j++) {
        nuevaMatriz[nuevoTamano - 1][j] = 0; // Nueva fila
    }

    // Asignar nueva matriz al grafo
    grafo->matriz = nuevaMatriz;
    grafo->numVertices = nuevoTamano;
}

void mostrarGrafo(struct Grafo *grafo) {
    int i,j;
    if (grafo == NULL || grafo->matriz == NULL || grafo->numVertices == 0) {
        printf("El grafo está vacío.\n");
        return;
    }

    printf("Matriz de adyacencia del grafo:\n");

    // Encabezado para los nodos
    printf("   ");
    for (i = 0; i < grafo->numVertices; i++) {
        printf("%3d", i);
    }
    printf("\n");

    // Imprimir los valores de la matriz
    for (i = 0; i < grafo->numVertices; i++) {
        printf("%3d", i); // Etiqueta para la fila
        for (j = 0; j < grafo->numVertices; j++) {
            printf("%3d", grafo->matriz[i][j]);
        }
        printf("\n");
    }
}

struct Grafo *crearGrafo() {
    struct Grafo *grafo = (struct Grafo *)malloc(sizeof(struct Grafo));
    grafo->numVertices = 0; // Inicialmente no hay nodos
    grafo->matriz = NULL; // No hay matriz al principio
    return grafo;
}



/*MENUS*/
void menuAdministrar(struct ProcesoLegislativo *pais) {
    int opcion, verificarOpcion;
    while(1){
        printf("\n===== Menu Administracion =====\n");
        printf("1. Administrar Ciudadanos\n"); 
        printf("2. Administrar Diputados\n");
        printf("3. Administrar Senadores\n");
        printf("4. Administrar Presidente\n"); 
        printf("5. Administrar Proyectos\n"); 
        printf("6. Administrar Camaras o Comision Mixta\n"); 
        printf("7. Promulgacion o Veto Presidencial\n"); 
        printf("8. Administrar Boletines\n"); 
        printf("9. Administrar Tribunal Constitucional\n");
        printf("0. Salir\n");
        printf("=============================\n");
        printf("Ingrese una opcion: ");
        scanf("%d", &opcion);
        switch(opcion){
            case 0:
                printf("\nSaliendo del programa...\n");
                exit(0);
            case 1:
                administrarCiudadanos(pais);
                cls();
                printf("¿Desea realizar otra acción?\n");
                printf("1. Sí\n");
                printf("2. No\n");
                printf("Insertar: ");
                scanf("%d", &verificarOpcion);
                if (verificarOpcion == 1) {
                    /*limpiar consola y volver al menu principal*/
                    cls();
                    menuAdministrar(pais);
                }
                if (verificarOpcion == 2) {
                    printf("\nSaliendo del programa...\n");
                    exit(0);
                }
                break;
            case 2:
                

                cls();
                printf("¿Desea realizar otra acción?\n");
                printf("1. Sí\n");
                printf("2. No\n");
                printf("Insertar: ");
                scanf("%d", &verificarOpcion);
                if (verificarOpcion == 1) {
                    /*limpiar consola y volver al menu principal*/
                    cls();
                    menuAdministrar(pais);
                }
                if (verificarOpcion == 2) {
                    printf("\nSaliendo del programa...\n");
                    exit(0);
                }
                break;
            case 3:
                

                cls();
                printf("¿Desea realizar otra acción?\n");
                printf("1. Sí\n");
                printf("2. No\n");
                printf("Insertar: ");
                scanf("%d", &verificarOpcion);
                if (verificarOpcion == 1) {
                    /*limpiar consola y volver al menu principal*/
                    cls();
                    menuAdministrar(pais);
                }
                if (verificarOpcion == 2) {
                    printf("\nSaliendo del programa...\n");
                    exit(0);
                }
                break;
            case 4:
                administrarPresidente(pais);
                cls();
                printf("¿Desea realizar otra acción?\n");
                printf("1. Sí\n");
                printf("2. No\n");
                printf("Insertar: ");
                scanf("%d", &verificarOpcion);
                if (verificarOpcion == 1) {
                    /*limpiar consola y volver al menu principal*/
                    cls();
                    menuAdministrar(pais);
                }
                if (verificarOpcion == 2) {
                    printf("\nSaliendo del programa...\n");
                    exit(0);
                }
                break;
            case 5:
                administrarProyectos(pais);
                cls();
                printf("¿Desea realizar otra acción?\n");
                printf("1. Sí\n");
                printf("2. No\n");
                printf("Insertar: ");
                scanf("%d", &verificarOpcion);
                if (verificarOpcion == 1) {
                    /*limpiar consola y volver al menu principal*/
                    cls();
                    menuAdministrar(pais);
                }
                if (verificarOpcion == 2) {
                    printf("\nSaliendo del programa...\n");
                    exit(0);
                }
                break;
            case 6:
                administrarCamaras(pais);

                cls();
                printf("¿Desea realizar otra acción?\n");
                printf("1. Sí\n");
                printf("2. No\n");
                printf("Insertar: ");
                scanf("%d", &verificarOpcion);
                if (verificarOpcion == 1) {
                    /*limpiar consola y volver al menu principal*/
                    cls();
                    menuAdministrar(pais);
                }
                if (verificarOpcion == 2) {
                    printf("\nSaliendo del programa...\n");
                    exit(0);
                }
                break;
            case 7:
                // Promulgación o Veto Presidencial
                if (pais->presidente == NULL || pais->propuesta == NULL) {
                    printf("Se necesita tanto un presidente como una propuesta para proceder con la promulgacion o veto.\n");
                } else {
                    promulgacionOVetoPresidencial(pais->presidente, pais->propuesta, pais->congreso);  // Asegurarse de pasar la estructura congreso correctamente
                }
                cls();
                printf("¿Desea realizar otra acción?\n");
                printf("1. Sí\n");
                printf("2. No\n");
                printf("Insertar: ");
                scanf("%d", &verificarOpcion);
                if (verificarOpcion == 1) {
                    /*limpiar consola y volver al menu principal*/
                    cls();
                    menuAdministrar(pais);
                }
                if (verificarOpcion == 2) {
                    printf("\nSaliendo del programa...\n");
                    exit(0);
                }
                break;
            case 8:
                administrarBoletines(pais);

                cls();
                printf("¿Desea realizar otra acción?\n");
                printf("1. Sí\n");
                printf("2. No\n");
                printf("Insertar: ");
                scanf("%d", &verificarOpcion);
                if (verificarOpcion == 1) {
                    /*limpiar consola y volver al menu principal*/
                    cls();
                    menuAdministrar(pais);
                }
                if (verificarOpcion == 2) {
                    printf("\nSaliendo del programa...\n");
                    exit(0);
                }
                break;
            case 9:
                administrarTribunal(pais);

                cls();
                printf("¿Desea realizar otra acción?\n");
                printf("1. Sí\n");
                printf("2. No\n");
                printf("Insertar: ");
                scanf("%d", &verificarOpcion);
                if (verificarOpcion == 1) {
                    /*limpiar consola y volver al menu principal*/
                    cls();
                    menuAdministrar(pais);
                }
                if (verificarOpcion == 2) {
                    printf("\nSaliendo del programa...\n");
                    exit(0);
                }
                break;
            default:
                printf("OPCIÓN NO VÁLIDA... INGRESAR NUEVAMENTE");
                cls();
        }

    }
}

void administrarCiudadanos(struct ProcesoLegislativo *pais){
    int opcion, verificarOpcion;
    struct nodoCiudadano *ciudadanos = pais->ciudadanos;
    struct persona *ciudadano = (struct persona *)malloc(sizeof(struct persona));
    char rutBuscado[20];

    while(1){
        printf("\n===== Administrar Ciudadanos =====\n");
        printf("1. Agregar Ciudadano\n");
        printf("2. Mostrar Ciudadanos\n");
        printf("3. Eliminar Ciudadano\n");
        printf("4. Buscar Ciudadano por RUT\n");
        printf("5. Mostrar promedio de edad de los ciudadanos\n");
        printf("-1. Volver\n");
        printf("0. Salir\n");
        printf("==================================\n");
        printf("Ingrese una opcion: ");
        scanf("%d", &opcion);
        switch(opcion){
            case -1:
                menuAdministrar(pais);
                break;
            case 0:
                printf("SALIENDO DEL PROGRAMA...\n");
                exit(0);
            case 1:
                ciudadano = crearCiudadano();
                ciudadanos = agregarCiudadano(ciudadanos, ciudadano);
                cls();
                printf("¿Desea realizar otra acción?\n");
                printf("1. Sí\n");
                printf("2. No\n");
                printf("Insertar: ");
                scanf("%d", &verificarOpcion);
                if (verificarOpcion == 1) {
                    /*limpiar consola y volver al menu principal*/
                    cls();
                    menuAdministrar(pais);
                }
                if (verificarOpcion == 2) {
                    printf("\nSaliendo del programa...\n");
                    exit(0);
                }
                break;
            case 2:
                mostrarCiudadanos(ciudadanos);
                cls();
                printf("¿Desea realizar otra acción?\n");
                printf("1. Sí\n");
                printf("2. No\n");
                printf("Insertar: ");
                scanf("%d", &verificarOpcion);
                if (verificarOpcion == 1) {
                    /*limpiar consola y volver al menu principal*/
                    cls();
                    menuAdministrar(pais);
                }
                if (verificarOpcion == 2) {
                    printf("\nSaliendo del programa...\n");
                    exit(0);
                }
                break;
            case 3:
                printf("Ingresa el RUT del ciudadano a eliminar: ");
                fgets(rutBuscado, sizeof(rutBuscado), stdin);
                rutBuscado[strcspn(rutBuscado, "\n")] = '\0';

                eliminarCiudadano(&pais->ciudadanos,rutBuscado);
                cls();
                printf("¿Desea realizar otra acción?\n");
                printf("1. Sí\n");
                printf("2. No\n");
                printf("Insertar: ");
                scanf("%d", &verificarOpcion);
                if (verificarOpcion == 1) {
                    /*limpiar consola y volver al menu principal*/
                    cls();
                    menuAdministrar(pais);
                }
                if (verificarOpcion == 2) {
                    printf("\nSaliendo del programa...\n");
                    exit(0);
                }
                break;
            case 4:
                printf("Ingresa el RUT del ciudadano a buscar: ");
                fgets(rutBuscado, sizeof(rutBuscado), stdin);
                rutBuscado[strcspn(rutBuscado, "\n")] = '\0';

                ciudadano = buscarCiudadanoPorRUT(ciudadanos, rutBuscado);

                cls();
                printf("¿Desea realizar otra acción?\n");
                printf("1. Sí\n");
                printf("2. No\n");
                printf("Insertar: ");
                scanf("%d", &verificarOpcion);
                if (verificarOpcion == 1) {
                    /*limpiar consola y volver al menu principal*/
                    cls();
                    menuAdministrar(pais);
                }
                if (verificarOpcion == 2) {
                    printf("\nSaliendo del programa...\n");
                    exit(0);
                }
                break;

            case 5:
                mostrarPromedioEdadCiudadanos(ciudadanos);

                cls();
                printf("¿Desea realizar otra acción?\n");
                printf("1. Sí\n");
                printf("2. No\n");
                printf("Insertar: ");
                scanf("%d", &verificarOpcion);
                if (verificarOpcion == 1) {
                    /*limpiar consola y volver al menu principal*/
                    cls();
                    menuAdministrar(pais);
                }
                if (verificarOpcion == 2) {
                    printf("\nSaliendo del programa...\n");
                    exit(0);
                }
                break;
            default:
                printf("OPCIÓN NO VÁLIDA... INGRESAR NUEVAMENTE");
                cls();
        }
    }
}

void administrarDiputados(struct ProcesoLegislativo *pais){
    int opcion, verificarOpcion, verificarEliminacion;
    struct persona *personaBuscada;
    char rut[20];
    
    while(1){
        printf("\n===== Administrar Diputados =====\n");
        printf("1. Agregar Miembro\n");
        printf("2. Mostrar Miembros\n");
        printf("3. Eliminar Miembro\n");
        printf("-1. Volver\n");
        printf("0. Salir\n");
        printf("=================================\n");
        printf("Ingrese una opcion: ");
        scanf("%d", &opcion);
        switch(opcion){
            case -1:
                menuAdministrar(pais);
                break;
            case 1:
                printf("Ingresa el RUT del miembro a agregar: ");
                fgets(rut, sizeof(rut), stdin);
                rut[strcspn(rut, "\n")] = '\0';

                personaBuscada = buscarCiudadanoPorRUT(pais->ciudadanos, rut);
                if (personaBuscada != NULL){
                    insertarParlamentarioOrdenado(pais->congreso->diputados,&pais->congreso->plibreDiputados,pais->congreso->MaxDiputados, personaBuscada);
                }
                if (personaBuscada == NULL){
                    printf("No se encontró un ciudadano con el RUT %s.\n", rut);
                }
                
                cls();
                printf("¿Desea realizar otra acción?\n");
                printf("1. Sí\n");
                printf("2. No\n");
                printf("Insertar: ");
                scanf("%d", &verificarOpcion);
                if (verificarOpcion == 1) {
                    /*limpiar consola y volver al menu principal*/
                    cls();
                    menuAdministrar(pais);
                }
                if (verificarOpcion == 2) {
                    printf("\nSaliendo del programa...\n");
                    exit(0);
                }
                break;
            case 2:
                mostrarDiputados(pais->congreso);

                cls();
                printf("¿Desea realizar otra acción?\n");
                printf("1. Sí\n");
                printf("2. No\n");
                printf("Insertar: ");
                scanf("%d", &verificarOpcion);
                if (verificarOpcion == 1) {
                    /*limpiar consola y volver al menu principal*/
                    cls();
                    menuAdministrar(pais);
                }
                if (verificarOpcion == 2) {
                    printf("\nSaliendo del programa...\n");
                    exit(0);
                }
                break;
            case 3:
                printf("Ingresa el RUT del miembro a eliminar: ");
                fgets(rut, sizeof(rut), stdin);
                rut[strcspn(rut, "\n")] = '\0';

                verificarEliminacion = eliminarDiputado(pais->congreso, rut);
                if (verificarEliminacion == 1){
                    printf("El miembro con RUT %s ha sido eliminado.\n", rut);
                }
                if(verificarEliminacion == -1){
                    printf("No se encontró un miembro con el RUT %s.\n", rut);
                }
                
                cls();
                printf("¿Desea realizar otra acción?\n");
                printf("1. Sí\n");
                printf("2. No\n");
                printf("Insertar: ");
                scanf("%d", &verificarOpcion);
                if (verificarOpcion == 1) {
                    /*limpiar consola y volver al menu principal*/
                    cls();
                    menuAdministrar(pais);
                }
                if (verificarOpcion == 2) {
                    printf("\nSaliendo del programa...\n");
                    exit(0);
                }
                break;
            case 0:
                printf("SALIENDO DEL PROGRAMA...\n");
                exit(0);
            default:
                printf("OPCIÓN NO VÁLIDA... INGRESAR NUEVAMENTE");
                cls();
        }
    }
}

void administrarSenadores(struct ProcesoLegislativo *pais){
    int opcion, verificarOpcion, verificarEliminacion;
    struct persona *personaBuscada;
    char rut[20];
    
    while(1){
        printf("\n===== Administrar Senadores =====\n");
        printf("1. Agregar Miembro\n");
        printf("2. Mostrar Miembros\n");
        printf("3. Eliminar Miembro\n");
        printf("-1. Volver\n");
        printf("0. Salir\n");
        printf("=================================\n");
        printf("Ingrese una opcion: ");
        scanf("%d", &opcion);
        switch(opcion){
            case -1:
                menuAdministrar(pais);
                break;
            case 1:
                printf("Ingresa el RUT del miembro a agregar: ");
                fgets(rut, sizeof(rut), stdin);
                rut[strcspn(rut, "\n")] = '\0';

                personaBuscada = buscarCiudadanoPorRUT(pais->ciudadanos, rut);
                if (personaBuscada != NULL){
                    insertarParlamentarioOrdenado(pais->congreso->senadores,&pais->congreso->plibreSenadores,pais->congreso->MaxSenadores, personaBuscada);
                }
                if (personaBuscada == NULL){
                    printf("No se encontró un ciudadano con el RUT %s.\n", rut);
                }

                
                cls();
                printf("¿Desea realizar otra acción?\n");
                printf("1. Sí\n");
                printf("2. No\n");
                printf("Insertar: ");
                scanf("%d", &verificarOpcion);
                if (verificarOpcion == 1) {
                    /*limpiar consola y volver al menu principal*/
                    cls();
                    menuAdministrar(pais);
                }
                if (verificarOpcion == 2) {
                    printf("\nSaliendo del programa...\n");
                    exit(0);
                }
                break;
            case 2:
                mostrarSenadores(pais->congreso);

                cls();
                printf("¿Desea realizar otra acción?\n");
                printf("1. Sí\n");
                printf("2. No\n");
                printf("Insertar: ");
                scanf("%d", &verificarOpcion);
                if (verificarOpcion == 1) {
                    /*limpiar consola y volver al menu principal*/
                    cls();
                    menuAdministrar(pais);
                }
                if (verificarOpcion == 2) {
                    printf("\nSaliendo del programa...\n");
                    exit(0);
                }
                break;
            case 3:
                printf("Ingresa el RUT del miembro a eliminar: ");
                fgets(rut, sizeof(rut), stdin);
                rut[strcspn(rut, "\n")] = '\0';

                verificarEliminacion = eliminarSenador(pais->congreso, rut);
                if (verificarEliminacion == 1){
                    printf("El miembro con RUT %s ha sido eliminado.\n", rut);
                }
                if(verificarEliminacion == -1){
                    printf("No se encontró un miembro con el RUT %s.\n", rut);
                }

                cls();
                printf("¿Desea realizar otra acción?\n");
                printf("1. Sí\n");
                printf("2. No\n");
                printf("Insertar: ");
                scanf("%d", &verificarOpcion);
                if (verificarOpcion == 1) {
                    /*limpiar consola y volver al menu principal*/
                    cls();
                    menuAdministrar(pais);
                }
                if (verificarOpcion == 2) {
                    printf("\nSaliendo del programa...\n");
                    exit(0);
                }
                break;
            case 0:
                printf("SALIENDO DEL PROGRAMA...\n");
                exit(0);
            default:
                printf("OPCIÓN NO VÁLIDA... INGRESAR NUEVAMENTE");
                cls();
        }
    }
}

void administrarPresidente(struct ProcesoLegislativo *pais){
    int opcion, verificarOpcion;
    char rut[20];
    struct persona *personaPresidente = NULL;

    while(1){
        printf("\n===== Administrar Presidente =====\n");
        printf("1. Agregar Presidente\n");
        printf("2. Mostrar Presidente\n");
        printf("-1. Volver\n");
        printf("0. Salir\n");
        printf("==================================\n");
        printf("Ingrese una opcion: ");
        scanf("%d", &opcion);
        switch(opcion){
            case -1:
                menuAdministrar(pais);
                break;
            case 0:
                printf("SALIENDO DEL PROGRAMA...\n");
                exit(0);
            case 1:
                // Agregar Presidente
                printf("Ingresa el RUT del presidente: ");
                fgets(rut, sizeof(rut), stdin);
                rut[strcspn(rut, "\n")] = '\0';
                /*holaamigos de youtube arreglar*/
                personaPresidente = buscarCiudadanoPorRUT(pais->ciudadanos, rut);
                if (personaPresidente == NULL) {
                    printf("El ciudadano con RUT %s no existe.\n", rut);
                } else {
                    pais->presidente = crearPresidente(personaPresidente);  // Asignamos al presidente
                }

                cls();
                printf("¿Desea realizar otra acción?\n");
                printf("1. Sí\n");
                printf("2. No\n");
                printf("Insertar: ");
                scanf("%d", &verificarOpcion);
                if (verificarOpcion == 1) {
                    /*limpiar consola y volver al menu principal*/
                    cls();
                    menuAdministrar(pais);
                }
                if (verificarOpcion == 2) {
                    printf("\nSaliendo del programa...\n");
                    exit(0);
                }
                break;
            case 2:
                mostrarPresidente(pais->presidente);

                cls();
                printf("¿Desea realizar otra acción?\n");
                printf("1. Sí\n");
                printf("2. No\n");
                printf("Insertar: ");
                scanf("%d", &verificarOpcion);
                if (verificarOpcion == 1) {
                    /*limpiar consola y volver al menu principal*/
                    cls();
                    menuAdministrar(pais);
                }
                if (verificarOpcion == 2) {
                    printf("\nSaliendo del programa...\n");
                    exit(0);
                }
                break;
            default:
                printf("OPCIÓN NO VÁLIDA... INGRESAR NUEVAMENTE");
                cls();
        }
    }
}

void administrarProyectos(struct ProcesoLegislativo *pais){
    int opcion, verificarOpcion, idPropuesta;
    struct proyecto *propuestaEncontrada = NULL;

    while(1){
        printf("\n===== Administrar Proyectos =====\n");
        printf("1. Crear Proyecto\n");
        printf("2. Mostrar Proyecto por ID\n");
        printf("3. Mostrar Todos las Proyectos\n");
        printf("4. Mostrar Grafo Proyectos por Urgencia\n");
        printf("-1. Volver\n");
        printf("0. Salir\n");
        printf("=================================\n");
        printf("Ingrese una opcion: ");
        scanf("%d", &opcion);
        switch(opcion){
            case -1:
                menuAdministrar(pais);
                break;
            case 0:
                printf("SALIENDO DEL PROGRAMA...\n");
                exit(0);
            case 1:
                // Crear Propuesta y agregarla al ABB
                if (pais->presidente == NULL) {
                    printf("Primero debes agregar un presidente para asignar una propuesta.\n");
                } else {
                    pais->propuesta = crearPropuesta(pais, pais->presidente->persona);
                }

                cls();
                printf("¿Desea realizar otra acción?\n");
                printf("1. Sí\n");
                printf("2. No\n");
                printf("Insertar: ");
                scanf("%d", &verificarOpcion);
                if (verificarOpcion == 1) {
                    /*limpiar consola y volver al menu principal*/
                    cls();
                    menuAdministrar(pais);
                }
                if (verificarOpcion == 2) {
                    printf("\nSaliendo del programa...\n");
                    exit(0);
                }
                break;
            case 2:
                // Mostrar Propuesta por ID
                printf("Ingresa el ID de la propuesta a buscar: ");
                scanf("%d", &idPropuesta);
                limpiarBuffer();

                propuestaEncontrada = buscarPropuesta(pais->propuesta, idPropuesta);
                mostrarPropuesta(propuestaEncontrada);  // Esta función ya maneja el caso si la propuesta es NULL

                cls();
                printf("¿Desea realizar otra acción?\n");
                printf("1. Sí\n");
                printf("2. No\n");
                printf("Insertar: ");
                scanf("%d", &verificarOpcion);
                if (verificarOpcion == 1) {
                    /*limpiar consola y volver al menu principal*/
                    cls();
                    menuAdministrar(pais);
                }
                if (verificarOpcion == 2) {
                    printf("\nSaliendo del programa...\n");
                    exit(0);
                }
                break;
            case 3:
                // Mostrar todas las propuestas
                mostrarPropuestas(pais->propuesta);

                cls();
                printf("¿Desea realizar otra acción?\n");
                printf("1. Sí\n");
                printf("2. No\n");
                printf("Insertar: ");
                scanf("%d", &verificarOpcion);
                if (verificarOpcion == 1) {
                    /*limpiar consola y volver al menu principal*/
                    cls();
                    menuAdministrar(pais);
                }
                if (verificarOpcion == 2) {
                    printf("\nSaliendo del programa...\n");
                    exit(0);
                }
                break;
            case 4:
                mostrarGrafo(pais->grafoProyectos);

                cls();
                printf("¿Desea realizar otra acción?\n");
                printf("1. Sí\n");
                printf("2. No\n");
                printf("Insertar: ");
                scanf("%d", &verificarOpcion);
                if (verificarOpcion == 1) {
                    /*limpiar consola y volver al menu principal*/
                    cls();
                    menuAdministrar(pais);
                }
                if (verificarOpcion == 2) {
                    printf("\nSaliendo del programa...\n");
                    exit(0);
                }
                break;
            default:
                printf("OPCIÓN NO VÁLIDA... INGRESAR NUEVAMENTE");
                cls();
        }
    }
}

void administrarCamaras(struct ProcesoLegislativo *pais){
    int opcion, verificarOpcion;

    while(1){
        printf("\n===== Administrar Camaras o Comision Mixta =====\n");
        printf("1. Iniciar Camara de Origen\n");
        printf("2. Iniciar Camara Revisora\n");
        printf("3. Comision Mixta\n");
        printf("-1. Volver\n");
        printf("0. Salir\n");
        printf("================================================\n");
        printf("Ingrese una opcion: ");
        scanf("%d", &opcion);
        switch(opcion){
            case -1:
                menuAdministrar(pais);
                break;
            case 0:
                printf("SALIENDO DEL PROGRAMA...\n");
                exit(0);
            case 1:
                // Iniciar Cámara de Origen
                if (pais->propuesta == NULL) {
                    printf("Primero debes crear una propuesta para iniciar la Camara de Origen.\n");
                } else {
                    camaraDeOrigen(pais->propuesta, pais->congreso);  // Asegurarse de pasar la estructura congreso correctamente
                }

                cls();
                printf("¿Desea realizar otra acción?\n");
                printf("1. Sí\n");
                printf("2. No\n");
                printf("Insertar: ");
                scanf("%d", &verificarOpcion);
                if (verificarOpcion == 1) {
                    /*limpiar consola y volver al menu principal*/
                    cls();
                    menuAdministrar(pais);
                }
                if (verificarOpcion == 2) {
                    printf("\nSaliendo del programa...\n");
                    exit(0);
                }
                break;
            case 2:
                // Iniciar Cámara Revisora
                if (pais->propuesta == NULL) {
                    printf("Primero debes crear una propuesta para iniciar la Camara Revisora.\n");
                } else {
                    camaraRevisora(pais->propuesta, pais->congreso);  // Asegurarse de pasar la estructura congreso correctamente
                }

                cls();
                printf("¿Desea realizar otra acción?\n");
                printf("1. Sí\n");
                printf("2. No\n");
                printf("Insertar: ");
                scanf("%d", &verificarOpcion);
                if (verificarOpcion == 1) {
                    /*limpiar consola y volver al menu principal*/
                    cls();
                    menuAdministrar(pais);
                }
                if (verificarOpcion == 2) {
                    printf("\nSaliendo del programa...\n");
                    exit(0);
                }
                break;
            case 3:
                // Comisión Mixta
                if (pais->propuesta == NULL) {
                    printf("Primero debes crear una propuesta para enviar a la Comision Mixta.\n");
                } else {
                    comisionMixta(pais->propuesta, pais->congreso);  // Asegurarse de pasar la estructura congreso correctamente
                }

                cls();
                printf("¿Desea realizar otra acción?\n");
                printf("1. Sí\n");
                printf("2. No\n");
                printf("Insertar: ");
                scanf("%d", &verificarOpcion);
                if (verificarOpcion == 1) {
                    /*limpiar consola y volver al menu principal*/
                    cls();
                    menuAdministrar(pais);
                }
                if (verificarOpcion == 2) {
                    printf("\nSaliendo del programa...\n");
                    exit(0);
                }
                break;
            default:
                printf("OPCIÓN NO VÁLIDA... INGRESAR NUEVAMENTE");
                cls();
        }

    }
}
    
void administrarBoletines(struct ProcesoLegislativo *pais){
    int opcion, verificarOpcion;
    int numeroBoletin;
    int idPropuesta;

    struct proyecto *propuesta = NULL;
    
    while(1){
        printf("\n===== Administrar Boletines =====\n");
        printf("1. Publicar Ley en Boletin y Establecer Vigencia\n");
        printf("2. Eliminar Ley de Boletin\n");
        printf("-1. Volver\n");
        printf("0. Salir\n");
        printf("==================================\n");
        printf("Ingrese una opcion: ");
        scanf("%d", &opcion);
        switch(opcion){
            case -1:
                menuAdministrar(pais);
                break;
            case 0:
                printf("SALIENDO DEL PROGRAMA...\n");
                exit(0);
            case 1:
                // Publicar Ley en Boletín y Establecer Vigencia

                printf("Ingresa el ID de la propuesta a publicar: ");
                scanf("%d", &idPropuesta);
                limpiarBuffer();  // Limpiar el buffer

                propuesta = buscarPropuesta(pais->propuesta, idPropuesta);
                if (propuesta == NULL) {
                    printf("Propuesta con ID %d no encontrada.\n", idPropuesta);
                } else {
                    pais->boletinEstado = publicarLeyEnBoletin(pais->boletinEstado, propuesta);
                }

                cls();
                printf("¿Desea realizar otra acción?\n");
                printf("1. Sí\n");
                printf("2. No\n");
                printf("Insertar: ");
                scanf("%d", &verificarOpcion);
                if (verificarOpcion == 1) {
                    /*limpiar consola y volver al menu principal*/
                    cls();
                    menuAdministrar(pais);
                }
                if (verificarOpcion == 2) {
                    printf("\nSaliendo del programa...\n");
                    exit(0);
                }
                break;
            case 2:
                printf("Ingresa el numero de boletin a eliminar: ");
                scanf("%d", &numeroBoletin);
                pais->boletinEstado = eliminarLeyDeBoletin(pais->boletinEstado, numeroBoletin);

                cls();
                printf("¿Desea realizar otra acción?\n");
                printf("1. Sí\n");
                printf("2. No\n");
                printf("Insertar: ");
                scanf("%d", &verificarOpcion);
                if (verificarOpcion == 1) {
                    /*limpiar consola y volver al menu principal*/
                    cls();
                    menuAdministrar(pais);
                }
                if (verificarOpcion == 2) {
                    printf("\nSaliendo del programa...\n");
                    exit(0);
                }
                break;
            default:
                printf("OPCIÓN NO VÁLIDA... INGRESAR NUEVAMENTE");
                cls();
        }
    }
}

void administrarTribunal(struct ProcesoLegislativo *pais){
    int opcion, verificarOpcion;
    int hayMinistros;
    int esConstitucional;
    int idPropuesta;

    struct proyecto *propuesta = NULL;
    char rut[20];
    
    while(1){
        printf("\n===== Administrar Tribunal =====\n");
        printf("1. Agregar Ministro a Tribunal Constitucional\n");
        printf("2. Eliminar Ministro del Tribunal Constitucional\n");
        printf("3. Mostrar Ministros del Tribunal Constitucional\n");
        printf("4. Realizar Control de Constitucionalidad a un Proyecto\n");
        printf("5. Mostrar porcentaje de proyectos aprobadados por el Tribunal Constitucional\n");
        printf("-1. Volver\n");
        printf("0. Salir\n");
        printf("==================================\n");
        printf("Ingrese una opcion: ");
        scanf("%d", &opcion);
        switch(opcion){
            case -1:
                menuAdministrar(pais);
                break;
            case 0:
                printf("SALIENDO DEL PROGRAMA...\n");
                exit(0);
            case 1:
                // Agregar Ministro a Tribunal Constitucional
                printf("Ingresa el RUT del ciudadano a agregar como ministro del tribunal constitucional: ");
                fgets(rut, sizeof(rut), stdin);
                rut[strcspn(rut, "\n")] = '\0';
                agregarMinistroTribunalConstitucional(pais->tribunalConstitucional, pais->ciudadanos, rut);

                cls();
                printf("¿Desea realizar otra acción?\n");
                printf("1. Sí\n");
                printf("2. No\n");
                printf("Insertar: ");
                scanf("%d", &verificarOpcion);
                if (verificarOpcion == 1) {
                    /*limpiar consola y volver al menu principal*/
                    cls();
                    menuAdministrar(pais);
                }
                if (verificarOpcion == 2) {
                    printf("\nSaliendo del programa...\n");
                    exit(0);
                }
                break;
            case 2:
                // Eliminar Ministro del Tribunal Constitucional
                printf("Ingresa el RUT del ministro a eliminar del tribunal constitucional: ");
                fgets(rut, sizeof(rut), stdin);
                rut[strcspn(rut, "\n")] = '\0';
                eliminarMinistroTribunalConstitucional(pais->tribunalConstitucional, pais->ciudadanos, rut);

                cls();
                printf("¿Desea realizar otra acción?\n");
                printf("1. Sí\n");
                printf("2. No\n");
                printf("Insertar: ");
                scanf("%d", &verificarOpcion);
                if (verificarOpcion == 1) {
                    /*limpiar consola y volver al menu principal*/
                    cls();
                    menuAdministrar(pais);
                }
                if (verificarOpcion == 2) {
                    printf("\nSaliendo del programa...\n");
                    exit(0);
                }
                break;
            case 3:
                // Mostrar Ministros del Tribunal Constitucional
                mostrarTribunalConstitucional(pais->tribunalConstitucional);

                cls();
                printf("¿Desea realizar otra acción?\n");
                printf("1. Sí\n");
                printf("2. No\n");
                printf("Insertar: ");
                scanf("%d", &verificarOpcion);
                if (verificarOpcion == 1) {
                    /*limpiar consola y volver al menu principal*/
                    cls();
                    menuAdministrar(pais);
                }
                if (verificarOpcion == 2) {
                    printf("\nSaliendo del programa...\n");
                    exit(0);
                }
                break;
            case 4:
                // Control de Constitucionalidad
                hayMinistros = verificarTC(pais->tribunalConstitucional);

                if (hayMinistros == 0) {
                    printf("No hay suficientes ministros en el tribunal constitucional para realizar el control de constitucionalidad.\n");
                } else { // si alguien modulariza esto seria un golazo
                    printf("Ingresa el ID de la propuesta a verificar en el boletin: ");
                    scanf("%d", &idPropuesta);
                    limpiarBuffer();

                    propuesta = buscarPropuesta(pais->propuesta, idPropuesta);
                    if (propuesta == NULL) {
                        printf("Propuesta con ID %d no encontrada.\n", idPropuesta);
                    } else {
                        esConstitucional = controlConstitucionalidad(pais->boletinEstado, propuesta, pais->tribunalConstitucional);
                        if (esConstitucional == 0) {
                            printf("La propuesta '%s' aun no se ha publicado en el boletin del estado.\n", propuesta->tema);
                        } else if (esConstitucional == 2) {
                            printf("La propuesta '%s' no es constitucional. ", propuesta->tema);
                            eliminarLeyDeBoletin(pais->boletinEstado, propuesta->id);
                        } else {
                            printf("La propuesta '%s' es constitucional y se mantiene en el boletin del estado\n", propuesta->tema);
                        }
                    }
                }

                cls();
                printf("¿Desea realizar otra acción?\n");
                printf("1. Sí\n");
                printf("2. No\n");
                printf("Insertar: ");
                scanf("%d", &verificarOpcion);
                if (verificarOpcion == 1) {
                    /*limpiar consola y volver al menu principal*/
                    cls();
                    menuAdministrar(pais);
                }
                if (verificarOpcion == 2) {
                    printf("\nSaliendo del programa...\n");
                    exit(0);
                }
                break;
            case 5:
                // Mostrar porcentaje de proyectos aprobados por el Tribunal Constitucional
                mostrarPorcentajeProyectosAprobados(pais->propuesta);

                cls();
                printf("¿Desea realizar otra acción?\n");
                printf("1. Sí\n");
                printf("2. No\n");
                printf("Insertar: ");
                scanf("%d", &verificarOpcion);
                if (verificarOpcion == 1) {
                    /*limpiar consola y volver al menu principal*/
                    cls();
                    menuAdministrar(pais);
                }
                if (verificarOpcion == 2) {
                    printf("\nSaliendo del programa...\n");
                    exit(0);
                }
                break;
            default:
                printf("OPCIÓN NO VÁLIDA... INGRESAR NUEVAMENTE");
                cls();
        }
    }
}


int main() {
    struct ProcesoLegislativo *procesoLegislativo;
    struct persona *personaPresidente = NULL;
    struct proyecto *propuestaEncontrada = NULL;
    struct proyecto *propuesta = NULL;

    procesoLegislativo = (struct ProcesoLegislativo *)malloc(sizeof(struct ProcesoLegislativo));

    procesoLegislativo->congreso = NULL;
    procesoLegislativo->propuesta = NULL; // arbol de propuestas
    procesoLegislativo->ciudadanos = NULL;
    procesoLegislativo->presidente = NULL;
    procesoLegislativo->boletinEstado = NULL; // lista de boletines
    procesoLegislativo->grafoProyectos = crearGrafo();

    // Inicializa el congreso y le asigna memoria, si falla retorna 1
    procesoLegislativo->congreso = (struct congreso *)malloc(sizeof(struct congreso));
    if (procesoLegislativo->congreso == NULL) {
        printf("Error al asignar memoria para la estructura congreso.\n");
        return 1;
    }

    procesoLegislativo->congreso->diputados = NULL;  // Inicializando en NULL para evitar acceso a memoria no válida
    procesoLegislativo->congreso->senadores = NULL;

    menuAdministrar(procesoLegislativo);


    return 0;
}
