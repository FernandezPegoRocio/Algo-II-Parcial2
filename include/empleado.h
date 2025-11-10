#ifndef EMPLEADO_H
#define EMPLEADO_H

#include <string>

class Empleado {
private:
    std::string id;
    std::string nombre;
    std::string apellido;

public:
    Empleado(const std::string& id, const std::string& nombre, const std::string& apellido);

    std::string getId() const;
    std::string getNombre() const;
    std::string getApellido() const;
    std::string getNombreCompleto() const;
};

#endif