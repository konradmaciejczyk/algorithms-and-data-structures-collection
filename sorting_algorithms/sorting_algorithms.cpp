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

int abs(int number){
    return number < 0 ? number *-1 : number;
}

//==========================BUBBLE SORT==========================
void bubbleSort(int *array, int n){
    int *array_ptr_buff = array;
    int *array_next{array+1};
    int i, aux;
    for(n; n>-1; n--){
        for(i = 0; i<n-1; i++){
            if(*array > *array_next){
                aux = *array;
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

//==========================COCKTAIL SORT==========================
void cocktailSort(int *array, int n){
    bool swapped = false;
    int aux = 2; int i, buff;

    while(true){
        for(i = 0; i < n - aux; i++){
            if(array[i] > array[i + 1]){
                buff = array[i];
                array[i] = array[i + 1];
                array[i + 1] = buff;

                swapped = true;
            }
        }

        if (!swapped){
            break;
        }

        swapped = false;

        for(i = n - 2; i > aux - 2; i--){
            if(array[i] > array[i + 1]){
                buff = array[i];
                array[i] = array[i + 1];
                array[i + 1] = buff;
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

//==========================SHELL SORT==========================
void shellSort(int *array, int n){
    for(int gap = n/2; gap > 0; gap /= 2){
        for(int i = gap; i < n; i++){
            for(int j = i - gap; (j > -1) && (array[j] > array[j + gap]); j--){
                    int aux = array[j];
                    array[j] = array[j+gap];
                    array[j+gap] = aux;
            }
        }
    }
}

//==========================SELECTION SORT==========================
void selectionSort(int *array, int n){
    int i, j, aux;

    for(i = 0; i<n; i++){
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
    if(n == 0){
        return;
    }

    int *buff_array{new int[n]};
    int i;    

    int lower_bound = findMin(array, n);
    int upper_bound = findMax(array, n);
    int bias = lower_bound < 0 ? lower_bound : 0;

    int count_length = lower_bound < 0 ? upper_bound - lower_bound +1 : upper_bound +1;
    int *count_array{new int[count_length]};
    fillWith0(count_array, count_length);

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

//==========================RADIX SORT==========================
void radixSort(int *array, int n, bool desc = false){
    if(n == 0){
        return;
    }

    int p=0; int q=n-1; int aux;

    while(true){
        if(array[p] < 0){
            p++;
        }
        
        if(array[q] >= 0){
            q--;
        }

        if(p >= q){
            break;
        }

        aux = array[p];
        array[p] = array[q];
        array[q] = aux;
    }
    
    int maximum;
    int count_array [10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int *temp_array {new int [n]};
    int i, position, pos;
    aux = q;

    if(!(p == 0 && q == 0)){
        maximum = findMin(array, n) * -1;
        for(pos=1; (maximum/pos) > 0; pos *= 10){
            for(i=0; i<q+1; i++){
                position = (abs(array[i]) / pos) % 10;
                count_array[position]++;
            }

            for(i=1; i<10; i++){
                count_array[i] += count_array[i - 1];
            }

            for(i = q; i > -1; i--){
                position = --count_array[(abs(array[i]) / pos) % 10];
                temp_array[position] = array[i]; 
            }

            for(i = 0; i < q+1; i++){
                array[i] = temp_array[i];
            }

            fillWith0(count_array, 10);
        }

        for(i = 0, aux; i < q+1; i++, aux--){
            array[i] = temp_array[aux];
        }
    }else{
        q--;
    } 

    if(!(p==n-1 && q == n - 1)){
        maximum = findMax(array, n);
        for(pos=1; (maximum/pos) > 0; pos *= 10){
            for(i=q+1; i<n; i++){
                position = (array[i] / pos) % 10;
                count_array[position]++;
            }

            for(i=1; i<10; i++){
                count_array[i] += count_array[i - 1];
            }

            for(i = n - 1; i > q; i--){
                position = --count_array[(array[i] / pos) % 10] + (q + 1);
                temp_array[position] = array[i]; 
            }

            for(i = n - 1; i > q; i--){
                array[i] = temp_array[i];
            }

            fillWith0(count_array, 10);
        }

    }

    delete [] temp_array; temp_array = nullptr;   
}