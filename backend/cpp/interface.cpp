#include "interface.h"
#include <iostream>
#include <string>

/**
 *Following are the constructor implementations for the Integer class.
*/
InfiniteArithmetic::Integer::Integer() { value = "0"; } //default constructor

InfiniteArithmetic::Integer::Integer(std::string s) { value = s; } //parameterized constructor for string

InfiniteArithmetic::Integer::Integer(int i) { value = std::to_string(i); } //parameterized constructor for an int

InfiniteArithmetic::Integer::Integer(Integer &obj) { value = obj.value; }  //copy constructor

InfiniteArithmetic::Integer::~Integer() { value.clear(); } //destructor

InfiniteArithmetic::Integer InfiniteArithmetic::Integer::parse(const std::string &s)
{
    Integer obj(s);
    return obj;
}

std::string InfiniteArithmetic::Integer::getString(){ return value; }

/*
 * Following are some functions which are used for repititive tasks in the overloaded operators
*/
/**
 * Function to remove leading zeroes from a string.
*/
std::string removeZeroes(std::string s)
{
    int i = 0;
    while (s[i] == '0')
    {
        i++;
    }
    return s.substr(i);
}

/*
 * Function to check if the string has a decimal point
*/
bool checkDec(std::string s){
    for(int i=0;i<s.length();i++){
        if(s[i] == '.'){
            return true;
        }
    }
    return false;
}

int findDec(std::string s){
    for(int i=0;i<s.length();i++){
        if(s[i] == '.'){
            return i;
        }
    }
    return -1;
}

/**
 * Function to check which of the two absolute values is greater.
*/
std::string checkMax(std::string s1, std::string s2)
{
    s1 = removeZeroes(s1);
    s2 = removeZeroes(s2);
    if (s1.length() > s2.length()) //s1 is greater if it is longer
        return s1;
    else if (s1.length() < s2.length()) //s2 is greater if it is longer
        return s2;
    else  //lexicographical checking
    {
        for (int i = 0; i < s1.length(); i++)
        {
            if (s1[i] > s2[i])
                return s1;
            else if (s1[i] < s2[i])
                return s2;
        }
        return s1;
    }
}

/*
 * Function to remove the decimal from a float string an return an integer string 
 * It is used in case the type chosen is int but user enters a float
*/
std::string float_to_int(std::string s){
    for(int i=0;i<s.length();i++){
        if(s[i] == '.'){
            s = s.substr(0,i);
            break;
        }
    }
    return s;
}

/*
 * Function to check if the string is zero   
*/
bool checkZero(std::string s){
    for(int i=0;i<s.length();i++){
        if(s[i] != '0'){
            return false;
        }
    }
    return true;
}

/*
 * Function to remove trailing zeroes from a string   
*/
std::string removeTrailZeroes(std::string s){
    int i = s.length()-1;
    while(s[i] == '0'){
        i--;
    }
    return s.substr(0,i+1);
}

std::ostream &InfiniteArithmetic::operator<<(std::ostream &os, const InfiniteArithmetic::Integer &obj)
{
    os << obj.value;
    return os;
}

/**
 * This overloaded operator performs addition for Integer class
 * It takes two Integer objects as arguments and returns an Integer object
 * It first checks if the numbers are negative and then performs addition accordingly
 * The function uses subtraction accordingly if the numbers are negative
 * It then performs addition digit by digit and returns the result
 * It also checks for overflow and carries over the carry to the next digit
 * It also checks for negative result and returns the result accordingly
*/
InfiniteArithmetic::Integer InfiniteArithmetic::operator+(InfiniteArithmetic::Integer &obj1, InfiniteArithmetic::Integer &obj2)
{
    std::string s1 = obj1.getString();
    std::string s2 = obj2.getString();
    if(checkDec(s1) || checkDec(s2)){
        InfiniteArithmetic::Float f1(s1);
        InfiniteArithmetic::Float f2(s2);
        InfiniteArithmetic::Float ans;
        ans = f1 + f2;
        std::string ansStr = ans.getString();
        ansStr = float_to_int(ansStr);
        InfiniteArithmetic::Integer obj(ansStr);
        return obj;
    }
    bool neg=false;

    if (s1[0] == '-' && s2[0] == '-') // if both are negative
    {
        neg = true; 
        s1 = s1.substr(1);
        s2 = s2.substr(1);
    }
    else if (s1[0] == '-' && s2[0] != '-') // if first of them is negative
    {
        s1 = s1.substr(1);
        s1 = removeZeroes(s1);
        s2 = removeZeroes(s2);
        InfiniteArithmetic::Integer tmp1;
        tmp1 = InfiniteArithmetic::Integer(s1);
        InfiniteArithmetic::Integer tmp2;
        tmp2 = InfiniteArithmetic::Integer(s2);
        InfiniteArithmetic::Integer ans;
        if (checkMax(s1, s2) == s1) // negative number has greater absolute value
        {
            neg = true; 
            ans = tmp1 - tmp2; //use of subtraction to get magnitude of the answer
        }
        else
        {
            ans = tmp2 - tmp1; //use of subtraction 
        }
        std::string ansStr = ans.getString();
        if(ansStr == "-"){
            ansStr = "0";
        }
        if(neg && ansStr != "0"){
            ansStr = "-" + ansStr;
        }
        InfiniteArithmetic::Integer obj(ansStr);
        return obj;
    }
    else if(s2[0]=='-' && s1[0]!='-') //if second of them is negative
    {
        s2 = s2.substr(1);
        s2 = removeZeroes(s2);
        s1 = removeZeroes(s1);
        InfiniteArithmetic::Integer tmp1;
        tmp1 = InfiniteArithmetic::Integer(s1);
        InfiniteArithmetic::Integer tmp2;
        tmp2 = InfiniteArithmetic::Integer(s2);
        InfiniteArithmetic::Integer ans;
        if (checkMax(s1, s2) == s2) // negative number has greater absolute value
        {
            neg = true;
            ans = tmp2 - tmp1; //use of subtraction to get the magnitude of answer
        }
        else
        {
            ans = tmp1 - tmp2; //use of subtraction to get magnitude
        }
        std::string ansStr = ans.getString();
        if(ansStr == "-"){
            ansStr = "0";
        }
        if(neg && ansStr != "0"){
            ansStr = "-" + ansStr;
        }
        InfiniteArithmetic::Integer obj(ansStr);
        return obj;
    }
    
    int l1 = s1.length();
    int l2 = s2.length();
    std::string ans = "";
    int l = (l1 > l2) ? l1 : l2;
    int carry = 0;
    for (int i = 0; i < l; i++)
    {
        int first_digit = (i < l1) ? s1[l1 - i - 1] - '0' : 0; //digit=0 in case of overflow
        int second_digit = (i < l2) ? s2[l2 - i - 1] - '0' : 0; //digit=0 in case of overflow
        int currSum = first_digit + second_digit + carry; //currSum stores digit by digit sum
        if (currSum > 9)
        {
            carry = 1; //carry=1 in case of overflow(above 10)
            currSum -= 10; //subtracting 10 from the overflowed digit sum
        }
        else
        {
            carry = 0;
        }
        ans = std::to_string(currSum) + ans;  //converting int to string and inserting at the beginning of the string
    }
    if (carry)
    {
        ans = "1" + ans;  //carry over at the front most digit(last iteration)
    }
    if(ans == "-"){
        ans = "0";
    }
    ans = removeZeroes(ans); //removing leading zeroes
    if (neg) //if the result is negative
    {
        ans = "-" + ans;
    }    
    InfiniteArithmetic::Integer obj(ans);
    return obj;
}

/*
 * This overloaded operator performs subtraction for Integer class
 * It takes two Integer objects as arguments and returns an Integer object
 * It first checks if the numbers are negative and then performs subtraction accordingly
 * The function uses addition accordingly if the numbers are negative
 * It then performs subtraction digit by digit and returns the result
 * It also checks for overflow and borrows from the next digit
 * It also checks for negative result and returns the result accordingly
*/
InfiniteArithmetic::Integer InfiniteArithmetic::operator-(InfiniteArithmetic::Integer &obj1, InfiniteArithmetic::Integer &obj2)
{
    std::string s1 = obj1.getString();
    std::string s2 = obj2.getString();
    if(checkDec(s1) || checkDec(s2)){ //if the numbers entered have decimals
        InfiniteArithmetic::Float f1(s1);
        InfiniteArithmetic::Float f2(s2);
        InfiniteArithmetic::Float ans;
        ans = f1 - f2;
        std::string ansStr = ans.getString();
        ansStr = float_to_int(ansStr);  //only take the integer part of the float answer
        InfiniteArithmetic::Integer obj(ansStr);
        return obj;
    }
    bool neg = false;
    if (s1[0] == '-' && s2[0] == '-') //if both are negative, the answer will be negative if the first number is greater
    {
        s1 = s1.substr(1);
        s2 = s2.substr(1);
        InfiniteArithmetic::Integer tmp1;
        tmp1 = InfiniteArithmetic::Integer(s1);
        InfiniteArithmetic::Integer tmp2;
        tmp2 = InfiniteArithmetic::Integer(s2);
        InfiniteArithmetic::Integer ans;
        if(checkMax(s1, s2)==s1) // magnitude of first number is greater
        {
            ans = tmp1 - tmp2;
            neg = true;
        }
        else
        {
            ans = tmp2 - tmp1;
            neg = false;
        }
        std::string ansStr = ans.getString();
        if(ansStr == "-"){
            ansStr = "0";
        }
        if(neg && ansStr != "0"){
            ansStr = "-" + ansStr;
        }
        InfiniteArithmetic::Integer obj(ansStr);
        return obj;
    }
    else if (s1[0] == '-' && s2[0] != '-') //answer will be negative always
    {
        s1 = s1.substr(1);
        neg = true;
        InfiniteArithmetic::Integer tmp1;
        tmp1 = InfiniteArithmetic::Integer(s1);
        InfiniteArithmetic::Integer tmp2;
        tmp2 = InfiniteArithmetic::Integer(s2);
        InfiniteArithmetic::Integer ans;
        ans = tmp1 + tmp2; //use of addition to get the magnitude of the answer
        std::string ansStr = ans.getString();
        if(ansStr == "-"){
            ansStr = "0";
        }
        if(neg && ansStr != "0"){
            ansStr = "-" + ansStr;
        }
        InfiniteArithmetic::Integer obj(ansStr);
        return obj;
    }
    else if (s2[0] == '-' && s1[0] != '-') //answer will be positive always
    {
        s2 = s2.substr(1);
        neg = false;
        InfiniteArithmetic::Integer tmp1;
        tmp1 = InfiniteArithmetic::Integer(s1);
        InfiniteArithmetic::Integer tmp2;
        tmp2 = InfiniteArithmetic::Integer(s2);
        InfiniteArithmetic::Integer ans;
        ans = tmp1 + tmp2;
        std::string ansStr = ans.getString();
        if(ansStr == "-"){
            ansStr = "0";
        }
        if(neg && ansStr != "0"){
            ansStr = "-" + ansStr;
        }
        InfiniteArithmetic::Integer obj(ansStr);
        return obj;
    }
    //remove leading zeroes
    s1 = removeZeroes(s1);
    s2 = removeZeroes(s2);
    std::string max = checkMax(s1, s2);
    if (max == s2)
    {
        neg = true;
    }
    std::string min = (max == s1) ? s2 : s1;
    std::string ans = "";
    int l1 = max.length();
    int l2 = min.length();
    
    int borrow = 0;

    for (int i = 0; i < l1; i++)
    {
        int first_digit = (i < l1) ? max[l1 - i - 1] - '0' : 0; //digit=0 in case of overflow
        int second_digit = (i < l2) ? min[l2 - i - 1] - '0' : 0; //digit=0 in case of overflow
        int currDiff = first_digit - second_digit - borrow; //digit by digit subtraction
        if (currDiff < 0)  //case of a borrow
        {
            borrow = 1;
            currDiff += 10;
        }
        else
        {
            borrow = 0;
        }
        ans = std::to_string(currDiff) + ans;
    }
    while (ans[0] == '0') //removing leading zeroes
    {
        ans = ans.substr(1);
    }
    if(ans == "-" || ans == ""){
        ans = "0";
    }
    if (neg && ans != "0") //if the result is negative
    {
        ans = "-" + ans;
    }
    InfiniteArithmetic::Integer ansInt(ans);
    return ansInt;
}

/*
 * This overloaded operator performs multiplication for Integer class
 * It takes two Integer objects as arguments and returns an Integer object
 * It first checks if the numbers are negative and then performs multiplication accordingly
 * The function creates a string of zeroes of length equal to the sum of the lengths of the two numbers
 * It then multiplies the numbers digit by digit and adds the result to the string of zeroes
 * It then removes leading zeroes and returns the result
 * It also checks for negative result and returns the result accordingly
*/
InfiniteArithmetic::Integer InfiniteArithmetic::operator*(InfiniteArithmetic::Integer &obj1, InfiniteArithmetic::Integer &obj2)
{
    std::string s1 = obj1.getString();
    std::string s2 = obj2.getString();
    if(checkDec(s1) || checkDec(s2)){ //if the numbers entered have decimals
        InfiniteArithmetic::Float f1(s1);
        InfiniteArithmetic::Float f2(s2);
        InfiniteArithmetic::Float prod;
        prod = f1 * f2;
        std::string ansStr = prod.getString();
        ansStr = float_to_int(ansStr); //only take the integer part of the float answer
        InfiniteArithmetic::Integer obj(ansStr);
        return obj;
    }
    bool neg = false;
    if (s1[0] == '-' && s2[0] == '-') //if both are negative, answer will be positive
    {
        s1 = s1.substr(1);
        s2 = s2.substr(1);
        neg = false;
    }
    else if (s2[0] == '-')
    {
        s2 = s2.substr(1);
        neg = true;
    }
    else if (s1[0] == '-')
    {
        s1 = s1.substr(1);
        neg = true;
    }
    std::string ans = "";
    int l1 = s1.length();
    int l2 = s2.length();
    for (int i = 0; i < l1 + l2; i++)
    {
        ans += "0";
    }
    for (int i = l1 - 1; i >= 0; i--)
    {
        for (int j = l2 - 1; j >= 0; j--)
        {
            int mul = (s1[i] - '0') * (s2[j] - '0'); //multiplying the digits
            int sum = mul + (ans[i + j + 1] - '0'); //adding the product to the existing digit
            ans[i + j + 1] = sum % 10 + '0'; //storing the unit digit
            ans[i + j] += sum / 10; //storing the carry in the previous higher digit
        }
    }
    while (ans[0] == '0') //removing leading zeroes
    {
        ans = ans.substr(1);
    }
    if(ans=="" || ans=="-"){
        ans="0";
    }
    if (neg && ans != "0")  //if the result is negative
    {
        ans = "-" + ans;
    }
    InfiniteArithmetic::Integer ansInt(ans);
    return ansInt;
}

/*
 * This overloaded operator performs division for Integer class
 * It takes two Integer objects as arguments and returns an Integer object
 * It first checks if the numbers are negative and then performs division accordingly
 * The implementation is done using long division method
 * First substrings of the dividend are taken and divided by the divisor
 * The quotient is then multiplied by the divisor and subtracted from the dividend to obtain the remainder
 * The implementation runs until dividend runs out of digits or only remaining dividend is less than the divisor
*/
InfiniteArithmetic::Integer InfiniteArithmetic::operator/(InfiniteArithmetic::Integer &obj1, InfiniteArithmetic::Integer &obj2){
    std::string s1 = obj1.getString();
    std::string s2 = obj2.getString();
    if(checkDec(s1) || checkDec(s2)){
        InfiniteArithmetic::Float f1(s1);
        InfiniteArithmetic::Float f2(s2);
        InfiniteArithmetic::Float ans;
        ans = f1 / f2;
        std::string ansStr = ans.getString();
        ansStr = float_to_int(ansStr);
        InfiniteArithmetic::Integer obj(ansStr);
        return obj;
    }
    if (checkZero(s2))
    {
        std::cerr << "Division by zero error" << std::endl;
        exit(1);
    }
    bool neg = false;
    if (s1[0] == '-' && s2[0] == '-')
    {
        s1 = s1.substr(1);
        s2 = s2.substr(1);
    }
    else if (s1[0] == '-' && s2[0] != '-')
    {
        s1 = s1.substr(1);
        neg = true;
    }
    else if (s2[0] == '-' && s1[0] != '-')
    {
        s2 = s2.substr(1);
        neg = true;
    }
    s1 = removeZeroes(s1);
    s2 = removeZeroes(s2);
    if(s2 == "1"){ //if divisor is 1, the quotient is the dividend
        if(neg){
            s1 = "-" + s1;
        }
        InfiniteArithmetic::Integer ans(s1);
        return ans;
    }
    if(s1 == s2){
        InfiniteArithmetic::Integer ans("1");
        return ans;
    }
    if(checkMax(s1,s2) == s2){
        InfiniteArithmetic::Integer ans("0");
        return ans;
    }
    std::string tmp = s1;
    std::string ans = "";
    int tail = s2.length();
    int count = 0;
    while (tmp.length() > 0 && tmp.length() >= s2.length() && tmp != "" && tmp != "0")
    {
        count++;
        std::string curr = tmp.substr(0, tail);
        std::string curr2 = removeZeroes(curr);
        while(checkMax(curr2, s2) == s2 && curr2 != s2) //if the current substring is less than the divisor
        {   
            if (tail < s1.length()){ //we can increment tail and increase size of curr2
                tail++;
            }
            else //we run out of digits in the dividend
            {
                ans = ans + "0";
                InfiniteArithmetic::Integer ansStr(ans);
                return ansStr;
            }
            if (count > 1) //if the count is greater than 1, we add a zero to the answer when we take an extra digit
            {
                ans = ans + "0";
            }
            curr = tmp.substr(0, tail); //taking the new substring
            curr2 = removeZeroes(curr); 
            if(checkMax(curr2, s2) == curr2 || curr2 == s2){ //if the new substring is more than the divisor
                break;
            }
        }
        
        InfiniteArithmetic::Integer dividend(curr2);
        InfiniteArithmetic::Integer divisor(s2);
        std::string rem = "";
        for (int i = 1; i <= 10; i++) //loop to find the quotient and remainder
        {
            InfiniteArithmetic::Integer tempQuo(i);
            std::string tempProd = (divisor * tempQuo).getString();
            if (checkMax(tempProd, curr2) == tempProd && tempProd != curr2) //to multiply the divisor by quotient till we get a number greater than the current substring
            {
                ans = ans + std::to_string(i - 1);
                InfiniteArithmetic::Integer quotient(i - 1);
                InfiniteArithmetic::Integer temp;
                temp = quotient * divisor;
                rem = (dividend - temp).getString();
                break;
            }
        }
        if(rem == "-"){
            rem = "0";
        }
        int l = curr.length() - rem.length(); //adding zeroes to the remainder to make it equal to the current substring
        for(int i=0;i<l;i++){
            rem = "0" + rem;
        }
        tmp = rem + tmp.substr(tail);
        bool zero = true;
        for (int i = 0; i < tmp.length(); i++) //checking if the remaining dividend is zero
        {
            if (tmp[i] != '0')
            {
                zero = false;
                break;
            }
        }

        if (zero) //if the remaining dividend is zero , we add zeroes
        {
            int l = s1.length() - tail;
            for (int i = 0; i < l; i++)
            {
                ans = ans + "0";
            }
            break;
        }
        std::string tmp2 = removeZeroes(tmp);
        if(checkMax(tmp2, s2) == s2 && tail == s1.length()){
            break;
        }
        tail++;
    }
    removeZeroes(ans);
    if(ans == ""){
        ans = "0";
    }
    bool flag = true;
    for (int i = 0; i < ans.length(); i++)
    {
        if (ans[i] != '0')
        {
            flag = false;
            break;
        }
    }
    if(neg){
        ans = "-" + ans;
    }
    if(flag){
        ans = "0";
    }
    InfiniteArithmetic::Integer ansInt(ans);
    return ansInt;
}

InfiniteArithmetic::Float::Float() { value = "0"; } //default constructor

InfiniteArithmetic::Float::Float(std::string s) { value = s; } //parameterized constructor for string

InfiniteArithmetic::Float::Float(Float &obj) { value = obj.value;}

InfiniteArithmetic::Float::~Float() { value.clear(); } //destructor

InfiniteArithmetic::Float InfiniteArithmetic::Float ::parse(const std::string &s)
{
    Float obj(s);
    return obj;
}

InfiniteArithmetic::Float::Float(float f)
{
    value = std::to_string(f);
}

/*
 * Function to return the string value of the float
*/
std::string InfiniteArithmetic::Float::getString() 
{
    return value;
}

std::ostream &InfiniteArithmetic::operator<<(std::ostream &os, const InfiniteArithmetic::Float &obj)
{
    os << obj.value;
    return os;
}

/**
 * This overloaded operator performs addition for Float class
 * It takes two Float objects as arguments and returns a Float object
 * It first checks if the numbers are negative and then performs addition accordingly
 * The numbers are centered about the decimals and the decimal is removed
 * This uses Integer addition at its core after removing the decimal from the float
 * It then adds the decimal back to the result and returns the result
*/
InfiniteArithmetic::Float InfiniteArithmetic::operator+( InfiniteArithmetic::Float &obj1, InfiniteArithmetic::Float &obj2)
{
    std::string s1 = obj1.getString();
    std::string s2 = obj2.getString();
    int dec1 = 0, dec2 = 0;
    int decIndex1 = findDec(s1);
    int decIndex2 = findDec(s2);
    if (decIndex1 == -1 || decIndex2 == -1)
    {
        if(decIndex1 == -1){
            decIndex1 = s1.length();
            s1 = s1 + ".0";
        }
        if(decIndex2 == -1){
            decIndex2 = s2.length();
            s2 = s2 + ".0";
        }
    }
    dec1 = s1.length() - decIndex1 - 1;
    dec2 = s2.length() - decIndex2 - 1;
    s1 = s1.substr(0, decIndex1) + s1.substr(decIndex1 + 1);
    s2 = s2.substr(0, decIndex2) + s2.substr(decIndex2 + 1);

    //make the decimal digits equal for easy addition
    if (dec1 > dec2)
    {
        for (int i = 0; i < (dec1 - dec2); i++)
            s2 += "0";
    }
    else if (dec2 > dec1)
    {
        for (int i = 0; i < (dec2 - dec1); i++)
            s1 += "0";
    }
    InfiniteArithmetic::Integer tempSum;
    InfiniteArithmetic::Integer tmp1(s1);
    InfiniteArithmetic::Integer tmp2(s2);
    tempSum = tmp1 + tmp2;  //use of Integer addition to get the answer without the decimal
    std::string sumStr = tempSum.getString();
    bool neg = false;
    if(sumStr[0] == '-'){
        sumStr = sumStr.substr(1);
        neg = true;
    }
    int dec = (dec1 > dec2) ? dec1 : dec2; //dec is the maximum of the two decimals
    if (sumStr == "-")
    {
        sumStr = "0";
    }
    if (sumStr != "0") //adding decimal back to the answer
    { 
        sumStr = sumStr.substr(0, sumStr.length() - dec) + "." + sumStr.substr(sumStr.length() - dec);
    }
    sumStr = removeTrailZeroes(sumStr);
    if(sumStr[0]=='.'){
        sumStr = "0" + sumStr;
    
    }
    if(sumStr[sumStr.length()-1] == '.'){
        sumStr = sumStr + "0";
    }
    if(neg){
        sumStr = "-" + sumStr;
    }
    InfiniteArithmetic::Float ans(sumStr);
    return ans;
}

/**
 * This overloaded operator performs subtraction for Float class
 * It takes two Float objects as arguments and returns a Float object
 * It first checks if the numbers are negative and then performs subtraction accordingly
 * The numbers are centered about the decimals and the decimal is removed
 * This uses Integer subtraction after removing the decimal from the float
 * It then adds the decimal back to the result and returns the result
*/
InfiniteArithmetic::Float InfiniteArithmetic::operator-(InfiniteArithmetic::Float &obj1, InfiniteArithmetic::Float &obj2)
{
    std::string s1 = obj1.getString();
    std::string s2 = obj2.getString();
    int dec1 = 0, dec2 = 0;
    int decIndex1 = findDec(s1);
    int decIndex2 = findDec(s2);
    if (decIndex1 == -1 || decIndex2 == -1)
    {
        if(decIndex1 == -1){
            decIndex1 = s1.length();
            s1 = s1 + ".0";
        }
        if(decIndex2 == -1){
            decIndex2 = s2.length();
            s2 = s2 + ".0";
        }
    }
    dec1 = s1.length() - decIndex1 - 1;
    dec2 = s2.length() - decIndex2 - 1;
    s1 = s1.substr(0, decIndex1) + s1.substr(decIndex1 + 1);
    s2 = s2.substr(0, decIndex2) + s2.substr(decIndex2 + 1);
    if (dec1 > dec2) //make the decimal digits equal for easy subtraction
    {
        for (int i = 0; i < (dec1 - dec2); i++)
            s2 += "0";
    }
    else if (dec2 > dec1)  //make the decimal digits equal for easy subtraction
    {
        for (int i = 0; i < (dec2 - dec1); i++)
            s1 += "0";
    }
    s1 = removeZeroes(s1);
    s2 = removeZeroes(s2);
    InfiniteArithmetic::Integer tempDiff;
    InfiniteArithmetic::Integer tmp1(s1);
    InfiniteArithmetic::Integer tmp2(s2);
    tempDiff = tmp1 - tmp2; //use of Integer subtraction to get the answer without the decimal
    std::string diffStr = tempDiff.getString();
    bool neg = false;
    if(diffStr[0] == '-'){
        diffStr = diffStr.substr(1);
        neg = true;
    }
    //put the decimal back
    int dec = (dec1 > dec2) ? dec1 : dec2;

    if(diffStr.length() < dec){
        int l = diffStr.length();
        for(int i=0;i<dec-l;i++){
            diffStr = "0" + diffStr;
        }
        diffStr = "0." + diffStr;
    }
    else{
        diffStr = diffStr.substr(0, diffStr.length() - dec) + "." + diffStr.substr(diffStr.length() - dec);
    }

    if (diffStr == "-")
    {
        diffStr = "0";
    }
    diffStr = removeTrailZeroes(diffStr);
    if(diffStr[0] == '.'){
        diffStr = "0" + diffStr;
    }
    if(diffStr[diffStr.length()-1] == '.'){
        diffStr = diffStr + "0";
    }
    if(neg){
        diffStr = "-" + diffStr;
    }
    InfiniteArithmetic::Float ans(diffStr);
    return ans;
}

/*
 * This overloaded operator performs multiplication for Float class
 * It takes two Float objects as arguments and returns a Float object
 * This uses Integer Multiplication after removing the decimals from the numbersz
 * The numbers are centered about the decimals and the decimal is removed
 * This uses Integer multiplication after removing the decimal from the float
 * It then adds the decimal back to the result and returns the result
*/
InfiniteArithmetic::Float InfiniteArithmetic::operator*(InfiniteArithmetic::Float &obj1,InfiniteArithmetic::Float &obj2){
    std::string s1 = obj1.getString();
    std::string s2 = obj2.getString();
    int dec1 = 0, dec2 = 0;
    int decIndex1 = findDec(s1);
    int decIndex2 = findDec(s2);
    if (decIndex1 == -1 || decIndex2 == -1)
    {
        if(decIndex1 == -1){
            decIndex1 = s1.length();
            s1 = s1 + ".0";
        }
        if(decIndex2 == -1){
            decIndex2 = s2.length();
            s2 = s2 + ".0";
        }
    }
    dec1 = s1.length() - decIndex1 - 1;
    dec2 = s2.length() - decIndex2 - 1;
    s1 = s1.substr(0, decIndex1) + s1.substr(decIndex1 + 1);
    s2 = s2.substr(0, decIndex2) + s2.substr(decIndex2 + 1);
    InfiniteArithmetic::Integer tempProd;
    InfiniteArithmetic::Integer tmp1(s1);
    InfiniteArithmetic::Integer tmp2(s2);
    tempProd = tmp1 * tmp2; //use of Integer multiplication to get the answer without the decimal
    std::string ans = tempProd.getString();
    if(ans == "0"){
        InfiniteArithmetic::Float ansFloat("0");
        return ansFloat; 
    }
    int dec = dec1 + dec2; //dec is the sum of the two decimals
    if (dec > ans.length()) // if the decimal is greater than the length of the answer, add zeroes in the beginning to compensate for the less length
    {
        int l = ans.length();
        for (int i = 0; i < dec - l; i++)
        {
            ans = "0" + ans;
        }
        ans = "0." + ans;
    }
    else
    {
        ans = ans.substr(0, ans.length() - dec) + "." + ans.substr(ans.length() - dec);
    }
    //loop to cut off trailing decimal zeros
    for (int i = ans.length() - 1; i >= 0; i--)
    {
        if (ans[i] != '0')
        {
            ans = ans.substr(0, i + 1);
            break;
        }
    }
    if(ans[ans.length()-1] == '.'){
        ans = ans + "0";
    }
    if(ans[0] == '.'){
        ans = "0" + ans;
    }
    InfiniteArithmetic::Float ansFloat(ans);
    return ansFloat;
}

/* 
 * This overloaded operator performs division for Float class
 * It takes two Float objects as arguments and returns a Float object
 * This uses Integer Division after removing the decimals from the numbers
 * The quotients are calculated till the remainder is zero or the precision is reached
 * The decimal is then added back to the result and returned
*/
InfiniteArithmetic::Float InfiniteArithmetic::operator/(InfiniteArithmetic::Float &obj1,InfiniteArithmetic::Float &obj2){
    std::string s1 = obj1.getString();
    std::string s2 = obj2.getString();
    bool neg = false;
    //check if the numbers are negative and remove the negative sign
    if (s1[0] == '-' && s2[0] == '-')
    {
        s1 = s1.substr(1);
        s2 = s2.substr(1);
    }
    else if (s1[0] == '-')
    {
        s1 = s1.substr(1);
        neg = true;
    }
    else if (s2[0] == '-')
    {
        s2 = s2.substr(1);
        neg = true;
    }
    int dec1 = -1, dec2 = -1;
    int decIndex1 = findDec(s1);
    int decIndex2 = findDec(s2);
    if (decIndex1 == -1 || decIndex2 == -1)
    {
        if(decIndex1 == -1){
            decIndex1 = s1.length();
            s1 = s1 + ".0";
        }
        if(decIndex2 == -1){
            decIndex2 = s2.length();
            s2 = s2 + ".0";
        }
    }
    dec1 = s1.length() - decIndex1 - 1;
    dec2 = s2.length() - decIndex2 - 1;
    s1 = s1.substr(0, decIndex1) + s1.substr(decIndex1 + 1);
    s2 = s2.substr(0, decIndex2) + s2.substr(decIndex2 + 1);
    
    //make the decimals equal
    if (dec1 > dec2)
    {
        for (int i = 0; i < dec1 - dec2; i++)
        {
            s2 = s2 + "0";
        }
    }
    else if (dec2 > dec1)
    {
        for (int i = 0; i < dec2 - dec1; i++)
        {
            s1 = s1 + "0";
        }
    }
    if (checkZero(s2))
    {
        std::cerr << "Division by zero error" << std::endl;
        exit(1);
    }
    s1 = removeZeroes(s1);
    s2 = removeZeroes(s2);
    std::string ans;
    InfiniteArithmetic::Integer tmp1(s1);
    InfiniteArithmetic::Integer tmp2(s2);
    InfiniteArithmetic::Integer rem(s1);
    InfiniteArithmetic::Integer tempQuo;
    int count = 0;
    int int_quotient_length = 0;  // integer part of the quotient
    while (rem.getString() != "0" ){ //long division method
        count++;
        tmp1 = rem;
        tempQuo = tmp1 / tmp2; //use of Integer division to get the quotient
        if (count == 1)        // integer part of the quotient
        {                                                     
            int_quotient_length=tempQuo.getString().length(); //store the length of the first quotient to put the decimal back in the end
        }
        ans = ans + tempQuo.getString();
        InfiniteArithmetic::Integer tempProduct;
        tempProduct = tmp2 * tempQuo;
        InfiniteArithmetic::Integer tempProd(tempProduct.getString());
        rem = tmp1 - tempProd;
        if (rem.getString() == "-" || rem.getString() == "0")
        {
            break;
        }
        std::string tempStr = rem.getString();
        if (tempStr == "0")
        {
            break;
        }
        tempStr = tempStr + "0";
        if (checkMax(tempStr, s2) == s2) //if the remainder is less than the divisor even after adding a zero
        {
            tempStr = tempStr + "0";
            ans = ans + "0";
            count++;
        }
        rem = InfiniteArithmetic::Integer(tempStr);
        if (count == 1001) //reached 1000 digits precision without reaching zero remainder
        {
            break;
        }
    }

    if (ans == "")
    {
        ans = "0";
    }
    if (checkZero(ans))
    {
        ans = "0";
    }
    //put the decimal back
    ans = ans.substr(0, int_quotient_length) + "." + ans.substr(int_quotient_length);
    if (ans[ans.length() - 1] == '.')  //if the decimal is at the end
    {
        ans = ans + "0";
    }
    if (ans == "0.00")
    {
        ans = "0.0";
    }

    if (neg) //if the result is negative
    {
        ans = "-" + ans;
    }

    InfiniteArithmetic::Float ansFloat(ans);
    return ansFloat;
}
