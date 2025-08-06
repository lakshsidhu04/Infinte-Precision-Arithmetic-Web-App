#include <iostream>
namespace InfiniteArithmetic
{
    /*
     * The class Arithm is the parent class for Integer and Float classes.
        * It has a pure virtual function getString() which is implemented in the child classes. 
        * All the classes have a value which is a string.
        * All classes will have a parse function which will convert a string to the respective class object.
    */
    class Arithm{  //parent class
        std::string value;  //each class will have a value
        public:
        virtual std::string getString() = 0;  //pure virtual function
    };
    

    /*
     * The class Integer is a child class of Arithm.
     * It has a value which is a string.
     * It is implemented for operations of infinite precision arithmetic on integers.
     * It has a parse function which converts a string to an Integer object.
     * It has overloaded operators for addition, subtraction, multiplication and division.
    */
    class Integer : public Arithm
    {
        std::string value;

    public:
        Integer(); //default constructor
        Integer(std::string s); // parameterized constructor for string
        Integer(Integer &obj); //copy constructor
        Integer(int i); //parameterized constructor for an int
        ~Integer(); //destructor
        
        std::string getString();  //function to get the string value of the object
        static Integer parse(const std::string &s); //parse
        
        friend std::ostream &operator<<(std::ostream &os, const Integer &obj); //overloaded << for easy output
    
    };
    
    //overloaded operators
    Integer operator+( Integer &obj1, Integer &obj2);
    Integer operator-(Integer &obj1, Integer &obj2);
    Integer operator*(Integer &obj1, Integer &obj2);
    Integer operator/(Integer &obj1, Integer &obj2);
    

    /*
     * The class Float is a child class of Arithm.
     * It has a value which is a string.
     * It is implemented for operations of infinite precision arithmetic on floating point numbers.
     * It has a parse function which converts a string to a Float object.
     * It has overloaded operators for addition, subtraction, multiplication and division.
    */
    class Float : public Arithm
    {
        std::string value;

        public:
        Float();   //default constructor
        Float(std::string s); //parameterized constructor for string
        Float(Float &obj); //copy constructor
        Float(float f); //parameterized constructor for a float
        ~Float(); //destructor
        
        std::string getString(); //function to get the string value of the object
        
        static Float parse(const std::string &s); //parse
        friend std::ostream &operator<<(std::ostream &os, const Float &obj); //overloaded << for easy output
    };
    
    //overloaded operators
    Float operator+(Float &obj1, Float &obj2);
    Float operator-(Float &obj1, Float &obj2);
    Float operator*(Float &obj1, Float &obj2);
    Float operator/(Float &obj1, Float &obj2);
    
}
