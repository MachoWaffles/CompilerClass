# Three-Address Code (TAC) - Optimized

 1: FUNC_BEGIN Master
 2: DECL int result
 3: P0 = 5
 4: P1 = 3
 5: t0 = CALL helper
 6: result = t0
 7: PRINT t0
 8: RETURN
 9: FUNC_END Master
10: FUNC_BEGIN helper
11: DECL int a
12: DECL int b
13: DECL int sum
14: t1 = a + b
15: sum = t1
16: RETURN sum
17: FUNC_END helper
