def split1(x):
    return x // 10, x % 10
def swipe(n):
    """Print the digits of n, one per line, first backward then forward.
    >>> swipe(2837)
    7
    3
    8
    2
    8
    3
    7
    """
    if n < 10:
        print(n)
    elif n > 10:
        all_but_last,last = split1(n)
        print(last)
        swipe(all_but_last)
        print(last)

def skip_factorial(n):
    """Return the product of positive integers n * (n - 2) * (n - 4) * ...

    >>> skip_factorial(5) # 5 * 3 * 1
    15
    >>> skip_factorial(8) # 8 * 6 * 4 * 2
    384
    """
    if n - 2 <= 0:
        return n
    else:
        return n * skip_factorial(n - 2)
    
def is_prime(n):
    """Returns True if n is a prime number and False otherwise.
    >>> is_prime(2)
    True
    >>> is_prime(16)
    False
    >>> is_prime(521)
    True
    """
    if n == 2:
        return True #special situation
    i = 2
    return helper_is_prime(i,n)

def helper_is_prime(k,n):
    if n % k == 0:
        return False
    elif k < n - 1:
        return helper_is_prime(k + 1,n)
    return True

def is_prime(n):
    def f(i):
        if i == n:
            return True
        elif n % i == 0:
            return False
        else:
            return f(i + 1)
    return f(2)

def hailstone(n):
    """Print out the hailstone sequence starting at n, 
    and return the number of elements in the sequence.
    >>> a = hailstone(10)
    10
    5
    16
    8
    4
    2
    1
    >>> a
    7
    >>> b = hailstone(1)
    1
    >>> b
    1
    """
    print(n)
    if n % 2 == 0:
        return even(n)
    else:
        return odd(n)

def even(n):
    return hailstone(n // 2) + 1

def odd(n):
    if n == 1:
        return 1
    else:
        return hailstone(3 * n + 1) + 1
    

def trace1(fn):
    def traced(x):
        print("the function",fn,"argument is",x)
        return fn(x)
    return traced

def trace2(fn):
    def traced(x,y):
        print("the function",fn,"argument is",x,y)
        return fn(x,y)
    return traced
#主函数，使用递归思想
def sevens(n, k):
    """Return the (clockwise) position of who says n among k players.

    >>> sevens(2, 5)
    2
    >>> sevens(6, 5)
    1
    >>> sevens(7, 5)
    2
    >>> sevens(8, 5)
    1
    >>> sevens(9, 5)
    5
    >>> sevens(18, 5)
    2
    """
    def f(i, who, direction):
        if i == n:
            return who
        else:
            if has_seven(i) or divided_seven(i):
                return f(i + 1,circle(who - direction,k),-direction)
            else:
                return f(i + 1,circle(who +direction,k),direction)
    return f(1, 1, 1)
#检验是否反转
def has_seven(n):
    if n == 0:
        return False
    elif n % 10 == 7:
        return True
    else:
        return has_seven(n // 10)
    
def divided_seven(n):
    if n % 7 == 0:
        return True
    else:
        return False
#确保循环    
def circle(tag,k):
    if tag > k:
        return 1
    elif tag == 0:
        return k
    else:
        return tag

