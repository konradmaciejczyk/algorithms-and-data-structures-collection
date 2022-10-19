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

//==========================SHELL SORT==========================
void shellSort(int *array, int n){
    for(int gap = n/2; gap > 0; gap /= 2){
        for(int i = gap; i < n; i++){
            for(int j = i - gap; (j > -1) && (*(array + j) > *(array + j + gap)); j--){
                int aux = *(array + j);
                *(array + j) = *(array + j + gap);
                *(array + j + gap) = aux;
            }
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

//==========================MERGE SORT==========================
void merge(int *array, int start, int mid, int end){
    int n = mid - start + 1;
    int m = end - mid;
    
    int *left_array{new int[n]};
    int *right_array{new int[m]};

    for(int i=0; i<n; i++){
        *(left_array + i) = *(array + start + i);
    }

    for(int j=0; j<m; j++){
        *(right_array + j) = *(array + mid + 1 + j);
    }

    int i=0; int j = 0;
    while(i < n && j < m){
        if(*(left_array + i) < *(right_array + j)){
            *(array + start) = *(left_array + i);
            i++;
        }else{
            *(array + start) = *(right_array + j);
            j++;
        }

        array++;
    }

    while(i < n){
        *(array + start) = *(left_array + i);
        i++; array++;
    }

    while(j < m){
        *(array + start) = *(right_array + j);
        j++; array++;
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

    int *count_array_ptr = count_array;
    for(i = 0; i<n; i++){
        ++*(count_array_ptr + array[i] - bias) ;
    }

    count_array_ptr = count_array +1;
    int *count_array_prev_ptr = count_array;
    for(i = 0; i<count_length; i++){
        *(count_array_ptr + i) += *(count_array_prev_ptr + i);
    }    
    count_array_prev_ptr = nullptr;

    count_array_ptr = nullptr;
    for(i = n-1; i > -1; i--){
        *(buff_array + --*(count_array + *(array + i) - bias)) = *(array + i);
    }

    count_array_ptr = nullptr;
    delete count_array; count_array = nullptr;

    for(i = 0; i < n; i++){
        *(array + i) = *(buff_array + i);
    }

    delete buff_array; buff_array = nullptr;

    if(desc){
        int p{0}, q{n-1};
        int buff;
        while(p < q){
            buff = *(array + p);
            *(array + p) = *(array + q);
            *(array + q) = buff;

            p++; q--;
        }
    }
}

int main(){
    int size = 150000;
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

    //==========================SHELL SORT==========================
    int *array = new int[size];

    generateArray(array, size, 1000);

    // std::cout<<std::setw(40)<<std::left<<"Unsorted array: ";
    // printArray(array, size);

    start = clock();
    shellSort(array, size);
    stop = clock();

    // std::cout<<std::endl<<std::setw(40)<<std::left<<"Array sorted with shellSort: ";
    // printArray(array, size);

    time = (double) (stop - start) / CLOCKS_PER_SEC;
    std::cout<<std::endl<<std::setw(40)<<std::left<<"Time (shellSort): "<<time<<"s."<<std::endl<<std::endl;

    delete [] array; array = nullptr;

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
    // int *array = new int[size];

    // generateArray(array, size, 100);

    // // std::cout<<std::setw(40)<<std::left<<"Unsorted array: ";
    // // printArray(array, size);

    // start = clock();
    // mergeSort(array, 0, size-1);
    // stop = clock();

    // // std::cout<<std::endl<<std::setw(40)<<std::left<<"Array sorted with mergeSort: ";
    // // printArray(array, size);

    // time = (double) (stop - start) / CLOCKS_PER_SEC;
    // std::cout<<std::endl<<std::setw(40)<<std::left<<"Time (mergeSort): "<<time<<"s."<<std::endl<<std::endl;

    // delete [] array; array = nullptr;

    return 0;    
}