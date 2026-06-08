# Three-Address Code (TAC) - Unoptimized

 1: FUNC_BEGIN Add
 2: DECL int a
 3: DECL int b
 4: t0 = a + b
 5: RETURN t0
 6: FUNC_END Add
 7: FUNC_BEGIN Master
 8: DECL int x
 9: P0 = 5
10: P1 = 7
11: t1 = CALL Add
12: x = t1
13: PRINT x
14: FUNC_END Master
