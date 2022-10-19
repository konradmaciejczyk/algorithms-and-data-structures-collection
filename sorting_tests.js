import {bubbleSort, cocktailSort, selectionSort, insertionSort, shellSort, mergeSort, quickSort, countingSort, radixSort} from './sorting_algorithms/sorting_algorithms.js';

const generateArray = (lower_bound, upper_bound, n) => {
    let output = []
    for(let i=0; i<n; i++){
        output.push(Math.floor(Math.random() * (upper_bound - lower_bound + 1)) + lower_bound);
    }
    return output;
}

const arrayCmp = (array_a, array_b) => {
    let n = array_a.length;
    let m = array_b.length;

    if (n !== m){
        return false;
    }else{
        for(let i = 0; i < n; i++){
            if(array_a[i] !== array_b[i]){
                return false;
            }
        }

        return true;
    }    
}

const printArray = (array) => {
    let n = array.length;

    if(n <=20){
        process.stdout.write("[ ");
        array.forEach(element => {
            process.stdout.write(`${element} `);
        });
        process.stdout.write("]\n"); 
    }else{
        process.stdout.write("[ ");
        for(let i = 0; i < 10; i++){
            process.stdout.write(`${array[i]} `);
        }
        process.stdout.write(" (...) ");
        for(let i = n - 10; i < n; i++){
            process.stdout.write(`${array[i]} `);
        }
        process.stdout.write("]\n");
    }
}

function singleTest(algorithm, lower_bound = -10000, upper_bound = 10000, size = 20, check_correctness = true, verbose = true){
    let start, stop, delta_time;

    let array = generateArray(lower_bound, upper_bound, size);
    let array_copy;

    if(check_correctness){
        array_copy = [...array];
    }

    if(verbose){
        console.log(`Performing test for dataset of: ${size} integers in range of (${lower_bound}, ${upper_bound}) for ${algorithm}.`);
        process.stdout.write("Unsorted array: ".padEnd(30, " ")); printArray(array);
    }

    switch (algorithm){
        case "bubbleSort":{
            start = performance.now();
            bubbleSort(array);
            stop = performance.now();
            break;
        }case "cocktailSort":{
            start = performance.now();
            cocktailSort(array);
            stop = performance.now();
            break;
        }case "selectionSort":{
            start = performance.now();
            selectionSort(array);
            stop = performance.now();
            break;
        }case "insertionSort":{
            start = performance.now();
            insertionSort(array);
            stop = performance.now();
            break;
        }case "shellSort":{
            start = performance.now();
            shellSort(array);
            stop = performance.now();
            break;
        }case "mergeSort":{
            start = performance.now();
            mergeSort(array, 0, size - 1);
            stop = performance.now();
            break;
        }case "quickSort":{
            start = performance.now();
            quickSort(array, 0, size - 1);
            stop = performance.now();
            break;
        }case "countingSort":{
            start = performance.now();
            countingSort(array);
            stop = performance.now();
            break;
        }case "radixSort":{
            start = performance.now();
            radixSort(array);
            stop = performance.now();
            break;
        } default: {
            throw new Error("Unknown algorithm. Terminating.");
        }
    }

    delta_time = stop - start;
    if(verbose){
        process.stdout.write("Sorted array: ".padEnd(30, " ")); printArray(array);
        console.log("Time: ".padEnd(30, " ") + parseFloat((delta_time) / 1000).toFixed(5) + "s."); 

        if(check_correctness){
            array_copy.sort((a, b) => {
                return a - b;
            });
            printArray(array_copy);
            let result = arrayCmp(array, array_copy);
            console.log("Correctness: " + String(result));
            if(!result){
                throw new Error("Correctness: " + String(result));
            }            
        }
        console.log();
    }
    return delta_time;
}

function correctnessTest(correctness = true, verbose = true){
    let data = [[-20, -10, 15], [-20, 0, 15], [0, 0, 15], [0, 10, 15], [0, 20, 15], [10, 20, 0], [-20, -10, 1], [0, 0, 1], [10, 20, 1]]

    data.forEach((data_example) => {
        let lower_bound = data_example[0];
        let upper_bound = data_example[1];
        let size = data_example[2];

        singleTest("bubbleSort", lower_bound, upper_bound, size, correctness, verbose);
        singleTest("selectionSort", lower_bound, upper_bound, size, correctness, verbose);
        singleTest("insertionSort", lower_bound, upper_bound, size, correctness, verbose);
        singleTest("shellSort", lower_bound, upper_bound, size, correctness, verbose);
        singleTest("mergeSort", lower_bound, upper_bound, size, correctness, verbose);
        singleTest("quickSort", lower_bound, upper_bound, size, correctness, verbose);
        singleTest("countingSort", lower_bound, upper_bound, size, correctness, verbose);
        singleTest("radixSort", lower_bound, upper_bound, size, correctness, verbose);
        singleTest("cocktailSort", lower_bound, upper_bound, size, correctness, verbose);
    })
}

function performanceTest(algorithm, dataset, probs_per_test = 3){
    console.log(`Performance test for ${algorithm} (${probs_per_test} probes per test).`);

    dataset.forEach((element) => {
        let duration = 0;
        let lower_bound = element[0];
        let upper_bound = element[1];
        let size = element[2];

        process.stdout.write(`Sorting ${size} integers in range of (${lower_bound}, ${upper_bound}): `);
        for(let i=0; i<probs_per_test; i++){
            duration += singleTest(algorithm, lower_bound, upper_bound, size, false, false);
        }

        duration /= probs_per_test;
        console.log(`${parseFloat((duration) / 1000).toFixed(5)}s.`);

    });
    console.log();
}

//correctnessTest();
// let dataset = [[-10000, 10000, 1000], [-10000, 10000, 20000], [-10000, 10000, 40000], [-10000, 10000, 60000], [-10000, 10000, 80000], [-10000, 10000, 100000]];
// performanceTest("bubbleSort", dataset, 2);
// performanceTest("selectionSort", dataset, 2);
// performanceTest("insertionSort", dataset, 2);
// performanceTest("cocktailSort", dataset, 2);

// let dataset = [[-10000, 10000, 1000], [-10000, 10000, 20000], [-10000, 10000, 40000], [-10000, 10000, 60000], [-10000, 10000, 80000], [-10000, 10000, 100000]];
// performanceTest("shellSort", dataset, 2);

let dataset = [[-10000, 10000, 1000], [-10000, 10000, 5000000], [-10000, 10000, 10000000], [-10000, 10000, 15000000], [-10000, 10000, 20000000], [-10000, 10000, 25000000]];
// performanceTest("mergeSort", dataset, 2);
// performanceTest("quickSort", dataset, 2);
// performanceTest("countingSort", dataset, 2);
performanceTest("radixSort", dataset, 2);



