### 综述
目录中包括数独程序的C++与Java两版本, 使用的算法,算法实现, 类库设计完全相同.

### C++編譯运行方法(Linux only, 且依赖gcc >= 4.7):
	$ make
	$ ./main ../test.txt ./output

### Java编译运行方法:
	$ javac *.java
	$ java Sudoku ../test.txt ./output

### 输入输出说明:
两程序对外行为完全一致.
程序将从第一个参数的文件名内读取一个数独矩阵, 所有答案将写入到第二参数的文件中, 用换行符分隔.
同时, 程序将在标准输出中输出程序计算时间(不包含IO时间), 及结果总数.

### 算法简述:
首先将数独问题转化为exact cover问题(http://en.wikipedia.org/wiki/Exact_cover)

然后利用Donald E. Knuth提出的Algorithm X求解(http://en.wikipedia.org/wiki/Knuth's_Algorithm_X)

	求解思路为,对于当前已选择的行,刪除行中所有1所在的列,及这些列中的1所在的行,再进行递归搜索.
	搜索失败败回溯,选择另外的行.

Algorithm X的实现利用了Knuth提出的Dancing Links算法(http://en.wikipedia.org/wiki/Dancing_Links).

	实现原理大致为,将所有“1”利用双向十字链表相连,快速的维护刪除及还原的操作,以保证递归回溯时的效率.


### 性能

使用``test_big.txt``做测试数据, 其内容为我随机输入, 此数独共有2681311个解.

测试环境cpu: 8 x i7-3770 3.4GHz

          |   C++      | Java
----------|------------|---------
 计算用时 |   4.5s     | 27.0s
 总用时   |   20.1s    | 51.8s
 内存峰值 |   936M     | 1.76G
 cpu峰值  |   99%      | 约600%

注1: Java版本直接运行会抛出``OutOfMemoryError``异常,设置堆空间最大值为3G(``-Xmx3G``)后能够运行.

注2: 计算用时不包含文件IO操作, 总用时中大部分为输出结果至``/dev/null``的用时.

注3: 类库设计中, 是由负责计算的类返回所有计算结果, 再一起输出. 因而会占大量内存.
