#include <algorithm>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <math.h>
#include <string>
#include <cstring>
#include <queue>
using namespace std;

int main() {
    int sobresCajon,i;
    int val;
    int sobresCena;
    while(cin>>sobresCajon>>sobresCena&&sobresCajon){
        deque<int> cola;
        vector<int> result;
        result.reserve(sobresCajon);
        for(i=0;i<sobresCajon;i++){
            cin>>val;
            result.push_back(val);
        }
        for(i=0;i<sobresCena;++i){
            while(!cola.empty()&&result[i]>=result[cola.back()]){
                cola.pop_back();
            }
            cola.push_back(i);
        }
        for(;i<sobresCajon;++i){
            cout<<result[cola.front()]<<" ";
            while(!cola.empty()&&cola.front()<=i-sobresCena){
                cola.pop_front();
            }
            while(!cola.empty()&&result[i]>=result[cola.back()]){
                cola.pop_back();
            }
            cola.push_back(i);
        }
        cout<<result[cola.front()]<<"\n";
    }
    
    return 0;
}