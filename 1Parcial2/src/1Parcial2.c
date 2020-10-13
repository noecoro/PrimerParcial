/*
 Un diario requiere un sistema de publicación de avisos clasificados, el mismo deberá tener un
registro de CLIENTES y de avisos publicados.(PUBLICIDAD)
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "utn.h"
#include "Cliente.h"
#include "Publicidad.h"

#define CLIENTES_CANT 100
#define PUBLICIDADES_CANT 1000

int main(void) {
	setbuf(stdout,NULL);
	Cliente arrayClientes[CLIENTES_CANT];
	Publicidad arrayPublicidades[PUBLICIDADES_CANT];

	int idClientes=0;
	int idPublicidades=0;

	int opcion;

	int auxIndice;
	int auxId;

	int auxIdPublicidad;
	int auxIndicePublicidad;

	int respuesta;
	//int auxRubro;


	if(cli_inicializar(arrayClientes,CLIENTES_CANT) == 0)
	{
		printf("Array de Clientes inicializado correctamente. \n");
	}

	if(publi_inicializar(arrayPublicidades,PUBLICIDADES_CANT) == 0)
	{
		printf("Array de Publicidades inicializado correctamente. \n");
	}


	cli_altaForzada(arrayClientes,CLIENTES_CANT,0,&idClientes,"Sol","Diaz", "20349474982\n");
	cli_altaForzada(arrayClientes,CLIENTES_CANT,1,&idClientes,"Tam","Klug", "20368742917\n");
	cli_altaForzada(arrayClientes,CLIENTES_CANT,2,&idClientes,"Eri","Jara", "30397022957\n");

	publi_altaForzada(arrayPublicidades,PUBLICIDADES_CANT,0,&idPublicidades,2,"Clavel",1,0);
	publi_altaForzada(arrayPublicidades,PUBLICIDADES_CANT,1,&idPublicidades,1,"Rosas",1,0);
	publi_altaForzada(arrayPublicidades,PUBLICIDADES_CANT,2,&idPublicidades,1,"Estati",1,1);
	publi_altaForzada(arrayPublicidades,PUBLICIDADES_CANT,3,&idPublicidades,0,"Calas",4,1);
	publi_altaForzada(arrayPublicidades,PUBLICIDADES_CANT,4,&idPublicidades,0,"Fresia",2,1);
	publi_altaForzada(arrayPublicidades,PUBLICIDADES_CANT,5,&idPublicidades,2,"Nardo",10,1);

	do
	{
		if(!utn_getNumero(	&opcion,
									"\n1.Alta cliente"
									"\n2.Modificar datos del cliente"
									"\n3.Baja cliente"
									"\n4.Publicar (alta de publicidad)"
									"\n5.Pausar publicacion"//llegue hasta el 5
									"\n6.Reanudar publicacion(pasa a ser imprimir hardcodeo d publicidades)"//hasta aca funciona
									"\n7.Imprimir clientes"
									"\n8.Salir\n",
									//"\n8.Informar"
									//"\n9.Salir\n\n",
									"\nError opcion invalida",1,8,2) )
		{
			switch(opcion)
			{
			case 1:
				auxIndice = cli_getEmptyIndex(arrayClientes,CLIENTES_CANT);

				if(auxIndice >= 0)
				{
					if(cli_alta(arrayClientes,CLIENTES_CANT,auxIndice,&idClientes) == 0)
					{
						printf("\nCarga exitosa, ID: %d\n", idClientes);
					}
				}
				else
				{
					printf("\nNo hay lugar disponible");
				}
				break;
			case 2:
				cli_imprimir(arrayClientes,CLIENTES_CANT);
				if(utn_getNumero(&auxId,"\nIngrese ID del cliente que desea modificar: \n","\nID invalido",0,idClientes,0) == 0)//idClientes por q es hasta mil segun yo
				{
					auxIndice = cli_buscarId(arrayClientes,CLIENTES_CANT,auxId);
					if(	auxIndice >= 0 &&
						cli_modificar(arrayClientes,CLIENTES_CANT,auxIndice) == 0)
					{
						printf("\nModificacion exitosa\n");
					}
					else
					{
						printf("ID inválido\n");
					}
				}
				break;
			case 3:
				cli_imprimir(arrayClientes,CLIENTES_CANT);
				if(utn_getNumero(&auxId,"\n\nIngrese ID del cliente que desea eliminar: \n","\nID invalido",0,10000,0)==0)
				{
					auxIndice = cli_buscarId(arrayClientes,CLIENTES_CANT,auxId);
					if(	auxIndice >= 0 &&
						!utn_getNumero(&respuesta, "¿Confirma la eliminacion del cliente? de ser si ingrese el nro 1: \n", "Opción inválida\n", 1, 1, 0))

					{
						printf("\nBaja exitosa\n");
					}
					else
					{
						printf("\nId inválido\n");
					}
				}
				break;
			case 4:
				auxIndicePublicidad = publi_getEmptyIndex(arrayPublicidades,PUBLICIDADES_CANT);
				if(auxIndicePublicidad >= 0)
				{
					cli_imprimir(arrayClientes,CLIENTES_CANT);
					if(	utn_getNumero(&auxId,"\nIngrese el Id del Cliente que va a contratar la publicidad: ","\nError",0,10000,2) == 0 &&
						cli_buscarId(arrayClientes,CLIENTES_CANT,auxId) != -1)
					{
						publi_alta(arrayPublicidades,PUBLICIDADES_CANT,auxIndicePublicidad,&idPublicidades,auxId);
						printf("La publicidad ha sido contratada, se le asigno el  ID : %d", idPublicidades -1);//agrego -1 p descontar
					}
					else
					{
						printf("\nEl ID ingresado no exite \n");
					}
				}
				break;

			case 5://creo una func q pausa
				publi_imprimir(arrayPublicidades,PUBLICIDADES_CANT);
				if(!utn_getNumero(&auxIdPublicidad, "\n\nIngrese ID de la publicación que desea pausar\n", "\n inválido\n", 0, 10000, 1) &&
					publi_buscarId(arrayPublicidades,PUBLICIDADES_CANT, auxIdPublicidad) != -1)
				{
						respuesta = publi_buscarIdCliente(arrayPublicidades,PUBLICIDADES_CANT, auxIdPublicidad);

						cli_imprimirSimple(&arrayClientes[respuesta]);
						auxIndicePublicidad= publi_buscarId(arrayPublicidades,PUBLICIDADES_CANT, auxIdPublicidad );
						if(arrayPublicidades[auxIndicePublicidad].estado == 1 &&
								auxIndicePublicidad>=0 &&
							!publi_pausar(arrayPublicidades,PUBLICIDADES_CANT, auxIndicePublicidad))
						{
							printf("\n\nLa publicidad seleccionada ha sido pausada\n");
							publi_imprimirSimple(&arrayPublicidades[auxIndicePublicidad]);
						}else
						{
							printf("\n\nLa publicación seleccionada ya se encontraba pausada\n");
						}
				}
				else
				{
					printf("\nEl Id no corresponde a una publicación\n");
				}
				break;
			case 6://MUESTRA LO HARDCODEADO
				publi_imprimir(arrayPublicidades,PUBLICIDADES_CANT);
								break;
			case 7:

				cli_imprimir(arrayClientes,CLIENTES_CANT);
						break;
					}

		}
	}while(opcion != 8);

	return EXIT_SUCCESS;
}
