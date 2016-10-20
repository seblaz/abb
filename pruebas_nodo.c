#include <stdio.h>
#include "nodo_ab.h"
#include "testing.h"
#include <string.h>

static void prueba_crear_nodo_vacio()
{
    nodo_ab_t* nodo = nodo_ab_crear("", NULL);

    print_test("Prueba nodo crear nodo vacio", nodo);
    print_test("Prueba nodo el dato es NULL", !nodo_ab_obtener_valor(nodo));
    print_test("Prueba nodo la clave no es NULL", nodo_ab_obtener_clave(nodo));
    print_test("Prueba nodo la clave esta vacia", !strcmp(nodo_ab_obtener_clave(nodo), ""));

    nodo_ab_destruir(nodo, NULL);
}

static void prueba_nodo_cambiar_claves()
{
    char *clave1 = "perro", *valor1a = "guau";
    char *clave2 = "gato", *valor2a = "miau";

    nodo_ab_t* nodo1 = nodo_ab_crear(clave1, valor1a);
    nodo_ab_t* nodo2 = nodo_ab_crear(clave2, valor2a);

    print_test("Prueba nodo el dato1 no es NULL", nodo_ab_obtener_valor(nodo1));
    print_test("Prueba nodo el dato2 no es NULL", nodo_ab_obtener_valor(nodo2));
    print_test("Prueba nodo la clave1 no es NULL", nodo_ab_obtener_clave(nodo1));
    print_test("Prueba nodo la clave2 no es NULL", nodo_ab_obtener_clave(nodo2));

    print_test("Prueba nodo el dato de nodo1 es valor1a", nodo_ab_obtener_valor(nodo1) == valor1a);
    print_test("Prueba nodo el dato de nodo2 es valor2a", nodo_ab_obtener_valor(nodo2) == valor2a);
    print_test("Prueba nodo la clave de nodo1 es clave1", !strcmp(nodo_ab_obtener_clave(nodo1), clave1));
    print_test("Prueba nodo la clave de nodo2 es clave2", !strcmp(nodo_ab_obtener_clave(nodo2), clave2));

    clave1 = "gato";
    clave2 = "perro";

    print_test("Prueba nodo cambiar clave1", strcmp(nodo_ab_obtener_clave(nodo1), clave1));
    print_test("Prueba nodo cambiar clave2", strcmp(nodo_ab_obtener_clave(nodo2), clave2));

    print_test("Prueba nodo cambiar valor clave1", nodo_ab_cambiar_clave(nodo1, clave1));
    print_test("Prueba nodo cambiar valor clave2", nodo_ab_cambiar_clave(nodo2, clave2));
    print_test("Prueba nodo la clave de nodo1 es clave1", !strcmp(nodo_ab_obtener_clave(nodo1), clave1));
    print_test("Prueba nodo la clave de nodo2 es clave2", !strcmp(nodo_ab_obtener_clave(nodo2), clave2));

    nodo_ab_destruir(nodo1, NULL);
    nodo_ab_destruir(nodo2, NULL);
}

static void prueba_nodo_cambiar_valores()
{
    char *clave1 = "perro", *valor1a = "guau", *valor1b = "warf";
    char *clave2 = "gato", *valor2a = "miau", *valor2b = "meaow";

    nodo_ab_t* nodo1 = nodo_ab_crear(clave1, valor1a);
    nodo_ab_t* nodo2 = nodo_ab_crear(clave2, valor2a);

    print_test("Prueba nodo el dato de nodo1 es valor1a", nodo_ab_obtener_valor(nodo1) == valor1a);
    print_test("Prueba nodo el dato de nodo2 es valor2a", nodo_ab_obtener_valor(nodo2) == valor2a);
    print_test("Prueba nodo la clave de nodo1 es clave1", !strcmp(nodo_ab_obtener_clave(nodo1), clave1));
    print_test("Prueba nodo la clave de nodo2 es clave2", !strcmp(nodo_ab_obtener_clave(nodo2), clave2));

    nodo_ab_cambiar_valor(nodo1, valor1b, NULL);
    nodo_ab_cambiar_valor(nodo2, valor2b, NULL);

    print_test("Prueba nodo el dato de nodo1 es valor1b", nodo_ab_obtener_valor(nodo1) == valor1b);
    print_test("Prueba nodo el dato de nodo2 es valor2b", nodo_ab_obtener_valor(nodo2) == valor2b);

    nodo_ab_destruir(nodo1, NULL);
    nodo_ab_destruir(nodo2, NULL);
}

static void prueba_nodo_apuntar()
{
  char *clave1 = "perro", *valor1 = "guau";
  char *clave2 = "gato", *valor2 = "miau";
  char *clave3 = "vaca", *valor3 = "mu";

  nodo_ab_t* nodo1 = nodo_ab_crear(clave1, valor1);
  nodo_ab_t* nodo2 = nodo_ab_crear(clave2, valor2);
  nodo_ab_t* nodo3 = nodo_ab_crear(clave3, valor3);

  print_test("Prueba nodo obtener nodo izquierdo de nodo1 es NULL", !nodo_ab_obtener_izq(nodo1));
  print_test("Prueba nodo obtener nodo derecho de nodo1 es NULL", !nodo_ab_obtener_der(nodo1));
  print_test("Prueba nodo obtener nodo izquierdo de nodo2 es NULL", !nodo_ab_obtener_izq(nodo2));
  print_test("Prueba nodo obtener nodo derecho de nodo2 es NULL", !nodo_ab_obtener_der(nodo2));
  print_test("Prueba nodo obtener nodo izquierdo de nodo3 es NULL", !nodo_ab_obtener_izq(nodo3));
  print_test("Prueba nodo obtener nodo derecho de nodo3 es NULL", !nodo_ab_obtener_der(nodo3));

  nodo_ab_apuntar_izq(nodo1, nodo2);
  print_test("Prueba nodo obtener nodo izquierdo de nodo1 es nodo2", nodo_ab_obtener_izq(nodo1) == nodo2);

  nodo_ab_apuntar_der(nodo1, nodo3);
  print_test("Prueba nodo obtener nodo derecho de nodo1 es nodo3", nodo_ab_obtener_der(nodo1) == nodo3);

  nodo_ab_destruir(nodo1, NULL);
  nodo_ab_destruir(nodo2, NULL);
  nodo_ab_destruir(nodo3, NULL);
}

static void prueba_nodo_borrar()
{
  char *clave1 = "perro", *valor1 = "guau";
  char *clave2 = "gato", *valor2 = "miau";
  char *clave3 = "vaca", *valor3 = "mu";

  nodo_ab_t* nodo1 = nodo_ab_crear(clave1, valor1);
  nodo_ab_t* nodo2 = nodo_ab_crear(clave2, valor2);
  nodo_ab_t* nodo3 = nodo_ab_crear(clave3, valor3);

  print_test("Prueba nodo borrrar nodo1 es valor1", nodo_ab_borrar(nodo1) == valor1);
  print_test("Prueba nodo borrrar nodo2 es valor2", nodo_ab_borrar(nodo2) == valor2);
  print_test("Prueba nodo borrrar nodo3 es valor3", nodo_ab_borrar(nodo3) == valor3);
}

void pruebas_nodo(){
  printf("%s\n", "***************** PRUEBAS NODO *****************");
  prueba_crear_nodo_vacio();
  prueba_nodo_cambiar_claves();
  prueba_nodo_cambiar_valores();
  prueba_nodo_apuntar();
  prueba_nodo_borrar();
}
