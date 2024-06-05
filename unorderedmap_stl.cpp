#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>
#include <chrono>
#include <random>
#include <unordered_map>

struct u_followers {
    std::string university;
    long long user_id; 
    std::string user_name;
    int number_tweets;
    int friends_count;
    int followers_count;
    std::string created_at;
};

long long scientificToInteger(const std::string& scientificNumber) {
    double number = std::stod(scientificNumber);  // Convierte a double
    long long integerNumber = std::llround(number); // Redondea y convierte a long long (para user_id)
    return integerNumber;
}

// Función para cargar los datos desde el archivo CSV
void loadCSVData(const std::string& filename, 
                 std::unordered_map<long long, u_followers>& tabla1, 
                 std::unordered_map<std::string, u_followers>& tabla2, int n) {
    std::ifstream file(filename);
    std::string line, word;
    
    // Verifica si el archivo se abrió correctamente
    if (!file.is_open()) {
        std::cerr << "Error abriendo el archivo: " << filename << std::endl;
        return;
    }

    // Leer la primera línea (header)
    std::getline(file, line);
    
    // Leer cada línea del archivo CSV hasta que llegue a n
    int count = 0;
    while (std::getline(file, line) && count < n) {
        count++;
        std::stringstream ss(line);
        u_followers follower;
        
        // Leer cada campo de la línea
        std::getline(ss, follower.university, ',');
        std::getline(ss, word, ',');
        follower.user_id = scientificToInteger(word);
        std::getline(ss, follower.user_name, ',');
        std::getline(ss, word, ',');
        follower.number_tweets = std::stoi(word);
        std::getline(ss, word, ',');
        follower.friends_count = std::stoi(word);
        std::getline(ss, word, ',');
        follower.followers_count = std::stoi(word);
        std::getline(ss, follower.created_at, ',');
        
        // Insertar en las tablas hash
        tabla1[follower.user_id] = follower;
        tabla2[follower.user_name] = follower;
    }
}
// Funcion que busca un usuario y lo imprime en caso de encontrarlo
void searchUserID(long long id, std::unordered_map<long long, u_followers> t) {
    auto it1 = t.find(id);

    if (it1 != t.end()) {
        std::cout << "Found user with ID " << id << ": " 
                  << it1->second.user_name << ", " 
                  << it1->second.university << std::endl;
    } else {
        std::cout << "User with ID " << id << " not found." << std::endl;
    }    ;
}
// Funcion que busca un usuario por su noombre y lo imprime en caso de encontrarlo
void searchUserName(std::string name, std::unordered_map<std::string, u_followers> t) {
    auto it1 = t.find(name);

    if (it1 != t.end()) {
        std::cout << "Found user with name " << name << ": " 
                  << it1->second.user_name << ", " 
                  << it1->second.university << std::endl;
    } else {
        std::cout << "User with name " << name << " not found." << std::endl;
    }    ;
}

long long generateRandom(long long min, long long max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<long long> dis(min, max);
    return dis(gen);
}

// Experimentación
int main() {
    std::unordered_map<long long, u_followers> tabla1;	// tabla con user_id como clave
    std::unordered_map<std::string, u_followers> tabla2; // tabla con user_name como clave 
    int cantidad_inserciones = 20000;

    auto start = std::chrono::high_resolution_clock::now();

    // carga de datos hacia ambas tablas
    loadCSVData("universities_followers.csv", tabla1, tabla2, cantidad_inserciones);// último parámetro cantidad de inserciones
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end-start;
    std::cout << "Tiempo de inscersión de: " << duration.count() << " segundos" << std::endl;
    /* Búsquedas usando user_id y user_name respectivamente
    searchUserID(9769796966999, tabla1);
    searchUserName("freeoftheories", tabla2);
    */
    return 0;
}
// Recursos: https://www.geeksforgeeks.org/measure-execution-time-function-cpp/

    /* impresión de los datos de la tabla 1
    for (const auto& pair : tabla1) {
        std::cout << "UserID(key): " << pair.first 
                  << ", UserName: " << pair.second.user_name 
                  << ", University: " << pair.second.university 
                  << ", CreatedAt: " << pair.second.created_at << std::endl;
    }
    */
    /* impresión de los datos de la tabla 2
    for (const auto& pair : tabla2) {
        std::cout << "UserName(key): " << pair.first 
                  << ", UserID: " << pair.second.user_id 
                  << ", University: " << pair.second.university 
                  << ", CreatedAt: " << pair.second.created_at << std::endl;
    }
    */