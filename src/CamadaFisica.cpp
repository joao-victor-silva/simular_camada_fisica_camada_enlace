#include <vector>
#include <bitset>
#include <iostream>

#include "CamadaFisica.h"

// Transmissao

void CamadaFisicaTransmissora(std::vector<bitset<8>>& quadros, int tipo_de_codificacao) {
  std::vector<std::bitset<8>> fluxo_de_bits;
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

  MeioDeComunicacao(fluxo_de_bits, tipo_de_codificacao);
}

std::vector<std::bitset<8>> CamadaFisicaTransmissoraCodificacaoBinaria(std::vector<std::bitset<8>>& quadros) {
  return quadros;
}

std::vector<std::bitset<8>> CamadaFisicaTransmissoraCodificacaoManchester(std::vector<std::bitset<8>>& quadros) {
  std::bitset<8> clock;
  clock = 0b01010101;
  std::vector<std::bitset<8>> manchester_quadros;

  for (std::bitset<8>& quadro: quadros) {
    std::bitset<8> inicio_do_quadro;
    std::bitset<8> fim_do_quadro;

    for (int i = 0; i <= 3; i++) {
      fim_do_quadro[(2 * i)] = quadro[i];
      fim_do_quadro[(2 * i) + 1] = quadro[i];
    }

    for (int i = 0; i <= 3; i++) {
      inicio_do_quadro[(2 * i)] = quadro[4 + i];
      inicio_do_quadro[(2 * i) + 1] = quadro[4 + i];
    }

    // bitwise XOR
    // std::cout << "quadro:\t\t\t" << quadro << std::endl;
    // std::cout << "fim do quadro:\t\t" << fim_do_quadro << std::endl;
    // std::cout << "clock:\t\t\t" << clock << std::endl;
    manchester_quadros.push_back(std::bitset<8> (clock ^ fim_do_quadro));
    manchester_quadros.push_back(std::bitset<8> (inicio_do_quadro ^ clock));
    // std::cout << "resultado:\t\t" << manchester_quadro[0] << std::endl;
  }

  return manchester_quadros;
}

std::vector<std::bitset<8>> CamadaFisicaTransmissoraCodificacaoManchesterDiferencial(std::vector<std::bitset<8>>& quadros) {
  std::bitset<2> last_bit_manchester = 0b00;
  int last_bit = -1;
  std::vector<std::bitset<8>> manchester_diferencial_quadros;

  // 01001110

  // 01110010

  // 0111             0010
  // 01 10 01 10      10 10 01 01

  // 01101010 10011001

  for (std::bitset<8>& quadro: quadros) {
    std::bitset<8> inicio_do_quadro;
    std::bitset<8> fim_do_quadro;

    for (int i = 0; i <= 3; i++) {
      if (last_bit == -1) {
        if (quadro[i] == 0b0) {
          last_bit = 0;
          last_bit_manchester[0] = 0b1;
          last_bit_manchester[1] = 0b0;
          fim_do_quadro[(2 * i)] = last_bit_manchester[0];
          fim_do_quadro[(2 * i) + 1] = last_bit_manchester[1];
        } else {
          last_bit = 1;
          last_bit_manchester[0] = 0b0;
          last_bit_manchester[1] = 0b1;
          fim_do_quadro[(2 * i)] = last_bit_manchester[0];
          fim_do_quadro[(2 * i) + 1] = last_bit_manchester[1];
        }
      } else {
        if (quadro[i] == 0) {
          last_bit = 0;
          fim_do_quadro[(2 * i)] = last_bit_manchester[0];
          fim_do_quadro[(2 * i) + 1] = last_bit_manchester[1];
        } else {
          last_bit = 1;
          last_bit_manchester = ~last_bit_manchester;
          fim_do_quadro[(2 * i)] = last_bit_manchester[0];
          fim_do_quadro[(2 * i) + 1] = last_bit_manchester[1];
        }
      }
    }

    for (int i = 0; i <= 3; i++) {
      if (quadro[4 + i] == 0) {
        last_bit = 0;
        inicio_do_quadro[(2 * i)] = last_bit_manchester[0];
        inicio_do_quadro[(2 * i) + 1] = last_bit_manchester[1];
      } else {
        last_bit = 1;
        last_bit_manchester = ~last_bit_manchester;
        inicio_do_quadro[(2 * i)] = last_bit_manchester[0];
        inicio_do_quadro[(2 * i) + 1] = last_bit_manchester[1];
      }
    }


    manchester_diferencial_quadros.push_back(fim_do_quadro);
    manchester_diferencial_quadros.push_back(inicio_do_quadro);
  }

  return manchester_diferencial_quadros;
}


// Recepcao

void CamadaFisicaReceptora(std::vector<std::bitset<8>>& quadros, int tipo_de_codificacao) {
  std::vector<std::bitset<8>> fluxo_de_bits;
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

  CamadaDeAplicacaoReceptora(fluxo_de_bits);
}

std::vector<std::bitset<8>> CamadaFisicaReceptoraDecodificacaoBinaria(std::vector<std::bitset<8>>& quadros_em_binario) {
  return quadros_em_binario;
}

std::vector<std::bitset<8>> CamadaFisicaReceptoraDecodificacaoManchester(std::vector<std::bitset<8>>& manchester_quadros) {
  std::vector<std::bitset<8>> decodificado_quadros;
  for (unsigned int i = 0; i < manchester_quadros.size() / 2; i++) {
    std::bitset<8> decodificado_quadro;
    for (int j = 0; j <= 3; j++) {
      if (manchester_quadros[2 * i][(2 * j)] == 0b0 &&
          manchester_quadros[2 * i][(2 * j) + 1] == 0b1) {
        decodificado_quadro[j] = 0b1;
      } else {
        decodificado_quadro[j] = 0b0;
      }
    }

    for (int j = 0; j <= 3; j++) {
      if (manchester_quadros[(2 * i) + 1][(2 * j)] == 0b0 &&
          manchester_quadros[(2 * i) + 1][(2 * j) + 1] == 0b1) {
        decodificado_quadro[4 + j] = 0b1;
      } else {
        decodificado_quadro[4 + j] = 0b0;
      }
    }
    decodificado_quadros.push_back(decodificado_quadro);
  }

  return decodificado_quadros;
}

std::vector<std::bitset<8>> CamadaFisicaReceptoraDecodificacaoManchesterDiferencial(std::vector<std::bitset<8>>& manchester_diferencial_quadros) {
  std::bitset<2> last_bit_manchester_diferencial = 0b01;
  int last_bit = -1;
  std::vector<std::bitset<8>> decodificado_quadros;

  // 01101010 10011001

  // 0111             0010
  // 01 10 01 10      10 10 01 01

  // 01110010

  // 01001110

  for (unsigned int i = 0; i < manchester_diferencial_quadros.size() / 2; i++) {
    std::bitset<8> decodificado_quadro;
    for (int j = 0; j <= 3; j++) {
      std::bitset<2> encode_bit;
      encode_bit[0] = manchester_diferencial_quadros[2 * i][(2 * j)];
      encode_bit[1] = manchester_diferencial_quadros[2 * i][(2 * j) + 1];
      if (last_bit == -1) {
        if (encode_bit == last_bit_manchester_diferencial) {
          decodificado_quadro[j] = 0b0;
          last_bit = 0;
        } else {
          decodificado_quadro[j] = 0b1;
          last_bit = 1;
          last_bit_manchester_diferencial = encode_bit;
        }
      } else {
        if (encode_bit == last_bit_manchester_diferencial) {
          decodificado_quadro[j] = 0b0;
          last_bit = 0;
        } else {
          decodificado_quadro[j] = 0b1;
          last_bit = 1;
          last_bit_manchester_diferencial = encode_bit;
        }
      }
    }

    for (int j = 0; j <= 3; j++) {
      std::bitset<2> encode_bit;
      encode_bit[0] = manchester_diferencial_quadros[(2 * i) + 1][(2 * j)];
      encode_bit[1] = manchester_diferencial_quadros[(2 * i) + 1][(2 * j) + 1];

      if (encode_bit == last_bit_manchester_diferencial) {
        decodificado_quadro[4 + j] = 0b0;
        last_bit = 0;
      } else {
        decodificado_quadro[4 + j] = 0b1;
        last_bit = 1;
        last_bit_manchester_diferencial = encode_bit;
      }
    }

    decodificado_quadros.push_back(decodificado_quadro);
  }

  return decodificado_quadros;
}


// Meio de Comunicacao
void MeioDeComunicacao() {

}
