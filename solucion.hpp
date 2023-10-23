#pragma once
#include <global.hh>

void solucionMultiHilo(std::map<std::string, uint32_t>&, uint32_t numThreads);
void procesarArchivo(std::map<std::string, uint32_t>&, uint32_t begin, uint32_t end);

// funciones de ayuda
std::string eliminarPuntuacion(const std::string&);
std::vector<std::string> dividirTexto(const std::string&);


// Variable global del texto con el que se trabaje (conjunto de lineas de un texto).
inline std::vector<std::string> textoEnMemoria;

