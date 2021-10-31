#include <iostream>
#include <stdlib.h>

using namespace std;

class Lattices{
private:
    int width;
    int value;
    int **lattices_map;
public:
    void setWidth(int initWidth){
        this->width = initWidth;
    }
    void setValue(int initValue){
        this->value = initValue;
    }
    void setLatticesMap(int x,int y){
        lattices_map[x][y] = value;
    }
    int getWidth() const{
        return this->width;
    }
    int getValue() const{
        return this->value;
    }
    int **getLatticesMap(){
        return lattices_map;
    }
    void initMap(){//先初始化数组
        if(width != 0){
            lattices_map = new int*[width];
            for(int i = 0;i < width;i++){
                lattices_map[i] = new int[width];
            }
            for(int i = 0;i < width;i++){
                for (int j = 0;j < width;j++){
                    lattices_map[i][j] = 0;
                }
            }
        }
    }
    void printLattices(){//细分行，粗分列
        cout<<width<<"*"<<width<<"\n";
        for(int i = 0;i < 2*width+1;i++){
            for(int j = 0;j < width;j++){
                if(i%2==0){
                    if(j == width-1){
                        cout<<"+ ----- +"<<"\n";
                    } else{
                        cout<<"+ ----- ";
                    }
                }else{
                    if(j == width-1){
                        if(lattices_map[(i-1)/2][j] != 0){
                            cout<<"|"<<"   "<<lattices_map[(i-1)/2][j]<<"   "<<"|\n";
                        } else{
                            cout<<"|"<<"   "<<" "<<"   "<<"|\n";
                        }

                    } else{
                        if(lattices_map[(i-1)/2][j] != 0){
                            cout<<"|"<<"   "<<lattices_map[(i-1)/2][j]<<"   ";
                        } else{
                            cout<<"|"<<"   "<<" "<<"   ";
                        }
                    }
                }

            }
        }
    }
    bool isFull(int x,int y){//判断某个方格是否填充
        bool result = true;
        if(lattices_map[x][y] == 0){
            result = false;
        }
        return result;
    };
    bool isFull_lattices(){//判断整个方格是否填满
        bool result = true;
        for(int i = 0;i < width;i++){
            for(int j = 0;j < width;j++){
                if(lattices_map[i][j] == 0){
                    result = false;
                }
            }
        }
        return result;
    }
};

int main() {
    Lattices lattices;
    lattices.setValue(2);
    lattices.setWidth(4);
    lattices.initMap();
    cout<<"初始化方格:\n";
    lattices.printLattices();
    for(; ;){
        if(lattices.isFull_lattices()){
            cout<<"退出游戏!\n";
            break;
        }
        char instruct;
        cout<<"请输入指令:\n";
        cin>>instruct;
        if(instruct == 'n'){

            for(;;){
                int x = (rand() % (lattices.getWidth()-0))+ 0;//[0,width)
                int y = (rand() % (lattices.getWidth()-0))+ 0;
                if(!lattices.isFull(x,y)) {
                    lattices.setLatticesMap(x, y);
                    lattices.printLattices();
                    break;
                } else{
                    continue;
                }
            }
        }else{
            break;
        }
    }
}
