#include <solucion.hpp>
#include <checkArgs.hpp>


int main(int argc, char** argv)
{
    // Obtener argumentos
    checkArgs args{argc, argv};
    auto const [ numHilos, nombreArchivo ] = args.getArgs();

    // Verificar archivo
    std::ifstream archivo(nombreArchivo);
    if (!archivo) {
        std::cerr << "No se pudo abrir el archivo." << std::endl;
        return EXIT_FAILURE;
    }

    // Cargar texto a memoria
    std::string linea;
    while (std::getline(archivo, linea)) textoEnMemoria.push_back(linea);
    archivo.close();
    
    std::map<std::string, uint32_t> histogramaPalabras;

    try {
        solucionMultiHilo(histogramaPalabras, numHilos);
        //throw std::runtime_error("Ha ocurrido un error con la solución");
    }
    catch (const std::exception& e) {
        std::cerr << "Se ha producido una excepción: " << std::endl;
        return EXIT_FAILURE;
    }


    // Mostrar el histograma de palabras
    for (auto const& [palabra, rep] : histogramaPalabras)
        std::cout << palabra << ": " << rep << '\n';


    return EXIT_SUCCESS;
}

