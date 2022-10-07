#include <iostream>
#include <iomanip>
#include <time.h>

void generateArray(int *array, int size, int upper_bound){
    int aux;
    for(int i{1}; i<size; i++){
        aux = rand()%50;
        *array = aux % 2 == 0 ? rand()%upper_bound : rand()%upper_bound * -1;
        array++;
    }
}

void printArray(int *array, int n){
    for(size_t i {0}; i<n; i++){
        std::cout<<*array<<" ";
        array++;
    }
}

//==========================BUBBLE SORT==========================
void bubbleSort(int *array, int n){
    int *array_ptr_buff = array;
    int *array_next{array+1};

    for(n; n>-1; n--){
        for(int i{0}; i<n-1; i++){
            if(*array > *array_next){
                int aux = *array;
                *array = *array_next;
                *array_next = aux;
            }
            array++;
            array_next++;
        }

        array = array_ptr_buff;
        array_next = array+1;
    }
}

void nBubbleSort(int *array, int n){
    int i, aux;

    for(n; n > -1; n--){
        for(i=0; i<n-1; i++){
            if(array[i] > array[i+1]){
                aux = array[i];
                array[i] = array[i+1];
                array[i+1] = aux;
            }
        }
    }
}

//==========================INSERTION SORT==========================
void insertionSort(int *array, int n){
    int i, j, aux;
    int *j_ptr{}, *j_prev_ptr{};
    
    for(i = 0; i<n-1; i++){
        j = i + 1;
        j_ptr = (array + j);
        j_prev_ptr = j_ptr - 1;
        while(j > 0 && *j_ptr < *j_prev_ptr){
            aux = *j_ptr;
            *j_ptr = *j_prev_ptr;
            *j_prev_ptr = aux;

            j--;
            j_ptr--;
            j_prev_ptr--;
        }
    }
}

void nInsertionSort(int *array, int n){
    int i, j, aux;

    for(i=0; i<n-1; i++){
        j = i + 1;
        while(j > 0 && array[j] < array[j - 1]){
            aux = array[j];
            array[j] = array[j-1];
            array[j-1] = aux;

            j--;
        }
    }
}

//==========================SELECTION SORT==========================
void selectionSort(int *array, int n){
    int *i_ptr = array;
    int *j_ptr{};
    int *aux_ptr{};
    int i, j, buff;
    for(i = 0; i<n; i++){
        aux_ptr = i_ptr;
        j_ptr = i_ptr + 1;
        for(j = i+1; j<n; j++){
            if(*j_ptr < *aux_ptr){
                aux_ptr = j_ptr;
            }
            j_ptr++;
        }

        buff = *i_ptr;
        *i_ptr = *aux_ptr;
        *aux_ptr = buff;

        i_ptr++;
    }    
}

void nSelectionSort(int *array, int n){
    int j, aux;

    for(int i{0}; i<n; i++){
        j = i+1;
        aux = i;
        for(j; j<n; j++){
            if(array[j]<array[aux]){
                aux = j;
            }
        }

        int buff = array[aux];
        array[aux] = array[i];
        array[i] = buff;
    }
}

//==========================QUICK SORT==========================
int partition(int *array, int p, int q){
    int pivot = array[(p + q) / 2];
    p--;
    q++;

    while(true){
        p++;
        while(array[p] < pivot){
            p++;
        }

        q--;
        while(array[q] > pivot){
            q--;
        }

        if(p >= q){
            return q;
        }

        int aux = array[p];
        array[p] = array[q];
        array[q] = aux;
    }
}

void quickSort(int *array, int p, int q){
    if(p < q){
        int pivot = partition(array, p, q);
        quickSort(array, p, pivot);
        quickSort(array, pivot + 1, q);
    }
}

int main(){
    int size = 10;
    clock_t start, stop;
    double time;

    std::cout<<std::fixed<<std::setprecision(4);

    //==========================BUBBLE SORT==========================
    // int *array{new int[size]};
    // generateArray(array, size, 1000);

    // std::cout<<std::setw(40)<<std::left<<"Unsorted array: ";
    // printArray(array, size);

    // start = clock();
    // nBubbleSort(array, size);
    // stop = clock();

    // std::cout<<std::endl<<std::setw(40)<<std::left<<"Array sorted with bubbleSort: ";
    // printArray(array, size);

    // time = (double) (stop - start) / CLOCKS_PER_SEC;
    // std::cout<<std::endl<<std::setw(40)<<std::left<<"Time (bubbleSort): "<<time<<"s."<<std::endl<<std::endl;

    // delete [] array;

    //==========================INSERTION SORT==========================
    // *array = new int[size];

    // generateArray(array, size, 1000);

    // // std::cout<<std::setw(40)<<std::left<<"Unsorted array: ";
    // // printArray(array, size);

    // start = clock();
    // insertionSort(array, size);
    // stop = clock();

    // // std::cout<<std::endl<<std::setw(40)<<std::left<<"Array sorted with insertionSort: ";
    // // printArray(array, size);

    // time = (double) (stop - start) / CLOCKS_PER_SEC;
    // std::cout<<std::endl<<std::setw(40)<<std::left<<"Time (insertionSort): "<<time<<"s."<<std::endl<<std::endl;

    // delete array;

    //==========================SELECTION SORT==========================
    // array = new int[size];

    // generateArray(array, size, 1000);

    // // std::cout<<std::setw(40)<<std::left<<"Unsorted array: ";
    // // printArray(array, size);

    // start = clock();
    // selectionSort(array, size);
    // stop = clock();

    // // std::cout<<std::endl<<std::setw(40)<<std::left<<"Array sorted with selectionSort: ";
    // // printArray(array, size);

    // time = (double) (stop - start) / CLOCKS_PER_SEC;
    // std::cout<<std::endl<<std::setw(40)<<std::left<<"Time (selectionSort): "<<time<<"s."<<std::endl<<std::endl;

    // delete array;

    //==========================QUICK SORT==========================
    int *array = new int[size];

    generateArray(array, size, 1000);

    // std::cout<<std::setw(40)<<std::left<<"Unsorted array: ";
    // printArray(array, size);

    start = clock();
    quickSort(array, 0, size - 1);
    stop = clock();

    // std::cout<<std::endl<<std::setw(40)<<std::left<<"Array sorted with quickSort: ";
    // printArray(array, size);

    time = (double) (stop - start) / CLOCKS_PER_SEC;
    std::cout<<std::endl<<std::setw(40)<<std::left<<"Time (quickSort): "<<time<<"s."<<std::endl<<std::endl;

    delete array;


    return 0;
    
}