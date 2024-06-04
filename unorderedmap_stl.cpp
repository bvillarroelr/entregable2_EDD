#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>

struct u_followers {
    std::string university;
    long long user_id; // Cambiado a long long
    std::string user_name;
    int number_tweets;
    int friends_count;
    int followers_count;
    std::string created_at;
};

// Función para cargar los datos desde el archivo CSV (obtenida de chatGPT)
void loadCSVData(const std::string& filename, 
                 std::unordered_map<long long, u_followers>& tabla1, 
                 std::unordered_map<std::string, u_followers>& tabla2) {
    std::ifstream file(filename);
    std::string line, word;
    
    // Verifica si el archivo se abrió correctamente
    if (!file.is_open()) {
        std::cerr << "Error abriendo el archivo: " << filename << std::endl;
        return;
    }

    // Leer la primera línea (header)
    std::getline(file, line);
    
    // Leer cada línea del archivo CSV
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        u_followers follower;
        
        // Leer cada campo de la línea
        std::getline(ss, follower.university, ',');
        std::getline(ss, word, ',');
        follower.user_id = std::stoll(word); // Convertir a long long
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

int main() {
    std::unordered_map<long long, u_followers> tabla1;
    std::unordered_map<std::string, u_followers> tabla2;

    loadCSVData("universities_followers.csv", tabla1, tabla2);

    for (const auto& pair : tabla1) {
        std::cout << "UserID: " << pair.first 
                  << ", UserName: " << pair.second.user_name 
                  << ", University: " << pair.second.university 
                  << ", CreatedAt: " << pair.second.created_at << std::endl;
    }

    return 0;
}
