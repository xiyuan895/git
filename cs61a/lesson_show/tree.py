def tree(label : int ,branch = []):
    for branches in branch:
        assert is_tree(branches)
    return [label] + list(branch)#深刻理解，树的分支还是树
def label(tree):
    return tree[0]
def branch(tree):
    return tree[1:]
def is_tree(tree):
    if type(tree) != tree and len(tree) < 1:
        return False
    else:
        for branches in branch(tree):
            if not is_tree(branches):
                return False
    return True
def is_leaf(tree):
    return not branch(tree)
def fibonaqi_tree(n:int) -> tree:#要理解这个fibonaqi本质要返回tree，调用他本身也是个tree，所以可以使用上述tree的操作
    if n < 2:
        return tree(n)
    else:
        left,right = fibonaqi_tree(n - 2),fibonaqi_tree(n - 1)
        return tree(label(left) + label(right),[left,right])
def count_leaf(tree):
    if is_leaf(tree):
        return 1
    else:
        branch_leaf = [count_leaf(b) for b in branch(tree)]#构建一个list存储所有分支leaf的数量
        return sum(branch_leaf)
def leaf(tree):
    if is_leaf(tree):
        return [label(tree)]
    else:
        branch_leaf = [leaf(b) for b in branch(tree)]
        return  sum(branch_leaf,[])
def increment_leaves(tree):
    if is_leaf(tree):
        return tree(label(tree) + 1)
    else:
        bs = [increment_leaves(b) for b in branch(tree)]
        return tree(label(tree),bs)
def increment(tree):
    return tree(label(tree) + 1,[increment(b) for b in branch(tree)])
def print_tree(tree,indent = 0):
    print(' ' * indent + str(label(tree)))
    for b in branch(tree):
        print_tree(b,indent + 1)
def print_sum(tree,sum_num = 0):
    sum_num += label(tree)
    if is_leaf(tree):
        print(sum_num)
    else:
        for b in branch(tree):
            print_sum(b,sum_num)
def count_paths(tree,total):
    if total == label(tree):
        found = 1
    else:
        found = 0
    return found + sum([count_paths(b,total - label(tree)) for b in branch(tree)])
