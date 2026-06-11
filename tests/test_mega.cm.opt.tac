# Three-Address Code (TAC) - Optimized

 1: DECL int gIntA
 2: gIntA = 100
 3: DECL int gIntB
 4: gIntB = 200
 5: DECL int gSeed
 6: gSeed = 7
 7: DECL int gStep
 8: gStep = 3
 9: DECL float gPi
10: gPi = 3.14
11: DECL char gLetter
12: gLetter = 65
13: DECL bool gTrue
14: gTrue = 1
15: DECL bool gFalse
16: gFalse = 0
17: FUNC_BEGIN addTwo
18: DECL int a
19: DECL int b
20: t0 = a + b
21: RETURN t0
22: FUNC_END addTwo
23: FUNC_BEGIN mul
24: DECL int a
25: DECL int b
26: t1 = a * b
27: RETURN t1
28: FUNC_END mul
29: FUNC_BEGIN maxOf
30: DECL int a
31: DECL int b
32: t2 = a > b
33: IF_FALSE t2 GOTO L0
34: RETURN a
35: GOTO L1
36: LABEL L0
37: RETURN b
38: LABEL L1
39: FUNC_END maxOf
40: FUNC_BEGIN fact
41: DECL int n
42: t3 = n <= 1
43: IF_FALSE t3 GOTO L3
44: RETURN 1
45: LABEL L3
46: t4 = n - 1
47: P0 = t4
48: t5 = CALL fact
49: t6 = n * t5
50: RETURN t6
51: FUNC_END fact
52: FUNC_BEGIN halfOf
53: DECL int n
54: DECL float f
55: f = n
56: t7 = f / 2
57: RETURN t7
58: FUNC_END halfOf
59: FUNC_BEGIN getZ
60: RETURN 90
61: FUNC_END getZ
62: FUNC_BEGIN isPos
63: DECL int n
64: t8 = n > 0
65: IF_FALSE t8 GOTO L4
66: RETURN 1
67: GOTO L5
68: LABEL L4
69: RETURN 0
70: LABEL L5
71: FUNC_END isPos
72: FUNC_BEGIN printVal
73: DECL int v
74: PRINT v
75: RETURN
76: FUNC_END printVal
77: FUNC_BEGIN doNothing
78: FUNC_END doNothing
79: FUNC_BEGIN Master
80: PRINT gIntA
81: PRINT gIntB
82: PRINT gSeed
83: PRINT gStep
84: PRINT gPi
85: PRINT gLetter
86: PRINT gTrue
87: PRINT gFalse
88: DECL int a
89: a = 10
90: DECL int b
91: b = 5
92: DECL int r_add
93: t9 = a + b
94: r_add = t9
95: PRINT r_add
96: DECL int r_sub
97: t10 = a - b
98: r_sub = t10
99: PRINT r_sub
100: DECL int r_mul
101: t11 = a * b
102: r_mul = t11
103: PRINT r_mul
104: DECL int r_div
105: t12 = a / b
106: r_div = t12
107: PRINT r_div
108: DECL int r_prec
109: t13 = 4
110: t14 = 6
111: r_prec = 6
112: PRINT r_prec
113: DECL int r_paren
114: t15 = 4
115: t16 = 8
116: r_paren = 8
117: PRINT r_paren
118: DECL int r_ltr
119: t17 = 17
120: t18 = 15
121: r_ltr = 15
122: PRINT r_ltr
123: DECL int r_idiv
124: t19 = 3
125: r_idiv = 3
126: PRINT r_idiv
127: DECL int negOne
128: t20 = -1
129: negOne = -1
130: PRINT negOne
131: DECL float f1
132: f1 = 5
133: DECL float f2
134: f2 = 2
135: DECL float f_div
136: t21 = f1 / f2
137: f_div = t21
138: PRINT f_div
139: DECL float f_add
140: t22 = f1 + f2
141: f_add = t22
142: PRINT f_add
143: DECL float f_mul
144: t23 = f1 * f2
145: f_mul = t23
146: PRINT f_mul
147: DECL float f_sub
148: t24 = f1 - f2
149: f_sub = t24
150: PRINT f_sub
151: DECL float f_wide
152: f_wide = 10
153: PRINT f_wide
154: DECL float f_mix
155: t25 = f1 + 3
156: f_mix = t25
157: PRINT f_mix
158: DECL bool cmp_lt
159: t26 = a < b
160: cmp_lt = t26
161: PRINT cmp_lt
162: DECL bool cmp_gt
163: t27 = a > b
164: cmp_gt = t27
165: PRINT cmp_gt
166: DECL bool cmp_le
167: t28 = b <= 5
168: cmp_le = t28
169: PRINT cmp_le
170: DECL bool cmp_ge
171: t29 = b >= 6
172: cmp_ge = t29
173: PRINT cmp_ge
174: DECL bool cmp_eq
175: t30 = a == 10
176: cmp_eq = t30
177: PRINT cmp_eq
178: DECL bool cmp_ne
179: t31 = a != 10
180: cmp_ne = t31
181: PRINT cmp_ne
182: DECL char c_nl
183: c_nl = 10
184: DECL char c_tab
185: c_tab = 9
186: DECL char c_bs
187: c_bs = 92
188: DECL char c_A
189: c_A = 65
190: PRINT c_nl
191: PRINT c_tab
192: PRINT c_bs
193: PRINT c_A
194: DECL bool bt
195: bt = 1
196: DECL bool bf
197: bf = 0
198: PRINT bt
199: PRINT bf
200: DECL int s_add
201: P0 = 13
202: P1 = 17
203: t32 = CALL addTwo
204: s_add = t32
205: PRINT s_add
206: DECL int s_mul
207: P0 = 6
208: P1 = 7
209: t33 = CALL mul
210: s_mul = t33
211: PRINT s_mul
212: DECL int s_max1
213: P0 = 3
214: P1 = 9
215: t34 = CALL maxOf
216: s_max1 = t34
217: PRINT s_max1
218: DECL int s_max2
219: P0 = 9
220: P1 = 3
221: t35 = CALL maxOf
222: s_max2 = t35
223: PRINT s_max2
224: DECL bool p_pos
225: P0 = 5
226: t36 = CALL isPos
227: p_pos = t36
228: PRINT p_pos
229: DECL bool p_neg
230: P0 = negOne
231: t37 = CALL isPos
232: p_neg = t37
233: PRINT p_neg
234: DECL float hf
235: P0 = 5
236: t38 = CALL halfOf
237: hf = t38
238: PRINT hf
239: DECL char zc
240: t39 = CALL getZ
241: zc = t39
242: PRINT zc
243: DECL int fw
244: P0 = 10
245: t40 = CALL lateHelper
246: fw = t40
247: PRINT fw
248: DECL int fac5
249: P0 = 5
250: t41 = CALL fact
251: fac5 = t41
252: PRINT fac5
253: DECL int fac0
254: P0 = 0
255: t42 = CALL fact
256: fac0 = t42
257: PRINT fac0
258: DECL int nums
259: nums[0] = 10
260: nums[1] = 20
261: nums[2] = 30
262: nums[3] = 40
263: nums[4] = 50
264: PRINT nums[0]
265: PRINT nums[1]
266: PRINT nums[2]
267: PRINT nums[3]
268: PRINT nums[4]
269: DECL int arr_sum
270: arr_sum = 0
271: DECL int arr_i
272: arr_i = 0
273: LABEL L6
274: t43 = arr_i < 5
275: IF_FALSE t43 GOTO L7
276: t44 = arr_sum + nums[arr_i]
277: arr_sum = t44
278: t45 = arr_i + 1
279: arr_i = t45
280: GOTO L6
281: LABEL L7
282: PRINT arr_sum
283: DECL int dbl
284: t46 = nums[2] * 2
285: dbl = t46
286: PRINT dbl
287: DECL int pair
288: t47 = nums[1] + nums[3]
289: pair = t47
290: PRINT pair
291: DECL float farr
292: farr[0] = 1.5
293: farr[1] = 2.5
294: farr[2] = 3.5
295: PRINT farr[0]
296: PRINT farr[1]
297: PRINT farr[2]
298: DECL bool barr
299: barr[0] = 1
300: barr[1] = 0
301: PRINT barr[0]
302: PRINT barr[1]
303: DECL char carr
304: carr[0] = 67
305: carr[1] = 83
306: carr[2] = 84
307: PRINT carr[0]
308: PRINT carr[1]
309: PRINT carr[2]
310: DECL int sq
311: DECL int i
312: i = 0
313: LABEL L8
314: t48 = i < 5
315: IF_FALSE t48 GOTO L9
316: t49 = i * i
317: sq[i] = t49
318: t50 = i + 1
319: i = t50
320: GOTO L8
321: LABEL L9
322: DECL int i
323: i = 0
324: LABEL L10
325: t51 = i < 5
326: IF_FALSE t51 GOTO L11
327: PRINT sq[i]
328: t52 = i + 1
329: i = t52
330: GOTO L10
331: LABEL L11
332: DECL int fcall_arr
333: P0 = 1
334: P1 = 2
335: t53 = CALL addTwo
336: fcall_arr[0] = t53
337: P0 = 3
338: P1 = 4
339: t54 = CALL mul
340: fcall_arr[1] = t54
341: P0 = 10
342: P1 = 20
343: t55 = CALL addTwo
344: fcall_arr[2] = t55
345: PRINT fcall_arr[0]
346: PRINT fcall_arr[1]
347: PRINT fcall_arr[2]
348: DECL int big
349: DECL int i
350: i = 0
351: LABEL L12
352: t56 = i < 10
353: IF_FALSE t56 GOTO L13
354: t57 = i * 3
355: big[i] = t57
356: t58 = i + 1
357: i = t58
358: GOTO L12
359: LABEL L13
360: DECL int big_sum
361: big_sum = 0
362: DECL int i
363: i = 0
364: LABEL L14
365: t59 = i < 10
366: IF_FALSE t59 GOTO L15
367: t60 = big_sum + big[i]
368: big_sum = t60
369: t61 = i + 1
370: i = t61
371: GOTO L14
372: LABEL L15
373: PRINT big_sum
374: PRINT (null)
375: PRINT (null)
376: DECL int pt_sum
377: t62 = (null) + (null)
378: pt_sum = t62
379: PRINT pt_sum
380: PRINT (null)
381: PRINT (null)
382: DECL int area
383: t63 = (null) * (null)
384: area = t63
385: PRINT area
386: DECL int farg
387: P0 = (null)
388: P1 = (null)
389: t64 = CALL addTwo
390: farg = t64
391: PRINT farg
392: PRINT (null)
393: LABEL L16
394: t65 = (null) < (null)
395: IF_FALSE t65 GOTO L17
396: PRINT (null)
397: GOTO L16
398: LABEL L17
399: DECL int i
400: i = 0
401: LABEL L18
402: t66 = i < 4
403: IF_FALSE t66 GOTO L19
404: t67 = i + 1
405: i = t67
406: GOTO L18
407: LABEL L19
408: PRINT (null)
409: DECL int wi
410: wi = 1
411: LABEL L20
412: t68 = wi <= 5
413: IF_FALSE t68 GOTO L21
414: PRINT wi
415: t69 = wi + 1
416: wi = t69
417: GOTO L20
418: LABEL L21
419: DECL int acc
420: acc = 0
421: DECL int wj
422: wj = 1
423: LABEL L22
424: t70 = wj <= 5
425: IF_FALSE t70 GOTO L23
426: t71 = acc + wj
427: acc = t71
428: t72 = wj + 1
429: wj = t72
430: GOTO L22
431: LABEL L23
432: PRINT acc
433: DECL int wk
434: wk = 10
435: LABEL L24
436: t73 = wk == 10
437: IF_FALSE t73 GOTO L25
438: PRINT wk
439: t74 = wk + 1
440: wk = t74
441: GOTO L24
442: LABEL L25
443: DECL int wm
444: wm = 3
445: LABEL L26
446: t75 = wm != 0
447: IF_FALSE t75 GOTO L27
448: PRINT wm
449: t76 = wm - 1
450: wm = t76
451: GOTO L26
452: LABEL L27
453: DECL int wn
454: wn = 3
455: LABEL L28
456: t77 = wn >= 1
457: IF_FALSE t77 GOTO L29
458: PRINT wn
459: t78 = wn - 1
460: wn = t78
461: GOTO L28
462: LABEL L29
463: DECL int wo
464: wo = 1
465: LABEL L30
466: t79 = wo <= 3
467: IF_FALSE t79 GOTO L31
468: PRINT wo
469: t80 = wo + 1
470: wo = t80
471: GOTO L30
472: LABEL L31
473: DECL int ni
474: ni = 1
475: LABEL L32
476: t81 = ni <= 3
477: IF_FALSE t81 GOTO L33
478: DECL int nj
479: nj = 1
480: LABEL L34
481: t82 = nj <= 3
482: IF_FALSE t82 GOTO L35
483: PRINT nj
484: t83 = nj + 1
485: nj = t83
486: GOTO L34
487: LABEL L35
488: t84 = ni + 1
489: ni = t84
490: GOTO L32
491: LABEL L33
492: DECL int wi2
493: wi2 = 1
494: LABEL L36
495: t85 = wi2 <= 6
496: IF_FALSE t85 GOTO L37
497: t86 = wi2 == 3
498: IF_FALSE t86 GOTO L39
499: PRINT 300
500: LABEL L39
501: t87 = wi2 + 1
502: wi2 = t87
503: GOTO L36
504: LABEL L37
505: DECL bool running
506: running = 1
507: DECL int cnt
508: cnt = 0
509: LABEL L40
510: t88 = running == 1
511: IF_FALSE t88 GOTO L41
512: t89 = cnt + 1
513: cnt = t89
514: t90 = cnt == 3
515: IF_FALSE t90 GOTO L43
516: running = 0
517: LABEL L43
518: GOTO L40
519: LABEL L41
520: PRINT cnt
521: DECL int never
522: never = 0
523: LABEL L44
524: t91 = never > 999
525: IF_FALSE t91 GOTO L45
526: GOTO L44
527: LABEL L45
528: DECL int i
529: i = 0
530: LABEL L46
531: t92 = i < 5
532: IF_FALSE t92 GOTO L47
533: PRINT i
534: t93 = i + 1
535: i = t93
536: GOTO L46
537: LABEL L47
538: DECL int i
539: i = 10
540: LABEL L48
541: t94 = i <= 30
542: IF_FALSE t94 GOTO L49
543: PRINT i
544: t95 = i + 10
545: i = t95
546: GOTO L48
547: LABEL L49
548: DECL int even_sum
549: even_sum = 0
550: DECL int i
551: i = 0
552: LABEL L50
553: t96 = i < 6
554: IF_FALSE t96 GOTO L51
555: t97 = i == 2
556: IF_FALSE t97 GOTO L53
557: t98 = even_sum + i
558: even_sum = t98
559: LABEL L53
560: t99 = i == 4
561: IF_FALSE t99 GOTO L55
562: t100 = even_sum + i
563: even_sum = t100
564: LABEL L55
565: t101 = i + 1
566: i = t101
567: GOTO L50
568: LABEL L51
569: PRINT even_sum
570: DECL int i
571: i = 1
572: LABEL L56
573: t102 = i <= 2
574: IF_FALSE t102 GOTO L57
575: DECL int j
576: j = 1
577: LABEL L58
578: t103 = j <= 2
579: IF_FALSE t103 GOTO L59
580: DECL int prod
581: t104 = i * j
582: prod = t104
583: PRINT prod
584: t105 = j + 1
585: j = t105
586: GOTO L58
587: LABEL L59
588: t106 = i + 1
589: i = t106
590: GOTO L56
591: LABEL L57
592: DECL int lsum1
593: lsum1 = 0
594: DECL int i
595: i = 0
596: LABEL L60
597: t107 = i < 5
598: IF_FALSE t107 GOTO L61
599: t108 = lsum1 + i
600: lsum1 = t108
601: t109 = i + 1
602: i = t109
603: GOTO L60
604: LABEL L61
605: PRINT lsum1
606: DECL int lsum2
607: lsum2 = 0
608: DECL int i
609: i = 0
610: LABEL L62
611: t110 = i < 5
612: IF_FALSE t110 GOTO L63
613: t111 = i * 2
614: t112 = lsum2 + t111
615: lsum2 = t112
616: t113 = i + 1
617: i = t113
618: GOTO L62
619: LABEL L63
620: PRINT lsum2
621: DECL int call_acc
622: call_acc = 0
623: DECL int i
624: i = 1
625: LABEL L64
626: t114 = i <= 4
627: IF_FALSE t114 GOTO L65
628: P0 = i
629: P1 = i
630: t115 = CALL addTwo
631: t116 = call_acc + t115
632: call_acc = t116
633: t117 = i + 1
634: i = t117
635: GOTO L64
636: LABEL L65
637: PRINT call_acc
638: DECL int i
639: i = 0
640: LABEL L66
641: t118 = i < 0
642: IF_FALSE t118 GOTO L67
643: t119 = i + 1
644: i = t119
645: GOTO L66
646: LABEL L67
647: DECL int iv
648: iv = 5
649: t120 = iv > 0
650: IF_FALSE t120 GOTO L69
651: PRINT 10
652: LABEL L69
653: t121 = iv > 100
654: IF_FALSE t121 GOTO L71
655: PRINT 9999
656: LABEL L71
657: t122 = iv == 5
658: IF_FALSE t122 GOTO L72
659: PRINT 20
660: GOTO L73
661: LABEL L72
662: PRINT 21
663: LABEL L73
664: t123 = iv == 99
665: IF_FALSE t123 GOTO L74
666: PRINT 99
667: GOTO L75
668: LABEL L74
669: PRINT 30
670: LABEL L75
671: DECL int grade
672: grade = 75
673: t124 = grade >= 90
674: IF_FALSE t124 GOTO L76
675: PRINT 4
676: GOTO L77
677: LABEL L76
678: t125 = grade >= 80
679: IF_FALSE t125 GOTO L78
680: PRINT 3
681: GOTO L79
682: LABEL L78
683: t126 = grade >= 70
684: IF_FALSE t126 GOTO L80
685: PRINT 2
686: GOTO L81
687: LABEL L80
688: PRINT 1
689: LABEL L81
690: LABEL L79
691: LABEL L77
692: IF_FALSE 0 GOTO L82
693: GOTO L83
694: LABEL L82
695: PRINT 888
696: LABEL L83
697: IF_FALSE 1 GOTO L84
698: PRINT 777
699: GOTO L85
700: LABEL L84
701: LABEL L85
702: DECL int ev_acc
703: ev_acc = 0
704: DECL int i
705: i = 0
706: LABEL L86
707: t127 = i < 10
708: IF_FALSE t127 GOTO L87
709: t128 = i == 2
710: IF_FALSE t128 GOTO L89
711: t129 = ev_acc + i
712: ev_acc = t129
713: LABEL L89
714: t130 = i == 4
715: IF_FALSE t130 GOTO L91
716: t131 = ev_acc + i
717: ev_acc = t131
718: LABEL L91
719: t132 = i == 6
720: IF_FALSE t132 GOTO L93
721: t133 = ev_acc + i
722: ev_acc = t133
723: LABEL L93
724: t134 = i == 8
725: IF_FALSE t134 GOTO L95
726: t135 = ev_acc + i
727: ev_acc = t135
728: LABEL L95
729: t136 = i + 1
730: i = t136
731: GOTO L86
732: LABEL L87
733: PRINT ev_acc
734: IF_FALSE 1 GOTO L97
735: DECL int wb
736: wb = 1
737: LABEL L98
738: t137 = wb <= 3
739: IF_FALSE t137 GOTO L99
740: PRINT wb
741: t138 = wb + 1
742: wb = t138
743: GOTO L98
744: LABEL L99
745: LABEL L97
746: DECL int sv
747: sv = 2
748: DECL int sv2
749: sv2 = 99
750: DECL int sw3
751: P0 = 1
752: P1 = 1
753: t139 = CALL addTwo
754: sw3 = t139
755: DECL bool bsw
756: bsw = 1
757: DECL int sv4
758: sv4 = 3
759: DECL int swi
760: swi = 1
761: LABEL L100
762: t140 = swi <= 3
763: IF_FALSE t140 GOTO L101
764: t141 = swi + 1
765: swi = t141
766: GOTO L100
767: LABEL L101
768: DECL int sv5
769: sv5 = 5
770: t142 = sv5 > 0
771: IF_FALSE t142 GOTO L103
772: LABEL L103
773: DECL int outer_sw
774: outer_sw = 1
775: DECL int inner_sw
776: inner_sw = 2
777: DECL int max_int
778: max_int = 2147483647
779: PRINT max_int
780: DECL int zero
781: zero = 0
782: PRINT zero
783: DECL int neg42
784: t143 = -42
785: neg42 = -42
786: PRINT neg42
787: DECL int chain
788: P0 = 1
789: P1 = 2
790: t144 = CALL addTwo
791: P2 = t144
792: P0 = 3
793: P1 = 4
794: t145 = CALL addTwo
795: P2 = t145
796: t146 = CALL addTwo
797: chain = t146
798: PRINT chain
799: DECL int cbase
800: cbase = 5
801: DECL bool cc1
802: t147 = cbase == 5
803: cc1 = t147
804: DECL bool cc2
805: t148 = cbase != 5
806: cc2 = t148
807: DECL bool cc3
808: t149 = cbase < 6
809: cc3 = t149
810: DECL bool cc4
811: t150 = cbase > 4
812: cc4 = t150
813: DECL bool cc5
814: t151 = cbase <= 5
815: cc5 = t151
816: DECL bool cc6
817: t152 = cbase >= 5
818: cc6 = t152
819: PRINT cc1
820: PRINT cc2
821: PRINT cc3
822: PRINT cc4
823: PRINT cc5
824: PRINT cc6
825: DECL float ftest
826: ftest = 3.14
827: DECL bool fgt
828: t153 = ftest > 3
829: fgt = t153
830: DECL bool flt
831: t154 = ftest < 3
832: flt = t154
833: PRINT fgt
834: PRINT flt
835: t155 = gIntA + 50
836: gIntA = t155
837: PRINT gIntA
838: P0 = gSeed
839: P1 = 3
840: t156 = CALL addTwo
841: gSeed = t156
842: PRINT gSeed
843: DECL int comment_var
844: comment_var = 42
845: PRINT comment_var
846: DECL int uninit_warn
847: DECL int rec_chain
848: P0 = 3
849: t157 = CALL fact
850: P1 = t157
851: P0 = 4
852: t158 = CALL fact
853: P1 = t158
854: t159 = CALL maxOf
855: rec_chain = t159
856: PRINT rec_chain
857: FUNC_END Master
858: FUNC_BEGIN lateHelper
859: DECL int x
860: t160 = x * 2
861: RETURN t160
862: FUNC_END lateHelper
