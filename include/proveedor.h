#ifndef PROVEEDOR_H
#define PROVEEDOR_H

#include <string>

class Proveedor {
private:
    std::string id;
    std::string nombre;
    std::string cuit;

public:
    Proveedor(const std::string& id, const std::string& nombre, const std::string& cuit);

    std::string getId() const;
    std::string getNombre() const;
    std::string getCuit() const;

    void setNombre(const std::string& nuevoNombre);
};

#endif