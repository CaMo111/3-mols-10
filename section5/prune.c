/*
 * net5.c -- depth-first search for a 5-net of order 10 (i.e. 3 MOLS of
 *           order 10) in which every point and line carries a "type".
 *
 * MODEL
 *   Points 0..99.  Point p has a 10-bit type (2*NCLS bits).  Class c (0..4) uses
 *   bits 2c and 2c+1 of it: bit 2c  = "p lies on a line of relation 1 in class c",
 *                           bit 2c+1 = "p lies on a line of relation 2 in class c".
 *   A line in class c has a 2-bit type t (bit0 = in relation 1, bit1 = in
 *   relation 2) and may only contain points whose class-c bits equal t.
 *   A class therefore contains total[c][t] = (#points with class-c bits == t)/10
 *   lines of type t.  Lines from different classes meet in at most one point;
 *   lines of the same class are disjoint.
 *
 * SEARCH
 *   drawline() picks the parallel class (A) and the line type within it (B),
 *   then enumerates every 10-point line of that type that is compatible with
 *   the lines drawn so far, recursing after each.
 *
 *   Symmetry: two points are equivalent if they have the same type and lie on
 *   exactly the same drawn lines.  Swapping equivalent points is an
 *   automorphism of the partial configuration, so of any set of equivalent
 *   points we only ever use the lowest-numbered ones.
 *
 *   Forced lines: when only 10 uncovered points of a given (class,type) remain,
 *   that line is drawn immediately (or the branch is abandoned if it would
 *   meet an existing line twice).  Forced lines count towards the score.
 *
 * VARIANTS (compile-time)
 *   (A) class choice : default = class with FEWEST lines so far
 *                      -DCLASS_MOST = class with MOST lines (skipping full ones)
 *   (B) type choice  : default = RAREST type still needing lines in the class
 *                      -DTYPE_COMMON = MOST COMMON such type
 *       "Rarity" = number of lines of that type still to be drawn in the class
 *       (see type_weight()).  Ties go to the lowest class / type number.
 *
 * BUILD  (add -DNCLS=4 to search for a 4-net instead; -DN=7 etc. for a smaller order)
 *   gcc -O2 -march=native -o net5_fewest_rarest  net5.c
 *   gcc -O2 -march=native -DTYPE_COMMON -o net5_fewest_common net5.c
 *   gcc -O2 -march=native -DCLASS_MOST  -o net5_most_rarest   net5.c
 *   gcc -O2 -march=native -DCLASS_MOST -DTYPE_COMMON -o net5_most_common net5.c
 *
 * USAGE
 *   ./net5_xxx [typefile|-] [seconds]
 *   Input: 100 point types, each 2*NCLS binary digits (10 by default;
 *   whitespace/commas between digits or groups are ignored).  Digit i of point p is bit i of its type,
 *   so digits 2c,2c+1 belong to class c (relation 1, relation 2).
 *   Stops on a complete net, on Ctrl-C, after the optional time limit, or when
 *   the search is exhausted; then prints the best set of lines found.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <signal.h>
#include <time.h>
#include <ctype.h>

#ifndef N
#define N       10             /* order (-DN=7 etc. for quick sanity tests; must be <= 10) */
#endif
#define NPTS    (N * N)
#ifndef NCLS
#define NCLS    5              /* number of parallel classes (-DNCLS=4 to test 4-nets) */
#endif
#define NDIG    (2 * NCLS)     /* binary digits per point in the input */
#define NTYPES  4
#define NLINES  (NCLS * N)

typedef unsigned __int128 u128;
typedef uint64_t          u64;

#define BIT(i)    (((u128)1) << (i))
#define HAS(m, i) ((int)(((m) >> (i)) & 1))

static inline int pop128(u128 x)
{
    return __builtin_popcountll((u64)x) + __builtin_popcountll((u64)(x >> 64));
}
static inline int ctz128(u128 x)
{
    u64 lo = (u64)x;
    return lo ? __builtin_ctzll(lo) : 64 + __builtin_ctzll((u64)(x >> 64));
}

/* ---------- static problem data ---------- */
static unsigned short ptype[NPTS];
static u128 typemask[NCLS][NTYPES];   /* points whose class-c bits == t   */
static int  total[NCLS][NTYPES];      /* lines of type t needed in class c */

/* ---------- search state ---------- */
static u128 lines[NLINES];
static unsigned char lcls[NLINES], ltyp[NLINES];
static int  nlines;
static u128 covered[NCLS];            /* points already on a line of class c */
static int  cnt[NCLS][NTYPES];        /* lines drawn per (class,type)        */
static int  ccount[NCLS];             /* lines drawn per class               */
static u128 ptunion[NPTS];            /* p itself + all drawn lines through p */
static u64  lineset[NPTS];            /* bitmask of indices of lines through p */

/* ---------- best result ---------- */
static u128 bestlines[NLINES];
static unsigned char bestcls[NLINES], besttyp[NLINES];
static int  best;

static volatile sig_atomic_t stop;
static int  found_net;
static unsigned long long nodes, ticks;
static time_t deadline;

static void on_sigint(int s) { (void)s; stop = 1; }

static inline void tick(void)
{
    if (((++ticks) & 0xFFFFF) == 0 && deadline && time(NULL) >= deadline)
        stop = 1;
}

/* ------------------------------------------------------------------ */

static void add_line(u128 L, int c, int t)
{
    int idx = nlines++;
    lines[idx] = L; lcls[idx] = (unsigned char)c; ltyp[idx] = (unsigned char)t;
    covered[c] |= L;
    cnt[c][t]++;
    ccount[c]++;
    for (u128 m = L; m; m &= m - 1) {
        int p = ctz128(m);
        ptunion[p] |= L;
        lineset[p] |= 1ULL << idx;
    }
}

/* Undo the most recently added line.  Lines from different classes meet only
 * in the point itself, so removing L from ptunion[p] leaves p's other lines. */
static void undo_line(void)
{
    int idx = --nlines;
    u128 L = lines[idx];
    int c = lcls[idx], t = ltyp[idx];
    covered[c] &= ~L;
    cnt[c][t]--;
    ccount[c]--;
    for (u128 m = L; m; m &= m - 1) {
        int p = ctz128(m);
        ptunion[p] = (ptunion[p] & ~L) | BIT(p);
        lineset[p] &= ~(1ULL << idx);
    }
}

static void record(void)
{
    if (nlines > best) {
        best = nlines;
        memcpy(bestlines, lines, sizeof(u128) * (size_t)nlines);
        memcpy(bestcls, lcls, (size_t)nlines);
        memcpy(besttyp, ltyp, (size_t)nlines);
        printf("Found %d lines\n", best);
        fflush(stdout);
        if (best == NLINES) { found_net = 1; stop = 1; }
    }
}

/* Draw every line that is forced (exactly one line of its (class,type) still
 * to place, so its 10 points are the 10 uncovered ones).  Returns 0 if a
 * forced line is impossible.  Drawing one forced line cannot force another,
 * because coverage in class c only depends on lines of class c. */
static int propagate(void)
{
    for (int c = 0; c < NCLS; c++)
        for (int t = 0; t < NTYPES; t++) {
            if (total[c][t] - cnt[c][t] != 1) continue;
            u128 F = typemask[c][t] & ~covered[c];
            u128 blocked = 0;
            for (u128 m = F; m; m &= m - 1) {
                int p = ctz128(m);
                if (HAS(blocked, p)) return 0;   /* meets a line twice */
                blocked |= ptunion[p];
            }
            add_line(F, c, t);
            record();
        }
    return 1;
}

/* ---------- choice of class (A) and type (B) ---------- */

static int pick_class(void)
{
    int c = -1;
    for (int k = 0; k < NCLS; k++) {
        if (ccount[k] >= N) continue;
#ifdef CLASS_MOST
        if (c < 0 || ccount[k] > ccount[c]) c = k;
#else
        if (c < 0 || ccount[k] < ccount[c]) c = k;
#endif
    }
    return c;
}

/* How "common" a type is in a class: lines of it still to be drawn.
 * (Use total[c][t] instead for the type's overall frequency in the class.) */
static inline int type_weight(int c, int t) { return total[c][t] - cnt[c][t]; }

static int pick_type(int c)
{
    int t = -1;
    for (int k = 0; k < NTYPES; k++) {
        if (type_weight(c, k) < 2) continue;  /* 0: finished; 1: already forced */
#ifdef TYPE_COMMON
        if (t < 0 || type_weight(c, k) > type_weight(c, t)) t = k;
#else
        if (t < 0 || type_weight(c, k) < type_weight(c, t)) t = k;
#endif
    }
    return t;
}

/* ---------- point equivalence ---------- */

/* pred[p] = next lower-numbered point with the same type and the same set of
 * drawn lines as p, or -1.  Equivalent points share availability, so in a new
 * line a point may be used only if its pred (if any) is used too. */
static unsigned hstamp[256], epoch;
static u64      hkey[256];
static int      hlast[256];

static void compute_pred(int *pred)
{
    epoch++;
    for (int p = 0; p < NPTS; p++) {
        u64 k = (lineset[p] << 10) | ptype[p];       /* <= 50+10 bits */
        unsigned h = (unsigned)((k * 0x9E3779B97F4A7C15ULL) >> 56);
        while (hstamp[h] == epoch && hkey[h] != k) h = (h + 1) & 255;
        if (hstamp[h] == epoch) {
            pred[p] = hlast[h];
        } else {
            hstamp[h] = epoch; hkey[h] = k; pred[p] = -1;
        }
        hlast[h] = p;
    }
}

/* ---------- the search ---------- */

typedef struct { int c, t; u128 avail; int pred[NPTS]; } Ctx;

static void search(void);

static void leaf(u128 L, int c, int t)
{
    // retain five percent 
    //if (rand() % 1000 != 0) {
    //  return;
    // }

    int base = nlines;
    add_line(L, c, t);
    record();
    if (propagate()) search();
    while (nlines > base) undo_line();
}

/* Choose the remaining N-k points of the new line, in increasing order.
 * P = points chosen so far; blocked = points lying on a drawn line that
 * already contains a point of P (they would give a second intersection). */
static void enumerate(Ctx *x, u128 P, int k, u128 blocked, int start)
{
    u128 cand = x->avail & ~blocked & ~(BIT(start) - 1);
    int want = N - k;
    tick();
    while (cand && !stop) {
        int p = ctz128(cand);
        cand &= cand - 1;
        if (1 + pop128(cand) < want) break;          /* not enough left */
        int q = x->pred[p];
        if (q >= 0 && !HAS(P, q)) continue;          /* symmetry: lowest first */
	
	// hail mary
	//	if ((rand() % 3) != 0) continue;
	// if ((rand() % 5) < 3) continue;
	//int drop_threshold = 2 + (nlines / 4); 
        //if ((rand() % drop_threshold) != 0) continue;
	int keep_chance = 10 - (nlines / 10); 
        if (keep_chance < 5) keep_chance = 5; // Floor at 50% per point
        if ((rand() % 10) >= keep_chance) continue;

	u128 P2 = P | BIT(p);
        if (k + 1 == N) leaf(P2, x->c, x->t);
        else enumerate(x, P2, k + 1, blocked | ptunion[p], p + 1);
    }
}

/* drawline: pick class and type, then try every (symmetry-reduced) line. */
static void search(void)
{
    if (stop || nlines == NLINES) return;
    nodes++;

    // prune in search 
   if (nlines > 0 && (rand() % 2 != 0)) {
       return;
    }

    int c = pick_class();
    if (c < 0) return;
    int t = pick_type(c);
    if (t < 0) return;

    Ctx x;
    x.c = c; x.t = t;
    x.avail = typemask[c][t] & ~covered[c];
    compute_pred(x.pred);
    enumerate(&x, 0, 0, 0, 0);
}

/* ---------- I/O ---------- */

static void print_lines(int n, const u128 *L, const unsigned char *cl,
                        const unsigned char *ty)
{
    for (int i = 0; i < n; i++) {
        printf("class %d type %d%d :", cl[i], ty[i] & 1, ty[i] >> 1);
        for (u128 m = L[i]; m; m &= m - 1) printf(" %d", ctz128(m));
        printf("\n");
    }
}

int main(int argc, char **argv)
{
    srand((unsigned int)time(NULL));

    FILE *f = stdin;
    if (argc > 1 && strcmp(argv[1], "-") != 0) {
        f = fopen(argv[1], "r");
        if (!f) { perror(argv[1]); return 1; }
    }
    if (argc > 2) {
        long s = atol(argv[2]);
        if (s > 0) deadline = time(NULL) + s;
    }

    /* read NPTS * NDIG binary digits */
    int ndig = 0, ch;
    static unsigned char dig[NPTS * NDIG];
    while ((ch = fgetc(f)) != EOF) {
        if (ch == '0' || ch == '1') {
            if (ndig < NPTS * NDIG) dig[ndig] = (unsigned char)(ch - '0');
            ndig++;
        } else if (!isspace(ch) && ch != ',') {
            fprintf(stderr, "bad character '%c' in input\n", ch);
            return 1;
        }
    }
    if (ndig != NPTS * NDIG) {
        fprintf(stderr, "expected %d binary digits, got %d\n", NPTS * NDIG, ndig);
        return 1;
    }
    for (int p = 0; p < NPTS; p++) {
        ptype[p] = 0;
        for (int i = 0; i < NDIG; i++)
            if (dig[p * NDIG + i]) ptype[p] |= (unsigned short)(1u << i);
    }

    /* per-class type groups */
    for (int p = 0; p < NPTS; p++)
        for (int c = 0; c < NCLS; c++)
            typemask[c][(ptype[p] >> (2 * c)) & 3] |= BIT(p);
    for (int c = 0; c < NCLS; c++)
        for (int t = 0; t < NTYPES; t++) {
            int n = pop128(typemask[c][t]);
            if (n % N) {
                fprintf(stderr, "class %d has %d points of type %d%d: not a "
                        "multiple of %d, so no net is possible\n",
                        c, n, t & 1, t >> 1, N);
                return 1;
            }
            total[c][t] = n / N;
        }

    for (int p = 0; p < NPTS; p++) ptunion[p] = BIT(p);
    signal(SIGINT, on_sigint);

    if (propagate()) search();

    if (found_net)      printf("Complete %d-net found!\n", NCLS);
    else if (stop)      printf("Run stopped early (interrupt or time limit).\n");
    else                printf("Search space exhausted.\n");
    printf("Best: %d lines (%llu search nodes)\n", best, nodes);
    print_lines(best, bestlines, bestcls, besttyp);
    return 0;
}
