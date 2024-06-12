#include "../headers/Permutations.h"

Set* generate(UTYPE n)  // function in order to generate a subset
{
    Set* s;
    s.size = n;
    s.mas = (UTYPE *)malloc(sizeof(UTYPE) * n);
    return s;
}

ITYPE input(Set *x)
{
    for (UTYPE _i = 0; _i < x->size; ++_i)
    {
        scanf("%lu", &(x->mas[_i]));
    }
    return x->size;
}

void output(Set x)
{
    printf("( ");
    for (UTYPE _i = 0; _i < x.size; ++_i)
        printf("%lu ", x.mas[_i]);
    printf(")");
}

ITYPE inputTextFile(char *file, Set *x)
{
    FILE *read_ptr;
    if ((read_ptr = fopen(file, "r")) == NULL)
    {
        fprintf(stderr, "Read error!\n");
        return 0;
    }

    for (UTYPE _i = 0; _i < x->size; ++_i)
        fscanf(read_ptr, "%lu", &(x->mas[_i]));
    fclose(read_ptr);
    return x->size;
}

ITYPE outputTextFile(char *file, Set x)
{
    FILE *write_ptr;
    if ((write_ptr = fopen(file, "w")) == NULL)
    {
        fprintf(stderr, "Write error!\n");
        return 0;
    }
    printf("( ");
    for (UTYPE _i = 0; _i < x.size; ++_i)
        fprintf(write_ptr, "%lu ", x.mas[_i]);
    printf(")");
    fclose(write_ptr);
    return x.size;
}

ITYPE inputBinaryFile(char *file, Set *x)
{
    FILE *read_ptr;
    if ((read_ptr = fopen(file, "rb")) == NULL)
    {
        fprintf(stderr, "Read error!\n");
        return 0;
    }
    printf("%p\n", read_ptr);
    fread(x->mas, sizeof(UTYPE), x->size, read_ptr);
    fclose(read_ptr);
    return x->size;
}

ITYPE outputBinaryFile(char *file, Set x)
{
    FILE *write_ptr;
    if ((write_ptr = fopen(file, "wb")) == NULL)
    {
        fprintf(stderr, "Write error!\n");
        return 0;
    }
    fwrite(x.mas, sizeof(UTYPE), x.size, write_ptr);
    fclose(write_ptr);
    return x.size;
}

UTYPE Pow(UTYPE x, UTYPE deg) // function in order to rise to degree
{
    if (x == 0)
        return 0;

    UTYPE answer = 1;
    for (UTYPE i = 0; i < deg; i++)
    {
        answer *= x;
    }

    return answer;
}

UTYPE Factorial(UTYPE n) // factorial function
{
    UTYPE answer = 1;
    for (UTYPE i = 2; i <= n; i++)
    {
        answer *= i;
    }
    return answer;
}

UTYPE Combinations(UTYPE n, UTYPE k) // function in order to get all combinations of set
{
    if (n <= 0 || k <= 0 || n < k)
        return 0;

    return Factorial(n) / (Factorial(n - k) * Factorial(k));
}

void sort(Set *sets, UTYPE size) // sort function
{
    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = i + 1; j < size; j++)
        {
            if (a_more_b(&sets[i], &sets[j]))
            {
                Set temp = sets[i];
                sets[i] = sets[j];
                sets[j] = temp;
            }
        }
    }
}

void swap(UTYPE i, UTYPE j, Set *s) //
{
    UTYPE temp = s->mas[i];
    s->mas[i] = s->mas[j];
    s->mas[j] = temp;
}

UTYPE a_more_b(Set *a, Set *b) // function to compare sizes of permutations
{
    if (a->size < b->size)
    {
        return 0;
    }
    else if (a->size > b->size)
    {
        return 1;
    }
    else
    {
        for (size_t i = 0; i < a->size; i++)
        {
            if (a->mas[i] > b->mas[i])
            {
                return 1;
            }
            else if (a->mas[i] < b->mas[i])
            {
                return 0;
            }
        }
        return 0;
    }
}

ITYPE equil(Set s1, Set s2) // function in order to check whether two sets are equal
{
    if (!a_more_b(&s1, &s2) && !a_more_b(&s2, &s1))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * Helper recursive function to create all possible subsets from given Set.
 * Create new subset by adding s[index] element to s_old, if it is possible.
 * Or add nothing and go to the next symbol.
 *
 * @param s the Set
 * @param s_old previous subset
 * @index current element from s, which can be added to the new subset
 * @subsets pointer to array of subsets
 * @indices helper array whith indices, that help to correctly write subsets to an array.
 */
void _generate_subsets(Set *s, Set s_old, UTYPE index, Set *subsets, UTYPE *indices) // function to generate subsets
{
    if (index >= s->size)
        return;

    // create new subset
    Set s_new = generate(s_old.size + 1);

    // copy old subset
    for (UTYPE i = 0; i < s_old.size; i++)
    {
        s_new.mas[i] = s_old.mas[i];
    }

    // add new value
    s_new.mas[s_old.size] = s->mas[index];

    subsets[indices[s_old.size + 1]] = s_new;
    indices[s_old.size + 1] += 1;

    // continue generate from new subset
    _generate_subsets(s, s_new, index + 1, subsets, indices);
    // continue generate from previous subset
    _generate_subsets(s, s_old, index + 1, subsets, indices);
}

/**
 * Generate subsets from given Set .
 * Also Set n to the amount of generated subsets .
 *
 * @param s Set
 * @param n pointer to UTYPE variable
 * @return pointer to the array of subsets
 */
Set *generate_subsets(Set *s, UTYPE *n)
{
    *n = Pow(2, s->size);
    Set *subsets = (Set *)malloc(sizeof(Set) * (*n));

    // indices[i] = first position in array to insert subset, which length is i
    UTYPE *indices = (UTYPE *)malloc(sizeof(UTYPE) * (s->size + 1));
    for (UTYPE i = 0; i < s->size + 1; i++)
    {
        if (i == 0)
            indices[i] = 0;
        else if (i == 1)
            indices[i] = 1;
        else
            indices[i] = Combinations(s->size, i - 1) + indices[i - 1];
    }

    Set s_empty = generate(0);
    subsets[0] = s_empty;

    _generate_subsets(s, s_empty, 0, subsets, indices);

    return subsets;
}

Set *get_unsorted_subsets(Set *s, UTYPE *n)//get all unsorted generated subsets
{
    return generate_subsets(s, n);
}

Set *get_sorted_subsets(Set *s, UTYPE *n) // get all sorted generated subsets
{
    Set *subsets = generate_subsets(s, n);
    sort(subsets, *n);
    return subsets;
}

Set *get_k_size_unsorted_subsets(Set *s, UTYPE *n, UTYPE k) // get unsorted subsets with size = k
{
    UTYPE n_all_subsets;
    Set *subsets = get_unsorted_subsets(s, &n_all_subsets);
    *n = Combinations(s->size, k);
    Set *answer = (Set *)malloc(sizeof(Set) * (*n));
    UTYPE index = 0;
    for (UTYPE i = 0; i < n_all_subsets; i++)
    {
        if (subsets[i].size == k)
        {
            answer[index++] = subsets[i];
        }
    }
    return answer;
}

Set *get_k_size_sorted_subsets(Set *s, UTYPE *n, UTYPE k) //get sorted subsets with size = k
{
    Set *subsets = get_k_size_unsorted_subsets(s, n, k);
    sort(subsets, *n);
    return subsets;
}

void _unsorted_permutations_without_repetitions(Set *s, UTYPE k, Set *perms, UTYPE *index)
{
    if (k == s->size - 1)
    {
        perms[(*index)++] = *s;
    }
    else
    {
        for (int j = k; j < s->size; j++)
        {
            Set s2 = generate(s->size);
            for (UTYPE i = 0; i < s->size; i++)
            {
                s2.mas[i] = s->mas[i];
            }

            swap(k, j, &s2);

            _unsorted_permutations_without_repetitions(&s2, k + 1, perms, index);

            swap(k, j, s);
        }
    }
}

Set *unsorted_permutations_without_repetitions(Set *s, UTYPE *n) // function in order to get unsorted permutations without repetitions
{
    Set *perms = (Set *)malloc(sizeof(Set) * (Factorial(s->size)));
    _unsorted_permutations_without_repetitions(s, 0, perms, n);
    return perms;
}

Set *sorted_permutations_without_repetitions(Set *s, UTYPE *n)
{
    Set *perms = unsorted_permutations_without_repetitions(s, n);
    sort(perms, *n);
    return perms;
}

Set *get_unsorted_subsets_wse(Set *s, UTYPE *n) // for set which contains same elements
{
    UTYPE n_subsets;
    Set *subsets = get_sorted_subsets(s, &n_subsets);
    Set *answer = (Set *)malloc(sizeof(Set) * (n_subsets));
    Set pivot = subsets[0];
    *n = 0;
    answer[(*n)++] = pivot;
    for (size_t i = 1; i < n_subsets; i++)
    {
        if (!equil(subsets[i], pivot))
        {
            pivot = subsets[i];
            answer[(*n)++] = pivot;
        }
    }
    return answer;
}

Set *get_sorted_subsets_wse(Set *s, UTYPE *n) // for Set which contains same elements
{
    Set *answer = get_unsorted_subsets_wse(s, n);
    sort(answer, *n);
    return answer;
}

Set *get_k_size_unsorted_subsets_wse(Set *s, UTYPE *n, UTYPE k) // function in order to get k-size unsorted subsets that contain same elements
{
    UTYPE n_subsets;
    Set *subsets = get_unsorted_subsets(s,n_subsets);
    Set *ans = (Set *)malloc(sizeof(Set) * (n_subsets));
    UTYPE index = 0;
    for (UTYPE i = 0; i < n_subsets; i++)
    {
        if (subsets[i].size == k)
        {
            ans[index ++] = subsets[i];
        }
    }

    return ans;
}

Set *get_k_size_sorted_subsets_wse(Set *s, UTYPE *n, UTYPE k) // function in order to get k-size sorted subsets that contain same elements
{
    Set *subsets = get_k_size_unsorted_subsets_wse(s,n,k);
    sort(subsets,*n);
    return subsets;
}

Set *unsorted_permutations_without_repetitions_wse(Set *s, UTYPE *n)
    UTYPE n_subsets;
    Set *perms = unsorted_permutations_without_repetitions(s, &n_subsets);
    Set *ans = (Set *)malloc(sizeof(Set) * (n_subsets));
    UTYPE index = 0;
    for (UTYPE i=0; i<n_subsets; i++)
    {
        if( perms[i]->size == perms[i+1]->size)
        {
            if ( !a_more_b(perms[i]->))
        }
    }
    return NULL;
}

Set *sorted_permutations_without_repetitions_wse(Set *s, UTYPE *n) // function in order to get sorted permutations that contain
{
    Set *ans = unsorted_permutations_without_repetitions_wse(s,n);
    sort(ans,*n);
    return ans;
}


Set *unsorted_permutations_without_repetitions_wse(Set *s, UTYPE *n)
{
    UTYPE n_subsets;
    Set *sub = sorted_permutations_without_repetitions(s,n_subsets);
    Set *ans = (Set *)malloc(sizeof(Set) * (n_subsets));
    UTYPE index = 0;
    for (UTYPE i = 1; i < n_subsets; i++)
    {
        if(sub[i-1].size == sub[i].size)
        {
            if (!a_more_b(sub->mas[i-1],sub->mas[i]) || !a_more_b(sub->mas[i],sub->mas[i-1]))
            {
                ans[index ++] = sub[i-1];
            }
        }
    }
    return ans;
}
