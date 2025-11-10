#include "../include/itempedido.h"
#include <iostream> // Para nullptr

ItemPedido::ItemPedido(Articulo* art, int cant)
    : articulo(art), cantidad(cant) {
    if (articulo != nullptr) {
        // Congelamos el precio al momento de crear el item
        this->precioCongelado = articulo->getPrecioActual();
    } else {
        this->precioCongelado = 0.0;
    }
}

ItemPedido::~ItemPedido() {
    // No eliminamos 'articulo' aquí porque ItemPedido no es su dueño.
}

double ItemPedido::calcularSubtotal() const {
    return precioCongelado * cantidad;
}

Articulo* ItemPedido::getArticulo() const {
    return articulo;
}

int ItemPedido::getCantidad() const {
    return cantidad;
}

double ItemPedido::getPrecioCongelado() const {
    return precioCongelado;
}