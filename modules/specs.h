#ifndef SPECS_MOD
#define SPECS_MOD
/******************************/
/*Especificações HD           */
/******************************/
#define TRILHA_CILINDRO 5
#define SETOR_TRILHA 60
#define TRILHA_SUPERFICIE 10
#define TAM_SETOR 512//bytes
#define TAM_CLUSTER 4//setores
/******************************/
#define QUANT_MAX_ARQ ( (SETOR_TRILHA*TRILHA_SUPERFICIE*TRILHA_CILINDRO)/TAM_CLUSTER )
/******************************/
#define TEMPO_MEDIO_SEEK 4//ms
#define TEMPO_MIN_SEEK 1//ms
#define TEMPO_MEDIO_LATENCIA 6//ms
#define TEMPO_TRANSFERENCIA 12//ms/trilha
/******************************/

#endif //SPECS_MOD
