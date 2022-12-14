//Name: David DeCosta
//Date: 11/9/2022
/*Program Description:
                        This program implements a NPDA that validates whether a password compiles
                        given requirements. The requirements as of now are the NDPA will accept
                        E={a,b,0,1}. The password can be arbitrarily long, will contain 1 letter and 1 digit,
                        and must contain more letters than digits.
*/

#include <iostream>
#include <map>
#include <stack>
#include <string>

using namespace std;

void checkAccepted(string password , map <tuple<string, char, string>, pair<string,string>> m, stack<string> myStack);

int main()
{

    string password;
    map <tuple<string, char, string>, pair<string,string>> justAMap;
    stack<string> myStack;

    justAMap[{"Q0", '1', "z"}] = {"Q0", "D"}; // push
    justAMap[{"Q0", '0', "z"}] = {"Q0", "D"}; // push
    justAMap[{"Q0", 'a', "z"}] = {"Q0", "L"}; // push
    justAMap[{"Q0", 'b', "z"}] = {"Q0", "L"}; // push
    justAMap[{"Q0", '1', "D"}] = {"Q0", "D"}; // push
    justAMap[{"Q0", '0', "D"}] = {"Q0", "D"}; // push
    justAMap[{"Q0", 'a', "L"}] = {"Q0", "L"}; // push
    justAMap[{"Q0", 'b', "L"}] = {"Q0", "L"}; // push
    justAMap[{"Q0", '1', "L"}] = {"Q1", "~"}; // pop
    justAMap[{"Q0", '0', "L"}] = {"Q1", "~"}; // pop
    justAMap[{"Q0", 'a', "D"}] = {"Q1", "~"}; // pop
    justAMap[{"Q0", 'b', "D"}] = {"Q1", "~"}; // pop
    justAMap[{"Q1", '1', "L"}] = {"Q1", "~"}; // pop
    justAMap[{"Q1", '0', "L"}] = {"Q1", "~"}; // pop
    justAMap[{"Q1", 'a', "D"}] = {"Q1", "~"}; // pop
    justAMap[{"Q1", 'b', "D"}] = {"Q1", "~"}; // pop
    justAMap[{"Q1", '1', "D"}] = {"Q1", "D"}; // push
    justAMap[{"Q1", '0', "D"}] = {"Q1", "D"}; // push'
    justAMap[{"Q1", 'a', "L"}] = {"Q1", "L"}; // push
    justAMap[{"Q1", 'b', "L"}] = {"Q1", "L"}; // push
    justAMap[{"Q1", '~', "L"}] = {"Q2", "L"}; // do nothing because final state

    justAMap[{"Q1", 'a', "z"}] = {"Q1", "L"}; // push
    justAMap[{"Q1", 'b', "z"}] = {"Q1", "L"}; // push
    justAMap[{"Q1", '0', "z"}] = {"Q1", "D"}; // push
    justAMap[{"Q1", '1', "z"}] = {"Q1", "D"}; // push


    while(true)
    {
        cout << "Enter a password (Ctrl^C to end): \n";
        cin >> password;
        for(int i = 0; i < password.length();i++)
        {
            if(password[i] != 'a' && password[i] != 'b' && password[i] != '0' && password[i] !='1')
            {
                exit(0);
            }
        }
           checkAccepted(password, justAMap,myStack);
    }


    return 0;
}

void checkAccepted(string password, map <tuple<string, char, string>, pair<string,string>> m, stack<string> myStack)
{

    char tempChar = '~';

    string currstate = "Q0";                                            //always start at Q0 but will update after every itteration
    string nextstate = " ";                                             //will be assigned by the make_tuple function return
    string finalState = "Q2";
    string thetop;                                                      //used to display the top of stack if need be
    pair<string, string> t;
    password.insert(0, "~");                                            //make the password terminate with lambda
    myStack.push("z");                                                  //start the stack with z on the top
    string c = myStack.top();

    cout <<"   (" + currstate + " , ";
    for(int i =0; i <password.length();i++)
    {
        cout << password[i+1];
    }
    cout << " , "<<myStack.top() << " )\n";

    int j;                                                               //for the loop
    for(j = password.length()-1; j >= 0; j--)
    {
        thetop = myStack.top();
        t = m[make_tuple(currstate,password[j], thetop)];
        nextstate = t.first;                                            //defined from the map returns the next state
        c = t.second;                                                   //defined from the map returns what should happen on the stack (push or pop)

        if(c == "L")
        {
            myStack.push("L");
        }
        else if(c == "D")
        {
            myStack.push("D");
        }
        else if(c == "~")
        {
            myStack.pop();
        }
        else
        {
            cout << "unable to push or pop \n";
        }

        thetop = myStack.top();
        stack<string> tempStack;                                            //used so i can traverse though the stack and display its contents without popping the original stack
        tempStack = myStack;

        password.pop_back();
        cout << "|- (" << nextstate << ", ";

        for(int i =0 ; i < password.length(); i++)
        {
            cout << password[i+1];                                          //so the tilda isnt displayed while there are chars left in the string to be processed
            
        }

        if(password.length() < 2)
        {
            cout << tempChar;                                               //once the whole string has been processed so that lambda is remaining
        }
        cout <<" , ";
        while(!tempStack.empty())                                          //this loop displays all the contents of the stack
        {
            cout << tempStack.top();
            tempStack.pop();
        }
        cout  << " )\n";

        currstate = nextstate;
    }

    
    if(currstate == finalState)
    {
        cout << " : Accepted \n";
    }
    else
    {
        cout << " : Rejected \n";
    }   

}

