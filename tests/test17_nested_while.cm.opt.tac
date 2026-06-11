# Three-Address Code (TAC) - Optimized

 1: FUNC_BEGIN Master
 2: DECL int i
 3: i = 1
 4: LABEL L0
 5: t0 = i < 4
 6: IF_FALSE t0 GOTO L1
 7: DECL int j
 8: j = 1
 9: LABEL L2
10: t1 = j < 4
11: IF_FALSE t1 GOTO L3
12: PRINT j
13: t2 = j + 1
14: j = t2
15: GOTO L2
16: LABEL L3
17: t3 = i + 1
18: i = t3
19: GOTO L0
20: LABEL L1
21: FUNC_END Master
