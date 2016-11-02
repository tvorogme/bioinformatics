#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include <set>
#include <cmath>
#include <set>
#include <algorithm>

using namespace std;
vector <pair<string, string>> in_vec;
vector <pair<int, string>> out_vecc;
set<int> whole_vgenes;


int intersection(set<int> const& first, vector<int> const& second) {
    int answer = 0;

    for (auto p: second){
        if (first.find(p) != first.end()){
            answer++;
        }
    }

    return answer;
}

vector<int> n_plet(string const& in, int n) {
    vector<int> in_vec;
    vector<int> out_vec;
    int now_element = 0;

    for (auto chr: in) {

        switch (chr) {
            case 'A':
                in_vec.push_back(0);
                break;
            case 'C':
                in_vec.push_back(1);
                break;
            case 'G':
                in_vec.push_back(2);
                break;
            case 'T':
                in_vec.push_back(3);
                break;
            default:
                break;
        }
    }

    int answer = 0;
    for (int stepen = 0; stepen < n; ++stepen) {

        int a = n - stepen - 1;

        answer += int(pow(4, stepen)) * in_vec[a];
    }
    out_vec.push_back(answer);

    for (int i = n; i < in_vec.size(); ++i) {
        int now_answer = (out_vec[now_element] % int(pow(4, n - 1))) + in_vec[i];
        out_vec.push_back(now_answer);
        now_element++;
    }

    return out_vec;
}

int main() {
    ifstream f1("IGHV-exp5.v2.fa");

    string current_name;
    string current_seq;

    while (f1) {
        string now_str;
        getline(f1, now_str);

        if (now_str[0] == '>') {
            if (current_seq != "") {
                in_vec.push_back(make_pair(current_seq, current_name));
            }
            current_name = now_str;
            current_seq = "";


        } else {
            current_seq += now_str;
        }
    }
    in_vec.push_back(make_pair(current_seq, current_name));


    for (auto p: in_vec) {
        vector<int> now = n_plet(p.first, 10);

        for (auto in: now) {
            whole_vgenes.insert(in);
        }
    }

    int a = 0;

    string first, second, third, fourth;

    while (cin) {
        cout << "\r" << a;
        a++;

        getline(cin, first);
        getline(cin, second);
        getline(cin, third);
        getline(cin, fourth);

        cout << "===========+++++++++++++============\n" << first << "\n" << second << "\n" << third << "\n" << fourth << "=========+++++++++++++++++===================" << endl;

        vector<int> now = n_plet(second, 10);
        out_vecc.push_back(make_pair(intersection(whole_vgenes,now), first));
    }


    cout << "\n" << "=============================" << "\n" << out_vecc.size() << endl;
    cout << "\n";
    for (auto p: out_vecc){
        cout << "------------" << "\n";
        cout << p.first << " " << p.second;
        cout << "------------" << "\n\n\n";
    }
    return 0;
}
