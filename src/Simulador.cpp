#include <cstring>
#include <iostream>

#include "CamadaAplicacao.h"

void mostrar_ajuda();
void mostrar_versao();

int main(int argc, char* argv[]) {
  if (argc == 1) {
    AplicacaoTransmissora(0);
  } else if (argc == 2) {
    char parametro_ajuda[] = "--help";
    char parametro_versao[] = "--version";
    if (strncmp(parametro_ajuda,
                argv[1], sizeof(parametro_ajuda)) == 0) {
      mostrar_ajuda();
    } else if (strncmp(parametro_versao,
                       argv[1], sizeof(parametro_versao)) == 0) {
      mostrar_versao();
    } else {
      std::cout << "Parametro invalido!!!" << std::endl;
      std::cout << std::endl;
      mostrar_ajuda();
    }
  } else if (argc == 3) {
    char parametro_codificacao[] = "--encode";
    char codificacao_binaria[] = "0";
    char codificacao_manchester[] = "1";
    char codificacao_manchester_diferencial[] = "2";
    if (strncmp(parametro_codificacao,
                argv[1], sizeof(parametro_codificacao)) == 0) {
      if (strncmp(codificacao_binaria,
                  argv[2], sizeof(codificacao_binaria)) == 0) {
        AplicacaoTransmissora(0);
      } else if (strncmp(codificacao_manchester,
                         argv[2], sizeof(codificacao_manchester)) == 0) {
        AplicacaoTransmissora(1);
      } else if (strncmp(codificacao_manchester_diferencial,
                         argv[2], sizeof(codificacao_manchester_diferencial)) == 0) {
        AplicacaoTransmissora(2);
      } else {
        std::cout << "Codificacao invalida!!!" << std::endl;
        std::cout << std::endl;
        mostrar_ajuda();
      }
    } else {
      std::cout << "Parametro invalido!!!" << std::endl;
      std::cout << std::endl;
      mostrar_ajuda();
    }
  }
  return 0;
}

void mostrar_ajuda() {
  mostrar_versao();
  std::cout << "Como usar:" << std::endl;
  std::cout << "Simulador [--encode tipo_de_codificacao]"<< std::endl;
  std::cout << std::endl;
  std::cout << "Parametros: " << std::endl;
  std::cout << "--help: Mostra a ajuda" << std::endl;
  std::cout << "--version: Mostra a versao do software" << std::endl;
  std::cout << "--encode tipo_de_codificacao: Seleciona a codificacao para transmissao, por padrao utiliza a Codificacao Binaria" << std::endl;
  std::cout << std::endl;
  std::cout << "Tipos de codificacao:" << std::endl;
  std::cout << "0: Codificacao binaria" << std::endl;
  std::cout << "1: Codificacao Manchester" << std::endl;
  std::cout << "2: Codificacao Manchester Diferencial" << std::endl;
}

void mostrar_versao() {
  std::cout << "Simulador de camadas de fisica e de enlace" << std::endl;
  std::cout << "Versao 1.0" << std::endl;
  std::cout << std::endl;
}
