'''
https://www.geeksforgeeks.org/z-algorithm-linear-time-pattern-searching-algorithm/
'''
def z_array(z_string):
    z_array=[0]
    l=-1; r=-1
    for i in range(1,len(z_string)):
        valToAppend = 0
        if i<=r:
            valToAppend = z_array[i-l]
        if valToAppend+i>r or i>r:
            l=-1
        if l==-1 and z_string[i] == z_string[0]:
            l=i; 
            if i>r: r=i
            while (r+1)<len(z_string) and z_string[r-l+1] == z_string[r+1]:
                r+=1
            valToAppend = r-l+1
        z_array.append(valToAppend)
    return z_array
