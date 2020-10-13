#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//PROPIAS
#include "utn.h"
#include "Cliente.h"

//===============================================================================================
/**
 * \brief Imprime los datos de un cliente
 * \param pElemento Puntero al Cliente que va a imprimir
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 *
 */
int cli_imprimirSimple(Cliente* pElemento)
{
	int retorno = -1;

	if(pElemento != NULL && pElemento->isEmpty == 0)
	{
		retorno = 0;
		//printf("ID  NOMBRE APELLLIDO CUIT\n");
		printf("\nID: %d - NOMBRE: %s - APELLIDO: %s - CUIT: %s",pElemento->idCliente
										,pElemento->nombre
										,pElemento->apellido
										, pElemento->cuit);
	}
	return retorno;
}
//===============================================================================================
/**
 * \brief Imprime el array de clientes
 * \param pArray Array de clientes para imprimir
 * \param limite Limite del array de clientes
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 *
 */
int cli_imprimir(Cliente* pArray,int limite)
{
	int respuesta = -1;

	if(pArray != NULL && limite > 0)
	{
		respuesta = 0;
		for(int i=0; i<limite; i++)
		{
			cli_imprimirSimple(&pArray[i]);
		}
	}
	return respuesta;
}
//===============================================================================================
/**
 * \brief Inicializa el array
 * \param pArray Array de clientes a ser inicializado
 * \param limite Limite del array de clientes
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 *
 */
int cli_inicializar(Cliente* pArray,int limite)
{
	int respuesta = -1;

	if(pArray != NULL && limite > 0)
	{
		respuesta = 0;
		for(int i=0;i<limite;i++)
		{
			pArray[i].isEmpty = 1;
		}
	}
	return respuesta;
}
//===============================================================================================
/**
 * \brief Da de alta a un cliente
 * \param pArray Array de clientes a ser actualizado
 * \param limite Limite del array de clientes
 * \param indice Posicion a ser actualizada
 * \param id Identificador a ser asignado al cliente
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 *
 */
int cli_alta(Cliente* pArray,int limite, int indice, int* idCliente)
{
	int respuesta = -1;
	Cliente bufferAux;

	if(pArray != NULL && limite > 0 && indice < limite && indice >= 0 && idCliente != NULL)
	{
		if(	utn_getNombre(bufferAux.nombre,NOMBRE,"\n Ingrese Nombre\n","\n Invalido\n\n",2) == 0 &&
			utn_getNombre(bufferAux.apellido,APELLIDO,"\nIngrese Apellido \n","\n Invalido \n\n",2) == 0 &&
			utn_getCuit(bufferAux.cuit, CUIT, "\nIngrese su cuit de 11 nros (sin guiones)\n", "\nValor Invalido\n", 2)==0)
		{
			//prueba de mayusculas

			bufferAux.nombre[0] = toupper(bufferAux.nombre[0]);
			bufferAux.apellido[0] = toupper(bufferAux.apellido[0]);
			//fin
			respuesta = 0;
			bufferAux.idCliente = *idCliente;
			bufferAux.isEmpty = 0;
			pArray[indice] = bufferAux;
			(*idCliente)++;
		}
	}
	return respuesta;
}
//===============================================================================================
/**
 * \brief Actualiza los datos de un cliente en una posicion del array
 * \param pArray Array de clientes a ser modificado
 * \param limite Limite del array de clientes
 * \param indice Posicion a ser actualizada
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 *
 */
int cli_modificar(Cliente* pArray,int limite, int indice)
{
	int respuesta = -1;
	Cliente auxBuffer;

	if(pArray != NULL && limite > 0 && indice < limite && indice >= 0 && pArray[indice].isEmpty == 0)
	{
		if(	utn_getNombre(auxBuffer.nombre,NOMBRE,"\nIngrese Nombre\n","\nValor Invalido \n\n",2) == 0 &&
			utn_getNombre(auxBuffer.apellido,APELLIDO,"\nIngrese Apellido?\n","\nValor Invalido \n\n",2) == 0 &&
			utn_getCuit(auxBuffer.cuit, CUIT, "\nIngrese su cuit de 11 numeros sin guiones\n", "\nValor Invalido\n", 2)==0)
		{
			respuesta = 0;
			auxBuffer.idCliente = pArray[indice].idCliente;
			auxBuffer.isEmpty = 0;
			pArray[indice] = auxBuffer;
		}
	}
	return respuesta;
}
//===============================================================================================


/** \brief Busca un ID en un array y devuelve la posicion en que se encuentra
* \param pArray cliente Array de cliente
* \param limite tamaño del array
* \param valorBuscado ID a encontrar
* \return Return (-1) si no encuentra el valor buscado sino, devuelve el indice donde se encuentra el valor buscado
*
*/
int cli_buscarId(Cliente* pArray, int limite, int valorBuscado)
{
	int respuesta = -1;

	if(pArray != NULL && limite > 0 && valorBuscado >= 0)
	{
		for(int i=0; i<limite; i++)
		{
			if(pArray[i].isEmpty == 0 && pArray[i].idCliente == valorBuscado)
			{
				respuesta = i;
				break;
			}
		}
	}
	return respuesta;
}
//===============================================================================================
/**
 * \brief Buscar primer posicion vacia
 * \param pArray Array de clientes
 * \param limite Limite del array de clientes
 * \return Retorna el indice de la posicion vacia 0 -1 (ERROR)
 *
 */
int cli_getEmptyIndex(Cliente* pArray,int limite)
{
	int respuesta = -1;

	if(pArray != NULL && limite > 0)
	{
		for(int i=0; i<limite; i++)
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

//===============================================================================================

/**
 * \brief Da de alta un cliente en una posicion del array
 * \param pArrayArray de clientes a ser actualizado
 * \param limite Limite del array de clientes
 * \param indice Posicion a ser actualizada
 * \param id Identificador a ser asignado al cliente
 * \param nombre Nombre a ser asignado al cliente
 * \param apellido Apellido a ser asignado al cliente
 * \param cuit Cuit a ser asignado al cliente
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 *
 */
int cli_altaForzada(Cliente* pArray,int limite, int indice, int* idCliente,char* nombre,char* apellido, char* cuit)

{//PARA HARDCODEO
	int respuesta = -1;
	Cliente bufferCliente;

	if(pArray != NULL && limite > 0 && indice < limite && indice >= 0 && idCliente != NULL)
	{//copio
			strncpy(bufferCliente.nombre,nombre,NOMBRE);
			strncpy(bufferCliente.apellido,apellido,APELLIDO);
			strncpy(bufferCliente.cuit,cuit,CUIT);
			respuesta = 0;
			bufferCliente.idCliente = *idCliente;
			bufferCliente.isEmpty = 0;
			pArray[indice] = bufferCliente;
			(*idCliente)++;
	}
	return respuesta;
}
