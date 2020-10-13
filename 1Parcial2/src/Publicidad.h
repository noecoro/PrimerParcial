#ifndef PUBLICIDAD_H_
#define PUBLICIDAD_H_

#define ACTIVO 1//para estado
#define PAUSADO 0
#define PUBLITEXTO 64 // SIEMPRE REFERENCIA A TAMAÑO

typedef struct{
	int rubro;
	int estado;
	int idPublicidad;
	int isEmpty;
	int idCliente;
	char textoDePublicidad[PUBLITEXTO];
}Publicidad;

int publi_imprimirSimple(Publicidad* pElemento);
int publi_inicializar(Publicidad* pArray,int limite);
int publi_getEmptyIndex(Publicidad* pArray,int limite);
int publi_alta(Publicidad* pArray,int limite, int indice, int* idPublicidad, int idCliente);
//modificar faltaria
int publi_imprimir(Publicidad* pArray,int limite);
int publi_buscarId(Publicidad* pArray, int limite, int valorBuscado);
int publi_pausar(Publicidad* pArray,int limite, int indice);

int publi_buscarIdCliente(Publicidad* pArray, int limite, int idPublicidadBuscada);



int publi_altaForzada(Publicidad* pArray,int limite, int indice, int* idPublicidad, int idCliente,char* textoDePublicidad,int rubro,int estado);

#endif /* PUBLICIDAD_H_ */
