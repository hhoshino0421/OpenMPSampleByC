#include <iostream>
#include <stdlib.h>
#include <stdio.h>


int main() {

    printf("Start---------------------\n");

    //変数定義
    int i, j, k;

    const int height = 5000;
    const int width  = 5000;

    double *data1;
    double *data2;
    double *data3;

    data1 = (double *)malloc((sizeof(double)) * height * width);
    data2 = (double *)malloc((sizeof(double)) * height * width);
    data3 = (double *)malloc((sizeof(double)) * height * width);

    if (data1 == NULL) {
        printf("data1 malloc error\n");
        return -1;
    }

    if (data2 == NULL) {
        printf("data2 malloc error\n");
        return -1;
    }

    if (data3 == NULL) {
        printf("data3 malloc error\n");
        return -1;
    }


    //現在時刻取得
    time_t start_t = time(NULL);


    //データ準備
    for (i = 0; i < height; i++) {

        for (j = 0; j < width; j++) {

            *(data1 + sizeof(double) * i + sizeof(double) * j) = rand() * 1000;

            *(data2 + sizeof(double) * i + sizeof(double) * j) = rand() * 100;

            *(data3 + sizeof(double) * i + sizeof(double) * j) = 0.0;

        }
    }




    //計算処理
    #pragma omp parallel        //ここが並列実行するブロック指定
    {

        for(i = 0; i < height; i++) {

            for (j = 0; j < width; j++) {

                for(k = 0; k < height; k++) {

                    *(data3 + sizeof(double) * i + sizeof(double) * j) =
                            *(data1 + sizeof(double) * j + sizeof(double) * k) * *(data2 + sizeof(double) * k + sizeof(double) * j);


                }
            }
        }

    };


    //デバッグ出力
//    for(i = 0; i < height; i++) {
//        for (j = 0;j < width; j++) {
//            printf("%f\n", *(data3 + sizeof(double) * i + sizeof(double) * j) );
//        }
//    }

    //現在時刻取得
    time_t end_t = time(NULL);

    time_t proc_t = end_t - start_t;

    printf("\n");
    printf("Process Time:%ld\n",proc_t);
    printf("End---------------------\n");
    printf("\n");

    free(data1);
    free(data2);
    free(data3);


    return 0;
}