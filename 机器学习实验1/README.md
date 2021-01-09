# 组员信息
**洪伟程（组长）**
**苏聪颖**
## 分工：
### 实验一：
洪伟程负责完成**实验一中的数据清洗**及**第一题**和**第二题**

苏聪颖负责完成**第三题**和**第四题**

# 实验一 多源数据集成、清洗与统计
 **广州大学某班有同学100人，现要从两个数据源汇总学生数据。第一个数据源在数据库中，第二个数据源在txt文件中，两个数据源课程存在缺失、冗余和不一致性，请用C/C++/Java程序实现对两个数据源的一致性合并以及每个学生样本的数值量化。数据库表：ID (int), 姓名(string), 家乡(string:限定为Beijing / Guangzhou / Shenzhen / Shanghai), 性别（string:boy/girl）、身高（float:单位是cm)）、课程1成绩（float）、课程2成绩（float）、...、课程10成绩(float)、体能测试成绩（string：bad/general/good/excellent）；其中课程1-课程5为百分制，课程6-课程10为十分制。txt文件：ID(string：6位学号)，性别（string:male/female）、身高（string:单位是m)）、课程1成绩（string）、课程2成绩（string）、...、课程10成绩(string)、体能测试成绩（string：差/一般/良好/优秀）；其中课程1-课程5为百分制，课程6-课程10为十分制。两个数据源合并后读入内存，并统计:**

- **1. 学生中家乡在Beijing的所有课程的平均成绩。**
- **2. 学生中家乡在广州，课程1在80分以上，且课程9在9分以上的男同学的数量。(备注：该处做了修正，课程10数据为空，更改为课程9)**
- **3. 比较广州和上海两地女生的平均体能测试成绩，哪个地区的更强些？**
- **4. 学习成绩和体能测试成绩，两者的相关性是多少？（九门课的成绩分别与体能成绩计算相关性）**

# 说明
## 文件说明
在代码+数据文件夹中**data1.csv**为数据源1，**data2.csv**为数据源2，**result.csv**为直接将两个数据源合并的结果（未数清洗），运行结果截图或运行结果文件文件夹中**result(washed).csv**为数据清洗完后导出的结果，且之后实验题目数据均采用**result(washed).csv**，运行结果截图或运行结果文件文件夹中“**exp1-x**”表示实验1第x题截图

## 函数说明
**填充缺失值**

    def fillackofvalue(xx,df):	# #发现空值从另外一个数据源找到对应值并填充
    	xx_list=df[df[xx].isnull()].index.tolist()
    	for i in range(len(xx_list)):
    	for j in range(len(df)):
    	if df.Name[j] == df.Name[xx_list[i]] and j != xx_list:
    	df.loc[df.index[xx_list[i]], xx] = df.loc[df.index[j], xx]
**填充剩下无对照的缺失值**

    def fillrest(df):
    #填充剩下没有对照的数据，以平均值填充
    	df.loc[df.C3.isnull(), 'C3'] = 80
    	df.loc[df.C4.isnull(), 'C4'] = int(df.C4.mean() + 0.5)
    	df.loc[df.C5.isnull(), 'C5'] = int(df.C5.mean() + 0.5)
    	df.loc[df.Constitution.isnull(), 'Constitution'] = "general"
**计算所有北京学生平均成绩，除了体育成绩**

	def courseaverage(xx):
	#用来计算北京学生的平均成绩，不包括体育成绩
	#xx代表传入的列名
    	xx_list=df.loc[df["City"]=="Beijing",xx].tolist() #先用xx_list列表存放传入数据
    	sum=0 #sum用来计算列表中所有数字总和
    	for i in xx_list:
        	sum+=i
    	average=sum/len(xx_list)  #average用来存平均成绩
    	print(xx+"平均成绩："+str(average))
**计算所有成绩平均值**

    def averagecourse(x,num):#计算成绩平均数
    	x_sum = 0	#用来存放成绩总和
    	#由于体育成绩是字符串不是数，所以加判断来分辨要计算的是体育成绩还是学科成绩
    	if x!="Constitution":
    		for i in range(num):
    		x_sum+=df[x][i]
    	else:
    	#体育成绩量化
    		for i in range(len(df)):
    			if df[x][i] == "bad":
    				x_sum += 60
    			elif df[x][i] == "general":
    				x_sum += 75
    			elif df[x][i] == "good":
    				x_sum += 85
    			elif df[x][i] == "excellent":
    				x_sum += 95
    	return x_sum / num	#返回成绩平均值
**计算协方差**

    def covariance(x,y,num,a,b):#计算协方差
    #运用公式cov（x，y）=E(xy）-E（x）E（y)，a表示学科成绩，b表示体育成绩，num表示学生数量
    #
    	xy_sum = 0	#xy表示学习成绩和体育成绩相乘，xy_sum表示总和
    	for i in range(num):
    		if df[y][i] == "bad":
    			xy_sum += 60 * df[x][i]
    		elif df[y][i] == "general":
    			xy_sum += 75 * df[x][i]
    		elif df[y][i] == "good":
    			xy_sum += 85 * df[x][i]
    		elif df[y][i] == "excellent":
    			xy_sum += 95 * df[x][i]
    	xy_average=xy_sum/num #E（xy）
		return xy_average-a*b #返回协方差
**计算方差**

	def variance(x,num,average):#计算方差
    	x_sum=0   #x_sum表示学科成绩-学科成绩平均值（average）然后平方，最后所有项求和
    	if x!="Constitution":
        	for i in range(num):
            	x_sum += (df[x][i] - average) **2
    	else:
        	for i in range(num):
            	if df[x][i] == "bad":
                	x_sum += (60 - average) **2
            	elif df[x][i] == "general":
                	x_sum += (75 - average) **2
            	elif df[x][i] == "good":
                	x_sum += (85 - average) **2
            	elif df[x][i] == "excellent":
                	x_sum += (95 - average) **2
    	return x_sum / num    #返回方差
**计算相关系数**

	def correlation(x,y):#计算相关系数
	#运用公式r=cov（x，y）/（std（x）*std（y））
    	num=len(df)   #学生数量
    	x_average=averagecourse(x,num)
    	y_average=averagecourse(y,num)
    	x_var=variance(x,num,x_average)   #学科成绩方差
    	y_var=variance(y,num,y_average)   #体育成绩方差
    	Var=np.sqrt(x_var*y_var)  #学科成绩和体育成绩方差相乘后开方
    	covar=covariance(x,y,num,x_average,y_average) #协方差
    	return covar/Var  #返回相关系数
## 调用库
    glob
    os
    pandas as pd
    numpy as np
## 涉及的技术
| 技术| 说明|
| ---| ---|
| pd.set_option('display.max_columns', 1000) <br> pd.set_option('display.width', 1000) <br> pd.set_option('display.max_colwidth', 1000) <br> pd.set_option("display.max_columns",None) <br> pd.set_option("display.max_rows",None)| 将pandas读的文件数据全部显示，而不是部分显示|
| pd.read_csv(filepath)| 读csv文件 <br> 参数：filepath文件地址|
| pd.to_csv(outputfile, index=False)| 导出csv文件 <br> 参数：outputfile文件存放地址 <br> index索引值是否导出到文件，false表示否|
| pd.loc[pd.index[i],'ID']| pd.loc[]用来定位第几行第几列数据，pd.index[i]用来找第i+1行数据|
| pd.drop_duplicates(subset=['ID'],keep='last',inplace=True)| 删除重复行 <br> subset根据某一列重复来删除重复值 <br> keep重复是删除哪一个，默认删除第一个，last删除后一个 <br> inplace是否在生成副本做修改，true不生成|
| pd.sort_values(by='ID',ascending=True,inplace=True)| 根据值大小排序 <br> by按照某一列值排序 <br> ascending序列方向，true表示升序 <br> inplace是否在生成副本做修改，true不生成|

# 难题与解决

## 数据合并
用\*.csv来读取文件夹中所有的csv文件即**data1.csv**和**data2.csv**，然后调用glob中的`glob`来存这两个数据源，同时这个`glob`可以去除数据源2中的表头即保留数据源1的表头
## 数据填充
调用自定义的函数`fillackofvalue(xx,df)`来进行填充函数，但发现还是有部分数据的空缺值无法填充，所以调用另外一个自定义函数`fillrest(df)`来进行剩下未填充数据
## 数据标准化
首先ID为非202000打头，类型由字符串转化为int类型然后就加上202000来统一标准；身高如果是小数即单位是m的就将其数值乘100来将所有数据统一身高单位为cm；性别就是将所有boy和girl改为male和female
## 数据去重
先调用`pd.drop_duplicates()`来进行所有重复数据删除操作，然后观察数据发现还是有些极度相似的数据比如说有的人所有数据都一样就性别不一样，很明显是同一个人，所以在调用`pd.drop_duplicates()`设立其变量`subset='ID'`来进行去重，最后调用`pd.sort_values()`来以ID大小排个升序，然后重新设立下所有数据的索引值
## 体育成绩量化
量化体育成绩（bad=60，general=75，good=85，excellent=95）


# 总结
一开始完全不懂这个实验该怎么做，通过问朋友，他发来一个[数据清洗视频](https://www.bilibili.com/video/BV1qb411M7ew?from=search&seid=8917071004612287550)，慢慢了解了数据清洗到底是怎么回事，然后开始不断查资料问这位朋友如何，最后终于花了两天半终于完成实验1，就像下面这句名言
> 世上无难事，只怕有心人
