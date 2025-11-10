#include "../include/gestordecompra.h"
#include <iostream>
#include <limits> 
#include <string>
#include <vector>
#include <utility> 

using namespace std;

void limpiarBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void pausar() {
    cout << "\nPresione Enter para continuar...";
    cin.get();
}


void mostrarMenuPrincipal() {
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

void mostrarMenuCRUDProveedores() {
    cout << "\n=== CRUD PROVEEDORES ===" << endl;
    cout << "1. Crear Proveedor" << endl;
    cout << "2. Leer Proveedor (Buscar)" << endl;
    cout << "3. Listar Proveedores" << endl;
    cout << "4. Actualizar Proveedor" << endl;
    cout << "5. Eliminar Proveedor" << endl;
    cout << "0. Volver" << endl;
    cout << "Seleccione una opcion: ";
}


void opcionCargarArticulo(GestorDeCompra& gestor) {
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
    gestor.crearArticulo(id, nombre, precio);
}

void opcionCargarProveedor(GestorDeCompra& gestor) {
    string id, nombre, cuit;
    cout << "\n=== CARGAR PROVEEDOR ===" << endl;
    cout << "ID: ";
    getline(cin, id);
    cout << "Nombre: ";
    getline(cin, nombre);
    cout << "CUIT: ";
    getline(cin, cuit);
    gestor.crearProveedor(id, nombre, cuit);
}

void opcionCargarEmpleado(GestorDeCompra& gestor) {
    string id, nombre, apellido;
    cout << "\n=== CARGAR EMPLEADO ===" << endl;
    cout << "ID: ";
    getline(cin, id);
    cout << "Nombre: ";
    getline(cin, nombre);
    cout << "Apellido: ";
    getline(cin, apellido);
    gestor.crearEmpleado(id, nombre, apellido);
}

void opcionCrearPedido(GestorDeCompra& gestor) {
    string idEmpleado, idProveedor, fecha;
    vector<pair<string, int>> items;

    cout << "\n=== CREAR PEDIDO ===" << endl;

    gestor.listarEmpleados();
    cout << "\nID del Empleado: ";
    getline(cin, idEmpleado);

    gestor.listarProveedores();
    cout << "\nID del Proveedor: ";
    getline(cin, idProveedor);

    cout << "Fecha (YYYY-MM-DD): ";
    getline(cin, fecha);

    gestor.listarArticulos();
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
    gestor.crearPedido(idEmpleado, idProveedor, fecha, items);
}

void crudCrearProveedor(GestorDeCompra& gestor) {
    string id, nombre, cuit;
    cout << "\nID: ";
    getline(cin, id);
    cout << "Nombre: ";
    getline(cin, nombre);
    cout << "CUIT: ";
    getline(cin, cuit);
    gestor.crearProveedor(id, nombre, cuit);
}

void crudLeerProveedor(GestorDeCompra& gestor) {
    string id;
    cout << "\nID del Proveedor a buscar: ";
    getline(cin, id);
    gestor.leerProveedor(id);
}

void crudActualizarProveedor(GestorDeCompra& gestor) {
    string id, nuevoNombre;
    gestor.listarProveedores();
    cout << "\nID del Proveedor a actualizar: ";
    getline(cin, id);
    cout << "Nuevo nombre: ";
    getline(cin, nuevoNombre);
    gestor.actualizarProveedor(id, nuevoNombre);
}

void crudEliminarProveedor(GestorDeCompra& gestor) {
    string id;
    gestor.listarProveedores();
    cout << "\nID del Proveedor a eliminar: ";
    getline(cin, id);
    gestor.eliminarProveedor(id);
}

void opcionCRUDProveedores(GestorDeCompra& gestor) {
    int opcionCRUD;
    do {
        mostrarMenuCRUDProveedores();
        cin >> opcionCRUD;
        limpiarBuffer();

        switch (opcionCRUD) {
            case 1: crudCrearProveedor(gestor); break;
            case 2: crudLeerProveedor(gestor); break;
            case 3: gestor.listarProveedores(); break;
            case 4: crudActualizarProveedor(gestor); break;
            case 5: crudEliminarProveedor(gestor); break;
            case 0: cout << "Volviendo al menu principal..." << endl; break;
            default: cout << "Opcion invalida." << endl;
        }
    } while (opcionCRUD != 0);
}

int main() {
    GestorDeCompra gestor;
    gestor.cargarDatosIniciales();

    int opcion;
    do {
        mostrarMenuPrincipal();
        cin >> opcion;
        limpiarBuffer();

        switch (opcion) {
            case 1: opcionCargarArticulo(gestor); break;
            case 2: opcionCargarProveedor(gestor); break;
            case 3: opcionCargarEmpleado(gestor); break;
            case 4: opcionCrearPedido(gestor); break;
            case 5: gestor.mostrarPedidos(); break;
            case 6: opcionCRUDProveedores(gestor); break;
            case 7: gestor.listarArticulos(); break;
            case 8: gestor.listarEmpleados(); break;
            case 0: cout << "\nGracias por usar el sistema. Adios!" << endl; break;
            default: cout << "Opcion invalida. Intente nuevamente." << endl;
        }

        if (opcion != 0) {
            pausar();
        }

    } while (opcion != 0);

    return 0;
}
