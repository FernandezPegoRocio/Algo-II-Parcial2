#include "../include/gestordecompra.h"
#include <iomanip>
#include <iostream> 

using namespace std;

GestorDeCompra::GestorDeCompra() {}

GestorDeCompra::~GestorDeCompra() {

    for (auto pedido : pedidos) delete pedido;
    for (auto proveedor : proveedores) delete proveedor;
    for (auto empleado : empleados) delete empleado;
    for (auto articulo : articulos) delete articulo;
}

Articulo* GestorDeCompra::buscarArticulo(const string& id) const {
    for (auto art : articulos) {
        if (art->getId() == id) {
            return art;
        }
    }
    return nullptr;
}

Empleado* GestorDeCompra::buscarEmpleado(const string& id) const {
    for (auto emp : empleados) {
        if (emp->getId() == id) {
            return emp;
        }
    }
    return nullptr;
}

Proveedor* GestorDeCompra::buscarProveedor(const string& id) const {
    for (auto prov : proveedores) {
        if (prov->getId() == id) {
            return prov;
        }
    }
    return nullptr;
}

void GestorDeCompra::crearArticulo(const string& id, const string& nombre, double precio) {
    Articulo* nuevo = new Articulo(id, nombre, precio);
    articulos.push_back(nuevo);
    cout << "Articulo creado: " << nombre << endl;
}

void GestorDeCompra::listarArticulos() const {
    cout << "\n=== LISTADO DE ARTICULOS ===" << endl;
    for (const auto& art : articulos) {
        cout << "ID: " << art->getId()
             << " | Nombre: " << art->getNombre()
             << " | Precio: $" << fixed << setprecision(2) 
             << art->getPrecioActual()
             << endl;
    }
}

void GestorDeCompra::crearEmpleado(const string& id, const string& nombre, const string& apellido) {
    Empleado* nuevo = new Empleado(id, nombre, apellido);
    empleados.push_back(nuevo);
    cout << "Empleado creado: " << nombre << " " << apellido << endl;
}

void GestorDeCompra::listarEmpleados() const {
    cout << "\n=== LISTADO DE EMPLEADOS ===" << endl;
    for (const auto& emp : empleados) {
        cout << "ID: " << emp->getId()
             << " | Nombre: " << emp->getNombreCompleto()
             << endl;
    }
}

void GestorDeCompra::crearProveedor(const string& id, const string& nombre, const string& cuit) {
    Proveedor* nuevo = new Proveedor(id, nombre, cuit);
    proveedores.push_back(nuevo);
    cout << "Proveedor creado: " << nombre << endl;
}

void GestorDeCompra::leerProveedor(const string& id) const {
    Proveedor* prov = buscarProveedor(id);
    if (prov) {
        cout << "\n=== DATOS DEL PROVEEDOR ===" << endl;
        cout << "ID: " << prov->getId() << endl;
        cout << "Nombre: " << prov->getNombre() << endl;
        cout << "CUIT: " << prov->getCuit() << endl;
    } else {
        cout << "Proveedor no encontrado." << endl;
    }
}

void GestorDeCompra::listarProveedores() const {
    cout << "\n=== LISTADO DE PROVEEDORES ===" << endl;
    for (const auto& prov : proveedores) {
        cout << "ID: " << prov->getId()
             << " | Nombre: " << prov->getNombre()
             << " | CUIT: " << prov->getCuit()
             << endl;
    }
}

void GestorDeCompra::actualizarProveedor(const string& id, const string& nuevoNombre) {
    Proveedor* prov = buscarProveedor(id);
    if (prov) {
        prov->setNombre(nuevoNombre);
        cout << "Proveedor actualizado correctamente." << endl;
    } else {
        cout << "Proveedor no encontrado." << endl;
    }
}

void GestorDeCompra::eliminarProveedor(const string& id) {
    for (auto it = proveedores.begin(); it != proveedores.end(); ++it) {
        if ((*it)->getId() == id) {
            delete *it; 
            proveedores.erase(it); 
            cout << "Proveedor eliminado correctamente." << endl;
            return;
        }
    }
    cout << "Proveedor no encontrado." << endl;
}

void GestorDeCompra::crearPedido(const string& idEmpleado, const string& idProveedor,
                               const string& fecha, const vector<pair<string, int>>& articulosCantidad) {
    
    Empleado* empleado = buscarEmpleado(idEmpleado);
    Proveedor* proveedor = buscarProveedor(idProveedor);

    if (!empleado) {
        cout << "Error: Empleado no encontrado." << endl;
        return;
    }
    if (!proveedor) {
        cout << "Error: Proveedor no encontrado." << endl;
        return;
    }

    Pedido* nuevoPedido = new Pedido(empleado, proveedor, fecha);

    for (const auto& par : articulosCantidad) {
        Articulo* articulo = buscarArticulo(par.first);
        if (articulo) {
            nuevoPedido->agregarItem(articulo, par.second);
        } else {
            cout << "Advertencia: Articulo " << par.first << " no encontrado." << endl;
        }
    }

    pedidos.push_back(nuevoPedido);
    cout << "Pedido #" << nuevoPedido->getNroPedido() << " creado exitosamente." << endl;
}

void GestorDeCompra::mostrarPedidos() const {
    if (pedidos.empty()) {
        cout << "\nNo hay pedidos registrados." << endl;
        return;
    }
    cout << "\n========================================" << endl;
    cout << "   LISTADO DE PEDIDOS A PROVEEDORES" << endl;
    cout << "========================================" << endl;

    for (const auto& pedido : pedidos) {
        cout << "\n--- PEDIDO #" << pedido->getNroPedido() << " ---" << endl;
        cout << "Fecha: " << pedido->getFecha() << endl;
        cout << "Empleado: " << pedido->getEmpleado()->getNombreCompleto() << endl;
        cout << "Proveedor: " << pedido->getProveedor()->getNombre()
             << " (CUIT: " << pedido->getProveedor()->getCuit() << ")" << endl;
        
        cout << "\nItems del pedido:" << endl;
        cout << setw(30) << left << "Articulo"
             << setw(10) << "Cantidad"
             << setw(12) << "P. Unitario"
             << setw(12) << "Subtotal" << endl;
        cout << string(64, '-') << endl;

        for (const auto& item : pedido->getItems()) {
            cout << setw(30) << left << item->getArticulo()->getNombre()
                 << setw(10) << item->getCantidad()
                 << "$" << setw(11) << fixed << setprecision(2) 
                 << item->getPrecioCongelado()
                 << "$" << setw(11) << item->calcularSubtotal()
                 << endl;
        }
        
        cout << string(64, '-') << endl;
        cout << setw(52) << right << "TOTAL: $"
             << fixed << setprecision(2) << pedido->calcularTotal() 
             << endl;
        cout << endl;
    }
}

void GestorDeCompra::cargarDatosIniciales() {
    cout << "\n=== Cargando datos iniciales ===" << endl;
    
    crearProveedor("P001", "Cauchos del Norte SA", "20-33445566-7");
    crearProveedor("P002", "Gomas Industriales SA", "20-44556677-8");
    crearProveedor("P003", "Proveedora Central", "20-55667788-9");

    crearArticulo("A001", "Goma Natural Premium", 1500.00);
    crearArticulo("A002", "Goma Sintetica Standard", 1200.00);
    crearArticulo("A003", "Adhesivo para Goma", 850.00);
    crearArticulo("A004", "Molde de Neumatico", 3500.00);

    crearEmpleado("E001", "Don", "Gomitas");
    crearEmpleado("E002", "Marco", "Polo");
    crearEmpleado("E003", "Armando", "Lio");
    
    cout << "\n=== Datos iniciales cargados ===" << endl;
}
