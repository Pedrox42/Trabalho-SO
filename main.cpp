#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <csignal>
#include <vector>

using namespace std;

int main()
{
    pid_t parentId = getpid();
    vector<pid_t> processos(0);
    vector<string> nomes(0);

    while(true)
    {
        char escolha;

        cout << "-------------------------------" << endl;
        cout << "Eescolha uma opção: " << endl;
        cout << "[1] Criar um novo processo" << endl;
        cout << "[2] Listar processos ativos" << endl;
        cout << "[3] matar um processo" << endl;

        cin >> escolha;

        switch(escolha)
        {
            case '1' :
            {
                string nome;
                cout << "escolha um nome para o processo: ";
                cin >> nome;
                nomes.push_back(nome);
                processos.push_back(fork());
                break;
            }

            case '2':
            {
                cout << "processos ativos: " << endl << endl;
                for(int i = 0; i < processos.size(); i++)
                {
                    string command = "ps -p " + to_string(processos[i]);

                    cout << "Nome do processo: " << nomes[i] << endl << endl;
                    int result = system(command.c_str());
                    if (result == 0) {
                        cout << endl << "----------------------------------------------------" << endl << endl;
                    } else {
                        cout << "Process not found" << endl;
                    }
                }
                break;
            }

            case '3':
            {
                pid_t processoId;
                cout << "Digite o id do processo que deseja remover: ";
                cin >> processoId;
                kill(processoId, 9);
            }

            default :
            {
                break;
            }
        }

        if(parentId != getpid())
        {
            while(true){
                continue;
            }
        }
    }

    return 0;
}
