# Three-Address Code (TAC) - Optimized

 1: FUNC_BEGIN Master
 2: DECL int x
 3: x = 3
 4: t0 = x > 0
 5: IF_FALSE t0 GOTO L1
 6: LABEL L2
 7: t1 = x > 0
 8: IF_FALSE t1 GOTO L3
 9: t2 = x == 2
10: IF_FALSE t2 GOTO L4
11: PRINT 99
12: GOTO L5
13: LABEL L4
14: PRINT x
15: LABEL L5
16: t3 = x - 1
17: x = t3
18: GOTO L2
19: LABEL L3
20: LABEL L1
21: FUNC_END Master
