# Three-Address Code (TAC) - Unoptimized

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
12: LABEL L0
13: IF_FALSE t1 GOTO L1
14: t2 = sum + vals[j]
15: sum = t2
16: t3 = j + 1
17: j = t3
18: GOTO L0
19: LABEL L1
20: PRINT sum
21: FUNC_END Master
