#include <cstdlib>
#include <cstring>
#include <iostream>

#include "CamadaAplicacao.h"

void mostrar_ajuda();
void mostrar_versao();

int main(int argc, char* argv[]) {
  if (argc == 1) {
    AplicacaoTransmissora(0, 0, 0, 0);
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
  } else if (argc >= 3) {
    if (argc % 2 == 1) {
      char parametro_codificacao[] = "--encode";
      char parametro_erro_percentual[] = "--percentual";
      char parametro_enquadramento[] = "--frame";
      char parametro_controle_erro[] = "--control";

      // char codificacao_binaria[] = "0";
      // char codificacao_manchester[] = "1";
      // char codificacao_manchester_diferencial[] = "2";

      // char enquadramento_contagem_de_caracteres[] = "0";
      // char enquadramento_insercao_de_bytes[] = "1";
      // char enquadramento_insercao_de_bits[] = "2";

      // char controle_erro_paridade_par[] = "0";
      // char controle_erro_paridade_impar[] = "1";
      // char controle_erro_CRC[] = "2";
      // char controle_erro_hamming[] = "3";

      int controle_de_erro = -1;
      int codificacao = -1;
      int enquadramento = -1;
      int erro_percentual = -1;

      for (int i = 0; i < (argc - 1) / 2; i++) {
        if (strncmp(parametro_codificacao,
                    argv[1 + (i * 2)], sizeof(parametro_codificacao)) == 0 && codificacao == -1) {
          int par = atoi(argv[2 + (i * 2)]);
          switch(par) {
            case 0:
              codificacao = 0;
              std::cout << "Codificacao: Binaria" << std::endl;
              break;
            case 1:
              codificacao = 1;
              std::cout << "Codificacao: Manchester" << std::endl;
              break;
            case 2:
              codificacao = 2;
              std::cout << "Codificacao: Manchester diferencial" << std::endl;
              break;
            default:
              codificacao = 0;
              std::cout << "Codificacao: Binaria" << std::endl;
              break;
          }
        } else if (strncmp(parametro_enquadramento,
                           argv[1 + (i * 2)], sizeof(parametro_enquadramento)) == 0 && enquadramento == -1) {
          int par = atoi(argv[2 + (i * 2)]);
          switch(par) {
          case 0:
            enquadramento = 0;
            std::cout << "Enquadramento: Contagem de caracteres" << std::endl;
            break;
          case 1:
            enquadramento = 1;
            std::cout << "Enquadramento: Insercao de bytes" << std::endl;
            break;
          case 2:
            enquadramento = 2;
            std::cout << "Enquadramento: Insercao de bits" << std::endl;
            break;
          default:
            enquadramento = 0;
            std::cout << "Enquadramento: Contagem de caracteres" << std::endl;
            break;
          }
        } else if (strncmp(parametro_controle_erro,
                           argv[1 + (i * 2)], sizeof(parametro_controle_erro)) == 0 && controle_de_erro == -1) {
          int par = atoi(argv[2 + (i * 2)]);
          switch(par) {
          case 0:
            controle_de_erro = 0;
            std::cout << "Controle de Erro: Bit de paridade par" << std::endl;
            break;
          case 1:
            controle_de_erro = 1;
            std::cout << "Controle de Erro: Bit de paridade impar" << std::endl;
            break;
          case 2:
            controle_de_erro = 2;
            std::cout << "Controle de Erro: CRC" << std::endl;
            break;
          case 3:
            controle_de_erro = 3;
            std::cout << "Controle de Erro: Codigo de Hamming" << std::endl;
            break;
          default:
            controle_de_erro = 0;
            std::cout << "Controle de Erro: Bit de paridade par" << std::endl;
            break;
          }
        } else if (strncmp(parametro_erro_percentual,
                          argv[1 + (i * 2)], sizeof(parametro_erro_percentual)) == 0 && erro_percentual == -1) {
          erro_percentual = atoi(argv[2 + (i * 2)]);
          std::cout << "Erro percentual: " << erro_percentual << "%" << std::endl;
        }
      }

      if (erro_percentual <= 0 || erro_percentual > 100) {
        erro_percentual = 0;
        std::cout << "Erro percentual: " << erro_percentual << "%" << std::endl;
      }

      if (enquadramento == -1) {
        enquadramento = 0;
        std::cout << "Enquadramento: Contagem de caracteres" << std::endl;
      }

      if (controle_de_erro == -1) {
        controle_de_erro = 0;
        std::cout << "Controle de Erro: Bit de paridade par" << std::endl;
      }

      if (codificacao == -1) {
        codificacao = 0;
        std::cout << "Codificacao: Binaria" << std::endl;
      }

      AplicacaoTransmissora(enquadramento, controle_de_erro, codificacao, erro_percentual);
    } else {
      std::cout << "Quantidade de parametro invalida!!!" << std::endl;
      std::cout << std::endl;
      mostrar_ajuda();
    }
  }
  return 0;
}

void mostrar_ajuda() {
  mostrar_versao();
  std::cout << "Como usar:" << std::endl;
  std::cout << "Simulador [--frame tipo_de_enquadramento] [--control tipo_de_controle_de_erro] [--encode tipo_de_codificacao] [--percentual porcentagem]"<< std::endl;
  std::cout << std::endl;
  std::cout << "Parametros: " << std::endl;
  std::cout << "--help: Mostra a ajuda" << std::endl;
  std::cout << "--version: Mostra a versao do software" << std::endl;
  std::cout << "--frame tipo_de_enquadramento: Seleciona o tipo de enquadramento da camada de enlace, por padrao utiliza a Contagem de caracteres" << std::endl;
  std::cout << "--control tipo_de_controle_de_erro: Seleciona o tipo de controle de erro da camada de enlace, por padrao utiliza o Bit de paridade par" << std::endl;
  std::cout << "--encode tipo_de_codificacao: Seleciona a codificacao para transmissao, por padrao utiliza a Codificacao Binaria" << std::endl;
  std::cout << "--percentual porcentagem: Numero inteiro para o percentual de erro de transmissao, por padrao 0" << std::endl;
  std::cout << std::endl;
  std::cout << "Tipos de Enquadramento:" << std::endl;
  std::cout << "0: Contagem de Caracteres" << std::endl;
  std::cout << "1: Insercao de Bytes" << std::endl;
  std::cout << "2: Insercao de Bits" << std::endl;
  std::cout << std::endl;
  std::cout << "Tipos de Controle de Erro:" << std::endl;
  std::cout << "0: Bit de Paridade Par" << std::endl;
  std::cout << "1: Bit de Paridade Impar" << std::endl;
  std::cout << "2: CRC" << std::endl;
  std::cout << "3: Hamming" << std::endl;
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
