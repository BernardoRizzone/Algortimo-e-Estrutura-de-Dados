/*
Nome: Bernardo Rizzone
matricula: 232013194
Problema: Gestão de Reservas de Hotel
Descrição:
Um hotel precisa de um sistema para gerenciar reservas de quartos e hóspedes. O sistema deve permitir o cadastro de hóspedes e quartos, bem como gerenciar as reservas.

Requisitos:
1. Criação das classes Pessoa, Hospede e Quarto.
2. Implementação do enum StatusQuarto para o status dos quartos.
3. Encapsulamento dos atributos das classes.
4. Métodos para reservar e liberar quartos, e para imprimir detalhes.
5. Uso de polimorfismo para sobrescrever métodos.
6. Manipulação de arquivos para salvar e carregar dados.
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

enum StatusQuarto { DISPONIVEL, RESERVADO };

class Pessoa 
{
protected:
    string cpf;
    string nome;

public:
    Pessoa(string cpf, string nome) : cpf(cpf), nome(nome) {}

    void setCpf(string cpf) { this->cpf = cpf; }
    void setNome(string nome) { this->nome = nome; }

    string getCpf() const { return cpf; }
    string getNome() const { return nome; }

    virtual void imprime() const
    {
        cout << "Pessoa: CPF: " << cpf << ", Nome: " << nome << endl;
    }
};

class Quarto
{
private:
    int numero;
    string tipo;
    float preco;
    StatusQuarto status;

public:
    Quarto(int numero, string tipo, float preco) 
        : numero(numero), tipo(tipo), preco(preco), status(DISPONIVEL) {}

    void setNumero(int numero) { this->numero = numero; }
    void setTipo(string tipo) { this->tipo = tipo; }
    void setPreco(float preco) { this->preco = preco; }
    void setStatus(StatusQuarto status) { this->status = status; }

    int getNumero() const { return numero; }
    string getTipo() const { return tipo; }
    float getPreco() const { return preco; }
    StatusQuarto getStatus() const { return status; }

    void imprime() const
    {
        cout << "Quarto: Número: " << numero << ", Tipo: " << tipo 
             << ", Preço: " << preco << ", Status: " << (status == DISPONIVEL ? "DISPONÍVEL" : "RESERVADO") << endl;
    }
};

class Hospede : public Pessoa 
{
private:
    int numeroReserva;
    vector<Quarto*> quartosReservados;

public:
    Hospede(string cpf, string nome, int numeroReserva) 
        : Pessoa(cpf, nome), numeroReserva(numeroReserva) {}

    void setNumeroReserva(int numeroReserva) { this->numeroReserva = numeroReserva; }
    int getNumeroReserva() const { return numeroReserva; }

    void reservarQuarto(Quarto& quarto) 
    {
        if (quarto.getStatus() == DISPONIVEL)
        {
            quarto.setStatus(RESERVADO);
            quartosReservados.push_back(&quarto);
            cout << "Quarto reservado: " << quarto.getNumero() << endl;
        } else
        {
            cout << "Quarto já está reservado!" << endl;
        }
    }

    void liberarQuarto(Quarto& quarto)
    {
        for (auto it = quartosReservados.begin(); it != quartosReservados.end(); ++it)
        {
            if ((*it)->getNumero() == quarto.getNumero()) 
            {
                quarto.setStatus(DISPONIVEL);
                quartosReservados.erase(it);
                cout << "Quarto liberado: " << quarto.getNumero() << endl;
                return;
            }
        }
        cout << "Quarto não encontrado nas reservas!" << endl;
    }

    void imprime() const override
    {
        Pessoa::imprime();
        cout << "Hóspede: Número da Reserva: " << numeroReserva << endl;
        cout << "Quartos Reservados: " << endl;
        for (const auto& quarto : quartosReservados)
        {
            quarto->imprime();
        }
    }
};

void salvarDados(const vector<Pessoa*>& hospedes, const vector<Quarto>& quartos, const string& arquivoHospedes, const string& arquivoQuartos)
{
    ofstream outHospedes(arquivoHospedes);
    if (outHospedes.is_open())
    {
        for (const auto& hospede : hospedes)
        {
            Hospede* h = dynamic_cast<Hospede*>(hospede);
            if (h) 
            {
                outHospedes << h->getCpf() << " " << h->getNome() << " " << h->getNumeroReserva() << endl;
            }
        }
        outHospedes.close();
    } else 
    {
        cerr << "Erro ao abrir o arquivo de hóspedes para escrita." << endl;
    }

    ofstream outQuartos(arquivoQuartos);
    if (outQuartos.is_open()) 
    {
        for (const auto& quarto : quartos) 
        {
            outQuartos << quarto.getNumero() << " " << quarto.getTipo() << " " << quarto.getPreco() << " " << quarto.getStatus() << endl;
        }
        outQuartos.close();
    } else
    {
        cerr << "Erro ao abrir o arquivo de quartos para escrita." << endl;
    }
}

void carregarDados(vector<Pessoa*>& hospedes, vector<Quarto>& quartos, const string& arquivoHospedes, const string& arquivoQuartos) {
    ifstream inHospedes(arquivoHospedes);
    if (inHospedes.is_open()) 
    {
        string cpf, nome;
        int numeroReserva;
        while (inHospedes >> cpf >> nome >> numeroReserva) 
        {
            hospedes.push_back(new Hospede(cpf, nome, numeroReserva));
        }
        inHospedes.close();
    } else 
    {
        cerr << "Erro ao abrir o arquivo de hóspedes para leitura." << endl;
    }

    ifstream inQuartos(arquivoQuartos);
    if (inQuartos.is_open()) 
    {
        int numero;
        string tipo;
        float preco;
        int status;
        while (inQuartos >> numero >> tipo >> preco >> status) 
        {
            quartos.emplace_back(numero, tipo, preco);
            quartos.back().setStatus(static_cast<StatusQuarto>(status));
        }
        inQuartos.close();
    } else 
    {
        cerr << "Erro ao abrir o arquivo de quartos para leitura." << endl;
    }
}

int main() 
{
    vector<Pessoa*> hospedes;
    vector<Quarto> quartos;
    char opcao;

    
    do 
    {
        string cpf, nome;
        int numeroReserva;

        cout << "Digite os detalhes do hóspede:" << endl;
        cout << "CPF: "; cin >> cpf;
        cout << "Nome: "; cin >> nome;
        cout << "Número da Reserva: "; cin >> numeroReserva;

        hospedes.push_back(new Hospede(cpf, nome, numeroReserva));

        cout << "Deseja adicionar outro hóspede? (s/n): "; cin >> opcao;
    } while (opcao == 's' || opcao == 'S');

    
    do 
    {
        int numero;
        string tipo;
        float preco;

        cout << "Digite os detalhes do quarto:" << endl;
        cout << "Número: "; cin >> numero;
        cout << "Tipo: "; cin >> tipo;
        cout << "Preço: "; cin >> preco;

        quartos.emplace_back(numero, tipo, preco);

        cout << "Deseja adicionar outro quarto? (s/n): "; cin >> opcao;
    } while (opcao == 's' || opcao == 'S');

    
    dynamic_cast<Hospede*>(hospedes[0])->reservarQuarto(quartos[0]);

    
    cout << "\nHóspedes cadastrados:\n";
    for (const auto& hospede : hospedes) 
    {
        hospede->imprime();
    }

    cout << "\nQuartos cadastrados:\n";
    for (const auto& quarto : quartos)
    {
        quarto.imprime();
    }

    
    salvarDados(hospedes, quartos, "hospedes.txt", "quartos.txt");

    
    vector<Pessoa*> hospedesCarregados;
    vector<Quarto> quartosCarregados;
    carregarDados(hospedesCarregados, quartosCarregados, "hospedes.txt", "quartos.txt");

    
    cout << "\nDados carregados dos arquivos:\n";
    for (const auto& hospede : hospedesCarregados) 
    {
        hospede->imprime();
    }

    for (const auto& quarto : quartosCarregados)
    {
        quarto.imprime();
    }

    
    for (auto& hospede : hospedesCarregados)
    {
        delete hospede;
    }

    return 0;
}
