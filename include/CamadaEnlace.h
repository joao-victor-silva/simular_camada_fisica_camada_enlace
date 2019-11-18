#include <vector>
#include "CamadaFisica.h"

// Transmissao

void CamadaEnlaceDadosTransmissora(std::vector<bool>& quadros);
void CamadaEnlaceDadosTransmissoraEnquadramento(std::vector<bool>& quadros);
void CamadaEnlaceDadosTransmissoraControleDeErro(std::vector<bool>& quadros);
void CamadaEnlaceDadosTransmissoraControleDeFluxo(std::vector<bool>& quadros);

// Transmissao >> Enquadramento

void CamadaEnlaceDadosTransmissoraEnquadramentoContagemDeCaracteres(std::vector<bool>& quadro);
void CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoDeBytes(std::vector<bool>& quadro);
void CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoDeBits(std::vector<bool>& quadro);
void CamadaEnlaceDadosTransmissoraEnquadramentoViolacaoDaCamadaFisica(std::vector<bool>& quadro);

// Transmissao >> Controle de Erro

std::vector<bool> CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar(std::vector<bool>&);
std::vector<bool> CamadaEnlaceDadosTransmissoraControleDeErroBitParidadeImpar(std::vector<bool>&);
void CamadaEnlaceDadosTransmissoraControleDeErroCRC();
void CamadaEnlaceDadosTransmissoraControleDeErroCodigoDeHamming();

// Recepcao

void CamadaEnlaceDadosReceptora();
void CamadaEnlaceDadosReceptoraEnquadramento();
void CamadaEnlaceDadosReceptoraControleDeErro();
void CamadaEnlaceDadosReceptoraControleDeFluxo();

// Recepcao >> Enquadramento

void CamadaEnlaceDadosReceptoraEnquadramentoContagemDeCaracteres();
void CamadaEnlaceDadosReceptoraEnquadramentoInsercaoDeBytes();
void CamadaEnlaceDadosReceptoraEnquadramentoInsercaoDeBits();
void CamadaEnlaceDadosReceptoraEnquadramentoViolacaoDaCamadaFisica();

// Recepcao >> Controle de Erro

std::vector<bool> CamadaEnlaceDadosReceptoraControleDeErroBitParidadePar(std::vector<bool>&);
void CamadaEnlaceDadosReceptoraControleDeErroBitParidadeImpar();
void CamadaEnlaceDadosReceptoraControleDeErroCRC();
void CamadaEnlaceDadosReceptoraControleDeErroCodigoDeHamming();
