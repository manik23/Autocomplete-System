#include<bits/stdc++.h>
using namespace std;
struct trieNode{
    char data;
    bool we;
    int freq;
    struct trieNode* child[255];
    trieNode(char d){
        data = d;
        we = 0;
        freq = 0;
        memset(child,NULL,sizeof(child));
    }
};

typedef pair<string,int> item;

class AutocompleteSystem {
public:
    struct trieNode* root;
    unordered_map<string,int> repeat;
    string last;
    void insert(string s,int times){
        struct trieNode* head = root;
        for(int i=0;i<s.length();i++){
            int idx = s[i];
            if(head->child[idx]==NULL)
                head->child[idx] = new trieNode(s[i]);
            head = head->child[idx];
        }
        head->we = 1;
        head->freq = times;
    }
    
    void helper(struct trieNode* temp,vector<item> &result,string s=""){
        s += temp->data;
        
        if(temp->we == 1){
            result.push_back({s,temp->freq});
        }
        
        for(int i=0; i<255;i++){
            if(temp->child[i] != NULL){
                helper(temp->child[i],result,s);
            }
        }
    }
    
    vector<string> search(string temp){
        
        struct trieNode* head = root;
        string s;
        for(auto x: temp){
             
            if(head->child[x] == NULL) return {};
            head = head->child[x];  
            s += x;
        }
        s.pop_back();
        vector<item> result;
        helper(head,result,s);
        
        sort(result.begin(),result.end(),[](item a, item b){
           
            
            if(a.second != b.second){
                return a.second > b.second;
            }
            
            return a.first < b.first;
            
        });
        
        vector<string> answer;
        for(int i=0; i<min(3,int(result.size()));i++){
            answer.push_back(result[i].first);
        }
        
        return answer;
        
        
    }
    
    
    AutocompleteSystem(vector<string>& sentences, vector<int>& times) {
        root = new trieNode('$');
        for(int i=0; i<times.size(); i++){
            insert(sentences[i],times[i]);
            repeat[sentences[i]]=times[i];
        }
    }
    
    vector<string> input(char c) {
        if(c=='#') {
            repeat[last]++;
            insert(last,repeat[last]);
            last.clear();
            return {};
        }
        last += c;
        return search(last);
    }
};

/**
 * Your AutocompleteSystem object will be instantiated and called as such:
 * AutocompleteSystem* obj = new AutocompleteSystem(sentences, times);
 * vector<string> param_1 = obj->input(c);
 */
int main(){
return 1;
}
