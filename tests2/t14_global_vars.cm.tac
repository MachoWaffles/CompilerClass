# Three-Address Code (TAC) - Unoptimized

 1: DECL int counter
 2: DECL int step
 3: step = 10
 4: FUNC_BEGIN increment
 5: t0 = counter + step
 6: counter = t0
 7: RETURN
 8: FUNC_END increment
 9: FUNC_BEGIN Master
10: counter = 0
11: PRINT counter
12: PRINT counter
13: PRINT counter
14: PRINT counter
15: FUNC_END Master
