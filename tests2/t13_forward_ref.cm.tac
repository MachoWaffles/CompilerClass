# Three-Address Code (TAC) - Unoptimized

 1: FUNC_BEGIN Master
 2: DECL int a
 3: P0 = 3
 4: P1 = 5
 5: t0 = CALL addTwo
 6: a = t0
 7: PRINT a
 8: DECL int b
 9: P0 = 5
10: t1 = CALL sumTo
11: b = t1
12: PRINT b
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
26: LABEL L0
27: IF_FALSE t3 GOTO L1
28: t4 = total + i
29: total = t4
30: t5 = i + 1
31: i = t5
32: GOTO L0
33: LABEL L1
34: RETURN total
35: FUNC_END sumTo
