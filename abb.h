#ifndef ABB_H
#define ABB_H

#include <stdbool.h>
#include <stdlib.h>

typedef struct abb abb_t;

typedef int (*abb_comparar_clave_t) (const char *, const char *);
typedef void (*abb_destruir_dato_t) (void *);

/*************************************************************************
                            Arbol Binario
*************************************************************************/

// Crea un nuevo arbol binario de busqueda y devuelve un puntero al mismo.
// Recibe cmp para comparar las claves del arbol. cmp debe devolver 0 si
// las claves son iguales, <0 si la primer clave es menor que la segunda
// y >0 si la segunda clave es menor que la primera.
// Recibe destruir_dato en caso de que sea necesario reemplazar uno de los
// datos del nodo. Si falla en la creacion devuelve NULL.
// Post: se devolvio un puntero a un nuevo arbol binario de busqueda.
abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato);

// Guarda dato bajo la clave en el arbol. Devuelve verdadero si pudo guardar
// el dato y falso en caso contrario.
// Pre: el arbol fue creado.
// Post: se guardo el dato bajo la clave en el arbol.
bool abb_guardar(abb_t *arbol, const char *clave, void *dato);

// Borra el dato guardado bajo la clave. En caso que exista la clave
// devuelve el dato, en caso contrario devuelve NULL.
// Pre: el arbol fue creado.
// Post: se borro el dato y la clave del arbol. El arbol tiene un elemento
// menos.
void *abb_borrar(abb_t *arbol, const char *clave);

void *abb_obtener(const abb_t *arbol, const char *clave);

bool abb_pertenece(const abb_t *arbol, const char *clave);

size_t abb_cantidad(abb_t *arbol);

void abb_destruir(abb_t *arbol);

/*************************************************************************
                            Iterador Interno
*************************************************************************/

void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra);

/*************************************************************************
                            Iterador Externo
*************************************************************************/

typedef struct abb_iter abb_iter_t;

abb_iter_t *abb_iter_in_crear(const abb_t *arbol);

bool abb_iter_in_avanzar(abb_iter_t *iter);

const char *abb_iter_in_ver_actual(const abb_iter_t *iter);

bool abb_iter_in_al_final(const abb_iter_t *iter);

void abb_iter_in_destruir(abb_iter_t* iter);

#endif
