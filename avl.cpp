#include <iostream>
#include <tuple>
#include <string>
using namespace std;
struct data
{
    basic_string<char> symbols;
    int numbers;
    int count;
};

bool operator < (const data &a, const data &b) {
    return std::tie(a.numbers, a.symbols) < std::tie(b.numbers, b.symbols);
}
bool operator > (const data &a, const data &b) { return b < a; }
bool operator <= (const data &a, const data &b) { return !(b < a); }
bool operator >= (const data &a, const data &b) { return !(a < b); }
bool operator == (const data &a, const data &b) { return !(a < b) && !(b < a); }

struct Node
{
    data key;
    struct Node* left;
    struct Node* right;
    char balance;
    Node(data newKey){key = newKey; left = nullptr; right = nullptr; balance = 0;}
};

void BalanceL(Node* &root, bool &h)
{
    Node* p1;
    Node* p2;
    char bal1, bal2;
    switch (root -> balance)
    {
        case -1:
            root -> balance = 0;
            break;
        case 0:
            root -> balance = 1;
            h = false;
            break;
        case 1:
            p1 = root -> right; bal1 = p1 ->balance;
            if (bal1 >= 0)
            {
                root -> right = p1 -> left;
                p1 -> left = root;
                if (bal1 == 0){
                    root -> balance = 1;
                    p1 -> balance = -1;
                    h = false;
                }
                else
                {
                    root -> balance = 0;
                    p1 -> balance = 0;
                }
                root = p1;
            }
            else
            {
                p2 = p1 ->left; bal2 = p2 -> balance;
                p1 -> left = p2 -> right; p2 -> right = p1;
                root -> right = p2 -> left; p2 -> left = root;
                if (bal2 == 1) root ->balance = -1;
                else root -> balance = 0;
                if (bal2 == -1) p1 -> balance = 1;
                else p1 -> balance = 0;
                root = p2;
                p2 -> balance = 0;
            }

    }
}

void BalanceR(Node* &root, bool &h)
{
    Node* p1;
    Node* p2;
    char bal1, bal2;
    switch (root -> balance)
    {
        case 1:
            root -> balance = 0;
            break;
        case 0:
            root -> balance = 1;
            h = false;
            break;
        case -1:
            p1 = root -> left; bal1 = p1 ->balance;
            if (bal1 <= 0)
            {
                root -> left = p1 -> right;
                p1 -> right = root;
                if (bal1 == 0){
                    root -> balance = -1;
                    p1 -> balance = 1;
                    h = false;
                }
                else
                {
                    root -> balance = 0;
                    p1 -> balance = 0;
                }
                root = p1;
            }
            else
            {
                p2 = p1 ->right; bal2 = p2 -> balance;
                p1 -> right = p2 -> left; p2 -> left = p1;
                root -> left = p2 -> right; p2 -> right = root;
                if (bal2 == -1) root ->balance = 1;
                else root -> balance = 0;
                if (bal2 == 1) p1 -> balance = -1;
                else p1 -> balance = 0;
                root = p2;
                p2 -> balance = 0;
            }

    }
}

void Add(Node* &root, bool &h, data key)
{
    Node* p1;
    Node* p2;
    if (!root)
    {
        root = new Node(key);
        h = true;
    }
    else if (root -> key >= key)
    {
        Add(root -> left, h, key);
        if (h)
        {
            if (root->balance == 1){root->balance =0; h = false;}
            else if (root -> balance == 0){root -> balance = -1;}
            else
            {
                p1 = root->left;
                if (p1->balance == -1)
                {
                    root->left = p1->right;
                    p1->right = root;
                    root->balance = 0;
                    root = p1;
                }
                else
                {
                    p2 = p1->right;
                    p1->right = p2->left;
                    p2->left = p1;
                    root->left = p2->right;
                    p2->right = root;
                    if (p2->balance == -1)
                    {
                        root->balance = 1;
                    }
                    else
                    {
                        root->balance = 0;
                    }
                    if (p2->balance == 1)
                    {
                        p1->balance = -1;
                    }
                    else
                    {
                        p1->balance = 0;
                    }
                    root = p2;
                }
                root->balance = 0;
                h = false;
            }
        }
    }
    else if (root -> key < key)
    {
        Add(root -> right, h, key);
        if (h)
        {
            if (root->balance == -1){root->balance =0; h = false;}
            else if (root -> balance == 0){root -> balance = 1;}
            else
            {
                p1 = root->right;
                if (p1->balance == 1)
                {
                    root->right = p1->left;
                    p1->left = root;
                    root->balance = 0;
                    root = p1;
                }
                else
                {
                    p2 = p1->left;
                    p1->left = p2->right;
                    p2->right = p1;
                    root->right = p2->left;
                    p2->left = root;

                    if (p2->balance == 1)
                    {
                        root->balance = -1;
                    }
                    else
                    {
                        root->balance = 0;
                    }
                    if (p2->balance == -1)
                    {
                        p1->balance = 1;
                    }
                    else
                    {
                        p1->balance = 0;
                    }
                    root = p2;
                }

                root->balance = 0;
                h = false;

            }
        }
    }
    if (key == root -> key) {
        root -> key.count++;
    }
}

void Del(Node* &r, Node* &q, bool &h)
{
    if (r -> left)
    {
        Del(r -> left, q, h);
        if (h)BalanceL(r, h);
    }
    else
    {
        q->key = r->key;
        q = r;
        r = r->right;
        h = true;
    }
}

void Delete(Node* &root, bool &h, data key)
{
    Node* q;
    if(!root){}
    else if (root -> key > key)
    {
        Delete(root -> left, h, key);
        if (h) BalanceL(root, h);
    }
    else if (root -> key < key)
    {
        Delete(root -> right, h, key);
        if (h) BalanceR(root, h);
    }
    else
    {
        q = root;
        if (!q -> right){root = q -> left; h = true;}
        else if (!q -> left){root = q -> right; h = true;}
        else
        {
            Del(q -> left, q, h);
            if (h) BalanceL(root, h);
        }
    }

}

Node * MemoryClear(Node* &root)
{
    if(root -> left)MemoryClear(root->left);
    if(root->right)MemoryClear(root->right);
    delete root;
    root = nullptr;
}

void SearchElement(Node* root, data key)
{
    if(!root)
        if (root -> key == key)std::cout << "Element was found by address: " << root << std::endl;
    if(root -> left)SearchElement(root->left, key);
    if(root->right)SearchElement(root->right, key);
}

string FlightNumberToString(data k){
    string res;
    res="["+k.symbols +':'+ to_string(k.numbers)+"]";
    return res;
}

void PrintTree(Node* root, int h)
{
    if(root)
    {
        PrintTree(root -> right, h+4);
        for (int i = 1; i <= h; i++)std::cout << " ";
        if (root->key.count > 1) cout << "[" << root->key.count << "]";
        cout << root -> key.symbols << "." << root -> key.numbers << endl;
        PrintTree(root -> left, h+4);
    }
}

int TreeLevel(Node* root)
{
    if(root)return std::max(root->left?TreeLevel(root->left)+1:1, root->right?TreeLevel(root->right)+1:1);
    else return 0;
}
const int ch_max = 26;
string RandomString(int ch)
{
    char alpha[ch_max] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g',
                           'h', 'i', 'j', 'k', 'l', 'm', 'n',
                           'o', 'p', 'q', 'r', 's', 't', 'u',
                           'v', 'w', 'x', 'y', 'z' };
    string result = "";
    for (int i = 0; i<ch; i++)
        result = result + alpha[rand() % ch_max];

    return result;
}
int main()
{   srand(time(NULL));
    int ch = 2;
    data key{};
    Node* tree1 = nullptr;
    bool h = false;
    for(int i = 0; i <= 15; i++) {
        key.symbols = RandomString(2); key.numbers = 1000+i;
        Add(tree1,h,key);
    }
    PrintTree(tree1, 1);
    MemoryClear(tree1);
    for(int i = 0; i <= 15; i++) {
        key.symbols = RandomString(2); key.numbers = 2000-i;
        Add(tree1,h,key);
    }
    PrintTree(tree1,h);
    for(int i = 0; i <= 40; i++) {
        key.symbols = RandomString(2); key.numbers = 1000+i;
        Delete(tree1,h,key);
    }
    cout << "==========================="<< endl;
    PrintTree(tree1,1);
  
}

