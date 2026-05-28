# Three-Address Code (TAC) - Unoptimized

 1: DECL int globalX
 2: FUNC_BEGIN Master
 3: DECL int x
 4: DECL int y
 5: x = 10
 6: y = 20
 7: DECL int z
 8: t0 = x + y
 9: z = t0
10: PRINT z
11: x = t1
12: PRINT x
13: y = t2
14: PRINT y
15: globalX = x
16: RETURN
17: FUNC_END Master
