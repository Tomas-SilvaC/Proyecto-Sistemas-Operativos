#include <bits/stdc++.h>

using namespace std;

void generarMatriz(int filas, int columnas, int cantidadCeros, const string &nombreArchivo) {
    int total = filas * columnas;
    int cantidadUnos = total - cantidadCeros;

    vector<int> matriz(total, 1);
    for (int i = 0; i < cantidadCeros; ++i) {
        matriz[i] = 0;
    }

    srand(time(0));
    random_shuffle(matriz.begin(), matriz.end());

    ofstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cerr << "No se pudo crear el archivo " << nombreArchivo << endl;
        return;
    }

    for (int i = 0; i < total; ++i) {
        archivo << matriz[i];
        if ((i + 1) % columnas == 0)
            archivo << '\n';
        else
            archivo << ' ';
    }

    archivo.close();

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

    if (opcion == 1) {
        int filas, columnas, cantidadCeros;
        cout << "Ingrese el número de filas: ";
        cin >> filas;
        cout << "Ingrese el número de columnas: ";
        cin >> columnas;
        cout << "Ingrese la cantidad de ceros que desea: ";
        cin >> cantidadCeros;

        int total = filas * columnas;
        if (cantidadCeros > total || cantidadCeros < 0) {
            cerr << "La cantidad de ceros no es válida. Debe ser entre 0 y " << total << ".\n";
            return 1;
        }

        generarMatriz(filas, columnas, cantidadCeros, "matriz.txt");

    } else if (opcion == 2) {
        vector<int> tamanos = {1000, 2000, 5000, 8000, 10000};

        for (int tam : tamanos) {
            int total = tam * tam;
            int cantidadCeros = static_cast<int>(round(total * 0.77));
            string nombreArchivo = "matriz" + to_string(tam) + ".txt";

            generarMatriz(tam, tam, cantidadCeros, nombreArchivo);
        }

        cout << "Todas las matrices de evaluación fueron generadas correctamente.\n";

    } else {
        cerr << "Opción inválida.\n";
        return 1;
    }

    return 0;
}
