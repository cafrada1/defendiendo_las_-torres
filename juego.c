#include "juego.h"
#include "utiles.h"

const int INICIAL = 0;

const int ENEMIGOS_ESTE = 100;
const int ENEMIGOS_OESTE = 200;
const int ENEMIGOS_NORTE = 150;
const int ENEMIGOS_SUR = 250;

const int JUGANDO = 0;
const int GANADOR = 1;
const int PERDEDOR = -1;

const int EXITOSO = 0;

const int ENANOS_ESTE = 5;
const int ELFOS_ESTE = 0;

const int ENANOS_OESTE = 0;
const int ELFOS_OESTE = 5;

const int ENANOS_NORTE = 3;
const int ELFOS_NORTE = 3;

const int ENANOS_SUR = 4;
const int ELFOS_SUR = 4;

const int TOPE_UN_CAMINO = 14;
const int TOPE_DOS_CAMINOS = 19;

const int REFUERZOS_OESTE = 50;
const int REFUERZOS_DOS_CAMINOS = 25;
const int REFUERZOS_ESTE = 25;

const bool VALIDO = true;
const bool NO_VALIDO = false;


const char SI = 'S';


const int CAMINO_1 = 1;
const int CAMINO_2 = 2;

const int VIDA_BASE_TORRE = 600;

const int COSTO_ELFO_TORRE_2 = 50;
const int COSTO_ENANO_TORRE_1 = 50;
const int COSTO_ELFO_TORRE_1 = 0;
const int COSTO_ENANO_TORRE_2 = 0;

const int CANTIDAD_ENANOS_EXTRA = 10;
const int CANTIDAD_ELFOS_EXTRA = 10;


const char MALO = 'M';
const char REGULAR = 'R';
const char BUENO = 'B';
const int PROBILIDAD_LETAL_MALO = 0;
const int PROBILIDAD_LETAL_REGULAR = 10;
const int PROBILIDAD_LETAL_BUENO = 25;


/*
* Recibe:
*	 animo: un char con el estado de animo del personaje. Debe ser M-R-B	 
* Devuelve:
*	 la probabilidad de critico como un entero
*/
int probabilidad_letal(char estado_animo) {
    int probabilidad;

    if (estado_animo == MALO) {
        probabilidad = PROBILIDAD_LETAL_MALO;
    }
    if (estado_animo == REGULAR) {
        probabilidad = PROBILIDAD_LETAL_REGULAR;
    } else if (estado_animo == BUENO) {
        probabilidad = PROBILIDAD_LETAL_BUENO;
    }
    return probabilidad;
}

/*
* Recibe:
*	 factor: entero entre 0 y 200	 
* Devuelve:
*	 probabilidad de fallo como un entero
*/
int probabilidad_fallo_ataque(int factor) {
    int probabilidad;

    probabilidad = factor / 2;

    return probabilidad;
}

/*
*Recibe:
*	 *nivel: puntero a la estructura nivel del juego
*	 nivel_actual: entero del nivel en el que se encuentra. Debe estar entre 1 y 4
*	 camino_niveles: contiene todos los caminos de los niveles
*Funcionamiento:
*	 asigna al nivel los caminos 1 y 2 con sus respectivos topes
*/
void inicia_caminos(nivel_t *nivel, camino_niveles_t caminos_niveles, int nivel_actual) {

    for (int i = 0; i < caminos_niveles.tope_caminos[nivel_actual - 1][0]; i++) {

        nivel->camino_1[i].fil = caminos_niveles.caminos[nivel_actual - 1][0][i].fil;
        nivel->camino_1[i].col = caminos_niveles.caminos[nivel_actual - 1][0][i].col;
    }
    nivel->tope_camino_1 = caminos_niveles.tope_caminos[nivel_actual - 1][0];

    for (int i = 0; i < caminos_niveles.tope_caminos[nivel_actual - 1][1]; i++) {

        nivel->camino_2[i].fil = caminos_niveles.caminos[nivel_actual - 1][1][i].fil;
        nivel->camino_2[i].col = caminos_niveles.caminos[nivel_actual - 1][1][i].col;
    }
    nivel->tope_camino_2 = caminos_niveles.tope_caminos[nivel_actual - 1][1];
}

/*
*Funcionamiento:
*	asigna al juego los valores y estructuras iniciales de cada nivel
*/
void inicia_nivel(juego_t *juego, camino_niveles_t caminos_niveles) {

    if (juego->nivel_actual == NIVEL_ESTE) {

        juego->nivel.max_enemigos_nivel = ENEMIGOS_ESTE;
    } else if (juego->nivel_actual == NIVEL_OESTE) {

        juego->nivel.max_enemigos_nivel = ENEMIGOS_OESTE;
    } else if (juego->nivel_actual == NIVEL_NORTE) {

        juego->nivel.max_enemigos_nivel = ENEMIGOS_NORTE;
    } else if (juego->nivel_actual == NIVEL_SUR) {

        juego->nivel.max_enemigos_nivel = ENEMIGOS_SUR;
    }

    inicia_caminos(&juego->nivel, caminos_niveles, juego->nivel_actual);

    juego->nivel.tope_defensores = INICIAL;
    juego->nivel.tope_enemigos = INICIAL;
}

/*
*Recibe:
*	 nivel_actual: entero del nivel en el que se encuentra. Debe estar entre 1 y 4
*Devuelve:
*	 entero con el largo del tablero
*/
int asignar_tope(int nivel_actual) {
    int tope;

    if (nivel_actual == NIVEL_ESTE || nivel_actual == NIVEL_OESTE) {
        tope = TOPE_UN_CAMINO;
    } else {
        tope = TOPE_DOS_CAMINOS;
    }

    return tope;
}

/*
*Recibe:
*	 *nivel: puntero a la estructura nivel del juego
*	 personaje: char del tipo de defensor a agregar
*	 nivel_actual: entero del nivel en el que se encuentra. Debe estar entre 1 y 4
*Funcionamiento:
*	 Pide al usuario las coordenadas del defensor en el tablero
*	 hasta que ingrese coordenadas validas.
*	 Coloca el defensor en dichas coordenadas
*/
void coloca_manual(nivel_t *nivel, char personaje, int nivel_actual) {
    int fila;
    int columna;
    int tope;
    int correcto;
    coordenada_t posicion_defensor;

    tope = asignar_tope(nivel_actual);

    if (personaje == ENANO) {
        printf("Elija la ubicacion del enano\n");
    } else {
        printf("Elija la ubicacion del elfo\n");
    }

    printf("Ingrese la fila: ");
    scanf("%i", &fila);
    printf("Ingrese la columna: ");
    scanf("%i", &columna);

    posicion_defensor.fil = fila - 1;
    posicion_defensor.col = columna - 1;

    correcto = agregar_defensor(nivel, posicion_defensor, personaje);

    while (correcto != EXITOSO || fila > tope + 1 || columna <= INICIAL || columna > tope + 1 || fila <= INICIAL) {
        printf("Ingreso una posicion no valida\n");

        printf("Ingrese la fila (%i-%i): ", INICIAL + 1, tope + 1);
        scanf("%i", &fila);

        printf("Ingrese la columna(%i-%i): ", INICIAL + 1, tope + 1);
        scanf("%i", &columna);

        posicion_defensor.fil = fila - 1;
        posicion_defensor.col = columna - 1;

        correcto = agregar_defensor(nivel, posicion_defensor, personaje);
    }
}

/*
* Funcionamiento: asigna los valores por default de enanos y elfos iniciales
* y la cantidad de enemigos que deben pasar para poder asignar extras
*/
void valores_defensores_default(int nivel_actual, int *enanos, int *elfos, int *refuerzos) {
    if (nivel_actual == NIVEL_ESTE) {
        *enanos = ENANOS_ESTE;
        *elfos = ELFOS_ESTE;
        *refuerzos = REFUERZOS_ESTE;
    } else if (nivel_actual == NIVEL_OESTE) {
        *enanos = ENANOS_OESTE;
        *elfos = ELFOS_OESTE;
        *refuerzos = REFUERZOS_OESTE;
    } else if (nivel_actual == NIVEL_NORTE) {
        *enanos = ENANOS_NORTE;
        *elfos = ELFOS_NORTE;
        *refuerzos = REFUERZOS_DOS_CAMINOS;
    } else if (nivel_actual == NIVEL_SUR) {
        *enanos = ENANOS_SUR;
        *elfos = ELFOS_SUR;
        *refuerzos = REFUERZOS_DOS_CAMINOS;
    }
}

/*
*Recibe:
*	 nivel_actual: entero del nivel en el que se encuentra. Debe estar entre 1 y 4
*	configuracion: configuracion del juego
*	*enanos: puntero a entero con la cantidad de enanos a ingresar
* 	*elfos: puntero a entero con la cantidad de elfos a ingresar
*	*refuerzos: puntero al entero que establece la cantidad de turnos antes
*	 	de ingresar un refuerzo 
*Funcionamiento:
*	 Establece la cantidad de enanos y elfos de la configuracion si esta esta definida
*	sino agrega por default y reemplaza los valores en configuracion
*/
void defensores_iniciales(int nivel_actual, configuracion_t *configuracion, int *enanos, int *elfos, int *refuerzos) {

    valores_defensores_default(nivel_actual, enanos, elfos, refuerzos);

    if (configuracion->enanos_inicio[nivel_actual - 1] != NO_INGRESADO) {
        *enanos = configuracion->enanos_inicio[nivel_actual - 1];
    } else {
        configuracion->enanos_inicio[nivel_actual - 1] = *enanos;
    }
    if (configuracion->elfos_inicio[nivel_actual - 1] != NO_INGRESADO) {
        *elfos = configuracion->elfos_inicio[nivel_actual - 1];
    } else {
        configuracion->elfos_inicio[nivel_actual - 1] = *elfos;
    }
}

/*
*Recibe:
*	 *juego: puntero a la estructura del juego actualizada
*	*configuracion: configuracion del juego
*	*refuerzos: puntero al entero que establece la cantidad de turnos antes
*	 	de ingresar un refuerzo
*Funcionamiento: 
*	 Inicializa la cantidad de defensores correspondientes a cada nivel pidiendo al
*	 usuario que asigne sus coordenadas
*/
void defensores_manual(juego_t *juego, configuracion_t *configuracion, int *refuerzos) {
    int enanos_iniciales;
    int elfos_iniciales;

    defensores_iniciales(juego->nivel_actual, configuracion, &enanos_iniciales, &elfos_iniciales, refuerzos);

    for (int i = INICIAL; i < enanos_iniciales; i++) {
        mostrar_juego(*juego);
        printf("Enanos %i/%i colocados\n", i, enanos_iniciales);
        coloca_manual(&juego->nivel, ENANO, juego->nivel_actual);
    }

    for (int j = INICIAL; j < elfos_iniciales; j++) {
        mostrar_juego(*juego);
        printf("Elfos %i/%i colocados\n", j, elfos_iniciales);
        coloca_manual(&juego->nivel, ELFO, juego->nivel_actual);
    }
}

/*
* Funcionamiento:
*	pregunta al usuario que tipo de personaje quiere agregar
*	Valores de personajes validos. G o L
*/
void elegir_tipo(char *personaje) {

    printf("Ingrese el defensor extra a agregar\nG para enano\nL para elfo\nopcion: ");
    scanf(" %c", personaje);

    while (*personaje != ENANO && *personaje != ELFO) {
        printf("Ingreso no valido\n");
        printf("Ingrese el defensor extra a agregar\nG para enano\nL para elfo\nopcion: ");
        scanf(" %c", personaje);
    }
}

/*
* Funcionamiento:
*	Determina si las torres admiten un defensor extra revisando
*	su resistencia con el costo del defensor y su contador de defensores extra
*/
void verificar_extra(juego_t juego, configuracion_t configuracion, bool *extra_enano, bool *extra_elfo) {

    *extra_enano = NO_VALIDO;
    *extra_elfo = NO_VALIDO;

    if (juego.torres.resistencia_torre_1 > configuracion.enanos_extras[1] &&
        juego.torres.resistencia_torre_2 > configuracion.enanos_extras[2] && juego.torres.enanos_extra > INICIAL) {
        *extra_enano = VALIDO;
    }
    if (juego.torres.resistencia_torre_1 > configuracion.elfos_extras[1] &&
        juego.torres.resistencia_torre_2 > configuracion.elfos_extras[2] && juego.torres.elfos_extra > INICIAL) {
        *extra_elfo = VALIDO;
    }
}

/*
*Funcionamiento:
*	Determina que tipo de defensor puede agregarse segun el nivel
*	Descuenta el defensor del contador de la torre y pide
*	a usuario que ingrese sus coordenadas.
*	Si pueden agregarse ambos se le pregunta al usuario cual quiere	
*/
void defensor_extra(juego_t *juego, configuracion_t configuracion, bool enanos_extra, bool elfos_extra) {
    int nivel_actual;
    char personaje;

    nivel_actual = juego->nivel_actual;

    if (nivel_actual == NIVEL_ESTE) {
        printf("Solo puede agregar enanos\n");

        juego->torres.resistencia_torre_1 -= configuracion.enanos_extras[1];
        juego->torres.resistencia_torre_2 -= configuracion.enanos_extras[2];
        juego->torres.enanos_extra--;

        coloca_manual(&juego->nivel, ENANO, juego->nivel_actual);
    } else if (nivel_actual == NIVEL_OESTE) {
        printf("Solo puede agregar elfos\n");

        juego->torres.resistencia_torre_1 -= configuracion.elfos_extras[1];
        juego->torres.resistencia_torre_2 -= configuracion.elfos_extras[2];
        juego->torres.elfos_extra--;

        coloca_manual(&juego->nivel, ELFO, juego->nivel_actual);
    } else {
        if (enanos_extra == VALIDO && elfos_extra == VALIDO) {
            elegir_tipo(&personaje);
        } else if (enanos_extra == VALIDO) {
            printf("Solo puede agregar enanos\n");
            personaje = ENANO;
        } else {
            personaje = ELFO;
            printf("Solo puede agregar elfos\n");
        }
        if (personaje == ENANO) {
            juego->torres.resistencia_torre_1 -= configuracion.enanos_extras[1];
            juego->torres.resistencia_torre_2 -= configuracion.enanos_extras[2];
            juego->torres.enanos_extra--;

            coloca_manual(&juego->nivel, ENANO, juego->nivel_actual);
        } else {
            juego->torres.resistencia_torre_1 -= configuracion.elfos_extras[1];
            juego->torres.resistencia_torre_2 -= configuracion.elfos_extras[2];
            juego->torres.elfos_extra--;
            coloca_manual(&juego->nivel, ELFO, juego->nivel_actual);
        }
    }
}

/*
*Funcionamiento:
*	pregunta al usuario si desea agregar un defensor solo si este puede
*	ser agregado
*/
void preguntar_defensor_extra(juego_t *juego, configuracion_t configuracion) {
    char ingreso;
    bool preguntar;

    bool elfos_extra;

    bool enanos_extra;

    preguntar = NO_VALIDO;

    verificar_extra(*juego, configuracion, &enanos_extra, &elfos_extra);

    if (juego->nivel_actual == NIVEL_ESTE && enanos_extra == VALIDO) {
        preguntar = VALIDO;
    } else if (juego->nivel_actual == NIVEL_OESTE && elfos_extra == VALIDO) {
        preguntar = VALIDO;
    } else if (enanos_extra == VALIDO || elfos_extra == VALIDO) {
        preguntar = VALIDO;
    }

    if (preguntar == VALIDO) {
        printf("¿Desea agregar un defensor extra?\nS para si\nCualquier otra tecla para no\nopcion: ");
        scanf(" %c", &ingreso);

        if (ingreso == SI) {
            defensor_extra(juego, configuracion, enanos_extra, elfos_extra);
        }
    }
}

/*
* Funcionamiento:
*	muestra la informacion de los personajes al inicio del juego
*/
void informacion_inicio(juego_t juego) {
    system("clear");
    printf("Informacion del de los personajes durante el juego\n");
    printf("\nCritico legolas %i\n", juego.critico_legolas);
    printf("Critico gimli %i\n", juego.critico_gimli);
    printf("Fallo legolas %i\n", juego.fallo_legolas);
    printf("Fallo gimli %i\n", juego.fallo_gimli);
    printf("El juego comenzara pronto...\n");
    detener_el_tiempo(TIEMPO_INICIO);
}

/*
* Funcionamiento:
*	Muestra un mensaje final dependiendo si el juego
*	se gano o perdio
*/
void mensaje_final(juego_t juego) {
    int estado;
    estado = estado_juego(juego);
    if (estado == PERDEDOR) {
        printf("\n\n\tLAS FUERZAS OSCURAS HAN TRIUNFADO\n");
        printf("\nManuel nos ha traicionado, los refuerzos nunca llegaron...\n\n\tCharly vuelve a reinar.\n\n");
    } else if (estado == GANADOR) {
        printf("\n\tSAURON HA SIDO DERROTADO\n");
        printf("\nEl amanecer del quinto dia ha llegado, por el oriente a todo galope baja por la montaña Manu con todos los ayudantes\n\n");
        printf("Esto nunca lo habriamos logrado sin la ayuda de Mendez y todo su equipo\n\n\t¡GRACIAS!\n\n");
    }
}

/*
* Funcionamiento: guarda la estructura del juego en el estado actual en un archivo binario
*/
void guardar_turno(juego_t *turno, FILE *archivo) {

    size_t cantidad_guardada = 0;

    cantidad_guardada = fwrite(turno, sizeof(juego_t), 1, archivo);

    if (cantidad_guardada != 1) {
        printf("Fallo, se guardaron  \n");
    }
}

/*
 * Completa la configuracion no ingresada por el usuario con los valores por default
 */
void completa_configuracion(configuracion_t *configuracion, int viento, int humedad,
                            char animo_legolas, char animo_gimli) {

    if (configuracion->resistencia_1 == NO_INGRESADO) {
        configuracion->resistencia_1 = VIDA_BASE_TORRE;
    }
    if (configuracion->resistencia_2 == NO_INGRESADO) {
        configuracion->resistencia_2 = VIDA_BASE_TORRE;
    }

    if (configuracion->critico_enanos == NO_INGRESADO) {
        configuracion->critico_enanos = probabilidad_letal(animo_gimli);
    }
    if (configuracion->critico_elfos == NO_INGRESADO) {
        configuracion->critico_elfos = probabilidad_letal(animo_legolas);
    }

    if (configuracion->fallo_enanos == NO_INGRESADO) {
        configuracion->fallo_enanos = probabilidad_fallo_ataque(humedad);
    }
    if (configuracion->fallo_elfos == NO_INGRESADO) {
        configuracion->fallo_elfos = probabilidad_fallo_ataque(viento);
    }
    if (configuracion->enanos_extras[0] == NO_INGRESADO) {
        configuracion->enanos_extras[0] = CANTIDAD_ENANOS_EXTRA;
    }
    if (configuracion->elfos_extras[0] == NO_INGRESADO) {
        configuracion->elfos_extras[0] = CANTIDAD_ELFOS_EXTRA;
    }
    if (configuracion->enanos_extras[1] == NO_INGRESADO) {
        configuracion->enanos_extras[1] = COSTO_ENANO_TORRE_1;
    }
    if (configuracion->enanos_extras[1] == NO_INGRESADO) {
        configuracion->enanos_extras[2] = COSTO_ENANO_TORRE_2;
    }
    if (configuracion->elfos_extras[1] == NO_INGRESADO) {
        configuracion->elfos_extras[1] = COSTO_ELFO_TORRE_1;
    }
    if (configuracion->elfos_extras[1] == NO_INGRESADO) {
        configuracion->elfos_extras[2] = COSTO_ELFO_TORRE_2;
    }
}

/*
* Funcionamiento: completa la informacion no ingresada por el usuario,inicializa el juego,
*	muestra la informacion de los personajes y pide al usuario que coloque los defensores iniciales
*/
void comenzar_juego(juego_t *juego, int *preguntar_refuerzos, configuracion_t *configuracion,
                    camino_niveles_t caminos_niveles, float *velocidad_juego) {

    int viento;
    int humedad;

    char animo_legolas;
    char animo_gimli;

    viento = 50;
    humedad = 25;
    animo_legolas = 'B';
    animo_gimli = 'B';
    //animos(&viento,&humedad,&animo_legolas,&animo_gimli);

    system("clear");

    if (configuracion->velocidad_juego != NO_INGRESADO) {
        *velocidad_juego = configuracion->velocidad_juego;
    } else {
        *velocidad_juego = VELOCIDAD_JUEGO_DEFAULT;
    }
    completa_configuracion(configuracion, viento, humedad, animo_legolas, animo_gimli);

    inicializar_juego(juego, viento, humedad, animo_legolas, animo_gimli, *configuracion);

    informacion_inicio(*juego);

    juego->nivel_actual = NIVEL_ESTE;

    inicia_nivel(juego, caminos_niveles);
    defensores_manual(juego, configuracion, preguntar_refuerzos);
}

/*
* Funcionamiento: actualiza las estructuras del juego a los valores del nivel
*	correspondiente y pide al usuario que ingrese los defensores del nivel
*/
void iniciar_siguiente_nivel(juego_t *juego, configuracion_t *configuracion,
                             camino_niveles_t caminos_niveles, int *preguntar_refuerzos) {

    juego->nivel_actual++;

    inicia_nivel(juego, caminos_niveles);

    defensores_manual(juego, configuracion, preguntar_refuerzos);

    mostrar_juego(*juego);
}

/*
* Funcionamiento: cuenta la cantidad de orcos muertos que no llegaron a la torre al final de cada nivel
*/
void cantidad_muertos(juego_t juego, int *cantidad_orcos_muertos) {

    coordenada_t torre_1;
    coordenada_t torre_2;
    coordenada_t coordenada_orco;

    int camino_orco;
    int indice_camino;


    torre_1.fil = juego.nivel.camino_1[juego.nivel.tope_camino_1 - 1].fil;
    torre_1.col = juego.nivel.camino_1[juego.nivel.tope_camino_1 - 1].col;

    if (juego.nivel.tope_camino_2 != 0) {
        torre_2.fil = juego.nivel.camino_2[juego.nivel.tope_camino_2 - 1].fil;
        torre_2.col = juego.nivel.camino_2[juego.nivel.tope_camino_2 - 1].col;
    } else {
        torre_2.fil = NO_INGRESADO;
        torre_2.col = NO_INGRESADO;
    }

    for (int i = 0; i < juego.nivel.tope_enemigos; i++) {
        camino_orco = juego.nivel.enemigos[i].camino;
        indice_camino = juego.nivel.enemigos[i].camino;

        if (camino_orco == CAMINO_1) {
            coordenada_orco.fil = juego.nivel.camino_1[indice_camino].fil;
            coordenada_orco.col = juego.nivel.camino_1[indice_camino].col;
        } else if (camino_orco == CAMINO_2) {
            coordenada_orco.fil = juego.nivel.camino_2[indice_camino].fil;
            coordenada_orco.col = juego.nivel.camino_2[indice_camino].col;
        }

    }
    if (coordenada_orco.fil != torre_1.fil && coordenada_orco.col != torre_1.col) {
        *cantidad_orcos_muertos = *cantidad_orcos_muertos + 1;
    } else if (coordenada_orco.fil != torre_2.fil && coordenada_orco.col != torre_2.col) {
        *cantidad_orcos_muertos = *cantidad_orcos_muertos + 1;
    }
}

/*
* Funcionamiento: comienza el juego, lo ejecuta y guarda cada turno hasta que el juego termine. 
*	Una vez finalizado cuenta la cantidad de orcos muertos.
*/
void correr_juego_grabando(juego_t *juego, FILE *archivo, configuracion_t *configuracion,
                           camino_niveles_t caminos, int *orcos_muertos) {

    int preguntar_refuerzos;

    int contador;

    float velocidad_juego;

    contador = INICIAL;

    comenzar_juego(juego, &preguntar_refuerzos, configuracion, caminos, &velocidad_juego);

    guardar_turno(juego, archivo);

    while (estado_juego(*juego) == JUGANDO) {

        if (estado_nivel(juego->nivel) == GANADOR) {

            cantidad_muertos(*juego, orcos_muertos);

            iniciar_siguiente_nivel(juego, configuracion, caminos, &preguntar_refuerzos);

            contador = INICIAL;

        }

        if (contador == preguntar_refuerzos) {

            preguntar_defensor_extra(juego, *configuracion);

            contador = INICIAL;
        }

        jugar_turno(juego);

        mostrar_juego(*juego);


        if (juego->nivel.tope_enemigos != juego->nivel.max_enemigos_nivel) {

            contador++;
        }

        detener_el_tiempo(velocidad_juego);

        guardar_turno(juego, archivo);
    }
    cantidad_muertos(*juego, orcos_muertos);
}

/*
* Funcionamiento: comienza el juego y lo ejecuta hasta que el juego termine. 
*	Una vez finalizado cuenta la cantidad de orcos muertos.
*/

void correr_juego_sin_grabar(juego_t *juego, configuracion_t *configuracion,
                             camino_niveles_t caminos, int *orcos_muertos) {


    int preguntar_refuerzos;

    int contador;

    float velocidad_juego;

    contador = INICIAL;

    comenzar_juego(juego, &preguntar_refuerzos, configuracion, caminos, &velocidad_juego);

    while (estado_juego(*juego) == JUGANDO) {

        if (estado_nivel(juego->nivel) == GANADOR) {

            cantidad_muertos(*juego, orcos_muertos);

            iniciar_siguiente_nivel(juego, configuracion, caminos, &preguntar_refuerzos);

            contador = INICIAL;

        }

        if (contador == preguntar_refuerzos) {
            preguntar_defensor_extra(juego, *configuracion);

            contador = INICIAL;
        }

        jugar_turno(juego);

        mostrar_juego(*juego);


        if (juego->nivel.tope_enemigos != juego->nivel.max_enemigos_nivel) {

            contador++;
        }

        detener_el_tiempo(velocidad_juego);
    }
    cantidad_muertos(*juego, orcos_muertos);
}

/*
* Funcionamiento: realiza el conteo del puntaje final basado en las estructuras del juego
* y la cantidad de orcos muertos. 
*/
int puntaje_final(juego_t juego, configuracion_t configuracion, int cantidad_orcos_muertos) {

    int vida_torre_1;
    int vida_torre_2;

    int enanos_inicio_total = 0;
    int elfos_inicio_total = 0;

    int cantidad_defensores_usados;

    int puntaje;

    vida_torre_1 = configuracion.resistencia_1;
    vida_torre_2 = configuracion.resistencia_2;

    cantidad_defensores_usados =
            configuracion.enanos_extras[0] - juego.torres.enanos_extra + configuracion.elfos_extras[0] -
            juego.torres.elfos_extra;

    for (int i = 0; i < CANTIDAD_NIVELES; i++) {

        enanos_inicio_total += configuracion.enanos_inicio[i];
        elfos_inicio_total += configuracion.elfos_inicio[i];
    }

    puntaje = (int) (cantidad_orcos_muertos * 1000 /
                     (vida_torre_1 + vida_torre_2 + cantidad_defensores_usados + enanos_inicio_total +
                      elfos_inicio_total));

    return puntaje;
}

/*
* Funcionamiento: abre el archivo de grabacion, ejectura el juego, muestra un mensaje final y asigna el puntaje final. 
*/
void juego_grabando_partida(configuracion_t configuracion, camino_niveles_t caminos, char ruta_grabacion[MAX_RUTA],
                            int *puntaje) {

    int orcos_muertos = 0;

    FILE *archivo_grabacion = fopen(ruta_grabacion, "w");

    srand((unsigned) time(NULL));

    juego_t juego;

    system("clear");

    correr_juego_grabando(&juego, archivo_grabacion, &configuracion, caminos, &orcos_muertos);

    system("clear");

    mensaje_final(juego);

    fclose(archivo_grabacion);

    *puntaje = puntaje_final(juego, configuracion, orcos_muertos);
}

/*
* Funcionamiento: ejectura el juego, muestra un mensaje final y asigna el puntaje final. 
*/
void juego_sin_grabar_partida(configuracion_t configuracion, camino_niveles_t caminos, int *puntaje) {

    int orcos_muertos = 0;

    srand((unsigned) time(NULL));

    juego_t juego;

    system("clear");

    correr_juego_sin_grabar(&juego, &configuracion, caminos, &orcos_muertos);

    system("clear");

    mensaje_final(juego);

    *puntaje = puntaje_final(juego, configuracion, orcos_muertos);
}








