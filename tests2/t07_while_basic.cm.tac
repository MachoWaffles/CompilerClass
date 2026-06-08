# Three-Address Code (TAC) - Unoptimized

 1: FUNC_BEGIN Master
 2: DECL int i
 3: i = 0
 4: LABEL L0
 5: IF_FALSE t0 GOTO L1
 6: PRINT i
 7: t1 = i + 1
 8: i = t1
 9: GOTO L0
10: LABEL L1
11: DECL int j
12: j = 10
13: LABEL L2
14: IF_FALSE t2 GOTO L3
15: PRINT j
16: t3 = j - 2
17: j = t3
18: GOTO L2
19: LABEL L3
20: FUNC_END Master
