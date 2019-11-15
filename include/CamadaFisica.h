#include <bitset>
#include <vector>

// Transmissao

void CamadaFisicaTransmissora();
std::vector<std::bitset<8>> CamadaFisicaTransmissoraCodificacaoBinaria(std::vector<std::bitset<8>>&);
std::vector<std::bitset<8>> CamadaFisicaTransmissoraCodificacaoManchester(std::vector<std::bitset<8>>&);
std::vector<std::bitset<8>> CamadaFisicaTransmissoraCodificacaoManchesterDiferencial(std::vector<std::bitset<8>>&);

// Recepcao

void CamadaFisicaReceptora();
std::vector<std::bitset<8>> CamadaFisicaReceptoraDecodificacaoBinaria(std::vector<std::bitset<8>>&);
std::vector<std::bitset<8>> CamadaFisicaReceptoraDecodificacaoManchester(std::vector<std::bitset<8>>&);
std::vector<std::bitset<8>> CamadaFisicaReceptoraDecodificacaoManchesterDiferencial(std::vector<std::bitset<8>>&);


// Meio de Comunicacao
void MeioDeComunicacao();
