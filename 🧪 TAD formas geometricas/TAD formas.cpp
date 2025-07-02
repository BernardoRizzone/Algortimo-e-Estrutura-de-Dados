//Nome: Bernardo Rizzone Sousa Vale de Araujo
//Matricula: 232013194

#include <iostream>
#include <cmath>

using namespace std;

class Paralelepipedo 
{
private:
    double largura;
    double altura;
    double profundidade;

public:
    // Construtor
    Paralelepipedo(double l, double a, double p) : largura(l), altura(a), profundidade(p) {}

    // Funções para retornar os tamanhos de cada lado
    double getLargura()
    const 
    {
        return largura; 
    }
    double getAltura() const 
    { 
        return altura; 
    }
    double getProfundidade() const 
    {
        return profundidade; 
    }

    // Função para calcular a área
    double area() const 
    {
        return 2 * (largura * altura + largura * profundidade + altura * profundidade);
    }

    // Função para calcular o volume
    double volume() const 
    {
        return largura * altura * profundidade;
    }
};

class Cilindro {
private:
    double altura;
    double raio;

public:
    // Construtor
    Cilindro(double r, double h) : raio(r), altura(h) {}

    // Funções para retornar a altura e o raio
    double getAltura() const 
    {
        return altura; 
    }
    double getRaio() const 
    { 
        return raio; 
    }

    // Função para calcular a área
    double area() const 
    {
        return 2 * M_PI * raio * (raio + altura);
    }

    // Função para calcular o volume
    double volume() const 
    {
        return M_PI * raio * raio * altura;
    }
};

class Esfera 
{
private:
    double raio;

public:
    // Construtor
    Esfera(double r) : raio(r) {}

    // Função para retornar o raio
    double getRaio() const 
    { 
        return raio; 
    }

    // Função para calcular a área
    double area() const 
    {
        return 4 * M_PI * raio * raio;
    }

    // Função para calcular o volume
    double volume() const 
    {
        return (4.0 / 3.0) * M_PI * raio * raio * raio;
    }
};

int main() {
    // Testando a classe Paralelepipedo
    Paralelepipedo p(3.0, 4.0, 5.0);
    cout << "Paralelepipedo:" << endl;
    cout << "Largura: " << p.getLargura() << endl;
    cout << "Altura: " << p.getAltura() << endl;
    cout << "Profundidade: " << p.getProfundidade() << endl;
    cout << "Área: " << p.area() << endl;
    cout << "Volume: " << p.volume() << endl;

    // Testando a classe Cilindro
    Cilindro c(2.0, 5.0);
    cout << "\nCilindro:" << endl;
    cout << "Raio: " << c.getRaio() << endl;
    cout << "Altura: " << c.getAltura() << endl;
    cout << "Área: " << c.area() << endl;
    cout << "Volume: " << c.volume() << endl;

    // Testando a classe Esfera
    Esfera e(3.0);
    cout << "\nEsfera:" << endl;
    cout << "Raio: " << e.getRaio() << endl;
    cout << "Área: " << e.area() << endl;
    cout << "Volume: " << e.volume() << endl;

    return 0;
}