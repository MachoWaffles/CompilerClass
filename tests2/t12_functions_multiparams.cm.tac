# Three-Address Code (TAC) - Unoptimized

 1: FUNC_BEGIN multiply
 2: DECL int a
 3: DECL int b
 4: t0 = a * b
 5: RETURN t0
 6: FUNC_END multiply
 7: FUNC_BEGIN subtract
 8: DECL int a
 9: DECL int b
10: t1 = a - b
11: RETURN t1
12: FUNC_END subtract
13: FUNC_BEGIN Master
14: DECL int r1
15: P0 = 2
16: P1 = 5
17: t2 = CALL multiply
18: r1 = t2
19: PRINT r1
20: DECL int r2
21: P0 = 10
22: P1 = 4
23: t3 = CALL subtract
24: r2 = t3
25: PRINT r2
26: FUNC_END Master
