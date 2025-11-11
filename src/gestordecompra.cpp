#include "../include/gestordecompra.h"
#include <iomanip>
#include <iostream>
#include <limits>

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


void GestorDeCompra::limpiarBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void GestorDeCompra::pausar() {
    cout << "\nPresione Enter para continuar...";
    cin.get();
}

void GestorDeCompra::opcionCargarArticulo() {
    string id, nombre;
    double precio;
    cout << "\n=== CARGAR ARTICULO ===" << endl;
    cout << "ID: ";
    getline(cin, id);
    cout << "Nombre: ";
    getline(cin, nombre);
    cout << "Precio: $";
    cin >> precio;
    limpiarBuffer();
    crearArticulo(id, nombre, precio);
}

void GestorDeCompra::opcionCargarProveedor() {
    string id, nombre, cuit;
    cout << "\n=== CARGAR PROVEEDOR ===" << endl;
    cout << "ID: ";
    getline(cin, id);
    cout << "Nombre: ";
    getline(cin, nombre);
    cout << "CUIT: ";
    getline(cin, cuit);
    crearProveedor(id, nombre, cuit);
}

void GestorDeCompra::opcionCargarEmpleado() {
    string id, nombre, apellido;
    cout << "\n=== CARGAR EMPLEADO ===" << endl;
    cout << "ID: ";
    getline(cin, id);
    cout << "Nombre: ";
    getline(cin, nombre);
    cout << "Apellido: ";
    getline(cin, apellido);
    crearEmpleado(id, nombre, apellido);
}

void GestorDeCompra::opcionCrearPedido() {
    string idEmpleado, idProveedor, fecha;
    vector<pair<string, int>> items;

    cout << "\n=== CREAR PEDIDO ===" << endl;
    
    listarEmpleados();
    cout << "\nID del Empleado: ";
    getline(cin, idEmpleado);
    
    listarProveedores();
    cout << "\nID del Proveedor: ";
    getline(cin, idProveedor);
    
    cout << "Fecha (YYYY-MM-DD): ";
    getline(cin, fecha);
    
    listarArticulos();
    char continuar = 's';
    while (continuar == 's' || continuar == 'S') {
        string idArticulo;
        int cantidad;
        cout << "\nID del Articulo: ";
        getline(cin, idArticulo);
        cout << "Cantidad: ";
        cin >> cantidad;
        limpiarBuffer();
        
        items.push_back(make_pair(idArticulo, cantidad));
        
        cout << "Desea agregar otro articulo? (s/n): ";
        cin >> continuar;
        limpiarBuffer();
    }
    crearPedido(idEmpleado, idProveedor, fecha, items);
}

void GestorDeCompra::crudCrearProveedor() {
    string id, nombre, cuit;
    cout << "\nID: ";
    getline(cin, id);
    cout << "Nombre: ";
    getline(cin, nombre);
    cout << "CUIT: ";
    getline(cin, cuit);
    crearProveedor(id, nombre, cuit);
}

void GestorDeCompra::crudLeerProveedor() {
    string id;
    cout << "\nID del Proveedor a buscar: ";
    getline(cin, id);
    leerProveedor(id);
}

void GestorDeCompra::crudActualizarProveedor() {
    string id, nuevoNombre;
    listarProveedores();
    cout << "\nID del Proveedor a actualizar: ";
    getline(cin, id);
    cout << "Nuevo nombre: ";
    getline(cin, nuevoNombre);
    actualizarProveedor(id, nuevoNombre);
}

void GestorDeCompra::crudEliminarProveedor() {
    string id;
    listarProveedores();
    cout << "\nID del Proveedor a eliminar: ";
    getline(cin, id);
    eliminarProveedor(id);
}

void GestorDeCompra::menuCRUDProveedores() {
    int opcionCRUD;
    do {
        cout << "\n=== CRUD PROVEEDORES ===" << endl;
        cout << "1. Crear Proveedor" << endl;
        cout << "2. Leer Proveedor (Buscar)" << endl;
        cout << "3. Listar Proveedores" << endl;
        cout << "4. Actualizar Proveedor" << endl;
        cout << "5. Eliminar Proveedor" << endl;
        cout << "0. Volver" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcionCRUD;
        limpiarBuffer();

        switch (opcionCRUD) {
            case 1: crudCrearProveedor(); break;
            case 2: crudLeerProveedor(); break;
            case 3: listarProveedores(); break;
            case 4: crudActualizarProveedor(); break;
            case 5: crudEliminarProveedor(); break;
            case 0: cout << "Volviendo al menu principal..." << endl; break;
            default: cout << "Opcion invalida." << endl;
        }
    } while (opcionCRUD != 0);
}

void GestorDeCompra::menuPrincipal() {
    cout << "\n========================================" << endl;
    cout << "   SISTEMA DE GESTION DE COMPRAS" << endl;
    cout << "      Productos de Goma S.A." << endl;
    cout << "========================================" << endl;
    cout << "1. Cargar Articulo" << endl;
    cout << "2. Cargar Proveedor" << endl;
    cout << "3. Cargar Empleado" << endl;
    cout << "4. Crear Pedido" << endl;
    cout << "5. Mostrar Pedidos" << endl;
    cout << "6. CRUD Proveedores" << endl;
    cout << "7. Listar Articulos" << endl;
    cout << "8. Listar Empleados" << endl;
    cout << "0. Salir" << endl;
    cout << "----------------------------------------" << endl;
    cout << "Seleccione una opcion: ";
}


void GestorDeCompra::ejecutar() {
    cargarDatosIniciales();
    
    int opcion;
    do {
        menuPrincipal();
        cin >> opcion;
        limpiarBuffer();

        switch (opcion) {
            case 1: opcionCargarArticulo(); break;
            case 2: opcionCargarProveedor(); break;
            case 3: opcionCargarEmpleado(); break;
            case 4: opcionCrearPedido(); break;
            case 5: mostrarPedidos(); break;
            case 6: menuCRUDProveedores(); break;
            case 7: listarArticulos(); break;
            case 8: listarEmpleados(); break;
            case 0: cout << "\nGracias por usar el sistema. Adios!" << endl; break;
            default: cout << "Opcion invalida. Intente nuevamente." << endl;
        }

        if (opcion != 0) {
            pausar();
        }

    } while (opcion != 0);
}