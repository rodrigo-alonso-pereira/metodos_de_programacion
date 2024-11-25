#include <stdio.h>
#include <stdlib.h>

typedef struct pokemon {
  char* nombre;
  int numero;
  int nivel_poder;
  char* tipo;
} pokemon;

pokemon crear_pokemon(pokemon nuevo_pokemon) {
  nuevo_pokemon.nombre = (char*)malloc(sizeof(char)*35);
  printf("\nIngrese nombre del pokemon: ");
  scanf("%s", nuevo_pokemon.nombre);//No se agrega & ya que es una direccion de memoria
  printf("Ingrese  numero del pokemon: ");
  scanf("%d", &nuevo_pokemon.numero);
  printf("Ingrese  nivel de poder: ");
  scanf("%d", &nuevo_pokemon.nivel_poder);
  nuevo_pokemon.tipo = (char*)malloc(sizeof(char)*35);
  printf("Ingrese  tipo: ");
  scanf("%s", nuevo_pokemon.tipo);

  return nuevo_pokemon;
}

pokemon* agregar_pokemon(pokemon* old_pokedex, int* n, pokemon nuevo_pokemon) {
  pokemon* nuevo_pokedex = (pokemon*)malloc(sizeof(pokemon) * (*n + 1));
  for (int i = 0; i < *n; i++){
    nuevo_pokedex[i] = old_pokedex[i];
  }
  nuevo_pokedex[*n] = nuevo_pokemon;
  *n = *n + 1;
  free(old_pokedex);

  return nuevo_pokedex;
}

void buscar_pokemon(pokemon* pokedex, int* n, int numero_pokemon) {
  int i;
  int encontrado = -1;
  for (i = 0; i < *n; i++) {
    if (numero_pokemon == pokedex[i].numero) {
      printf("\n-------------------- o --------------------\n");
      printf("El pokemon buscado es:\n\n");
      printf("Nombre del pokemon: %s\n", pokedex[i].nombre);
      printf("Numero del pokemon: %d \n", pokedex[i].numero);
      printf("Nivel de poder del pokemon: %d \n", pokedex[i].nivel_poder);
      printf("Tipo del pokemon: %s\n", pokedex[i].tipo);
      printf("-------------------- o --------------------\n");
      encontrado = i;
    }
  }
  if (encontrado == -1) {
    printf("\n-------------------- o --------------------\n");
    printf("No se ha encontrado el pokemon con numero: %d\n", numero_pokemon);
    printf("-------------------- o --------------------\n");
  }
}

pokemon* eliminar_pokemon(pokemon* old_pokedex, int* n, int numero_pokemon) {
  int count = 0;

  pokemon* nuevo_pokedex = (pokemon*)malloc(sizeof(pokemon) * (*n - 1));
  for (int i = 0; i < *n; i++){
    if (numero_pokemon != old_pokedex[i].numero) {
      nuevo_pokedex[count] = old_pokedex[i];
      count++;
    }
  }
  printf("\n");
  printf("Se ha eliminando el pokemon con numero: %d\n", numero_pokemon);
  printf("\n");

  *n = *n - 1;
  free(old_pokedex);

  return nuevo_pokedex;
}

void mostrar_pokemones(pokemon* pokedex, int* n){
  printf("\n************ Listado de Pokemones ************\n\n");
  for (int i = 0; i < *n; i++) {
    printf("Nombre del pokemon: %s\n", pokedex[i].nombre);
    printf("Numero del pokemon: %d \n", pokedex[i].numero);
    printf("Nivel de poder del pokemon: %d \n", pokedex[i].nivel_poder);
    printf("Tipo del pokemon: %s\n", pokedex[i].tipo);
    printf("-------------------- o --------------------\n");
  }
}

void buscar_mayor(pokemon* pokedex, int* n) {
  int max;
  int posicion_mayor;
  max = pokedex[0].nivel_poder;
  for (int i = 0; i < *n; i++) {
    if (max <= pokedex[i].nivel_poder) {
      max = pokedex[i].nivel_poder;
      posicion_mayor = i;
    }
  }
  printf("\n-------------------- o --------------------\n");
  printf("El pokemon de mayor nivel es:\n\n");
  printf("Nombre del pokemon: %s\n", pokedex[posicion_mayor].nombre);
  printf("Numero del pokemon: %d \n", pokedex[posicion_mayor].numero);
  printf("Nivel de poder del pokemon: %d \n", pokedex[posicion_mayor].nivel_poder);
  printf("Tipo del pokemon: %s\n", pokedex[posicion_mayor].tipo);
  printf("-------------------- o --------------------\n");
}

int main () {
  //Cambiar por append.  
  int n = 0;
  int opcion;

  pokemon* arreglo_pokemon = (pokemon*)malloc(sizeof(pokemon) * n);
  printf("\n************ Bienvenido a la pokedex! ************\n\n");
  
  do {
    printf("Seleccione una de las siguiente opciones \n");
    printf("1. Agregar un Pokemon: \n");
    printf("2. Buscar por numero: \n");
    printf("3. Liberar pokemon. \n"); //Es c/ append pero eliminando el pokemon i
    printf("4. Mostrar todos los pokemon. \n");
    printf("5. Buscar el pokemon de mayor nivel. \n");
    printf("6. Cerrar el programa \n");
    printf("\nIngrese opcion: ");
    scanf("%d", &opcion);
    
    switch(opcion) {
      case 1:
        pokemon nuevo_pokemon;
        nuevo_pokemon = crear_pokemon(nuevo_pokemon);
        arreglo_pokemon = agregar_pokemon(arreglo_pokemon, &n, nuevo_pokemon);
        break;
      case 2:
        printf("\nIngrese numero de pokemon a buscar: ");
        scanf("%d", &opcion);
        buscar_pokemon(arreglo_pokemon, &n, opcion);
        break;
      case 3:
        mostrar_pokemones(arreglo_pokemon, &n);
        printf("\nIngrese numero de pokemon a eliminar: ");
        scanf("%d", &opcion); //TODO: Verificar que exista pokemon.
        arreglo_pokemon = eliminar_pokemon(arreglo_pokemon, &n, opcion);
        break;
      case 4:
        mostrar_pokemones(arreglo_pokemon, &n);
        break;
      case 5:
        buscar_mayor(arreglo_pokemon, &n);
        break;
      case 6:
        printf("\n\n");
        printf("\n************ Saliendo de la pokedex! ************\n");
        printf("\n\n");
        printf("Hasta luego...");
        break;
      default:
        printf("\nOpcion no valida!\n");
    }
    printf("\n");
    
  } while(opcion != 6);
    
  return 0;
}
