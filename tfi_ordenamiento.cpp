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

// Prototipo de funciones.

// Flujo del programa.
void iniciarOrdenamiento();
void cargarAleatorio(int v[], int &n);
int elegirMetodo();
void ejecutarMetodo(int v[], int n, int codMetodo);

// Utilidades.
void imprimirVector(int v[], int n);
void imprimirOrdenado(int v[], int n, int comparaciones, int intercambios);
void intercambiar(int v[], int a, int b);

// Metodos de ordenamiento.
void bubbleSort(int v[], int n);
void selectionSort(int v[], int n);
void insertionSort(int v[], int n);

void mergeSort(int v[], int n);
void mergeSortRecursion(int v[], int n, int &comparaciones, int &intercambios);
void mergeSortUnion(int v[], int n, int izq[], int der[], int &comparaciones, int &intercambios);

void quickSort(int v[], int n);
void quickSortRecursion(int v[], int inicio, int fin, int &comparaciones, int &intercambios);
int quickSortParticion(int v[], int inicio, int fin, int &comparaciones, int &intercambios);

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
    	if(opcion < 1 || opcion > cOpciones){
			printf("El metodo elegido no existe, seleccione uno de la lista.\n");
		}
	} while(opcion < 1 || opcion > cOpciones);
    
	return opcion - 1;
}

void ejecutarMetodo(int v[], int n, int codMetodo) {
	printf("El metodo elegido es: %s.\n", metodos[codMetodo]);
	
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
            mergeSort(v, n);
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

void mergeSort(int v[], int n) {
	int comparaciones = 0, intercambios = 0;
	mergeSortRecursion(v, n, comparaciones, intercambios);
	imprimirOrdenado(v, n, comparaciones, intercambios);	
}

void mergeSortRecursion(int v[], int n, int &comparaciones, int &intercambios) {
	if(n < 2) { // Si tenemos un vector vacio o con un solo elemento, no necesita ordenarse.
		return;
	}
	
	int medio = n / 2; // Obtenemos el indice del elemento medio del vector, si n es impar, el indice se redondea para abajo. EJ: 5/2 = 2.
	// Generamos dos vectores, donde copiaremos los valores a la izquierda y a la derecha respecto al elemento medio del vector original.
	// EJ: n = 5; medio = 5/2 = 2; izq[2]; der[5 - 2] -> der[3];
	int izq[medio];
	int der[n - medio];
	
	for(int i = 0; i < medio; i++) {
		// Tomamos los elementos del vector original desde el inicio hasta el elemnto medio.
		izq[i] = v[i];
	}
	
	for (int i = medio; i < n; i++) {
		// Tomamos los elementos desde el medio en adelante. Hacemos i-medio para colocar los elementos al inicio de der[].
		der[i - medio] = v[i];
	}

	// Ordenamos cada mitad de manera recursiva.
	mergeSortRecursion(izq, medio, comparaciones, intercambios);
	mergeSortRecursion(der, n-medio, comparaciones, intercambios);
	
	// Comparamos las mitades ordenadas y las vamos ordenando en el vector principal.
	mergeSortUnion(v, n, izq, der, comparaciones, intercambios);
}

void mergeSortUnion(int v[], int n, int izq[], int der[], int &comparaciones, int &intercambios){
	int medio = n / 2;
	int nIzq = medio;
	int nDer = n - medio;
	
	int i=0,j=0,k=0;
	
	// Iteramos hasta quedarnos sin elementos en alguno de los vectores.
	// i -> para izquierda. j -> para derecha. k -> vector original.
	// Colocamos el elemento menor en la posicion v[k].
	while (i < nIzq && j < nDer) {
		comparaciones++;
		if(izq[i] <= der[j]) { // Si el elemento en izq[] es menor, lo ubicamos en la posicion v[k] y continuamos con el siguiente elemento en el vector.
			v[k] = izq[i];
			intercambios++;
			i++;
		} else { // Si el elemento en der[] es menor, lo ubicamos en la posicion v[k] y continuamos con el siguiente elemento en el vector.
			v[k] = der[j];
			intercambios++;
			j++;
		}
		
		k++;
	}
	
	// Si (i < nIzq && j < nDer) no se cumple, alguno de los vectores queda con elementos, aqui sumamos el descarte a v[].
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
	int comparaciones = 0, intercambios = 0;
	quickSortRecursion(v, 0, n - 1, comparaciones, intercambios);
	imprimirOrdenado(v, n, comparaciones, intercambios);
}

void quickSortRecursion(int v[], int inicio, int fin, int &comparaciones, int &intercambios) {
	// Solo ejecutamos si hay varios elementos en el arreglo. EJ: n = 1; inicio = 0; fin = n - 1 = 0; (inicio < fin) no se cumple.
	if(inicio < fin) {
		int pivote = quickSortParticion(v, inicio, fin, comparaciones, intercambios); // Obtenemos el indice del elemento pivote luego de la particion.
		
		quickSortRecursion(v, inicio, pivote - 1, comparaciones, intercambios); // Ordenamos la parte izquierda de forma recursiva.
		quickSortRecursion(v, pivote + 1, fin, comparaciones, intercambios);  // Ordenamos la parte derecha de forma recursiva.
	}
}

int quickSortParticion(int v[], int inicio, int fin, int &comparaciones, int &intercambios) {
	int pivote = v[fin]; // Utilizamos el ultimo elemento del arreglo como nuestro pivote. Idealmente deberiamos obtenerlo de forma aleatoria.
	int i = inicio; // Indice que utilizaremos para ubicar el valor pivote al final de la particion.
	
	for (int j = i; j < fin; j++) {
		comparaciones++;
		if(v[j] <= pivote) { // Si el valor al que apuntamos en v[j] es menor al pivote, lo intercambiamos ya que debe estar a la izquierda del pivote.
			intercambiar(v, i, j);
			i++;
			intercambios++;
		}
	}
	
	intercambiar(v, i, fin); // Colocamos el pivote en la posicion v[i], de forma que todos los elementos menores queden a su izquierda, y los mayores a su derecha.
	intercambios++;
	return i; // Devolvemos la posicion del pivote.
}

