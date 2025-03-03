class Solution {
public:
    unordered_map<string, unordered_map<string, double>> graph;

    // Function to perform DFS and find the value from src to dest
    double dfs(string src, string dest, unordered_set<string>& visited) {
        if (graph.find(src) == graph.end() || graph.find(dest) == graph.end()) 
            return -1.0;  // If either variable is missing, return -1.0

        if (src == dest) 
            return 1.0;  // x/x = 1.0

        visited.insert(src);
        for (auto& neighbor : graph[src]) {
            string nextNode = neighbor.first;
            double weight = neighbor.second;

            if (visited.find(nextNode) == visited.end()) {  // If not visited
                double result = dfs(nextNode, dest, visited);
                if (result != -1.0) 
                    return result * weight;
            }
        }
        return -1.0;  // If no valid path found
    }

    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
        int n = equations.size();

        // Step 1: Build the graph
        for (int i = 0; i < n; i++) {
            string A = equations[i][0], B = equations[i][1];
            double value = values[i];

            graph[A][B] = value;
            graph[B][A] = 1.0 / value;
        }

        // Step 2: Process Queries
        vector<double> results;
        for (auto& query : queries) {
            string C = query[0], D = query[1];
            unordered_set<string> visited;
            results.push_back(dfs(C, D, visited));
        }

        return results;
    }
};
