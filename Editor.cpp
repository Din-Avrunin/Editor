#include "Editor.h"
#include "Document.h"
#include <iostream>
#include <algorithm>
#include <sstream>
using namespace std;
Document d;
string str;
Editor::Editor()
{
    cur=-1;
}
void Editor::loop(){
    while (true)
    { 
        int ind = 0; 
        getline(cin,str);
        if (str == "Q")
            break;
        else if (str == "%p")
            print();
        else if (str.at(0) == 's' && str.at(1) == '/')
        {
            int i = 2;
            string str1 = "";
            while (i < str.size() && str.at(i)!='/')
            {
                str1+=str.at(i);
                i++;
            }
            // cout<<"str1 is "<<str1<<endl;
            //make sure "new text" exist
            if (i >= str.size()-1)
                cout << "error";
            else
            {
                string str2 = "";
                i++;
                while (i<str.size() && str.at(i)!='/')
                {
                    str2 += str.at(i);
                    i++;
                }
                // cout<<"str2 is "<<str2<<endl;
                if (i >= str.size() || str.at(i) != '/')
                    cout << "error!";
                else
                {
                    // cout<<"cur is "<<cur<<endl;
                    // cout<<"vector size is "<<d.vec.size();
                    int index = d.vec.at(cur).find(str1);
                    // cout<<"index is "<<index<<endl;
                    if (index != -1)
                       d.vec.at(cur).replace(index,str1.size(),str2);
                    else
                        cout<<"didn't find old text in this line "<<endl;
                }
                
            }
            
        }
        else if (str.at(0) == '/')
                {
                    bool flag = false;
                    string tempStr = str.substr(1,str.size());
                    for (int i = cur; i < d.vec.size(); i++)
                    {
                        int index = d.vec.at(i).find(tempStr);
                        if (index != -1)
                        {
                            cout<<d.vec.at(i)<<endl;
                            cur=i;
                            flag = true;
                            break;
                        }
                    }
                    if (!flag)
                        cur=d.vec.size()-1;
                }
        else if (str.at(0) == '?')
                {
                    bool flag = false;
                    string tempStr = str.substr(1,str.size());
                    for (int i = 0; i <= cur; i++)
                    {
                        int index = d.vec.at(i).find(tempStr);
                        if (index != -1)
                        {
                            cout<<d.vec.at(i)<<endl;
                            cur=i;
                            flag = true;
                            break;
                        }
                    }
                    if (!flag)
                        cur=0;
                }
        else if (str == "c")
        {
            d.vec.erase(d.vec.begin()+(cur));
            while (true)
                {
                    getline(cin,str);
                    if (str != ".")
                    {
                        auto itPos = d.vec.begin()+cur;
                        auto newIt = d.vec.insert(itPos,str);
                                        cur++;
                    }
                    else
                        break;
                }
        }
        else if (str == "a")
            {
                while (true)
                {
                    getline(cin,str);
                    if (str != ".")
                    {
                        auto itPos = d.vec.begin()+cur+1;
                        auto newIt = d.vec.insert(itPos,str);
                        cur++;
                    }
                    else
                        break;
                }
            }
        else if (str == "i" && cur>=0)
            {
                while (true)
                {
                    getline(cin,str);
                    if (str.at(0) != '.')
                    {
                        auto itPos = d.vec.begin()+cur;
                        auto newIt = d.vec.insert(itPos,str);
                        cur++;
                    }
                    else
                        break;
                }
            }
        else if (str == "i" && cur==-1)
            {
                while (true)
                {
                    getline(cin,str);
                    if (str.at(0) != '.')
                    {
                        d.vec.push_back(str);
                        cur++;
                    }
                    else
                        break;
                }
            }
        //if there's a number then it can be one of the following 3 commands: 'n', 'd' or 'j'
        else if (isdigit(str.at(ind)))
        {
            while (ind < str.size() && isdigit(str.at(ind)))
            {
                ind++;
            }
            stringstream temp(str.substr(0,ind));
            int num = 0;
            temp >> num;
            if (num>d.vec.size() || num <=0)
            {
                cout << "num < 0 or num > vec.size()" << endl;
            }
            else if (str.at(ind) == 'n')
            {
                cout << num << "\t" << d.vec.at(num-1) << endl;
                cur=num-1;
            }
            else if (str.at(ind) == 'd')
            {
                d.vec.erase(d.vec.begin()+(num-1));
                cur=num-1;
            }
            else if (str.at(ind == ','))
            {
                ind++;
                int ind2 = ind;
                while (isdigit(str.at(ind)))
                    {
                       ind++;
                    }
                stringstream temp2 (str.substr(ind2,ind));
                int num2 = 0;
                temp2 >> num2;
                if (str.at(ind) == 'j')
                {
                    d.vec.at(num-1) += d.vec.at(num2-1);
                    d.vec.erase(d.vec.begin()+num2-1);
                    cur=num-1;
                }
                else
                {
                    cerr << "error in J function" << endl;
                }            
            }
            else
            {
                cerr << "Error in Editor - in n,d or j functions" << endl;
            }
        }
        else
            cout<<"ERROR";
        }
    }
    void isNumber(int num)
    {
        
    }
    void Editor::print()
    {
        for (int i = 0; i < d.vec.size(); i++)
            {
                cout << d.vec.at(i) << endl;
            }
        cur=d.vec.size()-1;
    }
    