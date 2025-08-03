#include <stdio.h> // Libreria estandar para usar printf() y scanf().
#include <stdlib.h> // Libreria para hacer uso de la funcion rand().

// Variables globales
const char *metodos[] = { // Guardamos los metodos en un arreglo para poder generar las opciones dinamicamente y acceder a sus valores a traves de un indice.
    "Bubble Sort",
    "Selection Sort",
    "Insertion Sort",
    "MergeSort",
    "QuickSort"
};

int cOpciones = 5; // Podriamos obtener la cantiodad de opciones de forma dinamica con sizeof(), pero como sabemos que es estatica, directamente la declararemos.
int min = 5, max = 25; // Variables globales para controlar la cantidad de elementos minimos y maximos en el vector.

// Prototipo de funciones
void iniciarOrdenamiento();
void cargarAleatorio(int v[], int &n);
int elegirMetodo();
void ejecutarMetodo(int v[], int n, int codMetodo);

void imprimirVector(int v[], int n);
void imprimirOrdenado(int v[], int n, int comparaciones, int intercambios);
void intercambiar(int v[], int a, int b);

void bubbleSort(int v[], int n);
void selectionSort(int v[], int n);
void insertionSort(int v[], int n);
void mergeSort(int v[], int n, int &comparaciones, int &intercambios);
void merge(int v[], int n, int izq[], int der[], int &comparaciones, int &intercambios);
void quickSort(int v[], int n);

main() {
	printf("========== TRABAJO FINAL INTEGRADOR - AyED 2025 ==========\n");
	iniciarOrdenamiento();	
}

void iniciarOrdenamiento() {
	int v[100], n;
	cargarAleatorio(v, n);
	
	printf("El vector generado es: \n");
	imprimirVector(v, n);
	
	int codMetodo = elegirMetodo();
	ejecutarMetodo(v, n, codMetodo);
	
    int opcion;
    printf("> Ordenamiento finalizado. Ingrese 1 para repetir o cualquier tecla para salir: ");
    scanf("%d", &opcion);
    printf("\n");
    
    if(opcion == 1) {
    	printf("================================================\n");
    	iniciarOrdenamiento();
	}
}

void cargarAleatorio(int v[], int &n) {
	do {
		printf("> Ingrese cantidad de elementos para el vector (entre %d y %d):", min, max);
		scanf("%d", &n);
		if(n < min || n > max) {
			printf("ERROR: Ingrese un valor entre %d y %d.\n", min, max);
		}
	} while (n < min || n > max);

	
	for (int i = 0; i < n; i++) {
		v[i] = rand() % 100; // Asignamos un valor aleatorio entre 0 y 99
	}
}

int elegirMetodo() {
	int opcion;
	
	printf("\n========== METODOS DE ORDENAMIENTO ==========\n");
	for (int i = 0; i < cOpciones; i++) { // Generamos las opciones de forma dinamica.
		printf("[%d]. %s\n", i+1, metodos[i]);
	}
    
    do {
    	printf("> Seleccione una opcion: ");
    	scanf("%d", &opcion);
    	if(opcion < 1 || opcion >= cOpciones){
			printf("El metodo elegido no existe, seleccione uno de la lista.\n");
		}
	} while(opcion < 1 || opcion >= cOpciones);
    
	return opcion - 1;
}

void ejecutarMetodo(int v[], int n, int codMetodo) {
	printf("El metodo elegido es: %s.\n", metodos[codMetodo]);
	int comparaciones = 0, intercambios = 0;
	
    switch (codMetodo) {
        case 0:
            bubbleSort(v, n);
            break;
            selectionSort(v, n);
            break;
        case 2:
        case 1:
            insertionSort(v, n);
            break;
        case 3:
            mergeSort(v, n, comparaciones, intercambios);
            imprimirOrdenado(v, n, comparaciones, intercambios);
            break;
        case 4:
            quickSort(v, n);
            break;
    }
}

void imprimirVector(int v[], int n) {
	printf("[");
	for (int i = 0; i < n; i++) {
		// Imprimimos el valor en la misma linea, y si no es el ultimo elemento, agregamos una coma.
		printf("%d", v[i]);
		if (i != n - 1) {
			printf(",")	;
		}
	}
	printf("]\n");
}

void imprimirOrdenado(int v[], int n, int comparaciones, int intercambios) {
	printf("El vector ordenado es: \n");
	imprimirVector(v, n);
	printf("Cantidad de comparaciones: %d.\n", comparaciones);
	printf("Cantidad de intercambios: %d.\n\n", intercambios);
}

void intercambiar(int v[], int a, int b) {
	int aux = v[a];
	v[a] = v[b];
	v[b] = aux;
}

void bubbleSort(int v[], int n) {
	int intercambios = 0, comparaciones = 0;
	
	for (int i = 0; i < n-1; i++) { // Iteramos hasta el penultimo valor, ya que debemos comparar con i+1.
		int desordenado = 0;
		
		for (int j = 0; j < n-i-1; j++) { // Usando ifs anidados, evitamos volver a validar valores que ya estan ordenados.
		comparaciones++;
		
			if(v[j] > v[j+1]) { // Si el numero en j+i es mayor, realizamos el intercambio
				intercambiar(v, j, j+1);
				
				desordenado = 1; // Marcamos que el vector continua desordenado para seguir iterando.
				intercambios++;
			}
		}
		
		if (desordenado = 0) { // Si el vector se encuentra en orden, cortamos el for para evitar evaluaciones innecesarias.
			break;
		}
	}
	
	imprimirOrdenado(v, n, comparaciones, intercambios);
}

void selectionSort(int v[], int n) {
	int comparaciones = 0, intercambios = 0;
	
	for (int i = 0; i < n - 1; i++) { // Iteramos desde el inicio hasta el penultimo valor, ya que evaluaremos con i+1.
		int min = i, aux; // Establecemos el indice menor como i al inicio.
		
		for (int j = i + 1; j < n; j++) {
			comparaciones++;
			if (v[j] < v[min]) { // Comparamos el elemento actual con el presente en el indice menor y reemplazamos si corresponde.
				min = j;
			}
		}
		
		if(min != i) { // Verificamos si corresponde hacer el intercambio.
			intercambiar(v, i, min);
			intercambios++;
		}
	}
	
	imprimirOrdenado(v, n, comparaciones, intercambios);
}

void insertionSort(int v[], int n) {
	int comparaciones = 0, intercambios = 0;
	
	for(int i = 1; i < n; i++) { // Como debemos comparar "hacia atras" empezamos en el indice 1, caso contrario estariamos al inicio del vector.
		int valorEvaluado = v[i];
		int j = i - 1;
		
		// Iteramos de forma descendente desde el valor anterior al evaluado, hasta el inicio del vector, o hasta encontrar un elemento menor o igual al evaluado.
		while(j >=0 && v[j] > valorEvaluado) {
			v[j+1] = v[j]; // Si el elemento anterior al evaluado es mayor, lo movemos hacia la derecha.
			j--;
			comparaciones++;
			intercambios++;
		}
		
		intercambios++;
		v[j+1] = valorEvaluado; // Guardamos el valor evaluado en la posicion que le corresponde.
	}
	
	imprimirOrdenado(v, n, comparaciones, intercambios);
}
	
void mergeSort(int v[], int n, int &comparaciones, int &intercambios) {
	if(n < 2) { // Si tenemos un vector vacio o con un solo elemento, no necesita ordenarse.
		return;
	}
	
	int medio = n / 2; // Obtenemos el medio del vector, si el numero es impar, se redondea para abajo. EJ: 5/2 = 2.
	// Generamos dos vectores, donde copiaremos los valores a la izquierda y a la derecha respecto al medio del vector original.
	int izq[medio];
	int der[n - medio];
	
	for(int i = 0; i < medio; i++) {
		// Tomamos los elementos del vector original desde el inicio hasta el medio.
		izq[i] = v[i];
	}
	
	for (int i = medio; i < n; i++) {
		// Tomamos los elementos desde el medio en adelante. Hacemos i-medio para colocar los elementos al inicio de der[].
		der[i - medio] = v[i];
	}

	// Ordenamos cada mitad de manera recursiva.
	mergeSort(izq, medio, comparaciones, intercambios);
	mergeSort(der, n-medio, comparaciones, intercambios);
	
	// Unimos las mitades ordenadas en el vector principal.
	merge(v, n, izq, der, comparaciones, intercambios);
}

void merge(int v[], int n, int izq[], int der[], int &comparaciones, int &intercambios){
	int medio = n / 2;
	int nIzq = medio;
	int nDer = n - medio;
	
	int i=0,j=0,k=0;
	
	// Iteramos hasta quedarnos sin elementos en alguno de los vectores.
	// i -> para izquierda. j -> para derecha. k -> vector original.
	while (i < nIzq && j < nDer) {
		comparaciones++;
		if(izq[i] <= der[j]) {
			v[k] = izq[i];
			intercambios++;
			i++;
		} else {
			v[k] = der[j];
			intercambios++;
			j++;
		}
		k++;
	}
	
	// Agregamos los elementos que quedaron en alguno de los vectores.
	
	while (i < nIzq) {
		v[k] = izq[i];
		i++;
		k++;
		intercambios++;
	}
	
	while (j < nDer) {
		v[k] = der[j];
		j++;
		k++;
		intercambios++;
	}
}

void quickSort(int v[], int n) {
	printf("Ordenado con quickSort\n");
}