#ifndef NODO_AB_H
#define NODO_AB_H

#include <stdbool.h>
#include <stdlib.h>
#include "abb.h"

struct nodo_ab;
typedef struct nodo_ab nodo_ab_t;

// Crea el nodo con la clave y el dato correspondiente.
// En caso de no poder crearlo devuelve NULL.
// El nodo izquierdo y derecho apuntan a NULL.
// Post: se creo el nodo del hash.
nodo_ab_t* nodo_ab_crear(const char* clave, void* dato);

// Devuele la clave del nodo.
// Pre: el nodo fue creado.
// Post: se devolvio la clave del nodo.
const char* nodo_ab_obtener_clave(nodo_ab_t * nodo);

// Devuele el valor del nodo.
// Pre: el nodo fue creado.
// Post: se devolvio el valor del nodo.
void* nodo_ab_obtener_valor(nodo_ab_t * nodo);

// Cambia el valor del nodo y destruye el dato anterior
// si se pasa destruir_dato como parametro.
// Pre: el nodo fue creado.
// Post: se cambio el valor del nodo y se destruyo el anterior.
void nodo_ab_cambiar_valor(nodo_ab_t * nodo, void * dato, abb_destruir_dato_t destruir_dato);

// Cambia la clave del nodo. Devuelve verdadero o falso
// si pudo cambiar la clave o no. Si no pudo cambiarla
// deja el nodo como estaba.
// Pre: el nodo fue creado.
// Post: se cambio la clave del nodo.
bool nodo_ab_cambiar_clave(nodo_ab_t * nodo, const char *clave);

// Apunta el nodo izquierdo de nodo1 a nodo2.
// Pre: nodo1 y nodo2 fueron creados.
// Post: se apunto el nodo izquierdo de nodo1 a nodo2.
void nodo_ab_apuntar_izq(nodo_ab_t * nodo1, nodo_ab_t * nodo2);

// Apunta el nodo derecho de nodo1 a nodo2.
// Pre: nodo1 y nodo2 fueron creados.
// Post: se apunto el nodo derecho de nodo1 a nodo2.
void nodo_ab_apuntar_der(nodo_ab_t * nodo1, nodo_ab_t * nodo2);

// Devuelve el nodo izquierdo de nodo.
// Pre: el nodo fue creado.
// Post: se devolvio el nodo izquierdo de nodo.
nodo_ab_t* nodo_ab_obtener_izq(nodo_ab_t * nodo);

// Devuelve el nodo derecho de nodo.
// Pre: el nodo fue creado.
// Post: se devolvio el nodo derecho de nodo.
nodo_ab_t* nodo_ab_obtener_der(nodo_ab_t * nodo);

// Borra el nodo y devuele el dato almacenado en el mismo.
// Pre: el nodo fue creado.
// Post: se borro el nodo.
void* nodo_ab_borrar(nodo_ab_t * nodo);

// Destruye el nodo. Si la funcion destruir_dato es pasada
// por parametro aplica dicha funcion al dato almacenado en el nodo.
// Pre: el nodo fue creado.
// Post: se destruyo el nodo.
void nodo_ab_destruir(nodo_ab_t * nodo, abb_destruir_dato_t destruir_dato);

#endif
