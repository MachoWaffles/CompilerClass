# Three-Address Code (TAC) - Optimized

 1: DECL int globalCounter
 2: FUNC_BEGIN add
 3: DECL int a
 4: DECL int b
 5: DECL int result
 6: t0 = a + b
 7: result = t0
 8: RETURN result
 9: FUNC_END add
10: FUNC_BEGIN scale
11: DECL float x
12: DECL float doubled
13: t1 = x + x
14: doubled = t1
15: RETURN doubled
16: FUNC_END scale
17: FUNC_BEGIN describeChar
18: DECL char c
19: DECL bool loud
20: DECL char code
21: code = c
22: PRINT c
23: RETURN
24: FUNC_END describeChar
25: FUNC_BEGIN Master
26: globalCounter = 0
27: DECL int sum
28: P0 = 3
29: P1 = 4
30: t2 = CALL add
31: sum = t2
32: PRINT t2
33: DECL float pi
34: pi = 3.14
35: DECL bool flag
36: flag = 1
37: DECL char letter
38: letter = 65
39: RETURN
40: FUNC_END Master
