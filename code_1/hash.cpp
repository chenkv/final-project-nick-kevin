// CPP program to implement hashing with chaining
#include<iostream>
#include "hash.hpp"


using namespace std;

HashNode* HashTable::createNode(string key, HashNode* next)
{
    HashNode* nw = NULL;
    return nw;
}

HashTable::HashTable(int bsize)
{
   tableSize = bsize;
   table = new HashNode*[bsize];
   for(int i = 0; i < bsize; i++){
       table[i] = NULL;
   }
}

//function to calculate hash function
unsigned int HashTable::hashFunction(string s)
{
    int sum=0, index=0;
    for(string::size_type i=0; i < s.length(); i++){
        sum += s[i];
    }
    index = sum % tableSize;
    return index;
}

// TODO Complete this function
//function to search
HashNode* HashTable::searchItem(string key)
{
   HashNode* ptr = table[hashFunction(key)]; //Get the index for the key

   if(ptr == NULL){
       return NULL;
   }

   while(ptr && ptr->key != key){
       ptr = ptr->next;
   }

    //TODO
    return ptr;
}

//TODO Complete this function
//function to insert
bool HashTable::insertItem(string key, int cNum)
{
    HashNode* tmp = searchItem(key);

    if(tmp){
        tmp->commitNums.push_back(cNum);
        return true;
    }

    int index = hashFunction(key);

    HashNode* insert = new HashNode();
    insert->key = key;
    insert->commitNums.push_back(cNum);

    HashNode* ptr = table[index];
    if(ptr){
        while(ptr->next != NULL){
            ptr = ptr->next;
        }
        ptr->next = insert;
        return true;
    }else{
        table[index] = insert;
        return true;
    }

    //TODO
    return false;
}


// function to display hash table //
/* assume the table size is 5. For each bucket it will show the 
** the string key and the commit number (separated by comma) within parenthesis
** e.g. the key is science and commit numbers are 1 and 4. The key science
** is hashed to position 0. So the print format will be-

0|| science(1,4,)
1|| 
2|| 
3|| 
4|| difficult(3,)-->fun(2,)-->computer(0,)

*/
void HashTable::printTable()
{
    for(int i = 0;  i< tableSize; i++){
        cout << i << "|| ";
        
        HashNode* ptr = table[i];
        while(ptr){
            cout << ptr->key << "(";
            for(int j = 0; j < ptr->commitNums.size(); j++){
                cout << ptr->commitNums.at(j) << ",";
            }
            cout << ")";
        }
        cout << endl;
    }
 }
