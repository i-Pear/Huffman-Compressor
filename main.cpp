#include <bits/stdc++.h>

using namespace std;

template<typename T>
class PriorityQueue{

public:
    static const int INIT_CAPACITY=8;
    typedef T* ptr;
    int capacity;
    int size;
    ptr* data; // Index starts from 1

    PriorityQueue() : size(0),capacity(INIT_CAPACITY){
        data=new T[capacity];
    }

    void enlarge(){
        capacity*=2;
        data=(T*)realloc(data,capacity*sizeof(T));
    }

    void shiftUp(int i){
        if(i==1)return;
        while(i!=1){
            if(data[i]<data[i/2]){
                swap(data[i],data[i/2]);
                i/=2;
            }else{
                return;
            }
        }
    }

    void shiftDown(int i){

        int smallestIndex=i;

        while(i*2<=size){

            if(data[smallestIndex]>data[i*2]){ // If exist left son
                smallestIndex=i*2;
            }

            if(i*2+1<=size){// If exist right son
                if(data[smallestIndex]>data[i*2+1]){
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

    void insert(const T &val){
        if(size+1==capacity)enlarge();
        data[size++]=val;
        shiftUp(size-1);
    }

    const T &top() const{
        return data[1];
    }

    void pop(){
        assert(size>0);
        data[1]=data[size--];
        shiftDown(1);
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

namespace Compressor{

    template<typename T>
    class HuffmanTreeNode{

        int weight;
        T* data;
        HuffmanTreeNode* l,r;

        HuffmanTreeNode(const T* data,int weight):weight(weight),data(data),l(nullptr),r(nullptr){}
        HuffmanTreeNode(HuffmanTreeNode& a,HuffmanTreeNode& b):weight(a.weight+b.weight),data(nullptr),l(a),r(b){}

        bool operator < (const HuffmanTreeNode& b)const{
            return weight<b.weight;
        }

        HuffmanTreeNode operator + (const HuffmanTreeNode& b){
            return {*this,b};
        }

    };

    class HuffmanTree{

    };

}

int main(){

}