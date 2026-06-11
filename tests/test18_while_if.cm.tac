# Three-Address Code (TAC) - Unoptimized

 1: FUNC_BEGIN Master
 2: DECL int x
 3: x = 1
 4: LABEL L0
 5: t0 = x < 6
 6: IF_FALSE t0 GOTO L1
 7: t1 = x == 3
 8: IF_FALSE t1 GOTO L2
 9: PRINT 99
10: GOTO L3
11: LABEL L2
12: PRINT x
13: LABEL L3
14: t2 = x + 1
15: x = t2
16: GOTO L0
17: LABEL L1
18: FUNC_END Master
