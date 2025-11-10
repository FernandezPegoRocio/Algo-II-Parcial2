#include "../include/pedido.h"

using namespace std;

int Pedido::contadorPedidos = 0;

// ----- ARCHIVO CORREGIDO -----
// El orden de inicialización (fecha, empleado, proveedor)
// ahora coincide con el orden de declaración en pedido.h
// para eliminar la advertencia -Wreorder
Pedido::Pedido(Empleado* emp, Proveedor* prov, const string& fecha)
    : fecha(fecha), empleado(emp), proveedor(prov) {
    nroPedido = ++contadorPedidos;
}

Pedido::~Pedido() {
    // Elimina items (Composición - Pedido es dueño de sus items)
    for (auto item : items) {
        delete item;
    }
    items.clear();
    // NO elimina empleado ni proveedor (Agregación)
}

void Pedido::agregarItem(Articulo* articulo, int cantidad) {
    ItemPedido* nuevoItem = new ItemPedido(articulo, cantidad);
    items.push_back(nuevoItem);
}

double Pedido::calcularTotal() const {
    double total = 0.0;
    for (const auto& item : items) {
        total += item->calcularSubtotal();
    }
    return total;
}

int Pedido::getNroPedido() const {
    return nroPedido;
}

string Pedido::getFecha() const {
    return fecha;
}

Empleado* Pedido::getEmpleado() const {
    return empleado;
}

Proveedor* Pedido::getProveedor() const {
    return proveedor;
}

const vector<ItemPedido*>& Pedido::getItems() const {
    return items;
}