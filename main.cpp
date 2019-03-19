#include <iostream>
#include <vector>
#include <random>
#include <string>
#include <functional> //for std::function
#include <algorithm>  //for std::generate_n
#include <map>
#include <ctime>
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

int contar_vocales(string cadena) {
    int contador = 0;
    bool hay_vocal = false;
    int indice = 0;
    for (int i = 0; i < cadena.size(); ++i) {
        if (es_vocal(cadena[i])) {
            if (!hay_vocal) {
                indice = i;
                hay_vocal = true;
            }
            contador++;
        }
    }
    return contador;
}


int solucion_directa(string cadena1, string cadena2) {
    if (cadena1.length() == 1) {
        if (es_vocal(cadena1[0]) && es_vocal(cadena2[0]))
            return 1;
    }
    return 0;
}


bool es_combinable(string cadena1, string cadena2) {
    return  (es_vocal(cadena1[cadena1.size() - 1]) && es_vocal(cadena2[0]));
}

int algoritmo_2(string cadena1, string cadena2);

int algoritmo(string cadena1, string cadena2) {
    int longitud = (int) max(cadena2.size(), cadena1.size());
    int accion = 0;
    if (longitud <= 1) return solucion_directa(cadena1, cadena2);
    else {
        string cadena_media_A_1 = cadena1.substr(0, (unsigned long) (longitud / 2));
        string cadena_media_B_1 = cadena2.substr(0, (unsigned long) (longitud / 2));
        string cadena_media_A_2 = cadena1.substr((unsigned long) (longitud / 2), (unsigned long) longitud);
        string cadena_media_B_2 = cadena2.substr((unsigned long) (longitud / 2), (unsigned long) longitud);
        int res1 = algoritmo(cadena_media_A_1, cadena_media_B_1);     // Parte 1 calculad
        int res2_principal = algoritmo(cadena_media_A_2, cadena_media_B_2);
        if(es_combinable(cadena_media_A_1, cadena_media_A_2)) {
            return res1 + res2_principal;
        } else {
            return max(res1, res2_principal);
        }
    }
}

bool es_combinable_() {

}

int algoritmo_1(string cadena1, string cadena2) {
    int resultado = 0;
    int longitud = (int) cadena1.size();
    if (longitud <= 1) return solucion_directa(cadena1, cadena2);

    string cadena_media_A_1 = cadena1.substr(0, (unsigned long) (longitud / 2));
    string cadena_media_B_1 = cadena2.substr(0, (unsigned long) (longitud / 2));
    string cadena_media_A_2 = cadena1.substr((unsigned long) (longitud / 2), (unsigned long) longitud);
    string cadena_media_B_2 = cadena2.substr((unsigned long) (longitud / 2), (unsigned long) longitud);

    int res2 = algoritmo_1(cadena_media_A_2, cadena_media_B_2);

    if (es_combinable(cadena_media_A_1, cadena_media_A_2)) {
        if (parte_mas_derecha == 0) {
            int res1 = algoritmo_1(cadena_media_A_1, cadena_media_B_1);
            return res1 + res2;
        } else {
            return res2;
        }
    } else {
        parte_mas_derecha = 1;
        return res2;
    }
}

int algoritmo_2(string cadena1, string cadena2) {
    int resultado = 0;
    int longitud = (int) cadena1.size();
    if (longitud <= 1) return solucion_directa(cadena1, cadena2);

    string cadena_media_A_1 = cadena1.substr(0, (unsigned long) (longitud / 2));
    string cadena_media_B_1 = cadena2.substr(0, (unsigned long) (longitud / 2));
    string cadena_media_A_2 = cadena1.substr((unsigned long) (longitud / 2), (unsigned long) longitud);
    string cadena_media_B_2 = cadena2.substr((unsigned long) (longitud / 2), (unsigned long) longitud);

    int res1 = algoritmo_2(cadena_media_A_1, cadena_media_B_1);     // Parte 1 calculada
    if (es_combinable(cadena_media_A_1, cadena_media_A_2)) {
        if (parte_mas_izquierda == 0) {
            int res2 = algoritmo_2(cadena_media_A_2, cadena_media_B_2);

            return res1 + res2;
        } else {
            return res1;
        }
    } else {
        parte_mas_izquierda = 1;
        return res1;
    }
}

int algoritmo_general(string cadena1, string cadena2) {
    int resultado = 0;
    int longitud = (int) cadena1.size();
    if (longitud <= 1) return solucion_directa(cadena1, cadena2);

    string cadena_media_A_1 = cadena1.substr(0, (unsigned long) (longitud / 2));
    string cadena_media_B_1 = cadena2.substr(0, (unsigned long) (longitud / 2));
    string cadena_media_A_2 = cadena1.substr((unsigned long) (longitud / 2), (unsigned long) longitud);
    string cadena_media_B_2 = cadena2.substr((unsigned long) (longitud / 2), (unsigned long) longitud);

    int res1 = algoritmo_general(cadena_media_A_1, cadena_media_B_1);
    int res2 = algoritmo_general(cadena_media_A_2, cadena_media_B_2);
    if (es_combinable(cadena_media_A_1, cadena_media_A_2) && es_combinable(cadena_media_B_1, cadena_media_B_2)){
        int res1_derecho = algoritmo_1(cadena_media_A_1, cadena_media_B_1);
        int res1_izquierdo = algoritmo_2(cadena_media_A_2, cadena_media_B_2);
        parte_mas_derecha = 0;
        parte_mas_izquierda = 0;
        if (res1_derecho + res1_izquierdo > max(res1, res2))
            return res1_derecho + res1_izquierdo;
        else max(res1, res2);
    } else {
        return max(res1, res2);
    }
}

int combinar(int algoritmo, int algoritmo1) {
    return 0;
}


int main() {

    // keeeee ekaakg
    // keeeee ekaakg

    string cadena1 =  "abcaeaabbcbekaabbcsabzzzyxaaaaa";       // 5 + 4 + 2
    string cadena2 =  "abcaeaabbcbekaabbcsabzzzyxaraaa";

    cout << cadena1 << endl;
    cout << cadena2 << endl;

    cout  << algoritmo_general(cadena1, cadena2) << endl;

    return 0;
}
