#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using namespace std;

class StringArray {
private:
    vector<string> arr;
    int size;
public:
    StringArray(int len) : size(len) {
        arr.resize(len);
    }

    void set(int index, string val) {
        if (index < 0 || index >= size) {
            cerr << "Index out of bounds!" << endl;
            return;
        }
        arr[index] = val;
    }

    string get(int index) {
        if (index < 0 || index >= size) {
            cerr << "Index out of bounds!" << endl;
            return "";
        }
        return arr[index];
    }

    void print() {
        for (int i = 0; i < size; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }

    void setArray(StringArray& other) {
        if (size != other.size) {
            cerr << "Array sizes must be the same!" << endl;
            return;
        }
        for (int i = 0; i < size; i++) {
            arr[i] = other.get(i);
        }
    }

    void merge(StringArray& other) {
        vector<string> tmp = arr;
        for (int i = 0; i < other.size; i++) {
            if (find(tmp.begin(), tmp.end(), other.get(i)) == tmp.end()) {
                tmp.push_back(other.get(i));
            }
        }
        arr = tmp;
        size = arr.size();
    }

    string operator[](int index) {
        return get(index);
    }

    int getSize() {
        return size;
    }

    json toJson() {
        json j;
        j["size"] = size;
        j["arr"] = arr;
        return j;
    }

    void fromJson(json j) {
        size = j["size"];
        arr = j["arr"].get<vector<string>>();
    }

    void saveToJsonFile(string filename) {
        json j = toJson();
        ofstream fout(filename);
        fout << j;
        fout.close();
    }

    void loadFromJsonFile(string filename) {
        ifstream fin(filename);
        json j;
        fin >> j;
        fromJson(j);
        fin.close();
    }
};


int main() {
    StringArray arr1(5);
    arr1.set(0, "hello");
    arr1.set(1, "world");
    arr1.set(2, "foo");
    arr1.set(3, "bar");
    arr1.set(4, "baz");

    arr1.saveToJsonFile("arr1.json"); // Save arr1 to a JSON file

    StringArray arr2(5);
    arr2.loadFromJsonFile("arr1.json"); // Load arr1 from the JSON file
    arr2.print();

    return 0;
}
