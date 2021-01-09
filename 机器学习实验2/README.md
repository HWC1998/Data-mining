# 组员信息
**洪伟程（组长）**
**苏聪颖**
## 分工：
### 实验二：
洪伟程负责完成**第一题**、**第二题**和**第三题**

苏聪颖负责完成**第四题**和**第五题**

# 实验二 数据统一与可视化
**基于实验一中清洗后的数据练习统计和视化操作，100个同学（样本），每个同学有11门课程的成绩（11维的向量）；那么构成了一个100x11的数据矩阵。以你擅长的语言，编程计算：**

- **1. 请以课程1成绩为x轴，体能成绩为y轴，画出散点图。**
- **2. 以5分为间隔，画出课程1的成绩直方图。**
- **3. 对每门成绩进行z-score归一化，得到归一化的数据矩阵。**
- **4. 计算出100x100的相关矩阵，并可视化出混淆矩阵。（为避免歧义，这里“协相关矩阵”进一步细化更正为100x100的相关矩阵，100为学生样本数目，视实际情况而定）**
- **5. 根据相关矩阵，找到距离每个样本最近的三个样本，得到100x3的矩阵（每一行为对应三个样本的ID）输出到txt文件中，以\t,\n间隔**
# 说明
## 文件说明
以实验1得到的**result(washed).csv**来完成实验二中的题目,“exp2-x-y”表示实验二第x题y图
## 函数说明
**计算协方差**

		def corvar(i,j):
		#计算两个学生即两行的协方差
		#运用公式cov（x，y）=E[（x-E（x)*(y-E(y))]
    		stu1=[]   #存放第i行的成绩-其对应平均值的列表
    		stu2=[]   #存放第j行的成绩-其对应平均值的列表
    		for k in range(10):
        		stu1.append(data1_mat[i,k]-list_avg[i])
        		stu2.append(data1_mat[j,k]-list_avg[j])
    		sum=0 #stu1和stu2元素按照下标对应相乘后加起来
    		for k in range(10):
        		sum+=stu1[k]*stu2[k]
    		# print(stu1)
    		# print(stu2)
    		return sum/9.0    #返回协方差

## 调用库
    pandas as pd
    numpy as np
    matplotlib.pyplot as plt
    random
    seaborn as sns
    copy
## 涉及技术
| 技术| 说明|
| ----| ----|
| plt.rcParams['font.sans-serif']=['SimHei'] <br> plt.rcParams['axes.unicode_minus'] = False| 绘图时可以显示中文而不会出现乱码|
| np.set_printoptions(threshold=np.inf)| 数据全显示|
| random.randint(a,b)| 随机整数，范围从a到b-1|
| plt.scatter(C1_list,PE_list,c='red',marker='*')| 生成散点图 <br> 参数：c表示显示颜色，marker表示形状|
| plt.title()| 图名|
| plt.xlabel()| 横坐标轴名字|
| plt.ylabel()| 纵坐标轴名字|
| plt.savefig()| 导出图|
| plt.show()| 显示图|
| plt.hist(df.C1,edgecolor='black',bins=bins)| 生成直方图 <br> 参数：edgecolor表示直方图边缘颜色 <br> bins表示当bins=整数时表示显示柱子的数量，当为序列时表示每个柱子取值范围（前闭后开）|
| plt.grid(True, linestyle='--', alpha=0.5,axis='y')| 生成网格线 <br> 参数：True表示显示网格线 <br> linestyle表示网格线样式，axis表示以哪个轴做网格线|
| np.mat()| 生成矩阵|
| np.T| 矩阵转置|
| np.sqrt()| 算术平方根|
| np.zeros()| 生成全零矩阵|
| plt.figure(figsize=(20,20),dpi=80)| 参数：figsize表示图像宽高，dpi表示图像分辨率|
| sns.heatmap(cor_mat,vmin=-1,vmax=1,linewidths=0.08,xticklabels=False,cmap='coolwarm')| 热点图 <br> 参数：vmin和vmax表示数值最小和最大，linewidths表示每个颜色块间隔，xticklabels表示是否显示x坐标，cmap表示色块风格|
| copy.deepcopy()| 深拷贝|
| np.argsort()| 数值从小到大排序，返回的结果是下标构成列表|



# 难题与解决
由于第一题是散点图，如果不随机化体育成绩而是固定值，很多点会重合，这样图像效果不好，所以这里重新量化体育成绩（bad在60\~69随机，general在70\~79随机，good在80\~89随机，excellent在90\~99随机）后面题目也是一样，第二题和第三题都还好，但到了相关矩阵（第四题），先是网络上相关矩阵定义是列与列之间的相关性，按照网络上的定义规模应该是10x10，但要求100x100，那就只有一种情况就是学生与学生之间的相关性即行与行，第五题就是基于第四题相关矩阵来，距离最近的三个样本就是相关系数除了自身以外最大的三个，先是调用`np.argsort()`来相关矩阵每一行排个序，创建列表存放其最大三个的下标值，然后根据下标值在**result(washed).csv**找到对应ID，用另外一个列表存放，最后在导出txt文件

# 总结
实验2相对于实验1简单一点，可能这就是万事开头难
