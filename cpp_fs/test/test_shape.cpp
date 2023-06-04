/*******************************************************************************
--------------------------------------------------------------------------------
*	file name: test_shape.cpp
*	author: Moshe Cohen
*	reviewer: Dor Glaubach

--------------------------------------------------------------------------------
*******************************************************************************/
#include <iostream>    // cout
#include <cassert>    // assert
#include <cstring>   // strcmp

#include "shape.hpp"
#include "circle.hpp"
#include "rectangle.hpp"
#include "square.hpp"
#include "line.hpp"

enum status_t {SUCCESS, FAILURE};

const char *RED_B = "\033[01;31m";
const char *GREEN_B = "\033[01;32m";
const char *YELLOW_B = "\033[01;33m";
const char *BLUE_B = "\033[01;34m";
const char *BLACK_B = "\033[01;30m";
const char *WHITE_B = "\033[01;37m";
const char *RED = "\033[0;31m";
const char *GREEN = "\033[0;32m";
const char *YELLOW = "\033[0;33m";
const char *RESET = "\033[0m";
void RunTest(bool result, const char *name)
{
    std::cout << YELLOW_B << "Test "  << name << ": " << RESET;
    if (result)
    {
        std::cout << GREEN_B << "SUCCESS" << RESET << std::endl;
    }
    else
    {
        std::cout << RED_B << "FAILURE" << RESET << std::endl;
    }
}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~includes~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

const size_t OFFSET(20);

using namespace ilrd;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~definitions~~~~~~~~~~~~~~~~~~~~~~~~~~*/
status_t TestCircle();
status_t TestRectangle();
status_t TestSquare();
status_t TestLine();
status_t TestListOfShapes();

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~functions~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// compile line:
// g++ test/test_shapes.cpp src/circle.cpp src/rectangle.cpp src/line.cpp src/square.cpp  -I include/
int main()
{
    std::cout << BLUE_B << "Test Shapes:" << RESET << std::endl;

    RunTest(SUCCESS == TestCircle(), "Test Circle");
    RunTest(SUCCESS == TestRectangle(), "Test Rectangle");
    RunTest(SUCCESS == TestSquare(), "Test Square");
    RunTest(SUCCESS == TestLine(), "Test Line");

    TestListOfShapes();

    std::cout << GREEN_B << "Test Shapes Succeed!" << RESET << std::endl;

	return 0;
}

status_t TestCircle()
{
    Circle circle2;
    Shape *circle = new Circle;

    assert(0 == circle2.GetOffset());
    assert(0 == circle->GetOffset());
    
    std::cout << "Circle before Move:" << std::endl;
    circle2.Draw();
    circle->Draw();

    circle2.Move(OFFSET);
    circle->Move(OFFSET);

    assert(OFFSET == circle2.GetOffset());
    assert(OFFSET == circle->GetOffset());

    std::cout << "Circle after Move:" << std::endl;
    circle2.Draw();
    circle->Draw();

    assert(22 == circle2.Move(22).GetOffset()); // test for cat

    delete circle;
    return SUCCESS;    
}

status_t TestRectangle()
{
    Rectangle rectangle2;
    Shape *rectangle = new Rectangle;

    assert(0 == rectangle2.GetOffset());
    assert(0 == rectangle->GetOffset());
    
    std::cout << "Rectangle before Move:" << std::endl;
    rectangle2.Draw();
    rectangle->Draw();

    rectangle2.Move(OFFSET);
    rectangle->Move(OFFSET);

    assert(OFFSET == rectangle2.GetOffset());
    assert(OFFSET == rectangle->GetOffset());

    std::cout << "Rectangle after Move:" << std::endl;
    rectangle2.Draw();
    rectangle->Draw(); 

    delete rectangle;
    return SUCCESS; 
}

status_t TestSquare()
{
    Square square2;
    Shape *square = new Square;

    assert(0 == square2.GetOffset());
    assert(0 == square->GetOffset());
    
    std::cout << "square before Move:" << std::endl;
    square2.Draw();
    square->Draw();

    square2.Move(OFFSET);
    square->Move(OFFSET);

    assert(OFFSET == square2.GetOffset());
    assert(OFFSET == square->GetOffset());

    std::cout << "square after Move:" << std::endl;
    square2.Draw();
    square->Draw(); 

    delete square;
    return SUCCESS;  
}

status_t TestLine()
{
    Line line2;
    Shape *line = new Line;

    assert(0 == line2.GetOffset());
    assert(0 == line->GetOffset());
    
    std::cout << "line before Move:" << std::endl;
    line2.Draw();
    line->Draw();

    line2.Move(OFFSET);
    line->Move(OFFSET);

    assert(OFFSET == line2.GetOffset());
    assert(OFFSET == line->GetOffset());

    std::cout << "line after Move:" << std::endl;
    line2.Draw();
    line->Draw(); 

    delete line;
    return SUCCESS;   
}

status_t TestListOfShapes()
{
    // Shape *ListOfShapes = static_cast<Shape *>(operator new(4 * sizeof(Shape *)));

    Shape **List = new Shape *[4];
    Circle circle;
    Rectangle rectangle;
    Square square;
    Line line;

    List[0] = &circle;
    List[2] = &rectangle;
    List[1] = &square;
    List[3] = &line;

    std::cout << "ListOfShapes:" << std::endl;
    ListOfShapes(List, 4);
    
    delete[] List;

    return SUCCESS;
}