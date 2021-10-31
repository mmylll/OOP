//
// Created by 22332 on 2021/3/16.
//

#ifndef LAB2_LATTICES_H
#define LAB2_LATTICES_H
class Lattices{
private:
    int width;
    int value;
    int **lattices_map;
    int initNums;
    int success_value;
public:
    void setWidth(int initWidth);

    void setValue(int initValue);

    void setLatticesMap(int x,int y);

    void setInitNums(int nums);

    void setSuccessValue(int success_value);

    int getWidth() const;

    int getValue() const;

    int **getLatticesMap();

    int *getRandoms();

    int getSuccessValue();

    void initMap();//先初始化数组

    void printLattices();//细分行，粗分列

    void addRandom(int value,int nums);//添加随机数,随机数个数

    bool isFull(int x,int y);

    bool isFull_lattices();//判断整个方格是否填满

    void key_w();

    void key_s();

    void key_a();

    void key_d();

    bool check_game_over();

    bool check_game_success();

    int logical_move(int operate,Lattices lattices);
};
#endif //LAB2_LATTICES_H
