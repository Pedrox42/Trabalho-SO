
# TRABALHO DE SISTEMAS OPERACIONAIS
## Tema 13: Implementar uma chamada ao sistema no Linux (Criar/listar/encerrar processos e threads)

### Integrantes do grupo
   * ANNA LETICIA FRANCO MONTEIRO
   * DAVI ESTEVES DOS SANTOS
   * GABRIEL DO CARMO SILVA
   * PEDRO CAMPOS LIMA
   * PEDRO PAULO SILVA FILOGONIO

### Índice
   * [Objetivo](#objetivo)
   * [Tecnologias](#tecnologias)
   * [Instalação](#instalação)
   * [Pré-requisitos para utilização](#pré-requisitos-para-utilização)
   * [Compilação e execução](#compilação-e-execução)
   * [Funcionamento](#funcionamento)
   * [Referências](#referências)

### Objetivo:
- O objetivo do código é criar uma interface no terminal capaz de criar, encerrar e listar processos e threads de forma simples, utilizando chamadas ao sistema.

### Tecnologias:
- A seguinte linguagem foi usada na construção do projeto: C++

### Instalação:
- Basta clonar ou fazer download do arquivos do repositório. Para clonar abra o terminal na pasta desejada e digite o comando:
```
git clone https://github.com/Pedrox42/Trabalho-SO.git
```
### Pré-requisitos para utilização:
- Antes de começar, você vai precisar ter instalado em sua máquina a seguinte ferramenta: C++
- O C++ foi instalado utilizando os seguintes comandos:
```
sudo apt update
sudo apt install build-essential
```

### Compilação e execução:
- Após clonar o repositório ou descompactar o .zip acesse a pasta do projeto pelo terminal e utilize os comandos abaixo:
```
g++ *.c* -pthread -o exec
```
```
./exec
```
- Após isso, o programa estará em execução no terminal.

### Funcionamento:
- Variáveis gerais
    - parentId: Armazena o pid_t do processo principal.
    - processos: Armazena os pid_t dos processos criados e do principal.
    - nomes: Armazena os nomes simbólicos dos processos criados e do principal.
    - threads: Armazena os IDs das threads criadas.
- Loop alternativo
    - É o loop em que os processos filhos se encontram. Ele consiste em manter os processos criando threads e em seguida "dormindo".
- Função da thread
    - A função tem o objetivo de dormir por um determinado tempo e encerrar por meio da função pthread_detach(), passando como parâmetro a função pthread_self() que retorna o id da própria thread.
- O loop principal exibe um menu aguardando uma resposta do usuário. De acordo com a resposta direciona para uma das seguintes funcionalidades por meio de um switch case.
    - [1] Criar um novo processo 
        - Pergunta ao usuário um nome simbólico para o processo e faz uma chamada ao sistema por meio da função fork(), que cria o processo filho e retorna o pid_t dele. Esse pid_t é armazenado no vetor de processos e o nome é armazenado no vetor de nomes com o índice equivalente.
        - Os processos filhos são colocados em um loop alternativo, por meio de uma verifição de pid_t no loop principal, para se manterem em execução até que o usuário decida encerrá-lo.
    - [2] Listar processos
        - Percorre o vetor de processos e faz uma chamada ao sistema para cada um por meio da função system(), passando como parâmetro o comando: "ps -p {id_do_processo}" e exibindo-o no terminal.
    - [3] Matar um processo
        - Pergunta ao usuário o pid_t do processo que deseja encerrar e faz uma chamada ao sistema por meio da função kill(), passando como parâmetro o pid_t do processo e o sinal 9. Vale ressaltar que o processo não é removido do vetor de processos pois em sua listagem aparece como "DEFUNCT".
    - [4] Criar uma nova thread
        - Faz uma chamada ao sistema por meio da função pthread_create(), passando como parâmetro a função que a thread vai executar, criando a thread no processo que a chamou e retorna o thread_id dela. Esse thread_id é armazenado no vetor de threads.
    - [5] Listar threads de um processo
        - Pergunta ao usuário o pid_t do processo que deseja listar as threads e faz uma chamada ao sistema por meio da função system(), passando como parâmetro o comando: "ps -p {id_do_processo} -T" e exibindo-o no terminal.
    - [6] Encerrar thread
        - Percorre o vetor de IDs das threads exibindo-os no terminal. Pergunta ao usuário o id da thread que deseja encerrar e faz uma chamada ao sistema por meio da função pthread_cancel(), passando como parâmetro o id da thread escolhida. Após isso, remove o id dela do vetor de IDs de threads.

### Referências:
```
Fork: https://www.geeksforgeeks.org/fork-system-call
```
```
Encerrar Processo: https://www.ibm.com/docs/en/zos/2.4.0?topic=functions-kill-send-signal-process
```
```
Listar Processos: https://www.geeksforgeeks.org/processes-in-linuxunix/
```
```
Chamadas de Sistemas de Threads: https://www.geeksforgeeks.org/thread-functions-in-c-c/
```
```
Listar Threads: https://unixhealthcheck.com/blog?id=465#:~:text=The%20top%20command%20can%20show,by%20pressing%20%27H%27%20key
```
