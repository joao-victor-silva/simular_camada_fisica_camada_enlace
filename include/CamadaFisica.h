#include <bitset>
#include <vector>

// Transmissao

void CamadaFisicaTransmissora();
std::vector<std::bitset<8>> CamadaFisicaTransmissoraCodificacaoBinaria(std::vector<std::bitset<8>>&);
std::vector<std::bitset<8>> CamadaFisicaTransmissoraCodificacaoManchester(std::vector<std::bitset<8>>&);
void CamadaFisicaTransmissoraCodificacaoManchesterDiferencial();

// Recepcao

void CamadaFisicaReceptora();
void CamadaFisicaReceptoraDecodificacaoBinaria();
std::vector<std::bitset<8>> CamadaFisicaReceptoraDecodificacaoManchester(std::vector<std::bitset<8>>&);
void CamadaFisicaReceptoraDecodificacaoManchesterDiferencial();


// Meio de Comunicacao
void MeioDeComunicacao();
