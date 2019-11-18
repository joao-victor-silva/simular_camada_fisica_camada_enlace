# Simular Camadas Física e de Enlace

## Estrutura do Projeto 

```text
.
|-- LICENSE.md
|-- Makefile
|-- README.md
|-- bin
|-- doc
|-- include
|   |-- CamadaAplicacao.h
|   |-- CamadaEnlace.h
|   |-- CamadaFisica.h
|   `-- MeioDeComunicacao.h
|-- lib
|   `-- catch.hpp
|-- src
|   |-- CamadaAplicacao.cpp
|   |-- CamadaEnlace.cpp
|   |-- CamadaFisica.cpp
|   |-- MeioDeComunicacao.cpp
|   `-- Simulador.cpp
`-- test
    `-- tester.cpp
```

## Dependências

g++ >= 8.3.0-6 

### Dependências opcionais

make >= 4.2.1

### Dependências para o testes

catch2 >= 2.10.2 - disponível em [Catch2](https://github.com/catchorg/Catch2)

Basta ir no link do Github do projeto e ir na seção Releases e procurar pelo
arquivo catch.hpp.

## Compilar

### Com o make

Se você tiver o make instalado basta executar o seguinte comando na raiz do
projeto, pelo terminal :

```shell
make
```

### Sem o make

É possível compilar e executar o projeto sem o make, porém o processo é mais
trabalhoso. Para isso basta executar os comandos abaixo na raiz do projeto, pelo
terminal:

```shell
g++ -g -Wall -I include -c -o CamadaFisica.o src/CamadaFisica.cpp
g++ -g -Wall -I include -c -o CamadaEnlace.o src/CamadaEnlace.cpp
g++ -g -Wall -I include -c -o Simulador.o src/Simulador.cpp
g++ CamadaFisica.o CamadaEnlace.o Simulador.o -o Simulador -I lib
```

## Executar

### Com o make

Se você compilou o projeto com o make, basta executar o seguinte comando na raiz
do projeto, pelo terminal :

```shell
./bin/Simulador
```

### Sem o make

Se você compilou o projeto sem o make, basta executar o seguinte comando na raiz
do projeto, pelo terminal :

```shell
./Simulador
```

## Testes

### Compilar

Basta executar o comando abaixo no diretório raiz, pelo terminal:

```shell
make tester
```

### Executar

Basta executar o comando abaixo no diretório raiz, pelo terminal:

```shell
./bin/tester
```

## Nomenclaturas

### Funções

Funções devem ser nomeadas seguindo o padrão PascalCase.

### Variáveis

Variáveis devem ser nomeadas seguindo o padrão snake_case.
