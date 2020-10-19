#include<stdio.h>
#include<stdlib.h>

struct Nodo {
    int dato;
    int num_nodo;
    struct Nodo *siguiente_nodo;
};

int numero_nodos;

struct Nodo *crea_nodo(int dato,struct Nodo *siguiente_nodo){

    struct Nodo *nuevo_nodo = (struct Nodo*)malloc(sizeof(struct Nodo));

    if (nuevo_nodo == NULL)
    {
        printf("Error al Crear al Nodo");
        exit(0);
    }
    
    nuevo_nodo->dato = dato;
    nuevo_nodo->siguiente_nodo = siguiente_nodo;

    return nuevo_nodo;
};

int esta_vacia(struct Nodo *primer_nodo){
    return (primer_nodo == NULL);
}

void numera_nodos(struct Nodo *primer_nodo){
    if (esta_vacia(primer_nodo))
    {
        printf("\nNo hay Elementos por Enumerar.");
        return;
    }

    int num_nodo = 1;

    struct Nodo *aux = primer_nodo;
    while (aux -> siguiente_nodo != NULL)
    {
        aux->num_nodo = num_nodo;
        aux = aux->siguiente_nodo;
        num_nodo++;
    }
    aux->num_nodo = num_nodo;
    numero_nodos = num_nodo;
}

void imprime_lista(struct Nodo *primer_nodo){
    if(esta_vacia(primer_nodo)){
        printf("\nNo Hay elementos para imprimir.");
        return;
    }
    
    printf("\n\nLos Elementos de la Lista son: \n\n");
    while (primer_nodo != NULL)
    {
        printf("[No.%d|%d]-->",primer_nodo->num_nodo,primer_nodo->dato);
        primer_nodo = primer_nodo->siguiente_nodo;
    }

}

struct Nodo *inserta_inicio(struct Nodo *primer_nodo,int dato){
    struct Nodo *nuevo_nodo = crea_nodo(dato,primer_nodo);
    primer_nodo = nuevo_nodo;

    numera_nodos(primer_nodo);
    return primer_nodo;
}

struct Nodo *borrar_inicio(struct Nodo *primer_nodo){
    if(esta_vacia(primer_nodo)){
        printf("\nNo hay elementos para borrar.");
    }

    struct Nodo *aux = primer_nodo;
    primer_nodo = primer_nodo->siguiente_nodo;
    aux->siguiente_nodo = NULL;
    free(aux);
    numera_nodos(primer_nodo);

    return primer_nodo;
}

struct Nodo *inserta_final(struct Nodo *primer_nodo,int dato){
   if(esta_vacia(primer_nodo))
		return inserta_inicio(primer_nodo, dato);
		
	// Creamos el nodo nuevo
	struct Nodo *nuevo_nodo = crea_nodo(dato, NULL);
	
	// Creamos un auxiliar para que recorra la lista hasta el final
	struct Nodo *aux = primer_nodo;
    
	while(aux->siguiente_nodo != NULL)
		aux = aux->siguiente_nodo;
	
	aux->siguiente_nodo = nuevo_nodo; // pone una flecha desde aux hasta nuevo_nodo
	numera_nodos(primer_nodo);
	return primer_nodo;

}

struct Nodo *borrar_final(struct Nodo *primer_nodo){
    if (esta_vacia(primer_nodo))
    {
        printf("\nNo hay Elementos para Borrar.");
    }
    
    //Cuando Solo hay un solo elemento en la lista
    if(primer_nodo -> siguiente_nodo == NULL)
        return borrar_inicio(primer_nodo);

    struct Nodo *aux1 = primer_nodo;
    struct Nodo *aux2 = primer_nodo->siguiente_nodo;

    while (aux2->siguiente_nodo != NULL)
    {
        aux1 = aux1->siguiente_nodo;
        aux2 = aux2->siguiente_nodo;
    }
    
    aux1->siguiente_nodo = NULL;
    free(aux2);
    numera_nodos(primer_nodo);
    return primer_nodo;
}


struct Nodo *insertar_posicion_n(struct Nodo *primer_nodo, int posicion, int dato){
    if(posicion < 1 || posicion > numero_nodos ){
        printf("\nPosicion fuera de Rango.");
        exit(0);
    }

    if(posicion == 1 ){
        printf("\nInsertando al inicio.");
        return inserta_inicio(primer_nodo,dato);
    }

    if(posicion == numero_nodos +1)
        return inserta_final(primer_nodo,dato);

    if(posicion > 1 && posicion <= numero_nodos){
        int n;
        struct Nodo *aux1 = primer_nodo;
        struct Nodo *aux2 = primer_nodo->siguiente_nodo;

        while (n < posicion-1)
        {
            n++;
            aux1= aux1->siguiente_nodo;
            aux2 = aux2->siguiente_nodo;
        }
        
        struct Nodo *nuevo_nodo = crea_nodo(dato,aux2);
        aux1->siguiente_nodo=nuevo_nodo;
		numera_nodos(primer_nodo);
		
		return primer_nodo;
    }
}

struct Nodo *borra_lugar_n(struct Nodo *primer_nodo, int posicion){

    if(esta_vacia(primer_nodo)){
        printf("\nNo hay elementos para eliminar.");
    }
    
    if(posicion == 1){
        return borrar_inicio(primer_nodo);
    }

    if(posicion == numero_nodos){
        return borrar_final(primer_nodo);
    }

    if(posicion < numero_nodos || posicion > numero_nodos){
        printf("\nFuera de Rango");
    }

    if(posicion > 1 && posicion <= numero_nodos){

        int n = 1;
        struct Nodo *aux1 = primer_nodo;
        struct Nodo *aux2 = primer_nodo->siguiente_nodo;
        
        //Avanzamos al primer Nodo y al siguiente Nodo
        while(n < posicion -1){
            n++;
            aux1= primer_nodo->siguiente_nodo;
            aux2 = primer_nodo->siguiente_nodo;
        }
        aux1->siguiente_nodo=aux2->siguiente_nodo;
		free(aux2);
		numera_nodos(primer_nodo);
		return primer_nodo;
    }
}

int main(int argc, char const *argv[])
{
  
    struct Nodo *primer_nodo = NULL;

    primer_nodo = crea_nodo(15,primer_nodo);
     primer_nodo = inserta_inicio(primer_nodo,20);
     primer_nodo = inserta_inicio(primer_nodo,30);
    imprime_lista(primer_nodo);

    primer_nodo = borrar_final(primer_nodo);
    imprime_lista(primer_nodo);


    primer_nodo = insertar_posicion_n(primer_nodo,2,150);
    imprime_lista(primer_nodo);

    primer_nodo = borra_lugar_n(primer_nodo,1);
    imprime_lista(primer_nodo);

    primer_nodo = inserta_final(primer_nodo,5);
    primer_nodo = inserta_final(primer_nodo,15);
    imprime_lista(primer_nodo);
    primer_nodo = borrar_inicio(primer_nodo);
    imprime_lista(primer_nodo);
    numera_nodos(primer_nodo);
    
 
    return 0;
}

