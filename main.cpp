#include <iostream>
#include "m_vector.h"
#include "exception.h"

bool constructor_check();
bool get_set_check();
bool to_array_check();
bool operators_check();
bool iterators_check();

void check_construct_ini(bool &success);
void check_get_1(bool &success);
void check_get_2(bool &success);
void check_set(bool &success);
void check_math_operation_1(bool &success);
void check_math_operation_2(bool &success);
void check_math_operation_3(bool &success);
void check_math_operation_4(bool &success);
void check_iterator_1(bool &success);
void check_iterator_2(bool &success);
void check_iterator_3(bool &success);


bool (*const checks[])(void) = {constructor_check, get_set_check, to_array_check, operators_check, iterators_check};

int main() {
    for(auto f : checks)//имя функции без () это указатель на функцию
           if(!f())
               return 1;
    return 0;
}

bool constructor_check(){
    bool success = true;
    const int standard_length = 10;
    {//проверка конструктора длины
        m_vector <int> the_vector(standard_length);
        if(the_vector.get_length() != standard_length){
            success = success && false;
            std::cerr << "error length constructor, expected = " << standard_length << " length = " << the_vector.get_length() << std::endl;
        }
    }
    {//отрицательная длина
        try {
            m_vector <int> the_vector(-standard_length);
            success = false;
            std::cerr << "error length constructor, expected error, length = " << -standard_length << std::endl;
        } catch (MException &ex) {}
    }
    {//конструктора копирования
        m_vector <int> the_vector_1(standard_length);
        m_vector <int> the_vector_2(the_vector_1);
        for(int i = 0; i < standard_length; i++){
            if(the_vector_1[i] != the_vector_2[i]){
                std::cerr << "error copy constructor, expected = " << the_vector_1[i] << " value = " << the_vector_2[i] << std::endl;
                success = success && false;
            }
        }
    }
    check_construct_ini(success);
    std::cout << (success ? "construct check passed" : "construct check not passed") << std::endl;
    return success;
}

bool get_set_check(){
    bool success = true;
    check_get_1(success);
    check_get_2(success);
    check_set(success);

    std::cout << (success ? "get/set check passed" : "get/set check not passed") << std::endl;
    return success;
}

bool to_array_check()
{
    bool success = true;
    m_vector<int> the_vector({-3, -2, -1, 0, 1, 2, 3});
    int *array = the_vector.to_array();
    for (int i  = 0; i < the_vector.get_length(); i++)
    {
        if(the_vector[i] != array[i])
        {
            std::cerr << "error to_array(), expected (" << i << ") = " << the_vector[i] << " val = " << array[i] << std::endl;
            success = success && false;
        }
    }
    delete[] array;
    std::cout << (success ? "to array check passed" : "to array check not passed") << std::endl;
    return success;
}

bool operators_check() {
    bool success = true;
    const int standard_length = 10;
    {
        m_vector <int> the_vector_1(standard_length);
        m_vector <int> the_vector_2(standard_length);
        the_vector_2 = the_vector_1;

        if(the_vector_1.get_length() != the_vector_2.get_length())
        {
            std::cerr << "error operator \"=\",  expected len = " << the_vector_1.get_length() << " len = " << the_vector_2.get_length() << std::endl;
            success = success && false;
        }

        for (int i = 0; i < the_vector_1.get_length(); i++) {
            if(the_vector_1[i] != the_vector_2[i]){
                std::cerr << "error operator \"=\",  expected val[" << i << "] = " << the_vector_1[i] << " val = " << the_vector_2[i] << std::endl;
                success = success && false;
            }
        }
    }

    check_math_operation_1(success);
    check_math_operation_2(success);
    check_math_operation_3(success);
    check_math_operation_4(success);

    std::cout << (success ? "operators check passed" : "operators check not passed") << std::endl;
    return success;
}

bool iterators_check()
{
    bool success = true;
    check_iterator_1(success);
    check_iterator_2(success);
    check_iterator_3(success);
    std::cout << (success ? "iterators check passed" : "iterators check not passed") << std::endl;
    return success;
}


void check_construct_ini(bool &success){
    {//конструктор инициализации
        m_vector <int> the_vector({-3, -2, -1, 0, 1, 2 , 3});
        if(the_vector.get_length() != 7){
            std::cerr << "error ini constructor, expected = " << 7 << " length = " << the_vector.get_length() << std::endl;
            success = success && false;
        }
        for(int i = 0; i < the_vector.get_length(); i++){
            if(the_vector[i] != i - 3){
                std::cerr << "error ini constructor, expected = " << i - 3 << " value = " << the_vector[i] << std::endl;
                success = success && false;
            }
        }
        try {
            m_vector <int> the_vector_2({});
            std::cerr << "error ini constructor, expected error, length = " << 0 << std::endl;
            success = success && false;
        }  catch (MException &ex) {
        }
    }
}


void check_get_1(bool &success){
    m_vector <int> the_vector({-3, -2, -1, 0, 1, 2 , 3});
    {// get check
        for(int i = 0; i < the_vector.get_length(); i++){
            auto value = the_vector[i];
            if(value != i - 3){
                std::cerr << "error get[], expected = " << i - 3 << " value = " << value << std::endl;
                success = success && false;
            }
        }
        for(int i = 0; i < the_vector.get_length(); i++){
            auto value = the_vector.get_elem(i);
            if(value != i - 3){
                std::cerr << "error get(), expected = " << i - 3 << " value = " << value << std::endl;
                success = success && false;
            }
        }
        for(int i = 0; i < the_vector.get_length(); i++){
            auto value1 = the_vector.get_elem(i);
            auto value2 = the_vector[i];
            if(value1 != value2){
                std::cerr << "error get() != get[], get() = " << value1 << " get[] = " << value2 << std::endl;
                success = success && false;
            }
        }

    }
}
// проверки на выход за границу
void check_get_2(bool &success)
{
    m_vector <int> the_vector({-3, -2, -1, 0, 1, 2 , 3});
    {
        try {
            the_vector.get_elem(-1);
            std::cerr << "error get(-1), expected error " << std::endl;
            success = success && false;
        }  catch (MException &ex) {
            std::cout << ex << std::endl;
        }
    }
    {
        try {
            the_vector.get_elem(the_vector.get_length());
            std::cerr << "error get(len), expected error " << std::endl;
            success = success && false;
        }  catch (MException &ex) {}

    }
    {
        try {
            the_vector[-1];// левая граница
            std::cerr << "error get[-1], expected error" << std::endl;
            success = success && false;
        }  catch (MException &ex) {}
    }
    {
        try {
            the_vector[the_vector.get_length()];// правая граница
            std::cerr << "error get[len], expected error" << std::endl;
            success = success && false;
        }  catch (MException &ex) {}
    }
}

void check_set(bool &success){
    {//set check
        m_vector<int> the_vector({-3, -2, -1, 0, 1, 2, 3});
        for (int i = 0; i < the_vector.get_length(); i++) {
            int diff = 20;
            auto pred_value = the_vector.get_elem(i) + diff;
            the_vector.set_elem(i, pred_value);
            auto post_value = the_vector.get_elem(i);
            if(post_value != pred_value){
                std::cerr << "error set(" << i << "), pred_get() + diff = " << pred_value << " post_get() = " << post_value << std::endl;
                success = success && false;
            }
        }
        {
            try {
                int value = 0;
                the_vector.set_elem(-1, value);
                std::cerr << "error set(-1), expected error " << std::endl;
                success = success && false;
            }  catch (MException &ex) {}
        }
        {
            try {
                int value = 0;
                the_vector.set_elem(the_vector.get_length(), value);
                std::cerr << "error set(len), expected error " << std::endl;
                success = success && false;
            }  catch (MException &ex) {}
        }
    }
}

void check_math_operation_1(bool &success){
    const int standard_length = 10;
    {
        m_vector <int> the_vector_1(standard_length);
        m_vector <int> the_vector_2(standard_length);
        m_vector <int> the_vector_3 = the_vector_2;
        the_vector_3 += the_vector_1;

        for (int i = 0; i < the_vector_1.get_length(); i++) {
            auto value =  the_vector_1[i] + the_vector_2[i];
            if(value != the_vector_3[i]){
                std::cerr << "error operator \"+=\",  expected val[" << i << "] = " << value << " val = " << the_vector_3[i] << std::endl;
                success = success && false;
            }
        }
    }
    {
        m_vector <int> the_vector_1(standard_length);
        m_vector <int> the_vector_2(standard_length);
        m_vector <int> the_vector_3 = the_vector_2;
        the_vector_3 -= the_vector_1;

        for (int i = 0; i < the_vector_1.get_length(); i++) {
            auto value = the_vector_2[i] - the_vector_1[i] ;
            if(value != the_vector_3[i]){
                std::cerr << "error operator \"-=\",  expected val[" << i << "] = " << value << " val = " << the_vector_3[i] << std::endl;
                success = success && false;
            }
        }
    }
}

void check_math_operation_2(bool &success){
    const int standard_length = 10;
    {
        m_vector <int> the_vector_1(standard_length);
        m_vector <int> the_vector_2 = the_vector_1;
        int multiplier = 5; //
        the_vector_2 *= multiplier;

        for (int i = 0; i < the_vector_1.get_length(); i++) {
            auto value = the_vector_1[i] * multiplier;
            if(value != the_vector_2[i]){
                std::cerr << "error operator \"*=\",  expected val[" << i << "] = " << value << " val = " << the_vector_2[i] << std::endl;
                success = success && false;
            }
        }
    }
    {
        m_vector <int> the_vector_1(standard_length);
        m_vector <int> the_vector_2 = the_vector_1;
        int divider = 5;
        the_vector_2 /= divider;
        for (int i = 0; i < the_vector_1.get_length(); i++) {
            auto value = the_vector_1[i] / divider;
            if(value != the_vector_2[i]){
                std::cerr << "error operator \"/=\",  expected val[" << i << "] = " << value << " val = " << the_vector_2[i] << std::endl;
                success = success && false;
            }
        }
    }
    {
        m_vector <int> the_vector(standard_length);
        try {
            the_vector /= 0;
            std::cerr << "error operator \"/=\",  expected error " << std::endl;
            success = success && false;
        }  catch (MException &ex) {

        }
    }
}

void check_math_operation_3(bool &success){
    const int standard_length = 10;
    {
        m_vector <int> the_vector_1(standard_length);
        m_vector <int> the_vector_2(standard_length);
        m_vector <int> the_vector_3 = the_vector_2 + the_vector_1;

        for (int i = 0; i < the_vector_1.get_length(); i++) {
            auto value =  the_vector_1[i] + the_vector_2[i];
            if(value != the_vector_3[i]){
                std::cerr << "error operator \"+\",  expected val[" << i << "] = " << value << " val = " << the_vector_3[i] << std::endl;
                success = success && false;
            }
        }
    }
    {
        m_vector <int> the_vector_1(standard_length);
        m_vector <int> the_vector_2(standard_length);
        m_vector <int> the_vector_3 = the_vector_2 - the_vector_1;

        for (int i = 0; i < the_vector_1.get_length(); i++) {
            auto value = the_vector_2[i] - the_vector_1[i];
            if(value != the_vector_3[i]){
                std::cerr << "error operator \"-\",  expected val[" << i << "] = " << value << " val = " << the_vector_3[i] << std::endl;
                success = success && false;
            }
        }
    }
}

void check_math_operation_4(bool &success){
    const int standard_length = 10;
    {
        int multiplier = 5;
        m_vector <int> the_vector_1(standard_length);
        m_vector <int> the_vector_2 = the_vector_1 * multiplier;

        for (int i = 0; i < the_vector_1.get_length(); i++) {
            auto value = the_vector_1[i] * multiplier;
            if(value != the_vector_2[i]){
                std::cerr << "error operator \"*\",  expected val[" << i << "] = " << value << " val = " << the_vector_2[i] << std::endl;
                success = success && false;
            }
        }
    }
    {
        int divider = 5;
        m_vector <int> the_vector_1(standard_length);
        m_vector <int> the_vector_2 = the_vector_1 / divider;

        for (int i = 0; i < the_vector_1.get_length(); i++) {
            auto value = the_vector_1[i] / divider;
            if(value != the_vector_2[i]){
                std::cerr << "error operator \"/\",  expected val[" << i << "] = " << value << " val = " << the_vector_2[i] << std::endl;
                success = success && false;
            }
        }
    }
    {
        m_vector <int> the_vector(standard_length);
        int dvider = 0;
        try {
            the_vector / dvider;
            std::cerr << "error operator \"/\",  expected error " << std::endl;
            success = success && false;
        }  catch (MException &ex) {

        }
    }
}

void check_iterator_1(bool &success){
    const int standard_length = 10;
    {
        m_vector <int> the_vector(standard_length);
        Iterator<int> it = the_vector.iterator_begin();

        for (int i = 0; i < the_vector.get_length(); i++)
        {
            auto value = it.value();
            if(value != the_vector[i])
            {
                std::cerr << "error Iterator without overload, expected val[" << i << "] = " << the_vector[i] << " val = " << value << std::endl;
                success = success && false;
            }
            it.next();
        }
        Iterator<int> end = the_vector.iterator_end();
        if(it != end)
        {
            std::cerr << "error Iterator without overload, it != iterator_end" << std::endl;
            success = success && false;
        }
        if(!it.is_end())
        {
            std::cerr << "error Iterator without overload, !it.is_end()" << std::endl;
            success = success && false;
        }
    }
}

void check_iterator_2(bool &success){
    const int standard_length = 10;
    {
        m_vector <int> the_vector(standard_length);
        Iterator<int> it = the_vector.iterator_begin();

        for (int i = 0; i < the_vector.get_length(); i++)
        {
            auto value = *it;
            if(value != the_vector[i])
            {
                std::cerr << "error Iterator with overload, expected val[" << i << "] = " << the_vector[i] << " val = " << value << std::endl;
                success = success && false;
            }
            ++it;
        }
        Iterator<int> end = the_vector.iterator_end();
        if(it != end)
        {
            std::cerr << "error Iterator with overload, it != iterator_end" << std::endl;
            success = success && false;
        }
        if(!it.is_end())
        {
            std::cerr << "error Iterator with overload, !it.is_end()" << std::endl;
            success = success && false;
        }
    }
}

void check_iterator_3(bool &success){
    const int standard_length = 10;
    {
        m_vector <int> the_vector(standard_length);
        Iterator<int> it(the_vector);

        for (int i = 0; i < the_vector.get_length(); i++)
        {
            auto value = *it;
            if(value != the_vector[i])
            {
                std::cerr << "error Iterator with overload, expected val[" << i << "] = " << the_vector[i] << " val = " << value << std::endl;
                success = success && false;
            }
            ++it;
        }
        Iterator<int> end = the_vector.iterator_end();
        if(it != end)
        {
            std::cerr << "error Iterator with overload, it != iterator_end" << std::endl;
            success = success && false;
        }
        if(!it.is_end())
        {
            std::cerr << "error Iterator with overload, !it.is_end()" << std::endl;
            success = success && false;
        }
    }
}




