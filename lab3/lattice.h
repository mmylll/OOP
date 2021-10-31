//
// Created by 22332 on 2021/4/2.
//

#ifndef LAB3_LATTICE_H
#define LAB3_LATTICE_H
class Lattice{
private:
    int value;
    bool leftMove;
    bool rightMove;
    bool upMove;
    bool downMove;

public:
    void setValue(int mValue);

    void setLeftMove(bool mLeftMove);

    void setRightMove(bool mRightMove);

    void setUpMove(bool mUpMove);

    void setDownMove(bool mDownMove);

    int getValue();

    bool getLeftMove();

    bool getRightMove();

    bool getUpMove();

    bool getDownMove();
};


#endif //LAB3_LATTICE_H
