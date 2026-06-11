# Three-Address Code (TAC) - Unoptimized

 1: FUNC_BEGIN Master
 2: DECL int x
 3: x = 3
 4: LABEL L0
 5: IF_FALSE x GOTO L1
 6: PRINT x
 7: t0 = x - 1
 8: x = t0
 9: GOTO L0
10: LABEL L1
11: FUNC_END Master
