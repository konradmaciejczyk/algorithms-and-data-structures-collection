from random import randint
from timeit import default_timer

def bubbleSort(array: list) -> None:
    n = len(array)

    while n > -1:
        i = 0
        while i < n - 1:
            if array[i] > array[i+1]:
                array[i], array[i+1] = array[i+1], array[i]
            i += 1
        n -= 1

#============SELECTION SORT============
def selectionSort(array: list) -> None:
    n = len(array)
    i = 0

    while i < n:
        aux = i
        j = i + 1
        while j < n:
            if array[j] < array[aux]:
                aux = j
            j += 1
        array[aux], array[i] = array[i], array[aux]
        i += 1

#============INSERTION SORT============
def insertionSort(array: list) -> None:
    n = len(array)
    i = 0

    while i < n - 1:
        j = i + 1
        while j > 0 and array[j] < array[j - 1]:
            array[j - 1], array[j] = array[j], array[j - 1]
            j -= 1
        i += 1

#============MERGE SORT============
def merge(left_array: list, right_array: list) -> list:
    m = len(left_array)
    n = len(right_array)
    i = j = 0
    output = []

    while i < m and j < n:
        if left_array[i] < right_array[j]:
            output.append(left_array[i])
            i += 1
        else:
            output.append(right_array[j])
            j += 1

    while i < m:
        output.append(left_array[i])
        i += 1

    while j < n:
        output.append(right_array[j])
        j += 1

    return output

def mergeSort(array: list) -> list:
    n = len(array)
    
    if n > 1:
        mid = n//2
        left_array = mergeSort(array[:mid])
        right_array = mergeSort(array[mid:])

        return merge(left_array, right_array)
    else:
        return array

#============QUICK SORT============
def partition(array: list, p: int, q: int) -> int:
    pivot = array[(p + q) // 2]
    p -= 1
    q += 1

    while True:
        p += 1
        while array[p] < pivot:
            p += 1

        q -= 1
        while array[q] > pivot:
            q -= 1

        if p >= q:
            return q

        array[p], array[q] = array[q], array[p]

def quickSort(array: list, p: int, q: int) -> None:
    if p < q:
        pivot = partition(array, p, q)
        quickSort(array, p, pivot)
        quickSort(array, pivot + 1, q)

#============COUNTING SORT============
def countingSort(array, lower_bound = False, upper_bound = False, desc = False):
    if array == []:
        return []

    lower_bound = lower_bound if lower_bound != False else min(array)
    upper_bound = upper_bound if upper_bound != False else max(array)
    bias = lower_bound if lower_bound < 0 else 0

    count = [0 for _ in range((upper_bound - lower_bound) +1)]
    output = [0 for _ in range(len(array))]

    for i in range(len(array)):
        count[array[i] - bias] += 1

    for i in range(1, len(count)):
        count[i] += count[i-1]

    for i in range(len(array) -1, -1, -1):
        position = count[array[i] - bias] -1
        output[position] = array[i]
        count[array[i] - bias] -= 1

    if desc:
        p = 0
        q = len(output) - 1
        while p < q:
            output[p], output[q] = output[q], output[p]
            p += 1
            q -= 1

    return output


if __name__ == "__main__":
    input_size = 50000

    array = [randint(-10000, 10000) for _ in range(input_size)]
    #print("Before bubbleSort: {}".format(array))
    start = default_timer()
    bubbleSort(array)
    stop = default_timer()
    #print("After bubbleSort: {}".format(array))
    print("Time (bubbleSort): {:.3f}s.".format(stop - start), end="\n\n")

    array = [randint(-10000, 10000) for _ in range(input_size)]
    #print("Before selectionSort: {}".format(array))
    start = default_timer()
    selectionSort(array)
    stop = default_timer()
    #print("After selectionSort: {}".format(array))
    print("Time (selectionSort): {:.3f}s.".format(stop - start), end="\n\n")

    array = [randint(-10000, 10000) for _ in range(input_size)]
    #print("Before insertionSort: {}".format(array))
    start = default_timer()
    insertionSort(array)
    stop = default_timer()
    #print("After insertionSort: {}".format(array))
    print("Time (insertionSort): {:.3f}s.".format(stop - start), end="\n\n")

    array = [randint(-10000, 10000) for _ in range(input_size)]
    #print("Before mergeSort: {}".format(array))
    start = default_timer()
    array = mergeSort(array)
    stop = default_timer()
    #print("After mergeSort: {}".format(array))
    print("Time (mergeSort): {:.3f}s.".format(stop - start), end="\n\n")

    array = [randint(-10000000, 10000000) for _ in range(input_size)]
    #print("Before quickSort: {}".format(array))
    start = default_timer()
    quickSort(array, 0, len(array) - 1)
    stop = default_timer()
    #print("After quickSort: {}".format(array))
    print("Time (quickSort): {:.3f}s.".format(stop - start), end="\n\n")

    array = [randint(-10000, 10000) for _ in range(input_size)]
    #print("Before countingSort: {}".format(array))
    start = default_timer()
    array = countingSort(array, -10000, 10000)
    stop = default_timer()
    print("After countingSort: {}".format(array))
    print("Time (countingSort): {:.3f}s.".format(stop - start), end="\n\n")