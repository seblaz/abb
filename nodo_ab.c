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

void nodo_ab_apuntar(nodo_ab_t * nodo1, nodo_ab_t * nodo2, pos_nodo pos){
  if(pos == izq){
    nodo_ab_apuntar_izq(nodo1, nodo2);
  }else{
    nodo_ab_apuntar_der(nodo1, nodo2);
  }
}

nodo_ab_t* nodo_ab_obtener_izq(nodo_ab_t * nodo){
  return nodo->izq;
}

nodo_ab_t* nodo_ab_obtener_der(nodo_ab_t * nodo){
  return nodo->der;
}

nodo_ab_t* nodo_ab_obtener(nodo_ab_t * nodo, pos_nodo pos){
  if(pos == izq)
    return nodo_ab_obtener_izq(nodo);
  return nodo_ab_obtener_der(nodo);
}

nodo_ab_t** nodo_ab_obtener_puntero_izq(nodo_ab_t * nodo){
  return &nodo->izq;
}

nodo_ab_t** nodo_ab_obtener_puntero_der(nodo_ab_t * nodo){
  return &nodo->der;
}

bool nodo_ab_es_hoja(nodo_ab_t * nodo){
  return !nodo->izq && !nodo->der;
}

bool nodo_ab_tiene_un_hijo(nodo_ab_t * nodo, pos_nodo* pos){
  if(nodo->izq)
    *pos = izq;

  if(nodo->der)
    *pos = der;

  return !(nodo->izq && nodo->der) && !nodo_ab_es_hoja(nodo);
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

void nodo_var_dump(nodo_ab_t* nodo, int cant_tabs){
  if(!nodo)
    return;

  for (int i = 0; i < cant_tabs; i++)
    printf("\t");

  printf("|clave: [%s]|\n", nodo_ab_obtener_clave(nodo));

  for (int i = 0; i < cant_tabs; i++)
    printf("\t");

  printf("|valor: [%d]|\n", *(int*)nodo_ab_obtener_valor(nodo));

  cant_tabs++;
  for (int i = 0; i < cant_tabs; i++)
    printf("\t");
  printf("%s\n", "nodo izquierdo:");
  nodo_var_dump(nodo_ab_obtener_izq(nodo), cant_tabs);

  for (int i = 0; i < cant_tabs; i++)
    printf("\t");
  printf("%s\n", "nodo derecho:");
  nodo_var_dump(nodo_ab_obtener_der(nodo), cant_tabs);
}
