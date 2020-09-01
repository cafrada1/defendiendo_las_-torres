#include "animos.h"

/*Define el orden de las preguntas realizadas al usuario*/
const int PREGUNTA_DIA = 0;
const int PREGUNTA_HORA = 1;
const int PREGUNTA_PIE_LEGOLAS = 2;
const int PREGUNTA_CENA_LEGOLAS = 3;
const int PREGUNTA_SUENIO_LEGOLAS = 4;
const int PREGUNTA_PIE_GIMLI = 5;
const int PREGUNTA_CENA_GIMLI = 6;
const int PREGUNTA_SUENIO_GIMLI = 7;

/*Cantidad de preguntas necesarias a realizar*/
const int PREGUNTAS_TOTALES = 8;

/*Parametros validos de ingreso por el usuario*/

//Dias permitidos
const int MINIMO_DIAS_MES = 1;
const int MAXIMO_DIAS_MES = 30;

//Horas de sueño permitidas
const int MINIMO_HORAS_SUENIO = 0;
const int MAXIMO_HORAS_SUENIO = 12;

//Caracteres horas del dia
const char MANIANA = 'M';
const char TARDE = 'T';
const char NOCHE = 'N';

//Caracteres del pie
const char PIE_DERECHO = 'D';
const char PIE_IZQUIERDO = 'I';

//Caracteres de la cena anterior
const char ENSALADA = 'E';
const char HAMBURGUESA = 'H';
const char PIZZA = 'P';
const char GUISO = 'G';


/*Intervalo de dias para el viento*/
const int DIA_VIENTO_INFERIOR = 10;
const int DIA_VIENTO_MEDIO = 20;
const int DIA_VIENTO_SUPERIOR = 30;

/*Velocidades del viento en cada intervalo*/
const int VELOCIDAD_VIENTO_INFERIOR = 75;
const int VELOCIDAD_VIENTO_MEDIO = 50;
const int VELOCIDAD_VIENTO_SUPERIOR = 25;

/*Valores humedad segun la hora*/
const int HUMEDAD_MANIANA = 75;
const int HUMEDAD_TARDE = 25;
const int HUMEDAD_NOCHE = 50;

/*Intervalo de sueño*/
const int HORA_SUENIO_MINIMO = 4;
const int HORA_SUENIO_MEDIO = 8;

/*Valores de los puntajes para el animo*/
const int PUNTAJE_DERECHO = 10;
const int PUNTAJE_IZQUIERDO = 0;

const int PUNTAJE_ENSALADA = 20;
const int PUNTAJE_HAMBURGUESA = 15;
const int PUNTAJE_PIZZA = 10;
const int PUNTAJE_GUISO = 5;

const int PUNTAJE_SUENIO_MINIMO = 0;
const int PUNTAJE_SUENIO_MEDIO = 10;
const int PUNTAJE_SUENIO_MAXIMO = 20;

/*Intervalos para los estados de animo*/
const int PUNTAJE_ANIMO_MALO_MINIMO = 5;
const int PUNTAJE_ANIMO_MALO_MAXIMO = 20;

const int PUNTAJE_ANIMO_REGULAR_MINIMO = 21;
const int PUNTAJE_ANIMO_REGULAR_MAXIMO = 35;

const int PUNTAJE_ANIMO_BIEN_MINIMO = 36;
const int PUNTAJE_ANIMO_BIEN_MAXIMO = 50;

/*Caracteres para los estados de animo*/
const char ANIMO_MALO = 'M';
const char ANIMO_REGULAR = 'R';
const char ANIMO_BUENO = 'B';


/*Valores iniciales de las variables*/
const int DIA_DEL_MES_INICIAL = 0;

const int SUENIO_LEGOLAS_INICIAL = 0;
const int SUENIO_GIMLI_INICIAL = 0;

const char HORA_DIA_INICIAL = '0';

const char CENA_LEGOLAS_INICIAL = '0';
const char CENA_GIMLI_INICIAL = '0';

const char PIE_LEGOLAS_INICIAL = '0';
const char PIE_GIMLI_INICIAL = '0';

const int INGRESO_CORRECTO = 1;
const int INGRESO_INCORRECTO = 0;
const int INICIO_CONTADORES = 0;

/*
 *Analisis: valida si el numero esta entre los valores validos
 *Pre: valor_ingresado y numero_pregunta
 *Post: 1 si es valido y 0 si no lo es
 */
int comprobador_numeros(int valor_ingresado, int numero_pregunta) {

    int validado = INGRESO_INCORRECTO;
    int maximo;
    int minimo;

    if (numero_pregunta == PREGUNTA_DIA) {

        minimo = MINIMO_DIAS_MES;
        maximo = MAXIMO_DIAS_MES;
    } else {

        minimo = MINIMO_HORAS_SUENIO;
        maximo = MAXIMO_HORAS_SUENIO;

    }

    if (minimo <= valor_ingresado && valor_ingresado <= maximo) {

        validado = INGRESO_CORRECTO;
    }

    return validado;
}

/*
 *Analisis: valida si valor_ingresado es valido
 *Pre: valor ingresado,numero_pregunta
 *Post: 1 si es valido y 0 si no lo es
 */
int comprobador_letra(char valor_ingresado, int numero_pregunta) {

    int validado = INGRESO_INCORRECTO;

    if (numero_pregunta == PREGUNTA_HORA) {

        if (valor_ingresado == MANIANA || valor_ingresado == TARDE || valor_ingresado == NOCHE) {

            validado = INGRESO_CORRECTO;
        }
    } else if (numero_pregunta == PREGUNTA_PIE_LEGOLAS || numero_pregunta == PREGUNTA_PIE_GIMLI) {

        if (valor_ingresado == PIE_DERECHO || valor_ingresado == PIE_IZQUIERDO) {

            validado = INGRESO_CORRECTO;
        }
    } else if (numero_pregunta == PREGUNTA_CENA_LEGOLAS || numero_pregunta == PREGUNTA_CENA_GIMLI) {

        if (valor_ingresado == ENSALADA || valor_ingresado == HAMBURGUESA || valor_ingresado == PIZZA ||
            valor_ingresado == GUISO) {

            validado = INGRESO_CORRECTO;
        }
    }

    return validado;
}

/*
 *Analisis:Determina la velocidad del viento
 *Pre: Dia_del_mes en rango
 *Post: Valor de la velocidad del viento
 */
int velocidad_dia(int dia_del_mes) {

    int velocidad;

    if (dia_del_mes <= DIA_VIENTO_INFERIOR) {

        velocidad = VELOCIDAD_VIENTO_INFERIOR;
    } else if (DIA_VIENTO_INFERIOR < dia_del_mes && dia_del_mes <= DIA_VIENTO_MEDIO) {

        velocidad = VELOCIDAD_VIENTO_MEDIO;
    } else if (DIA_VIENTO_MEDIO < dia_del_mes && dia_del_mes <= DIA_VIENTO_SUPERIOR) {

        velocidad = VELOCIDAD_VIENTO_SUPERIOR;
    }

    return velocidad;
}

/*
 *Analisis:Determina el porcentaje de humedad
 *Pre: Hora dia en valores validos
 *Post: Valor de la humedad
 */
int humedad_hora(char hora_dia) {

    int porcentaje;

    if (hora_dia == MANIANA) {

        porcentaje = HUMEDAD_MANIANA;
    } else if (hora_dia == TARDE) {

        porcentaje = HUMEDAD_TARDE;
    } else if (hora_dia == NOCHE) {

        porcentaje = HUMEDAD_NOCHE;
    }

    return porcentaje;
}

/*
 *Analisis: Calcula el puntaje por el pie ingresado
 *Pre: pie tiene que estar validado
 *Post: puntaje por pie
 */
int puntaje_pie(char pie) {

    int puntaje;

    if (pie == PIE_DERECHO) {

        puntaje = PUNTAJE_DERECHO;
    } else if (pie == PIE_IZQUIERDO) {

        puntaje = PUNTAJE_IZQUIERDO;
    }

    return puntaje;
}


/*
 *Analisis: Calcula el puntaje por la cena ingresada
 *Pre: cena tiene que estar validado caracter valido
 *Post: puntaje por cena
 */
int puntaje_cena(char cena) {

    int puntaje;

    //Suma los puntos correspondientes a la ultina cena.
    if (cena == ENSALADA) {

        puntaje = PUNTAJE_ENSALADA;
    } else if (cena == HAMBURGUESA) {

        puntaje = PUNTAJE_HAMBURGUESA;
    } else if (cena == PIZZA) {

        puntaje = PUNTAJE_PIZZA;
    } else if (cena == GUISO) {

        puntaje = PUNTAJE_GUISO;
    }

    return puntaje;
}

/*
 *Analisis: Calcula el puntaje por las horas de suenio ingresadas
 *Pre: horas de suenio tiene que estar validada
 *Post: puntaje por las horas de suenio
 */
int puntaje_suenio(int horas_suenio) {

    int puntaje;

    if (horas_suenio <= HORA_SUENIO_MINIMO) {

        puntaje = PUNTAJE_SUENIO_MINIMO;
    } else if (HORA_SUENIO_MINIMO < horas_suenio && horas_suenio <= HORA_SUENIO_MEDIO) {

        puntaje = PUNTAJE_SUENIO_MEDIO;
    } else if (horas_suenio > HORA_SUENIO_MEDIO) {

        puntaje = PUNTAJE_SUENIO_MAXIMO;
    }

    return puntaje;
}

/*
 *Analisis: Evalua los parametros, suma los correspondientes puntajes y determina el animo
 *Pre: Pie, Cena y Suenio en valores validos
 *Post: Animo del personaje
 */
char valor_animo(int puntos_totales) {

    char estado_animo;

    if (PUNTAJE_ANIMO_MALO_MINIMO <= puntos_totales && puntos_totales <= PUNTAJE_ANIMO_MALO_MAXIMO) {

        estado_animo = ANIMO_MALO;
    } else if (PUNTAJE_ANIMO_REGULAR_MINIMO <= puntos_totales && puntos_totales <= PUNTAJE_ANIMO_REGULAR_MAXIMO) {

        estado_animo = ANIMO_REGULAR;
    } else if (PUNTAJE_ANIMO_BIEN_MINIMO <= puntos_totales && puntos_totales <= PUNTAJE_ANIMO_BIEN_MAXIMO) {

        estado_animo = ANIMO_BUENO;
    }

    return estado_animo;
}

/*
 *Analisis: Determina el estado de animo dependiendo el puntaje total
 *Pre: pie, cena y suenio tienen que estar validados
 *Post: El estado de animo
 */
char determina_animo(char pie, char cena, int suenio) {

    int puntos_totales = INICIO_CONTADORES;

    char animo;

    puntos_totales += puntaje_pie(pie);

    puntos_totales += puntaje_cena(cena);

    puntos_totales += puntaje_suenio(suenio);

    animo = valor_animo(puntos_totales);

    return animo;
}

/*
 *Analisis: Determina el mensaje que debe ser mostrado dependiendo del numero de pregunta
 			en el que se encuentre
 *Pre: numero_pregunta
 *Post: -
 */
void mensaje_fallo(int numero_pregunta) {

    //printf("\nSe tiene que arrepentir de lo que dijo...\n");
    printf("\nRealizo un ingreso no valido...\n\nPor favor: ");

    if (numero_pregunta == PREGUNTA_DIA) {

        printf("\nIngrese valores numericos entre el %i y el %i.", MINIMO_DIAS_MES, MAXIMO_DIAS_MES);
    } else if (numero_pregunta == PREGUNTA_HORA) {

        printf("\nIngrese %c para mañana %c para tarde o %c para noche en mayusculas.", MANIANA, TARDE, NOCHE);
    } else if (numero_pregunta == PREGUNTA_PIE_LEGOLAS || numero_pregunta == PREGUNTA_PIE_GIMLI) {

        printf("\nIngrese %c para el pie derecho (como el de Roman) o %c para el pie izquierdo (como el de Leo).",
               PIE_DERECHO, PIE_IZQUIERDO);
    } else if (numero_pregunta == PREGUNTA_CENA_LEGOLAS || numero_pregunta == PREGUNTA_CENA_GIMLI) {

        printf("\nIngrese %c para Ensalada, %c para Hamburguesa, %c para Pizza o %c para Guiso (por $5).", ENSALADA,
               HAMBURGUESA, PIZZA, GUISO);
    } else if (numero_pregunta == PREGUNTA_SUENIO_LEGOLAS || numero_pregunta == PREGUNTA_SUENIO_GIMLI) {

        printf("\nIngrese valores numericos entre el %i y el %i.", MINIMO_HORAS_SUENIO, MAXIMO_HORAS_SUENIO);
    }
    printf("\n");
    //printf("Hazlo por mi, por Maginer\n");
}

/*
 *Analisis: Determina el mensaje que debe mostrarse al usuario 
 *Pre: numero_pregunta, ingreso_valido como 0 o 1
 *Post: -
 */
void mensaje_pregunta(int ingreso_valido, int numero_pregunta) {

    if (ingreso_valido == INGRESO_INCORRECTO) {

        mensaje_fallo(numero_pregunta);
    }

    if (numero_pregunta == PREGUNTA_DIA) {

        printf("\nIngrese el dia del mes (%i-%i): ", MINIMO_DIAS_MES, MAXIMO_DIAS_MES);
    } else if (numero_pregunta == PREGUNTA_HORA) {

        printf("\nIngrese la hora del dia ( %c - %c - %c ): ", MANIANA, TARDE, NOCHE);
    } else if (numero_pregunta == PREGUNTA_PIE_LEGOLAS) {

        printf("\nIngrese el pie con el que se levanto Legolas ( %c - %c ): ", PIE_DERECHO, PIE_IZQUIERDO);
    } else if (numero_pregunta == PREGUNTA_CENA_LEGOLAS) {

        printf("\nIngrese la ultima cena de Legolas ( %c - %c - %c - %c ): ", ENSALADA, HAMBURGUESA, PIZZA, GUISO);
    } else if (numero_pregunta == PREGUNTA_SUENIO_LEGOLAS) {

        printf("\nIngrese las horas de sueño de Legolas (%i-%i): ", MINIMO_HORAS_SUENIO, MAXIMO_HORAS_SUENIO);
    } else if (numero_pregunta == PREGUNTA_PIE_GIMLI) {

        printf("\nIngrese el pie con el que se levanto Gimli ( %c - %c ): ", PIE_DERECHO, PIE_IZQUIERDO);
    } else if (numero_pregunta == PREGUNTA_CENA_GIMLI) {

        printf("\nIngrese la ultima cena de Gimli ( %c - %c - %c - %c ): ", ENSALADA, HAMBURGUESA, PIZZA, GUISO);
    } else if (numero_pregunta == PREGUNTA_SUENIO_GIMLI) {

        printf("\nIngrese las horas de sueño de Gimli (%i-%i): ", MINIMO_HORAS_SUENIO, MAXIMO_HORAS_SUENIO);
    }
}

/*
 *Analisis: Pide el ingreso numerico al usuario validando si es correcto
 *Pre: puntero de la variable por la que se esta preguntando, variable con la que se valida, numero de pregunta
 *Post:  Asigna el ingreso a la variable pasada como puntero y 0 o 1 para el validador.
 */
void ingreso_numero_usuario_valido(int *ingreso, int *valido, int numero_pregunta) {

    scanf(" %i", ingreso);

    *valido = comprobador_numeros(*ingreso, numero_pregunta);

}

/*
 *Analisis: Pide el ingreso de un caracter al usuario validando si es correcto
 *Pre: puntero de la variable por la que se esta preguntando, variable con la que se valida, numero de pregunta
 *Post:  Asigna el ingreso a la variable pasada como puntero y 0 o 1 para el validador.
 */
void ingreso_letra_usuario_valido(char *ingreso, int *valido, int numero_pregunta) {

    scanf(" %c", ingreso);

    *valido = comprobador_letra(*ingreso, numero_pregunta);

}

void animos(int *viento, int *humedad, char *animo_legolas, char *animo_gimli) {
    /*Variables que debe ingresar el usuario*/
    int dia_del_mes = DIA_DEL_MES_INICIAL;
    char hora_dia = HORA_DIA_INICIAL;

    char pie_legolas = PIE_LEGOLAS_INICIAL;
    char cena_legolas = CENA_LEGOLAS_INICIAL;
    int suenio_legolas = SUENIO_LEGOLAS_INICIAL;
    char pie_gimli = PIE_GIMLI_INICIAL;
    char cena_gimli = CENA_GIMLI_INICIAL;
    int suenio_gimli = SUENIO_GIMLI_INICIAL;

    int numero_pregunta = INICIO_CONTADORES;
    int valor_correcto = INGRESO_CORRECTO;

    while (numero_pregunta < PREGUNTAS_TOTALES) {

        mensaje_pregunta(valor_correcto, numero_pregunta);

        //Determina si el ingreso tiene que ser un entero o un caracter por la pregunta
        if (numero_pregunta == PREGUNTA_DIA) {
            ingreso_numero_usuario_valido(&dia_del_mes, &valor_correcto, numero_pregunta);
        } else if (numero_pregunta == PREGUNTA_HORA) {
            ingreso_letra_usuario_valido(&hora_dia, &valor_correcto, numero_pregunta);
        } else if (numero_pregunta == PREGUNTA_PIE_LEGOLAS) {
            ingreso_letra_usuario_valido(&pie_legolas, &valor_correcto, numero_pregunta);
        } else if (numero_pregunta == PREGUNTA_CENA_LEGOLAS) {
            ingreso_letra_usuario_valido(&cena_legolas, &valor_correcto, numero_pregunta);
        } else if (numero_pregunta == PREGUNTA_SUENIO_LEGOLAS) {
            ingreso_numero_usuario_valido(&suenio_legolas, &valor_correcto, numero_pregunta);
        } else if (numero_pregunta == PREGUNTA_PIE_GIMLI) {
            ingreso_letra_usuario_valido(&pie_gimli, &valor_correcto, numero_pregunta);
        } else if (numero_pregunta == PREGUNTA_CENA_GIMLI) {
            ingreso_letra_usuario_valido(&cena_gimli, &valor_correcto, numero_pregunta);
        } else if (numero_pregunta == PREGUNTA_SUENIO_GIMLI) {
            ingreso_numero_usuario_valido(&suenio_gimli, &valor_correcto, numero_pregunta);
        }


        numero_pregunta += valor_correcto;
    }

    *viento = velocidad_dia(dia_del_mes);
    *humedad = humedad_hora(hora_dia);
    *animo_legolas = determina_animo(pie_legolas, cena_legolas, suenio_legolas);
    *animo_gimli = determina_animo(pie_gimli, cena_gimli, suenio_gimli);

    //printf("\nResumen: %i %i %c %c.",velocidad_viento,humedad,animo_legolas,animo_gimli);
}

