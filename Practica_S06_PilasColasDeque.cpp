// Practica S06 - Pilas, Colas y Deque (SIS210)
// C++ - balanceo + BFS + benchmark STL
// Compilar: g++ -std=c++17 -O2 -Wall -o s06 Practica_S06_PilasColasDeque.cpp && ./s06
#include <stack>
#include <queue>
#include <deque>
#include <vector>
#include <chrono>
#include <iostream>
#include <string>
#include <cassert>

using Clock = std::chrono::high_resolution_clock;

bool estaBalanceado(const std::string &s)
{
    std::stack<char> pila;
    for (char c : s)
    {
        if (c == '(' || c == '[' || c == '{')
            pila.push(c);
        else if (c == ')' || c == ']' || c == '}')
        {
            if (pila.empty())
                return false;
            char tope = pila.top();
            pila.pop();
            if ((c == ')' && tope != '(') || (c == ']' && tope != '[') || (c == '}' && tope != '{'))
                return false;
        }
    }
    return pila.empty();
}

// BFS en grafo de adyacencia
std::vector<int> bfs(const std::vector<std::vector<int>> &g, int inicio)
{
    int n = static_cast<int>(g.size());
    std::vector<bool> vis(n, false);
    std::queue<int> cola;
    std::vector<int> orden;
    vis[inicio] = true;
    cola.push(inicio);
    while (!cola.empty())
    {
        int u = cola.front();
        cola.pop();
        orden.push_back(u);
        for (int v : g[u])
            if (!vis[v])
            {
                vis[v] = true;
                cola.push(v);
            }
    }
    return orden;
}

int main()
{
    // --- Balanceo ---
    assert(estaBalanceado("([{}])") == true);
    assert(estaBalanceado("([)]") == false);
    assert(estaBalanceado("{[()]}") == true);
    assert(estaBalanceado("(((") == false);
    assert(estaBalanceado("") == true);
    std::cout << "Balanceo C++: OK\n";

    // --- BFS sobre la red de ciudades de Puno (mismo grafo de la Actividad 4) ---
    // 0:Puno 1:Juliaca 2:Ilave 3:Desaguadero 4:Yunguyo 5:Juli 6:Lampa 7:Azangaro 8:Huancane 9:Ayaviri
    std::vector<std::vector<int>> grafo = {
        {1, 2, 5}, {0, 6, 7}, {0, 3, 4}, {2, 4}, {2, 3, 5}, {0, 4}, {1}, {1, 8, 9}, {7}, {7}};
    std::vector<int> orden = bfs(grafo, 0);
    assert((orden == std::vector<int>{0, 1, 2, 5, 6, 7, 3, 4, 8, 9}));
    std::cout << "BFS C++ desde Puno:";
    for (int u : orden)
        std::cout << ' ' << u;
    std::cout << "  OK\n";

    // --- Benchmark: N operaciones en cola vs deque vs vector ---
    int N = 100'000;
    auto bench = [&](auto &c, auto push_fn, auto pop_fn, const char *nom)
    {
        auto t0 = Clock::now();
        for (int i = 0; i < N; i++)
            push_fn(c, i);
        for (int i = 0; i < N; i++)
            pop_fn(c);
        double ms = std::chrono::duration<double, std::milli>(Clock::now() - t0).count();
        std::cout << nom << " N=" << N << ": " << ms << "ms\n";
    };
    std::queue<int> q;
    std::deque<int> dq;
    std::vector<int> v;
    bench(q, [](auto &c, int x)
          { c.push(x); }, [](auto &c)
          { c.pop(); }, "queue");
    bench(dq, [](auto &c, int x)
          { c.push_back(x); }, [](auto &c)
          { c.pop_front(); }, "deque");
    bench(v, [](auto &c, int x)
          { c.push_back(x); }, [](auto &c)
          { c.erase(c.begin()); }, "vector (incorrecto para cola)");
    return 0;
}
