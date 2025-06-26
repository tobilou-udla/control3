#include <stdio.h>
#include <string.h>
#include <time.h>
#include "repuestos.h"

void leerCadena(char *cadena, int num){
    fflush(stdin);
    fgets(cadena, num, stdin);
    int len = strlen(cadena) - 1;
    if (len >= 0 && cadena[len] == '\n') {
        cadena[len] = '\0';
    }
}

void obtenerFechaActual(char *fecha) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(fecha, "%02d/%02d/%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
}

int menu(){
    int opc;
    printf("\n=== SISTEMA DE CONTROL DE REPUESTOS ===\n");
    printf("=====================================\n");
    printf("1. Gestión de Repuestos\n");
    printf("2. Gestión de Clientes\n");
    printf("3. Registrar Venta\n");
    printf("4. Consultar Stock\n");
    printf("5. Verificar Stock Mínimo\n");
    printf("6. Reportes de Ventas\n");
    printf("7. Buscar Repuesto\n");
    printf("8. Buscar Cliente\n");
    printf("9. Salir\n");
    printf("Seleccione una opción: ");
    scanf("%d", &opc);
    fflush(stdin);
    return opc;
}

void crearRepuestos(){
    struct Repuesto repuestos[] = {
        {1, "BR001", "Pastillas de Freno Delanteras", "Frenos", "Bosch", 15, 85.50, 5},
        {2, "MT002", "Filtro de Aceite", "Motor", "Mann", 25, 12.75, 8},
        {3, "SU003", "Amortiguador Delantero", "Suspension", "Monroe", 8, 145.00, 3},
        {4, "EL004", "Bujías (Set 4)", "Electrico", "NGK", 20, 32.50, 6},
        {5, "FR005", "Discos de Freno Traseros", "Frenos", "Brembo", 10, 95.75, 4},
        {6, "MT006", "Correa de Distribución", "Motor", "Gates", 12, 55.25, 4},
        {7, "SU007", "Rotula de Dirección", "Suspension", "TRW", 18, 28.90, 5},
        {8, "EL008", "Alternador", "Electrico", "Valeo", 5, 185.00, 2},
        {9, "FR009", "Líquido de Frenos DOT4", "Frenos", "Castrol", 30, 8.50, 10},
        {10, "MT010", "Aceite Motor 5W30", "Motor", "Mobil1", 40, 25.75, 15}
    };
    
    guardarRepuestos(repuestos, 10);
    printf("Repuestos iniciales creados y guardados correctamente.\n");
}

void agregarRepuesto(){
    struct Repuesto repuestos[100];
    int numRepuestos = 0;
    
    if(!cargarRepuestos(repuestos, &numRepuestos)) {
        printf("Error al cargar repuestos existentes.\n");
        return;
    }
    
    if(numRepuestos >= 100) {
        printf("No se pueden agregar más repuestos. Límite alcanzado.\n");
        return;
    }
    
    struct Repuesto nuevoRepuesto;
    nuevoRepuesto.id = numRepuestos + 1;
    
    printf("Ingrese el código del repuesto: ");
    leerCadena(nuevoRepuesto.codigo, sizeof(nuevoRepuesto.codigo));
    
    printf("Ingrese el nombre del repuesto: ");
    leerCadena(nuevoRepuesto.nombre, sizeof(nuevoRepuesto.nombre));
    
    printf("Ingrese la categoría: ");
    leerCadena(nuevoRepuesto.categoria, sizeof(nuevoRepuesto.categoria));
    
    printf("Ingrese la marca: ");
    leerCadena(nuevoRepuesto.marca, sizeof(nuevoRepuesto.marca));
    
    printf("Ingrese el stock inicial: ");
    scanf("%d", &nuevoRepuesto.stock);
    
    printf("Ingrese el precio: ");
    scanf("%f", &nuevoRepuesto.precio);
    
    printf("Ingrese el stock mínimo: ");
    scanf("%d", &nuevoRepuesto.stockMinimo);
    
    repuestos[numRepuestos] = nuevoRepuesto;
    numRepuestos++;
    
    guardarRepuestos(repuestos, numRepuestos);
    printf("Repuesto agregado correctamente.\n");
}

void imprimirRepuestos(struct Repuesto repuestos[], int numRepuestos){
    printf("\n=== INVENTARIO DE REPUESTOS ===\n");
    printf("=====================================\n");
    printf("%-3s %-8s %-25s %-12s %-10s %-5s %-8s %-5s\n", 
           "ID", "Código", "Nombre", "Categoría", "Marca", "Stock", "Precio", "Min");
    printf("=====================================\n");
    
    for (int i = 0; i < numRepuestos; i++) {
        printf("%-3d %-8s %-25s %-12s %-10s %-5d $%-7.2f %-5d", 
               repuestos[i].id, repuestos[i].codigo, repuestos[i].nombre,
               repuestos[i].categoria, repuestos[i].marca, repuestos[i].stock,
               repuestos[i].precio, repuestos[i].stockMinimo);
        
        if(repuestos[i].stock <= repuestos[i].stockMinimo) {
            printf(" *** STOCK BAJO ***");
        }
        printf("\n");
    }
    
    if (numRepuestos == 0) {
        printf("No hay repuestos registrados.\n");
    }
}

void guardarRepuestos(struct Repuesto repuestos[], int numRepuestos){
    FILE *archivo = fopen("repuestos.dat", "wb");
    if (archivo == NULL) {
        printf("Error al abrir el archivo para guardar los repuestos.\n");
        return;
    }
    fwrite(repuestos, sizeof(struct Repuesto), numRepuestos, archivo);
    fclose(archivo);
}

int cargarRepuestos(struct Repuesto repuestos[], int *numRepuestos){
    FILE *archivo = fopen("repuestos.dat", "rb");
    if (archivo == NULL) {
        printf("Error al abrir el archivo para cargar los repuestos.\n");
        return 0;
    }
    *numRepuestos = fread(repuestos, sizeof(struct Repuesto), 100, archivo);
    fclose(archivo);
    return 1;
}

void buscarRepuesto(){
    struct Repuesto repuestos[100];
    int numRepuestos = 0;
    char busqueda[100];
    int encontrado = 0;
    
    if(!cargarRepuestos(repuestos, &numRepuestos)) {
        printf("Error al cargar repuestos.\n");
        return;
    }
    
    printf("Ingrese código o nombre del repuesto a buscar: ");
    leerCadena(busqueda, sizeof(busqueda));
    
    printf("\n=== RESULTADOS DE BÚSQUEDA ===\n");
    for (int i = 0; i < numRepuestos; i++) {
        if (strstr(repuestos[i].codigo, busqueda) != NULL || 
            strstr(repuestos[i].nombre, busqueda) != NULL) {
            printf("ID: %d | Código: %s | Nombre: %s\n", 
                   repuestos[i].id, repuestos[i].codigo, repuestos[i].nombre);
            printf("Categoría: %s | Marca: %s\n", 
                   repuestos[i].categoria, repuestos[i].marca);
            printf("Stock: %d | Precio: $%.2f | Stock Mínimo: %d\n", 
                   repuestos[i].stock, repuestos[i].precio, repuestos[i].stockMinimo);
            printf("-------------------------------------\n");
            encontrado = 1;
        }
    }
    
    if (!encontrado) {
        printf("No se encontraron repuestos que coincidan con la búsqueda.\n");
    }
}

void actualizarStock(){
    struct Repuesto repuestos[100];
    int numRepuestos = 0;
    int id, nuevoStock;
    
    if(!cargarRepuestos(repuestos, &numRepuestos)) {
        printf("Error al cargar repuestos.\n");
        return;
    }
    
    imprimirRepuestos(repuestos, numRepuestos);
    
    printf("Ingrese el ID del repuesto a actualizar: ");
    scanf("%d", &id);
    
    if (id < 1 || id > numRepuestos) {
        printf("ID de repuesto inválido.\n");
        return;
    }
    
    printf("Stock actual: %d\n", repuestos[id-1].stock);
    printf("Ingrese el nuevo stock: ");
    scanf("%d", &nuevoStock);
    
    if (nuevoStock < 0) {
        printf("El stock no puede ser negativo.\n");
        return;
    }
    
    repuestos[id-1].stock = nuevoStock;
    guardarRepuestos(repuestos, numRepuestos);
    
    printf("Stock actualizado correctamente.\n");
    if (nuevoStock <= repuestos[id-1].stockMinimo) {
        printf("ADVERTENCIA: El stock está por debajo del mínimo (%d).\n", 
               repuestos[id-1].stockMinimo);
    }
}

void verificarStockMinimo(){
    struct Repuesto repuestos[100];
    int numRepuestos = 0;
    int hayAlerta = 0;
    
    if(!cargarRepuestos(repuestos, &numRepuestos)) {
        printf("Error al cargar repuestos.\n");
        return;
    }
    
    printf("\n=== ALERTA DE STOCK MÍNIMO ===\n");
    printf("=====================================\n");
    
    for (int i = 0; i < numRepuestos; i++) {
        if (repuestos[i].stock <= repuestos[i].stockMinimo) {
            printf("ALERTA: %s (Código: %s)\n", repuestos[i].nombre, repuestos[i].codigo);
            printf("        Stock actual: %d | Stock mínimo: %d\n", 
                   repuestos[i].stock, repuestos[i].stockMinimo);
            printf("        Se recomienda reabastecer urgentemente.\n");
            printf("-------------------------------------\n");
            hayAlerta = 1;
        }
    }
    
    if (!hayAlerta) {
        printf("Todos los repuestos tienen stock adecuado.\n");
    }
}

void crearClientes(){
    struct Cliente clientes[] = {
        {1, "Juan Pérez", "0999123456", "juan.perez@email.com", "Av. Principal 123"},
        {2, "María González", "0998765432", "maria.gonzalez@email.com", "Calle Secundaria 456"},
        {3, "Carlos Rodríguez", "0997654321", "carlos.rodriguez@email.com", "Sector Norte 789"},
        {4, "Ana Martínez", "0996543210", "ana.martinez@email.com", "Barrio Centro 321"},
        {5, "Luis Torres", "0995432109", "luis.torres@email.com", "Zona Sur 654"}
    };
    
    guardarClientes(clientes, 5);
    printf("Clientes iniciales creados y guardados correctamente.\n");
}

void agregarCliente(){
    struct Cliente clientes[100];
    int numClientes = 0;
    
    if(!cargarClientes(clientes, &numClientes)) {
        numClientes = 0; // Si no hay archivo, empezar desde 0
    }
    
    if(numClientes >= 100) {
        printf("No se pueden agregar más clientes. Límite alcanzado.\n");
        return;
    }
    
    struct Cliente nuevoCliente;
    nuevoCliente.id = numClientes + 1;
    
    printf("Ingrese el nombre del cliente: ");
    leerCadena(nuevoCliente.nombre, sizeof(nuevoCliente.nombre));
    
    printf("Ingrese el teléfono: ");
    leerCadena(nuevoCliente.telefono, sizeof(nuevoCliente.telefono));
    
    printf("Ingrese el email: ");
    leerCadena(nuevoCliente.email, sizeof(nuevoCliente.email));
    
    printf("Ingrese la dirección: ");
    leerCadena(nuevoCliente.direccion, sizeof(nuevoCliente.direccion));
    
    clientes[numClientes] = nuevoCliente;
    numClientes++;
    
    guardarClientes(clientes, numClientes);
    printf("Cliente agregado correctamente.\n");
}

void imprimirClientes(struct Cliente clientes[], int numClientes){
    printf("\n=== LISTA DE CLIENTES ===\n");
    printf("=====================================\n");
    
    for (int i = 0; i < numClientes; i++) {
        printf("ID: %d\n", clientes[i].id);
        printf("Nombre: %s\n", clientes[i].nombre);
        printf("Teléfono: %s\n", clientes[i].telefono);
        printf("Email: %s\n", clientes[i].email);
        printf("Dirección: %s\n", clientes[i].direccion);
        printf("-------------------------------------\n");
    }
    
    if (numClientes == 0) {
        printf("No hay clientes registrados.\n");
    }
}

void guardarClientes(struct Cliente clientes[], int numClientes){
    FILE *archivo = fopen("clientes.dat", "wb");
    if (archivo == NULL) {
        printf("Error al abrir el archivo para guardar los clientes.\n");
        return;
    }
    fwrite(clientes, sizeof(struct Cliente), numClientes, archivo);
    fclose(archivo);
}

int cargarClientes(struct Cliente clientes[], int *numClientes){
    FILE *archivo = fopen("clientes.dat", "rb");
    if (archivo == NULL) {
        return 0;
    }
    *numClientes = fread(clientes, sizeof(struct Cliente), 100, archivo);
    fclose(archivo);
    return 1;
}

void buscarCliente(){
    struct Cliente clientes[100];
    int numClientes = 0;
    char busqueda[100];
    int encontrado = 0;
    
    if(!cargarClientes(clientes, &numClientes)) {
        printf("Error al cargar clientes.\n");
        return;
    }
    
    printf("Ingrese nombre o teléfono del cliente a buscar: ");
    leerCadena(busqueda, sizeof(busqueda));
    
    printf("\n=== RESULTADOS DE BÚSQUEDA ===\n");
    for (int i = 0; i < numClientes; i++) {
        if (strstr(clientes[i].nombre, busqueda) != NULL || 
            strstr(clientes[i].telefono, busqueda) != NULL) {
            printf("ID: %d | Nombre: %s\n", clientes[i].id, clientes[i].nombre);
            printf("Teléfono: %s | Email: %s\n", clientes[i].telefono, clientes[i].email);
            printf("Dirección: %s\n", clientes[i].direccion);
            printf("-------------------------------------\n");
            encontrado = 1;
        }
    }
    
    if (!encontrado) {
        printf("No se encontraron clientes que coincidan con la búsqueda.\n");
    }
}

void registrarVenta(){
    struct Repuesto repuestos[100];
    struct Cliente clientes[100];
    struct Venta ventas[1000];
    int numRepuestos = 0, numClientes = 0, numVentas = 0;
    int idRepuesto, idCliente, cantidad;
    
    // Cargar datos
    if(!cargarRepuestos(repuestos, &numRepuestos)) {
        printf("Error: No hay repuestos registrados.\n");
        return;
    }
    
    if(!cargarClientes(clientes, &numClientes)) {
        printf("Error: No hay clientes registrados.\n");
        return;
    }
    
    if(!cargarVentas(ventas, &numVentas)) {
        numVentas = 0; // Si no hay archivo, empezar desde 0
    }
    
    // Mostrar repuestos disponibles
    printf("\n=== REPUESTOS DISPONIBLES ===\n");
    imprimirRepuestos(repuestos, numRepuestos);
    
    printf("\nIngrese el ID del repuesto: ");
    scanf("%d", &idRepuesto);
    
    if (idRepuesto < 1 || idRepuesto > numRepuestos) {
        printf("ID de repuesto inválido.\n");
        return;
    }
    
    printf("Stock disponible: %d\n", repuestos[idRepuesto-1].stock);
    printf("Ingrese la cantidad a vender: ");
    scanf("%d", &cantidad);
    
    if (cantidad <= 0) {
        printf("La cantidad debe ser mayor a 0.\n");
        return;
    }
    
    if (cantidad > repuestos[idRepuesto-1].stock) {
        printf("Stock insuficiente. Stock disponible: %d\n", repuestos[idRepuesto-1].stock);
        return;
    }
    
    // Mostrar clientes
    printf("\n=== CLIENTES REGISTRADOS ===\n");
    imprimirClientes(clientes, numClientes);
    
    printf("\nIngrese el ID del cliente: ");
    scanf("%d", &idCliente);
    
    if (idCliente < 1 || idCliente > numClientes) {
        printf("ID de cliente inválido.\n");
        return;
    }
    
    // Crear la venta
    struct Venta nuevaVenta;
    nuevaVenta.id = numVentas + 1;
    nuevaVenta.idCliente = idCliente;
    obtenerFechaActual(nuevaVenta.fechaVenta);
    nuevaVenta.repuesto = repuestos[idRepuesto-1];
    nuevaVenta.cantidad = cantidad;
    nuevaVenta.subtotal = repuestos[idRepuesto-1].precio * cantidad;
    nuevaVenta.total = nuevaVenta.subtotal; // Sin impuestos por simplicidad
    
    // Actualizar stock
    repuestos[idRepuesto-1].stock -= cantidad;
    
    // Guardar datos
    ventas[numVentas] = nuevaVenta;
    numVentas++;
    
    guardarVentas(ventas, numVentas);
    guardarRepuestos(repuestos, numRepuestos);
    
    // Mostrar resumen de venta
    printf("\n=== VENTA REGISTRADA ===\n");
    printf("Venta ID: %d\n", nuevaVenta.id);
    printf("Cliente: %s\n", clientes[idCliente-1].nombre);
    printf("Fecha: %s\n", nuevaVenta.fechaVenta);
    printf("Repuesto: %s\n", nuevaVenta.repuesto.nombre);
    printf("Cantidad: %d\n", nuevaVenta.cantidad);
    printf("Precio unitario: $%.2f\n", nuevaVenta.repuesto.precio);
    printf("Total: $%.2f\n", nuevaVenta.total);
    
    if (repuestos[idRepuesto-1].stock <= repuestos[idRepuesto-1].stockMinimo) {
        printf("\nADVERTENCIA: Stock bajo para %s (Stock actual: %d, Mínimo: %d)\n", 
               repuestos[idRepuesto-1].nombre, repuestos[idRepuesto-1].stock, 
               repuestos[idRepuesto-1].stockMinimo);
    }
}

void imprimirVentas(struct Venta ventas[], int numVentas){
    printf("\n=== HISTORIAL DE VENTAS ===\n");
    printf("=====================================\n");
    
    for (int i = 0; i < numVentas; i++) {
        printf("Venta ID: %d | Fecha: %s\n", ventas[i].id, ventas[i].fechaVenta);
        printf("Cliente ID: %d\n", ventas[i].idCliente);
        printf("Repuesto: %s (Código: %s)\n", ventas[i].repuesto.nombre, ventas[i].repuesto.codigo);
        printf("Cantidad: %d | Precio unit.: $%.2f | Total: $%.2f\n", 
               ventas[i].cantidad, ventas[i].repuesto.precio, ventas[i].total);
        printf("-------------------------------------\n");
    }
    
    if (numVentas == 0) {
        printf("No hay ventas registradas.\n");
    }
}

void guardarVentas(struct Venta ventas[], int numVentas){
    FILE *archivo = fopen("ventas.dat", "wb");
    if (archivo == NULL) {
        printf("Error al abrir el archivo para guardar las ventas.\n");
        return;
    }
    fwrite(ventas, sizeof(struct Venta), numVentas, archivo);
    fclose(archivo);
}

int cargarVentas(struct Venta ventas[], int *numVentas){
    FILE *archivo = fopen("ventas.dat", "rb");
    if (archivo == NULL) {
        return 0;
    }
    *numVentas = fread(ventas, sizeof(struct Venta), 1000, archivo);
    fclose(archivo);
    return 1;
}

void reporteVentasPorFecha(){
    struct Venta ventas[1000];
    int numVentas = 0;
    char fecha[20];
    float totalDia = 0;
    int ventasDelDia = 0;
    
    if(!cargarVentas(ventas, &numVentas)) {
        printf("No hay ventas registradas.\n");
        return;
    }
    
    printf("Ingrese la fecha (DD/MM/AAAA): ");
    leerCadena(fecha, sizeof(fecha));
    
    printf("\n=== VENTAS DEL DÍA %s ===\n", fecha);
    printf("=====================================\n");
    
    for (int i = 0; i < numVentas; i++) {
        if (strcmp(ventas[i].fechaVenta, fecha) == 0) {
            printf("Venta ID: %d | Repuesto: %s | Cantidad: %d | Total: $%.2f\n", 
                   ventas[i].id, ventas[i].repuesto.nombre, ventas[i].cantidad, ventas[i].total);
            totalDia += ventas[i].total;
            ventasDelDia++;
        }
    }
    
    printf("=====================================\n");
    printf("Total de ventas del día: %d\n", ventasDelDia);
    printf("Monto total vendido: $%.2f\n", totalDia);
}

void reporteVentasPorCliente(){
    struct Venta ventas[1000];
    struct Cliente clientes[100];
    int numVentas = 0, numClientes = 0;
    int idCliente;
    float totalCliente = 0;
    int ventasCliente = 0;
    
    if(!cargarVentas(ventas, &numVentas)) {
        printf("No hay ventas registradas.\n");
        return;
    }
    
    if(!cargarClientes(clientes, &numClientes)) {
        printf("No hay clientes registrados.\n");
        return;
    }
    
    imprimirClientes(clientes, numClientes);
    
    printf("\nIngrese el ID del cliente: ");
    scanf("%d", &idCliente);
    
    if (idCliente < 1 || idCliente > numClientes) {
        printf("ID de cliente inválido.\n");
        return;
    }
    
    printf("\n=== HISTORIAL DE COMPRAS - %s ===\n", clientes[idCliente-1].nombre);
    printf("=====================================\n");
    
    for (int i = 0; i < numVentas; i++) {
        if (ventas[i].idCliente == idCliente) {
            printf("Fecha: %s | Repuesto: %s | Cantidad: %d | Total: $%.2f\n", 
                   ventas[i].fechaVenta, ventas[i].repuesto.nombre, 
                   ventas[i].cantidad, ventas[i].total);
            totalCliente += ventas[i].total;
            ventasCliente++;
        }
    }
    
    printf("=====================================\n");
    printf("Total de compras: %d\n", ventasCliente);
    printf("Monto total gastado: $%.2f\n", totalCliente);
}
