#include<bits/stdc++.h>
using namespace std;

vector<int> tempimg()
{
    int n = 500;
    vector<int> img(n);
    srand(time(0));
    for(int i=0;i<500;++i)
    {
        img[i] = rand()%256;
    }
    
    return img;
}

struct minheapNode{

    int pixelVal;
    int frequency;

    minheapNode *left,*right;

};

minheapNode* createNode(int pixelVal, int frequency)
{
    minheapNode *temp = new minheapNode;

    temp->pixelVal = pixelVal;
    temp->frequency = frequency;

    temp->right = NULL;
    temp->left  = NULL;

    return temp;
}

vector<int> countFrequency(vector<vector<int>>&img, int r, int c)
{
    vector<int>frequency(256,0);
    
    for(int i=0;i<r;++i)
    {
        for(int j=0;j<c;++j)
        {
            frequency[img[i][j]]++;
        }
    }
    return frequency;
}

void minheapify(vector<minheapNode*>&minheap,int idx)
{
    int leftidx = 2*idx+1;
    int rightidx = 2*idx+2;

    int minFrequency = minheap[idx]->frequency;;
    int minidx = idx;
    
    if((int)minheap.size()>leftidx)
    {
        int leftFreqency = minheap[leftidx]->frequency;
        
        if(minFrequency>leftFreqency)
        {
            minFrequency = leftFreqency;
            minidx = leftidx;
        }

    }

    if((int)minheap.size()>rightidx)
    {
        int rightFreqency = minheap[rightidx]->frequency;
        
        if(minFrequency>rightFreqency)
        {
            minFrequency = rightFreqency;
            minidx = rightidx;
        }

    }

    if(idx!=minidx)
    {
        swap(minheap[idx],minheap[minidx]);
        minheapify(minheap,minidx);
    }

}

void buildMinheap(vector<minheapNode*>&minheap)
{
    int sz = minheap.size();
    for(int i = sz/2;i>=0;--i)
    {
        minheapify(minheap,i);
    }
}

minheapNode* extractMin(vector<minheapNode*>&minheap)
{
    minheapNode *minNode = minheap[0];
    int sz = minheap.size();
    minheap[0] = minheap[sz-1];
    minheap.pop_back();
    minheapify(minheap,0);

    return minNode;
}

void insertNode(vector<minheapNode*>&minheap,minheapNode* Node)
{
    minheap.push_back(Node);
    int curidx = minheap.size()-1;
    int parentidx = curidx/2;
    if(curidx%2==0 && curidx>0)
    {
        parentidx--;
    }
    int frequencyParent = minheap[parentidx]->frequency; 
    int frequencyCur = minheap[curidx]->frequency;
    while(curidx>0 && frequencyCur<frequencyParent)
    {
        swap(minheap[parentidx],minheap[curidx]);
        curidx = parentidx;
        parentidx = curidx/2;
        if(curidx%2==0 && curidx>0)
        {
            parentidx--;
        }
        frequencyParent = minheap[parentidx]->frequency; 
        frequencyCur = minheap[curidx]->frequency;

    }

}

void buildHuffmanTree(vector<minheapNode*>&minheap)
{
    minheapNode *rightNode = new minheapNode;
    minheapNode *leftNode = new minheapNode;

    rightNode = extractMin(minheap);
    leftNode = extractMin(minheap);

    int leftFrequency = leftNode->frequency;
    int rightFrequency = rightNode->frequency;
    int sum = leftFrequency+rightFrequency;

    minheapNode *newNode = createNode(256,sum);
    newNode->right = rightNode;
    newNode->left = leftNode;

    insertNode(minheap,newNode);

}

void traverseTree(minheapNode *Node, string* code, string curCode)
{
    if(Node->right==NULL && Node->left==NULL)
    {
        code[Node->pixelVal] = curCode;
        return;
    }
    string temp = curCode;
    curCode = temp+'0';
    traverseTree(Node->left,code,curCode);
    curCode = temp+'1';
    traverseTree(Node->right,code,curCode);

}

void checkerFreqLen(vector<int>&frequencyArr,string *code)
{
    vector<pair<int,int>>v;
    map<int,int>mn,mx;
    
    for(int i=0;i<256;++i)
    {
        if(frequencyArr[i]!=0)
        {
            v.push_back({frequencyArr[i],code[i].length()});
            if(mn[frequencyArr[i]]==0)
            {
                mn[frequencyArr[i]] = code[i].length();
                mx[frequencyArr[i]] = code[i].length();
            }
            else
            {
                mn[frequencyArr[i]] = min(mn[frequencyArr[i]],(int)code[i].length());
                mx[frequencyArr[i]] = max(mx[frequencyArr[i]],(int)code[i].length());
            }
        }
    }
    for(auto it:mn)
    {
        cout<<it.first<<" "<<mn[it.first]<<" "<<mx[it.first]<<endl;
    }
    
}

void checkerPrefix(string *code)
{
    for(int i=0;i<256;++i)
    {
        int len = code[i].length();
        for(int j=0;j<256;++j)
        {
            if(i!=j && code[j].length()>=len)
            {
                string s = code[j].substr(0,len);
                if(s==code[i] && s!="")
                {
                    cout<<s<<endl;
                    cout<<code[i]<<endl;
                    cout<<"Failed\n";
                    return;
                }  
            }  
        }
    }
    cout<<"Success!!\n";
}

void printHuffmanCode(string *code,vector<vector<int>>&img, int r, int c)
{
    for(int i=0;i<r;++i)
    {
        for(int j=0;j<c;++j)
        {
            cout<<code[img[i][j]];
        }
        cout<<endl;
    }
}

int main()
{
    string code[256];

    ifstream Image("MyFile.txt");
    int r,c;
    Image >> r >>c;
    cout<<r<<" "<<c<<endl;
    vector<vector<int>>img;
    img.resize(r);
    for(int i=0;i<r;++i)
    {
        img[i].resize(c);
    }

    for(int i=0;i<r;++i)
    {
        for(int j=0;j<c;++j)
        {
            Image >> img[i][j];
        }
    }

    for(int i=0;i<r;++i)
    {
        for(int j=0;j<c;++j)
        {
            cout << img[i][j] <<" ";
        }
        cout<<endl;
    }   

    vector<int>frequencyArr = countFrequency(img,r,c);
    vector<minheapNode*>minheap;

    for(int i=0;i<256;++i)
    {
        if(frequencyArr[i]!=0)
        {
            minheap.push_back(createNode(i,frequencyArr[i]));
        }
    }

    buildMinheap(minheap);

    while(minheap.size()>1)
        buildHuffmanTree(minheap);

    traverseTree(minheap[0],code,"");
    
    // checkerFreqLen(frequencyArr,code);
    // checkerPrefix(code);
    printHuffmanCode(code,img,r,c);

}