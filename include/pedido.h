#ifndef PEDIDO_H
#define PEDIDO_H

#include "empleado.h"
#include "proveedor.h"
#include "itempedido.h"
#include <vector>
#include <string>

class Pedido {
private:
    static int contadorPedidos;
    int nroPedido;
    std::string fecha;
    
    Empleado* empleado;   
    Proveedor* proveedor;
    
    std::vector<ItemPedido*> items; 

public:
    Pedido(Empleado* emp, Proveedor* prov, const std::string& fecha);
    ~Pedido();

    void agregarItem(Articulo* articulo, int cantidad);
    double calcularTotal() const;

    int getNroPedido() const;
    std::string getFecha() const;
    Empleado* getEmpleado() const;
    Proveedor* getProveedor() const;
    
    const std::vector<ItemPedido*>& getItems() const;
};

#endif
