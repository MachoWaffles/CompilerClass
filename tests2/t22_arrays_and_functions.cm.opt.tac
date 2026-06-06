# Three-Address Code (TAC) - Optimized

 1: FUNC_BEGIN double
 2: DECL int n
 3: t0 = n + n
 4: RETURN t0
 5: FUNC_END double
 6: FUNC_BEGIN Master
 7: DECL int vals
 8: DECL int sum
 9: sum = 0
10: DECL int j
11: j = 0
12: t2 = 0 + vals[j]
13: sum = t2
14: t3 = 1
15: j = 1
16: PRINT t2
17: FUNC_END Master
