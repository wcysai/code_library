#!/usr/bin/python2
from fractions import *

def polyadd(a, b) : return map(lambda x, y : (x or 0) + (y or 0), a, b)

def polymul(a, b) :
    p = [0] * (len(a)+len(b)-1)
    for e1, c1 in enumerate(a) :
        for e2, c2 in enumerate(b) :
            p[e1 + e2] += c1 * c2
    return p

x, y = [map(Fraction, raw_input().split()) for _ in 0,0]
n = len(x)
lj = [reduce(polymul, [[-x[m]/(x[j]-x[m]), 1/(x[j]-x[m])]
    for m in range(n) if m != j]) for j in range(n)]
print ' '.join(map(str, reduce(polyadd, 
    map(lambda a, b : [x * a for x in b], y, lj))))
