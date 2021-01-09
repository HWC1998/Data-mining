#include <iostream>
#include <fstream>
#include <Eigen/Dense>
#include <Eigen/Eigenvalues>
using namespace std;
using namespace Eigen;

const int ROW = 106;
const int VOL = 10;

float P[ROW][VOL];//存储初始样本数据的数组
float PT[VOL][ROW];//定义一个10行106列的转置数组
float C[10][10];//定义一个10*10的数组存放协方差矩阵
float cv1[10];//建立数组存放特征值
int cv2[2];//建立数组存放最大的特征值对应的下标
float fv1[10][10];//建立数组存放特征向量
float fv2[2][10];//建立数组存放最大的两个特征值对应的特征向量
float Tddm[2][ROW];//定义一个二维数据矩阵存放数据，Tddm为二维数据矩阵Two dimensional data matrix的缩写
int k[5];//定义一个存储初始簇质心下标的数组
float kk[5][2];//定义一个存储簇质心的数组
float kk2[5][2];//定义一个存储初始簇质心的数组
float kdistance[5];//存储质心与点的判断距离
int Tddm2[106];//给样本划分簇的标记

void Readdata_1()
{
    ifstream in("1_data.txt");//打开文件
//读数据并存储初始样本数据到数组P
    for (int i = 0; i < ROW; ++i) {
        for (int j = 0; j < VOL; ++j) {
            in >> P[i][j];
        }
    }
    in.close();//关闭文件

}

void SetPT()//将样本数组转置，并且用数组PT存储
{
    for (int i = 0; i < VOL; i++)
    {
        for (int j = 0; j < ROW; j++)
        {
            PT[i][j] = P[j][i];
        }
    }
}
void SetC()//计算协方差矩阵
{
    for (int i = 0; i < 10; i++)//将协方差矩阵初始化
    {
        for (int j = 0; j < 10; j++)
        {
            C[i][j] = 0;
        }
    }
    int i0 = 0;//协方差矩阵的行
    int j0 = 0;//协方差矩阵的列
    for (int a = 0; a < VOL; a++)//转置矩阵的行
    {

        for (int b = 0; b < VOL; b++)//未转置矩阵的列
        {
            for (int c = 0; c < ROW;)//转置矩阵的列
            {
                for (int d = 0; d < ROW;)//未转置矩阵的行
                {
                    C[i0][j0] += PT[a][c] * P[d][b];
                    c++;
                    d++;
                }
            }
            C[i0][j0] = C[i0][j0] / ROW;
            j0++;
        }
        if (j0 == 9)//重置协方差矩阵的列的位置，并且换行
        {
            j0 = 0;
            i0++;
        }

    }
    ofstream outfile0;
    string valuesFileName0("cm.txt"); //协方差矩阵所在的txt文件
    outfile0.open(valuesFileName0, ostream::trunc);  //以添加模式打开文件
    for (int i = 0; i < 10; i++)//输出协方差矩阵
    {
        for (int j = 0; j < 10; j++)
        {
            outfile0 << C[i][j] << " ";
        }
        outfile0 << endl;
    }
    outfile0.close();//关闭文件
    MatrixXd cm(10, 10);//创建一个协方差矩阵
    ifstream input("cm.txt");  //读取存有协方差矩阵数据的txt文件
    while (!input.eof())  //若未到文件结束一直循环，读取文本数据到mm
    {
        for (int a = 0; a < 10; a++)
            for (int b = 0; b < 10; b++)
            {
                input >> cm(a, b);
            }
    }
    EigenSolver<Matrix<double, 10, 10>> es(cm);//计算数据,
    ofstream outfile1;
    ofstream outfile2;
    string valuesFileName("values.txt"); //特征值所在的txt文件
    string vectorsFileName("vectors.txt"); //特征向量所在的txt文件
    outfile1.open(valuesFileName, ostream::trunc);  //以添加模式打开文件
    outfile2.open(vectorsFileName, ostream::trunc);  //以添加模式打开文件
    outfile1 << es.pseudoEigenvalueMatrix();
    outfile2 << es.pseudoEigenvectors();
    outfile1.close();  //关闭文件
    outfile2.close();  //关闭文件
}
void Findfv()//找出特征向量最大的两个值
{
    ifstream incv("values.txt");//打开文件
    //读特征值数据到数组cv1
    for (int i = 0; i < 10; ++i) {
        incv >> cv1[i];
        if (cv1[i] == 0)//如果读取的数据为0，则数组的下标不移动，继续读，直至不为0
        {
            i--;
        }
    }
    incv.close();//关闭文件

    for (int i = 0; i < 2; i++)//将特征值排序
    {
        int temp = 0;
        for (int j = 0; j < 10; j++)
        {
            if (cv1[j] < 0)//如果特征值小于0，则取相反数
            {
                cv1[j] = -cv1[j];
            }
            if (cv1[temp] < cv1[j])
            {
                temp = j;
            }
        }
        cv2[i] = temp;
        cv1[temp] = 0;//因为最大的两个值都是大于0的，所以将最大的值设为0，继续遍历
    }
    ifstream infv("vectors.txt");//打开文件
    //读特征向量数据到数组fv1[][]数组
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            infv >> fv1[i][j];
        }
    }
    infv.close();//关闭文件

    for (int i = 0; i < 2; i++)//读取特征值对应的特征向量
    {
        for (int j = 0; j < 10; j++)
        {
            fv2[i][j] = fv1[cv2[i]][j];
        }

    }


    for (int i = 0; i < 2; i++)//初始化二维数据矩阵为0
    {
        for (int j = 0; j < ROW; j++)
        {
            Tddm[i][j] = 0;
        }
    }
    int i1 = 0;//二维数据矩阵Tddm的行
    int j1 = 0;//二维数据矩阵Tddm的列
    for (int a = 0; a < 2; a++)//fv2矩阵的行
    {

        for (int b = 0; b < ROW; b++)//转置矩阵的列
        {
            for (int c = 0; c < 10;)//fv2矩阵的列
            {
                for (int d = 0; d < 10;)//转置矩阵的行
                {
                    Tddm[i1][j1] += fv2[a][c] * PT[d][b];
                    c++;
                    d++;
                }
            }
            j1++;
        }
        if (j1 == ROW - 1)
        {
            j1 = 0;
            i1++;
        }
    }
}

void CreateK(int a)//从数据中随机选取数据作为质心
{
    for (int i = 0; i < a; i++)
    {
        k[i] = rand() % 106;
        for (int j = 0; j < i; j++)//判断前面的质心是否相同
        {
            while (Tddm[0][k[i]] == Tddm[0][k[j]])
            {
                k[i] = rand() % 106;
            }
        }
    }
    for (int i = 0; i < a; i++)//存取质心对应数据的下标
    {
        kk[i][0] = Tddm[0][k[i]];
        kk[i][1] = Tddm[1][k[i]];
    }
}

void Findmin(int index, int a)//判断数据距离质心的距离，因为距离的平方越大，距离也就越大，因此这里不开平方
{
    for (int i = 0; i < a; i++)//数据距离质心的距离
    {
        kdistance[i] = (Tddm[0][index] - kk[i][0]) * (Tddm[0][index] - kk[i][0]) + (Tddm[1][index] - kk[i][1]) * (Tddm[1][index] - kk[i][1]);
    }
    int temp = 0;
    for (int i = 0; i < a; i++)
    {
        if (kdistance[temp] > kdistance[i])
        {
            temp = i;
        }
    }
    Tddm2[index] = temp;     //划定簇
}
void update(int a)//质心更新
{
    int count = 1;
    int s = Tddm2[a];//获取簇
    for (int i = 0; i <= a; i++)
    {
        if (Tddm2[i] == s)//判断样本属于哪个簇
        {
            kk[s][0] += Tddm[0][i];
            kk[s][1] += Tddm[1][i];
            count++;
        }
    }
    //更新
    kk[s][0] = kk[s][0] / count;
    kk[s][1] = kk[s][1] / count;
}
void Cluster(int a)//划分样本到簇
{
    cout << "聚类为" << a << "类时：" << endl;
    int over = 0;//定义变量over,判断样本的簇已经划分好了，是否还需要发生变动
    while (over == 0)
    {
        for (int i = 0; i < a; i++)
        {
            kk2[i][0] = kk[i][0];
            kk2[i][1] = kk[i][1];
        }
        for (int i = 0; i < 106; i++)
        {
            Findmin(i, a);//找出距离离点最近的质心
            update(i);//质心更新
        }
        over = 1;
        for (int i = 0; i < a; i++)
        {
            if ((kk2[i][0] != kk[i][0]) || (kk2[i][1] != kk[i][1]))//如果簇的质心发生更改
            {
                over = 0;
            }
        }
    }
    for (int i = 0; i < a; i++)//输出簇的质心和簇样本
    {
        cout << i << "簇的质心为：" << kk[i][0] << " " << kk[i][1] << endl;
        cout << i << "簇的样本为：" << endl;
        for (int k = 0; k < ROW; k++)
        {
            if (Tddm2[k] == i)
            {
                cout << "(" << Tddm[0][k] << "," << Tddm[1][k] << ")" << " ";
            }
        }
        cout << endl << endl;
    }
    /*for (int i = 0; i < a; i++)//输出质心和簇样本对于的簇，主要用于可视化
    {
        cout << kk[i][0] << "," << kk[i][1] << endl;
    }
    for (int i = 0; i < ROW; i++)
    {
        cout << Tddm[0][i] << "," << Tddm[1][i] << " " << Tddm2[i] << endl;
    }
    cout << endl << endl;*/

}
void K_Means()
{
    int a = 2;
    CreateK(a);//创建两个质心
    Cluster(a);//划分样本到簇
    cout << endl << endl;
    int b = 3;
    CreateK(b);//创建三个质心
    Cluster(b);//划分样本到簇
    cout << endl << endl;
    int c = 4;
    CreateK(c);//创建四个质心
    Cluster(c);//划分样本到簇
    cout << endl << endl;
    int d = 5;
    CreateK(d);//创建五个质心
    Cluster(d);//划分样本到簇
    cout << endl << endl;
}
void first()//实验三第一题
{
    Readdata_1();//读取data_1.txt文件的数据
    SetPT();//设置转置矩阵
    SetC();//计算协方差矩阵
    Findfv(); //找出特征向量最大的两个值
    K_Means();//K-means算法
}

int main() {
    first();//实验三第一题
}