const findMin = (array) =>{
    let n = array.length;
    let min = array[0];
    
    for(let i = 1; i < n; i++){
        if(array[i] < min){
            min = array[i];
        }
    }

    return min;
}

const findMax = (array) =>{
    let n = array.length;
    let max = array[0];
    
    for(let i = 1; i < n; i++){
        if(array[i] > max){
            max = array[i];
        }
    }

    return max;
}

//=================BUBBLE SORT===================
export function bubbleSort(array){
    let n = array.length;
    
    while(n > -1){
        let i = 0;
        while (i < n - 1){
            if(array[i] > array[i+1]){
                let aux = array[i];
                array[i] = array[i+1];
                array[i+1] = aux;
            }
            i++;
        }
        n--;
    }
}

//=================COCKTAIL SORT===================
export function cocktailSort(array) {
    let n = array.length;
    let swapped = false;
    let aux = 1;
    while (true) {
      for (let i = 0; i < n - aux; i++) {
        if (array[i] > array[i + 1]) {
          [array[i], array[i + 1]] = [array[i + 1], array[i]];
          swapped = true;
        }
      }
  
      if (!swapped) {
        break;
      }
  
      swapped = false;
      
      for (let i = n - aux; i > 0; i--) {
        if (array[i] > array[i + 1]) {
          [array[i], array[i + 1]] = [array[i + 1], array[i]];
        }
      }

      aux++;
    }
  }

//=================SELECTION SORT===================
export function selectionSort(array){
    let n = array.length;
    
    let i = 0, j, aux, buff;
    while(i < n){
        j = i + 1;
        aux = i;
        while(j < n){
            if(array[aux] > array[j]){
                aux = j;
            }
            j++;
        }
        buff = array[i];
        array[i] = array[aux];
        array[aux] = buff;
        i++;
    }
}

//=================INSERTION SORT===================
export function insertionSort(array){
    let n = array.length;

    let i = 0, j, aux;
    while(i < n - 1){
        j = i + 1;
        while(j > 0 && array[j] < array[j - 1]){
            aux = array[j];
            array[j] = array[j - 1];
            array[j - 1] = aux;

            j--;
        }
        i++;
    }
}

//=================SHELL SORT===================
export function shellSort(array){
    let n = array.length;
    let gap = Math.floor(n/2);
    let i; let j; let aux;
    for(gap; gap > 0; gap = Math.floor(gap/2)){
        for(i = gap; i < n; i++){
            for(j = i - gap; (j > -1) && (array[j] > array[j + gap]); j--){
                aux = array[j];
                array[j] = array[j + gap];
                array[j + gap] = aux;
            }
        }
    }
}

//=================MERGE SORT===================
const merge = (array, start, mid, end) => {
   let n = mid - start + 1;
   let m = end - mid;

   let left_array = [];
   for(let i = 0; i < n; i++){
    left_array.push(array[start + i]);
   }

   let right_array = [];
   for(let j = 0; j < m; j++){
    right_array.push(array[mid + 1 + j]);
   }

   let i = 0, j = 0, k = start;
   while(i < n && j < m){
        if(left_array[i] < right_array[j]){
            array[k] = left_array[i];
            i++;
        }else{
            array[k] = right_array[j];
            j++;
        }
        k++;
   }

    while(i < n){
        array[k] = left_array[i];
        i++; k++;
    }

    while(j < m){
        array[k] = right_array[j];
        j++; k++;
    }
}

export function mergeSort(array, start, end){
    if(start < end){
        let mid = Math.floor((start + end) / 2);
        mergeSort(array, start, mid);
        mergeSort(array, mid + 1, end);
        merge(array, start, mid, end);
    }
    
}

//=================QUICK SORT===================
const partition = (array, p, q) => {
    let pivot = array[Math.floor((p + q) / 2)];
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

        let aux = array[p];
        array[p] = array[q];
        array[q] = aux;
    }
}

export function quickSort(array, p, q){
    if(p < q){
        let pivot = partition(array, p, q);
        quickSort(array, p, pivot);
        quickSort(array, pivot + 1, q);
    }
}

//=================COUNTING SORT===================
export function countingSort(array, lower_bound = false, upper_bound = false, desc = false){
    if(array.length === 0){
        return;
    }

    let n = array.length;
    let output = new Array(n).fill(0);

    upper_bound = upper_bound !== false ? upper_bound : findMax(array);
    lower_bound = lower_bound !== false ? lower_bound : findMin(array);
    let bias = lower_bound < 0  ? lower_bound : 0;

    let count_length = lower_bound < 0 ? upper_bound - lower_bound +1 : upper_bound +1;
    let count = new Array(count_length).fill(0);

    for(let i=0; i < n; i++){
        count[array[i] - bias]++;
    }

    for(let i=1; i < count_length; i++){
        count[i] += count[i-1];
    }

    for(let i = n -1; i > -1; i--){
        let position = --count[array[i] - bias];
        output[position] = array[i];
    }

    for(let i = 0; i < n; i++){
        array[i] = output[i];
    }

    if(desc){
        let p = 0; let q = output.length - 1;
        while(p < q){
            let aux = output[p];
            output[p] = output[q];
            output[q] = aux;
            p++; q--;
        }
    }

    return output;
}

//=================RADIX SORT===================
export function radixSort(array, desc = false){
    let n = array.length;
    let p = 0; let q = n - 1; let aux;

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

    let maximum;
    let count_array = new Array(10).fill(0);
    let temp_array = new Array(n);
    let i, position, pos;
    aux = q;

    if(!(p == 0 && q == 0)){
        maximum = findMin(array) *-1;
        for(pos=1; Math.floor(maximum/pos) > 0; pos *= 10){
            for(i=0; i<q+1; i++){
                position = Math.floor(Math.abs(array[i]) / pos) % 10;
                count_array[position]++;
            }

            for(i=1; i<10; i++){
                count_array[i] += count_array[i - 1];
            }

            for(i = q; i > -1; i--){
                position = --count_array[Math.floor(Math.abs(array[i]) / pos) % 10];
                temp_array[position] = array[i]; 
            }

            for(i = 0; i < q+1; i++){
                array[i] = temp_array[i];
            }

            count_array.fill(0);
        }

        for(i = 0, aux; i < q+1; i++, aux--){
            array[i] = temp_array[aux];
        }
    }else{
        q--;
    } 

    maximum = findMax(array, n);
    for(pos=1; Math.floor(maximum/pos) > 0; pos *= 10){
        for(i=q+1; i<n; i++){
            position = Math.floor(array[i] / pos) % 10;
            count_array[position]++;
        }

        for(i=1; i<10; i++){
            count_array[i] += count_array[i - 1];
        }

        for(i = n - 1; i > q; i--){
            position = --count_array[Math.floor(array[i] / pos) % 10] + (q + 1);
            temp_array[position] = array[i]; 
        }

        for(i = n - 1; i > q; i--){
            array[i] = temp_array[i];
        }

        count_array.fill(0);
    }

    if(desc){
        p = 0; q = n - 1;
        while(p < q){
            aux = array[p];
            array[p] = array[q];
            array[q] = aux;

            p++; q--;
        }
    }
}