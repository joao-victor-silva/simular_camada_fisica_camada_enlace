#include <vector>
#include <iostream>
#include "CamadaFisica.h"
#include "MeioDeComunicacao.h"
#include "CamadaAplicacao.h"

// Transmissao

void CamadaFisicaTransmissora(std::vector<bool>& quadros, int tipo_de_enquadramento,
                              int tipo_de_controle_de_erro, int tipo_de_codificacao,
                              int percentual_de_erro) {
  std::cout << "Quadro a ser transmitido: \t\t";
  for (unsigned int i = 0; i < quadros.size(); i++) {
    if (quadros[i]) {
      std::cout << "1";
    } else {
      std::cout << "0";
    }
  }
  std::cout << std::endl;

  std::vector<bool> fluxo_de_bits;
  switch (tipo_de_codificacao) {
    case 0:
      fluxo_de_bits = CamadaFisicaTransmissoraCodificacaoBinaria(quadros);
      break;
    case 1:
      fluxo_de_bits = CamadaFisicaTransmissoraCodificacaoManchester(quadros);
      break;
    case 2:
      fluxo_de_bits = CamadaFisicaTransmissoraCodificacaoManchesterDiferencial(quadros);
      break;
    default:
      fluxo_de_bits = CamadaFisicaTransmissoraCodificacaoBinaria(quadros);
      break;
  }

  std::cout << "Fluxo de bits enviados: \t\t";
  for (unsigned int i = 0; i < fluxo_de_bits.size(); i++) {
    if (fluxo_de_bits[i]) {
      std::cout << "1";
    } else {
      std::cout << "0";
    }
  }
  std::cout << std::endl;

  MeioDeComunicacao(fluxo_de_bits, tipo_de_enquadramento, tipo_de_controle_de_erro,
                    tipo_de_codificacao, percentual_de_erro);
}

std::vector<bool> CamadaFisicaTransmissoraCodificacaoBinaria(std::vector<bool>& quadros) {
  // Nao ha alteracoes a se fazer no quadro, logo o resultado eh a propria entrada
  return quadros;
}

std::vector<bool> CamadaFisicaTransmissoraCodificacaoManchester(std::vector<bool>& quadros) {
  // cada bit deve ser codificado como um par de bits, 01 ou 10, de acordo com o valor do bit
  std::vector<bool> manchester_quadros;

  for (bool quadro: quadros) {
    if (quadro) {
      // se o bit for 1, o par de bits deve ser 10 (na ordem de leitura usual, da esquerda pra direita)
      manchester_quadros.push_back(false);
      manchester_quadros.push_back(true);
    } else {
      // se o bit for 0, o par de bits deve ser 01 (na ordem de leitura usual, da esquerda pra direita)
      manchester_quadros.push_back(true);
      manchester_quadros.push_back(false);
    }
  }

  return manchester_quadros;
}

std::vector<bool> CamadaFisicaTransmissoraCodificacaoManchesterDiferencial(std::vector<bool>& quadros) {
  // assim como a codificacao de manchester, cada bit deve ser codificado como um par de bits, 01 ou 10,
  // porem o valor do par de bits depende do par anterior e valor do bit, 0 mantem o par anterior e 1
  // alterna os bits do par anterior
  bool last_bits_manchester_diferencial[2];
  last_bits_manchester_diferencial[0] = false;
  last_bits_manchester_diferencial[1] = true;
  int last_bit = -1;
  std::vector<bool> manchester_diferencial_quadros;

  // 01001110

  // 01110010

  // 0111             0010
  // 01 10 01 10      10 10 01 01

  // 01101010 10011001

  for (bool quadro: quadros) {
    if (last_bit == -1) {
      // se for o primeiro bit, define o par de acordo com a codificacao de Manchester
      if (quadro) {
        last_bit = 1;
        last_bits_manchester_diferencial[0] = false;
        last_bits_manchester_diferencial[1] = true;
        manchester_diferencial_quadros.push_back(last_bits_manchester_diferencial[0]);
        manchester_diferencial_quadros.push_back(last_bits_manchester_diferencial[1]);
      } else {
        last_bit = 0;
        last_bits_manchester_diferencial[0] = true;
        last_bits_manchester_diferencial[1] = false;
        manchester_diferencial_quadros.push_back(last_bits_manchester_diferencial[0]);
        manchester_diferencial_quadros.push_back(last_bits_manchester_diferencial[1]);
      }
    } else {
      // se nao for o primeiro bit, define o par de acordo com o par anterior e o bit atual
      if (quadro) {
        // se o bit for 1, o par atual eh a inversao do par anterior
        last_bit = 1;
        last_bits_manchester_diferencial[0] = !last_bits_manchester_diferencial[0];
        last_bits_manchester_diferencial[1] = !last_bits_manchester_diferencial[1];
        manchester_diferencial_quadros.push_back(last_bits_manchester_diferencial[0]);
        manchester_diferencial_quadros.push_back(last_bits_manchester_diferencial[1]);
      } else {
        // se o bit for 0, o par atual eh o mesmo par anterior
        last_bit = 0;
        manchester_diferencial_quadros.push_back(last_bits_manchester_diferencial[0]);
        manchester_diferencial_quadros.push_back(last_bits_manchester_diferencial[1]);
      }
    }
  }

  return manchester_diferencial_quadros;
}


// Recepcao

void CamadaFisicaReceptora(std::vector<bool>& quadros, int tipo_de_enquadramento,
                           int tipo_de_controle_de_erro, int tipo_de_codificacao) {
  std::vector<bool> fluxo_de_bits;
  std::cout << "Fluxo de bits recebidos: \t\t";
  for (unsigned int i = 0; i < quadros.size(); i++) {
    if (quadros[i]) {
      std::cout << "1";
    } else {
      std::cout << "0";
    }
  }
  std::cout << std::endl;
  switch (tipo_de_codificacao) {
  case 0:
    fluxo_de_bits = CamadaFisicaReceptoraDecodificacaoBinaria(quadros);
    break;
  case 1:
    fluxo_de_bits = CamadaFisicaReceptoraDecodificacaoManchester(quadros);
    break;
  case 2:
    fluxo_de_bits = CamadaFisicaReceptoraDecodificacaoManchesterDiferencial(quadros);
    break;
  default:
    fluxo_de_bits = CamadaFisicaReceptoraDecodificacaoBinaria(quadros);
    break;
  }

  std::cout << "Quadro decodificado: \t\t\t";
  for (unsigned int i = 0; i < fluxo_de_bits.size(); i++) {
    if (fluxo_de_bits[i]) {
      std::cout << "1";
    } else {
      std::cout << "0";
    }
  }
  std::cout << std::endl;

  CamadaDeAplicacaoReceptora(fluxo_de_bits);
}

std::vector<bool> CamadaFisicaReceptoraDecodificacaoBinaria(std::vector<bool>& quadros_em_binario) {
  // Nao houve alteracoes no quador na transmissao, logo o resultado eh a propria entrada
  return quadros_em_binario;
}

std::vector<bool> CamadaFisicaReceptoraDecodificacaoManchester(std::vector<bool>& manchester_quadros) {
  std::vector<bool> decodificado_quadros;
  // analisa cada par de bits, definido o valor do bit de acordo com o valor do par
  for (unsigned int i = 0; i < manchester_quadros.size() / 2; i++) {
    if (!manchester_quadros[2 * i] && manchester_quadros[(2 * i) + 1]) {
      // se o par for 10 (na forma de leitura usual da esquerda pra direita), o bit tem valor 1
      decodificado_quadros.push_back(true);
    } else {
      // se o par for 01 (na forma de leitura usual da esquerda pra direita), o bit tem valor 0
      decodificado_quadros.push_back(false);
    }
  }
  return decodificado_quadros;
}

std::vector<bool> CamadaFisicaReceptoraDecodificacaoManchesterDiferencial(std::vector<bool>& manchester_diferencial_quadros) {
  // analisa cada par de bits, definido o valor do bit de acordo com o valor do par atual e o valor do par anterior
  bool last_bits_manchester_diferencial[2];
  last_bits_manchester_diferencial[0] = true;
  last_bits_manchester_diferencial[1] = false;
  std::vector<bool> decodificado_quadros;

  // 01101010 10011001

  // 0111             0010
  // 01 10 01 10      10 10 01 01

  // 01110010

  // 01001110

  for (unsigned int i = 0; i < manchester_diferencial_quadros.size() / 2; i++) {
    if (manchester_diferencial_quadros[2 * i] == last_bits_manchester_diferencial[0] &&
        manchester_diferencial_quadros[(2 * i) + 1] == last_bits_manchester_diferencial[1]) {
      // se o par for igual ao par anterior, o bit tem valor 0
      decodificado_quadros.push_back(false);
    } else {
      // se o par for diferente ao par anterior, o bit tem valor 1
      decodificado_quadros.push_back(true);
      last_bits_manchester_diferencial[0] = manchester_diferencial_quadros[2 * i];
      last_bits_manchester_diferencial[1] = manchester_diferencial_quadros[(2 * i) + 1];
    }
  }

  return decodificado_quadros;
}

