

def trace2(fn):
    def traced(x,y):
        print("the function",fn,"argument is",x,y)
        return fn(x,y)
    return traced

def print_all(x):
    print(x)
    return print_all

def print_sum(x):
    print(x)
    def next_sum(y):
        return print_sum(x + y)
    return next_sum

@trace2
def split(x):
    return x // 10,x % 10

@trace2
def digit_sum(x):
    assert x > 0,"x cannot be a nagative number"
    digit_but_last,last = split(x)
    if x < 10:
        return x
    else:
        return digit_sum(digit_but_last) + last
'''单函数递归写法'''
def split2(x):
    return x // 100 ,x % 100

def tag(x):
    assert x > 0 ,'x cannot be a negative number'
    if x < 10:
        return 1
    else:
        return tag(x//10) + 1
    
def up_digit(x):
    if (x//10) * 2 > 10:
        return x % 10 + ((x//10)*2) % 10 +((x // 10) * 2) // 10
    else:
        return x % 10 + (x // 10) * 2
    
def check_credit_card(x):
        all_but_twolast,last = split2(x)
        if tag(x) == 1:
            return x
        if tag(x) == 2:
            return up_digit(x)
        else:
            return check_credit_card(all_but_twolast) + up_digit(last)
        
def is_valid(f):
    def check(x):
        if f(x) % 10 == 0:
            return True
        else:
            return False
    return check
"""相互调用递归写法"""
def luhn_sum(x):
    all_but_last,last = split(x)
    if x < 10:
        return last
    else:
        return luhn_double_sum(all_but_last) + last
    
def luhn_double_sum(x):
    all_but_last,last = split(x)
    luhn_double_num = digit_sum(last * 2)
    if x < 10:
        return luhn_double_num
    else:
        return luhn_sum(all_but_last) + luhn_double_num
    
def cascade(n):
    print(n)
    if n > 10:
        cascade(n//10)
        print(n)

def inverse_cascade(n):
    grow(n//10)
    print(n)
    shrink(n//10)
def grow(n):
    if n < 10:
        print(n)
    else:
        grow(n // 10)
        print(n)
def shrink(n):
    if n > 0:
        print(n)
        shrink(n // 10)
def f_then_g(f,g,n):
    if n:
        f(n)
        g(n)
grow = lambda n:f_then_g(grow,print,n//10)
shrink = lambda n:f_then_g(print,shrink,n//10)


@trace2
def fibonaqi(n):
    if n == 0:
        return 0
    if n == 1:
        return 1
    if n >= 2:
        return fibonaqi(n - 1) + fibonaqi(n - 2)
@trace2    
def count_partition(x,y):
   if x == 0:
       return 1
   elif x < 0:
       return 0
   elif y == 0:
       return 0
   else:
       return count_partition(x - y,y) + count_partition(x,y - 1)
   ''' if x == 0:
        return 1
    if x == 1:
        return 1
    if y == 1:
        return 1
    if x >= y:
        return count_partition(x - y,y) + count_partition(x,y - 1)
    if x < y:
        return count_partition(x,x)
'''

