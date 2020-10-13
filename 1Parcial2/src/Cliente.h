
#ifndef CLIENTE_H_
#define CLIENTE_H_

#define NOMBRE 50 // SIEMPRE REFERENCIA A TAMAÑO
#define APELLIDO 50
#define CUIT 12 // sin guiones y un lugar mas para \n

typedef struct{
	char nombre[NOMBRE];
	char apellido[APELLIDO];
	char cuit[CUIT];
	int isEmpty;
	int idCliente;

}Cliente;
//para abm

int cli_imprimirSimple(Cliente* pAuxBuffer);
int cli_inicializar(Cliente* pArray,int limite);
int cli_getEmptyIndex(Cliente* pArray,int limite);
int cli_alta(Cliente* array,int limite, int indice, int* id);

int cli_imprimir(Cliente* pArray,int limite);
int cli_buscarId(Cliente* pArray, int limite, int valorBuscado);
int cli_modificar(Cliente* pArray,int limite, int indice);


int cli_altaForzada(Cliente* pArray,int limite, int indice, int* idCliente,char* nombre,char* apellido, char* cuit);


#endif /* CLIENTE_H_ */
