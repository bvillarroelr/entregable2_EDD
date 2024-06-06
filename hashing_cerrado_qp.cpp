
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>
#include <chrono>
#include <vector>
#include <functional>
#include <optional>

// Código adaptado de unorderedmap_stl.cpp, pero esta vez usando implementación propia de tabla hash (cerrado)
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

template<typename K, typename V>
class HashTableClosed {
private:
    struct HashNode {
        K key;
        V value;
        bool occupied;
        bool deleted;
        HashNode() : occupied(false), deleted(false) {}
    };
    
    std::vector<HashNode> table;
    size_t capacity;
    size_t size;
    std::hash<K> hashFunction;
    
public:
    HashTableClosed(size_t capacity) : capacity(capacity), size(0) {
        table.resize(capacity);
    }

    bool insert(const K& key, const V& value) {
        if (size >= capacity) {
            std::cerr << "Hash table is full." << std::endl;
            return false;
        }

        size_t index = hashFunction(key) % capacity;
        size_t startIndex = index;
        size_t i = 1;
        
        while (table[index].occupied && !table[index].deleted) {
            if (table[index].key == key) {
                return false; // Duplicate key
            }
            index = (startIndex + i * i) % capacity;
            ++i;
            if (index == startIndex) {
                std::cerr << "Hash table is full." << std::endl;
                return false;
            }
        }

        table[index].key = key;
        table[index].value = value;
        table[index].occupied = true;
        table[index].deleted = false;
        ++size;
        return true;
    }

    std::optional<V> search(const K& key) {
        size_t index = hashFunction(key) % capacity;
        size_t startIndex = index;
        size_t i = 1;
        
        while (table[index].occupied) {
            if (table[index].key == key && !table[index].deleted) {
                return table[index].value;
            }
            index = (startIndex + i * i) % capacity;
            ++i;
            if (index == startIndex) {
                break;
            }
        }
        
        return std::nullopt;
    }

    bool remove(const K& key) {
        size_t index = hashFunction(key) % capacity;
        size_t startIndex = index;
        size_t i = 1;
        
        while (table[index].occupied) {
            if (table[index].key == key && !table[index].deleted) {
                table[index].deleted = true;
                --size;
                return true;
            }
            index = (startIndex + i * i) % capacity;
            ++i;
            if (index == startIndex) {
                break;
            }
        }
        
        return false;
    }
};

// Función para cargar los datos desde el archivo CSV
void loadCSVData(const std::string& filename, 
                 HashTableClosed<long long, u_followers>& tabla1, 
                 HashTableClosed<std::string, u_followers>& tabla2, int n) {
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
        // Convierte los user_id que estén en notación científica a enteros redondeados (para que no hayan problemas en la búsqueda)
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
        tabla1.insert(follower.user_id, follower);
        tabla2.insert(follower.user_name, follower);
    }
}

// Experimentación
int main(int argc, char* argv[]) {
    size_t tableSize = 30000; // Capacidad inicial de la tabla hash

    HashTableClosed<long long, u_followers> tabla1(tableSize);  // tabla con user_id como clave
    HashTableClosed<std::string, u_followers> tabla2(tableSize); // tabla con user_name como clave 
    int ejecucion = std::stoi(argv[1]); // Obtener el número de ejecución del argumento de línea de comandos
    int cantidad_inserciones = 20000;

    // carga de datos hacia ambas tablas
    auto start2 = std::chrono::high_resolution_clock::now();
    loadCSVData("universities_followers.csv", tabla1, tabla2, cantidad_inserciones); // último parámetro cantidad de inserciones
    auto end2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration2 = end2 - start2;
    std::cout << ejecucion << ";insertion;" << duration2.count() << std::endl;

    // Medición searchID (scientific notation)
    auto start1 = std::chrono::high_resolution_clock::now();
    long long searchID = 9999999999; // UsuarioID a buscar
    tabla1.search(searchID);
    auto end1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration1 = end1 - start1;
    std::cout << ejecucion << ";searchUserID;" << duration1.count() << std::endl;
    
    /* Medición searchUserName
    tabla2.search("pasten_pato");
    std::chrono::duration<double> duration2 = end2 - start2;
    std::cout << ejecucion << ";searchUserName;" << duration2.count() << std::endl;
    */
    return 0;
}