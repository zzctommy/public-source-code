

def gcd(x, y) :
    while y > 0 :
        t = x % y
        x = y
        y = t
    return x

x=input()
y=input()
print gcd(x,y)