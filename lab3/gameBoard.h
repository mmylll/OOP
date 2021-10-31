//
// Created by 22332 on 2021/4/2.
//

#ifndef LAB3_GAMEBOARD_H
#define LAB3_GAMEBOARD_H

#include "lattice.h"
#include <stdlib.h>

class GameBoard{
private:
    int scale;
    int value;
    int **lattices_map;
    int initNums;//初始化随机数数量
    int success_value;
    int roundFraction;//回合分数
    int fraction;//总分
    std::string username;
    int* p_fraction = &fraction;
    //Lattice **lattices;

public:
    void setScale(int mScale);

    void setValue(int mValue);

    void setLatticesMap(int x,int y);

    void setInitNums(int nums);

    void setSuccessValue(int mSuccess_value);

    void setRoundFraction(int mRoundFraction);

    void setFraction(int mFraction);

    void setUserName(std::string mUsername);

    int getScale() const;

    int getValue() const;

    int **getLatticesMap();

    int *getRandoms();

    int getSuccessValue();

    int getRoundFraction();

    int getFraction();

    std::string getUsername();

    void initMap();//先初始化数组

    void printLattices();//细分行，粗分列

    void addRandom(int mValue,int mNums);//添加随机数,随机数个数

    bool isFull(int x,int y);

    bool isFull_lattices();//判断整个方格是否填满

    void key_w();

    void key_s();

    void key_a();

    void key_d();

    bool check_game_over();

    bool check_game_success();

    int logical_move(int operate,GameBoard gameBoard);
};
#endif //LAB3_GAMEBOARD_H