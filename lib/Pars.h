#include <vector>
#include <string>

using namespace std;

class Pars {
public:
    string operation;
    vector<string> file_names;
    string arc_name;
    string arc_to_merge_1;
    string arc_to_merge_2;
    bool to_create = false;
    bool to_list = false;
    bool to_extract = false;
    bool to_append = false;
    bool to_delete = false;
    bool to_concatenate = false;
    void Parse(int argc, char **argv);
};

