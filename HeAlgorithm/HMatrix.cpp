#include "HMatrix.h"
#include "HGslHelper.h"
#include <gsl/gsl_blas.h>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_permutation.h>

HE_BEGIN_NAMESPACE

void HMatrix::mul(gsl_matrix *a, gsl_matrix *b, gsl_matrix *c)
{
    gsl_blas_dgemm(CblasNoTrans, CblasNoTrans, 1.0, a, b, 0.0, c);
}

QVector<double> HMatrix::mul(gsl_matrix *a, QVector<double> b)
{
    auto v = gsl_matrix_view_array(b.data(), b.size(), 1);
    auto c = gsl_matrix_calloc(b.size(), 1);
    mul(a, &v.matrix, c);
    auto r = HGslHelper::toVector(c);
    gsl_matrix_free(c);
    return r;
}

void HMatrix::inverse(gsl_matrix *a)
{
    int sign = 0;
    auto n = a->size1;
    auto t = gsl_matrix_calloc(n, n);
    auto i = gsl_matrix_calloc(n ,n);
    auto p = gsl_permutation_calloc(n);

    gsl_matrix_memcpy(t, a);
    gsl_linalg_LU_decomp(t, p, &sign);
    gsl_linalg_LU_invert(t, p, i);
    gsl_matrix_memcpy(a, i);

    gsl_permutation_free(p);
    gsl_matrix_free(i);
    gsl_matrix_free(t);
}

HE_END_NAMESPACE

//#include <stdio.h>
//#include <gsl/gsl_blas.h>

//int main (void)
//{
//    double a[] = { 0.11, 0.12, 0.13,
//                  0.21, 0.22, 0.23 };

//    double b[] = { 1011, 1012,
//                  1021, 1022,
//                  1031, 1032 };

//    double c[] = { 0.00, 0.00,
//                  0.00, 0.00 };

//    gsl_matrix_view A = gsl_matrix_view_array(a, 2, 3);
//    gsl_matrix_view B = gsl_matrix_view_array(b, 3, 2);
//    gsl_matrix_view C = gsl_matrix_view_array(c, 2, 2);

//    /* Compute C = A B */

//    gsl_blas_dgemm (CblasNoTrans, CblasNoTrans,
//                   1.0, &A.matrix, &B.matrix,
//                   0.0, &C.matrix);

//    printf ("[ %g, %g\n", c[0], c[1]);
//    printf ("  %g, %g ]\n", c[2], c[3]);

//    return 0;
//}

// 相乘
//void gsl_matrix_mul(gsl_matrix *a,gsl_matrix *b,gsl_matrix *c)
//{
//    for (size_t i=0;i<a->size1;i++)
//    {
//        for (size_t j=0;j<b->size2;j++)
//        {
//            double sum=0.0;
//            for (size_t k=0;k<b->size1;k++)
//            {
//                sum+=gsl_matrix_get(a,i,k)*gsl_matrix_get(b,k,j);
//            }
//            gsl_matrix_set(c,i,j,sum);
//        }
//    }
//}

// 求逆
//void gsl_matrix_inverse(gsl_matrix *a)
//{
//    size_t n=a->size1;
//    size_t m=a->size2;

//    gsl_matrix *temp1=gsl_matrix_calloc(n,n);
//    gsl_matrix_memcpy(temp1,a);

//    gsl_permutation *p=gsl_permutation_calloc(n);
//    int sign=0;
//    gsl_linalg_LU_decomp(temp1,p,&sign);
//    gsl_matrix *inverse=gsl_matrix_calloc(n,n);

//    gsl_linalg_LU_invert(temp1,p,inverse);
//    gsl_matrix_memcpy(a,inverse);

//    gsl_permutation_free(p);
//    gsl_matrix_free(temp1);
//    gsl_matrix_free(inverse);

//}


