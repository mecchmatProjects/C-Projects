#include "../src/Permutations1.c"

enum INPUT_TYPE
{
    INPUT_FROM_CONSOLE,
    INPUT_FROM_FILE
};

enum OUTPUT_TYPE
{
    OUTPUT_IN_CONSOLE,
    OUTPUT_IN_FILE
};

const enum INPUT_TYPE input_type = INPUT_FROM_FILE;
const enum OUTPUT_TYPE ouput_type = OUTPUT_IN_FILE;
const char *path_to_inputfile = "home/Julia/C project_2019/20.Permutations_Heifman_Marchuk/tests/test.txt";
const char *path_to_outputfile = "home/Julia/C project_2019/20.Permutations_Heifman_Marchuk/tests/output.txt";

void test_generate_subsets()
{
    printf("TEST generate_subsets function\n");
    Set s;
    UTYPE s_size;
    scanf("%lu", &s_size);
    s = generate(s_size);
    input(&s);
    UTYPE n;
    Set *subsets = generate_subsets(&s, &n);
    for (size_t i = 0; i < n; i++)
    {
        output(subsets[i]);
        printf("\n");
    }
}

void test_get_unsorted_subsets()
{
    printf("TEST get_unsorted_subsets function\n");
    Set s;
    UTYPE s_size;
    scanf("%lu", &s_size);
    s = generate(s_size);
    input(&s);
    UTYPE n;
    Set *subsets = get_unsorted_subsets(&s, &n);
    for (size_t i = 0; i < n; i++)
    {
        output(subsets[i]);
        printf("\n");
    }
}

void test_get_sorted_subsets()
{
    printf("TEST get_sorted_subsets function\n");
    Set s;
    UTYPE s_size;
    scanf("%lu", &s_size);
    s = generate(s_size);
    input(&s);
    UTYPE n;
    Set *subsets = get_sorted_subsets(&s, &n);
    for (size_t i = 0; i < n; i++)
    {
        output(subsets[i]);
        printf("\n");
    }
}

void test_get_k_size_unsorted_subsets()
{
    printf("TEST get_k_size_unsorted_subsets function\n");
    Set s;
    UTYPE s_size, k;
    scanf("%lu %lu", &s_size, &k);
    s = generate(s_size);
    input(&s);
    UTYPE n;
    Set *subsets = get_k_size_unsorted_subsets(&s, &n, k);
    for (size_t i = 0; i < n; i++)
    {
        output(subsets[i]);
        printf("\n");
    }
}

void test_get_k_size_sorted_subsets()
{
    printf("TEST get_k_size_sorted_subsets function\n");
    Set s;
    UTYPE s_size, k;
    scanf("%lu %lu", &s_size, &k);
    s = generate(s_size);
    input(&s);
    UTYPE n;
    Set *subsets = get_k_size_sorted_subsets(&s, &n, k);
    for (size_t i = 0; i < n; i++)
    {
        output(subsets[i]);
        printf("\n");
    }
}

void test_unsorted_permutations_without_repetitions()
{
    printf("TEST unsorted_permutations_without_repetitions function\n");
    Set s;
    UTYPE s_size;
    scanf("%lu", &s_size);
    s = generate(s_size);
    input(&s);
    UTYPE n = 0;
    Set *subsets = unsorted_permutations_without_repetitions(&s, &n);
    for (size_t i = 0; i < n; i++)
    {
        output(subsets[i]);
        printf("\n");
    }
}

void test_sorted_permutations_without_repetitions()
{
    printf("TEST sorted_permutations_without_repetitions function\n");
    Set s;
    UTYPE s_size;
    scanf("%lu", &s_size);
    s = generate(s_size);
    input(&s);
    UTYPE n = 0;
    Set *subsets = sorted_permutations_without_repetitions(&s, &n);
    for (size_t i = 0; i < n; i++)
    {
        output(subsets[i]);
        printf("\n");
    }
}

void test_get_unsorted_subsets_wse()
{
    printf("TEST get_unsorted_subsets_wse function\n");
    Set s;
    UTYPE s_size;
    scanf("%lu", &s_size);
    s = generate(s_size);
    input(&s);
    UTYPE n = 0;
    Set *subsets = get_unsorted_subsets_wse(&s, &n);
    for (size_t i = 0; i < n; i++)
    {
        output(subsets[i]);
        printf("\n");
    }
}

void test_get_sorted_subsets_wse()
{
    printf("TEST get_sorted_subsets_wse function\n");
    Set s;
    UTYPE s_size;
    scanf("%lu", &s_size);
    s = generate(s_size);
    input(&s);
    UTYPE n = 0;
    Set *subsets = get_sorted_subsets_wse(&s, &n);
    for (size_t i = 0; i < n; i++)
    {
        output(subsets[i]);
        printf("\n");
    }
}

void test_get_k_size_unsorted_subsets_wse()
{
    printf("TEST get_k_size_unsorted_subsets_wse function\n");
    Set s;
    UTYPE s_size, k;
    scanf("%lu %lu", &s_size, &k);
    s = generate(s_size);
    input(&s);
    UTYPE n = 0;
    Set *subsets = get_k_size_unsorted_subsets_wse(&s, &n, k);
    for (size_t i = 0; i < n; i++)
    {
        output(subsets[i]);
        printf("\n");
    }

}

void test_get_k_size_sorted_subsets_wse()
{
    printf("TEST get_k_size_sorted_subsets_wse function\n");
    Set s;
    UTYPE s_size,k;
    scanf("%lu %lu", &s_size, &k);
    s = generate(s_size);
    input(&s);
    UTYPE n = 0;
    Set *subsets = get_k_size_sorted_subsets_wse(&s, &n, k);
    for (size_t i = 0; i < n; i++)
    {
        output(subsets[i]);
        printf("\n");
    }
}

void test_unsorted_permutations_without_repetitions_wse()
{
    printf("TEST unsorted_permutations_without_repetitions_wse function\n");
    Set s;
    UTYPE s_size;
    scanf("%lu", &s_size);
    s = generate(s_size);
    input(&s);
    UTYPE n = 0;
    Set *subsets = unsorted_permutations_without_repetitions_wse(&s, &n);
    for (size_t i = 0; i < n; i++)
    {
        output(subsets[i]);
        printf("\n");
    }
}

void test_sorted_permutations_without_repetitions_wse()
{
    printf("TEST sorted_permutations_without_repetitions_wse function\n");
    Set s;
    UTYPE s_size;
    scanf("%lu", &s_size);
    s = generate(s_size);
    input(&s);
    UTYPE n = 0;
    Set *subsets = sorted_permutations_without_repetitions_wse(&s, &n);
    for (size_t i = 0; i < n; i++)
    {
        output(subsets[i]);
        printf("\n");
    }
}

//void test_task1()
//{
//    printf("TEST task1 function\n");
 //   Set s;
   // UTYPE s_size;
    //scanf("%lu", &s_size);
    //s = generate(s_size);
    //input(&s);
    //UTYPE n = 0;
    //Set *subsets = task1(&s, &n);
   // for (size_t i = 0; i < n; i++)
    //{
      //  output(subsets[i]);
        //printf("\n");
    //}
//}

//void test_task2()
//{
   // printf("TEST task2 function\n");
    //Set s;
   // UTYPE s_size;
    //scanf("%lu", &s_size);
   // s = generate(s_size);
   // input(&s);
   // UTYPE n = 0;
    //Set *subsets = task2(&s, &n);
    //for (size_t i = 0; i < n; i++)
    //{
     //   output(subsets[i]);
      //  printf("\n");
    //}
//}

int main()
{
    if (input_type == INPUT_FROM_FILE)
    {
        freopen(path_to_inputfile, "r", stdin);
    }
    if (ouput_type == OUTPUT_IN_FILE)
    {
        freopen(path_to_outputfile, "w", stdout);
    }

    test_get_unsorted_subsets();

    if (input_type == INPUT_FROM_FILE)
    {
        fclose(stdin);
    }
    if (ouput_type == OUTPUT_IN_FILE)
    {
        fclose(stdout);
    }
}
