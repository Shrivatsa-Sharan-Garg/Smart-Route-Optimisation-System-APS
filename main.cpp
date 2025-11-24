#include <iostream>
#include <algorithm>
#include <limits>
#include <string>
using namespace std;

#define MAX 100
const int INF = 1000000000;

long long g_min_path_distance = INF;
int g_best_intermediate_path[MAX];
int g_path_size = 0;

void swapInt(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

void permuteAndCheck(
    int n,
    string city[],
    int floydArr[MAX][MAX],
    int srcIndex,
    int destIndex,
    int current_intermediate_path[],
    int start_index,
    int end_index)
{
    if (start_index == end_index)
    {
        long long current_distance = 0;
        int current_city_index = srcIndex;
        bool path_valid = true;

        int first_intermediate = current_intermediate_path[0];
        if (floydArr[current_city_index][first_intermediate] == INF)
        {
            path_valid = false;
        }
        else
        {
            current_distance += floydArr[current_city_index][first_intermediate];
            current_city_index = first_intermediate;
        }

        if (path_valid)
        {
            for (int i = 0; i < g_path_size - 1; ++i)
            {
                int next_intermediate = current_intermediate_path[i + 1];
                if (floydArr[current_city_index][next_intermediate] == INF)
                {
                    path_valid = false;
                    break;
                }
                current_distance += floydArr[current_city_index][next_intermediate];
                current_city_index = next_intermediate;
            }
        }

        if (path_valid)
        {
            if (floydArr[current_city_index][destIndex] == INF)
            {
                path_valid = false;
            }
            else
            {
                current_distance += floydArr[current_city_index][destIndex];
            }
        }

        if (path_valid && current_distance < g_min_path_distance)
        {
            g_min_path_distance = current_distance;
            for (int i = 0; i < g_path_size; ++i)
            {
                g_best_intermediate_path[i] = current_intermediate_path[i];
            }
        }
        return;
    }

    for (int i = start_index; i <= end_index; i++)
    {
        swapInt(current_intermediate_path[start_index], current_intermediate_path[i]);
        permuteAndCheck(n, city, floydArr, srcIndex, destIndex, current_intermediate_path, start_index + 1, end_index);
        swapInt(current_intermediate_path[start_index], current_intermediate_path[i]);
    }
}

void findShortestHamiltonianPath(int n, string city[], int floydArr[MAX][MAX], int srcIndex, int destIndex)
{

    int intermediateCities[MAX];
    int count = 0;
    for (int i = 0; i < n; ++i)
    {
        if (i != srcIndex && i != destIndex)
        {
            intermediateCities[count++] = i;
        }
    }

    g_path_size = count;

    if (g_path_size == 0)
    {
        cout << "\nOnly source and destination specified. Use option 1 for shortest path.\n";
        return;
    }

    g_min_path_distance = INF;

    permuteAndCheck(n, city, floydArr, srcIndex, destIndex, intermediateCities, 0, g_path_size - 1);

    cout << "\n--- Shortest Path Covering All Cities (Path TSP) ---\n";
    if (g_min_path_distance == INF)
    {
        cout << "No path exists that visits all cities from " << city[srcIndex] << " to " << city[destIndex] << ".\n";
    }
    else
    {
        cout << "Shortest path distance: " << g_min_path_distance << "\n";

        cout << "Path: " << city[srcIndex];
        for (int i = 0; i < g_path_size; ++i)
        {
            cout << " -> " << city[g_best_intermediate_path[i]];
        }
        cout << " -> " << city[destIndex] << "\n";

        cout << "\nNOTE: This solution uses a brute-force approach (O((N-2)! * N)), which is only practical for graphs with a small number of cities (N < 11-12).\n";
    }
}

void FloydWarshall(int dist[MAX][MAX], int nextHop[MAX][MAX], int n)
{
    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (dist[i][k] < INF && dist[k][j] < INF)
                {
                    if (dist[i][k] + dist[k][j] < dist[i][j])
                    {
                        dist[i][j] = dist[i][k] + dist[k][j];
                        nextHop[i][j] = nextHop[i][k];
                    }
                }
            }
        }
    }
}
void BFS(int adj[MAX][MAX], int n, int start, string city[]) {
    bool visited[MAX] = {false};
    int queue[MAX];
    int front = 0, rear = 0;

    visited[start] = true;
    queue[rear++] = start;

    cout << "BFS Traversal: ";

    while (front < rear) {
        int current = queue[front++];
        cout << city[current] << " ";

        for (int i = 0; i < n; i++) {
            if (adj[current][i] != INF && !visited[i] && current != i) {
                visited[i] = true;
                queue[rear++] = i;
            }
        }
    }

    cout << endl;
}

void DFSUtil(int adj[MAX][MAX], int n, int node, bool visited[], string city[]) {
    visited[node] = true;
    cout << city[node] << " ";

    for (int i = 0; i < n; i++) {
        if (adj[node][i] != INF && !visited[i] && node != i) {
            DFSUtil(adj, n, i, visited, city);
        }
    }
}

void DFS(int adj[MAX][MAX], int n, int start, string city[]) {
    bool visited[MAX] = {false};
    cout << "DFS Traversal: ";
    DFSUtil(adj, n, start, visited, city);
    cout << endl;
}

void printPath(int src, int dest, int nextHop[MAX][MAX], string city[])
{
    if (nextHop[src][dest] == -1)
    {
        cout << "No path exists.\n";
        return;
    }

    cout << "Path: " << city[src];

    int curr = src;
    while (curr != dest)
    {
        curr = nextHop[curr][dest];
        if (curr == -1 || curr == src)
            break;
        cout << " -> " << city[curr];
    }

    cout << endl;
}

int getIndex(string city[], int n, string name)
{
    for (int i = 0; i < n; i++)
    {
        if (city[i] == name)
        {
            return i;
        }
    }
    return -1;
}

int main()
{
    int n;
    cout << "Enter number of cities: ";
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string city[MAX];

    for (int i = 0; i < n; i++)
    {
        cout << "Enter name of city " << i + 1 << ": ";
        getline(cin, city[i]);
    }

    int adj[MAX][MAX];
    int floydArr[MAX][MAX];
    int nextHop[MAX][MAX];

    cout << "\nEnter distance between cities (-1 if no path):-\n";
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == j)
            {
                adj[i][j] = 0;
                nextHop[i][j] = j;
                continue;
            }
            cout << "Enter distance between cities (" << city[i] << " to " << city[j] << "): ";
            int dist;
            cin >> dist;

            if (dist == -1)
            {
                adj[i][j] = INF;
                nextHop[i][j] = -1;
            }
            else
            {
                adj[i][j] = dist;
                nextHop[i][j] = j;
            }
        }
    }

    int choice;
    bool FloydDone = false;

    do
    {
        cout << "\n--- MENU ---\n";
        cout << "1. Shortest distance between two cities\n";
        cout << "2. Shortest path covering all cities between 2 specific cities (Path TSP)\n";
        cout << "3. Traversal of Cities (BFS/DFS)\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            if (!FloydDone)
            {
                for (int i = 0; i < n; i++)
                {
                    for (int j = 0; j < n; j++)
                    {
                        floydArr[i][j] = adj[i][j];
                    }
                }
                FloydWarshall(floydArr, nextHop, n);
                FloydDone = true;
            }

            string s, d;
            cout << "Enter source city: ";
            cin >> s;
            cout << "Enter destination city: ";
            cin >> d;

            int src = getIndex(city, n, s);
            int dest = getIndex(city, n, d);

            if (src == -1 || dest == -1)
            {
                cout << "Invalid city name.\n";
            }
            else
            {
                if (floydArr[src][dest] == INF)
                {
                    cout << "No path exists from " << s << " to " << d << ".\n";
                }
                else
                {
                    cout << "Shortest distance from " << s << " to " << d << " is " << floydArr[src][dest] << ".\n";
                    int choose = 0;
                    cout << "Enter 1 to print path too:";
                    cin >> choose;
                    if (choose == 1)
                    {
                        printPath(src, dest, nextHop, city);
                    }
                }
            }
            break;
        }
        case 2:
        {
            if (!FloydDone)
            {
                for (int i = 0; i < n; i++)
                {
                    for (int j = 0; j < n; j++)
                    {
                        floydArr[i][j] = adj[i][j];
                    }
                }
                FloydWarshall(floydArr, nextHop, n);
                FloydDone = true;
            }

            string s, d;
            cout << "Enter start city for the path (Source): ";
            cin >> s;
            cout << "Enter end city for the path (Destination): ";
            cin >> d;

            int src = getIndex(city, n, s);
            int dest = getIndex(city, n, d);

            if (src == -1 || dest == -1)
            {
                cout << "Invalid city name.\n";
            }
            else if (src == dest)
            {
                cout << "Source and Destination cannot be the same for this operation.\n";
            }
            else
            {
                findShortestHamiltonianPath(n, city, floydArr, src, dest);
            }
            break;
        }
        case 3:{
            string startCity;
            cout << "Enter starting city for traversal: ";
            cin >> startCity;
            int start = getIndex(city, n, startCity);
        if (start == -1){
            cout << "Invalid city name.\n";
            break;
        }
        int opt;
        cout << "\nChoose Traversal Method:\n";
        cout << "1. BFS\n";
        cout << "2. DFS\n";
        cout << "Enter choice: ";
        cin >> opt;
        if (opt == 1){
            BFS(adj, n, start, city);
        }
        else if (opt == 2){
            DFS(adj, n, start, city);
        }
        else{
            cout << "Invalid traversal choice.\n";
        }
        break;
        }
        case 4:
        {
            cout << "Exiting...\n";
            break;
        }
        default:
        {
            cout << "Invalid choice.\n";
            break;
        }
        }

    } while (choice != 4);

    return 0;
}
