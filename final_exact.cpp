#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;

//Add edges to the nodes randomly
void addEdge(vector<int> adj[], int u, int v, int n)
{

    vector<int>::iterator p;

    //Determine if the node contains the same connected edges as the edges that are
    //currently connecting
    p = find(adj[u].begin(), adj[u].end(), v);

    //If nodes had been connected to the edges, randomize the edges until it is unique
    //If the nodes connect to itself, randomize the edges
    while (p != adj[u].end() || u == v)
    {
        v = rand() % n;
        u = rand() % n;
        p = find(adj[u].begin(), adj[u].end(), v);
    }

    //Add edges to both corresponding nodes
    adj[u].push_back(v);
    adj[v].push_back(u);
    //cout<<endl<<"Connect "<<u<<" to "<<v<<endl;
}

int main()
{

    int numOfNodes = 13;
    int edges = 28;
    int tempEdges = ((numOfNodes * (numOfNodes - 1)) / 2);
    
    clock_t start2;
    
    
    double duration2 = 0;
    

    bool done = false;
   
    for (int times = 0; times < 50; times++)
    {
        //edges = rand() % tempEdges + 1;
        start2 = clock();
        //numOfNodes = rand()%6+8;
        
        //Initialise node capacity
        vector<int> adj[numOfNodes];
        vector<int>::iterator p;

        //Add edges
        for (int i = 0; i < edges; i++)
        {
            addEdge(adj, rand() % numOfNodes, rand() % numOfNodes, numOfNodes);
        }

        //EXACT

       
        vector<int> vi;
        for (int i = 0; i < numOfNodes; i++)
        {
            vi.push_back(i);
        }
        sort(vi.begin(), vi.end());
        int counter = 0;

        vector<int> hamiltonian_path;
        hamiltonian_path.push_back(vi[0]);
        done = false;

        for (int i = 0; i < vi.size(); i++)
        {
            //Determine the node consist the following edges
            p = find(adj[vi[i]].begin(), adj[vi[i]].end(), vi[i + 1]);

            //If node consist of following edges, counter + 1
            if (p != adj[vi[i]].end())
            {
                counter++;
                hamiltonian_path.push_back(vi[i + 1]);

                //If counter equals to the number of nodes, then
                //the graph consist a hamiltonian path and terminate the program
                if (counter == numOfNodes - 1)
                {
                    duration2 = (clock() - start2) / (double)CLOCKS_PER_SEC;
                    cout << duration2 <<"\n       TRUE"<< endl;

                    done = true;
                }
            }
            else
            {
                hamiltonian_path.clear();
                break;
            }
        }

        if (!done)
        {
            int permutation_counter = 1;
            int factorial = 1;

            //Calculate the total combination of permutation can be found
            for (int i = 1; i <= numOfNodes; ++i)
            {
                factorial *= i;
            }

            bool done2 = false;

            //Permutation process
            while (next_permutation(vi.begin(), vi.end()))
            {
                if (done2)
                {
                    break;
                }

                permutation_counter++;
                counter = 0;

                hamiltonian_path.push_back(vi[0]);

                for (int i = 0; i < vi.size(); i++)
                {

                    //Determine the node consist the following edges
                    p = find(adj[vi[i]].begin(), adj[vi[i]].end(), vi[i + 1]);

                    //If node consist of following edges, counter + 1
                    if (p != adj[vi[i]].end())
                    {

                        counter++;

                        hamiltonian_path.push_back(vi[i + 1]);

                        //If counter equals to the number of nodes, then
                        //the graph consist a hamiltonian path and terminate the program
                        if (counter == numOfNodes - 1)
                        {

                            duration2 = (clock() - start2) / (double)CLOCKS_PER_SEC;
                            cout << duration2 <<"\n       TRUE"<< endl;

                            done2 = true;

                            break;
                        }
                    }
                    else
                    {
                        hamiltonian_path.clear();
                        break;
                    }
                }

                //If counter is less than number of nodes and permutation process is complete,
                //it states that hamiltonian path is not found
                if (counter < numOfNodes - 1 && permutation_counter == factorial)
                {

                    duration2 = (clock() - start2) / (double)CLOCKS_PER_SEC;
                     cout << duration2 <<"\n       FALSE"<< endl;

                    break;
                }
            }
        }
    }

    return 0;
}
