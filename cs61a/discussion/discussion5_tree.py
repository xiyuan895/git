from tree import *
def has_path(t, p):
    """Return whether tree t has a path from the root with labels p.

    >>> t2 = tree(5, [tree(6), tree(7)])
    >>> t1 = tree(3, [tree(4), t2])
    >>> has_path(t1, [5, 6])        # This path is not from the root of t1
    False
    >>> has_path(t2, [5, 6])        # This path is from the root of t2
    True
    >>> has_path(t1, [3, 5])        # This path does not go to a leaf, but that's ok
    True
    >>> has_path(t1, [3, 5, 6])     # This path goes to a leaf
    True
    >>> has_path(t1, [3, 4, 5, 6])  # There is no path with these labels
    False
    """
    if len(p) == 1 and p[0] == label(t):  # when len(p) is 1
        return True
    elif label(t) != p[0]:#检验是否匹配
        return False
    else:
        return any(has_path(b,p[1:]) for b in branch(t))#用any函数来处理true与false，从而判定是否有路径
def find_path(t, x):
    """
    >>> t2 = tree(5, [tree(6), tree(7)])
    >>> t1 = tree(3, [tree(4), t2])
    >>> find_path(t1, 5)
    [3, 5]
    >>> find_path(t1, 4)
    [3, 4]
    >>> find_path(t1, 6)
    [3, 5, 6]
    >>> find_path(t2, 6)
    [5, 6]
    >>> print(find_path(t1, 2))
    None
    """
    if label(t) == x: #找到了，label（t） == x
        return [label(t)]#最好直接用【】，不推荐用list转换，可能会有报错
    elif label(t) != x and not is_leaf(t):#label（t） ！= x，我应该怎么记录？用什么做迭代，维护什么指标？
        for b in branch(t):
            path = find_path(b,x)
            if path:
                return [label(t)] + path #注意逻辑顺序，python对这个列表推导的顺序有很强的要求，哪个在先就要写到加号前面
    return None
def only_paths(t, n):
    """Return a tree with only the nodes of t along paths from the root to a leaf of t
    for which the node labels of the path sum to n. If no paths sum to n, return None.

    >>> print_tree(only_paths(tree(5, [tree(2), tree(1, [tree(2)]), tree(1, [tree(1)])]), 7))
    5
      2
      1
        1
    >>> t = tree(3, [tree(4), tree(1, [tree(3, [tree(2)]), tree(2, [tree(1)]), tree(5), tree(3)])])
    >>> print_tree(only_paths(t, 7))
    3
      4
      1
        2
          1
        3
    >>> print_tree(only_paths(t, 9))
    3
      1
        3
          2
        5
    >>> print(only_paths(t, 3))
    None
    """
    if is_leaf(t) and n - label(t) == 0:
        return t
    if is_leaf(t) and n -label(t) != 0:
        return None
    new_branches = [only_paths(b,n - label(t)) for b in branch(t)]
    new_branches = [b for b in new_branches if b is not None]
    if new_branches:
        return tree(label(t), new_branches)