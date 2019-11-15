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
  std::vector<std::bitset<8>> quadros;
  for (long unsigned int i = 0; i < mensagem.size(); i++) {
    std::bitset<8> bits_da_letra(mensagem[i]);
    quadros.push_back(bits_da_letra);
  }


  CamadaFisicaTransmissora(quadros, tipo_de_codificacao);
}

void CamadaDeAplicacaoReceptora(std::vector<std::bitset<8>>& quadros) {
  std::string mensagem = "";
  for (std::bitset<8>& bits_da_letra: quadros) {
    unsigned long int ascii_letra = bits_da_letra.to_ulong();
    mensagem.push_back((char) ascii_letra);
  }

  AplicacaoReceptora(mensagem);
}

void AplicacaoReceptora(std::string& mensagem) {
  std::cout << "A mensagem recebida foi: " << mensagem << std::endl;
}
