#include <bits/stdc++.h>
#include <queue>
using namespace std;


class heap{

    public:

    int arr[100];
    int size;

    heap(){
        arr[0] = -1;
        size = 0;
    }

    //t.c O(log n)
    void insert(int val){

        size = size + 1;
        int ind = size;
        arr[ind] = val;

        while(ind>1){
            int parent = ind/2;
            if(arr[parent] < arr[ind]){
                swap(arr[parent],arr[ind]);
                ind = parent;
            }else{
                return ;
            }
        }
    }

    void deleteRoot(){

        if(size == 0) {
            cout<<"nothing do delete";
            cout<<endl;
        }

        arr[1] = arr[size];
        size--;

        int ind = 1;
        
        
        while(ind<size){
            int largest = ind;
            int left = 2*ind;
            int right = 2*ind + 1;

            if(left<size && arr[left]>arr[largest]){
                largest = left;
            }if(right<size && arr[right]>arr[largest]){
                largest = right;
            }
            if(ind != largest){
                swap(arr[ind],arr[largest]);
                ind = largest;
            }else{
                return ;
            }
            
        }
    }

    void heapify(int arr[],int n,int ind){

        int largest = ind;
        int left = 2*ind;
        int right = 2*ind + 1;


        //1 based me <= size
        //0 based me <size
        if(left<=size && arr[left]>arr[largest]){

            largest = left;

        }if(right<=size && arr[right]>arr[largest]){

            largest = right;

        }
        if(ind != largest){

            swap(arr[ind],arr[largest]);
            heapify(arr,n,largest);

        }
    }

    void print(){
        for(int i = 1;i <= size;i++){
            cout<<arr[i]<<" ";
        }cout<<endl;
    }
};
void heapify(int arr[],int n,int ind){

    int largest = ind;
    int left = 2*ind;
    int right = 2*ind + 1;

    if(left<=n && arr[left]>arr[largest]){

        largest = left;

    }if(right<=n && arr[right]>arr[largest]){

        largest = right;

    }
    if(ind != largest){

        swap(arr[ind],arr[largest]);
        heapify(arr,n,largest);

    }
}

void heapSort(int arr[],int n){

    int size = n;
    while(size>1){

        swap(arr[1],arr[size]);
        size--;
        heapify(arr,size,1);
    }

}

int main(){


    heap h;
    h.insert(40);
    h.insert(60);
    h.insert(55);
    h.insert(30);
    h.insert(20);
    h.print();

    h.deleteRoot();
    h.print();

    int arr[6] = {-1,54,53,55,52,50};
    int n = 5;
    for(int i = n/2;i>0;i--){
        heapify(arr,n,i);
    }
    for(int i = 1;i<=n;i++){
        cout<<arr[i]<<" ";
    }
    cout<<endl;
    heapSort(arr,n);
    for(int i = 1;i<=n;i++){
        cout<<arr[i]<<" ";
    }
    return 0;

}