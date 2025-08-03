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
int elegirMetodo();
void cargarAleatorio(int v[], int &n);
void imprimirVector(int v[], int n);
void ejecutarMetodo(int v[], int n, int codMetodo);

void bubbleSort(int v[], int n);
void selectionSort(int v[], int n);
void insertionSort(int v[], int n);
void mergeSort(int v[], int n);
void quickSort(int v[], int n);

main() {
	printf("========== TRABAJO FINAL INTEGRADOR - AyED 2025 ==========\n");
	int v[100], n;
	cargarAleatorio(v, n);
	
	printf("El vector generado es: \n");
	imprimirVector(v, n);
	
	int codMetodo = elegirMetodo();
	ejecutarMetodo(v, n, codMetodo);
}

void cargarAleatorio(int v[], int &n) {
	do {
		printf("Ingrese cantidad de elementos para el vector (entre %d y %d):", min, max);
		scanf("%d", &n);
		if(n < min || n > max) {
			printf("ERROR: Ingrese un valor entre %d y %d.\n", min, max);
		}
	} while (n < min || n > max);

	
	for (int i = 0; i < n; i++) {
		v[i] = rand() % 100; // Asignamos un valor aleatorio entre 0 y 99
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

int elegirMetodo() {
	int opcion;
	
	printf("========== METODOS DE ORDENAMIENTO ==========\n");
	for (int i = 0; i < cOpciones; i++) { // Generamos las opciones de forma dinamica.
		printf("[%d]. %s\n", i, metodos[i]);
	}
    
    do {
    	printf("Seleccione una opcion: ");
    	scanf("%d", &opcion);
    	if(opcion < 0 || opcion > 4){
			printf("El metodo elegido no existe, seleccione uno de la lista.\n");
		}
	} while(opcion < 0 || opcion > 4);
    
	return opcion;
}

void ejecutarMetodo(int v[], int n, int codMetodo) {
	printf("El metodo elegido es: %s.\n", metodos[codMetodo]);
	
    switch (codMetodo) {
        case 0:
            bubbleSort(v, n);
            break;
        case 1:
            selectionSort(v, n);
            break;
        case 2:
            insertionSort(v, n);
            break;
        case 3:
            mergeSort(v, n);
            break;
        case 4:
            quickSort(v, n);
            break;
    }
}

void bubbleSort(int v[], int n) {
	int intercambios = 0, comparaciones = 0;
	for (int i = 0; i < n-1; i++) { // Iteramos hasta el penultimo valor, ya que debemos comparar con i+1.
		int desordenado = 0;
		for (int j = 0; j < n-i-1; j++) { // Usando ifs anidados, evitamos volver a validar valores que ya estan ordenados.
			if(v[j] > v[j+1]) {			
				int aux = v[j];
				v[j] = v[j+1];
				v[j+1] = aux;
				
				desordenado = 1;
				comparaciones++;
				intercambios += 2;
			}
		}
		if (desordenado = 0) {
			break;
		}
	}
	printf("El vector ordenado es: \n");
	imprimirVector(v, n);
	printf("Cantidad de comparaciones: %d.\n", comparaciones);
	printf("Cantidad de intercambios: %d.\n", intercambios);
}

void selectionSort(int v[], int n) {
	int comparaciones = 0, intercambios = 0;
	for (int i = 0; i < n - 1; i++) {
		for (int j = i + 1; j < n; j++) {
			if (v[j] < v[min]) { // Comparamos el elemento actual con el presente en el indice menor y reemplazamos.
				min = j;
			}
		}
		
		if(min != i) { // Verificamos si corresponde hacer el intercambio
			aux = v[i];
			v[i] = v[min];
			v[min] = aux;
		}
	}
	
	printf("El vector ordenado es: \n");
	imprimirVector(v, n);
}

void insertionSort(int v[], int n) {
	printf("Ordenado con insertionSort\n");
}
	
void mergeSort(int v[], int n) {
	printf("Ordenado con mergeSort\n");
}
void quickSort(int v[], int n) {
	printf("Ordenado con quickSort\n");
}