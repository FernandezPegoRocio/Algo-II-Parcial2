#include "../include/proveedor.h"

using namespace std;

Proveedor::Proveedor(const string& id, const string& nombre, const string& cuit)
    : id(id), nombre(nombre), cuit(cuit) {}

string Proveedor::getId() const {
    return id;
}

string Proveedor::getNombre() const {
    return nombre;
}

string Proveedor::getCuit() const {
    return cuit;
}

void Proveedor::setNombre(const string& nuevoNombre) {
    nombre = nuevoNombre;
}