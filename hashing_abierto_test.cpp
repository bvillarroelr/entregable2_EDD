#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <chrono>

#include "Usuario.h"
#include "Hashing_abierto_string.h"
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
    std::ofstream file("Resultados_String_1000.csv"); // Cambiar el nombre del archivo .csv aca cada que haces un archivo cambias el numero para que nos lo separe sino tambien lo arreglo despues.

    file << "ejecucion;metodo;tiempo_segundos\n"; // Escribimos la cabecera del archivo .csv

        HashAbiertoString hashTable(n); // Crearemos una tabla de hash con n elementos

        // Creamos n usuarios y los insertamos en la tabla hash
        auto start = std::chrono::high_resolution_clock::now();
        for(int i = 1; i <= n; i++) {
            Usuario Usuario = Usuarios[i];
            hashTable.insert(Usuario.UsuarioName, Usuario);
        }
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;

/*
        // Buscamos cada usuario en la tabla hash
        start = std::chrono::high_resolution_clock::now();
        for(int i = 1; i <= n; i++) {
            Usuario Usuario = Usuarios[i];
            hashTable.search(Usuario.UsuarioName, Usuario);  //buscamos el usuario (elemento) en la tabla hash
        }
        end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> Busqueda = end - start;

        // Buscamos de usuario inecistentes en la tabla hash
        start = std::chrono::high_resolution_clock::now();
        for(int i = 1; i <= n; i++) {
        	Usuario Usuario = Usuarios[i];
            hashTable.search(-Usuario.UsuarioName, Usuario);
        }
        end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> Busqueda_f = end - start;
*/
        // Escribimos los resultados en el archivo .csv
        
        file << "HashAbiertoInt" << ";" << n << ";insert;" << duration.count() << "\n";
        //file << "HashAbiertoInt" << ";" << n << ";search;" << Busqueda.count() << "\n";  //escribimos el tiempo de busqueda
        //file << "HashAbiertoInt" << ";" << n << ";search_nouser;" << Busqueda_f.count() << "\n"; //escribimos el tiempo de busqueda de un usuario inexistente

    file.close(); // Cerramos el archivo .csv
    return 0;
}