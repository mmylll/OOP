#include <iostream>

#define pi 3.1415926
using namespace std;
class Shape			//抽象类
{
public:
    virtual float area() const //计算面积
    {
        return 0.0;
    }
    virtual float volume() const//计算体积
    {
        return 0.0;
    }
    virtual void ShapeName() const =0;//纯虚函数 ——形状名

    virtual  ~Shape(){
        cout<<"Shape was deleted"<<endl;
    }
};


class Point: public Shape
{
public:
    Point(float =0,float =0);
    void setPoint(float,float);
    float getX()const;//获取x坐标
    float getY()const;//获取y坐标
    virtual void ShapeName()const
    {
        cout<<"Point:";
    }
    friend ostream &operator<< (ostream &output,const Point &point);

    virtual ~Point(){
        cout<<"Point was deleted"<<endl;
    }
protected://重载操作符<<，使得能够用cout<<来输出成员变量
    float x,y;//点的坐标x,y
};


//声明圈类
class Circle:public Point
{
public:
    Circle(float x=0,float y=0,float r=0);
    void setRadius(float);
    float GetRadius()const;
    virtual float area() const;
    virtual void ShapeName()const
    {
        cout<<"Circle:";
    }
    friend ostream &operator<< (ostream &output,const Circle &circle);
protected:
    float radius;//圈的半径
};

//声明圆柱类
class Cylinder:public Circle
{
public:
    Cylinder(float x=0,float y=0,float r=0,float h=0);
    void setHeight(float h);
    float getHeight();
    virtual float area()const;
    virtual float volume()const;
    virtual void ShapeName()const
    {
        cout<<"Cylinder:";
    }
    friend ostream &operator<< (ostream &output,const Cylinder &cylinder);

    virtual ~Cylinder(){
        cout<<"Cylinder was deleted"<<endl;
    }
protected:
    float height; //圆柱的高度
};


//Point类
Point::Point(float x, float y) {
    setPoint(x,y);
}

void Point::setPoint(float x1 , float y1) {
    this->x=x1;
    this->y=y1;
}

float Point::getX() const {
    return this->x;
}

float Point::getY() const {
    return this->y;
}

ostream &operator<<(ostream & output, const Point & point) {
    output << "x:" <<  point.x << "   y:" << point.y << "\n";
    return output;
}


//Circle类
Circle::Circle(float x1, float y1, float r1) {
    this->x=x1;
    this->y=y1;
    this->radius=r1;
}

void Circle::setRadius(float r) {
    this->radius=r;
}

float Circle::GetRadius() const {
    return this->radius;
}

float Circle::area() const {
    return pi*radius*radius;
}

ostream &operator<<(ostream & output , const Circle & circle) {
    output << "x:" << circle.x << "   y:" << circle.y << "   r:" << circle.radius << "   area:" << circle.area() << "\n";
    return output;
}


//Cylinder类
Cylinder::Cylinder(float x, float y, float r, float h) {
    this->x=x;
    this->y=y;
    this->radius=r;
    this->height=h;
}

void Cylinder::setHeight(float h) {
    this->height = h;
}

float Cylinder::getHeight() {
    return this->height;
}

float Cylinder::area() const {
    return (2*pi*radius*height)+2*(pi*radius*radius);
}
float Cylinder::volume() const {
    return area()*height;
}

ostream &operator<<(ostream & output, const Cylinder & cylinder) {
    output << "x:" << cylinder.x << "   y:" << cylinder.y << "   r:" << cylinder.radius << "   h:" << cylinder.height << "   area:" << cylinder.area() << "   volume:" << cylinder.volume() << "\n";
    return output;
}

int main()
{
    Point  point(1.1,2.2);
    Circle circle(3.3,4.4,5.5);
    Cylinder cylinder(6.6,7.7,8.8,9.9);
    //补全调用部分，静态关联，直接调用各个ShapeName，输出各个成员变量（最好直接用cout）
    point.ShapeName();
    cout << point << "\n";
    circle.ShapeName();
    cout << circle << "\n";
    cylinder.ShapeName();
    cout << cylinder << "\n";
    //补全调用部分，使用基类指针进行动态关联
    Shape *pt;
    pt = &point;
    pt->ShapeName();
    cout << "x:" <<  point.getX() << "   y:" << point.getY() << "\n";
    pt = &circle;
    pt->ShapeName();
    cout << "x:" << circle.getX() << "   y:" << circle.getY() << "   r:" << circle.GetRadius() << "   area:" << pt->area() << "\n";
    pt = &cylinder;
    pt->ShapeName();
    cout << "x:" << cylinder.getX() << "   y:" << cylinder.getY() << "   r:" << cylinder.GetRadius() << "   h:" << cylinder.getHeight() << "   area:" << pt->area() << "   volume:" << pt->volume() << "\n";
    return 0;
}