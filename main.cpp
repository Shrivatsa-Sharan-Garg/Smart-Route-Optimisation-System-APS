#include <iostream>
#include <algorithm>
using namespace std;

#define MAX 100
const int INF=1000000000;

void FloydWarshall(int dist[MAX][MAX],int nextHop[MAX][MAX],int n){
    for(int k=0;k<n;k++){
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(dist[i][k]<INF && dist[k][j]<INF){
                    if(dist[i][k] + dist[k][j] < dist[i][j]){
                        dist[i][j]=dist[i][k] + dist[k][j];
                        nextHop[i][j]=nextHop[i][k];
                    }
                }
            }
        }
    }
}

void printPath(int src,int dest,int nextHop[MAX][MAX],string city[]){
    if (nextHop[src][dest]==-1){
        cout<<"No path exists.\n";
        return;
    }

    cout<<"Path: "<<city[src];

    while(src!=dest){
        src=nextHop[src][dest];
        cout<<" -> "<<city[src];
    }

    cout<<endl;
}

int getIndex(string city[],int n,string name){
    for(int i=0;i<n;i++){
        if(city[i]==name){
            return i;
        }
    }
    return -1;
}

int main(){
    int n;
    cout<<"Enter number of cities: ";
    cin>>n;

    string city[MAX];

    for(int i=0;i<n;i++){
        cout<<"Enter name of city "<<i+1<<": ";
        cin>>city[i];
    }

    int adj[MAX][MAX];
    int floydArr[MAX][MAX];
    int nextHop[MAX][MAX];

    cout<<"\nEnter distance between cities (-1 if no path):-\n";
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if (i==j){
                adj[i][j]=0;
                nextHop[i][j]=j;
                continue;
            }
            cout<<"Enter distance between cities ("<<city[i]<<" to "<<city[j]<<"): ";
            cin>>adj[i][j];

            if(adj[i][j]==-1){
                adj[i][j]=INF;
                nextHop[i][j]=-1;
            }else{
                nextHop[i][j]=j;
            }
        }
    }

    int choice;
    bool FloydDone=false;

    do{
        cout<<"\n--- MENU ---\n";
        cout<<"1. Shortest distance between two cities\n";
        cout<<"2. Shortest path covering all cities between 2 specific cities\n";
        cout<<"3. Traversal of Cities (BFS/DFS)\n";
        cout<<"4. Exit\n";
        cout<<"Enter choice: ";
        cin>>choice;

        if(choice==1){
            if (FloydDone!=true){
                for(int i=0;i<n;i++){
                    for(int j=0;j<n;j++){
                        floydArr[i][j]=adj[i][j];
                    }
                }

                FloydWarshall(floydArr,nextHop,n);
                FloydDone=true;
            }

            string s,d;
            cout<<"Enter source city: ";
            cin>>s;
            cout<<"Enter destination city: ";
            cin>>d;

            int src=getIndex(city,n,s);
            int dest=getIndex(city,n,d);

            if(src==-1 || dest==-1){
                cout<<"Invalid city name.\n";
            }
            else{
                if(floydArr[src][dest]==INF){
                    cout<<"No path exists from "<<s<<" to "<<d<<".\n";
                }
                else{
                    cout<<"Shortest distance from "<<s<<" to "<<d<<" is "<<floydArr[src][dest]<<".\n";
                    int choose=0;
                    cout<<"Enter 1 to print path too:";
                    cin>>choose;
                    if (choose==1){
                        printPath(src,dest,nextHop,city);
                    }
                }
            }
        }

        else if(choice==2){
            cout<<"Placeholder.\n";
        }

        else if(choice==3){
            cout<<"Placeholder.\n";
        }

        else if(choice==4){
            cout<<"Exiting...\n";
        }

        else{
            cout<<"Invalid choice.\n";
        }

    }while(choice!=4);

    return 0;
}
