#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct Node {
    string payload;
    Node* next;
};


// This acts like a call to 'new' with a constructor 
Node* newNode(const string& payload) {
  Node* newPlayerNode = new Node();

  newPlayerNode->payload = payload;
  newPlayerNode->next = nullptr; 

  return newPlayerNode;
}

// make a circular list with n amount of players
Node* loadGame(int numPlayers, const vector<string>& names) {
  Node* head = nullptr;
  Node* prev = nullptr;
  string name;

  for (int i = 0; i < numPlayers; ++i) {
    name = names.at(i);

	  // Special edge case when the list is initially empty
    if (head == nullptr) {
      head = newNode(name);
      prev = head;
    } 
    
    else {
      prev->next = newNode(name);
      prev = prev->next;
    }
  }

  if (prev != nullptr) { // make circular
    prev->next = head; 
  }

  return head;
}

// prints out list
void print(const Node* start) {
  const Node* curr = start;
  // We check curr against nullptr because we need to check that it is
  // a circular list, else it wont stop because curr will never equal start
  while (curr != nullptr) {
    cout << curr->payload << endl;
    curr = curr->next;
    if (curr == start) {
      break; // exit circular list
    }
  }
}

// run the game
Node* runGame(Node* start, int k) {
  Node* victim = start;
  Node* prev = nullptr;
  while (victim->next != victim) { // exit condition, last person standing
    for (int i = 0; i < k; ++i) { // find kth node
      prev = victim;
      victim = victim->next;
    }

    prev->next = victim->next; // delete kth node
    delete victim; 
    victim = prev->next;
  }

  return victim; // last person standing
}



/* Driver program to test above functions */
int main() {
    int n = 1, k = 1; // n = num names; k = num skips (minus 1)
    string name;
    vector<string> names;

    // get inputs
    cin >> n >> k;
    if (!cin) throw runtime_error("error reading n and k from input");
    
    while (cin >> name && name != ".") { names.push_back(name); } // EOF or . ends input

    // initialize and run game
    Node* startPerson = loadGame(n, names);
    Node* lastPerson = runGame(startPerson, k);

    if (lastPerson != nullptr) {
        cout << lastPerson->payload << " wins!" << endl;
    } else {
        cout << "error: null game" << endl;
    }

    return 0;
}

