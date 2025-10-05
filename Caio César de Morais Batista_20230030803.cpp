#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>
using namespace std;

//Protoptipos das funções de ordenação
void bubbleSort(vector<int>& vetor);
void insertionSort(vector<int>& vetor);
void selectionSort(vector<int>& vetor);
void mergeSort(vector<int>& vetor, int inicio, int fim);
void quickSort(vector<int>& vetor, int baixo, int alto);

//Função principal para executar os testes
int main() {
    //Vetores com menos de 1000 elementos executam em menos de 0ms na maioria dos algortimos de ordenção
    //Trocar o valor do tamanho para 2500 quando for testar vetores "pequenos"
    const int TAMANHO = 55000; //Tamanho dos vetores para teste
    
    //Cria os vetores para teste
    vector<int> vetorAleatorio(TAMANHO);
    vector<int> vetorQuaseOrdenado(TAMANHO);
    vector<int> vetorInverso(TAMANHO);
    
    //Vetor aleatório
    random_device rd; //Cria um número aleatório
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, TAMANHO);
    for(int i = 0; i < TAMANHO; i++) { //Preenche com números aleatórios
        vetorAleatorio[i] = dis(gen);
    }
    
    //Vetor quase ordenado
    for(int i = 0; i < TAMANHO; i++) { //Preenche com números em ordem
        vetorQuaseOrdenado[i] = i;
    }
    for(int i = 0; i < TAMANHO/20; i++) { //Desordena um pouco o vetor
        int pos1 = dis(gen) % TAMANHO; //Pega uma posição aleatória
        int pos2 = dis(gen) % TAMANHO; //Pega outra posição aleatória
        swap(vetorQuaseOrdenado[pos1], vetorQuaseOrdenado[pos2]); //Troca os elementos de posição
    }
    
    //Vetor inversamente ordenado
    for(int i = 0; i < TAMANHO; i++) { // Preenche com números em ordem decrescente
        vetorInverso[i] = TAMANHO - i;
    }
    
    //Vetor que vai copiar os dados originais
    vector<int> vetorTeste;
    
    cout << "Comparação de Algoritmos de Ordenação" << endl;
    
    //Testando cada algoritmo com cada tipo de vetor
    string tipos[] = {"Aleatório", "Quase Ordenado", "Inversamente Ordenado"};
    vector<vector<int>> vetores = {vetorAleatorio, vetorQuaseOrdenado, vetorInverso};
    
    for(int tipo = 0; tipo < 3; tipo++) {
        cout << "\nTestando com vetor " << tipos[tipo] << ":" << endl;
        
        //Bubble Sort
        vetorTeste = vetores[tipo];
        auto inicio = chrono::high_resolution_clock::now();
        bubbleSort(vetorTeste);
        auto fim = chrono::high_resolution_clock::now();
        cout << "Bubble Sort: " << chrono::duration_cast<chrono::milliseconds>(fim - inicio).count() << " ms" << endl;
        
        //Insertion Sort
        vetorTeste = vetores[tipo];
        inicio = chrono::high_resolution_clock::now();
        insertionSort(vetorTeste);
        fim = chrono::high_resolution_clock::now();
        cout << "Insertion Sort: " << chrono::duration_cast<chrono::milliseconds>(fim - inicio).count() << " ms" << endl;
        
        //Selection Sort
        vetorTeste = vetores[tipo];
        inicio = chrono::high_resolution_clock::now();
        selectionSort(vetorTeste);
        fim = chrono::high_resolution_clock::now();
        cout << "Selection Sort: " << chrono::duration_cast<chrono::milliseconds>(fim - inicio).count() << " ms" << endl;
        
        //Merge Sort
        vetorTeste = vetores[tipo];
        inicio = chrono::high_resolution_clock::now();
        mergeSort(vetorTeste, 0, vetorTeste.size() - 1);
        fim = chrono::high_resolution_clock::now();
        cout << "Merge Sort: " << chrono::duration_cast<chrono::milliseconds>(fim - inicio).count() << " ms" << endl;
        
        //Quick Sort
        vetorTeste = vetores[tipo];
        inicio = chrono::high_resolution_clock::now();
        quickSort(vetorTeste, 0, vetorTeste.size() - 1);
        fim = chrono::high_resolution_clock::now();
        cout << "Quick Sort: " << chrono::duration_cast<chrono::milliseconds>(fim - inicio).count() << " ms" << endl;
    }
    
    return 0;
}

//Bubble Sort
void bubbleSort(vector<int>& vetor) {
    int tamanho = vetor.size();
    for(int i = 0; i < tamanho-1; i++) {
        for(int j = 0; j < tamanho-1-i; j++) { //Percorre o vetor até o último elemento não ordenado
            if(vetor[j] > vetor[j+1]) { //Compara os elementos vizinhos
                swap(vetor[j], vetor[j+1]); // Troca se estiverem na ordem errada
            }
        }
    }
}

//Insertion Sort
void insertionSort(vector<int>& vetor) {
    int tamanho = vetor.size();
    for(int i = 1; i < tamanho; i++) { //Começa do segundo elemento
        int chave = vetor[i];
        int j = i - 1;
        while(j >= 0 && vetor[j] > chave) { //Move os elementos maiores que a chave para a direita
            vetor[j + 1] = vetor[j];
            j--;
        }
        vetor[j + 1] = chave; //Adiciona a chave na posição certa
    }
}


// Selection Sort
void selectionSort(vector<int>& vetor) {
    int tamanho = vetor.size();
    for(int i = 0; i < tamanho-1; i++) {
        int min_idx = i; //Assume que o menor é o primeiro elemento não ordenado
        for(int j = i+1; j < tamanho; j++) {
            if(vetor[j] < vetor[min_idx]) { //Encontra o menor elemento
                min_idx = j; //Atualiza a posição do menor elemento
            }
        }
        swap(vetor[min_idx], vetor[i]); //Troca o menor elemento com o primeiro elemento que não está ordenado
    }
}


//Função auxiliar para o merge sort para juntar dois sub vetores
void merge(vector<int>& vetor, int inicio, int meio, int fim) {
    vector<int> temp(fim - inicio + 1);
    int i = inicio, j = meio + 1, k = 0;

    while(i <= meio && j <= fim) {
        if(vetor[i] <= vetor[j]) {
            temp[k++] = vetor[i++];
        } else {
            temp[k++] = vetor[j++];
        }
    }
    
    while(i <= meio) { //Copia os elementos restantes do primeiro sub-vetor
        temp[k++] = vetor[i++];
    }
    
    while(j <= fim) { //Copia os elementos restantes do segundo sub-vetor
        temp[k++] = vetor[j++];
    }
    
    for(i = 0; i < k; i++) { //Copia de volta para o vetor original
        vetor[inicio + i] = temp[i];
    }
}

//Merge Sort
void mergeSort(vector<int>& vetor, int inicio, int fim) {
    if(inicio < fim) {
        int meio = inicio + (fim - inicio) / 2; //Encontra o ponto médio
        mergeSort(vetor, inicio, meio); //Ordena a primeira metade
        mergeSort(vetor, meio + 1, fim); //Ordena a segunda metade
        merge(vetor, inicio, meio, fim); //Junta as metades já ordenadas
    }
}


//Função auxiliar para o Quick Sort que escolhe o pivô e particiona o vetor
int particionar(vector<int>& vetor, int baixo, int alto) {
    int pivo = vetor[alto]; //Escolhe o último elemento como pivô
    int i = (baixo - 1);
    
    for(int j = baixo; j <= alto - 1; j++) {
        if(vetor[j] < pivo) {
            i++;
            swap(vetor[i], vetor[j]); //Troca se o elemento for menor que o pivô
        }
    }
    swap(vetor[i + 1], vetor[alto]); //Coloca o pivô na posição correta
    return (i + 1); //Retorna a posição do pivô
}

//Quick Sort
void quickSort(vector<int>& vetor, int baixo, int alto) {
    if(baixo < alto) {
        int pi = particionar(vetor, baixo, alto); //Particiona o vetor
        quickSort(vetor, baixo, pi - 1); //Ordena a parte esquerda do pivô
        quickSort(vetor, pi + 1, alto); //Ordena a parte direita do pivô
    }
}
