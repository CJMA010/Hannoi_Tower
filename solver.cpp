//
//  main.cpp
//  solver_for_tower_of_hanoi
//
//  Created by apple on 8/27/18.
//  Copyright © 2018 Changjie Ma. All rights reserved.
//

# include <iostream>
# include <vector>
# include <math.h>
# include <set>
using namespace std;

int steps=0;

bool check (vector<vector<int> > status){
    for (int i = 0 ; i < status.size() ; i++){
        for (int j = 1 ; j < (status[i].size()-1) ; j++){
            if (status[i][j] <=  status[i][j+1])
                return false;
        }
    }
    return true;
}

void refresh (vector<vector<int> > & status)
{
    for ( int i = 0 ; i < status.size() ; i++){
        status[i][0] = (int)status[i].size() - 1;
    }
}

void output(vector<vector<int> > value)
{
    for ( int i = 0 ; i < value.size() ; i++ )
    {
        cout << value[i][0] << "|";
        for ( int j = 1 ; j < value[i].size() ; j++)
        {
            cout << value[i][j] << " ";
        }
        cout << endl;
    }
}

void conduct_movement (int start , int goal , vector<vector<int> > & status){
    int code = status[start-1][status[start-1].size()-1];
    cout << "Move disk " << code << " from Peg " << start << " to Peg "<< goal;
    status[start-1].pop_back();
    status[goal-1].push_back(code);
    refresh(status);
    // output(status);
    if (check(status))
        cout << "(legal)" << endl;
    else
        cout << "(warning: illegal!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!)" << endl;
    steps++;
}

set<int> inetermedia(int start , int goal ,int number, vector<vector<int> > & status){
    
    set<int> avaliable_peg = {};
    for (int i = 0 ; i < status.size() ; i++){
        avaliable_peg.insert(i);
    }
    
    avaliable_peg.erase (avaliable_peg.find(start-1));
    avaliable_peg.erase (avaliable_peg.find(goal-1));
    
    for (int i = 0 ; i < status.size() ; i++){
        int h = (int)status[start-1].size() - number;

        if ((status[i][status[i].size()-1] < status[start-1][h]) && (status[i][0] != 0) && (i!=(start-1)) && (i!=(goal-1)) )
            avaliable_peg.erase (avaliable_peg.find(i));
    }
    

    return avaliable_peg;

}

void move(int start , int goal , int number , vector<vector<int> > & status){
    
    if (1 == number){
        conduct_movement(start , goal , status);
    }
    else if (((int)(inetermedia(start,goal,number,status).size()) == 1)){

        int p = number - 1;

        int mid = *inetermedia(start,goal,number,status).begin();
        move(start , mid+1 , p , status);
        move(start , goal , 1 , status);
        move(mid+1, goal , p , status);
    }
    
    
    else if (number <= (inetermedia(start,goal,number,status).size()+1))
    {
        set<int> peg_set = inetermedia(start,goal,number,status);

        set<int>::iterator it = peg_set.begin();
        for (int i = 0 ; i < (number - 1) ; i++){
            conduct_movement(start, *(it)+1, status);
            ++it;
        }
        conduct_movement(start,goal,status);
        it = peg_set.end();
        for (int i = 0 ; i < (peg_set.size()-number+1); i++)
            --it;
        for (int i = 0 ; i < (number - 1) ; i++){
            --it;
            conduct_movement(*(it)+1, goal , status);
        }
    }
    else
    {
        int mid = *(inetermedia(start,goal,number,status).begin());
        int the_number = (int)inetermedia(start,goal,number,status).size()+1;
        move(start , mid+1 , the_number , status);
        move(start , goal , number-the_number , status);
        move(mid+1 , goal , the_number , status);
    }
}

vector<vector<int> > initialize (int pegs, int disks, int start , int goal ,vector<vector<int> >  & status ){
    vector<int> temp;
    temp.push_back(0);
    for (int i = 0 ; i < pegs ; i++)
        status.push_back(temp);
    for (int i = disks ; i > 0 ; i--)
        status[0].push_back(i);
    refresh (status);
    return status;
}

int main(void){
    vector<vector<int> > status;
    int pegs;
    int disks;
    
    cout << "Number of pegs? ";
    cin >> pegs;
    cout << "Number of disks? ";
    cin >> disks;
    
    int start = 1;
    int goal = pegs;
    
    vector<vector<int> > a = initialize(pegs,disks,start,goal,status);
    
    cout << "----------------------------------------" << endl;
    cout << "State of Peg 1 (Top to Bottom): ";
    for (int i = 1 ; i < status[0].size() ; i++)
        cout << status[0][status[0].size()-i] << " ";
    cout << endl;
    cout << "Number of Steps = " << steps << endl;
    cout << "----------------------------------------" << endl;
    
    cout << "After initialized:" << endl;
    // output(a);
    move(start,goal,disks,a);
    
    cout << "----------------------------------------" << endl;
    cout << "State of Peg " << goal << " (Top to Bottom): ";
    
    
    
    for (int i = 1 ; i < a[goal-1].size() ; i++)
        cout << a[goal-1][a[goal-1].size()-i] << " ";
    
    cout << endl;
    cout << "Number of Steps = " << steps << endl;
    cout << "----------------------------------------" << endl;
    
    
    
    return 0;
}
