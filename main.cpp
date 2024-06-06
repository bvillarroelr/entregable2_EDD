#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <chrono>

#include "Usuario.h"
#include "Hashing_Abierto_String.h"
#include "Hashing_Abierto.h"

// Función para leer el archivo CSV y retornar un vector de Usuario
std::vector<Usuario> readCSV(const std::string& filename) {
    std::vector<Usuario> Usuarios;
    std::ifstream file(filename);
    std::string line, cell;

    // Skip the header
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::stringstream lineStream(line);
        std::vector<std::string> tokens;

        while (std::getline(lineStream, cell, ',')) {
            tokens.push_back(cell);
        }

        if (tokens.size() == 7) {
            std::string university = tokens[0];
            unsigned long long UsuarioID = std::stoll(tokens[1]); // Use std::stoll for long long int
            std::string UsuarioName = tokens[2];
            int numberTweets = std::stoi(tokens[3]);
            int friendsCount = std::stoi(tokens[4]);
            int followersCount = std::stoi(tokens[5]);
            std::string createdAt = tokens[6];

            Usuarios.push_back(Usuario(university, UsuarioID, UsuarioName, numberTweets, friendsCount, followersCount, createdAt));
        }
    }
    return Usuarios;
}

int main(int argc, char** argv) {
    std::vector<Usuario> Usuarios = readCSV("universities_followers.csv");

    // Si no hay suficientes argumentos, terminamos la ejecución
    if(argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <cantidad de elementos>" << std::endl;
        exit(1);
    }

    int n = atoi(argv[1]); // Almacenará la cantidad de elementos

    // Abrimos el archivo .csv en modo de escritura
    std::ofstream file("resultados_20000.csv");
    file << "Ejecucion;Metodo;Tiempo_Segundos\n"; // Escribimos la cabecera del archivo .csv

    // Realizamos las pruebas varias veces
    for (int test = 1; test <= 20; test++) {

        HashAbierto hashTable(n); // Crearemos una tabla de hash con n elementos

        // Creamos n usuarios y los insertamos en la tabla hash
        auto start = std::chrono::high_resolution_clock::now();
        for(int i = 1; i <= n; i++) {
            Usuario Usuario = Usuarios[i];
            hashTable.insert(Usuario.UsuarioID, Usuario);
        }
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;

        // Escribimos los resultados en el archivo .csv
        file << "HashAbiertoInt" << ";insert;" << duration.count() << "\n";
    }

    file.close(); // Cerramos el archivo .csv
    return 0;
}
