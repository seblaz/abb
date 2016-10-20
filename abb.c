#include "abb.h"
#include "nodo_ab.h"

#define CANTIDAD_INICIAL 0
#define PRIMERA_MENOR   -1
#define SEGUNDA_MENOR    1
#define IGUALES          0

/*************************************************************************
                            Estructura
*************************************************************************/
typedef struct abb{
  abb_comparar_clave_t  comparar_claves;
  abb_destruir_dato_t   destruir_dato;
  nodo_ab_t*            raiz;
  size_t                cantidad;
}abb_t;

/*************************************************************************
                            Declaracion de auxiliares
*************************************************************************/
bool pertenece_aux(nodo_ab_t* nodo, const char *clave, abb_comparar_clave_t comparar_claves);

/*************************************************************************
                              Primitivas
*************************************************************************/
abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato){
  abb_t* arbol = malloc(sizeof(abb_t));
  if(!arbol)
    return NULL;

  if(!cmp)
    return NULL;

  arbol->comparar_claves  = cmp;
  arbol->destruir_dato    = destruir_dato;
  arbol->cantidad         = CANTIDAD_INICIAL;
  arbol->raiz             = NULL;
  return arbol;
}

bool abb_guardar(abb_t *arbol, const char *clave, void *dato){
  nodo_ab_t* nodo = nodo_ab_crear(clave, dato);
  if(!nodo)
    return false;

  arbol->cantidad++;
  if(!arbol->raiz)
    arbol->raiz = nodo;

  return true;
}

bool abb_pertenece(const abb_t *arbol, const char *clave){
  return pertenece_aux(arbol->raiz, clave, arbol->comparar_claves);
}

/*************************************************************************
                            Funciones Auxiliares
*************************************************************************/
nodo_ab_t* guardar_aux(nodo_ab_t* nodo, const char *clave, abb_comparar_clave_t comparar_claves){
  switch (comparar_claves(clave, nodo_ab_obtener_clave(nodo))) {
    case IGUALES:
      break;

    case PRIMERA_MENOR:
      break;

    case SEGUNDA_MENOR:
      break;
  }
  return NULL;
}

bool pertenece_aux(nodo_ab_t* nodo, const char *clave, abb_comparar_clave_t comparar_claves){
  if(!nodo)
    return false;

  switch (comparar_claves(clave, nodo_ab_obtener_clave(nodo))) {
    case IGUALES:
      return true;

    case PRIMERA_MENOR:
      return pertenece_aux(nodo_ab_obtener_izq(nodo), clave, comparar_claves);

    case SEGUNDA_MENOR:
      return pertenece_aux(nodo_ab_obtener_der(nodo), clave, comparar_claves);

    default:
      return false; // No deberia ocurrir
  }
}
