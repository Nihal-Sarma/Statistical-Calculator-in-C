#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <limits.h>
void clearInputBuffer(void)
{
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF)
        ;
}
void sort(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}
float quartile_interpolated(int x[], int n, float p)
{
    float pos = p * (n - 1);
    int i = (int)pos;
    float frac = pos - i;

    if (i + 1 < n)
        return x[i] + frac * (x[i + 1] - x[i]);
    else
        return x[i];
}
float indiv_Mean(int x[], int n, bool *mark)
{
    if (*mark == true)
    {
        printf("==========================================================================\n");
        printf("                          Arithmetic Mean\n");
        printf("==========================================================================\n");
        printf("                                                        Individual serise:\n");
        printf("NO. Of X           X\n");
        printf("===========================\n");
    }
    float sum = 0;
    for (int i = 0; i < n; i++)
    {
        if (*mark == true)
            printf("    %d              %d\n", i + 1, x[i]);
        sum += x[i];
    }
    if (*mark == true)
        printf("\nN = %d      Sigma_X = %d", n, (int)sum);
    *mark = false;
    return sum / n;
}
float discr_Mean(int x[], int f[], int n, bool *mark)
{
    if (*mark == true)
    {
        printf("==========================================================================\n");
        printf("                          Arithmetic Mean\n");
        printf("==========================================================================\n");
        printf("                                                          Discrete serise:\n");
        printf("\n       X                  F                   FX      \n");
        printf("========================================================\n");
    }
    float N = 0, sum = 0;
    for (int i = 0; i < n; i++)
    {
        if (*mark == true)
            printf("      %d                  %d                   %d\n", x[i], f[i], x[i] * f[i]);
        sum += (x[i] * f[i]);
        N += f[i];
    }
    if (*mark == true)
        printf("\n                        N = %d         Sigma_FX = %d\n", (int)N, (int)sum);
    *mark = false;
    return sum / N;
}
float conti_Mean(int l[], int u[], int f[], int n, bool *mark)
{
    if (*mark == true)
    {
        printf("==========================================================================\n");
        printf("                          Arithmetic Mean\n");
        printf("==========================================================================\n");
        printf("                                                        Continuous serise:\n");
        printf("\n      C.I         F           M           FM      \n");
        printf("====================================================\n");
    }
    float N = 0, sum = 0;
    for (int i = 0; i < n; i++)
    {
        if (*mark == true)
            printf("    %d - %d        %d          %.2f          %.2f\n", l[i], u[i], f[i], (float)(l[i] + u[i]) / 2, (float)f[i] * ((l[i] + u[i]) / 2));
        sum += (((l[i] + u[i]) / 2) * f[i]);
        N += f[i];
    }
    if (*mark == true)
        printf("\n                        N = %d          Sigma_FM = %.2f\n", (int)N, sum);
    *mark = false;
    return sum / N;
}
float indiv_Median(int x[], int n, bool *mark)
{
    if (*mark == true)
    {
        printf("==========================================================================\n");
        printf("                          Calculate Median\n");
        printf("==========================================================================\n");
        printf("                                                        Individual serise:\n");
    }
    int *xs = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
        xs[i] = x[i];
    sort(xs, n);
    if (*mark == true)
        printf("\n  X   :  ");
    for (int i = 0; i < n; i++)
        if (*mark == true)
            printf("%d ", xs[i]);
    float median;
    if (n % 2 != 0)
        median = xs[n / 2];
    else
    {
        median = (xs[(n / 2) - 1] + xs[(n / 2)]) / 2.0;
    }
    free(xs);
    *mark = false;
    return median;
}
int discr_Median(int x[], int f[], int n, bool *mark)
{
    if (*mark == true)
    {
        printf("==========================================================================\n");
        printf("                          Calculate Median\n");
        printf("==========================================================================\n");
        printf("                                                          Discrete serise:\n");
        printf("\n       X                  F                   CF      \n");
        printf("========================================================\n");
    }
    int *cf = malloc(n * sizeof(int));
    int temp = 0, median;
    for (int i = 0; i < n; i++)
    {
        temp += f[i];
        cf[i] = temp;
        if (*mark == true)
            printf("      %d                  %d                   %d\n", x[i], f[i], cf[i]);
    }
    if (*mark == true)
        printf("\n                      N/2 = %.2f\n", (float)cf[n - 1] / 2);
    for (int i = 0; i < n; i++)
    {
        if ((float)cf[n - 1] / 2 <= cf[i])
        {
            median = x[i];
            break;
        }
    }
    free(cf);
    *mark = false;
    return median;
}
float conti_Median(int l[], int u[], int f[], int n, bool *mark)
{
    if (*mark == true)
    {
        printf("==========================================================================\n");
        printf("                           Calculate Median\n");
        printf("==========================================================================\n");
        printf("                                                        Continuous serise:\n");
    }
    int temp = 0;
    int *cf = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
    {
        temp += f[i];
        cf[i] = temp;
    }
    float Nd2 = cf[n - 1] / 2.0, h;
    int L, cf1, f1;
    for (int i = 0; i < n; i++)
    {
        if (Nd2 <= cf[i])
        {
            if (i == 0)
                cf1 = 0;
            else
                cf1 = cf[i - 1];
            f1 = f[i];
            L = l[i];
            h = u[i] - l[i];
            temp = i;
            break;
        }
    }
    if (*mark == true)
    {
        printf("\n      C.I               F                CF\n");
        printf("====================================================\n");
        for (int i = 0; i < n; i++)
        {
            if (L == l[i])
                printf("   L%d - %d             f%d              %d\n", l[i], u[i], f[i], cf[i]);
            else if (temp == i + 1)
                printf("    %d - %d              %d             cf%d\n", l[i], u[i], f[i], cf[i]);
            else
                printf("    %d - %d              %d               %d\n", l[i], u[i], f[i], cf[i]);
        }
        printf("\n                    N/2 = %.2f", Nd2);
    }
    free(cf);
    *mark = false;
    return L + (((Nd2 - cf1) / f1) * h);
}
int indiv_Mode(int x[], int n)
{
    printf("==========================================================================\n");
    printf("                            Calculate Mode\n");
    printf("==========================================================================\n");
    printf("                                                        Individual serise:\n");
    int mode;
    int count1, count2 = 0;
    printf("\n  X   :  ");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", x[i]);
        count1 = 0;
        for (int j = 0; j < n; j++)
        {
            if (x[i] == x[j])
            {
                count1++;
            }
        }
        if (count2 < count1)
        {
            count2 = count1;
            mode = x[i];
        }
    }
    if (count2 == 1)
    {
        return INT_MIN;
    }
    else
        return mode;
}
int discr_Mode(int x[], int f[], int n)
{
    printf("==========================================================================\n");
    printf("                            Calculate Mode\n");
    printf("==========================================================================\n");
    printf("                                                          Discrete serise:\n");
    int mode, count = 0;
    int maxf = INT_MIN;
    printf("   X                F\n");
    printf("===========================\n");
    for (int i = 0; i < n; i++)
    {
        printf("   %d               %d\n", x[i], f[i]);
        if (f[i] > maxf)
        {
            maxf = f[i];
            mode = x[i];
        }
    }
    for (int i = 0; i < n; i++)
    {
        if (f[i] == maxf)
            count++;
    }
    if (count != n)
        return mode;
    else
        return INT_MIN;
}
float conti_Mode(int l[], int u[], int f[], int n)
{
    printf("==========================================================================\n");
    printf("                            Calculate Mode\n");
    printf("==========================================================================\n");
    printf("                                                        Continuous serise:\n");
    int f0, f2, modal, h, f1 = INT_MIN;
    for (int i = 0; i < n; i++)
    {
        if (f[i] > f1)
        {
            f1 = f[i];
            modal = i;
        }
    }
    printf("     C.I                 F\n");
    printf("================================\n");
    for (int i = 0; i < n; i++)
    {
        if (i == modal)
        {
            printf("   L%d - %d          f1 %d\n", l[i], u[i], f[i]);
        }
        else if (i == modal - 1)
        {
            printf("    %d - %d            f0 %d\n", l[i], u[i], f[i]);
        }
        else if (i == modal + 1)
        {
            printf("    %d - %d          f2 %d\n", l[i], u[i], f[i]);
        }
        else
            printf("    %d - %d             %d\n", l[i], u[i], f[i]);
    }
    if (modal == 0 || modal == n - 1)
    {
        printf("\nMode cannot be calculated (modal class at boundary).\n");
        return INT_MIN;
    }
    else
    {
        f0 = f[modal - 1];
        f2 = f[modal + 1];
        h = u[modal] - l[modal];
        float L = l[modal] - 0.5f;
        return L + ((f1 - f0) / ((float)(2 * f1) - f0 - f2) * h);
    }
}
void indiv_Range(int x[], int n, int *R, float *CV)
{
    printf("==========================================================================\n");
    printf("                           Calculate Range\n");
    printf("==========================================================================\n");
    printf("                                                        Individual serise:\n");
    int max = INT_MIN, min = INT_MAX;
    if (n <= 0)
    {
        *R = INT_MIN;
        return;
    }
    printf("\n  X   :  ");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", x[i]);
        if (max < x[i])
            max = x[i];

        if (min > x[i])
            min = x[i];
    }
    *R = max - min;
    *CV = *R / (float)(max + min);
}
void discr_Range(int x[], int f[], int n, int *R, float *CV)
{
    printf("==========================================================================\n");
    printf("                           Calculate Range\n");
    printf("==========================================================================\n");
    printf("                                                          Discrete serise:\n");
    int max = INT_MIN, min = INT_MAX;
    if (n <= 0)
    {
        *R = INT_MIN;
        return;
    }
    printf("   X                F\n");
    printf("===========================\n");
    for (int i = 0; i < n; i++)
    {
        printf("   %d               %d\n", x[i], f[i]);
        if (max < x[i])
            max = x[i];

        if (min > x[i])
            min = x[i];
    }
    *R = max - min;
    *CV = *R / (float)(max + min);
}
void conti_Range(int l[], int u[], int f[], int n, int *R, float *CV)
{
    printf("==========================================================================\n");
    printf("                           Calculate Range\n");
    printf("==========================================================================\n");
    printf("                                                        Continuous serise:\n");
    int max = INT_MIN, min = INT_MAX;
    if (n <= 0)
    {
        *R = INT_MIN;
        return;
    }
    printf("     C.I                F\n");
    printf("================================\n");
    for (int i = 0; i < n; i++)
    {
        printf("    %d - %d             %d\n", l[i], u[i], f[i]);
        if (max < u[i])
            max = u[i];
        if (min > l[i])
            min = l[i];
    }
    *R = max - min;
    *CV = *R / (float)(max + min);
}
void indiv_Q(float *AIQD, float *AQD, float *SIQD, float *SQD, float *CV, float *SCV, int x[], int n)
{
    printf("==========================================================================\n");
    printf("                          Calculate QD & IQD\n");
    printf("==========================================================================\n");
    printf("                                                        Individual serise:\n");
    int *xs = malloc(n * sizeof(int));
    printf("\n  X   :  ");
    for (int i = 0; i < n; i++)
    {
        xs[i] = x[i];
        printf("%d ", xs[i]);
    }
    sort(xs, n);
    float pQ1 = quartile_interpolated(xs, n, 0.25);
    float pQ3 = quartile_interpolated(xs, n, 0.75);
    *AIQD = pQ3 - pQ1;
    *AQD = (*AIQD) / 2.0;
    *CV = *AIQD / (pQ3 + pQ1);
    float Q3, Q1;
    if (n % 2 == 0)
    {
        Q3 = ((3 * (n + 1)) / 4);
        Q1 = ((n + 1) / 4);
    }
    else
    {
        Q3 = ((3 * (n + 1)) / 4);
        if ((Q3 + 0.50) > (int)(Q3 + 1))
            Q3 = ceil(Q3);

        Q1 = ((n + 1) / 4);
        if ((Q1 + 0.50) > (int)(Q1 + 1))
            Q1 = ceil(Q1);
    }
    *SIQD = xs[(int)Q3 - 1] - (float)xs[(int)Q1 - 1];
    *SQD = (xs[(int)Q3 - 1] - xs[(int)Q1 - 1]) / 2.0;
    *SCV = *SIQD / (xs[(int)Q3 - 1] + (float)xs[(int)Q1 - 1]);
    free(xs);
}
void discr_Q(float *SIQD, float *SQD, float *CV, int x[], int f[], int n)
{
    printf("==========================================================================\n");
    printf("                          Calculate QD & IQD\n");
    printf("==========================================================================\n");
    printf("                                                          Discrete serise:\n");
    int temp = 0;
    int *cf = malloc(n * sizeof(int));
    printf("\n       X               F                CF\n");
    printf("=================================================\n");
    for (int i = 0; i < n; i++)
    {
        temp += f[i];
        cf[i] = temp;
        printf("      %d               %d                %d\n", x[i], f[i], cf[i]);
    }
    int N = cf[n - 1];
    float pQ3, pQ1, Q1, Q3;
    pQ3 = ((3 * (N + 1)) / 4.0);
    pQ1 = ((N + 1) / 4.0);
    for (int i = 0; i < n; i++)
    {
        if (cf[i] >= pQ1)
        {
            Q1 = x[i];
            break;
        }
    }
    for (int i = 0; i < n; i++)
    {
        if (cf[i] >= pQ3)
        {
            Q3 = x[i];
            break;
        }
    }
    *SIQD = Q3 - Q1;
    *SQD = *SIQD / 2;
    *CV = *SIQD / (Q3 + Q1);
    free(cf);
}
void conti_Q(float *SIQD, float *SQD, float *CV, int l[], int u[], int f[], int n)
{
    printf("==========================================================================\n");
    printf("                          Calculate QD & IQD\n");
    printf("==========================================================================\n");
    printf("                                                        Continuous serise:\n");
    int h, temp = 0;
    int *cf = malloc(n * sizeof(int));
    printf("\n       C.I              F                CF\n");
    printf("==================================================\n");
    for (int i = 0; i < n; i++)
    {
        temp += f[i];
        cf[i] = temp;
        printf("     %d - %d            %d                %d\n", l[i], u[i], f[i], cf[i]);
    }
    float Nd4 = cf[n - 1] / 4.0;
    int L, cf1, f1;
    for (int i = 0; i < n; i++)
    {
        if (Nd4 <= cf[i])
        {
            cf1 = (i == 0) ? 0 : cf[i - 1];
            f1 = f[i];
            L = l[i];
            h = u[i] - l[i];
            break;
        }
    }
    float Q1 = L + (Nd4 - cf1) / f1 * h;
    for (int i = 0; i < n; i++)
    {
        if (3 * Nd4 <= cf[i])
        {
            cf1 = (i == 0) ? 0 : cf[i - 1];
            f1 = f[i];
            L = l[i];
            h = u[i] - l[i];
            break;
        }
    }
    float Q3 = L + ((3 * Nd4) - cf1) / f1 * h;
    *SIQD = Q3 - Q1;
    *SQD = *SIQD / 2;
    *CV = *SIQD / (Q3 + Q1);
    free(cf);
}
void indiv_MD(float *MDx, float *MDm, float *CMDx, float *CMDm, int x[], int n, bool *mark)
{
    printf("==============================================================================================\n");
    printf("                                 Calculate Mean Deviation\n");
    printf("==============================================================================================\n");
    printf("                                                                            Individual serise:\n");
    float mean = indiv_Mean(x, n, &(*mark)), median = indiv_Median(x, n, &(*mark));
    float sum = 0, sum2 = 0;
    printf("\n    X            |X - Mean|           |X - Median|\n");
    printf("========================================================\n");
    for (int i = 0; i < n; i++)
    {
        printf("     %d               %.2f                 %.2f\n", x[i], (float)(fabs(x[i] - mean)), (float)(fabs(x[i] - median)));
        sum += fabs(x[i] - mean);
        sum2 += fabs(x[i] - median);
    }
    *MDx = sum / n;
    *MDm = sum / n;
    *CMDx = (mean != 0) ? (*MDx / mean) : 0;
    *CMDm = (median != 0) ? (*MDm / median) : 0;
}
void discr_MD(float *MDx, float *MDm, float *CMDx, float *CMDm, int x[], int f[], int n, bool *mark)
{
    printf("==============================================================================================\n");
    printf("                                 Calculate Mean Deviation\n");
    printf("==============================================================================================\n");
    printf("                                                                                Discrete serise:\n");
    float N = 0, sum = 0, sum2 = 0;
    float mean = discr_Mean(x, f, n, &(*mark)), median = discr_Median(x, f, n, &(*mark));
    printf("\n  X       F       |X - Mean|      F|X - Mean|     |X - Median|        F|X - Median|\n");
    printf("========================================================================================\n");
    for (int i = 0; i < n; i++)
    {
        printf("  %d      %d          %.2f             %.2f           %.2f               %.2f\n", x[i], f[i], (float)(fabs(x[i] - mean)), (float)(f[i] * fabs(x[i] - mean)), (float)(fabs(x[i] - median)), (float)(f[i] * fabs(x[i] - median)));
        N += f[i];
        sum += f[i] * (fabs(x[i] - mean));
        sum2 += f[i] * (fabs(x[i] - median));
    }
    *MDx = sum / N;
    *MDm = sum2 / N;
    *CMDx = (mean != 0) ? (*MDx / mean) : 0;
    *CMDm = (median != 0) ? (*MDm / median) : 0;
}
void conti_MD(float *MDx, float *MDm, float *CMDx, float *CMDm, int l[], int u[], int f[], int n, bool *mark)
{
    printf("==============================================================================================\n");
    printf("                                 Calculate Mean Deviation\n");
    printf("==============================================================================================\n");
    printf("                                                                            Continuous serise:\n");
    int N = 0;
    float sum = 0, sum2 = 0, mean = conti_Mean(l, u, f, n, &(*mark)), median = conti_Median(l, u, f, n, &(*mark));
    printf("\n    C.I       F       M       |M - Mean|   F|M - Mean|   |M - Median|    F|M - Median|\n");
    printf("===========================================================================================\n");
    for (int i = 0; i < n; i++)
    {
        if ((float)((l[i] + u[i]) / 2) < 9)
            printf("  %d - %d      %d     %.2f        %.2f         %.2f         %.2f            %.2f\n", l[i], u[i], f[i], (float)((l[i] + u[i]) / 2), (float)(fabs(((l[i] + u[i]) / 2) - mean)), (float)(f[i] * fabs(((l[i] + u[i]) / 2) - mean)), (float)(fabs(((l[i] + u[i]) / 2) - median)), (float)(f[i] * fabs(((l[i] + u[i]) / 2) - median)));
        else
            printf("  %d - %d     %d     %.2f        %.2f         %.2f           %.2f           %.2f\n", l[i], u[i], f[i], (float)((l[i] + u[i]) / 2), (float)(fabs(((l[i] + u[i]) / 2) - mean)), (float)(f[i] * fabs(((l[i] + u[i]) / 2) - mean)), (float)(fabs(((l[i] + u[i]) / 2) - median)), (float)(f[i] * fabs(((l[i] + u[i]) / 2) - median)));
        N += f[i];
        sum += f[i] * (float)(fabs(((l[i] + u[i]) / 2) - mean));
        sum2 += f[i] * (float)(fabs(((l[i] + u[i]) / 2) - median));
    }
    *MDx = sum / N;
    *MDm = sum2 / N;
    *CMDx = (mean != 0) ? (*MDx / mean) : 0;
    *CMDm = (median != 0) ? (*MDm / median) : 0;
}
void indiv_SD(float *SD, float *CV, float *Vri, int x[], int n, bool *mark)
{
    printf("=============================================================================\n");
    printf("                 Calculate Standard Deviation(SD) & Variance\n");
    printf("=============================================================================\n");
    printf("                                                           Individual serise:\n");
    float mean = indiv_Mean(x, n, &(*mark));
    float sum = 0;
    printf("\n    X            X - Mean         (X - Mean)^2\n");
    printf("==================================================\n");
    for (int i = 0; i < n; i++)
    {
        printf("  %d               %.2f              %.2f\n", x[i], x[i] - mean, pow((x[i] - mean), 2));
        sum += (pow(x[i] - mean, 2));
    }
    printf("                N = %d", n);
    *SD = sqrt(sum / n);
    *CV = (mean != 0) ? (*SD / mean) : 0.0;
    *Vri = sum / n;
}
void discr_SD(float *SD, float *CV, float *Vri, int x[], int f[], int n, bool *mark)
{
    printf("=============================================================================\n");
    printf("                 Calculate Standard Deviation(SD) & Variance\n");
    printf("=============================================================================\n");
    printf("                                                             Discrete serise:\n");
    float N = 0, sum = 0, mean = discr_Mean(x, f, n, &(*mark));
    printf("\n    X      F      X - Mean       (X - Mean)^2      F(X - Mean)^2\n");
    printf("=====================================================================\n");
    for (int i = 0; i < n; i++)
    {
        if ((x[i] - mean) > 9.0 || (x[i] - mean) < -9.0)
            printf("  %d      %d       %.2f           %.2f            %.2f\n", x[i], f[i], x[i] - mean, pow((x[i] - mean), 2), f[i] * (pow((x[i] - mean), 2)));
        else
            printf("  %d      %d         %.2f             %.2f             %.2f\n", x[i], f[i], x[i] - mean, pow((x[i] - mean), 2), f[i] * (pow((x[i] - mean), 2)));
        N += f[i];
        sum += (f[i] * (pow(x[i] - mean, 2)));
    }
    printf("                N = %d", (int)N);
    *SD = sqrt(sum / N);
    *CV = (mean != 0) ? (*SD / mean): 0.0;
    *Vri = sum / N;
}
void conti_SD(float *SD, float *CV, float *Vri, int l[], int u[], int f[], int n, bool *mark)
{
    printf("=============================================================================\n");
    printf("                 Calculate Standard Deviation(SD) & Variance\n");
    printf("=============================================================================\n");
    printf("                                                           Continuous serise:\n");
    float sum = 0, N = 0, mean = conti_Mean(l, u, f, n, &(*mark));
    printf("\n    C.I      F       M       M - Mean       (M - Mean)^2      F(M - Mean)^2\n");
    printf("==============================================================================\n");
    for (int i = 0; i < n; i++)
    {
        printf("  %d - %d    %d      %.2f      %.2f           %.2f             %.2f\n", l[i], u[i], f[i], (float)((l[i] + u[i]) / 2), (float)((l[i] + u[i]) / 2) - mean, (float)(pow(((l[i] + u[i]) / 2) - mean, 2)), (float)(f[i] * pow(((l[i] + u[i]) / 2) - mean, 2)));
        N += f[i];
        sum += (f[i] * pow(((float)((l[i] + u[i]) / 2) - mean), 2));
    }
    printf("                N = %d", (int)N);
    *SD = sqrt(sum / N);
    *CV = (mean != 0) ? (*SD / mean) : 0.0;
    *Vri = sum / N;
}
int main()
{
    printf("                                               Welcome!\n");
    printf("==========================================================================================================\n");
    printf("                                     Statistical Calculator V1.O\n");
    printf("==========================================================================================================\n");

    printf("\n# MEASURES OF CENTRAL TENDENCY :                                   # MEASURES OF DISPERSION :       \n");
    printf("\n       1. Arithmetic Mean.                                             4. Range. \n");
    printf("       2. Median.                                                      5. Interquartile Deviation(IQD)");
    printf("\n       3. Mode.                                                          & Quartile Deviation(QD) \n");
    printf("                                                                       6. Mean Deviation. \n");
    printf("                                                                       7. Standard Deviation & Variance\n");
    printf("\n==========================================================================================================\n");
    printf("     NOTE : Before calculating enter the serise.....");
    printf("\n==========================================================================================================\n");
    int choice;
    printf("\n1.Individual serise\n");
    printf("2.Discrete serise\n");
    printf("3.Continuous serise\n");
    printf("\nWhich serise do you want to calculate : ");
    scanf("%d", &choice);
    int *x = NULL;
    int *f = NULL;
    int *l = NULL;
    int *u = NULL;
    int size = 0;

    if (choice == 1)
    {
        x = malloc(100 * sizeof(int));
        printf("NOTE : When you want stop the serise just enter s ...\n\n");
        printf("Enter X serise : ");
        int n = 0;
        while (n < 100)
        {
            if (scanf("%d", &x[n]) != 1)
            {
                clearInputBuffer();
                break;
            }
            n++;
        }
        size = n;
    }
    else if (choice == 2)
    {
        x = malloc(100 * sizeof(int));
        f = malloc(100 * sizeof(int));
        printf("NOTE : When you want stop the serise just enter s ...\n\n");
        printf("Enter X serise : ");
        int n = 0;
        while (n < 100)
        {
            if (scanf("%d", &x[n]) != 1)
            {
                clearInputBuffer();
                break;
            }

            n++;
        }
        size = n;
        printf("\nEnter Frequencies f : ");
        for (int i = 0; i < n; i++)
        {
            scanf("%d", &f[i]);
        }
    }
    else if (choice == 3)
    {
        l = malloc(100 * sizeof(int));
        u = malloc(100 * sizeof(int));
        f = malloc(100 * sizeof(int));
        printf("\nNOTE :\nEnter Continuous serise as pair, first enter one pair & press enter then so on OR stop with s..\n\n");
        printf("Enter C.I : \n");
        int n = 0;
        while (n < 100)
        {

            if (scanf("%d", &l[n]) != 1)
            {
                clearInputBuffer();
                break;
            }
            scanf("%d", &u[n]);
            n++;
        }
        size = n;
        printf("\nEnter Frequencies f : ");
        for (int i = 0; i < n; i++)
        {
            scanf("%d", &f[i]);
        }
    }
    else
    {
        system("cls");
        printf("Out of list!\n");
        return 0;
    }

    system("cls");
    char ch;
    int choice2, R;
    float Z, CV, SCV, AIQD, AQD, SIQD, SQD, MDx, MDm, CMDx, CMDm, SD, Vri;
    bool mark = false;
    do
    {
        if (choice == 1)
        {
            printf("Your serise : \n");
            printf(" X :  ");
            for (int i = 0; i < size; i++)
                printf("%d ", x[i]);
        }
        else if (choice == 2)
        {
            printf("Your serise : \n");
            printf(" X : ");
            for (int i = 0; i < size; i++)
                printf("%d ", x[i]);
            printf("\n F : ");
            for (int i = 0; i < size; i++)
                printf("%d ", f[i]);
        }
        else if (choice == 3)
        {
            printf("Your serise : \n");
            printf(" C.I :  ");
            for (int i = 0; i < size; i++)
                printf("%d ", l[i]);
            printf("\n       ");
            for (int i = 0; i < size; i++)
                printf("%d ", u[i]);
            printf("\n\n   F : ");
            for (int i = 0; i < size; i++)
                printf("%d ", f[i]);
        }
        printf("\n==========================================================================================================\n");
        printf("                                      Statistical Calculator V1.O\n");
        printf("==========================================================================================================\n");

        printf("\n# MEASURES OF CENTRAL TENDENCY :                                   # MEASURES OF DISPERSION :       \n");
        printf("\n       1. Arithmetic Mean.                                             4. Range. \n");
        printf("       2. Median.                                                      5. Interquartile Deviation(IQD)");
        printf("\n       3. Mode.                                                          & Quartile Deviation(QD) \n");
        printf("                                                                       6. Mean Deviation. \n");
        printf("                                                                       7. Standard Deviation & Variance\n");
        printf("\n==========================================================================================================\n");
        printf("\nwhich one do you want to calculate : ");
        scanf("%d", &choice2);
        system("cls");
        switch (choice2)
        {
        case 1:
            switch (choice)
            {
            case 1:
                mark = true;
                printf("\n\nArithmetic Mean is %.2f", indiv_Mean(x, size, &mark));
                break;
            case 2:
                mark = true;
                printf("\n\nArithmetic Mean is %.2f", discr_Mean(x, f, size, &mark));
                break;
            case 3:
                mark = true;
                printf("\n\nArithmetic Mean is %.2f", conti_Mean(l, u, f, size, &mark));
                break;
            default:
                printf("Invalid statement\n");
            }
            break;
        case 2:
            switch (choice)
            {
            case 1:
                mark = true;
                printf("\n\nMedian is %.2f", indiv_Median(x, size, &mark));
                break;
            case 2:
                mark = true;
                printf("\n\nMedian is %d", discr_Median(x, f, size, &mark));
                break;
            case 3:
                mark = true;
                printf("\n\nMedian is %.2f", conti_Median(l, u, f, size, &mark));
                break;
            default:
                printf("Invalid statement\n");
            }
            break;
        case 3:
            switch (choice)
            {
            case 1:
                Z = indiv_Mode(x, size);
                if (Z != INT_MIN)
                    printf("\n\nMode is %d", (int)Z);
                else
                    printf("\n\nNO mode!");
                break;
            case 2:
                Z = discr_Mode(x, f, size);
                if (Z != INT_MIN)
                    printf("\nMode is %d", (int)Z);
                else
                    printf("\n\nNO mode!");
                break;
            case 3:
                Z = conti_Mode(l, u, f, size);
                if (Z != INT_MIN)
                    printf("\n\nMode is %.2f", Z);
                break;
            default:
                printf("Invalid statement\n");
            }
            break;
        case 4:
            switch (choice)
            {
            case 1:
                indiv_Range(x, size, &R, &CV);
                if (R != INT_MIN)
                {
                    printf("\n\nRange is %d", R);
                    printf("\nC.V of Range is %.2f", CV);
                }
                else
                    printf("ERROR");
                break;
            case 2:
                discr_Range(x, f, size, &R, &CV);
                if (R != INT_MIN)
                {
                    printf("\n\nRange is %d", R);
                    printf("\nC.V of Range is %.2f", CV);
                }
                else
                    printf("ERROR");
                break;
            case 3:
                conti_Range(l, u, f, size, &R, &CV);
                if (R != INT_MIN)
                {
                    printf("\n\nRange is %d", R);
                    printf("\nC.V of Range is %.2f", CV);
                }
                else
                    printf("ERROR");
                break;
            default:
                printf("Invalid statement\n");
            }
            break;
        case 5:
            switch (choice)
            {
            case 1:
                indiv_Q(&AIQD, &AQD, &SIQD, &SQD, &CV, &SCV, x, size);
                printf("\n\nAccurate:\n     Inter-Quartile Deviation (IQD) is : %.2f\n     Quartile Deviation (QD) is : %.2f\n     CV of QD is : %.2f", AIQD, AQD, CV);
                printf("\n\nSimple:\n     Inter-Quartile Deviation (IQD) is : %.2f\n     Quartile Deviation (QD) is : %.2f\n     CV of QD is :  %.2f", SIQD, SQD, SCV);
                break;
            case 2:
                discr_Q(&SIQD, &SQD, &CV, x, f, size);
                printf("\n\nInter-Quartile Deviation (IQD) is : %.2f\nQuartile Deviation (QD) is : %.2f\nCV of QD is :  %.2f", SIQD, SQD, CV);
                break;
            case 3:
                conti_Q(&SIQD, &SQD, &CV, l, u, f, size);
                printf("\n\nInter-Quartile Deviation (IQD) is : %.2f\nQuartile Deviation (QD) is : %.2f\nCV of QD is :  %.2f", SIQD, SQD, CV);
                break;
            default:
                printf("Invalid statement\n");
            }
            break;
        case 6:
            switch (choice)
            {
            case 1:
                indiv_MD(&MDx, &MDm, &CMDx, &CMDm, x, size, &mark);
                printf("\nFrom Mean:\nMean Deviation(MD) is %.2f\nCoefficient of Mean Deviation(CV) is %.2f", MDx, CMDx);
                printf("\n\nFrom Median:\nMean Deviation(MD) is %.2f\nCoefficient of Mean Deviation(CV) is %.2f", MDm, CMDm);
                break;
            case 2:
                discr_MD(&MDx, &MDm, &CMDx, &CMDm, x, f, size, &mark);
                printf("\nFrom Mean:\nMean Deviation(MD) is %.2f\nCoefficient of Mean Deviation(CMD) is %.2f", MDx, CMDx);
                printf("\n\nFrom Median:\nMean Deviation(MD) is %.2f\nCoefficient of Mean Deviation(CMD) is %.2f", MDm, CMDm);
                break;
            case 3:
                conti_MD(&MDx, &MDm, &CMDx, &CMDm, l, u, f, size, &mark);
                printf("\nFrom Mean:\nMean Deviation(MD) is %.2f\nCoefficient of Mean Deviation(CMD) is %.2f", MDx, CMDx);
                printf("\n\nFrom Median:\nMean Deviation(MD) is %.2f\nCoefficient of Mean Deviation(CMD) is %.2f", MDm, CMDm);
                break;
            default:
                printf("Invalid statement\n");
            }
            break;
        case 7:
            switch (choice)
            {
            case 1:
                indiv_SD(&SD, &CV, &Vri, x, size, &mark);
                printf("\n\nStandard Deviation(SD) is %.2f\nCoefficient of Standard Deviation(CV) is %.2f\nVariance is %.2f", SD, CV, Vri);
                break;
            case 2:
                discr_SD(&SD, &CV, &Vri, x, f, size, &mark);
                printf("\n\nStandard Deviation(SD) is %.2f\nCoefficient of Standard Deviation(CV) is %.2f\nVariance is %.2f", SD, CV, Vri);
                break;
            case 3:
                conti_SD(&SD, &CV, &Vri, l, u, f, size, &mark);
                printf("\n\nStandard Deviation(SD) is %.2f\nCoefficient of Standard Deviation(CV) is %.2f\nVariance is %.2f", SD, CV, Vri);
                break;
            default:
                printf("Invalid statement\n");
            }
            break;
        default:
            printf("Out of list!\n");
            break;
        }
        printf("\n\nDo you want continue?(y/n) : ");
        scanf(" %c", &ch);
        system("cls");
        if (ch != 'y' && ch != 'Y' && ch != 'n' && ch != 'N')
        {
            printf("Invalit stement!\n");
        }

    } while (ch != 'n' && ch != 'N');
    free(x);
    free(f);
    free(l);
    free(u);
    return 0;
}