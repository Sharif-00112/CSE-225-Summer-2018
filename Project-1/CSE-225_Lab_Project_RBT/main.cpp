#include <bits/stdc++.h>
#include "RedBlack.h"

using namespace std;

int main()
{
    int data,data2,data3;

    RedBlack rbTree1;
    RedBlack rbTree2;

    cout<<"Enter values for the tree :"<<endl;
    cin >> data;
    while (data != 0)
    {
        rbTree1.insertValue(data);
        cin >> data;
    }

    rbTree1.preorder();
    rbTree1.inorder();

    cout<<"Enter value to delete :"<<endl;
    cin>>data2;
    rbTree1.deleteValue(data2);

    rbTree1.inorder();
    rbTree1.preorder();

    rbTree1.searchValue();




    /*cin >> data;
    while (data != 0)
    {
        rbTree2.insertValue(data);
        cin >> data;
    }

    rbTree1.merge(rbTree2);
    rbTree1.preorder();*/

    return 0;
}
