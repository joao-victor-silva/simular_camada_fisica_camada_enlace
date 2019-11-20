#include <vector>
#include <iostream>
#include <cstdlib>

#include "CamadaFisica.h"
#include "MeioDeComunicacao.h"

// Meio de Comunicacao
void MeioDeComunicacao(std::vector<bool>& fluxo_de_bits, int tipo_de_enquadramento,
                       int tipo_de_controle_de_erro, int tipo_de_codificacao, int percentual_de_erro) {
  std::vector<bool> fluxo_de_bits_ponto_A, fluxo_de_bits_ponto_B;

  srand(42);

  fluxo_de_bits_ponto_A = fluxo_de_bits;
  for (bool bit : fluxo_de_bits_ponto_A) {
    if (rand() % 100 < percentual_de_erro) {
      bit ? fluxo_de_bits_ponto_B.push_back(false) : fluxo_de_bits_ponto_B.push_back(true);
    } else {
      fluxo_de_bits_ponto_B.push_back(bit);
    }
  }

  CamadaFisicaReceptora(fluxo_de_bits_ponto_B, tipo_de_enquadramento,
                        tipo_de_controle_de_erro, tipo_de_codificacao);
}
