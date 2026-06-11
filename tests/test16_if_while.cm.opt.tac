# Three-Address Code (TAC) - Optimized

 1: FUNC_BEGIN Master
 2: DECL float x
 3: x = 10
 4: t0 = x > 0
 5: IF_FALSE t0 GOTO L1
 6: LABEL L2
 7: t1 = x > 2
 8: IF_FALSE t1 GOTO L3
 9: t2 = x - 1
10: x = t2
11: t3 = x / 2
12: t4 = t3 == 0
13: IF_FALSE t4 GOTO L4
14: PRINT 1
15: GOTO L5
16: LABEL L4
17: PRINT 2
18: LABEL L5
19: GOTO L2
20: LABEL L3
21: LABEL L1
22: FUNC_END Master
