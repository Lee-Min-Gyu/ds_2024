def find_max_recursive(lst,n):
    if n==1:
        return lst[0]
    return lst[0] if lst[0] > find_max_recursive(lst[1:],n-1) else find_max_recursive(lst[1:],n-1)



def find_max_iterative(lst,n):
    max = 0
    i = 0
    for i in range(n):
        if max <=lst[i]:
            max = lst[i]
    return max

num =list(map(int,input("10개 숫자 : ").split( )))

print(find_max_iterative(num, len(num)))
print(find_max_recursive(num,len(num)))