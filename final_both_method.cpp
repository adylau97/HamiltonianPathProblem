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
    int edges = 0;
    int tempEdges = ((numOfNodes * (numOfNodes - 1)) / 2) - 40;
    clock_t start;
    clock_t start2;
    clock_t start3;
    double duration = 0;
    double duration2 = 0;
    double duration3 = 0;

    bool done = false;
   
    for (int times = 10; times < 20; times++)
    {
        edges = rand() % tempEdges + 40;

        //Calculate time
        start = clock();
        start3 = clock();

        //Initialise node capacity
        vector<int> adj[numOfNodes];

        //Add edges
        for (int i = 0; i < edges; i++)
        {
            addEdge(adj, rand() % numOfNodes, rand() % numOfNodes, numOfNodes);
        }

        duration3 = (clock() - start3) / (double)CLOCKS_PER_SEC;

        //NON-EXACT

        //Determine the size of each node and sort it based on the sizes
        int size = 0;

        //Check the first biggest size of the node and store it
        for (int p = 0; p < numOfNodes; p++)
        {
            if (size <= adj[p].size())
            {
                size = adj[p].size();
            }
        }

        vector<int> greedy_sort;

        //Loop for sorting all nodes in big to small sequence
        while (greedy_sort.size() != numOfNodes)
        {

            //Add all nodes that equal to the size
            for (int p = 0; p < numOfNodes; p++)
            {
                if (adj[p].size() == size)
                {
                    greedy_sort.push_back(p);
                }
            }

            int temp_size = 0;

            //Check the sizes of the nodes that is bigger than the rest but
            //smaller than the previous selected node size
            for (int p = 0; p < numOfNodes; p++)
            {
                if (temp_size <= adj[p].size() && adj[p].size() < size)
                {
                    temp_size = adj[p].size();
                }
            }

            //Assign the current largest size for reference
            size = temp_size;
        }

        int counter = numOfNodes - 1;
        int temp_counter = 0;
        vector<int>::iterator p;
        vector<int>::iterator a;
        vector<int> greedy_final;

        //Push the first node that are the largest
        greedy_final.push_back(greedy_sort[0]);
        int i = 0;
        int c = 1;

        //Loop until all nodes are succesfully connected or unconnected nodes are detected
        //equal to the number of remaining nodes
        while (counter != temp_counter && greedy_final.size() != numOfNodes)
        {

            //Check whether the nodes are the edges of the selected node
            p = find(adj[greedy_sort[i]].begin(), adj[greedy_sort[i]].end(), greedy_sort[c]);
            //Check whether the connecting nodes are connected previously
            a = find(greedy_final.begin(), greedy_final.end(), greedy_sort[c]);

            if (p != adj[greedy_sort[i]].end() && a == greedy_final.end())
            {

                greedy_final.push_back(greedy_sort[c]);

                //Reduce the number of unconnected nodes
                counter--;

                temp_counter = 0;

                //Change the node to the previously connected node
                i = c;
                c = 1;
                
            }
            else
            {
                if (a == greedy_final.end())
                {
                    temp_counter++;
                    //Record the remaining node that are not connected

                }
                c++;
                if (c == numOfNodes)
                {
                    c = 1;
                }
            }
        }

        bool done3 = true;

        //If nodes are all connected then no need to perform iterative improvement
        if (numOfNodes - greedy_final.size() == 0)
        {
            duration = (clock() - start) / (double)CLOCKS_PER_SEC;
            cout << duration;
            cout << "True" << endl;

            done3 = false;
        }

        if (done3)
        {
            int random_position;

            vector<int> temp_greedy;
            int compareNode;
            int compareSize;
            vector<int> smallest;

            //Remove all the nodes after a randomize position and re-execute greedy algorithm
            for (int q = 0; q < 40; q++)
            {
                random_position = rand() % greedy_final.size();
                compareSize = numOfNodes - greedy_final.size();
                counter = numOfNodes - random_position - 1;
                temp_counter = 0;
                i = random_position;
                c = 1;

                //Store all the nodes until the randomize position
                for (int i = 0; i < random_position + 1; i++)
                {
                    temp_greedy.push_back(greedy_final[i]);
                    compareNode = greedy_final[i + 1];
                }

                //Start generating nodes based on node sizes from the randomize position onwards
                while (counter != temp_counter && temp_greedy.size() != numOfNodes)
                {

                    if (greedy_sort[c] == compareNode && i + 1 == random_position + 1)
                    {
                        c++;
                        temp_counter++;
                    }

                    p = find(adj[temp_greedy[i]].begin(), adj[temp_greedy[i]].end(), greedy_sort[c]);
                    a = find(temp_greedy.begin(), temp_greedy.end(), greedy_sort[c]);

                    if (p != adj[temp_greedy[i]].end() && a == temp_greedy.end())
                    {

                        temp_greedy.push_back(greedy_sort[c]);
                        counter--;
                        temp_counter = 0;
                        i++;
                        c = 1;
                    }
                    else
                    {
                        if (a == temp_greedy.end())
                        {
                            temp_counter++;
                        }
                        c++;
                        if (c == numOfNodes)
                        {
                            c = 1;
                        }
                    }
                }

                if (numOfNodes - temp_greedy.size() < compareSize)
                {
                    smallest.clear();
                    for (int i = 0; i < temp_greedy.size(); i++)
                    {
                        smallest.push_back(temp_greedy[i]);
                    }
                    greedy_final = smallest;
                }

                temp_greedy.clear();
            }

            duration = (clock() - start) / (double)CLOCKS_PER_SEC;
            cout << duration;

            if (smallest.size() == numOfNodes)
            {
                cout << "True" << endl;
            }
            else
            {
                cout << "False" << endl;
                //if(numOfNodes - smallest.size() == numOfNodes){
                   // cout<<"Nodes left: "<< compareSize <<endl;
                //}else{
                  //  cout<<"Nodes left: "<< numOfNodes - smallest.size()<<endl;
                //}
            }
        }
        //EXACT

        start2 = clock();
        vector<int> vi;
        for (int i = 0; i < numOfNodes; i++)
        {
            vi.push_back(i);
        }
        sort(vi.begin(), vi.end());
        counter = 0;

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
                    cout << duration2 + duration3;
                    cout << "True" << endl
                         << endl;

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
                            cout <<duration2 + duration3 ;
                            cout << "True" << endl
                                 << endl;

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
                    cout << duration2 + duration3 ;
                    cout << "False" << endl
                         << endl;

                    break;
                }
            }
        }
    }

    return 0;
}
