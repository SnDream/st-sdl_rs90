#include <SDL/SDL.h>
#include "font.h"
#include "utf8_utils.h"

static const unsigned char embedded_font[] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	/* Char 000 (.) */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	/* Char 001 (.) */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	/* Char 002 (.) */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	/* Char 003 (.) */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	/* Char 004 (.) */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	/* Char 005 (.) */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	/* Char 006 (.) */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	/* Char 007 (.) */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	/* Char 008 (.) */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	/* Char 009 (.) */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	/* Char 010 (.) */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	/* Char 011 (.) */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	/* Char 012 (.) */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	/* Char 013 (.) */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	/* Char 014 (.) */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	/* Char 015 (.) */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	/* Char 016 (.) */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	/* Char 017 (.) */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	/* Char 018 (.) */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	/* Char 019 (.) */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	/* Char 020 (.) */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	/* Char 021 (.) */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	/* Char 022 (.) */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	/* Char 023 (.) */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	/* Char 024 (.) */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	/* Char 025 (.) */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	/* Char 026 (.)*/
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	/* Char 027 (.) */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	/* Char 028 (.) */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	/* Char 029 (.) */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	/* Char 030 (.) */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	/* Char 031 (.) */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	/* Char 032 ( ) */
	0x40, 0x40, 0x40, 0x00, 0x40, 0x00, 0x00, 0x00,	/* Char 033 (!) */
	0xa0, 0xa0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	/* Char 034 (") */
	0xa0, 0xe0, 0xa0, 0xe0, 0xa0, 0x00, 0x00, 0x00,	/* Char 035 (#) */
	0x40, 0x60, 0x40, 0xc0, 0x40, 0x00, 0x00, 0x00,	/* Char 036 ($) */
	0x80, 0x20, 0x40, 0x80, 0x20, 0x00, 0x00, 0x00,	/* Char 037 (%) */
	0xc0, 0xc0, 0xa0, 0x40, 0xa0, 0x00, 0x00, 0x00,	/* Char 038 (&) */
	0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	/* Char 039 (') */
	0x20, 0x40, 0x40, 0x40, 0x20, 0x00, 0x00, 0x00,	/* Char 040 (() */
	0x80, 0x40, 0x40, 0x40, 0x80, 0x00, 0x00, 0x00,	/* Char 041 ()) */
	0x00, 0xa0, 0x40, 0xa0, 0x00, 0x00, 0x00, 0x00,	/* Char 042 (*) */
	0x00, 0x40, 0xe0, 0x40, 0x00, 0x00, 0x00, 0x00,	/* Char 043 (+) */
	0x00, 0x00, 0x00, 0x40, 0x80, 0x00, 0x00, 0x00,	/* Char 044 (,) */
	0x00, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00,	/* Char 045 (-) */
	0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00,	/* Char 046 (.) */
	0x20, 0x20, 0x40, 0x40, 0x80, 0x80, 0x00, 0x00,	/* Char 047 (/) */
	0xe0, 0xa0, 0xa0, 0xa0, 0xe0, 0x00, 0x00, 0x00,	/* Char 048 (0) */
	0x40, 0xc0, 0x40, 0x40, 0xe0, 0x00, 0x00, 0x00,	/* Char 049 (1) */
	0xe0, 0x20, 0xe0, 0x80, 0xe0, 0x00, 0x00, 0x00,	/* Char 050 (2) */
	0xe0, 0x20, 0xe0, 0x20, 0xe0, 0x00, 0x00, 0x00,	/* Char 051 (3) */
	0xa0, 0xa0, 0xe0, 0x20, 0x20, 0x00, 0x00, 0x00,	/* Char 052 (4) */
	0xe0, 0x80, 0xe0, 0x20, 0xe0, 0x00, 0x00, 0x00,	/* Char 053 (5) */
	0xe0, 0x80, 0xe0, 0xa0, 0xe0, 0x00, 0x00, 0x00,	/* Char 054 (6) */
	0xe0, 0x20, 0x20, 0x20, 0x20, 0x00, 0x00, 0x00,	/* Char 055 (7) */
	0xe0, 0xa0, 0xe0, 0xa0, 0xe0, 0x00, 0x00, 0x00,	/* Char 056 (8) */
	0xe0, 0xa0, 0xe0, 0x20, 0xe0, 0x00, 0x00, 0x00,	/* Char 057 (9) */
	0x00, 0x40, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00,	/* Char 058 (:) */
	0x00, 0x40, 0x00, 0x40, 0x80, 0x00, 0x00, 0x00,	/* Char 059 (;) */
	0x20, 0x40, 0x80, 0x40, 0x20, 0x00, 0x00, 0x00,	/* Char 060 (<) */
	0x00, 0xe0, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x00,	/* Char 061 (=) */
	0x80, 0x40, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00,	/* Char 062 (>) */
	0xc0, 0x20, 0x40, 0x00, 0x40, 0x00, 0x00, 0x00,	/* Char 063 (?) */
	0x40, 0xa0, 0xa0, 0x80, 0x60, 0x00, 0x00, 0x00,	/* Char 064 (@) */
	0x40, 0xa0, 0xa0, 0xe0, 0xa0, 0x00, 0x00, 0x00,	/* Char 065 (A) */
	0xc0, 0xa0, 0xc0, 0xa0, 0xc0, 0x00, 0x00, 0x00,	/* Char 066 (B) */
	0x60, 0x80, 0x80, 0x80, 0x60, 0x00, 0x00, 0x00,	/* Char 067 (C) */
	0xc0, 0xa0, 0xa0, 0xa0, 0xc0, 0x00, 0x00, 0x00,	/* Char 068 (D) */
	0xe0, 0x80, 0xc0, 0x80, 0xe0, 0x00, 0x00, 0x00,	/* Char 069 (E) */
	0xe0, 0x80, 0xc0, 0x80, 0x80, 0x00, 0x00, 0x00,	/* Char 070 (F) */
	0x60, 0x80, 0xa0, 0xa0, 0x60, 0x00, 0x00, 0x00,	/* Char 071 (G) */
	0xa0, 0xa0, 0xe0, 0xa0, 0xa0, 0x00, 0x00, 0x00,	/* Char 072 (H) */
	0xe0, 0x40, 0x40, 0x40, 0xe0, 0x00, 0x00, 0x00,	/* Char 073 (I) */
	0x60, 0x20, 0x20, 0xa0, 0x40, 0x00, 0x00, 0x00,	/* Char 074 (J) */
	0xa0, 0xa0, 0xc0, 0xa0, 0xa0, 0x00, 0x00, 0x00,	/* Char 075 (K) */
	0x80, 0x80, 0x80, 0x80, 0xe0, 0x00, 0x00, 0x00,	/* Char 076 (L) */
	0xa0, 0xe0, 0xe0, 0xa0, 0xa0, 0x00, 0x00, 0x00,	/* Char 077 (M) */
	0xc0, 0xa0, 0xa0, 0xa0, 0xa0, 0x00, 0x00, 0x00,	/* Char 078 (N) */
	0x40, 0xa0, 0xa0, 0xa0, 0x40, 0x00, 0x00, 0x00,	/* Char 079 (O) */
	0xc0, 0xa0, 0xc0, 0x80, 0x80, 0x00, 0x00, 0x00,	/* Char 080 (P) */
	0x40, 0xa0, 0xa0, 0xc0, 0x60, 0x00, 0x00, 0x00,	/* Char 081 (Q) */
	0xc0, 0xa0, 0xc0, 0xa0, 0xa0, 0x00, 0x00, 0x00,	/* Char 082 (R) */
	0x60, 0x80, 0x40, 0x20, 0xc0, 0x00, 0x00, 0x00,	/* Char 083 (S) */
	0xe0, 0x40, 0x40, 0x40, 0x40, 0x00, 0x00, 0x00,	/* Char 084 (T) */
	0xa0, 0xa0, 0xa0, 0xa0, 0x60, 0x00, 0x00, 0x00,	/* Char 085 (U) */
	0xa0, 0xa0, 0xa0, 0xa0, 0x40, 0x00, 0x00, 0x00,	/* Char 086 (V) */
	0xa0, 0xa0, 0xe0, 0xe0, 0xa0, 0x00, 0x00, 0x00,	/* Char 087 (W) */
	0xa0, 0xa0, 0x40, 0xa0, 0xa0, 0x00, 0x00, 0x00,	/* Char 088 (X) */
	0xa0, 0xa0, 0x40, 0x40, 0x40, 0x00, 0x00, 0x00,	/* Char 089 (Y) */
	0xe0, 0x20, 0x40, 0x80, 0xe0, 0x00, 0x00, 0x00,	/* Char 090 (Z) */
	0x60, 0x40, 0x40, 0x40, 0x60, 0x00, 0x00, 0x00,	/* Char 091 ([) */
	0x80, 0x80, 0x40, 0x40, 0x20, 0x20, 0x00, 0x00,	/* Char 092 (\) */
	0xc0, 0x40, 0x40, 0x40, 0xc0, 0x00, 0x00, 0x00,	/* Char 093 (]) */
	0x40, 0xa0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	/* Char 094 (^) */
	0x00, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x00,	/* Char 095 (_) */
	0x80, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	/* Char 096 (`) */
	0x00, 0x60, 0xa0, 0xa0, 0x60, 0x00, 0x00, 0x00,	/* Char 097 (a) */
	0x80, 0x80, 0xc0, 0xa0, 0xc0, 0x00, 0x00, 0x00,	/* Char 098 (b) */
	0x00, 0x60, 0x80, 0x80, 0x60, 0x00, 0x00, 0x00,	/* Char 099 (c) */
	0x20, 0x20, 0x60, 0xa0, 0x60, 0x00, 0x00, 0x00,	/* Char 100 (d) */
	0x00, 0x60, 0xe0, 0x80, 0x60, 0x00, 0x00, 0x00,	/* Char 101 (e) */
	0x20, 0x40, 0xe0, 0x40, 0x40, 0x00, 0x00, 0x00,	/* Char 102 (f) */
	0x00, 0x60, 0xa0, 0xe0, 0x20, 0xc0, 0x00, 0x00,	/* Char 103 (g) */
	0x80, 0x80, 0xc0, 0xa0, 0xa0, 0x00, 0x00, 0x00,	/* Char 104 (h) */
	0x40, 0x00, 0xc0, 0x40, 0xe0, 0x00, 0x00, 0x00,	/* Char 105 (i) */
	0x20, 0x00, 0x60, 0x20, 0xa0, 0x40, 0x00, 0x00,	/* Char 106 (j) */
	0x80, 0xa0, 0xc0, 0xa0, 0xa0, 0x00, 0x00, 0x00,	/* Char 107 (k) */
	0x80, 0x80, 0x80, 0x80, 0x60, 0x00, 0x00, 0x00,	/* Char 108 (l) */
	0x00, 0xe0, 0xe0, 0xa0, 0xa0, 0x00, 0x00, 0x00,	/* Char 109 (m) */
	0x00, 0xc0, 0xa0, 0xa0, 0xa0, 0x00, 0x00, 0x00,	/* Char 110 (n) */
	0x00, 0x40, 0xa0, 0xa0, 0x40, 0x00, 0x00, 0x00,	/* Char 111 (o) */
	0x00, 0xc0, 0xa0, 0xc0, 0x80, 0x80, 0x00, 0x00,	/* Char 112 (p) */
	0x00, 0x60, 0xa0, 0x60, 0x20, 0x20, 0x00, 0x00,	/* Char 113 (q) */
	0x00, 0xc0, 0xa0, 0x80, 0x80, 0x00, 0x00, 0x00,	/* Char 114 (r) */
	0x00, 0x60, 0xc0, 0x20, 0xc0, 0x00, 0x00, 0x00,	/* Char 115 (s) */
	0x40, 0xe0, 0x40, 0x40, 0x20, 0x00, 0x00, 0x00,	/* Char 116 (t) */
	0x00, 0xa0, 0xa0, 0xa0, 0x60, 0x00, 0x00, 0x00,	/* Char 117 (u) */
	0x00, 0xa0, 0xa0, 0xa0, 0x40, 0x00, 0x00, 0x00,	/* Char 118 (v) */
	0x00, 0xa0, 0xa0, 0xe0, 0xe0, 0x00, 0x00, 0x00,	/* Char 119 (w) */
	0x00, 0xa0, 0x40, 0xa0, 0xa0, 0x00, 0x00, 0x00,	/* Char 120 (x) */
	0x00, 0xa0, 0xa0, 0x60, 0x20, 0xc0, 0x00, 0x00,	/* Char 121 (y) */
	0x00, 0xe0, 0x20, 0x40, 0xe0, 0x00, 0x00, 0x00,	/* Char 122 (z) */
	0x60, 0x40, 0x80, 0x40, 0x60, 0x00, 0x00, 0x00,	/* Char 123 ({) */
	0x40, 0x40, 0x40, 0x40, 0x40, 0x00, 0x00, 0x00,	/* Char 124 (|) */
	0xc0, 0x40, 0x20, 0x40, 0xc0, 0x00, 0x00, 0x00,	/* Char 125 (}) */
	0x60, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	/* Char 126 (~) */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	/* Char 127 (.) */
};

static const unsigned char boxdrawing_font[] = {
	0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0xf0, 0xf0, 0x00, 0x00, 0x00, 0x00,
	0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x00, 0x00,
	0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x00, 0x00,
	0x00, 0x00, 0xa0, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0xa0, 0xa0, 0x00, 0x00, 0x00, 0x00,
	0x40, 0x00, 0x40, 0x00, 0x40, 0x00, 0x00, 0x00,
	0x60, 0x00, 0x60, 0x00, 0x60, 0x00, 0x00, 0x00,
	0x00, 0x00, 0xa0, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0xa0, 0xa0, 0x00, 0x00, 0x00, 0x00,
	0x40, 0x00, 0x40, 0x00, 0x40, 0x00, 0x00, 0x00,
	0x60, 0x00, 0x60, 0x00, 0x60, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x70, 0x40, 0x40, 0x40, 0x00, 0x00,
	0x00, 0x00, 0x70, 0x70, 0x40, 0x40, 0x00, 0x00,
	0x00, 0x00, 0x70, 0x60, 0x60, 0x60, 0x00, 0x00,
	0x00, 0x00, 0x70, 0x70, 0x60, 0x60, 0x00, 0x00,
	0x00, 0x00, 0xc0, 0x40, 0x40, 0x40, 0x00, 0x00,
	0x00, 0x00, 0xc0, 0xc0, 0x40, 0x40, 0x00, 0x00,
	0x00, 0x00, 0xe0, 0x60, 0x60, 0x60, 0x00, 0x00,
	0x00, 0x00, 0xe0, 0xe0, 0x60, 0x60, 0x00, 0x00,
	0x40, 0x40, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x40, 0x40, 0x70, 0x70, 0x00, 0x00, 0x00, 0x00,
	0x60, 0x60, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x60, 0x60, 0x70, 0x70, 0x00, 0x00, 0x00, 0x00,
	0x40, 0x40, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x40, 0x40, 0xc0, 0xc0, 0x00, 0x00, 0x00, 0x00,
	0x60, 0x60, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x60, 0x60, 0xe0, 0xe0, 0x00, 0x00, 0x00, 0x00,
	0x40, 0x40, 0x70, 0x40, 0x40, 0x40, 0x00, 0x00,
	0x40, 0x40, 0x70, 0x70, 0x40, 0x40, 0x00, 0x00,
	0x60, 0x60, 0x70, 0x40, 0x40, 0x40, 0x00, 0x00,
	0x40, 0x40, 0x70, 0x60, 0x60, 0x60, 0x00, 0x00,
	0x60, 0x60, 0x70, 0x60, 0x60, 0x60, 0x00, 0x00,
	0x60, 0x60, 0x70, 0x70, 0x40, 0x40, 0x00, 0x00,
	0x40, 0x40, 0x70, 0x70, 0x60, 0x60, 0x00, 0x00,
	0x60, 0x60, 0x70, 0x70, 0x60, 0x60, 0x00, 0x00,
	0x40, 0x40, 0xc0, 0x40, 0x40, 0x40, 0x00, 0x00,
	0x40, 0x40, 0xc0, 0xc0, 0x40, 0x40, 0x00, 0x00,
	0x60, 0x60, 0xe0, 0x40, 0x40, 0x40, 0x00, 0x00,
	0x40, 0x40, 0xe0, 0x60, 0x60, 0x60, 0x00, 0x00,
	0x60, 0x60, 0xe0, 0x60, 0x60, 0x60, 0x00, 0x00,
	0x60, 0x60, 0xe0, 0xe0, 0x40, 0x40, 0x00, 0x00,
	0x40, 0x40, 0xe0, 0xe0, 0x60, 0x60, 0x00, 0x00,
	0x60, 0x60, 0xe0, 0xe0, 0x60, 0x60, 0x00, 0x00,
	0x00, 0x00, 0xf0, 0x40, 0x40, 0x40, 0x00, 0x00,
	0x00, 0x00, 0xf0, 0xc0, 0x40, 0x40, 0x00, 0x00,
	0x00, 0x00, 0xf0, 0x70, 0x40, 0x40, 0x00, 0x00,
	0x00, 0x00, 0xf0, 0xf0, 0x40, 0x40, 0x00, 0x00,
	0x00, 0x00, 0xf0, 0x60, 0x60, 0x60, 0x00, 0x00,
	0x00, 0x00, 0xf0, 0xe0, 0x60, 0x60, 0x00, 0x00,
	0x00, 0x00, 0xf0, 0x70, 0x60, 0x60, 0x00, 0x00,
	0x00, 0x00, 0xf0, 0xf0, 0x60, 0x60, 0x00, 0x00,
	0x40, 0x40, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x40, 0x40, 0xf0, 0xc0, 0x00, 0x00, 0x00, 0x00,
	0x40, 0x40, 0xf0, 0x70, 0x00, 0x00, 0x00, 0x00,
	0x40, 0x40, 0xf0, 0xf0, 0x00, 0x00, 0x00, 0x00,
	0x60, 0x60, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x60, 0x60, 0xf0, 0xe0, 0x00, 0x00, 0x00, 0x00,
	0x60, 0x60, 0xf0, 0x70, 0x00, 0x00, 0x00, 0x00,
	0x60, 0x60, 0xf0, 0xf0, 0x00, 0x00, 0x00, 0x00,
	0x40, 0x40, 0xf0, 0x40, 0x40, 0x40, 0x00, 0x00,
	0x40, 0x40, 0xf0, 0xc0, 0x40, 0x40, 0x00, 0x00,
	0x40, 0x40, 0xf0, 0x70, 0x40, 0x40, 0x00, 0x00,
	0x40, 0x40, 0xf0, 0xf0, 0x40, 0x40, 0x00, 0x00,
	0x60, 0x60, 0xf0, 0x40, 0x40, 0x40, 0x00, 0x00,
	0x40, 0x40, 0xf0, 0x60, 0x60, 0x60, 0x00, 0x00,
	0x60, 0x60, 0xf0, 0x60, 0x60, 0x60, 0x00, 0x00,
	0x60, 0x60, 0xf0, 0xe0, 0x40, 0x40, 0x00, 0x00,
	0x60, 0x60, 0xf0, 0x70, 0x40, 0x40, 0x00, 0x00,
	0x40, 0x40, 0xf0, 0xe0, 0x60, 0x60, 0x00, 0x00,
	0x40, 0x40, 0xf0, 0x70, 0x60, 0x60, 0x00, 0x00,
	0x60, 0x60, 0xf0, 0xf0, 0x40, 0x40, 0x00, 0x00,
	0x40, 0x40, 0xf0, 0xf0, 0x60, 0x60, 0x00, 0x00,
	0x60, 0x60, 0xf0, 0xe0, 0x60, 0x60, 0x00, 0x00,
	0x60, 0x60, 0xf0, 0x70, 0x60, 0x60, 0x00, 0x00,
	0x60, 0x60, 0xf0, 0xf0, 0x60, 0x60, 0x00, 0x00,
	0x00, 0x00, 0xa0, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0xa0, 0xa0, 0x00, 0x00, 0x00, 0x00,
	0x40, 0x40, 0x00, 0x40, 0x40, 0x00, 0x00, 0x00,
	0x60, 0x60, 0x00, 0x60, 0x60, 0x00, 0x00, 0x00,
	0x00, 0xf0, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00,
	0xa0, 0xa0, 0xa0, 0xa0, 0xa0, 0xa0, 0x00, 0x00,
	0x00, 0x70, 0x40, 0x70, 0x40, 0x40, 0x00, 0x00,
	0x00, 0x00, 0xf0, 0xa0, 0xa0, 0xa0, 0x00, 0x00,
	0x00, 0xf0, 0x80, 0xb0, 0xa0, 0xa0, 0x00, 0x00,
	0x00, 0xc0, 0x40, 0xc0, 0x40, 0x40, 0x00, 0x00,
	0x00, 0x00, 0xe0, 0xa0, 0xa0, 0xa0, 0x00, 0x00,
	0x00, 0x00, 0xe0, 0xa0, 0xa0, 0xa0, 0x00, 0x00,
	0x40, 0x70, 0x40, 0x70, 0x00, 0x00, 0x00, 0x00,
	0xa0, 0xa0, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00,
	0xa0, 0xb0, 0x80, 0xf0, 0x00, 0x00, 0x00, 0x00,
	0x40, 0xc0, 0x40, 0xc0, 0x00, 0x00, 0x00, 0x00,
	0xa0, 0xa0, 0xa0, 0xe0, 0x00, 0x00, 0x00, 0x00,
	0xa0, 0xa0, 0xa0, 0xe0, 0x00, 0x00, 0x00, 0x00,
	0x40, 0x70, 0x40, 0x70, 0x40, 0x40, 0x00, 0x00,
	0xa0, 0xa0, 0xb0, 0xa0, 0xa0, 0xa0, 0x00, 0x00,
	0xa0, 0xb0, 0x80, 0xb0, 0xa0, 0xa0, 0x00, 0x00,
	0x40, 0xc0, 0x40, 0xc0, 0x40, 0x40, 0x00, 0x00,
	0xa0, 0xa0, 0xa0, 0xa0, 0xa0, 0xa0, 0x00, 0x00,
	0xa0, 0xa0, 0x20, 0xa0, 0xa0, 0xa0, 0x00, 0x00,
	0x00, 0xf0, 0x00, 0xf0, 0x40, 0x40, 0x00, 0x00,
	0x00, 0x00, 0xf0, 0xa0, 0xa0, 0xa0, 0x00, 0x00,
	0x00, 0xf0, 0x00, 0xb0, 0xa0, 0xa0, 0x00, 0x00,
	0x40, 0xf0, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00,
	0xa0, 0xa0, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00,
	0xa0, 0xb0, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00,
	0x40, 0xf0, 0x40, 0xf0, 0x40, 0x40, 0x00, 0x00,
	0xa0, 0xa0, 0xf0, 0xa0, 0xa0, 0xa0, 0x00, 0x00,
	0xa0, 0xb0, 0x00, 0xb0, 0xa0, 0xa0, 0x00, 0x00,
	0x00, 0x00, 0x30, 0x40, 0x40, 0x40, 0x00, 0x00,
	0x00, 0x00, 0x80, 0x40, 0x40, 0x40, 0x00, 0x00,
	0x40, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x40, 0x40, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x10, 0x10, 0x20, 0x40, 0x80, 0x80, 0x00, 0x00,
	0x80, 0x80, 0x40, 0x20, 0x10, 0x10, 0x00, 0x00,
	0x90, 0x90, 0x40, 0x20, 0x90, 0x90, 0x00, 0x00,
	0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x40, 0x40, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x40, 0x40, 0x40, 0x40, 0x00, 0x00,
	0x00, 0x00, 0xe0, 0xe0, 0x00, 0x00, 0x00, 0x00,
	0x60, 0x60, 0x60, 0x60, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x70, 0x70, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x60, 0x60, 0x60, 0x60, 0x00, 0x00,
	0x00, 0x00, 0xf0, 0x70, 0x00, 0x00, 0x00, 0x00,
	0x40, 0x40, 0x60, 0x60, 0x60, 0x60, 0x00, 0x00,
	0x00, 0x00, 0xf0, 0xe0, 0x00, 0x00, 0x00, 0x00,
	0x60, 0x60, 0x60, 0x60, 0x20, 0x20, 0x00, 0x00,
};

void draw_font(SDL_Surface* surface, const unsigned char* ptr, int x, int y, unsigned short color) {
	for (int ys = 0; (ys < 6) && (y + ys < surface->h); ptr++, ys++) {
		for (int xs = 0; (xs < 4) && (x + xs < surface->w); xs++) {
			if (*ptr & (1u << (7 - xs))) {
				((unsigned short*)surface->pixels)[(y + ys ) * (surface->w) + x + xs] = color;
			}
		}
	}
}

void draw_char(SDL_Surface* surface, unsigned char symbol, int x, int y, unsigned short color) {
	draw_font(surface, embedded_font + symbol * 8, x, y, color);
}

static const unsigned char unknown_font[] = {
	0x40, 0xe0, 0xe0, 0xe0, 0x40, 0x00, 0x00, 0x00,
};

void draw_unknown_char(SDL_Surface* surface, long utf8c, int x, int y, unsigned short color) {
	draw_font(surface, unknown_font, x, y, color);
}

void draw_string(SDL_Surface* surface, const char* text, int orig_x, int orig_y, unsigned short color) {
	int x = orig_x, y = orig_y;
	int count = 1;
	for (; *text; text++) {
		if (count-- > 1) continue;
		count = utf8size(text);
		if (count > 1){
			long utf8c;
			utf8decode(text, &utf8c);
			if ((utf8c & 0x1FFF80) == 0x2500) draw_font(surface, boxdrawing_font + (utf8c & 0x7F) * 8, x, y, color );
			else draw_font(surface, unknown_font, x, y, color);
			x += 4;
		} else {
			if(*text == '\n') {
				x = orig_x;
				y += 6;
			} else {
				draw_char(surface, *text, x, y, color);
				x += 4;
			}
		}
	}
}

static const unsigned char kb_font[] = {
	0x20, 0x70, 0xa8, 0x20, 0x20, 0x00, 0x00, 0x00,
	0x20, 0x20, 0xa8, 0x70, 0x20, 0x00, 0x00, 0x00,
	0x20, 0x40, 0xf8, 0x40, 0x20, 0x00, 0x00, 0x00,
	0x20, 0x10, 0xf8, 0x10, 0x20, 0x00, 0x00, 0x00,
	0xe8, 0x88, 0xe8, 0x88, 0x88, 0x00, 0x00, 0x00,
	0x70, 0x50, 0x50, 0x50, 0x70, 0x00, 0x00, 0x00,
	0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x00, 0x00,
	0x70, 0x10, 0x70, 0x40, 0x70, 0x00, 0x00, 0x00,
	0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00,
};

void draw_kb_font(SDL_Surface* surface, const unsigned char* ptr, int x, int y, unsigned short color) {
	for (int ys = 0; (ys < 6) && (y + ys < surface->h); ptr++, ys++) {
		for (int xs = -1; (xs < 4) && (x + xs < surface->w); xs++) {
			if (*ptr & (1u << (7 - 1 - xs))) {
				((unsigned short*)surface->pixels)[(y + ys ) * (surface->w) + x + xs] = color;
			}
		}
	}
}

void draw_kb_string(SDL_Surface* surface, const char* text, int orig_x, int orig_y, unsigned short color) {
	int x = orig_x, y = orig_y;
	while(*text) {
		switch (*text) {
		case '\n':
			x = orig_x;
			y += 6;
			break;
		case 0x10:
		case 0x11:
		case 0x12:
		case 0x13:
		case 0x14:
		case 0x15:
		case 0x16:
		case 0x17:
		case 0x18:
			draw_kb_font(surface, kb_font + (*text - 0x10) * 8, x, y, color);
			x += 5;
			break;
		default:
			draw_char(surface, *text, x, y, color);
			x += 4;
		}
		text++;
	}
}
