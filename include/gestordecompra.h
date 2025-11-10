#ifndef GESTORDECOMPRA_H
#define GESTORDECOMPRA_H

#include "articulo.h"
#include "empleado.h"
#include "proveedor.h"
#include "pedido.h"
#include <vector>
#include <iostream>
#include <string> 
#include <utility> // Para std::pair

class GestorDeCompra {
private:
    std::vector<Articulo*> articulos;
    std::vector<Empleado*> empleados;
    std::vector<Proveedor*> proveedores;
    std::vector<Pedido*> pedidos;

    // Métodos de búsqueda privados
    Articulo* buscarArticulo(const std::string& id) const;
    Empleado* buscarEmpleado(const std::string& id) const;
    Proveedor* buscarProveedor(const std::string& id) const;

public:
    GestorDeCompra();
    ~GestorDeCompra();

    // CRUD de Articulos
    void crearArticulo(const std::string& id, const std::string& nombre, double precio);
    void listarArticulos() const;

    // CRUD de Empleados
    void crearEmpleado(const std::string& id, const std::string& nombre, const std::string& apellido);
    void listarEmpleados() const;

    // CRUD de Proveedores (completo según consigna)
    void crearProveedor(const std::string& id, const std::string& nombre, const std::string& cuit);
    void leerProveedor(const std::string& id) const;
    void listarProveedores() const;
    void actualizarProveedor(const std::string& id, const std::string& nuevoNombre);
    void eliminarProveedor(const std::string& id);

    // Gestion de Pedidos
    void crearPedido(const std::string& idEmpleado, const std::string& idProveedor,
                     const std::string& fecha, const std::vector<std::pair<std::string, int>>& articulosCantidad);
    void mostrarPedidos() const;

    // Carga de datos hardcodeados
    void cargarDatosIniciales();
};

#endif