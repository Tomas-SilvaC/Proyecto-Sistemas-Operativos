/**************************************************************
                Pontificia Universidad Javeriana
        Autores: Gabriel Jaramillo, Juan Pabón, Tomas Silva y Felipe Rodrpiguez
        Fecha: Mayo 2025
        Materia: Sistemas Operativos
        Tema: Proyecto Final
        Fichero: GeneradorMatrices
        Descripción: 
            Este fichero permite generar matrices cuadradas o rectangulares
            de valores binarios (0 y 1), donde una cantidad específica de ceros 
            es distribuida aleatoriamente entre los elementos.
****************************************************************/
#include <bits/stdc++.h>

using namespace std;

/* Genera una matriz de valores binarios (0 y 1), la desordena aleatoriamente
     y la guarda en un archivo de texto. */

void generarMatriz(int filas, int columnas, int cantidadCeros, const string &nombreArchivo) {
    
    // Calcula el total de elementos de la matriz y la cantidad de unos necesarios para llenarla
    int total = filas * columnas;
    int cantidadUnos = total - cantidadCeros;

    // Crea un vector con los elementos inicializados en 1 y reemplaza la priemra cantidadCeros por 0
    vector<int> matriz(total, 1);
    for (int i = 0; i < cantidadCeros; ++i) {
        matriz[i] = 0;
    }

    // Mezcla aleatoriamente los elementos de la matriz
    srand(time(0));
    random_shuffle(matriz.begin(), matriz.end());

    // Abre el archivo de salida
    ofstream archivo(nombreArchivo);

    //En caso de haber un error con el archivo genera un mensaje de error
    if (!archivo.is_open()) {
        cerr << "No se pudo crear el archivo " << nombreArchivo << endl;
        return;
    }

    // Escribe los elementos de la matriz en el archivo
    for (int i = 0; i < total; ++i) {
        archivo << matriz[i];
        if ((i + 1) % columnas == 0)
            archivo << '\n';
        else
            archivo << ' ';
    }

    // Cierra el archivo
    archivo.close();
    
    // Imprime la información de la matriz generada
    cout << "Matriz generada correctamente: " << nombreArchivo << "\n";
    cout << "Tamaño: " << filas << "x" << columnas << "\n";
    cout << "Ceros: " << cantidadCeros << ", Unos: " << cantidadUnos << "\n\n";
}

int main(int argc, char *argv[]) {
    int opcion = 0;

    // Si se pasa un argumento (opción directa)
    if (argc > 1) {
        opcion = atoi(argv[1]);  // Convierte el argumento a entero
    } else {
        // Mostrar menú si no hay argumento
        cout << "Generador de matrices\n";
        cout << "1. Generar matriz personalizada (matriz.txt)\n";
        cout << "2. Generar matrices de evaluación (matriz1000.txt, matriz2000.txt, ...)\n";
        cout << "Ingrese una opción: ";
        cin >> opcion;
    }

    // Opción de generar matriz personalizada
    if (opcion == 1) {
        int filas, columnas, cantidadCeros;

        // Recibe los datos de la matriz deseada por parte del usuario
        cout << "Ingrese el número de filas: ";
        cin >> filas;
        cout << "Ingrese el número de columnas: ";
        cin >> columnas;
        cout << "Ingrese la cantidad de ceros que desea: ";
        cin >> cantidadCeros;

        // Calcula la cantidad de elementos de la matriz
        int total = filas * columnas;

        // Verifica que la cantidad de ceros deseada es menor a la cantidad total de elementos
        if (cantidadCeros > total || cantidadCeros < 0) {
            cerr << "La cantidad de ceros no es válida. Debe ser entre 0 y " << total << ".\n";
            return 1;
        }

        // Llama a la función generadora de matriz con los valores recibidos
        generarMatriz(filas, columnas, cantidadCeros, "matriz.txt");

    // Opción de generar matrices de evaluación
    } else if (opcion == 2) {

        // Declara un vector con todos los tamaños de matriz a probar
        vector<int> tamanos = {1000, 2000, 5000, 8000, 10000};

        // Recorre el vector de tamanos
        for (int tam : tamanos) {
            // Calcula el total de elementos
            int total = tam * tam;

            // Asigna una cantidad de ceros aproximada del 77% de datos de la matriz
            int cantidadCeros = static_cast<int>(round(total * 0.77));

            // Genera el nombre del archivo dado el tamano de la matriz
            string nombreArchivo = "matriz" + to_string(tam) + ".txt";
            
            // Llama a la funcion generadora con los datos generados
            generarMatriz(tam, tam, cantidadCeros, nombreArchivo);
        }

        cout << "Todas las matrices de evaluación fueron generadas correctamente.\n";

    // Opción invalida para el menu
    } else {
        cerr << "Opción inválida.\n";
        return 1;
    }

    return 0;
}
