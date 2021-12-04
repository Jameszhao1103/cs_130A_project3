#ifndef GRAPHOPERATOR_H
#define GRAPHOPERATOR_H

#include <vector>
#include <set>
#include <queue>
#include <algorithm>
#include "GraphGenerator.h"

//IsAcyclic reference: https://cppsecrets.com/users/22319897989712197103975756505164103109971051084699111109/C00-implementation-to-detect-cycle-in-a-directed-graph-.php

using namespace std;

class GraphOperator : public GraphGenerator
{
public:
    vector<int> visited;
  
    bool result = false;
    void IsAcyclic()
    {
        // printAdjList(root);
        //We want to use DFS for this

        visited.resize(size);

        cout << "Is acyclic(Yes/No):" << endl;

        for (int i = 0; i < size; i++)
        {
            visited[i] = 0;
        }
        leaf *temp = root;
        traversal_helper(temp);
        // for (int i = 0; i < size; i++)
        // {
        //     if (visited[i] == 0)
        //         if (hasCycle(i + 1, -1))
        //         {
        //             result = true;
        //             break;
        //         }
        // }

        if (result == true)
        {
            cout << "No" << endl;
        }
        else
        {
            cout << "Yes" << endl;
        }
    }

    void ConnectedComponents(){
        for (int i = 1; i < size+1; i++){
            visited[i] = 0;
        }

        cout << "Connected Components:" << endl;
        leaf *temp = root;

        for (int i = 1; i < size+1; i++){
            if(visited[i]==0){
                BFS(i);
            }
        }

            
        
        
    }

private:
    void printAdjList(leaf *root)
    {
        if (root == NULL)
            return;
        printAdjList(root->left);
        adjlist *templist = root->list;
        while (templist != NULL)
        {
            cout << root->vertex << " " << templist->vertex_connected << endl;
            templist = templist->next;
        }
        printAdjList(root->right);
    }

    bool hasCycle(int i, int parent)
    {
        visited[i - 1] = 1;
        leaf *node = LookUp(i);
        adjlist *nodelist = node->list;
        int vertexVal;
        while (nodelist != NULL)
        {
            vertexVal = nodelist->vertex_connected;
            if (visited[vertexVal - 1] == 0)
            {

                bool flag = hasCycle(vertexVal, i);
                if (flag)
                {
                    return true;
                }
            }
            else if (vertexVal != parent && parent != -1)
            {
                // cout << vertexVal << ": " << parent << endl;
                return true;
            }
            nodelist = nodelist->next;
        }
        return false;
    }

    void traversal_helper(leaf *root)
    {

        if (root == NULL)
            return;

        traversal_helper(root->left);
        if (visited[root->vertex] == 0)
        {
            bool flag = hasCycle(root->vertex, -1);

            if (flag)
            {
                result = true;
            }
        }
        traversal_helper(root->right);
    }

    

    void BFS(int vertex){
        queue<int> q;
        visited[vertex] = 1;
        q.push(vertex);

        vector<int> printlist;
        int v;

        while (!q.empty()){   
            v = q.front();
            printlist.push_back(v);
            numvisited += 1;
            q.pop();

            adjlist *nodelist = LookUp(v)->list;
            while (nodelist != NULL){
                if(visited[nodelist->vertex_connected]==0){
                    visited[nodelist->vertex_connected] = 1;
                    q.push(nodelist->vertex_connected);
                }
                nodelist = nodelist->next;
            }
        }

        sort(printlist.begin(),printlist.end());
        for (int j = 0; j < printlist.size(); j++){
            if(j!=printlist.size()-1){
                cout << printlist[j] << " ";
            }else{
                cout << printlist[j];
            }
        }
        cout << endl;
    }
};

#endif