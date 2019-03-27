#include <iostream>
#include <vector>
#include <random>
#include <string>
#include <map>
#include <list>

using namespace std;

static const char alfabeto[] = "abcdefghijklmnopqrstuvwxyz";
static const char vocales[] = "aeiou";
static const map<int, int> mapa;
// crear los generadores



list<int> lista;
int parte_mas_izquierda = 0;
int parte_mas_derecha = 0;

int combinar(int algoritmo, int algoritmo1);
/*
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
*/
int encontrar_ocurrencias(string cadena, char caracter) {
    int ocurrencias = 0;
    if (cadena.size() == 1)
        if (cadena.find(caracter, 0))
            ocurrencias++;

    return ocurrencias;
}

bool es_vocal(char caracter) {
    for (int i = 0; i < 5; ++i) {
        if (vocales[i] == caracter)
            return true;
    }
    return false;
}

int pos_media(int pos_inicial, int pos_final) {
    int media = (pos_final - pos_inicial) / 2;
    if (media > 0)
        return pos_inicial + media;
    return pos_inicial;
}


int * solucion_directa(string cadena1, string cadena2, int pos_inicial, int pos_final) {
    int * res = new int[3];
    res[0] = 0;
    res[1] = 0;
    res[2] = 0;
    if (cadena1.length() == 1) {
        if (es_vocal(cadena1[0]) && es_vocal(cadena2[0])) {
            res[0] = 1;
            res[1] = pos_inicial;
            res[2] = pos_inicial;
        }
    }
    return res;
}


bool es_combinable(string cadena1, string cadena2) {
    return  (es_vocal(cadena1[cadena1.size() - 1]) && es_vocal(cadena2[0]));
}

int * algoritmo_2(string cadena1, string cadena2, int pos_inicial, int pos_final);

int * algoritmo_1(string cadena1, string cadena2, int pos_inicial, int pos_final) {
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

    int * res2 = algoritmo_1(cadena_media_A_2, cadena_media_B_2, pos_inicial, pos_final);

    if (es_combinable(cadena_media_A_1, cadena_media_A_2)) {
        if (parte_mas_derecha == 0) {
            int * res1 = algoritmo_1(cadena_media_A_1, cadena_media_B_1, pos_inicial, pos_media);
            resultado[0] = res1[0] + res2[0];
            resultado[1] = res1[1];
            resultado[2] = res2[1];
        } else {
            resultado[0] = res2[0];
            resultado[1] = res2[1];
            resultado[2] = res2[2];
        }
    } else {
        parte_mas_derecha = 1;
        resultado[0] = res2[0];
        resultado[1] = res2[1];
        resultado[2] = res2[2];
    }
    return resultado;
}

int * algoritmo_2(string cadena1, string cadena2, int pos_inicial, int pos_final) {
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

    int * res1 = algoritmo_2(cadena_media_A_1, cadena_media_B_1, pos_inicial, pos_final);     // Parte 1 calculada
    if (es_combinable(cadena_media_A_1, cadena_media_A_2)) {
        if (parte_mas_izquierda == 0) {
            int * res2 = algoritmo_2(cadena_media_A_2, cadena_media_B_2, pos_media, pos_final);
            resultado[0] = res1[0] + res2[0];
            resultado[1] = res1[1];
            resultado[2] = res2[1];
            //return res1 + res2;
        } else {
            resultado[0] = res1[0];
            resultado[1] = res1[1];
            resultado[2] = res1[2];
            //return res1;
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

    int * res1 = algoritmo_general(cadena_media_A_1, cadena_media_B_1, pos_inicial, pos_medio);
    int * res2 = algoritmo_general(cadena_media_A_2, cadena_media_B_2, pos_medio, pos_final);
    if (es_combinable(cadena_media_A_1, cadena_media_A_2) && es_combinable(cadena_media_B_1, cadena_media_B_2)) {
        int * res1_derecho = algoritmo_1(cadena_media_A_1, cadena_media_B_1, pos_inicial, pos_medio);
        int * res1_izquierdo = algoritmo_2(cadena_media_A_2, cadena_media_B_2, pos_medio, pos_final);
        parte_mas_derecha = 0;
        parte_mas_izquierda = 0;
        if (res1_derecho[0] + res1_izquierdo[0] > max(res1[0], res2[0])) {
            resultado[0] = res1_derecho[0] + res1_izquierdo[0];
            resultado[1] = res1_derecho[1];
            resultado[2] = res1_izquierdo[1];
        } else {
            if (res1[0] >= res2[0]) {
                resultado[0] = res1[0];
                resultado[1] = res1[1];
                resultado[2] = res2[1];
            } else {
                resultado[0] = res2[0];
                resultado[1] = res2[1];
                resultado[2] = res2[1];
            }
        }
    } else {
        if (res1[0] >= res2[0]) {
            resultado[0] = res1[0];
            resultado[1] = res1[1];
            resultado[2] = res2[1];
        } else {
            resultado[0] = res2[0];
            resultado[1] = res2[1];
            resultado[2] = res2[1];
        }
    }
    return resultado;
}

int combinar(int algoritmo, int algoritmo1) {
    return 0;
}


int main() {

    // keeeee ekaakg
    // keeeee ekaakg

    string cadena1 =  "eeiioouuaaiiabcaeaabbcbekaabbcaeiouaesabzzzyxaaaaa";       // 5 + 4 + 2
    string cadena2 =  "eeiioouuaaiiabcaeaabbcbekaabbcaeiouaesabzzzyxaaaaa";

    cout << cadena1 << endl;
    cout << cadena2 << endl;

    cout << algoritmo_general(cadena1, cadena2, 0, cadena1.size())[0] << " - " << algoritmo_general(cadena1, cadena2, 0, cadena1.size())[1] << endl;

    return 0;
}
