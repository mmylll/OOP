##程序运行说明

1.按照正常的C++文件编译和运行`main.cpp`,`gameBoard.cpp`,`lattice.cpp`
编译:`g++ main.cpp gameBoard.cpp lattice.cpp -o main`

运行:`main.exe -t`(不需要设置终止方块，输入`main.exe`)


2.双人模式两个用户共用`wsad`来控制上下左右移动，可以通过`gameBoard.cpp`中的`setSuccessValue`来设置终止条件