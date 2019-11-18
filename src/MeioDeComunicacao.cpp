#include <vector>
#include <iostream>

#include "CamadaFisica.h"
#include "MeioDeComunicacao.h"

// Meio de Comunicacao
void MeioDeComunicacao(std::vector<bool>& fluxo_de_bits, int tipo_de_codificacao) {
  std::vector<bool> fluxo_de_bits_ponto_A, fluxo_de_bits_ponto_B;

  fluxo_de_bits_ponto_A = fluxo_de_bits;
  for (bool bit : fluxo_de_bits_ponto_A) {
    fluxo_de_bits_ponto_B.push_back(bit);
  }

  CamadaFisicaReceptora(fluxo_de_bits_ponto_B, tipo_de_codificacao);
}
