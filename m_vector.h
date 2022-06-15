#ifndef M_VECTOR_H
#define M_VECTOR_H
#include<iostream>
#include<math.h>
#include <sstream>
#include <string>
#include "exception.h"

#define MIN(x, y) ((x) < (y) ? (x) : (y))


template<typename T>
class Iterator;

template <typename T>
class m_vector {
private:
    size_t n;
    T *data;

    void copy(T* arr);
public:
    m_vector();//нулевой конструктор
    m_vector(int length);//конструктор который принимает длину, записывает это в приватное поле n и динамически выделяет память под массив типа Т и размера n
    m_vector(m_vector<T>const& vect);//конструктор копирования для констант
    explicit m_vector(std::initializer_list<T> lst);//конструктор инициализации через {} // = {}
    ~m_vector();//деструктор
    
    m_vector<T>& operator =(m_vector<T>& lst);//перегрузка оператора =
    int get_length() const;//метод возвращение длины
    void set_elem(int index, T& elem);//метод втавляет элемент по индексу
    T& get_elem(int index);//метод берет элемент по индексу
    T* to_array();//создает массив и заполняет его элементами из data
    T& operator[](int index);//перегрузка оператора []
    T& operator[](int index) const;//перегрузка оператора [] для констант
    m_vector<T>& operator +=(m_vector<T>& vect);//перегрузка оператора +=
    m_vector<T>& operator -=(m_vector<T>& vect);//перегрузка оператора -=
    m_vector<T>& operator *=(T const& val);//перегрузка оператора *=
    m_vector<T>& operator /=(T const& val);//перегрузка оператора /=

    template <typename _T>//перегрузка оператора вывода <<
    friend std::ostream& operator <<(std::ostream &os, m_vector <_T> &lst);

    template<typename _T>//перегрузка оператора +
    friend m_vector<_T> operator +(m_vector<_T>& v1, m_vector<_T>& v2);

    template<typename _T>//перегрузка оператора -
    friend m_vector<_T> operator -(m_vector<_T>& v1, m_vector<_T>& v2);

    template<typename _T>//перегрузка оператора *
    friend m_vector<_T>operator *(m_vector<_T>& v1, _T& val);

    template<typename _T>//перегрузка оператора /
    friend m_vector<_T>operator /(m_vector<_T>& v1, _T& val);

    //методы типа касса Iterator<T>
    Iterator<T> iterator_begin();//переводит итераторр в начало
    Iterator<T> iterator_end();//переводит итератор в конец
};

//класс итератор
template <typename T>
class Iterator {
private:
    size_t it;
    m_vector<T>& container_obj;//ссылка на класс m_vector
public:
    Iterator<T>(m_vector<T> &container_obj);
    Iterator<T>(m_vector<T> *container_obj, size_t n);

    Iterator<T> next();//метод переходящий к следующему значению итератора
    bool is_end();//метод возвращает через it длину переданного контейнера
    T value();//возвращает container_obj по it индексу
    Iterator& operator ++();//перегрузка оператора ++
    T& operator *();//перегрузка указателя, разыменовка
    bool operator ==(Iterator<T> &b);//перегрузка оператора ==
    bool operator !=(Iterator<T> &b);//перегрузка оператора !=
};

template <typename T>
void m_vector<T>::copy(T* arr){
    for(size_t i = 0; i < n; i++){
        data[i] = arr[i];
    }
}

template <typename _T>//перегрузка оператора <<
std::ostream& operator <<(std::ostream &os, m_vector <_T> &lst){
    os << "m_vector(";
    size_t i = 0;
    for(; i < lst.get_length() - 1; i++){
        os << lst[i] << ", ";
    }
    os << lst[i] << ")";
    return os;
}

//нулевой конструктор
template <typename T>
m_vector<T>::m_vector() {//конст без аргументов
    size_t standart_lenght = 10;
    std::cerr << "standart lenght = " << standart_lenght << std::endl;
    n = standart_lenght;
    try {
       data = new T[n];
    } catch (std::bad_alloc ex) {
        throw MException("not memory:(");
    }
}

//конструктор который принимает длину, записывает это в приватное поле n
//и динамически выделяет память под массив типа Т и размера n
template <typename T>//класс шаблоном и работаем с данными по шаблону Т
m_vector<T>::m_vector(int length) {
    if(length <= 0){
        std::ostringstream os;//создаем поток
        os << "incorrect length = " << length << std::endl;//бросаем что-то в поток
        std::string s = os.str();//преобразуем поток в строку
        throw MException(s);//создаем новый экспепшен с нашей строкой
    }
    n = (size_t)length;
    try {
       data = new T[n];
    } catch (std::bad_alloc ex) {

        throw MException("not memory:(");
    }
}


//конструктор копирования для констант:)
template <typename T>
m_vector<T>::m_vector(m_vector<T>const& vect){
    n = vect.get_length();//ссылка - псевдоним
    if(n == 0){
        throw MException("memory = 0, not good:(");
    }
    try {
       data = new T[n];
    } catch (std::bad_alloc ex) {
        throw MException("not memory:(");
    }
    copy(vect.data);
}


//принимает фигурные скобочки и значения меж ними
template <typename T>
m_vector<T>::m_vector(std::initializer_list<T> lst){
    //std::copy(lst.begin(), lst.end(), data);
    n = lst.size();
    if(n == 0){
        throw MException("memory = 0, not good:(");
    }
    try {
       data = new T[n];
    } catch (std::bad_alloc ex) {
        throw MException("not memory:(");
    }
    auto it = lst.begin();
    for(size_t i = 0; it != lst.end(); i++){
        data[i] = *it;
        it++;
    }
}


//деструктор
template <typename T>
m_vector<T>::~m_vector() {
    delete[] data;
}

//перегрузка оператора присваивания
template <typename T>
m_vector<T>& m_vector<T>::operator =( m_vector<T>& lst){
    if(this == &lst){
        return *this;
    }
    delete[] data;
    n = (size_t)lst.get_length();
    try {
       data = new T[n];
    } catch (std::bad_alloc ex) {
        throw MException("not memory:(");
    }
    copy(lst.data);
    /*for(size_t i = 0; i < n; i++){
        data[i] = lst[i];
    }*/
    return *this;
}

template <typename T>//
T* m_vector<T>::to_array(){
    try {
       T *new_array = new T[n];
       for(size_t i = 0; i < n; i++){//копи
           new_array[i] = data[i];
       }
       return new_array;
    } catch (std::bad_alloc ex) {
        throw MException("not memory:(");
    }
}

//const
template <typename T>//метод возвращения длины
int m_vector<T>::get_length() const {
    return (int)n;
}

template <typename T>//перегрузка оператора [], переход к элементу массива по индексу
T& m_vector<T>::operator[](int index) {
    if(index < 0){
        std::ostringstream os;
        os << "incorrect index - " << index <<  std::endl;
        std::string s = os.str();
        throw MException(s);
    }
    if(index >= n){
        std::ostringstream os;
        os << "incorrect index - " << index << std::endl;
        std::string s = os.str();
        throw MException(s);
    }
    return data[index];
}


template <typename T>//перегрузка оператора [] const, переход к элементу массива по индексу
T& m_vector<T>::operator[](int index) const{
    return (*this)[index];
}

template <typename T>
void m_vector<T>::set_elem(int index, T& elem){
    (*this)[index] = elem;
}

template <typename T>
T& m_vector<T>::get_elem(int index){
    return (*this)[index];
}

template <typename T>//перегрузка оператора +=
m_vector<T>& m_vector<T>::operator +=(m_vector<T>& vect){
    for(size_t i = 0; i < MIN(n, vect.get_length()); i++){
        data[i] += vect[i];
    }
    return *this;
}

template <typename T>//пергрузка оператора -=
m_vector<T>& m_vector<T>::operator -=(m_vector<T>& vect){
    for(size_t i = 0; i < MIN(n, vect.get_length()); i++){
        data[i] -= vect[i];
    }
    return *this;
}

template <typename T>//перегрузка оператора *=
m_vector<T>& m_vector<T>::operator *=(T const& val){
    for(size_t i = 0; i < n; i++){
        data[i] *= val;
    }
    return *this;
}

template <typename T>//перегрузка оператора /=
m_vector<T>& m_vector<T>::operator /=(T const& val){
    if(val == (T)0){
        throw MException("division by 0!");
    }else{
        for(size_t i = 0; i < n; i++){
            data[i] /= val;
        }
    }
    return *this;
}

template<typename _T>//перегрузка оператора +
m_vector<_T> operator +(m_vector<_T>& v1, m_vector<_T>& v2){
    m_vector<_T> new_vector(v1);
    new_vector += v2;
    return new_vector;
}

template<typename _T>//перегрузка оператора -
m_vector<_T> operator -(m_vector<_T>& v1, m_vector<_T>& v2){
    m_vector<_T> new_vector(v1);
    new_vector -= v2;
    return new_vector;
}

template<typename _T>//перегрузка оператора *
m_vector<_T> operator *(m_vector<_T>& v1, _T& val){
    m_vector<_T> new_vector(v1);
    new_vector *= val;
    return new_vector;
}

template<typename _T>//перегрузка оператора /
m_vector<_T> operator /(m_vector<_T>& v1, _T& val){
    if(val == (_T)0){
        throw MException("division by 0!");
    }else{
        m_vector<_T> new_vector(v1);
        new_vector /= val;
        return new_vector;
    }
}

template<typename T>//
Iterator<T> m_vector<T>::iterator_begin(){
    return Iterator<T>(this, 0);
}

template<typename T>//
Iterator<T> m_vector<T>::iterator_end(){
    return Iterator<T>(this, n);
}


template<typename T>//просто конструктор итератора
Iterator<T>::Iterator(m_vector<T> &container_obj) : it{0}, container_obj{container_obj}{}

template<typename T>//конструктор итератора
Iterator<T>::Iterator(m_vector<T> *container_obj, size_t n) : it{n}, container_obj{*container_obj}{}

template<typename T>//
Iterator<T> Iterator<T>::next(){//this
    ++(*this);
    /*if(!this->is_end()){
        it++;
    }*/
    return *this;
}

template<typename T>//метод переносит it  в конец
bool Iterator<T>::is_end(){
    return it == (size_t)container_obj.get_length();
}

template<typename T>//
T Iterator<T>::value(){
    //return container_obj[it];
    return *(*this);
}

template<typename T>//прегрузка инкррмента
Iterator<T>& Iterator<T>::operator ++(){
    if(!this->is_end()){
        it++;
    }
    return *this;
}

template<typename T>//перегрузка разыменования
T& Iterator<T>::operator *(){
     return container_obj[it];
}

template<typename T>//перегрузка сравнивания
bool Iterator<T>::operator ==(Iterator<T> &b){
    return &container_obj == &b.container_obj && it == b.it;
}

template<typename T>//перегрузка !=
bool Iterator<T>::operator !=(Iterator<T> &b){
    return !(*this == b);
}
#endif // M_VECTOR_H //защита от повторнго включения
