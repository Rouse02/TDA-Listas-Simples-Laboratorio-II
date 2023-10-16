#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DIM 30
/*Estructuras-----------------------------------------------------------------------------------*/
typedef struct {
    char nombreYapellido[DIM];
    int edad;
}stPersona;

typedef struct {
    stPersona infoPersona;
    struct stNodo *ptrSiguiente;
}stNodo;

/*Prototipado-----------------------------------------------------------------------------------*/
stNodo *inicializarLista();
stNodo *crearNodo(stPersona unaPersona);
stNodo *buscarUltimoNodo(stNodo *ptrLista);
stNodo *invertirLista(stNodo *ptrLista, stNodo *ptrListaInvertida);
int buscarDatoLista(stNodo *ptrLista, int edad);
stNodo *insertarNodosALista3(stNodo *lista1, stNodo *lista2, stNodo *lista3);

stNodo *agregarNodoAlPrincipio(stNodo *ptrLista, stNodo *nuevoNodo);
stNodo *agregarNodosAlPrincipio(stNodo *ptrLista, char rutaArchivoPersonas[]);

stNodo *agregarNodoAlFinal(stNodo *ptrLista, stNodo *nuevoNodo);
stNodo *agregarNodosAlFinal(stNodo *ptrLista, char rutaArchivoPersonas[]);

stNodo *agregarNodoEnOrden(stNodo *ptrLista, stNodo *nuevoNodo);
stNodo *agregarNodosEnOrden(stNodo *ptrLista, char rutaArchivoPersonas[]);

void borrarListaRecursiva(stNodo *ptrLista);
stNodo *borrarNodoAlPrincipio(stNodo *ptrLista);
stNodo *borrarNodoPorNombre(stNodo *ptrLista, char nombre[]);

void mostrarListaRecursiva(stNodo *ptrLista);

void escrbirArchivoPersonas(char rutaArchivoPersonas[]);
void mostrarArchivoPersonas(char rutaArchivoPersonas[]);
stPersona cargarUnaPersona();
void mostrarUnaPersona(stPersona unaPersona);
/*-----------------------------------------------------------------------------------*/
int main(){

    char rutaArchivoPersonas[] = {"archivoPersonas.bin"};
    stNodo *ptrLista = inicializarLista();
    stNodo *ptrLista2 = inicializarLista();
    stNodo *ptrLista3 = inicializarLista();

    //escrbirArchivoPersonas(rutaArchivoPersonas);
    printf("Mostrando Archivo de Personas \n\n");
    mostrarArchivoPersonas(rutaArchivoPersonas);

//    ptrLista = agregarNodosAlPrincipio(ptrLista, rutaArchivoPersonas);
//    printf("Mostrando Lista agregando al Principio \n\n");
//    mostrarListaRecursiva(ptrLista);

    ptrLista = agregarNodosAlFinal(ptrLista, rutaArchivoPersonas);
    printf("Mostrando Lista agregando al Final \n\n");
    mostrarListaRecursiva(ptrLista);

//    ptrLista = agregarNodosEnOrden(ptrLista, rutaArchivoPersonas);
//    printf("Mostrando Lista agregando en Orden (Por nombre) \n\n");
//    mostrarListaRecursiva(ptrLista);

//    stNodo *ptrListaInvertida = inicializarLista();
//    ptrListaInvertida = invertirLista(ptrLista, ptrListaInvertida);
//    printf("Mostrando Lista Invertida \n\n");
//    mostrarListaRecursiva(ptrListaInvertida);

//    ptrLista = borrarNodoAlPrincipio(ptrLista);
//    printf("Mostrando Lista luego de eliminar el Primer Nodo \n\n");
//    mostrarListaRecursiva(ptrLista);

//    char nombre[] = {"Brisa Ortiz"};
//    ptrLista = borrarNodoPorNombre(ptrLista, nombre);
//    printf("Mostrando Lista luego de eliminar un nodo por valor \n\n");
//    mostrarListaRecursiva(ptrLista);

//    int edad = 56;
//
//    int resultado = buscarDatoLista(ptrLista, edad);
//
//    if(resultado == 1) printf("Registro encontrado con exito \n\n");
//
//    else printf("Registro no encontrado \n\n");

    ptrLista2 = agregarNodosAlFinal(ptrLista2, rutaArchivoPersonas);
    printf("Mostrando Lista 2 \n");
    mostrarListaRecursiva(ptrLista2);

    ptrLista3 = insertarNodosALista3(ptrLista, ptrLista2, ptrLista3);
    printf("Mostrando Lista Intercalada \n");
    mostrarListaRecursiva(ptrLista3);

}
/*Funciones-----------------------------------------------------------------------------------*/

void escrbirArchivoPersonas(char rutaArchivoPersonas[]) {

    char eleccion = 's';
    FILE *ptrArchivoPersonas = fopen(rutaArchivoPersonas, "ab");

    if(ptrArchivoPersonas == NULL) printf("Error al abrir el archivo \n");

    else {
        do {
            stPersona unaPersona = cargarUnaPersona();
            fwrite(&unaPersona, sizeof(stPersona), 1, ptrArchivoPersonas);

            printf("Pulse 's' para cargar otra Persona en Sistema --> ");
            fflush(stdin);
            scanf("%c", &eleccion);
            printf("\n");

        }while(eleccion == 's');

    fclose(ptrArchivoPersonas);
    }
}

stPersona cargarUnaPersona() {

    int flag = 0;
    int edad;
    stPersona unaPersona;

    printf("Ingrese su Nombre y Apellido --> ");
    fflush(stdin);
    gets(unaPersona.nombreYapellido);
    printf("\n");

    do {
    printf("Ingrese su Edad --> ");
    fflush(stdin);

    if(scanf("%i", &edad) == 1) {

        if(edad >= 0 && edad <= 110) {
            printf("\n");
            flag = 1;
            unaPersona.edad = edad;

        }else printf("No ingresaste una edad valida. Vuelva a intentarlo \n");

    }else printf("No ingresaste un numero. Vuelva a intentarlo \n");

    }while(flag == 0);

    return unaPersona;
}

void mostrarArchivoPersonas(char rutaArchivoPersonas[]) {

    FILE *ptrArchivoPersonas = fopen(rutaArchivoPersonas, "rb");

    if(ptrArchivoPersonas == NULL) printf("Error al abrir el archivo \n");

    else {
        stPersona unaPersona;

        while(!feof(ptrArchivoPersonas)) {
            fread(&unaPersona, sizeof(stPersona), 1, ptrArchivoPersonas);

            if(!feof(ptrArchivoPersonas)) {
                mostrarUnaPersona(unaPersona);
            }
        }
    fclose(ptrArchivoPersonas);
    }
}

void mostrarUnaPersona(stPersona unaPersona) {

    printf("Nombre y Apellido --> |%s|\n", unaPersona.nombreYapellido);
    printf("Edad --> |%i|\n\n", unaPersona.edad);
}
/*Funciones de Listas Simples-----------------------------------------------------------------------------------*/

stNodo *inicializarLista() {
    return NULL;
}

stNodo *crearNodo(stPersona unaPersona) {

    stNodo *nuevoNodo = (stNodo *) malloc(sizeof(stNodo));

    nuevoNodo->infoPersona = unaPersona;
    nuevoNodo->ptrSiguiente = NULL;

    return nuevoNodo;
}

stNodo *agregarNodoAlPrincipio(stNodo *ptrLista, stNodo *nuevoNodo) {

    if(ptrLista == NULL) ptrLista = nuevoNodo;

    else {
        nuevoNodo->ptrSiguiente = ptrLista;
        ptrLista = nuevoNodo;
    }
    return ptrLista;
}

stNodo *agregarNodosAlPrincipio(stNodo *ptrLista, char rutaArchivoPersonas[]) {

    FILE *ptrArchivoPersonas = fopen(rutaArchivoPersonas, "rb");

    if(ptrArchivoPersonas == NULL) printf("Error al abrir el archivo \n");

    else {
        stPersona unaPersona;

        while(!feof(ptrArchivoPersonas)) {

            fread(&unaPersona, sizeof(stPersona), 1, ptrArchivoPersonas);
            if(!feof(ptrArchivoPersonas)) ptrLista = agregarNodoAlPrincipio(ptrLista, crearNodo(unaPersona));
        }
    fclose(ptrArchivoPersonas);
    }
    return ptrLista;
}

stNodo *buscarUltimoNodo(stNodo *ptrLista) {

    stNodo *auxSeguidor = ptrLista;

    if(ptrLista != NULL) while(auxSeguidor->ptrSiguiente != NULL) auxSeguidor = auxSeguidor->ptrSiguiente;

    return auxSeguidor;
}

stNodo *agregarNodoAlFinal(stNodo *ptrLista, stNodo *nuevoNodo) {

    if(ptrLista == NULL) ptrLista = nuevoNodo;

    else {
        stNodo *ultimoNodo = buscarUltimoNodo(ptrLista);

        ultimoNodo->ptrSiguiente = nuevoNodo;
    }
    return ptrLista;
}

stNodo *agregarNodosAlFinal(stNodo *ptrLista, char rutaArchivoPersonas[]) {

    FILE *ptrArchivoPersonas = fopen(rutaArchivoPersonas, "rb");

    if(ptrArchivoPersonas == NULL) printf("Error al abrir el archivo \n");

    else {
        stPersona unaPersona;

        while(!feof(ptrArchivoPersonas)) {

            fread(&unaPersona, sizeof(stPersona), 1, ptrArchivoPersonas);
            if(!feof(ptrArchivoPersonas)) ptrLista = agregarNodoAlFinal(ptrLista, crearNodo(unaPersona));
        }
    fclose(ptrArchivoPersonas);
    }
    return ptrLista;
}

stNodo *agregarNodoEnOrden(stNodo *ptrLista, stNodo *nuevoNodo) {

    if(ptrLista == NULL) ptrLista = nuevoNodo;

    else {
        if(strcmp(nuevoNodo->infoPersona.nombreYapellido, ptrLista->infoPersona.nombreYapellido) < 0) ptrLista = agregarNodoAlPrincipio(ptrLista, nuevoNodo);

        else {

            stNodo *auxAnterior = ptrLista;
            stNodo *auxSeguidor = ptrLista->infoPersona.nombreYapellido;

            while((auxSeguidor != NULL) && (strcmp(nuevoNodo->infoPersona.nombreYapellido, auxSeguidor->infoPersona.nombreYapellido) > 0)) {
                auxAnterior = auxSeguidor;
                auxSeguidor = auxSeguidor->ptrSiguiente;
            }
            nuevoNodo->ptrSiguiente = auxSeguidor;
            auxAnterior->ptrSiguiente = nuevoNodo;
        }
    }
    return ptrLista;
}

stNodo *borrarNodoPorNombre(stNodo *ptrLista, char nombre[]) {

    stNodo *auxSeguidor;
    stNodo *auxAnterior;

    if(ptrLista == NULL) return ptrLista;

    else {

        if(strcmp(ptrLista->infoPersona.nombreYapellido, nombre) == 0) {
            ptrLista = borrarNodoAlPrincipio(ptrLista);
            return ptrLista;

        }else {
            auxSeguidor = ptrLista;

            while((auxSeguidor != NULL) && (strcmp(auxSeguidor->infoPersona.nombreYapellido, nombre) != 0)) {
                auxAnterior = auxSeguidor;
                auxSeguidor = auxSeguidor->ptrSiguiente;
            }
            if(auxSeguidor != NULL) {
                auxAnterior->ptrSiguiente = auxSeguidor->ptrSiguiente;
                free(auxSeguidor);
                auxSeguidor = NULL;
            }
        }
    }
    return ptrLista;
}

stNodo *borrarNodoAlPrincipio(stNodo *ptrLista) {

    if(ptrLista == NULL) return ptrLista;

    else {
        stNodo *auxLista = ptrLista;
        ptrLista = ptrLista->ptrSiguiente;
        free(auxLista);
        auxLista = NULL;
    }
    return ptrLista;
}

stNodo *agregarNodosEnOrden(stNodo *ptrLista, char rutaArchivoPersonas[]) {

    FILE *ptrArchivoPersonas = fopen(rutaArchivoPersonas, "rb");

    if(ptrArchivoPersonas == NULL) printf("Error al abrir el archivo \n");

    else {
        stPersona unaPersona;

        while(!feof(ptrArchivoPersonas)) {

            fread(&unaPersona, sizeof(stPersona), 1, ptrArchivoPersonas);
            if(!feof(ptrArchivoPersonas)) ptrLista = agregarNodoEnOrden(ptrLista, crearNodo(unaPersona));
        }
    fclose(ptrArchivoPersonas);
    }
    return ptrLista;
}

void mostrarListaRecursiva(stNodo *ptrLista) {

    if(ptrLista != NULL) {
        printf("Nombre y Apellido --> |%s|\n", ptrLista->infoPersona.nombreYapellido);
        printf("Edad --> |%i|\n\n", ptrLista->infoPersona.edad);
        mostrarListaRecursiva(ptrLista->ptrSiguiente);
    }
}

void borrarListaRecursiva(stNodo *ptrLista) {

    if(ptrLista == NULL) printf("Lista Borrada %p \n\n", ptrLista);

    else borrarListaRecursiva(ptrLista->ptrSiguiente);

    free(ptrLista);
}

stNodo *invertirLista(stNodo *ptrLista, stNodo *ptrListaInvertida) {

    stNodo *aux = ptrLista;
    stNodo *nuevoNodo;

    if(ptrListaInvertida == NULL) {

        while(aux != NULL) {
            nuevoNodo = crearNodo(aux->infoPersona);
            ptrListaInvertida = agregarNodoAlPrincipio(ptrListaInvertida, nuevoNodo);
            aux = aux->ptrSiguiente;
        }
    }
    nuevoNodo = NULL;
    free(nuevoNodo);
    borrarListaRecursiva(ptrLista);

    return ptrListaInvertida;
}

int buscarDatoLista(stNodo *ptrLista, int edad) {

    int flag = 0;
    stNodo *aux = ptrLista;
    while(aux != NULL){

        if(aux->infoPersona.edad == edad) {
            flag = 1;
            aux = aux->ptrSiguiente;

        }else aux = aux->ptrSiguiente;
    }
    return flag;
}

stNodo *insertarNodosALista3(stNodo *lista1, stNodo *lista2, stNodo *lista3){

    if(lista3 == NULL){
        if(lista1->infoPersona.edad < lista2->infoPersona.edad){
        lista3 = lista1;
        lista1 = lista1->ptrSiguiente;
        }else{
        lista3 = lista2;
        lista2 = lista2->ptrSiguiente;
        }
    }
    stNodo *auxLista3 = lista3;
    while(lista1 != NULL && lista2 != NULL){

        if(lista1->infoPersona.edad < lista2->infoPersona.edad){
            auxLista3->ptrSiguiente = lista1;
            lista1 = lista1->ptrSiguiente;
        }else{
            auxLista3->ptrSiguiente = lista2;
            lista2 = lista2->ptrSiguiente;
            }
        auxLista3 = auxLista3->ptrSiguiente;
    }

    if(lista1 == NULL) auxLista3 = lista2;
    else auxLista3 = lista1;

    return lista3;
}



