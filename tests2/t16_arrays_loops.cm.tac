# Three-Address Code (TAC) - Unoptimized

 1: FUNC_BEGIN Master
 2: DECL int arr
 3: DECL int sum
 4: sum = 0
 5: DECL int j
 6: j = 0
 7: LABEL L0
 8: IF_FALSE t0 GOTO L1
 9: t1 = sum + arr[j]
10: sum = t1
11: t2 = j + 1
12: j = t2
13: GOTO L0
14: LABEL L1
15: PRINT sum
16: FUNC_END Master
