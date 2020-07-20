

#include<iostream>
#include<bits/stdc++.h>

using namespace std;



bool checkPosition(vector<vector<int>> &myVector,int row, int col){
    int i, j;
    //safe in left
    for (i = 0; i < col; i++) 
        if (myVector[row][i]) 
            return false; 
    //safe in left upward
    for (i = row, j = col; i >= 0 && j >= 0; i--, j--) 
        if (myVector[i][j]) 
            return false; 
    //safe in left downward
    for (i = row, j = col; j >= 0 && i < 8; i++, j--) 
        if (myVector[i][j]) 
            return false; 

    return true; 
}    

/* applying the Heuristic Function
*Saving positon of queen in array row and columnm
*Now checking for validity 
*increasing the count if the position is valid
*/

int heuristicValue(vector<vector<int>> &myVector)
{ vector<int> row,column;
    vector<vector<int>> temp(8,vector<int>(8,0)); 
    int i,j,counter=0,k = row.size(),h,flag=0,b = column.size();
    
   for( i=0;i<8;i++){
        for(j=0;j<8;j++){
             if(myVector[i][j]==1)
                  {row.push_back(i);
                   column.push_back(j);}
        }
  }
  
    for( i=0;i<8;i++){
       flag=0;
        for(j=0;j<8;j++){
            for( h=0;h<k;h++){
                if(i==row[h])
                    {flag=1;
                     break;}
            }                  
            if(flag==1)continue;
            for( h=0;h<k;h++){
                if(b==column[h])
                    {flag=1;
                        break;}
            }
            if(flag==1)continue;
             for(h=0;h<k;h++){
                 if(abs(i-row[h]) == abs(j-column[h]))
                     {  flag==1;
                        break;}
             }
                 
            if(flag==0)
                counter++;
        }
   }
  return counter;
}

void sovleAstar(priority_queue<pair<int,vector<vector<int>>>,vector<pair<int,vector<vector<int>>>>,greater<pair<int,vector<vector<int>>>>> &openQueue, vector<vector<int>> &myVector){
    //push initial conditions of chess board and cost
    openQueue.push(make_pair(0,myVector));
    int k = 1;
    int j,x;
    while(!openQueue.empty()){
        for(j = 0; j < 8; ++j){
            pair<int,vector<vector<int>>> storePair = openQueue.top();
            
            vector<vector<int>> vec = storePair.second;
            if(storePair.first!=0)
                  { int val = heuristicValue(vec);
                    storePair.first -= val;
                  }
                  x = storePair.first;
            
            if(checkPosition(vec,j,x)){
                if(x == 7){
                     vec[j][x] = 1;
                     
                     cout << "solution :"<<k << endl;
                     ++k;
                     // print possible solutions
                     for(auto it : vec){
                        for(auto i : it){
                            cout << i << " ";
                        }
                        cout << endl;
                    }
                    cout << endl;
                }else{
                    vec[j][x] = 1;
                    
                    
                   int y = heuristicValue(vec);
                   // x+1 is g(n) and y is h(n)
                   y=y+(x+1);
                   //y is priority of the state
                    openQueue.push(make_pair(y,vec));
                    
                }  
            }
        }
        openQueue.pop();        
    }
}

int main(){
    //pairs of cost and pointer to chess board
    priority_queue<pair<int,vector<vector<int>>>,vector<pair<int,vector<vector<int>>>>,greater<pair<int,vector<vector<int>>>>> openQueue;
    //8X8 chess board
    vector<vector<int>> cBoard(8,vector<int>(8,0));
    sovleAstar(openQueue,cBoard);
}