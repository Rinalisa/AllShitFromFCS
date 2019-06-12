#include <iostream>
#include <fstream>                         
#include <string>                          
#include <vector>                          
    

class Nudes
{
public:
    std::vector<int> lt, rt;      // LefT = lt     RighT = rt
    int value;
    bool parent = false;
};


void goingThroughAllTree(int root, std::vector<Nudes> base, std::vector<int> &checkThis)
{
    if (base[root].lt.size() != 0)
        goingThroughAllTree(base[root].lt[0], base, checkThis);
    checkThis.push_back(base[root].value);
    if (base[root].rt.size() != 0)
        goingThroughAllTree(base[root].rt[0], base, checkThis);
}


int main()
{
    std::ifstream file;
    file.open("input.txt");
    int val, summary, id = 0;                  // val = value summary = all id = index
    char side;
    std::string str;
    std::vector<int> checkThis;
    getline(file, str);
    summary = int(str[0]) - 48;
    getline(file, str);
    std::vector<Nudes> base (summary);                  // place with all our Nodes of size set by first string
    int* i = new int(0);                             //did this only for reserving i, as it'd be easy for me, as i'd have "i" as cycle variable. Just my 
    while (id < str.length())                        //wish. 
    {
        val = int(str[id]) - 48;
        base[(*i)].value = val;
        id += 2;
        (*i)++;
    }
    delete i;
    while (getline(file, str))
    {
        id = int(str[0]) - 49;
        val = int(str[4]) - 49;
        side = str[2];
        if (side == 'L')
        {
            base[id].lt.push_back(val);
            base[val].parent = true;
        }
        else
        {
            base[id].rt.push_back(val);
            base[val].parent = true;
        }
    }
    int rootId;
    for (int i = 0; i < base.size(); i++)
        if (!base[i].parent)
        {
            rootId = i;
            break;
        }
    goingThroughAllTree(rootId, base, checkThis);
    bool result = false;
    for (int i = 1; i < checkThis.size(); i++)
        if (checkThis[i]<checkThis[i-1])
        {
            result = true;
        }
    if (result)
        std::cout << "NO";
    else
        std::cout << "YES";
    return 0;
}
