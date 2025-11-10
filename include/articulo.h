#ifndef ARTICULO_H
#define ARTICULO_H

#include <string>

class Articulo {
private:
    std::string id;
    std::string nombre;
    double precioActual;

public:
    Articulo(const std::string& id, const std::string& nombre, double precio);

    std::string getId() const;
    std::string getNombre() const;
    double getPrecioActual() const;

    void setPrecioActual(double nuevoPrecio);
};

#endif