#include <iostream>
#include <vector>
#include <random>
#include <string>
#include <map>
#include <list>
#include "main.h"
using namespace std;

static const char alfabeto[] = "abcdefghijklmnopqrstuvwxyz";
static const char vocales[] = "aeiou";
// crear los generadores


int parte_mas_izquierda = 0;
int parte_mas_derecha = 0;

string random_string(size_t length )
{
    srand((unsigned int) time(NULL));
    auto randchar = []() -> char
    {
        const size_t max_index = (sizeof(alfabeto) - 1);
        return alfabeto[ rand() % max_index];
    };
    std::string str(length,0);
    std::generate_n( str.begin(), length, randchar );
    return str;
}


bool es_vocal(char caracter) {
    for (int i = 0; i < 5; ++i) {
        if (vocales[i] == caracter)
            return true;
    }
    return false;
}

/**
 *
 * @param pos_inicial
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
 *
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
    res[2] = pos_inicial;
    if (cadena1.length() <= 1) {
        if (es_vocal(cadena1[0]) && es_vocal(cadena2[0])) {
            res[0] = 1;
            res[1] = pos_inicial;
            res[2] = pos_inicial;
        }
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
bool hay_union_de_vocales(string cadena1, string cadena2) {
    return  (es_vocal(cadena1[cadena1.size() - 1]) && es_vocal(cadena2[0]));
}


/**
 *
 * @param cadena1
 * @param cadena2
 * @param pos_inicial
 * @param pos_final
 * @return
 */
int * calcular_parte_derecha(string cadena1, string cadena2, int pos_inicial, int pos_final) {
    int * resultado = new int[3];
    resultado[0] = 0;
    resultado[1] = 0;
    resultado[2] = 0;
    int pos_media = (pos_inicial + pos_final) / 2;
    int longitud = (int) cadena1.size();
    if (longitud <= 1) return solucion_directa(cadena1, cadena2, pos_inicial, pos_final);

    string cadena_media_A_1 = cadena1.substr(0, (unsigned long) (longitud / 2));
    string cadena_media_B_1 = cadena2.substr(0, (unsigned long) (longitud / 2));
    string cadena_media_A_2 = cadena1.substr((unsigned long) (longitud / 2), (unsigned long) longitud);
    string cadena_media_B_2 = cadena2.substr((unsigned long) (longitud / 2), (unsigned long) longitud);

    int * segunda_parte = calcular_parte_derecha(cadena_media_A_2, cadena_media_B_2, pos_media, pos_final);
    cout << segunda_parte[1] << endl;
    if (hay_union_de_vocales(cadena_media_A_1, cadena_media_A_2)) {
        if (parte_mas_derecha == 0) {
            int * primera_parte = calcular_parte_derecha(cadena_media_A_1, cadena_media_B_1, pos_inicial, pos_media);
            resultado[0] = primera_parte[0] + segunda_parte[0];
            resultado[1] = primera_parte[1];
            resultado[2] = segunda_parte[1];
        } else {
            resultado[0] = segunda_parte[0];
            resultado[1] = segunda_parte[1];
            resultado[2] = segunda_parte[2];
        }
    } else {
        parte_mas_derecha = 1;
        resultado[0] = segunda_parte[0];
        resultado[1] = segunda_parte[1];
        resultado[2] = segunda_parte[2];
    }
    return resultado;
}

int * calcular_parte_izquierda(string cadena1, string cadena2, int pos_inicial, int pos_final) {
    int * resultado = new int[3];
    resultado[0] = 0;
    resultado[1] = 0;
    resultado[2] = 0;
    int pos_media = (pos_inicial + pos_final) / 2;
    int longitud = (int) cadena1.size();
    if (longitud <= 1) return solucion_directa(cadena1, cadena2, pos_inicial, pos_final);

    string cadena_media_A_1 = cadena1.substr(0, (unsigned long) (longitud / 2));
    string cadena_media_B_1 = cadena2.substr(0, (unsigned long) (longitud / 2));
    string cadena_media_A_2 = cadena1.substr((unsigned long) (longitud / 2), (unsigned long) longitud);
    string cadena_media_B_2 = cadena2.substr((unsigned long) (longitud / 2), (unsigned long) longitud);

    int * res1 = calcular_parte_izquierda(cadena_media_A_1, cadena_media_B_1, pos_inicial, pos_final);     // Parte 1 calculada
    if (hay_union_de_vocales(cadena_media_A_1, cadena_media_A_2)) {
        if (parte_mas_izquierda == 0) {
            int * res2 = calcular_parte_izquierda(cadena_media_A_2, cadena_media_B_2, pos_media, pos_final);
            resultado[0] = res1[0] + res2[0];
            resultado[1] = res2[1];
            resultado[2] = res2[1];
        } else {
            resultado[0] = res1[0];
            resultado[1] = res1[1];
            resultado[2] = res1[2];
        }
    } else {
        parte_mas_izquierda = 1;
        resultado[0] = res1[0];
        resultado[1] = res1[1];
        resultado[2] = res1[2];
    }
    return resultado;
}

int * algoritmo_general(string cadena1, string cadena2, int pos_inicial, int pos_final) {
    int * resultado = new int[3];
    resultado[0] = 0;
    resultado[1] = 0;
    resultado[2] = 0;


    int longitud = (int) cadena1.size();
    if (longitud <= 1) return solucion_directa(cadena1, cadena2, pos_inicial, pos_final);
    int pos_medio = pos_media(pos_inicial, pos_final);
    string cadena_media_A_1 = cadena1.substr(0, (unsigned long) (longitud / 2));
    string cadena_media_B_1 = cadena2.substr(0, (unsigned long) (longitud / 2));
    string cadena_media_A_2 = cadena1.substr((unsigned long) (longitud / 2), (unsigned long) longitud);
    string cadena_media_B_2 = cadena2.substr((unsigned long) (longitud / 2), (unsigned long) longitud);

    int * parte_derecha = algoritmo_general(cadena_media_A_1, cadena_media_B_1, pos_inicial, pos_medio);
    int * parte_izquierda = algoritmo_general(cadena_media_A_2, cadena_media_B_2, pos_medio, pos_final);
    
    if (hay_union_de_vocales(cadena_media_A_1, cadena_media_A_2) && hay_union_de_vocales(cadena_media_B_1, cadena_media_B_2)) {
        int * parte_mas_derecho = calcular_parte_derecha(cadena_media_A_1, cadena_media_B_1, pos_inicial, pos_medio);
        int * parte_mas_izquierdo = calcular_parte_izquierda(cadena_media_A_2, cadena_media_B_2, pos_medio, pos_final);
        parte_mas_derecha = 0;
        parte_mas_izquierda = 0;
        if (parte_mas_derecho[0] + parte_mas_izquierdo[0] > max(parte_derecha[0], parte_izquierda[0])) {
            resultado[0] = parte_mas_derecho[0] + parte_mas_izquierdo[0];
            resultado[1] = parte_mas_derecho[1];
            resultado[2] = parte_mas_izquierdo[1];
        } else {
            if (parte_derecha[0] >= parte_izquierda[0]) {
                resultado[0] = parte_derecha[0];
                resultado[1] = parte_derecha[1];
                resultado[2] = parte_izquierda[1];
            } else {
                resultado[0] = parte_izquierda[0];
                resultado[1] = parte_izquierda[1];
                resultado[2] = parte_izquierda[1];
            }
        }
    } else {
        if (parte_derecha[0] >= parte_izquierda[0]) {
            resultado[0] = parte_derecha[0];
            resultado[1] = parte_derecha[1];
            resultado[2] = parte_izquierda[1];
        } else {
            resultado[0] = parte_izquierda[0];
            resultado[1] = parte_izquierda[1];
            resultado[2] = parte_izquierda[1];
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

    cout << algoritmo_general(cadena1, cadena2, 0, cadena1.size()-1)[0] << " - " << algoritmo_general(cadena1, cadena2, 0, cadena1.size()-1)[1] << endl;

    return 0;
}

*/
