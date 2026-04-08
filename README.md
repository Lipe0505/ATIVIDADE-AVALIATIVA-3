# Atividade Avaliativa 3 — Fila Dinâmica e Prioridade

Repositório com os dois desafios da Atividade Avaliativa 3 da disciplina de Estruturas de Dados.

---

## 📁 Estrutura do Repositório

```
.
├── desafio1.c   # Simulação de fila de clientes
├── desafio2.c   # Fila de impressão com prioridade
└── README.md
```

---

## ⚙️ Como Compilar e Executar

```bash
# Desafio 1
gcc -Wall -o desafio1 desafio1.c && ./desafio1

# Desafio 2
gcc -Wall -o desafio2 desafio2.c && ./desafio2
```

---

## 🧱 Estrutura da Fila (base dos dois desafios)

Ambos os programas implementam uma **fila encadeada dinâmica** do zero, sem bibliotecas prontas.

```
INÍCIO                              FIM
  ↓                                  ↓
┌──────┐    ┌──────┐    ┌──────┐
│  C1  │ →  │  C2  │ →  │  C3  │ → NULL
└──────┘    └──────┘    └──────┘
```

A estrutura usa dois tipos:

```c
typedef struct No {
    <Dado>      dado;       // cliente ou documento
    struct No  *proximo;    // aponta para o próximo nó
} No;

typedef struct {
    No *inicio;   // frente da fila (próximo a ser atendido)
    No *fim;      // final da fila (último a chegar)
} Fila;
```

### Operações implementadas

| Função       | O que faz                                                  |
|--------------|------------------------------------------------------------|
| `inicializar`| Define `inicio = fim = NULL`                               |
| `isEmpty`    | Retorna `1` se `inicio == NULL`                            |
| `enqueue`    | Aloca novo nó e insere no fim (ou por prioridade no D2)    |
| `dequeue`    | Remove e retorna o dado do início, libera memória          |

---

## 📝 Desafio 1 — Simulação de Fila de Clientes (`desafio1.c`)

### Objetivo
Simular o atendimento sequencial de `n` clientes, exibindo o tempo de espera de cada um.

### Struct do Cliente

```c
typedef struct Cliente {
    int id;
    int tempoAtendimento;
} Cliente;
```

### Como funciona

O tempo de espera de um cliente é a **soma dos tempos de atendimento de todos os clientes à sua frente**.

- O primeiro cliente espera **0 minutos**.
- O segundo espera o tempo do primeiro.
- O terceiro espera a soma dos dois anteriores.
- E assim por diante.

```
tempoEspera acumulado:
  Cliente 1: espera = 0           → atendido por 5 min
  Cliente 2: espera = 5           → atendido por 3 min
  Cliente 3: espera = 5 + 3 = 8   → atendido por 7 min
```

### Exemplo de saída

```
Quantos clientes? 3

--- Cliente 1 --- ID: 101 | Tempo: 5 min
--- Cliente 2 --- ID: 102 | Tempo: 3 min
--- Cliente 3 --- ID: 103 | Tempo: 7 min

========== SIMULAÇÃO DE ATENDIMENTO ==========
Cliente    Tempo Atendimento    Tempo Espera
----------------------------------------------
101        5                    0
102        3                    5
103        7                    8
----------------------------------------------
Tempo total de atendimento: 15 minutos
```

---

## 📝 Desafio 2 — Fila de Impressão com Prioridade (`desafio2.c`)

### Objetivo
Gerenciar uma fila de documentos onde **menor valor de prioridade = mais urgente**. Em caso de empate, respeitar a ordem de chegada.

### Struct do Documento

```c
typedef struct Documento {
    int id;
    int paginas;
    int prioridade;  // menor valor = maior prioridade
} Documento;
```

### Estratégia: Inserção Ordenada

A ordenação acontece no momento do **enqueue**, não do dequeue. Ao inserir um novo documento, o algoritmo percorre a fila e o posiciona **antes do primeiro nó com prioridade pior** (valor maior):

```
Fila atual:  [P=1] → [P=2] → [P=3]
Inserindo P=2:
  - P=1 ≤ 2 → passa
  - P=2 ≤ 2 → passa  (empate: respeita chegada, vai depois)
  - P=3 > 2 → insere aqui

Resultado:   [P=1] → [P=2] → [P=2, novo] → [P=3]
```

Essa lógica garante **estabilidade**: documentos com a mesma prioridade são impressos na ordem em que chegaram.

### Exemplo de saída

```
Quantos documentos? 4
Doc 1: ID=10, páginas=5,  prioridade=2
Doc 2: ID=20, páginas=12, prioridade=1
Doc 3: ID=30, páginas=3,  prioridade=3
Doc 4: ID=40, páginas=8,  prioridade=1

========== ORDEM DE IMPRESSÃO ==========
Ord.  Doc. ID    Páginas    Prioridade
----------------------------------------
1     20         12         1           ← chegou primeiro com P=1
2     40         8          1           ← chegou depois com P=1
3     10         5          2
4     30         3          3
```

---

| Nome Completo | Usuário GitHub |
|---------------|----------------|
|  André Felipe            |    Lipe0505    |
|  Erick Sartori           |                |

> A atividade pode ser realizada individualmente ou em grupo de até 5 integrantes.

---

## 📬 Entrega

- **Data (ADS):** 08/04 até 19h
- **Data (ES):** 10/04 até 19h
- **E-mail para:** joao.vsantos@unicesumar.edu.br
- **Título:** `Trabalho Estruturas de dados ADSIS3S`
- **CC:** gabriel.pjesus@unicesumar.edu.br e todos os integrantes
