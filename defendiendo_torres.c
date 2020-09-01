#include "defendiendo_torres.h"


const int RANGO_PROBABILIDAD_ENTERO = 100;
const int MINIMO_PROBABILIDAD = 0;

const int NIVEL_1 = 1;
const int NIVEL_2 = 2;
const int NIVEL_3 = 3;
const int NIVEL_4 = 4;

const int NUMERO_CAMINO_1 = 1;
const int NUMERO_CAMINO_2 = 2;

const int LIBRE = 0;
const int OCUPADO = -1;

const char CARACTER_ELFOS = 'L';
const char CARACTER_ENANOS = 'G';

const int MAXIMOS_ATAQUES_ELFO = 23;
const int MAXIMOS_ATAQUES_ENANOS = 1;
const int RANGO_ATAQUE_ENANO = 1;
const int RANGO_ATAQUE_ELFO = 3;
const int VIDA_BASE_ORCO = 200;
const int CRITICO_ENANO = 100;
const int CRITICO_ELFO = 70;

const int ATAQUE_BASE_ENANO = 60;
const int ATAQUE_BASE_ELFO = 30;

const int NO_ASIGANADA = -1;
const int SIN_VIDA = 0;

const int FALLA = 1;
const int NO_FALLA = 0;
const int INICIO = 0;

const int PERDIDO = -1;
const int GANADO = 1;
const int CONTINUANDO = 0;

const int LARGO_UN_CAMINO = 15;
const int LARGO_DOS_CAMINOS = 20;

const char CARACTER_VACIO = ' ';
const char CARACTER_ENTRADA = 'E';
const char CARACTER_CAMINO = '#';
const char CARACTER_CAMINO_2 = '=';
const char CARACTER_TORRE = 'T';
const char CARACTER_ORCOS = 'O';

const int SIN_ENEMIGOS = 0;
const int TORRE_1 = 1;
const int TORRE_2 = 2;

const int ES_CRITICO = 0;
const int NO_CRITICO = 1;

const int ALCANZA = 0;
const int NO_ALCANZA = 1;

const int MISMO_LUGAR = 0;

/*
* Recibe:
*	 rango: entero que determina el rango de los numeros. Debe ser mayor a 0
*	 minimo: entero a partir del cual comenzaran los numeros. Debe ser mayor a 0
* Devuelve:
*	 Numero entero entre minimo y minimo+rango
*/
int numero_aleatorio(int rango, int minimo) {

    return (rand() % rango + minimo);
}


/*
* Recibe:
*	 nivel: estructura del nivel actual actualizado
*	 indice: entero que representa la ubicacion del enemigo en vector enemigos	 
* Devuelve:
*	 la coordenada del enemigo en el tablero
*/
coordenada_t ubicar_orco(nivel_t nivel, int indice) {
    int camino_orco;
    int pos_orco;
    coordenada_t coordenada_orco;

    camino_orco = nivel.enemigos[indice].camino;
    pos_orco = nivel.enemigos[indice].pos_en_camino;

    if (camino_orco == NUMERO_CAMINO_1) {
        coordenada_orco = nivel.camino_1[pos_orco];
    } else if (camino_orco == NUMERO_CAMINO_2) {
        coordenada_orco = nivel.camino_2[pos_orco];
    }

    return coordenada_orco;
}

/*
 * Recibe un nivel con todas sus estructuras válidas. 
 * El nivel se dará por ganado cuando estén TODOS los orcos de ese 
 * nivel muertos (esto es, con vida menor o igual a 0).
 * Devolverá:
 * >  0 si el estado es jugando.
 * >  1 si el estado es ganado.
 */
int estado_nivel(nivel_t nivel) {
    int continuar;
    int contador_muertos;

    continuar = CONTINUANDO;
    contador_muertos = INICIO;

    for (int i = INICIO; i < nivel.tope_enemigos; i++) {
        if (nivel.enemigos[i].vida <= SIN_VIDA) {
            contador_muertos++;
        }
    }

    if (contador_muertos == nivel.max_enemigos_nivel) {
        continuar = GANADO;
    }

    return continuar;
}

/*
* Recibe:
*	 *nivel: puntero a la estructura del nivel actual actualizado
*	 posicion: coordenada en rango del tablero	 
* Devuelve:
*	 0 si la coordenada esta libre
*	 -1 si la coordenada esta ocupada
*/
int verifica_disponibilidad(nivel_t *nivel, coordenada_t posicion) {
    int tope_def;
    int tope_camino_1;
    int tope_camino_2;
    int disponible;
    coordenada_t pos_preguntada;

    tope_def = nivel->tope_defensores;
    tope_camino_1 = nivel->tope_camino_1;
    tope_camino_2 = nivel->tope_camino_2;

    disponible = LIBRE;

    for (int i = INICIO; i < tope_def; i++) {
        pos_preguntada = nivel->defensores[i].posicion;
        if (pos_preguntada.fil == posicion.fil && pos_preguntada.col == posicion.col) {
            disponible = OCUPADO;
        }
    }

    for (int i = INICIO; i < tope_camino_1; i++) {
        pos_preguntada = nivel->camino_1[i];
        if (pos_preguntada.fil == posicion.fil && pos_preguntada.col == posicion.col) {
            disponible = OCUPADO;
        }
    }

    for (int i = INICIO; i < tope_camino_2; i++) {
        pos_preguntada = nivel->camino_2[i];
        if (pos_preguntada.fil == posicion.fil && pos_preguntada.col == posicion.col) {
            disponible = OCUPADO;
        }
    }

    return disponible;
}


/*
 * Inicializará el juego, cargando la informacion de las torres y
 * los ataques críticos y fallo de enanos y elfos de la configuracion.
 * NO inicializará el primer nivel.
 */
void inicializar_juego(juego_t *juego, int viento, int humedad, char animo_legolas, char animo_gimli,
                       configuracion_t configuracion) {


    juego->torres.resistencia_torre_1 = configuracion.resistencia_1;

    juego->torres.resistencia_torre_2 = configuracion.resistencia_2;

    juego->torres.enanos_extra = configuracion.enanos_extras[0];

    juego->torres.elfos_extra = configuracion.elfos_extras[0];

    juego->critico_gimli = configuracion.critico_enanos;

    juego->critico_legolas = configuracion.critico_elfos;

    juego->fallo_legolas = configuracion.fallo_elfos;

    juego->fallo_gimli = configuracion.fallo_enanos;
}

/*
 * Recibe un nivel con todas sus estructuras válidas. 
 * El nivel se dará por ganado cuando estén TODOS los orcos de ese 
 * nivel muertos (esto es, con vida menor o igual a 0).
 * Devolverá:
 * >  0 si el estado es jugando.
 * >  1 si el estado es ganado.
 */
int estado_juego(juego_t juego) {
    int continuar;

    continuar = CONTINUANDO;

    if (juego.torres.resistencia_torre_1 <= SIN_VIDA) {
        continuar = PERDIDO;
    } else if (juego.torres.resistencia_torre_2 <= SIN_VIDA) {
        continuar = PERDIDO;
    } else if (juego.nivel_actual == NIVEL_4) {

        if (juego.nivel.max_enemigos_nivel == juego.nivel.tope_enemigos) {
            continuar = estado_nivel(juego.nivel);
        }
    }

    return continuar;
}

/* 
 * Agregará un defensor en el nivel recibido como parametro.
 * Devolverá:
 * >  0 si pudo agregar el defensor correctamente.
 * > -1 si no pudo (la coordenada es parte del camino de ese nivel, 
 * existe otro defensor, etc.)
 */
int agregar_defensor(nivel_t *nivel, coordenada_t posicion, char tipo) {
    int tope_def;
    int disponible;

    tope_def = nivel->tope_defensores;

    disponible = verifica_disponibilidad(nivel, posicion);

    if (disponible == LIBRE) {
        nivel->defensores[tope_def].tipo = tipo;
        nivel->defensores[tope_def].posicion = posicion;

        if (tipo == CARACTER_ELFOS) {
            nivel->defensores[tope_def].fuerza_ataque = ATAQUE_BASE_ELFO;
        } else if (tipo == CARACTER_ENANOS) {
            nivel->defensores[tope_def].fuerza_ataque = ATAQUE_BASE_ENANO;
        }

        nivel->tope_defensores++;
    }

    return disponible;
}

/*
* Recibe:
*	 juego: estructura actualizada del juego
* Funcionamiento:
*	 Muestra la informacion de la estructura torre 
*	  y la cantidad de enemigos restantes en el juego
*/
void muestra_informacion(juego_t juego) {
    int orcos_restantes;

    printf("\nTorre %i:", TORRE_1);
    printf(" Vida actual: %i", juego.torres.resistencia_torre_1);
    printf("  Enanos extra disponibles %i", juego.torres.enanos_extra);


    printf("\nTorre %i:", TORRE_2);
    printf(" Vida actual: %i", juego.torres.resistencia_torre_2);
    printf("  Elfos extra disponibles %i", juego.torres.elfos_extra);


    orcos_restantes = juego.nivel.max_enemigos_nivel - juego.nivel.tope_enemigos;
    printf("\nEnemigos restastes: %i\n", orcos_restantes);
}

/*
* Recibe:
*	 origen: coordenada en rango de tablero
*	 destino: coordenada en rango de tablero
* Funcionamiento:
*	 Calcula la suma de la diferencia entre filas y columnas de
*	 las coordenadas de origen y destino
* Devuelve
*	 Numero entero de la distancia Manhatan entre las coordenadas
*/
int distancia_manhatam(coordenada_t origen, coordenada_t destino) {
    int distancia;
    int distancia_filas;
    int distancia_columnas;

    distancia_filas = abs(origen.fil - destino.fil);
    distancia_columnas = abs(origen.col - destino.col);

    distancia = distancia_columnas + distancia_filas;

    return distancia;
}

/*
* Recibe:
*	 enano: coordenada en rango de tablero del enano
*	 enemigo: coordenada en rango de tablero del enemigo
* Funcionamiento:
*	 Determina si el enemigo esta al alcanze del enano
* Devuelve
*	 0 si esta al alcance
*	 1 si no esta al alcance
*/
int entorno_enano(coordenada_t enano, coordenada_t enemigo) {
    int alcanza;
    int distancia_filas;
    int distancia_columnas;

    distancia_filas = abs(enano.fil - enemigo.fil);
    distancia_columnas = abs(enano.col - enemigo.col);

    alcanza = NO_ALCANZA;

    if (distancia_columnas + distancia_filas <= RANGO_ATAQUE_ENANO) {
        alcanza = ALCANZA;
    } else if (distancia_filas == RANGO_ATAQUE_ENANO && distancia_columnas == RANGO_ATAQUE_ENANO) {
        alcanza = ALCANZA;
    }

    return alcanza;
}

/*
* Recibe:
*	 elfo: coordenada en rango de tablero del elfo
*	 enemigo: coordenada en rango de tablero del enemigo
* Funcionamiento:
*	 Determina si el enemigo esta al alcanze del elfo
*	 en distancia Manhatam
* Devuelve
*	 0 si esta al alcance
*	 1 si no esta al alcance
*/
int entorno_elfo(coordenada_t elfo, coordenada_t enemigo) {
    int alcanza;
    int distancia;

    distancia = distancia_manhatam(elfo, enemigo);

    alcanza = NO_ALCANZA;

    if (distancia <= RANGO_ATAQUE_ELFO) {
        alcanza = ALCANZA;
    }

    return alcanza;
}

/*
* Devuelve
*	 Entero aleatorio entre 200 y 300
*/
int vida_orco() {
    int vida;

    vida = VIDA_BASE_ORCO;

    vida += numero_aleatorio(RANGO_PROBABILIDAD_ENTERO, MINIMO_PROBABILIDAD);

    return vida;
}

/*
* Recibe:
*	 probabilidad_ataque_critico: entero mayor o igual a 0 
*	 y menor o igual a 100 
* Funcionamiento:
*	 Obtiene un numero entero aleatorio entre 0 y 100 y lo 
*	 compara con probabilidad_ataque_critico
* Devuelve
*	 0 si el numero es menor a probabilidad_ataque_critico
*	 1 si el numero es mayor a probabilidad_ataque_critico
*/
int determina_critico(int probabilidad_ataque_critico) {
    int aleatorio;
    int critico;

    critico = NO_CRITICO;

    aleatorio = numero_aleatorio(RANGO_PROBABILIDAD_ENTERO, MINIMO_PROBABILIDAD);
    if (aleatorio < probabilidad_ataque_critico) {
        critico = ES_CRITICO;
    }

    return critico;
}

/*
* Recibe:
*	 probabilidad: entero mayor o igual a 0 
*	 y menor o igual a 100 
* Funcionamiento:
*	 Obtiene un numero entero aleatorio entre 0 y 100 y lo 
*	 compara con probabilidad
* Devuelve
*	 0 si el numero es menor a probabilidad
*	 1 si el numero es mayor a probabilidad
*/
int determina_fallo(int probabilidad) {
    int aleatorio;
    int fallo;

    fallo = NO_FALLA;

    aleatorio = numero_aleatorio(RANGO_PROBABILIDAD_ENTERO, MINIMO_PROBABILIDAD);
    if (aleatorio < probabilidad) {
        fallo = FALLA;
    }

    return fallo;
}

/*
* Recibe:
*	 *juego: puntero a la estructura actualizada del juego
*	 indice_orco: entero con la posicion del enemigo en el vector enemigos
*	 alcanzado: entero 0 o 1
*	 danio_defensor: entero mayor o igual a 0
*	 fallo: entero 0 o 1
*	 *contador_ataques: puntero al contador de ataques realizados por el defensor 
* Funcionamiento:
*	 Si alcanzado es 0 suma 1 a contador_ataques sin importar fallo
*	 Si tambien fallo es 0  resta danio_defensor a la 
*	 vida del enemigo 
*	 Asigna 0 a la vida del enemigo si esta es negativa
*/
void
organiza_ataque(juego_t *juego, int indice_orcos, int alcanzado, int danio_defensor, int fallo, int *contador_ataques) {

    if (alcanzado == ALCANZA && juego->nivel.enemigos[indice_orcos].vida > SIN_VIDA) {
        *contador_ataques = *contador_ataques + 1;

        if (fallo == NO_FALLA) {
            juego->nivel.enemigos[indice_orcos].vida -= danio_defensor;
        }
        if (juego->nivel.enemigos[indice_orcos].vida < SIN_VIDA) {
            juego->nivel.enemigos[indice_orcos].vida = SIN_VIDA;
        }
    }
}

/*
* Recibe:
*	 *juego: puntero a la estructura actualizada del juego
*	 indice_elfo: entero con la posicion del elfo en el vector defensores 
* Funcionamiento:
*	 Recorre cada elemento del vector de enemigos excepto que se llegue al maximo
*	 de ataques.
*	 Establece las condiciones del ataque para cada enemigo. alcanzado,fallo,critico y danio
*/
void ataque_elfo(juego_t *juego, int indice_elfo) {
    int indice_orcos;
    int alcanzado;
    int contador_ataques;
    int critico_defensor;
    int danio_defensor;
    int fallo;
    int tope_orcos;
    coordenada_t posicion_elfo;
    coordenada_t posicion_orco;

    tope_orcos = juego->nivel.tope_enemigos;

    indice_orcos = INICIO;
    contador_ataques = INICIO;

    while (contador_ataques < MAXIMOS_ATAQUES_ELFO && indice_orcos < tope_orcos) {

        fallo = determina_fallo(juego->fallo_legolas);
        critico_defensor = determina_critico(juego->critico_legolas);

        if (critico_defensor == ES_CRITICO) {
            danio_defensor = CRITICO_ELFO;
        } else {
            danio_defensor = juego->nivel.defensores[indice_elfo].fuerza_ataque;
        }

        posicion_elfo = juego->nivel.defensores[indice_elfo].posicion;
        posicion_orco = ubicar_orco(juego->nivel, indice_orcos);

        alcanzado = entorno_elfo(posicion_elfo, posicion_orco);

        organiza_ataque(juego, indice_orcos, alcanzado, danio_defensor, fallo, &contador_ataques);

        indice_orcos++;
    }
}

/*
* Recibe:
*	 *juego: puntero a la estructura actualizada del juego
*	 indice_elfo: entero con la posicion del elfo en el vector defensores 
* Funcionamiento:
*	 Recorre cada elemento del vector de enemigos excepto que se llegue al maximo
*	 de ataques.
*	 Establece las condiciones del ataque para todos los enemigos. alcanzado,fallo,critico y danio
*/
void ataque_enano(juego_t *juego, int indice_enano) {
    int indice_orcos;
    int alcanzado;
    int tope_orcos;
    int contador_ataques;
    int critico_defensor;
    int danio_defensor;
    int fallo;
    coordenada_t posicion_enano;
    coordenada_t posicion_orco;

    indice_orcos = INICIO;
    contador_ataques = INICIO;

    tope_orcos = juego->nivel.tope_enemigos;

    fallo = determina_fallo(juego->fallo_gimli);
    critico_defensor = determina_critico(juego->critico_gimli);

    if (critico_defensor == ES_CRITICO) {
        danio_defensor = CRITICO_ENANO;
    } else {
        danio_defensor = juego->nivel.defensores[indice_enano].fuerza_ataque;
    }

    while (contador_ataques < MAXIMOS_ATAQUES_ENANOS && indice_orcos < tope_orcos) {

        posicion_enano = juego->nivel.defensores[indice_enano].posicion;
        posicion_orco = ubicar_orco(juego->nivel, indice_orcos);

        alcanzado = entorno_enano(posicion_enano, posicion_orco);

        organiza_ataque(juego, indice_orcos, alcanzado, danio_defensor, fallo, &contador_ataques);

        indice_orcos++;
    }
}

/*
* Recibe:
*	 *juego: puntero a la estructura actualizada del juego
*	 defensor: caracter del tipo de defensor 
* Funcionamiento:
*	 Recorre cada elemento del vector defensores y determina si
*	 el tipo de defensor es el del turno correspondiente y realiza
*	 su respectivo ataque	 
*/
void ataque_defensores(juego_t *juego, char defensor) {
    for (int indice = INICIO; indice < juego->nivel.tope_defensores; indice++) {

        if (juego->nivel.defensores[indice].tipo == defensor && defensor == CARACTER_ELFOS) {
            ataque_elfo(juego, indice);
        } else if (juego->nivel.defensores[indice].tipo == defensor && defensor == CARACTER_ENANOS) {
            ataque_enano(juego, indice);
        }
    }
}

/*
* Recibe:
*	 mis_enemigos: vector de enemigos actualizado
*	 tope_enemigos: entero del tope del vector enemigos
*	 camino_enemigo: entero del camino del enemigo. 1 o 2
*	 tope_camino: entero del tope del vector camino 
* Funcionamiento:
*	 Recorre cada elemento del vector enemigos hasta tope_enemigos-1
*	 Si su vida es mayor a 0 y pertenece al camino correspondiente
*	 suma 1 a pos_en_camino.
*/
void mueve_orcos(enemigo_t mis_enemigos[MAX_ENEMIGOS], int tope_enemigos, int camino_enemigo, int tope_camino) {
    for (int i = INICIO; i < tope_enemigos; i++) {

        if (mis_enemigos[i].camino == camino_enemigo && mis_enemigos[i].vida > SIN_VIDA) {

            if (mis_enemigos[i].pos_en_camino < tope_camino - 1) {
                mis_enemigos[i].pos_en_camino++;
            }
        }
    }
}

/*
* Recibe:
*	 mis_enemigos: vector de enemigos actualizado
*	 *tope_enemigos: puntero al entero del tope del vector enemigos
*	 camino_enemigo: entero del camino del enemigo. 1 o 2
*	 tope_camino: entero del tope del vector camino 
* Funcionamiento:
*	 Agrega un enemigo al vector enemigos con todas sus estructuras validas
*	 menos posicion que se inicia en -1
*	 Una vez agregado se modifica tope_enemigos y se mueven todos
*/
void agrega_enemigo(enemigo_t mis_enemigos[MAX_ENEMIGOS], int *tope_enemigos, int camino_enemigo, int tope_camino) {
    enemigo_t enemigo_agregado;

    enemigo_agregado.vida = vida_orco();
    enemigo_agregado.camino = camino_enemigo;
    enemigo_agregado.pos_en_camino = NO_ASIGANADA;
    mis_enemigos[*tope_enemigos] = enemigo_agregado;
    *tope_enemigos += 1;

    mueve_orcos(mis_enemigos, *tope_enemigos, camino_enemigo, tope_camino);
}

/*
* Recibe:
*	 *juego: puntero a la estructura actualizada del juego
*	 indice_enemigo: entero de la ubicacion del enemigo en el vector enemigos
*	 torre: entero con el numero de la torres. Debe ser 1 o 2
* Funcionamiento:
*	 Si las coordenadas del enemigo en el camino 1 y la torre 1 o 2 son iguales y el enemigo
*	 tiene vida mayor a 0 resta su vida a la resistencia de la torre correspondiente
*	 La vida del enemigo pasa a ser 0.
*/
void ataque_camino_1(juego_t *juego, int indice_enemigo, int torre) {
    int distancia;
    int tope_camino;
    enemigo_t enemigo;

    tope_camino = juego->nivel.tope_camino_1;

    coordenada_t pos_enemigo;
    coordenada_t pos_torre;

    enemigo = juego->nivel.enemigos[indice_enemigo];

    pos_enemigo = juego->nivel.camino_1[enemigo.pos_en_camino];
    pos_torre = juego->nivel.camino_1[tope_camino - 1];
    distancia = distancia_manhatam(pos_torre, pos_enemigo);

    if (enemigo.vida > SIN_VIDA && distancia == MISMO_LUGAR) {
        if (torre == TORRE_1) {
            juego->torres.resistencia_torre_1 -= enemigo.vida;
        } else {
            juego->torres.resistencia_torre_2 -= enemigo.vida;
        }

        juego->nivel.enemigos[indice_enemigo].vida = SIN_VIDA;

        if (juego->torres.resistencia_torre_1 < SIN_VIDA) {
            juego->torres.resistencia_torre_1 = SIN_VIDA;
        }

        if (juego->torres.resistencia_torre_2 < SIN_VIDA) {
            juego->torres.resistencia_torre_2 = SIN_VIDA;
        }
    }
}

/*
* Recibe:
*	 *juego: puntero a la estructura actualizada del juego
*	 indice_enemigo: entero de la ubicacion del enemigo en el vector enemigos
* Funcionamiento:
*	 Si las coordenadas del enemigo en el camino 2 y la torre 2 son iguales y el enemigo
*	 tiene vida mayor a 0 resta su vida a la resistencia de la torre correspondiente
*	 La vida del enemigo pasa a ser 0.
*/
void ataque_camino_2(juego_t *juego, int indice_enemigo) {
    int distancia;
    int tope_camino;
    enemigo_t enemigo;
    coordenada_t pos_enemigo;
    coordenada_t pos_torre;

    tope_camino = juego->nivel.tope_camino_2;

    enemigo = juego->nivel.enemigos[indice_enemigo];

    pos_enemigo = juego->nivel.camino_2[enemigo.pos_en_camino];
    pos_torre = juego->nivel.camino_2[tope_camino - 1];
    distancia = distancia_manhatam(pos_torre, pos_enemigo);

    if (enemigo.vida > SIN_VIDA && distancia == MISMO_LUGAR) {
        juego->torres.resistencia_torre_2 -= enemigo.vida;

        juego->nivel.enemigos[indice_enemigo].vida = SIN_VIDA;
    }
    if (juego->torres.resistencia_torre_2 < SIN_VIDA) {
        juego->torres.resistencia_torre_2 = SIN_VIDA;
    }
}

/*
* Recibe:
*	 *juego: puntero a la estructura actualizada del juego
* Funcionamiento:
*	 Recorre cada elemento del vector enemigos
*	 Determina el nivel en el que se encuentra con lo que
*	 establece que torre se ataca y por que camino
*/
void ataque_a_torres(juego_t *juego) {
    for (int i = INICIO; i < juego->nivel.tope_enemigos; i++) {

        if (juego->nivel_actual == NIVEL_1) {
            ataque_camino_1(juego, i, TORRE_1);
        } else if (juego->nivel_actual == NIVEL_2) {
            ataque_camino_1(juego, i, TORRE_2);
        } else {
            if (juego->nivel.enemigos[i].camino == NUMERO_CAMINO_1) {
                ataque_camino_1(juego, i, TORRE_1);
            } else {
                ataque_camino_2(juego, i);
            }
        }
    }
}

/*
 * Jugará un turno y dejará el juego en el estado correspondiente.
 * Harán su jugada enanos, elfos y orcos en ese orden.
 */
void jugar_turno(juego_t *juego) {

    ataque_defensores(juego, CARACTER_ENANOS);
    ataque_defensores(juego, CARACTER_ELFOS);

    if (juego->nivel.tope_enemigos < juego->nivel.max_enemigos_nivel) {
        agrega_enemigo(juego->nivel.enemigos, &(juego->nivel.tope_enemigos), NUMERO_CAMINO_1,
                       juego->nivel.tope_camino_1);
    } else {
        mueve_orcos(juego->nivel.enemigos, juego->nivel.tope_enemigos, NUMERO_CAMINO_1,
                    juego->nivel.tope_camino_1);
    }

    if (juego->nivel_actual > NIVEL_2) {
        if (juego->nivel.tope_enemigos < juego->nivel.max_enemigos_nivel) {
            agrega_enemigo(juego->nivel.enemigos, &(juego->nivel.tope_enemigos), NUMERO_CAMINO_2,
                           juego->nivel.tope_camino_2);
        } else {
            mueve_orcos(juego->nivel.enemigos, juego->nivel.tope_enemigos, NUMERO_CAMINO_2,
                        juego->nivel.tope_camino_2);
        }
    }
    ataque_a_torres(juego);
}

/*
* Recibe:
*	 nivel_actual: entero del nivel en el que se encuentra
*	 el juego. Debe ser entre 1 y 4
* Funcionamiento:
*	 Determina el largo del tablero
*/
int verificar_largo(int nivel_actual) {
    int largo;

    if (nivel_actual == NIVEL_1 || nivel_actual == NIVEL_2) {
        largo = LARGO_UN_CAMINO;
    } else {
        largo = LARGO_DOS_CAMINOS;
    }

    return largo;
}

/*
* Recibe
* largo_tablero: entero mayor a 0
* Funcionamiento: muestra la parte superior
*	del tablero
*/
void tablero_superior(int largo_tablero) {
    printf("\t");
    for (int i = INICIO; i < largo_tablero; i++) {
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
void tablero_inferior(int largo_tablero) {

    for (int i = INICIO; i < largo_tablero; i++) {
        printf("|¯¯¯");
    }
    printf("|¯¯¯¯|\n\t");
    for (int i = INICIO; i < largo_tablero; i++) {

        if (i < 9) {
            printf("| %i ", i + 1);
        } else {
            printf("|%i ", i + 1);
        }
    }
    printf("|    |\n\t");
    for (int i = INICIO; i < largo_tablero; i++) {
        printf("¯¯¯¯");
    }
    printf("¯¯¯¯¯\n");
}

/*
* Funcionamiento:
*	asigna la la fila y columna de la coordenada recibida
*/
void coordenadas_tablero(coordenada_t camino, int *fila, int *columna) {
    *fila = camino.fil;
    *columna = camino.col;
}

/*
* Recibe
*	juego: estructura actualizada del juego
*	tablero: matriz de caracteres
*	largo_tablero: entero mayor a 0
* Funcionamiento: 
*	recorre todo el tablero asignando un caracter vacio a
*	cada coordenada del mismo
*	recorre ambos caminos asignando el caracter camino a 
*	cada coordenada de los mismos
*	recorre el vector de enemigos y asigna el caracter orco
*	a cada coordenada
*	recorre el vector de defensores y asigna el caracter correspondiente
*	dependiendo del tipo
*	Asigna el caracter de torre y entrada en las coordenadas correspondientes
*/
void asigna_caracteres(juego_t juego, char tablero[MAX_FILAS][MAX_COLUMNAS], int largo_tablero) {
    int fila;
    int columna;
    coordenada_t coor_orco;
    for (int i = INICIO; i < largo_tablero; i++) {
        for (int j = INICIO; j < largo_tablero; j++) {
            tablero[i][j] = CARACTER_VACIO;
        }
    }

    for (int i = INICIO; i < juego.nivel.tope_camino_1; i++) {
        coordenadas_tablero(juego.nivel.camino_1[i], &fila, &columna);
        tablero[fila][columna] = CARACTER_CAMINO;
    }

    for (int i = INICIO; i < juego.nivel.tope_camino_2; i++) {
        coordenadas_tablero(juego.nivel.camino_2[i], &fila, &columna);
        tablero[fila][columna] = CARACTER_CAMINO;
    }

    for (int i = INICIO; i < juego.nivel.tope_enemigos; i++) {
        if (juego.nivel.enemigos[i].vida > SIN_VIDA) {
            coor_orco = ubicar_orco(juego.nivel, i);
            coordenadas_tablero(coor_orco, &fila, &columna);
            tablero[fila][columna] = CARACTER_ORCOS;
        }
    }

    for (int i = INICIO; i < juego.nivel.tope_defensores; i++) {
        coordenadas_tablero(juego.nivel.defensores[i].posicion, &fila, &columna);
        tablero[fila][columna] = juego.nivel.defensores[i].tipo;
    }

    if (juego.nivel.tope_camino_1 != INICIO) {
        coordenadas_tablero(juego.nivel.camino_1[INICIO], &fila, &columna);
        tablero[fila][columna] = CARACTER_ENTRADA;
        coordenadas_tablero(juego.nivel.camino_1[juego.nivel.tope_camino_1 - 1], &fila, &columna);
        tablero[fila][columna] = CARACTER_TORRE;
    }

    if (juego.nivel.tope_camino_2 != INICIO) {
        coordenadas_tablero(juego.nivel.camino_2[INICIO], &fila, &columna);
        tablero[fila][columna] = CARACTER_ENTRADA;
        coordenadas_tablero(juego.nivel.camino_2[juego.nivel.tope_camino_2 - 1], &fila, &columna);
        tablero[fila][columna] = CARACTER_TORRE;
    }
}

/*
* Funcionamiento:
*	muestra el tablero con los separadores y numeros de filas y columnas
*/
void tablero_centro_numeros(char tablero[MAX_FILAS][MAX_COLUMNAS], int largo_tablero) {
    for (int i = INICIO; i < largo_tablero; i++) {
        for (int j = INICIO; j < largo_tablero; j++) {
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
 * Mostrará el mapa dependiendo del nivel en que se encuentra el jugador.
 */
void mostrar_juego(juego_t juego) {
    int largo_tablero;
    char tablero[MAX_FILAS][MAX_COLUMNAS];

    system("clear");
    muestra_informacion(juego);

    largo_tablero = verificar_largo(juego.nivel_actual);
    asigna_caracteres(juego, tablero, largo_tablero);

    tablero_superior(largo_tablero);
    tablero_centro_numeros(tablero, largo_tablero);
    tablero_inferior(largo_tablero);
}

