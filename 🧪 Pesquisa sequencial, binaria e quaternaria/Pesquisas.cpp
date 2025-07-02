//////////Bernardo Rizzone Sousa Vale de Araujo
////////// Matricula: 232013194





#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>


using namespace std;

class Pesquisa {
public:
    // Função de pesquisa sequencial
    void pesquisaSequencial(const vector<unsigned long>& array, const vector<unsigned long>& valores) {
        for (unsigned long valor : valores) {
            auto start = chrono::high_resolution_clock::now(); // Inicia a contagem do tempo
            for (unsigned long num : array) {
                if (num == valor) {
                    break; // Interrompe a busca se o valor for encontrado
                }
            }
            auto end = chrono::high_resolution_clock::now(); // Termina a contagem do tempo
            chrono::duration<double> duracao = end - start;
            cout << "Tempo para encontrar " << valor << " (Sequencial): " << duracao.count() << " segundos" << endl;
        }
    }

    // Função de pesquisa binária
    void pesquisaBinaria(const vector<unsigned long>& array, const vector<unsigned long>& valores) {
        for (unsigned long valor : valores) {
            auto start = chrono::high_resolution_clock::now(); // Inicia a contagem do tempo
            binary_search(array.begin(), array.end(), valor); // Realiza a busca binária
            auto end = chrono::high_resolution_clock::now(); // Termina a contagem do tempo
            chrono::duration<double> duracao = end - start;
            cout << "Tempo para encontrar " << valor << " (Binaria): " << duracao.count() << " segundos" << endl;
        }
    }

    // Função de pesquisa quaternária
    void pesquisaQuaternaria(const vector<unsigned long>& array, const vector<unsigned long>& valores) {
        for (unsigned long valor : valores) {
            auto start = chrono::high_resolution_clock::now(); // Inicia a contagem do tempo
            quaternarySearch(array, 0, array.size() - 1, valor); // Realiza a busca quaternária
            auto end = chrono::high_resolution_clock::now(); // Termina a contagem do tempo
            chrono::duration<double> duracao = end - start;
            cout << "Tempo para encontrar " << valor << " (Quaternaria): " << duracao.count() << " segundos" << endl;
        }
    }

private:
    
    bool quaternarySearch(const vector<unsigned long>& array, int left, int right, unsigned long valor) {
        if (left > right) {
            return false; // Retorna false se o valor não for encontrado
        }
        int mid1 = left + (right - left) / 4; // Calcula o primeiro ponto médio
        int mid2 = left + (right - left) / 2; // Calcula o segundo ponto médio
        int mid3 = left + 3 * (right - left) / 4; // Calcula o terceiro ponto médio

        if (array[mid1] == valor) return true; // Verifica o primeiro ponto médio
        if (array[mid2] == valor) return true; // Verifica o segundo ponto médio
        if (array[mid3] == valor) return true; // Verifica o terceiro ponto médio

        // Realiza a busca nos quatro quadrantes
        if (valor < array[mid1]) return quaternarySearch(array, left, mid1 - 1, valor);
        if (valor < array[mid2]) return quaternarySearch(array, mid1 + 1, mid2 - 1, valor);
        if (valor < array[mid3]) return quaternarySearch(array, mid2 + 1, mid3 - 1, valor);
        return quaternarySearch(array, mid3 + 1, right, valor);
    }
};

int main() {
    vector<unsigned long> array(100000000L); // Cria um vetor com 1.000.000 de elementos
    for (unsigned long i = 0; i < 100000000L; ++i) {
        array[i] = i + 1; // Inicializa o vetor com valores de 1 a 1.000.000
    }
    vector<unsigned long> valores = {1L, 30000000L, 60000000L, 120000000L, 240000000L}; // Valores a serem buscados

    Pesquisa p; // Cria um objeto da classe Pesquisa
    p.pesquisaSequencial(array, valores); // Realiza a pesquisa sequencial
    p.pesquisaBinaria(array, valores); // Realiza a pesquisa binária
    p.pesquisaQuaternaria(array, valores); // Realiza a pesquisa quaternária

    return 0;
}
