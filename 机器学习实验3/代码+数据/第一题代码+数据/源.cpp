#include <iostream>
#include <fstream>
#include <Eigen/Dense>
#include <Eigen/Eigenvalues>
using namespace std;
using namespace Eigen;

const int ROW = 106;
const int VOL = 10;

float P[ROW][VOL];//�洢��ʼ�������ݵ�����
float PT[VOL][ROW];//����һ��10��106�е�ת������
float C[10][10];//����һ��10*10��������Э�������
float cv1[10];//��������������ֵ
int cv2[2];//������������������ֵ��Ӧ���±�
float fv1[10][10];//������������������
float fv2[2][10];//����������������������ֵ��Ӧ����������
float Tddm[2][ROW];//����һ����ά���ݾ��������ݣ�TddmΪ��ά���ݾ���Two dimensional data matrix����д
int k[5];//����һ���洢��ʼ�������±������
float kk[5][2];//����һ���洢�����ĵ�����
float kk2[5][2];//����һ���洢��ʼ�����ĵ�����
float kdistance[5];//�洢���������жϾ���
int Tddm2[106];//���������ִصı��

void Readdata_1()
{
    ifstream in("1_data.txt");//���ļ�
//�����ݲ��洢��ʼ�������ݵ�����P
    for (int i = 0; i < ROW; ++i) {
        for (int j = 0; j < VOL; ++j) {
            in >> P[i][j];
        }
    }
    in.close();//�ر��ļ�

}

void SetPT()//����������ת�ã�����������PT�洢
{
    for (int i = 0; i < VOL; i++)
    {
        for (int j = 0; j < ROW; j++)
        {
            PT[i][j] = P[j][i];
        }
    }
}
void SetC()//����Э�������
{
    for (int i = 0; i < 10; i++)//��Э��������ʼ��
    {
        for (int j = 0; j < 10; j++)
        {
            C[i][j] = 0;
        }
    }
    int i0 = 0;//Э����������
    int j0 = 0;//Э����������
    for (int a = 0; a < VOL; a++)//ת�þ������
    {

        for (int b = 0; b < VOL; b++)//δת�þ������
        {
            for (int c = 0; c < ROW;)//ת�þ������
            {
                for (int d = 0; d < ROW;)//δת�þ������
                {
                    C[i0][j0] += PT[a][c] * P[d][b];
                    c++;
                    d++;
                }
            }
            C[i0][j0] = C[i0][j0] / ROW;
            j0++;
        }
        if (j0 == 9)//����Э���������е�λ�ã����һ���
        {
            j0 = 0;
            i0++;
        }

    }
    ofstream outfile0;
    string valuesFileName0("cm.txt"); //Э����������ڵ�txt�ļ�
    outfile0.open(valuesFileName0, ostream::trunc);  //�����ģʽ���ļ�
    for (int i = 0; i < 10; i++)//���Э�������
    {
        for (int j = 0; j < 10; j++)
        {
            outfile0 << C[i][j] << " ";
        }
        outfile0 << endl;
    }
    outfile0.close();//�ر��ļ�
    MatrixXd cm(10, 10);//����һ��Э�������
    ifstream input("cm.txt");  //��ȡ����Э����������ݵ�txt�ļ�
    while (!input.eof())  //��δ���ļ�����һֱѭ������ȡ�ı����ݵ�mm
    {
        for (int a = 0; a < 10; a++)
            for (int b = 0; b < 10; b++)
            {
                input >> cm(a, b);
            }
    }
    EigenSolver<Matrix<double, 10, 10>> es(cm);//��������,
    ofstream outfile1;
    ofstream outfile2;
    string valuesFileName("values.txt"); //����ֵ���ڵ�txt�ļ�
    string vectorsFileName("vectors.txt"); //�����������ڵ�txt�ļ�
    outfile1.open(valuesFileName, ostream::trunc);  //�����ģʽ���ļ�
    outfile2.open(vectorsFileName, ostream::trunc);  //�����ģʽ���ļ�
    outfile1 << es.pseudoEigenvalueMatrix();
    outfile2 << es.pseudoEigenvectors();
    outfile1.close();  //�ر��ļ�
    outfile2.close();  //�ر��ļ�
}
void Findfv()//�ҳ�����������������ֵ
{
    ifstream incv("values.txt");//���ļ�
    //������ֵ���ݵ�����cv1
    for (int i = 0; i < 10; ++i) {
        incv >> cv1[i];
        if (cv1[i] == 0)//�����ȡ������Ϊ0����������±겻�ƶ�����������ֱ����Ϊ0
        {
            i--;
        }
    }
    incv.close();//�ر��ļ�

    for (int i = 0; i < 2; i++)//������ֵ����
    {
        int temp = 0;
        for (int j = 0; j < 10; j++)
        {
            if (cv1[j] < 0)//�������ֵС��0����ȡ�෴��
            {
                cv1[j] = -cv1[j];
            }
            if (cv1[temp] < cv1[j])
            {
                temp = j;
            }
        }
        cv2[i] = temp;
        cv1[temp] = 0;//��Ϊ��������ֵ���Ǵ���0�ģ����Խ�����ֵ��Ϊ0����������
    }
    ifstream infv("vectors.txt");//���ļ�
    //�������������ݵ�����fv1[][]����
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            infv >> fv1[i][j];
        }
    }
    infv.close();//�ر��ļ�

    for (int i = 0; i < 2; i++)//��ȡ����ֵ��Ӧ����������
    {
        for (int j = 0; j < 10; j++)
        {
            fv2[i][j] = fv1[cv2[i]][j];
        }

    }


    for (int i = 0; i < 2; i++)//��ʼ����ά���ݾ���Ϊ0
    {
        for (int j = 0; j < ROW; j++)
        {
            Tddm[i][j] = 0;
        }
    }
    int i1 = 0;//��ά���ݾ���Tddm����
    int j1 = 0;//��ά���ݾ���Tddm����
    for (int a = 0; a < 2; a++)//fv2�������
    {

        for (int b = 0; b < ROW; b++)//ת�þ������
        {
            for (int c = 0; c < 10;)//fv2�������
            {
                for (int d = 0; d < 10;)//ת�þ������
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

void CreateK(int a)//�����������ѡȡ������Ϊ����
{
    for (int i = 0; i < a; i++)
    {
        k[i] = rand() % 106;
        for (int j = 0; j < i; j++)//�ж�ǰ��������Ƿ���ͬ
        {
            while (Tddm[0][k[i]] == Tddm[0][k[j]])
            {
                k[i] = rand() % 106;
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
        for (int i = 0; i < 106; i++)
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
    for (int i = 0; i < a; i++)//����ص����ĺʹ�����
    {
        cout << i << "�ص�����Ϊ��" << kk[i][0] << " " << kk[i][1] << endl;
        cout << i << "�ص�����Ϊ��" << endl;
        for (int k = 0; k < ROW; k++)
        {
            if (Tddm2[k] == i)
            {
                cout << "(" << Tddm[0][k] << "," << Tddm[1][k] << ")" << " ";
            }
        }
        cout << endl << endl;
    }
    /*for (int i = 0; i < a; i++)//������ĺʹ��������ڵĴأ���Ҫ���ڿ��ӻ�
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
    CreateK(a);//������������
    Cluster(a);//������������
    cout << endl << endl;
    int b = 3;
    CreateK(b);//������������
    Cluster(b);//������������
    cout << endl << endl;
    int c = 4;
    CreateK(c);//�����ĸ�����
    Cluster(c);//������������
    cout << endl << endl;
    int d = 5;
    CreateK(d);//�����������
    Cluster(d);//������������
    cout << endl << endl;
}
void first()//ʵ������һ��
{
    Readdata_1();//��ȡdata_1.txt�ļ�������
    SetPT();//����ת�þ���
    SetC();//����Э�������
    Findfv(); //�ҳ�����������������ֵ
    K_Means();//K-means�㷨
}

int main() {
    first();//ʵ������һ��
}