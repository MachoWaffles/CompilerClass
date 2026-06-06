# Three-Address Code (TAC) - Optimized

 1: FUNC_BEGIN Master
 2: DECL int a
 3: P0 = 3
 4: P1 = 5
 5: t0 = CALL addTwo
 6: a = t0
 7: PRINT t0
 8: DECL int b
 9: P0 = 5
10: t1 = CALL sumTo
11: b = t1
12: PRINT t1
13: FUNC_END Master
14: FUNC_BEGIN addTwo
15: DECL int x
16: DECL int y
17: t2 = x + y
18: RETURN t2
19: FUNC_END addTwo
20: FUNC_BEGIN sumTo
21: DECL int n
22: DECL int total
23: total = 0
24: DECL int i
25: i = 1
26: t4 = 1
27: total = 1
28: t5 = 2
29: i = 2
30: RETURN total
31: FUNC_END sumTo
