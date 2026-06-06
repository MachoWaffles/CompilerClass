# Three-Address Code (TAC) - Unoptimized

 1: FUNC_BEGIN Master
 2: DECL int sum
 3: sum = 0
 4: DECL int n
 5: n = 1
 6: LABEL L0
 7: IF_FALSE t0 GOTO L1
 8: t1 = sum + n
 9: sum = t1
10: t2 = n + 1
11: n = t2
12: GOTO L0
13: LABEL L1
14: PRINT sum
15: DECL int outer
16: outer = 1
17: LABEL L2
18: IF_FALSE t3 GOTO L3
19: DECL int inner
20: inner = 1
21: LABEL L4
22: IF_FALSE t4 GOTO L5
23: PRINT inner
24: t5 = inner + 1
25: inner = t5
26: GOTO L4
27: LABEL L5
28: t6 = outer + 1
29: outer = t6
30: GOTO L2
31: LABEL L3
32: FUNC_END Master
