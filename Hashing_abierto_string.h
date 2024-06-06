#ifndef HASH_ABIERTO_STRING_H
#define HASH_ABIERTO_STRING_H

#include <iostream>
#include <vector>
#include <list>
#include <utility>
#include <string>

class HashAbiertoString
{
private:
    std::vector<std::list<std::pair<std::string, Usuario>>> table; // El vector que almacena los pares Username-Usuario.
    unsigned long long table_size;                                 //  El tamaño de la tabla hash.

    unsigned long long hash(const std::string &key) const
    {
        unsigned long long hash_value = 0;
        for (char ch : key)
        {
            hash_value = hash_value * 20 + ch; // Multiplicamos el hash_value por 20 y le sumamos el valor ascii del caracter
        }
        return hash_value % table_size;
    }

public:
    HashAbiertoString(unsigned long long size) : table_size(size)
    {
        table.resize(size);
    }

    void insert(std::string key, Usuario usuario)
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

    bool search(std::string key, Usuario &usuario) const
    {
        unsigned long long index = hash(key); // Obtenemos el índice de la tabla
        for (const auto &pair : table[index])
        { // Recorremos la lista en la posición index
            if (pair.first == key)
            {
                usuario = pair.second;
                return true; // Si no encontramos la key, retornamos false
            }
        }
        return false;
    }

    bool remove(std::string key)
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