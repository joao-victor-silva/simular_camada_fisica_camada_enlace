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
|   |-- CamadaEnlace.h
|   `-- CamadaFisica.h
|-- lib
|   `-- catch.hpp
|-- src
|   |-- CamadaEnlace.cpp
|   |-- CamadaFisica.cpp
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

Basta ir no link do Github do projeto e ir na seção Releases e procurar pelo arquivo catch.hpp.


## Nomenclaturas

### Funções

Funções devem ser nomeadas seguindo o padrão PascalCase.

### Variáveis

Variáveis devem ser nomeadas seguindo o padrão snake_case.
