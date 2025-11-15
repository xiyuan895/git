def paths(m, n):
    """Return the number of paths from one corner of an
    M by N grid to the opposite corner.

    >>> paths(2, 2)
    2
    >>> paths(5, 7)
    210
    >>> paths(117, 1)
    1
    >>> paths(1, 157)
    1
    """
    if m == 1 or n == 1:
        return 1
    return paths(m -1,n) + paths(m,n - 1)

def max_product(s):
    """Return the maximum product of non-consecutive elements of s.

    >>> max_product([10, 3, 1, 9, 2])   # 10 * 9
    90
    >>> max_product([5, 10, 5, 10, 5])  # 5 * 5 * 5
    125
    >>> max_product([])                 # The product of no numbers is 1
    1
    """
    if not s:
        return 1
    return max(s[0] * max_product(s[2:]),max_product(s[1:]))

def sums(n, m):
    """Return lists that sum to n containing positive numbers up to m that
    have no adjacent repeats.

    >>> sums(5, 1)
    []
    >>> sums(5, 2)
    [[2, 1, 2]]
    >>> sums(5, 3)
    [[1, 3, 1], [2, 1, 2], [2, 3], [3, 2]]
    >>> sums(5, 5)
    [[1, 3, 1], [1, 4], [2, 1, 2], [2, 3], [3, 2], [4, 1], [5]]
    >>> sums(6, 3)
    [[1, 2, 1, 2], [1, 2, 3], [1, 3, 2], [2, 1, 2, 1], [2, 1, 3], [2, 3, 1], [3, 1, 2], [3, 2, 1]]
    """
    if n < 0:
        return []
    if n == 0:
        sums_to_zero = []     # The only way to sum to zero using positives
        return [sums_to_zero] # Return a list of all the ways to sum to zero
    result = []
    for k in range(1, m + 1):
        result = result + [ [k] + rest for rest in sums(n - k,m) if rest == [] or rest[0] != k]
        """首先，要确定分类原则为第一项的大小，然后
         注意到可以使用本函数返回的列表做迭代，但要注意不可以有相同元素出现，因此if条件要设置好 """
    return result

def fit(total, n):
    """Return whether there are n positive perfect squares that sums to total.

    >>> [fit(4, 1), fit(4, 2), fit(4, 3), fit(4, 4)]  # 1*(2*2) for n=1; 4*(1*1) for n=4
    [True, False, False, True]
    >>> [fit(12, n) for n in range(3, 8)]  # 3*(2*2), 3*(1*1)+3*3, 4*(1*1)+2*(2*2)
    [True, True, False, True, False]
    >>> [fit(32, 2), fit(32, 3), fit(32, 4), fit(32, 5)] # 2*(4*4), 3*(1*1)+2*2+5*5
    [True, False, False, True]
    """
    def f(total, n, k):
        if total == k * k and n == 1:#只有当正好只剩下一个数以及刚好相等的情况才能算是true
            return True
        elif total < k * k:
            return False
        else:
            return f(total - k * k,n - 1,k) or f(total - k * k,n - 1,k + 1) or f(total,n,k + 1)#有三种情况：1 减去k*k，计算有多少个k*k 2：-k*k 但是下一个变为k+1 3：不减去k*k 直接跳到下一个
    return f(total, n, 1)
    """终止条件的设置是很重要的，必须谨慎考虑，以及对于要维护的量也必须要思考完备，会出现几种情况"""