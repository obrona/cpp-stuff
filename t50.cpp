#include <unordered_map>
#include <ranges>
#include <iostream>

using namespace std;

int main() {
    unordered_map<string, int> mp = {
        {"a", 1},
        {"b", 2},
        {"c", 3}
    };

    auto even_values =
        mp
        | views::filter([](const auto& kv) {
              return kv.second % 2 == 0;
          });

    for (const auto& [k, v] : even_values) {
        cout << k << ' ' << v << '\n';
    }
}