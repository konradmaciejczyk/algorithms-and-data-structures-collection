def LCM(a: int, b: int) -> int:
    """Least common multiple"""
    if a == 0 or b == 0:
        raise ValueError("LCM for 0 is not available!")

    assert type(a) is int and type(b) is int, "a and b must be integers"

    x = a
    y = b
    while y:
        x, y = y, x % y

    result = (a * b) // x 
    return  result if result > 0 else result * -1

#=============GREATEST COMMON DIVISOR=============
def GCD(a: int,b: int) -> int:
    """Greatest common divisor"""    
    if a == 0 and b == 0:
        raise ValueError("At least one of two numbers must not be 0!")
    assert type(a) is int and type(b) is int, "a and b must be integers"

    while b:
        a,b = b,a%b

    return a if a > 0 else a * -1

#=============GREATEST COMMON DIVISOR recursive=============
def rGCD(a: int, b: int) -> int:
    """Greatest common divisor (recursive)"""
    if b == 0:
        return a 
    else:
        result = rGCD(b, a % b)
        return result

#=============GREATEST COMMON DIVISOR using substraction=============
def sGCD(a: int, b: int) -> int:
    """Greatest common divisor (using substraction)"""
    if a == 0 or b == 0:
        raise ValueError("All two numbers must not be 0!")
    assert type(a) is int and type(b) is int, "a and b must be integers"

    a = a if a > 0 else a *-1
    b = b if b > 0 else b *-1

    while a != b:
        while a>b:
            a = a - b
        while b>a:
            b = b- a
    return a if a > 0 else a *-1

#=============SIEVE OF ERATOSTHENES=============
def sieve_of_eratosthenes(n: int) -> list:
    """Generate list of prime numbers [2...n] using sieve of erathosthenes"""
    if n < 2:
        raise ValueError("Range must be greater or equal to 2")
    elif n == 2:
        return [2]
    assert n is not int, "Range must be integer"

    prime = [True for i in range(n + 1)] 
    p = 2
    while (p * p <= n):
        if (prime[p] == True): 
            for i in range(p * 2, n + 1, p): 
                prime[i] = False
        p += 1        
    result = []
    for p in range(2, n):        
        if prime[p]: 
            result.append(p)            
    return result

#=============FACTORIAL=============
def factorial(n: int) -> int:
    if n < 0 or type(n) is not int:
        raise ValueError("Factorial can be computed only for positive integers")

    result = 1
    if n == 0 or n == 1:
        return result
    else:
        while n >= 2:
            result *= n
            n -= 1
    return result

#=============FACTORIAL (recursive)=============
def rFactorial(n):
    """Factorial (recursive)"""

    if n < 2:
        return 1
    else:
        return rFactorial(n-1) * n

#=============HORNER=============
def horner(cooficients, root):
    aux = cooficients[0]
    n = len(cooficients)
    result = [aux]

    i = 0
    while i <= n -2:
        result.append(result[i] * root + cooficients[i+1])
        i += 1

    remainder = result[n - 1]
    result.pop(len(result) - 1)

    return (result, remainder)


if __name__ == "__main__":
    a, b = 3, 9
    print("Least common multiple of {} and {} (LCM): {}".format(a, b, LCM(a, b)))
    print("Greatest common divisor of {} and {} (GCD): {}".format(a, b, GCD(a, b)))
    print("Greatest common divisor of {} and {} (rGCD): {}".format(a, b, rGCD(a, b)))
    print("Greatest common divisor of {} and {} (sGCD): {}".format(a, b, sGCD(a, b)))
    print()
    end = 3
    print("Prime numbers from 2 to {}: {}".format(end, sieve_of_eratosthenes(end)))
    print()
    n = 5
    print("{}!={} (factorial)".format(n, factorial(n)))
    print("{}!={} (rFactorial)".format(n, rFactorial(n)))