#include <iostream>
#include <fstream>
#include<cmath>
using namespace std;

const int ROW = 20;
const int VOL = 2;
float Tddm[2][20];//读取老师给出测试数据。Ps:提前将老师给出测试数据写到2_data.txt文件
int k[5];//定义一个存储初始簇质心下标的数组
float kk[5][2];//定义一个存储簇质心的数组
float kk2[5][2];//定义一个存储初始簇质心的数组
float kdistance[5];//存储质心与点的判断距离
int Tddm2[20];//给样本划分簇的标记

void CreateK(int a)//从数据中随机选取数据作为质心
{
    for (int i = 0; i < a; i++)
    {
        k[i] = rand() % 20;
        for (int j = 0; j < i; j++)//判断前面的质心是否相同
        {
            while (Tddm[0][k[i]] == Tddm[0][k[j]])
            {
                k[i] = rand() % 20;
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
        for (int i = 0; i < 20; i++)
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
    float r[5] = { 0,0,0,0,0 };//定义r数组存储类半径,并初始化为0
    for (int i = 0; i < a; i++)//输出簇的质心和簇样本
    {
        cout << i << "簇的质心为：" << kk[i][0] << " " << kk[i][1] << endl;
        cout << i << "簇的样本为：" << endl;
        for (int k = 0; k < ROW; k++)
        {
            
            float temp = 0;
            if (Tddm2[k] == i)
            {
                cout << "(" << Tddm[0][k] << "," << Tddm[1][k] << ")" << " ";
                temp = sqrt((kk[i][0] - Tddm[0][k]) * (kk[i][0] - Tddm[0][k]) + (kk[i][1] - Tddm[1][k]) * (kk[i][1] - Tddm[1][k]));//计算点到簇质心的距离
                if (temp > r[i])//寻找点到簇质心的最大距离作为类中心
                {
                    r[i] = temp;
                }
                
            }
        }
        cout << endl;
        cout << "该类半径为：" << r[i]<<endl;
    }
    //for (int i = 0; i < a; i++)//输出质心和簇样本对于的簇，主要用于可视化
    //{
    //    cout << kk[i][0] << "," << kk[i][1] << endl;
    //}
    //for (int i = 0; i < ROW; i++)
    //{
    //    cout << Tddm[0][i] << "," << Tddm[1][i] << " " << Tddm2[i] << endl;
    //}
    //cout << endl << endl;
}
void classification(int a)//判断(2, 6)是属于哪一类
{
    for (int i = 0; i < a; i++)//数据距离质心的距离
    {
        kdistance[i] = (2 - kk[i][0]) * (2 - kk[i][0]) + (6 - kk[i][1]) * (6 - kk[i][1]);
    }
    int temp = 0;
    for (int i = 0; i < a; i++)
    {
        if (kdistance[temp] > kdistance[i])
        {
            temp = i;
        }
    }
    for (int i = 0; i < a; i++)//输出簇的质心
    {
        cout << i << "簇的质心为：" << kk[i][0] << " " << kk[i][1] << endl;
    }
    cout<<"(2, 6)是属于"<<temp<<"类"<<endl;     //划定簇
    cout << endl;
}
void K_Means()
{
    int a = 2;
    CreateK(a);//创建两个质心
    Cluster(a);//划分样本到簇
    cout << "聚类为：" << a << endl;
    classification(a);//判断(2,6)是属于哪一类
    cout << endl << endl;
    int b = 3;
    CreateK(b);//创建三个质心
    Cluster(b);//划分样本到簇
    cout << "聚类为：" << b << endl;
    classification(b); //判断(2, 6)是属于哪一类
    cout << endl << endl;
    int c = 4;
    CreateK(c);//创建四个质心
    Cluster(c);//划分样本到簇
    cout << "聚类为：" << c << endl;
    classification(c);//判断(2, 6)是属于哪一类
    cout << endl << endl;
    int d = 5;
    CreateK(d);//创建五个质心
    Cluster(d);//划分样本到簇
    cout << "聚类为：" << d << endl;
    classification(d);//判断(2, 6)是属于哪一类
    cout << endl << endl;
}

void Readdata_2()
{
    ifstream in2("2_data.txt");//打开文件
//读数据并存储初始样本数据到数组Tddm
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 20; ++j) {
            in2 >> Tddm[i][j];
        }
    }
    in2.close();//关闭文件
}

void second()//实验三第二题
{
    Readdata_2();//读取data_2.txt文件的数据
    K_Means();//K-means算法

}
int main()
{
    second();//实验三第二题
}