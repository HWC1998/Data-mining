#include <iostream>
#include <fstream>
#include<cmath>
using namespace std;

const int ROW = 20;
const int VOL = 2;
float Tddm[2][20];//��ȡ��ʦ�����������ݡ�Ps:��ǰ����ʦ������������д��2_data.txt�ļ�
int k[5];//����һ���洢��ʼ�������±������
float kk[5][2];//����һ���洢�����ĵ�����
float kk2[5][2];//����һ���洢��ʼ�����ĵ�����
float kdistance[5];//�洢���������жϾ���
int Tddm2[20];//���������ִصı��

void CreateK(int a)//�����������ѡȡ������Ϊ����
{
    for (int i = 0; i < a; i++)
    {
        k[i] = rand() % 20;
        for (int j = 0; j < i; j++)//�ж�ǰ��������Ƿ���ͬ
        {
            while (Tddm[0][k[i]] == Tddm[0][k[j]])
            {
                k[i] = rand() % 20;
            }
        }
    }
    for (int i = 0; i < a; i++)//��ȡ���Ķ�Ӧ���ݵ��±�
    {
        kk[i][0] = Tddm[0][k[i]];
        kk[i][1] = Tddm[1][k[i]];
    }
}

void Findmin(int index, int a)//�ж����ݾ������ĵľ��룬��Ϊ�����ƽ��Խ�󣬾���Ҳ��Խ��������ﲻ��ƽ��
{
    for (int i = 0; i < a; i++)//���ݾ������ĵľ���
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
    Tddm2[index] = temp;     //������
}
void update(int a)//���ĸ���
{
    int count = 1;
    int s = Tddm2[a];//��ȡ��
    for (int i = 0; i <= a; i++)
    {
        if (Tddm2[i] == s)//�ж����������ĸ���
        {
            kk[s][0] += Tddm[0][i];
            kk[s][1] += Tddm[1][i];
            count++;
        }
    }
    //����
    kk[s][0] = kk[s][0] / count;
    kk[s][1] = kk[s][1] / count;
}
void Cluster(int a)//������������
{
    cout << "����Ϊ" << a << "��ʱ��" << endl;
    int over = 0;//�������over,�ж������Ĵ��Ѿ����ֺ��ˣ��Ƿ���Ҫ�����䶯
    while (over == 0)
    {
        for (int i = 0; i < a; i++)
        {
            kk2[i][0] = kk[i][0];
            kk2[i][1] = kk[i][1];
        }
        for (int i = 0; i < 20; i++)
        {
            Findmin(i, a);//�ҳ�����������������
            update(i);//���ĸ���
        }
        over = 1;
        for (int i = 0; i < a; i++)
        {
            if ((kk2[i][0] != kk[i][0]) || (kk2[i][1] != kk[i][1]))//����ص����ķ�������
            {
                over = 0;
            }
        }
    }
    float r[5] = { 0,0,0,0,0 };//����r����洢��뾶,����ʼ��Ϊ0
    for (int i = 0; i < a; i++)//����ص����ĺʹ�����
    {
        cout << i << "�ص�����Ϊ��" << kk[i][0] << " " << kk[i][1] << endl;
        cout << i << "�ص�����Ϊ��" << endl;
        for (int k = 0; k < ROW; k++)
        {
            
            float temp = 0;
            if (Tddm2[k] == i)
            {
                cout << "(" << Tddm[0][k] << "," << Tddm[1][k] << ")" << " ";
                temp = sqrt((kk[i][0] - Tddm[0][k]) * (kk[i][0] - Tddm[0][k]) + (kk[i][1] - Tddm[1][k]) * (kk[i][1] - Tddm[1][k]));//����㵽�����ĵľ���
                if (temp > r[i])//Ѱ�ҵ㵽�����ĵ���������Ϊ������
                {
                    r[i] = temp;
                }
                
            }
        }
        cout << endl;
        cout << "����뾶Ϊ��" << r[i]<<endl;
    }
    //for (int i = 0; i < a; i++)//������ĺʹ��������ڵĴأ���Ҫ���ڿ��ӻ�
    //{
    //    cout << kk[i][0] << "," << kk[i][1] << endl;
    //}
    //for (int i = 0; i < ROW; i++)
    //{
    //    cout << Tddm[0][i] << "," << Tddm[1][i] << " " << Tddm2[i] << endl;
    //}
    //cout << endl << endl;
}
void classification(int a)//�ж�(2, 6)��������һ��
{
    for (int i = 0; i < a; i++)//���ݾ������ĵľ���
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
    for (int i = 0; i < a; i++)//����ص�����
    {
        cout << i << "�ص�����Ϊ��" << kk[i][0] << " " << kk[i][1] << endl;
    }
    cout<<"(2, 6)������"<<temp<<"��"<<endl;     //������
    cout << endl;
}
void K_Means()
{
    int a = 2;
    CreateK(a);//������������
    Cluster(a);//������������
    cout << "����Ϊ��" << a << endl;
    classification(a);//�ж�(2,6)��������һ��
    cout << endl << endl;
    int b = 3;
    CreateK(b);//������������
    Cluster(b);//������������
    cout << "����Ϊ��" << b << endl;
    classification(b); //�ж�(2, 6)��������һ��
    cout << endl << endl;
    int c = 4;
    CreateK(c);//�����ĸ�����
    Cluster(c);//������������
    cout << "����Ϊ��" << c << endl;
    classification(c);//�ж�(2, 6)��������һ��
    cout << endl << endl;
    int d = 5;
    CreateK(d);//�����������
    Cluster(d);//������������
    cout << "����Ϊ��" << d << endl;
    classification(d);//�ж�(2, 6)��������һ��
    cout << endl << endl;
}

void Readdata_2()
{
    ifstream in2("2_data.txt");//���ļ�
//�����ݲ��洢��ʼ�������ݵ�����Tddm
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 20; ++j) {
            in2 >> Tddm[i][j];
        }
    }
    in2.close();//�ر��ļ�
}

void second()//ʵ�����ڶ���
{
    Readdata_2();//��ȡdata_2.txt�ļ�������
    K_Means();//K-means�㷨

}
int main()
{
    second();//ʵ�����ڶ���
}