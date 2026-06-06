# Three-Address Code (TAC) - Unoptimized

 1: FUNC_BEGIN Master
 2: DECL int a
 3: a = 5
 4: PRINT a
 5: DECL int b
 6: b = 3
 7: PRINT b
 8: DECL int sum
 9: t0 = a + b
10: sum = t0
11: PRINT sum
12: DECL int diff
13: t1 = a - b
14: diff = t1
15: PRINT diff
16: DECL int prod
17: t2 = a * b
18: prod = t2
19: PRINT prod
20: DECL int quot
21: t3 = a / b
22: quot = t3
23: PRINT quot
24: DECL int compound
25: t4 = a + b
26: t5 = t4 * 2
27: compound = t5
28: PRINT compound
29: FUNC_END Master
