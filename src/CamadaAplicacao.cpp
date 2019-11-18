#include <vector>
#include <bitset>
#include <string>
#include <iostream>

#include "CamadaAplicacao.h"
#include "CamadaFisica.h"

void AplicacaoTransmissora(int tipo_de_codificacao) {
  std::string mensagem;
  std::cout << "Digite uma mensagem" << std::endl;
  std::getline(std::cin, mensagem);
  CamadaDeAplicacaoTransmissora(mensagem, tipo_de_codificacao);
}

void CamadaDeAplicacaoTransmissora(std::string& mensagem, int tipo_de_codificacao) {
  std::vector<bool> quadros;
  for (long unsigned int i = 0; i < mensagem.size(); i++) {
    std::bitset<8> bits_da_letra(mensagem[i]);
    for (int j = 0; j < 8; j++) {
      if (bits_da_letra[j] == 0b1) {
        quadros.push_back(true);
      } else {
        quadros.push_back(false);
      }
    }
  }

  CamadaFisicaTransmissora(quadros, tipo_de_codificacao);
}

void CamadaDeAplicacaoReceptora(std::vector<bool>& quadros) {
  std::string mensagem = "";
  for (unsigned int i = 0; i < quadros.size() / 8; i++) {
    std::bitset<8> bits_da_letra;
    for (int j = 0; j < 8; j++) {
      bits_da_letra[j] = quadros[(i * 8) + j] ? 0b1 : 0b0;
    }
    unsigned long int ascii_letra = bits_da_letra.to_ulong();
    mensagem.push_back((char) ascii_letra);
  }
  AplicacaoReceptora(mensagem);
}

void AplicacaoReceptora(std::string& mensagem) {
  std::cout << "A mensagem recebida foi: " << mensagem << std::endl;
}
