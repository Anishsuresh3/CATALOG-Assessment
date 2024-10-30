#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

double toBase10(const string& value, double base) {
    double result = 0;
    int power = 0;
    for (auto it = value.rbegin(); it != value.rend(); ++it) {
        int digit = (*it >= '0' && *it <= '9') ? (*it - '0') : (*it - 'A' + 10);
        result += digit * pow(base, power++);
    }
    return result;
}

double lagrangeInterpolation(const vector<pair<int, int>>& points) {
    double c = 0.0;
    int n = points.size();
    for (int i = 0; i < n; ++i) {
        double term = points[i].second;
        for (int j = 0; j < n; ++j) {
            if (i != j) {
                term *= (0.0 - points[j].first) / (points[i].first - points[j].first);
            }
        }
        c += term;
    }
    return c;
}

int main() {
    ifstream file("testcase.json");
    json jsonData;
    file>>jsonData;
    int n = jsonData["keys"]["n"];
    int k = jsonData["keys"]["k"];
    vector<pair<int, int>> points;

    for (auto it = jsonData.begin(); it != jsonData.end(); ++it) {
        if (it.key() != "keys") {
            int x = stoi(it.key());
            auto item = it.value();
            string b = item["base"];
            double base = stoi(b);
            string value = it.value()["value"];
            double y = toBase10(value, base);
            points.emplace_back(x, y);
        }
    }
    double constantTerm = lagrangeInterpolation(points);

    cout<<"The constant term c is: "<<constantTerm<< endl;

    return 0;
}