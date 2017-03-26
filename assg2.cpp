/**
*     CPL Assignment - 2
*     Name of the submitter- Anish Kelkar
*     Language of Implementation - C++
*     Data Structure Used - Linked List
*     Roll No. BT15CSE040
*/
#include<bits/stdc++.h>
using namespace std;
#define SIZE 100000
typedef struct node
{
    string memName;
    int startAddress;
    int sz;
    node* next;
}node;
/**
* Show the contents in the free list and the allocated list
*/
void showLists(node *freeList , node* allocList)
{
    node *it;
    it=freeList;
    cout<<"Free List -";
    while(it!=NULL)
    {
        cout<<"->"<<it->startAddress<<","<<it->sz+it->startAddress;
        it=it->next;
    }
    cout<<endl;
    it=allocList;
    cout<<"Alloc List -";
    while(it!=NULL)
    {
        cout<<"->"<<it->memName<<","<<it->startAddress<<","<<it->sz+it->startAddress;
        it=it->next;
    }
    cout<<endl;
}
/**
* Insert Node in Allocated List
*/
void insertNodeInAllocList(node** headAllocpptr, node** createpptr)
{
        node *it,*prev;
        it=*headAllocpptr;
        prev=NULL;
        int reached=0;
        while(it!=NULL && reached==0)
        {
            if(it->startAddress <((*createpptr)->startAddress))
            {
                prev=it;
                it=it->next;
            }
            else
            {
                reached=1;
            }
        }
        if(prev!=NULL)
        {
            prev->next=*createpptr;
            (*createpptr)->next=it;
        }
        else
        {
            (*createpptr)->next=it;
            *headAllocpptr=*createpptr;
        }


}
/**
* This function inserts the node in the free list
*/
void insertNodeInFreeList(node** freeListpptr, node** createpptr)
{
    int reached=0;
    node *it=*freeListpptr,*prev=NULL;
    while(it!=NULL && reached==0)
    {
        if(it->startAddress< (*createpptr)->startAddress)
        {
            prev=it;
            it=it->next;
        }
        else
        {
            reached=1;
        }
    }
    if(prev!=NULL)
    {
        if(prev->startAddress+prev->sz!=(*createpptr)->startAddress)
        {
            prev->next=*createpptr;
            (*createpptr)->next=it;
            if(it!=NULL)
            {
                if((*createpptr)->startAddress+(*createpptr)->sz==it->startAddress)
                {
                    (*createpptr)->sz+=it->sz;
                    (*createpptr)->next=it->next;
                    free(it);
                }
            }

        }
        else
        {
            prev->sz+=(*createpptr)->sz;
            prev->next=(*createpptr)->next;
            free(*createpptr);
            if(it!=NULL)
            {
                if(prev->startAddress + prev->sz==it->startAddress)
                {
                    prev->sz+=it->sz;
                    prev->next=it->next;
                    free(it);
                }
            }
        }
    }
    else
    {
        if((*createpptr)->startAddress+(*createpptr)->sz==it->startAddress )
        {
            (*createpptr)->sz+=it->sz;
            (*createpptr)->next=it->next;
            free(it);
        }
        else
        {
            (*createpptr)->next=it;
        }
        *freeListpptr=*createpptr;
    }
}
/**
* This function will create Node of both the types free as well as allocated
*/
node* createNode(string name, int sze,int SA)
{
    node* temp;
    temp=(node*)malloc(sizeof(node));
    temp->memName=name;
    temp->sz=sze;
    temp->startAddress=SA;
    temp->next=NULL;
    return temp;
}
/**
* This function is used to calculate the space required for the allocation of the memory.
*/
int getSpace(string dataType , int freq)
{
    int ret;
    if(dataType.compare("int[]")==0||dataType.compare("int[] ")==0 )
    {
        ret=sizeof(int);
    }
    else if(dataType.compare("float[]")==0||dataType.compare("float[] ")==0)
    {
        ret=sizeof(float);
    }
    else if(dataType.compare("char[]")==0 || dataType.compare("char[] ")==0)
    {
        ret=sizeof(char);
    }
    else if(dataType.compare("double[]")==0 || dataType.compare("double[] ")==0)
    {
        ret=sizeof(double);
    }
    else
    {
        ret=sizeof(long int);
    }
    ret*=freq;
    return ret;
}
/**
* This function is used add nodes to the allocatedList Linked List and if the free space is equal to the memory required,
* then the node from the freeList Linked List will be removed .
*/
bool allocateMem(node** headFreepptr,node** headAllocpptr,string inpName, int inpSize)
{
    bool retVal;
    node* create;
    node *it, *prev=NULL;;
    it=*headFreepptr;
    int allocated=0;
    while(it!=NULL && allocated==0)
    {
        if(it->sz>=inpSize)
        {
            create=createNode(inpName,inpSize,it->startAddress);
            insertNodeInAllocList(headAllocpptr,&create);
            it->startAddress+=inpSize;
            it->sz-=inpSize;
            if(it->sz==0)
            {
                if(it==*headFreepptr || prev==NULL)
                {
                    *headFreepptr=it->next;
                }
                else
                {
                    prev->next=it->next;
                }
                free(it);
            }
            allocated=1;
        }
        else
        {
            prev=it;
            it=it->next;
        }
    }
    if(it==NULL)
    {
        retVal=false;
    }
    else
    {
        retVal=true;

    }
    return retVal;
}
/**
* This function is used to free memory , and add the nodes to freeList and also perform compaction
* if two consecutive free nodes are adjacent to each other.
*/
bool freeMem(node** freeListpptr, node** allocatedListpptr, string inpName)
{
    bool retVal;
    node *it , *prev=NULL;
    it=*allocatedListpptr;
    int found=0;
    while(it!=NULL && found==0)
    {
        if(it->memName.compare(inpName)==0)
        {
            found=1;
            if(prev!=NULL)
            {
                prev->next=it->next;
            }
            else
            {
                *allocatedListpptr=it->next;
            }
            insertNodeInFreeList(freeListpptr,&it);
        }
        else
        {
            prev=it;
            it=it->next;
        }
    }
    if(it!=NULL)
    {
        retVal=true;
    }
    else
    {
        retVal=false;
    }
    return retVal;
}
/**
* Main Function
*/
int main()
{
    cout<<" NOTE:- to enter an array of datatype append the datatypeName string with '[]' "<<endl;
    cout<<" i.e to allocate memory for an int array.Enter 'int[]' instead of 'int'"<<endl<<endl<<endl;;
    node* freeList;
    node* allocatedList;
    freeList=createNode("-",SIZE,0);
    allocatedList=NULL;
    int flag;
    cout<<"To add the element press 1 else press 2 , to exit press 0"<<endl;;
    cin>>flag;
    string inpName,typeName;
    int space;
    int freq=1;
    while(flag!=0)
    {
        cout<<"READY!"<<endl;
        if(flag==1)
        {
            cout<<"Enter the data type name"<<endl;
            cin>>typeName;
            cout<<"Enter the variable identifier"<<endl;
            cin>>inpName;
            for(int it=0;it<typeName.size();it++)
            {
                typeName[it]=tolower(typeName[it]);
            }
            if(typeName[typeName.size()-1]!=']')
            {
                space=getSpace(typeName,1);
            }
            else
            {
                cout<<"Enter the length of the array"<<endl;
                cin>>freq;
                space=getSpace(inpName,freq);
            }
            bool success=allocateMem(&freeList,&allocatedList,inpName,space);
            if(success)
            {
                cout<<"SUCCESS!"<<endl;
            }
            else
            {
                cout<<"FAILURE!!"<<endl;
            }
        }
        else
        {
            cout<<"Enter the variable identifier"<<endl;
            cin>>inpName;
            bool success=freeMem(&freeList,&allocatedList,inpName);
            if(success)
            {
                cout<<"Freed"<<endl;
            }
            else
            {
                cout<<"Cannot be freed"<<endl;
            }
        }
        showLists(freeList,allocatedList);
        cout<<"To add the element press 1 else press 2 , to exit press 0"<<endl;
        cin>>flag;
    }
    return 0;
}
