#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <vector>
#include <bitset>

#include "CamadaFisica.h"

TEST_CASE("O quadro 01001110 deve retornar 01001110 na codificacao \
    binaria", "[codificacao]") {

  std::vector<std::bitset<8>> quadros;
  std::vector<std::bitset<8>> quadros_em_binario;
  std::vector<std::bitset<8>> quadros_em_binario_esperado;

  std::bitset<8> mensagem;
  mensagem = 0b01001110;
  quadros.push_back(mensagem);

  quadros_em_binario = CamadaFisicaTransmissoraCodificacaoBinaria(quadros);

  quadros_em_binario_esperado.push_back(std::bitset<8> (0b01001110));

  REQUIRE(quadros_em_binario.size() == 1);
  REQUIRE(quadros_em_binario[0] == quadros_em_binario_esperado[0]);

}


TEST_CASE("O quadro 01001110 deve retornar 01100101 10101001 na codificacao de \
    manchester", "[codificacao]") {
  std::vector<std::bitset<8>> quadros;
  std::vector<std::bitset<8>> manchester_quadros;
  std::vector<std::bitset<8>> manchester_quadros_esperado;

  std::bitset<8> mensagem;
  mensagem = 0b01001110;
  quadros.push_back(mensagem);

  manchester_quadros = CamadaFisicaTransmissoraCodificacaoManchester(quadros);

  manchester_quadros_esperado.push_back(std::bitset<8> (0b10101001));
  manchester_quadros_esperado.push_back(std::bitset<8> (0b01100101));

  REQUIRE(manchester_quadros.size() == 2);
  REQUIRE(manchester_quadros[0] == manchester_quadros_esperado[0]);
  REQUIRE(manchester_quadros[1] == manchester_quadros_esperado[1]);
}


TEST_CASE("O quadro 01100101 10101001 na codificacao de \
    manchester deve retornar o quadro 01001110 decodificado", "[codificacao]") {
  std::bitset<8> quadro_esperado;
  std::vector<std::bitset<8>> manchester_quadros;
  std::vector<std::bitset<8>> decodificado_quadros;

  quadro_esperado = 0b01001110;

  manchester_quadros.push_back(std::bitset<8> (0b10101001));
  manchester_quadros.push_back(std::bitset<8> (0b01100101));

  decodificado_quadros =
    CamadaFisicaReceptoraDecodificacaoManchester(manchester_quadros);

  REQUIRE(decodificado_quadros.size() == 1);
  REQUIRE(quadro_esperado == decodificado_quadros[0]);
}

TEST_CASE("O quadro 01001110 na codificacao binaria \
    deve retornar o quadro 01001110 decodificado", "[codificacao]") {
  std::bitset<8> quadro_esperado;
  std::vector<std::bitset<8>> quadros_em_binario;
  std::vector<std::bitset<8>> quadros_em_binario_decodificado;

  quadro_esperado = 0b01001110;

  quadros_em_binario.push_back(std::bitset<8> (0b01001110));

  quadros_em_binario_decodificado =
    CamadaFisicaReceptoraDecodificacaoBinaria(quadros_em_binario);

  REQUIRE(quadros_em_binario_decodificado.size() == 1);
  REQUIRE(quadro_esperado == quadros_em_binario_decodificado[0]);
}


TEST_CASE("O quadro 01001110 deve retornar 01101010 01100101 na codificacao de \
    manchester diferencial", "[codificacao]") {
  std::vector<std::bitset<8>> quadros;
  std::vector<std::bitset<8>> manchester_diferencial_quadros;
  std::vector<std::bitset<8>> manchester_diferencial_quadros_esperado;

  std::bitset<8> mensagem;
  mensagem = 0b01001110;
  quadros.push_back(mensagem);

  manchester_diferencial_quadros = CamadaFisicaTransmissoraCodificacaoManchesterDiferencial(quadros);

  manchester_diferencial_quadros_esperado.push_back(std::bitset<8> (0b01100101));
  manchester_diferencial_quadros_esperado.push_back(std::bitset<8> (0b01101010));

  REQUIRE(manchester_diferencial_quadros.size() == 2);
  REQUIRE(manchester_diferencial_quadros[0] == manchester_diferencial_quadros_esperado[0]);
  REQUIRE(manchester_diferencial_quadros[1] == manchester_diferencial_quadros_esperado[1]);
}
