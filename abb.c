#include "abb.h"
#include "nodo_ab.h"
#include <stdio.h>

#define CANTIDAD_INICIAL 0
#define PRIMERA_MENOR   <0
#define SEGUNDA_MENOR   >0
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
// bool guardar_aux(nodo_ab_t*, nodo_ab_t*, abb_comparar_clave_t, abb_destruir_dato_t);
nodo_ab_t* buscar_nodo(nodo_ab_t*, const char*, abb_comparar_clave_t);
nodo_ab_t* buscar_nodo_padre(nodo_ab_t*, nodo_ab_t*, const char*, abb_comparar_clave_t, pos_nodo*, bool*);
nodo_ab_t* obtener_ultimo(nodo_ab_t* nodo, pos_nodo pos);
bool intercambiar_nodos(nodo_ab_t* nodo1, nodo_ab_t* nodo2);
void *abb_borrar_aux(nodo_ab_t * nodo_raiz, const char *clave, abb_comparar_clave_t comparar_claves, size_t*);

/*************************************************************************
                              Primitivas
*************************************************************************/
abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato){
  if(!cmp)
    return NULL;

  abb_t* arbol = malloc(sizeof(abb_t));
  if(!arbol)
    return NULL;

  arbol->comparar_claves  = cmp;
  arbol->destruir_dato    = destruir_dato;
  arbol->cantidad         = CANTIDAD_INICIAL;
  arbol->raiz             = NULL;
  return arbol;
}

bool abb_guardar(abb_t *arbol, const char *clave, void *dato){
  pos_nodo pos;
  bool existe_hijo;
  nodo_ab_t* nodo_padre = buscar_nodo_padre(arbol->raiz, NULL, clave, arbol->comparar_claves, &pos, &existe_hijo);

  if(existe_hijo){    // La clave esta en el arbol
    nodo_ab_cambiar_valor(nodo_ab_obtener(nodo_padre, pos), dato, arbol->destruir_dato);
  }else{              // se necesita crear un nuevo nodo
    nodo_ab_t* nuevo_nodo = nodo_ab_crear(clave, dato);
    if(!nuevo_nodo)
      return false;

    if(nodo_padre){   // el nuevo nodo tiene un padre
      nodo_ab_apuntar(nodo_padre, nuevo_nodo, pos);
    }else{            // el nuevo nodo tiene que ser raiz
      arbol->raiz = nuevo_nodo;
    }
    arbol->cantidad++;
  }
  return true;
}

bool abb_pertenece(const abb_t *arbol, const char *clave){
  return buscar_nodo(arbol->raiz, clave, arbol->comparar_claves);
}

size_t abb_cantidad(abb_t *arbol){
  return arbol->cantidad;
}

void *abb_borrar(abb_t *arbol, const char *clave){
  if(!arbol->raiz)
    return NULL;

  if(arbol->comparar_claves(clave, nodo_ab_obtener_clave(arbol->raiz)) == IGUALES){ // el nodo a borrar es la raiz
    if(nodo_ab_es_hoja(arbol->raiz)){ // es una hoja
      void* dato = nodo_ab_borrar(arbol->raiz);
      arbol->raiz = NULL;
      arbol->cantidad--;
      return dato;
    }

    pos_nodo pos_hijo;
    if(nodo_ab_tiene_un_hijo(arbol->raiz, &pos_hijo)){ // tiene un solo hijo
      nodo_ab_t* nodo_raiz = arbol->raiz;
      arbol->raiz = nodo_ab_obtener(arbol->raiz, pos_hijo);
      arbol->cantidad--;
      return nodo_ab_borrar(nodo_raiz);
    }

    nodo_ab_t* ultimo_nodo = obtener_ultimo(nodo_ab_obtener_izq(arbol->raiz), der); // tiene dos hijos
    if(!intercambiar_nodos(arbol->raiz, ultimo_nodo))
      return NULL;

    return abb_borrar_aux(nodo_ab_obtener_izq(arbol->raiz), clave, arbol->comparar_claves, &arbol->cantidad);
  }
  return abb_borrar_aux(arbol->raiz, clave, arbol->comparar_claves, &(arbol->cantidad));
}


/*************************************************************************
                            Funciones Auxiliares
*************************************************************************/
void *abb_borrar_aux(nodo_ab_t * nodo_raiz, const char *clave, abb_comparar_clave_t comparar_claves, size_t* cantidad){
  pos_nodo pos_hijo;
  bool existe;
  nodo_ab_t* nodo_padre = buscar_nodo_padre(nodo_raiz, NULL, clave, comparar_claves, &pos_hijo, &existe);
  if(!existe) // No existe el nodo a borrar
    return NULL;

  nodo_ab_t* nodo_hijo = nodo_ab_obtener(nodo_padre, pos_hijo);

  if(nodo_ab_es_hoja(nodo_hijo)){ // el nodo a borrar es una hoja
    nodo_ab_apuntar(nodo_padre, NULL, pos_hijo);
    (*cantidad)--;
    return nodo_ab_borrar(nodo_hijo);
  }

  pos_nodo pos_hijo_del_hijo;
  if(nodo_ab_tiene_un_hijo(nodo_hijo, &pos_hijo_del_hijo)){ // el nodo a borrar tiene un solo hijo
    nodo_ab_apuntar(nodo_padre, nodo_ab_obtener(nodo_hijo, pos_hijo_del_hijo), pos_hijo);
    (*cantidad)--;
    return nodo_ab_borrar(nodo_hijo);
  }

  nodo_ab_t* ultimo_nodo = obtener_ultimo(nodo_ab_obtener_izq(nodo_hijo), der); // el nodo a borrar tiene dos hijos
  if(!intercambiar_nodos(nodo_hijo, ultimo_nodo))
    return NULL;

  return abb_borrar_aux(nodo_ab_obtener_izq(nodo_hijo), clave, comparar_claves, cantidad);
}

nodo_ab_t* buscar_nodo(nodo_ab_t* nodo, const char* clave, abb_comparar_clave_t comparar_claves){
  if(!nodo)
    return NULL;

  int resultado = comparar_claves(clave, nodo_ab_obtener_clave(nodo));
  if(resultado == IGUALES)
    return nodo;

  if(resultado PRIMERA_MENOR)
    return buscar_nodo(nodo_ab_obtener_izq(nodo), clave, comparar_claves);

  return buscar_nodo(nodo_ab_obtener_der(nodo), clave, comparar_claves);
}

nodo_ab_t* buscar_nodo_padre(nodo_ab_t* nodo, nodo_ab_t* nodo_padre, const char* clave, abb_comparar_clave_t comparar_claves, pos_nodo* pos, bool* existe){
  if(!nodo){
    *existe = false;
    return nodo_padre;
  }

  int resultado = comparar_claves(clave, nodo_ab_obtener_clave(nodo));
  if(resultado == IGUALES){
    *existe = true;
    return nodo_padre;
  }

  if(resultado PRIMERA_MENOR){
    *pos = izq;
    return buscar_nodo_padre(nodo_ab_obtener_izq(nodo), nodo, clave, comparar_claves, pos, existe);
  }

  *pos = der;
  return buscar_nodo_padre(nodo_ab_obtener_der(nodo), nodo, clave, comparar_claves, pos, existe);
}

nodo_ab_t* obtener_ultimo(nodo_ab_t* nodo, pos_nodo pos){
  while (!nodo_ab_es_hoja(nodo))
    nodo = nodo_ab_obtener(nodo, pos);
  return nodo;
}

bool intercambiar_nodos(nodo_ab_t* nodo1, nodo_ab_t* nodo2){
  const char* clave1 = nodo_ab_obtener_clave(nodo1);
  void* dato1  = nodo_ab_obtener_valor(nodo1);
  if(!nodo_ab_cambiar_clave(nodo1, nodo_ab_obtener_clave(nodo2)))
    return false;
  if(!nodo_ab_cambiar_clave(nodo2, clave1))
    return false;
  nodo_ab_cambiar_valor(nodo1, nodo_ab_obtener_valor(nodo2), NULL);
  nodo_ab_cambiar_valor(nodo2, dato1, NULL);
  return true;
}
