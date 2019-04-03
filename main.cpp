/*
 * Grupo: 3
 * Nombre: Mourad Abbou Aazaz
 * IMPORTANTE: Al compilarlo, utilizr el flag -std=c++11
 */
#include <iostream>
#include <vector>
#include <random>
#include <string>
#include <map>
#include <list>
#include "main.h"
using namespace std;

static const char alfabeto[] = "abcdefghijklmnopqrstuvwxyz";
static const char consonantes[] = "bcdfghjklmnpqrstvwxyz";
static const char vocales[] = "aeiou";

int parte_mas_izquierda = 0;
int parte_mas_derecha = 0;

/**
 * FUNCION AUXILIAR
 * @param caracter
 * @return
 */
bool es_vocal(char caracter) {
    for (int i = 0; i < 5; ++i) {
        if (vocales[i] == caracter)
            return true;
    }
    return false;
}

/**
 * FUNCION AUXILIAR
 * Devuelve la media entre dos argumentos
 * @param pos_inicial primer argumentos
 * @param pos_final
 * @return Esta funcion devuelve la media entre pos_inicial y pos:final
 */
int pos_media(int pos_inicial, int pos_final) {
    int media = (pos_final - pos_inicial) / 2;
    if (media > 0)
        return pos_inicial + media;
    return pos_inicial;
}

/**
 * Calcula si la primera cadena y la segunda son vocales.
 * @param cadena1 Primera Cadena
 * @param cadena2 Segunda Cadena
 * @param pos_inicial Posicion inicial de las cadenas
 * @param pos_final Posicion final de las cadenas
 * @return
 */
int * solucion_directa(string cadena1, string cadena2, int pos_inicial, int pos_final) {
    int * res = new int[3];
    res[0] = 0;
    res[1] = pos_inicial;
    if (cadena1.length() <= 1) {
        if (es_vocal(cadena1[0]) && es_vocal(cadena2[0])) {
            res[0] = 1;
            res[1] = pos_inicial;

        }
    } else {
        int num = 0;
        for (int i = 0; i < cadena1.size(); ++i) {
            if (es_vocal(cadena1[i]) && es_vocal(cadena2[i]))
                num++;
        }

        res[0] = num;
        res[1] = pos_inicial;
    }
    return res;
}

/**
 * Dadas dos cadenas, se comprueba si la ultima letra de la primera cadena y la primera letra de las segunda cadena
 * son vocales
 *
 * Exemplo: adfasdfa y oiuwerwwe
 *
 * @param cadena1
 * @param cadena2
 * @return
 */
bool existen_vocales_consecutivas(string cadena1, string cadena2) {
    return  (es_vocal(cadena1[cadena1.size() - 1]) && es_vocal(cadena2[0]));
}


/**
 * Se encarga de calcula la parte secuencia de vocales mas significativa que tienen en
 * comun 2 cadenas y su posición de comienzo con respecto a la cadena principal.
 * 1 - Inicializa la variable resultado[]
 * 2 - Comprueba si lo puede ejecutar por solucion directa
 * 3 - Si la longitud es mayor que 1:
 *  3.1 - Calcula las subcadenas
 *  3.2 - Calcula la secuencia mas a la derecha
 *  3.3 - Si existe consecucion de vocales
 *      3.3.1 - Vuelve a calcular la parte mas derecha de la primera mitad de la cadena
 *      3.3.2 - Se le asigna la suma de ambos resultados
 * @param cadena1 Primera Cadena
 * @param cadena2 Segunda cadena
 * @param pos_inicial Posición en la que se encuentran las cadenas con respecto a las cadenas pricipales
 * @param pos_final
 * @return Devuelve un array con el tamano de secuencia mas larga y su posicion
 */
int * calcular_parte_derecha(string cadena1, string cadena2, int pos_inicial, int pos_final) {
    int * resultado = new int[3];
    resultado[0] = 0;
    resultado[1] = 0;
    int pos_media = (pos_inicial + pos_final) / 2;
    int longitud = (int) cadena1.size();
    if (longitud <= 1) return solucion_directa(cadena1, cadena2, pos_inicial, pos_final);

    string cadena1_primera_mitad = cadena1.substr(0, (unsigned long) (longitud / 2));
    string cadena2_primera_mitad = cadena2.substr(0, (unsigned long) (longitud / 2));
    string cadena1_segunda_mitad = cadena1.substr((unsigned long) (longitud / 2), (unsigned long) longitud);
    string cadena2_segunda_mitad = cadena2.substr((unsigned long) (longitud / 2), (unsigned long) longitud);

    int * segunda_parte = calcular_parte_derecha(cadena1_segunda_mitad, cadena2_segunda_mitad, pos_media, pos_final);
    if (existen_vocales_consecutivas(cadena1_primera_mitad, cadena1_segunda_mitad)) {
        if (parte_mas_derecha == 0) {
            int * primera_parte = calcular_parte_derecha(cadena1_primera_mitad, cadena2_primera_mitad, pos_inicial, pos_media);
            resultado[0] = primera_parte[0] + segunda_parte[0];
            resultado[1] = primera_parte[1];
        } else {
            resultado[0] = segunda_parte[0];
            resultado[1] = segunda_parte[1];
        }
    } else {
        parte_mas_derecha = 1;
        resultado[0] = segunda_parte[0];
        resultado[1] = segunda_parte[1];
    }
    return resultado;
}


/**
 * Se utiliza para calcular la secuencia menos significativa que tienen en común dos cadenas.
 * El proceso es exactamente igual que la funcion calcular_parte_derecha
 * @param cadena1
 * @param cadena2
 * @param pos_inicial
 * @param pos_final
 * @return
 */
int * calcular_parte_izquierda(string cadena1, string cadena2, int pos_inicial, int pos_final) {
    int * resultado = new int[3];
    resultado[0] = 0;
    resultado[1] = 0;
    int pos_media = (pos_inicial + pos_final) / 2;
    int longitud = (int) cadena1.size();
    if (longitud <= 1) return solucion_directa(cadena1, cadena2, pos_inicial, pos_final);

    string cadena1_primera_mitad = cadena1.substr(0, (unsigned long) (longitud / 2));
    string cadena_media_B_1 = cadena2.substr(0, (unsigned long) (longitud / 2));
    string cadena_media_A_2 = cadena1.substr((unsigned long) (longitud / 2), (unsigned long) longitud);
    string cadena_media_B_2 = cadena2.substr((unsigned long) (longitud / 2), (unsigned long) longitud);

    int * res1 = calcular_parte_izquierda(cadena1_primera_mitad, cadena_media_B_1, pos_inicial, pos_final);     // Parte 1 calculada
    if (existen_vocales_consecutivas(cadena1_primera_mitad, cadena_media_A_2)) {
        if (parte_mas_izquierda == 0) {
            int * res2 = calcular_parte_izquierda(cadena_media_A_2, cadena_media_B_2, pos_media, pos_final);
            resultado[0] = res1[0] + res2[0];
            resultado[1] = res2[1];
        } else {
            resultado[0] = res1[0];
            resultado[1] = res1[1];
        }
    } else {
        parte_mas_izquierda = 1;
        resultado[0] = res1[0];
        resultado[1] = res1[1];
    }
    return resultado;
}


int * combinacion_izquierda_alternativa(string cadena1, string cadena2, int pos_inicial, int pos_final) {
    int  * resultado = new int[2];
    resultado[0] = 0;
    resultado[1] = 0;
    int pos_media = (pos_inicial + pos_final) / 2;
    int longitud = (int) cadena1.size();
    if (longitud <= 1)  return solucion_directa(cadena1, cadena2, pos_inicial, pos_final);
    int pos_aux = pos_inicial;
    int num_vocales = 0;
    for (int i = 0; i < longitud && es_vocal(cadena1[i]) && es_vocal(cadena2[i]); ++i) {
           num_vocales++;
    }
    resultado[0] = num_vocales;
    resultado[1] = pos_inicial;
    return resultado;
}

int * combinacion_derecha_alternativa(string cadena1, string cadena2, int posicion_inicial, int pos_final) {
    int * resultado = new int[2];
    resultado[0] = 0;
    resultado[1] = 0;
    int longitud = (int) cadena1.size();
    if (longitud <= 1)  return solucion_directa(cadena1, cadena2, posicion_inicial, pos_final);
    int pos_aux = pos_final;
    int num_vocales = 0;
    for (int i = longitud - 1; i >= 0 && es_vocal(cadena1[i]) && es_vocal(cadena2[i]) ; --i) {
            num_vocales++;
            pos_aux--;

    }
    resultado[0] = num_vocales;
    resultado[1] = pos_aux;
    return resultado;
}


/**
 * Algoritmo DIVIDE y VENCERÁS
 * La funcionalidad del algortimo es:
 * 1 - Inicializa el array resultado
 * 2 - Comprobamos si tiene longitud 1 para resolverlo por solucion directa
 * 3 - Calculamos las 4 subcadenas
 * 4 - Calculamos las los resultados de las dos mitades ()
 * 5 - Si existen vocales consecutivas:
 *  5.1 - Calculamos la parte mas significativa con repecto a la primera mitad
 *  5.2 - Calculamos la parte menos significativa con respecto a la segunda mitad
 *  Si el resultado de la suma de las dos partes mas significativa y menos significativa con respecto al centro
 *  es mayor que el maximo que existe entre el resultado de la parte derecha y la parte izquierda:
 *      - Asignamos valores
 *  Sino:
 *      - Comprobamos si la perte derecha es mayor que la izquierda
 *          - Si lo es
 *              Asignamos respectivos valores
 *      - En caso contrario, asignamos los valores de la izquierda
 * @param cadena1 Primera cadena
 * @param cadena2 Segunda cadena
 * @param pos_inicial Posicion inicial de las cadenas, (Al comenzar es 0)
 * @param pos_final Posicion final que ocupa la ultima letra de las cadenas
 * @return Devolvemos el resultado
 */
int * algoritmo_dyv(string cadena1, string cadena2, int pos_inicial, int pos_final, int caso_base) {
    int * resultado = new int[3];
    resultado[0] = 0;
    resultado[1] = 0;

    int longitud = (int) cadena1.size();
    if (longitud <= caso_base) return solucion_directa(cadena1, cadena2, pos_inicial, pos_final);
    int pos_medio = pos_media(pos_inicial, pos_final);
    string cadena1_primera_mitad = cadena1.substr(0, (unsigned long) (longitud / 2));
    string cadena2_primera_mitad = cadena2.substr(0, (unsigned long) (longitud / 2));
    string cadena1_segunda_mitad = cadena1.substr((unsigned long) (longitud / 2), (unsigned long) longitud);
    string cadena2_segunda_mitad = cadena2.substr((unsigned long) (longitud / 2), (unsigned long) longitud);

    int * parte_derecha = algoritmo_dyv(cadena1_primera_mitad, cadena2_primera_mitad, pos_inicial, pos_medio, caso_base);
    int * parte_izquierda = algoritmo_dyv(cadena1_segunda_mitad, cadena2_segunda_mitad, pos_medio, pos_final, caso_base);



    if (existen_vocales_consecutivas(cadena1_primera_mitad, cadena1_segunda_mitad) && existen_vocales_consecutivas(cadena2_primera_mitad, cadena2_segunda_mitad)) {
       // int * parte_mas_derecho = calcular_parte_derecha(cadena1_primera_mitad, cadena2_primera_mitad, pos_inicial, pos_medio);
       // int * parte_mas_izquierdo = calcular_parte_izquierda(cadena1_segunda_mitad, cadena2_segunda_mitad, pos_medio, pos_final);
        int * parte_mas_derecho =  combinacion_derecha_alternativa(cadena1_primera_mitad, cadena2_primera_mitad, pos_inicial, pos_medio);
        int * parte_mas_izquierdo = combinacion_izquierda_alternativa(cadena1_segunda_mitad, cadena2_segunda_mitad, pos_medio, pos_final);
        parte_mas_derecha = 0;
        parte_mas_izquierda = 0;
        int derecha = parte_mas_derecho[0];
        int izquierda =  parte_mas_izquierdo[0];
        if (derecha + izquierda > max(parte_derecha[0], parte_izquierda[0])) {
            resultado[0] = parte_mas_derecho[0] + parte_mas_izquierdo[0];
            resultado[1] = parte_mas_derecho[1];
        } else {
            if (parte_derecha[0] >= parte_izquierda[0]) {
                resultado[0] = parte_derecha[0];
                resultado[1] = parte_derecha[1];
            } else {
                resultado[0] = parte_izquierda[0];
                resultado[1] = parte_izquierda[1];
            }
        }
    } else {
        if (parte_derecha[0] >= parte_izquierda[0]) {
            resultado[0] = parte_derecha[0];
            resultado[1] = parte_derecha[1];
        } else {
            resultado[0] = parte_izquierda[0];
            resultado[1] = parte_izquierda[1];
        }
    }
    return resultado;
}

/*

int main() {

    string cadena1 =  "eeiioouuaaiiabcaeaabbcbekaabbcaeiouaesabzzzyxaaaaa";       // 5 + 4 + 2
    string cadena2 =  "eeiioouuaaiiabcaeaabbcbekaabbcaeiouaesabzzzyxaaaaa";

    cout << cadena1 << endl;
    cout << cadena2 << endl;

    cout << algoritmo_general(cadena1, cadena2, 0, cadena1.size()-1)[0] << " - " << algoritmo_dyv(cadena1, cadena2, 0, cadena1.size()-1)[1] << endl;

    return 0;
}

*/
