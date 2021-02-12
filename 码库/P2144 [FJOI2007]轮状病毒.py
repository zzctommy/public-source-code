def det(n, a):
    res = 1
    for i in range(n):
        for j in range(i + 1, n):
            while a[j][i] != 0:
                div = a[i][i] / a[j][i]
                for k in range(i, n):
                    a[i][k] -= a[j][k] * div
                    tmp = a[i][k]
                    a[i][k] = a[j][k]
                    a[j][k] = tmp
                res *= -1
        res *= a[i][i]
    return res

n = int(input())
if n == 1:
    print 1
    exit()
if n == 2:
    print 5
    exit()
a = [[0 for i in range(n + 1)]for i in range(n + 1)]
for i in range(0, n):
    a[i][i] = 3
    if i == 0:
        a[i][n - 1] = -1
    else:
        a[i][i - 1] = -1
    if i == n - 1:
        a[i][0] = -1
    else:
        a[i][i + 1] = -1
    a[i][n] = -1
a[n][n] = n
for i in range(0, n):
    a[n][i] = -1
print det(n, a)