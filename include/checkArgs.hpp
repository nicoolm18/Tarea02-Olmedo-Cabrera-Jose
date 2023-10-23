#ifndef _CHECKARGS_H_
#define _CHECKARGS_H_

#include <unistd.h>

extern char *optarg;
extern int optind, opterr, optopt;

class checkArgs {
private:
	// 1) Modificar esta sección
	const std::string optString = "t:f:h";
	
	const std::string opciones = "-t threads -f file [-h]";

	const std::string descripcion  = "Descripción:\n"
		                             "\t-t   Cantidad de threads a utilizar. Si es 1, entonces ejecuta la version secuencial.\n"
									 "\t-f   Archivo a procesar.\n"
									 "\t-h   Muestra esta ayuda y termina.\n";
	
	typedef struct args_t {
		uint32_t numHilos;
		std::string archivo;
	} args_t;
	
	// 2) Modificar constructor
	// 3) Modificar ciclo "getopt" en método checkArgs::getArgs()
	// 4) Recuerde que para compilar nuevamente, y por tratarse
	//    de un archivo header, debe hacer primero un make clean
	
	args_t  parametros;
	
	int argc;
	char **argv;

	
public:
	checkArgs(int _argc, char **_argv);
	~checkArgs();
	args_t getArgs();
	
private:
	void printUsage();
	
	
};

checkArgs::checkArgs(int _argc, char**_argv){
	parametros.numHilos = 0;
	parametros.archivo     = "";

	argc = _argc;
	argv = _argv;
	
}

checkArgs::~checkArgs(){}

checkArgs::args_t checkArgs::getArgs(){
	int opcion = 0;
	
	while ( (opcion = getopt(argc, argv, optString.c_str())) != -1){
		switch (opcion) {
			case 't':
					parametros.numHilos = atoi(optarg);
					break;
			case 'f':
					parametros.archivo = optarg;
					break;
			case 'h':
			default:
					printUsage();
					exit(EXIT_FAILURE);
		}
	}

	if ( parametros.numHilos  == 0 
		|| parametros.archivo      == "" )
	{
		printUsage();
		exit(EXIT_FAILURE);
	}
	
	return parametros;
}

void checkArgs::printUsage(){
	std::cout << "Uso: " <<
		argv[0] << " " << opciones << " " << descripcion << std::endl;
}


#endif
