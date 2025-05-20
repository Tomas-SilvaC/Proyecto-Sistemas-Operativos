#include <bits/stdc++.h>

int main() {

    int filas, columnas, cantidadCeros;

    std::cout << "Ingrese el número de filas: ";
    std::cin >> filas;
    std::cout << "Ingrese el número de columnas: ";
    std::cin >> columnas;
    std::cout << "Ingrese la cantidad de ceros que desea: ";
    std::cin >> cantidadCeros;

    int total = filas * columnas;
    if (cantidadCeros > total || cantidadCeros < 0) {
        std::cerr << "La cantidad de ceros no es válida. Debe ser entre 0 y " << total << ".\n";
        return 1;
    }

    int cantidadUnos = total - cantidadCeros;

    std::vector<int> matriz(total, 1);
    for (int i = 0; i < cantidadCeros; ++i) {
        matriz[i] = 0;
    }

    std::srand(std::time(0));
    std::random_shuffle(matriz.begin(), matriz.end());

    std::ofstream archivo("matriz.txt");
    if (!archivo.is_open()) {
        std::cerr << "No se pudo crear el archivo." << std::endl;
        return 1;
    }

    for (int i = 0; i < total; ++i) {
        archivo << matriz[i];
        if ((i + 1) % columnas == 0)
            archivo << '\n';
        else
            archivo << ' ';
    }

    archivo.close();

    std::cout << "Matriz generada correctamente.\n";
    std::cout << "Cantidad de ceros: " << cantidadCeros << std::endl;
    std::cout << "Cantidad de unos: " << cantidadUnos << std::endl;
    std::cout << "Total de elementos: " << total << std::endl;

    return 0;
}
