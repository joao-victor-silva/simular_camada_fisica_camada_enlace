#include <vector>
#include <bitset>
#include <iostream>

#include "CamadaFisica.h"
#include "MeioDeComunicacao.h"

// Meio de Comunicacao
void MeioDeComunicacao(std::vector<std::bitset<8>>& fluxo_de_bits, int tipo_de_codificacao) {
  std::vector<std::bitset<8>> fluxo_de_bits_ponto_A, fluxo_de_bits_ponto_B;

  fluxo_de_bits_ponto_A = fluxo_de_bits;
  for (std::bitset<8>& quadro : fluxo_de_bits_ponto_A) {
    std::bitset<8> quadro_a_transmitir;
    for (int i = 0; i < 8; i++) {
      quadro_a_transmitir[i] = quadro[i];
    }
    fluxo_de_bits_ponto_B.push_back(quadro_a_transmitir);
  }

  CamadaFisicaReceptora(fluxo_de_bits_ponto_B, tipo_de_codificacao);
}
