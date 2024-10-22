#include <iostream>
#include <string>
#include <time.h>
#include <Windows.h>
void main()
{
#pragma region VARIABLES 1
	srand(time(NULL));
	const int size = 10;
	char playerBoard[size][size] = {};
	char opponentBoard[size][size] = {};
	char playerBoardBoats[size][size] = {};
	char opponentBoardBoats[size][size] = {};
	int boats[] = { 3, 4, 5, 6 }; //Creo 4 tablas distintas, 2 en las que no se veran los barcos, y otras que si mostraran los barcos.
#pragma endregion

#pragma region TABLAS
	std::cout << "Bienvenido a hundir la flota!" << std::endl;
	std::cout << "_____________________________" << std::endl;
	std::cout << "\n" << std::endl; //Mensaje inicial

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			playerBoard[i][j] = '~';
			opponentBoard[i][j] = '~';
			playerBoardBoats[i][j] = '~';
			opponentBoardBoats[i][j] = '~'; //Se define que todas las tablas tengan agua
		}
	}
#pragma endregion

#pragma region COLOCAR BARCOS AUTOMATICAMENTE
	for (int i = 0; i < 4; i++) { //Contador de barcos a poner
		int boatSize = boats[i];
		bool placed = false;

		while (!placed) {
			int row = rand() % size;
			int column = rand() % size;
			bool orientation = rand() % 2; //Dice en que orientacion se van a colocar los barcos. True es horizontal.
			bool casillaLibre = true; //Estas variables se inician para poder ejecutar la colocacion 

			if (orientation) {
				if (column + boatSize <= size) {
					for (int i = 0; i < boatSize; i++) {
						if (playerBoardBoats[row][column + i] != '~') {
							casillaLibre = false;  //Si en horizontal alguna de las casillas delante de la posicion aleatoria no es agua se marca como que no hay casillas libres
						}
					}
					if (casillaLibre) {
						for (int i = 0; i < boatSize; i++) {
							playerBoardBoats[row][column + i] = '0' + boatSize;
						}
						placed = true; // Si en horizontal el barco cabe, se coloca y se marca como colocado
					}
				}
			}
			else {
				if (row + boatSize <= size) {
					for (int i = 0; i < boatSize; i++)
					{
						if (playerBoardBoats[row + i][column] != '~') {
							casillaLibre = false;
						}
					}
					if (casillaLibre) {
						for (int i = 0; i < boatSize; i++) {
							playerBoardBoats[row + i][column] = '0' + boatSize;
						}
						placed = true; //Lo mismo que antes pero en vertical
					}
				}
			}
		}
	}
	for (int i = 0; i < 4; i++) {
		int boatSize = boats[i];
		bool placed = false;

		while (!placed) {
			int row = rand() % size;
			int column = rand() % size;
			bool orientation = rand() % 2;
			bool casillaLibre = true;

			if (orientation) {
				if (column + boatSize <= size) {
					for (int i = 0; i < boatSize; i++) {
						if (opponentBoardBoats[row][column + i] != '~') {
							casillaLibre = false;
						}
					}
					if (casillaLibre) {
						for (int i = 0; i < boatSize; i++) {
							opponentBoardBoats[row][column + i] = '0' + boatSize;
						}
						placed = true;
					}
				}
			}
			else {
				if (row + boatSize <= size) {
					for (int i = 0; i < boatSize; i++)
					{
						if (opponentBoardBoats[row + i][column] != '~') {
							casillaLibre = false;
						}
					}
					if (casillaLibre) {
						for (int i = 0; i < boatSize; i++) {
							opponentBoardBoats[row + i][column] = '0' + boatSize;
						}
						placed = true; //Todo esto es lo mismo que antes pero para la tabla del oponente
					}
				}
			}
		}
	}

	std::cout << "Tablero Jugador 1" << std::endl;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			std::cout << playerBoardBoats[i][j] << " ";
		}
		std::cout << std::endl; // Se muestra la tabla del jugador
	}
	std::cout << "\n";

	std::cout << "Tablero Jugador 2" << std::endl;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			std::cout << opponentBoardBoats[i][j] << " ";
		}
		std::cout << std::endl; // Se muestra la tabla del oponente
	}
#pragma endregion

#pragma region GAMEPLAY
	int pointsP1 = 0; //Se crea una variable que es la puntuacion para los jugadores
	int pointsP2 = 0;

	while (pointsP1 < 18 && pointsP2 < 18) { //Comprovacion de puntos
		int positionX;
		int positionY; //Posiciones
		int turno = 0; //Turno de jugador

		if (turno == 0) {
			std::cout << "TURNO JUGADOR 1" << std::endl;
			std::cout << " " << std::endl;
			std::cout << "Escoje la posicion horizontal: ";
			std::cin >> positionX; //Se escoje la posicion en el turno del jugador 1

			while (positionX > size || positionX < 1) {
				std::cout << "Posicion horizontal no valida, introduce otra: ";
				std::cin >> positionX; //Si no es valida se vuelve a pedir
			}
			std::cout << "Escoje la posicion vertical: ";
			std::cin >> positionY; //Si es valida se pide la horizontal

			while (positionY > size || positionY < 1) {
				std::cout << "Posicion vertical no valida, introduce otra: ";
				std::cin >> positionY; //Si no es valida se vuelve a pedir
			}
			if (opponentBoardBoats[positionX-1][positionY-1] != '~') { //Se pone -1 para que vaya del 1 al 10
				system("cls");
				opponentBoard[positionX-1][positionY-1] = 'X'; //Se pone -1 para que vaya del 1 al 10
				pointsP1++;
				std::cout << "Has acertado!" << std::endl; //Si se ha escogido la posicion de un barco se acierta
			}
			else {
				system("cls");
				opponentBoard[positionX-1][positionY-1] = 'O';
				std::cout << "Has fallado!" << std::endl;
				std::cout << "\n"; //Si no se ha escogido la posicion de un barco se falla
			}
			turno++; //El turno pasa al jugador 2
			std::cout << "Tablero Jugador 1" << std::endl;
			for (int i = 0; i < size; i++) {
				for (int j = 0; j < size; j++) {
					std::cout << playerBoard[i][j] << " ";
				}
				std::cout << std::endl; // Se muestra la tabla del jugador
			}
			std::cout << "\n";

			std::cout << "Tablero Jugador 2" << std::endl;
			for (int i = 0; i < size; i++) {
				for (int j = 0; j < size; j++) {
					std::cout << opponentBoard[i][j] << " ";
				}
				std::cout << std::endl; // Se muestra la tabla del oponente
			}
		}
		if (turno == 1) {
			std::cout << "TURNO JUGADOR 2" << std::endl;
			std::cout << " " << std::endl;
			std::cout << "Escoje la posicion horizontal: ";
			std::cin >> positionX; //Se escoje la posicion en el turno del jugador 2

			while (positionX > size || positionX < 1) {
				std::cout << "Posicion horizontal no valida, introduce otra: ";
				std::cin >> positionX; //Si no es valida se vuelve a pedir
			}
			std::cout << "Escoje la posicion vertical: ";
			std::cin >> positionY; //Si es valida se pide la horizontal

			while (positionY > size || positionY < 1) {
				std::cout << "Posicion vertical no valida, introduce otra: ";
				std::cin >> positionY; //Si no es valida se vuelve a pedir
			}
			if (playerBoardBoats[positionX-1][positionY-1] != '~') {
				system("cls");
				playerBoard[positionX-1][positionY-1] = 'X';
				pointsP2++;
				std::cout << "Has acertado!" << std::endl; //Si se ha escogido la posicion de un barco se acierta
			}
			else {
				system("cls");
				playerBoard[positionX-1][positionY-1] = 'O';
				std::cout << "Has fallado!" << std::endl; //Si no se ha escogido la poisicion de un barco se falla
			}
			turno--;
			std::cout << "Tablero Jugador 1" << std::endl;
			for (int i = 0; i < size; i++) {
				for (int j = 0; j < size; j++) {
					std::cout << playerBoard[i][j] << " ";
				}
				std::cout << std::endl; // Se muestra la tabla del jugador
			}
			std::cout << "\n";

			std::cout << "Tablero Jugador 2" << std::endl;
			for (int i = 0; i < size; i++) {
				for (int j = 0; j < size; j++) {
					std::cout << opponentBoard[i][j] << " ";
				}
				std::cout << std::endl;
				// Se muestra la tabla del oponente
			}
		}
	}
	if (pointsP1 == 18) {
		std::cout << "El JUGADOR 1 ha ganado la partida!!";
	}
	else {
		std::cout << "El JUGADOR 2 ha ganado la partida!!";
	}
#pragma endregion
}