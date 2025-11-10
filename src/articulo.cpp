#include "../include/articulo.h"

using namespace std;

Articulo::Articulo(const string& id, const string& nombre, double precio)
    : id(id), nombre(nombre), precioActual(precio) {}

string Articulo::getId() const {
    return id;
}

string Articulo::getNombre() const {
    return nombre;
}

double Articulo::getPrecioActual() const {
    return precioActual;
}

void Articulo::setPrecioActual(double nuevoPrecio) {
    precioActual = nuevoPrecio;
}