#include <bits/stdc++.h>

using namespace std;

template<typename T>
class PriorityQueue{

private:

    static const int INIT_CAPACITY=8;
    int capacity;
    int __size;
    bool(*lessCompare)(const T&,const T&);
    T*data; // Index starts from 1

    static bool defaultCompare(const T& a,const T& b){
        return a<b;
    }

    void enlarge(){
        capacity*=2;
        data=(T*)realloc(data,capacity*sizeof(T));
    }

    void shiftUp(int i){
        if(i==1)return;
        while(i!=1){
            if(lessCompare(data[i],data[i/2])){
                swap(data[i],data[i/2]);
                i/=2;
            }else{
                return;
            }
        }
    }

    void shiftDown(int i){

        int smallestIndex=i;

        while(i*2<=__size){

            if(lessCompare(data[i*2],data[smallestIndex])){ // If exist left son
                smallestIndex=i*2;
            }

            if(i*2+1<=__size){// If exist right son
                if(lessCompare(data[i*2+1],data[smallestIndex])){
                    smallestIndex=i*2+1;
                }
            }

            if(smallestIndex!=i){
                swap(data[i],data[smallestIndex]);
                i=smallestIndex;
            }else{
                return;
            }

        }

    }

public:

    PriorityQueue() : __size(0),capacity(INIT_CAPACITY){
        data=new T[capacity];
        lessCompare=defaultCompare;
    }

    PriorityQueue(bool(*cmp)(const T&,const T&)) : __size(0),capacity(INIT_CAPACITY){
        data=new T[capacity];
        lessCompare=cmp;
    }

    void insert(const T &val){
        if(__size+1==capacity)enlarge();
        data[__size++]=val;
        shiftUp(__size-1);
    }

    const T &top() const{
        return data[1];
    }

    void pop(){
        assert(__size>0);
        data[1]=data[__size--];
        shiftDown(1);
    }

    bool empty(){
        return __size==0;
    }

    int size(){
        return __size;
    }

    PriorityQueue & operator >> (T& ele){
        ele=top();
        pop();
        return *this;
    }

    PriorityQueue& operator<<(const T& ele){
        insert(ele);
        return *this;
    }

};

namespace HuffmanCompressor{

    template<typename T>
    class HuffmanTreeNode{

        int weight;
        T* data;
        HuffmanTreeNode* l,r;

        HuffmanTreeNode(const T* data,int weight):weight(weight),data(data),l(nullptr),r(nullptr){} // 使用名称和权重初始化

        HuffmanTreeNode(HuffmanTreeNode& a,HuffmanTreeNode& b):weight(a.weight+b.weight),data(nullptr),l(a),r(b){} // 将两个节点合并为一个

        bool operator < (const HuffmanTreeNode& b)const{
            return weight<b.weight;
        }

        HuffmanTreeNode operator + (const HuffmanTreeNode& b){
            return {*this};
        }

    };

    class HuffmanTree{

    };

}

int main(){

}