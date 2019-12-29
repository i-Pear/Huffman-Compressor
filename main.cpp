#include <bits/stdc++.h>

using namespace std;
typedef unsigned char uchar;

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

    explicit PriorityQueue(bool(*cmp)(const T &,const T &)) : __size(0),capacity(INIT_CAPACITY){
        data=new T[capacity];
        lessCompare=cmp;
}

    void insert(const T &val){
        if(__size+1==capacity)enlarge();
        data[++__size]=val;
        shiftUp(__size);
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


class HuffmanEncoder{

public:

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

    list<uchar> compressed;

    unsigned char*data;
    int dataLength;
    unsigned int bitPos;
    list<bool> encoding[256];
    int head; // 哈夫曼树头结点

    // Should write to file:
    // head / dataLength / dict / compressed


    HuffmanEncoder(uchar*data,int length){
        this->dataLength=length;
        this->data=new uchar[length];
        memcpy(this->data,data,length*sizeof(uchar));
        bitPos=8;
    }

    void calculateEncoding(int n){
        static vector<bool> st;
        if(dict[n].content){
            for(bool i:st){
                encoding[dict[n].content].push_back(i);
            }
            return;
        }else{
            st.push_back(false);
            calculateEncoding(dict[n].zero);
            st.pop_back();

            st.push_back(true);
            calculateEncoding(dict[n].one);
            st.pop_back();
        }
    }

    void createHuffman(){

        // Can init head
        int count[256]={0};
        for(int i=0;i<dataLength;i++){
            count[data[i]]++;
        }
        PriorityQueue<PriorQueueNode> pq;
        for(int i=0;i<256;i++){
            if(count[i]){
                dict.push_back({(char)i,0,0});
                pq.insert({int(dict.size()-1),count[i]});
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
                dict.back().zero=a.id;
                dict.back().one=b.id;
                pq.insert({int(dict.size()-1),a.weight+b.weight});
            }
        }

        calculateEncoding(head);

        for(int i=0;i<dataLength;i++){
            for(auto&c:encoding[data[i]]){
                writeBit(c);
            }
        }

    }

    inline void writeBit(bool t){
        if(bitPos==8){
            compressed.push_back(0);
            bitPos=0;
        }
        if(t){
            compressed.back()|=(1U<<bitPos);
        }
        bitPos++;
    }

    void writeToFile(const string& path){
        ofstream ofs(path,ios::binary|ios::trunc|ios::out);

        ofs.write((char*)&head,sizeof(head));
        ofs.write((char*)&dataLength,sizeof(dataLength));

        int dictSize=dict.size();
        ofs.write((char*)&dictSize,sizeof(dictSize));
        for(auto&i:dict){
            ofs.write(&i.content,sizeof(i.content));
            ofs.write((char*)&i.zero,sizeof(i.zero));
            ofs.write((char*)&i.one,sizeof(i.one));
        }

        int length=compressed.size();
        ofs.write((char*)&length,sizeof(length));
        for(auto&i:compressed){
            ofs.write((char*)&i,sizeof(i));
        }

        ofs.close();
    }

    ~HuffmanEncoder(){
        delete[] data;
    }

};


class HuffmanDecoder{

public:

    struct node{
        char content;
        int zero;
        int one;
    };
    vector<node> dict;

    list<uchar> compressed;
    unsigned char*data;
    int dataLength;
    list<bool> encoding[256];
    int head; // 哈夫曼树头结点
    int compressedLength;


    HuffmanDecoder(){}

    void readFromFile(const string& path){
        ifstream ifs(path,ios::binary|ios::in);

        ifs.read((char*)&head,sizeof(head));
        ifs.read((char*)&dataLength,sizeof(dataLength));
        this->data=new uchar[dataLength];

        int dictSize;
        ifs.read((char*)&dictSize,sizeof(dictSize));
        char content;
        int zero,one;
        for(int i=0;i<dictSize;i++){
            ifs.read(&content,sizeof(content));
            ifs.read((char*)&zero,sizeof(zero));
            ifs.read((char*)&one,sizeof(one));
            dict.push_back({content,zero,one});
        }

        int length;
        ifs.read((char*)&length,sizeof(length));
        compressedLength=length;
        char temp;
        for(int i=0;i<length;i++){
            ifs.read((char*)&temp,sizeof(temp));
            compressed.push_back(temp);
        }

        ifs.close();

        decode();
    }

    void decode(){

        int bitPos=0;
        int status=head;
        auto iter=compressed.begin();
        int dataP=0;

        bool cnt;
        while(dataP<dataLength){

            cnt=(*iter)&(1U<<bitPos);
            bitPos++;
            if(bitPos==8){
                bitPos=0;
                iter++;
            }

            // Jump
            if(cnt){
                status=dict[status].one;
            }else{
                status=dict[status].zero;
            }

            // Check if it is destination
            if(dict[status].content){
                data[dataP++]=dict[status].content;
                status=head;
            }
        }

    }

    ~HuffmanDecoder(){
        delete[] data;
    }

};



int main(){

    char* str="123456";
    HuffmanEncoder encoder((uchar*)str,21);
    encoder.createHuffman();
    encoder.writeToFile("D:\\1.txt");

    HuffmanDecoder decoder;
    decoder.readFromFile("D:\\1.txt");

    printf("Compress rate: %.3lf%%",1.0*decoder.compressedLength/decoder.dataLength*100);

}