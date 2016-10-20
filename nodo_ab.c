#include "nodo_ab.h"
#include <string.h>
#include <stdio.h>

typedef struct nodo_ab{
  char * clave;
  void * valor;
  struct nodo_ab * izq;
  struct nodo_ab * der;
}nodo_ab_t;

nodo_ab_t* nodo_ab_crear(const char* clave, void* dato){
  nodo_ab_t* nodo = malloc(sizeof(nodo_ab_t));
  if(!nodo)
    return NULL;

  nodo->clave = malloc(sizeof(char)*(strlen(clave)+1));
  if(nodo->clave == NULL){
    free(nodo);
    return NULL;
  }

  nodo->valor = dato;
  nodo->izq = NULL;
  nodo->der = NULL;

  strcpy(nodo->clave, clave);
  return nodo;
}

const char* nodo_ab_obtener_clave(nodo_ab_t * nodo){
  return nodo->clave;
}

void* nodo_ab_obtener_valor(nodo_ab_t * nodo){
  return nodo->valor;
}

void nodo_ab_cambiar_valor(nodo_ab_t * nodo, void * dato, abb_destruir_dato_t destruir_dato){
  if(destruir_dato)
    destruir_dato(nodo->valor);
  nodo->valor = dato;
}

bool nodo_ab_cambiar_clave(nodo_ab_t * nodo, const char *clave){
  char* nueva_clave = realloc(nodo->clave, sizeof(char)*(strlen(clave)+1));
  if(nueva_clave == NULL)
    return false;

  nodo->clave = nueva_clave;
  strcpy(nodo->clave, clave);
  return true;
}

void nodo_ab_apuntar_izq(nodo_ab_t * nodo1, nodo_ab_t * nodo2){
  nodo1->izq = nodo2;
}

void nodo_ab_apuntar_der(nodo_ab_t * nodo1, nodo_ab_t * nodo2){
  nodo1->der = nodo2;
}

nodo_ab_t* nodo_ab_obtener_izq(nodo_ab_t * nodo){
  return nodo->izq;
}

nodo_ab_t* nodo_ab_obtener_der(nodo_ab_t * nodo){
  return nodo->der;
}

void* nodo_ab_borrar(nodo_ab_t * nodo){
  void* dato  = nodo->valor;
  free(nodo->clave);
  free(nodo);
  return dato;
}

void nodo_ab_destruir(nodo_ab_t * nodo, abb_destruir_dato_t destruir_dato){
  if(destruir_dato)
    destruir_dato(nodo->valor);
  free(nodo->clave);
  free(nodo);
}
