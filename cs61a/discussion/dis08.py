class Link:
    """A linked list is either a Link object or Link.empty

    >>> s = Link(3, Link(4, Link(5)))
    >>> s.rest
    Link(4, Link(5))
    >>> s.rest.rest.rest is Link.empty
    True
    >>> s.rest.first * 2
    8
    >>> print(s)
    (3 4 5)
    """
    empty = ()

    def __init__(self, first, rest=empty):
        assert rest is Link.empty or isinstance(rest, Link)
        self.first = first
        self.rest = rest

    def __repr__(self):
        if self.rest:
            rest_repr = ', ' + repr(self.rest)
        else:
            rest_repr = ''
        return 'Link(' + repr(self.first) + rest_repr + ')'

    def __str__(self):
        string = '('
        while self.rest is not Link.empty:
            string += str(self.first) + ' '
            self = self.rest
        return string + str(self.first) + ')'



def strange_loop():
    """Return a Link s for which s.rest.first.rest is s.

    >>> s = strange_loop()
    >>> s.rest.first.rest is s
    True
    """
    "*** YOUR CODE HERE ***"
    s = Link(1,Link(Link(5)))
    s.rest.first.rest = s
    return s

def sum_rec(s, k):
    """Return the sum of the first k elements in s.

    >>> a = Link(1, Link(6, Link(8)))
    >>> sum_rec(a, 2)
    7
    >>> sum_rec(a, 5)
    15
    >>> sum_rec(Link.empty, 1)
    0
    """
    # Use a recursive call to sum_rec; don't call sum_iter
    if s == Link.empty:
        return 0
    elif k == 0:
        return 0
    else:
        return sum_rec(s.rest,k-1) + s.first


def sum_iter(s, k):
    """Return the sum of the first k elements in s.

    >>> a = Link(1, Link(6, Link(8)))
    >>> sum_iter(a, 2)
    7
    >>> sum_iter(a, 5)
    15
    >>> sum_iter(Link.empty, 1)
    0
    """
    # Don't call sum_rec or sum_iter
    sum = 0
    temp = s
    if s == Link.empty:
        return 0
    while k > 0 and temp is not Link.empty:
        sum += temp.first
        temp = temp.rest
        k -= 1
    return sum
        



def overlap(s, t):
    """For increasing s and t, count the numbers that appear in both.

    >>> a = Link(3, Link(4, Link(6, Link(7, Link(9, Link(10))))))
    >>> b = Link(1, Link(3, Link(5, Link(7, Link(8)))))
    >>> overlap(a, b)  # 3 and 7
    2
    >>> overlap(a.rest, b)  # just 7
    1
    >>> overlap(Link(0, a), Link(0, b))
    3
    """
    temp1 = s
    temp2 = t
    both = 0
    while temp1 is not Link.empty:
        while temp2 is not Link.empty:
            if temp1.first == temp2.first:
                both += 1
            temp2 = temp2.rest
        temp1 = temp1.rest
        temp2 = t
    return both

def iterate_in_order(s, t):
    """For increasing s and t, yields the elements in s and t, in non-decreasing order.

    >>> a = Link(3, Link(4, Link(6, Link(7, Link(9, Link(10))))))
    >>> b = Link(1, Link(3, Link(5, Link(7, Link(8)))))
    >>> t = iterate_in_order(a, b)
    >>> for item in t:
    ...     print(item)
    1
    3
    3
    4
    5
    6
    7
    7
    8
    9
    10
    >>> t = iterate_in_order(Link.empty, b)
    >>> for item in t:
    ...      print(item)
    1
    3
    5
    7
    8
    """
    temp1 = s
    temp2 = t
    while temp1 is not Link.empty and temp2 is not Link.empty:
        if temp1.first < temp2.first:
            yield temp1.first
            temp1 = temp1.rest
        elif temp1.first > temp2.first:
            yield temp2.first
            temp2 = temp2.rest
        else:
            yield temp1.first
            yield temp2.first
            temp1 = temp1.rest
            temp2 = temp2.rest
    while temp1 == Link.empty and temp2 is not Link.empty:
        yield temp2.first
        temp2 = temp2.rest
    while temp1 is not Link.empty and temp2 == Link.empty:
        yield temp1.first
        temp1 = temp1.rest

def display(s, k=10):
    """Print the first k digits of infinite linked list s as a decimal.

    >>> s = Link(0, Link(8, Link(3)))
    >>> s.rest.rest.rest = s.rest.rest
    >>> display(s)
    0.8333333333...
    """
    assert s.first == 0, f'{s.first} is not 0'
    digits = f'{s.first}.'
    s = s.rest
    for _ in range(k):
        assert s.first >= 0 and s.first < 10, f'{s.first} is not a digit'
        digits += str(s.first)
        s = s.rest
    print(digits + '...')

def divide(n, d):
    """Return a linked list with a cycle containing the digits of n/d.

    >>> display(divide(5, 6))
    0.8333333333...
    >>> display(divide(2, 7))
    0.2857142857...
    >>> display(divide(1, 2500))
    0.0004000000...
    >>> display(divide(3, 11))
    0.2727272727...
    >>> display(divide(3, 99))
    0.0303030303...
    >>> display(divide(2, 31), 50)
    0.06451612903225806451612903225806451612903225806451...
    """
    assert n > 0 and n < d
    result = Link(0)  # The zero before the decimal point
    remainder = n
    current = result
    seen_remainders = {}  # Map remainder -> node (the node before the digit produced by that remainder)

    # Produce digits until remainder repeats or becomes 0
    while remainder not in seen_remainders and remainder != 0:
        seen_remainders[remainder] = current
        digit = (remainder * 10) // d
        current.rest = Link(digit)
        remainder = (remainder * 10) % d
        current = current.rest

    if remainder == 0:
        # Terminating decimal: create a repeating 0 cycle so display can show trailing zeros
        zero_node = Link(0)
        zero_node.rest = zero_node
        current.rest = zero_node
    else:
        # Repeating decimal: link the tail to the node that starts the repetition
        # The stored node's .rest is the first node produced when that remainder first appeared
        current.rest = seen_remainders[remainder].rest

    return result
