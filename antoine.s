.name "Nihon no otoko"
.comment "Anata o korosu !"

	sti		r1, %:start, %1
	sti		r1, %:samurai1, %1
	sti		r1, %:samurai2, %1
	sti		r1, %:corelive, %1
	sti		r1, %:corelive, %6
	sti		r1, %:corelive, %11
	sti		r1, %:corelive, %16
	fork	%:ninja

start:
	live	%1
	fork	%:samurai1
	st		r1, 6
	live	%1
	fork	%:samurai2
	st 		r1, 6
	live	%1
	fork	%:corelive
	ld		%0, r16
	zjmp	%:start

corelive:
	live	%210391
	live	%071190
	live	%081089
	live	%1
	ld		%0, r16
	zjmp	%:corelive

samurai1:
	live	%1
	ld		%150994953, r3
	sti		r3, %:start, %-6
	sti		r3, %:start, %-12
	st		r3, -104
	st		r3, -115
	st		r3, -126
	st		r3, -137
	st		r3, -148
	st		r3, -159
	st		r3, -170
	st		r3, -181
	st		r3, -192
	st		r3, -203
	st		r3, -214
	st		r3, -225
	st		r3, -236
	st		r3, -247
	st		r3, -258
	st		r3, -269
	st		r3, -280
	st		r3, -291
	ld		%0, r16
	zjmp	%:samurai1

samurai2:
	live	%1
	ld		%150994953, r3
	st		r3, 254
	st		r3, 255
	st		r3, 256
	st		r3, 257
	st		r3, 258
	st		r3, 259
	st		r3, 260
	st		r3, 261
	st		r3, 262
	st		r3, 263
	st		r3, 264
	st		r3, 265
	st		r3, 266
	st		r3, 267
	st		r3, 268
	st		r3, 269
	st		r3, 270
	ld		%0, r16
	zjmp	%:samurai2
	live	%0
	live	%0
	live	%0
	live	%0

ninja:
	st		r1, 6
	live	%1
	sti		r1, %:ninja_kunai, %1
	sti		r1, %:ninja_live, %1
	fork	%:ninja

ninja_shuriken:
	ld		%0, r2
	ld		%150994953, r3
	ld		%4, r6
	ld		%104, r5
ninja_kunai:
	live	%1
	st		r3, -66
	st		r3, -77
	st		r3, -88
ninja_live:
	live	%1
	st		r3, 53
	st		r3, 54
	st		r3, 55
	ldi		%:ninja_shuriken, r2, r4
	sti		r4, r2, %350
	add		r2, r6, r2
	xor		r2, r5, r9
	zjmp	%334
	ld		%0, r10
	zjmp	%:ninja_kunai
ninja_fin:
	live	%0
