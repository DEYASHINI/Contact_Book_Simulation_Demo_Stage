#include <iostream>
#include<bits/stdc++.h>
#include "demo.h"
typedef unsigned long long int ull;
using namespace std;

//total number of contacts in the directory


//latitude and longitude of contact
struct coordinates
{
 float x;
 float y;
};

//structure of contact
struct entity
{
    ull phone;
    string name;
    coordinates location;
    string email;
};

map<ull,entity> hashmap;
stack<entity> recents;
//BST Implementation
struct Node{
        Node(entity value): data(value), left(NULL), right(NULL) {}
        entity data;
        Node *left;
        Node *right;
};

class Trie
{
   public:
    bool isEndOfWord;
    unordered_map<char, Trie*> mp;

    Trie() {
      isEndOfWord=false;

    }

    void insertInTrie(const string &word)
   {

    Trie* tmp=this;
       for(char ch:word)
       {

           if(tmp->mp.find(ch)==tmp->mp.end())
             tmp->mp[ch]=new Trie;
           tmp=tmp->mp[ch];       }
        tmp->isEndOfWord=true;
    }


    bool search(string word)
    {
        Trie * cur=this;
        for(char ch:word)
        {
            cur=cur->mp[ch];
            if(!cur)
                return false;
        }
        if(cur->isEndOfWord)
            return true;
        else
            return false;
    }
int printAutoSuggestions(string s);
bool isLastNode(Trie *root);
void getSuggestions(Trie * root, string currPrefix);
Trie* removeFromTrie(Trie* root, string keyString,int depth);
void deleteTrie(string s);
};


Trie* Trie :: removeFromTrie(Trie* root, string keyString,int depth=0)
{
  if(!root)
        return NULL;
if(depth==keyString.size())
{
    if(root->isEndOfWord)
        root->isEndOfWord=false;
    if(isLastNode(root))
    {
        delete(root);
        root=NULL;
    }
    return root;
}

char ch=keyString[depth];
root->mp[ch]=removeFromTrie(root->mp[ch],keyString,depth+1);

if(isLastNode(root) && root->isEndOfWord==false)
 {
   delete(root);
    root=NULL;
 }
 return root;

}



void Trie :: deleteTrie(string s)
{
    Trie* root=this;
    root=removeFromTrie(root,s);
}


bool Trie ::  isLastNode(Trie *root)
{
    if(!(root->mp).empty())
        return 0;
    return 1;
}


void Trie :: getSuggestions(Trie * root, string currPrefix)
{
    if(root->isEndOfWord)
    {
        cout<<currPrefix<<endl;
    }
    if(isLastNode(root))
        return;

    for(auto it:root->mp)
    {
        currPrefix.push_back(it.first);
        getSuggestions(it.second,currPrefix);
        currPrefix.pop_back();
    }
}

int Trie :: printAutoSuggestions(string s)
{
    Trie * root=this;
    Trie *crawler=root;
    for(char ch:s)
    {
        if(!((crawler->mp)[ch]))
            return 0;
        crawler=(crawler->mp)[ch];
    }

    bool isEndingWord=((crawler->isEndOfWord)==true);
    bool isLastnode=isLastNode(crawler);

    if(isEndingWord && isLastnode)
    {
        cout<<s<<endl;
        return -1;
    }

    if(!isLastnode)
    {
        string prefix=s;
        getSuggestions(crawler,prefix);
    }
    return 1;
}



Trie* trieObj=new Trie();
/*struct TrieNode
{
 bool endOfWord;
    unordered_map<char, TrieNode*> mp;

};

TrieNode *root=NULL;

TrieNode* getNewNode()
{
    TrieNode* newnode=new TrieNode;
    newnode->endOfWord=false;
    return newnode;
}*/


void autoComplete(string s)
{
    cout<<endl<<endl<<"The auto-suggestions are as follows:"<<endl<<endl;
    bool comparison=trieObj->printAutoSuggestions(s);
    if(comparison==-1)
        cout<<endl<<endl<<"No other names with this prefix string"<<endl;
    else if(comparison==0)
       cout<<endl<<endl<<"No Contact Name with this prefix string"<<endl;

}
class BST
{   Node *_root;
        void insert(Node *treeNode, entity data);
        void deleteBST(Node *treeNode);
        void inOrder(Node * treeNode);
        void modifyData(Node *root,entity new_data);
        Node *findInorderSuccessor(Node *root);
        Node *deleteNode(Node *root,string searchName);
        Node* search(Node* root,string key)
     {

     if(root==NULL || (root->data).name==key)
       return root;


       if((root->data).name<key)
       return search(root->right,key);
       return search(root->left, key);
     }

public:

        BST();  // constructor
        ~BST(); // destractor

        void insert(entity data)
        {
            insert(_root,data);
        }
        void modify(entity new_data)
        {
            modifyData(_root,new_data);
        }
       void deleteBST()
        {
            deleteBST(_root);
        }

        void inOrder()
        {
            inOrder(_root);
        }


         void deletByKey(string searchName)
         {
           _root=deleteNode(_root,searchName);
         }


        bool isPresentBST(string searchName)
        {
            Node *res=search(_root,searchName);
            if(res==0)
                return false;
            else
                return true;
        }


        ull searchBST(string searchName)
        {
            Node * res=search(_root,searchName);
            if(res==NULL)
             {
                cout<<endl<<endl<<"No record found with that name"<<endl<<endl;
                return 0;
             }
            else
            {
              entity e=res->data;
              cout<<endl<<endl<<"Record Found!!!"<<endl;
              cout<<"The details of Searched Record are:"<<endl<<endl;
              cout<<"<Phone No.> : "<<e.phone<<" <Name> : "<<e.name<<" <Latitude> : "<<e.location.x<<" <Longitude> : "<<e.location.y<<" <Email> : "<<e.email<<endl<<endl;
              if(recents.empty())
              {
               recents.push(e);
               return e.phone;
              }
              if((recents.top()).phone!=e.phone)
              recents.push(e);
              return e.phone;
            }
        }
};

BST bstobj;


Node * BST :: findInorderSuccessor(Node *root)
{
    Node * curr=root;
    while(curr && curr->left!=NULL)
        curr=curr->left;
    return curr;
}


void BST :: modifyData(Node *root,entity new_data)
{
   if(root==NULL)
   return;
   if((root->data).name==new_data.name)
   {
     root->data=new_data;
     return;
   }

       if((root->data).name<new_data.name)
       modifyData(root->right,new_data);
       modifyData(root->left,new_data);
}



Node * BST :: deleteNode(Node *root,string searchName)
{
    if(root==NULL)
        return NULL;

    if(searchName<((root->data).name))
    root->left=deleteNode(root->left,searchName);

    else if(searchName>((root->data).name))
        root->right=deleteNode(root->right,searchName);
    else
    {
        if(root->left==NULL)
        {
            Node * tmp=root->right;
            delete(root);
            return tmp;
        }
        else if(root->right==NULL)
        {
            Node * tmp=root->left;
            delete(root);
            return tmp;
        }
        Node *tmp=findInorderSuccessor(root->right);
        root->data=tmp->data;
        root->right=deleteNode(root->right,(tmp->data).name);
    }
    return root;
}


 BST::BST()
{
        _root=NULL;
}


void BST :: insert(Node* treeNode,entity newData)
{

    if(treeNode==NULL)
    {
        treeNode=new Node(newData);
        _root=treeNode;

    }
    else
        {
          if(newData.name<=((treeNode->data).name))
          {
              if(!treeNode->left)
              {
                  Node* temp=new Node(newData);
                  treeNode->left=temp;
              }
              else
                insert(treeNode->left,newData);
          }
          else
          {
            if(!treeNode->right)
            {
                Node* temp=new Node(newData);
                treeNode->right=temp;
            }
            else
            insert(treeNode->right,newData);
          }

        }

}

    void BST::deleteBST(Node *treeNode)
{
        if(!treeNode)
                return;

        Node * curTreeNode = treeNode;
        Node * leftTreeNode = treeNode->left;
        Node * rightTreeNode = treeNode->right;
        delete(curTreeNode);
        deleteBST(leftTreeNode);
        deleteBST(rightTreeNode);
}

BST::~BST()
{
        deleteBST();
}

void BST::inOrder(Node * treeNode)
{
        if (!treeNode)
                return;
        inOrder(treeNode->left);
        cout <<"<Name> : "<<((treeNode->data).name)<<"  <Phone> : "<<((treeNode->data).phone)<<"  <Latitude> : "<<((treeNode->data).location.x)<<"  <Longitude> : "<<((treeNode->data).location.y)<<"  <Email> : "<<((treeNode->data).email)<<endl<<endl;
        inOrder(treeNode->right);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/*void insertInTrie(TrieNode *&root,const string &s)
{
  if(root==NULL)
      root=getNewNode();
  TrieNode *tmp=root;
  for(char ch:s)
  {
      if(tmp->mp.find(ch)==tmp->mp.end())
        tmp->mp[ch]=getNewNode();
      tmp=tmp->mp[ch];
  }

}*/
//to read record from contact.txt
vector<entity> readRecord(string filename)
{
    vector<entity> v;
    v.clear();
    ifstream fin;
    fin.open(filename,ios::in);
     if(!fin)
              cout<<"File can not open";

     else
     {
         while(!fin.eof())
     {
          entity e1;
      fin>>e1.phone;
      fin>>e1.name;
      if(e1.name=="")
        break;
      fin>>e1.location.x;
      fin>>e1.location.y;
      fin>>e1.email;
      v.push_back(e1);
     }
     }
    fin.close();

   return v;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//to print the read records
void printRecord(string filename)
{
    vector<entity> v=readRecord(filename);
    for(int i=0;i<v.size();i++)
        cout<<"<Phone> : "<<v[i].phone<<"  "<<"<Name> : "<<v[i].name<<"  <Latitude> : "<<v[i].location.x<<"  <Longitude> : "<<v[i].location.y<<"  <Email> : "<<v[i].email<<endl<<endl;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//to add initial contacts at start of application
void addInitialInformation(vector<entity>v,string filename)
{
    ofstream fout;
    fout.open(filename,ios::out);
     if(!fout)
              cout<<"File can not open"<<endl<<endl<<endl;
     else
     {
        for(int i=0;i<v.size();i++)
       fout<<v[i].phone<<" "<<v[i].name<<" "<<v[i].location.x<<" "<<v[i].location.y<<" "<<v[i].email<<endl;
     }
    fout.close();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//to load hash map from file
void loadHashMap(vector<entity> v)
{
   for(int i=0;i<v.size();i++)
   {
       hashmap[v[i].phone]=v[i];

   }

}

void deleteFromHashMap(ull searchNumber)
{
  hashmap.erase(searchNumber);
}


//to load binary search tree from file
void loadBinarySearchTree(vector<entity> v)
{

  for(int i=0;i<v.size();i++)
   bstobj.insert(v[i]);

  /*cout<<"BST records are: "<<endl;
  bstobj.inOrder();*/
}


//to load Trie Data Structure
void loadTrieDataStructure(vector<entity> v)
{
    for(int i=0;i<v.size();i++)
    {
        trieObj->insertInTrie(v[i].name);
    }
}



//to create the data structures
void loadDataStructures(string filename)
{
    vector<entity> v=readRecord(filename);
    if(v.empty())
    {
        cout<<endl<<"                        Account not found!!! Reopen application and try to sign up"<<endl<<endl;
        printExitMessage();
        exit(0);
    }
    loadHashMap(v);
    cout<<"Records loaded into hashmap successfully"<<endl;
    //map<ull,entity>:: iterator itr;

    /*for(itr=hashmap.begin();itr!=hashmap.end();itr++)
        cout<<(itr->first)<<"\t"<<((itr->second).name)<<" "<<((itr->second).location.x)<<" "<<((itr->second).location.y)<<" "<<((itr->second).email)<<endl;*/
        loadBinarySearchTree(v);
    cout<<"Records loaded into BST successfully"<<endl;

    loadTrieDataStructure(v);
    cout<<"Records loaded into Trie successfully"<<endl;
}

//to insert new data in hash map
void insertHashMap(entity new_contact)
{
    if(hashmap.find(new_contact.phone)!=hashmap.end())
    {

        cout<<"Contact already exists"<<endl;
        return;
    }
    hashmap[new_contact.phone]=new_contact;

}


void backUpData(string filename)
{
    ofstream fout;
    fout.open(filename,ios::out);
     if(!fout)
              cout<<"File can not open";
     else
     {
       for(auto it:hashmap)
       {   entity e=it.second;
           fout<<e.phone<<" "<<e.name<<" "<<e.location.x<<" "<<e.location.y<<" "<<e.email<<endl;
       }
     }
    fout.close();
}
//driver module
int main()
{
    ull userId=0;
    printMessage();
    int choice;
    printMenu();
    cin>>choice;
    cin.ignore();
    string filename="E:\\dsa project\\Contact Book Simulation\\ContactBook\\";
    if(choice==1)
    {
        cout<<endl<<endl<<"Enter your details and create an account to continue"<<endl;
        entity e_new;

        cout<<"Enter your name in Camel Case  :   ";
        getline(cin,e_new.name);

        cout<<"Enter phone number  :   ";
        cin>>e_new.phone;
        cout<<"Enter your location latitude  :   ";
        cin>>e_new.location.x;
        cout<<"Enter your location longitutde  :   ";
        cin>>e_new.location.y;
        cout<<"Enter your email id  :   ";
        cin>>e_new.email;
        userId=e_new.phone;
        cout<<endl<<endl;


        filename = filename + to_string(e_new.phone);
        filename=filename+".txt";

        //initialize file with initial contact records
        entity e1={9876509832,"Fire",{55.3,76.5},"fire@muni.com"};
        entity e2={8697213432,"Ambulance",{13.3,62.5},"ambulance@service.in"};
        entity e3={100,"Police",{34.8,95.3},"kolkatapolice@service.in"};
        vector<entity> v_initial;
        v_initial.push_back(e1);
        v_initial.push_back(e2);
        v_initial.push_back(e3);
        addInitialInformation(v_initial,filename);

        cout<<endl<<endl<<"The initial records accessible to you are:"<<endl<<endl<<endl;
        printRecord(filename);
        cout<<endl<<endl<<endl<<endl;
        //load data structures
        loadDataStructures(filename);
        cout<<endl<<endl;
        //add user details to BST and trie and hash map
         if(hashmap.find(e_new.phone)==hashmap.end())
        {
         insertHashMap(e_new);
         bstobj.insert(e_new);
         trieObj->insertInTrie(e_new.name);

        }
         backUpData(filename);
         cout<<"\n\n\n\n                      Successfully Signed Up...Account Created....."<<endl<<endl<<endl<<endl;
    }

    else if(choice==2)
    {
        ull ph;
        cout<<endl<<endl<<"Enter your phone number  :  ";
        cin>>ph;
        filename=filename+to_string(ph);
        filename=filename+".txt";
        cout<<endl<<endl;
        loadDataStructures(filename);
        cout<<"\n\n\n\n                       Successfully Logged In"<<endl<<endl<<endl;
       //search number if present in hashmap----already checked in loadDataStructures(filename)
       /*if(hashmap.find(ph)==hashmap.end())
       {
         cout<<"Record not found!!! Reopen application and try to sign up"<<endl;
         exit(0);
       }*/
       userId=ph;
    }
    else if(choice==3)
    {
       printExitMessage();
       exit(0);
    }
     cout<<"\n\n\n\n                     Welcome to Contact Simulation....Continue using the application\n\n\n\n";


     entity new_contact,recent_contact,search_contact,modified_contact;
     ull searchNumber;
     string recommend,searchName,modifiedName;
     ull searchPhone;
     int ctr=1,modify_choice,cancel_delete=0;
     stack<entity> temp;
     bool flag;

    while(1==1)
    {   printChoice();
        cin>>choice;
        cout<<endl<<endl;
        switch(choice)
        {

        case 1: cout<<"Enter details of the new contact you want to store"<<endl<<endl;
                cout<<"Enter contact name in CamelCase  :  ";
                cin.ignore();
                getline(cin,new_contact.name);
                cout<<"Enter contact phone number  :  ";
                cin>>new_contact.phone;
                cout<<"Enter contact location latitude :  ";
                cin>>new_contact.location.x;
                cout<<"Enter contact location longitutde  :  ";
                cin>>new_contact.location.y;
                cout<<"Enter contact email id  :  ";
                cin>>new_contact.email;
                cout<<endl<<endl;
                insertHashMap(new_contact);
                if(!bstobj.isPresentBST(new_contact.name))
                {
                    trieObj->insertInTrie(new_contact.name);
                }
                bstobj.insert(new_contact);
                //cout<<endl<<"Present : "<<(bstobj.isPresentBST(new_contact.name))<<endl;

                cout<<endl<<endl<<"                             Contact Added Successfully"<<endl;
                break;

        case 2:
                cout<<"Enter initials of name you are looking for to get suggestions : ";
                cin.ignore();
                getline(cin,recommend);
                autoComplete(recommend);
                break;
        case 3:
                cout<<"Enter name whose details to be retrieved and to place a call : ";
                cin.ignore();
                getline(cin,searchName);
                searchNumber=bstobj.searchBST(searchName);
                break;
        case 4:
                if(recents.empty())
                { cout<<endl<<endl<<"No people contacted today"<<endl;
                  break;
                }
                cout<<endl<<endl<<"The recent people contacted today are:"<<endl<<endl;
                ctr=1;
                while(ctr<=5 && !recents.empty())
                {
                  recent_contact=recents.top();
                  temp.push(recent_contact);
                  recents.pop();
                  cout<<recent_contact.name<<" : "<<recent_contact.phone<<"  "<<recent_contact.location.x<<"  "<<recent_contact.location.y<<"  "<<recent_contact.email<<endl;
                  ctr++;
                }
                while(!temp.empty())
                {
                    recents.push(temp.top());
                    temp.pop();
                }
                break;
        case 5: cout<<"Enter number to search  :  ";
                cin>>searchPhone;
                if(hashmap.find(searchPhone)==hashmap.end())
                    cout<<endl<<endl<<"SORRY !!!!  No such record exists"<<endl;
                else
                {
                    cout<<endl<<endl<<"Contact details with the input number is:"<<endl<<endl;
                    search_contact=hashmap[searchPhone];
                    if(searchPhone!=(recents.top()).phone)
                        recents.push(search_contact);
                    cout<<"<Phone> : "<<search_contact.phone<<" <Name> : "<<search_contact.name<<" <Latitude> : "<<search_contact.location.x<<" <Longitude> : "<<search_contact.location.y<<" <Email> : "<<search_contact.email<<endl;
                }
                break;

        case 6: cout<<"The sorted contact details in ascending order by name is:"<<endl<<endl<<endl;
                bstobj.inOrder();

                break;
        case 7: //can't delete r modify duplicate records of your own account
                cout<<endl<<endl<<"CAUTION !!! The first entry with the given name will be deleted"<<endl;
                cout<<endl<<"Enter the name to be deleted from the contact book  :  ";

                cin.ignore();
                getline(cin,searchName);

                flag=bstobj.isPresentBST(searchName);

                if(flag)
                cout<<endl<<endl<<"The record to be deleted is:"<<endl;
                searchNumber=bstobj.searchBST(searchName);
                if(flag)
                {
                cout<<"\n To cancel deletion,  enter 1 else any other number"<<endl<<endl;
                cin>>cancel_delete;
                if(cancel_delete==1)
                {
                    cout<<"****************                  Deletion Canceled                  ****************************"<<endl<<endl;
                    break;
                }


                if(searchNumber==userId)
                {
                    cout<<"                                    OOPS !!!! Can't delete your own account now!!!!!"<<endl;
                    cout<<"                                    To delete your account, chose option 9 "<<endl;
                    break;
                }



                cout<<endl<<" *********        Record is being deleted permanently    *********"<<endl<<endl;
                }
                //delete from hashmap
                if(searchNumber!=0)
               {
                 deleteFromHashMap(searchNumber);
                //delete from BST
                 bstobj.deletByKey(searchName);
                 //cout<<endl<<"Deletion from BST and Hashmap successful"<<endl;


                //delete from Trie
                if(!bstobj.isPresentBST(searchName)==0) //other entries dont exist by that name then only delete from trie
                {trieObj->deleteTrie(searchName);
                  //cout<<"data deleted from Trie successfully"<<endl;
                }
                cout<<endl<<"Deletion Successful"<<endl;
               }
                break;
        case 8: //can't delete r modify duplicate records of your own account
                cout<<"Enter name whose details to be modified  :  ";
                cin.ignore();
                getline(cin,searchName);
                flag=bstobj.isPresentBST(searchName);

                if(flag)
                cout<<endl<<endl<<"The record to be modified is:"<<endl;
                searchNumber=bstobj.searchBST(searchName);

                if(searchNumber==0)
                {
                  //cout<<"No such Record found so try something else!!"<<endl;
                  break;
                }
                if(searchNumber==userId)
                {
                  cout<<"                                    OOPS !!!! Can't modify your own account now!!!!!"<<endl;
                  cout<<"                                    Delete your account from option 9 and create new modified account"<<endl;
                  break;
                }

                modified_contact=hashmap[searchNumber];
                cout<<"1. To modify name"<<endl;
                cout<<"2. To modify phone number"<<endl;
                cout<<"3. To modify location latitude"<<endl;
                cout<<"4. To modify longitude location"<<endl;
                cout<<"5. To modify email"<<endl;
                cout<<"6.To cancel modification"<<endl;
                cout<<"Enter your choice  :  ";
                 cin>>modify_choice;
                 if(modify_choice==1)
                 {
                     cout<<"Enter modified name  :  ";
                     cin.ignore();
                     getline(cin,(modified_contact.name));
                     modifiedName=modified_contact.name;
                 }
                 else if(modify_choice==2)
                 {
                   cout<<"Enter modified phone number :  ";
                     cin>>modified_contact.phone;
                 }
                 else if(modify_choice==3)
                 {
                     cout<<"Enter modified location latitude  :  ";
                     cin>>modified_contact.location.x;
                 }
                 else if(modify_choice==4)
                 {
                     cout<<"Enter modified location longitude  :  ";
                     cin>>modified_contact.location.y;
                 }
                 else if(modify_choice==5)
                 {
                     cout<<"Enter modified email   :  ";
                     cin>>modified_contact.email;
                 }
                 else
                 {
                     cout<<"Invalid choice entered";
                     break;
                 }
                if(modify_choice==1)
                {   //update hashmap
                    hashmap[searchNumber]=modified_contact;
                   // cout<<"Hashmap updated"<<endl;

                   //delete from BST
                    bstobj.deletByKey(searchName);
                    //cout<<"Deleted from BST"<<endl;

                    if(!bstobj.isPresentBST(searchName))
                   {
                       trieObj->deleteTrie(searchName);
                    //cout<<"data deleted from Trie"<<endl;
                    //insert into trie
                   }
                    trieObj->insertInTrie(modifiedName);
                    //cout<<"Inserted new name back in trie"<<endl;

                    //new insertion in BST
                    bstobj.insert(modified_contact);
                    //cout<<"Inserted new data in BST"<<endl;
                    //delete from trie

                }
                else if(modify_choice==2)
                {
                    //remove from hashmap
                    deleteFromHashMap(searchNumber);
                    //insert into hashmap
                    insertHashMap(modified_contact);
                    //modify bst
                    bstobj.modify(modified_contact);
                }

                else
                {
                    //update hashmap
                  hashmap[searchNumber]=modified_contact;
                  //modify bst
                  bstobj.modify(modified_contact);
                }
                cout<<endl<<endl<<"Modification Successful"<<endl;
                break;
        case 9:
               if(remove(filename.c_str())!=0)
		        perror("                                          File deletion failed!!!!");
	            else
		         cout<<endl<<endl<<"Contact File and account deleted successfully"<<endl<<endl<<endl;
		         printExitMessage();
		         exit(0);
		         break;
        case 10: printExitMessage();
                 backUpData(filename);
                 exit(0);
                 break;
        }
    }
   return 0;
}
