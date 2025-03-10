#include "abb.h"

#include "nodo_ab.h"
#include "pila.h"
#include <stdio.h>
#include <string.h>

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
void *abb_borrar_aux(nodo_ab_t * nodo_raiz, nodo_ab_t **, const char *clave, abb_comparar_clave_t comparar_claves, size_t*);
void abb_destruir_aux(nodo_ab_t* nodo, abb_destruir_dato_t destruir_dato);

nodo_ab_t* buscar_nodo_padre(nodo_ab_t*, nodo_ab_t*, const char*, abb_comparar_clave_t, pos_nodo*, bool*);
nodo_ab_t* obtener_ultimo(nodo_ab_t* nodo, pos_nodo pos);
bool intercambiar_nodos(nodo_ab_t* nodo1, nodo_ab_t* nodo2);

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
    if(!nodo_padre){  // el nodo es la raiz
      nodo_ab_cambiar_valor(arbol->raiz, dato, arbol->destruir_dato);
    }else{
      nodo_ab_cambiar_valor(nodo_ab_obtener(nodo_padre, pos), dato, arbol->destruir_dato);
    }
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

void *abb_borrar(abb_t *arbol, const char *clave){
  if(!arbol->raiz)
    return NULL;

  return abb_borrar_aux(arbol->raiz, &(arbol->raiz), clave, arbol->comparar_claves, &arbol->cantidad);
}

void *abb_obtener(const abb_t *arbol, const char *clave){
  pos_nodo pos;
  bool existe_hijo;
  nodo_ab_t* nodo_padre = buscar_nodo_padre(arbol->raiz, NULL, clave, arbol->comparar_claves, &pos, &existe_hijo);

  if(existe_hijo){ // existe el nodo
    if(nodo_padre) // el nodo no es raiz
      return nodo_ab_obtener_valor(nodo_ab_obtener(nodo_padre, pos));
    return nodo_ab_obtener_valor(arbol->raiz); // el nodo es raiz
  }
  return NULL;
}

bool abb_pertenece(const abb_t *arbol, const char *clave){
  pos_nodo pos;
  bool existe_hijo;
  buscar_nodo_padre(arbol->raiz, NULL, clave, arbol->comparar_claves, &pos, &existe_hijo);
  return existe_hijo;
}

size_t abb_cantidad(abb_t *arbol){
  return arbol->cantidad;
}

void abb_destruir(abb_t *arbol){
  if(arbol->raiz)
    abb_destruir_aux(arbol->raiz, arbol->destruir_dato);
  free(arbol);
}

/*************************************************************************
                            Funciones Auxiliares
*************************************************************************/
void *abb_borrar_aux(nodo_ab_t * nodo_raiz, nodo_ab_t ** puntero_raiz, const char *clave, abb_comparar_clave_t comparar_claves, size_t* cantidad){
  pos_nodo pos_hijo;
  bool existe;
  nodo_ab_t* nodo_padre = buscar_nodo_padre(nodo_raiz, NULL, clave, comparar_claves, &pos_hijo, &existe);

  if(!existe) // No existe el nodo a borrar
    return NULL;

  if(!nodo_padre){ // el nodo a borrar es la raiz
    pos_nodo pos_del_hijo = izq;
    if(nodo_ab_tiene_un_hijo(nodo_raiz, &pos_del_hijo) || nodo_ab_es_hoja(nodo_raiz)){ // la raiz tiene un hijo o es hoja
      *puntero_raiz = nodo_ab_obtener(nodo_raiz, pos_del_hijo);
      (*cantidad)--;
      return nodo_ab_borrar(nodo_raiz);
    }

    nodo_ab_t* ultimo_nodo = obtener_ultimo(nodo_ab_obtener_izq(nodo_raiz), der); // la raiz tiene dos hijos
    if(!intercambiar_nodos(nodo_raiz, ultimo_nodo))
      return NULL;

    return abb_borrar_aux(nodo_ab_obtener_izq(nodo_raiz), nodo_ab_obtener_puntero_izq(nodo_raiz), clave, comparar_claves, cantidad);
  }

  nodo_ab_t* nodo_hijo = nodo_ab_obtener(nodo_padre, pos_hijo); // el nodo tiene padre
  pos_nodo pos_hijo_del_hijo = izq;
  if(nodo_ab_tiene_un_hijo(nodo_hijo, &pos_hijo_del_hijo) || nodo_ab_es_hoja(nodo_hijo)){ // el nodo a borrar tiene un hijo o es hoja
    nodo_ab_apuntar(nodo_padre, nodo_ab_obtener(nodo_hijo, pos_hijo_del_hijo), pos_hijo);
    (*cantidad)--;
    return nodo_ab_borrar(nodo_hijo);
  }

  nodo_ab_t* ultimo_nodo = obtener_ultimo(nodo_ab_obtener_izq(nodo_hijo), der); // el nodo a borrar tiene dos hijos
  if(!intercambiar_nodos(nodo_hijo, ultimo_nodo))
    return NULL;

  return abb_borrar_aux(nodo_ab_obtener_izq(nodo_hijo), nodo_ab_obtener_puntero_izq(nodo_hijo), clave, comparar_claves, cantidad);
}

void abb_destruir_aux(nodo_ab_t* nodo, abb_destruir_dato_t destruir_dato){
  if(!nodo)
    return;

  abb_destruir_aux(nodo_ab_obtener_izq(nodo), destruir_dato);
  abb_destruir_aux(nodo_ab_obtener_der(nodo), destruir_dato);
  nodo_ab_destruir(nodo, destruir_dato);
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
  while (nodo_ab_obtener(nodo, pos))
    nodo = nodo_ab_obtener(nodo, pos);
  return nodo;
}

bool intercambiar_nodos(nodo_ab_t* nodo1, nodo_ab_t* nodo2){
  char* clave1 = malloc(sizeof(char)*strlen(nodo_ab_obtener_clave(nodo1))+1); // tengo que hacer esto porque el realloc de nodo_ab_cambiar_clave puede mantener el puntero.
  if(!clave1)
    return false;

  strcpy(clave1, nodo_ab_obtener_clave(nodo1));
  void* dato1  = nodo_ab_obtener_valor(nodo1);

  if(!nodo_ab_cambiar_clave(nodo1, nodo_ab_obtener_clave(nodo2)))
    return false;

  if(!nodo_ab_cambiar_clave(nodo2, clave1))
    return false;

  nodo_ab_cambiar_valor(nodo1, nodo_ab_obtener_valor(nodo2), NULL);
  nodo_ab_cambiar_valor(nodo2, dato1, NULL);

  free(clave1);
  return true;
}

/*************************************************************************
                            Iterador Interno
*************************************************************************/
void abb_in_order_aux(nodo_ab_t* nodo, bool visitar(const char *, void *, void *), void *extra, bool* corte){
  if(!nodo || !(*corte))
    return;

  abb_in_order_aux(nodo_ab_obtener_izq(nodo), visitar, extra, corte);
  if(visitar){
    *corte = visitar(nodo_ab_obtener_clave(nodo), nodo_ab_obtener_valor(nodo), extra);
  }
  abb_in_order_aux(nodo_ab_obtener_der(nodo), visitar, extra, corte);
}

void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra){
  bool corte = true;
  abb_in_order_aux(arbol->raiz, visitar, extra, &corte);
}

/*************************************************************************
                            Iterador Externo
*************************************************************************/
typedef struct abb_iter{
  const abb_t*  arbol;
  nodo_ab_t*    actual;
  pila_t*       pila;
}abb_iter_t;

bool apilar_hacia_izq(abb_iter_t *iter){
  bool ok = true;
  while (nodo_ab_obtener_izq(iter->actual)) {
    ok = pila_apilar(iter->pila, iter->actual);
    if(!ok) return false;
    iter->actual = nodo_ab_obtener_izq(iter->actual);
  }
  return true;
}

abb_iter_t *abb_iter_in_crear(const abb_t *arbol){
  abb_iter_t* iter = malloc(sizeof(abb_iter_t));
  if(!iter)
    return NULL;

  iter->arbol   = arbol;
  iter->actual  = arbol->raiz;
  iter->pila    = pila_crear();
  if(!iter->pila)
    return NULL;

  if(iter->actual) // avanzo iter->actual al primer nodo
    if(!apilar_hacia_izq(iter)){
      pila_destruir(iter->pila);
      free(iter);
      return NULL;
    }

  return iter;
}

bool abb_iter_in_avanzar(abb_iter_t *iter){
  if(abb_iter_in_al_final(iter))
    return false;

  if(nodo_ab_obtener_der(iter->actual)){
    iter->actual = nodo_ab_obtener_der(iter->actual);
    return apilar_hacia_izq(iter);
  }
  iter->actual = pila_desapilar(iter->pila);
  return true;
}

bool abb_iter_in_al_final(const abb_iter_t *iter){
  return iter->actual == NULL;
}

const char *abb_iter_in_ver_actual(const abb_iter_t *iter){
  if(abb_iter_in_al_final(iter))
    return NULL;
  return nodo_ab_obtener_clave(iter->actual);
}

void abb_iter_in_destruir(abb_iter_t* iter){
  pila_destruir(iter->pila);
  free(iter);
}

void abb_var_dump(abb_t* arbol){ // es preorder
  if(!arbol->raiz){
    printf("%s\n", "sin raiz");
    return;
  }
  printf("%s\n", "raiz:");
  nodo_var_dump(arbol->raiz, 0);
}
