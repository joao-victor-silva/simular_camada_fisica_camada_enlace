#include <vector>
#include "CamadaFisica.h"
#include "MeioDeComunicacao.h"
#include "CamadaAplicacao.h"

// Transmissao

void CamadaFisicaTransmissora(std::vector<bool>& quadros, int tipo_de_codificacao) {
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

  MeioDeComunicacao(fluxo_de_bits, tipo_de_codificacao);
}

std::vector<bool> CamadaFisicaTransmissoraCodificacaoBinaria(std::vector<bool>& quadros) {
  return quadros;
}

std::vector<bool> CamadaFisicaTransmissoraCodificacaoManchester(std::vector<bool>& quadros) {
  std::vector<bool> manchester_quadros;

  for (bool quadro: quadros) {
    if (quadro) {
      manchester_quadros.push_back(false);
      manchester_quadros.push_back(true);
    } else {
      manchester_quadros.push_back(true);
      manchester_quadros.push_back(false);
    }
  }

  return manchester_quadros;
}

std::vector<bool> CamadaFisicaTransmissoraCodificacaoManchesterDiferencial(std::vector<bool>& quadros) {
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
      if (quadro) {
        last_bit = 1;
        last_bits_manchester_diferencial[0] = !last_bits_manchester_diferencial[0];
        last_bits_manchester_diferencial[1] = !last_bits_manchester_diferencial[1];
        manchester_diferencial_quadros.push_back(last_bits_manchester_diferencial[0]);
        manchester_diferencial_quadros.push_back(last_bits_manchester_diferencial[1]);
      } else {
        last_bit = 0;
        manchester_diferencial_quadros.push_back(last_bits_manchester_diferencial[0]);
        manchester_diferencial_quadros.push_back(last_bits_manchester_diferencial[1]);
      }
    }
  }
  return manchester_diferencial_quadros;
}


// Recepcao

void CamadaFisicaReceptora(std::vector<bool>& quadros, int tipo_de_codificacao) {
  std::vector<bool> fluxo_de_bits;
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

std::vector<bool> CamadaFisicaReceptoraDecodificacaoBinaria(std::vector<bool>& quadros_em_binario) {
  return quadros_em_binario;
}

std::vector<bool> CamadaFisicaReceptoraDecodificacaoManchester(std::vector<bool>& manchester_quadros) {
  std::vector<bool> decodificado_quadros;
  for (unsigned int i = 0; i < manchester_quadros.size() / 2; i++) {
    if (!manchester_quadros[2 * i] && manchester_quadros[(2 * i) + 1]) {
      decodificado_quadros.push_back(true);
    } else {
      decodificado_quadros.push_back(false);
    }
  }
  return decodificado_quadros;
}

std::vector<bool> CamadaFisicaReceptoraDecodificacaoManchesterDiferencial(std::vector<bool>& manchester_diferencial_quadros) {
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
      decodificado_quadros.push_back(false);
    } else {
      decodificado_quadros.push_back(true);
      last_bits_manchester_diferencial[0] = manchester_diferencial_quadros[2 * i];
      last_bits_manchester_diferencial[1] = manchester_diferencial_quadros[(2 * i) + 1];
    }
  }

  return decodificado_quadros;
}

