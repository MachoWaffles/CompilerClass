# Three-Address Code (TAC) - Unoptimized

 1: DECL int g
 2: g = 100
 3: FUNC_BEGIN funcA
 4: DECL int x
 5: x = 1
 6: RETURN x
 7: FUNC_END funcA
 8: FUNC_BEGIN funcB
 9: DECL int x
10: x = 2
11: RETURN x
12: FUNC_END funcB
13: FUNC_BEGIN Master
14: PRINT g
15: DECL int a
16: t0 = CALL funcA
17: a = t0
18: PRINT a
19: DECL int b
20: t1 = CALL funcB
21: b = t1
22: PRINT b
23: PRINT g
24: FUNC_END Master
