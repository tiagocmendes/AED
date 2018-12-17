/*best_distances[18][1<<18]
                |- cidade final 

calc_dist(int dest, int mask)
{
    if(best_distance[dest][mask] == 0)
    {
        int i, m = 100000000, d;

        for(i = 0; i < 15; i++)
        {
            if( mask & (1<<i))
            {
                d = calc_dist(i, mask*(1<<i)+ dist(i, dest));
                if(d <= m)
                {
                    m = d;
                }
            }
        }
    }
}*/

#include<iostream>
using namespace std;

#define INT_MAX 999999

int n=4;
int dist[10][10] = {
        {0,20,42,25},
        {20,0,30,34},
        {42,30,0,10},
        {25,34,10,0}
};
int VISITED_ALL = (1<<n) -1;

int dp[16][4];


int  tsp(int mask,int pos){
	
	if(mask==VISITED_ALL){
		return dist[pos][0];
	}
	if(dp[mask][pos]!=-1){
	   return dp[mask][pos];
	}

	//Now from current node, we will try to go to every other node and take the min ans
	int ans = INT_MAX;

	//Visit all the unvisited cities and take the best route
	for(int city=0;city<n;city++){

		if((mask&(1<<city))==0){

			int newAns = dist[pos][city] + tsp( mask|(1<<city), city);
			ans = min(ans, newAns);
		}

	}
	
	return dp[mask][pos] = ans;
} 

int main(){
    /* init the dp array */
    for(int i=0;i<(1<<n);i++){
        for(int j=0;j<n;j++){
            dp[i][j] = -1;
        }
    }
	cout<<"Travelling Saleman Distance is "<<tsp(1,0);

return 0;
}
    