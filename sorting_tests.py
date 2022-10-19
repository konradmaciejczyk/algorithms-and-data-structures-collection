from sorting_algorithms.sorting_algorithms import *
from random import randint
from timeit import default_timer

def printArray(array):
    n = len(array)
    if n <= 20:
        print(array)
    else:
        print("[ ", end="")
        for i in range(10):
            print(array[i], end=" ")
        print(" (..) ", end="")
        for i in range(n - 12, n):
            print(array[i], end=" ")
        print("]")

def singleTest(algorithm, size = 30, lower_bound = -10000, upper_bound = 10000, check_correctness = False, verbose=False):
    start, stop = (0, 0)

    if verbose:
        print(f"Performing test for dataset of {size} integers in range of ({lower_bound}, {upper_bound}) for {algorithm}")
        print("Unsorted array: ".ljust(20), end="")

    array = [randint(lower_bound, upper_bound) for _ in range(size)]
    array_copy = False
    if check_correctness:
        array_copy = array.copy()

    if verbose:
        printArray(array)
    
    if algorithm == "bubbleSort":
        start = default_timer()
        bubbleSort(array)
        stop = default_timer()
    elif algorithm == "cocktailSort":
        start = default_timer()
        cocktailSort(array)
        stop = default_timer()
    elif algorithm == "selectionSort":
        start = default_timer()
        selectionSort(array)
        stop = default_timer()
    elif algorithm == "insertionSort":
        start = default_timer()
        insertionSort(array)
        stop = default_timer()
    elif algorithm == "shellSort":
        start = default_timer()
        shellSort(array)
        stop = default_timer()
    elif algorithm == "mergeSort":
        start = default_timer()
        mergeSort(array, 0, size - 1)
        stop = default_timer()
    elif algorithm == "quickSort":
        start = default_timer()
        quickSort(array, 0, size - 1)
        stop = default_timer()
    elif algorithm == "countingSort":
        start = default_timer()
        countingSort(array)
        stop = default_timer()
    elif algorithm == "radixSort":
        start = default_timer()
        radixSort(array)
        stop = default_timer()
    else:
        raise Exception("Unknown algorithm. Terminating.")

    delta_time = stop - start
    if verbose:
        print("Sorted array: ".ljust(20), end="")
        printArray(array)
        print("Time: ".ljust(20) + "{:.5f}s. ".format(delta_time))
        
        if check_correctness:
            print("Correctness: {}".format(array == sorted(array_copy)))
            #assert array == sorted(array_copy)
        print()

    return delta_time

def correctnessTest(correctness = True, verbose = True):
    data = [(-20, -10, 15), (-20, 0, 15), (0, 0, 15), (0, 10, 15), (10, 20, 15), (10, 20, 0), (-20, -10, 1), (0, 0, 1), (10, 20, 1)]

    for el in data:
        lower_bound = el[0]
        upper_bound = el[1]
        size = el[2]

        singleTest("bubbleSort", size, lower_bound, upper_bound, correctness, verbose)
        singleTest("cocktailSort", size, lower_bound, upper_bound, correctness, verbose)
        singleTest("selectionSort", size, lower_bound, upper_bound, correctness, verbose)
        singleTest("insertionSort", size, lower_bound, upper_bound, correctness, verbose)
        singleTest("shellSort", size, lower_bound, upper_bound, correctness, verbose)
        singleTest("mergeSort", size, lower_bound, upper_bound, correctness, verbose)
        singleTest("quickSort", size, lower_bound, upper_bound, correctness, verbose)
        singleTest("countingSort", size, lower_bound, upper_bound, correctness, verbose)
        singleTest("radixSort", size, lower_bound, upper_bound, correctness, verbose)

def performanceTest(algorithm, dataset, probs_per_test = 3):
    print("Performance test for {} ({} probes per test).".format(algorithm, probs_per_test))
    for data in dataset:
        duration = 0
        lower_bound = data[0]
        upper_bound = data[1]
        size = data[2]

        print("Sorting {} integers in range of ({}, {}): ".format(size, lower_bound, upper_bound), end="")
        for i in range(probs_per_test):
            duration += singleTest(algorithm, size, lower_bound, upper_bound, check_correctness = False, verbose = False)

        duration /= probs_per_test
        print("{:.5f}s. ".format(duration), end="\n")
    print()




if __name__ == "__main__":
    correctnessTest()
    # dataset = [(-10000, 10000, 1000), (-10000, 10000, 3000), (-10000, 10000, 6000), (-10000, 10000, 9000), (-10000, 10000, 12000), (-10000, 10000, 15000)]
    # performanceTest("bubbleSort", dataset, 2)
    # performanceTest("cocktailSort", dataset, 2)
    # performanceTest("insertionSort", dataset, 2)
    # performanceTest("selectionSort", dataset, 2)

    # dataset = [(-10000, 10000, 1000), (-10000, 10000, 10000), (-10000, 10000, 20000), (-10000, 10000, 30000), (-10000, 10000, 40000), (-10000, 10000, 50000)]
    # performanceTest("shellSort", dataset, 2)

    # dataset = [(-10000, 10000, 1000), (-10000, 10000, 100000), (-10000, 10000, 200000), (-10000, 10000, 300000), (-10000, 10000, 400000), (-10000, 10000, 500000)]
    # performanceTest("quickSort", dataset, 2)
    # performanceTest("mergeSort", dataset, 2)
    # performanceTest("countingSort", dataset, 2)
    # performanceTest("radixSort", dataset, 2)