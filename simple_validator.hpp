#include <string>
#include <stack>
#include <iostream>

using namespace std;


enum STATUS {
    START, // Start a label
    END, // End of a label
};

//feel free to add other classes/methods if you want
bool DetermineXml(const string &input)
{
    stack<string> data;
    string temp;
    temp.clear();
    auto curr = STATUS::END;
    for(string::size_type i = 0; i < input.size(); ++i) {
        switch(curr){
            default:
            case STATUS::END:
                if(input[i]=='<'){
                    temp.clear();
                    curr = STATUS::START;
                } 
                break;
            case STATUS::START:
                if(input[i]=='>'){
                    if(!data.empty() && temp[0] == '/'){
                        if(data.top().compare(temp.substr(1))==0) {
                            data.pop();
                        } else {
                            return false;
                        }
                    } else {
                        data.push(temp);
                    }
                    temp.clear();
                    curr = STATUS::END;
                } else {
                    temp += input[i];
                }
                break;
        }
    }
    return data.empty();
}
