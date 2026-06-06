# Three-Address Code (TAC) - Optimized

 1: FUNC_BEGIN addInts
 2: DECL int a
 3: DECL int b
 4: DECL int result
 5: t0 = a + b
 6: result = t0
 7: RETURN result
 8: FUNC_END addInts
 9: FUNC_BEGIN printValue
10: DECL int v
11: PRINT v
12: RETURN
13: FUNC_END printValue
14: FUNC_BEGIN Master
15: DECL int s
16: P0 = 3
17: P1 = 4
18: t1 = CALL addInts
19: s = t1
20: PRINT t1
21: FUNC_END Master
