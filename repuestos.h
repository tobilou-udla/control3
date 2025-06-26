#ifndef REPUESTOS_H
#define REPUESTOS_H

struct Repuesto
{
    int id;
    char codigo[20];
    char nombre[100];
    char categoria[50];  // Motor, Frenos, Suspension, etc.
    char marca[50];
    int stock;
    float precio;
    int stockMinimo;
};

struct Cliente
{
    int id;
    char nombre[100];
    char telefono[20];
    char email[50];
    char direccion[150];
};

struct Venta
{
    int id;
    int idCliente;
    char fechaVenta[20];
    struct Repuesto repuesto;
    int cantidad;
    float subtotal;
    float total;
};

// Funciones para repuestos
void crearRepuestos();
void agregarRepuesto();
void imprimirRepuestos(struct Repuesto repuestos[], int numRepuestos);
void guardarRepuestos(struct Repuesto repuestos[], int numRepuestos);
int cargarRepuestos(struct Repuesto repuestos[], int *numRepuestos);
void buscarRepuesto();
void actualizarStock();
void verificarStockMinimo();

// Funciones para clientes
void crearClientes();
void agregarCliente();
void imprimirClientes(struct Cliente clientes[], int numClientes);
void guardarClientes(struct Cliente clientes[], int numClientes);
int cargarClientes(struct Cliente clientes[], int *numClientes);
void buscarCliente();

// Funciones para ventas
void registrarVenta();
void imprimirVentas(struct Venta ventas[], int numVentas);
void guardarVentas(struct Venta ventas[], int numVentas);
int cargarVentas(struct Venta ventas[], int *numVentas);
void reporteVentasPorFecha();
void reporteVentasPorCliente();

// Funciones auxiliares
void leerCadena(char *cadena, int num);
int menu();
void obtenerFechaActual(char *fecha);

#endif
