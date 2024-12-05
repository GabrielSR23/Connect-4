#include <iostream>
#include <iomanip>
#include <string> // Se utilizo para usar variables string.
#include <limits> // Se utilizo para poder hacer input validation de las columnas en referencia a caracteres.
using namespace std;

const int COLS = 7; // Variable constante de columnas.
const int ROWS = 6; // Variable constante de filas.
string Player1 = " X ", Player2 = " O ", Player; // Variables strings de jugadores.
bool end_game = false; // Variable bool para terminar juego si es true.
bool winner = false, draw = false; // Variables bool para verificar el ganador y si hay empate.

void How_To_Play(); // Funcion que explica las reglas.
void Play(string [][COLS],int ROWS); // Funcion que corre el juego.
void DisplayBoard(string [][COLS],int ROWS); //Funcion que despliega la tabla.
void Token(string [][COLS],int ROWS,string); // Funcion para colocar fichas.
void PlayerinTurn(string, string, int &); // Funcion para verificar a que jugador le toca el turno.
bool Check_winner(string [][COLS], int ROWS, int COLS, string Player); // Funcion que verifica si alguien gano.
bool CheckColumnFull(string [][COLS], int ROWS, int ); // Funcion que verifica si la columna esta llena.
bool CheckRow0Full (string [][COLS],int ROWS); // Funcion que verifica si la primera columna esta llena.

int main(){

    bool restart = true; // Variable bool para verificar si quieren volver al menu al fin del juego
    char opcion; // Variable char para opcion de menu.

    while(restart){ // Ciclo de main para volver a enseñar el menu al fin del juego.

        string Game_array[ROWS][COLS] = { // Arreglo de la tabla.
        {" - ", " - ", " - ", " - ", " - ", " - ", " - "}, 
        {" - ", " - ", " - ", " - ", " - ", " - ", " - "}, 
        {" - ", " - ", " - ", " - ", " - ", " - ", " - "},
        { " - ", " - ", " - ", " - ", " - ", " - ", " - "},
        { " - ", " - ", " - ", " - ", " - ", " - ", " - "},
        { " - ", " - ", " - ", " - ", " - ", " - ", " - "}
        };
    
        cout << "Connect Four!\n"; // Titulo
        cout << "A.) Jugar." << endl << "B.) Como jugar." << endl // Opciones de menu.
            << "C.) Salir." << endl << "Oprima opcion: ";
        cin >> opcion;


        while(opcion < 97 || opcion > 99){ // Input validation de opciones.
           cout << "****Opcion invalida!!!!! Ingrese opcion(a, b ó c): ";
           cin >> opcion;
        }

        switch(opcion){ // Estructura switch para menu.
            case 'a':   
               Play(Game_array, ROWS); // Invocacion de play para comenzar secuencia de juego.
               break;

           case 'b':
              How_To_Play(); // Invocacion de How to play para desplegar reglas.
               break;

          case 'c': // Opcion de salir
            restart = false; // Restart es igual a falso para que el ciclo del menu no itere.
            break;
         }

        if(opcion == 'a' || opcion == 'b'){ // Verificar si quieren volver al menu al fin del juego
            char opcion_restart;
            cout << "\nDeseas regresar al menu o volver a jugar?. (S/N): ";
            cin >> opcion_restart;
            cout << endl;
        
            if(opcion_restart == 'N' || opcion_restart == 'n')
                restart = false;
        }
    }

    return 0;
}

void Play(string Game_array[][COLS],int ROWS){

    static int number = 0; // Variable static number para verificar turnos de jugador.

    if(winner || draw){ // Limpia la tabla al fin del juego
        for(int i = 0; i < ROWS; i++)
            for(int j = 0; j < COLS; j++){
                Game_array[i][j] = " - ";
                }

            winner = false;
            draw = false;
            number = 0;
    }

    while(!winner && !draw){ // Ciclo que invoca funciones que corren el juego.
        DisplayBoard(Game_array, ROWS); // Invocacion de DisplayBoard para desplegar la tabla.
        PlayerinTurn(Player1, Player2, number); // Invocacion de Player in turn para verificar turno de jugador.
        Token(Game_array, ROWS, Player); // Invocacion de Token para colocar fichas
        draw = CheckRow0Full(Game_array, ROWS); // Invocacion de CheckRow0Full para chequear si hubo un empate.
        if(draw == true){
            cout << "\nEmpate!";
            break;
        }
    
    if(winner){ // Si winner == true el juego termina.
        DisplayBoard(Game_array, ROWS);
        cout << "\nFelicidades Jugador" << Player << ", has ganado!" << endl;
        }

    if(end_game == true){ // Si el jugador decide salir a mitad de juego con -1 end_game == true y el juego termina.
        cout << "\nGracias por jugar!!!" << endl;
        return;
    }


    }
}

void How_To_Play(){ // Funcion explica reglas del juego y como se juega.
    cout << "\nSConnect 4 es un juego en el cual dos jugadores toman turnos soltando fichas a una de las 7 posible columnas. \nEl primer jugador que tenga cuatro fichas de su color gana el juego."
         << endl << "Las fichas pueden conectarse horizontal, vertical o diagonalmente." << "\nEn este programa puedes escoger la columna en la cual deseas soltar la ficha con los numeros entre 1 al 7.";
}


void DisplayBoard(string Game_array[][COLS], int ROWS){ // Despliega la tabla.
    cout << "\n 1   2   3   4   5   6   7"; // Las columnas en las cual se sueltan las fichas.
    for(int i = 0; i < ROWS; i++){
        cout << "\n";
        for(int j = 0; j < COLS; j++)
            cout << Game_array[i][j] << "|";
    }
}

void Token(string Tok[][COLS],int ROWS, string Player){ // Colocar fichas

    int Column, decrement = 1; // Variable que incrementa si el espacia esta ocupado en la tabla.
    bool Lleno = true; // Variable para ver si la columna esta llena.

    // Input del Usuario.
    cout << "\nJugador " << Player;
    cout << "\nEntra una columna del 1 - " << COLS << " (Para salir de el juego oprima '-1'): ";
    cin >> Column;

    if(Column == -1){
        end_game = true;
        return;
    }

    while(Column < 1 || Column > COLS){ // Input Validation de decision de columna del usuario.
        DisplayBoard(Tok, ROWS);
        cout << "\nEntro un valor invalido" << "\nLas columnas son de 1 a " << COLS << ": " << endl;
        cout << "Jugador" << Player << "Entre una columna del 1 - " << COLS <<  " (Para salir de el juego oprima '-1'): ";
        cin >> Column;
        if(cin.fail()) { // Si el usuario no es un numero entero el cin.fail lo detecta.
            cin.clear(); // cin.clear borra el dato entrado ya que no es un numero entero y hace que cin se pueda volver a utilizar sin salir como fail.
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // cin.ignore ignora el valor entrado y salta a el proximo valor en el keyboard buffer.
            continue; 
        } 

        if(Column == -1){
            end_game = true;
            return;    
        }
    }
       
    Lleno = CheckColumnFull(Tok, ROWS, Column); // Chequea si la columna esta llena

    while(Lleno){ // Ciclo que despliega que esta llena la columna.
        DisplayBoard(Tok, ROWS);
        cout << "\nLa columna que has ingresado esta llena." << Player << " Entre otra columna.";
        cin >> Column;

        if(Column == -1){
            end_game = true;
            return;
        }

        Lleno = CheckColumnFull(Tok, ROWS, Column); // Volver a chequear si esta llena al fin del ciclo.
    }
        

    while(Column < 1 || Column > COLS){ // Input validation.
        DisplayBoard(Tok, ROWS);
        cout << "\nEntro un valor invalido" << "\nLas columnas son de 1 a " << COLS << ": " << endl;
        cout << "Jugador" << Player << "Entre una columna del 1 - " << COLS <<  " (Para salir de el juego oprima '-1'): ";
        cin >> Column;
        if(cin.fail()){ // Si el usuario no es un numero entero el cin.fail lo detecta.
            cin.clear(); // cin.clear borra el dato entrado ya que no es un numero entero y hace que cin se pueda volver a utilizar sin salir como fail.
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // cin.ignore ignora el valor entrado y salta a el proximo valor en el keyboard buffer.
            continue;
        } 

        if(Column == -1){
            end_game = true;
            return;
        }

    }

    if(Lleno){
         draw = CheckRow0Full(Tok, ROWS); // Si las columnas estan llenas se chequea por un empate.
    }

    if(draw){
        return;
    }


// To do: funcion LlenarEspacioVacio()

    while (Tok[ROWS - decrement][Column - 1] == Player1 || Tok[ROWS - decrement][Column - 1] == Player2){ //Encontrar el espacio vacio y llenarlo
        decrement++;    
    }

    DisplayBoard(Tok, ROWS); // Volver a desplegar la tabla

    Tok[ROWS - decrement][Column - 1] = Player;
    winner = Check_winner(Tok, ROWS, COLS, Player); // Chequear si alguien halla ganado.
}

void PlayerinTurn(string Player1, string Player2, int & number){ // Funcion que verifica el turno del jugador.
    if(number % 2 == 0)
        Player = Player1;
    else 
        Player = Player2;
    number++;

}

bool CheckColumnFull(string Tok[][COLS], int ROWS, int Column){ // Funcion que verifica si la columna esta llena.
    for(int i = 0; i < ROWS; i++){
        if (Tok[i][Column-1] == " - "){
            return false;
        }
    }
    return true;
}


bool CheckRow0Full (string Tok[][COLS],int ROWS){ // Funcion que verifica si la primera columna esta llena.
    for(int j = 0; j < COLS; j++){
        if(Tok[0][j] == " - ")
            return false;
    }
    return true;
}

bool Check_winner(string Tok[][COLS], int ROWS, int COLS, string Player){ // Funcion que verifica si alguien ha ganado.

    // Ciclo for que busca si hay cuatro fichas corridas horizontalmente.
    for(int i = 0; i < ROWS; i++){
        for(int j = 0; j < COLS - 3; j++){ // COLS - 3 es para que empieze a buscar en columna que si es posible que hayan cuatro corridos.
            if(Tok[i][j] == Player && Tok[i][j + 1] == Player && Tok[i][j + 2] == Player && Tok[i][j + 3] == Player){
                return true;
            }
        }
    }

    // Ciclo for que busca si hay cuatro fichas corridas verticalmente.
    for(int i = 0; i < ROWS - 3; i++){ // ROWS - 3 es para que empieze a buscar en columna que si es posible que hayan cuatro corridos.
        for(int j = 0; j < COLS; j++){
            if(Tok[i][j] == Player && Tok[i + 1][j] == Player && Tok[i + 2][j] == Player && Tok[i + 3][j] == Player){
                return true;
            }
        }
    }

    // Ciclo que busca si hay cuatro fichas corridas diagonalmente de izquierda a derecha, abajo hacia arriba.
    for(int i = 0; i < ROWS - 3; i++){
        for(int j = 0; j < COLS - 3; j++){
            if(Tok[i][j] == Player && Tok[i + 1][j + 1] == Player && Tok[i + 2][j + 2] == Player && Tok[i + 3][j + 3] == Player){
                return true;
            }
        }
    }

    // Ciclo que busca si hay cuatro fichas corridas diagonalmente de derecha a izquierda, arriba hacia abajo.
    for(int i = 3; i < ROWS; i++){
        for(int j = 0; j < COLS - 3; j++){
            if(Tok[i][j] == Player && Tok[i - 1][j + 1] == Player && Tok[i - 2][j + 2] == Player && Tok[i - 3][j + 3] == Player){
                return true;
            }
        }
    }

    return false;
    
}