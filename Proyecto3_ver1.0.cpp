#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <sstream>
#include <random>
#include <map>
#include <unordered_set>
//#include <variant>
using namespace std;


int numeroMinModo1; 
int numeroMaxModo1;
int numeroMinModo2; 
int numeroMaxModo2;
int numeroMinModo3; 
int numeroMaxModo3;
map<string,double> tiemposAlgoritmos;

using std::cout;
using std::endl;
using std::chrono::high_resolution_clock;
using std::chrono::duration;
using std::chrono::duration_cast;

void heapifyInverso(vector<int>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest]) // Cambiar de "<" a ">"
        largest = left;

    if (right < n && arr[right] > arr[largest]) // Cambiar de "<" a ">"
        largest = right;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapifyInverso(arr, n, largest);
    }
}

void heapSortInverso(vector<int>& arr) {
    int n = arr.size();

    for (int i = n / 2 - 1; i >= 0; i--)
        heapifyInverso(arr, n, i);

    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapifyInverso(arr, i, 0);
    }
}

void heapify(vector<int>& arr, int n, int i) {
    int largest = i; // Inicializa el nodo raíz como el más grande
    int left = 2 * i + 1; // Índice del hijo izquierdo
    int right = 2 * i + 2; // Índice del hijo derecho

    // Si el hijo izquierdo es más grande que la raíz
    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    // Si el hijo derecho es más grande que la raíz o el hijo izquierdo
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    // Si se encuentra un nodo más grande que la raíz, se intercambia y se continúa heapificando
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(vector<int>& arr) {
    int n = arr.size();

    // Construye el heap máximo (ordenación del montículo)
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }

    // Extrae los elementos uno a uno del montículo
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

auto timeHeapSort(vector<int>& arr,int Modo) {
    if(Modo==1)    // Ascendente
    {
        auto start = high_resolution_clock::now();
    
         heapSort(arr);
    
        auto end = high_resolution_clock::now();
        return duration_cast<duration<double>>(end - start);
    }
    if(Modo==2)    // Descendente
    {
        auto start = high_resolution_clock::now();
    
         heapSortInverso(arr);
    
        auto end = high_resolution_clock::now();
        return duration_cast<duration<double>>(end - start);
    }
}

int partitionInvertido(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] >= pivot) { // Cambiar de "<=" a ">="
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSortInvertido(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partitionInvertido(arr, low, high);

        quickSortInvertido(arr, low, pi - 1);
        quickSortInvertido(arr, pi + 1, high);
    }
}

int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

auto timeQuickSort(vector<int>& arr,int Modo) {
    if(Modo==1) // Ascendente
    {
        auto start = high_resolution_clock::now();
    
        quickSort(arr,0,arr.size()-1);
    
        auto end = high_resolution_clock::now();
        return duration_cast<duration<double>>(end - start);
    }
    if(Modo==2) // Descendente
    {
        auto start = high_resolution_clock::now();
    
        quickSortInvertido(arr,0,arr.size()-1);
    
        auto end = high_resolution_clock::now();
        return duration_cast<duration<double>>(end - start);
    }
}

void merge(vector<int>& arr, int left, int middle, int right) {
    int n1 = middle - left + 1;
    int n2 = right - middle;

    // Crear subvectores temporales
    vector<int> L(n1), R(n2);

    // Copiar los datos a los subvectores temporales
    for (int i = 0; i < n1; i++) {
        L[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arr[middle + 1 + j];
    }

    // Combinar los subvectores temporales en el vector original
    int i = 0; // Índice inicial del subvector izquierdo
    int j = 0; // Índice inicial del subvector derecho
    int k = left; // Índice inicial del vector combinado

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copiar los elementos restantes del subvector izquierdo, si los hay
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copiar los elementos restantes del subvector derecho, si los hay
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}
void mergeInvertido(vector<int>& arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;

    while (i < n1 && j < n2) {
        if (L[i] >= R[j]) { // Cambiar de "<=" a ">="
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}
void mergeSortInvertido(vector<int>& arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        mergeSortInvertido(arr, l, m);
        mergeSortInvertido(arr, m + 1, r);
        mergeInvertido(arr, l, m, r);
    }
}

void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int middle = left + (right - left) / 2;

        // Ordenar la primera y segunda mitad del vector
        mergeSort(arr, left, middle);
        mergeSort(arr, middle + 1, right);

        // Combinar las mitades ordenadas
        merge(arr, left, middle, right);
    }
}

auto timeMergeSort(vector<int>& arr,int Modo) {
    if(Modo==1)    // Ascendente
    {
        auto start = high_resolution_clock::now();
    
        mergeSort(arr,0,arr.size()-1);
    
        auto end = high_resolution_clock::now();
        return duration_cast<duration<double>>(end - start);
    }else if (Modo==2){ //Descendente
        auto start = high_resolution_clock::now();
    
        mergeSortInvertido(arr,0,arr.size()-1);
    
        auto end = high_resolution_clock::now();
        return duration_cast<duration<double>>(end - start);
    }else{
        auto start = high_resolution_clock::now();
    
        //cout no se ingreso un numero valido
    
        auto end = high_resolution_clock::now();
        return duration_cast<duration<double>>(end - start);
    }
    
}

void shellSort(vector<int>& arr) {
    int n = arr.size();

    // Calcula el tamaño del incremento inicial (gap)
    int gap = n / 2;

    while (gap > 0) {
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j = i;

            // Inserta el elemento en su posición correcta dentro del subarreglo ordenado
            while (j >= gap && arr[j - gap] > temp) {
                arr[j] = arr[j - gap];
                j -= gap;
            }

            arr[j] = temp;
        }

        // Reduce el tamaño del gap para la siguiente iteración
        gap /= 2;
    }
}

void shellSortInverso(vector<int>& arr) {
    int n = arr.size();

    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j = i;

            while (j >= gap && arr[j - gap] < temp) { // Cambiar de ">" a "<"
                arr[j] = arr[j - gap];
                j -= gap;
            }

            arr[j] = temp;
        }
    }
}

auto timeShellSort(vector<int>& arr, int Modo) {
    if(Modo ==1)  // Ascendente
    {
        auto start = high_resolution_clock::now();
    
        shellSort(arr);
    
        auto end = high_resolution_clock::now();
        return duration_cast<duration<double>>(end - start);
    }
    if(Modo ==2)  // Ascendente
    {
        auto start = high_resolution_clock::now();
    
        shellSortInverso(arr);
    
        auto end = high_resolution_clock::now();
        return duration_cast<duration<double>>(end - start);
    }
}

void insertionSort(vector<int>& arr) {
    int n = arr.size();

    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        // Desplaza los elementos mayores que la clave hacia la derecha
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = key;
    }
}

void insertionSortInverso(vector<int>& arr) {
    int n = arr.size();

    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] < key) { // Cambiar de ">" a "<"
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = key;
    }
}

auto timeInsertionSort(vector<int>& arr,int Modo) {
    if(Modo ==1)// Ascendente
    {
        auto start = high_resolution_clock::now();
    
    insertionSort(arr);
    
    auto end = high_resolution_clock::now();
    return duration_cast<duration<double>>(end - start);
    }
    if(Modo ==2)//Descendente
    {
        auto start = high_resolution_clock::now();
    
    insertionSortInverso(arr);
    
    auto end = high_resolution_clock::now();
    return duration_cast<duration<double>>(end - start);
    }
    
}

void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    bool swapped;

    for (int i = 0; i < n - 1; i++) {
        swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }

        // Si no hubo intercambios en esta pasada, el vector ya está ordenado
        if (!swapped)
            break;
    }
}

void MostrarResultados(vector<double>& arr, map<string,double>& tiempos ) {
    int n = arr.size();
    bool swapped;

    for (int i = 0; i < n - 1; i++) {
        swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (swapped==false)
        {
            break;
        }
    }
    for (int i = 0; i < 3; i++)
    {
        for (const auto& pair : tiempos)
        {
            const string& key = pair.first;
            double value = pair.second;
         //           cout << i <<"tine el valor de " <<pair.first <<"en segundo es " << pair.second <<" seconds" << endl;
            if(value == arr[i] )
            {
                cout << i <<"._" << key <<" with " << value <<" seconds" << endl;
            }
        }             
    }       
}

void bubbleSortInverso(vector<int>& arr) {
    int n = arr.size();
    bool swapped;

    for (int i = 0; i < n - 1; i++) {
        swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] < arr[j + 1]) { // Modificación: cambiar el operador de comparación
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }

        if (!swapped)
            break;
    }
}

auto timeBubbleSort(vector<int>& arr, int Modo) {
    if(Modo ==1) //Ascendente
    {
        auto start = high_resolution_clock::now();
    
        bubbleSort(arr);
    
        auto end = high_resolution_clock::now();
        return duration_cast<duration<double>>(end - start);
    }
    if(Modo ==2) //Descendente
    {
        auto start = high_resolution_clock::now();
    
        bubbleSortInverso(arr);
    
        auto end = high_resolution_clock::now();
        return duration_cast<duration<double>>(end - start);
    }
    

    
}

void selectionSort(vector<int>& arr) {
    int n = arr.size();

    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;

        // Encuentra el índice del elemento mínimo en el subarreglo sin ordenar
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }

        // Intercambia el elemento mínimo con el elemento en la posición actual
        swap(arr[i], arr[minIndex]);
    }
}

void selectionSortInverso(vector<int>& arr) {
    int n = arr.size();

    for (int i = 0; i < n - 1; i++) {
        int max_idx = i; // Cambiar de min_idx a max_idx

        for (int j = i + 1; j < n; j++) {
            if (arr[j] > arr[max_idx]) // Cambiar de "<" a ">"
                max_idx = j;
        }

        swap(arr[i], arr[max_idx]); // Cambiar de min_idx a max_idx
    }
}

auto timeSelectionSort(vector<int>& arr,int Modo) {
    if(Modo==1) //Ascendente
    {
    auto start = high_resolution_clock::now();
    
     selectionSort(arr);
    
    auto end = high_resolution_clock::now();
    return duration_cast<duration<double>>(end - start);
    }
    if(Modo==2) //Descendente
    {
    auto start = high_resolution_clock::now();
    
     selectionSortInverso(arr);
    
    auto end = high_resolution_clock::now();
    return duration_cast<duration<double>>(end - start);
    }
}


int generarNumeroAleatorio(int min,int max) {
    random_device rd; // Generador de numeros aleatorios
    mt19937 gen(rd()); // Semilla para el generador
    uniform_int_distribution<int> distribucion(min, max); // Rango de numeros

 
    return distribucion(gen); // Genera y devuelve el numero aleatorio
}


vector<int> EliminarDuplicadosConAleatorio(const vector<int>& arregloOriginal) {
    vector<int> arregloSinDuplicados;
    unordered_set<int> numerosVistos;

    for (int num : arregloOriginal) {
        // Verificar si el número ya está presente en el nuevo vector
        if (numerosVistos.find(num) == numerosVistos.end()) {
            arregloSinDuplicados.push_back(num);
            numerosVistos.insert(num);
        } else {
            // Generar un número aleatorio que no esté en el nuevo vector
            int aleatorio;
            do {
                aleatorio = generarNumeroAleatorio(0,20000);
            } while (numerosVistos.find(aleatorio) != numerosVistos.end());

            arregloSinDuplicados.push_back(aleatorio);
            numerosVistos.insert(aleatorio);
        }
    }

    return arregloSinDuplicados;
}

void ejecutarCarrera(int min, int max,int Modo,vector<int>& arregloBasico) // Rango del modo de la carrera ,MIN Y MAX YA NO SON NESESARIOS
{
    
    vector<double> resultados;
    vector<int> arregloD1(arregloBasico);
    vector<int> arregloD2(arregloBasico);
    vector<int> arregloD3(arregloBasico);
    vector<int> arregloD4(arregloBasico);
    vector<int> arregloD5(arregloBasico);
    vector<int> arregloD6(arregloBasico);
    vector<int> arregloD7(arregloBasico);
/*
    vector<int> arregloOrdenadoMayMen(arregloBasico); // arreglos originales
    vector<int> arregloOrdenadoMenMay(arregloBasico);
    vector<int> arregloAleatorio(arregloBasico);
    vector<int> arregloAleatorioNoDuplicados(arregloBasico);
*/

        auto time_taken_bubble = timeBubbleSort(arregloD1,Modo);
        tiemposAlgoritmos["Bubble Sort"] = time_taken_bubble.count();
        cout << "Bubble time: " << tiemposAlgoritmos["Bubble Sort"]  << " seconds" << endl;
        resultados.push_back(tiemposAlgoritmos["Bubble Sort"]);
    /*
        for(int i=0; i < numeroRandom; i++ )
    {
        cout <<arregloBasico[i] << " ";
    }
    */
        auto time_taken_Selection = timeSelectionSort(arregloD2,Modo);
        tiemposAlgoritmos["Selection Sort"] =time_taken_Selection.count();
        cout << "Selection time: " << tiemposAlgoritmos["Selection Sort"]  << " seconds" << endl;
        resultados.push_back(tiemposAlgoritmos["Selection Sort"]);

        auto time_taken_Insertion = timeInsertionSort(arregloD3,Modo);
        tiemposAlgoritmos["Insert Sort"] =time_taken_Insertion.count();
        cout << "Insert time: " << tiemposAlgoritmos["Insert Sort"]  << " seconds" << endl;
        resultados.push_back(tiemposAlgoritmos["Insert Sort"]);

        auto time_taken_Shell = timeShellSort(arregloD4,Modo);
        tiemposAlgoritmos["Shell Sort"] =time_taken_Shell.count();
        cout << "Shell time: " << tiemposAlgoritmos["Shell Sort"]  << " seconds" << endl;
        resultados.push_back(tiemposAlgoritmos["Shell Sort"]);

        auto time_taken_Merge = timeMergeSort(arregloD5,Modo);
        tiemposAlgoritmos["Merge Sort"] =time_taken_Merge.count();
        cout << "Merge time: " << tiemposAlgoritmos["Merge Sort"]  << " seconds" << endl;
        resultados.push_back(tiemposAlgoritmos["Merge Sort"]);

        auto time_taken_Quick = timeMergeSort(arregloD6,Modo);
        tiemposAlgoritmos["Quick Sort"] =time_taken_Quick.count();
        cout << "Quick time: " << tiemposAlgoritmos["Quick Sort"]  << " seconds" << endl;
        resultados.push_back(tiemposAlgoritmos["Quick Sort"]);

        auto time_taken_Heap = timeHeapSort(arregloD7,Modo);
        tiemposAlgoritmos["Heap Sort"] =time_taken_Heap.count();
        cout << "Heap time: " << tiemposAlgoritmos["Heap Sort"]  << " seconds" << endl;
        resultados.push_back(tiemposAlgoritmos["Heap Sort"]);

        MostrarResultados(resultados,tiemposAlgoritmos);
        cout << endl;

}

void igualarArreglos(const vector<int>& arregloOriginal, vector<int>& arregloDestino, int REsize) {
    //int tamArreglo = arregloOriginal.size();    
    arregloDestino.resize(REsize); 

    for (int i = 0; i < REsize; i++) {
        arregloDestino[i] = arregloOriginal[i];
    }
}

int main(){
	int op=0;
  //  vector<double> resultados;
    tiemposAlgoritmos.insert(make_pair("Bubble Sort",1));
    tiemposAlgoritmos.insert(make_pair("Selection Sort",2));
    tiemposAlgoritmos.insert(make_pair("Insert Sort",3));
    tiemposAlgoritmos.insert(make_pair("Shell Sort",4));
    tiemposAlgoritmos.insert(make_pair("Merge Sort",5));
    tiemposAlgoritmos.insert(make_pair("Quick Sort",6));
    tiemposAlgoritmos.insert(make_pair("Heap Sort",7));
    
    ifstream archivo("Config.txt"); // Abre el archivo en modo lectura
    if (archivo.is_open()) { // Comprueba si el archivo se abri� correctamente
        string linea;
        
        
        getline(archivo, linea); // Ignora la primera l�nea
		getline(archivo, linea); // Obtiene la segunda linea        
        stringstream ss(linea);        
        getline(ss, linea,',');
        numeroMinModo1 = stoi(linea);        
        getline(ss, linea);
        numeroMaxModo1 = stoi(linea);
        
        getline(archivo, linea); // Obtiene la Tercera linea  
        stringstream ss2(linea);  //Dividir la linea 3
        getline(ss2, linea,',');
        numeroMinModo2 = stoi(linea);        
        getline(ss2, linea);
        numeroMaxModo2 = stoi(linea);
        
        getline(archivo, linea); // Obtiene la Tercera linea  
        stringstream ss3(linea);  //Dividir la linea 3
        getline(ss3, linea,',');
        numeroMinModo3 = stoi(linea);        
        getline(ss3, linea);
        numeroMaxModo3 = stoi(linea);
			
        archivo.close(); // Cierra el archivo despues de leerlo
        // Hacer algo con el numero global
        
        cout << "El Rango Min del Modo 1 es: " << numeroMinModo1 << endl;
        cout << "El Rango Max del Modo 1 es: " << numeroMaxModo1 << endl;
        
        cout << "El Rango Min del Modo 2 es: " << numeroMinModo2 << endl;
        cout << "El Rango Max del Modo 2 es: " << numeroMaxModo2 << endl;
        
        cout << "El Rango Min del Modo 3 es: " << numeroMinModo3 << endl;
        cout << "El Rango Max del Modo 3 es: " << numeroMaxModo3 << endl;
               
    } else {
        cout << "No se pudo abrir el archivo." << endl;
    }    
    //int numeroRandom = generarNumeroAleatorio(numeroMinModo1,numeroMaxModo1);
       
    //cout << "El numero Random es: " << numeroRandom << endl;
    int numeroRandom = generarNumeroAleatorio(numeroMinModo1,numeroMaxModo1);
    cout << "El numero Random1 es: " << numeroRandom << endl; //numero en el cual se creara el arreglo

    vector<int> arregloOriginal;
    vector<int> arregloDuplidado;
    

    for(int i=0; i < numeroRandom; i++ )    
    {
        arregloOriginal.push_back(generarNumeroAleatorio(0,5000)); // Rango de los numeros a crear
    //    cout <<arregloBasico[i] << " ";
    }

    cout << "Carrera de algotitmos" << endl;
    cout << "1. Ascendente " << endl;
    cout << "2. Descendente " << endl;
    cout << "Opcion Elegida: " << endl;
    cin >> op;


    
    if(op == 1) //Ascendente
    {
        //Duplicar el arreglo, Ordenar el arreglo, entregar el arreglo duplicado
        cout << "Carrera por el Tablero: Modo Ordenado" << endl;
        igualarArreglos(arregloOriginal,arregloDuplidado,numeroRandom);
        insertionSort(arregloDuplidado);
        ejecutarCarrera(numeroMinModo1,numeroMaxModo1,1,arregloDuplidado);

        cout << "Carrera por el Tablero: Modo Inverso" << endl;
        igualarArreglos(arregloOriginal,arregloDuplidado,numeroRandom);
        insertionSortInverso(arregloDuplidado);
        ejecutarCarrera(numeroMinModo1,numeroMaxModo1,1,arregloDuplidado);

        cout << "Carrera por el Tablero: Modo Aleatorio" << endl;
        igualarArreglos(arregloOriginal,arregloDuplidado,numeroRandom);
        ejecutarCarrera(numeroMinModo1,numeroMaxModo1,1,arregloDuplidado);

        cout << "Carrera por el Tablero: Modo Aleatorio Sin Duplicados" << endl;
        igualarArreglos(arregloOriginal,arregloDuplidado,numeroRandom);
        arregloDuplidado = EliminarDuplicadosConAleatorio(arregloDuplidado);
        ejecutarCarrera(numeroMinModo1,numeroMaxModo1,1,arregloDuplidado);
        

        numeroRandom = generarNumeroAleatorio(numeroMinModo2,numeroMaxModo2);// CArrera Modo 2
        cout << "El numero Random es: " << numeroRandom << endl; //numero en el cual se creara el arreglo

        cout << "Carrera por las Aldeas: Modo Ordenado" << endl; 
        igualarArreglos(arregloOriginal,arregloDuplidado,numeroRandom);
        insertionSort(arregloDuplidado);
        ejecutarCarrera(numeroMinModo2,numeroMaxModo2,1,arregloDuplidado);

        for(int i=0; i < numeroRandom; i++ )    
        {
       // arregloOriginal.push_back(generarNumeroAleatorio(0,500)); // Rango de los numeros a crear
            cout <<arregloDuplidado[i] << " ";
        }
        cout << "Carrera por las Aldeas: Modo Inverso" << endl;
        igualarArreglos(arregloOriginal,arregloDuplidado,numeroRandom);
        insertionSortInverso(arregloDuplidado);
        ejecutarCarrera(numeroMinModo1,numeroMaxModo1,1,arregloDuplidado);

        cout << "Carrera por las Aldeas: Modo Aleatorio" << endl;
        igualarArreglos(arregloOriginal,arregloDuplidado,numeroRandom);
        ejecutarCarrera(numeroMinModo1,numeroMaxModo1,1,arregloDuplidado);

        cout << "Carrera por las Aldeas: Modo Aleatorio Sin Duplicados" << endl;
        igualarArreglos(arregloOriginal,arregloDuplidado,numeroRandom);
        arregloDuplidado = EliminarDuplicadosConAleatorio(arregloDuplidado);
        ejecutarCarrera(numeroMinModo1,numeroMaxModo1,1,arregloDuplidado);

        for (int i = 1; i < 16; i++) //CARRERA MODO 3
        {

            numeroRandom = generarNumeroAleatorio(numeroMinModo3,numeroMaxModo3);// CArrera Modo 2
            cout << "El numero Random es: " << numeroRandom << endl; //numero en el cual se creara el arreglo
            cout << "La categoria " << i  << endl; //numero en el cual se creara el arreglo

            cout << "Carrera por las Aldeas: Modo Ordenado categoria " << i  << endl; 
            igualarArreglos(arregloOriginal,arregloDuplidado,numeroRandom);
            insertionSort(arregloDuplidado);
            ejecutarCarrera(numeroMinModo3,numeroMaxModo3,1,arregloDuplidado);

            for(int i=0; i < numeroRandom; i++ )    
            {
        // arregloOriginal.push_back(generarNumeroAleatorio(0,500)); // Rango de los numeros a crear
             //   cout <<arregloDuplidado[i] << " ";
            }
            cout << "Carrera por las Aldeas: Modo Inverso categoria " << i  << endl;
            igualarArreglos(arregloOriginal,arregloDuplidado,numeroRandom);
            insertionSortInverso(arregloDuplidado);
            ejecutarCarrera(numeroMinModo3,numeroMaxModo3,1,arregloDuplidado);

            cout << "Carrera por las Aldeas: Modo Aleatorio categoria " << i << endl;
            igualarArreglos(arregloOriginal,arregloDuplidado,numeroRandom);
            ejecutarCarrera(numeroMinModo3,numeroMaxModo3,1,arregloDuplidado);

            cout << "Carrera por las Aldeas: Modo Aleatorio Sin Duplicados categoria " << i << endl;
            igualarArreglos(arregloOriginal,arregloDuplidado,numeroRandom);
            arregloDuplidado = EliminarDuplicadosConAleatorio(arregloDuplidado);
            ejecutarCarrera(numeroMinModo3,numeroMaxModo3,1,arregloDuplidado);   
        }
    }
    if(op == 2) // Descendente
    {
        ejecutarCarrera(numeroMinModo1,numeroMaxModo1,2,arregloOriginal);
	}

    return 0;   
    
}
