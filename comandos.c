#include "juego.h"

#define SEPARADOR_CLAVES "="

#define RUTA_RANKING_AUXILIAR "ranking_auxiliar.csv"
#define RUTA_CONFIG_DEFAULT "config_default.txt"
#define RUTA_CAMINOS_DEFAULT "camino_default.txt"
#define RUTA_GRABACION_DEFAULT "repeticion_default.dat"
#define RUTA_RANKING_DEFAULT "ranking_config_default.csv"
#define RUTA_RANKING_USUARIO "ranking_"

#define TIPO_CSV ".csv"

#define CLAVE_JUGAR "jugar"
#define CLAVE_RANKING "ranking"
#define CLAVE_CREAR_CAMINO "crear_camino"
#define CLAVE_CREAR_CONFIGURACION "crear_configuracion"

#define CLAVE_RUTA_CONFIGURACION "config"
#define CLAVE_CANTIDAD_LISTAR "listar"
#define CLAVE_RUTA_GRABACION "grabacion"
#define CLAVE_VELOCIDAD "velocidad"
#define CLAVE_REPETICION "poneme_la_repe"

#define FORMATO_TORRES "=%i,%i\n"
#define FORMATO_INICIO "=%i,%i,%i,%i\n"
#define FORMATO_EXTRA "=%i,%i,%i\n"
#define FORMATO_ANIMO "=%i,%i\n"
#define FORMATO_VELOCIDAD "=%f\n"
#define FORMATO_CAMINOS "=%s\n"
#define FORMATO_PUNTAJE "=%s,%i\n"
#define FORMATO_CLAVE "%[^ =]"
#define FORMATO_NIVEL "%s=%i\n"
#define FORMATO_COORDENADA "%i;%i\n"
#define FORMATO_PALABRA "%s\n"
#define FORMATO_LEER_RANKING "%[^,],%i\n"
#define FORMATO_ESCRIBIR_RANKING "%s,%i\n"

#define RESISTENCIA "RESISTENCIA_TORRES"
#define ENANOS_INICIO "ENANOS_INICIO"
#define ELFOS_INICIO "ELFOS_INICIO"
#define ENANOS_EXTRA "ENANOS_EXTRA"
#define ELFOS_EXTRA "ELFOS_EXTRA"
#define ENANOS_ANIMO "ENANOS_ANIMO"
#define ELFOS_ANIMO "ELFOS_ANIMO"
#define VELOCIDAD "VELOCIDAD"
#define CAMINOS "CAMINOS"

#define CLAVE_NIVEL "NIVEL"
#define CLAVE_NIVEL_2 "NIVEL=2"
#define CLAVE_NIVEL_3 "NIVEL=3"
#define CLAVE_NIVEL_4 "NIVEL=4"
#define CLAVE_CAMINO "CAMINO"
#define CLAVE_CAMINO_2 "CAMINO=2"
#define CLAVE_CAMINO_1 "CAMINO=1"
#define CLAVE_FIN_ARCHIVO " "
#define NUMERO_CLAVES_CONFIG 9


#define SEPARADOR_TIPO_ARCHIVO "."
#define SEPARADOR_COORDENADA ";"
#define SEPARADOR_ARGUMENTOS "="


const bool NO_GRABAR = false;
const bool GRABAR = true;
const float TIEMPO_CAMINOS = 10;

/*
* Recibe:
*	 nivel_actual: entero del nivel en el que se encuentra
*	 Debe ser entre 1 y 4
* Funcionamiento:
*	 Asigna el largo del tablero
*/
int asignar_largo(int nivel_actual) {
    int largo;

    if (nivel_actual < NIVEL_NORTE) {
        largo = MAXIMO_CAMINO_SIMPLE;
    } else {
        largo = MAXIMO_CAMINO_DOBLE;
    }

    return largo;
}

/*
* Recibe
* largo_tablero: entero mayor a 0
* Funcionamiento: muestra la parte superior
*	del tablero
*/
void tablero_superior_creador(int largo_tablero) {
    printf("\t");
    for (int i = 0; i < largo_tablero; i++) {
        printf("____");
    }
    printf("_____\n\t");
}

/*
* Recibe
* largo_tablero: entero mayor a 0
* Funcionamiento: muestra la parte inferior
*	del tablero
*/
void tablero_inferior_creador(int largo_tablero) {


    for (int i = 0; i < largo_tablero; i++) {
        printf("|¯¯¯");
    }

    printf("|¯¯¯¯|\n\t");

    for (int i = 0; i < largo_tablero; i++) {

        if (i < 9) {
            printf("| %i ", i + 1);
        } else {
            printf("|%i ", i + 1);
        }
    }

    printf("|    |\n\t");

    for (int i = 0; i < largo_tablero; i++) {
        printf("¯¯¯¯");
    }

    printf("¯¯¯¯¯\n");
}

/*
* Recibe
*	camino: vector de coordenadas del camino
*	tope: tope del vector
*	tablero: matriz de caracteres
*	largo_tablero: entero mayor a 0
* Funcionamiento: 
*	recorre el camino asignando el caracter camino a 
*	cada coordenada de los mismos
*/
void pintar_camino(coordenada_t camino[MAX_LONGITUD_CAMINO], int tope, char tablero[MAX_FILAS][MAX_COLUMNAS]) {
    int fila;
    int columna;

    if (tope != 0) {
        for (int i = 0; i < tope; i++) {
            fila = camino[i].fil;
            columna = camino[i].col;
            tablero[fila][columna] = CARACTER_CAMINO;
        }
    }
}

/*
* Recibe
*	camino: vector de coordenadas del camino
*	tope: tope del vector
*	tablero: matriz de caracteres
*	largo_tablero: entero mayor a 0
* Funcionamiento: 
*	Asigna el caracter de entrada y torre al trablero
*/
void pintar_entrada_salida(coordenada_t camino[MAX_LONGITUD_CAMINO], int tope, char tablero[MAX_FILAS][MAX_COLUMNAS]) {
    int fila;
    int columna;

    if (tope != 0) {
        fila = camino[tope - 1].fil;
        columna = camino[tope - 1].col;
        tablero[fila][columna] = TORRE;

        fila = camino[0].fil;
        columna = camino[0].col;
        tablero[fila][columna] = ENTRADA;
    }
}

/*
* Recibe
*	camino_1: vector de coordenadas del camino 1
*	tope_1: tope del vector 1
*	camino_2: vector de coordenadas del camino 2
*	tope_2: tope del vector 2
*	tablero: matriz de caracteres
*	largo_tablero: entero mayor a 0
* Funcionamiento: 
*	Asigna los caracteres al tablero
*/
void asigna_caracteres_creador(coordenada_t camino_1[MAX_LONGITUD_CAMINO], int tope_1,
                               coordenada_t camino_2[MAX_LONGITUD_CAMINO], int tope_2,
                               char tablero[MAX_FILAS][MAX_COLUMNAS], int largo_tablero) {

    for (int i = 0; i < largo_tablero; i++) {
        for (int j = 0; j < largo_tablero; j++) {
            tablero[i][j] = CARACTER_VACIO;
        }
    }

    pintar_camino(camino_1, tope_1, tablero);
    pintar_camino(camino_2, tope_2, tablero);

    pintar_entrada_salida(camino_1, tope_1, tablero);
    pintar_entrada_salida(camino_2, tope_2, tablero);
}

/*
* Funcionamiento:
*	muestra el tablero con los separadores y numeros de filas y columnas
*/
void tablero_centro_numeros_creador(char tablero[MAX_FILAS][MAX_COLUMNAS], int largo_tablero) {
    for (int i = 0; i < largo_tablero; i++) {
        for (int j = 0; j < largo_tablero; j++) {
            printf("| %c ", tablero[i][j]);
        }
        if (i < 9) {
            printf("|  %i |\n\t", i + 1);
        } else {
            printf("| %i |\n\t", i + 1);
        }
    }
}

/*
* Recibe
*	camino_1: vector de coordenadas del camino 1
*	tope_1: tope del vector 1
*	camino_2: vector de coordenadas del camino 2
*	tope_2: tope del vector 2
*	tablero: matriz de caracteres
*	largo_tablero: entero mayor a 0
* Funcionamiento: 
*	Muestra el tablero con los caracteres correspondientes
*/
void mostrar_tablero(coordenada_t camino_1[MAX_LONGITUD_CAMINO], int tope_1,
                     coordenada_t camino_2[MAX_LONGITUD_CAMINO], int tope_2, int nivel_actual) {

    char tablero[MAX_FILAS][MAX_COLUMNAS];

    int largo_tablero;

    largo_tablero = asignar_largo(nivel_actual);

    asigna_caracteres_creador(camino_1, tope_1, camino_2, tope_2, tablero, largo_tablero);

    tablero_superior_creador(largo_tablero);
    tablero_centro_numeros_creador(tablero, largo_tablero);
    tablero_inferior_creador(largo_tablero);
}

/*
* Funcionamiento: 
*	asigna el minimo y maximo nivel del tablero
*	dependiendo del nivel
*/
void determina_limites(int nivel_actual, int *minimo, int *maximo) {
    if (nivel_actual < NIVEL_NORTE) {
        *minimo = MINIMO_CAMINO_SIMPLE;
        *maximo = MAXIMO_CAMINO_SIMPLE;
    } else {
        *minimo = MINIMO_CAMINO_DOBLE;
        *maximo = MAXIMO_CAMINO_DOBLE;
    }
}

/*
* Funcionamiento: 
*	Pide al usuario el ingreso de una fila
* 	hasta que la misma sea valida
*/
void pedir_fila(int *fila, int minimo, int maximo) {

    printf("Ingrese la fila: ");

    scanf("%i", fila);

    while (*fila < minimo || *fila > maximo) {

        printf("Ingrese la fila: ");

        scanf("%i", fila);
    }
}

/*
* Funcionamiento: 
*	Pide al usuario el ingreso de una columna
* 	hasta que la misma sea valida
*/
void pedir_columna(int *columna, int minimo, int maximo) {

    printf("Ingrese la columna: ");

    scanf("%i", columna);

    while (*columna < minimo || *columna > maximo) {

        printf("Ingrese la columna: ");

        scanf("%i", columna);
    }
}

/*
* Funcionamiento: 
*	Pide al usuario el ingreso de las
*	coordenadas validando que la fila o
*	la columna coincida con la ultima
*/
void pedir_coordenadas(int *fila, int *columna, int minimo, int maximo, coordenada_t ultimo_punto) {

    pedir_fila(fila, minimo, maximo);
    pedir_columna(columna, minimo, maximo);

    while (ultimo_punto.fil != *fila - 1 && ultimo_punto.col != *columna - 1) {

        printf("Los puntos deben estar en la misma fila o columna\n");
        pedir_fila(fila, minimo, maximo);
        pedir_columna(columna, minimo, maximo);

    }
}

/*
* Funcionamiento: 
*	Pide al usuario el ingreso de la
*	fila o columna libres de la entrada y torre
*	asignando la otra dependiendo el nivel
*/
void coordenadas_basicas(int nivel_actual, coordenada_t *entrada, coordenada_t *torre) {

    int minimo;
    int maximo;

    determina_limites(nivel_actual, &minimo, &maximo);

    if (nivel_actual == NIVEL_ESTE) {
        entrada->col = maximo;
        printf("Coordenada de la entrada\n\n");
        pedir_fila(&entrada->fil, minimo, maximo);
        torre->col = minimo;
        printf("Coordenada de la torre\n\n");
        pedir_fila(&torre->fil, minimo, maximo);

    } else if (nivel_actual == NIVEL_OESTE) {
        entrada->col = minimo;
        printf("Coordenada de la entrada\n\n");
        pedir_fila(&entrada->fil, minimo, maximo);
        torre->col = maximo;
        printf("Coordenada de la torre\n\n");
        pedir_fila(&torre->fil, minimo, maximo);

    } else if (nivel_actual == NIVEL_NORTE) {
        entrada->fil = minimo;
        printf("Coordenada de la entrada\n\n");
        pedir_columna(&entrada->col, minimo, maximo);
        torre->fil = maximo;
        printf("Coordenada de la torre\n\n");
        pedir_columna(&torre->col, minimo, maximo);
    } else if (nivel_actual == NIVEL_SUR) {
        entrada->fil = maximo;
        printf("Coordenada de la entrada\n\n");
        pedir_columna(&entrada->col, minimo, maximo);
        torre->fil = minimo;
        printf("Coordenada de la torre\n\n");
        pedir_columna(&torre->col, minimo, maximo);
    }
}

/*
* Funcionamiento: 
*	Determina si la coordenada camino coincide
* 	con la coordenada torre
*/
int camino_en_torre(coordenada_t camino, coordenada_t torre) {

    return (camino.fil == torre.fil && camino.col == torre.col);
}

/*
*Recibe:
*	camino: vector de coordenadas del camino creado
*	tope: tope del vector
*	cantidad: cantidad de puntos que tienen que colocarse
*	avance_fila: 0,1,-1
*	avance_columna: 0,1,-1
*	coordenada_torre: coordenadas de la torre 
* Funcionamiento: 
*	Coloca en el vector camino los puntos aumentando o restando
*	las filas o columnas hasta completar
*	la cantidad o hasta llegar a la torre
*/
void colocar_puntos(coordenada_t camino[MAX_LONGITUD_CAMINO], int *tope, int cantidad,
                    int avance_fila, int avance_columna, coordenada_t torre) {

    int contador = 0;

    while (contador < cantidad) {

        camino[*tope - 1].fil = camino[*tope - 2].fil + avance_fila;
        camino[*tope - 1].col = camino[*tope - 2].col + avance_columna;

        camino[*tope].fil = torre.fil - 1;
        camino[*tope].col = torre.col - 1;


        contador++;
        *tope = *tope + 1;

        if (camino_en_torre(camino[*tope - 2], camino[*tope - 1])) {

            contador = cantidad;
        }

    }
}

/*
*Recibe:
*	camino: vector de coordenadas del camino creado
*	tope: tope del vector
*	fila: fila hasta la que debe llegar el camino
*	columnda: columna hasta la que debe llegar el camino
*	coordenada_torre: coordenadas de la torre 
* Funcionamiento: 
*	Conecta el ultimo punto del camino con el punto determinado
*	por la fila y columna
*/
void conectar_puntos(coordenada_t camino[MAX_LONGITUD_CAMINO], int *tope, int fila, int columna, coordenada_t torre) {

    int cantidad_puntos = 0;

    int avance_fila = 0;

    int avance_columna = 0;

    if (fila == camino[*tope - 2].fil && columna == camino[*tope - 2].col) {
        printf("Debe avanzar un casillero por lo menos\n");
    } else {
        if (fila == camino[*tope - 2].fil) {

            cantidad_puntos = abs(camino[*tope - 2].col - columna);

            avance_columna = (columna - camino[*tope - 2].col) / abs(camino[*tope - 2].col - columna);

        } else if (columna == camino[*tope - 2].col) {

            cantidad_puntos = abs(camino[*tope - 2].fil - fila);

            avance_fila = (fila - camino[*tope - 2].fil) / abs(camino[*tope - 2].fil - fila);

        }

        colocar_puntos(camino, tope, cantidad_puntos, avance_fila, avance_columna, torre);
    }
}

/*
*Recibe:
*	camino_principal: vector de coordenadas del camino que se esta creando
*	tope_principal: tope del vector del camino que se esta creando
*	camino_secundario: vector de coordenadas del camino que no se esta creando
*	tope_secundario: tope del vector del camino que no se esta creando
*	nivel_actual: nivel del juego
*	torre: coordenadas de la torre del camino printical
* Funcionamiento: 
*	Coloca en el vector camino los puntos aumentando o restando
*	las filas o columnas hasta completar
*	la cantidad o hasta llegar a la torre
*/
void armar_camino(coordenada_t camino_principal[MAX_LONGITUD_CAMINO], int *tope_principal,
                  coordenada_t camino_secundario[MAX_LONGITUD_CAMINO], int *tope_secundario, int nivel_actual,
                  coordenada_t torre) {

    int fila;
    int columna;

    int minimo;
    int maximo;

    determina_limites(nivel_actual, &minimo, &maximo);

    while (!camino_en_torre(camino_principal[*tope_principal - 2], camino_principal[*tope_principal - 1])) {

        system("clear");

        printf("NIVEL %i\n", nivel_actual);

        mostrar_tablero(camino_principal, *tope_principal, camino_secundario, *tope_secundario, nivel_actual);

        printf("Coordenadas camino\n");

        printf("Ingrese las coordenadas (en linea recta) hasta las que quiere dirigirse\n\n");

        pedir_coordenadas(&fila, &columna, minimo, maximo, camino_principal[*tope_principal - 2]),

                conectar_puntos(camino_principal, tope_principal, fila - 1, columna - 1, torre);
    }
    *tope_principal = *tope_principal - 1;

    mostrar_tablero(camino_principal, *tope_principal, camino_secundario, *tope_secundario, nivel_actual);
}

/*
*Recibe:
*	camino: vector de coordenadas del camino que se esta creando
*	tope: tope del vector del camino que se esta creando
*	entrada: coordenadas de la entrada del camino printical
*	torre: coordenadas de la torre del camino printical
* Funcionamiento: 
*	Coloca en el vector camino la entrada y la torre
*/
void
agregar_entrada_salida(coordenada_t camino[MAX_LONGITUD_CAMINO], int *tope, coordenada_t entrada, coordenada_t torre) {
    camino[0].fil = entrada.fil - 1;
    camino[0].col = entrada.col - 1;
    *tope = *tope + 1;

    camino[*tope].fil = torre.fil - 1;
    camino[*tope].col = torre.col - 1;
    *tope = *tope + 1;
}

/*
*Recibe:
*	camino_1: vector de coordenadas del camino que se esta creando
*	tope_1: tope del vector del camino que se esta creando
*	camino_2: vector de coordenadas del camino que no se esta creando
*	tope_2: tope del vector del camino que no se esta creando
*	nivel_actual: nivel del juego
* Funcionamiento: 
*	Pide al usuario que ingrese las coordenadas de la entrada y la torre
*	y las coordenadas del camino o de los caminos dependiendo del nivel
*/
void ingresar_camino_usuario(coordenada_t camino_1[MAX_LONGITUD_CAMINO], int *tope_1,
                             coordenada_t camino_2[MAX_LONGITUD_CAMINO], int *tope_2, int nivel_actual) {

    coordenada_t torre_1;
    coordenada_t torre_2;

    coordenada_t entrada_1;
    coordenada_t entrada_2;

    *tope_1 = 0;
    *tope_2 = 0;

    system("clear");

    printf("NIVEL %i\n", nivel_actual);

    mostrar_tablero(camino_1, *tope_1, camino_2, *tope_2, nivel_actual);

    coordenadas_basicas(nivel_actual, &entrada_1, &torre_1);

    agregar_entrada_salida(camino_1, tope_1, entrada_1, torre_1);

    if (nivel_actual > NIVEL_OESTE) {

        system("clear");

        printf("NIVEL %i\n", nivel_actual);

        mostrar_tablero(camino_1, *tope_1, camino_2, *tope_2, nivel_actual);

        coordenadas_basicas(nivel_actual, &entrada_2, &torre_2);

        agregar_entrada_salida(camino_2, tope_2, entrada_2, torre_2);
    }

    armar_camino(camino_1, tope_1, camino_2, tope_2, nivel_actual, torre_1);

    if (nivel_actual > NIVEL_OESTE) {
        armar_camino(camino_2, tope_2, camino_1, tope_1, nivel_actual, torre_2);
    }
}

/*
*Recibe:
*	camino_niveles: estructura que contiene los vectores de los caminos
*	y el tope de los mismos
*Funcionamiento: 
*	Pide el ingreso de los caminos de cada nivel al usuario
*/
void ingresar_camino(camino_niveles_t *camino_niveles) {


    for (int i = 0; i < CANTIDAD_NIVELES; i++) {

        ingresar_camino_usuario(camino_niveles->caminos[i][0], &camino_niveles->tope_caminos[i][0],
                                camino_niveles->caminos[i][1], &camino_niveles->tope_caminos[i][1], i + 1);

    }
}

/*
*Recibe:
*	clave: string leido del archivo
*	clave_corte: string de las cabeceras del archivo
*Funcionamiento: 
*	Compara el string leido con los de cabera
*/
int compara_claves(char clave[MAX_CLAVE], char clave_corte[MAX_CLAVE]) {

    return strcmp(strtok(clave, SEPARADOR_CLAVES), clave_corte);
}

/*
*Funcionamiento: 
*	Lee el archivo linea a linea colocando las coordenadas en el vector
*	hasta leer una cabecera
*/
void asignar_camino(FILE *archivo, coordenada_t camino[MAX_LONGITUD_CAMINO], int *tope) {
    char clave[MAX_CLAVE];

    int contador = 0;

    *tope = 0;


    fscanf(archivo, FORMATO_PALABRA, clave);

    while (compara_claves(clave, CLAVE_CAMINO) && compara_claves(clave, CLAVE_NIVEL) && !feof(archivo)) {

        camino[contador].fil = (int) atoi(strtok(clave, SEPARADOR_COORDENADA));
        camino[contador].col = (int) atoi(strtok(NULL, SEPARADOR_COORDENADA));
        *tope = *tope + 1;

        fscanf(archivo, FORMATO_PALABRA, clave);

        contador++;
    }

    if (feof(archivo)) {

        camino[contador].fil = (int) atoi(strtok(clave, SEPARADOR_COORDENADA));
        camino[contador].col = (int) atoi(strtok(NULL, SEPARADOR_COORDENADA));
        *tope = *tope + 1;
    }
}

/*
*Funcionamiento: 
*	Asigna todos los caminos del archivo a la estructura
*	junto con sus respectivos topes 
*/
void leer_caminos(FILE *archivo, camino_niveles_t *caminos) {

    char clave[MAX_CLAVE];

    fscanf(archivo, FORMATO_PALABRA, clave);

    for (int i = 0; i < CANTIDAD_NIVELES; i++) {

        fscanf(archivo, FORMATO_PALABRA, clave);

        asignar_camino(archivo, caminos->caminos[i][0], &caminos->tope_caminos[i][0]);

        if (i + 1 > NIVEL_OESTE) {
            asignar_camino(archivo, caminos->caminos[i][1], &caminos->tope_caminos[i][1]);
        } else {
            caminos->tope_caminos[i][1] = 0;
        }
    }
}

/*
* Recibe:
*	 rango: entero que define el intervalo
*	 minimo: entero que establece el minimo valor
* Devuelve:
*	 un entero aleatorio entre minimo y rango+minimo
*/
int aleatorio(int rango, int minimo) {

    return (rand() % rango + minimo);
}

/*
* Recibe:
*	 *torre: puntero a las coordenadas de la torre en el nivel
*	 *entrada: puntero a las coordenadas de la entrada en el nivel
*	 entrada_fija: entero que define el primer tope del tablero
*	 torre_fija: entero que define el segundo tope del tablero
* Funcionamiendo:
*	 asigna un entero aleatorio a la fila de la entrada y a la fila de la torre
*/
void posiciones_nivel_simple(coordenada_t *torre, coordenada_t *entrada, int entrada_fija, int torre_fija) {

    torre->col = torre_fija;
    entrada->col = entrada_fija;

    if (entrada_fija > torre_fija) {
        entrada->fil = aleatorio(entrada_fija, torre_fija);
        torre->fil = aleatorio(entrada_fija, torre_fija);
    } else {
        entrada->fil = aleatorio(torre_fija, entrada_fija);
        torre->fil = aleatorio(torre_fija, entrada_fija);
    }
}

/*
* Recibe:
*	 *torre: puntero a las coordenadas de la torre en el nivel
*	 *entrada: puntero a las coordenadas de la entrada en el nivel
*	 entrada_fija: entero que define el primer tope del tablero. Debe ser mayor a 0
*	 torre_fija: entero que define el segundo tope del tablero. Debe ser mayor a 0
* Funcionamiendo:
*	 asigna un entero aleatorio a la columna de la entrada y a la columna de la torre
*/
void posiciones_nivel_doble(coordenada_t *torre, coordenada_t *entrada, int entrada_fija, int torre_fija) {

    torre->fil = torre_fija;
    entrada->fil = entrada_fija;

    if (entrada_fija > torre_fija) {
        entrada->col = aleatorio(entrada_fija, torre_fija);
        torre->col = aleatorio(entrada_fija, torre_fija);
    } else {
        entrada->col = aleatorio(torre_fija, entrada_fija);
        torre->col = aleatorio(torre_fija, entrada_fija);
    }
}

/*
* Recibe:
*	 camino: vector de las coordenadas del camino
*	 entrada_fija: entero que define el primer tope del tablero. Debe ser mayor a 0
*	 torre_fija: entero que define el segundo tope del tablero. Debe ser mayor a 0
* Funcionamiendo:
*	 Asigna las coordenadas de la entrada, la torre y crea el camino del nivel
*/
void nivel_simple(coordenada_t camino[MAX_LONGITUD_CAMINO], int *tope_camino, int entrada_fija, int torre_fija) {
    coordenada_t entrada_torre;
    coordenada_t entrada_camino;
    posiciones_nivel_simple(&entrada_torre, &entrada_camino, entrada_fija, torre_fija);
    obtener_camino(camino, tope_camino, entrada_camino, entrada_torre);
}

/*
* Recibe:
*	 camino_1: vector de coordenadas vacio
*	 camino_2: vector de coordenadas vacio
*	 *tope_camino_1: puntero al entero del tope del vector camino_1
*	 *tope_camino_2: puntero al entero del tope del vector camino_2
*	 entrada_fija: entero que define el primer tope del tablero. Debe ser mayor a 0
*	 torre_fija: entero que define el segundo tope del tablero. Debe ser mayor a 0
* Funcionamiento:
*	Ubica aleatoriamente las torres y entradas en el tablero y obtiene los caminos
*	Verifica que las entradas y torres no sean iguales
*/
void nivel_doble(coordenada_t camino_1[MAX_LONGITUD_CAMINO], int *tope_camino_1,
                 coordenada_t camino_2[MAX_LONGITUD_CAMINO], int *tope_camino_2, int entrada_fija, int torre_fija) {

    coordenada_t entrada_torre_1;
    coordenada_t entrada_camino_1;
    coordenada_t entrada_torre_2;
    coordenada_t entrada_camino_2;

    posiciones_nivel_doble(&entrada_torre_1, &entrada_camino_1, entrada_fija, torre_fija);
    posiciones_nivel_doble(&entrada_torre_2, &entrada_camino_2, entrada_fija, torre_fija);

    while (entrada_torre_1.col == entrada_torre_2.col || entrada_camino_1.col == entrada_camino_2.col) {
        posiciones_nivel_doble(&entrada_torre_1, &entrada_camino_1, entrada_fija, torre_fija);
    }
    obtener_camino(camino_1, tope_camino_1, entrada_camino_1, entrada_torre_1);
    obtener_camino(camino_2, tope_camino_2, entrada_camino_2, entrada_torre_2);
}

/*
*Funcinamiento: crea los caminos de cada nivel de forma aleatoria
*/
void caminos_aleatorios(camino_niveles_t *caminos_niveles) {

    nivel_simple(caminos_niveles->caminos[0][0], &caminos_niveles->tope_caminos[0][0],
                 MAXIMO_CAMINO_SIMPLE - 1, MINIMO_CAMINO_SIMPLE - 1);

    caminos_niveles->tope_caminos[0][1] = 0;

    nivel_simple(caminos_niveles->caminos[1][0], &caminos_niveles->tope_caminos[1][0],
                 MINIMO_CAMINO_SIMPLE - 1, MAXIMO_CAMINO_SIMPLE - 1);

    caminos_niveles->tope_caminos[1][1] = 0;

    nivel_doble(caminos_niveles->caminos[2][0], &caminos_niveles->tope_caminos[2][0],
                caminos_niveles->caminos[2][1], &caminos_niveles->tope_caminos[2][1],
                MINIMO_CAMINO_DOBLE - 1, MAXIMO_CAMINO_DOBLE - 1);

    nivel_doble(caminos_niveles->caminos[3][0], &caminos_niveles->tope_caminos[3][0],
                caminos_niveles->caminos[3][1], &caminos_niveles->tope_caminos[3][1],
                MAXIMO_CAMINO_DOBLE - 1, MINIMO_CAMINO_DOBLE - 1);
}

/*
*Funcionamiento: escribe el camino 1 con sus cabeceras y el camnino 2
*	si este no esta vacio
*/
void guardar_camino(FILE *archivo, coordenada_t camino_1[MAX_LONGITUD_CAMINO], int tope_1,
                    coordenada_t camino_2[MAX_LONGITUD_CAMINO], int tope_2, int nivel_actual) {

    fprintf(archivo, FORMATO_NIVEL, CLAVE_NIVEL, nivel_actual);

    fprintf(archivo, FORMATO_PALABRA, CLAVE_CAMINO_1);

    for (int i = 0; i < tope_1; i++) {
        fprintf(archivo, FORMATO_COORDENADA, camino_1[i].fil, camino_1[i].col);
    }

    if (tope_2 != 0) {
        fprintf(archivo, FORMATO_PALABRA, CLAVE_CAMINO_2);

        for (int i = 0; i < tope_2; i++) {
            fprintf(archivo, FORMATO_COORDENADA, camino_2[i].fil, camino_2[i].col);
        }
    }
}

/*
*Funcionamiento: guarda en el archivo los caminos de los distintos niveles
*/
void escribir_caminos(FILE *archivo, camino_niveles_t caminos) {

    for (int i = 0; i < CANTIDAD_NIVELES; i++) {
        guardar_camino(archivo, caminos.caminos[i][0], caminos.tope_caminos[i][0],
                       caminos.caminos[i][1], caminos.tope_caminos[i][1], i + 1);
    }
}

/*
*Funcionamiento: compara la clave leida y lee la informacion con su respectivo formato
*/
void determina_formato_clave(char palabra_clave[MAX_CLAVE], configuracion_t *config_leida, FILE *archivo) {

    if (strcmp(palabra_clave, RESISTENCIA) == 0) {
        fscanf(archivo, FORMATO_TORRES, &config_leida->resistencia_1, &config_leida->resistencia_2);
    } else if (strcmp(palabra_clave, ENANOS_INICIO) == 0) {
        fscanf(archivo, FORMATO_INICIO, &config_leida->enanos_inicio[0], &config_leida->enanos_inicio[1],
               &config_leida->enanos_inicio[2], &config_leida->enanos_inicio[3]);
    } else if (strcmp(palabra_clave, ELFOS_INICIO) == 0) {
        fscanf(archivo, FORMATO_INICIO, &config_leida->elfos_inicio[0], &config_leida->elfos_inicio[1],
               &config_leida->elfos_inicio[2], &config_leida->elfos_inicio[3]);
    } else if (strcmp(palabra_clave, ENANOS_EXTRA) == 0) {
        fscanf(archivo, FORMATO_EXTRA, &config_leida->enanos_extras[0], &config_leida->enanos_extras[1],
               &config_leida->enanos_extras[2]);
    } else if (strcmp(palabra_clave, ELFOS_EXTRA) == 0) {
        fscanf(archivo, FORMATO_EXTRA, &config_leida->elfos_extras[0], &config_leida->elfos_extras[1],
               &config_leida->elfos_extras[2]);
    } else if (strcmp(palabra_clave, ENANOS_ANIMO) == 0) {
        fscanf(archivo, FORMATO_ANIMO, &config_leida->fallo_enanos, &config_leida->critico_enanos);
    } else if (strcmp(palabra_clave, ELFOS_ANIMO) == 0) {
        fscanf(archivo, FORMATO_ANIMO, &config_leida->fallo_elfos, &config_leida->critico_elfos);
    } else if (strcmp(palabra_clave, VELOCIDAD) == 0) {
        fscanf(archivo, FORMATO_VELOCIDAD, &config_leida->velocidad_juego);
    } else if (strcmp(palabra_clave, CAMINOS) == 0) {
        fscanf(archivo, FORMATO_CAMINOS, config_leida->ruta_caminos);
    }
}

/*
*Funcionamiento: asigna -1 a todos los campos de configuracion
*/
void configuracion_vacia(configuracion_t *configuracion) {

    configuracion->resistencia_1 = NO_INGRESADO;
    configuracion->resistencia_2 = NO_INGRESADO;

    configuracion->critico_enanos = NO_INGRESADO;
    configuracion->critico_elfos = NO_INGRESADO;

    configuracion->fallo_enanos = NO_INGRESADO;
    configuracion->fallo_elfos = NO_INGRESADO;
    configuracion->velocidad_juego = NO_INGRESADO;
    strcpy(configuracion->ruta_caminos, RUTA_NO_INGRESADA);

    for (int i = 0; i < CANTIDAD_NIVELES; i++) {

        configuracion->enanos_inicio[i] = NO_INGRESADO;
        configuracion->elfos_inicio[i] = NO_INGRESADO;
    }
    for (int i = 0; i < CANTIDAD_EXTRAS; i++) {

        configuracion->enanos_extras[i] = NO_INGRESADO;
        configuracion->elfos_extras[i] = NO_INGRESADO;
    }
}

/*
*Funcionamiento: si el archivo existe lee los valores de configuracion que contiene
*	caso contrario crea una configuracion con todos sus campos en -1
*/
configuracion_t obtener_configuracion(char ruta[MAX_RUTA]) {


    configuracion_t configuracion_leida;

    FILE *archivo = fopen(ruta, "r");

    if (archivo == NULL) {

        printf("Archivo no encontrado. Se utilizaran valores por default\n");

        printf("El juego iniciara solo\n");

        configuracion_vacia(&configuracion_leida);

        detener_el_tiempo(TIEMPO_INICIO);
    } else {

        char palabra_clave[MAX_CLAVE];

        int contador = 0;

        while (contador < NUMERO_CLAVES_CONFIG) {

            fscanf(archivo, FORMATO_CLAVE, palabra_clave);

            determina_formato_clave(palabra_clave, &configuracion_leida, archivo);

            contador++;
        }
        fclose(archivo);
    }
    return configuracion_leida;
}

/*
*Funcionamiento: pide al usuario el ingreso de las resistencias a la torre
*	y las asigna a config
*/
void ingreso_resistencia(configuracion_t *config) {
    printf("Ingrese la resistencia de la torres 1: ");
    scanf("%i", &config->resistencia_1);

    printf("Ingrese la resistencia de la torres 2: ");
    scanf("%i", &config->resistencia_2);
}

/*
*Funcionamiento: pide al usuario el ingreso de la probabilidad de fallo 
*	y probabilidad de golpe critico y las asigna a config
*/
void ingreso_animos(int *fallo, int *critico, char tipo[MAX_TIPO]) {
    printf("Ingrese el porcetaje de critico de los %s: ", tipo);
    scanf("%i", critico);
    printf("Ingrese el porcetaje de fallo de los %s: ", tipo);
    scanf("%i", fallo);
}

/*
*Recibe:
*	cantidad_inicio: vector con la cantidad de defensores iniciales de cada nivel
.	tipo: tipo de defensor (elfo o enano)
*Funcionamiento: pide al usuario el ingreso de los defensores iniciales 
*	de cada nivel y las asigna a config
*/
void ingreso_cantidad_inicio(int cantidad_inicio[CANTIDAD_NIVELES], char tipo[MAX_TIPO]) {

    for (int i = 0; i < CANTIDAD_NIVELES; i++) {

        printf("Ingrese la cantidad de %s iniciales en el nivel %i: ", tipo, i + 1);
        scanf("%i", &cantidad_inicio[i]);
    }
}

/*
*Recibe:
*	cantidad_extra: vector con la cantidad de defensores extra y costo a cada una de las torres
.	tipo: tipo de defensor (elfo o enano)
*Funcionamiento: pide al usuario el ingreso de los defensores extras y el costo de estos a cada torre
*	y las asigna a config
*/
void ingreso_cantidad_extra(int cantidad_extra[CANTIDAD_EXTRAS], char tipo[MAX_TIPO]) {

    printf("Ingrese la cantidad de %s extras en el nivel: ", tipo);
    scanf("%i", &cantidad_extra[0]);

    printf("Ingrese el costo de los %s en la torre 1: ", tipo);
    scanf("%i", &cantidad_extra[1]);

    printf("Ingrese la costo de los %s en la torre 2: ", tipo);
    scanf("%i", &cantidad_extra[2]);
}

/*
* Funcionamiento: pide al usuario el ingreso de la velocidad del juego
*	y la asigna a config
*/
void ingreso_velocidad(float *velocidad) {
    char ingreso_usuario[MAX_FORMATO];

    printf("Ingrese la velocidad del juego: ");
    scanf("%s", ingreso_usuario);
    *velocidad = (float) atof(ingreso_usuario);
}

/*
* Funcionamiento: pide al usuario el ingreso de la ruta del archivo de caminos
*	y la asigna a config
*/
void ingreso_ruta_camino(char ruta_caminos[MAX_RUTA]) {

    printf("Ingrese la ruta del archivo de caminos: ");

    scanf("%s", ruta_caminos);
}

/*
* Funcionamiento: llama a las respectivas funciones para pedir la informacion de los enanos
*	y las asigna a config
*/
void ingreso_info_enanos(configuracion_t *config) {
    printf("Valores iniciales de los enanos\n");

    ingreso_cantidad_inicio(config->enanos_inicio, ENANOS);

    system("clear");

    printf("Valores extras de los enanos\n");

    ingreso_cantidad_extra(config->enanos_extras, ENANOS);

    system("clear");

    printf("Valores de combate de los enanos\n");

    ingreso_animos(&config->fallo_enanos, &config->critico_enanos, ENANOS);
}

/*
* Funcionamiento: llama a las respectivas funciones para pedir al usuario la informacion de los elfos
*	y las asigna a config
*/
void ingreso_info_elfos(configuracion_t *config) {
    printf("Valores iniciales de los elfos\n");

    ingreso_cantidad_inicio(config->elfos_inicio, ELFOS);

    system("clear");

    printf("Valores extras de los elfos\n");

    ingreso_cantidad_extra(config->elfos_extras, ELFOS);

    system("clear");

    printf("Valores de combate de los elfos\n");

    ingreso_animos(&config->fallo_elfos, &config->critico_elfos, ELFOS);
}

/*
* Funcionamiento: llama a las respectivas funciones para pedir al usuario la informacion 
*	de la configuracion
*/
void ingresar_configuracion(configuracion_t *config_usuario) {
    system("clear");
    printf("Si no desea asignar un valor coloque -1\n");
    ingreso_resistencia(config_usuario);

    system("clear");
    printf("Si no desea asignar un valor coloque -1\n");
    ingreso_info_enanos(config_usuario);

    system("clear");
    printf("Si no desea asignar un valor coloque -1\n");
    ingreso_info_elfos(config_usuario);

    system("clear");
    printf("Si no desea asignar un valor coloque -1\n");
    ingreso_velocidad(&config_usuario->velocidad_juego);

    ingreso_ruta_camino(config_usuario->ruta_caminos);
}

/*
* Funcionamiento: muestra la configuracion pasada por parametro
*/
void mostrar_configuracion(configuracion_t config) {
    printf("Configuracion guardada: \n");

    printf("\nResistencia torres 1 %i\n", config.resistencia_1);

    printf("Resistencia torres 2 %i\n", config.resistencia_2);

    printf("\nEnanos iniciales: \nNivel 1: %i\n Nivel 2: %i\n Nivel 3: %i\n Nivel 4: %i\n", config.enanos_inicio[0],
           config.enanos_inicio[1],
           config.enanos_inicio[2], config.enanos_inicio[3]);

    printf("\nElfos iniciales: \nNivel 1: %i\n Nivel 2: %i\n Nivel 3: %i\n Nivel 4: %i\n", config.elfos_inicio[0],
           config.elfos_inicio[1],
           config.elfos_inicio[2], config.elfos_inicio[3]);

    printf("\nEnanos extras: %i\n \nCosto enanos a la torre 1: %i \nCosto enanos a la torre 2: %i\n",
           config.enanos_extras[0], config.enanos_extras[1],
           config.enanos_extras[2]);

    printf("\nElfos extras: %i\n \nCosto elfos a la torre 1: %i \nCosto elfos a la torre 2: %i\n",
           config.elfos_extras[0], config.elfos_extras[1],
           config.elfos_extras[2]);

    printf("\nCritico enano %i\n", config.critico_enanos);
    printf("Fallo enano %i\n", config.fallo_enanos);

    printf("\nCritico elfo %i\n", config.critico_elfos);
    printf("Fallo elfo %i\n", config.fallo_elfos);

    printf("\nVelocidad del juego %2.6f\n", config.velocidad_juego);
    printf("\nRuta caminos %s\n", config.ruta_caminos);
}

/*
* Funcionamiento: guarda la configuracion en un un archivo con la ruta pasada por
* 	parametro.
*	Si el archivo no exite lo crea y si existe lo sobreescribe
*/
void guardar_configuracion(configuracion_t config, char ruta[MAX_RUTA]) {

    char formato[MAX_FORMATO];

    FILE *archivo = fopen(ruta, "w");


    fprintf(archivo, strcat(strcpy(formato, RESISTENCIA), FORMATO_TORRES),
            config.resistencia_1, config.resistencia_2);


    fprintf(archivo, strcat(strcpy(formato, ENANOS_INICIO), FORMATO_INICIO),
            config.enanos_inicio[0], config.enanos_inicio[1], config.enanos_inicio[2], config.enanos_inicio[3]);

    fprintf(archivo, strcat(strcpy(formato, ELFOS_INICIO), FORMATO_INICIO),
            config.elfos_inicio[0], config.elfos_inicio[1], config.elfos_inicio[2], config.elfos_inicio[3]);


    fprintf(archivo, strcat(strcpy(formato, ENANOS_EXTRA), FORMATO_EXTRA),
            config.enanos_extras[0], config.enanos_extras[1], config.enanos_extras[2]);

    fprintf(archivo, strcat(strcpy(formato, ELFOS_EXTRA), FORMATO_EXTRA),
            config.elfos_extras[0], config.elfos_extras[1], config.elfos_extras[2]);


    fprintf(archivo, strcat(strcpy(formato, ENANOS_ANIMO), FORMATO_ANIMO), config.fallo_enanos, config.critico_enanos);

    fprintf(archivo, strcat(strcpy(formato, ELFOS_ANIMO), FORMATO_ANIMO), config.fallo_elfos, config.critico_elfos);


    fprintf(archivo, strcat(strcpy(formato, VELOCIDAD), FORMATO_VELOCIDAD), config.velocidad_juego);

    fprintf(archivo, strcat(strcpy(formato, CAMINOS), FORMATO_CAMINOS), config.ruta_caminos);

    fclose(archivo);
}

/*
* Funcionamiento: recorre el archivo hasta encontrar un valor menor al puntaje o hasta
*	llegar al final del archivo y escribe el valor de puntaje y nombre 
* 	Si los puntajes coinciden los escribe alfabeticamente
*/
void
ordenar_archivo(FILE *archivo_originial, FILE *archivo_auxiliar, char nombre_agregar[MAX_RUTA], int puntaje_agregar) {
    char nombre_leido[MAX_RUTA];
    char nombre_auxiliar[MAX_RUTA];
    int puntaje_leido;
    int puntaje_auxiliar;

    while (!feof(archivo_originial)) {

        fscanf(archivo_originial, FORMATO_LEER_RANKING, nombre_leido, &puntaje_leido);

        if (puntaje_leido > puntaje_agregar) {

            fprintf(archivo_auxiliar, FORMATO_ESCRIBIR_RANKING, nombre_leido, puntaje_leido);

        } else if (puntaje_leido < puntaje_agregar) {

            puntaje_auxiliar = puntaje_leido;

            strcpy(nombre_auxiliar, nombre_leido);

            fprintf(archivo_auxiliar, FORMATO_ESCRIBIR_RANKING, nombre_agregar, puntaje_agregar);

            puntaje_agregar = puntaje_auxiliar;

            strcpy(nombre_agregar, nombre_auxiliar);
        } else {

            if (strcmp(nombre_leido, nombre_agregar) < 0) {

                fprintf(archivo_auxiliar, FORMATO_ESCRIBIR_RANKING, nombre_leido, puntaje_leido);
            } else {
                puntaje_auxiliar = puntaje_leido;

                strcpy(nombre_auxiliar, nombre_leido);

                fprintf(archivo_auxiliar, FORMATO_ESCRIBIR_RANKING, nombre_agregar, puntaje_agregar);

                puntaje_agregar = puntaje_auxiliar;

                strcpy(nombre_agregar, nombre_auxiliar);
            }
        }

    }
    fprintf(archivo_auxiliar, FORMATO_ESCRIBIR_RANKING, nombre_agregar, puntaje_agregar);
}

/*
* Funcionamiento: guarda el puntaje y el nombre pasado por parametro en la linea
*	correspondiente para que el archivo quede en orden descendente de puntajes
*/
void guardar_ranking(char ruta[MAX_RUTA], char nombre_agregar[MAX_RUTA], int puntaje_agregar) {

    char *ruta_auxiliar = RUTA_RANKING_AUXILIAR;

    FILE *archivo_originial = fopen(ruta, "r");

    if (archivo_originial == NULL) {
        FILE *archivo_originial = fopen(ruta, "w");
        fprintf(archivo_originial, FORMATO_ESCRIBIR_RANKING, nombre_agregar, puntaje_agregar);
        fclose(archivo_originial);
    } else {

        FILE *archivo_auxiliar = fopen(ruta_auxiliar, "w");
        ordenar_archivo(archivo_originial, archivo_auxiliar, nombre_agregar, puntaje_agregar);

        fclose(archivo_auxiliar);
        fclose(archivo_originial);
        rename(ruta_auxiliar, ruta);
    }
}

/*
* Recibe:
*	cantidad_listar: cantidad de puntajes a mostrar
* Funcionamiento: muestra la cantidad de puntajes indicados
* o todos los que hay en el archivo siempre que este exista
*/
void listar_ranking(char ruta[MAX_RUTA], int cantidad_listar) {
    int contador = 0;
    FILE *archivo = fopen(ruta, "r");

    if (archivo == NULL) {
        perror("No existe un archivo para esa configuracion\n");
    } else {
        char nombre_leido[MAX_RUTA];
        int puntaje_leido;

        while (!feof(archivo) && contador != cantidad_listar) {
            fscanf(archivo, FORMATO_LEER_RANKING, nombre_leido, &puntaje_leido);
            printf("Posicion Nº: %i | Puntos: %i |  Nombre jugador: %s \n", contador + 1, puntaje_leido, nombre_leido);
            contador++;
        }
        fclose(archivo);
    }
}

/*
* Funcionamiento:
*	pide al usuario el ingreso de la configuracion
*	y guarda la misma en la ruta pasada por parametro
*
*/
void crear_configuracion(int argc, char *argv[]) {

    configuracion_t configuracion_usuario;

    char ruta[MAX_RUTA] = RUTA_CONFIG_DEFAULT;

    if (argc == 3) {

        strcpy(ruta, argv[2]);

        strcpy(configuracion_usuario.ruta_caminos, ruta);

        ingresar_configuracion(&configuracion_usuario);

        mostrar_configuracion(configuracion_usuario);

        guardar_configuracion(configuracion_usuario, ruta);
    }
}

/*
* Funcionamiento:
*	muestra los caminos de cada nivel
*/
void mostrar_caminos(camino_niveles_t caminos_niveles) {

    printf("Los caminos creados son\n");

    for (int i = 0; i < CANTIDAD_NIVELES; i++) {

        printf("\nNivel %i\n", i + 1);

        mostrar_tablero(caminos_niveles.caminos[i][0], caminos_niveles.tope_caminos[i][0],
                        caminos_niveles.caminos[i][1], caminos_niveles.tope_caminos[i][1], i + 1);
    }
}

/*
* Funcionamiento:
*	crea un archivo con la ruta pasada por consola
*	en el cual escribe los caminos que ingreso el usuario
*	Si no hay sufientes argumentos pasados por consola no realiza accion
*/
void crear_caminos(int argc, char *argv[]) {

    camino_niveles_t caminos_niveles;

    char ruta[MAX_RUTA] = RUTA_CAMINOS_DEFAULT;


    if (argc == 3) {
        strcpy(ruta, argv[2]);

        FILE *archivo = fopen(ruta, "w");
        ingresar_camino(&caminos_niveles);

        escribir_caminos(archivo, caminos_niveles);
        mostrar_caminos(caminos_niveles);

        fclose(archivo);
    }
}

/*
* Funcionamiento:
*	muestra la repeticion de una partida si existe el archivo
*	en la ruta pasada por parametro
*/
void ver_partida(char ruta[MAX_RUTA], float velocidad) {

    juego_t juego_leido;

    FILE *archivo = fopen(ruta, "r");

    if (archivo == NULL) {
        perror("Grabacion no encontrada");
    } else {

        fread(&juego_leido, sizeof(juego_t), 1, archivo);

        while (!feof(archivo)) {

            mostrar_juego(juego_leido);

            printf("\n\n············ ACTUALMENTE ESTA OBSERVANDO UNA REPETICION DE LA PARTIDA ············\n");

            detener_el_tiempo(velocidad);

            fread(&juego_leido, sizeof(juego_t), 1, archivo);
        }

        fclose(archivo);
    }
}


/*
* Funcionamiento:
*	asigna la ruta del archivo de grabacion y la velocidad
* 	de los parametros pasados por consola.
*	Si no recibe la ruta del archivo no realiza accion
*	Si no recibe la velocidad utiliza la velocidad por default
*/
void ver_repeticion(int argc, char *argv[]) {

    char ruta[MAX_RUTA] = RUTA_GRABACION_DEFAULT;

    float velocidad = VELOCIDAD_JUEGO_DEFAULT;

    char argumento[MAX_CLAVE];

    bool mostrar_grabacion = false;

    for (int i = 2; i < argc; i++) {

        strcpy(argumento, strtok(argv[i], SEPARADOR_ARGUMENTOS));

        if (strcmp(argumento, CLAVE_RUTA_GRABACION) == 0) {

            strcpy(ruta, strtok(NULL, SEPARADOR_ARGUMENTOS));

            mostrar_grabacion = true;

        } else if (strcmp(argumento, CLAVE_VELOCIDAD) == 0) {

            velocidad = (float) atof(strtok(NULL, SEPARADOR_ARGUMENTOS));
        }
    }
    if (mostrar_grabacion) {
        ver_partida(ruta, velocidad);
    }
}

/*
* Funcionamiento:
*	obtiene la ruta de configuracion y crea la ruta del
*	archivo ranking a abrir y obtiene la cantidad de 
*	de elementos a mostrar.
*/
void ver_ranking(int argc, char *argv[]) {

    char ruta[MAX_RUTA] = RUTA_RANKING_DEFAULT;

    char argumento[MAX_CLAVE];

    int cantidad_listar = NO_INGRESADO;

    for (int i = 2; i < argc; i++) {

        strcpy(argumento, strtok(argv[i], SEPARADOR_ARGUMENTOS));

        if (strcmp(argumento, CLAVE_RUTA_CONFIGURACION) == 0) {

            strcpy(ruta, RUTA_RANKING_USUARIO);

            strcat(ruta, strtok(strtok(NULL, SEPARADOR_ARGUMENTOS), SEPARADOR_TIPO_ARCHIVO));

            strcat(ruta, TIPO_CSV);
        } else if (strcmp(argumento, CLAVE_CANTIDAD_LISTAR) == 0) {

            cantidad_listar = atoi(strtok(NULL, SEPARADOR_ARGUMENTOS));
        }
    }

    listar_ranking(ruta, cantidad_listar);
}

/*
* Funcionamiento: obtiene la ruta donde debe guardarse el puntaje y el nombre
*	que debe ser ingresado por el usuario 
*/
void guardar_puntaje(char ruta_configuracion[MAX_RUTA], int puntaje) {

    char ruta_ranking[MAX_RUTA] = RUTA_RANKING_USUARIO;

    char nombre_usuario[MAX_CLAVE];

    strcat(strcat(ruta_ranking, strtok(ruta_configuracion, SEPARADOR_TIPO_ARCHIVO)), TIPO_CSV);

    printf("Obtuvo un puntaje de %i MendezPoints\n", puntaje);

    printf("Debemos guardar su nombre en nuestro ranking mundial\nIngrese su nombre: ");

    scanf("%s", nombre_usuario);

    guardar_ranking(ruta_ranking, nombre_usuario, puntaje);
}

/*
* Funcionamiento: determina la ruta del archivo configuracion y la ruta del
*	la repetucion  si la partida debe grabarse.
*/
void argumentos_jugar(int argc, char *argv[], char ruta_configuracion[MAX_RUTA], char ruta_grabacion[MAX_RUTA],
                      bool *partida_grabada) {

    char argumento[MAX_CLAVE];
    *partida_grabada = NO_GRABAR;

    for (int i = 2; i < argc; i++) {

        strcpy(argumento, strtok(argv[i], SEPARADOR_ARGUMENTOS));
        if (strcmp(argumento, CLAVE_RUTA_CONFIGURACION) == 0) {

            strcpy(ruta_configuracion, strtok(NULL, SEPARADOR_ARGUMENTOS));
        } else if (strcmp(argumento, CLAVE_RUTA_GRABACION) == 0) {

            strcpy(ruta_grabacion, strtok(NULL, SEPARADOR_ARGUMENTOS));
            *partida_grabada = GRABAR;
        }

    }
}

/*
* Funcionamiento: determina si el usuario ingreso la ruta de la configuracion
*	caso contrario asigna la configuracion por default, verifica si la partida debe
*	grabarse y en ese caso obtiene la ruta del archivo en el cual se grabara.
* Si en la configuracion usada no esta asignado la tura del archivo caminos se 
*	crean caminos de forma aleatoria
*/
void jugar(int argc, char *argv[]) {

    char ruta_grabacion[MAX_RUTA] = RUTA_GRABACION_DEFAULT;

    char ruta_configuracion[MAX_RUTA] = RUTA_CONFIG_DEFAULT;

    int puntaje;

    bool partida_grabada;

    argumentos_jugar(argc, argv, ruta_configuracion, ruta_grabacion, &partida_grabada);

    configuracion_t configuracion = obtener_configuracion(ruta_configuracion);


    FILE *archivo = fopen(configuracion.ruta_caminos, "r");

    camino_niveles_t caminos;

    if (archivo == NULL) {
        caminos_aleatorios(&caminos);

        mostrar_caminos(caminos);

        detener_el_tiempo(TIEMPO_CAMINOS);
    } else {

        leer_caminos(archivo, &caminos);
    }


    if (partida_grabada) {
        juego_grabando_partida(configuracion, caminos, ruta_grabacion, &puntaje);
    } else {
        juego_sin_grabar_partida(configuracion, caminos, &puntaje);
    }

    guardar_puntaje(ruta_configuracion, puntaje);
}

int main(int argc, char *argv[]) {

    if (argc > 1) {

        if (strcmp(CLAVE_CREAR_CONFIGURACION, argv[1]) == 0) {

            crear_configuracion(argc, argv);
        } else if (strcmp(CLAVE_REPETICION, argv[1]) == 0) {

            ver_repeticion(argc, argv);
        } else if (strcmp(CLAVE_RANKING, argv[1]) == 0) {

            ver_ranking(argc, argv);
        } else if (strcmp(CLAVE_CREAR_CAMINO, argv[1]) == 0) {

            crear_caminos(argc, argv);
        } else if (strcmp(CLAVE_JUGAR, argv[1]) == 0) {
            jugar(argc, argv);
        }
    }

    return 0;
}