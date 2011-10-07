#include <string>
#include <vector>
#include <boost/unordered_map.hpp>
using namespace std;

typedef struct DisjointSetWrapper
{
    string Parent;
    vector<string> Elements;

} DisjointSetWrapper;

typedef boost::unordered_map<std::string,DisjointSetWrapper> Hash;

void AddNewDisjointSetWrapper(string parent, Hash &hash);
void AddNewElementToDisjointSet(string parent, string element, Hash &hash);

