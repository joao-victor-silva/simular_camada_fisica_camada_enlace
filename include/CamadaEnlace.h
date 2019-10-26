// Transmissao

void CamadaEnlaceDadosTransmissora();
void CamadaEnlaceDadosTransmissoraEnquadramento();
void CamadaEnlaceDadosTransmissoraControleDeErro();
void CamadaEnlaceDadosTransmissoraControleDeFluxo();

// Transmissao >> Enquadramento

void CamadaEnlaceDadosTransmissoraEnquadramentoContagemDeCaracteres();
void CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoDeBytes();
void CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoDeBits();
void CamadaEnlaceDadosTransmissoraEnquadramentoViolacaoDaCamadaFisica();

// Transmissao >> Controle de Erro

void CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar();
void CamadaEnlaceDadosTransmissoraControleDeErroBitParidadeImpar();
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
void CamadaEnlaceDadosReceptoraControleDeErroBitParidadePar();

// Recepcao >> Controle de Erro

void CamadaEnlaceDadosReceptoraControleDeErroBitParidadeImpar();
void CamadaEnlaceDadosReceptoraControleDeErroCRC();
void CamadaEnlaceDadosReceptoraControleDeErroCodigoDeHamming();
