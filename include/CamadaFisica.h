#include <vector>

// Transmissao

void CamadaFisicaTransmissora(std::vector<bool>&, int);
std::vector<bool> CamadaFisicaTransmissoraCodificacaoBinaria(std::vector<bool>&);
std::vector<bool> CamadaFisicaTransmissoraCodificacaoManchester(std::vector<bool>&);
std::vector<bool> CamadaFisicaTransmissoraCodificacaoManchesterDiferencial(std::vector<bool>&);

// Recepcao

void CamadaFisicaReceptora(std::vector<bool>&, int);
std::vector<bool> CamadaFisicaReceptoraDecodificacaoBinaria(std::vector<bool>&);
std::vector<bool> CamadaFisicaReceptoraDecodificacaoManchester(std::vector<bool>&);
std::vector<bool> CamadaFisicaReceptoraDecodificacaoManchesterDiferencial(std::vector<bool>&);
