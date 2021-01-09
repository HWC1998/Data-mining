# 组员信息
**洪伟程（组长）**
**苏聪颖**
## 分工：
### 实验一：
洪伟程负责完成**实验一中的数据清洗**及**第一题**和**第二题**

苏聪颖负责完成**第三题**和**第四题**
### 实验二：
洪伟程负责完成**第一题**、**第二题**和**第三题**

苏聪颖负责完成**第四题**和**第五题**
### 实验三：
洪伟程负责完成**PCA算法**

苏聪颖完成**K-Means算法**
# 作业题目：
## 实验一 多源数据集成、清洗与统计
## 实验二 数据统一与可视化
## 实验三 k-mean聚类算法
# 作业内容：
## 实验一 多源数据集成、清洗与统计
 **广州大学某班有同学100人，现要从两个数据源汇总学生数据。第一个数据源在数据库中，第二个数据源在txt文件中，两个数据源课程存在缺失、冗余和不一致性，请用C/C++/Java程序实现对两个数据源的一致性合并以及每个学生样本的数值量化。数据库表：ID (int), 姓名(string), 家乡(string:限定为Beijing / Guangzhou / Shenzhen / Shanghai), 性别（string:boy/girl）、身高（float:单位是cm)）、课程1成绩（float）、课程2成绩（float）、...、课程10成绩(float)、体能测试成绩（string：bad/general/good/excellent）；其中课程1-课程5为百分制，课程6-课程10为十分制。txt文件：ID(string：6位学号)，性别（string:male/female）、身高（string:单位是m)）、课程1成绩（string）、课程2成绩（string）、...、课程10成绩(string)、体能测试成绩（string：差/一般/良好/优秀）；其中课程1-课程5为百分制，课程6-课程10为十分制。两个数据源合并后读入内存，并统计:**

- **1. 学生中家乡在Beijing的所有课程的平均成绩。**
- **2. 学生中家乡在广州，课程1在80分以上，且课程9在9分以上的男同学的数量。(备注：该处做了修正，课程10数据为空，更改为课程9)**
- **3. 比较广州和上海两地女生的平均体能测试成绩，哪个地区的更强些？**
- **4. 学习成绩和体能测试成绩，两者的相关性是多少？（九门课的成绩分别与体能成绩计算相关性）**
## 实验二 数据统一与可视化
**基于实验一中清洗后的数据练习统计和视化操作，100个同学（样本），每个同学有11门课程的成绩（11维的向量）；那么构成了一个100x11的数据矩阵。以你擅长的语言，编程计算：**

- **1. 请以课程1成绩为x轴，体能成绩为y轴，画出散点图。**
- **2. 以5分为间隔，画出课程1的成绩直方图。**
- **3. 对每门成绩进行z-score归一化，得到归一化的数据矩阵。**
- **4. 计算出100x100的相关矩阵，并可视化出混淆矩阵。（为避免歧义，这里“协相关矩阵”进一步细化更正为100x100的相关矩阵，100为学生样本数目，视实际情况而定）**
- **5. 根据相关矩阵，找到距离每个样本最近的三个样本，得到100x3的矩阵（每一行为对应三个样本的ID）输出到txt文件中，以\t,\n间隔**

## 实验三 k-mean聚类算法
**用C++实现k-means聚类算法，**

- **1. 对实验二中的z-score归一化的成绩数据进行测试，观察聚类为2类，3类，4类，5类的结果，观察得出什么结论？**
- **2. 由老师给出测试数据，进行测试，并画出可视化出散点图，类中心，类半径，并分析聚为几类合适。**
 
**现有样例(x,y)数据对，**

**x	3.45	1.76	4.29	3.35	3.17	3.68	2.11	2.58	3.45	6.17	4.2	    5.8     5.47	5.97	6.24	6.89	5.38	5.13	7.26	6.32**

**y	7.08	7.24	9.55	6.65	6.41	5.99	4.08	7.1	    7.88	5.4	    6.46	3.87	2.21	3.62	3.06	2.41	2.32	2.73	4.19	3.62**

**找到聚类中心后，判断(2,6)是属于哪一类？**