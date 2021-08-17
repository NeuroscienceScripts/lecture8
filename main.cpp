//sorting.cpp
#include <iostream>
#include <queue>
#include <set>
#include <vector>
#include <time.h>

using namespace std;

//Precondition: unsorted vector v of size N
//Post condition: sorted array in ascending order
template<class T>
void selectionSort(vector<T>& v){
    int N = v.size();
    for(int i =0; i < N; i++){
        int index=i;
        for(int j = i+1; j< N;j++){
            if(v[j].size() < v[index].size())
                index = j;
        }

        T tmp = v[i];
        v[i] = v[index];
        v[index]=tmp;
    }
}

template<class T>
void selectionSortPointer(vector<T>& v){
    int N = v.size();
    for(int i =0; i < N; i++){
        int index=i;
        for(int j = i+1; j< N;j++){
            if(v[j]->size() < v[index]->size())
                index = j;
        }

        T tmp = v[i]; // all of this can now be done in constant time thanks to not having to write new BSTs
        v[i] = v[index];
        v[index]=tmp;
    }
}


class compareTreePtr{
public:
    bool operator()(set<int>*&lhs, set<int>*&rhs ){
        return lhs->size()> rhs->size();
    }
};

template<class T, class cmpClass>
void heapSort(vector<T>& v){
    priority_queue<T,vector<T>,cmpClass> pq;
    int N = v.size();
    for(int i =0; i < N; i++){
        pq.push(v[i]);
    } // Nlog(N)
    int i=0;
    while(!pq.empty()){
        v[i]=pq.top(); //O(1)
        pq.pop(); //O(log N)
        i++;// O(1)
    }//NlogN
    // Total = O(NlogN)
}

// Running  time is not constant for the following three lines
// We are calling the copy constructor and copy assignment
// both of which iterate over all the keys of the tree
// Running time depends on M (maximum size of the trees)
// O(N^2) for vector of ints
// not the case for vector of trees
template  <class T>
void print(vector<T>&v){
    for(auto &tree: v){
        cout<<"Size: "<< tree.size()<<endl;
        cout<<"Elements: "<<endl;
        for(auto key:tree){//inorder traversal
            cout<<key<<" ";
        }
        cout<<endl;
        cout<<endl;

    }
    cout<<endl;
}

vector<set<int>> GenerateIntSetVector(int num_trees, int num_keys, int keyMax){
    vector<set<int>> forest; // set is the STL standard for BSTs

    for(int i=0; i<num_trees; i++){
        forest.push_back(set<int>{});

        int n = rand() % num_keys; // number of keys in tree at index i

        for(int j=0; j<n; j++) // inserting keys into tree number i
            forest[i].insert(rand()%keyMax);

    }
    return forest;
}

vector<set<int>*> GenerateIntSetPointerVector(int num_trees, int num_keys, int keyMax){
    vector<set<int>*> forest; // set is the STL standard for BSTs

    for(int i=0; i<num_trees; i++){
        forest.push_back(new set<int>{}); // Using new pushes a pointer instead of a set

        int n = rand() % num_keys; // number of keys in tree at index i

        for(int j=0; j<n; j++) // inserting keys into tree number i
            forest[i]->insert(rand()%keyMax);

    }
    return forest;
}

int main(){
    int N = 10000; // number of trees
    int M = 10000; // maximum number of keys in each tree
    int Vmax = 10000; // max value of the keys

//    auto forest = GenerateIntSetVector(N, M, Vmax);
    auto forest = GenerateIntSetPointerVector(N, M, Vmax);



    //print(forest);
    clock_t t = clock();

    //selectionSort(forest);
    //selectionSortPointer(forest);
    heapSort<set<int>*, compareTreePtr>(forest);

    t = clock() - t;

    //cout << "SORTED" << endl << endl;

    //print(forest);

    cout<<"Time to sort forest with  "<< N <<" trees and a max of "<<M<< " keys is "
        <<t*1000/CLOCKS_PER_SEC<<" ms"<<endl;

    return 0;

}