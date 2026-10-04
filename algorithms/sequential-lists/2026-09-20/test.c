//////#include <iostream>
//////#include <iomanip>
//////
//////using namespace std;
//////
//////struct Complex {
//////	double real;
//////	double imag;
//////};
//////
//////void intputComplex(Complex* z)
//////{
//////	cin >> z->real >> z->imag;
//////}
//////
//////Complex addComplex(Complex a, Complex b)
//////{
//////	Complex result;
//////
//////	result.real = a.real + b.real;
//////	result.imag = b.real+ b.imag;
//////
//////	return result;
//////}
//////
//////void outputComplex(Complex z)
//////{
//////	cout << fixed << setprecision(2)
//////		<< z.real << "+" << z.imag << "i "<<endl;
//////}
//////
//////int main()
//////{
//////	Complex z1, z2, result;
//////
//////	intputComplex(&z1);
//////	intputComplex(&z2);
//////
//////	result = addComplex(z1, z2);
//////
//////	outputComplex(result);
//////
//////	return 0;
//////}
////#define _CRT_SECURE_NO_WARNINGS
////#include <stdio.h>
////
////#define MAXN     100005
////#define LINE_MAX (1 << 21)
////
////static int  A[MAXN], B[MAXN];
////static char line[LINE_MAX];
////
/////* 取下一个整数：跳过逗号、空格、换行 */
////int nextInt(char** pp)
////{
////    char* p = *pp;
////    int sign = 1, v = 0;
////
////    while (*p && (*p < '0' || *p > '9') && *p != '-')
////        ++p;
////    if (*p == '-') { sign = -1; ++p; }
////
////    while (*p >= '0' && *p <= '9') {
////        v = v * 10 + (*p - '0');
////        ++p;
////    }
////
////    *pp = p;
////    return sign * v;
////}
////
////int CompareSqList(const int A[], int n, const int B[], int m)
////{
////    int i = 0;
////
////    while (i < n && i < m && A[i] == B[i])
////        ++i;
////
////    if (i == n && i == m) return 0;
////    if (i == n)           return -1;
////    if (i == m)           return 1;
////
////    return (A[i] < B[i]) ? -1 : 1;
////}
////
////int main(void)
////{
////    char* p;
////    int   n, m, i;
////
////    if (fgets(line, LINE_MAX, stdin) == NULL) return 0;
////    p = line;
////    n = nextInt(&p);
////
////    if (fgets(line, LINE_MAX, stdin) == NULL) return 0;
////    p = line;
////    for (i = 0; i < n; ++i) A[i] = nextInt(&p);
////
////    if (fgets(line, LINE_MAX, stdin) == NULL) return 0;
////    p = line;
////    m = nextInt(&p);
////
////    if (fgets(line, LINE_MAX, stdin) == NULL) return 0;
////    p = line;
////    for (i = 0; i < m; ++i) B[i] = nextInt(&p);
////
////    printf("%d\n", CompareSqList(A, n, B, m));
////    return 0;
//////}
//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//
//#define MAXN     100005
//#define LINE_MAX (1 << 21)
//
//static int  A[MAXN + 1];      
//static char line[LINE_MAX];
//
//int nextInt(char** pp)       
//{
//    char* p = *pp;
//    int sign = 1, v = 0;
//    while (*p && (*p < '0' || *p > '9') && *p != '-') ++p;
//    if (*p == '-') { sign = -1; ++p; }
//    while (*p >= '0' && *p <= '9') { v = v * 10 + (*p - '0'); ++p; }
//    *pp = p;
//    return sign * v;
//}
//
//int InsertOrder(int A[], int n, int x)
//{
//    int i;
//
//    if (n >= MAXN) return n;
//
//    for (i = n - 1; i >= 0 && A[i] > x; --i)
//        A[i + 1] = A[i];
//
//    A[i + 1] = x;
//    return n + 1;
//}
//    int main(void)
//    {
//        char* p;
//        int   n, x, i;
//
//        if (fgets(line, LINE_MAX, stdin) == NULL) return 0;
//        p = line; n = nextInt(&p);
//
//        if (fgets(line, LINE_MAX, stdin) == NULL) return 0;
//        p = line;
//        for (i = 0; i < n; ++i) A[i] = nextInt(&p);
//
//        if (fgets(line, LINE_MAX, stdin) == NULL) return 0;
//        p = line; x = nextInt(&p);
//
//        n = InsertOrder(A, n, x);
//
//        for (i = 0; i < n; ++i) {
//            if (i) putchar(',');
//            printf("%d", A[i]);
//        }
//        putchar('\n');
//        return 0;
//    }

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define MAXN 100005

static int A[MAXN], B[MAXN], C[MAXN], D[MAXN];

int readList(int a[], int maxn)
{
    int n = 0;
    int x;

    while (scanf("%d", &x) == 1 && x != -1)   /* 读到 -1 或文件尾为止 */
    {
        if (n < maxn)
        {
            a[n++] = x;
        }
    }
    return n;
}

/* 求 B 与 C 的交集，存进 D，返回长度 d（D 递增、无重复） */
int intersect(const int B[], int m, const int C[], int p, int D[])
{
    int j = 0, k = 0, d = 0;

    while (j < m && k < p)
    {
        if (B[j] < C[k])
        {
            ++j;                          /* B 的元素小，永久丢弃 */
        }
        else if (B[j] > C[k])
        {
            ++k;                          /* C 的元素小，同理 */
        }
        else
        {
            int v = B[j];                 /* 公共元素 */
            D[d++] = v;
            while (j < m && B[j] == v)    /* 跳过 B 里的重复 v */
            {
                ++j;
            }
            while (k < p && C[k] == v)    /* 跳过 C 里的重复 v */
            {
                ++k;
            }
        }
    }
    return d;
}

/* 从 A 中删去所有出现在 D 中的元素，返回新表长 */
int removeAll(int A[], int n, const int D[], int d)
{
    int i = 0, w = 0, t = 0;

    while (i < n)
    {
        while (t < d && D[t] < A[i])      /* t 只前进不后退（A 也有序） */
        {
            ++t;
        }

        if (t >= d || D[t] != A[i])
        {
            A[w++] = A[i];                /* 不在 D 中 → 保留（向前覆写） */
        }
        /* 否则命中，丢弃 A[i] */

        ++i;
    }
    return w;
}

int main(void)
{
    int n, m, p, d, i;

    n = readList(A, MAXN);
    m = readList(B, MAXN);
    p = readList(C, MAXN);

    d = intersect(B, m, C, p, D);
    n = removeAll(A, n, D, d);

    for (i = 0; i < n; ++i)
    {
        if (i)
        {
            putchar(' ');
        }
        printf("%d", A[i]);
    }
    putchar('\n');
    return 0;
}