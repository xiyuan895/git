def main(s,value):
    '''while 版本
    total,index = 0,0
    while index < len(s):
        element = s[index]
        if element == value:
            total += 1
        index += 1
    print(total)'''
    total = 0 
    for element in s:
        if element == value:
            total += 1
    print(total)
main([1,2,3,4,6,3,4,25,6,35,6],6)