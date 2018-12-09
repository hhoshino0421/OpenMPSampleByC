#include <iostream>

int main() {


    //変数定義
    int i, j, k;

    const int height = 100;
    const int width  = 100;

    double data1[height][width];
    double data2[height][width];
    double data3[height][width];

    //現在時刻取得
    time_t start_t = time(NULL);


    //データ準備
    for (i=0;i<height;i++) {

        for (j=0;j<width;j++) {

            data1[i][j] = rand() * 1000;

            data2[i][j] = rand() * 100;

            data3[i][j] = 0.0;

        }
    }




    //計算処理
    #pragma omp parallel        //ここが並列実行するブロック指定
    {

        for(i=0;i<height;i++) {

            for (j=0;j<width;j++) {

                for(k=0;k<height;k++) {

                    data3[i][j] = data1[i][k] * data2[k][j];

                }
            }
        }

    };

    //現在時刻取得
    time_t end_t = time(NULL);

    time_t proc_t = end_t - start_t;

    printf("%ld",proc_t);


    return 0;
}