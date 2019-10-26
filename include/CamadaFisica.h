#include <bitset>
#include <vector>

// Transmissao

void CamadaFisicaTransmissora();
void CamadaFisicaTransmissoraCodificacaoBinaria();
std::vector<std::bitset<8>> CamadaFisicaTransmissoraCodificacaoManchester(std::vector<std::bitset<8>>&);
void CamadaFisicaTransmissoraCodificacaoManchesterDiferencial();

// Recepcao

void CamadaFisicaReceptora();
void CamadaFisicaReceptoraDecodificacaoBinaria();
void CamadaFisicaReceptoraDecodificacaoManchester();
void CamadaFisicaReceptoraDecodificacaoManchesterDiferencial();


// Meio de Comunicacao
void MeioDeComunicacao();
