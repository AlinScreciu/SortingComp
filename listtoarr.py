import os
l = []
directory = "dataset/"
for filename in os.listdir(directory):
    a = filename[:-4]
    if "SORTED" in a and "HALF" in a and "ALMOST" not in a:
        l.append(a)
for i in range(len(l)):
    for j in range(len(l)-1):
        a = int(l[j][:-10])
        b = int(l[j+1][:-10])
        if a>b:
            l[j],l[j+1] = l[j+1],l[j]
print(len(l))      
 
a ='", "'.join(l)
a = '{"' + a + '"}'
print(a)