#include "CamadaEnlace.h"
#include "CamadaFisica.h"
#include "CamadaAplicacao.h"
#include <iostream>
#include <bitset>
#include <cmath>
#include <algorithm>

// Transmissao

std::vector<bool> CalculaHamming(std::vector<std::vector<int>>& formula, std::vector<bool>& quadro, bool mostraFormula);
std::vector<std::vector<int>> obtemFormulaDeHamming(std::vector<bool>& quadro);
std::vector<bool> isolaBitsDeHamming(std::vector<bool>& quadro);
std::vector<bool> removeBitsDeHamming(std::vector<bool>& quadro);

void CamadaEnlaceDadosTransmissora(std::vector<bool>& quadro, int tipo_de_enquadramento,
                                   int tipo_de_controle_de_erro, int tipo_de_codificacao, int percentual_de_erro) {
  std::vector<bool> quadro_enquadrado = CamadaEnlaceDadosTransmissoraEnquadramento(quadro, tipo_de_enquadramento);
  std::vector<bool> quadro_com_controle_de_erro = CamadaEnlaceDadosTransmissoraControleDeErro(quadro_enquadrado, tipo_de_controle_de_erro);
  std::vector<bool> quadro_com_controle_de_fluxo = CamadaEnlaceDadosTransmissoraControleDeFluxo(quadro_com_controle_de_erro);
	CamadaFisicaTransmissora(quadro_com_controle_de_fluxo,
                           tipo_de_enquadramento, tipo_de_controle_de_erro,
                           tipo_de_codificacao, percentual_de_erro);
}

std::vector<bool> CamadaEnlaceDadosTransmissoraEnquadramento(std::vector<bool>& quadro, int tipoDeEnquadramento) {
	std::vector<bool> quadroEnquadrado;
	switch (tipoDeEnquadramento) {
	case 0:
		quadroEnquadrado = CamadaEnlaceDadosTransmissoraEnquadramentoContagemDeCaracteres(quadro);
		break;
	case 1:
		quadroEnquadrado = CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoDeBytes(quadro);
		break;
	case 2:
		quadroEnquadrado = CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoDeBits(quadro);
		break;
	}

  return quadroEnquadrado;
}

std::vector<bool> CamadaEnlaceDadosTransmissoraControleDeErro(std::vector<bool>& quadro, int tipo_de_controle_de_erro) {
	std::vector<bool> quadroEnquadrado;
	switch (tipo_de_controle_de_erro) {
	case 0:
		quadroEnquadrado = CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar(quadro);
		break;
	case 1:
		quadroEnquadrado = CamadaEnlaceDadosTransmissoraControleDeErroBitParidadeImpar(quadro);
		break;
	case 2:
		quadroEnquadrado = CamadaEnlaceDadosTransmissoraControleDeErroCRC(quadro);
		break;
	case 3:
		quadroEnquadrado = CamadaEnlaceDadosTransmissoraControleDeErroCodigoDeHamming(quadro);
		break;
	}

  return quadroEnquadrado;
}

std::vector<bool> CamadaEnlaceDadosTransmissoraControleDeFluxo(std::vector<bool>& quadro) {
  return quadro;
}

// Transmissao >> Enquadramento

std::vector<bool> CamadaEnlaceDadosTransmissoraEnquadramentoContagemDeCaracteres(std::vector<bool>& quadro) {
	std::vector<bool> quadroEnquadrado;						//Quadro onde sera montado o quadro apos contagem
	std::vector<bool> contadorBitsTemp;						//Quadro que guardara o numero de bits que compoe o quadro
	int tamanhoQuadro = quadro.size() / 8;					//Variavel que guardara temporariamente o numero de bits do quadro
	tamanhoQuadro += 1;
	// std::cout << tamanhoQuadro << std::endl;
	while (tamanhoQuadro) {									//Convertendo o tamanho para binario
		contadorBitsTemp.push_back(tamanhoQuadro % 2);
		tamanhoQuadro /= 2;
	}
	while (contadorBitsTemp.size() < 8) {
		contadorBitsTemp.push_back(0);
	}

	std::reverse(contadorBitsTemp.begin(), contadorBitsTemp.end());
	quadroEnquadrado = contadorBitsTemp;					//Insere o contador no quadro temporario

	for (bool bit : quadro) {								//Insere bit a bit o quadro no quadro temporario
		quadroEnquadrado.push_back(bit);
	}

	std::cout << "Quadro enquadrado: \t\t\t";
	for (bool bit : quadroEnquadrado) {
		bit ? std::cout << "1" : std::cout << "0";
	}
	std::cout << std::endl;

	return quadroEnquadrado;								//Coloca o quadro temporario montado no quadro
}

std::vector<bool> CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoDeBytes(std::vector<bool>& quadro) {
	bool flag[] = { 0,0,0,0,1,1,1,1 };						//Definindo a sequencia de flag
	bool esc[] = { 0,0,1,1,0,0,1,1 };						//Definindo a sequencia de escape
	bool charalloc[8];										//Alocando espaco para a verificacao do char
	bool achaCharEsp;										//Flag para guardar a informacao se o char verificado eh especial	
	std::vector<bool> quadroEnquadrado;
	for (bool bit : flag) {									//Pushando a flag de inicio do quadro
		quadroEnquadrado.push_back(bit);
	}
	for (unsigned int i = 0; i < quadro.size(); i++) {				//For para verificar bit a bit
		for (unsigned int j = 0; i < quadro.size() && j < 8; i++, j++) {	//For para capturar char a char
			charalloc[j] = quadro[i];
		}
		i--;
		achaCharEsp = true;									//Inicializando a flag com true, caso algum char seja
		for (int j = 0; j < 8 && achaCharEsp; j++) {		//diferente da flag, ele ja assumira que o char nao eh
			if (charalloc[j] != flag[j]) {					//uma flag acidental
				achaCharEsp = false;
			}
		}
		if (achaCharEsp) {									//Caso a flag ainda seja true, deve-se pushar um char
			for (bool bit : esc) {							//de escape para o quadro temporario
				quadroEnquadrado.push_back(bit);
			}
		}
		achaCharEsp = true;									//Ira acontecer o mesmo acima, porem agora testanto se
		for (int j = 0; j < 8 && achaCharEsp; j++) {		//o char nao e um esc acidental
			if (charalloc[j] != esc[j]) {
				achaCharEsp = false;
			}
		}
		if (achaCharEsp) {
			for (bool bit : esc) {
				quadroEnquadrado.push_back(bit);
			}
		}
		for (bool bit : charalloc) {						//Ao fim, pusha-se o char do quadro para o temporario
			quadroEnquadrado.push_back(bit);
		}
	}
	for (bool bit : flag) {
		quadroEnquadrado.push_back(bit);					//Insere-se a flag final do quadro
	}

	std::cout << "Quadro enquadrado: \t\t\t";
	for (bool bit : quadroEnquadrado) {
		bit ? std::cout << "1" : std::cout << "0";
	}
	std::cout << std::endl;

	return quadroEnquadrado;
}

std::vector<bool> CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoDeBits(std::vector<bool>& quadro) {
	bool flag[] = { 0,1,1,1,1,1,1,0 };						//Definindo a flag de inicio e fim
	int seq = 0;											//variavel que guardara sequencias de 1
	std::vector<bool> quadroEnquadrado;
	for (bool bit : flag) {
		quadroEnquadrado.push_back(bit);					//Inserindo a flag de inicio
	}
	for (unsigned int i = 0; i < quadro.size(); i++) {
		if (seq == 5) {										//Se encontrou uma sequencia com 5 uns, insira um zero
			quadroEnquadrado.push_back(0);
			seq = 0;
		}
		if (quadro[i] == 1)									//Se encontrou um 1, soma 1 na sequencia
			seq++;
		else												//Se encontrou um 0, zera a sequencia de uns
			seq = 0;
		quadroEnquadrado.push_back(quadro[i]);
	}
	for (bool bit : flag) {									//Inserindo a flag de fim
		quadroEnquadrado.push_back(bit);
	}

	std::cout << "Quadro enquadrado: \t\t\t";
	for (bool bit : quadroEnquadrado) {
		bit ? std::cout << "1" : std::cout << "0";
	}
	std::cout << std::endl;

	return quadroEnquadrado;
}

// Transmissao >> Controle de Erro

std::vector<bool> CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar(std::vector<bool>& quadro) {
  // conta o numero de bits 1 no quadro e se o valor for impar, adiciona um 1, senao adiciona um 0 no final do quadro
	int quantidade_de_ums = 0;
	for (bool bit : quadro) {
		if (bit) {
			quantidade_de_ums += 1;
		}
	}

	if (quantidade_de_ums % 2 == 1) {
    // adiciona 1 ao final do quadro
		quadro.push_back(true);
	} else {
    // adiciona 0 ao final do quadro
		quadro.push_back(false);
	}

	return quadro;
}


std::vector<bool> CamadaEnlaceDadosTransmissoraControleDeErroBitParidadeImpar(std::vector<bool>& quadro) {
  // conta o numero de bits 1 no quadro e se o valor for par, adiciona um 1, senao adiciona um 0 no final do quadro
	int quantidade_de_ums = 0;
	for (bool bit : quadro) {
		if (bit) {
			quantidade_de_ums += 1;
		}
	}

	if (quantidade_de_ums % 2 == 0) {
    // adiciona 1 ao final do quadro
		quadro.push_back(true);
	} else {
    // adiciona 0 ao final do quadro
		quadro.push_back(false);
	}

	return quadro;
}

std::vector<bool> CamadaEnlaceDadosTransmissoraControleDeErroCRC(std::vector<bool>& quadro) {
  // criar um quadro auxiliar com zeros no final para o calculo do crc do quadro
  std::vector<bool> quadro_aux = quadro;
  for (unsigned int i = 0; i < quadro_aux.size(); i++) {
    std::cout << quadro_aux[i];
  }
  std::cout << std::endl << "zeros adicionais: " << std::endl;
  for (int i = 0; i < 32; i++) {
    quadro_aux.push_back(false);
    std::cout << "0";
  }
  std::cout << std::endl;

  // calcula o crc do quadro
  std::vector<bool> crc_resto = DivisaoModulo2(quadro_aux);
  for (unsigned int i = 0; i < crc_resto.size(); i++) {
    std::cout << crc_resto[i];
  }
  std::cout << std::endl;

  // adiciona o crc ao final do quadro
  for (unsigned int i = 0; i < crc_resto.size(); i++) {
    quadro.push_back(crc_resto[i]);
  }

  return quadro;
}

std::vector<bool> DivisaoModulo2(std::vector<bool>& dividendo) {
  // 0x 01 04 C1 1D B7
  // 1 0000 0100 1100 0001 0001 1101 1011 0111
	std::vector<bool> crc32 = {1,0,0,0,0,0,1,0,0,1,1,0,0,0,0,0,1,0,0,0,1,1,1,0,1,1,0,1,1,0,1,1,1};
  unsigned int ultimo_indice_xor = crc32.size();

  std::vector<bool> auxiliar;
  for (unsigned int i = 0; i < ultimo_indice_xor; i++) {
    auxiliar.push_back(dividendo[i]);
  }

  while (ultimo_indice_xor < dividendo.size()) {
    if (auxiliar[0]) {
      auxiliar = XOR(crc32, auxiliar);
      auxiliar.push_back(dividendo[ultimo_indice_xor]);
    } else {
      std::vector<bool> div_todos_zeros(ultimo_indice_xor, false);
      auxiliar = XOR(div_todos_zeros, auxiliar);
      auxiliar.push_back(dividendo[ultimo_indice_xor]);
    }
    ultimo_indice_xor++;
  }

  if (auxiliar[0]) {
    auxiliar = XOR(crc32, auxiliar);
  } else {
    std::vector<bool> div_todos_zeros(ultimo_indice_xor, false);
    auxiliar = XOR(div_todos_zeros, auxiliar);
  }

  return auxiliar;
}

std::vector<bool> XOR(std::vector<bool>& x, std::vector<bool>& y) {
  std::vector<bool> xor_resultado;
  for (unsigned int i = 1; i < y.size(); i++) {
    if (x[i] == y[i]) {
      xor_resultado.push_back(false);
    } else {
      xor_resultado.push_back(true);
    }
  }
  return xor_resultado;
}

std::vector<bool> CamadaEnlaceDadosTransmissoraControleDeErroCodigoDeHamming(std::vector<bool>& quadro) {
	// std::vector<bool> quadroEnquadrado;									//Quadro temporário para efetuar as operacoes
	// quadroEnquadrado.push_back(0);										//Pushando os dois primeiros bits de paridade
	// quadroEnquadrado.push_back(0);
	// for (unsigned int i = 3, j = 3; i < quadro.size() + 3; i++, j++) {	//Pushando os bits do quadro
	// 	if (log2(j) == (int)log2(j)) {									//Caso seja um bit de controle, pushar um zero
	// 		quadroEnquadrado.push_back(0);
	// 		j++;
	// 	}
	// 	quadroEnquadrado.push_back(quadro[i - 3]);
	// }
	// for (unsigned int i = 3; i < quadro.size(); i++) {
	// 	if (log2(i) != (int)log2(i)) {									//Se nao for um bit de controle
	// 		int icopia = i;												//Copia do i para poder fazer operacoes
	// 		int j = 1;													//Variavel que diz qual eh o bit de controle
	// 		while (icopia && quadro[i]) {								//Enquanto a copia do i nao zerar, deve fazer
	// 			if (icopia % 2 && quadro[i]) {							//um shift de um bit e ver se o carry eh 1 ou 0
	// 				quadroEnquadrado[j - 1] = !quadroEnquadrado[j - 1];	//visto que isso diz quais bits de mensagem
	// 			}														//participa da constituicao dos bits de controle
	// 			j *= 2;													//Pula para o proximo bit de controle
	// 			icopia /= 2;											//Desloca os bits novamente
	// 		}
	// 	}																//Inverte-se o bit a cada 1 para manter a paridade
	// }
	// return quadroEnquadrado;											//Atribui o quadro temporario ao quadro

	unsigned int contadorQuadro = 0;         // contador de 0 ate o quantidade de bits do quadro - 1
	unsigned int contadorVerificacao = 0;    // quantidade de bits de verificacao
	unsigned int contadorGeral = 1;          // contador de 3 ate o (quantidade de bits de verificacao + quantidade de bits do quadro) - 1 
	std::vector<std::vector<int>> formula;
	std::vector<bool> quadroComHamming;

	// monta o quadro com hamming e as formulas dos bits de verificacao
	while (contadorQuadro < quadro.size()) {
		unsigned int potenciaDeDois = 1;
		for (unsigned int i = 0; i < contadorVerificacao; i++) {
			potenciaDeDois = potenciaDeDois * 2;
		}

		// se o contadorGeral for uma potencia de 2 
		if (contadorGeral == potenciaDeDois) {
			// adiciona um novo bit de verificacao (nova formula)
			// p(2 ^ n)
			std::vector<int> vetor;
			formula.push_back(vetor);
			// bitsDeVerificacao.push_back(false);
			// adiciona bit de verificacao com valor 0, sera alterado apos o calculo utilizando as formulas
			quadroComHamming.push_back(false);
			contadorVerificacao++;
		// se o contadorGeral NAO for uma potencia de 2 
		} else {
			// converte o contadorGeral em potencia de 2 (binario)
			std::bitset<32> indiceEmBinario(contadorGeral);
			for (int i = 0; i < 32; i++) {
				// se o bit de indice i do contadorGeral for 1, o bit do quadro faz parte da formula do bit de verificacao de indice i
				if (indiceEmBinario[i] == 0b1) {
					formula[i].push_back(contadorGeral);
				}
			}
			quadroComHamming.push_back(quadro[contadorQuadro]);
			contadorQuadro++;
		}

		contadorGeral++;
	}

	std::cout << "quantidade de formulas: " << formula.size() << std::endl;

	for (unsigned int i = 0; i < formula.size(); i++) {
		// calcula o indice do bit de verificacao
		unsigned int potenciaDeDois = 1;
		for (unsigned int k = 0; k < i; k++) {
			potenciaDeDois = potenciaDeDois * 2;
		}

		std::cout << "P" << potenciaDeDois << " = ";
		bool bit = false;
		for (unsigned int j = 0; j < formula[i].size(); j++) {
			std::cout << "M" << formula[i][j] << " ";
			if (quadroComHamming[formula[i][j] - 1]) {
				bit = !bit;
			}
			if (j < formula[i].size() - 1) {
				std::cout << "+ ";
			}
		}

		std::cout << " => ";
		if (bit) {
			std::cout << "1";
		} else {
			std::cout << "0";
		}
		std::cout << std::endl;

		quadroComHamming[potenciaDeDois - 1] = bit;
	}

	return quadroComHamming;
}

// Recepcao

void CamadaEnlaceDadosReceptora(std::vector<bool>& quadro, int tipo_de_enquadramento, int tipo_de_controle_de_erro, int tipo_de_codificacao) {
  std::vector<bool> quadro_com_controle_de_fluxo = CamadaEnlaceDadosReceptoraControleDeFluxo(quadro);
  std::vector<bool> quadro_com_controle_de_erro = CamadaEnlaceDadosReceptoraControleDeErro(quadro_com_controle_de_fluxo, tipo_de_controle_de_erro);
  std::vector<bool> quadro_enquadrado = CamadaEnlaceDadosReceptoraEnquadramento(quadro_com_controle_de_erro, tipo_de_enquadramento);

  CamadaDeAplicacaoReceptora(quadro_enquadrado);
}

std::vector<bool> CamadaEnlaceDadosReceptoraEnquadramento(std::vector<bool>& quadro, int tipoDeEnquadramento) {
	std::vector<bool> quadroEnquadrado;
	switch (tipoDeEnquadramento) {
	case 0:
		quadroEnquadrado = CamadaEnlaceDadosReceptoraEnquadramentoContagemDeCaracteres(quadro);
		break;
	case 1:
		quadroEnquadrado = CamadaEnlaceDadosReceptoraEnquadramentoInsercaoDeBytes(quadro);
		break;
	case 2:
		quadroEnquadrado = CamadaEnlaceDadosReceptoraEnquadramentoInsercaoDeBits(quadro);
		break;
	}

  return quadroEnquadrado;
}

std::vector<bool> CamadaEnlaceDadosReceptoraControleDeErro(std::vector<bool>& quadro, int tipo_de_controle_de_erro) {
	std::vector<bool> quadroEnquadrado;
	switch (tipo_de_controle_de_erro) {
	case 0:
		quadroEnquadrado = CamadaEnlaceDadosReceptoraControleDeErroBitParidadePar(quadro);
		break;
	case 1:
		quadroEnquadrado = CamadaEnlaceDadosReceptoraControleDeErroBitParidadeImpar(quadro);
		break;
	case 2:
		quadroEnquadrado = CamadaEnlaceDadosReceptoraControleDeErroCRC(quadro);
		break;
	case 3:
		quadroEnquadrado = CamadaEnlaceDadosReceptoraControleDeErroCodigoDeHamming(quadro);
		break;
	}

  return quadroEnquadrado;
}

std::vector<bool> CamadaEnlaceDadosReceptoraControleDeFluxo(std::vector<bool>& quadro) {
  return quadro;
}

// Recepcao >> Enquadramento

std::vector<bool> CamadaEnlaceDadosReceptoraEnquadramentoContagemDeCaracteres(std::vector<bool>& quadro) {
	std::bitset<8> guardaContadorTemp;									//Variavel para guardar o contador temporariamente
	unsigned long int tamanhoQuadro = 0;								//Inteiro onde sera convertido o contador pra inteiro
	for (int i = 0; i < 8; i++) {										//Pegando os 8 bits que formam o contador
		guardaContadorTemp[i] = quadro[i];
	}
	quadro.erase(quadro.begin(), quadro.begin() + 8);					//Retirando o contador do quadro
	tamanhoQuadro = guardaContadorTemp.to_ulong();						//Convertendo os bits em inteiro
	if (quadro.size() / 8 != tamanhoQuadro) {							//Caso sejam diferentes, significa que o contador está errado
		std::cout << "Contagem errada dos caracteres" << std::endl;
	}

  return quadro;
}

std::vector<bool> CamadaEnlaceDadosReceptoraEnquadramentoInsercaoDeBytes(std::vector<bool>& quadro) {
	std::vector<bool> charTemp;											//Variavel para guardar o byte temporariamente
	bool flag[] = { 0,0,0,0,1,1,1,1 };									//Sequencia de flag de inicio/fim
	bool esc[] = { 0,0,1,1,0,0,1,1 };									//Sequencia de escape
	bool continua = true;												//Variavel que dira se ainda tem byte a ser lido
	bool achouEsc;									//Variaveis que dizem se o ultimo char era esc
	for (int i = 0; i < 8; i++) {										//Capturando a flag de inicio
		charTemp.push_back(quadro[i]);
	}
	for (int i = 0; i < 8; i++) {
		if (charTemp[i] != flag[i]) {									//Isso significa que a flag de inicio foi enviada errada
			std::cout << "Erro na flag de inicio" << std::endl;
			break;
		}
	}
	quadro.erase(quadro.begin(), quadro.begin() + 8);
	for (int i = 0; continua; i+=8) {									//For para pegar byte a byte do quadro
		charTemp.clear();												//Limpar o vetor para guardar o novo byte
		for (int j = 0; j < 8; j++) {									//Copiando o byte para o vetor de testes
			charTemp.push_back(quadro[i + j]);
		}
		achouEsc = true;												//Parte do pressuposto que eh um esc, se achar
		for (int j = 0; j < 8 && achouEsc; j++) {						//um bit diferente, deduz-se o contrario
			if (esc[j] != charTemp[j]) {
				achouEsc = false;
			}
		}
		if (achouEsc) {													//Se o byte atual, eh um esc, deve-se excluir
			quadro.erase(quadro.begin() + i, quadro.begin() + i + 8);	//o mesmo do quadro e com o erase o proximo ja eh ignorado
		}
		else {															//Se nao for um esc, deve-se testar se eh a
			for (int j = 0; j < 8 && flag[j] == charTemp[j]; j++) {		//flag de fim, deve-se dizer para o loop finalizar
				if (j == 7) {											//e apagar a flag do quadro
					continua = false;
					quadro.erase(quadro.begin() + i, quadro.begin() + i + 8);
				}
			}
		}
	}
  return quadro;
}

std::vector<bool> CamadaEnlaceDadosReceptoraEnquadramentoInsercaoDeBits(std::vector<bool>& quadro) {
	std::vector<bool> charTemp;											//Variavel para guardar o byte temporariamente
	bool flag[] = { 0,1,1,1,1,1,1,0 };									//Definindo a sequencia de flag
	bool continua = true;
	unsigned int seq = 0;
	for (int i = 0; i < 8; i++) {										//Capturando a flag de inicio
		charTemp.push_back(quadro[i]);
	}
	for (int i = 0; i < 8; i++) {
		if (charTemp[i] != flag[i]) {									//Isso significa que a flag de inicio foi enviada errada
			std::cout << "Erro na flag de inicio" << std::endl;
			break;
		}
	}
	quadro.erase(quadro.begin(), quadro.begin() + 8);					//Removendo a flag do inicio
	for (int i = 0; continua; i++) {									//Loop que roda ate achar a flag de fim
		if (quadro[i]) {												//Se o bit atual for 1, incrementa o contador
			seq++;
		}
		else {															//Senao zera o contador
			seq = 0;
		}
		if (seq == 5 && !quadro[i + 1]) {								//Se ja tem 5 uns e o proximo eh um zero,
			quadro.erase(quadro.begin() + i + 1);						//deve-se ignorar o zero, visto que foi
		}																//inserido no algoritmo de encapsulamento.
		if (seq == 6) {													//Se tem 6 uns, significa que achou a flag
			quadro.erase(quadro.begin() + i - 7, quadro.begin() + i + 1);//de fim, logo a flag deve ser removida e
			continua = false;											//o loop finalizado.
		}
	}

  return quadro;
}

// Recepcao >> Controle de Erro

std::vector<bool> CamadaEnlaceDadosReceptoraControleDeErroBitParidadePar(std::vector<bool>& quadro) {
	int quantidade_de_ums = 0;
	bool bit_de_paridade = quadro.back();

	quadro.pop_back();
	for (bool bit : quadro) {
		if (bit) {
			quantidade_de_ums += 1;
		}
	}

	if ((quantidade_de_ums % 2 == 1 && bit_de_paridade) ||
		(quantidade_de_ums % 2 == 0 && !bit_de_paridade)) {
		std::cout << "Nao foram detectados problemas no quadro pelo bit de paridade par" << std::endl;
	}
	else {
		std::cout << "ATENCAO: FORAM detectados problemas no quadro pelo bit de paridade par" << std::endl;
	}

	return quadro;
}

std::vector<bool> CamadaEnlaceDadosReceptoraControleDeErroBitParidadeImpar(std::vector<bool>& quadro) {
	int quantidade_de_ums = 0;
	bool bit_de_paridade = quadro.back();

	quadro.pop_back();
	for (bool bit : quadro) {
		if (bit) {
			quantidade_de_ums += 1;
		}
	}

	if ((quantidade_de_ums % 2 == 0 && bit_de_paridade) ||
		(quantidade_de_ums % 2 == 1 && !bit_de_paridade)) {
		std::cout << "Nao foram detectados problemas no quadro pelo bit de paridade impar" << std::endl;
	}
	else {
		std::cout << "ATENCAO: FORAM detectados problemas no quadro pelo bit de paridade impar" << std::endl;
	}

	return quadro;
}

std::vector<bool> CamadaEnlaceDadosReceptoraControleDeErroCRC(std::vector<bool>& quadro) {
  // calcula o crc do quadro
  std::vector<bool> crc_resto = DivisaoModulo2(quadro);

  int quantidade_de_ums = 0;

  for (bool bit: crc_resto) {
    if (bit) {
      quantidade_de_ums += 1;
    }
  }

  if (quantidade_de_ums > 0) {
    std::cout << "ATENCAO: FORAM detectados problemas no quadro pelo CRC" << std::endl;
  } else {
    std::cout << "Nao foram detectados problemas no quadro pelo CRC" << std::endl;
  }

  std::vector<bool> quadro_sem_crc;
  for (unsigned int i = 0; i < quadro.size() - 32; i++) {
    quadro_sem_crc.push_back(quadro[i]);
  }

  return quadro_sem_crc;
}

std::vector<bool> CamadaEnlaceDadosReceptoraControleDeErroCodigoDeHamming(std::vector<bool>& quadro) {
	std::vector<bool> bitsDeVerificacaoRecebidos;
	std::vector<bool> bitsDeVerificacaoCalculados;
	std::vector<bool> quadroSemHamming;
	std::vector<std::vector<int>> formula;
	std::vector<bool> quadroAuxiliar = quadro;
	std::vector<bool> quadroCorrigido = quadro;
	int quantidadeDeBitsDeVerificacaoErrados = 0;
	unsigned int contadorVerificacao = 0;    // quantidade de bits de verificacao
	unsigned int contadorGeral = 1;          // contador de 3 ate o (quantidade de bits de verificacao + quantidade de bits do quadro) - 1 

	// obtem a formula necessaria para o calculo do Hamming do quadro
	formula = obtemFormulaDeHamming(quadro);

	// calcula os bits de verificacao apartir do quadro recebido
	bitsDeVerificacaoCalculados = CalculaHamming(formula, quadro, true);


	// isola os bits de Hamming que foram recebidos no quadro
	bitsDeVerificacaoRecebidos = isolaBitsDeHamming(quadro);


	for (int j = 0; j < formula.size(); j++) {
		if (bitsDeVerificacaoCalculados[j] != bitsDeVerificacaoRecebidos[j]) {
			quantidadeDeBitsDeVerificacaoErrados++;
		}
	}

	if (quantidadeDeBitsDeVerificacaoErrados == 1) {
		std::cout << "Bits Verificacao Errados: ";
		for (unsigned int i = 0; i < formula.size(); i++) {
			unsigned int potenciaDeDois = 1;
			for (unsigned int k = 0; k < i; k++) {
				potenciaDeDois = potenciaDeDois * 2;
			}

			if (bitsDeVerificacaoCalculados[i] != bitsDeVerificacaoRecebidos[i]) {
				std::cout << "P" << potenciaDeDois << " ";
				quadroCorrigido[potenciaDeDois - 1] = !bitsDeVerificacaoRecebidos[i];
			} else {
				quadroCorrigido[potenciaDeDois - 1] = bitsDeVerificacaoRecebidos[i];
			}
		}
		std::cout << std::endl;
	} 

	// inicia a correcao dos bits errados do quadro
	std::cout << "Bits errados: ";
	for (int i = 1; i < quadro.size() + 1; i++) {
		// verifica as formulas em que o bit do quadro ocorre e quais destas formulas estao erradas
		std::vector<int>::iterator it; 
		int emListasDeParidade = 0;
		int emListasDeParidadeErradas = 0;
		for (int j = 0; j < formula.size(); j++) {
			it = std::find(formula[j].begin(), formula[j].end(), i);
			if (it != formula[j].end()) {
				// conta em quantas formulas o bit do quadro esta
				emListasDeParidade++;
				if (bitsDeVerificacaoCalculados[j] != bitsDeVerificacaoRecebidos[j]) {
					// conta quantas delas estao erradas
					emListasDeParidadeErradas++;
				}
			}
		}
		// se um bit do quadro esta em todas as formulas erradas (dos bits de paridade errados) e apenas nelas
		if (emListasDeParidadeErradas == quantidadeDeBitsDeVerificacaoErrados &&
			emListasDeParidadeErradas == emListasDeParidade &&
			emListasDeParidadeErradas > 1) {
			std::cout << "M" << i << " ";
			// inverte o bit
			quadroCorrigido[i - 1] = !quadro[i - 1];
		} else {
			// caso contrario mantem o bit
			quadroCorrigido[i - 1] = quadro[i - 1];
		}
	}
	std::cout << std::endl;

	quadroSemHamming = removeBitsDeHamming(quadroCorrigido);

	contadorVerificacao = 0;    // quantidade de bits de verificacao
	contadorGeral = 1;          // contador de 3 ate o (quantidade de bits de verificacao + quantidade de bits do quadro) - 1 
	std::cout << "quadro sem hamming: ";
	for (unsigned int i = 0; i < quadroSemHamming.size(); i++) {
		if (quadroSemHamming[i]) {
			std::cout << "1";
		} else {
			std::cout << "0";
		}
	}
	std::cout << std::endl;

	return quadroSemHamming;
}


std::vector<bool> CalculaHamming(std::vector<std::vector<int>>& formula, std::vector<bool>& quadro, bool mostraFormula) {
	std::vector<bool> bitsDeParidadeCalculados;
	if (mostraFormula) {
		std::cout << "quantidade de formulas: " << formula.size() << std::endl;
	}

	for (unsigned int i = 0; i < formula.size(); i++) {
		// calcula o indice do bit de verificacao
		unsigned int potenciaDeDois = 1;
		for (unsigned int k = 0; k < i; k++) {
			potenciaDeDois = potenciaDeDois * 2;
		}

		if (mostraFormula) {
			std::cout << "P" << potenciaDeDois << " = ";
		}

		bool bit = false;
		for (unsigned int j = 0; j < formula[i].size(); j++) {
			if (quadro[formula[i][j] - 1]) {
				bit = !bit;
			}

			if (mostraFormula) {
				std::cout << "M" << formula[i][j] << " ";
				if (j < formula[i].size() - 1) {
					std::cout << "+ ";
				}
			}
		}

		if (mostraFormula) {
			std::cout << " => ";
			if (bit) {
				std::cout << "1";
			} else {
				std::cout << "0";
			}
			std::cout << std::endl;
		}

		bitsDeParidadeCalculados.push_back(bit);
	}

	return bitsDeParidadeCalculados;
}


std::vector<std::vector<int>> obtemFormulaDeHamming(std::vector<bool>& quadro) {
	unsigned int contadorVerificacao = 0;    // quantidade de bits de verificacao
	unsigned int contadorGeral = 1;          // contador de 3 ate o (quantidade de bits de verificacao + quantidade de bits do quadro) - 1 
	std::vector<std::vector<int>> formula;

	while (contadorGeral <= quadro.size()) {
		unsigned int potenciaDeDois = 1;
		for (unsigned int i = 0; i < contadorVerificacao; i++) {
			potenciaDeDois = potenciaDeDois * 2;
		}

		// se o contadorGeral for uma potencia de 2 
		if (contadorGeral == potenciaDeDois) {
			std::vector<int> vetor;
			formula.push_back(vetor);
			contadorVerificacao++;
		// se o contadorGeral NAO for uma potencia de 2 
		} else {
			// converte o contadorGeral em potencia de 2 (binario)
			std::bitset<32> indiceEmBinario(contadorGeral);
			for (int i = 0; i < 32; i++) {
				// se o bit de indice i do contadorGeral for 1, o bit do quadro faz parte da formula do bit de verificacao de indice i
				if (indiceEmBinario[i] == 0b1) {
					formula[i].push_back(contadorGeral);
				}
			}
		}

		contadorGeral++;
	}

	return formula;
}

std::vector<bool> removeBitsDeHamming(std::vector<bool>& quadro) {
	unsigned int contadorVerificacao = 0;    // quantidade de bits de verificacao
	unsigned int contadorGeral = 1;          // contador de 3 ate o (quantidade de bits de verificacao + quantidade de bits do quadro) - 1 
	std::vector<bool> quadroSemHamming;

	while (contadorGeral <= quadro.size()) {
		unsigned int potenciaDeDois = 1;
		for (unsigned int i = 0; i < contadorVerificacao; i++) {
			potenciaDeDois = potenciaDeDois * 2;
		}

		// se o contadorGeral for uma potencia de 2 
		if (contadorGeral != potenciaDeDois) {
			quadroSemHamming.push_back(quadro[contadorGeral - 1]);
		} else {
			contadorVerificacao++;
		}
		contadorGeral++;
	}

	return quadroSemHamming;
}


std::vector<bool> isolaBitsDeHamming(std::vector<bool>& quadro) {
	unsigned int contadorVerificacao = 0;    // quantidade de bits de verificacao
	unsigned int contadorGeral = 1;          // contador de 3 ate o (quantidade de bits de verificacao + quantidade de bits do quadro) - 1 
	std::vector<bool> bitsDeHamming;

	while (contadorGeral <= quadro.size()) {
		unsigned int potenciaDeDois = 1;
		for (unsigned int i = 0; i < contadorVerificacao; i++) {
			potenciaDeDois = potenciaDeDois * 2;
		}

		// se o contadorGeral for uma potencia de 2 
		if (contadorGeral == potenciaDeDois) {
			bitsDeHamming.push_back(quadro[contadorGeral - 1]);
			contadorVerificacao++;
		} 
		contadorGeral++;
	}

	return bitsDeHamming;
}
