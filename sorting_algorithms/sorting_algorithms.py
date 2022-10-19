#============BUBBLE SORT============
def bubbleSort(array: list) -> None:
    n = len(array)

    while n > -1:
        i = 0
        while i < n - 1:
            if array[i] > array[i+1]:
                array[i], array[i+1] = array[i+1], array[i]
            i += 1
        n -= 1

#============COCKTAIL SORT============
def cocktailSort(array: list) -> None:
    n = len(array)
    swapped = True
    aux = 1
    while True:
        i = 0
        for i in range(n - aux):
            if array[i] > array[i + 1]:
                array[i], array[i + 1] = array[i + 1], array[i]
                swapped = True
        
        if not swapped:
            break
        
        swapped = False
        
        for i in range(n - 2, aux - 2, -1):
            if array[i] > array[i + 1]:
                array[i], array[i + 1] = array[i + 1], array[i]
            
        aux += 1

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

#============SHELL SORT============
def shellSort(array: list) -> None:
    n = len(array)
    gap = n // 2
    while gap > 0:
        i = gap
        while i < n:
            j = i - gap
            while j > -1 and array[j] > array[j + gap]:
                array[j], array[j + gap] = array[j + gap], array[j]
                j -= 1
            i += 1
        gap //= 2

#============MERGE SORT============
def merge(array: list, start: int, mid: int, end: int) -> list:
    n = mid - start + 1
    m = end - mid

    left_array = [array[start + i] for i in range(n)]
    right_array = [array[mid + 1 + i] for i in range(m)]

    i = 0
    j = 0
    k = start
    while i < n and j < m:
        if(left_array[i] < right_array[j]):
            array[k] = left_array[i]
            i += 1
        else:
            array[k] = right_array[j]
            j += 1

        k += 1

    while i < n:
        array[k] = left_array[i]
        i += 1
        k += 1

    while j < m:
        array[k] = right_array[j]
        j += 1
        k += 1


def mergeSort(array: list, l: int, r: int) -> list:
    if l < r:
        mid = (l + r) // 2
        mergeSort(array, l, mid)
        mergeSort(array, mid + 1, r)
        merge(array, l, mid, r)

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

    n = len(array)
    lower_bound = lower_bound if lower_bound != False else min(array)
    upper_bound = upper_bound if upper_bound != False else max(array)
    bias = lower_bound if lower_bound < 0 else 0

    count_array_n = upper_bound - lower_bound if lower_bound < 0 else upper_bound
    count_array = [0 for _ in range(count_array_n +1)]
    temp_array = [0 for _ in range(n)]

    for i in range(n):
        count_array[array[i] - bias] += 1

    for i in range(1, len(count_array)):
        count_array[i] += count_array[i-1]

    for i in range(n -1, -1, -1):
        position = count_array[array[i] - bias] -1
        temp_array[position] = array[i]
        count_array[array[i] - bias] -= 1

    for i in range(n):
        array[i] = temp_array[i]

    if desc:
        p = 0
        q = len(array) - 1
        while p < q:
            array[p], array[q] = array[q], array[p]
            p += 1
            q -= 1

#============RADIX SORT (partition)===========
def radixSort(array, desc = False):
    n = len(array)
    if n == 0:
        return []
    elif n == 1:
        return array

    p = 0
    q = n-1

    while True:
        if array[p] < 0:
            p += 1

        if array[q] >= 0:
            q -= 1        

        if p >= q:
            break

        array[p], array[q] = array[q], array[p]

    count_array = [0 for _ in range(10)]
    temp_array = [0 for _ in range(n)]
    if not (p==0 and q==0):
        aux = q
        maximum = min(array[:q+1]) *-1
        pos = 1
        while maximum//pos > 0:
            for i in range(q+1):
                position = (abs(array[i]) // pos) % 10
                count_array[position] += 1

            for i in range(1, 10):
                count_array[i] += count_array[i - 1]
            
            for i in range(q, -1, -1):
                position = (abs(array[i]) // pos) % 10
                count_array[position] -= 1
                temp_array[count_array[position]] = array[i]

            for i in range(q+1):
                array[i] = temp_array[i]

            for i in range(10):
                count_array[i] = 0

            pos *= 10

        for i in range(q+1):
            array[i] = temp_array[aux]
            aux -= 1

    else:
        q -= 1
    
    if not (p == n-1 and q == n - 1):
        maximum = max(array[q+1:])
        pos = 1
        while maximum//pos > 0:
            for i in range(q+1, n):
                position = (array[i] // pos) % 10
                count_array[position] += 1

            for i in range(1, 10):
                count_array[i] += count_array[i - 1]

            for i in range(n - 1, q, -1):
                position = (array[i] // pos) % 10
                count_array[position] -= 1
                temp_array[count_array[position] + q + 1] = array[i]

            for i in range(n-1, q, -1):
                array[i] = temp_array[i]

            for i in range(10):
                count_array[i] = 0

            pos *= 10

    if desc:
        p = 0
        q = n - 1
        while p < q:
            array[p], array[q] = array[q], array[p]
            p += 1
            q -= 1