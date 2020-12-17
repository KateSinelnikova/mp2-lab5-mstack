#ifndef _MULTISTACK_
#define _MULTISTACK_

#include <iostream>
#include <fstream>
#include <math.h>
#include "Stack.h"
using namespace std;

template <class T>
class TMultiStack
{
public:
    int size;
    int stackCount;
    TStack<T>* stacks;
    T** oldData;
    T* data;

    TMultiStack(int size = 1, int stackCount = 1);
    TMultiStack(TMultiStack<T>& _v);
    ~TMultiStack();

    void StackRelocation(int i);
    inline int MinStack();
    inline void WriteFile();
    inline TMultiStack<T> ReadFile();

    void Push(T d, int i); 
    T Pop(int i);
    bool IsEmpty(int i) const; 
    bool IsFull(int i) const; 
    int GetSize();
    void Resize(int size = 1, int stackCount = 1);

    TMultiStack<T>& operator =(TMultiStack<T>& _v);
    template <class T1>
    friend ostream& operator<< (ostream& ostr, const TMultiStack<T1>& A);
    template <class T1>
    friend istream& operator >> (istream& istr, TMultiStack<T1>& A);
};

template<class T>
inline TMultiStack<T>::TMultiStack(int size, int _stackCount)
{
    if ((size > 0) && (_stackCount > 0))
    {
        this->size = size;
        this->stackCount = _stackCount;

        data = new T[size];
        for (int i = 0; i < size; i++)
            data[i] = 0;

        int count = int(floor(double(size) / stackCount));
        int* sizes = new int[this->stackCount];

        for (int i = 0; i < (stackCount - 1); i++)
            sizes[i] = count;

        sizes[stackCount - 1] = size - (count * (stackCount - 1));
        oldData = new T * [stackCount];
        this->stacks = new TStack<T>[stackCount];
        int k = 0;

        for (int i = 0; i < stackCount; i++)
        {
            this->stacks[i].SetData(&(data[k]), sizes[i], 0);
            this->oldData[i] = &(data[k]);
            k = k + sizes[i];
        }
    }
    else throw "Error";
}

template <class T>
TMultiStack<T>::TMultiStack(TMultiStack<T>& _v)
{
    size = _v.size;
    stackCount = _v.stackCount;

    data = new T[size];
    for (int i = 0; i < size; i++)
        data[i] = _v.data[i];

    stacks = new TStack<T>[stackCount];
    for (int i = 0; i < stackCount; i++)
        this->stacks[i].SetData(_v.stacks[i].data, _v.stacks[i].GetSize(), _v.stacks[i].GetCount());

    oldData = _v.oldData;
}

template <class T>
TMultiStack<T>::~TMultiStack()
{
    if (data == NULL)
    {
        delete[] data;
        data = NULL;
    }

    if (stacks == NULL)
    {
        delete[] stacks;
        stacks = NULL;
    }
}

template<class T>
inline void TMultiStack<T>::StackRelocation(int index)
{
    int freeSize = 0;
    for (int i = 0; i < stackCount; i++)
        freeSize += stacks[i].GetSize() - stacks[i].GetCount();

    if (freeSize == 0) throw "Error";

    int count = int(floor(double(freeSize) / stackCount));
    int* sizes = new int[this->stackCount];

    for (int i = 0; i < (stackCount - 1); i++)
        sizes[i] = stacks[i].GetCount() + count;

    int c = stacks[stackCount - 1].GetCount();
    sizes[this->stackCount - 1] = c + (freeSize - (count * (this->stackCount - 1)));

    T** newData = new T * [stackCount];
    int k = 0;

    for (int i = 0; i < stackCount; i++)
    {
        newData[i] = &(data[k]);
        k = k + sizes[i];
    }


    for (int i = 0; i < stackCount; i++)
    {
        if (newData[i] == oldData[i])
        {
            stacks[i].SetData(newData[i], sizes[i], stacks[i].GetCount());
        }
        else if (newData[i] < oldData[i])
        {
            for (int j = 0; j < stacks[i].GetCount(); j++)
            {
                newData[i][j] = oldData[i][j];
            }
            stacks[i].SetData(newData[i], sizes[i], stacks[i].GetCount());
        }
        else if (newData[i] > oldData[i])
        {
            int k = i;
            for (; k < stackCount; ++k)
            {
                if (newData[k] > oldData[k]) continue;
                else break;
            }
            k--;
            for (int s = k; s >= i; --s)
            {
                for (int j = stacks[s].GetCount() - 1; j >= 0; j--)
                    newData[s][j] = oldData[s][j];

                stacks[s].SetData(newData[s], sizes[s], stacks[s].GetCount());
            }

        }
    }

    T** buf = oldData;
    oldData = newData;
    delete[] buf;
    delete[] sizes;
}

template<typename T>
inline int TMultiStack<T>::MinStack()
{
    int i = 0;
    if (this->stacks[0].is_empty())
        return i;
    int iStack = stacks[0].GetCount();
    for (int j = 0; j < this->iStack; j++) {
        if (stacks[j].GetCount() < iStack) i = j;
        if (stacks[j].GetCount()) return j;
    }
    return i;
}

template<typename T>
inline void TMultiStack<T>::WriteFile()
{
    ofstream f;
    f.open("Data.txt");
    if (!f.is_open()) throw "notOpen";

    f << size << " " << stackCount << "\n" << *this;
    f.close();
}

template<class T>
inline TMultiStack<T> TMultiStack<T>::ReadFile()
{
    ifstream file;
    file.open("Data.txt");
    if (!file.is_open()) throw "Cant open uch file";
    TMultiStack* stack = new TMultiStack(1,1);
    file >> stack->size;
    file >> stack->stackCount;
    for (int i = 0; i < stackCount; i++)
        file >> stacks[i];
    file.close();
    return *stack;
}

template<class T>
inline void TMultiStack<T>::Push(T d, int i)
{
    if (i < 0 || i >= stackCount) throw "Error";

    if (stacks[i].IsFull())
        StackRelocation(i);

    stacks[i].Push(d);
}

template<class T>
inline T TMultiStack<T>::Pop(int i)
{
    if (i < 0 || i > stackCount) throw "Error";

    if (stacks[i].IsEmpty()) throw "Error mem";

    return stacks[i].Pop();
}

template<class T>
inline bool TMultiStack<T>::IsEmpty(int i) const
{
    if (i < 0 || i > stackCount)  throw "Error";

    return stacks[i].IsEmpty();
}

template<class T>
inline bool TMultiStack<T>::IsFull(int i) const
{
    if (i < 0 || i > stackCount) throw "Error";

    return stacks[i].IsFull();
}

template <class T>
int TMultiStack<T>::GetSize()
{
    return size;
}

template<class T>
inline void TMultiStack<T>::Resize(int size, int stackCount)
{
    stacks[stackCount].Resize(size);
}

template <class T>
TMultiStack<T>& TMultiStack<T>::operator =(TMultiStack<T>& _v)
{
    if (this == &_v) return *this;

    this->size = _v.size;
    if (data != NULL)
        delete[] data;

    if (stacks != NULL)
        delete[] stacks;

    data = new T[size];
    for (int i = 0; i < size; i++)
        data[i] = _v.data[i];

    stacks = new TStack<T>[stackCount];
    for (int i = 0; i < stackCount; i++)
        stacks[i] = _v.stacks[i];

    return *this;
}

template <class T1>
ostream& operator<< (ostream& ostr, const TMultiStack<T1>& A) {
    for (int i = 0; i < A.stackCount; i++)
        ostr << (A.stacks[i]) << endl;
    return ostr;
}

template <class T1>
istream& operator >> (istream& istr, TMultiStack<T1>& A) {
    int size = 0;
    istr >> size;
    int stCount = 0;
    istr >> stCount;

    A.Resize(size, stCount);

    for (int i = 0; i < A.stackCount; i++)
        istr >> A.stacks[i];
    return istr;
}

#endif 
