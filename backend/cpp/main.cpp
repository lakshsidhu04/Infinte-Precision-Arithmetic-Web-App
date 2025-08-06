#include "interface.h" 
#include <iostream>

/*
 * The function checkValid checks if the string is a valid number.
*/
bool checkValid(std::string s){
    if(s[0]=='-'){
        s = s.substr(1);
    }
    for(int i=0;i<s.length();i++){
        if(s[i]=='.'){
            s = s.substr(0,i) + s.substr(i+1);
            break;
        }
    }
    for(int i=0;i<s.length();i++){
        if(s[i]<'0' || s[i]>'9'){
            return false;
        }
    }
    
    return true;

}
/*
 * The execution of the program starts here.
 * The program takes 4 arguments:
 * 1. Type of the number (int/float)
 * 2. Operation to be performed (add/sub/mul/div)
 * 3. First number
 * 4. Second number
 * The program then performs the operation on the two numbers and prints the result.
*/
int main(int argc, char *argv[]) // argc is the number of arguments and argv is the array of arguments
{
    if (argc != 5)  //checking if the number of arguments is correct
    {
        std::cerr << "Invalid number of arguments" << std::endl;
        return 1;
    }
    
    //getting the arguments
    std::string type = argv[1];
    std::string oper = argv[2];
    std::string s1 = argv[3];
    std::string s2 = argv[4];
    if(!checkValid(s1) || !checkValid(s2)){
        std::cerr << "Invalid number(s)" << std::endl;
        return 1;
    }
    if (type == "int")
    {
        InfiniteArithmetic::Integer ans; //creating an empty Integer object for answer
        InfiniteArithmetic::Integer obj1;
        obj1 = InfiniteArithmetic::Integer(s1); 
        InfiniteArithmetic::Integer obj2;
        obj2 = InfiniteArithmetic::Integer(s2);

        //checking for type of operation
        if (oper == "add")
        {
            ans = obj1 + obj2;
        }
        else if (oper == "sub")
        {
            ans = obj1 - obj2;
        }
        else if(oper == "mul")
        {
            ans = obj1 * obj2;
        }
        else if(oper == "div"){
            ans = obj1 / obj2;
        }
        else
        {
            std::cerr << "Invalid operation" << std::endl;
            return 1;
        }
        std::cout << ans << std::endl;
    }
    else if (type == "float")
    {
        InfiniteArithmetic::Float ans; //created an empty Float object for answer
        InfiniteArithmetic::Float obj1;
        obj1 = InfiniteArithmetic::Float(s1);
        InfiniteArithmetic::Float obj2;
        obj2 = InfiniteArithmetic::Float(s2);

        //checking for type of operation
        if (oper == "add")
        {
            ans = obj1 + obj2;
        }
        else if (oper == "sub")
        {
            ans = obj1 - obj2;
        }
        else if(oper == "mul")
        {
            ans = obj1 * obj2;
        }
        else if(oper == "div")
        {
            ans = obj1 / obj2;
        }
        else
        {
            std::cerr << "Invalid operation" << std::endl;
            return 1;
        }
        std::cout << ans << std::endl;
    }
    else
    {
        std::cerr << "Invalid type" << std::endl;
        return 1;
    }
    return 0;
}
