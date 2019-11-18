#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <vector>

#include "CamadaFisica.h"
#include "CamadaEnlace.h"

TEST_CASE("O quadro 01001110 deve retornar 01001110 na codificacao \
    binaria", "[codificacao]") {

  std::vector<bool> quadros;
  std::vector<bool> quadros_em_binario;
  std::vector<bool> quadros_em_binario_esperado;

  quadros.push_back(false);
  quadros.push_back(true);
  quadros.push_back(true);
  quadros.push_back(true);
  quadros.push_back(false);
  quadros.push_back(false);
  quadros.push_back(true);
  quadros.push_back(false);

  quadros_em_binario = CamadaFisicaTransmissoraCodificacaoBinaria(quadros);

  quadros_em_binario_esperado.push_back(false);
  quadros_em_binario_esperado.push_back(true);
  quadros_em_binario_esperado.push_back(true);
  quadros_em_binario_esperado.push_back(true);
  quadros_em_binario_esperado.push_back(false);
  quadros_em_binario_esperado.push_back(false);
  quadros_em_binario_esperado.push_back(true);
  quadros_em_binario_esperado.push_back(false);

  REQUIRE(quadros_em_binario.size() == 8);
  REQUIRE(quadros_em_binario[0] == quadros_em_binario_esperado[0]);
  REQUIRE(quadros_em_binario[1] == quadros_em_binario_esperado[1]);
  REQUIRE(quadros_em_binario[2] == quadros_em_binario_esperado[2]);
  REQUIRE(quadros_em_binario[3] == quadros_em_binario_esperado[3]);
  REQUIRE(quadros_em_binario[4] == quadros_em_binario_esperado[4]);
  REQUIRE(quadros_em_binario[5] == quadros_em_binario_esperado[5]);
  REQUIRE(quadros_em_binario[6] == quadros_em_binario_esperado[6]);
  REQUIRE(quadros_em_binario[7] == quadros_em_binario_esperado[7]);
}


TEST_CASE("O quadro 01001110 deve retornar 01100101 10101001 na codificacao de \
    manchester", "[codificacao]") {
  std::vector<bool> quadros;
  std::vector<bool> manchester_quadros;
  std::vector<bool> manchester_quadros_esperado;

  quadros.push_back(false);
  quadros.push_back(true);
  quadros.push_back(true);
  quadros.push_back(true);
  quadros.push_back(false);
  quadros.push_back(false);
  quadros.push_back(true);
  quadros.push_back(false);

  manchester_quadros = CamadaFisicaTransmissoraCodificacaoManchester(quadros);

  manchester_quadros_esperado.push_back(true);
  manchester_quadros_esperado.push_back(false);
  manchester_quadros_esperado.push_back(false);
  manchester_quadros_esperado.push_back(true);
  manchester_quadros_esperado.push_back(false);
  manchester_quadros_esperado.push_back(true);
  manchester_quadros_esperado.push_back(false);
  manchester_quadros_esperado.push_back(true);

  manchester_quadros_esperado.push_back(true);
  manchester_quadros_esperado.push_back(false);
  manchester_quadros_esperado.push_back(true);
  manchester_quadros_esperado.push_back(false);
  manchester_quadros_esperado.push_back(false);
  manchester_quadros_esperado.push_back(true);
  manchester_quadros_esperado.push_back(true);
  manchester_quadros_esperado.push_back(false);

  REQUIRE(manchester_quadros.size() == 16);
  REQUIRE(manchester_quadros[0] == manchester_quadros_esperado[0]);
  REQUIRE(manchester_quadros[1] == manchester_quadros_esperado[1]);
  REQUIRE(manchester_quadros[2] == manchester_quadros_esperado[2]);
  REQUIRE(manchester_quadros[3] == manchester_quadros_esperado[3]);
  REQUIRE(manchester_quadros[4] == manchester_quadros_esperado[4]);
  REQUIRE(manchester_quadros[5] == manchester_quadros_esperado[5]);
  REQUIRE(manchester_quadros[6] == manchester_quadros_esperado[6]);
  REQUIRE(manchester_quadros[7] == manchester_quadros_esperado[7]);
  REQUIRE(manchester_quadros[8] == manchester_quadros_esperado[8]);
  REQUIRE(manchester_quadros[9] == manchester_quadros_esperado[9]);
  REQUIRE(manchester_quadros[10] == manchester_quadros_esperado[10]);
  REQUIRE(manchester_quadros[11] == manchester_quadros_esperado[11]);
  REQUIRE(manchester_quadros[12] == manchester_quadros_esperado[12]);
  REQUIRE(manchester_quadros[13] == manchester_quadros_esperado[13]);
  REQUIRE(manchester_quadros[14] == manchester_quadros_esperado[14]);
  REQUIRE(manchester_quadros[15] == manchester_quadros_esperado[15]);
}


TEST_CASE("O quadro 01100101 10101001 na codificacao de \
    manchester deve retornar o quadro 01001110 decodificado", "[codificacao]") {
  std::vector<bool> quadro_esperado;
  std::vector<bool> manchester_quadros;
  std::vector<bool> decodificado_quadros;

  quadro_esperado.push_back(false);
  quadro_esperado.push_back(true);
  quadro_esperado.push_back(true);
  quadro_esperado.push_back(true);
  quadro_esperado.push_back(false);
  quadro_esperado.push_back(false);
  quadro_esperado.push_back(true);
  quadro_esperado.push_back(false);

  manchester_quadros.push_back(true);
  manchester_quadros.push_back(false);
  manchester_quadros.push_back(false);
  manchester_quadros.push_back(true);
  manchester_quadros.push_back(false);
  manchester_quadros.push_back(true);
  manchester_quadros.push_back(false);
  manchester_quadros.push_back(true);

  manchester_quadros.push_back(true);
  manchester_quadros.push_back(false);
  manchester_quadros.push_back(true);
  manchester_quadros.push_back(false);
  manchester_quadros.push_back(false);
  manchester_quadros.push_back(true);
  manchester_quadros.push_back(true);
  manchester_quadros.push_back(false);

  decodificado_quadros =
    CamadaFisicaReceptoraDecodificacaoManchester(manchester_quadros);

  REQUIRE(decodificado_quadros.size() == 8);
  REQUIRE(quadro_esperado[0] == decodificado_quadros[0]);
  REQUIRE(quadro_esperado[1] == decodificado_quadros[1]);
  REQUIRE(quadro_esperado[2] == decodificado_quadros[2]);
  REQUIRE(quadro_esperado[3] == decodificado_quadros[3]);
  REQUIRE(quadro_esperado[4] == decodificado_quadros[4]);
  REQUIRE(quadro_esperado[5] == decodificado_quadros[5]);
  REQUIRE(quadro_esperado[6] == decodificado_quadros[6]);
  REQUIRE(quadro_esperado[7] == decodificado_quadros[7]);
}

TEST_CASE("O quadro 01001110 na codificacao binaria \
    deve retornar o quadro 01001110 decodificado", "[codificacao]") {
  std::vector<bool> quadro_esperado;
  std::vector<bool> quadros_em_binario;
  std::vector<bool> quadros_em_binario_decodificado;

  quadro_esperado.push_back(false);
  quadro_esperado.push_back(true);
  quadro_esperado.push_back(true);
  quadro_esperado.push_back(true);
  quadro_esperado.push_back(false);
  quadro_esperado.push_back(false);
  quadro_esperado.push_back(true);
  quadro_esperado.push_back(false);

  quadros_em_binario.push_back(false);
  quadros_em_binario.push_back(true);
  quadros_em_binario.push_back(true);
  quadros_em_binario.push_back(true);
  quadros_em_binario.push_back(false);
  quadros_em_binario.push_back(false);
  quadros_em_binario.push_back(true);
  quadros_em_binario.push_back(false);

  quadros_em_binario_decodificado =
    CamadaFisicaReceptoraDecodificacaoBinaria(quadros_em_binario);

  REQUIRE(quadros_em_binario_decodificado.size() == 8);
  REQUIRE(quadro_esperado[0] == quadros_em_binario_decodificado[0]);
  REQUIRE(quadro_esperado[1] == quadros_em_binario_decodificado[1]);
  REQUIRE(quadro_esperado[2] == quadros_em_binario_decodificado[2]);
  REQUIRE(quadro_esperado[3] == quadros_em_binario_decodificado[3]);
  REQUIRE(quadro_esperado[4] == quadros_em_binario_decodificado[4]);
  REQUIRE(quadro_esperado[5] == quadros_em_binario_decodificado[5]);
  REQUIRE(quadro_esperado[6] == quadros_em_binario_decodificado[6]);
  REQUIRE(quadro_esperado[7] == quadros_em_binario_decodificado[7]);
}


TEST_CASE("O quadro 01001110 deve retornar 01011010 10011001 na codificacao de \
    manchester diferencial", "[codificacao]") {
  std::vector<bool> quadros;
  std::vector<bool> manchester_diferencial_quadros;
  std::vector<bool> manchester_diferencial_quadros_esperado;

  quadros.push_back(false);
  quadros.push_back(true);
  quadros.push_back(true);
  quadros.push_back(true);
  quadros.push_back(false);
  quadros.push_back(false);
  quadros.push_back(true);
  quadros.push_back(false);

  manchester_diferencial_quadros = CamadaFisicaTransmissoraCodificacaoManchesterDiferencial(quadros);

  manchester_diferencial_quadros_esperado.push_back(true);
  manchester_diferencial_quadros_esperado.push_back(false);
  manchester_diferencial_quadros_esperado.push_back(false);
  manchester_diferencial_quadros_esperado.push_back(true);
  manchester_diferencial_quadros_esperado.push_back(true);
  manchester_diferencial_quadros_esperado.push_back(false);
  manchester_diferencial_quadros_esperado.push_back(false);
  manchester_diferencial_quadros_esperado.push_back(true);

  manchester_diferencial_quadros_esperado.push_back(false);
  manchester_diferencial_quadros_esperado.push_back(true);
  manchester_diferencial_quadros_esperado.push_back(false);
  manchester_diferencial_quadros_esperado.push_back(true);
  manchester_diferencial_quadros_esperado.push_back(true);
  manchester_diferencial_quadros_esperado.push_back(false);
  manchester_diferencial_quadros_esperado.push_back(true);
  manchester_diferencial_quadros_esperado.push_back(false);

  REQUIRE(manchester_diferencial_quadros.size() == 16);
  REQUIRE(manchester_diferencial_quadros[0] == manchester_diferencial_quadros_esperado[0]);
  REQUIRE(manchester_diferencial_quadros[1] == manchester_diferencial_quadros_esperado[1]);
  REQUIRE(manchester_diferencial_quadros[2] == manchester_diferencial_quadros_esperado[2]);
  REQUIRE(manchester_diferencial_quadros[3] == manchester_diferencial_quadros_esperado[3]);
  REQUIRE(manchester_diferencial_quadros[4] == manchester_diferencial_quadros_esperado[4]);
  REQUIRE(manchester_diferencial_quadros[5] == manchester_diferencial_quadros_esperado[5]);
  REQUIRE(manchester_diferencial_quadros[6] == manchester_diferencial_quadros_esperado[6]);
  REQUIRE(manchester_diferencial_quadros[7] == manchester_diferencial_quadros_esperado[7]);
  REQUIRE(manchester_diferencial_quadros[8] == manchester_diferencial_quadros_esperado[8]);
  REQUIRE(manchester_diferencial_quadros[9] == manchester_diferencial_quadros_esperado[9]);
  REQUIRE(manchester_diferencial_quadros[10] == manchester_diferencial_quadros_esperado[10]);
  REQUIRE(manchester_diferencial_quadros[11] == manchester_diferencial_quadros_esperado[11]);
  REQUIRE(manchester_diferencial_quadros[12] == manchester_diferencial_quadros_esperado[12]);
  REQUIRE(manchester_diferencial_quadros[13] == manchester_diferencial_quadros_esperado[13]);
  REQUIRE(manchester_diferencial_quadros[14] == manchester_diferencial_quadros_esperado[14]);
  REQUIRE(manchester_diferencial_quadros[15] == manchester_diferencial_quadros_esperado[15]);
}

TEST_CASE("O quadro 01011010 10011001 na codificacao de \
    manchester diferencial deve retornar o quadro 01001110 decodificado", "[codificacao]") {
  std::vector<bool> quadro_esperado;
  std::vector<bool> manchester_diferencial_quadros;
  std::vector<bool> decodificado_quadros;

  quadro_esperado.push_back(false);
  quadro_esperado.push_back(true);
  quadro_esperado.push_back(true);
  quadro_esperado.push_back(true);
  quadro_esperado.push_back(false);
  quadro_esperado.push_back(false);
  quadro_esperado.push_back(true);
  quadro_esperado.push_back(false);

  manchester_diferencial_quadros.push_back(true);
  manchester_diferencial_quadros.push_back(false);
  manchester_diferencial_quadros.push_back(false);
  manchester_diferencial_quadros.push_back(true);
  manchester_diferencial_quadros.push_back(true);
  manchester_diferencial_quadros.push_back(false);
  manchester_diferencial_quadros.push_back(false);
  manchester_diferencial_quadros.push_back(true);

  manchester_diferencial_quadros.push_back(false);
  manchester_diferencial_quadros.push_back(true);
  manchester_diferencial_quadros.push_back(false);
  manchester_diferencial_quadros.push_back(true);
  manchester_diferencial_quadros.push_back(true);
  manchester_diferencial_quadros.push_back(false);
  manchester_diferencial_quadros.push_back(true);
  manchester_diferencial_quadros.push_back(false);

  decodificado_quadros =
    CamadaFisicaReceptoraDecodificacaoManchesterDiferencial(manchester_diferencial_quadros);

  REQUIRE(decodificado_quadros.size() == 8);
  REQUIRE(quadro_esperado[0] == decodificado_quadros[0]);
  REQUIRE(quadro_esperado[1] == decodificado_quadros[1]);
  REQUIRE(quadro_esperado[2] == decodificado_quadros[2]);
  REQUIRE(quadro_esperado[3] == decodificado_quadros[3]);
  REQUIRE(quadro_esperado[4] == decodificado_quadros[4]);
  REQUIRE(quadro_esperado[5] == decodificado_quadros[5]);
  REQUIRE(quadro_esperado[6] == decodificado_quadros[6]);
  REQUIRE(quadro_esperado[7] == decodificado_quadros[7]);
}

TEST_CASE("O quadro 01001110 deve retornar 001001110 como resultado do \
    controle de erro com bit de paridade par", "[enquadramento]") {

  std::vector<bool> quadro;
  std::vector<bool> quadro_esperado;
  std::vector<bool> quadro_com_paridade_par;

  quadro.push_back(false);
  quadro.push_back(true);
  quadro.push_back(true);
  quadro.push_back(true);
  quadro.push_back(false);
  quadro.push_back(false);
  quadro.push_back(true);
  quadro.push_back(false);

  quadro_esperado.push_back(false);
  quadro_esperado.push_back(true);
  quadro_esperado.push_back(true);
  quadro_esperado.push_back(true);
  quadro_esperado.push_back(false);
  quadro_esperado.push_back(false);
  quadro_esperado.push_back(true);
  quadro_esperado.push_back(false);
  quadro_esperado.push_back(false);

  quadro_com_paridade_par = CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar(quadro);

  REQUIRE(quadro_com_paridade_par.size() == 9);
  REQUIRE(quadro_esperado[0] == quadro_com_paridade_par[0]);
  REQUIRE(quadro_esperado[1] == quadro_com_paridade_par[1]);
  REQUIRE(quadro_esperado[2] == quadro_com_paridade_par[2]);
  REQUIRE(quadro_esperado[3] == quadro_com_paridade_par[3]);
  REQUIRE(quadro_esperado[4] == quadro_com_paridade_par[4]);
  REQUIRE(quadro_esperado[5] == quadro_com_paridade_par[5]);
  REQUIRE(quadro_esperado[6] == quadro_com_paridade_par[6]);
  REQUIRE(quadro_esperado[7] == quadro_com_paridade_par[7]);
  REQUIRE(quadro_esperado[8] == quadro_com_paridade_par[8]);
}

TEST_CASE("O quadro 001001110 deve retornar 01001110 como resultado do \
    controle de erro com bit de paridade par", "[enquadramento]") {

  std::vector<bool> quadro;
  std::vector<bool> quadro_esperado;
  std::vector<bool> quadro_com_paridade_par;

  quadro.push_back(false);
  quadro.push_back(true);
  quadro.push_back(true);
  quadro.push_back(true);
  quadro.push_back(false);
  quadro.push_back(false);
  quadro.push_back(true);
  quadro.push_back(false);
  quadro.push_back(false);

  quadro_esperado.push_back(false);
  quadro_esperado.push_back(true);
  quadro_esperado.push_back(true);
  quadro_esperado.push_back(true);
  quadro_esperado.push_back(false);
  quadro_esperado.push_back(false);
  quadro_esperado.push_back(true);
  quadro_esperado.push_back(false);

  quadro_sem_paridade_par = CamadaEnlaceDadosReceptoraControleDeErroBitParidadePar(quadro);

  REQUIRE(quadro_sem_paridade_par.size() == 8);
  REQUIRE(quadro_esperado[0] == quadro_sem_paridade_par[0]);
  REQUIRE(quadro_esperado[1] == quadro_sem_paridade_par[1]);
  REQUIRE(quadro_esperado[2] == quadro_sem_paridade_par[2]);
  REQUIRE(quadro_esperado[3] == quadro_sem_paridade_par[3]);
  REQUIRE(quadro_esperado[4] == quadro_sem_paridade_par[4]);
  REQUIRE(quadro_esperado[5] == quadro_sem_paridade_par[5]);
  REQUIRE(quadro_esperado[6] == quadro_sem_paridade_par[6]);
  REQUIRE(quadro_esperado[7] == quadro_sem_paridade_par[7]);
  REQUIRE(quadro_esperado[8] == quadro_sem_paridade_par[8]);
}
