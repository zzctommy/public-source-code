class nd:
    e = 0
    r = 0
N = 100005
a = [nd() for i in range(N)]
# nmd, I is a English men. I don't know how to use sort!!!
def msort(l, r) :
    if (r - l <= 1) : 
        return
    mid = (l + r) / 2
    msort(l, mid)
    msort(mid, r)
    i = l 
    j = mid
    b=[]
    while i < mid and j < r : 
        if a[i].e < a[j].e : 
            b.append(a[i])
            i += 1
        else : 
            b.append(a[j])
            j += 1
    while i < mid : 
        b.append(a[i])
        i += 1
    while j < r : 
        b.append(a[j])
        j += 1
    for i in range(l, r) :
        a[i] = b[i - l]


def gcd(x, y) :
    while y > 0 :
        t = x % y
        x = y
        y = t
    return x

s = raw_input().split()
b = int(s[0])
n = int(s[1])
q = int(s[2])
for i in range(n) :
    s = raw_input().split()
    a[i].e = int(s[0])
    a[i].r = int(s[1])
msort(0, n)
c = []
cnt = 0
for i in range(n - 1) : 
    if a[i].e > 1000 and a[i + 1].e - a[i].e < 10000 : 
        c.append(a[i].r * pow(b, a[i + 1].e - a[i].e) - a[i + 1].r)
        cnt += 1
        if cnt >= 5 :
            break
m = c[0]
for i in c :
    m = gcd(m, i)
for i in range(q) :
    x = int(input())
    print pow(b, x, m)