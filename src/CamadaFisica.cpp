#include <vector>
#include <bitset>
#include <iostream>

#include "CamadaFisica.h"


// Transmissao

void CamadaFisicaTransmissora() {

}

void CamadaFisicaTransmissoraCodificacaoBinaria() {

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

void CamadaFisicaTransmissoraCodificacaoManchesterDiferencial() {

}


// Recepcao

void CamadaFisicaReceptora() {

}

void CamadaFisicaReceptoraDecodificacaoBinaria() {

}

void CamadaFisicaReceptoraDecodificacaoManchester() {

}

void CamadaFisicaReceptoraDecodificacaoManchesterDiferencial() {

}


// Meio de Comunicacao
void MeioDeComunicacao() {

}
