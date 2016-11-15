#include "pila.h"
#include <stdlib.h>
#define CAPACIDAD_INICIAL 10
#define CANT_PILA_VACIA 0
#define REDIMENSIONAR 2

/* Definición del struct pila proporcionado por la cátedra.
 */
struct pila {
    void** datos;
    size_t cantidad;  // Cantidad de elementos almacenados.
    size_t capacidad;  // Capacidad del arreglo 'datos'.
};

/* *****************************************************************
 *                    PRIMITIVAS DE LA PILA
 * *****************************************************************/

bool redimensionar(pila_t * pila, size_t operacion_capacidad(size_t capacidad));

// Crea una pila. En caso de que no se haya podido crear la pila devuelve null.
// Post: devuelve una nueva pila vacía.
// Pre: existe el espacio en memoria para crear la pila.
pila_t* pila_crear(void){
	pila_t* nueva_pila 		= malloc(sizeof(pila_t));
	if(nueva_pila == NULL)
		return NULL;

	nueva_pila->datos 		= malloc(sizeof(void* )*CAPACIDAD_INICIAL);
	if(nueva_pila->datos == NULL){
		free(nueva_pila);
		return NULL;
	}

	nueva_pila->cantidad 	= CANT_PILA_VACIA;
	nueva_pila->capacidad = CAPACIDAD_INICIAL;
	return nueva_pila;
}

// Destruye la pila.
// Pre: la pila fue creada.
// Post: se eliminaron todos los elementos de la pila.
void pila_destruir(pila_t *pila){
    free(pila->datos);
    free(pila);
}

// Devuelve verdadero o falso, según si la pila tiene o no elementos apilados.
// Pre: la pila fue creada.
// Post: devuelve un booleano.
bool pila_esta_vacia(const pila_t *pila){
	return pila->cantidad == CANT_PILA_VACIA;
}

size_t multiplicar(size_t capacidad){
  return capacidad * REDIMENSIONAR;
}

// Agrega un nuevo elemento a la pila. Devuelve falso en caso de error.
// Pre: la pila fue creada.
// Post: se agregó un nuevo elemento a la pila, valor es el nuevo tope.
bool pila_apilar(pila_t *pila, void* valor){
	if(pila->cantidad == pila->capacidad){
    if(!redimensionar(pila, multiplicar))
      return false;
	}
	pila->datos[pila->cantidad] = valor;
	pila->cantidad++;
	return true;
}

// Obtiene el valor del tope de la pila. Si la pila tiene elementos,
// se devuelve el valor del tope. Si está vacía devuelve NULL.
// Pre: la pila fue creada.
// Post: se devolvió el valor del tope de la pila, cuando la pila no está
// vacía, NULL en caso contrario.
void* pila_ver_tope(const pila_t *pila){
	if(pila_esta_vacia(pila))
		return NULL;
	return pila->datos[pila->cantidad -1];
}

bool redimensionar(pila_t * pila, size_t operacion_capacidad(size_t capacidad)){
  void* datos_nuevo = realloc(pila->datos, operacion_capacidad(pila->capacidad) * sizeof(void *));
  if(datos_nuevo == NULL)
    return false;
  pila->datos     = datos_nuevo;
  pila->capacidad = operacion_capacidad(pila->capacidad);
  return true;
}

size_t dividir_capacidad(size_t capacidad){
  return capacidad / REDIMENSIONAR;
}

// Saca el elemento tope de la pila. Si la pila tiene elementos, se quita el
// tope de la pila, y se devuelve ese valor. Si la pila está vacía, devuelve
// NULL.
// Pre: la pila fue creada.
// Post: si la pila no estaba vacía, se devuelve el valor del tope anterior
// y la pila contiene un elemento menos.
void* pila_desapilar(pila_t *pila){
	if(pila_esta_vacia(pila))
		return NULL;
	pila->cantidad--;
	if(pila->cantidad < (pila->capacidad / REDIMENSIONAR) && pila->cantidad > CAPACIDAD_INICIAL/REDIMENSIONAR)
    redimensionar(pila, dividir_capacidad);

	return pila->datos[pila->cantidad];
}
