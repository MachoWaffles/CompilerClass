# Three-Address Code (TAC) - Unoptimized

 1: FUNC_BEGIN Master
 2: DECL int x
 3: x = 10
 4: DECL int y
 5: y = 4
 6: t0 = x > 0
 7: IF_FALSE t0 GOTO L1
 8: t1 = x < 20
 9: IF_FALSE t1 GOTO L3
10: t2 = y > 5
11: IF_FALSE t2 GOTO L4
12: t3 = y < 7
13: IF_FALSE t3 GOTO L7
14: PRINT 4
15: LABEL L7
16: GOTO L5
17: LABEL L4
18: PRINT 2
19: LABEL L5
20: LABEL L3
21: LABEL L1
22: FUNC_END Master
