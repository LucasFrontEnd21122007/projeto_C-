#include <iostream>
#include <vector>
#include <string>
#include <ctime>

class Livro {
public:
    std::string titulo;
    std::string autor;
    std::string isbn;
    bool emprestado;
    time_t dataEmprestimo;

    Livro(const std::string& _titulo, const std::string& _autor, const std::string& _isbn)
        : titulo(_titulo), autor(_autor), isbn(_isbn), emprestado(false), dataEmprestimo(0) {}
};

class Biblioteca {
private:
    std::vector<Livro> livros;

public:
    void adicionarLivro(const std::string& titulo, const std::string& autor, const std::string& isbn) {
        livros.push_back(Livro(titulo, autor, isbn));
    }

    Livro* encontrarLivroPorTitulo(const std::string& titulo) {
        for (auto& livro : livros) {
            if (livro.titulo == titulo) {
                return &livro;
            }
        }
        return nullptr;
    }

    void emprestarLivro(const std::string& titulo) {
        Livro* livro = encontrarLivroPorTitulo(titulo);
        if (livro) {
            livro->emprestado = true;
            livro->dataEmprestimo = std::time(nullptr);
            std::cout << "Livro emprestado com sucesso!" << std::endl;
        } else {
            std::cout << "Livro não encontrado na biblioteca." << std::endl;
        }
    }

    void devolverLivro(const std::string& titulo) {
        Livro* livro = encontrarLivroPorTitulo(titulo);
        if (livro && livro->emprestado) {
            livro->emprestado = false;
            std::cout << "Livro devolvido com sucesso!" << std::endl;
        } else if (livro && !livro->emprestado) {
            std::cout << "Este livro não está emprestado." << std::endl;
        } else {
            std::cout << "Livro não encontrado na biblioteca." << std::endl;
        }
    }
};

int main() {
    Biblioteca biblioteca;

    biblioteca.adicionarLivro("O Senhor dos Anéis", "J.R.R. Tolkien", "978-0-395-19395-7");
    biblioteca.adicionarLivro("Harry Potter e a Pedra Filosofal", "J.K. Rowling", "978-85-325-1417-9");

    while (true) {
        std::cout << "Escolha uma ação:" << std::endl;
        std::cout << "1. Empréstimo de livro" << std::endl;
        std::cout << "2. Devolução de livro" << std::endl;
        std::cout << "3. Sair" << std::endl;

        int escolha;
        std::cin >> escolha;

        if (escolha == 1) {
            std::cout << "Digite o título do livro que deseja emprestar: ";
            std::string titulo;
            std::cin.ignore();
            std::getline(std::cin, titulo);
            biblioteca.emprestarLivro(titulo);
        } else if (escolha == 2) {
            std::cout << "Digite o título do livro que deseja devolver: ";
            std::string titulo;
            std::cin.ignore();
            std::getline(std::cin, titulo);
            biblioteca.devolverLivro(titulo);
        } else if (escolha == 3) {
            break;
        } else {
            std::cout << "Opção inválida. Tente novamente." << std::endl;
        }
    }

    return 0;
}
