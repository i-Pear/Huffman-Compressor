#include "HuffmanDecoder.h"


long HuffmanEncoder::getFileLength(const string &path){
    ifstream ifs(path,ios::binary);
    ifs.seekg(0,ios::end);                       // 设置指针到文件流尾部
    streampos ps=ifs.tellg();                  // 指针距离文件头部的距离，即为文件流大小
    int len=ps;
    ifs.close();
    return len;
}


HuffmanEncoder::HuffmanEncoder(const string &path){

    int fileLength=getFileLength(path);
    dataLength=fileLength;
    data=new uchar[dataLength];
    ifstream ifs(path,ios::binary);
    ifs.read((char*)data,fileLength);
    ifs.close();

    bitPos=8;
}

void HuffmanEncoder::calculateEncoding(int n){
    static vector<bool> st;
    if(dict[n].isLeaf){
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

void HuffmanEncoder::createHuffman(){

    // Can init head
    int count[256]={0};
    for(int i=0;i<dataLength;i++){
        count[data[i]]++;
    }
    PriorityQueue<PriorQueueNode> pq;
    for(int i=0;i<256;i++){
        if(count[i]){
            dict.push_back({true,(unsigned char)i,0,0});
            pq.insert({int(dict.size()-1),count[i]});
        }
    }

    if(pq.size()!=1){
        PriorQueueNode a,b;
        while(true){
            if(pq.size()==1){
                head=pq.top().id;
                pq.pop();
                break;
            }else{
                pq>>a>>b;
                dict.push_back({false,0,a.id,b.id});
                dict.back().zero=a.id;
                dict.back().one=b.id;
                pq.insert({int(dict.size()-1),a.weight+b.weight});
            }
        }
        calculateEncoding(head);
    }else{
        encoding[dict[0].content].push_back(true);
        dict[0].one=1;
        dict.push_back({false,dict[0].content,0,0});
        head=0;
    }

    for(int i=0;i<dataLength;i++){
        for(auto &c:encoding[data[i]]){
            writeBit(c);
        }
    }

}

inline void HuffmanEncoder::writeBit(bool t){
    if(bitPos==8){
        compressed.push_back(0);
        bitPos=0;
    }
    if(t){
        compressed.back()|=(1U<<bitPos);
    }
    bitPos++;
}

void HuffmanEncoder::writeToFile(const string &path){
    ofstream ofs(path,ios::binary|ios::trunc|ios::out);

    ofs.write((char*)identifier,sizeof(identifier));

    ofs.write((char*)&head,sizeof(head));
    ofs.write((char*)&dataLength,sizeof(dataLength));

    int dictSize=dict.size();
    ofs.write((char*)&dictSize,sizeof(dictSize));
    for(auto &i:dict){
        ofs.write((char*)&i.isLeaf,sizeof(i.isLeaf));
        ofs.write((char*)&i.content,sizeof(i.content));
        ofs.write((char*)&i.zero,sizeof(i.zero));
        ofs.write((char*)&i.one,sizeof(i.one));
    }

    int length=compressed.size();
    ofs.write((char*)&length,sizeof(length));
    for(auto &i:compressed){
        ofs.write((char*)&i,sizeof(i));
    }

    ofs.close();
}

HuffmanEncoder::~HuffmanEncoder(){
    delete[] data;
}

