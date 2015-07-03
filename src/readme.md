#Project3
手写数字的检测和识别

#####文件树
    src
    ├── CMakeLists.txt
    ├── readme.md
    ├── run.sh
    └── src
        ├── DigitDetection.cpp
        ├── DigitDetection.h
        ├── FileProcess.cpp
        ├── FileProcess.h
        ├── Message.cpp
        ├── Message.h
        ├── SVMProcessor.cpp
        ├── SVMProcessor.h
        ├── Tools.cpp
        ├── Tools.h
        └── main.cpp


#####依赖
	cmake version = 3.0
	g++ version >= 4.1
	opencv version >= 2.4.9
	
#####执行
首先将要处理的全部图片放在上一层的 `image` 文件夹下，然后在终端执行如下指令：

	$bash run.sh
	
#####SVM模型的测试
模型的训练已经完成，如果需要对 svm 模型进行测试，可以将 `main.cpp` 文件的第 16 行的：

	#define TEST false
	
改为

	#define TEST true
	
#####程序结果
在执行完程序后，在 `result` 文件夹下查看结果。结果的名字对应于原图的名字。程序会将检测与识别结果直接在图片显示。

#####Author

	E-mail：xiezhw3@163.com
	Github: www.github.com/xiezhw3