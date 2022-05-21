/* Sistema para alocar aquisicoes de componetes eletronicos (IOT)
 * OBJETIVO: Controle de estoque
 * date: 20/05/2022 | 14:40
 * version: v1.22
 *
 *CAMPOS - EXAMPLE:
 
 -ID........: iot01
 -NOME......: ESP32
 -PRECO.....: R$ 69.99
 -UNIDADE...: 3
 -DATA......: 15/01/2022
 -APLICACAO.: LUZ INTELIGENTE
 -EMPRESA...: MERCADO LIVRE
 -DESCRICAO.: MICROCONTROLADOR ESPRESSIF 38 PORTAS
 *
 * copyright Ⓒ 2022 Wildes Sousa 
 *
 */
#include <iostream>
#include <string>  // using getline()
#include <string.h> //using strcpy()
#include <iomanip> // using setw()
#include <cstring> // using isupper()


using namespace std;


struct Componentes {

    string id;
    string nome;
    float preco;
    unsigned int und;
    string data;
    string aplicacao;
    string loja;
    string descricao;    
};

const int MARGEM = 25;
const int CAPACITY = 5; // Capacidade inicial 

// PROTOTIPOS DAS FUNÇÕES "DESING" MENU
/*void criaMenu(const int t, char str[]);
void criaLinhaSuperior();
void criaLinhaInferior();*/

// PROTOTIPOS DAS FUNÇÕES
void novoComponente (Componentes componente [], int *registros);
int buscaBinaria (Componentes componete[], int inicio, int fim, string busca);
void alterar (Componentes componente[], int *registro);
void listar (Componentes componente[], int *registro);
void excluir (Componentes componente[], int *registro);

int main()
{
   
    Componentes *cadastro = new Componentes[CAPACITY];
    
    int registros = 0;
    int op = -1;
    string id;
    
    while (op != 6){
     
        cout << "\n\n";
        cout << "1 - Cadastrar \n";
        cout << "2 - Alterar\n";
        cout << "3 - Listar\n";
        cout << "4 - Excluir\n";
        cout << "5 - Gravar\n";
        cout << "6 - Sair\n\n";
        cout << "Digite uma opcao: \n";
        cout << "\n\n";           
        cin >> op;
        
        switch(op)
        {
            case 1:
                system("clear");
                novoComponente (cadastro,&registros);
                break;
            case 2:
                system("clear");
                alterar (cadastro,&registros);
                
                break;
            case 3:
                system("clear");
                cout << "Lista dos componentes Cadastrados: " << registros << endl << endl;
                cout << "\tID\tNOME\tPREÇO\tUND\tCOMPRA\tAPLICAÇÃO\tLOJA\tDESCRIÇÃO\n";
                listar (cadastro,&registros);
                break;
            case 4:
                system("clear");
                excluir (cadastro, &registros);
                break;
            case 5:
                break;
            case 6:
                break;
            default:
                cout << "Entre com uma opção valida!\n";
        }
    }
    
    
    delete [] cadastro;
    
    return 0;
}

//..........INICIO DAS FUNCOES...........//
void novoComponente (Componentes componente [], int *registros)
{
    int verifica;
    string id;
    
    if (*registros < CAPACITY)
    {
        cout << "Cadastrar novo componete no sistema\n\n" << endl
             << "ID: ";
        cin.ignore();
        getline(cin, id);
        
        verifica = buscaBinaria (componente, 0, *registros-1, id); // verifica se ja existe o id 
        
        if (verifica == -1 or componente[verifica].id == "-1"){
            componente[*registros].id = id;        
            cout << "NOME: ";
            getline (cin, componente[*registros].nome);
            cout << "PREÇO: R$ ";
            cin >> componente[*registros].preco;
            cout << "UND: ";
            cin >> componente[*registros].und;
            cout << "DATA: ";
            cin.ignore();
            getline(cin, componente[*registros].data);
            cout << "APLICAÇÃO: ";
            getline (cin, componente[*registros].aplicacao);
            cout << "LOJA: ";
            getline (cin, componente[*registros].loja);
            cout << "DESCRIÇÃO: ";
            getline (cin, componente[*registros].descricao);
            
            *registros +=1; // controle de cadastros 
        }
        else{
            cout << id << " esse ID já existe ente com outro na proxima vez.\n";
        }
    }
    else{
        cout << "Acesso negado | Capacidade maxima ja encontra em 100%. " << endl;
    }
    
}

int buscaBinaria (Componentes componente[], int inicio, int fim, string busca)
{
    int meio;
    
    if (inicio < fim){
        meio = (inicio + fim) / 2;
        if (componente[meio].id == busca){
            return meio;
            inicio = fim + 1;
        }
        else if (componente[meio].id < busca)
            return buscaBinaria(componente, meio + 1, fim, busca);
        return buscaBinaria(componente, inicio, meio, busca);
    }
    return -1;
}


void listar (Componentes componente[], int *registro)
{
   
      for (int i = 0; i < *registro; i++) // exibe os registros baseado na quantidade de sensores cadastrados
      {
        cout << "\t";
        cout << componente[i].id << "\t"
             << componente[i].nome << "\t"
             << componente[i].preco << "\t"
             << componente[i].und << "\t"
             << componente[i].data << "\t"
             << componente[i].aplicacao << "\t"
             << componente[i].loja << "\t"             
             << componente[i].descricao << "\n";
    }
    
}

void alterar (Componentes componente[], int *registro)
{
        char op; 
        string id;
        cout << "\nEntre com o ID para alterar: ";
        cin.ignore();
        getline(cin, id);
               
        
        int verifica = buscaBinaria (componente, 0, *registro, id); //cadastro exixte ?
    
        if (verifica == -1){
            
            cout << "\n Item: " << id << " não consta no sistema.\n";
        }       
        else{
        
            cout << "\n\tID\tNOME\tPREÇO\tUND\tCOMPRA\tAPLICAÇÃO\tLOJA\tDESCRIÇÃO\n\t";
            cout << componente[verifica].id << "\t"
                 << componente[verifica].nome << "\t"
                 << componente[verifica].preco << "\t"
                 << componente[verifica].und << "\t"
                 << componente[verifica].data << "\t"
                 << componente[verifica].aplicacao << "\t"
                 << componente[verifica].loja << "\t"             
                 << componente[verifica].descricao << "\t\n";
            
            cout << "\nDeseja alterar este Item [S/n]: \n\n";
                 
            cin >> op;
        }
        
       if (op == 'S' or op == 's'){
            
            cout << "Escolha um campo para alterar.\n"
             << "\t1-NOME\n\t2-PREÇO\n\t3-UNIDADE\n\t4-DATA\n\t5-APLICAÇÃO\n\t6-LOJA\n\t7-DESCRIÇÃO\n\t";
            
            cin >> op;
            switch (op){
            
                case '1':
                    cin.ignore();
                    cout << "NOME: ";
                    getline (cin, componente[verifica].nome);  
                    cout << "Nome alterado com sucesso.\n";                
                    break;
                case '2':
                    cout << "PREÇO: R$ ";
                    cin >> componente[verifica].preco;
                    cout << "Preco alterado com sucesso.\n";              
                    break;
                case '3':
                    cout << "UND: ";
                    cin >> componente[verifica].und;
                    cout << "Quantidade alterada com sucesso.\n";                    
                    break;
                case '4':
                    cout << "DATA: ";
                    cin.ignore();
                    getline(cin, componente[verifica].data);
                    cout << "Data alterada com sucesso.\n";
                    break;
                case '5':
                    cin.ignore();
                    cout << "APLICAÇÃO: ";
                    getline (cin, componente[verifica].aplicacao);
                    cout << "Aplicacao alterada com sucesso.\n";
                    break;
                case '6':
                    cin.ignore();
                    cout << "LOJA: ";
                    getline (cin, componente[verifica].loja);
                    cout << "Loja alterada com sucesso.\n";                                   
                    break;
                case '7':
                    cin.ignore();
                    cout << "DESCRIÇÃO: ";
                    getline (cin, componente[verifica].descricao);
                    cout << "Descricao alterada com sucesso.\n";
                                      
                    break;
                default:
                    cout << "Entre com um valor valido!\n";
                    
            }
       } 
       else{
            cout << "\t\nMenu\n";
       }           
        
}

void excluir (Componentes componente[], int *registro)
{

    int verifica;
    char op;
    string id;
    cout << "Digite o ID para exclusão: ";
    cin.ignore(); // Limpa o buffer do teclado
    getline (cin, id);
    
    verifica = buscaBinaria (componente, 0, *registro, id);
    
    
    if (verifica != -1){
        
        cout << "\n\tID\t\tNOME\t\tPREÇO\tUND\tCOMPRA\tAPLICAÇÃO\tLOJA\t\tDESCRIÇÃO\n\t";
            cout << componente[verifica].id << "\t"
                 << componente[verifica].nome << "\t"
                 << componente[verifica].preco << "\t"
                 << componente[verifica].und << "\t"
                 << componente[verifica].data << "\t"
                 << componente[verifica].aplicacao << "\t"
                 << componente[verifica].loja << "\t"             
                 << componente[verifica].descricao << "\t\n";
            
            cout << "\nDeseja excluir este Item [S/n]: \n\n";
                 
            cin >> op;
        
           if (op == 'S' or op == 's'){
                

                componente[verifica].id =  "-1";
                componente[verifica].nome = "NULL";
                componente[verifica].preco = -1;
                componente[verifica].und = -1;
                componente[verifica].data = "NULL";
                componente[verifica].aplicacao = "NULL";
                componente[verifica].loja = "NULL";
                componente[verifica].descricao = "NULL";
                
              for (int indice = verifica; indice < *registro - 1; indice++) {
                componente[indice] = componente[indice + 1];
              }
              *registro -= 1; // diminui a quantidade de registros de componemntes
               cout << "\nCadastro excluido com sucesso \n"<< endl;  
          }  
   }
   else{
        cout << "ID não existe no sistema.\n";
   }
}

// FUNÇÕES PARA O LAYOUT DO MENU //