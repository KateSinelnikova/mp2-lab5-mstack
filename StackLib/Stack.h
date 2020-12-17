#ifndef _STACK_
#define _STACK_
#include <iostream>
#include <fstream>
using namespace std;

template <class T>
class TStack
{
public:
    int size; // размер стека
    T* data; // данные стека
    int top; // указатель на вершину стека
    bool flagBelongs; // флаг пренадлежит ли стеку значение

    TStack(int size = 1, bool _fB = true);
    TStack(TStack<T>& _v);
    ~TStack();

    void Push(T d);
    void SetData(T* _x, int _size, int _top);
    void Resize(int _size);
    T Pop();

    int IsEmpty(void) const; 
    int IsFull(void) const; 
    int GetSize();
    int GetCount();
   
    inline int MinElem(); 
    inline int MaxElem(); 
    inline void WriteFile(); 
    inline TStack<T>& ReadFile();

    TStack<T>& operator =(TStack<T>& _v);
    template <class T1>
    friend ostream& operator<< (ostream& ostr, const TStack<T1>& A);
    template <class T1>
    friend istream& operator >> (istream& istr, TStack<T1>& A);
};


template<class T>
inline TStack<T>::TStack(int size, bool _fB)
{
    if (size > 0)
    {
        this->size = size;
        this->flagBelongs = _fB;
        if (flagBelongs)
        {
            data = new T[size];
            for (int i = 0; i < size; i++)
                data[i] = 0;
        }
        this->top = 0;
    }
    else throw "Error";
}

template <class T>
TStack<T>::TStack(TStack<T>& _v)
{
    size = _v.size;
    top = _v.top;
    flagBelongs = _v.flagBelongs;

    if (flagBelongs)
    {
        data = new T[size];
        for (int i = 0; i < size; i++)
            data[i] = _v.data[i];
    }
    else data = _v.data;
}

template <class T>
TStack<T>::~TStack()
{
    if (flagBelongs)
        if (data != NULL)
        {
            delete[] data;
            data = NULL;
        }
}

template<class T>
inline void TStack<T>::Push(T d)
{
    if (this->IsFull()) throw "Error";

    data[top] = d;
    top++;
}

template<class T>
inline void TStack<T>::SetData(T* _x, int _size, int _top)
{
    if (flagBelongs)
    {
        if (data != NULL)
            delete[] data;

        this->size = _size;
        flagBelongs = false;
        data = _x;
        top = _top;
    }
}

template<class T>
inline void TStack<T>::Resize(int _size)
{
    if (_size <= 0) throw "Error";

    if (data == NULL)
    {
        delete[] data;
        data = new T[_size];
    }
    else
    {
        T* temp = new T[_size];

        if(_size > this->GetCount())
            for (int i = 0; i < this->GetCount(); i++)
                temp[i] = Pop();
        else 
            for (int i = 0; i < _size; i++)
                temp[i] = Pop();

        delete[] data;

        data = new T[_size];

        for (int i = 0; i < 1; i++)
            data[i] = temp[i];
    }
}

template<class T>
inline T TStack<T>::Pop()
{
    if (this->IsEmpty())  throw "Error";

    T d = data[top - 1];
    top--;
    return d;
}

template<class T>
inline int TStack<T>::IsEmpty(void) const
{
    return top == 0;
}

template<class T>
inline int TStack<T>::IsFull(void) const
{
    return top - 1 > size;
}

template <class T>
int TStack<T>::GetSize()
{
    return size;
}
template<class T>
inline int TStack<T>::GetCount()
{
    return top;
}

template<typename T>
inline int TStack<T>::MaxElem()
{
    T res = data[0];

    for (int i = 1; i < size; i++)
        if (data[i] > res)
            res = data[i];
    return res;
}

template<typename T>
inline int TStack<T>::MinElem()
{
    T res = data[0];

    for (int i = 1; i < size; i++)
        if (data[i] < res)
            res = data[i];
    return res;
}

template<typename T>
inline void TStack<T>::WriteFile()
{
    fstream file;
    file.open("Data.txt");
    if (!file.is_open())
        throw "Cant open such file";
    file << this->size << " " << this->top << "\n" << *this;
    file.close();
}

template<class T>
inline TStack<T> &TStack<T>::ReadFile()
{
    std::ifstream file;
    file.open("Data.txt");
    if (!file.is_open())
        throw "Cant open such file";
    int size;
    file >> size;
    TStack* stack = new TStack(size);
    file >> stack->top;
    file >> *stack;
    file.close();
    return *stack;
}

template <class T>
TStack<T>& TStack<T>::operator=(TStack<T>& _v)
{
    if (this == &_v)
        return *this;

    size = _v.size;
    flagBelongs = _v.flagBelongs;

    if (flagBelongs)
    {
        if (data != NULL)
            delete[] data;

        this->data = new T[size];

        for (int i = 0; i < size; i++)
            data[i] = _v.data[i];
    }
    else data = _v.data;

    this->top = _v.top;
    return *this;
}


template <class T>
ostream& operator<< (ostream& ostr, const TStack<T>& A)
{
    for (int i = 0; i < A.top; i++)
        ostr << A.data[i] << endl;

    return ostr;
}

template <class T>
istream& operator >> (istream& istr, TStack<T>& A)
{
    for (int i = 0; i <= A.top; ++i) {
        T data;
        istr >> data;
        A.data[i] = T(data);
    }
    return istr;
}
#endif 
