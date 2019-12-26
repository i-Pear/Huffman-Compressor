#include <bits/stdc++.h>

using namespace std;

template<typename T>
class PriorityQueue{

private:

    static const int INIT_CAPACITY=8;
    int capacity;
    int __size;

    bool (*lessCompare)(const T &,const T &);

    T*data; // Index starts from 1

    static bool defaultCompare(const T &a,const T &b){
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

    PriorityQueue(bool(*cmp)(const T &,const T &)) : __size(0),capacity(INIT_CAPACITY){
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

    PriorityQueue &operator>>(T &ele){
        ele=top();
        pop();
        return *this;
    }

    PriorityQueue &operator<<(const T &ele){
        insert(ele);
        return *this;
    }

}; // 优先队列 模板类


class HuffmanAutoMachineCreator{

private:

    struct node{
        char content;
        int zero;
        int one;
    };
    vector<node> dict;

    class PriorQueueNode{

    public:

        int weight;
        int id;

        PriorQueueNode(int id,int weight) : id(id),weight(weight){} // 使用编号和权重初始化
        PriorQueueNode(){}

        bool operator<(const PriorQueueNode &b) const{
            return weight<b.weight;
        }

    }; // 创建哈弗曼树时，用于优先队列节点

    unsigned char*compressed;
    int compressedLength;
    unsigned char*data;
    int dataLength;
    int pos;
    unsigned int bitPos;
    int head;

public:

    HuffmanAutoMachineCreator(char*data,int length){
        this->dataLength=length;
        memcpy(this->compressed,data,length*sizeof(char));
    }

    void createHuffman(){
        int count[256]={0};
        for(int i=0;i<dataLength;i++){
            count[data[i]]++;
        }
        PriorityQueue<PriorQueueNode> pq;
        for(int i=0;i<256;i++){
            if(count[i]){
                dict.push_back({0,0,0});
                pq.insert({pq.size()-1,count[i]});
            }
        }
        PriorQueueNode a,b;
        while(true){
            if(pq.size()==1){
                head=pq.top().id;
                pq.pop();
                break;
            }else{
                pq>>a>>b;
                dict.push_back({0,a.id,b.id});
                pq.insert({pq.size()-1,a.weight+b.weight});
            }
        }
    }

    ~HuffmanAutoMachineCreator(){
        delete data;
        delete compressed;
    }

};




inline bool nextBit(){
    if(bitPos&8U){
        bitPos=0;
        ++pos;
    }
    return (compressed[pos])&(1U<<bitPos);
}


int main(){

}