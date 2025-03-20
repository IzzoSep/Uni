#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* ======== ESTRUCTURAS PRINCIPALES ======== */

// Estructura para representar un cliente
struct Cliente {
	char nombres[50];
	char apellidos[50];
	char rut[12];
	char Numero_verificador[2];
};

// Estructura para representar una cuenta bancaria
struct Cuenta {
	int numero;
	float saldo;
	float comision;
	float interes;
	int tipo; // 1 = Corriente, 2 = Ahorros, 3 = Vista
	float linea_credito; // Solo para cuentas corrientes
	int estado; // Solo para cuentas de ahorro
	int retiros_mes; // Contador de retiros para cuentas vista
	char rut_cliente[12]; // RUT del cliente asociado
	char numero_verificador_cliente[2];
};

// Estructura para representar una sucursal bancaria
struct Sucursal {
	char nombre[50];
	struct Cliente clientes[100];
	struct Cuenta cuentas[200];
	int num_clientes;
	int num_cuentas;
};

// Estructura para representar el banco completo
struct Banco {
	struct Sucursal sucursales[3];
	int num_sucursales;
} banco;

/* ======== FUNCIONES ======== */

// Inicializa el banco con datos predeterminados
void inicializar_banco() {
	banco.num_sucursales = 3;
	char nombres_sucursales[3][50] = {"Santiago", "Talca", "Curico"};

	for (int i = 0; i < banco.num_sucursales; i++) {
		strcpy(banco.sucursales[i].nombre, nombres_sucursales[i]);
		banco.sucursales[i].num_clientes = 0;
		banco.sucursales[i].num_cuentas = 0;
	}
}

// Agrega datos de prueba
void agregar_datos_prueba() {
	struct Cliente clientes[5] = {
		{"Juan", "Perez", "12345678", "K"},
		{"Maria", "Lopez", "87654321", "9"},
		{"Carlos", "Sanchez", "11223344", "7"},
		{"Ana", "Diaz", "22334455", "1"},
		{"Pedro", "Gonzalez", "66778899", "3"}
	};

	struct Cuenta cuentas[5] = {
		{1000, 500000, 2000, 0.01, 1, 100000, 1, 0, "12345678", "K"},
		{1001, 150000, 1500, 0.02, 2, 0.0, 1, 0, "87654321", "9"},
		{1002, 30000, 1000, 0.01, 3, 0.0, 1, 0, "11223344", "7"},
		{1003, 200000, 2500, 0.02, 2, 0.0, 1, 0, "22334455", "1"},
		{1004, 120000, 1000, 0.01, 1, 50000, 1, 0, "66778899", "3"}
	};

	for (int i = 0; i < banco.num_sucursales; i++) {
		banco.sucursales[i].clientes[banco.sucursales[i].num_clientes] = clientes[i];
		banco.sucursales[i].num_clientes++;
		banco.sucursales[i].cuentas[banco.sucursales[i].num_cuentas] = cuentas[i];
		banco.sucursales[i].num_cuentas++;
	}
}

// Calcula el interes y la comision de una cuenta
void calcular_interes_y_comision(struct Cuenta *cuenta) {
	if (cuenta->tipo == 1) {
		cuenta->interes = cuenta->saldo * 0.01; // Corriente: 1%
		cuenta->comision = 2000; // Comision fija
	} else if (cuenta->tipo == 2) {
		cuenta->interes = cuenta->saldo * 0.02; // Ahorros: 2%
		cuenta->comision = 1500; // Comision fija
	} else if (cuenta->tipo == 3) {
		cuenta->interes = cuenta->saldo * 0.01; // Vista: 1%
		cuenta->comision = 1000; // Comision fija
	}
}

// Genera un extracto mensual para un cliente
void extracto_mensual() {
	char rut[12];
	int encontrado = 0;

	printf("Ingrese el RUT del cliente: ");
	scanf("%s", rut);

	for (int i = 0; i < banco.num_sucursales && !encontrado; i++) {
		for (int j = 0; j < banco.sucursales[i].num_cuentas; j++) {
			struct Cuenta *cuenta = &banco.sucursales[i].cuentas[j];
			if (strcmp(cuenta->rut_cliente, rut) == 0) {
				encontrado = 1;
				calcular_interes_y_comision(cuenta);
				printf("\n=== Extracto mensual de la cuenta %d ===\n", cuenta->numero);
				printf("Saldo inicial: $%f\n", cuenta->saldo);
				printf("Intereses generados: $%f\n", cuenta->interes);
				printf("Comision mensual: $%f\n", cuenta->comision);
				printf("Saldo final: $%f\n", cuenta->saldo + cuenta->interes - cuenta->comision);
				return;
			}
		}
	}

	if (!encontrado) {
		printf("No se encontro una cuenta asociada a ese RUT.\n");
	}
}

// Muestra el saldo de los proximos meses
void mostrar_saldo_proximos_meses() {
	char rut[12];
	int meses;
	printf("Ingrese el RUT del cliente: ");
	scanf("%s", rut);
	printf("Ingrese el numero de meses a proyectar: ");
	scanf("%d", &meses);

	for (int i = 0; i < banco.num_sucursales; i++) {
		for (int j = 0; j < banco.sucursales[i].num_cuentas; j++) {
			struct Cuenta *cuenta = &banco.sucursales[i].cuentas[j];
			if (strcmp(cuenta->rut_cliente, rut) == 0) {
				printf("\n=== Proyeccion de saldo para la cuenta %d ===\n", cuenta->numero);
				float saldo_proyectado = cuenta->saldo;
				for (int mes = 1; mes <= meses; mes++) {
					calcular_interes_y_comision(cuenta);
					saldo_proyectado += cuenta->interes - cuenta->comision;
					printf("Mes %d: Saldo proyectado: $%f\n", mes, saldo_proyectado);
				}
				return;
			}
		}
	}
	printf("No se encontro una cuenta asociada a ese RUT.\n");
}

// Muestra todas las cuentas en el banco
void mostrar_cuentas() {
	printf("\n=== Cuentas en todas las sucursales ===\n");
	for (int i = 0; i < banco.num_sucursales; i++) {
		for (int j = 0; j < banco.sucursales[i].num_cuentas; j++) {
			struct Cuenta cuenta = banco.sucursales[i].cuentas[j];
			printf("Sucursal: %s, Cuenta: %d, RUT: %s-%s, Saldo: %f\n",
			       banco.sucursales[i].nombre, cuenta.numero,
			       cuenta.rut_cliente, cuenta.numero_verificador_cliente,
			       cuenta.saldo);


		}
	}
}

// Muestra todos los clientes y permite crear una nueva cuenta
void mostrar_clientes() {
	printf("\n=== Clientes en todas las sucursales ===\n");
	for (int i = 0; i < banco.num_sucursales; i++) {
		printf("\nSucursal: %s\n", banco.sucursales[i].nombre);
		for (int j = 0; j < banco.sucursales[i].num_clientes; j++) {
			struct Cliente cliente = banco.sucursales[i].clientes[j];
			printf("  RUT: %s-%s, Nombre: %s %s\n",
			       cliente.rut, cliente.Numero_verificador,
			       cliente.nombres, cliente.apellidos);

		}
	}
}

// Crea una nueva cuenta para un cliente
void crear_cuenta() {
	int sucursal_id;
	printf("\nSeleccione la sucursal (1: Santiago, 2: Talca, 3: Curico): ");
	scanf("%d", &sucursal_id);

	if (sucursal_id < 1 || sucursal_id > banco.num_sucursales) {
		printf("Sucursal invalida.\n");
		return;
	}

	struct Cliente nuevo_cliente;

	printf("Ingrese primer nombre del cliente: ");
	scanf("%s", nuevo_cliente.nombres);
	printf("Ingrese primer apellido del cliente: ");
	scanf("%s", nuevo_cliente.apellidos);

	printf("\nIngrese RUT del cliente (sin digito verificador): ");
	scanf("%s", nuevo_cliente.rut);

	printf("Ingrese digito verificador del cliente: ");
	scanf(" %c", &nuevo_cliente.Numero_verificador[0]);
	nuevo_cliente.Numero_verificador[1] = '\0';

	banco.sucursales[sucursal_id - 1].clientes[banco.sucursales[sucursal_id - 1].num_clientes] = nuevo_cliente;
	banco.sucursales[sucursal_id - 1].num_clientes++;

	struct Cuenta nueva_cuenta;
	nueva_cuenta.numero = 1000 + banco.sucursales[sucursal_id - 1].num_cuentas;
	nueva_cuenta.saldo = 0;
	nueva_cuenta.retiros_mes = 0;
	strcpy(nueva_cuenta.rut_cliente, nuevo_cliente.rut);
	strcpy(nueva_cuenta.numero_verificador_cliente, nuevo_cliente.Numero_verificador); // Copia el numero verificador

	int tipo_cuenta;
	printf("\nSeleccione el tipo de cuenta:\n");
	printf("1. Cuenta Corriente\n");
	printf("2. Cuenta de Ahorro\n");
	printf("3. Cuenta Vista\n");
	printf("Ingrese su opcion: ");
	scanf("%d", &tipo_cuenta);

	nueva_cuenta.tipo = tipo_cuenta;

	if (tipo_cuenta == 1) {
		printf("Ingrese linea de credito: ");
		scanf("%f", &nueva_cuenta.linea_credito);
	} else if (tipo_cuenta == 2) {
		printf("Cuenta de ahorros creada con saldo inicial de $100,000\n");
		nueva_cuenta.saldo = 100000;
		nueva_cuenta.estado = 1;
	} else if (tipo_cuenta == 3) {
		printf("Cuenta Vista creada.\n");
	} else {
		printf("Tipo de cuenta invalido.\n");
		return;
	}

	banco.sucursales[sucursal_id - 1].cuentas[banco.sucursales[sucursal_id - 1].num_cuentas] = nueva_cuenta;
	banco.sucursales[sucursal_id - 1].num_cuentas++;

	printf("\nCuenta creada exitosamente. Numero de cuenta: %d\n", nueva_cuenta.numero);
}

// Funcion para retirar dinero de una cuenta
void retirar_dinero() {
	char rut[12];
	printf("Ingrese el RUT del cliente: ");
	scanf("%s", rut);

	for (int i = 0; i < banco.num_sucursales; i++) {
		for (int j = 0; j < banco.sucursales[i].num_cuentas; j++) {
			struct Cuenta *cuenta = &banco.sucursales[i].cuentas[j];
			if (strcmp(cuenta->rut_cliente, rut) == 0) {
				float monto;
				printf("Ingrese el monto a retirar: ");
				scanf("%f", &monto);

				if (cuenta->tipo == 1 ||
				        (cuenta->tipo == 2 && cuenta->estado == 1 && cuenta->saldo - monto >= 0) ||
				        (cuenta->tipo == 3 && cuenta->saldo - monto >= 0 && cuenta->retiros_mes < 4)) {
					cuenta->saldo -= monto;
					cuenta->retiros_mes++;
					printf("Retiro exitoso de %f. Nuevo saldo: $%f\n", monto, cuenta->saldo);
				} else {
					printf("No se puede realizar el retiro. Verifique el saldo o el tipo de cuenta.\n");
				}
				return;
			}
		}
	}
	printf("No se encontro una cuenta asociada a ese RUT.\n");
}

// Funcion para depositar dinero en una cuenta
void depositar_dinero() {
	char rut[12];
	printf("Ingrese el RUT del cliente: ");
	scanf("%s", rut);

	for (int i = 0; i < banco.num_sucursales; i++) {
		for (int j = 0; j < banco.sucursales[i].num_cuentas; j++) {
			struct Cuenta *cuenta = &banco.sucursales[i].cuentas[j];
			if (strcmp(cuenta->rut_cliente, rut) == 0) {
				float monto;
				printf("Ingrese el monto a depositar : ");
				scanf("%f", &monto);
				cuenta->saldo += monto;
				printf("Deposito de %f realizado. Nuevo saldo: $%f\n", monto, cuenta->saldo);
				return;
			}
		}
	}
	printf("No se encontro una cuenta asociada a ese RUT.\n");
}

// Funcion para transferir dinero entre cuentas
void transferir_dinero() {
	char rut_origen[12], rut_destino[12];
	float monto;

	printf("Ingrese el RUT de la cuenta de origen: ");
	scanf("%s", rut_origen);
	printf("Ingrese el RUT de la cuenta de destino: ");
	scanf("%s", rut_destino);
	printf("Ingrese el monto a transferir: ");
	scanf("%f", &monto);

	struct Cuenta *cuenta_origen = NULL;
	struct Cuenta *cuenta_destino = NULL;

	for (int i = 0; i < banco.num_sucursales; i++) {
		for (int j = 0; j < banco.sucursales[i].num_cuentas; j++) {
			struct Cuenta *cuenta = &banco.sucursales[i].cuentas[j];
			if (strcmp(cuenta->rut_cliente, rut_origen) == 0) {
				cuenta_origen = cuenta;
			}
			if (strcmp(cuenta->rut_cliente, rut_destino) == 0) {
				cuenta_destino = cuenta;
			}
		}
	}

	if (cuenta_origen && cuenta_destino) {
		if (cuenta_origen->saldo >= monto) {
			cuenta_origen->saldo -= monto;
			cuenta_destino->saldo += monto;
			printf("Transferencia de %f realizada de cuenta %d a cuenta %d.\n", monto, cuenta_origen->numero, cuenta_destino->numero);
			printf("Nuevo saldo de la cuenta de origen: $%f\n", cuenta_origen->saldo);
			printf("Nuevo saldo de la cuenta de destino: $%f\n", cuenta_destino->saldo);
		} else {
			printf("Fondos insuficientes en la cuenta de origen.\n");
		}
	} else {
		printf("Una o ambas cuentas no fueron encontradas.\n");
	}
}

/* ======== Baterias de prueba ======== */

void prueba_creacion_cuenta() {
	printf("\n=== Prueba de Creacion de Cuenta ===\n");
	struct Cliente nuevo_cliente = {"Test", "Usuario", "99999999", "9"};
	banco.sucursales[0].clientes[banco.sucursales[0].num_clientes++] = nuevo_cliente;

	struct Cuenta nueva_cuenta = {2000, 0.0, 0.0, 0.0, 1, 100000.0, 1, 0, "99999999"};
	banco.sucursales[0].cuentas[banco.sucursales[0].num_cuentas++] = nueva_cuenta;

	printf("Cuenta creada con exito para %s %s.\n", nuevo_cliente.nombres, nuevo_cliente.apellidos);
}

void prueba_retiro_cuenta() {
	printf("\n=== Prueba de Retiro de Cuenta ===\n");
	struct Cuenta *cuenta = &banco.sucursales[0].cuentas[0];
	float monto_retiro = 100000.0;
	if (cuenta->saldo >= monto_retiro) {
		cuenta->saldo -= monto_retiro;
		printf("Retiro de %f realizado. Nuevo saldo: %f\n", monto_retiro, cuenta->saldo);
	} else {
		printf("Fondos insuficientes.\n");
	}
}

void prueba_deposito_cuenta() {
	printf("\n=== Prueba de Deposito en Cuenta ===\n");
	struct Cuenta *cuenta = &banco.sucursales[0].cuentas[0];
	float monto_deposito = 50000.0;
	cuenta->saldo += monto_deposito;
	printf("Deposito de %f realizado. Nuevo saldo: %f\n", monto_deposito, cuenta->saldo);
}

void prueba_transferencia_cuenta() {
	printf("\n=== Prueba de Transferencia entre Cuentas ===\n");
	struct Cuenta *cuenta_origen = &banco.sucursales[0].cuentas[0];
	struct Cuenta *cuenta_destino = &banco.sucursales[0].cuentas[1];
	float monto_transferencia = 20000.0;
	if (cuenta_origen->saldo >= monto_transferencia) {
		cuenta_origen->saldo -= monto_transferencia;
		cuenta_destino->saldo += monto_transferencia;
		printf("Transferencia de %f realizada.\n", monto_transferencia);
	} else {
		printf("Fondos insuficientes.\n");
	}
}

void prueba_verificacion_saldo() {
	printf("\n=== Prueba de Verificacion de Saldo ===\n");
	struct Cuenta *cuenta = &banco.sucursales[0].cuentas[0];
	printf("Saldo actual: %f\n", cuenta->saldo);
}

void prueba_estado_cuenta_ahorros() {
	printf("\n=== Prueba de Estado de Cuenta de Ahorros ===\n");
	struct Cuenta *cuenta = &banco.sucursales[0].cuentas[1];
	printf("La cuenta de ahorros esta %s.\n", (cuenta->estado == 1) ? "activa" : "inactiva");
}

void prueba_limite_cuenta_vista() {
	printf("\n=== Prueba de Limite de Cuenta Vista ===\n");
	struct Cuenta *cuenta = &banco.sucursales[0].cuentas[2];
	printf("El saldo esta %s del limite.\n", (cuenta->saldo > 2500000) ? "fuera" : "dentro");
}

void prueba_comision_mensual() {
	printf("\n=== Prueba de Calculo de Comision Mensual ===\n");
	struct Cuenta *cuenta = &banco.sucursales[0].cuentas[0];
	cuenta->saldo -= cuenta->comision;
	printf("Comision de %f descontada. Nuevo saldo: %.f\n", cuenta->comision, cuenta->saldo);
}

void prueba_interes_cuenta() {
	printf("\n=== Prueba de Calculo de Interes ===\n");
	struct Cuenta *cuenta = &banco.sucursales[0].cuentas[0];
	calcular_interes_y_comision(cuenta);
	cuenta->saldo += cuenta->interes;
	printf("Interes de %f generado. Nuevo saldo: %f\n", cuenta->interes, cuenta->saldo);
}

void ejecutar_baterias() {
	printf("\n=== Ejecutando Baterias de Prueba ===\n");
	prueba_creacion_cuenta();
	prueba_retiro_cuenta();
	prueba_deposito_cuenta();
	prueba_transferencia_cuenta();
	prueba_verificacion_saldo();
	prueba_estado_cuenta_ahorros();
	prueba_limite_cuenta_vista();
	prueba_comision_mensual();
	prueba_interes_cuenta();
}

/* ======== MENÚ PRINCIPAL ======== */

int main() {
	inicializar_banco();
	agregar_datos_prueba();

	int opcion = -1;

	while (opcion != 0) {
		printf("\n===========================================\n");
		printf("             BIENVENIDO/A AL               \n");
		printf("             BANCO TUSUNAMI                \n");
		printf("===========================================\n");
		printf("  1. Clientes y Cuentas                   \n");
		printf("  2. Operaciones con cuentas              \n");
		printf("  3. Generar extracto mensual             \n");
		printf("  4. Ejecutar baterias de prueba          \n");
		printf("  0. Salir                                \n");
		printf("===========================================\n");
		printf("  Ingrese su opcion: ");
		scanf("%d", &opcion);

		if (opcion == 1) {
			int sub_opcion = -1;
			while (sub_opcion != 0) {
				printf("\n========== CLIENTES Y CUENTAS ==========\n");
				printf("1. Ver lista de clientes\n");
				printf("2. Ver lista de cuentas\n");
				printf("3. Crear cuenta\n");
				printf("0. Volver al menu principal\n");
				printf("=============================================\n");
				printf("Ingrese su opcion: ");
				scanf("%d", &sub_opcion);

				if (sub_opcion == 1) {
					mostrar_clientes();
				} else if (sub_opcion == 2) {
					mostrar_cuentas();
				} else if (sub_opcion == 3) {
					crear_cuenta();
				} else if (sub_opcion == 0) {
					printf("Volviendo al menu principal...\n");
				} else {
					printf("Opcion no valida. Intente nuevamente.\n");
				}
			}
		} else if (opcion == 2) {
			int sub_opcion = -1;
			while (sub_opcion != 0) {
				printf("\n========== OPERACIONES CON CUENTAS ==========\n");
				printf("1. Retirar dinero\n");
				printf("2. Depositar dinero\n");
				printf("3. Transferir dinero\n");
				printf("0. Volver al menu principal\n");
				printf("=============================================\n");
				printf("Ingrese su opcion: ");
				scanf("%d", &sub_opcion);

				if (sub_opcion == 1) {
					retirar_dinero();
				} else if (sub_opcion == 2) {
					depositar_dinero();
				} else if (sub_opcion == 3) {
					transferir_dinero();
				} else if (sub_opcion == 0) {
					printf("Volviendo al menu principal...\n");
				} else {
					printf("Opcion no valida. Intente nuevamente.\n");
				}
			}
		} else if (opcion == 3) {
			int sub_opcion = -1;
			while (sub_opcion != 0) {
				printf("\n========== OPERACIONES CON CUENTAS ==========\n");
				printf("1. Extracto mensual\n");
				printf("2. Mostrar saldo proximos meses\n");
				printf("0. Volver al menu principal\n");
				printf("=============================================\n");
				printf("Ingrese su opcion: ");
				scanf("%d", &sub_opcion);

				if (sub_opcion == 1) {
					extracto_mensual();
				} else if (sub_opcion == 2) {
					mostrar_saldo_proximos_meses();
				} else if (sub_opcion == 0) {
					printf("Volviendo al menu principal...\n");
				} else {
					printf("Opcion no valida. Intente nuevamente.\n");
				}
			}
		} else if (opcion == 4) {
			ejecutar_baterias();
		} else if (opcion == 0) {
			printf("Saliendo...\n");
		} else {
			printf("\nOpcion no valida. Intente nuevamente.\n");
		}
	}

	return 0;
}
