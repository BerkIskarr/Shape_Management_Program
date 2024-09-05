#include <iostream>
#include <cmath>
#include <string> // to be able to use string
#include <utility> // to be able to make pair
#include <cstddef> // for memory management
#include <vector> // to be able to use vector
using namespace std;
// class for storing and accessing the positions
class Coordinates {
public:
    pair<int, int> coords;

    Coordinates(pair<int, int> input_coordinate) : coords(input_coordinate) {}

    int getX() {
        return coords.first;
    }

    int getY() {
        return coords.second;
    }
    // to find the distance between vertexes
    double distance(Coordinates& p) {
        int xDif = p.getX() - coords.first;
        int yDif = p.getY() - coords.second;
        return sqrt(xDif * xDif + yDif * yDif);
    }
    // moves the coordinates
    void translate(int dx, int dy) {
        coords.first += dx;
        coords.second += dy;
    }
    // for scaling the coordinates
    void scale(int factor, bool sign) {
        if (sign) {
            coords.first *= factor;
            coords.second *= factor;
        } else {
            coords.first /= factor;
            coords.second /= factor;
        }
    }
    // for displaying the coordinates of the position
    string display() {
        return "(X = " + to_string(coords.first) + ", Y = " + to_string(coords.second)+")";
    }
};
// parent class of all the shapes
class Shape {
public:
    Coordinates position;
    int sides;

    Shape(int noOfSides, const Coordinates& coord) : sides(noOfSides), position(coord) {}
    // to get the center coordinates
    Coordinates getCoordinates() {
        return position;
    }
    // to get the side number
    int getSides() {
        return sides;
    }
    // updating the coordinates
    void setCoordinates(const Coordinates& newCoord) {
        position = newCoord;
    }

    virtual void translate(int dx, int dy) {}
    virtual void scale(int factor, bool sign) {}
    // to get the area to override in all shapes
    virtual double getArea() { return 0; }
    // to get the area to override in all shapes
    virtual double getPerimeter() { return 0; }
    virtual string display() { return ""; }
    virtual ~Shape() {}
};
// all the functions for square
class Square : public Shape {
public:
    double side;
    // gets side length and cord for center
    Square(double number, Coordinates& position) : Shape(4, position), side(number) {}
    // Overrides the virtual area functions in the Shape class
    double getArea(){
        return pow(side, 2);
    }
    // Overrides the virtual perimeter functions in the Shape class
    double getPerimeter(){
        return 4*side;
    }
    // Overrides the virtual translate functions in the Shape class
    void translate(int dx, int dy){
        position.translate(dx, dy);
    }
    // Overrides the virtual scale functions in the Shape class
    void scale(int factor, bool sign){
//        position.scale(factor, sign);
        if (sign) {
            side *= factor;
        } else {
            side /= factor;
        }
    }
    // Overrides the virtual functions in the Shape class
    string display(){
        return "The shape: Square\nThe area: "+to_string(int(getArea()))+"\nThe perimeter: "+to_string(int(getPerimeter()))+"\nThe length of the side: "+to_string(int(side))+"\nThe coordinate of the center: ("+to_string(position.getX())+","+to_string(position.getY())+")";
    }
};
// all the functions for circle
class Circle : public Shape {
public:
    double radius;
    // gets radius length and cord for center
    Circle(double number, const Coordinates& position) : Shape(0, position), radius(number) {}
    // Overrides the virtual area functions in the Shape class
    double getArea(){
        return round(M_PI* pow(radius, 2)*100)/100;
    }
    // Overrides the virtual perimeter functions in the Shape class 2pir
    double getPerimeter(){
        return round(2*M_PI*radius);
    }
    // Overrides the virtual translate functions in the Shape class
    void translate(int dx, int dy){
        position.translate(dx, dy);
    }
    // Overrides the virtual scale functions in the Shape class
    void scale(int factor, bool sign){
//        position.scale(factor, sign);
        if (sign) {
            radius *= factor;
            
        } else {
            radius /= factor;
        }
    }
    // Overrides the virtual display functions in the Shape class
    string display(){
        return "The shape: Circle\nThe area: "+to_string(int(getArea()))+"\nThe perimeter: "+to_string(int(getPerimeter()))+"\nThe radius: "+to_string(int(radius))+"\nThe coordinate of the center: "+position.display();
    }
};

// all the functions for rectangle
class Rectangle : public Shape {
 
public:
    double width, length;
    // gets width, length and cord for center
    Rectangle(double w, double l ,Coordinates& position ): Shape(4,position), width(w), length(l){}
        
    // Overrides the virtual area functions in the Shape class
    double getArea(){
        return round(width*length);
    }
    // Overrides the virtual perimeter functions in the Shape class
    double getPerimeter(){
        return round(2*(width+length));
    }
    // Overrides the virtual translate functions in the Shape class
    void translate(int dx, int dy){
        position.translate(dx, dy);
    }
    // Overrides the virtual scale functions in the Shape class
    void scale(int factor, bool sign){
//        position.scale(factor, sign);
        if (sign) {
            width *= factor;
            length *= factor;
        } else {
            width /= factor;
            length /= factor;
        }
    }
    // Overrides the virtual display functions in the Shape class
    string display(){
        return "The shape: Rectangle\nThe area: "+to_string(int(getArea()))+"\nThe perimeter: "+to_string(int(getPerimeter()))+"\nThe width: "+to_string(int(width))+"\nThe length: "+to_string(int(length))+"\nThe coordinate of the center: "+position.display();
    }
};
// to find the center coordinate of the triangle
pair<int, int> findCenter(int x1, int y1, int x2, int y2, int x3, int y3) {
    int x_center = round((x1 + x2 + x3) / 3);
    int y_center = round((y1 + y2 + y3) / 3);
    return make_pair(x_center, y_center);
}
// all the functions for triangle
class Triangle : public Shape {
public:
    Coordinates vertice1;
    Coordinates vertice2;
    Coordinates vertice3;
    Triangle(const pair<int, int>& v1, const pair<int, int>& v2, const pair<int, int>& v3)
        : Shape(3, findCenter(v1.first, v1.second, v2.first, v2.second, v3.first, v3.second)),
        vertice1(v1),vertice2(v2), vertice3(v3){}
    // Overrides the translate functions in the Shape class, moves all the vertices
    void translate(int dx, int dy) {
         position.translate(dx, dy);
         vertice1.translate(dx, dy);
         vertice2.translate(dx, dy);
         vertice3.translate(dx, dy);
     }
    // Overrides the virtual perimeter functions in the Shape class
     void scale(int factor, bool sign) {
         
         vertice1.scale(factor, sign);
         vertice2.scale(factor, sign);
         vertice3.scale(factor, sign);
     }
    // finding the distances for all the vertices
    vector<double> getDistances(){
        Coordinates vertex1(vertice1);
        Coordinates vertex2(vertice2);
        Coordinates vertex3(vertice3);
        vector<double> distances;
        double v1_v2=vertex1.distance(vertex2);
        double v1_v3=vertex1.distance(vertex3);
        double v2_v3=vertex2.distance(vertex3);
        distances.push_back(v1_v2);
        distances.push_back(v2_v3);
        distances.push_back(v1_v3);
        return distances;
    }
    // Overrides the virtual perimeter functions in the Shape class
    double getPerimeter(){
        return (getDistances()[0]+getDistances()[1]+getDistances()[2]);
    }
    // Overrides the virtual area functions in the Shape class
    double getArea(){
        double s=getPerimeter()/2;
        return sqrt(s*(s-getDistances()[0])*(s-getDistances()[1])*(s-getDistances()[2]));
    }
    
    // Overrides the virtual display functions in the Shape class
    string display(){
        return "The shape: Triangle\nThe area: "+to_string(int(round(getArea())))+"\nThe perimeter: "+to_string(int(round(getPerimeter())))+"\nThe coordinates of the vertices: "+vertice1.display()+", "+vertice2.display()+", "+vertice3.display()+", "+"\nThe coordinate of the center: "+position.display();
    }
};
// class for managing all the functions and menu
class ShapeManagement {
public:
    // initiate the coord as origin
    ShapeManagement():center_coord(make_pair(0, 0)) {choice = 0;}
    int choice;
    // vector for storing the shapes
    vector<Shape*> all_shapes;
    Shape* shape;
    Coordinates center_coord;
    void mainmenu() {
        while (true) {
            // display the main menu
            cout << "\n" << string(36, '-')<<"\n"<< endl;
            cout << "1: add a shape\n2: remove a shape by position\n3: get information about a shape by position\n4: area and perimeter of a shape by position\n5: Display information of all the shapes\n6: translate all the shapes\n7: scale all the shapes\n0: quit program" << endl;
            cout << "\nWhat can I do for you?" << endl;
            cin >> choice;
            cout << "\n" << string(36, '-')<<"\n"<< endl;
            // in case of every input
            switch (choice) {
                // case of adding a shape
                case 1:
                    while (true) {
                        int choice_shape;
                        cout << "Which shape?\n1: Rectangle\n2: Square\n3: Circle\n4: Triangle" << endl;
                        cin >> choice_shape;
                        cout << "\n" << string(36, '-')<<"\n"<< endl;
                    
                        // adding rectangle
                        if (choice_shape == 1) {
                            double width, length;
                            
                            cout << "Enter the center coordinates (X Y): ";
                            cin >> center_coord.coords.first >> center_coord.coords.second;
                            cout << "Enter width and length: ";
                            cin >> width >> length;
                            all_shapes.push_back(new Rectangle(width, length, center_coord));
                            cout<<"Rectangle is succesfully added!"<<endl;
                            break;
                        }
                        // adding square
                        else if (choice_shape==2){
                            double side;
                            
                            cout << "Enter the center coordinates (X Y): ";
                            cin >> center_coord.coords.first >> center_coord.coords.second;
                            cout << "Enter the length of the side: ";
                            cin >> side;
                            all_shapes.push_back(new Square(side, center_coord));
                            cout<<"Square is succesfully added!"<<endl;
                            break;
                        }
                        // adding circle
                        else if (choice_shape==3){
                            double radius;
                            
                            cout << "Enter the center coordinates (X Y): ";
                            cin >> center_coord.coords.first >> center_coord.coords.second;
                            cout << "Enter the radius: ";
                            cin >> radius;
                            all_shapes.push_back(new Circle(radius, center_coord));
                            cout<<"Circle is succesfully added!"<<endl;
                            break;
                        }
                        // adding triangle
                        else if (choice_shape==4){
                            
                            pair<int, int> v1, v2, v3;
                            cout << "Enter the coordinates of the first vertex (X Y): ";
                            cin >> v1.first >> v1.second;
                            cout << "Enter the coordinates of the second vertex (X Y): ";
                            cin >> v2.first >> v2.second;
                            cout << "Enter the coordinates of the third vertex (X Y): ";
                            cin >> v3.first >> v3.second;
                            all_shapes.push_back(new Triangle(v1, v2, v3));
                            cout << "Triangle is successfully added!" << endl;
                            break;
                        }
                        // error handling
                        else{
                            cout<<"Invalid Number!!\nTry again!!"<<endl;
                            cout << "\n" << string(36, '-')<<"\n"<< endl;
                        }
                    }
                    break;
                // the case of deletion of a shape
                case 2: {
                    bool found = false;
                    auto checked = all_shapes.begin();
                    cout << "Enter the center coordinates of the shape you wish to delete (X Y): " << endl;
                    cin >> center_coord.coords.first >> center_coord.coords.second;
                    cout << "\n" << string(36, '-')<<"\n"<< endl;
                    while (checked != all_shapes.end()) {
                        Shape* shape = *checked;
                        // if coordinates exist
                        if (shape->getCoordinates().getX() == center_coord.getX() && shape->getCoordinates().getY() == center_coord.getY()) {
                            delete shape;
                            checked = all_shapes.erase(checked);
                            found = true;
                            cout << "A shape has been deleted" << endl;
                        } else {
                            ++checked;
                        }
                    }
                    // error handling
                    if (!found) {
                        cout << "Couldn't find any shape, sorry :(" << endl;
                    }
                    break;
                }
                // getting information about a shape by position
                case 3:{
                    cout << "Enter the center coordinates of the shape, you wish to display(X Y): "<<endl;
                    cin >> center_coord.coords.first >> center_coord.coords.second;
                    bool found =true;
                    cout << "\n" << string(36, '-')<<"\n"<< endl;
                    for (auto checked = all_shapes.begin(); checked != all_shapes.end(); ++checked) {
                        Shape* shape = *checked;
                        // if coordinates exist
                        if(shape->getCoordinates().getX()==center_coord.getX() &&shape->getCoordinates().getY()==center_coord.getY()){
                            cout<<shape->display()<<endl;
                            found=false;}
                    }
                    if (found){
                        cout<<"Couldn't find any shape, sorry :("<<endl;
                    }
                    break;
                }
                // finding area and perimeter of a shape by position
                case 4:{
                    bool found =true;
                    cout << "Enter the center coordinates of the shape, you wish to see area and perimeter(X Y): "<<endl;
                    cin >> center_coord.coords.first >> center_coord.coords.second;
                    cout << "\n" << string(36, '-')<<"\n"<< endl;
                    for (auto checked = all_shapes.begin(); checked != all_shapes.end(); ++checked) {
                        Shape* shape = *checked;
                        // if coordinates exist
                        if(shape->getCoordinates().getX()==center_coord.getX() &&shape->getCoordinates().getY()==center_coord.getY()){
                            cout<<"Area: "<<shape->getArea()<<"\nPerimeter: "<<shape->getPerimeter()<<endl;
                            found=false;}
                    }
                    if (found){
                        cout<<"Couldn't find any shape, sorry :("<<endl;
                    }
                    break;}
                // displays all the shape informations
                case 5:
                    for (Shape* shape : all_shapes) {
                        cout<<shape->display()<<"\n"<<endl;
                        }
                    break;
                // translates every shapes
                case 6:
                    int dx,dy;
                    cout<<"Enter the translation in x then y: "<<endl;
                    cin>>dx>>dy;
                    for (Shape* shape : all_shapes) {
                        shape->translate(dx, dy);
                        }
                    cout<<"All shapes are translated!"<<endl;
                    break;
                //  calls the scaling function for all the shapes
                case 7:
                    int factor;
                    bool sign;
                    cout<<"Enter the factor to scale "<<endl;
                    cin>>factor;
                    cout<<"Enter the true for multiplication, false for division!"<<endl;
                    cin>>boolalpha>>sign;
                    for (Shape* shape : all_shapes) {
                        shape->scale(factor, sign);
                        }
                    cout<<"All shapes are scaled!"<<endl;
                    break;
                case 0:
                    exit(0);
                    break;
                // in case of inputting unexisting number
                default:
                    cout<<"Invalid Number!!\nTry again!!"<<endl;
            }
        }
    }
};



// main function to call the main menu
int main(int argc, const char * argv[]) {
    ShapeManagement management;
    management.mainmenu();
    return 0;
}
