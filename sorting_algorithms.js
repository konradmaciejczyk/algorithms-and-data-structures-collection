const generateArray = (size, lower_bound, upper_bound) => {
    let output = [];

    for(let i=0; i<size; i++){
        let aux = Math.floor(Math.random()*10);

        if(aux % 2 == 0){
            output.push(Math.floor(Math.random()*upper_bound));
        }else{
            output.push(Math.floor(Math.random()*lower_bound));
        }        
    }

    return output;
}

//=================BUBBLE SORT===================
function bubbleSort(array){
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

//=================SELECTION SORT===================
function selectionSort(array){
    let n = array.length;
    
    let i = 0;
    while(i < n){
        j = i + 1;
        aux = i;
        while(j < n){
            if(array[aux] > array[j]){
                aux = j;
            }
            j++;
        }
        let buff = array[i];
        aux[i] = array[aux];
        array[aux] = buff;
        i++;
    }
}

//=================INSERTION SORT===================
function insertionSort(array){
    let n = array.length;

    i = 0;
    while(i < n - 1){
        j = i + 1;
        while(j > 0 && array[j] < array[j - 1]){
            let aux = array[j];
            array[j] = array[j - 1];
            array[j - 1] = aux;

            j--;
        }
        i++;
    }
}

//=================MERGE SORT===================
const merge = (left_array, right_array) => {
    let m = left_array.length; let n = right_array.length;
    let i = 0; let j = 0;
    let output = [];

    while(i < m && j < n){
        if(left_array[i] < right_array[j]){
            output.push(left_array[i]);
            i++;
        }else{
            output.push(right_array[j]);
            j++;
        }
    }

    while(i < m){
        output.push(left_array[i]);
        i++;
    }

    while(j < n){
        output.push(right_array[j]);
        j++;
    }

    return output;
}

function mergeSort(array){
    let n = array.length;
    if(n > 1){
        let mid = Math.floor(n/2);
        let left_array = mergeSort(array.slice(0, mid));
        let right_array = mergeSort(array.slice(mid, n));

        return merge(left_array, right_array);
    }else{
        return array;
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

function quickSort(array, p, q){
    if(p < q){
        let pivot = partition(array, p, q);
        quickSort(array, p, pivot);
        quickSort(array, pivot + 1, q);
    }
}

//=================COUNTING SORT===================
function countingSort(array, lower_bound = false, upper_bound = false, desc = false){
    if(array.length === 1){
        return array;
    }

    let n = array.length;
    let output = new Array(n).fill(0);

    upper_bound = upper_bound !== false ? upper_bound : Math.max(...array);
    lower_bound = lower_bound !== false ? lower_bound : Math.min(...array);
    let bias = lower_bound < 0  ? lower_bound : 0;

    let count = new Array(upper_bound - lower_bound + 1).fill(0);

    for(let i=0; i < n; i++){
        count[array[i] - bias]++;
    }

    for(let i=1; i < count.length; i++){
        count[i] = count[i-1] + count[i];
    }

    n--;
    for(n; n > -1; n--){
        let position = count[array[n] - bias] -1;
        output[position] = array[n];
        count[array[n] - bias]--;
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


let size = 50000;
let array = generateArray(size, -10000, 10000);
console.log(`Before bubbleSort: ${array}`);
let start = performance.now();
bubbleSort(array);
let stop = performance.now();
console.log(`After bubbleSort: ${array}`);
console.log(`Time (bubbleSort): ${parseFloat((stop - start) / 1000).toFixed(3)}s.`);
console.log();

array = generateArray(size, -10000, 10000);
//console.log(`Before selectionSort: ${array}`);
start = performance.now();
selectionSort(array);
stop = performance.now();
//console.log(`After selectionSort: ${array}`);
console.log(`Time (selectionSort): ${parseFloat((stop - start) / 1000).toFixed(3)}s.`);
console.log();

array = generateArray(size, -10000, 10000);
//console.log(`Before insertionSort: ${array}`);
start = performance.now();
insertionSort(array);
stop = performance.now();
//console.log(`After insertionSort: ${array}`);
console.log(`Time (insertionSort): ${parseFloat((stop - start) / 1000).toFixed(3)}s.`);
console.log();

array = generateArray(size, -10000, 10000);
//console.log(`Before mergeSort: ${array}`);
start = performance.now();
array = mergeSort(array);
stop = performance.now();
//console.log(`After mergeSort: ${array}`);
console.log(`Time (mergeSort): ${parseFloat((stop - start) / 1000).toFixed(3)}s.`);
console.log();

array = generateArray(size, -10000, 10000);
//console.log(`Before quickSort: ${array}`);
start = performance.now();
quickSort(array, 0, array.length - 1);
stop = performance.now();
//console.log(`After quickSort: ${array}`);
console.log(`Time (quickSort): ${parseFloat((stop - start) / 1000).toFixed(3)}s.`);
console.log();

array = generateArray(size, -10000, 10000);
//console.log(`Before countingSort: ${array}`);
start = performance.now();
array = countingSort(array, -10000, 10000);
stop = performance.now();
//console.log(`After countingSort: ${array}`);
console.log(`Time (countingSort): ${parseFloat((stop - start) / 1000).toFixed(3)}s.`);
console.log();