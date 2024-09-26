#include <string>
#include <stack>
#include <iostream>

using namespace std;

class XmlChecker {
    enum STATUS {
        START, // Start a label
        END, // End of a label
    };

public:
    XmlChecker() {
        curr = STATUS::END;
        temp.clear();
    }
    void setInput(string input) {
        this->input = input;
    }
    bool validator() {
        for(string::size_type i = 0; i < input.size(); ++i) {
                switch(curr){
                    default:
                    case STATUS::END:
                        processStatusEnd(i);
                        break;
                    case STATUS::START:
                        if(!processStatusStart(i)){
                            return false;
                        }
                        break;
                }
            }
        return isDataEmpty();
    }

private:
    string input;
    stack<string> data;
    string temp;
    STATUS curr;
    void clearTemp() {
        this->temp.clear();
    }
    bool isDataEmpty() {
        return this->data.empty();
    }
    bool isLabelHead(char c) {
        return c == '<';
    }
    bool isLabelTail(char c) {
        return c == '>';
    }
    bool isSecondLabel() {
        return temp[0] == '/';
    }
    bool isLastDataEqualToTemp() {
        return data.top().compare(temp.substr(1))==0;
    }
    void removeLastData() {
        data.pop();
    }
    void setStatusStart() {
        curr = STATUS::START;
    }
    void setStatusEnd() {
        curr = STATUS::END;
    }
    void processStatusEnd(string::size_type idx) {
        if(isLabelHead(input[idx])){
            clearTemp();
            setStatusStart();
        } 
    }
    bool processStatusStart(string::size_type idx) {
        if(isLabelTail(input[idx])){
            if(!isDataEmpty() && isSecondLabel()){
                if(isLastDataEqualToTemp()) {
                    removeLastData();
                } else {
                    return false;
                }
            } else {
                data.push(temp);
            }
            clearTemp();
            setStatusEnd();
        } else {
            temp += input[idx];
        }
        return true;
    }
};

//feel free to add other classes/methods if you want
bool DetermineXml(const string &input)
{
    XmlChecker xmlChecker;
    xmlChecker.setInput(input);
    return xmlChecker.validator();
}
