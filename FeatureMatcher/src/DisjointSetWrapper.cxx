#include "DisjointSetWrapper.hxx"

using namespace std;




void AddNewDisjointSetWrapper(string parent, Hash &hash);
void AddNewElementToDisjointSet(string parent, string element, Hash &hash);




void AddNewDisjointSetWrapper(string parent, Hash &hash)
{
    DisjointSetWrapper newWrapper;
    vector<string> elements = vector<string>();
    newWrapper.Parent = parent;
    elements.push_back(parent);
    newWrapper.Elements = elements;
    (hash)[parent]=newWrapper;
}

void AddNewElementToDisjointSet(string parent, string element,Hash &hash)
{
    DisjointSetWrapper parentWrapper = (hash).at(parent);
    parentWrapper.Elements.push_back(element);
    (hash)[parent]=parentWrapper;
}
