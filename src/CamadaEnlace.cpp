#include "CamadaEnlace.h"
#include <iostream>

// Transmissao

void CamadaEnlaceDadosTransmissora(std::vector<bool>& quadro) {
	CamadaEnlaceDadosTransmissoraEnquadramento(quadro);
	CamadaEnlaceDadosTransmissoraControleDeErro(quadro);
	CamadaEnlaceDadosTransmissoraControleDeFluxo(quadro);
	//CamadaFisicaTransmissora();
}

void CamadaEnlaceDadosTransmissoraEnquadramento(std::vector<bool>& quadro) {
	unsigned int tipoDeEnquadramento = 1;
	std::vector<bool> quadroEnquadrado;
	switch (tipoDeEnquadramento) {
		case 0:
			CamadaEnlaceDadosTransmissoraEnquadramentoContagemDeCaracteres(quadro);
			quadroEnquadrado = quadro;
			break;
		case 1:
			CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoDeBytes(quadro);
			quadroEnquadrado = quadro;
			break;
		case 2:
			CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoDeBits(quadro);
			quadroEnquadrado = quadro;
			break;
		case 3:
			CamadaEnlaceDadosTransmissoraEnquadramentoViolacaoDaCamadaFisica(quadro);
			quadroEnquadrado = quadro;
	}
}

void CamadaEnlaceDadosTransmissoraControleDeErro(std::vector<bool>& quadro) {

}

void CamadaEnlaceDadosTransmissoraControleDeFluxo(std::vector<bool>& quadro) {

}

// Transmissao >> Enquadramento

void CamadaEnlaceDadosTransmissoraEnquadramentoContagemDeCaracteres(std::vector<bool>& quadro) {
	std::vector<bool> quadroEnquadrado;						//Quadro onde sera montado o quadro apos contagem
	std::vector<bool> contadorBitsTemp;						//Quadro que guardara o numero de bits que compoe o quadro
	int tamanhoQuadro = quadro.size() / 8;					//Variavel que guardara temporariamente o numero de bits do quadro
	tamanhoQuadro += 1;
	std::cout << tamanhoQuadro<<std::endl;
	while (tamanhoQuadro) {									//Convertendo o tamanho para binario
		contadorBitsTemp.push_back(tamanhoQuadro % 2);
		tamanhoQuadro /= 2;
	}
	while (contadorBitsTemp.size() < 8) {
		contadorBitsTemp.push_back(0);
	}
	reverse(contadorBitsTemp.begin(), contadorBitsTemp.end());
	quadroEnquadrado = contadorBitsTemp;					//Insere o contador no quadro temporario
	for (bool bit : quadro) {								//Insere bit a bit o quadro no quadro temporario
		quadroEnquadrado.push_back(bit);
	}
	quadro = quadroEnquadrado;								//Coloca o quadro temporario montado no quadro
}

void CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoDeBytes(std::vector<bool>& quadro) {
	bool flag[] = { 0,0,0,0,1,1,1,1 };						//Definindo a sequencia de flag
	bool esc[] = { 0,0,1,1,0,0,1,1 };						//Definindo a sequencia de escape
	bool charalloc[8];										//Alocando espaco para a verificacao do char
	bool achaCharEsp;										//Flag para guardar a informacao se o char verificado eh especial	
	std::vector<bool> quadroEnquadrado;
	for (bool bit : flag) {									//Pushando a flag de inicio do quadro
		quadroEnquadrado.push_back(bit);
	}
	for (int i = 0; i < quadro.size(); i++) {				//For para verificar bit a bit
		for (int j = 0; i < quadro.size() && j < 8; i++, j++) {	//For para capturar char a char
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
	quadro = quadroEnquadrado;
}

void CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoDeBits(std::vector<bool>& quadro) {
	bool flag[] = { 0,1,1,1,1,1,1,0 };						//Definindo a flag de inicio e fim
	int seq = 0;											//variavel que guardara sequencias de 1
	std::vector<bool> quadroEnquadrado;
	for (bool bit : flag) {
		quadroEnquadrado.push_back(bit);					//Inserindo a flag de inicio
	}
	for (int i = 0; i < quadro.size(); i++) {
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
	quadro = quadroEnquadrado;
}

void CamadaEnlaceDadosTransmissoraEnquadramentoViolacaoDaCamadaFisica(std::vector<bool>& quadro) {

}

// Transmissao >> Controle de Erro

std::vector<bool> CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar(std::vector<bool>& quadro) {
  int quantidade_de_ums = 0;
  for (bool bit: quadro) {
    if (bit) {
      quantidade_de_ums += 1;
    }
  }

  if (quantidade_de_ums % 2 == 1) {
    quadro.push_back(true);
  } else {
    quadro.push_back(false);
  }

  return quadro;
}


std::vector<bool> CamadaEnlaceDadosTransmissoraControleDeErroBitParidadeImpar(std::vector<bool>& quadro) {
  int quantidade_de_ums = 0;
  for (bool bit: quadro) {
    if (bit) {
      quantidade_de_ums += 1;
    }
  }

  if (quantidade_de_ums % 2 == 0) {
    quadro.push_back(true);
  } else {
    quadro.push_back(false);
  }

  return quadro;
}

void CamadaEnlaceDadosTransmissoraControleDeErroCRC() {

}

void CamadaEnlaceDadosTransmissoraControleDeErroCodigoDeHamming() {

}

// Recepcao

void CamadaEnlaceDadosReceptora() {

}

void CamadaEnlaceDadosReceptoraEnquadramento() {

}

void CamadaEnlaceDadosReceptoraControleDeErro() {

}

void CamadaEnlaceDadosReceptoraControleDeFluxo() {

}

// Recepcao >> Enquadramento

void CamadaEnlaceDadosReceptoraEnquadramentoContagemDeCaracteres() {

}

void CamadaEnlaceDadosReceptoraEnquadramentoInsercaoDeBytes() {

}

void CamadaEnlaceDadosReceptoraEnquadramentoInsercaoDeBits() {

}

void CamadaEnlaceDadosReceptoraEnquadramentoViolacaoDaCamadaFisica() {

}

// Recepcao >> Controle de Erro

std::vector<bool> CamadaEnlaceDadosReceptoraControleDeErroBitParidadePar(std::vector<bool>& quadro) {
  int quantidade_de_ums = 0;
  bool bit_de_paridade = quadro.back();

  quadro.pop_back();
  for (bool bit: quadro) {
    if (bit) {
      quantidade_de_ums += 1;
    }
  }

  if ((quantidade_de_ums % 2 == 1 && bit_de_paridade) ||
      (quantidade_de_ums % 2 == 0 && !bit_de_paridade)) {
    std::cout << "Nao foram detectados problemas no quadro pelo bit de paridade par" << std::endl;
  } else {
    std::cout << "ATENCAO: FORAM detectados problemas no quadro pelo bit de paridade par" << std::endl;
  }

  return quadro;
}

void CamadaEnlaceDadosReceptoraControleDeErroBitParidadeImpar() {

}

void CamadaEnlaceDadosReceptoraControleDeErroCRC() {

}

void CamadaEnlaceDadosReceptoraControleDeErroCodigoDeHamming() {

}
