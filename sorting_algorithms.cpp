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
    for(int i{0}; i<n; i++){
        std::cout<<array[i]<<" ";
    }
}

int findMin(int *array, int n){
    int *buff_ptr{array};
    int result = *buff_ptr;

    buff_ptr++;
    for(int i{1}; i<n; i++){
        if(result > *buff_ptr){
            result = *buff_ptr;
        }
        buff_ptr++;
    }

    return result;
}

int findMax(int *array, int n){
    int *buff_ptr{array};
    int result = *buff_ptr;

    buff_ptr++;
    for(int i{1}; i<n; i++){
        if(result < *buff_ptr){
            result = *buff_ptr;
        }
        buff_ptr++;
    }

    return result;
}

void fillWith0(int *array, int n){
    for(int i{0}; i<n; i++){
        *array = 0;
        array++;
    }
}

//==========================BUBBLE SORT==========================
void bubbleSort(int *array, int n){
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

//==========================MERGE SORT==========================
void merge(int *array, int start, int mid, int end){
    int n = mid - start + 1;
    int m = end - mid;
    
    int *left_array{new int[n]};
    int *right_array{new int[m]};

    for(int i=0; i<n; i++){
        left_array[i] = array[start + i];
    }

    for(int j=0; j<m; j++){
        right_array[j] = array[mid + 1 + j];
    }

    int i=0; int j = 0; int k = start;
    while(i < n && j < m){
        if(left_array[i] < right_array[j]){
            array[k] = left_array[i];
            i++; k++;
        }else{
            array[k] = right_array[j];
            j++; k++;
        }
    }

    while(i < n){
        array[k] = left_array[i];
        i++; k++;
    }

    while(j < m){
        array[k] = right_array[j];
        j++; k++;
    }

    delete [] left_array; left_array = nullptr;
    delete [] right_array; right_array = nullptr;
}

void mergeSort(int * array, int l, int r){
    if(l<r){
        int mid = (l + r) / 2;
        mergeSort(array, l, mid);
        mergeSort(array, mid + 1, r);
        merge(array, l, mid, r);
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

//==========================COUNTING SORT==========================
void countingSort(int *array, int n, bool desc=false){
    int *buff_array{new int[n]};
    int i;    

    int lower_bound = findMin(array, n);
    int upper_bound = findMax(array, n);
    int bias = lower_bound < 0 ? lower_bound : 0;

    int count_length = upper_bound - lower_bound + 1;
    int *count_array{new int[count_length]};
    fillWith0(buff_array, n);

    for(i = 0; i<n; i++){
        count_array[array[i] - bias]++;
    }

    for(i = 1; i<count_length; i++){
        count_array[i] = count_array[i] + count_array[i-1];
    }
    
    for(i = n-1; i > -1; i--){
        int position = --count_array[array[i] - bias];
        buff_array[position] = array[i];

    }

    delete count_array; count_array = nullptr;

    for(i = 0; i < n; i++){
        array[i] = buff_array[i];
    }

    delete buff_array; buff_array = nullptr;

    if(desc){
        int p{0}, q{n-1};
        int buff;
        while(p < q){
            buff = array[p];
            array[p] = array[q];
            array[q] = buff;

            p++; q--;
        }
    }
}

int main(){
    int size = 10000000;
    clock_t start, stop;
    double time;

    std::cout<<std::fixed<<std::setprecision(20);

    //==========================BUBBLE SORT==========================
    //int *array{new int[size]};
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

    // delete [] array; array = nullptr;

    //==========================INSERTION SORT==========================
    // array = new int[size];

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

    // delete [] array; array = nullptr;

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

    // delete [] array; array = nullptr;

    //==========================QUICK SORT==========================
    // int *array = new int[size];

    // generateArray(array, size, 1000);

    // // std::cout<<std::setw(40)<<std::left<<"Unsorted array: ";
    // // printArray(array, size);

    // start = clock();
    // quickSort(array, 0, size - 1);
    // stop = clock();

    // // std::cout<<std::endl<<std::setw(40)<<std::left<<"Array sorted with quickSort: ";
    // // printArray(array, size);

    // time = (double) (stop - start) / CLOCKS_PER_SEC;
    // std::cout<<std::endl<<std::setw(40)<<std::left<<"Time (quickSort): "<<time<<"s."<<std::endl<<std::endl;

    // delete [] array; array = nullptr;

    //==========================COUNTING SORT==========================
    // array = new int[size];

    // generateArray(array, size, 150000000);

    // // std::cout<<std::setw(40)<<std::left<<"Unsorted array: ";
    // // printArray(array, size);

    // start = clock();
    // countingSort(array, size, false);
    // stop = clock();

    // // std::cout<<std::endl<<std::setw(40)<<std::left<<"Array sorted with countingSort: ";
    // // printArray(array, size);

    // time = (double) (stop - start) / CLOCKS_PER_SEC;
    // std::cout<<std::endl<<std::setw(40)<<std::left<<"Time (countingSort): "<<time<<"s."<<std::endl<<std::endl;

    // delete [] array; array = nullptr;

    //==========================MERGE SORT==========================
    int *array = new int[size];

    generateArray(array, size, 100);

    // std::cout<<std::setw(40)<<std::left<<"Unsorted array: ";
    // printArray(array, size);

    start = clock();
    mergeSort(array, 0, size-1);
    stop = clock();

    // std::cout<<std::endl<<std::setw(40)<<std::left<<"Array sorted with mergeSort: ";
    // printArray(array, size);

    time = (double) (stop - start) / CLOCKS_PER_SEC;
    std::cout<<std::endl<<std::setw(40)<<std::left<<"Time (mergeSort): "<<time<<"s."<<std::endl<<std::endl;

    delete [] array; array = nullptr;

    return 0;    
}