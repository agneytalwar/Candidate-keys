#include<bits/stdc++.h>
using namespace std;
int K;
int countbits(int n){
    int ans=0;
    while(n!=0){
        if(n%2!=0){
            ans++;
        }
        n=n>>1;
    }
    return ans;
}
bool compare(int c1,int c2){
    int b1=countbits(c1);
    int b2=countbits(c2);
    if(b1!=b2){
        return b1<b2;
    }
    else{
        for(int x=0;x<K;x++){
            int a1=(c1&(1<<x));
            int a2=(c2&(1<<x));
            if(a1==a2){
                continue;
            }
            else if(a1<a2){
                return false;
            }
            else return true;
        }
        return true;
    }
}
int main(){
    //std::ifstream in("input1.txt");
    //std::streambuf *cinbuf = std::cin.rdbuf(); //save old buf
    //std::cin.rdbuf(in.rdbuf()); //redirect std::cin to in.txt!

    //std::ofstream out("out.txt");
    //std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf
    //std::cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!

    int n,fdnum;
    cin>>n>>fdnum;
    string s1,s2;
    getline(cin,s1);
    //scanf("\n");
    K=n;
    vector<pair<int,int>> FD;
    //INPUT
    for(int i=0;i<fdnum;i++){
        int x;
        int currant=0,currcons=0;
        getline(cin,s1);
        string curr="";
        for(int i=0;i<s1.size();i++){
            if(s1[i]==' ' && curr!=""){
                x=stoi(curr);
                currant|=(1<<(x-1));
                curr="";
                continue;
            }else{
                curr.push_back(s1[i]);
            }
        }
        if(curr!=""){
            x=stoi(curr);
            currant|=(1<<(x-1));
        }
        if(i==fdnum-1){
            while(cin>>x){
                currcons|=(1<<(x-1));
            }
        }
        else{
            getline(cin,s2);
            string curr="";
            for(int i=0;i<s2.size();i++){
                if(s2[i]==' ' && curr!=""){
                    x=stoi(curr);
                    currcons|=(1<<(x-1));
                    curr="";
                    continue;
                }else{
                    curr.push_back(s2[i]);
                }
            }
            if(curr!=""){
                x=stoi(curr);
                currcons|=(1<<(x-1));
            }
        }
        FD.push_back({currant,currcons});
    }
    //Calculation
    int N=1<<n;
    bool dp[N];
    for(int i=0;i<N;i++){
        dp[i]=true;
    }
    vector<int> ans;
    for(int i=1;i<N;i++){
        // if(i==N-1){
        //     cout<<dp[i]<<endl;
        // }
        if(!dp[i]){
            for(int k=0;k<n;k++){
                dp[i|(1<<k)]=false;
            }
            continue;
        }
        int currans=i;
        set<pair<int,int>> s1;
        for(auto x:FD){
            s1.insert(x);
        }
        while(s1.size()!=0){
            bool isthere=false;
            for(auto x:s1){
                int curr=x.first;
                if((curr|currans)==currans){
                    currans=currans|x.second;
                    isthere=true;
                    s1.erase(x);
                    break;
                }
            }
            if(!isthere){
                break;
            }
        }
        if(currans==(N-1)){
            for(int k=0;k<n;k++){
                if((i|(1<<k))!=i)
                    dp[i|(1<<k)]=false;
            }
            ans.push_back(i);
        }
    }
    // for(int x:ans){
    //     cout<<x<<endl;
    // }
    sort(ans.begin(),ans.end(),compare);
    cout<<ans.size()<<endl;
    for(int i=0;i<ans.size();i++){
        //cout<<ans[i]<<endl;
        for(int x=0;x<n;x++){
            if((ans[i]&(1<<x))!=0){
                cout<<x+1<<" ";
            }
        }
        cout<<endl;
    }
}
