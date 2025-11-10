#ifndef ITEMPEDIDO_H
#define ITEMPEDIDO_H

#include "articulo.h" 

class ItemPedido {
private:
    Articulo* articulo;
    int cantidad;
    double precioCongelado; // Precio histórico al momento de la compra

public:
    ItemPedido(Articulo* art, int cant);
    ~ItemPedido();

    double calcularSubtotal() const;
    Articulo* getArticulo() const;
    int getCantidad() const;
    double getPrecioCongelado() const;
};

#endif