#ifndef GESTORDECOMPRA_H
#define GESTORDECOMPRA_H

#include "articulo.h"
#include "empleado.h"
#include "proveedor.h"
#include "pedido.h"
#include <vector>
#include <iostream>
#include <string> 
#include <utility> 

class GestorDeCompra {
private:
    std::vector<Articulo*> articulos;
    std::vector<Empleado*> empleados;
    std::vector<Proveedor*> proveedores;
    std::vector<Pedido*> pedidos;

    Articulo* buscarArticulo(const std::string& id) const;
    Empleado* buscarEmpleado(const std::string& id) const;
    Proveedor* buscarProveedor(const std::string& id) const;

public:
    GestorDeCompra();
    ~GestorDeCompra();

    void crearArticulo(const std::string& id, const std::string& nombre, double precio);
    void listarArticulos() const;

    void crearEmpleado(const std::string& id, const std::string& nombre, const std::string& apellido);
    void listarEmpleados() const;

    void crearProveedor(const std::string& id, const std::string& nombre, const std::string& cuit);
    void leerProveedor(const std::string& id) const;
    void listarProveedores() const;
    void actualizarProveedor(const std::string& id, const std::string& nuevoNombre);
    void eliminarProveedor(const std::string& id);

    void crearPedido(const std::string& idEmpleado, const std::string& idProveedor,
                     const std::string& fecha, const std::vector<std::pair<std::string, int>>& articulosCantidad);
    void mostrarPedidos() const;

    void cargarDatosIniciales();
};

#endif