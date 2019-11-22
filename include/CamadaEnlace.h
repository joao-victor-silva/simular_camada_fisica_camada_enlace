#include <vector>
#include "CamadaFisica.h"

// Transmissao

void CamadaEnlaceDadosTransmissora(std::vector<bool>&, int, int, int, int);
std::vector<bool> CamadaEnlaceDadosTransmissoraEnquadramento(std::vector<bool>&, int);
std::vector<bool> CamadaEnlaceDadosTransmissoraControleDeErro(std::vector<bool>&, int);
std::vector<bool> CamadaEnlaceDadosTransmissoraControleDeFluxo(std::vector<bool>&);

// Transmissao >> Enquadramento

std::vector<bool> CamadaEnlaceDadosTransmissoraEnquadramentoContagemDeCaracteres(std::vector<bool>&);
std::vector<bool> CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoDeBytes(std::vector<bool>&);
std::vector<bool> CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoDeBits(std::vector<bool>&);

// Transmissao >> Controle de Erro

std::vector<bool> CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar(std::vector<bool>&);
std::vector<bool> CamadaEnlaceDadosTransmissoraControleDeErroBitParidadeImpar(std::vector<bool>&);
std::vector<bool> CamadaEnlaceDadosTransmissoraControleDeErroCRC(std::vector<bool>&);
std::vector<bool> CamadaEnlaceDadosTransmissoraControleDeErroCodigoDeHamming(std::vector<bool>&);

// Recepcao

void CamadaEnlaceDadosReceptora(std::vector<bool>&, int, int, int);
std::vector<bool> CamadaEnlaceDadosReceptoraEnquadramento(std::vector<bool>&, int);
std::vector<bool> CamadaEnlaceDadosReceptoraControleDeErro(std::vector<bool>&, int);
std::vector<bool> CamadaEnlaceDadosReceptoraControleDeFluxo(std::vector<bool>&);

// Recepcao >> Enquadramento

std::vector<bool> CamadaEnlaceDadosReceptoraEnquadramentoContagemDeCaracteres(std::vector<bool>&);
std::vector<bool> CamadaEnlaceDadosReceptoraEnquadramentoInsercaoDeBytes(std::vector<bool>&);
std::vector<bool> CamadaEnlaceDadosReceptoraEnquadramentoInsercaoDeBits(std::vector<bool>&);

// Recepcao >> Controle de Erro

std::vector<bool> CamadaEnlaceDadosReceptoraControleDeErroBitParidadePar(std::vector<bool>&);
std::vector<bool> CamadaEnlaceDadosReceptoraControleDeErroBitParidadeImpar(std::vector<bool>&);
std::vector<bool> CamadaEnlaceDadosReceptoraControleDeErroCRC(std::vector<bool>&);
std::vector<bool> CamadaEnlaceDadosReceptoraControleDeErroCodigoDeHamming(std::vector<bool>&);



std::vector<bool> XOR(std::vector<bool>&, std::vector<bool>&);
std::vector<bool> DivisaoModulo2(std::vector<bool>&);
