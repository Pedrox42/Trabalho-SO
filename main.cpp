#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <csignal>
#include <vector>
#include <pthread.h>

using namespace std;

void *thread_loop(void *arg)
{
    sleep(20);
    pthread_detach(pthread_self());
    return NULL;
}

int main()
{
    pid_t parentId = getpid();

    vector<pid_t> processos(0);
    vector<string> nomes(0);

    processos.push_back(parentId);
    nomes.push_back("Processo Principal");

    //coloca algo no vetor

    while(true)
    {
        char escolha;

        cout << "-------------------------------" << endl;
        cout << "Eescolha uma opção: " << endl;
        cout << "[1] Criar um novo processo" << endl;
        cout << "[2] Listar processos" << endl;
        cout << "[3] matar um processo" << endl;
        cout << "[4] Criar uma nova thread" << endl;
        cout << "[5] Listar threads de um processo" << endl;
        cout << "[6] Encerrar thread" << endl;

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
                break;
            }

            case '4':
            {
                pthread_t threadId;
                pthread_create(&threadId, NULL, thread_loop, NULL);
                cout << "thread criada com sucesso!" << endl;
                break;
            }

            case '5':
            {
                cout << "Digite o id do processo que deseja listar as threads: ";
                pid_t processoEscolhidoId;

                cin >> processoEscolhidoId;

                string command = "ps -p " + to_string(processoEscolhidoId) + " -T";
                system(command.c_str());
                break;
            }

            case '6':
            {
                pthread_t threadParaSerEncerrada;
                cout << "Digite o id da thread do processo principal que deseja encerrar: ";
                cin >> threadParaSerEncerrada;
                pthread_kill(threadParaSerEncerrada, 9);
                break;
            }

            default:
            {
                cout << "Por favor Digite um valor válido.";
                break;
            }
        }

        if(parentId != getpid())
        {
            while(true)
            {
                pthread_t threadId;
                pthread_create(&threadId, NULL, thread_loop, NULL);
                sleep(10);
            }
        }
    }

    return 0;
}
