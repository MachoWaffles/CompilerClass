# Three-Address Code (TAC) - Unoptimized

 1: DECL int globalSeed
 2: globalSeed = 5
 3: FUNC_BEGIN addInts
 4: DECL int a
 5: DECL int b
 6: t0 = a + b
 7: RETURN t0
 8: FUNC_END addInts
 9: FUNC_BEGIN Master
10: PRINT globalSeed
11: t1 = globalSeed + 5
12: globalSeed = t1
13: PRINT globalSeed
14: DECL bool flag
15: flag = 1
16: PRINT flag
17: DECL char letter
18: letter = 65
19: PRINT letter
20: DECL int s
21: P0 = 7
22: P1 = 8
23: t2 = CALL addInts
24: s = t2
25: PRINT s
26: DECL int acc
27: acc = 0
28: DECL int k
29: k = 1
30: LABEL L0
31: IF_FALSE t3 GOTO L1
32: t4 = acc + k
33: acc = t4
34: t5 = k + 1
35: k = t5
36: GOTO L0
37: LABEL L1
38: PRINT acc
39: PRINT (null)
40: FUNC_END Master
