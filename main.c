#include <stdio.h>
#include "repuestos.h"

int main() {
    struct Repuesto repuestos[100];
    struct Cliente clientes[100];
    struct Venta ventas[1000];
    int numRepuestos = 0;
    int numClientes = 0;
    int numVentas = 0;

    int opc, subOpc;
    
    printf("=== BIENVENIDO AL SISTEMA DE CONTROL DE REPUESTOS ===\n");
    printf("Una solución completa para el manejo de inventario y ventas\n");
    
    do {
        opc = menu();
        switch (opc) {
            case 1: // Gestión de Repuestos
                printf("\n=== GESTIÓN DE REPUESTOS ===\n");
                printf("1. Crear repuestos iniciales\n");
                printf("2. Agregar nuevo repuesto\n");
                printf("3. Ver todos los repuestos\n");
                printf("4. Actualizar stock\n");
                printf("Seleccione una opción: ");
                scanf("%d", &subOpc);
                
                switch(subOpc) {
                    case 1:
                        crearRepuestos();
                        break;
                    case 2:
                        agregarRepuesto();
                        break;
                    case 3:
                        if(cargarRepuestos(repuestos, &numRepuestos)) {
                            imprimirRepuestos(repuestos, numRepuestos);
                        } else {
                            printf("No se pudieron cargar los repuestos.\n");
                        }
                        break;
                    case 4:
                        actualizarStock();
                        break;
                    default:
                        printf("Opción no válida.\n");
                        break;
                }
                break;
                
            case 2: // Gestión de Clientes
                printf("\n=== GESTIÓN DE CLIENTES ===\n");
                printf("1. Crear clientes iniciales\n");
                printf("2. Agregar nuevo cliente\n");
                printf("3. Ver todos los clientes\n");
                printf("Seleccione una opción: ");
                scanf("%d", &subOpc);
                
                switch(subOpc) {
                    case 1:
                        crearClientes();
                        break;
                    case 2:
                        agregarCliente();
                        break;
                    case 3:
                        if(cargarClientes(clientes, &numClientes)) {
                            imprimirClientes(clientes, numClientes);
                        } else {
                            printf("No se pudieron cargar los clientes.\n");
                        }
                        break;
                    default:
                        printf("Opción no válida.\n");
                        break;
                }
                break;
                
            case 3: // Registrar Venta
                registrarVenta();
                break;
                
            case 4: // Consultar Stock
                if(cargarRepuestos(repuestos, &numRepuestos)) {
                    imprimirRepuestos(repuestos, numRepuestos);
                } else {
                    printf("No se pudieron cargar los repuestos.\n");
                }
                break;
                
            case 5: // Verificar Stock Mínimo
                verificarStockMinimo();
                break;
                
            case 6: // Reportes de Ventas
                printf("\n=== REPORTES DE VENTAS ===\n");
                printf("1. Ver todas las ventas\n");
                printf("2. Ventas por fecha\n");
                printf("3. Ventas por cliente\n");
                printf("Seleccione una opción: ");
                scanf("%d", &subOpc);
                
                switch(subOpc) {
                    case 1:
                        if(cargarVentas(ventas, &numVentas)) {
                            imprimirVentas(ventas, numVentas);
                        } else {
                            printf("No hay ventas registradas.\n");
                        }
                        break;
                    case 2:
                        reporteVentasPorFecha();
                        break;
                    case 3:
                        reporteVentasPorCliente();
                        break;
                    default:
                        printf("Opción no válida.\n");
                        break;
                }
                break;
                
            case 7: // Buscar Repuesto
                buscarRepuesto();
                break;
                
            case 8: // Buscar Cliente
                buscarCliente();
                break;
                
            case 9: // Salir
                printf("Gracias por usar el Sistema de Control de Repuestos.\n");
                printf("¡Hasta pronto!\n");
                break;
                
            default:
                printf("Opción no válida. Por favor, intente de nuevo.\n");
                break;
        }
        
        if (opc != 9) {
            printf("\nPresione Enter para continuar...");
            getchar();
            getchar();
        }
        
    } while (opc != 9);
    
    return 0;
}
