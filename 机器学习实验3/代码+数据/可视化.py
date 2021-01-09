import matplotlib.pyplot as plt
import pandas as pd
import csv
import numpy as np
plt.rcParams['font.sans-serif']=['SimHei']
plt.rcParams['axes.unicode_minus']=False
np.set_printoptions(threshold=np.inf)

pd.set_option('display.width', None)
pd.set_option('display.max_colwidth', 10000)
pd.set_option('display.max_columns',None)
pd.set_option('display.max_rows',None)

csvFile = open(r"C:\Users\16920\Desktop\2_5.csv",'w',newline='',encoding='utf-8')
writer = csv.writer(csvFile,dialect='excel')


f = open(r"C:\Users\16920\Desktop\2_5.txt",'r',encoding='GB2312')
for line in f.readlines():
    line=line.replace(',','\t')
    csvRow = line.split()
    writer.writerow(csvRow)

f.close()
csvFile.close()

df=pd.read_csv(r'D:\学习资料\机器学习\实验三 K-Means\k=3.csv',encoding='gbk',header=None)

d_type=3

fig=plt.figure(0)
color=['red','blue','green','orange','purple']
for i in range(d_type):
    x=df[0][i]
    y=df[1][i]
    plt.scatter(x,y,c=color[i],s=40,alpha=1,marker='*')
x=df[0][d_type:len(df)]
y=df[1][d_type:len(df)]
c=df[2][d_type:len(df)]
for i in range(d_type,len(df)):
    plt.scatter(x[i],y[i],c=color[int(c[i])],s=10,alpha=1,marker='.')
    print(x[i],y[i],int(c[i]))

plt.grid(True)
plt.legend(loc='best')
plt.show()