//Nome: Bernardo Rizzone Sousa Vale de Araujo
//Matricula: 232013194

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Conjunto 
{
private:
    vector<int> elementos;

public:
    // (b) Cria um conjunto vazio
    Conjunto() {}

    // (c) Insere um elemento no conjunto
    void insere(int valor) 
    {
        if (!pertence(valor)) 
        {
            elementos.push_back(valor);
        }
    }

    // (d) Remove um elemento do conjunto
    void remove(int valor) 
    {
        auto it = find(elementos.begin(), elementos.end(), valor);
        if (it != elementos.end())
        {
            elementos.erase(it);
        }
    }

    // (e) Intersecção
    Conjunto intersecao(const Conjunto& outro) const 
    {
        Conjunto resultado;
        for (int valor : elementos) 
        {
            if (outro.pertence(valor)) 
            {
                resultado.insere(valor);
            }
        }
        return resultado;
    }

    // (f) Diferença
    Conjunto diferenca(const Conjunto& outro) const 
    {
        Conjunto resultado;
        for (int valor : elementos) 
        {
            if (!outro.pertence(valor)) 
            {
                resultado.insere(valor);
            }
        }
        return resultado;
    }

    // (g) Testa se um número pertence ao conjunto
    bool pertence(int valor) const 
    {
        return find(elementos.begin(), elementos.end(), valor) != elementos.end();
    }

    // (h) Menor valor e Maior valor
    int menor() const 
    {
        if (elementos.empty()) throw runtime_error("Conjunto vazio");
        return *min_element(elementos.begin(), elementos.end());
    }

    int maior() const 
    {
        if (elementos.empty()) throw runtime_error("Conjunto vazio");
        return *max_element(elementos.begin(), elementos.end());
    }

    // (i) Testa se os conjuntos são iguais
    bool igual(const Conjunto& outro) const 
    {
        if (elementos.size() != outro.elementos.size()) return false;
        for (int valor : elementos) 
        {
            if (!outro.pertence(valor)) return false;
        }
        return true;
    }

    // (j) Tamanho
    size_t tamanho() const 
    {
        return elementos.size();
    }

    // (k) Testa se o conjunto é vazio
    bool vazio() const 
    {
        return elementos.empty();
    }

    // Método para exibir os elementos do conjunto (opcional)
    void exibir() const 
    {
        cout << "{ ";
        for (int valor : elementos) {
            cout << valor << " ";
        }
        cout << "}" << endl;
    }
};

int main() 
{
    Conjunto conjunto1;
    conjunto1.insere(1);
    conjunto1.insere(2);
    conjunto1.insere(3);
    cout << "Conjunto 1: ";
    conjunto1.exibir();

    Conjunto conjunto2;
    conjunto2.insere(2);
    conjunto2.insere(3);
    conjunto2.insere(4);
    cout << "Conjunto 2: ";
    conjunto2.exibir();

    // União
    Conjunto uniao;
    for (int i = 0; i < conjunto1.tamanho(); i++)
    {
        uniao.insere(conjunto1.pertence(i));
    }
    for (int i = 0; i < conjunto2.tamanho(); i++) 
    {
        uniao.insere(conjunto2.pertence(i));
    }
    cout << "União: ";
    uniao.exibir();

    // Intersecção
    Conjunto intersecao = conjunto1.intersecao(conjunto2);
    cout << "Intersecção: ";
    intersecao.exibir();

    // Diferença
    Conjunto diferenca = conjunto1.diferenca(conjunto2);
    cout << "Diferença (Conjunto 1 - Conjunto 2): ";
    diferenca.exibir();

    // Testa se um número pertence ao conjunto
    cout << "O número 2 pertence ao Conjunto 1? " << (conjunto1.pertence(2) ? "Sim" : "Não") << endl;

    // Menor e maior valor
    cout << "Menor valor do Conjunto 1: " << conjunto1.menor() << endl;
    

    // Testa se os conjuntos são iguais
    cout << "Os conjuntos são iguais? " << (conjunto1.igual(conjunto2) ? "Sim" : "Não") << endl;

    // Tamanho
    cout << "Tamanho do Conjunto 1: " << conjunto1.tamanho() << endl;

    // Testa se o conjunto é vazio
    cout << "O Conjunto 1 é vazio? " << (conjunto1.vazio() ? "Sim" : "Não") << endl;

    return 0;
}