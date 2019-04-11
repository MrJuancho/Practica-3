//
// Created by MrJuancho on 07/03/2019.
//

#ifndef PRACTICA_3_FUNCIONES_H
#define PRACTICA_3_FUNCIONES_H

typedef struct _Nodo{
    int dato;
    struct _Nodo *sig;
    struct _Nodo *ant;
}Nodo;

int Contador(Nodo* a){
    int i = 0;
    if(a !=NULL) {
        while (a->sig != NULL) {
            a = a->sig;
            i++;
        }
    }
    return i;
}

void Mostrar_Datos(Nodo *lista){
    if(lista != NULL){
        int i = 0;
        while (lista != NULL){
            printf("Elemento: %d ; Dato: %d\n", (i+1), lista -> dato);
            lista = lista -> sig;
            i++;
        }
        printf("La lista tiene %d datos\n", i);
    }else{
        puts("Tu Lista esta vacia\n");
    }
}

void Mostrar_Datos_OVO(Nodo *lista){
    int j = Contador(lista);
    int a = 1;
    char mov;
    puts("Ahorita estas en:");
    printf("Elemento : %d -> Dato : %d\n",a,lista->dato);
    printf("Size: %d\n",j);
    do{
        if (a <= 0 || a > j){
            puts("Se te Acabo el Array");
            break;
        }
        puts("Presiona '>' o '<' para moverte a traves de la lista.Puedes presionar 0 para regresar");
        scanf(" %c",&mov);
        switch (mov){
            case '>':
                a++;
                lista = lista->sig;
                printf("Elemento : %d -> Dato : %d\n",a,lista->dato);
                break;
            case '<':
                a--;
                if(a <= 0) break;
                lista = lista ->ant;
                printf("Elemento : %d -> Dato : %d\n",a,lista->dato);
                break;
            case '0':
                puts("Regresando...");
                break;
            default:
                puts("Am I a joke to you?");
                break;
        }
    }while(mov != '0');
}

Nodo* allocateMem(int dato){
    Nodo* dummy;
    dummy = (Nodo*)malloc(sizeof(Nodo));
    dummy -> dato = dato;
    dummy -> sig = NULL;
    dummy -> ant = NULL;
    return dummy;
}

Nodo* Alta_Final(int dato, Nodo* frente){
    Nodo *box,*aux;
    box = allocateMem(dato);
    if(frente == NULL){
        return box;
    }else{
        aux = frente;
        while(aux -> sig!=NULL){
            aux = aux -> sig;
        }
        aux -> sig = box;
        box -> ant = aux;
    }
    return frente;
}

Nodo* Alta_Inicial(int dato, Nodo* cima){
    Nodo* box;
    box = allocateMem(dato);
    if(cima != NULL){
        box -> sig = cima;
        cima -> ant = box;
    }
    cima = box;
    puts("Agregado");
    return cima;
}

Nodo* Alta_ID(Nodo *fila, int dato, int pos){
    Nodo *aux, *nuevo;
    int size,i;
    nuevo = allocateMem(dato);
    if (fila == NULL){
        return nuevo;
    }else{
        aux = fila;
        size = Contador(fila);
        if (pos < 0 || pos > size) {
            puts("Error en el numero de la posicion introducida");
            return nuevo;
        }
        for (i = 0; i < pos ; i++) {
            aux = aux -> sig;
        }
        nuevo -> sig = aux -> sig;
        nuevo -> ant = aux;
        aux -> sig = nuevo;
        nuevo -> sig -> ant = nuevo;
    }
    return fila;
}

Nodo* Alta_Dato(Nodo *fila, int dato_nuevo, int dato_busqueda){
    Nodo *aux, *nuevo;
    aux = fila;
    nuevo = allocateMem(dato_nuevo);
    if (fila == NULL){
        puts("No existen datos. Intenta de nuevo");
        return fila;
    } else {
        while(aux->sig != NULL){
            if (aux->dato == dato_busqueda){
                nuevo->sig = aux->sig;
                nuevo -> ant = aux;
                aux->sig = nuevo;
                nuevo -> sig -> ant = nuevo;
                break;
            }else{
                aux = aux->sig;
            }
        }
    }
    return fila;
}

Nodo *Baja_Inicial(Nodo* cima){
    Nodo* aux;
    int size = Contador(cima);
    if(cima == NULL){
        puts("Tu Lista no tiene datos");
    }else if(size <= 1){
        free(cima);
        return NULL;
    }
    if(cima != NULL){
        aux = cima;
        cima = aux -> sig;
        cima -> ant = NULL;
        free(aux);
    }
    return cima;
}

Nodo *Baja_Final(Nodo *cima){
    int size = Contador(cima);
    Nodo *aux;
    if(cima == NULL){
        return cima;
    }else{
        aux=cima;
        if(size != 1){
            aux = cima;
            int j;
            for (j = 0; j < (size-1) ; ++j) {
                aux = aux->sig;
            }
            free(aux->sig);
            aux->sig = NULL;
        }else{
            free(cima);
        }
    }
    return cima;
}

Nodo *Baja_ID(Nodo *fila, int pos){
    Nodo *aux, *borrar;
    int size;
    size = Contador(fila);
    if (fila == NULL){
        puts("No hay datos en tu fila, intenta de nuevo");
    }else{
        if(pos>size||pos<0)
        {
            puts("Error en el numero de la posicion introducida");
            return aux;
        }
        aux = fila;
        for (int i = 0; i < pos ; ++i) {
            aux = aux -> sig;
        }
        borrar = aux->sig;
        aux->sig = borrar->sig;
        borrar -> sig -> ant = aux;
        free(borrar);
    }
    return fila;
}

Nodo *Baja_Dato(Nodo *fila, int dato_busqueda){
    Nodo *aux, *borrar;
    int size = Contador(fila);
    if (fila == NULL){
        puts("No existen datos. Intenta de nuevo");
        return fila;
    } else {
        aux = fila;
        if(size == 1){
            free(fila);
            return fila;
        }else {
            while (aux->sig != NULL) {
                if (aux->sig->dato == dato_busqueda) {
                    borrar = aux->sig;
                    aux->sig = borrar->sig;
                    borrar -> sig -> ant = aux;
                    free(borrar);
                    break;
                } else {
                    aux = aux->sig;
                }
            }
        }
    }
    return fila;
}

Nodo *Modificar_ID(Nodo *fila, int pos, int dato){
    Nodo *aux;
    int size;
    if (fila == NULL){
        puts("No hay datos en tu fila, intenta de nuevo");
    }else{
        aux = fila;
        size = Contador(aux);
        while(pos < 0 || pos > size){
            puts("Ingresa una posicion existente");
            scanf("%d",pos);
        }
        for (int i = 0; i < pos ; i++) {
            aux = aux -> sig;
        }
        aux -> dato = dato;
    }
    return fila;
}

Nodo *Modificar_Dato(Nodo *fila, int dato_busqueda, int dato_nuevo){
    Nodo *aux, *sublista = NULL;
    int homonimos = 0;
    if (fila == NULL){
        puts("No existen datos. Intenta de nuevo");
        return fila;
    } else {
        aux = fila;
        while(aux->sig != NULL){
            if (aux->dato == dato_busqueda){
                homonimos++;
                sublista = Alta_Inicial(aux->dato,sublista);
                break;
            }else{
                aux = aux->sig;
            }
        }
        if(homonimos > 1){
            puts("Se encontraron los siguientes datos repetidos, cual deseas modificar?");
            Mostrar_Datos(sublista);
            int pos,size;
            while(pos < 0 || pos > size) {
                puts("Ingresa la pos del dato a modificar");
                scanf("%d", &pos);
            }
            for (int i = 0; i < pos ; ++i) {
                aux = aux -> sig;
            }
            fila = aux;
            fila -> dato = dato_nuevo;
        }else{
            while(aux->sig != NULL) {
                if (aux->dato == dato_busqueda) {
                    aux->dato = dato_nuevo;
                }else {
                    aux = aux->sig;
                }
            }
        }
    }
    return fila;
}

void intercambia(int *ptrElemento1, int *ptrElemento2 ) {
    int almacena = *ptrElemento1;
    *ptrElemento1 = *ptrElemento2;
    *ptrElemento2 = almacena;
}

int particion(int * arr, int const min, int const max){
    int pivot = arr[max];
    int i = (min - 1);
    for (int j = min; j <= max- 1; j++){
        if (arr[j] <= pivot){
            i++;
            intercambia(&arr[i], &arr[j]);
        }
    }
    intercambia(&arr[i + 1], &arr[max]);
    return (i + 1);
}

void quickSort(int *arr, int min, int max){
    if (min < max){
        int pi = particion(arr, min, max);
        quickSort(arr, min, pi - 1);
        quickSort(arr, pi + 1, max);
    }
}

Nodo* ordenamiento(Nodo* lista,Nodo *lista_final, int i) {
    lista_final = NULL;
    int size = 0, *aux_numeros = NULL, alpha = 1, inicio;
    size = Contador(lista);
    while (lista != NULL) {
        if (aux_numeros == NULL) {
            aux_numeros = malloc(sizeof(lista->dato));
            *aux_numeros = lista->dato;
        } else {
            alpha++;
            aux_numeros = realloc(aux_numeros, sizeof(aux_numeros) * i);
            inicio = alpha - 1;
            *(aux_numeros + inicio) = lista->dato;
        }
        lista = lista->sig;
    }
    quickSort(aux_numeros, 0, inicio);
    int y = 0;
    while (inicio >= 0) {
        lista_final = Alta_Final(*(aux_numeros + y), lista_final);
        inicio--;
        y++;
    }
    return lista_final;
}


#endif //PRACTICA_3_FUNCIONES_H
