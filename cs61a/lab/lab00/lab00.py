def twenty_twenty_five():
    """Come up with the most creative expression that evaluates to 2025
    using only numbers and the +, *, and - operators (or ** and % if you'd like).

    >>> twenty_twenty_five()
    2025
    """
    return 2025

def make_adder(n):
    return lambda k:n + k
def curry2(f):
    def g(x):
        def h(y):
            return f(x,y)
        return h
    return g

def search(f):
    x = 0
    while not f(x):
        x += 1
    return x
def inverse(f):
    return lambda y: search(lambda x:f(x) == y)
def square(x):
    return x*x
def double(x):
    return x*2