#ifndef HASHING_ABIERTO_H
#define HASHING_ABIERTO_H

#include <iostream>
#include <fstream>
#include <unordered_map>

#include "Usuario.h"

using namespace std;

class HashAbierto {

private:
    vector<list<pair<int, Usuario>>> table; /**< El vector que almacena los pares key-Usuario. */
    unsigned long long table_size;                      /**< El tamaño de la tabla hash. >*/
    unsigned long long hash(unsigned long long key) const
    {
        return key % table_size;
    }

public:
    HashAbierto(unsigned long long size) : table_size(size)
    {
        table.resize(size);
    }
    void insert(unsigned long long key, Usuario usuario)
    {
        unsigned long long index = hash(key); // Obtenemos el índice de la tabla
        for (auto &pair : table[index])
        { // Recorremos la lista en la posición index
            if (pair.first == key)
            { // Si la key ya existe, actualizamos el usuario
                pair.second = usuario;
                return;
            }
        }
        table[index].emplace_back(key, usuario); // Si no existe, insertamos el par key-usuario
    }

    bool search(unsigned long long key, Usuario &usuario) const
    {
        unsigned long long index = hash(key); // Obtenemos el índice de la tabla
        for (const auto &pair : table[index])
        { // Recorremos la lista en la posición index
            if (pair.first == key)
            {
                usuario = pair.second;
                return true;
            }
        }
        return false; // Si no encontramos la key, retornamos false
    }
    bool remove(unsigned long long key)
    {
        unsigned long long index = hash(key); // Obtenemos el índice de la tabla
        for (auto it = table[index].begin(); it != table[index].end(); ++it)
        { // Recorremos la lista en la posición index
            if (it->first == key)
            { // Si encontramos la key, la eliminamos
                table[index].erase(it);
                return true;
            }
        }
        return false;
    }
};

#endif
