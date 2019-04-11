#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"

int main() {
    FILE *Fin, *Fout;
    Nodo* lista = NULL, *lista_final = NULL;
    int c;
    int *numeros= NULL, i=1, index, e=0, apex = 0;
    char m,principal;
    char *nombre_in = "lectura_nodos.txt";
    char *nombre_out = "escritura_ordenada.txt";

    if((Fin = fopen(nombre_in,"r")) == NULL){
        puts("No se pueden abrir los archivos, intenta de nuevo");
        return 1;
    }else{
        Fin = fopen(nombre_in,"r");
    }

    while(fscanf(Fin,"%d",&c) != EOF ){
        if(numeros == NULL ){
            numeros = malloc(sizeof(c));
            *numeros = c;
        }else{
            i++;
            numeros = realloc(numeros,sizeof(numeros)*i);
            index = i-1;
            *(numeros+index) = c;
        }
    }
    c = 0;
    puts("Transfiriendo datos a la lista...");
    while( index >= 0 ){
        lista = Alta_Final(*(numeros+c),lista);
        index--;
        c++;
    }
    puts("...Transferidos.");

    do{
        fflush(stdin);
        puts("1 >> Modificar los Datos de la lista principal.\n"
             "2 >> Ordenar los Datos leidos.\n"
             "3 >> Mostrar la lista Final y Guardar Datos en Archivo.\n"
             "4 >> Eliminar los nodos.\n"
             "0 >> Salir.\n");
        scanf(" %c",&principal);
        fflush(stdin);
        switch (principal){
            case '1':
                do{
                    fflush(stdin);
                    puts("Elige una opcion:\n"
                         "1 >> Baja de datos de la fila.\n"
                         "2 >> Mostrar datos de la fila.\n"
                         "0 >> Salir.");
                    scanf(" %c",&m);
                    fflush(stdin);
                    switch (m) {
                        case ('1'):
                            char m_2;
                            do{
                                fflush(stdin);
                                puts("Elige una opcion:\n"
                                     "1 >> Baja de datos al Inicio.\n"
                                     "2 >> Baja de datos por ID.\n"
                                     "3 >> Baja de datos por Dato.\n"
                                     "4 >> Baja de datos al Final.\n"
                                     "0 >> Regresar.");
                                scanf(" %c",&m_2);
                                fflush(stdin);
                                switch (m_2) {
                                    case('1'):
                                        lista = Baja_Inicial(lista);
                                        if(e == 1){
                                            apex = 1;
                                        }
                                        break;
                                    case ('2'):
                                        puts("Ingresa el Id para dar de Baja");
                                        int size = Contador(lista);
                                        int id_baja;
                                        scanf("%d",&id_baja);
                                        if(id_baja==1){
                                            lista=Baja_Inicial(lista);
                                        }else if(id_baja==size){
                                            lista = Baja_Final(lista);
                                        }else{
                                            lista = Baja_ID(lista,id_baja);
                                        }
                                        if(e == 1){
                                            apex = 1;
                                        }
                                        break;
                                    case ('3'):
                                        puts("Ingresa el dato para dar de Baja:");
                                        int b_baja;
                                        scanf("%d",&b_baja);
                                        lista = Baja_Dato(lista,b_baja);
                                        if(e == 1){
                                            apex = 1;
                                        }
                                        break;
                                    case ('4'):
                                        lista = Baja_Final(lista);
                                        if(e == 1){
                                            apex = 1;
                                        }
                                        break;
                                    case ('0'):
                                        break;
                                    default:
                                        puts("Ingresa una opcion viable");
                                        break;
                                }
                                fflush(stdin);
                            }while(m_2 != '0');
                            break;
                        case ('2'):
                            char m_5;
                            do {
                                puts("Como quieres ver tus datos:");
                                puts("1 >> Completos.");
                                puts("2 >> Recorrido.");
                                puts("0 >> Cancelar.");
                                scanf(" %c",&m_5);
                                switch (m_5) {
                                    case '1':
                                        Mostrar_Datos(lista);
                                        break;
                                    case '2':
                                        Mostrar_Datos_OVO(lista);
                                        break;
                                }
                            } while (m_5 != '0');
                            break;
                        case ('0'):
                            puts("Regresando al menu principal...");
                            break;
                        default:
                            puts("Ingresa una opcion viable");
                            break;
                    }
                    fflush(stdin);
                }while(m != '0');
                break;
            case '2':
                lista_final = ordenamiento(lista,lista_final,i);
                e = 1;
                puts("Ordenado");
                break;
            case '3':
                if(e > 0){
                    char m_10;
                    do {
                        if(apex == 1){
                            lista_final = ordenamiento(lista, lista_final, i);
                        }
                        puts("Como quieres ver tus datos:");
                        puts("1 >> Completos");
                        puts("2 >> Recorrido");
                        puts("3 >> Guardar en Archivo");
                        puts("0 >> Cancelar");
                        scanf(" %c", &m_10);
                        switch (m_10) {
                            case '1':
                                Mostrar_Datos(lista_final);
                                break;
                            case '2':
                                Mostrar_Datos_OVO(lista_final);
                                break;
                            case '3':
                                if((Fout = fopen(nombre_out,"w")) == NULL){
                                    puts("No se pueden abrir los archivos, intenta de nuevo");
                                    return 1;
                                }else{
                                    Fout = fopen(nombre_out,"w");
                                }

                                while(lista_final != NULL){
                                    fprintf(Fout,"%d \n",lista_final->dato);
                                    lista_final = lista_final->sig;
                                }
                                m_10='0';
                                break;
                        }
                    } while (m_10 != '0');
                }else{
                    puts("Todavia no tienes la lista ordenada");
                    break;
                }
                break;
            case '4':
                fflush(stdin);
                puts("Estas a punto de reiniciar el proceso...\n"
                     "Deseas Continuar?(Y/N)\n");
                char desicion;
                scanf(" %c",&desicion);
                if (desicion == 'Y'){
                    lista_final = NULL;
                    e=0;
                }else{
                    puts("Se cancelo el proceso");
                    break;
                }
                break;
            case '0':
                puts("Adios...");
                break;
            default:
                puts("Pon algo real...");
                break;
        }
    }while(principal!= '0');

    fclose(Fin);
    fclose(Fout);
    free(numeros);
    numeros = NULL;

}