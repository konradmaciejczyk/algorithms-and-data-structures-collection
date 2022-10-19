#include <iostream>
#include <iomanip>
#include <time.h>
#include <string>
#include <cstdlib>
#include <algorithm>
#include "sorting_algorithms/sorting_algorithms.h"

void generateArray(int *array, int lower_bound, int upper_bound, int size){
    srand(time(NULL));    
    for(int i{0}; i<size; i++){
        *array = (rand() % (upper_bound - lower_bound + 1)) + lower_bound;
        array++;
    }
}

void printArray(int *array, int n){
    if(n <= 30){
        std::cout<<"[ ";
        for(int i{0}; i<n; i++){
            std::cout<<array[i]<<" ";
        }
        std::cout<<"]";
    }else{
        std::cout<<"[ ";
        for(int i{0}; i<10; i++){
             std::cout<<array[i]<<" ";
        }
        std::cout<<"(...) ";
        for(int i{n-10}; i<n; i++){
             std::cout<<array[i]<<" ";
        }
        std::cout<<"]";
    }    
}

bool arrayCmp(int *array_a, int *array_b, int size){
    for(int i{0}; i < size; i++){
        if (array_a[i] != array_b[i]){
            return false;
        }
    }
    return true;
}

void copyArray(int *array_a, int *array_b, int size){
    for(int i{0}; i < size; i++){
        *array_a = *array_b;
        array_a++; array_b++;
    }
}

struct{
    int BUBBLE_SORT = 0;
    int SELECTION_SORT = 1;
    int INSERTION_SORT = 2;
    int SHELL_SORT = 3;
    int MERGE_SORT = 4;
    int QUICK_SORT = 5;
    int COUNTING_SORT = 6;
    int RADIX_SORT = 7;
    int COCKTAIL_SORT = 8;
} Algorithms;

double singleTest(const int algorithm, int lower_bound = -10000, int upper_bound = 10000, int size = 20, bool check_correctness = false, bool verbose = true){
    clock_t start, stop;
    double delta_time;
    std::string algorithm_name;

    std::cout<<std::fixed<<std::setprecision(10);
    int *array{new int [size]};
    generateArray(array, lower_bound, upper_bound, size);

    int *array_copy{};
    if(check_correctness){
        array_copy = new int [size]; copyArray(array_copy, array, size);
    }

    if(verbose){
        std::cout<<"Performing test for dataset of: "<<size<<" integers in range of ("<<lower_bound<<", "<<" "<<upper_bound<<")"<<std::endl;
        std::cout<<std::setw(60)<<std::left<<"Unsorted array: ";
        printArray(array, size);        
    }    

    switch(algorithm){
        case 0:{
            algorithm_name = "bubble sort";
            start = clock();
            bubbleSort(array, size);
            stop = clock();
            break;
        } case 1:{
            algorithm_name = "selection sort";
            start = clock();
            selectionSort(array, size);
            stop = clock();
            break;
        } case 2:{
            algorithm_name = "insertion sort";
            start = clock();
            insertionSort(array, size);
            stop = clock();
            break;
        } case 3:{
            algorithm_name = "shell sort";
            start = clock();
            shellSort(array, size);
            stop = clock();
            break;
        } case 4:{
            algorithm_name = "merge sort";
            start = clock();
            mergeSort(array, 0, size - 1);
            stop = clock();
            break;
        } case 5:{
            algorithm_name = "quick sort";
            start = clock();
            quickSort(array, 0, size - 1);
            stop = clock();
            break;
        } case 6:{
            algorithm_name = "counting sort";
            start = clock();
            countingSort(array, size);
            stop = clock();
            break;
        } case 7:{
            algorithm_name = "radix sort";
            start = clock();
            radixSort(array, size);
            stop = clock();
            break;
        } case 8:{
            algorithm_name = "cocktail sort";
            start = clock();
            cocktailSort(array, size);
            stop = clock();
            break;
        } default:{
            std::cerr<<std::endl<<"Unknown algorithm. Terminating."<<std::endl;
            delete [] array; array = nullptr;
            return -1;
        }
    }
    delta_time = (double) (stop - start) / CLOCKS_PER_SEC;

    if(verbose){
        std::cout<<std::endl;
        std::cout<<std::setw(60)<<std::left<<"Sorted array (" + algorithm_name + "): ";
        printArray(array, size);

        std::cout<<std::endl<<std::setw(60)<<std::left<<"Time ("+algorithm_name+"): "<<delta_time<<"s."<<std::endl;

        if(check_correctness){
            std::sort(array_copy, array_copy + size);
            int result = arrayCmp(array, array_copy, size);
            std::string corr_result =  result == 1 ? "True" : "False";
            std::cout<<"Sorting correctness: " + corr_result <<std::endl;
            if(result != 1){
                exit(0);
            }

            delete [] array_copy;
        }

        std::cout<<std::endl;
    }    

    delete [] array; array = nullptr; array_copy = nullptr;

    return delta_time;
}

void correctnessTest(){
    double result;
    bool verbose = true;
    bool check_correctness = true;

    int data [27] = {-20, -10, 100, -20, 0, 100, 0, 0, 100, 0, 10, 100, 10, 20, 100, 10, 20, 0, -20, -10, 1, 0, 0, 1, 10, 20, 1};
    int lower_bound, upper_bound, size;
    for(int i = 0; i < 9; i++){
         for(int j=0; j < 25; j += 3){
            lower_bound = data[j]; upper_bound = data[j + 1]; size = data[j + 2];

            result = singleTest(Algorithms.BUBBLE_SORT, lower_bound, upper_bound, size, check_correctness, verbose);
            result = singleTest(Algorithms.SELECTION_SORT, lower_bound, upper_bound, size, check_correctness, verbose);
            result = singleTest(Algorithms.INSERTION_SORT, lower_bound, upper_bound, size, check_correctness, verbose);            
            result = singleTest(Algorithms.SHELL_SORT, lower_bound, upper_bound, size, check_correctness, verbose);
            result = singleTest(Algorithms.MERGE_SORT, lower_bound, upper_bound, size, check_correctness, verbose);
            result = singleTest(Algorithms.QUICK_SORT, lower_bound, upper_bound, size, check_correctness, verbose);
            result = singleTest(Algorithms.COUNTING_SORT, lower_bound, upper_bound, size, check_correctness, verbose);
            result = singleTest(Algorithms.RADIX_SORT, lower_bound, upper_bound, size, check_correctness, verbose);
            result = singleTest(Algorithms.COCKTAIL_SORT, lower_bound, upper_bound, size, check_correctness, verbose);
        }
    }
}

void performanceTest(int algorithm, const std::string &algorithm_name, int dataset[], int dataset_size, int probs_per_test = 3){
    std::cout<<"Performance test for "+ algorithm_name +" ("<<probs_per_test<<" probs per test)."<<std::endl;

    int lower_bound, upper_bound, size; double duration;
    int i, j;
    for(i = 0; i < dataset_size; i += 3){
        duration = 0;
        lower_bound = dataset[i + 0];
        upper_bound = dataset[i + 1];
        size = dataset[i + 2];

        std::cout<<"Sorting "<<size<<" integers in range of ("<<lower_bound<<", "<<upper_bound<<"): ";
        for(j = 0; j < probs_per_test; j++){
            duration += singleTest(algorithm, lower_bound, upper_bound, size, false, false);
        }

        duration /= probs_per_test;
        std::cout<<duration<<"s."<<std::endl;
    }

    std::cout<<std::endl;
}

int main(){    
    correctnessTest();
    // int dataset[18] {-10000, 10000, 1000, -10000, 10000, 20000, -10000, 10000, 40000, -10000, 10000, 60000, -10000, 10000, 80000, -10000, 10000, 100000};

    // performanceTest(0, "bubbleSort", dataset, std::size(dataset), 2);
    // performanceTest(1, "selectionSort", dataset, std::size(dataset), 2);
    // performanceTest(2, "insertionSort", dataset, std::size(dataset), 2);
    // performanceTest(8, "cocktailSort", dataset, std::size(dataset), 2);

    // int dataset[18] {-10000, 10000, 1000, -10000, 10000, 60000, -10000, 10000, 120000, -10000, 10000, 180000, -10000, 10000, 240000, -10000, 10000, 300000};
    // performanceTest(3, "shellSort", dataset, std::size(dataset), 2);

    // int dataset[18] {-10000, 10000, 1000, -10000, 10000, 5000000, -10000, 10000, 10000000, -10000, 10000, 15000000, -10000, 10000, 20000000, -10000, 10000, 25000000};
    // performanceTest(4, "mergeSort", dataset, std::size(dataset), 2);
    // performanceTest(5, "quickSort", dataset, std::size(dataset), 2);
    // performanceTest(6, "countingSort", dataset, std::size(dataset), 2);
    // performanceTest(7, "radixSort", dataset, std::size(dataset), 2);

    

    return 0;
}