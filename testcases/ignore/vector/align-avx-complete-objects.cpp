// RUN: %driver -cc1 %isys %std_cxx11-14 %s -fmax-type-align=16 -Werror %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys %std_cxx17- %s -fmax-type-align=16 -Werror %target -o %t%output-suffix && %filecheck

typedef float AVX2Float __attribute__((__vector_size__(32)));


#if __cplusplus < 202002L
volatile
#endif
float TestAlign(void)
{
       volatile AVX2Float *p = new AVX2Float;
        *p = *p;
        AVX2Float r = *p;
        return r[0];
}


typedef float AVX2Float_Explicitly_aligned __attribute__((__vector_size__(32))) __attribute__((aligned (32)));

typedef AVX2Float_Explicitly_aligned AVX2Float_indirect;

typedef AVX2Float_indirect AVX2Float_use_existing_align;

#if __cplusplus < 202002L
volatile
#endif
float TestAlign2(void)
{
       volatile AVX2Float_use_existing_align *p = new AVX2Float_use_existing_align;
        *p = *p;
        AVX2Float_use_existing_align r = *p;
        return r[0];
}

