# Three-Address Code (TAC) - Unoptimized

 1: FUNC_BEGIN Master
 2: DECL int i
 3: i = 1
 4: LABEL L0
 5: t0 = i < 3
 6: IF_FALSE t0 GOTO L1
 7: DECL int j
 8: j = 1
 9: LABEL L2
10: t1 = j < 3
11: IF_FALSE t1 GOTO L3
12: DECL int k
13: k = 1
14: LABEL L4
15: t2 = k < 3
16: IF_FALSE t2 GOTO L5
17: PRINT k
18: t3 = k + 1
19: k = t3
20: GOTO L4
21: LABEL L5
22: t4 = j + 1
23: j = t4
24: GOTO L2
25: LABEL L3
26: t5 = i + 1
27: i = t5
28: GOTO L0
29: LABEL L1
30: FUNC_END Master
