#include<bits/stdc++.h>
#define rep(i,N) for(int i=0;i<N;i++)
#define rep2(i,N) for(int i=1;i<=N;i++)
using namespace std;

int RangedRand(int range_min, int range_max)
{
    int r=((double)rand() / RAND_MAX) * (range_max - range_min) + range_min;
    return r;
}
//  同じ文字列かどうか反転する
bool isSameStr(string str1,string str2){
    if(str1.size()!=str2.size())return false;

    int n=str1.size();
    rep(i,n){
        if(str1[i]!=str2[i])return false;
    }
    return true;
}
//  文字列間の違う文字の数を数える
int getDiffBetweenStrs(string str1,string str2){
    
    int diff=0;
    int n=str1.size();
    rep(i,n)if(str1[i]!=str2[i])diff++;

    return diff;
}
//  文字列の各桁を確立epsで反転する
void addErrorToString(string& str,double eps){
    int len=str.size();
    rep(i,len){
        double randomNum=RangedRand(0,100);
        if(randomNum<=eps*100){
            if(str[i]=='0')str[i]='1';
            else if(str[i]=='1')str[i]='0';
        }
    }
    return;
}
void printDebug(int index,string nowHk,string original_graph){
        cout<<"# minIndex "<<index<<endl;;
        cout<<"# nowHk          "<<nowHk<<endl;
        cout<<"# original_graph "<<original_graph<<endl;
        return;
}
//  UnionFindでグラフの構造を管理する
struct UnionFind {
    vector<int> par;

    UnionFind() { }
    UnionFind(int n) : par(n, -1) { }
    void init(int n) { par.assign(n, -1); }
    
    int root(int x) {
        if (par[x] < 0) return x;
        else return par[x] = root(par[x]);
    }
    
    bool issame(int x, int y) {
        return root(x) == root(y);
    }
    
    bool merge(int x, int y) {
        x = root(x); y = root(y);
        if (x == y) return false;
        if (par[x] > par[y]) swap(x, y); // merge technique
        par[x] += par[y];
        par[y] = x;
        return true;
    }
    
    int size(int x) {
        return -par[root(x)];
    }
};

#define debug 0
int main(){
    int M;
    double eps;
    cin>>M>>eps;
    int N=4;
    cout<<N<<endl;
    vector<vector<int>>graph(N);

    
    multimap<string,int>graphStr;
    string graphStrVec[M];
    vector<vector<int>> V(N);
    rep(i,M){
            //ランダムにグラフを作成
        bool connect[N+2][N+2]={};
        rep(k,i){
            int x=RangedRand(0,N-1);
            int y=RangedRand(0,N-1);
            if(x==y){
                continue;
            }
            connect[x][y]=true;
            //cout<<"rand ="<<RangedRand(0,N)<<endl;
        }
        string tmpStr="";
        for(int k=0;k<N;k++){
            for(int l=k+1;l<N;l++){
                if(connect[k][l]){
                    cout<<"1";
                    tmpStr.push_back('1');
                    v[k].push_back(l);
                    v[l].push_back(k);
                }else{
                    cout<<"0";
                    tmpStr.push_back('0');
                }
            }
        }
        //graphStr.insert(make_pair(tmpStr,i));
        graphStrVec[i]=tmpStr;
        cout<<endl;
    }

    //ランダムなエラー率を反映する
    rep(i,M){
        addErrorToString(graphStrVec[i],eps);
    }
    //  連結数を数える
    int groupSize[N]={};
    rep(i,N)groupSize[i]=-1;
    rep(i,N){
        for(auto next:v[i]){

        }
    }

    //  グラフの辺の数
    int graphVNum[M]={};
    rep(i,M)graphVNum[i]=0;
   
    int p=(M*(M-1))/2;
    rep(i,M){
        rep(k,p){
            if(graphStrVec[i][k]=='1')graphVNum[i]++;
        }
        #if debug
        cout<<"# index "<<i<<" num of edge "<<graphVNum[i]<<endl;
        #endif 
    }

    rep(i,100){
        string nowHk;
        cin>>nowHk;
        int index=0;
#if 0
        //距離が最も近いものを探す
        rep(k,M){
            int nowDiff=getDiffBetweenStrs(nowHk,graphStrVec[k]);
            if(min>nowDiff){
                min=nowDiff;
                index=k;
            }
        }
        
#elif 0
        //完全に一致するものを探す
        rep(k,M){
            if(isSameStr(nowHk,graphStrVec[k])){
                index=k;
                break;
            }
        }
#else
        //  辺の数を数える
        int len=nowHk.size();
        int hLoadNum=0;
        rep(k,len)if(nowHk[k]=='1')hLoadNum++; 

        index=min(hLoadNum,M-1);
#endif

#if debug
        printDebug(index,nowHk,graphStrVec[index]);
#endif
        cout<<index<<endl;

    }
    
    return 0;
}