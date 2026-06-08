# Three-Address Code (TAC) - Optimized

 1: DECL int globalSeed
 2: globalSeed = 5
 3: FUNC_BEGIN addInts
 4: DECL int a
 5: DECL int b
 6: t0 = a + b
 7: RETURN t0
 8: FUNC_END addInts
 9: FUNC_BEGIN Master
10: PRINT 5
11: t1 = 10
12: globalSeed = 10
13: PRINT 10
14: DECL bool flag
15: flag = 1
16: PRINT 1
17: DECL char letter
18: letter = 65
19: PRINT 65
20: DECL int s
21: P0 = 7
22: P1 = 8
23: t2 = CALL addInts
24: s = t2
25: PRINT t2
26: DECL int acc
27: acc = 0
28: DECL int k
29: k = 1
30: t4 = 1
31: acc = 1
32: t5 = 2
33: k = 2
34: PRINT 1
35: PRINT (null)
36: FUNC_END Master
