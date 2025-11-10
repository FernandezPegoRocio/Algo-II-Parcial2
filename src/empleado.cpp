#include "../include/empleado.h"

using namespace std;

Empleado::Empleado(const string& id, const string& nombre, const string& apellido)
    : id(id), nombre(nombre), apellido(apellido) {}

string Empleado::getId() const {
    return id;
}

string Empleado::getNombre() const {
    return nombre;
}

string Empleado::getApellido() const {
    return apellido;
}

string Empleado::getNombreCompleto() const {
    return nombre + " " + apellido;
}