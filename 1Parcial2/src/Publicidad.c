#include "Publicidad.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "utn.h"

// const refiere a var q no se va a poder escribir, 2= 2 tipos(pausado y activo) 8 tamaño max q puede tener c/ elemento contando un lugar p/ \0
static const char TXT_ESTADO[2][8]={"PAUSADO","ACTIVO"};//se puede pedir en onformes.c

/**
 * \brief Imprime los datos de una publicidad
 * \param pElemento Puntero a la publicidad que se busca imprimir
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 *
 */
int publi_imprimirSimple(Publicidad* pElemento)
{
	int retorno = -1;
	if(pElemento != NULL && pElemento->isEmpty == 0)
	{
		retorno=0;
		//printf("ID  TEXTO  RUBRO   ID CLIENTE  ESTADO\n");
		printf("\nID: %d - TEXTO: %s - RUBRO: %d - IDCLIENTE: %d - ESTADO: %s"
												,pElemento->idPublicidad
												,pElemento->textoDePublicidad
												,pElemento->rubro
												,pElemento->idCliente
												,TXT_ESTADO[pElemento->estado]);//chequear TXT
	}
	return retorno;
}
//===================================================================================
/**
 * \brief Imprime el array de publicidad
 * \param pArray Array de publicidad a ser impreso
 * \param limite Limite del array de publicidades
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 *
 */
int publi_imprimir(Publicidad* pArray, int limite)
{
	int respuesta = -1;

	if(pArray != NULL && limite > 0)
	{
		respuesta = 0;
		for(int i=0; i<limite; i++)
		{
			 publi_imprimirSimple(&pArray[i]);
		}
	}
	return respuesta;
}
//===================================================================================
/**
 * \brief Inicializa el array
 * \param pArray Array de publicidades a ser inicializadas
 * \param limite Limite del array de publicidad
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 *
 */
int publi_inicializar(Publicidad* pArray,int limite)
{
	int respuesta = -1;

	if(pArray != NULL && limite > 0)
	{
		respuesta = 0;
		for(int i=0; i<limite; i++)
		{
			pArray[i].isEmpty = 1;
			pArray[i].estado = 3;
			pArray[i].rubro = 0;
		}
	}
	return respuesta;
}
//===================================================================================
/**
 * \brief Da de alta un publicidad en una posicion del array
 * \param pArray Array de publicaciones a ser actualizado
 * \param limite Limite del array de publicaciones
 * \param indice Posicion a ser actualizada
 * \param id Identificador a ser asignado al cliente
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 *
 */
int publi_alta(Publicidad* pArray,int limite, int indice, int* idPublicidad, int idCliente)//ya recibe un dato del cliente ademas del propio ID  en este caso
{
	int respuesta = -1;
	Publicidad auxBuffer;

	if(pArray != NULL && limite > 0 && indice < limite && indice >= 0 && idPublicidad != NULL)
	{
		if(	!utn_getNumero(&auxBuffer.rubro,"\n Ingrese Rubro (1 a 1000) ", "\nError",1,1000,2) &&
			!utn_getDescripcion(auxBuffer.textoDePublicidad,PUBLITEXTO,"\nIngrese texto de publicación\n ", "\nError",2))
		{
			auxBuffer.textoDePublicidad[0] = toupper(auxBuffer.textoDePublicidad[0]);
			respuesta = 0;
			auxBuffer.idCliente = idCliente;
			auxBuffer.idPublicidad= *idPublicidad;
			auxBuffer.isEmpty = 0;
			auxBuffer.estado = 1;
			pArray[indice] = auxBuffer;
			(*idPublicidad)++;
		}
	}
	return respuesta;
}
//===================================================================================
/**
 * \brief Da  alta un publicidad en una posicion del array de manera forzada
 * \param pArray Array de publicaciones a ser actualizado
 * \param limite Limite del array de publicaciones
 * \param indice Posicion a ser actualizada
 * \param idPublicidad Identificador a ser asignado al cliente
 * \param idCliente Identificador cliente
 * \param textoDePublicidad Texto que se asignará a la publicacion
 * \param estado  Estado a asignar a la publicidad
 * \param rubro Rubro a asignar a la publicacion
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 *
 */
int publi_altaForzada(Publicidad* pArray,int limite, int indice, int* idPublicidad, int idCliente,char* textoDePublicidad,int rubro,int estado)
{
	int respuesta = -1;
	Publicidad bufferPublicidad;

	if(pArray != NULL && limite > 0 && indice < limite && indice >= 0 && idPublicidad!= NULL)
	{
		strncpy(bufferPublicidad.textoDePublicidad,textoDePublicidad,PUBLITEXTO);
		bufferPublicidad.idCliente = idCliente;//la conexion d las 2 entidades
		bufferPublicidad.rubro = rubro;
		respuesta = 0;
		bufferPublicidad.idPublicidad= *idPublicidad;
		bufferPublicidad.isEmpty = 0;
		pArray[indice] = bufferPublicidad;
		(*idPublicidad)++;

	}
	return respuesta;
}

//===================================================================================


/** \brief Busca un ID en un array y devuelve la posicion en que se encuentra
* \param pArray Array de publicidades
* \param limite int Tamaño del array
* \param valorBuscado ID a encontrar
* \return int Return (-1) si no encuentra el valor buscado sino, devuelve el indice donde se encuentra el valor buscado
*
*/
int publi_buscarId(Publicidad* pArray, int limite, int valorBuscado)
{
	int respuesta = -1;

	if(pArray != NULL && limite > 0 && valorBuscado >= 0)
	{
		for(int i=0; i<limite; i++)
		{
			if(pArray[i].isEmpty == 0 && pArray[i].idPublicidad == valorBuscado)//id buscado
			{
				respuesta = i;
				break;
			}
		}
	}
	return respuesta;
}
//===================================================================================
/**
 * \brief Buscar primer posicion vacia
 * \param pArray Array de publicidads
 * \param limite Limite del array de publicaciones
 * \return Retorna el indice de la posicion vacia o -1 (ERROR)
 *
 */
int publi_getEmptyIndex(Publicidad* pArray,int limite)
{
	int respuesta = -1;

	if(pArray != NULL && limite > 0)
	{
		for(int i=0; i<limite ;i++)
		{
			if(pArray[i].isEmpty == 1)
			{
				respuesta = i;
				break;
			}
		}
	}
	return respuesta;
}
//===================================================================================

/** \brief Busca un ID en un array y devuelve el ID del cliente
* \param pArray Array de publicidades
* \param limite int Tamaño del array
* \param idpublicidad ID a encontrar
* \return int Return (-1) si no encuentra el valor buscado sino, devuelve el ID del cliente
*
*/
int publi_buscarIdCliente(Publicidad* pArray, int limite, int idPublicidadBuscada)
{//agrego un dato idCliente de la entidad cliente en una func de publicidad
	int respuesta = -1;
	int i;
	if(pArray!= NULL && limite > 0 && idPublicidadBuscada >= 0)
	{
		for(i=0; i<limite; i++)
		{
			if(pArray[i].isEmpty == 0 && pArray[i].idPublicidad == idPublicidadBuscada)
			{
				respuesta = pArray[idPublicidadBuscada].idCliente;//dato q une las 2 entidades
				break;
			}
		}
	}
	return respuesta;
}

//===================================================================================
/*brief Pausa una publicidad
 * \param pArray array de publicidades para actualizar
 * \param limite limite del array de las publicidades
 * \param indice la posicion que va a ser pausada
 * \return 0 exito 1 error
 */

int publi_pausar(Publicidad* pArray,int limite, int indice)
{
	int respuesta = -1;
	int estado;
	if(pArray!= NULL && limite > 0 && indice >= 0)
	{
		if( !utn_getNumero(&estado,"¿Esta seguro de pausar la publicidad que selecciono? Ingrese 1 para confirmar\n"
				,"La publicidad que selecciono no fue pausada\n",1,1,0))
		{
			respuesta = 0;
			pArray[indice].estado = 0;//0=PAUSADO
		}
	}

return respuesta;
}



