import matplotlib.pyplot as plt 
from matplotlib.font_manager import FontProperties
ns = ['ALMOSTSORTED','RANDOM','HALFSORTED','REVERSESORTED','SORTED','SMALLRANGEINT']

for name in ns:
    with open(f'{name}.txt','r') as f:
        a = f.read().split('\n')
    sorts = {}
    for i in range(len(a)):
        s = a[i].find(':')
        sorts.setdefault(a[i][:s],[])
    for i in range(len(a)):
        s = a[i].find(':')
        f = a[i].find('for')
        sorts[a[i][:s]].append(float(a[i][s+2:f-2])*1000000)
    s = []
    ra = [100,1000,10000,100000,1000000]
    for x in ra:
        for y in range(x//10,x,(x+1)//5):
            s.append(y)
    plt.figure(dpi=300)
    h = []
    for x in sorts:
        t, = plt.plot(s[:len(sorts[x][:10])],sorts[x][:10],label=x+' sort') 
        h.append(t)
# c = 'merge'
# plt.yticks([x for x in range(0,int(sorts[c][-1]*1.2),int(sorts[c][-1]*1.2)//10)])
# plt.xticks([x for x in range(0,900001,100000)])
# t, = plt.plot(s[:len(sorts['quick'])],sorts['quick'],label='Quick') 
# h.append(t)
    plt.ylabel("Microseconds")
    plt.xlabel("Number of elements")
    fontP = FontProperties()        
    fontP.set_size('medium')


    plt.legend(handles=h,title=name, bbox_to_anchor=(1.05, 1), loc='upper left', prop=fontP)