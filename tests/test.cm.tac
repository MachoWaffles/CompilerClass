# Three-Address Code (TAC) - Unoptimized

 1: DECL float globalX
 2: FUNC_BEGIN Master
 3: DECL float x
 4: DECL int y
 5: DECL bool s
 6: s = 1
 7: x = 10
 8: y = 20
 9: DECL char c
10: c = 103
11: DECL float z
12: t0 = y / x
13: t1 = t0 * 10
14: t2 = 3 * y
15: t3 = t1 / t2
16: z = t3
17: PRINT z
18: t4 = z * 2
19: x = t4
20: PRINT x
21: PRINT y
22: PRINT s
23: t5 = c + x
24: PRINT t5
25: globalX = x
26: RETURN
27: FUNC_END Master
