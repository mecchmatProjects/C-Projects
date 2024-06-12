#ifndef PERMUTATIONS_H
#define PERMUTATIONS_H

#include "common.h"

typedef struct Set
{
    UTYPE size;
    UTYPE *mas;
} Set;

extern Set generate(UTYPE n);

extern ITYPE input(Set *x);
extern void output(Set x);
extern ITYPE inputTextFile(char *file, Set *x);
extern ITYPE outputTextFile(char *File, Set x);
extern ITYPE inputBinaryFile(char *file, Set *x);
extern ITYPE outputBinaryFile(char *File, Set x);

extern UTYPE Pow(UTYPE x, UTYPE deg);
extern UTYPE Factorial(UTYPE n);
extern UTYPE Combinations(UTYPE n, UTYPE k);
extern void sort(Set *s, UTYPE n);
extern void swap(UTYPE i, UTYPE j, Set *s);
extern UTYPE a_more_b(Set *a, Set *b);
extern ITYPE equil(Set s1, Set s2);

extern void _generate_subsets(Set *s, Set s_old, UTYPE index, Set *subsets, UTYPE *indices);
extern Set *generate_subsets(Set *s, UTYPE *n);
extern Set *get_unsorted_subsets(Set *s, UTYPE *n);
extern Set *get_sorted_subsets(Set *s, UTYPE *n);

extern Set *get_k_size_unsorted_subsets(Set *s, UTYPE *n, UTYPE k);
extern Set *get_k_size_sorted_subsets(Set *s, UTYPE *n, UTYPE k);

extern void _unsorted_permutations_without_repetitions(Set *s, UTYPE k, Set *perms, UTYPE *index);
extern Set *unsorted_permutations_without_repetitions(Set *s, UTYPE *n);
extern Set *sorted_permutations_without_repetitions(Set *s, UTYPE *n);

extern Set *get_unsorted_subsets_wse(Set *s, UTYPE *n);
extern Set *get_sorted_subsets_wse(Set *s, UTYPE *n);
extern Set *get_k_size_unsorted_subsets_wse(Set *s, UTYPE *n, UTYPE k);
extern Set *get_k_size_sorted_subsets_wse(Set *s, UTYPE *n, UTYPE k);
extern Set *unsorted_permutations_without_repetitions_wse(Set *s, UTYPE *n);
extern Set *sorted_permutations_without_repetitions_wse(Set *s, UTYPE *n);

extern Set **task1(Set *b, Set *a, UTYPE *n);
extern Set **task2(Set **b, Set *a, UTYPE *n);

#endif // PERMUTATIONS_H
