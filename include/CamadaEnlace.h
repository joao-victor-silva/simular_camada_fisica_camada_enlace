#include <vector>
#include "CamadaFisica.h"

// Transmissao

void CamadaEnlaceDadosTransmissora(std::vector<bool>&);
void CamadaEnlaceDadosTransmissoraEnquadramento(std::vector<bool>&);
void CamadaEnlaceDadosTransmissoraControleDeErro(std::vector<bool>&);
void CamadaEnlaceDadosTransmissoraControleDeFluxo(std::vector<bool>&);

// Transmissao >> Enquadramento

void CamadaEnlaceDadosTransmissoraEnquadramentoContagemDeCaracteres(std::vector<bool>&);
void CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoDeBytes(std::vector<bool>&);
void CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoDeBits(std::vector<bool>&);

// Transmissao >> Controle de Erro

std::vector<bool> CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar(std::vector<bool>&);
std::vector<bool> CamadaEnlaceDadosTransmissoraControleDeErroBitParidadeImpar(std::vector<bool>&);
std::vector<bool> CamadaEnlaceDadosTransmissoraControleDeErroCRC(std::vector<bool>&);
void CamadaEnlaceDadosTransmissoraControleDeErroCodigoDeHamming();

// Recepcao

void CamadaEnlaceDadosReceptora(std::vector<bool>&);
void CamadaEnlaceDadosReceptoraEnquadramento(std::vector<bool>&);
void CamadaEnlaceDadosReceptoraControleDeErro(std::vector<bool>&);
void CamadaEnlaceDadosReceptoraControleDeFluxo(std::vector<bool>&);

// Recepcao >> Enquadramento

void CamadaEnlaceDadosReceptoraEnquadramentoContagemDeCaracteres(std::vector<bool>&);
void CamadaEnlaceDadosReceptoraEnquadramentoInsercaoDeBytes(std::vector<bool>&);
void CamadaEnlaceDadosReceptoraEnquadramentoInsercaoDeBits(std::vector<bool>&);

// Recepcao >> Controle de Erro

std::vector<bool> CamadaEnlaceDadosReceptoraControleDeErroBitParidadePar(std::vector<bool>&);
std::vector<bool> CamadaEnlaceDadosReceptoraControleDeErroBitParidadeImpar(std::vector<bool>&);
std::vector<bool> CamadaEnlaceDadosReceptoraControleDeErroCRC(std::vector<bool>&);
void CamadaEnlaceDadosReceptoraControleDeErroCodigoDeHamming();



std::vector<bool> XOR(std::vector<bool>&, std::vector<bool>&);
std::vector<bool> DivisaoModulo2(std::vector<bool>&);
