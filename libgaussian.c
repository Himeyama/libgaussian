/*
 *  (c) 2021 Murata Mitsuharu
 *  Licensed under the MIT License.
 */


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>


// 倍精度浮動小数点数の配列を表示
// d: 配列
// size: 配列の大きさ
void printd(double d[], long size){
    if(d == NULL) return;
    char* str = (char*)malloc(24 * size + 2);
    str[1] = '\0';
    str[0] = '[';
    char tmp[22];
    for(long i = 0; i < size; i++){
        sprintf(tmp, "%lf, ", d[i]);
        strcat(str, tmp);
    }
    long str_size = strlen(str);
    str[str_size - 2] = ']';
    str[str_size - 1] = '\0';
    puts(str);
}


// 反転したベクトルを返します
// v: 配列
// size: 配列の大きさ
double* dreverse(double v[], long size){
    double* r = malloc(sizeof(double) * size);
    for(long i = 0; i < size; i++)
        r[i] = v[size-i-1];
    return r;
}


// データの両端部分を補完
// v: 配列
// n: 配列の大きさ
// len: 片端補完サイズ
double* dreflect(double *v, long n, long len){
    if(n < len){
        fprintf(stderr, "エラー: 両端の大きさが元の配列より大きいため、補完できません。\n");
        return NULL;
    };
    long r_size = n + 2 * len;
    double* r = (double*)malloc(sizeof(double) * r_size);
    for(long i = 0; i < n; i++){
        r[len + i] = v[i];
    }
    for(long i = 0; i < len; i++){
        r[len - i - 1] = v[i];
        r[len + n + i] = v[n - i - 1];
    }
    return r;
}


// 畳み込み
// input: 入力配列
// input_size: 配列の大きさ
// weights: 重み配列
// weights_size: 重み配列の大きさ
double* correlate1d(double* input, long input_size, double* weights, long weights_size){
    long n = input_size - weights_size;
    double* r = (double*)malloc(sizeof(double) * n);
    for(long i = 0; i <= n; i++){
        double sum = 0;
        for(long j = 0; j < weights_size; j++)
            sum += weights[weights_size - j - 1] * input[i + j];
        r[i] = sum;
    }
    return r;
}


// ガウシアンフィルターの重み配列生成
// sd: 標準偏差
// n: カーネルの大きさ (n * 2 + 1)
double* gaussian_kernel(double sd, long n){
    double* w = (double*)malloc(sizeof(double) * (2 * n + 1));
    double sum = 0;
    for(long i = -n; i <= n; i++)
        sum += (w[i+n] = exp(-0.5 * i * i / (sd * sd)));
    for(long i = -n; i <= n; i++)
        w[i+n] /= sum;
    return w;
}

// ガウシアンフィルター
// v: 入力配列
// size: 入力配列の大きさ
// sd: 標準偏差
double* gaussian_filter1d(double* v, long size, double sd){
    long t = (long)(4.0 * sd + 0.5);
    double* tmp = gaussian_kernel(sd, t);
    double* weights = dreverse(tmp, 2 * t + 1);
    double* s = dreflect(v, size, t);
    double* r = correlate1d(s, 2 * t + size, weights, 2 * t + 1);
    free(tmp);
    free(s);
    free(weights);
    return r;
}
