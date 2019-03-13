#include <iostream>
#include <vector>
#include <random>
#include <string>
#include <functional> //for std::function
#include <algorithm>  //for std::generate_n
#include <map>
#include <ctime>
using namespace std;

static const char alfabeto[] = "abcdefghijklmnopqrstuvwxyz";
static const char vocales[] = "aeiou";
static const map<int, int> mapa;
// crear los generadores



int ultima_parte_1 = 0;
int primera_parte_1 = 0;
int ultima_parte_2 = 0;
int primera_parte_2 = 0;


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



int algoritmo(string cadena1, string cadena2, int tipo) {
    int longitud = (int) max(cadena2.size(), cadena1.size());
    int accion = 0;
    if (longitud <= 1) return solucion_directa(cadena1, cadena2);
    else {
        int ultmo_1 = ultima_parte_1;
        int primero_1 = primera_parte_1;

        int ultimo_2 = ultima_parte_2;
        int primero_2 = primera_parte_2;

        string cadena_media_A_1 = cadena1.substr(0, (unsigned long) (longitud / 2));
        string cadena_media_B_1 = cadena2.substr(0, (unsigned long) (longitud / 2));
        string cadena_media_A_2 = cadena1.substr((unsigned long) (longitud / 2), (unsigned long) longitud);
        string cadena_media_B_2 = cadena2.substr((unsigned long) (longitud / 2), (unsigned long) longitud);

        int res1 = algoritmo(cadena_media_A_1, cadena_media_B_1, tipo);
        int res2 = algoritmo(cadena_media_A_2, cadena_media_B_2, -tipo);

        int sub_res_1 = 0;
        int sub_res_2 = 0;

        if (longitud >= 4) {
            string subcadena_izquierda_A = cadena1.substr((unsigned long) (longitud / 4), (unsigned long) (longitud / 4));
            string subcadena_derecha_A = cadena1.substr((unsigned long) (longitud / 2), (unsigned long) ( (longitud / 4)));

            string subcadena_izquierda_B = cadena2.substr((unsigned long) (longitud / 4), (unsigned long) (longitud / 4));
            string subcadena_derecha_B = cadena2.substr((unsigned long) (longitud / 2), (unsigned long) ((longitud / 4)));

            sub_res_1 = algoritmo(subcadena_izquierda_A, subcadena_izquierda_B, 1);
            sub_res_2 = algoritmo(subcadena_derecha_A, subcadena_derecha_B, 1);
        }

        cout << "Longitud: " << longitud << endl;
        cout << "-- res1: " << res1 << endl;
        cout << "-- res2: " << res2 << endl;
        cout << "---- subres1: " << sub_res_1 << endl;
        cout << "---- subres2: "  << sub_res_2 << endl;
        int resultadofinal = 0;

        if(es_combinable(cadena_media_A_1, cadena_media_A_2)) {


            int res_alternativo = sub_res_1 + sub_res_2;
            resultadofinal = res1 + res2;
            cout << "Resultado alternativo: " << res_alternativo << endl;
            if (res_alternativo > resultadofinal)
                return res_alternativo;
            else
                return resultadofinal;
        } else {
            resultadofinal = max(res1, res2);
        }

        return resultadofinal;
    }
}

int combinar(int algoritmo, int algoritmo1) {
    return 0;
}


int main() {

    string cadena1 = "abcaeaabbcbekaabbcsabzzzyxaaaaa";
    string cadena2 = "abcaaeubdsbekabbccsbzxzzyxaaraa";


    cout << cadena1 << endl;
    cout << cadena2 << endl;

    cout  << algoritmo(cadena1, cadena2, 1) << endl;

    return 0;
}