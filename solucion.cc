#include <solucion.hpp>

void
solucionMultiHilo(std::map<std::string, uint32_t>& histogramaPalabras, uint32_t numHilos)
{
    uint32_t const totalLineas { static_cast<uint32_t>(textoEnMemoria.size()) };   // Cantidad de lineas totales del archivo
    uint32_t const lineasDelta { totalLineas / numHilos };                      // Cantiad de lineas para cada thread para procesar
    uint32_t const totalLineasRelativas { lineasDelta*numHilos };                // Cantidad total de lineas relativas (puede que falten respecto al total)

    // Histogramas para cada thread.
    std::vector<std::map<std::string, uint32_t>> histogramas(numHilos);
    std::vector<std::thread> hilos; // Almacen de threads
    hilos.reserve(numHilos);

    // Rango de lineas para cada thread.
    uint32_t inicio{0}, fin{0};

    // Instanciando threads en el vector y ejecutando.
    for (uint32_t t=0; t<numHilos; ++t)
    {   
        fin = inicio + lineasDelta - 1;
        hilos.emplace_back(procesarArchivo, std::ref(histogramas[t]), inicio, fin); // Construye y ejecuta.
        inicio += lineasDelta;
    }

    // Esperar que todos los threads terminen.
    for (uint32_t t=0; t<numHilos; ++t) hilos[t].join();

    // Consolidar el trabajo de todos los threads.
    for (auto const& palabraHistograma : histogramas)
        for (auto const& [palabra, rep] : palabraHistograma)
            histogramaPalabras[palabra] += rep;

    // Si hubieron lineas sobrantes, consolidarlas.
    auto const leftOverLines { totalLineas - totalLineasRelativas };
    if (leftOverLines) procesarArchivo(histogramaPalabras, totalLineasRelativas, totalLineas-1);
}

std::string
eliminarPuntuacion(const std::string& palabra) 
{
    std::string resultado;

    for (char c : palabra) {
        if (std::isalpha(c)) {
            resultado += c;
        }
    }
    return resultado;
}

// Función para dividir un texto en palabras
std::vector<std::string>
dividirTexto(const std::string &texto) 
{
    std::vector<std::string> palabras;
    std::string palabra;
    std::istringstream iss(texto);

    while (iss >> palabra) {
        
        for (char &c : palabra) {
            c = std::tolower(c);
        }
        
        palabra = eliminarPuntuacion(palabra);
        palabras.push_back(palabra);
    }
    return palabras;
}

void
procesarArchivo(std::map<std::string, uint32_t>& palabraHistograma, uint32_t inicio, uint32_t fin)
{
    for(auto i=inicio; i<=fin; ++i)
    {
        // Dividir cada línea del texto en palabras
        std::vector<std::string> palabras = dividirTexto(textoEnMemoria[i]);
        
        // Incrementar el conteo de cada palabra en el histograma
        for (const std::string& palabra : palabras) palabraHistograma[palabra]++;
    }
}