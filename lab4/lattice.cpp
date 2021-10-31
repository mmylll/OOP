//
// Created by 22332 on 2021/4/2.
//
#include <iostream>
#include <iomanip>
#include "lattice.h"

using namespace std;
void Lattice :: setValue(int mValue){
    this->value = mValue;
}
void Lattice :: setLeftMove(bool mLeftMove) {
    this->leftMove = mLeftMove;
}
void Lattice :: setRightMove(bool mRightMove) {
    this->rightMove = mRightMove;
}
void Lattice :: setUpMove(bool mUpMove) {
    this->upMove = mUpMove;
}
void Lattice :: setDownMove(bool mDownMove) {
    this->downMove = mDownMove;
}