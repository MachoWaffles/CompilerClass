# Three-Address Code (TAC) - Optimized

 1: FUNC_BEGIN Master
 2: DECL int x
 3: x = 1
 4: LABEL L0
 5: t0 = x < 4
 6: IF_FALSE t0 GOTO L1
 7: t1 = x + 1
 8: x = t1
 9: GOTO L0
10: LABEL L1
11: FUNC_END Master
